//
// Wire_Utilities.cpp
// Library C++ code
// ----------------------------------
// Developed with embedXcode+
// https://embedXcode.weebly.com
//
// Project 		SensorsBoosterPack
//
// Created by 	Rei Vilo, 20 Aug 2015
// 				https://embeddedcomputing.weebly.com
//
// Copyright	(c) Rei Vilo, 2015-2020
// Licence		CC = BY SA NC
//
// See 			Wire_Utilities.h for references
//


// Include library header
#include "Wire_Utilities.h"

// Library code
void writeRegister8(uint8_t device, uint8_t command, uint8_t data8)
{
    Wire.beginTransmission(device);
    Wire.write(command);
    Wire.write(data8);
    Wire.endTransmission();
}

void writeRegister16(uint8_t device, uint8_t command, uint16_t data16, uint8_t mode)
{
    Wire.beginTransmission(device);
    Wire.write(command);
    if (mode == MSBFIRST)
    {
        Wire.write(highByte(data16));
        Wire.write(lowByte(data16));
    }
    else
    {
        Wire.write(lowByte(data16));
        Wire.write(highByte(data16));
    }
    Wire.endTransmission();
}

uint8_t readRegister8(uint8_t device, uint8_t command)
{
    uint8_t value;

    Wire.beginTransmission(device);
    Wire.write(command);
    Wire.endTransmission();

    uint8_t w = Wire.requestFrom(device, 1);
    while (Wire.available() < 1);
    value = Wire.read();

    return value;
}

uint16_t readRegister16(uint8_t device, uint8_t command, uint8_t mode)
{
    uint16_t value;

    Wire.beginTransmission(device);
    Wire.write(command);
    Wire.endTransmission();

    uint8_t w = Wire.requestFrom(device, 2);
    while (Wire.available() < 2);

    if (mode == MSBFIRST)
    {
        value   = Wire.read() << 8;
        value  |= Wire.read();
    }
    else
    {
        value   = Wire.read();
        value  |= Wire.read() << 8;
    }

    return value;
}

void delayBusy(uint32_t ms)
{
    uint32_t chrono = millis() + ms;
    while (millis() < chrono);
}
