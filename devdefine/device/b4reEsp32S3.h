/*/t indent 4*/
#pragma once

#define dd_Version			5
#define dd_DeviceEsp32s3
#define dd_FamilyEsp32
#define dd_BootInput		0
#define dd_DebugLight		4


#define dd_FormatB4RE
#define ddb4_p0				9
#define ddb4_p1				8
#define ddb4_p2				5
#define ddb4_p3				6
#define ddb4_p4				7
#define ddb4_p5				4


#define dd_Graphics
#include"../display/ST7735S_160x80.h"
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
// #define RGBData			48