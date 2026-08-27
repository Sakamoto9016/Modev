/*
Psst...!
Modev has proven that these microcontroller below works:
	Espressif
		Esp32
			Esp32s3
			Esp32c3
			Esp32c6
*/
#include"mcfg.h"
#include"devdefine/main.h"
#pragma once
	#include<cstdint>
	#include<cstdio>
	#include<cmath>
	#include<string>
	#include<random>
	#include<cstdlib>
	#include<algorithm>
	#include<cstddef>
extern char boot[m_ScriptSize];
extern bool err;
extern char erno[1024];
#if defined(ARDUINO)
	#include<Arduino_GFX_Library.h>
	#include<Arduino.h>
	#include<Wire.h>

	extern Arduino_DataBus*bus;
	extern Arduino_TFT*gfxx;
#else
	#include<SDL2/SDL.h>
	#include<iostream>
	#include<thread>
	#include<atomic>

	#define PROGMEM
	extern SDL_Window*window;
	extern SDL_Renderer*renderer;
	extern SDL_Texture*texture;
	uint32_t millis();
	void delay(uint32_t ms);
	long random(long max);
	long random(long min,long max);
	#if defined(STUDIO)
		void runtime();
		extern uint width,height,scale;
		extern uint32_t size;
		extern uint16_t*buffer;
	#endif
#endif

#if !defined(STUDIO)
void setup();
void loop();
#endif

struct font{
	const char*name;
	uint8_t bufw,bufh,width,height,count;
	const uint8_t*repl,*data;
	const int8_t offsetX,offsetY;
};

#include"lua.hpp"

class System{
	public:
		time_t
			bootTime=0,
			elapTime=0,
			unixTime=0;
		bool
			logNL=true,		/*Newline*/
			logLC=false;	/*Line count*/
		void log(const char* text="",int8_t type=-1);
		void lightCrash(uint8_t err);
		bool bootInput();
		#if !defined(STUDIO)
		void begin();
		#endif
};
extern System sys;

class Graphics{
	public:
		uint16_t
			width=ddgfx_vWidth,
			height=ddgfx_vHeight,
			*buffer;
		uint32_t
			size=(uint32_t)width*height;

		void clip(uint16_t x,uint16_t y,uint16_t w,uint16_t h);
		void clipView(uint16_t x,uint16_t y,uint16_t w,uint16_t h);	
		void clip();
		void clipView();

		void begin();
		void flush();
		void antiBurn();
		uint32_t getFps();
		uint16_t getRgb565(uint8_t r=31,uint8_t g=63,uint8_t b=31);
		uint16_t getRgb111(uint8_t r=1,uint8_t g=1,uint8_t b=1);
		uint16_t getRgb222(uint8_t r=3,uint8_t g=3,uint8_t b=3);
		uint16_t getBlend(uint16_t c1,uint16_t c2,uint8_t value=127);
		void setBrightness(uint8_t v=255);
		uint8_t getBrightness();

		void clear(uint16_t c=0);
		void clearQuick(uint16_t c=0);
		void clearDither(uint8_t density=15,uint16_t c=0);
		void clearGrad(uint16_t c1=0,uint16_t c2=0xFFFF,uint8_t angle=63);
		void clearGradV(uint16_t c1=0,uint16_t c2=0xFFFF);
		void clearGradH(uint16_t c1=0,uint16_t c2=0xFFFF);

		void setPixel(int32_t x,int32_t y,uint16_t c=0,bool safe=true);
		uint16_t getPixel(int32_t x,int32_t y,bool safe=true);

		void line(int32_t x1,int32_t y1,int32_t x2,int32_t y2,uint16_t c=0);
		void lineV(int32_t x,int32_t y,uint16_t length,uint16_t c=0);
		void lineH(int32_t x,int32_t y,uint16_t length,uint16_t c=0);
		void lineDash(int32_t x1,int32_t y1,int32_t x2,int32_t y2,uint16_t c=0,uint8_t phase=0,uint8_t segment=10);
		void lineEdge(int32_t x,int32_t y,uint16_t length,uint16_t width,uint16_t c=0,uint8_t direction=0);

