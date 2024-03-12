#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    ui->comboBox_SerialPorts->clear(); // Clear previous entries
    foreach(const QSerialPortInfo &port, ports) {
        ui->comboBox_SerialPorts->addItem(port.portName());
    }
    connect(&m_comThread,SIGNAL(sendDataFrame(ld2410_frame)),this,SLOT(frameReceived(ld2410_frame)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Connect_clicked()
{
    QString currentPortName = ui->comboBox_SerialPorts->currentText();
    if (!m_DeviceConnected)
    {
        bool retval = m_comThread.openPort("/dev/" + currentPortName);
        if (retval)
        {
            m_comThread.start();
            m_DeviceConnected = true;
            ui->pushButton_Connect->setText("DISCONNECT");
        }
        else
        {
            m_comThread.stop();
            m_DeviceConnected = false;
            ui->pushButton_Connect->setText("CONNECT");
        }
    }
    else
    {
        m_comThread.stop();
        m_DeviceConnected = false;
        ui->pushButton_Connect->setText("CONNECT");
    }
}

void MainWindow::frameReceived(ld2410_frame frame)
{
    ui->label_MovingTargetDistance->setText(QString::number(frame.movement_target_distance_cm));
    ui->label_movingTargetEnergy->setText(QString::number(frame.moving_target_energy));
    ui->label_stationaryTargetDistance->setText(QString::number(frame.stationary_target_distance_cm));
    ui->label_stationaryTargetEnergy->setText(QString::number(frame.stationary_target_energy));
}

