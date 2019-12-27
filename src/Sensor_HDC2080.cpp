//
// Sensor_HDC2080.cpp
// Library C++ code
// ----------------------------------
// Developed with embedXcode+
// https://embedXcode.weebly.com
//
// Project         SensorsBoosterPack
//
// Created by      Rei Vilo, 22 Oct 2019
//                 https://embeddedcomputing.weebly.com
//
// Copyright       (c) Rei Vilo, 2015-2020
// Licence         CC = BY SA NC
//
// See             Sensor_HDC2080.h for references
//                 Brandon Fisher, August 1st 2017
//


// Library header
#include "Sensor_HDC2080.h"
#include "Wire_Utilities.h"

//Define Register Map
#define HDC2080_TEMPERATURE_LOW 0x00
#define HDC2080_TEMPERATURE_HIGH 0x01
#define HDC2080_HUMIDITY_LOW 0x02
#define HDC2080_HUMIDITY_HIGH 0x03
#define HDC2080_INTERRUPT_DATA_READY 0x04
#define HDC2080_TEMPERATURE_MAX 0x05
#define HDC2080_HUMIDITY_MAX 0x06
#define HDC2080_INTERRUPT_CONFIGURATION 0x07
#define HDC2080_TEMPERATURE_OFFSET_ADJUST 0x08
#define HDC2080_HUMIDITY_OFFSET_ADJUST 0x09
#define HDC2080_TEMPERATURE_THR_L 0x0a
#define HDC2080_TEMPERATURE_THR_H 0x0b
#define HDC2080_HUMIDITY_THR_L 0x0c
#define HDC2080_HUMIDITY_THR_H 0x0d
#define HDC2080_CONFIGURATION 0x0e
#define HDC2080_MEASURE_CONFIGURATION 0x0f
#define HDC2080_MID_L 0xfc
#define HDC2080_MID_H 0xfd
#define HDC2080_DEVICE_ID_L 0xfe
#define HDC2080_DEVICE_ID_H 0xff

Sensor_HDC2080::Sensor_HDC2080(uint8_t address)
{
    _address = address;
}

void Sensor_HDC2080::begin(uint8_t configuration, uint8_t measure)
{
    writeRegister8(_address, HDC2080_CONFIGURATION, configuration);
    writeRegister8(_address, HDC2080_MEASURE_CONFIGURATION, measure);
    delay(50);
    measure |= 0b00000001; // Trigger measurement
    writeRegister8(_address, HDC2080_MEASURE_CONFIGURATION, measure);
}

void Sensor_HDC2080::get()
{
    _humidity = readRegister16(_address, HDC2080_HUMIDITY_LOW, LSBFIRST);
    _temperature = readRegister16(_address, HDC2080_TEMPERATURE_LOW, LSBFIRST);
}

double Sensor_HDC2080::temperature(void)
{
    return float(_temperature) * 165.0 / 65536.0 - 40.0;
}

double Sensor_HDC2080::humidity()
{
    return float(_humidity) / 65536.0 * 100.0;
}

void Sensor_HDC2080::enableHeater(void)
{
    uint8_t _configuration = readRegister8(_address, HDC2080_CONFIGURATION);

    //set bit 3 to 1 to enable heater
    _configuration |= 0x08;

    writeRegister8(_address, HDC2080_CONFIGURATION, _configuration);
}

void Sensor_HDC2080::disableHeater(void)
{
    uint8_t _configuration = readRegister8(_address, HDC2080_CONFIGURATION);

    //set bit 3 to 0 to disable heater (all other bits 1)
    _configuration &= 0xf7;
    writeRegister8(_address, HDC2080_CONFIGURATION, _configuration);
}

float Sensor_HDC2080::rangeCheck(float value, float minValue, float maxValue)
{
    if (value < minValue)
    {
        value = minValue;
    }
    else if (value > maxValue)
    {
        value = maxValue;
    }
}


