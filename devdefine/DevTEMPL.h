/*/t indent 4*/
#pragma once

#define DevDefineVersion	1
/*Solid foundation to keep track... I don't know.*/
//#define DevDefineEsp32
//#define DevDefinePico
/*Uncomment your device processor.*/

#define SysBootInput	-1
/*Which pin is tied to BOOT button?*/
#define SysDebugLight	-1
/*Which pin is tied to the builtin LED? If not, use the backight pin instead.*/

//#define PsramSupported
/*Uncomment if your device has a PSRAM.*/

//#define BatSupported
/*Uncomment if your device has a battery.*/
//#define BatVoltage	?
/*Uncomment and give a gpio number if your device has a battery level reader.*/

#define SdSupported
#define SdMethodNative
#define SdClock			-1
#define SdCommand		40
#define SdData0			39
#define SdData1			41
#define SdData2			48
#define SdData3			47

#define GfxSupported
#define	GfxProtocolSPI
#define GfxModuleILI9341
#define GfxSelect		10
#define GfxCommand		46
#define GfxClock		12
#define GfxWrite		11
#define GfxRead			13
#define GfxInverted
#define GfxBacklight	45
#define GfxWidth		480
#define GfxHeight		272
#define GfxSpeed		80000000UL

//#define I2cSupported
//#define I2cData		?
//#define I2cClock		?
//#define I2cFrequency	400000UL
/*Uncomment and give gpio numbers if your device has an I2C protocol.*/



//#define RGBSupported
//#define RGBPin		?
/*Uncomment and give a gpio number if your device has a RGB LED.*/