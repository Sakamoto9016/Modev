/*/t indent 4*/
#pragma once

#define DevDefineVersion	2
#define DevDefineEsp32c3
#define SysBootInput	9
#define SysDebugLight	1


#define FormatB4RE
#define B4reP0		3
#define B4reP1		2
#define B4reP2		20
#define B4reP3		21
#define B4reP4		10
#define B4reP5		6


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
// #define GfxModuleST7789
// #define GfxModuleVariant1

// #define GfxHasIps		true

// #define GfxCommand		0
// #define GfxClock		6
// #define GfxWrite		7
// #define GfxReset		5
// #define GfxBacklight	1

// #define GfxWidth		240
// #define GfxHeight		240
// #define GfxSpeed		80000000UL


// #define RGBSupported
// #define RGBQuantity		1
// #define RGBData			8