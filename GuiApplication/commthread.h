#ifndef COMMTHREAD_H
#define COMMTHREAD_H

#include <QThread>
#include <QSerialPort>

class CommThread : public QThread
{
    Q_OBJECT
public:
    explicit CommThread(QObject *parent = nullptr);
    ~CommThread();

    void run() override;

    void stop();

signals:
    void dataReceived(const QByteArray &data);

private:
    bool m_stopRequested;
    QSerialPort m_port;
};


#endif // COMMTHREAD_H
