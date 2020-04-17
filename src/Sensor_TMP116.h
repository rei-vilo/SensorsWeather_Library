///
/// @file		Sensor_TMP116.h
/// @brief		Library header for TMP116 sensor
/// @details	TMP116 Infrared Thermopile Contactless Temperature Sensor with Integrated Math Engine
/// @n
/// @n @b		Project SensorsBoosterPack
/// @n @a		Developed with [embedXcode+](https://embedXcode.weebly.com)
///
/// @author		a0273900 Rei Vilo
/// @author		https://embeddedcomputing.weebly.com
///
/// @date		20 Nov 2019
/// @version	101
///
/// @copyright	(c) Rei Vilo, 2015-2019
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

#ifndef Sensor_TMP116_cpp
///
/// @brief	Release
///
#define Sensor_TMP116_cpp 102


///
/// @brief	TMP116 constants
/// @{
#define TMP116_SLAVE_ADDRESS            0x48

// bits fe                                fedcba9876543210
#define TMP116_ALERT_HIGH_LIMIT         0b1000000000000000
#define TMP116_ALERT_LOW_LIMIT          0b0100000000000000

// bit  d                                 fedcba9876543210
#define TMP116_DATA_REDAY               0b0010000000000000

// bit  c                                 fedcba9876543210
#define TMP116_EEPROM_BUSY              0b0001000000000000

// bits ba                                fedcba9876543210
#define TMP116_MODE_CONTINUOUS          0b0000000000000000
#define TMP116_MODE_SHUTDOWN            0b0000010000000000
#define TMP116_MODE_CONTINUOUS_BACK     0b0000100000000000
#define TMP116_MODE_ONCE                0b0000110000000000

// bits 987                               fedcba9876543210
#define TMP116_CONVERSION_15_MS         0b0000000000000000
#define TMP116_CONVERSION_125_MS        0b0000000010000000
#define TMP116_CONVERSION_250_MS        0b0000000100000000
#define TMP116_CONVERSION_500_MS        0b0000000110000000
#define TMP116_CONVERSION_1_SECOND      0b0000001000000000
#define TMP116_CONVERSION_4_SECONDS     0b0000001010000000
#define TMP116_CONVERSION_8_SECONDS     0b0000001100000000

// bits 65                                fedcba9876543210
#define TMP116_NO_AVERAGE               0b0000000000000000
#define TMP116_EIGHT_SAMPLES            0b0000000000100000
#define TMP116_THIRTY_TWO_SAMPLES       0b0000000001000000
#define TMP116_SIXTY_FOUR_SAMPLES       0b0000000001100000

// bit  4                                 fedcba9876543210
#define TMP116_MODE_TEMPERATURE         0b0000000000010000
#define TMP116_MODE_ALERT               0b0000000000000000

// bit  3                                 fedcba9876543210
#define TMP116_ALERT_PIN_HIGH           0b0000000000001000
#define TMP116_ALERT_PIN_LOW            0b0000000000000000

// bit  2                                 fedcba9876543210
#define TMP116_IRQ_DATA_READY           0b0000000000000100
#define TMP116_IRQ_ALERT                0b0000000000000000
/// @}

#include "Wire.h"

///
/// @brief      Class for sensor TMP116
/// @details    Infrared Thermopile Contactless Temperature Sensor with Integrated Math Engine
/// @see        http://www.ti.com/product/TMP116
///
class Sensor_TMP116
{
  public:
    ///
    /// @brief	Constructor
    /// @param  address default=0x48
    /// @param  pinPower pin powering the TMP116, default=0
    ///
    Sensor_TMP116(uint8_t address = TMP116_SLAVE_ADDRESS, uint8_t pinPower = 0);

    ///
    /// @brief	Initialisation
    /// @param	totalSamples default=8 samples, use pre-defined constants
    ///
    void begin(uint16_t totalSamples = TMP116_EIGHT_SAMPLES);

    ///
    /// @brief	Who Am I?
    /// @return	name of the sensor, string
    ///
    String WhoAmI();

    ///
    /// @brief	Acquisition
    ///
    void get();

    ///
    /// @brief	Measure
    /// @return	Temperature in °K
    ///
    float temperature();

    ///
    /// @brief	Manage power
    /// @param	mode LOW=default=off, HIGH=on
    /// @note   Not implemented, for compatibility only
    ///
    void setPowerMode(uint8_t mode = LOW);

  private:
    int16_t _rawTemperature;
    uint8_t _address;
    uint8_t _pinPower;
};


#endif
