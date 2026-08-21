/*
Requirements:
#define GfxSelect		gpio
#define GfxCommand		gpio
#define GfxClock		gpio
#define GfxWrite		gpio
#define GfxReset		gpio
#define GfxBacklight	gpio
*/
#define GfxProtocolHardSPI
#define GfxModuleST7735
#define GfxModuleVariant1

#define GfxShiftX		24
#define GfxRotate		3
#define GfxHasIps		true
#define GfxColorInvert

#define GfxWidth		160
#define GfxHeight		80
#define GfxSpeed		80000000UL