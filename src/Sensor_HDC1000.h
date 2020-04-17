///
/// @file		Sensor_HDC1000.h
/// @brief		Library header
/// @details	HDC1000 Temperature and Humidity Sensor
/// @n
/// @n @b		Project smartWatch
/// @n @a		Developed with [embedXcode+](https://embedXcode.weebly.com)
///
/// @author		ReiVilo
/// @author		ReiVilo
///
/// @date		12 Mar 2016
/// @version	101
///
/// @copyright	(c) Rei Vilo, 2016-2020
/// @copyright	CC = BY SA NC
///
/// @see		ReadMe.txt for references
///


// Core library for code-sense - IDE-based
#if defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"
#elif defined(ROBOTIS) // Robotis specific
#include "libpandora_types.h"
#include "pandora.h"
#elif defined(MPIDE) // chipKIT specific
#include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
#include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#elif defined(LITTLEROBOTFRIENDS) // LittleRobotFriends specific
#include "LRF.h"
#elif defined(MICRODUINO) // Microduino specific
#include "Arduino.h"
#elif defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#elif defined(REDBEARLAB) // RedBearLab specific
#include "Arduino.h"
#elif defined(RFDUINO) // RFduino specific
#include "Arduino.h"
#elif defined(SPARK) // Spark specific
#include "application.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
#include "Arduino.h"
#else // error
#   error Platform not defined
#endif // end IDE

#ifndef Sensor_HDC1000_cpp
#define Sensor_HDC1000_cpp

#include "Wire.h"

#define HDC1000_I2C_ADDRESS 0x43

//                                    1    1 0
//                                    5    0 8
#define HDC1000_RESET               0b10000000

#define HDC1000_HEATER_DISABLED     0
#define HDC1000_HEATER_ENABLED      0b00100000

#define HDC1000_MODE_EITHER         0
#define HDC1000_MODE_SEQUENCE       0b00010000

#define HDC1000_TEMPERATURE_14_BITS 0
#define HDC1000_TEMPERATURE_11_BITS 0b00000100

#define HDC1000_HUMIDITY_14_BITS    0
#define HDC1000_HUMIDITY_11_BITS    0b00000001
#define HDC1000_HUMIDITY_8_BITS     0b00000010

#define HDC1000_SETTINGS            0b00010101

///
/// @brief      Class for sensor HDC1000
/// @details    Temperature and Humidity Sensor
/// @see        http://www.ti.com/product/HDC1000
///
class Sensor_HDC1000
{
  public:
    ///
    /// @brief	Constructor
    /// @param	address I2C slave address
    /// @note   Valid addresses are 0x40..0x43
    ///
    Sensor_HDC1000(uint8_t address = HDC1000_I2C_ADDRESS);

    ///
    /// @brief	Initialisation
    /// @param	configuration default=HDC1000_SETTINGS
    ///
    void begin(uint8_t configuration = HDC1000_SETTINGS);

    ///
    /// @brief	Acquisition
    ///
    void get();

    ///
    /// @brief	Measure
    /// @return	Temperature in °K
    ///
    double temperature();

    ///
    /// @brief	Measure
    /// @return	Relative humidity in %
    ///
    double humidity();

    ///
    /// @brief    Manage power
    /// @param    mode LOW=default=off, HIGH=on
    /// @note     Empty function, for compatibility only
    ///
    void setPowerMode(uint8_t mode = LOW);

  private:
    uint8_t  _address;

    uint16_t _rawTemperature;
    uint16_t _rawHumidity;
};

#endif
