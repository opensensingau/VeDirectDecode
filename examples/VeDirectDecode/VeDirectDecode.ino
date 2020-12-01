/**
 * Main example sketch.
 * Reads various parameters and outputs them.
 */
#include "VeDirectDecode.h"

//The serial port that the VE device is attached too
#define VE_SERIAL_PORT Serial1

#define READ_TIMER_INTERVAL 2000

void setup() {
  Serial.begin(11200);

  int32_t batVoltage = 0;
  int32_t batCurrent = 0;
  int32_t loadCurrent = 0;
  int32_t loadState = 0;
  int32_t panelVoltage = 0;
  int32_t panelPower = 0;
  int32_t converterState = 0;
  int32_t maxPanelPowerToday = 0;
  int32_t panelYieldToday = 0;

  uint32_t readTimer = millis() + READ_TIMER_INTERVAL;

  VeDirectDecode test{&VE_SERIAL_PORT};

  while (1) {
    if (millis() > readTimer) {
      readTimer += READ_TIMER_INTERVAL;
      uint32_t timeBegin = micros();

      if (test.getData(batVoltage, batCurrent, loadCurrent, loadState, panelVoltage, panelPower,
                       converterState, maxPanelPowerToday, panelYieldToday)) {
        uint32_t timeEnd = micros();
        
        Serial.print("Solar Charger{Bat V:");
        Serial.print(batVoltage);
        Serial.print(" mV, Bat I:");
        Serial.print(batCurrent);

        Serial.print(" mA, Load I:");
        Serial.print(loadCurrent);
        Serial.print(" mA, Load State:");
        Serial.print(loadState);
        Serial.print(", Panel V:");
        Serial.print(panelVoltage);
        Serial.print(" mV, Panel P:");
        Serial.print(panelPower);
        Serial.print(" W, Converter State:");
        Serial.print(converterState);
        Serial.print(", Max Panel P:");
        Serial.print(maxPanelPowerToday);
        Serial.print(" W, Panel Yield P:");
        Serial.print(panelYieldToday*10);
        Serial.println(" Wh}");

        Serial.print("Read time: ");
        Serial.print(timeEnd - timeBegin);
        Serial.println(" us");
        Serial.println("-----------");
      } else {
        Serial.println("@ERROR: getData() failed!");
      }

    }
  }
}

void loop() {
}