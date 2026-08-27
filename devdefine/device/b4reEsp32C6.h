/*/t indent 4*/
#pragma once

#define dd_Version			5
#define dd_DeviceEsp32c6
#define dd_BootInput		9
#define dd_DebugLight		5


#define dd_FormatB4RE
#define ddb4_p0				14
#define ddb4_p1				15
#define ddb4_p2				7
#define ddb4_p3				6
#define ddb4_p4				5
#define ddb4_p5				4


#define dd_Graphics
#include"display/ST7735S_160x80.h"
#define ddgfx_oIps
#define ddgfx_oInvert

#define ddgfx_pClock		ddb4_p0
#define ddgfx_pWrite		ddb4_p1
#define ddgfx_pReset		ddb4_p2
#define ddgfx_pCommand		ddb4_p3
#define ddgfx_pSelect		ddb4_p4
#define ddgfx_pBacklight	ddb4_p5


// #define RGBSupported
// #define RGBQuantity		1
// #define RGBData			8