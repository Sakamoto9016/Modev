#if defined(ARDUINO)
	#include"main.h"
	void Graphics::raminit(){
		#if defined(GfxBacklight)
			pinMode(GfxBacklight,OUTPUT);
		#endif
		#if defined(PsramSupported)
			#if defined(DevDefineEsp32s3)
				buffer=(uint16_t*)ps_malloc(width*height*sizeof(uint16_t));
			#endif
		#else
			buffer=(uint16_t*)malloc(width*height*sizeof(uint16_t));
		#endif
		if(!buffer)sys.lightCrash(1);
	}
	void Graphics::businit(){
		#ifdef GfxProtocolHardSPI
			bus=new Arduino_HWSPI(GfxCommand,GfxSelect,GfxClock,GfxWrite,GfxRead);
		#elifdef GfxProtocolE32QSPI
			bus=new Arduino_ESP32QSPI(GfxSelect,GfxClock,GfxData0,GfxData1,GfxData2,GfxData3);
		#endif
	}
	void Graphics::dspinit(){
		#ifdef GfxModuleILI9341
			gfxx=new Arduino_ILI9341(bus,GfxReset,0,GfxHasIps);
		#elifdef GfxModuleNV3041A
			gfxx=new Arduino_NV3041A(bus,GfxReset,0,GfxHasIps);
		#elifdef GfxModuleST7735
			#if defined(GfxModuleVariant1)
				gfxx=new Arduino_ST7735(bus,GfxReset,0,GfxHasIps,
					GfxWidth,GfxHeight,
					GfxShiftX,GfxShiftY
				);
			#elif defined(GfxModuleVariant2)
				gfxx=new Arduino_ST7735(bus,GfxReset,0,GfxHasIps,
					GfxWidth,GfxHeight,
					GfxShiftX,GfxShiftY,
					GfxShiftX,GfxShiftY,
					GfxColorSwap
				);
			#elif defined(GfxModuleVariant3)
				gfxx=new Arduino_ST7735(bus,GfxReset,0,GfxHasIps,
					GfxWidth,GfxHeight,
					GfxShiftX,GfxShiftY,
					GfxShiftX,GfxShiftY
				);
			#else
				gfxx=new Arduino_ST7735(bus,GfxReset,0);
			#endif
		#elifdef GfxModuleST7789
			#if defined(GfxModuleVariant1)
				gfxx=new Arduino_ST7789(
					bus,GfxReset,0,GfxHasIps,
					GfxWidth,GfxHeight,
					GfxShiftX,GfxShiftY
				);
			#elif defined(GfxModuleVariant2)
				gfxx=new Arduino_ST7789(
					bus,GfxReset,0,GfxHasIps,
					GfxWidth,GfxHeight,
					GfxShiftX,GfxShiftY,
					GfxShiftX,GfxShiftY
				);
			#else
				gfxx=new Arduino_ST7789(bus,GfxReset,0,GfxHasIps);
			#endif
		#endif

		if(!gfxx)sys.lightCrash(3);
		if(!gfxx->begin(GfxSpeed))sys.lightCrash(2);
		#if defined(GfxColorInvert)
			gfxx->invertDisplay(true);
		#endif
		#if defined(GfxRotate)
			gfxx->setRotation(GfxRotate);
		#endif
	}
#endif