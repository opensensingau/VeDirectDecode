#ifndef VEDIRECTDECODE_H
#define VEDIRECTDECODE_H

#include <Arduino.h>

/**
 * Decodes VE Direct uart data
 * @author Simon Rosenzweig (https://github.com/zigon15)
 */
class VeDirectDecode {
public:
	/**
	 * @brief Base constructor
	 * @param HardwareSerial pointer to the serial that the VE device is connected too
	*/
	VeDirectDecode(HardwareSerial *serial);

	/**
	 * @brief Reads various MPPT parmeters
	*/
	bool getData(int32_t &batVoltage, int32_t &batCurrent, int32_t &loadCurrent, int32_t &loadState, 
				 int32_t &panelVoltage, int32_t &panelPower, int32_t &converterState, 
				 int32_t &maxPanelPowerToday, int32_t &panelPowerToday);

	/**
	 * @brief Finds and reads the param of the specified type
	 * @param type The param type to find
	 * @param param Buffer to store the parameter data in
	 * @param maxLength The max number of characters to write to the param buffer
	 * @return true if sucessfull, otherwise false
	*/
	bool getParam(char *type,  char *param, uint8_t maxLength);
private:
  bool flushToVal(char *type);
  HardwareSerial *_serial{nullptr};
};

#endif /* VEDIRECTDECODE_H */
