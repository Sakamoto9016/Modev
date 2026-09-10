#include"main.h"
#include"mfnt.h"

Graphics gfx;

void Graphics::begin()
	{
		sys.log("Initalizing graphics(4 parts)...",1);
		fnt.count=sizeof(fonts)/sizeof(fonts[0]);
		bseinit();raminit();businit();dspinit();
		sys.log("Initalized graphics.",2);
	}
void Graphics::lowClear(uint16_t c)
	{
		#ifdef ARDUINO
			gfxx->fillScreen(c);
		#else
			uint8_t r=gColorRed(c)*255/31,g=gColorGreen(c)*255/63,b=gColorBlue(c)*255/31;
			SDL_SetRenderDrawColor(renderer,r,g,b,255);
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
		#endif
	}
//
#if defined(ARDUINO)
	void Graphics::setBrightness(uint8_t v){
		#if defined(ddgfx_pBacklight)
			brightValue=v;
			#if defined(ddgfx_oLightSwap)
				analogWrite(ddgfx_pBacklight,255-brightValue);
			#else
				analogWrite(ddgfx_pBacklight,brightValue);
			#endif
		#endif
	}
	void Graphics::flush(){
		uint16_t
			x=clipVEn?clipVX:0,
			y=clipVEn?clipVY:0,
			w=clipVEn?clipVW:width,
			h=clipVEn?clipVH:height,
			lineBuf[width]={0};
		gfxx->startWrite();
		gfxx->writeAddrWindow(x,y,w,h);
		for (uint16_t yy=y;yy<y+h;yy++){
			memcpy(lineBuf,&buffer[yy*w+x],w*sizeof(uint16_t));
			gfxx->writePixels(lineBuf,w);
		}
		gfxx->endWrite();
	}
#else
	void Graphics::setBrightness(uint8_t v){
		brightValue=v;
		uint8_t b=15+(v*240)/255;
		SDL_SetTextureColorMod(texture,b,b,b);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer,texture,nullptr,nullptr);
		SDL_RenderPresent(renderer);
	}
	void Graphics::flush(){
		uint16_t
			x=clipVEn?clipVX:0,
			y=clipVEn?clipVY:0,
			w=clipVEn?clipVW:width,
			h=clipVEn?clipVH:height,
			lineBuf[width]={0};
		void*pixels;
		int pitch;
		SDL_LockTexture(texture,nullptr,&pixels,&pitch);
		for(uint16_t yy=clipVY;yy<y+h;yy++)memcpy((uint8_t*)pixels+yy*pitch+x*sizeof(uint16_t),&buffer[yy*width+x],w*sizeof(uint16_t));
		SDL_UnlockTexture(texture);
		uint8_t b=15+(brightValue*240)/255;
		SDL_SetTextureColorMod(texture,b,b,b);
	}
#endif


void Graphics::sBuffer(int64_t p,uint16_t c)
	{
		if(style.safe&&(p<0||p>=size))return;
		buffer[p]=c;
	}
uint16_t Graphics::gBuffer(int64_t p)
	{
		if(style.safe&&(p<0||p>=size))return 0;
		return buffer[p];
	}
void Graphics::sPixel(int32_t x,int32_t y,uint16_t c)
	{
		if(style.safe&&(x<0||y<0||x>=width||y>=height))return;
		if((x<clipX||y<clipY||x>=clipX+clipW||y>=clipY+clipH)&&clipEn)return;
		buffer[y*width+x]=c;
	}
uint16_t Graphics::gPixel(int32_t x,int32_t y)
	{
		if(style.safe&&(x<0||y<0||x>=width||y>=height))return 0;
		return buffer[y*width+x];
	}
//

