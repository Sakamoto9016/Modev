/*/t indent 4*/
#pragma once

#define DevDefineVersion	2
#define DevDefineEsp32
#define SysBootInput	0
#define SysDebugLight	45


#define PsramSupported


#define GfxSupported
#define	GfxProtocolHardSPI
#define GfxModuleILI9341

#define GfxColorInvert

#define GfxSelect		10
#define GfxCommand		46
#define GfxClock		12
#define GfxWrite		11
#define GfxRead			13
#define GfxBacklight	45

#define GfxWidth		240
#define GfxHeight		320
#define GfxSpeed		60000000UL


#define I2cSupported
#define I2cData			16
#define I2cClock		15
#define I2cFrequency	400000UL

#define TouchSupported
#define TouchModuleFT6336G
#define TouchAddress	0x38
#define TouchData		I2cData
#define TouchClock		I2cClock
#define TouchReset		18
#define TouchInterrupt	17


// #define BatSupported
// #define BatVoltage		9

// #define SdSupported
// #define SdMethodNative
// #define SdClock			38
// #define SdCommand		40
// #define SdData0			39
// #define SdData1			41
// #define SdData2			48
// #define SdData3			47

// #define I2sSupported
// #define I2sAmplifier	1
// #define I2sBitClock		5
// #define I2sLRClock		7
// #define I2sMasterClock	4
// #define I2sInput		8
// #define I2sOutput		6

// #define RGBSupported
// #define RGBQuantity		1
// #define RGBData			42