		void rectFrame(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c=0);
		void rectFill(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c=0);
		void rectPop(int32_t x,int32_t y,uint16_t w,uint16_t h,uint16_t c=0,uint16_t lightcolor=0xFFFF,uint16_t darkcolor=0x3333,uint16_t border=2,bool invert=false,bool flat=false);
		void rectDither(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c=0,uint8_t density=15);
		void rectProgress(int32_t x,int32_t y,uint16_t w,uint16_t h,uint16_t c=0,uint8_t value=127);
		void rectLoad(int32_t x,int32_t y,uint16_t w,uint16_t h,uint16_t c=0,uint8_t value=4);
		void rectGrad(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c1=0,uint16_t c2=0xFFFF,uint8_t angle=63);
		void rectGradV(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c1=0,uint16_t c2=0xFFFF);
		void rectGradH(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c1=0,uint16_t c2=0xFFFF);

		void circFrame(int32_t x,int32_t y,uint16_t radius=10,uint16_t c=0);
		void circFill(int32_t x,int32_t y,uint16_t radius=10,uint16_t c=0);

		void elipFrame(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c=0);
		void elipFill(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c=0);

		void triFrame(int32_t x1,int32_t y1,int32_t x2,int32_t y2,int32_t x3,int32_t y3,uint16_t c=0);
		void triFill(int32_t x1,int32_t y1,int32_t x2,int32_t y2,int32_t x3,int32_t y3,uint16_t c=0);

		void setFont(const char* fontname);
		const char*getFont();

		uint8_t getFontWidth();
		uint8_t getFontHeight();
		uint16_t getTextWidth(const char* text);
		void glyph(char ch,int32_t x,int32_t y,uint16_t c=0);
		void text(const char* text,int32_t x,int32_t y,uint16_t c=0);

		void setImageTone(uint16_t c=0xFFFF);
		void setImageChannels(uint8_t r,uint8_t g,uint8_t b,uint8_t a=0);
		void setImageChannels(uint8_t g,uint8_t a=0);
		void setImageCropPosition(uint16_t x,uint16_t y);
		void setImageCropSize(uint16_t w,uint16_t h);
		void setImageData(const uint8_t* data,uint16_t w,uint16_t h);
		uint16_t getImageWidth();
		uint16_t getImageHeight();
		void renderImage(int32_t x,int32_t y,uint8_t rotate=0,float scale=1);

		class Font{
			public:
				uint8_t
					count,
					index;
		};
		Font fnt;
	private:
		#if defined(ARDUINO)
			void raminit();
			void businit();
			void dspinit();
		#endif
		bool
			clipEn=false,clipVEn=false;
		uint8_t
			brightValue=255;
		uint16_t
			clipX=0,clipY=0,clipW=width,clipH=height,
			clipVX=0,clipVY=0,clipVW=width,clipVH=height;

		uint16_t
			imgGr=0xFFFF,
			imgSX=0,imgSY=0,
			imgCW=0,imgCH=0,
			imgW=0,imgH=0;
		uint8_t
			imgRb=5,imgGb=6,imgBb=5,imgAb=8;
		const uint8_t*imgD=nullptr;
		bool imgSi=false;
		const uint8_t bayer4x4[4][4]={
			{0	,8	,2	,10	},
			{12	,4	,14	,6	},
			{3	,11	,1	,9	},
			{15	,7	,13	,5	}
		};
		inline void swap16(int32_t&a,int32_t&b){int32_t t=a;a=b;b=t;}
		static bool fontPixel(const font&f,const uint8_t*glyph,int x,int y){
			if(x>=f.width||y>=f.height) return false;
			int bytesPerRow=f.bufw/8,byteIndex=y*bytesPerRow+(x/8),bitIndex=7-(x%8);
			return(glyph[byteIndex]>>bitIndex)&1;
		}
		static int resolveGlyphIndex(const font&f,unsigned char ch){
			int index=ch-32;
			if(index<0||index>=f.count)index=-1;
			return index;
		}
		static uint32_t imgIRB(const uint8_t* data,uint32_t& bitPos,uint8_t bits){
			if(bits==0)return 0;
			uint32_t value=0;
			for(uint8_t i=0;i<bits;i++){
				uint32_t bytePos=bitPos>>3;
				uint8_t
					bitInByte=7-(bitPos&7),
					bit=(data[bytePos]>>bitInByte)&1;
				value=(value<<1)|bit;
				bitPos++;
			}
			return value;
		}
		static uint8_t imgIE(uint32_t value,uint8_t bits){
			if(bits==0)return 0;
			if(bits>=8)return(uint8_t)(value >>(bits-8));
			uint32_t maxValue=(1UL<<bits)-1;
			return(uint8_t)((value*255UL+maxValue/2)/maxValue);
		}
};
extern Graphics gfx;

class Utility{
	public:
		char*spacer(char*out,const char*text,uint8_t size=4,bool left=false);
};
extern Utility utl;

