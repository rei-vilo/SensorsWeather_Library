///
/// @file		Sensor_OPT3001.h
/// @brief		Library header for OPT3001 sensor
/// @details	OPT3001 Digital Ambient Light Sensor (ALS) with High Precision Human Eye Response
/// @n
/// @n @b		Project SensorsBoosterPack
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		a0273900 for initial C-library
/// @author		Rei Vilo for Energia adapted C++-library
/// @author		http://embeddedcomputing.weebly.com
///
/// @date		20 Aug 2015
/// @version	102
///
/// @copyright	(c) Rei Vilo, 2015-2018
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

#include "Wire.h"

#ifndef Sensor_OPT3001_RELEASE
///
/// @brief	Release
///
#define Sensor_OPT3001_RELEASE 102

///
/// @brief      Conversion modes
/// @{
#define OPT3001_100_MS_OFF  0xc010 // shut-down
#define OPT3001_100_MS_ONCE 0xc210 // 100 ms once
#define OPT3001_100_MS_CONTINUOUS  0xc410 ///< continous
#define OPT3001_800_MS_ONCE  0xc810 // shut-down
#define OPT3001_800_MS_OFF  0xca10 // 800 ms once
#define OPT3001_800_MS_CONTINUOUS  0xcc10 ///< continuous
#define OPT3001_INTERRUPT_PIN 11

/// @}

#define OPT3001_SLAVE_ADDRESS           0x47

///
/// @brief      Class for sensor OPT3001
/// @details    Digital Ambient Light Sensor (ALS) with High Precision Human Eye Response
/// @see        http://www.ti.com/product/OPT3001
///
class Sensor_OPT3001
{
  public:
    ///
    /// @brief	Constructor
    ///
    Sensor_OPT3001(uint8_t address = OPT3001_SLAVE_ADDRESS);

    ///
    /// @brief	Initialisation
    /// @param	configuration default = 100 ms, OPT3001_100_MS or OPT3001_800_MS
    /// @param	interruptPin default = 11
    ///
    void begin(uint16_t configuration = OPT3001_100_MS_CONTINUOUS,
               uint8_t interruptPin = OPT3001_INTERRUPT_PIN);

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
    /// @return	light in lux
    ///
    float light();
    // uint32_t light();

    ///
    /// @brief	Manage power
    /// @param	mode LOW=default=off, HIGH=on
    ///
    void setPowerMode(uint8_t mode = LOW);

    /*
        uint16_t readManufacturerId();
        uint16_t readDeviceId();
        uint16_t readConfigReg();
        uint16_t readLowLimitReg();
        uint16_t readHighLimitReg();
    */

  private:
    //	uint16_t manu_id;/**< manufacture chip id of the sensor*/
    //	uint16_t device_id;/**< device id of the sensor*/
    //	uint16_t config_reg;/**< configuration register setting*/
    //	uint16_t lowlimit_reg;/**< low limit register value*/
    //	uint16_t highlimit_reg;/**< high limit register value*/
    uint8_t _interruptPin;
    uint16_t _configuration;
    uint32_t _rawLux; ///< raw lux result register value
    uint8_t _address;
};


#endif
