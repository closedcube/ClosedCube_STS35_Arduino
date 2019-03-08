/*

Arduino library for Arduino library for Sensirion STS35 High-Accuracy Digital Temperature Sensor
version 2019.3.8

---

Copyright (c) 2018-2019, ClosedCube
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

#include "ClosedCube_STS35.h"

ClosedCube::Sensor::STS35::STS35() {

}

ClosedCube::Sensor::STS35::STS35(uint8_t address) {
    _sensor.address(address);
}

void ClosedCube::Sensor::STS35::address(uint8_t address) {
    _sensor.address(address);
}

float ClosedCube::Sensor::STS35::calculateTemperature(uint16_t rawValue)
{
    return 175.0f * (float)rawValue / 65535.0f - 45.0f;
}

float ClosedCube::Sensor::STS35::readTemperature() {
    _sensor.writeWord(0x2C06);
    delay(5);

    byte buf[3];
    _sensor.readBytes(buf,(uint8_t)3);

    uint16_t t_raw = buf[0] << 8 | buf[1];
    uint8_t checksum = buf[2];

    if( calculateCrc(buf) != checksum ) {
        return 0;
    } else {
        return calculateTemperature(t_raw);
    }
}

float ClosedCube::Sensor::STS35::readT() {
    return readTemperature();
}

void ClosedCube::Sensor::STS35::heaterOn() {
    _sensor.writeWord(0x306D);
}

void ClosedCube::Sensor::STS35::heaterOff() {
    _sensor.writeWord(0x3066);
}

uint8_t ClosedCube::Sensor::STS35::calculateCrc(uint8_t data[])
{
    uint8_t bit;
    uint8_t crc = 0xFF;
    uint8_t dataCounter = 0;


    for (; dataCounter < 2; dataCounter++)
    {
        crc ^= (data[dataCounter]);
        for (bit = 8; bit > 0; --bit)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x131;
            else
                crc = (crc << 1);
        }
    }

    return crc;
}

