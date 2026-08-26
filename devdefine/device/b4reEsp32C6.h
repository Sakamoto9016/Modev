/*/t indent 4*/
#pragma once

#define dd_Version			5
#define dd_DeviceEsp32c6
#define dd_BootInput		9
#define dd_DebugLight		5


#define FormatB4RE
#define B4reP0		14
#define B4reP1		15
#define B4reP2		7
#define B4reP3		6
#define B4reP4		5
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
// #define RGBData			8