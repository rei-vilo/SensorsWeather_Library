///
/// @file       Sensor_HDC2080.h
/// @brief      Library header
/// @details    Library for HDC2080 humidity and temperature sensor
/// @n
/// @n @b       Project SensorsBoosterPack
/// @n @a       Developed with [embedXcode+](https://embedXcode.weebly.com)
///
/// @author     Rei Vilo
/// @author     https://embeddedcomputing.weebly.com
///
/// @date       22 Oct 2019
/// @version    102
///
/// @copyright  (c) Rei Vilo, 2015-2020
/// @copyright  CC = BY SA NC
///
/// @see        ReadMe.txt for references
///             Brandon Fisher, August 1st 2017
///

#ifndef SENSOR_HDC2080_H
///
/// @brief    Release
///
#define SENSOR_HDC2080_H 102

#include <Energia.h>
#include <Wire.h>

///
/// @brief    Default address on LPSTK
///
#define HDC2080_I2C_ADDRESS 0x41

///
/// @brief      Default settings
/// @details    Values 0b01010000
/// * LSB b7    Sotfware reset, 0 = normal
/// *     b6:4  Auto Measurement Mode, 101 = 1 Hz
/// *     b3    Heater, 0 = off
/// *     b2    Data ready interrupt, 0 = high-Z
/// *     b2    Interrupt polarity, 0 = active low
/// * MSB b0    Interrupt mode, 0 = Level sensitive
///
/// @details    Values 0b00000000
/// * LSB b7    Sotfware reset, 0 = normal
/// *     b6:4  Auto Measurement Mode, 000 = manual
/// *     b3    Heater, 0 = off
/// *     b2    Data ready interrupt, 0 = high-Z
/// *     b2    Interrupt polarity, 0 = active low
/// * MSB b0    Interrupt mode, 0 = Level sensitive
///
#define HDC2080_DEFAULT_SETTINGS 0b00000000

///
/// @brief      Default measurement settings
/// @details    Values 0b00000000
/// * LSB b7:6  Temperature resolution, 0 = 14 bits
/// *     b5:4  Humidity resolution, 0 = 14 bits
/// *     b3    Reserved
/// *     b2:1  Measurement configuration, 0 = Humidity + Temperature
/// * MSB b0    Measurement trigger, 1 = Start measurement
///
#define HDC2080_MEASURE_SETTINGS 0b00000000

///
/// @brief    Measurement resolution
/// @{
#define HDC2080_FOURTEEN_BIT 0 ///< 14-bit
#define HDC2080_ELEVEN_BIT 1 ///< 7-bit
#define HDC2080_NINE_BIT 2 ///< 9-bit
/// @}

///
/// @brief    Sensor modes
/// @{
#define HDC2080_TEMPERATURE_AND_HUMIDITY 0 ///< temperature and humidity
#define HDC2080_TEMPERATURE_ONLY 1 ///< temperature
#define HDC2080_HUMIDITY_ONLY 2 ///< humidity
#define HDC2080_ACTIVE_LOW 0 ///< interrupt output, active low
#define HDC2080_ACTIVE_HIGH 1 ///< interrupt output, active high
#define HDC2080_LEVEL_MODE 0 ///< interrupt output, level mode
#define HDC2080_COMPARATOR_MODE 1 ///< interrupt output, comparator mode
/// @}

///
/// @brief    Sample rate
/// @{
#define HDC2080_MANUAL			0 ///< manual mode, triggered by I2C
#define HDC2080_TWO_MINUTES		1 ///< period = 2 minutes
#define HDC2080_ONE_MINUTE		2 ///< period = 1 minutes
#define HDC2080_TEN_SECONDS		3 ///< period = 10 seconds
#define	HDC2080_FIVE_SECONDS	4 ///< period = 5 seconds
#define HDC2080_ONE_HZ			5 ///< period = 1 second
#define HDC2080_TWO_HZ			6 ///< period = 0.5 second
#define HDC2080_FIVE_HZ			7 ///< period = 0.2 second
/// @}


