///
/// @file		Sensor_Units.h
/// @brief		Library header
/// @details	Units conversion for sensors
/// @n
/// @n @b		Project SensorsBoosterPack
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
///
/// @date		Aug 20, 2015 19:03
/// @version	102
///
/// @copyright	(c) Rei Vilo, 2015-2016
/// @copyright	CC = SA BY NC
///
/// @see		ReadMe.txt for references
///

#ifndef Sensor_Units_RELEASE
///
/// @brief	Release
///
#define Sensor_Units_RELEASE 102


// Include core library - IDE-based
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


// Library header
///
/// @brief      Units
/// @details	A unit contains gain and base for conversion based on the SI reference unit.
/// @note       For each set of units, all units are defined the SI reference unit
/// @todo       A better solution would be typed enum.
/// @n			unit = (SI reference unit) * gain + base
///
/// @{
struct unit_conversion_s
{
    float gain; ///< gain
    float base; ///< base
    char  symbol[4]; ///< symbol
};
/// @}

///
/// @brief	Temperature units
/// @{
typedef unit_conversion_s temperature_unit_t;
const temperature_unit_t KELVIN      = { 1, 0, "°K"};          ///< °K degree kelvin, SI reference
const temperature_unit_t CELSIUS     = { 1, -273.15, "°C"};    ///< °C degree celsius
const temperature_unit_t FAHRENHEIT  = { 1.8, -459.67, "°F"};  ///< °F degree fahrenheit
/// @}

///
/// @brief	Pressure units
/// @{
typedef unit_conversion_s pressure_unit_t;
const pressure_unit_t    PASCAL      = { 1, 0, "Pa"};           ///< Pa pascal, SI reference
const pressure_unit_t    HECTOPASCAL = { 1e-2, 0, "hPa"};       ///< hPa hecto pascal, SI reference
const pressure_unit_t    BAR         = { 1e-5, 0, "bar"};       ///< bar
const pressure_unit_t    ATMOSPHERE  = { 1.0 / 101325.0, 0, "atm"}; ///< atmosphere
const pressure_unit_t    PSI         = { 0.014503773801, 0, "atm"};  ///< 0.014503773801 pound force/square inch
/// @}

///
/// @brief	Altitude units
/// @{
typedef unit_conversion_s altitude_unit_t;
const altitude_unit_t    METRE       = { 1, 0, "m"};           ///< m metre, SI reference
const altitude_unit_t    FOOT        = { 0.3048, 0, "ft"};     ///< ft foot
/// @}

///
/// @brief	Light units
/// @{
typedef unit_conversion_s light_unit_t;
const light_unit_t       LUX         = { 1, 0, "lux"};          ///< lux, SI reference
/// @}

///
/// @brief	Conversion utility
/// @param	value input value to be converted, float
/// @param	unitFrom unit of the input value to be converted
/// @param	unitTo unit for the output converted value
/// @return	output converted value, float
///
template <typename myType>
float conversion(float value, myType unitFrom, myType unitTo)
{
    return (value - unitFrom.base) / unitFrom.gain * unitTo.gain + unitTo.base;
}

///
/// @brief	Unit symbol as String
/// @param	unit unit constant
/// @return	symbol as String
///
template <typename myType>
String symbolString(myType unit)
{
    return String(unit.symbol);
}

///
/// @brief	Unit symbol as char*
/// @param	unit unit constant
/// @return	symbol as char*
///
template <typename myType>
char * symbolChar(myType unit)
{
    return unit.symbol;
}

#endif
