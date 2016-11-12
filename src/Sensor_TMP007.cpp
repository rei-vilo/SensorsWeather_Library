//
// Sensor_TMP007.cpp
// Library C++ code
// ----------------------------------
// Developed with embedXcode+
// http://embedXcode.weebly.com
//
// Project 		SensorsBoosterPack
//
// Created by 	Rei Vilo, 20/08/2015 13:42
// 				http://embeddedcomputing.weebly.com
//
// Copyright	(c) Rei Vilo, 2015-2016
// Licence		CC = BY SA NC
//
// See 			Sensor_TMP007.h and ReadMe.txt for references
//


// Library header
#include "Sensor_TMP007.h"
#include "Wire_Utilities.h"

#define TMP007_SLAVE_ADDRESS            0x40
#define TMP007_VOLTAGE                  0x00
#define TMP007_INTERNAL_TEMPERATURE     0x01
#define TMP007_CONFIGURATION            0x02
#define TMP007_EXTERNAL_TEMPERATURE     0x03
#define TMP007_STATUS                   0x04
#define TMP007_STATUS_MASK              0x05
#define TMP007_MANUFACTURER_ID          0xFE
#define TMP007_DEVICE_ID                0xFF

#define TMP007_ALERT_ENABLE             0x0100
#define TMP007_RESET                    0x8000
//#define TMP007_POWER_DOWN               0x0000
#define TMP007_POWER_UP                 0x1000
#define TMP007_READY                    0x4000

#define TMP007_CONVERSION_DONE          0x0080


// Code
Sensor_TMP007::Sensor_TMP007()
{

}

void Sensor_TMP007::begin(uint16_t totalSamples)
{
    writeRegister16(TMP007_SLAVE_ADDRESS, TMP007_CONFIGURATION, TMP007_RESET);
    writeRegister16(TMP007_SLAVE_ADDRESS, TMP007_CONFIGURATION, TMP007_POWER_UP | totalSamples);
    //    writeRegister16(TMP007_SLAVE_ADDRESS, TMP007_STATUS_MASK, TMP007_READY);
    delay(100);
}

void Sensor_TMP007::get()
{
    int16_t _rawTemperature;

    _rawTemperature = readRegister16(TMP007_SLAVE_ADDRESS, TMP007_INTERNAL_TEMPERATURE);
    // .03125 = 1 / 32
    _internalTemperature = (float)(_rawTemperature >> 2) * .03125 + 273.15;

    //    Serial.print("?=\t");
    //    Serial.print(readRegister16(TMP007_SLAVE_ADDRESS, TMP007_STATUS), BIN);
    //    Serial.print("\t");
    //    Serial.print(readRegister16(TMP007_SLAVE_ADDRESS, TMP007_CONFIGURATION), BIN);
    //    Serial.print("\t");
    //    Serial.print("\tb0=");
    //    Serial.print(_rawTemperature, BIN);
    //    Serial.print("\tb0&=");
    //    Serial.print(((_rawTemperature & 0b1) == 0), DEC);
    //    Serial.print("\t");

    _rawTemperature = readRegister16(TMP007_SLAVE_ADDRESS, TMP007_EXTERNAL_TEMPERATURE);
    // Check validity in bit 0
    if ((_rawTemperature & 0b1) == 0)
    {
        _externalTemperature = (float)(_rawTemperature >> 2) * .03125 + 273.15;
    }
    else
    {
        _externalTemperature = 0.0; // or keep previous reading
    }
}

String Sensor_TMP007::WhoAmI()
{
    return "TMP007 IR temperature";
}

float Sensor_TMP007::internalTemperature()
{
    return _internalTemperature;
}

float Sensor_TMP007::externalTemperature()
{
    return _externalTemperature;
}

void Sensor_TMP007::setPowerMode(uint8_t mode)
{
    //    uint16_t statusMaskRegister = readRegister16(TMP007_SLAVE_ADDRESS, TMP007_STATUS_MASK);
    //    Serial.print("sm=\t");
    //    Serial.print(statusMaskRegister, BIN);

    uint16_t configurationRegister = readRegister16(TMP007_SLAVE_ADDRESS, TMP007_CONFIGURATION);

    //    Serial.print(configurationRegister, BIN);

    if (mode == HIGH)
    {
        configurationRegister |= TMP007_POWER_UP;
    }
    else
    {
        configurationRegister &= ~TMP007_POWER_UP;
    }

    //    Serial.print("\tc=\t");
    //    Serial.print(configurationRegister, BIN);
    //    Serial.println();
    //
    writeRegister16(TMP007_SLAVE_ADDRESS, TMP007_CONFIGURATION, configurationRegister);
}

