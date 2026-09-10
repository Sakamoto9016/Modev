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
#endif

void setup();
void loop();

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
		void begin();
};
extern System sys;

class Graphics{
	private:
		const uint8_t ditherMap[256]={
			  0,128,32,160,  8,136, 40,168,  2,130, 34,162, 10,138, 42,170,
			192, 64,224, 96,200, 72,232,104,194, 66,226, 98,202, 74,234,106,
			 48,176, 16,144, 56,184, 24,152, 50,178, 18,146, 58,186, 26,154,
			240,112,208, 80,248,120,216, 88,242,114,210, 82,250,122,218, 90,
			 12,140, 44,172,  4,132, 36,164, 14,142, 46,174,  6,134, 38,166,
			204, 76,236,108,196, 68,228,100,206, 78,238,110,198, 70,230,102,
			 60,188, 28,156, 52,180, 20,148, 62,190, 30,158, 54,182, 22,150,
			252,124,220, 92,244,116,212, 84,254,126,222, 94,246,118,214, 86,
			  3,131, 35,163, 11,139, 43,171,  1,129, 33,161,  9,137, 41,169,
			195, 67,227, 99,203, 75,235,107,193, 65,225, 97,201, 73,233,105,
			 51,179, 19,147, 59,187, 27,155, 49,177, 17,145, 57,185, 25,153,
			243,115,211, 83,251,123,219, 91,241,113,209, 81,249,121,217, 89,
			 15,143, 47,175,  7,135, 39,167, 13,141, 45,173,  5,133, 37,165,
			207, 79,239,111,199, 71,231,103,205, 77,237,109,197, 69,229,101,
			 63,191, 31,159, 55,183, 23,151, 61,189, 29,157, 53,181, 21,149,
			255,127,223, 95,247,119,215, 87,253,125,221, 93,245,117,213, 85
		};
		class _A{
			friend class Graphics;
			uint16_t
				A=0,	/*Color A*/		B=0,	/*Color B*/
				C=0,	/*Top shade*/	D=0,	/*Bottom shade*/
				E=0,	/*Left shade*/	F=0,	/*Right shade*/
				a=0;	/*Auto swap*/
			uint8_t
				type=0;
				/*
					0: Solid fill
					1: Horizontal gradient fill
					2: Vertical gradient fill
				*/
		}color;
		class _B{
			friend class Graphics;
			uint8_t border=0,borderV=0;
			bool safe=true;
		}style;
		class _C{
			friend class Graphics;
			uint8_t A=255;
		}solid;
	public:
		uint16_t width=ddgfx_vWidth,height=ddgfx_vHeight,*buffer;
		uint32_t size=(uint32_t)width*height;
		/*Group of Logic Differentials*/
			void begin();
			void flush();
			void setBrightness(uint8_t v=255);
			void lowClear(uint16_t c=0);
		/*Group of Inlines*/
			/*Group of Utilities*/
				inline uint32_t gFps()
					{
						static uint32_t a=0,frames=0,lastTime=millis();
						frames++;
						uint32_t now=millis();
						if(now-lastTime>=1000){a=frames;frames=0;lastTime=now;}
						return a;
					}
				inline uint16_t getBlend(uint16_t c1,uint16_t c2,uint8_t value=127){
					uint16_t inv=255-value;
					uint8_t
						r1=(c1>>11)&0x1F,g1=(c1>>5)&0x3F,b1=c1&0x1F,
						r2=(c2>>11)&0x1F,g2=(c2>>5)&0x3F,b2=c2&0x1F,
						r=(r1*inv+r2*value)/255,
						g=(g1*inv+g2*value)/255,
						b=(b1*inv+b2*value)/255;
					return(r<<11)|(g<<5)|b;
				}
				inline uint16_t getRgb565(uint8_t r=31,uint8_t g=63,uint8_t b=31){
					r=std::min(r,(uint8_t)31);
					g=std::min(g,(uint8_t)63);
					b=std::min(b,(uint8_t)31);
					return(r<<11)|(g<<5)|b;
				}
				inline uint16_t getRgb111(uint8_t r=1,uint8_t g=1,uint8_t b=1){
					r=std::min(r,(uint8_t)1);
					g=std::min(g,(uint8_t)1);
					b=std::min(b,(uint8_t)1);
					return((r*31+0)<<11)|((g*63+0)<<5)|(b*31+0);
				}
				inline uint16_t getRgb222(uint8_t r=3,uint8_t g=3,uint8_t b=3){
					r=std::min(r,(uint8_t)3);
					g=std::min(g,(uint8_t)3);
					b=std::min(b,(uint8_t)3);
					return(((r*31+1)/3)<<11)|(((g*63+1)/3)<<5)|((b*31+1)/3);
				}
				inline uint8_t gBrightness()
					{return brightValue;}
				inline void aAntiBurn()
					{if(gBrightness()==0)lowClear(0);}	
				inline uint8_t gColorRed(uint16_t c)
					{return(c>>11)&0x1F;}
				inline uint8_t gColorGreen(uint16_t c)
					{return(c>>5)&0x3F;}
				inline uint8_t gColorBlue(uint16_t c)
					{return c&0x1F;}
				inline uint16_t gGradient(uint16_t c0,uint16_t c1,uint16_t x,uint16_t width)
					{
						if(width<1)return c0;
						uint8_t
							r0=gColorRed(c0),g0=gColorGreen(c0),b0=gColorBlue(c0),
							r1=gColorRed(c1),g1=gColorGreen(c1),b1=gColorBlue(c1);
						int16_t
							r=r0+((r1-r0)*x)/(width-1),
							g=g0+((g1-g0)*x)/(width-1),
							b=b0+((b1-b0)*x)/(width-1);
						return(r<<11)|(g<<5)|b;
					}
				inline bool gDither(uint8_t intensity,uint8_t x,uint8_t y)
					{
						if(intensity==0)return false;
						if(intensity==255)return true;
						return intensity>ditherMap[((y&15)<<4)|(x&15)];
					}
//

