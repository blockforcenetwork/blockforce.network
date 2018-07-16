#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include "pulltxsthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void handle_button_show();
    void handle_button_save_as();
    void upd_scroll_area(const QString&, const double&);
    void set_err_lbl(const QString&);
    void set_info_lbl(const QString&);

private:
    Ui::MainWindow *ui;

    int scroll_area_padding;
    QVBoxLayout *layout;
    QWidget *scroll_widget;

    long long total;
    double income_total;

    QString total_label;
    QString income_total_label;

    QNetworkAccessManager manager;
    PullTXsThread pull_thr;
    QFuture<void> pull_thread_f;

    void upd_total_label(long long);
    void upd_income_label(double);

    void set_to_default_state();
    void clear_layout(QLayout*);

    void handle_button(const QString&);
};

#endif // MAINWINDOW_H
