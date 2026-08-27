#if defined(ARDUINO)
	#include"main.h"
	void Graphics::raminit(){
		#if defined(ddgfx_pBacklight)
			pinMode(ddgfx_pBacklight,OUTPUT);
		#endif
		#if defined(dd_Psram)
			#if defined(dd_FamilyEsp32)
				buffer=(uint16_t*)ps_malloc(width*height*sizeof(uint16_t));
			#endif
		#else
			buffer=(uint16_t*)malloc(width*height*sizeof(uint16_t));
		#endif
		if(!buffer)sys.lightCrash(1);
	}
	void Graphics::businit(){
		#if defined(dd_FamilyEsp82)
			#if defined(ddgfx_oIoHardSPI)
				bus=new Arduino_HWSPI(ddgfx_pCommand,ddgfx_pSelect);
			#endif
		#elif defined(dd_FamilyEsp32)
			#if defined(ddgfx_oIoHardSPI)
				bus=new Arduino_ESP32QSPI(
					ddgfx_pSelect,ddgfx_pClock,
					ddgfx_pData0,ddgfx_pData1,
					ddgfx_pData2,ddgfx_pData3
				);
			#endif
		#else
			#if defined(ddgfx_oIoHardSPI)
				bus=new Arduino_HWSPI(
					ddgfx_pCommand,ddgfx_pSelect,
					ddgfx_pClock,ddgfx_pWrite,ddgfx_pRead
				);
			#endif
		#endif
	}
	void Graphics::dspinit(){
		#if defined(ddgfx_oDspILI9341)
			gfxx=new Arduino_ILI9341(bus,ddgfx_pReset,0,ddgfx_oIps);
		#elif defined(ddgfx_oDspNV3041A)
			gfxx=new Arduino_NV3041A(bus,ddgfx_pReset,0,ddgfx_oIps);
		#elif defined(ddgfx_oDspST7735)
			#if defined(ddgfx_oDspVar1)
				gfxx=new Arduino_ST7735(bus,ddgfx_pReset,0,ddgfx_oIps,
					ddgfx_vWidth,ddgfx_vHeight,
					ddgfx_vShiftX,ddgfx_vShiftY
				);
			#elif defined(ddgfx_oDspVar2)
				gfxx=new Arduino_ST7735(bus,ddgfx_pReset,0,ddgfx_oIps,
					ddgfx_vWidth,ddgfx_vHeight,
					ddgfx_vShiftX,ddgfx_vShiftY,
					ddgfx_vShiftX,ddgfx_vShiftY,
					ddgfx_oSwap
				);
			#elif defined(ddgfx_oDspVar3)
				gfxx=new Arduino_ST7735(bus,
					ddgfx_pReset,0,ddgfx_oIps,
					ddgfx_vWidth,ddgfx_vHeight,
					ddgfx_vShiftX,ddgfx_vShiftY,
					ddgfx_vShiftX,ddgfx_vShiftY
				);
			#else
				gfxx=new Arduino_ST7735(bus,ddgfx_pReset,0);
			#endif
		#elif defined(ddgfx_oDspST7789)
			#if defined(ddgfx_oDspVar1)
				gfxx=new Arduino_ST7789(
					bus,ddgfx_pReset,0,ddgfx_oIps,
					ddgfx_vWidth,ddgfx_vHeight,
					ddgfx_vShiftX,ddgfx_vShiftY
				);
			#elif defined(ddgfx_oDspVar2)
				gfxx=new Arduino_ST7789(
					bus,ddgfx_pReset,0,ddgfx_oIps,
					ddgfx_vWidth,ddgfx_vHeight,
					ddgfx_vShiftX,ddgfx_vShiftY,
					ddgfx_vShiftX,ddgfx_vShiftY
				);
			#else
				gfxx=new Arduino_ST7789(bus,ddgfx_pReset,0,ddgfx_oIps);
			#endif
		#endif

		if(!gfxx)sys.lightCrash(3);
		if(!gfxx->begin(ddgfx_vSpeed))sys.lightCrash(2);
		#if defined(ddgfx_oInvert)
			gfxx->invertDisplay(true);
		#endif
		#if defined(ddgfx_vRotate)
			gfxx->setRotation(ddgfx_vRotate);
		#endif
	}
#endif