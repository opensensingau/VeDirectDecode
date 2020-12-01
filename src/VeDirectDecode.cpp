#include "VeDirectDecode.h"

VeDirectDecode::VeDirectDecode(HardwareSerial *serial): _serial{serial} {
      _serial->begin(19200);
}

bool VeDirectDecode::getData(int32_t &batVoltage, int32_t &batCurrent, int32_t &loadCurrent, int32_t &loadState, 
                             int32_t &panelVoltage, int32_t &panelPower, int32_t &converterState, int32_t &maxPowerToday) {
  char buff[21] = {0};

  //Timeout timer
  uint32_t timer = millis() + 1000;

  //Make sure we have data to decode
  while(_serial->available() < 50){
	  delay(100);
    if(millis() > timer){
      //If it has been greater than a second and still no data
      //The module probably isn't connect
      return false;
    }
  }

  //Get the values first in the buffer
  //Might not be the latest but oh well
  if(getParam("V", buff, sizeof(buff)-1)){
    batVoltage = atoi(buff);
    memset(buff, 0, sizeof(buff));
  }
  if(getParam("I", buff, sizeof(buff)-1)){
    batCurrent = atoi(buff);
    memset(buff, 0, sizeof(buff));
  }
  if(getParam("VPV", buff, sizeof(buff)-1)){
    panelVoltage = atoi(buff);
    memset(buff, 0, sizeof(buff));
  }
  if(getParam("PPV", buff, sizeof(buff)-1)){
    panelPower = atoi(buff);
    memset(buff, 0, sizeof(buff));
  }
  if(getParam("CS", buff, sizeof(buff)-1)){
    converterState = atoi(buff);
    memset(buff, 0, sizeof(buff));
  }
  if(getParam("LOAD", buff, sizeof(buff)-1)){
    loadState = atoi(buff);
    memset(buff, 0, sizeof(buff));
  }
  if(getParam("IL", buff, sizeof(buff)-1)){
    loadCurrent = atoi(buff);
    memset(buff, 0, sizeof(buff));
  }
  if(getParam("H21", buff, sizeof(buff)-1)){
    maxPowerToday = atoi(buff);
    memset(buff, 0, sizeof(buff));
  }

  //Make sure we clear out any left over data
  while(_serial->available()){
    _serial->read();
  }
  return true;
}

bool VeDirectDecode::getParam(char *type, char *param, uint8_t maxLength) {
  if (!flushToVal(type)) {
    //Serial.print("Failed to find type:");
    //Serial.println(type);
    return false;
  }

  uint8_t index = 0;

  //Read in the param
  while(1){
    while (!_serial->available());
    char val = _serial->peek();

    if(val == '\n'){
      //At the end of the parameter so exit the loop
      break;
    }else{
      if(index == maxLength){
        break;
      }else{
        param[index++] = _serial->read();
      }
    }
  }

  return true;
}

bool VeDirectDecode::flushToVal(char *type) {
  char typeBuf[16] = {0};

  //Loop through serial buffer until the specified type is found
  while (strcmp(typeBuf, type) != 0) {
    for (int i = 0; i < 16; i++) {
      typeBuf[i] = 0;
    }

    //Flush all data until up to the next type variable
    while (1) {
      if (!_serial->available()) {
        return false;
      } else {
        if (_serial->read() == '\n') {
          break;
        }
      }
    }

    //Read in the type
    for (int i = 0; i < 10; i++) {
      if (!_serial->available()) {
        return false;
      }

      char temp = _serial->read();

      if (temp == '\t') {
        //Up to a tab so have read in the type
        //Serial.print(typeBuf);
        //Serial.print(", ");
        break;
      } else {
        typeBuf[i] = temp;
      }
    }
  }
  //Serial.println("{Success}");
  return true;
}