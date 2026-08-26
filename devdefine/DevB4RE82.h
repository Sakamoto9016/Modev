/*/t indent 4*/
/*

ESP8266        ST7735S
────────       ───────
GPIO14  ────── SCL/SCK
GPIO13  ────── SDA/MOSI
GPIO12  ────── RES
GPIO5   ────── DC
GPIO15  ────── CS
GPIO4   ────── BL
GND     ────── GND
3V3     ────── VCC

Ugh I'm still figuring this out
*/

#pragma once

#define dd_Version	2
#define dd_DeviceEsp8266
#define SysBootInput	0
#define SysDebugLight	2


#define FormatB4RE
#define B4reP0		4
#define B4reP1		5
#define B4reP2		12
#define B4reP3		13
#define B4reP4		15
#define B4reP5		14


#define GfxSupported
#include"display/ST7735S_128x160.h"

#define GfxCommand		B4reP3
#define GfxSelect		B4reP4
#define GfxBacklight	B4reP5