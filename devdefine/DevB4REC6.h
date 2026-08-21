/*/t indent 4*/
#pragma once

#define DevDefineVersion	2
#define DevDefineEsp32
#define SysBootInput	9
#define SysDebugLight	5


#define FormatB4RE
#define B4reP0		14
#define B4reP1		15
#define B4reP2		7
#define B4reP3		6
#define B4reP4		5
#define B4reP5		4


#define GfxSupported
#include"display/ST7735S_160x80.h"
#define GfxSelect		B4reP4
#define GfxCommand		B4reP3
#define GfxClock		B4reP0
#define GfxWrite		B4reP1
#define GfxReset		B4reP2
#define GfxBacklight	B4reP5


// #define GfxSupported
// #define GfxProtocolHardSPI
// #define GfxModuleST7735
// #define GfxModuleVariant2

// #define GfxSelect		4
// #define GfxCommand		6
// #define GfxClock		14
// #define GfxWrite		18
// #define GfxReset		7
// #define GfxBacklight	5

// #define GfxWidth		128
// #define GfxHeight		160
// #define GfxSpeed		80000000UL


// #define RGBSupported
// #define RGBQuantity		1
// #define RGBData			8