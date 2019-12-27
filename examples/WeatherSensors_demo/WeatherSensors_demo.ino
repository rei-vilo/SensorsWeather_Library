///
/// @mainpage	WeatherSensors
///
/// @details	Library for different LaunchPad and BoosgerPack weather sensors
/// @n
/// @n
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
/// @date		12 Nov 2016
/// @version	105
///
/// @copyright	(c) Rei Vilo, 2016-2020
/// @copyright	CC = BY SA NC
///
/// @see		ReadMe.txt for references
///
/// @note       List of sensors and I²C addresses
/// Board | Infra-Red | Temperature | Humidity | Pressure | Light
/// ---- | ---- | ---- | ---- | ---- | ----
/// **Sensors BoosterPack** | TMP007 0x40 |  | | | OPT3001 0x47
/// | | | BME280 0x77 | BME280 0x77 | BME280 0x77 | |
/// **BASS BoosterPack** | TMP116 0x48 |  | |  | OPT3001 0x44 |
///  | | | HDC1000 0x40 | HDC1000 0x40 | | |
/// **CC1350 SensorTag** | TMP007 0x44 |  | |  | OPT3001 0x45 |
///  | | | HDC1000 0x43 | HDC1000 0x43 | | |
/// | | | BMP280 0x77 | | BMP280 0x77 | |
/// **CC1352 LPSTK** | | HDC2080 0x41 | HDC2080 0x41 | | OPT3001 0x44 |
///
/// + **BASS** = Building Automation System Sensors
/// + **LPSTK** = LaunchPad SensorTag Kit
///
///
///
/// @file		WeatherSensors.ino
/// @brief		Main sketch
///
/// @details	Example for climate sensors
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
/// @date		12 Nov 2016
/// @version	105
///
/// @copyright	(c) Rei Vilo, 2016-2020
/// @copyright	CC = BY SA NC
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
#define USE_TMP007  1
#define USE_OPT3001 1
#define USE_BME280  1

// Include application, user and local libraries
#include "Wire.h"
#include "Sensor_Units.h"


// Define variables and constants
#if (USE_TMP007 == 1)
#include "Sensor_TMP007.h"
Sensor_TMP007 myTMP007;
float TMP007_internal, TMP007_external;
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

    Serial.println("Wire.begin");
//    Wire.setModule(1);
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
    Serial.println("myBME280.begin");
    myBME280.begin();
    Serial.println("myBME280.get");
    myBME280.get();
#endif
}

// Add loop code
void loop()
{
#if (USE_TMP007 == 1)
    myTMP007.get();
    TMP007_internal = conversion(myTMP007.internal(), KELVIN, CELSIUS);
    TMP007_external = conversion(myTMP007.external(), KELVIN, CELSIUS);
    Serial.print("TMP007_internal ");
    Serial.print(TMP007_internal);
    Serial.println(CELSIUS.symbol);

    Serial.print("TMP007_external ");
    Serial.print(TMP007_external);
    Serial.println(CELSIUS.symbol);
#endif

#if (USE_OPT3001 == 1)
    myOPT3001.get();
    OPT3001_light = myOPT3001.light();
    Serial.print("OPT3001_light             ");
    Serial.print(OPT3001_light);
    Serial.println(LUX.symbol);
#endif

#if (USE_BME280 == 1)
    Serial.println("myBME280.get");
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
