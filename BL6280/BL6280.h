/*************************************************** 
  This is a library for the BL6280 Capacitive Touch Screen driver
  commonly used in the U8 "Smartwatch"

 Written by A. Jordan
 ****************************************************/

#ifndef BL6280_H
#define BL6280_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>


#define BL6280_ADDR           0x38
#define BL6280_REG_NUMTOUCHES 0x02
#define BL6280_REG_MODE 0x00
#define BL6280_REG_THRESHHOLD 0x80

class TS_Point {
 public:
  TS_Point(void);
  TS_Point(int16_t x, int16_t y, int16_t z);
 
  int16_t x, y, z;
};

class BL6280 {
 public:

  BL6280(void);
  boolean begin(void);  

  void writeRegister8(uint8_t reg, uint8_t val);
  uint8_t readRegister8(uint8_t reg);

  void readData(uint16_t *x, uint16_t *y);
 void sleep(void);
 void wake(void);
  boolean touched(void);
  TS_Point getPoint(void);

 private:
  uint8_t touches;
  uint16_t touchX[2], touchY[2], touchID[2];

};

#endif //
