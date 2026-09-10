#include"main.h"
#ifdef ARDUINO
	Arduino_DataBus*bus=nullptr;
	Arduino_TFT*gfxx=nullptr;
#else
	SDL_Window*window=nullptr;
	SDL_Renderer*renderer=nullptr;
	SDL_Texture*texture=nullptr;
#endif

void Graphics::bseinit(){
	#ifdef ARDUINO
		#if defined(ddgfx_pBacklight)
			pinMode(ddgfx_pBacklight,OUTPUT);
		#endif
	#endif
	sys.log("Graphics: Initalized backlight.",2);
}
void Graphics::raminit(){
	#ifdef ARDUINO
		#ifdef dd_Psram
			#if defined(dd_FamilyEsp32)
				buffer=(uint16_t*)ps_malloc(width*height*sizeof(uint16_t));
			#endif
		#else
			buffer=(uint16_t*)malloc(width*height*sizeof(uint16_t));
		#endif
		if(!buffer)sys.lightCrash(1);
	#else
		buffer=new uint16_t[size];
		if(!buffer)sys.lightCrash(1);
	#endif
	sys.log("Graphics: Initalized buffer.",2);
}
void Graphics::businit(){
	#ifdef ARDUINO
		#if defined(dd_FamilyEsp82)
			#if defined(ddgfx_oIoHardSPI)
				bus=new Arduino_HWSPI(ddgfx_pCommand,ddgfx_pSelect);
			#endif
		#elif defined(dd_FamilyEsp32)
			#if defined(ddgfx_oIoHardQSPI)
				bus=new Arduino_ESP32QSPI(
					ddgfx_pSelect,ddgfx_pClock,
					ddgfx_pData0,ddgfx_pData1,
					ddgfx_pData2,ddgfx_pData3
				);
			#elif defined(ddgfx_oIoHardSPI)
				bus=new Arduino_HWSPI(
					ddgfx_pCommand,ddgfx_pSelect,
					ddgfx_pClock,ddgfx_pWrite,ddgfx_pRead
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
	#else
		SDL_Init(SDL_INIT_VIDEO);
	#endif
	sys.log("Graphics: Initalized bus.",2);
}
void Graphics::dspinit(){
	#ifdef ARDUINO
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
	#else
		char buf[256];
		sprintf(buf,"Modev %s(v%s) %s Emulation",m_VersionName,m_VersionString,m_UnderConstruction?"Prototype":"");
		window=SDL_CreateWindow(buf,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width*ddgfx_vScale,height*ddgfx_vScale,SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
		renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
		texture=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGB565,SDL_TEXTUREACCESS_STREAMING,width,height);
	#endif
	sys.log("Graphics: Initalized display.",2);
}