void Graphics::rRect(int32_t x,int32_t y,uint16_t w,uint16_t h)
	{
		uint8_t bord=style.border;
		if(bord>0){
			for(uint16_t yy=0;yy<bord;yy++){
				for(uint16_t xx=0;xx<w-(yy*2+1);xx++){
					sBuffer((y+yy)*width+(x+xx+yy),color.C);
					sBuffer((y+h-yy-1)*width+(x+xx+yy+1),color.D);
				}
			}
			for(uint16_t xx=0;xx<bord;xx++){
				for(uint16_t yy=0;yy<h-(xx*2+1);yy++){
					sBuffer((y+yy+1+xx)*width+(x+xx),color.E);
					sBuffer((y+yy+xx)*width+(x+w-(1+xx)),color.F);
				}
			}
		}
		for(uint16_t yy=0;yy<h-(bord*2);yy++){
			for(uint16_t xx=0;xx<w-(bord*2);xx++){
				uint16_t yyy=y+yy+bord,xxx=x+xx+bord;
				if(gDither(solid.A,xxx,yyy)){
					switch(color.type){
						case 1:sBuffer(yyy*width+xxx,gGradient(color.A,color.B,xx,w));break;
						case 2:sBuffer(yyy*width+xxx,gGradient(color.A,color.B,yy,h));break;
						default:sBuffer(yyy*width+xxx,color.A);break;
					}
				}
			}
		}
	}
void Graphics::rClear()
	{rRect(0,0,width,height);}

	// void Graphics::rBuffer(int32_t x,int32_t y,uint16_t w,uint16_t h,uint16_t c,uint8_t value){
		// 	rectFrame(x,y,w,h,c);
		// 	const time_t t=millis()/50;
		// 	const uint16_t ih=h-4,iw=w-4;
		// 	for(int i=0;i<ih;i++){
		// 		for(int j=0;j<iw;j++){
		// 			time_t q=j+t+i;
		// 			if((q/value)%2==0)setPixel(x+j+2,y+i+2,c);
		// 		}
		// 	}
		// }
void Graphics::rProgress(int32_t x,int32_t y,uint16_t w,uint16_t h,uint8_t progress){
	//rectFrame(x,y,w,h,color.A);
	//rectFill(x+2,y+2,((w-4)/255.0f)*value,h-4,color.A);
}



// void Graphics::lineH(int32_t x,int32_t y,uint16_t length,uint16_t c){
// 	for(uint i=0;i<length;i++)setPixel(x+i,y,c);
// }
// void Graphics::lineV(int32_t x,int32_t y,uint16_t length,uint16_t c){
// 	for(uint i=0;i<length;i++)setPixel(x,y+i,c);
// }
// void Graphics::line(int32_t x1,int32_t y1,int32_t x2,int32_t y2,uint16_t c){
// 	int32_t
// 		dx=abs(x2-x1),
// 		sx=x1<x2?1:-1,
// 		dy=-abs(y2-y1),
// 		sy=y1<y2?1:-1,
// 		err=dx+dy,e2;
// 	while(true){
// 		setPixel(x1,y1,c);
// 		if(x1==x2 && y1==y2)break;
// 		e2=2*err;
// 		if(e2>=dy){err+=dy; x1+=sx;}
// 		if(e2<=dx){err+=dx; y1+=sy;}
// 	}
// }
// void Graphics::lineDash(int32_t x1,int32_t y1,int32_t x2,int32_t y2,uint16_t c,uint8_t phase,uint8_t segment){
// 	if(segment==0)segment=1;
// 	int32_t dx=abs(x2-x1),sx=x1<x2?1:-1;
// 	int32_t dy=-abs(y2-y1),sy=y1<y2?1:-1;
// 	int32_t err=dx+dy,e2;
// 	uint8_t counter=phase;
// 	while(true){
// 		if((counter/segment)%2==0)setPixel(x1,y1,c);
// 		counter++;
// 		if(x1==x2&&y1==y2)break;
// 		e2=2*err;
// 		if(e2>=dy){err+=dy;x1+=sx;}
// 		if(e2<=dx){err+=dx;y1+=sy;}
// 	}
// }
// void Graphics::circFrame(int32_t x,int32_t y,uint16_t radius,uint16_t c){
// 	int32_t
// 		dx=0,
// 		dy=radius,
// 		d=3-2*radius;
// 	while(dx<=dy){
// 		setPixel(x+dx,y+dy,c);
// 		setPixel(x-dx,y+dy,c);
// 		setPixel(x+dx,y-dy,c);
// 		setPixel(x-dx,y-dy,c);
// 		setPixel(x+dy,y+dx,c);
// 		setPixel(x-dy,y+dx,c);
// 		setPixel(x+dy,y-dx,c);
// 		setPixel(x-dy,y-dx,c);
// 		if(d<0)d+=4*dx+6;
// 		else{
// 			d+=4*(dx-dy)+10;
// 			dy--;
// 		}
// 		dx++;
// 	}
// }
// void Graphics::circFill(int32_t x,int32_t y,uint16_t radius,uint16_t c){
// 	for(int32_t iy=-radius;iy<=radius;iy++){
// 		int32_t ix=(int32_t)sqrtf((float)radius*radius-(float)iy*iy);
// 		lineH(x-ix,y+iy,ix*2+1,c);
// 	}
// }
// void Graphics::elipFrame(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c){
// 	int32_t a=width>>1;
// 	int32_t b=height>>1;
// 	int32_t a2=a*a;
// 	int32_t b2=b*b;
// 	int32_t dx=0;
// 	int32_t dy=b;
// 	int32_t d1=b2-a2*b+(a2>>2);

