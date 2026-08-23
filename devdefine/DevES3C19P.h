/*/t indent 4*/
#pragma once

#define DevDefineVersion	2
#define DevDefineEsp32s3
#define SysBootInput	0
#define SysDebugLight	14


#define PsramSupported


#define GfxSupported
#define GfxProtocolHardSPI
#define GfxModuleST7789
#define GfxModuleVariant2

#define GfxBacklightSwap
#define GfxColorInvert
#define GfxShiftX		35

#define GfxSelect		12
#define GfxCommand		11
#define GfxClock		10
#define GfxWrite		13
#define GfxReset		9
#define GfxBacklight	14

#define GfxWidth		170
#define GfxHeight		320
#define GfxSpeed		80000000UL


// #define I2cSupported
// #define I2cData			15
// #define I2cClock		7
// #define I2cFrequency	400000UL


// #define TouchSupported
// #define TouchModuleCST816
// #define TouchProtocolHardI2C
// #define TouchAddress	0x15
// #define TouchData		I2cData
// #define TouchClock		I2cClock
// #define TouchReset		16
// #define TouchInterrupt	17


// #define BatSupported
// #define BatVoltage		4