			/*Group of Clip*/
				inline void sClip(uint16_t x,uint16_t y,uint16_t w,uint16_t h,bool toBuffer)
					{
						if(toBuffer){clipX=x;clipY=y;clipW=w;clipH=h;clipEn=true;}
						else{clipVX=x;clipVY=y;clipVW=w;clipVH=h;clipVEn=true;}
					}
				inline void xClip(bool toBuffer)
					{if(toBuffer)clipEn=false;else clipVEn=false;}
			/*Group of Color and Style*/
				/*
				apsgrx API system
				a=action
				p=passthrough/modular/stackable
				s=set
				g=get/check/probe
				r=render
				x=cancel/clear
				*/
				inline Graphics&psColor(uint16_t colorSolid,uint16_t colorGradient=0)
					{
						color.A=colorSolid;color.B=colorGradient;
						color.type=0;
						return*this;
					}
				inline Graphics&psBorderColorSingle(uint16_t colorSolid)
					{
						color.C=color.D=color.E=color.F=colorSolid;
						style.borderV=0;
						return*this;
					}
				inline Graphics&psBorderColorDuo(uint16_t colorLight,uint16_t colorDark)
					{
						color.C=color.E=colorLight;
						color.D=color.F=colorDark;
						style.borderV=1;
						return*this;
					}
				inline Graphics&psBorderColorQuad(uint16_t colorTop,uint16_t colorBottom,uint16_t colorLeft,uint16_t colorRight)
					{
						color.C=colorTop;
						color.D=colorBottom;
						color.E=colorLeft;
						color.F=colorRight;
						style.borderV=2;
						return*this;
					}
				inline Graphics&psColorGradientSwap(bool enable=true)
					{if(enable){color.a=color.A;color.A=color.B;color.B=color.a;}return*this;}
				inline Graphics&psBorderColorVerticalSwap(bool enable=true)
					{if(enable){color.a=color.C;color.C=color.D;color.D=color.a;}return*this;}
				inline Graphics&psBorderColorHorizontalSwap(bool enable=true)
					{if(enable){color.a=color.E;color.E=color.F;color.F=color.a;}return*this;}
				inline Graphics&psBorderColorSwap(bool enable=true)
					{
						if(enable){
							color.a=color.C;color.C=color.D;color.D=color.a;
							color.a=color.E;color.E=color.F;color.F=color.a;
						}
						return*this;
					}
				inline Graphics&psGradient(uint8_t angle)
					{
						angle%=4;
						if(angle==1||angle==2){
							color.a=color.A;
							color.A=color.B;
							color.B=color.a;
							color.type=1;
						}
						color.type=(angle+1%2)+1;
						return*this;
					}
				inline Graphics&psBorder(uint8_t thickness=0)
					{style.border=thickness;return*this;}
				inline Graphics&psDither(uint8_t density=255)
					{solid.A=density;return*this;}
				inline Graphics&psSafe(bool enable=true)
					{style.safe=enable;return*this;}
				inline Graphics&psClean()
					{
						style.border=0;
						solid.A=255;
						return*this;
					}
				inline Graphics&psTsHsNul2DWthUrPrb()
					{return*this;}
				//
				void sPixel(int32_t x,int32_t y,uint16_t c=0);
				uint16_t gPixel(int32_t x,int32_t y);
				void sBuffer(int64_t p,uint16_t c=0);
				uint16_t gBuffer(int64_t p);

		void rClear();
		void rRect(int32_t x,int32_t y,uint16_t w,uint16_t h);
		void rProgress(int32_t x,int32_t y,uint16_t w,uint16_t h,uint8_t progress);
		void rArray(int32_t x,int32_t y,uint8_t direction);




		void line(int32_t x1,int32_t y1,int32_t x2,int32_t y2,uint16_t c=0);
		void lineV(int32_t x,int32_t y,uint16_t length,uint16_t c=0);
		void lineH(int32_t x,int32_t y,uint16_t length,uint16_t c=0);
		void lineDash(int32_t x1,int32_t y1,int32_t x2,int32_t y2,uint16_t c=0,uint8_t phase=0,uint8_t segment=10);
		void lineEdge(int32_t x,int32_t y,uint16_t length,uint16_t width,uint16_t c=0,uint8_t direction=0);

		void rectProgress(int32_t x,int32_t y,uint16_t w,uint16_t h,uint16_t c=0,uint8_t value=127);
		void rectLoad(int32_t x,int32_t y,uint16_t w,uint16_t h,uint16_t c=0,uint8_t value=4);


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
		void bseinit();
		void raminit();
		void businit();
		void dspinit();
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