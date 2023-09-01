#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "stopwatch.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    stopwatch = new StopWatch(this);
    ui->setupUi(this);

    ui->pB_circle->setEnabled(false);
    ui->pB_circle->setText("Круг");

    ui->pB_clear->setText("Очистить");

    ui->pB_start->setCheckable(true);
    ui->pB_start->setText("Старт");

    connect(stopwatch, &StopWatch::sig_updateTime, this, &MainWindow::rcv_updateTime);
    connect(this, &MainWindow::sig_circleTime, stopwatch, &StopWatch::rcv_circleTime);
    connect(this, &MainWindow::sig_clearTime, stopwatch, &StopWatch::rcv_clearTime);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rcv_updateTime(QString text)
{
    ui->lb_time->setText(text);
}

void MainWindow::on_pB_start_clicked()
{
    if(ui->pB_start->isChecked()) {

        stopwatch->startTimer();
        ui->pB_start->setText("CTOP");
        ui->pB_circle->setEnabled(true);
    }
    else
    {
        stopwatch->stopTimer();
        ui->pB_start->setText("CTAPT");
        ui->pB_circle->setEnabled(false);
    }
}

void MainWindow::on_pB_circle_clicked()
{
    emit sig_circleTime();
    QString text = stopwatch->strCircleTime;
    ui->tB_time->append(text);
}

void MainWindow::on_pB_clear_clicked()
{
    ui->lb_time->setText("00:00.0");
    emit sig_clearTime();
}