class Input{
	public:
		uint16_t
			touchX=0,
			touchY=0;
		bool
			touchActive=false,
			touchEnable=true;
		bool checkTouch();
		void begin();
		void tick();
};
extern Input inp;

class Sound{
	public:
		void begin();
};
extern Sound sfx;

class Moon{
	public:
		static lua_State*L;
		bool begin(char*err);
		bool tick(char*err);
	private:
		class func{
			public:
				static int a0		(lua_State*L){lua_pushboolean(L,sys.bootInput());return 1;}
				static int aa0		(lua_State*L){lua_pushinteger(L,m_ScriptSize);return 1;}
				static int aa1		(lua_State*L){lua_pushboolean(L,m_UnderConstruction);return 1;}
				static int aa2		(lua_State*L){lua_pushboolean(L,m_Emulation);return 1;}
				static int aaa0		(lua_State*L){lua_pushinteger(L,m_VersionValue);return 1;}
				static int aaa1		(lua_State*L){lua_pushstring (L,m_VersionString);return 1;}
				static int aaa2		(lua_State*L){lua_pushstring (L,m_VersionName);return 1;}
				static int aab0		(lua_State*L){lua_pushinteger(L,m_DistVerValue);return 1;}
				static int aab1		(lua_State*L){lua_pushstring (L,m_DistVerString);return 1;}
				static int aab2		(lua_State*L){lua_pushstring (L,m_DistVerName);return 1;}
				static int aab3		(lua_State*L){lua_pushstring (L,m_DistroID);return 1;}
				static int ab0		(lua_State*L){lua_pushinteger(L,sys.elapTime);return 1;}
				static int ab1		(lua_State*L){lua_pushinteger(L,sys.bootTime);return 1;}
				static int ab2		(lua_State*L){lua_pushinteger(L,sys.unixTime);return 1;}
				static int ac0		(lua_State*L){
					int level=luaL_optnumber(L,2,-1);
					size_t len;
					const char*str=luaL_tolstring(L,1,&len);
					if(str==nullptr){
						lua_pop(L,1);
						return 0;
					}
					sys.log(str,level);
					lua_pop(L,1);
					return 0;
				}
				static int aca0(lua_State*L){lua_pushboolean(L,sys.logNL);return 1;}
				static int aca1(lua_State*L){luaL_checktype(L,1,LUA_TBOOLEAN);sys.logNL=lua_toboolean(L,1);return 0;}
				static int acb0(lua_State*L){lua_pushboolean(L,sys.logLC);return 1;}
				static int acb1(lua_State*L){luaL_checktype(L,1,LUA_TBOOLEAN);sys.logLC=lua_toboolean(L,1);return 0;}

