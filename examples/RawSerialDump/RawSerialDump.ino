/**
 * Reads data from the VE device and outputs it straight over serial
 * Useful to find what parameters your VE device is outputting
 */

#define VE_SERIAL_PORT Serial1

void setup() {
  Serial.begin(11200);
  VE_SERIAL_PORT.begin(19200);

  while (1) {
    while (VE_SERIAL_PORT.available()) {
      Serial.write(VE_SERIAL_PORT.read());
    }
  }
}

void loop() {
}