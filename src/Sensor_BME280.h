///
/// @file		Sensor_BME280.h
/// @brief		Library header for BME280 sensor
/// @details	BME280 Combined humidity and pressure sensor
/// @n
/// @n @b		Project SensorsBoosterPack
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
///
/// @date		20/08/2015 13:43
/// @version	102
///
/// @copyright	(c) Rei Vilo, 2015-2016
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

#ifndef Sensor_BME280_RELEASE
///
/// @brief	Release
///
#define Sensor_BME280_RELEASE 102

#define BM280_SUCCESS   0   ///< success
#define BM280_ERROR     1   ///< error

#include "Wire.h"

///
/// @brief      Class for sensor BME280
/// @details    Combined humidity and pressure sensor
/// @see        http://www.bosch-sensortec.com/de/homepage/products_3/environmental_sensors_1/bme280/bme280_1
///
class Sensor_BME280
{
  public:
    ///
    /// @brief	Constructor
    ///
    Sensor_BME280();

    ///
    /// @brief	Initialisation
    /// @todo	mode hardware accuracy
    /// @param  number of reads
    /// @note	See Table # of the BME280 data-sheet
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
    ///        result = myBME280.get();
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
    /// @brief	Return relative humidity
    /// @return relative humidity, in %
    ///
    float humidity();

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
    float _temperature;
    float _humidity;
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

    uint8_t  _calibrationH1;
    int16_t  _calibrationH2;
    uint8_t  _calibrationH3;
    int16_t  _calibrationH4;
    int16_t  _calibrationH5;
    int8_t   _calibrationH6;
};

#endif
