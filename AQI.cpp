#include "AQI.h"

int calculateCOAQI(float co_ppm) 
{
  randomSeed(analogRead(0));
  float co_mig = co_ppm * (28 * 1000 / 24.45);

  float coAQI = 0;
  if (co_mig >= 0 && co_mig <= 54) 
  {
    coAQI = map(co_mig, 0, 54, 0, 50); 
  }
  else if (co_mig > 54 && co_mig <= 154) 
  {
    coAQI = map(co_mig, 54.1, 154, 51, 100); 
  }
  else if (co_mig > 154 && co_mig <= 254) 
  {
    coAQI = map(co_mig, 154.1, 254, 101, 150); 
  }
  else if (co_mig > 254 && co_mig <= 354) 
  {
    coAQI = map(co_mig, 254.1, 354, 151, 200); 
  }
  else if (co_mig > 354 && co_mig <= 424) 
  {
    coAQI = map(co_mig, 354.1, 424, 201, 300); 
  }
  else if (co_mig > 424 && co_mig <= 604) 
  {
    coAQI = map(co_mig, 424.1, 604, 301, 500); 
  }
  else 
  {
    coAQI = 700;
  }
  return coAQI;
}

int calculatePM25AQI(float pm25_mg_per_m3) 
{
  randomSeed(analogRead(0));
  float pm25_ug_per_m3 = pm25_mg_per_m3 * 1000;

  float pm25AQI = 0;
  if (pm25_ug_per_m3 >= 0 && pm25_ug_per_m3 <= 54) 
  {
    pm25AQI = map(pm25_ug_per_m3, 0, 54, 0, 50);
  }
  else if (pm25_ug_per_m3 > 54 && pm25_ug_per_m3 <= 154) 
  {
    pm25AQI = map(pm25_ug_per_m3, 54.1, 154, 51, 100); 
  }
  else if (pm25_ug_per_m3 > 154 && pm25_ug_per_m3 <= 254) 
  {
    pm25AQI = map(pm25_ug_per_m3, 154.1, 254, 101, 150);
  }
  else if (pm25_ug_per_m3 > 254 && pm25_ug_per_m3 <= 354) 
  {
    pm25AQI = map(pm25_ug_per_m3, 254.1, 354, 151, 200); 
  }
  else if (pm25_ug_per_m3 > 354 && pm25_ug_per_m3 <= 424) 
  {
    pm25AQI = map(pm25_ug_per_m3, 354.1, 424, 201, 300); 
  }
  else if (pm25_ug_per_m3 > 424 && pm25_ug_per_m3 <= 604) 
  {
    pm25AQI = map(pm25_ug_per_m3, 424.1, 604, 301, 500); 
  }
  else 
  {
    pm25AQI = 700;
  }
  return pm25AQI;
}
