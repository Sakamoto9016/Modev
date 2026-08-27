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

#define dd_Version			5
#define dd_DeviceEsp8266
#define dd_FamilyEsp82
#define dd_BootInput		0
#define dd_DebugLight		2


#define dd_FormatB4RE
#define ddb4_p0				4
#define ddb4_p1				5
#define ddb4_p2				12
#define ddb4_p3				13
#define ddb4_p4				15
#define ddb4_p5				14


#define dd_Graphics
#include"display/ST7735S_128x160.h"
#define ddgfx_pCommand		ddb4_p3
#define ddgfx_pSelect		ddb4_p4
#define ddgfx_pBacklight	ddb4_p5