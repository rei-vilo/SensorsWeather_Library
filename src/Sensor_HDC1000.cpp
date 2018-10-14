//
// Sensor_HDC1000.cpp
// Library C++ code
// ----------------------------------
// Developed with embedXcode+
// http://embedXcode.weebly.com
//
// Project 		smartWatch
//
// Created by 	ReiVilo, 12 Mar 2016
// 				ReiVilo
//
// Copyright 	(c) Rei Vilo, 2016-2018
// Licence		CC = BY SA NC
//
// See 			Sensor_HDC1000.h and ReadMe.txt for references
//


// Library header
#include "Sensor_HDC1000.h"
#include "Wire_Utilities.h"

#define HDC1000_TEMPERATURE     0x00
#define HDC1000_HUMIDITY        0x01
#define HDC1000_CONFIGURATION   0x02


Sensor_HDC1000::Sensor_HDC1000(uint8_t address)
{
    _address = address;
}

void Sensor_HDC1000::begin(uint8_t configuration)
{
    // 1  1 11 0 0  0 0  0
    // 5  2 10 8 7  4 3  0
    // 0001 0000 0000 0000
    // 0001 0000 0000 0000

    configuration |= HDC1000_MODE_SEQUENCE;

//    writeRegister88(_address, HDC1000_CONFIGURATION, configuration, 0x00);
        Wire.beginTransmission(_address);
        Wire.write(HDC1000_CONFIGURATION);
        Wire.write(configuration);
        Wire.write(0x00);
        Wire.endTransmission();
}

void Sensor_HDC1000::get()
{
    // Doesn't work because a delay is required
    //     _rawTemperature = readRegister16(_address, HDC1000_TEMPERATURE);
    //     _rawHumidity    = readRegister16(_address, HDC1000_HUMIDITY);
    //     Serial.println(_rawTemperature, DEC);
    //     Serial.println(_rawHumidity, DEC);

    Wire.beginTransmission(_address);
    Wire.write(HDC1000_TEMPERATURE);
    Wire.endTransmission();
    
    // delay(20);
    uint32_t chrono = millis() + 20;
    while (millis() < chrono);
    // Table 7.5 Electrical Characteristics
    // Actually 10 ms for temperature + 10 ms for humidity

    Wire.requestFrom(_address, 4);
    while (Wire.available() < 4);

    _rawTemperature  = Wire.read() << 8;
    _rawTemperature |= Wire.read();

    _rawHumidity  = Wire.read() << 8;
    _rawHumidity |= Wire.read();
}

double Sensor_HDC1000::temperature()
{
    // 165 / 2^16 = 0,0025177002
    return (double)_rawTemperature * 160.0 / 65536.0 - 40.0 + 273.15;
}

double Sensor_HDC1000::humidity()
{
    // 100 / 2^16 = 0,0015258789
    return (double)_rawHumidity * 100.0 / 65536.0;
}

void Sensor_HDC1000::setPowerMode(uint8_t mode)
{
    ;
}


// Code
