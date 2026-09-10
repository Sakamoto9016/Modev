/*/t indent 4*/
#pragma once

#define dd_Version			5
#define dd_DeviceEsp32s3
#define dd_FamilyEsp32
#define dd_BootInput		0
#define dd_DebugLight		45


#define dd_Psram


#define dd_Graphics
#include"../display/ILI9341_240x320.h"
#define ddgfx_oIps

#define ddgfx_pSelect		10
#define ddgfx_pCommand		46
#define ddgfx_pClock		12
#define ddgfx_pWrite		11
#define ddgfx_pReset		13
#define ddgfx_pBacklight	45


#define dd_I2c
#define ddi2c_pData			16
#define ddi2c_pClock		15
#define ddi2c_vFrequency	400000UL


#define dd_TouchPanel	//tpi means touch panel input
#define ddtpi_oTpiFT6336G
#define ddtpi_vAddress		0x38
#define ddtpi_pData			ddi2c_pData
#define ddtpi_pClock		ddi2c_pClock
#define ddtpi_pReset		18
#define ddtpi_pInterrupt	7


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