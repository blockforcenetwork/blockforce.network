#ifndef EXCEL_WRITER_H
#define EXCEL_WRITER_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class excel_writer {
public:
    explicit excel_writer() = default;

    excel_writer(const QString& filename);

    void write_headers();

    void write_endings();

    void write_row(QStringList&);

private:
    QFile file;
    QTextStream out;
};

#endif // EXCEL_WRITER_H
