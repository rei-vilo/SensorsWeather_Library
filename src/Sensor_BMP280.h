///
/// @file		Sensor_BMP280.h
/// @brief		Library header for BMP280 sensor
/// @details	BMP280 Combined humidity and pressure sensor
/// @n
/// @n @b		Project SensorsBoosterPack
/// @n @a		Developed with [embedXcode+](https://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		https://embeddedcomputing.weebly.com
///
/// @date		20 Aug 2015
/// @version	102
///
/// @copyright	(c) Rei Vilo, 2015-2020
/// @copyright	CC = BY SA NC
///
/// @see		ReadMe.txt for references
/// * Pressure Altimetry using the MPL3115A2
/// @n  http://cache.freescale.com/files/sensors/doc/app_note/AN4528.pdf
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

#ifndef Sensor_BMP280_RELEASE
///
/// @brief	Release
///
#define Sensor_BMP280_RELEASE 102

///
/// @brief    Default I2C address
///
#define BMP280_SLAVE_ADDRESS  0x77

#define BM280_SUCCESS   0   ///< success
#define BM280_ERROR     1   ///< error

///
/// @brief    BME280 modes
/// @{
#define BME280_FORCED_MODE 0b01 ///< Forced mode
#define BME280_SLEEP_MODE 0b00 ///< Sleep mode
#define BME280_NORMAL_MODE 0b11 ///< Normal mode
/// @}

#include "Wire.h"

///
/// @brief      Class for sensor BMP280
/// @details    Combined humidity and pressure sensor
/// @see        http://www.bosch-sensortec.com/en/bst/products/all_products/bmp280
///
class Sensor_BMP280
{
  public:
    ///
    /// @brief	Constructor
    /// @param	address I2C slave address
    /// @note   Valid addresses are 0x76..0x78
    ///
    Sensor_BMP280(uint8_t address = BMP280_SLAVE_ADDRESS);


    ///
    /// @brief	Initialisation
    /// @todo	mode hardware accuracy
    /// @param  number of reads
    /// @note	See Table # of the BMP280 data-sheet
    /// @todo   Add options
    ///
    void begin();

    ///
    ///	@brief  Who am I?
    ///	@return Who am I? string
    ///
    String WhoAmI();

    ///
    ///	@brief	Acquire data
    /// @return 0 if success, error code otherwise
    /// @code
    ///    do
    ///    {
    ///        delay(100);
    ///        result = myBMP280.get();
    ///        count++;
    ///    }
    ///    while ((result > 0) and (count < 8));
    /// @endcode
    ///
    uint8_t get();

    ///
    /// @brief	Return temperature
    /// @return temperature, in °K
    /// @note   Use conversion() for another unit
    ///
    float temperature();

    ///
    /// @brief	Return pressure, relative to current altitude
    /// @return pressure, in hPa
    /// @note   Use conversion() for another unit
    ///
    float pressure();

    ///
    /// @brief	Return absolute pressure, equivalent at sea level
    /// @param  altitudeMeters current altitude, in meter
    /// @return absolute pressure at sea level, in hPa
    /// @note   Use conversion() for another unit
    ///
    float absolutePressure(float altitudeMeters = 50.0);

    ///
    /// @brief	Return altitude based on pressure
    /// @param  seaLevelPressure pressure at sea level, in hPa
    /// @return altitude, in meter
    /// @note   Use conversion() for another unit
    ///
    float altitude(float seaLevelPressure = 1013.250);

    ///
    /// @brief	Return altitude based on reference pressure and altitude
    /// @param  referencePressure reference pressure, in hPa
    /// @param  referenceAltitude reference altitude, in meter
    /// @return altitude in meter
    /// @note   The reference is a measure of the pressure at a known altitude.
    /// @note   Use conversion() for another unit
    ///
    float altitude(float referencePressure = 1013.250, float referenceAltitude = 0.0);

    ///
    /// @brief	Set power mode
    /// @param  mode default=LOW=sleep, HIGH=activated
    ///
    void setPowerMode(uint8_t mode = LOW);

  private:
    uint8_t _address;
    float _temperature;
    float _pressure;

    uint16_t _calibrationT1;
    int16_t  _calibrationT2;
    int16_t  _calibrationT3;

    uint16_t _calibrationP1;
    int16_t  _calibrationP2;
    int16_t  _calibrationP3;
    int16_t  _calibrationP4;
    int16_t  _calibrationP5;
    int16_t  _calibrationP6;
    int16_t  _calibrationP7;
    int16_t  _calibrationP8;
    int16_t  _calibrationP9;
};

#endif
