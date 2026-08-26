/*
Requirements:
#define GfxSelect		gpio
#define GfxCommand		gpio
#define GfxClock		gpio
#define GfxWrite		gpio
#define GfxReset		gpio
#define GfxBacklight	gpio
*/
#define ddgfx_Version		1
#define	ddgfx_oIoHardSPI
#define ddgfx_oDspST7735
#define ddgfx_oDspVar1

#define ddgfx_vShiftX		24
#define ddgfx_vRotate		3

#define ddgfx_vWidth		160
#define ddgfx_vHeight		80
#define ddgfx_vSpeed		80000000UL