// 	while(b2*dx<=a2*dy){
// 		setPixel(x+dx,y+dy,c);
// 		setPixel(x-dx,y+dy,c);
// 		setPixel(x+dx,y-dy,c);
// 		setPixel(x-dx,y-dy,c);

// 		if(d1<0)d1+=b2*(2*dx+3);
// 		else{
// 			d1+=b2*(2*dx+3)+a2*(-2*dy+2);
// 			dy--;
// 		}
// 		dx++;
// 	}

// 	float d2=b2*(dx+0.5f)*(dx+0.5f)+a2*(dy-1)*(dy-1)-a2*b2;

// 	while(dy>=0){
// 		setPixel(x+dx,y+dy,c);
// 		setPixel(x-dx,y+dy,c);
// 		setPixel(x+dx,y-dy,c);
// 		setPixel(x-dx,y-dy,c);

// 		if(d2>0)d2+=a2*(-2*dy+3);
// 		else{
// 			d2+=b2*(2*dx+2)+a2*(-2*dy+3);
// 			dx++;
// 		}
// 		dy--;
// 	}
// }
// void Graphics::elipFill(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c){
// 	int32_t a=width>>1;
// 	int32_t b=height>>1;
// 	if(b==0)return;

// 	for(int32_t iy=-b;iy<=b;iy++){
// 		float fy=(float)iy/b;
// 		int32_t ix=(int32_t)(a*sqrtf(1.0f-fy*fy));
// 		lineH(x-ix,y+iy,ix*2+1,c);
// 	}
// }
// void Graphics::triFrame(int32_t x1,int32_t y1,int32_t x2,int32_t y2,int32_t x3,int32_t y3,uint16_t c){
// 	line(x1,y1,x2,y2,c);
// 	line(x2,y2,x3,y3,c);
// 	line(x3,y3,x1,y1,c);
// }
// void Graphics::triFill(int32_t x1,int32_t y1,int32_t x2,int32_t y2,int32_t x3,int32_t y3,uint16_t c){
// 	int32_t sx1=x1,sy1=y1;
// 	int32_t sx2=x2,sy2=y2;
// 	int32_t sx3=x3,sy3=y3;
// 	if(sy1>sy2){swap16(sy1,sy2);swap16(sx1,sx2);}
// 	if(sy2>sy3){swap16(sy2,sy3);swap16(sx2,sx3);}
// 	if(sy1>sy2){swap16(sy1,sy2);swap16(sx1,sx2);}
// 	auto edgeInterp=[](int32_t x0,int32_t y0,int32_t x1,int32_t y1,int32_t y){if(y1==y0)return x0;return x0+(y-y0)*(x1-x0)/(y1-y0);};
// 	for(int32_t y=sy1;y<=sy3;y++){
// 		int32_t xa,xb;
// 		if(y<sy2){
// 			xa=edgeInterp(sx1,sy1,sx2,sy2,y);
// 			xb=edgeInterp(sx1,sy1,sx3,sy3,y);
// 		}else{
// 			xa=edgeInterp(sx2,sy2,sx3,sy3,y);
// 			xb=edgeInterp(sx1,sy1,sx3,sy3,y);
// 		}
// 		if(xa>xb){int32_t t=xa;xa=xb;xb=t;}
// 		lineH(xa,y,xb-xa+1,c);
// 	}
// }
// void Graphics::setFont(const char* fontname){
// 	for(int i=0;i<fnt.count;i++){
// 		if(strcmp(fonts[i].name,fontname)==0){
// 			fnt.index=i;
// 			return;
// 		}
// 	}
// 	fnt.index=0;
// }
// const char* Graphics::getFont(){
// 	return fonts[fnt.index].name;
// }
// uint8_t Graphics::getFontWidth(){
// 	return fonts[fnt.index].width;
// }
// uint8_t Graphics::getFontHeight(){
// 	return fonts[fnt.index].height;
// }
// uint16_t Graphics::getTextWidth(const char* text){
// 	if(!text)return 0;
// 	return strlen(text)*fonts[fnt.index].width;
// }
// void Graphics::glyph(char ch,int32_t x,int32_t y,uint16_t c){
// 	const font& f=fonts[fnt.index];
// 	int index=resolveGlyphIndex(f,(unsigned char)ch);
// 	int glyphSize=(f.bufw*f.bufh)/8;
// 	int ox=f.offsetX;
// 	int oy=f.offsetY;
// 	const uint8_t*glyph;
// 	if(index==-1)glyph=f.repl;
// 	else glyph=f.data+index*glyphSize;
// 	for(int gy=0;gy<f.height;gy++)
// 		for(int gx=0;gx<f.width;gx++)
// 			if(fontPixel(f,glyph,gx,gy))
// 				setPixel(x+gx+ox,y+gy+oy,c);
// }
// void Graphics::text(const char* text,int32_t x,int32_t y,uint16_t c){
// 	if(!text)return;
// 	const font&f=fonts[fnt.index];
// 	int16_t cx=x,cy=y;
// 	while(*text){
// 		if(*text=='\n'){
// 			cx=x;cy+=f.height;
// 			text++;
// 			continue;
// 		}
// 		glyph(*text,cx,cy,c);
// 		cx+=f.width;text++;
// 	}
// }
// void Graphics::rectPop(int32_t x,int32_t y,uint16_t w,uint16_t h,uint16_t c,uint16_t lightcolor,uint16_t darkcolor,uint16_t border,bool invert,bool flat){
// 	rectFill(x,y,w,h,c);
// 	if(!flat){
// 		lineEdge(x,y,w,border,invert?darkcolor:lightcolor,0);
// 		lineEdge(x,y,h,border,invert?darkcolor:lightcolor,3);
// 		lineEdge(x,y+h-1,w,border,invert?lightcolor:darkcolor,2);
// 		lineEdge(x+w-1,y,h,border,invert?lightcolor:darkcolor,1);
// 	}
// }
// void Graphics::setImageTone(uint16_t c){
// 	imgGr=c;
// }
// void Graphics::setImageChannels(uint8_t r,uint8_t g,uint8_t b,uint8_t a){
// 	imgRb=r;imgGb=g;
// 	imgBb=b;imgAb=a;
// 	imgSi=false;
// }
// void Graphics::setImageChannels(uint8_t g,uint8_t a){
// 	imgGb=g;imgAb=a;
// 	imgSi=true;
// }
// void Graphics::setImageCropPosition(uint16_t x,uint16_t y){
// 	imgSX=x;imgSY=y;
// }
// void Graphics::setImageCropSize(uint16_t w,uint16_t h){
// 	imgCW=w;imgCH=h;
// }
// void Graphics::setImageData(const uint8_t* data,uint16_t w,uint16_t h){
// 	imgD=data;imgW=w;imgH=h;
// }
// uint16_t Graphics::getImageWidth(){
// 	return imgW;
// }
// uint16_t Graphics::getImageHeight(){
// 	return imgH;
// }
// void Graphics::renderImage(int32_t x,int32_t y,uint8_t rotate,float scale){
// 	if(!imgD)return;
// 	if(!imgW||!imgH)return;
// 	if(scale<=0.0f)return;
// 	rotate&=3;
// 	const bool cropped=imgCW!=0&&imgCH!=0;
// 	uint16_t
// 		srcW=imgW,
// 		srcH=imgH;
// 	if(rotate&1){
// 		srcW=imgH;
// 		srcH=imgW;
// 	}
// 	uint16_t
// 		renderW=cropped?imgCW:srcW,
// 		renderH=cropped?imgCH:srcH;
// 	if(renderW>srcW)renderW=srcW;
// 	if(renderH>srcH)renderH=srcH;
// 	uint8_t bitsPerPixel;
// 	if(imgSi)bitsPerPixel=imgGb+imgAb;
// 	else bitsPerPixel=imgRb+imgGb+imgBb+imgAb;
// 	if(!bitsPerPixel)return;
// 	for(uint16_t dy=0;dy<renderH;dy++){
// 		for(uint16_t dx=0;dx<renderW;dx++){
// 			uint16_t
// 				rx=(uint16_t)((float)dx/scale),
// 				ry=(uint16_t)((float)dy/scale);
// 			if(rx>=renderW||ry>=renderH)continue;
// 			int32_t sx,sy;
// 			switch (rotate) {
// 				case 1:sx=ry;sy=imgH-1-rx;break;
// 				case 2:sx=imgW-1-rx;sy=imgH-1-ry;break;
// 				case 3:sx=imgW-1-ry;sy=rx;break;
// 				default:sx=rx;sy=ry;break;
// 			}
// 			if(cropped){
// 				sx+=imgSX;sy+=imgSY;
// 				sx%=imgW;sy%=imgH;
// 				if(sx<0)sx+=imgW;
// 				if(sy<0)sy+=imgH;
// 			}
// 			if(sx<0||sy<0||sx>=imgW||sy>=imgH)continue;
// 			uint32_t
// 				pixelIndex=(uint32_t)sy*imgW+(uint32_t)sx,
// 				bitPos=pixelIndex*bitsPerPixel;
// 			uint8_t
// 				r=0,
// 				g=0,
// 				b=0,
// 				a=255;
// 			if(imgSi){
// 				uint32_t
// 					gv=imgIRB(imgD,bitPos,imgGb),
// 					av=0;
// 				if(imgAb){
// 					av=imgIRB(imgD,bitPos,imgAb);
// 					a=imgIE(av,imgAb);
// 				}
// 				uint8_t gray=imgIE(gv,imgGb);
// 				if(imgGr==0xFFFF){
// 					r=gray;g=gray;b=gray;
// 				}else{ 
// 					uint8_t
// 						tr=(uint8_t)(((imgGr>>11)&0x1F)<<3),
// 						tg=(uint8_t)(((imgGr>>5)&0x3F)<<2),
// 						tb=(uint8_t)((imgGr&0x1F)<<3);
// 					r=(uint8_t)(((uint16_t)tr*gray)/255);
// 					g=(uint8_t)(((uint16_t)tg*gray)/255);
// 					b=(uint8_t)(((uint16_t)tb*gray)/255);
// 				}
// 			}else{
// 				uint32_t
// 					rv=imgIRB(imgD,bitPos,imgRb),
// 					gv=imgIRB(imgD,bitPos,imgGb),
// 					bv=imgIRB(imgD,bitPos,imgBb),
// 					av=0;
// 				if(imgAb){
// 					av=imgIRB(imgD,bitPos,imgAb);
// 					a=imgIE(av,imgAb);
// 				}
// 				r=imgIE(rv,imgRb);
// 				g=imgIE(gv,imgGb);
// 				b=imgIE(bv,imgBb);
// 			}
// 			int32_t
// 				px=x+(int32_t)((float)dx*scale),
// 				py=y+(int32_t)((float)dy*scale),
// 				scaledW=(int32_t)scale,
// 				scaledH=(int32_t)scale;
// 			if(scaledW<1)scaledW=1;
// 			if(scaledH<1)scaledH=1;
// 			if (a == 0)continue;
// 			for(int32_t yy=0;yy<scaledH;yy++){
// 				for(int32_t xx=0;xx<scaledW;xx++){
// 					int32_t
// 						fx=px+xx,
// 						fy=py+yy;
// 					uint16_t
// 						dst=gfx.getPixel(fx,fy),
// 						src=(uint16_t)(((r>>3)<<11)|((g>>2)<<5)|(b>>3)),
// 						finalColor=getBlend(dst,src,a);
// 					gfx.setPixel(fx,fy,finalColor);
// 				}
// 			}
// 		}
// 	}
// }