void Sensor_HDC2080::setLowTemp(float value)
{
    // Verify user is not trying to set value outside bounds
    value = rangeCheck(value, -40.0, 125.0);

    // Calculate value to load into register
    uint8_t _content = (uint8_t)(256.0 * (value + 40.0) / 165.0);

    writeRegister8(_address, HDC2080_TEMPERATURE_THR_L, _content);
}

void Sensor_HDC2080::setHighTemp(float value)
{
    // Verify user is not trying to set value outside bounds
    value = rangeCheck(value, -40.0, 125.0);

    // Calculate value to load into register
    uint8_t _content = (uint8_t)(256.0 * (value + 40.0) / 165.0);

    writeRegister8(_address, HDC2080_TEMPERATURE_THR_H, _content);
}

void Sensor_HDC2080::setHighHumidity(float value)
{
    // Verify user is not trying to set value outside bounds
    value = rangeCheck(value, 0.0, 100.0);

    // Calculate value to load into register
    uint8_t _content = (uint8_t)(256.0 * value / 100.0);

    writeRegister8(_address, HDC2080_HUMIDITY_THR_H, _content);
}

void Sensor_HDC2080::setLowHumidity(float value)
{
    // Verify user is not trying to set value outside bounds
    value = rangeCheck(value, 0.0, 100.0);

    // Calculate value to load into register
    uint8_t _content = (uint8_t)(256.0 * value / 100.0);

    writeRegister8(_address, HDC2080_HUMIDITY_THR_L, _content);
}

//  Return humidity from the low threshold register
float Sensor_HDC2080::readLowHumidityThreshold(void)
{
    uint8_t _content = readRegister8(_address, HDC2080_HUMIDITY_THR_L);
    return float(_content) * 100.0 / 256.0 ;
}

//  Return humidity from the high threshold register
float Sensor_HDC2080::readHighHumidityThreshold(void)
{
    uint8_t _content = readRegister8(_address, HDC2080_HUMIDITY_THR_H);
    return float(_content) * 100.0 / 256.0;
}

//  Return temperature from the low threshold register
float Sensor_HDC2080::readLowTempThreshold(void)
{
    uint8_t _content = readRegister8(_address, HDC2080_TEMPERATURE_THR_L);
    return float(_content) * 165.0 / 256.0 - 40.0;
}

//  Return temperature from the high threshold register
float Sensor_HDC2080::readHighTempThreshold(void)
{
    uint8_t _content = readRegister8(_address, HDC2080_TEMPERATURE_THR_H);
    return float(_content) * 165.0 / 256.0 - 40.0;
}

/*  Upper two bits of the HDC2080_MEASURE_CONFIGURATION register controls
    the temperature resolution*/
void Sensor_HDC2080::setTempRes(int resolution)
{
    uint8_t _configuration = readRegister8(_address, HDC2080_MEASURE_CONFIGURATION);

    switch (resolution)
    {
        case HDC2080_FOURTEEN_BIT:

            _configuration &= 0x3f;
            break;

        case HDC2080_ELEVEN_BIT:

            _configuration &= 0x7f;
            _configuration |= 0x40;
            break;

        case HDC2080_NINE_BIT:

            _configuration &= 0xbf;
            _configuration |= 0x80;
            break;

        default:

            _configuration &= 0x3f;
    }

    writeRegister8(_address, HDC2080_MEASURE_CONFIGURATION, _configuration);
}

/*  Bits 5 and 6 of the HDC2080_MEASURE_CONFIGURATION register controls
    the humidity resolution*/
void Sensor_HDC2080::setHumidRes(int resolution)
{
    uint8_t _configuration = readRegister8(_address, HDC2080_MEASURE_CONFIGURATION);

    switch (resolution)
    {
        case HDC2080_FOURTEEN_BIT:

            _configuration &= 0xcf;
            break;

        case HDC2080_ELEVEN_BIT:

            _configuration &= 0xdf;
            _configuration |= 0x10;
            break;

        case HDC2080_NINE_BIT:

            _configuration &= 0xef;
            _configuration |= 0x20;
            break;

        default:

            _configuration &= 0xcf;
    }

    writeRegister8(_address, HDC2080_MEASURE_CONFIGURATION, _configuration);
}

