#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pButton_Bar_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    int s;
public slots:
    void onTimeout();
};
#endif // MAINWINDOW_H
