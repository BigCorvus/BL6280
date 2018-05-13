/***************************************************
 Basic cap touch test
 ****************************************************/



#include <Wire.h>      // this is needed for BL6280
#include <BL6280.h>

// The BL6280 uses hardware I2C (SCL/SDA)
BL6280 ctp = BL6280();

void setup(void) {
 // while (!Serial);     // used for leonardo debugging
 ctp.begin();
  SerialUSB.begin(115200);
  while (!SerialUSB) {
    ; // wait for serial port to connect
  }
  SerialUSB.println("Capacitive touchscreen started");
 
}

void loop() {
  // Wait for a touch
  if (! ctp.touched()) {
    return;
  }

  // Retrieve a point  
  TS_Point p = ctp.getPoint();
  
 /*
  // Print out raw data from screen touch controller
  Serial.print("X = "); Serial.print(p.x);
  Serial.print("\tY = "); Serial.print(p.y);
  Serial.print(" -> ");
 */

  // flip it around to match the screen.
  //p.x = map(p.x, 0, 240, 240, 0);
 // p.y = map(p.y, 0, 320, 320, 0);

  // Print out the remapped (rotated) coordinates
  SerialUSB.print("("); 
  SerialUSB.print(p.x);
  SerialUSB.print(", "); 
  SerialUSB.print(p.y);
  SerialUSB.print(")");
  
}