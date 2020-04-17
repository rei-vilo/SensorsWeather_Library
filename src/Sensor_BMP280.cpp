//
// Sensor_BMP280.cpp
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
// Copyright 	(c) Rei Vilo, 2015-2020
// Licence		CC = BY SA NC
//
// See 			Sensor_BMP280.h and ReadMe.txt for references
//



// 0xF7 to 0xFE
#define BMP280_DATA_F7_FE       0xf7
#define BMP280_DATA_F7_FC       0xf7
#define BMP280_CONTROL          0xf4
#define BMP280_STATUS           0xf3
#define BMP280_CONFIGURATION    0xf5
#define BMP280_RESET            0xe0

#define BMP280_VALUE_RESET_EXECUTE  0xb6

#define BMP280_CALIBRATION_T1   0x88
#define BMP280_CALIBRATION_T2   0x8a
#define BMP280_CALIBRATION_T3   0x8c
#define BMP280_CALIBRATION_P1   0x8e
#define BMP280_CALIBRATION_P2   0x90
#define BMP280_CALIBRATION_P3   0x92
#define BMP280_CALIBRATION_P4   0x94
#define BMP280_CALIBRATION_P5 	0x96
#define BMP280_CALIBRATION_P6   0x98
#define BMP280_CALIBRATION_P7   0x9a
#define BMP280_CALIBRATION_P8   0x9c
#define BMP280_CALIBRATION_P9   0x9e

// Library header
#include "Sensor_BMP280.h"
#include "Wire_Utilities.h"
//#include "QuickDebug.h"


// Sensor
//
Sensor_BMP280::Sensor_BMP280(uint8_t address)
{
    _address = address;
}

String Sensor_BMP280::WhoAmI()
{
    return "BMP280 temperature + pressure";
}

void Sensor_BMP280::begin()
{
    // BMP280 uses a different I2C port
    //    pinMode(Board_MPU_POWER, OUTPUT);
    writeRegister8(_address, BMP280_RESET, BMP280_VALUE_RESET_EXECUTE);
    delayBusy(100); //    delay(100);
    //          7  4   0
    // 0x27 = 0b00100111
    //
    writeRegister8(_address, BMP280_CONTROL, 0b00100111);

    //    Register Address	Register content	Data type
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x88 / 0x89		dig_T1 [7:0] / [15:8]	unsigned short = uint16_t
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x8A / 0x8B		dig_T2 [7:0] / [15:8]	signed short = int16_t
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x8C / 0x8D		dig_T3 [7:0] / [15:8]	signed short
    _calibrationT1 = readRegister16(_address, BMP280_CALIBRATION_T1, LSBFIRST); // uint16_t
    _calibrationT2 = readRegister16(_address, BMP280_CALIBRATION_T2, LSBFIRST); // int16_t
    _calibrationT3 = readRegister16(_address, BMP280_CALIBRATION_T3, LSBFIRST); // int16_t

    //    Register Address	Register content	Data type
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x8E / 0x8F		dig_P1 [7:0] / [15:8]	unsigned short = uint16_t
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x90 / 0x91		dig_P2 [7:0] / [15:8]	signed short
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x92 / 0x93		dig_P3 [7:0] / [15:8]	signed short
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x94 / 0x95		dig_P4 [7:0] / [15:8]	signed short
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x96 / 0x97		dig_P5 [7:0] / [15:8]	signed short
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x98 / 0x99		dig_P6 [7:0] / [15:8]	signed short
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x9A / 0x9B		dig_P7 [7:0] / [15:8]	signed short
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x9C / 0x9D		dig_P8 [7:0] / [15:8]	signed short
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x9E / 0x9F		dig_P9 [7:0] / [15:8]	signed short
    _calibrationP1 = readRegister16(_address, BMP280_CALIBRATION_P1, LSBFIRST); // uint16_t
    _calibrationP2 = readRegister16(_address, BMP280_CALIBRATION_P2, LSBFIRST); // int16_t
    _calibrationP3 = readRegister16(_address, BMP280_CALIBRATION_P3, LSBFIRST); // int16_t
    _calibrationP4 = readRegister16(_address, BMP280_CALIBRATION_P4, LSBFIRST); // int16_t
    _calibrationP5 = readRegister16(_address, BMP280_CALIBRATION_P5, LSBFIRST); // int16_t
    _calibrationP6 = readRegister16(_address, BMP280_CALIBRATION_P6, LSBFIRST); // int16_t
    _calibrationP7 = readRegister16(_address, BMP280_CALIBRATION_P7, LSBFIRST); // int16_t
    _calibrationP8 = readRegister16(_address, BMP280_CALIBRATION_P8, LSBFIRST); // int16_t
    _calibrationP9 = readRegister16(_address, BMP280_CALIBRATION_P9, LSBFIRST); // int16_t

    // Is some delay needed for readiness?
    //    delay(100);
    delayBusy(100);
    // First dummy reading required?
    get();

}

