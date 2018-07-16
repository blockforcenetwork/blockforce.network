#include "excel_writer.h"

excel_writer::excel_writer(const QString &filename) {
    new(&file)QFile(filename);
    if (!file.open(QIODevice::WriteOnly)) {
       throw std::runtime_error("Unable to open file");
    }
    new(&out)QTextStream(&file);
}

void excel_writer::write_headers() {
    QString headers ="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
           "<?mso-application progid=\"Excel.Sheet\"?>\n"
           "<Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\" "
           "xmlns:x=\"urn:schemas-microsoft-com:office:excel\"\n xmlns:ss=\""
           "urn:schemas-microsoft-com:office:spreadsheet\" "
           "xmlns:html=\"http://www.w3.org/TR/REC-html40\">\n"
           "<Worksheet ss:Name=\"CognaLearn+Intedashboard\">\n"
           "<Table>\n<Column ss:Index=\"1\" ss:AutoFitWidth=\"0\" ss:Width=\"110\"/>";
    out << headers << endl;
}

void excel_writer::write_row(QStringList &list) {
    out << "<Row>" << endl;
    for (QString& str: list) {
        out << "<Cell><Data ss:Type=\"String\">" + str + "</Data></Cell>" << endl;
    }
    out << "</Row>" << endl;
}

void excel_writer::write_endings() {
    QString endings = "</Table>\n"
                      "</Worksheet>\n"
                      "</Workbook>";
    out << endings << endl;
}
