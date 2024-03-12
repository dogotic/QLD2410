#include "utils.h"
#include "ld2410_frame.h"

void displayFrame(const ld2410_frame& frame)
{
    qDebug() << "Target status: " << frame.target_status;
    qDebug() << "Movement Target Distance (cm):" << frame.movement_target_distance_cm;
    qDebug() << "Moving Target Energy:" << static_cast<int>(frame.moving_target_energy);
    qDebug() << "Stationary Target Distance (cm):" << frame.stationary_target_distance_cm;
    qDebug() << "Stationary Target Energy:" << static_cast<int>(frame.stationary_target_energy);
    qDebug() << "Detection Distance (cm):" << frame.detection_distance_cm;
}

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
