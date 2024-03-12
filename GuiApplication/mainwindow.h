#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "commthread.h"
#include "ld2410_frame.h"

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
    void on_pushButton_Connect_clicked();
    void frameReceived(ld2410_frame frame);

private:
    Ui::MainWindow *ui;
    bool m_DeviceConnected = false;
    CommThread m_comThread;
};
#endif // MAINWINDOW_H
