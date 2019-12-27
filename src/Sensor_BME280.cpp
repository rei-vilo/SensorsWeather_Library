//
// Sensor_BME280.cpp
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
// See 			Sensor_BME280.h and ReadMe.txt for references
//



// 0xF7 to 0xFE
#define BME280_SLAVE_ADDRESS 0x77

#define BME280_DATA_F7_FE 0xf7
#define BME280_CONTROL_TEMPERATURE_PRESSURE 0xf4
#define BME280_CONTROL_HUMIDITY 0xf2
#define BME280_STATUS 0xf3
#define BME280_CONFIGURATION 0xf5
#define BME280_RESET 0xe0

#define BME280_VALUE_RESET_EXECUTE 0xb6

#define BME280_CALIBRATION_T1 0x88
#define BME280_CALIBRATION_T2 0x8a
#define BME280_CALIBRATION_T3 0x8c
#define BME280_CALIBRATION_P1 0x8e
#define BME280_CALIBRATION_P2 0x90
#define BME280_CALIBRATION_P3 0x92
#define BME280_CALIBRATION_P4 0x94
#define BME280_CALIBRATION_P5 0x96
#define BME280_CALIBRATION_P6 0x98
#define BME280_CALIBRATION_P7 0x9a
#define BME280_CALIBRATION_P8 0x9c
#define BME280_CALIBRATION_P9 0x9e
#define BME280_calibrationH1 0xa1

#define BME280_calibrationH2 0xe1
#define BME280_calibrationH3 0xe3
#define BME280_calibrationH4 0xe4
#define BME280_calibrationH5 0xe5
#define BME280_calibrationH6 0xe7

// Library header
#include "Sensor_BME280.h"
#include "Wire_Utilities.h"

// Code

Sensor_BME280::Sensor_BME280(uint8_t address)
{
    _slaveAddressBME280 = address;
}

String Sensor_BME280::WhoAmI()
{
    return "BME280 temperature + humidity + pressure";
}

