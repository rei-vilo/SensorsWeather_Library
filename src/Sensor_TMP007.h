///
/// @file		Sensor_TMP007.h
/// @brief		Library header for TMP007 sensor
/// @details	TMP007 Infrared Thermopile Contactless Temperature Sensor with Integrated Math Engine
/// @n
/// @n @b		Project SensorsBoosterPack
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		a0273900 Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
///
/// @date		20/08/2015 13:42
/// @version	102
///
/// @copyright	(c) Rei Vilo, 2015-2016
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

#ifndef Sensor_TMP007_cpp
///
/// @brief	Release
///
#define Sensor_TMP007_cpp 102


///
/// @brief	TMP007 constants
/// @{
#define TMP007_ONE_SAMPLE               0x0000
#define TMP007_TWO_SAMPLES              0x0200
#define TMP007_FOUR_SAMPLES             0x0400
#define TMP007_EIGHT_SAMPLES            0x0600
#define TMP007_SIXTEEN_SAMPLES          0x0800
#define TMP007_ONE_SAMPLE_LOW_POWER     0x0A00
#define TMP007_TWO_SAMPLES_LOW_POWER    0x0C00
#define TMP007_FOUR_SAMPLES_LOW_POWER   0x0E00
/// @}

#include "Wire.h"

///
/// @brief      Class for sensor TMP007
/// @details    Infrared Thermopile Contactless Temperature Sensor with Integrated Math Engine
/// @see        http://www.ti.com/product/TMP007
///
class Sensor_TMP007
{
  public:
    ///
    /// @brief	Constructor
    ///
    Sensor_TMP007();

    ///
    /// @brief	Initialisation
    /// @param	totalSamples default = 4 samples, use pre-defined constants
    ///
    void begin(uint16_t totalSamples = TMP007_FOUR_SAMPLES);

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
    /// @return	Internal temperature in °K
    ///
    float internalTemperature();

    ///
    /// @brief	Measure
    /// @return	External temperature in °K
    ///
    float externalTemperature();

    ///
    /// @brief	Manage power
    /// @param	mode LOW=default=off, HIGH=on
    ///
    void setPowerMode(uint8_t mode = LOW);


  private:
    float _internalTemperature;
    float _externalTemperature;
};


#endif
