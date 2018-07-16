#ifndef PULLTXSTHREAD_H
#define PULLTXSTHREAD_H

#include <QThread>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>
#include <QFileDialog>
#include <cassert>

#include "excel_writer.h"

class PullTXsThread : public QObject
{
    Q_OBJECT
public:
    bool is_terminated;

    PullTXsThread() = default;

    PullTXsThread(const QString& address);

    PullTXsThread(const QString& address, bool _ign_int_txs,
                                          bool _ign_coms,
                                          bool _ign_zv_txs,
                                          bool _inc_adr);

    ~PullTXsThread();

    void run(const QString&);

signals:
    void upd_gui_signal(const QString&, const double&);
    void pass_error(const QString&);
    void pass_info(const QString&);

private:
    QString address;
    QString API_KEY;

    bool ign_int_txs;
    bool ign_coms;
    bool ign_zv_txs;
    bool inc_adr;

    excel_writer writer;

    enum request_mode { NORMAL, INTERNAL };

    void request(request_mode, const QString&);

    QJsonObject request_page(int page_number, request_mode mode);

    QJsonObject json_from_str(const QString&);

    QString build_by_map(double&, QMap<QString, QVariant> const&);

    QString wei_str_to_eth(QString);

    QStringList build_row_params(QMap<QString, QVariant> const&);

    QString timestamp_to_qstr(long long timestamp);

    void write_header_row();

};

#endif // PULLTXSTHREAD_H
