#ifndef _AQI_H
#define _AQI_H

#include <Arduino.h>

int calculateCOAQI(float co_ppm);
int calculatePM25AQI(float pm25_mg_per_m3);

#endif