/*  Bits 2 and 1 of the HDC2080_MEASURE_CONFIGURATION register controls
    the measurement mode  */
void Sensor_HDC2080::setMeasurementMode(int mode)
{
    uint8_t _configuration = readRegister8(_address, HDC2080_MEASURE_CONFIGURATION);

    switch (mode)
    {
        case HDC2080_TEMPERATURE_AND_HUMIDITY:

            _configuration &= 0xf9;
            break;

        case HDC2080_TEMPERATURE_ONLY:

            _configuration &= 0xfc;
            _configuration |= 0x02;
            break;

        case HDC2080_HUMIDITY_ONLY:

            _configuration &= 0xfd;
            _configuration |= 0x04;
            break;

        default:

            _configuration &= 0xf9;
    }

    writeRegister8(_address, HDC2080_MEASURE_CONFIGURATION, _configuration);
}

/*  Bit 0 of the HDC2080_MEASURE_CONFIGURATION register can be used
    to trigger measurements  */
void Sensor_HDC2080::triggerMeasurement(void)
{
    uint8_t _configuration = readRegister8(_address, HDC2080_MEASURE_CONFIGURATION);

    _configuration |= 0x01;
    writeRegister8(_address, HDC2080_MEASURE_CONFIGURATION, _configuration);
}

/*  Bit 7 of the HDC2080_CONFIGURATION register can be used to trigger a
    soft reset  */
void Sensor_HDC2080::reset(void)
{
    uint8_t _configuration = readRegister8(_address, HDC2080_CONFIGURATION);

    _configuration |= 0x80;
    writeRegister8(_address, HDC2080_CONFIGURATION, _configuration);
    delay(50);
}

/*  Bit 2 of the HDC2080_CONFIGURATION register can be used to enable/disable
    the interrupt pin  */
void Sensor_HDC2080::enableInterrupt(void)
{
    uint8_t _configuration = readRegister8(_address, HDC2080_CONFIGURATION);

    _configuration |= 0x04;
    writeRegister8(_address, HDC2080_CONFIGURATION, _configuration);
}

/*  Bit 2 of the HDC2080_CONFIGURATION register can be used to enable/disable
    the interrupt pin  */
void Sensor_HDC2080::disableInterrupt(void)
{
    uint8_t _configuration = readRegister8(_address, HDC2080_CONFIGURATION);

    _configuration &= 0xfb;
    writeRegister8(_address, HDC2080_CONFIGURATION, _configuration);
}

/*  Bits 6-4  of the HDC2080_CONFIGURATION register controls the measurement
    rate  */
void Sensor_HDC2080::setRate(int rate)
{
    uint8_t _configuration = readRegister8(_address, HDC2080_CONFIGURATION);

    switch (rate)
    {
        case HDC2080_MANUAL:

            _configuration &= 0x8f;
            break;

        case HDC2080_TWO_MINUTES:

            _configuration &= 0x9f;
            _configuration |= 0x10;
            break;

        case HDC2080_ONE_MINUTE:

            _configuration &= 0xaf;
            _configuration |= 0x20;
            break;

        case HDC2080_TEN_SECONDS:

            _configuration &= 0xbf;
            _configuration |= 0x30;
            break;

        case HDC2080_FIVE_SECONDS:

            _configuration &= 0xcf;
            _configuration |= 0x40;
            break;

        case HDC2080_ONE_HZ:

            _configuration &= 0xdf;
            _configuration |= 0x50;
            break;

        case HDC2080_TWO_HZ:

            _configuration &= 0xef;
            _configuration |= 0x60;
            break;

        case HDC2080_FIVE_HZ:

            _configuration |= 0x70;
            break;

        default:

            _configuration &= 0x8f;
    }

    writeRegister8(_address, HDC2080_CONFIGURATION, _configuration);
}

