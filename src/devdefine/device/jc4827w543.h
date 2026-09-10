/*/t indent 4*/
#pragma once

#define dd_Version			5
#define dd_DeviceEsp32s3
#define dd_FamilyEsp32
#define dd_BootInput		0
#define dd_DebugLight		1


#define dd_Psram


#define dd_Graphics
#define ddgfx_oIoHardQSPI
#define ddgfx_oDspNV3041A
#define ddgfx_oIps

#define ddgfx_pSelect		45
#define ddgfx_pClock		47
#define ddgfx_pData0		21
#define ddgfx_pData1		48
#define ddgfx_pData2		40
#define ddgfx_pData3		39
#define ddgfx_pBacklight	1

#define ddgfx_vWidth		480
#define ddgfx_vHeight		272
#define ddgfx_vSpeed		40000000UL


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