///
/// @brief      Class for sensor HDC2080
/// @details    Temperature and Humidity Sensor
/// @see        http://www.ti.com/product/HDC2080
///
class Sensor_HDC2080
{
  public:
    ///
    /// @brief    Constructor
    /// @param    address I2C slave address
    /// @note     Valid addresses are 0x40..0x41, default=HDC2080_I2C_ADDRESS
    ///
    Sensor_HDC2080(uint8_t address = HDC2080_I2C_ADDRESS);

    ///
    /// @brief    Initialisation
    /// @param    configuration default=HDC2080_DEFAULT_SETTINGS
    /// @param    measure default=HDC2080_MEASURE_SETTINGS
    ///
    void begin(uint8_t configuration = HDC2080_DEFAULT_SETTINGS, uint8_t measure = HDC2080_MEASURE_SETTINGS);

    ///
    /// @brief    Acquisition
    ///
    void get();

    ///
    /// @brief    Measure
    /// @return   Temperature in °C
    ///
    double temperature();

    ///
    /// @brief    Measure
    /// @return   Relative humidity in %
    ///
    double humidity();


    void enableHeater(void);				// Enables the heating element
    void disableHeater(void);				// Disables the heating element
    void setLowTemp(float temp);			// Sets low threshold temperature (in c)
    void setHighTemp(float temp);			// Sets high threshold temperature (in c)
    void setHighHumidity(float humid);		// Sets high Humiditiy threshold
    void setLowHumidity(float humid);		// Sets low Humidity threshold
    float readLowHumidityThreshold(void);	// Returns contents of low humidity threshold register
    float readHighHumidityThreshold(void);	// Returns contents of high humidity threshold register
    float readLowTempThreshold(void);		// Returns contents of low temperature threshold register (in C)
    float readHighTempThreshold(void);		// Returns contents of high temperature threshold register (in C)
    void triggerMeasurement(void);			// Triggers a manual temperature/humidity reading
    void reset(void); 						// Triggers a software reset
    void enableInterrupt(void);				// Enables the interrupt/DRDY pin
    void disableInterrupt(void); 			// Disables the interrupt/DRDY pin (High Z)
    uint8_t readInterruptStatus(void); 		// Reads the status of the interrupt register
    void clearMaxTemp(void);				// Clears the Maximum temperature register
    void clearMaxHumidity(void);			// Clears the Maximum humidity register
    float readMaxTemp(void); 				// Reads the maximum temperature register
    float readMaxHumidity(void);			// Reads the maximum humidity register
    void enableThresholdInterrupt(void);	// Enables high and low temperature/humidity interrupts
    void disableThresholdInterrupt(void);	// Disables high and low temperature/humidity interrupts
    void enableDRDYInterrupt(void);			// Enables data ready interrupt
    void disableDRDYInterrupt(void);		// Disables data ready interrupt

    /*  Sets Temperature & Humidity Resolution, 3 options
        0 - 14 bit
        1 - 11 bit
        2 - 9 bit
        default - 14 bit							*/
    void setTempRes(int resolution);
    void setHumidRes(int resolution);

    /*  Sets measurement mode, 3 options
        0 - Temperature and Humidity
        1 - Temperature only
        2 - Humidity only
        default - Temperature & Humidity			*/
    void setMeasurementMode(int mode);

    /*  Sets reading rate, 8 options
        0 - Manual
        1 - reading every 2 minutes
        2 - reading every minute
        3 - reading every ten seconds
        4 - reading every 5 seconds
        5 - reading every second
        6 - reading at 2Hz
        7 - reading at 5Hz
        default - Manual		*/
    void setRate(int rate);

    /*  Sets Interrupt polarity, 2 options
        0 - Active Low
        1 - Active High
        default - Active Low			*/
    void setInterruptPolarity(int polarity);

    /*  Sets Interrupt mode, 2 options
        0 - Level sensitive
        1 - Comparator mode
        default - Level sensitive	*/
    void setInterruptMode(int polarity);

  private:
    int _address; 									// Address of sensor
    uint16_t _humidity;
    uint16_t _temperature;
    float rangeCheck(float value, float minValue, float maxValue);
};


#endif
