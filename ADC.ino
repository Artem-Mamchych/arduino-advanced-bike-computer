// how many samples to take and average, more takes longer
// but is more 'smooth'
#define SHIFT_COUNT 2
#define NUMSAMPLES 4

void getAccelValues() {
  x = analogReadAverage(PIN_X) - CALIB_VAL_X;
  y = analogReadAverage(PIN_Y) - CALIB_VAL_Y;
  z = analogReadAverage(PIN_Z) - CALIB_VAL_Z;
  accel = abs(x) + abs(y);
}

int analogReadAverage(byte adcPin) {
  uint8_t i=0;
  int average=0;
 
  // take N samples in a row
  for (; i<NUMSAMPLES; i++) {
   average += analogRead(adcPin);
  }
  return average>>SHIFT_COUNT;
}
