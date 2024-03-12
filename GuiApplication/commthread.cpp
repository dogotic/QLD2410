#include <QDebug>
#include "commthread.h"

CommThread::CommThread(QObject *parent) :
    QThread(parent),
    m_stopRequested(false)
{
    // Configure serial port settings here if needed
}

CommThread::~CommThread()
{
    stop();
}

void CommThread::run()
{
    while (!m_stopRequested) {
        if (m_port.waitForReadyRead(100)) {
            //emit dataReceived(m_port.readAll());
            qDebug() << m_port.readAll();
        }
    }
}

void CommThread::stop()
{
    m_stopRequested = true;
    m_port.close();
}
