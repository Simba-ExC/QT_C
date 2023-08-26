#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <Qtimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    s = 2;
    ui->rButton_1->setText("Выбери меня");
    ui->rButton_2->setText("Нет меня");
    ui->groupBox->setTitle("Тайтл или название");
    for (int i=1; i<=12; ++i)
    {
        ui->cBox_month->addItem(QString("Месяц %1").arg(i));
    }
    ui->cBox_month->currentIndex();
    ui->cBox_month->currentText();
    ui->pButton_Bar->setCheckable(true);
    ui->pButton_Bar->setText("Нажми на меня");
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(10);
    ui->progressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pButton_Bar_toggled(bool checked)
{
    if (checked)
    {
        ui->pButton_Bar->setText("+10%");
        qDebug()<<"Button Checked -- ON--";
        int value = ui->progressBar->value();
        ui->progressBar->setValue(value+1);
        timer = new QTimer(this); // сделал таймер, ждем 2 секунды и возвращаем кнопку в исходное положение
        s = 2;
        connect (timer, SIGNAL(timeout()), this , SLOT (onTimeout()));
        timer->start(1000);
    }
    else
    {
        ui->pButton_Bar->setText("Нажми на меня");
        qDebug()<<"Button Un Checked -- OFF--";
    }
}

void MainWindow::onTimeout()
{
    qDebug()<<s;
    ui->pButton_Bar->setText(QString("+10%,%1").arg(s));
    s--;
    if (s == -1)
    {
        timer->stop();
        ui->pButton_Bar->toggled(false); // передаем значение кнопки, что она выключена
        ui->pButton_Bar->setCheckable(false); // перезапускаем кнопку, если так не сделать, то надо будет нажимать по 2 раза
        ui->pButton_Bar->setCheckable(true);
        int value = ui->progressBar->value();
        if (value == 10)
        {
            QMessageBox msg;
            msg.setText("А всё! Конец.");
            msg.setIcon(QMessageBox::Information);
            msg.setStandardButtons(QMessageBox::Yes);
            msg.setDefaultButton(QMessageBox::Yes);
            msg.setWindowTitle("Обнуляем до нуля.");
            msg.show();
            if (msg.exec() == QMessageBox::Yes)
            {
                ui->progressBar->setValue(0);
            }
        }
    }

}

