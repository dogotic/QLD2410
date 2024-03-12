#ifndef COMMTHREAD_H
#define COMMTHREAD_H

#include <QThread>
#include <QSerialPort>
#include "ld2410_frame.h"

class CommThread : public QThread
{
    Q_OBJECT
public:
    explicit CommThread(QObject *parent = nullptr);
    ~CommThread();
    void setPort(QSerialPort *port);
    void run() override;
    bool openPort(QString portPath);
    void stop();

signals:
    void sendDataFrame(ld2410_frame frame);

private:
    bool m_stopRequested;
    QSerialPort m_Port;
    QString m_portName;
};


#endif // COMMTHREAD_H
