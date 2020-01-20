/*

Arduino library for Arduino library for Sensirion STS35 High-Accuracy +/-0.1C Digital Temperature Sensor
version 2020.1.20

---

Copyright (c) 2018-2020, ClosedCube
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation and/or 
   other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors 
   may be used to endorse or promote products derived from this software
   without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef CLOSEDCUBE_STS35_ARDUINO_H
#define CLOSEDCUBE_STS35_ARDUINO_H

#include "ClosedCube_I2C.h"

namespace ClosedCube {

    namespace Sensor {

        typedef enum {
            STS35_REPEATABILITY_HIGH,
            STS35_REPEATABILITY_MEDIUM,
            STS35_REPEATABILITY_LOW,
        } STS35_Repeatability;

        class STS35 {

        public:
            STS35();
            STS35(uint8_t address);
            STS35(ClosedCube::Driver::I2CDevice device);

            void address(uint8_t address);

            void heaterOn();
            void heaterOff();

            void clockStrechingOn();
            void clockStrechingOff();

            void setRepeatability(STS35_Repeatability);

            float readTemperature();
            float readT();

        private:
            ClosedCube::Driver::I2CDevice _sensor;
            
            STS35_Repeatability _repeatability = STS35_REPEATABILITY_HIGH;
            bool _clockStreching = true;
            bool _singleShotMode = true;

            uint8_t readSignleShot(byte *buf);

            float calculateTemperature(uint16_t t_raw);
            uint8_t calculateCrc(uint8_t data[]);
        };
    }
}


#endif
