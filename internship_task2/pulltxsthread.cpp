#include "pulltxsthread.h"

PullTXsThread::PullTXsThread(const QString& _address) :
    PullTXsThread(_address, false, false, false, false)
{}

PullTXsThread::PullTXsThread(const QString &_address, bool _ign_int_txs,
                                                     bool _ign_coms,
                                                     bool _ign_zv_txs,
                                                     bool _inc_adr):
    is_terminated(false),
    address(_address),
    API_KEY("KMUQF21Z97Y1RI98HTYX5YESXAQCA22XN7"),
    ign_int_txs(_ign_int_txs),
    ign_coms(_ign_coms),
    ign_zv_txs(_ign_zv_txs),
    inc_adr(_inc_adr)
{}

PullTXsThread::~PullTXsThread() {
    wait();
}

void PullTXsThread::run(const QString& filename) {
    if (!filename.isEmpty()) {
        try {
            new(&writer)excel_writer(filename);
        }
        catch (const std::runtime_error& e) {
            emit pass_error(e.what());
            return;
        }
        pass_info("Start downloading. Please, wait...");
        writer.write_headers();
        write_header_row();
    }
    request(NORMAL, filename);
    if (!ign_int_txs)
        request(INTERNAL, filename);
    if (!filename.isEmpty()) {
        writer.write_endings();
        pass_info("Downloading is finished.");
    }
}

void PullTXsThread::write_header_row() {
    QStringList list;
    list.append("Date/time");
    if (inc_adr)
        list.append("Another address");
    list.append("Amount (eth)");
    if (!ign_coms)
        list.append("Commission (eth)");
    writer.write_row(list);
}

void PullTXsThread::request(request_mode mode, const QString& filename) {
    int page_number = 1;
    QJsonObject req_result;
    //if (mode == NORMAL)
    //    emit upd_gui_signal("-------Normal transactions-------\n", 0);
    //else
    //    emit upd_gui_signal("-------Internal transactions-------\n", 0);

    while (!is_terminated) {
        req_result = request_page(page_number++, mode);
        if (!req_result.contains("result"))
            break;
        if (req_result["message"].toString() != "OK") {
            emit pass_error(req_result["result"].toString());
            break;
        }
        QVariantMap json_map = req_result.toVariantMap();
        QVariantList arr = json_map["result"].toList();
        if (arr.isEmpty())
            break;

        QMap<QString, QVariant> fields;
        for (int i = 0; i < arr.count(); ++i) {
            fields = arr[i].toMap();
            double input_tx_sum = 0;
            if (ign_zv_txs && fields["value"].toInt() == 0)
                continue;
            if (filename.isEmpty()) {
                QString res = build_by_map(input_tx_sum, fields);
                emit upd_gui_signal(res, input_tx_sum);
            }
            else {
                auto res = build_row_params(fields);
                writer.write_row(res);
            }
        }
    }
}

QString PullTXsThread::timestamp_to_qstr(long long timestamp) {
    QDateTime dt;
    dt.setTime_t(timestamp);
    return dt.toString(Qt::SystemLocaleShortDate);
}

QStringList PullTXsThread::build_row_params(const QMap<QString, QVariant> &map) {
    auto value_str = map["value"].toString();
    double value = wei_str_to_eth(value_str).toDouble();
    QStringList out;
    out.append(timestamp_to_qstr(map["timeStamp"].toLongLong()));
    if (inc_adr) {
        out.append(QString::compare(map["from"].toString(), address, Qt::CaseInsensitive) == 0
                ? map["to"].toString() : map["from"].toString());
    }
    out.append(QString::number(value, 'g', 12));
    if (!ign_coms) {
        auto gas_price_str = map["gasPrice"].toString();
        out.append(QString::number(wei_str_to_eth(gas_price_str).toDouble() *
                                   map["gasUsed"].toLongLong(), 'g', 12));
    }
    return out;
}

QString PullTXsThread::build_by_map(double& inp_sum, QMap<QString, QVariant> const& map) {
    auto value_str = map["value"].toString();
    double value = wei_str_to_eth(value_str).toDouble();
    if (QString::compare(map["to"].toString(), address, Qt::CaseInsensitive) == 0) {
        inp_sum = value;
    }
    QString out;

    QString str_timestamp = timestamp_to_qstr(map["timeStamp"].toLongLong());
    out = "Date/time: " + str_timestamp + "\n" +
          "Transaction type: " + (QString::compare(map["from"].toString(), address, Qt::CaseInsensitive) == 0
            ? "send" : "receive") + ".\n";
    if (inc_adr) {
        out += "Another address: " +
                (QString::compare(map["from"].toString(), address, Qt::CaseInsensitive) == 0
                ? map["to"].toString() : map["from"].toString()) + "\n";
    }
    out += "Amount: " + QString::number(value, 'g', 12) + " eth.\n";
    if (!ign_coms) {
        auto gas_price_str = map["gasPrice"].toString();
          out += "Commission: " + QString::number(wei_str_to_eth(gas_price_str).toDouble() *
                  map["gasUsed"].toLongLong(), 'g', 12) + " eth.\n";
    }
    out += "\n";
    return out;
}

QJsonObject PullTXsThread::request_page(int page_number, request_mode mode) {
    QNetworkAccessManager manager;
    QEventLoop ql;
    QTimer t;
    t.setSingleShot(true);
    connect(&t, SIGNAL(timeout()), &ql, SLOT(quit()));
    connect(&manager, SIGNAL(finished(QNetworkReply*)), &ql, SLOT(quit()));
    QString url = QString("https://api.etherscan.io/api?module=account&action=txlist%1&address=%2&"
                          "startblock=0&endblock=blockNo&page=%3&offset=100&"
                          "sort=asc&apikey=%4").arg((mode == INTERNAL ? "internal" : ""),
                                                    address, QString::number(page_number), API_KEY);
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(url)));
    t.start(10000);
    ql.exec();
    if (t.isActive()) {
        t.stop();
    } else {
        emit pass_error("Internet connection problems. Please, try again");
    }

    QByteArray byte_arr = reply->readAll();
    QString result = QString::fromUtf8(byte_arr.data(), byte_arr.size());
    return json_from_str(result);
}

QJsonObject PullTXsThread::json_from_str(const QString& in)
{
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());

    if (!doc.isNull()) {
        if (doc.isObject())
            obj = doc.object();
        else {
            emit pass_error("Server returned invalid response");
        }
    }
    else {
        emit pass_error("Server returned invalid response");
    }

    return obj;
}

QString PullTXsThread::wei_str_to_eth(QString str) {
    int size = str.size();
    if (size <= 18) {
        QString zeros;
        zeros.fill('0', 18 - size);
        return "0." + zeros + str;
    }
    else {
        int point_pos = size - 18;
        return str.left(point_pos) + "." + str.right(point_pos);
    }
}
