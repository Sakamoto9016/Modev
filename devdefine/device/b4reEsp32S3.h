/*/t indent 4*/
#pragma once

#define DevDefineVersion	2
#define DevDefineEsp32s3
#define SysBootInput	0
#define SysDebugLight	4


#define FormatB4RE
#define B4reP0		9
#define B4reP1		8
#define B4reP2		5
#define B4reP3		6
#define B4reP4		7
#define B4reP5		4


#define GfxSupported
#include"display/ST7735S_160x80.h"
#define GfxHasIps		true
#define GfxColorInvert

#define GfxClock		B4reP0
#define GfxWrite		B4reP1
#define GfxReset		B4reP2
#define GfxCommand		B4reP3
#define GfxSelect		B4reP4
#define GfxBacklight	B4reP5


// #define RGBSupported
// #define RGBQuantity		1
// #define RGBData			48