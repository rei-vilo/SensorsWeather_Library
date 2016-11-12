///
/// @mainpage	WeatherSensors
///
/// @details	Description of the project
/// @n
/// @n
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
/// @date		nov. 12, 2016 19:37
/// @version	<#version#>
///
/// @copyright	(c) Rei Vilo, 2016
/// @copyright	GNU General Public Licence
///
/// @see		ReadMe.txt for references
///


///
/// @file		WeatherSensors.ino
/// @brief		Main sketch
///
/// @details	<#details#>
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
/// @date		nov. 12, 2016 19:37
/// @version	<#version#>
///
/// @copyright	(c) Rei Vilo, 2016
/// @copyright	GNU General Public Licence
///
/// @see		ReadMe.txt for references
/// @n
///


// Core library for code-sense - IDE-based
#if defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#else // error
#error Platform not supported
#endif // end IDE

// Set parameters
#define USE_TMP007  0
#define USE_OPT3001 1
#define USE_BME280  1

// Include application, user and local libraries
#include "Wire.h"
#include "Sensor_Units.h"


// Define variables and constants
#if (USE_TMP007 == 1)
#include "Sensor_TMP007.h"
Sensor_TMP007 myTMP007;
float TMP007_internalTemperature, TMP007_externalTemperature;
#endif

#if (USE_OPT3001 == 1)
#include "Sensor_OPT3001.h"
Sensor_OPT3001 myOPT3001;
float OPT3001_light;
#endif

#if (USE_BME280 == 1)
#include "Sensor_BME280.h"
Sensor_BME280 myBME280;
float BME280_pressure, BME280_temperature, BME280_humidity;
#endif

// Edit period_ms
const uint32_t period_ms = 10000;


// Add setup code
void setup()
{
    Serial.begin(9600);
    Wire.begin();

#if (USE_TMP007 == 1)
    myTMP007.begin(TMP007_FOUR_SAMPLES);
    myTMP007.get();
#endif

#if (USE_OPT3001 == 1)
    myOPT3001.begin();
    myOPT3001.get();
#endif

#if (USE_BME280 == 1)
    myBME280.begin();
    myBME280.get();
#endif
}

// Add loop code
void loop()
{
#if (USE_TMP007 == 1)
    myTMP007.get();
    TMP007_internalTemperature = conversion(myTMP007.internalTemperature(), KELVIN, CELSIUS);
    TMP007_externalTemperature = conversion(myTMP007.externalTemperature(), KELVIN, CELSIUS));
    Serial.print("TMP007_internalTemperature ");
    Serial.print(TMP007_internalTemperature);
    Serial.println(CELSIUS.symbol)

    Serial.print("TMP007_externalTemperature ");
    Serial.print(TMP007_externalTemperature);
    Serial.println(CELSIUS.symbol)
#endif

#if (USE_OPT3001 == 1)
    myOPT3001.get();
    OPT3001_light = myOPT3001.light();
    Serial.print("OPT3001_light             ");
    Serial.print(OPT3001_light);
    Serial.println(LUX.symbol);
#endif

#if (USE_BME280 == 1)
    myBME280.get();
    BME280_pressure = myBME280.pressure();
    BME280_temperature = conversion(myBME280.temperature(), KELVIN, CELSIUS);
    BME280_humidity = myBME280.humidity();

    Serial.print("BME280_pressure           ");
    Serial.print(BME280_pressure);
    Serial.println(HECTOPASCAL.symbol);

    Serial.print("BME280_temperature        ");
    Serial.print(BME280_temperature);
    Serial.println(CELSIUS.symbol);

    Serial.print("BME280_humidity           ");
    Serial.print(BME280_humidity);
    Serial.println("%");
#endif

    Serial.println();
    delay(period_ms);
}
