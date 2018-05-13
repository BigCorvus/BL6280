/*************************************************** 
  This is a library for the BL6280 Capacitive Touch Screen driver
  commonly used in the U8 "Smartwatch"

 Written by A. Jordan
 ****************************************************/


#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

#include <BL6280.h>

#if defined(__SAM3X8E__)
    #define Wire Wire1
#endif

/**************************************************************************/
/*! 
    @brief  Instantiates a new BL6280 class
*/
/**************************************************************************/
// I2C, no address adjustments or pins
BL6280::BL6280() {
}


/**************************************************************************/
/*! 
    @brief  Setups the HW
*/
/**************************************************************************/
boolean BL6280::begin(void) {
  Wire.begin();

Wire.beginTransmission(BL6280_ADDR);
    Wire.write((byte)0x00);
    Wire.write((byte)0x00);
    Wire.endTransmission();
  
  return true;
}




boolean BL6280::touched(void) {
  
  uint8_t n = readRegister8(BL6280_REG_NUMTOUCHES);
  if ((n == 1) || (n == 2)) return true;
  return false;
}

/*****************************/

void BL6280::readData(uint16_t *x, uint16_t *y) {

uint8_t i2cdat[4];
  //read point
  Wire.beginTransmission(BL6280_ADDR);
  Wire.write((byte)0x03);  
  Wire.endTransmission();
   Wire.beginTransmission(BL6280_ADDR);
  Wire.requestFrom((byte)BL6280_ADDR, (byte)4);
  for (uint8_t i=0; i<4; i++){
    i2cdat[i] = Wire.read();
    //SerialUSB.println(i2cdat[i]);
  }
    
    *x = 128-i2cdat[1]; 
	*y = i2cdat[3];
}

TS_Point BL6280::getPoint(void) {
  uint16_t x, y;
  uint8_t z;
  readData(&x, &y);
  return TS_Point(x, y, 1);
}
void BL6280::sleep(void){
	Wire.beginTransmission(BL6280_ADDR);
    Wire.write((byte)0xA5);
    Wire.write((byte)0x03);
    Wire.endTransmission();
}
void BL6280::wake(void){
	//not sure here but this is what happens after shutdown. Maybe the chip gets reset
	uint8_t yo;
	Wire.beginTransmission(BL6280_ADDR);
    Wire.write((byte)0x02);
    Wire.endTransmission();
	Wire.beginTransmission(BL6280_ADDR);
  Wire.requestFrom((byte)BL6280_ADDR, (byte)1);
  yo=Wire.read();	//expected: 0x01
  Wire.beginTransmission(BL6280_ADDR);
    Wire.write((byte)0x02);
    Wire.endTransmission();
	Wire.beginTransmission(BL6280_ADDR);
  Wire.requestFrom((byte)BL6280_ADDR, (byte)1);
  yo=Wire.read(); //expected: 0x01
}
uint8_t BL6280::readRegister8(uint8_t reg) {
  uint8_t x ;
   // use i2c
    Wire.beginTransmission(BL6280_ADDR);
    Wire.write((byte)reg);
    Wire.endTransmission();
    Wire.beginTransmission(BL6280_ADDR);
    Wire.requestFrom((byte)BL6280_ADDR, (byte)1);
    x = Wire.read();
    Wire.endTransmission();

  //  Serial.print("$"); Serial.print(reg, HEX); 
  //  Serial.print(": 0x"); Serial.println(x, HEX);
  
  return x;
}

void BL6280::writeRegister8(uint8_t reg, uint8_t val) {
   // use i2c
    Wire.beginTransmission(BL6280_ADDR);
    Wire.write((byte)reg);
    Wire.write((byte)val);
    Wire.endTransmission();
}

/****************/

TS_Point::TS_Point(void) {
  x = y = 0;
}

TS_Point::TS_Point(int16_t x0, int16_t y0, int16_t z0) {
  x = x0;
  y = y0;
  z = z0;
}

