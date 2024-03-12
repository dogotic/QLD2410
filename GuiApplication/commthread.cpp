#include <QDebug>
#include <QDebug>
#include <QSerialPort>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cstring>
#include <QByteArray>
#include <QtEndian>

#include "commthread.h"
#include "ld2410_frame.h"
#include "utils.h"

CommThread::CommThread(QObject *parent) :
    QThread(parent),
    m_stopRequested(false)
{

}

CommThread::~CommThread()
{
    stop();
}

bool CommThread::openPort(QString portPath)
{
    m_Port.setPortName(portPath);
    m_Port.setBaudRate(256000);
    m_Port.setDataBits(QSerialPort::Data8);
    m_Port.setParity(QSerialPort::NoParity);
    m_Port.setStopBits(QSerialPort::OneStop);
    m_Port.open(QIODevice::ReadOnly);

    return m_Port.isOpen();
}

void CommThread::run()
{
    QObject::connect(&m_Port, &QSerialPort::readyRead, [&]() {
        QByteArray data = m_Port.readAll();
        if (data.length() == 23) {
            QString hexString;
            for (int i = 0; i < data.size(); ++i) {
                hexString.append(QString("%1 ").arg(static_cast<unsigned char>(data.at(i)), 2, 16, QChar('0')).toUpper());
            }
            // qDebug() << "Received data in hex ( " <<data.size() << "bytes received ) " <<  ":" << hexString.trimmed();
            ld2410_frame frame = mapDataToFrame(data);
            emit sendDataFrame(frame);
        }
    });
}

void CommThread::stop()
{
    m_stopRequested = true;
    if (m_Port.isOpen())
    {
        m_Port.close();
    }
}