void Sensor_BME280::begin()
{
    writeRegister8(_slaveAddressBME280, BME280_RESET, BME280_VALUE_RESET_EXECUTE);
    delay(100);
    writeRegister8(_slaveAddressBME280, BME280_CONTROL_TEMPERATURE_PRESSURE, 0x25);
    // 001.001.01 Default = 0x00
    // 001.___.__ Pressure oversampling x1
    // ___.001.__ Temperature oversampling x1
    // ___.___.01 Mode = forced mode

    writeRegister8(_slaveAddressBME280, BME280_CONTROL_HUMIDITY, 0x01);
    /// xxxxx.011 Default = 0x00
    /// _____.001 Humidity oversampling x1

    //    Register Address	Register content	Data type
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x88 / 0x89		dig_T1 [7:0] / [15:8]	unsigned short = uint16_t
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x8A / 0x8B		dig_T2 [7:0] / [15:8]	signed short = int16_t
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x8C / 0x8D		dig_T3 [7:0] / [15:8]	signed short
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x8E / 0x8F		dig_P1 [7:0] / [15:8]	unsigned short = uint16_t
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x90 / 0x91		dig_P2 [7:0] / [15:8]	signed short
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x92 / 0x93		dig_P3 [7:0] / [15:8]	signed short
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x94 / 0x95		dig_P4 [7:0] / [15:8]	signed short
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x96 / 0x97		dig_P5 [7:0] / [15:8]	signed short
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x98 / 0x99		dig_P6 [7:0] / [15:8]	signed short
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x9A / 0x9B		dig_P7 [7:0] / [15:8]	signed short
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x9C / 0x9D		dig_P8 [7:0] / [15:8]	signed short
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0x9E / 0x9F		dig_P9 [7:0] / [15:8]	signed short
    //    0xA1              dig_H1 [7:0]￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼            unsigned char = uint8_t
    //    0xE1 / 0xE2  		dig_H2 [7:0] / [15:8]	signed short = int16_t
    //    0xE3              dig_H3 [7:0]            unsigned char = uint8_t
    //    0xE4 / 0xE5[3:0]	dig_H4 [11:4] / [3:0]	signed short = int16_t
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0xE5[7:4] / 0xE6	dig_H5 [3:0] / [11:4]	signed short = int16_t
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0xE7				dig_H6                  signed char = int8_t

    _calibrationT1 = readRegister16(_slaveAddressBME280, BME280_CALIBRATION_T1, LSBFIRST); // uint16_t
    _calibrationT2 = readRegister16(_slaveAddressBME280, BME280_CALIBRATION_T2, LSBFIRST); // int16_t
    _calibrationT3 = readRegister16(_slaveAddressBME280, BME280_CALIBRATION_T3, LSBFIRST); // int16_t

    _calibrationP1 = readRegister16(_slaveAddressBME280, BME280_CALIBRATION_P1, LSBFIRST); // uint16_t
    _calibrationP2 = readRegister16(_slaveAddressBME280, BME280_CALIBRATION_P2, LSBFIRST); // int16_t
    _calibrationP3 = readRegister16(_slaveAddressBME280, BME280_CALIBRATION_P3, LSBFIRST); // int16_t
    _calibrationP4 = readRegister16(_slaveAddressBME280, BME280_CALIBRATION_P4, LSBFIRST); // int16_t
    _calibrationP5 = readRegister16(_slaveAddressBME280, BME280_CALIBRATION_P5, LSBFIRST); // int16_t
    _calibrationP6 = readRegister16(_slaveAddressBME280, BME280_CALIBRATION_P6, LSBFIRST); // int16_t
    _calibrationP7 = readRegister16(_slaveAddressBME280, BME280_CALIBRATION_P7, LSBFIRST); // int16_t
    _calibrationP8 = readRegister16(_slaveAddressBME280, BME280_CALIBRATION_P8, LSBFIRST); // int16_t
    _calibrationP9 = readRegister16(_slaveAddressBME280, BME280_CALIBRATION_P9, LSBFIRST); // int16_t

    _calibrationH1 = readRegister8(_slaveAddressBME280, BME280_calibrationH1); // uint8_t
    _calibrationH2 = readRegister16(_slaveAddressBME280, BME280_calibrationH2, LSBFIRST); // int16_t
    _calibrationH3 = readRegister8(_slaveAddressBME280, BME280_calibrationH3); // uint8_t

    //    0xE4 / 0xE5[3:0]	dig_H4 [11:4] / [3:0]	signed short = int16_t
    _calibrationH4  = (readRegister8(_slaveAddressBME280, 0xe4) << 4) + (readRegister8(_slaveAddressBME280, 0xe5) & 0x0f);
    //    ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼0xE5[7:4] / 0xE6	dig_H5 [3:0] / [11:4]	signed short = int16_t
    _calibrationH5  = (readRegister8(_slaveAddressBME280, 0xe5) >> 4) + (readRegister8(_slaveAddressBME280, 0xe6) << 4);

    _calibrationH6 = readRegister8(_slaveAddressBME280, BME280_calibrationH6); // int8_t

    /*
        QuickDebugln("calibration T1 ui16: %i", _calibrationT1);
        QuickDebugln("calibration T2 i16:  %i", _calibrationT2);
        QuickDebugln("calibration T3 i16:  %i", _calibrationT3);

        QuickDebugln("calibration P1 ui16: %i", _calibrationP1);
        QuickDebugln("calibration P2 i16:  %i", _calibrationP2);
        QuickDebugln("calibration P3 i16:  %i", _calibrationP3);
        QuickDebugln("calibration P4 i16:  %i", _calibrationP4);
        QuickDebugln("calibration P5 i16:  %i", _calibrationP5);
        QuickDebugln("calibration P6 i16:  %i", _calibrationP6);
        QuickDebugln("calibration P7 i16:  %i", _calibrationP7);
        QuickDebugln("calibration P8 i16:  %i", _calibrationP8);
        QuickDebugln("calibration P9 i16:  %i", _calibrationP9);

        QuickDebugln("calibration H1 ui8:  %i", _calibrationH1);
        QuickDebugln("calibration H2 i16:  %i", _calibrationH2);
        QuickDebugln("calibration H3 ui8:  %i", _calibrationH3);
        QuickDebugln("calibration H4 i16:  %i", _calibrationH4);
        QuickDebugln("calibration H5 i16:  %i", _calibrationH5);
        QuickDebugln("calibration H6 i8:   %i", _calibrationH6);
    */

    // Is some delay needed for readiness?
    delay(100);
    // First dummy reading required?
    get();
}

