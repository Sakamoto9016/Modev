/*/t indent 4*/
#pragma once

#define dd_Version			5
#define dd_DeviceEsp32s3
#define dd_FamilyEsp32
#define dd_BootInput		0
#define dd_DebugLight		14


#define dd_Psram


#define dd_Graphics
#include"../display/ST7789_170x320.h"
#define ddgfx_oLightSwap
#define ddgfx_oInvert

#define ddgfx_pSelect		12
#define ddgfx_pCommand		11
#define ddgfx_pClock		10
#define ddgfx_pWrite		13
#define ddgfx_pReset		9
#define ddgfx_pBacklight	14


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