				static int b0(lua_State*L){gfx.flush();return 0;}
				static int b1(lua_State*L){gfx.antiBurn();return 0;}
				static int b2(lua_State*L){lua_pushinteger(L,gfx.getFps());return 1;}
				static int b3(lua_State*L){
					lua_pushinteger(L,
						gfx.getBlend(
							luaL_optnumber(L,1,0),
							luaL_optnumber(L,2,0xFFFF),
							luaL_optnumber(L,3,127)
						)
					);
					return 1;
				}
				static int ba0(lua_State*L){lua_pushinteger(L,gfx.width);return 1;}
				static int ba1(lua_State*L){lua_pushinteger(L,gfx.height);return 1;}
				static int ba2(lua_State*L){lua_pushinteger(L,gfx.size);return 1;}
				static int bba0(lua_State*L){
					gfx.clip(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4)
					);
					return 0;
				}
				static int bba1(lua_State*L){gfx.clip();return 0;}
				static int bbb0(lua_State*L){
					gfx.clipView(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4)
					);
					return 0;
				}
				static int bbb1(lua_State*L){gfx.clipView();return 0;}
				static int bc0(lua_State*L){lua_pushinteger(L,gfx.getBrightness());return 1;}
				static int bc1(lua_State*L){gfx.setBrightness(luaL_optnumber(L,1,255));return 0;}
				static int bd0(lua_State*L){
					lua_pushinteger(L,gfx.getRgb565(
						luaL_optnumber(L,1,31),
						luaL_optnumber(L,2,63),
						luaL_optnumber(L,3,31)
						));
					return 1;
				}
				static int bd1(lua_State*L){
					lua_pushinteger(L,gfx.getRgb111(
						luaL_optnumber(L,1,1),
						luaL_optnumber(L,2,1),
						luaL_optnumber(L,3,1)
						));
					return 1;
				}
				static int bd2(lua_State*L){
					lua_pushinteger(L,gfx.getRgb222(
						luaL_optnumber(L,1,3),
						luaL_optnumber(L,2,3),
						luaL_optnumber(L,3,3)
						));
					return 1;
				}
				static int be0(lua_State*L){lua_pushinteger(L,gfx.getPixel(luaL_checknumber(L,1),luaL_checknumber(L,2)));return 1;}
				static int be1(lua_State*L){gfx.setPixel(luaL_checknumber(L,1),luaL_checknumber(L,2),luaL_optnumber(L,3,0));return 0;}
				static int bf0(lua_State*L){gfx.clear(luaL_optnumber(L,1,0));return 0;}
				static int bf1(lua_State*L){gfx.clearQuick(luaL_optnumber(L,1,0));return 0;}
				static int bf2(lua_State*L){gfx.clearDither(luaL_optnumber(L,1,15),luaL_optnumber(L,2,255));return 0;}
				static int bfa0(lua_State*L){gfx.clearGrad(luaL_optnumber(L,1,0),luaL_optnumber(L,2,0xFFFF),luaL_optnumber(L,3,31));return 0;}
				static int bfa1(lua_State*L){gfx.clearGradV(luaL_optnumber(L,1,0),luaL_optnumber(L,2,0xFFFF));return 0;}
				static int bfa2(lua_State*L){gfx.clearGradV(luaL_optnumber(L,1,0),luaL_optnumber(L,2,0xFFFF));return 0;}
				static int bg0(lua_State*L){
					gfx.line(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4),
						luaL_optnumber(L,5,0)
					);
					return 0;
				}
				static int bg1(lua_State*L){
					gfx.lineV(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_optnumber(L,4,0)
					);
					return 0;
				}
				static int bg2(lua_State*L){
					gfx.lineH(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_optnumber(L,4,0)
					);
					return 0;
				}
				static int bg3(lua_State*L){
					gfx.lineDash(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4),
						luaL_optnumber(L,5,0),
						luaL_optnumber(L,6,0),
						luaL_optnumber(L,7,10)
					);
					return 0;
				}
				static int bg4(lua_State*L){
					gfx.lineEdge(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4),
						luaL_optnumber(L,5,0),
						luaL_optnumber(L,6,0)
					);
					return 0;
				}
				static int bh0(lua_State*L){
					gfx.rectFrame(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4),
						luaL_optnumber(L,5,0)
					);
					return 0;
				}
				static int bh1(lua_State*L){
					gfx.rectFill(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4),
						luaL_optnumber(L,5,0)
					);
					return 0;
				}
				static int bh2(lua_State*L){
					gfx.rectDither(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4),
						luaL_optnumber(L,5,0),
						luaL_optnumber(L,6,15)
					);
					return 0;
				}
				static int bha0(lua_State*L){
					luaL_checktype(L,9,LUA_TBOOLEAN);
					luaL_checktype(L,10,LUA_TBOOLEAN);
					gfx.rectPop(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4),
						luaL_optnumber(L,5,0),
						luaL_optnumber(L,6,0xFFFF),
						luaL_optnumber(L,7,0x3333),
						luaL_optnumber(L,8,2),
						lua_toboolean(L,9),
						lua_toboolean(L,10)
					);
					return 0;
				}
				static int bha1(lua_State*L){
					gfx.rectProgress(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4),
						luaL_optnumber(L,5,0),
						luaL_optnumber(L,6,127)
					);
					return 0;
				}
				static int bha2(lua_State*L){
					gfx.rectLoad(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4),
						luaL_optnumber(L,5,0),
						luaL_optnumber(L,6,4)
					);
					return 0;
				}
				static int bhb0(lua_State*L){
					gfx.rectGrad(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4),
						luaL_optnumber(L,5,0),
						luaL_optnumber(L,6,0xFFFF),
						luaL_optnumber(L,7,31)
					);
					return 0;
				}
				static int bhb1(lua_State*L){
					gfx.rectGradV(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4),
						luaL_optnumber(L,5,0),
						luaL_optnumber(L,6,0xFFFF)
					);
					return 0;
				}
				static int bhb2(lua_State*L){
					gfx.rectGradH(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4),
						luaL_optnumber(L,5,0),
						luaL_optnumber(L,6,0xFFFF)
					);
					return 0;
				}
				static int bi0(lua_State*L){
					gfx.circFrame(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_optnumber(L,4,0)
					);
					return 0;
				}
				static int bi1(lua_State*L){
					gfx.circFill(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_optnumber(L,4,0)
					);
					return 0;
				}
				static int bj0(lua_State*L){
					gfx.elipFrame(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4),
						luaL_optnumber(L,5,0)
					);
					return 0;
				}
				static int bj1(lua_State*L){
					gfx.elipFill(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4),
						luaL_optnumber(L,5,0)
					);
					return 0;
				}
				static int bk0(lua_State*L){
					gfx.triFrame(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4),
						luaL_checknumber(L,5),
						luaL_checknumber(L,6),
						luaL_optnumber(L,7,0)
					);
					return 0;
				}
				static int bk1(lua_State*L){
					gfx.triFill(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_checknumber(L,4),
						luaL_checknumber(L,5),
						luaL_checknumber(L,6),
						luaL_optnumber(L,7,0)
					);
					return 0;
				}
				static int bl0(lua_State*L){lua_pushstring(L,gfx.getFont());return 1;}
				static int bl1(lua_State*L){gfx.setFont(luaL_checkstring(L,1));return 0;}
				static int bl2(lua_State*L){lua_pushinteger(L,gfx.fnt.index);return 1;}
				static int bl3(lua_State*L){gfx.fnt.index=luaL_checknumber(L,1);return 0;}
				static int bl4(lua_State*L){lua_pushinteger(L,gfx.fnt.count);return 1;}
				static int bla0(lua_State*L){lua_pushinteger(L,gfx.getFontWidth());return 1;}
				static int bla1(lua_State*L){lua_pushinteger(L,gfx.getFontHeight());return 1;}
				static int bla2(lua_State*L){lua_pushinteger(L,gfx.getTextWidth(luaL_checkstring(L,1)));return 1;}
				static int blb0(lua_State*L){
					gfx.glyph(
						(char)luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_optnumber(L,4,0)
					);
					return 0;
				}	
				static int blb1(lua_State*L){
					gfx.text(
						luaL_checkstring(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3),
						luaL_optnumber(L,4,0)
					);
					return 0;
				}
				static int blm0(lua_State*L){
					gfx.renderImage(
						luaL_checknumber(L,1),
						luaL_checknumber(L,2),
						luaL_optnumber(L,3,0),
						luaL_optnumber(L,4,1.0f)
					);
					return 0;
				}
				static int blm1(lua_State*L){gfx.setImageTone(luaL_optnumber(L,1,0xFFFF));return 0;}
				static int blm2(lua_State*L){
					gfx.setImageChannels(
						luaL_optnumber(L,1,5),
						luaL_optnumber(L,2,6),
						luaL_optnumber(L,3,5),
						luaL_optnumber(L,4,8)
					);
					return 0;
				}
				static int blm3(lua_State*L){
					gfx.setImageChannels(
						luaL_optnumber(L,1,6),
						luaL_optnumber(L,2,8)
					);
					return 0;
				}
				static int blm4(lua_State*L){
					gfx.setImageCropPosition(
						luaL_optnumber(L,1,0),
						luaL_optnumber(L,2,0)
					);
					return 0;
				}
				static int blm5(lua_State*L){
					gfx.setImageCropSize(
						luaL_optnumber(L,1,0),
						luaL_optnumber(L,2,0)
					);
					return 0;
				}
				static int blm6(lua_State*L){
					gfx.setImageData(
						(const uint8_t*)luaL_checkstring(L,1),
						luaL_checknumber(L,2),
						luaL_checknumber(L,3)
					);
					return 0;
				}
				static int blm7(lua_State*L){lua_pushinteger(L,gfx.getImageWidth());return 1;}
				static int blm8(lua_State*L){lua_pushinteger(L,gfx.getImageHeight());return 1;}

				static int c0(lua_State*L){lua_pushboolean(L,inp.checkTouch());return 1;}
				static int ca0(lua_State*L){lua_pushboolean(L,inp.touchActive);return 1;}
				static int ca1(lua_State*L){lua_pushinteger(L,inp.touchX);return 1;}
				static int ca2(lua_State*L){lua_pushinteger(L,inp.touchY);return 1;}
				static int caa0(lua_State*L){lua_pushboolean(L,inp.touchEnable);return 1;}
				static int caa1(lua_State*L){luaL_checktype(L,1,LUA_TBOOLEAN);inp.touchEnable=lua_toboolean(L,1);return 0;}


				static int zer0(lua_State*L){return 0;}

		}fnc;
		static const luaL_Reg
			fnclib[],syslib[],gfxlib[],nonlib[],inplib[];
};
extern Moon lua;