# VeDirectDecode Arduino Library
Arduino library to decode serial data adhering to the VE.Direct protcol from Victron
Energy devices. 

Takes ~0.9ms for getData() to complete on a P1AM-100 (~Arduino MKR Zero)

## Overview
The Victron Energy devices are 3.3v. If you are using a 5v Arduino you must
use a 5v to 3.3v converter on the serial RX line.

Interface:
 - Read any parameter you would like with the getParam() function
 - Read a bunch of usefull parameters with the getData() function

 ### Example:
 ```C
#include "VeDirectDecode.h"

void setup(){
    VeDirectDecode test{&Serial1};

    int32_t batVoltage = 0;
    int32_t batCurrent = 0;
    int32_t loadCurrent = 0;
    int32_t loadState = 0;
    int32_t panelVoltage = 0;
    int32_t panelPower = 0;
    int32_t converterState = 0;
    int32_t maxPowerToday = 0;

    while(1){
        test.getData(batVoltage, batCurrent, loadCurrent, loadState, panelVoltage, panelPower, converterState, maxPowerToday);
    }
}

 ```