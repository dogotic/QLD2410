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
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Connect_clicked()
{
    if (m_DeviceConnected)
    {
        if (m_Port.isOpen())
        {
            m_comThread.stop();
            m_Port.close();
            m_DeviceConnected = false;
            ui->pushButton_Connect->setText("CONNECT");
            qDebug() << "Serial Port Closed succesfully";
        }
    }
    else
    {
        qDebug() << ui->comboBox_SerialPorts->currentText();
        m_Port.setPortName(ui->comboBox_SerialPorts->currentText());
        m_Port.setBaudRate(256000);
        m_Port.setDataBits(QSerialPort::Data8);
        m_Port.setParity(QSerialPort::NoParity);
        m_Port.setStopBits(QSerialPort::OneStop);
        m_Port.open(QIODevice::ReadOnly);
        m_comThread.start();

        if (!m_Port.isOpen())
        {
            qDebug() << "Failed to open serial port.";
            m_DeviceConnected = false;
            ui->pushButton_Connect->setText("CONNECT");
        }
        else
        {
            qDebug() << "Serial Port Openned succesfully";
            m_DeviceConnected = true;
            ui->pushButton_Connect->setText("DISCONNECT");
        }
    }
}

