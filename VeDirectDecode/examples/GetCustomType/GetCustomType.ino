/**
 * Reads various parameters from the VE device and outputs them.
 * getParam() types must be read in the order that they appear over serial,
 * use the RawSerialDump sketch to determine the order.
 */
#include "VeDirectDecode.h"

//The serial port that the VE device is attached too
#define VE_SERIAL_PORT Serial1

#define READ_TIMER_INTERVAL 5000

void setup() {
  Serial.begin(11200);
  VeDirectDecode test{&VE_SERIAL_PORT};

  uint32_t readTimer = millis() + READ_TIMER_INTERVAL;

  //Buffer to hold parmeter data in
  char buff[21] = {0};

  while (1) {
    if (millis() > readTimer) {
      readTimer += READ_TIMER_INTERVAL;
      
      if(test.getParam("PID", buff, sizeof(buff)-1)){
        Serial.print("PID: ");
        Serial.println(buff);
        memset(buff, 0, sizeof(buff));
      }else{
        Serial.println("@ERROR: Failed to find PID parameter");
      }
      
      if(test.getParam("SER#", buff, sizeof(buff)-1)){
        Serial.print("SER#: ");
        Serial.println(buff);
        memset(buff, 0, sizeof(buff));
      }else{
        Serial.println("@ERROR: Failed to find SER# parameter");
      }

      if(test.getParam("H21", buff, sizeof(buff)-1)){
        Serial.print("H21: ");
        Serial.println(buff);
        memset(buff, 0, sizeof(buff));
      }else{
        Serial.println("@ERROR: Failed to find H21 parameter");
      }

      Serial.println("----------");
    }
  }
}

void loop() {
}