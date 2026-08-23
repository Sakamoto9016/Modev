/*/t indent 4*/
#pragma once

#define DevDefineVersion	2
#define DevDefineEsp32s3
#define SysBootInput	0
#define SysDebugLight	1


#define PsramSupported


#define GfxSupported
#define GfxMethodE32QSPI
#define GfxModuleNV3041A

#define GfxHasIps		true

#define GfxSelect		45
#define GfxClock		47
#define GfxData0		21
#define GfxData1		48
#define GfxData2		40
#define GfxData3		39
#define GfxBacklight	1

#define GfxWidth		480
#define GfxHeight		272
#define GfxSpeed		40000000UL


// #define SdSupported
// #define SdMethodSPI
// #define SdClock			12
// #define SdCommand		11
// #define SdData0			13
// #define SdSelect		10

// #define I2cSupported
// #define I2cData			8
// #define I2cClock		4
// #define I2cFrequency	400000UL

// #define TouchSupported
// #define TouchModuleGT911
// #define TouchData		I2cData
// #define TouchClock		I2cClock
// #define TouchReset		38
// #define TouchInterrupt	3

// #define I2sSupported
// #define I2sMethodRaw
// #define I2sAmplifier 	0.5
// #define I2sBitClock		42
// #define I2sLRClock		2
// #define I2sMasterClock	-1
// #define I2sInput		-1
// #define I2sOutput		41