///
/// @file		Wire_Utilities.h
/// @brief		Library header
/// @details	Utilities for 8- and 16-bit read and write operations
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
///

#ifndef Wire_Utilities_RELEASE
#define Wire_Utilities_RELEASE 102

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
#error Platform not defined
#endif // end IDE


#include "Wire.h"


// Library header
///
/// @brief	Write 1 byte
/// @param	device I2C address, 7-bit coded
/// @param	command command or register, 8-bit
/// @param	data8 value, 8-bit
///
void writeRegister8(uint8_t device, uint8_t command, uint8_t data8);

///
/// @brief	Write 2 bytes
/// @param	device I2C address, 7-bit coded
/// @param	command command or register, 8-bit
/// @param	data16 value, 16-bit
/// @param	mode default=MSBFIRST, other option=LSBFIRST
/// @note   * with MSBFIRST, data16[15..8] written to command, data16[7..Ø] to command + 1
/// @note   * with LSBFIRST, data16[7..Ø] written to command, data16[15..8] to command + 1
///
void writeRegister16(uint8_t device, uint8_t command, uint16_t data16, uint8_t mode = MSBFIRST);

///
/// @brief	Read 1 byte
/// @param	device I2C address, 7-bit coded
/// @param	command command, 8-bit
/// @return	data8 value, 8-bit
///
uint8_t readRegister8(uint8_t device, uint8_t command);

///
/// @brief	Read 2 bytes
/// @param	device I2C address, 7-bit coded
/// @param	command command or register, 8-bit
/// @param	mode default=MSBFIRST, other option=LSBFIRST
/// @return	data16 value, 16-bit
/// @note   * with MSBFIRST, data16[15..8] read from command, data16[7..Ø] from command + 1
/// @note   * with LSBFIRST, data16[7..Ø] read from command, data16[15..8] from command + 1
///
uint16_t readRegister16(uint8_t device, uint8_t command, uint8_t mode = MSBFIRST);

///
/// @brief    Delay without yield
/// @param    ms period to wait for, ms
///
void delayBusy(uint32_t ms);

#endif
