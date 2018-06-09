//
// Sensor_OPT3001.cpp
// Library C++ code
// ----------------------------------
// Developed with embedXcode+
// http://embedXcode.weebly.com
//
// Project 		SensorsBoosterPack
//
// Created by	a0273900 for initial C-library
// Adapted by 	Rei Vilo, Aug 20, 2015 13:42
// 				http://embeddedcomputing.weebly.com
//
// Copyright	(c) Rei Vilo, 2015-2016
// Licence		CC = BY SA NC
//
// See 			Sensor_OPT3001.h and ReadMe.txt for references
//


// Library header
#include "Sensor_OPT3001.h"
#include "Wire_Utilities.h"


// Constants
#define OPT3001_SLAVE_ADDRESS           0x47

#define OPT3001_RESULT_REGISTER         0x00
#define OPT3001_CONFIGURATION_REGISTER  0x01
#define OPT3001_LOW_LIMIT_REGISTER      0x02
#define OPT3001_HIGH_LIMIT_REGISTER     0x03
#define OPT3001_MANUFACTURE_ID_REGISTER 0x7e
#define OPT3001_DEVICE_ID_REGISTER      0x7f

#define OPT3001_READY_FLAG              0x80
#define OPT3001_POWER_UP                0x0400


// Code
Sensor_OPT3001::Sensor_OPT3001()
{
    ;
}

String Sensor_OPT3001::WhoAmI()
{
    return "OPT3001 luxmeter";
}

void Sensor_OPT3001::begin(uint16_t configuration, uint8_t interruptPin)
{
    // Set configuration
    writeRegister16(OPT3001_SLAVE_ADDRESS, OPT3001_CONFIGURATION_REGISTER, configuration);
    _interruptPin = interruptPin;
}

/*
    uint16_t Sensor_OPT3001::readManufacturerId()
    {
    return readRegister16(OPT3001_SLAVE_ADDRESS, OPT3001_MANUFACTUREID_REGISTER);
    }

    uint16_t Sensor_OPT3001::readDeviceId()
    {
    return readRegister16(OPT3001_SLAVE_ADDRESS, OPT3001_DEVICEID_REGISTER);
    }

    uint16_t Sensor_OPT3001::readConfigReg()
    {
    return readRegister16(OPT3001_SLAVE_ADDRESS, OPT3001_CONFIGURATION_REGISTER);
    }

    uint16_t Sensor_OPT3001::readLowLimitReg()
    {
    return readRegister16(OPT3001_SLAVE_ADDRESS, OPT3001_LOWLIMIT_REGISTER);
    }

    uint16_t Sensor_OPT3001::readHighLimitReg()
    {
    return readRegister16(OPT3001_SLAVE_ADDRESS, OPT3001_HIGHLIMIT_REGISTER);
    }
*/

void Sensor_OPT3001::get()
{
    _rawLux = readRegister16(OPT3001_SLAVE_ADDRESS, OPT3001_RESULT_REGISTER);

    // Extract _fraction and _exponent from _rawLux data
    uint32_t _fraction = _rawLux & 0x0fff;
    uint32_t _exponent = 1 << ((_rawLux >> 12) & 0x000f);

    _rawLux = (_fraction * _exponent);
}

//uint32_t Sensor_OPT3001::light()
float Sensor_OPT3001::light()
{

    // Scale to lux
    return 0.01 * (float)_rawLux;
}

void Sensor_OPT3001::setPowerMode(uint8_t mode)
{
    //    uint16_t statusMaskRegister = readRegister16(TMP007_SLAVE_ADDRESS, TMP007_STATUS_MASK);
    //    Serial.print("sm=\t");
    //    Serial.print(statusMaskRegister, BIN);

    //#define OPT3001_100_MS  0xc010 // shut-down = clear 0x0400
    //#define OPT3001_100_MS  0xc410 // continous = set 0x0400
    //#define OPT3001_800_MS  0xc810 // shut-down
    //#define OPT3001_800_MS  0xcc10 // continuous
    uint16_t configurationRegister = readRegister16(OPT3001_SLAVE_ADDRESS, OPT3001_CONFIGURATION_REGISTER);

    if (mode == HIGH)
    {
        configurationRegister |= OPT3001_POWER_UP;
    }
    else
    {
        configurationRegister &= OPT3001_POWER_UP;
    }

    writeRegister16(OPT3001_SLAVE_ADDRESS, OPT3001_CONFIGURATION_REGISTER, configurationRegister);
}