/*  Bit 1 of the HDC2080_CONFIGURATION register can be used to control the
    the interrupt pins polarity */
void Sensor_HDC2080::setInterruptPolarity(int polarity)
{
    uint8_t _configuration = readRegister8(_address, HDC2080_CONFIGURATION);

    switch (polarity)
    {
        case HDC2080_ACTIVE_LOW:

            _configuration &= 0xfd;
            break;

        case HDC2080_ACTIVE_HIGH:

            _configuration |= 0x02;
            break;

        default:

            _configuration &= 0xfd;
    }

    writeRegister8(_address, HDC2080_CONFIGURATION, _configuration);
}

/*  Bit 0 of the HDC2080_CONFIGURATION register can be used to control the
    the interrupt pin's mode */
void Sensor_HDC2080::setInterruptMode(int mode)
{
    uint8_t _configuration = readRegister8(_address, HDC2080_CONFIGURATION);

    switch (mode)
    {
        case HDC2080_LEVEL_MODE:
            _configuration &= 0xfe;
            break;

        case HDC2080_COMPARATOR_MODE:
            _configuration |= 0x01;
            break;

        default:
            _configuration &= 0xfe;
    }

    writeRegister8(_address, HDC2080_CONFIGURATION, _configuration);
}

uint8_t Sensor_HDC2080::readInterruptStatus(void)
{
    uint8_t _content = readRegister8(_address, HDC2080_INTERRUPT_DATA_READY);
    return _content;
}

//  Clears the maximum temperature register
void Sensor_HDC2080::clearMaxTemp(void)
{
    writeRegister8(_address, HDC2080_TEMPERATURE_MAX, 0x00);
}

//  Clears the maximum humidity register
void Sensor_HDC2080::clearMaxHumidity(void)
{
    writeRegister8(_address, HDC2080_HUMIDITY_MAX, 0x00);
}

//  Reads the maximum temperature register
float Sensor_HDC2080::readMaxTemp(void)
{
    uint8_t _content = readRegister8(_address, HDC2080_TEMPERATURE_MAX);
    return float(_content) * 165.0 / 256.0 - 40.0;
}
//  Reads the maximum humidity register
float Sensor_HDC2080::readMaxHumidity(void)
{
    uint8_t _content = readRegister8(_address, HDC2080_HUMIDITY_MAX);
    return float(_content) * 100.0 / 256.0;
}


// Enables the interrupt pin for comfort zone operation
void Sensor_HDC2080::enableThresholdInterrupt(void)
{

    uint8_t _content = readRegister8(_address, HDC2080_INTERRUPT_CONFIGURATION);

    _content |= 0x78;

    writeRegister8(_address, HDC2080_INTERRUPT_CONFIGURATION, _content);
}

// Disables the interrupt pin for comfort zone operation
void Sensor_HDC2080::disableThresholdInterrupt(void)
{
    uint8_t _content = readRegister8(_address, HDC2080_INTERRUPT_CONFIGURATION);

    _content &= 0x87;

    writeRegister8(_address, HDC2080_INTERRUPT_CONFIGURATION, _content);
}

// enables the interrupt pin for DRDY operation
void Sensor_HDC2080::enableDRDYInterrupt(void)
{
    uint8_t _content = readRegister8(_address, HDC2080_INTERRUPT_CONFIGURATION);

    _content |= 0x80;

    writeRegister8(_address, HDC2080_INTERRUPT_CONFIGURATION, _content);
}

// disables the interrupt pin for DRDY operation
void Sensor_HDC2080::disableDRDYInterrupt(void)
{
    uint8_t _content = readRegister8(_address, HDC2080_INTERRUPT_CONFIGURATION);

    _content &= 0x7f;

    writeRegister8(_address, HDC2080_INTERRUPT_CONFIGURATION, _content);
}