uint8_t Sensor_BMP280::get()
{
    int32_t _rawPressure, _rawTemperature, _rawHumidity;
    int32_t t_fine;

    //    while (readRegister8(_address, BMP280_STATUS) & 0x08);

    Wire.beginTransmission(BMP280_SLAVE_ADDRESS);
    Wire.write(BMP280_DATA_F7_FC);
    Wire.endTransmission();

    //    uint8_t data[8];
    //    Wire.requestFrom(_address, 8);
    //    while (Wire.available() < 8);
    //    for (uint8_t i=0; i<8; i++) {
    //        data[i] = Wire.read();
    //    }
    //
    //    _rawPressure = ((uint32_t)data[0] << 12) + ((uint32_t)data[1] << 4) + ((uint32_t)data[2]>> 4); // f7.f8.f9
    //    _rawTemperature = ((uint32_t)data[3] << 12) + ((uint32_t)data[4] << 4) + ((uint32_t)data[5]>> 4); // fa.fb.fc
    //    _rawHumidity = ((uint32_t)data[6] << 8) + ((uint32_t)data[7]); // fd.fe

    Wire.requestFrom(_address, 6);
    while (Wire.available() < 6);
    _rawPressure = ((uint32_t)Wire.read() << 12) + ((uint32_t)Wire.read() << 4) + ((uint32_t)Wire.read() >> 4); // f7.f8.f9
    _rawTemperature = ((uint32_t)Wire.read() << 12) + ((uint32_t)Wire.read() << 4) + ((uint32_t)Wire.read() >> 4); // fa.fb.fc

    if (_rawPressure == 0x80000)
    {
        return BMP280_ERROR;
    }

    // Code from Adafruit from BMP280 (BST-BMP280-DS001-11).pdf
    int64_t var1, var2, var3;

    // 1. Temperature
    var1  = ((((_rawTemperature >> 3) - ((int32_t)_calibrationT1 << 1))) * ((int32_t)_calibrationT2)) >> 11;
    var2  = (((((_rawTemperature >> 4) - ((int32_t)_calibrationT1)) * ((_rawTemperature >> 4) - ((int32_t)_calibrationT1))) >> 12) * ((int32_t)_calibrationT3)) >> 14;
    t_fine = var1 + var2;

    // _temperature  = (float)(t_fine * 5 + 128) / 25600.0;
    _temperature = (float)(t_fine) / 5120.0 + 273.15; // in Kelvin

    // 2. Pressure
    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)_calibrationP6;
    var2 = var2 + ((var1 * (int64_t)_calibrationP5) << 17);
    var2 = var2 + (((int64_t)_calibrationP4) << 35);
    var1 = ((var1 * var1 * (int64_t)_calibrationP3) >> 8) + ((var1 * (int64_t)_calibrationP2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)_calibrationP1) >> 33;

    if (var1 != 0)
    {
        var3 = 1048576 - _rawPressure;
        var3 = (((var3 << 31) - var2) * 3125) / var1;
        var1 = (((int64_t)_calibrationP9) * (var3 >> 13) * (var3 >> 13)) >> 25;
        var2 = (((int64_t)_calibrationP8) * var3) >> 19;

        var3 = ((var3 + var1 + var2) >> 8) + (((int64_t)_calibrationP7) << 4);
        _pressure = (float)var3 / 25600.0; // in hPa
    }

    return BMP280_SUCCESS;
}

float Sensor_BMP280::temperature()
{

    return _temperature;
}

float Sensor_BMP280::pressure()
{
    return _pressure;
}

void Sensor_BMP280::setPowerMode(uint8_t mode)
{
//    uint8_t value = readRegister8(_address, BMP280_CONTROL);
//    if (mode == HIGH)
//    {
//        value |=  0b00000011;
//        writeRegister8(_address, BMP280_CONTROL, value);
//    }
//    else
//    {
//        value &= ~0b00000011;
//        writeRegister8(_address, BMP280_CONTROL, value);
//    }
    uint8_t configuration = readRegister8(_address, BMP280_CONTROL);

    configuration &= 0b11111100;
    configuration |= mode;

    writeRegister8(_address, BMP280_CONTROL, configuration);
}

float Sensor_BMP280::absolutePressure(float altitudeMeters)
{
    return _pressure / pow(1 - altitudeMeters / 44330.77, 5.255876);

    // Absolute pressure from read = relative pressure would be
    // return seaLevelPressure * pow(1 - altitudeMeters / 44330.77, 5.255876);
}

float Sensor_BMP280::altitude(float seaLevelPressure)
{
    return 44330.77 * (1.0 - pow(_pressure / seaLevelPressure, 0.190263));
}

float Sensor_BMP280::altitude(float referencePressure, float referenceAltitude)
{
    // Sea level pressure
    float seaLevelPressure = referencePressure / pow(1 - referenceAltitude  / 44330.77, 5.255876);
    // Altitude based on absolute pressure
    return 44330.0 * (1.0 - pow(_pressure / seaLevelPressure, 0.1903));
}




