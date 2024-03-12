#ifndef UTILS_H
#define UTILS_H

#include "ld2410_frame.h"

void displayFrame(const ld2410_frame& frame);
ld2410_frame mapDataToFrame(const QByteArray& data);

#endif // UTILS_H