uint8_t Sensor_BME280::get()
{
    // Power-up
    setPowerMode(HIGH);

    int32_t _rawPressure, _rawTemperature, _rawHumidity;
    int64_t t_fine;
    _rawPressure = 0;
    _rawTemperature = 0;
    _rawHumidity = 0;
    //    while (readRegister8(_slaveAddressBME280, BME280_STATUS) & 0x08);

    Wire.beginTransmission(_slaveAddressBME280);
    Wire.write(BME280_DATA_F7_FE);
    Wire.endTransmission();

    //    uint8_t data[8];
    //    Wire.requestFrom(_slaveAddressBME280, 8);
    //    while (Wire.available() < 8);
    //    for (uint8_t i=0; i<8; i++) {
    //        data[i] = Wire.read();
    //    }
    //
    //    _rawPressure = ((uint32_t)data[0] << 12) + ((uint32_t)data[1] << 4) + ((uint32_t)data[2]>> 4); // f7.f8.f9
    //    _rawTemperature = ((uint32_t)data[3] << 12) + ((uint32_t)data[4] << 4) + ((uint32_t)data[5]>> 4); // fa.fb.fc
    //    _rawHumidity = ((uint32_t)data[6] << 8) + ((uint32_t)data[7]); // fd.fe

    Wire.requestFrom(_slaveAddressBME280, 8);
    while (Wire.available() < 8);
    _rawPressure = ((uint32_t)Wire.read() << 12) + ((uint32_t)Wire.read() << 4) + ((uint32_t)Wire.read() >> 4); // f7.f8.f9
    _rawTemperature = ((uint32_t)Wire.read() << 12) + ((uint32_t)Wire.read() << 4) + ((uint32_t)Wire.read() >> 4); // fa.fb.fc
    _rawHumidity = ((uint32_t)Wire.read() << 8) + ((uint32_t)Wire.read()); // fd.fe

    if (_rawPressure == 0x80000)
    {
        return BM280_ERROR;
        //        Serial.print("!!! Error");
    }

    //    QuickDebugln("_rawPressure    %x", _rawPressure);
    //    QuickDebugln("_rawTemperature %x", _rawTemperature);
    //    QuickDebugln("_rawHumidity    %x", _rawHumidity);


    /*
        // Code from Bosch
        // 1. Temperature
        int32_t v_x1_u32, v_x2_u32;
        int32_t t_fine;

        v_x1_u32  = ((((_rawTemperature>> 3) - ((int32_t)_calibrationT1 << 1))) * ((int32_t)_calibrationT2))>> 11;
        v_x2_u32  = (((((_rawTemperature>> 4) - ((int32_t)_calibrationT1)) * ((_rawTemperature>> 4) - ((int32_t)_calibrationT1)))>> 12) * ((int32_t)_calibrationT3))>> 14;
        t_fine = v_x1_u32 + v_x2_u32;

        QuickDebugln("v_x1_u32 %i, v_x2_u32 %i \r\n", v_x1_u32, v_x2_u32);

        //    _temperature = (float)(t_fine * 5 + 128) * (1.0/256.0);
        //    _temperature = (float)(t_fine * 10 + 256) * (1.0/512.0);
        _temperature = (float)(v_x1_u32 + v_x2_u32) / 5120.0;

        // 2. Pressure
        uint32_t pressure32;

        v_x1_u32 = (((int32_t)t_fine)>> 1) - (int32_t)64000;
        v_x2_u32 = (((v_x1_u32>> 2) * (v_x1_u32>> 2))>> 11) * ((int32_t)_calibrationP6);
        v_x2_u32 = v_x2_u32 + ((v_x1_u32 * ((int32_t)_calibrationP5)) << 1);
        v_x2_u32 = (v_x2_u32>> 2) + (((int32_t)_calibrationP4) << 16);
        v_x1_u32 = (((_calibrationP3 * (((v_x1_u32>> 2) * (v_x1_u32>> 2))>> 13))>> 3) + ((((int32_t)_calibrationP2) * v_x1_u32)>> 1))>> 18;
        v_x1_u32 = ((((32768+v_x1_u32)) * ((int32_t)_calibrationP1))>> 15);

        if (v_x1_u32 != 0) {
        // Avoid exception caused by division by zero
        pressure32 = (((uint32_t)(((int32_t)1048576) - _rawPressure) - (v_x2_u32>> 12))) * 3125;
        if (pressure32 < 0x80000000)    pressure32 = (pressure32 << 1) / ((uint32_t)v_x1_u32);
        else                            pressure32 = (pressure32 / (uint32_t)v_x1_u32) * 2;

        v_x1_u32 = (((int32_t)_calibrationP9) * ((int32_t)(((pressure32>> 3) * (pressure32>> 3))>> 13)))>> 12;
        v_x2_u32 = (((int32_t)(pressure32>> 2)) * ((int32_t)_calibrationP8))>> 13;
        //        pressure32 = (float)(uint32_t)((int32_t)pressure32 + ((v_x1_u32 + v_x2_u32 + _calibrationP7)>> 4));
        //        pressure32 = pressure32 + (v_x1_u32 + v_x2_u32 + ((float)_calibrationP7)) / 16.0;
        _pressure = (float)pressure32 + ((float)(v_x1_u32 + v_x2_u32 + _calibrationP7) / 16.0);

        }

        // 3. Humidity
        v_x1_u32 = (t_fine - ((int32_t)76800));
        v_x1_u32 = (((((_rawHumidity << 14) - (((int32_t)_calibrationH4) << 20) - (((int32_t)_calibrationH5) * v_x1_u32)) + ((int32_t)16384))>> 15) * (((((((v_x1_u32 * ((int32_t)_calibrationH6))>> 10) * (((v_x1_u32 * ((int32_t)_calibrationH3))>> 11) + ((int32_t)32768)))>> 10) + ((int32_t)2097152)) * ((int32_t)_calibrationH2) + 8192)>> 14));
        v_x1_u32 = (v_x1_u32 - (((((v_x1_u32>> 15) * (v_x1_u32>> 15))>> 7) * ((int32_t)_calibrationH1))>> 4));
        v_x1_u32 = (v_x1_u32 < 0 ? 0 : v_x1_u32);
        v_x1_u32 = (v_x1_u32 > 419430400 ? 419430400 : v_x1_u32);
        _humidity = (float)(v_x1_u32>> 12) / 512.0;
    */

    /*
        // Code from Bosch, float
        float v_x1_u32 = 0.0;
        float v_x2_u32 = 0.0;

        // 1. Temperature
        v_x1_u32  = (((float)_rawPressure) / 16384.0 - ((float)_calibrationT1) / 1024.0) * ((float)_calibrationT2);
        v_x2_u32  = ((((float)_rawTemperature) / 131072.0 - ((float)_calibrationT1) / 8192.0) * (((float)_rawTemperature) / 131072.0 - ((float)_calibrationT1) / 8192.0)) * ((float)_calibrationT3);
        t_fine = (int32_t)(v_x1_u32 + v_x2_u32);
        _temperature  = (v_x1_u32 + v_x2_u32) / 5120.0;

        // 2. Pressure
        v_x1_u32 = ((float)t_fine / 2.0) - 64000.0;
        v_x2_u32 = v_x1_u32 * v_x1_u32 * ((float)_calibrationP6) / 32768.0;
        v_x2_u32 = v_x2_u32 + v_x1_u32 * ((float)_calibrationP5) * 2.0;
        v_x2_u32 = (v_x2_u32 / 4.0) + (((float)_calibrationP4) * 65536.0);
        v_x1_u32 = (((float)_calibrationP3) * v_x1_u32 * v_x1_u32 / 524288.0 + ((float)_calibrationP2) * v_x1_u32) / 524288.0;
        v_x1_u32 = (1.0 + v_x1_u32 / 32768.0) * ((float)_calibrationP1);

        // Avoid exception caused by division by zero
        if (v_x1_u32 != 0)
        {
        _pressure = 1048576.0 - (float)_rawPressure ;
        _pressure = (_pressure - (v_x2_u32 / 4096.0)) * 6250.0 / v_x1_u32;
        v_x1_u32 = ((float)_calibrationP9) * _pressure * _pressure / 2147483648.0;
        v_x2_u32 = _pressure * ((float)_calibrationP8) / 32768.0;
        _pressure = _pressure + (v_x1_u32 + v_x2_u32 + ((float)_calibrationP7)) / 16.0;
        }

        // 3. Humidity
        float var_h = (((float)t_fine) - 76800.0);
        // Avoid invalid data

        QuickDebugln("var_h %5.2f", var_h);
        if (var_h != 0)
        {
        _humidity = (_rawHumidity - (((float)_calibrationH4) * 64.0 + ((float)_calibrationH5) / 16384.0 * var_h)) * (((float)_calibrationH2) / 65536.0 * (1.0 + ((float) _calibrationH6) / 67108864.0 * var_h * (1.0 + ((float)_calibrationH3) / 67108864.0 * var_h)));
        _humidity = _humidity * (1.0 - ((float)_calibrationH1)*var_h / 524288.0);

        QuickDebugln("_humidity %5.2f", _humidity);
        if (_humidity > 100.0)      _humidity = 100.0;
        else if (_humidity < 0.0)   _humidity = 0.0;
        }
    */

    // Code from Adafruit
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

    // 3. Humidity
    var1 = (t_fine - ((int32_t)76800));

    var1 = (((((_rawHumidity << 14) - (((int32_t)_calibrationH4) << 20) - (((int32_t)_calibrationH5) * var1)) + ((int32_t)16384)) >> 15) * (((((((var1 * ((int32_t)_calibrationH6)) >> 10) * (((var1 * ((int32_t)_calibrationH3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) * ((int32_t)_calibrationH2) + 8192) >> 14));

    var1 = (var1 - (((((var1 >> 15) * (var1 >> 15)) >> 7) * ((int32_t)_calibrationH1)) >> 4));

    if (var1 < 0)
    {
        var1 = 0;
    }
    if (var1 > 419430400)
    {
        var1 = 419430400;
    }
    _humidity = (float)(var1 >> 12) / 1024.0; // in %

    return BM280_SUCCESS;
}

float Sensor_BME280::temperature()
{

    return _temperature;
}

float Sensor_BME280::humidity()
{
    return _humidity;
}

float Sensor_BME280::pressure()
{
    return _pressure;
}

void Sensor_BME280::setPowerMode(uint8_t mode)
{
    uint8_t configuration = readRegister8(_slaveAddressBME280, BME280_CONTROL_TEMPERATURE_PRESSURE);

    configuration &= 0b11111100;
    configuration |= mode;

    writeRegister8(_slaveAddressBME280, BME280_CONTROL_TEMPERATURE_PRESSURE, configuration);
}

float Sensor_BME280::absolutePressure(float altitudeMeters)
{
    return _pressure / pow(1 - altitudeMeters / 44330.77, 5.255876);

    // Absolute pressure from read = relative pressure would be
    // return seaLevelPressure * pow(1 - altitudeMeters / 44330.77, 5.255876);
}

float Sensor_BME280::altitude(float seaLevelPressure)
{
    return 44330.77 * (1.0 - pow(_pressure / seaLevelPressure, 0.190263));
}

float Sensor_BME280::altitude(float referencePressure, float referenceAltitude)
{
    // Sea level pressure
    float seaLevelPressure = referencePressure / pow(1 - referenceAltitude  / 44330.77, 5.255876);
    // Altitude based on absolute pressure
    return 44330.0 * (1.0 - pow(_pressure / seaLevelPressure, 0.190263));
}




