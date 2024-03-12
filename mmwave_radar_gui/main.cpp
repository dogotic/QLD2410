#include <QCoreApplication>
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

struct ld2410_frame {
    uint8_t     start_of_frame[4];
    uint16_t    data_length;
    uint8_t     data_type;
    uint8_t     intra_frame_head;
    uint8_t     target_status;
    uint16_t    movement_target_distance_cm;
    uint8_t     moving_target_energy;
    uint16_t    stationary_target_distance_cm;
    uint8_t     stationary_target_energy;
    uint16_t    detection_distance_cm;
    uint8_t     intra_frame_tail;
    uint8_t     calibration;
    uint8_t     end_of_frame[4];
};

ld2410_frame mapDataToFrame(const QByteArray& data) {
    ld2410_frame frame;

    // Copy data to the frame structure
    frame.start_of_frame[0] = data[0];
    frame.start_of_frame[1] = data[1];
    frame.start_of_frame[2] = data[2];
    frame.start_of_frame[3] = data[3];

    frame.data_length = data[5] << 8 | data[4]; // Convert from big-endian to host byte order
    frame.data_type = data[6];
    frame.intra_frame_head = data[7];
    frame.target_status = data[8];
    frame.movement_target_distance_cm = (data[10] << 8) | data[9];
    frame.moving_target_energy = data[11];
    frame.stationary_target_distance_cm = (data[13] << 8) | data[12];
    frame.stationary_target_energy = data[14];
    frame.detection_distance_cm = (data[16] << 8) | data[15];
    frame.calibration = data[17];
    frame.intra_frame_tail = data[18];

    frame.end_of_frame[0] = data[19];
    frame.end_of_frame[1] = data[20];
    frame.end_of_frame[2] = data[21];
    frame.end_of_frame[3] = data[22];

    return frame;
}

void displayFrame(const ld2410_frame& frame) {
    qDebug() << "Target status: " << frame.target_status;
    qDebug() << "Movement Target Distance (cm):" << frame.movement_target_distance_cm;
    qDebug() << "Moving Target Energy:" << static_cast<int>(frame.moving_target_energy);
    qDebug() << "Stationary Target Distance (cm):" << frame.stationary_target_distance_cm;
    qDebug() << "Stationary Target Energy:" << static_cast<int>(frame.stationary_target_energy);
    qDebug() << "Detection Distance (cm):" << frame.detection_distance_cm;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSerialPort serial;
    serial.setPortName("/dev/ttyUSB0");
    serial.setBaudRate(256000);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.open(QIODevice::ReadOnly);

    if (!serial.isOpen()) {
        qDebug() << "Failed to open serial port.";
        return 1;
    }

    qDebug() << "Serial port opened successfully.";

    QObject::connect(&serial, &QSerialPort::readyRead, [&]() {
        QByteArray data = serial.readAll();
        if (data.length() == 23) {
            QString hexString;
            for (int i = 0; i < data.size(); ++i) {
                hexString.append(QString("%1 ").arg(static_cast<unsigned char>(data.at(i)), 2, 16, QChar('0')).toUpper());
            }
            qDebug() << "Received data in hex ( " <<data.size() << "bytes received ) " <<  ":" << hexString.trimmed();
            ld2410_frame frame = mapDataToFrame(data);
            displayFrame(frame);
        }
    });

    return a.exec();
}
