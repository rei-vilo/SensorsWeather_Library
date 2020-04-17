//
// Sensor_TMP116.cpp
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
// Copyright	(c) Rei Vilo, 2015-2019
// Licence		CC = BY SA NC
//
// See 			Sensor_TMP116.h and ReadMe.txt for references
//


// Library header
#include "Sensor_TMP116.h"
#include "Wire_Utilities.h"

#define TMP116_TEMPERATURE              0x00
#define TMP116_CONFIGURATION            0x01
#define TMP116_HIGH_LIMIT               0x02
#define TMP116_LOW_LIMIT                0x03
#define TMP116_EEPROM_UNLOCK            0x04
#define TMP116_EEPROM1                  0x05
#define TMP116_EEPROM2                  0x06
#define TMP116_EEPROM3                  0x07
#define TMP116_EEPROM4                  0x08
#define TMP116_DEVICE_ID                0x0f

// Code
Sensor_TMP116::Sensor_TMP116(uint8_t address, uint8_t pinPower)
{
    _address = address;
    _pinPower = pinPower;
}

void Sensor_TMP116::begin(uint16_t totalSamples)
{
//    writeRegister16(_address, TMP116_CONFIGURATION, TMP116_CONVERSION_1_SECOND + TMP116_EIGHT_SAMPLES + TMP116_MODE_CONTINUOUS);
    if (_pinPower > 0)
    {
        pinMode(_pinPower, OUTPUT);
        digitalWrite(_pinPower, HIGH);
    }

    delay(100);
    get();
    delay(100);
}

void Sensor_TMP116::get()
{
//    uint16_t _register = readRegister16(_address, TMP116_CONFIGURATION);
//    _register &= ~0b0000110000000000;
//    _register |= TMP116_MODE_ONCE;
//    writeRegister16(_address, TMP116_CONFIGURATION, _register);

    _rawTemperature = readRegister16(_address, TMP116_TEMPERATURE);

//    _register &= ~0b0000110000000000;
//    _register |= TMP116_MODE_SHUTDOWN;
//    writeRegister16(_address, TMP116_CONFIGURATION, _register);
}

String Sensor_TMP116::WhoAmI()
{
    return "TMP116 temperature";
}

float Sensor_TMP116::temperature()
{
    return (float)(_rawTemperature) * 0.0078125 + 273.15;
    ;
}

void Sensor_TMP116::setPowerMode(uint8_t mode)
{
    // Problem:
    // Current configuration should be saved for later re-use
//    if (_pinPower > 0) {
//        digitalWrite(_pinPower, mode);
//    }

    //    uint16_t statusMaskRegister = readRegister16(_address, TMP116_STATUS_MASK);
    //    Serial.print("sm=\t");
    //    Serial.print(statusMaskRegister, BIN);

//    uint16_t _register = readRegister16(_address, TMP116_CONFIGURATION);

    //    Serial.print(configurationRegister, BIN);

//    if (mode == HIGH)
//    {
//        _register |= TMP116_POWER_UP;
//    }
//    else
//    {
//        _register &= ~TMP116_POWER_UP;
//    }

    //    Serial.print("\tc=\t");
    //    Serial.print(configurationRegister, BIN);
    //    Serial.println();
    //
//    writeRegister16(_address, TMP116_CONFIGURATION, _register);
}

