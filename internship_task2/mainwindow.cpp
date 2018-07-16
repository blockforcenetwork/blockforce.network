#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scroll_area_padding(10),
    layout(new QVBoxLayout),
    scroll_widget(new QWidget),
    total(0),
    income_total(0),
    total_label("Total: "),
    income_total_label("Incoming Txs Total: ")
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/eth.png"));
    connect(ui->button_show, SIGNAL(released()), this, SLOT(handle_button_show()));
    connect(ui->button_save_as, SIGNAL(released()), this, SLOT(handle_button_save_as()));

    scroll_widget->setLayout(layout);
    ui->scrollArea->setWidget(scroll_widget);

    ui->label_error_msg->setStyleSheet("QLabel { color : red; }");

    upd_total_label(0);
    upd_income_label(0);

}

void MainWindow::handle_button_show() {
   handle_button("");
}

void MainWindow::handle_button_save_as() {
    QString fileName = QFileDialog::getSaveFileName(this,
           tr("Save Transaction History"), "",
           tr("Excel (*.xls);;All Files (*)"));
    if (fileName.isEmpty())
           return;
    handle_button(fileName);
}

void MainWindow::handle_button(const QString& filename) {
    set_to_default_state();
    const QString address = ui->textfield_address->text();
    new(&pull_thr)PullTXsThread(address, ui->checkBox_ign_internal->isChecked(),
                                    ui->checkBox_ign_cms->isChecked(),
                                    ui->checkBox_ign_zv->isChecked(),
                                    ui->checkBox_inc_address->isChecked());

    connect(&pull_thr, SIGNAL(upd_gui_signal(QString, double)),
            this, SLOT(upd_scroll_area(QString, double)));
    connect(&pull_thr, SIGNAL(pass_error(QString)),
            this, SLOT(set_err_lbl(QString)));
    connect(&pull_thr, SIGNAL(pass_info(QString)),
            this, SLOT(set_info_lbl(QString)));
    pull_thread_f = QtConcurrent::run(&pull_thr, &PullTXsThread::run, filename);
}

void MainWindow::set_to_default_state() {
    if (pull_thread_f.isRunning())
        pull_thr.is_terminated = true;
    ui->label_total->setText(total_label + "0");
    ui->label_txs_count->setText(income_total_label + "0 eth");
    ui->label_error_msg->setText("");
    total = 0;
    income_total = 0;
    clear_layout(layout);
}

MainWindow::~MainWindow()
{
    delete layout;
    delete scroll_widget;
    delete ui;
}

void MainWindow::upd_scroll_area(const QString &str, const double& income_sum) {
    upd_total_label(1);
    upd_income_label(income_sum);
    QLabel* lbl = new QLabel;
    lbl->setText(str);
    lbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lbl->setGeometry(10, 10, 350, 100);
    layout->addWidget(lbl);
}

void MainWindow::set_err_lbl(const QString &msg) {
    if (msg.isEmpty())
        return;
    ui->label_error_msg->setText(msg);
    //set_to_default_state();
}

void MainWindow::set_info_lbl(const QString &msg) {
    if (msg.isEmpty())
        return;
    ui->label_info_msg->setText(msg);
    //set_to_default_state();
}

void MainWindow::upd_total_label(long long _total) {
    ui->label_total->setText(total_label + QString::number(total + _total));
    total += _total;
}

void MainWindow::upd_income_label(double sum) {
    ui->label_txs_count->setText(income_total_label +
                                 QString::number(income_total + sum, 'g', 12) + " eth");
    income_total += sum;
}

void MainWindow::clear_layout(QLayout* _layout) {
    QLayoutItem *item;
    while((item = _layout->takeAt(0))) {
        if (item->layout()) {
            clear_layout(item->layout());
            delete item->layout();
        }
        delete item->widget();
    }
}
