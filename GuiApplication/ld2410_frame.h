#ifndef LD2410_FRAME_H
#define LD2410_FRAME_H

#include <QDebug>
#include <inttypes.h>

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

#endif // LD2410_FRAME_H
