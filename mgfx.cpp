#include"main.h"
#include"mfnt.h"

Graphics gfx;

#if defined(ARDUINO)
	Arduino_DataBus*bus=nullptr;
	Arduino_TFT*gfxx=nullptr;
	void Graphics::begin(){
		fnt.count=sizeof(fonts)/sizeof(fonts[0]);
		raminit();
		businit();
		dspinit();
	}
	void Graphics::setBrightness(uint8_t v){
		#if defined(GfxBacklight)
			brightValue=v;
			#if defined(GfxBacklightSwap)
				analogWrite(GfxBacklight,255-brightValue);
			#else
				analogWrite(GfxBacklight,brightValue);
			#endif
		#endif
	}
	void Graphics::clearQuick(uint16_t c){
		gfxx->fillScreen(c);
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
	SDL_Window*window=nullptr;
	SDL_Renderer*renderer=nullptr;
	SDL_Texture*texture=nullptr;
	void Graphics::begin(){
		fnt.count=sizeof(fonts)/sizeof(fonts[0]);
		buffer=new uint16_t[size];
		if(!buffer)sys.lightCrash(1);

		SDL_Init(SDL_INIT_VIDEO);
		char buf[256];
		sprintf(buf,"Modev %s(v%s) %s Emulation",sys.versionName,sys.versionString,sys.prototype?"Prototype":"");
		//window=SDL_CreateWindow(buf,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width*GfxScale,height*GfxScale,SDL_WINDOW_SHOWN);
		window=SDL_CreateWindow(buf,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width*GfxScale,height*GfxScale,SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
		renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
		texture=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGB565,SDL_TEXTUREACCESS_STREAMING,width,height);
	}
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
	void Graphics::clearQuick(uint16_t c){
		uint8_t
			r=((c>>11)&0x1F)*255/31,
			g=((c>>5)&0x3F)*255/63,
			b=(c& 0x1F)*255/31;
		SDL_SetRenderDrawColor(renderer,r,g,b,255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}
#endif
uint8_t Graphics::getBrightness(){
	return brightValue;
}
uint32_t Graphics::getFps(){
	static uint32_t
		a=0,
		frames=0,
		lastTime=millis();
	frames++;
	uint32_t now=millis();
	if(now-lastTime>=1000){
		a=frames;
		frames=0;
		lastTime=now;
	}
	return a;
}
void Graphics::antiBurn(){
	if(getBrightness()==0)clearQuick(0);
}
uint16_t Graphics::getRgb565(uint8_t r,uint8_t g,uint8_t b){
	r=std::min(r,(uint8_t)31);
	g=std::min(g,(uint8_t)63);
	b=std::min(b,(uint8_t)31);
	return(r<<11)|(g<<5)|b;
}
uint16_t Graphics::getRgb111(uint8_t r,uint8_t g,uint8_t b){
	r=std::min(r,(uint8_t)1);
	g=std::min(g,(uint8_t)1);
	b=std::min(b,(uint8_t)1);
	return((r*31+0)<<11)|((g*63+0)<<5)|(b*31+0);
}
uint16_t Graphics::getRgb222(uint8_t r, uint8_t g, uint8_t b){
	r=std::min(r,(uint8_t)3);
	g=std::min(g,(uint8_t)3);
	b=std::min(b,(uint8_t)3);
	return(((r*31+1)/3)<<11)|(((g*63+1)/3)<<5)|((b*31+1)/3);
}
uint16_t Graphics::getBlend(uint16_t c1,uint16_t c2,uint8_t value){
	uint16_t inv=255-value;
	uint8_t
		r1=(c1>>11)&0x1F,g1=(c1>>5)&0x3F,b1=c1&0x1F,
		r2=(c2>>11)&0x1F,g2=(c2>>5)&0x3F,b2=c2&0x1F,
		r=(r1*inv+r2*value)/255,
		g=(g1*inv+g2*value)/255,
		b=(b1*inv+b2*value)/255;
	return(r<<11)|(g<<5)|b;
}
void Graphics::clip(uint16_t x,uint16_t y,uint16_t w,uint16_t h){
	clipX=x;clipY=y;clipW=w;clipH=h;clipEn=true;
}
void Graphics::clipView(uint16_t x,uint16_t y,uint16_t w,uint16_t h){
	clipVX=x;clipVY=y;clipVW=w;clipVH=h;clipVEn=true;
}
void Graphics::clip(){
	clipEn=false;
}
void Graphics::clipView(){
	clipVEn=false;
}
void Graphics::clear(uint16_t c){
	for(uint32_t i=0;i<size;i++)buffer[i]=c;
}
void Graphics::setPixel(int32_t x,int32_t y,uint16_t c,bool safe){
	if(safe&&(x<0||y<0||x>=width||y>=height))return;
	if((x<clipX||y<clipY||x>=clipX+clipW||y>=clipY+clipH)&&clipEn)return;
	buffer[y*width+x]=c;
}
uint16_t Graphics::getPixel(int32_t x,int32_t y,bool safe){
	if(safe&&(x<0||y<0||x>=width||y>=height))return 0;
	return buffer[y*width+x];
}
void Graphics::lineH(int32_t x,int32_t y,uint16_t length,uint16_t c){
	for(uint i=0;i<length;i++)setPixel(x+i,y,c);
}
void Graphics::lineV(int32_t x,int32_t y,uint16_t length,uint16_t c){
	for(uint i=0;i<length;i++)setPixel(x,y+i,c);
}
void Graphics::line(int32_t x1,int32_t y1,int32_t x2,int32_t y2,uint16_t c){
	int32_t
		dx=abs(x2-x1),
		sx=x1<x2?1:-1,
		dy=-abs(y2-y1),
		sy=y1<y2?1:-1,
		err=dx+dy,e2;
	while(true){
		setPixel(x1,y1,c);
		if(x1==x2 && y1==y2)break;
		e2=2*err;
		if(e2>=dy){err+=dy; x1+=sx;}
		if(e2<=dx){err+=dx; y1+=sy;}
	}
}
void Graphics::lineDash(int32_t x1,int32_t y1,int32_t x2,int32_t y2,uint16_t c,uint8_t phase,uint8_t segment){
	if(segment==0)segment=1;
	int32_t dx=abs(x2-x1),sx=x1<x2?1:-1;
	int32_t dy=-abs(y2-y1),sy=y1<y2?1:-1;
	int32_t err=dx+dy,e2;
	uint8_t counter=phase;
	while(true){
		if((counter/segment)%2==0)setPixel(x1,y1,c);
		counter++;
		if(x1==x2&&y1==y2)break;
		e2=2*err;
		if(e2>=dy){err+=dy;x1+=sx;}
		if(e2<=dx){err+=dx;y1+=sy;}
	}
}
void Graphics::rectFrame(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c){
	if(width==0||height==0)return;
	lineH(x,y,width,c);
	lineH(x,y+height-1,width,c);
	lineV(x,y,height,c);
	lineV(x+width-1,y,height,c);
}
void Graphics::rectFill(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c){
	for(uint i=0;i<height;i++)lineH(x,y+i,width,c);
}
void Graphics::rectDither(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c,uint8_t density){
	if(density>15)density=15;
	for(int32_t iy=0;iy<height;iy++)for(int32_t ix=0;ix<width;ix++){
		uint8_t threshold=bayer4x4[(y+iy)&3][(x+ix)&3];
		if(density>threshold)setPixel(x+ix,y+iy,c);
	}
}
void Graphics::clearDither(uint8_t density,uint16_t c){
	rectDither(0,0,width,height,density,c);
}
void Graphics::rectGradH(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c1,uint16_t c2){
	if(width==0)return;
	uint8_t r1=(c1>>11)&31,g1=(c1>>5)&63,b1=c1&31;
	uint8_t r2=(c2>>11)&31,g2=(c2>>5)&63,b2=c2&31;
	for(uint16_t i=0;i<width;i++){
		uint8_t ratio=(width<=1)?0:(uint32_t)i*255/(width-1);
		uint8_t r=r1+((r2-r1)*ratio)/255;
		uint8_t g=g1+((g2-g1)*ratio)/255;
		uint8_t b=b1+((b2-b1)*ratio)/255;
		lineV(x+i,y,height,(r<<11)|(g<<5)|b);
	}
}
void Graphics::rectGradV(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c1,uint16_t c2){
	if(height==0)return;
	uint8_t r1=(c1>>11)&31,g1=(c1>>5)&63,b1=c1&31;
	uint8_t r2=(c2>>11)&31,g2=(c2>>5)&63,b2=c2&31;
	for(uint16_t i=0;i<height;i++){
		uint8_t ratio=(height<=1)?0:(uint32_t)i*255/(height-1);
		uint8_t r=r1+((r2-r1)*ratio)/255;
		uint8_t g=g1+((g2-g1)*ratio)/255;
		uint8_t b=b1+((b2-b1)*ratio)/255;
		lineH(x,y+i,width,(r<<11)|(g<<5)|b);
	}
}
void Graphics::rectGrad(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c1,uint16_t c2,uint8_t angle){
	if(width==0||height==0)return;
	float rad=angle*6.28318530718f/256.0f;
	float dx=cosf(rad);
	float dy=sinf(rad);
	uint8_t
		r1=(c1>>11)&31,g1=(c1>>5)&63,b1=c1&31,
		r2=(c2>>11)&31,g2=(c2>>5)&63,b2=c2&31;
	float p0=0;
	float p1=(width-1)*dx;
	float p2=(height-1)*dy;
	float p3=(width-1)*dx+(height-1)*dy;
	float mn=fminf(fminf(p0,p1),fminf(p2,p3));
	float mx=fmaxf(fmaxf(p0,p1),fmaxf(p2,p3));
	float span=mx-mn;
	if(span==0)span=1;
	for(uint16_t iy=0;iy<height;iy++){
		for(uint16_t ix=0;ix<width;ix++){
			float t=(ix*dx+iy*dy-mn)/span;
			uint8_t r=r1+(r2-r1)*t;
			uint8_t g=g1+(g2-g1)*t;
			uint8_t b=b1+(b2-b1)*t;
			setPixel(x+ix,y+iy,(r<<11)|(g<<5)|b,false);
		}
	}
}
void Graphics::clearGradH(uint16_t c1,uint16_t c2){
	rectGradH(0,0,width,height,c1,c2);
}
void Graphics::clearGradV(uint16_t c1,uint16_t c2){
	rectGradV(0,0,width,height,c1,c2);
}
void Graphics::clearGrad(uint16_t c1,uint16_t c2,uint8_t angle){
	rectGrad(0,0,width,height,c1,c2,angle);
}
void Graphics::circFrame(int32_t x,int32_t y,uint16_t radius,uint16_t c){
	int32_t
		dx=0,
		dy=radius,
		d=3-2*radius;
	while(dx<=dy){
		setPixel(x+dx,y+dy,c);
		setPixel(x-dx,y+dy,c);
		setPixel(x+dx,y-dy,c);
		setPixel(x-dx,y-dy,c);
		setPixel(x+dy,y+dx,c);
		setPixel(x-dy,y+dx,c);
		setPixel(x+dy,y-dx,c);
		setPixel(x-dy,y-dx,c);
		if(d<0)d+=4*dx+6;
		else{
			d+=4*(dx-dy)+10;
			dy--;
		}
		dx++;
	}
}
void Graphics::circFill(int32_t x,int32_t y,uint16_t radius,uint16_t c){
	for(int32_t iy=-radius;iy<=radius;iy++){
		int32_t ix=(int32_t)sqrtf((float)radius*radius-(float)iy*iy);
		lineH(x-ix,y+iy,ix*2+1,c);
	}
}
void Graphics::elipFrame(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c){
	int32_t a=width>>1;
	int32_t b=height>>1;
	int32_t a2=a*a;
	int32_t b2=b*b;
	int32_t dx=0;
	int32_t dy=b;
	int32_t d1=b2-a2*b+(a2>>2);

	while(b2*dx<=a2*dy){
		setPixel(x+dx,y+dy,c);
		setPixel(x-dx,y+dy,c);
		setPixel(x+dx,y-dy,c);
		setPixel(x-dx,y-dy,c);

		if(d1<0)d1+=b2*(2*dx+3);
		else{
			d1+=b2*(2*dx+3)+a2*(-2*dy+2);
			dy--;
		}
		dx++;
	}

	float d2=b2*(dx+0.5f)*(dx+0.5f)+a2*(dy-1)*(dy-1)-a2*b2;

	while(dy>=0){
		setPixel(x+dx,y+dy,c);
		setPixel(x-dx,y+dy,c);
		setPixel(x+dx,y-dy,c);
		setPixel(x-dx,y-dy,c);

		if(d2>0)d2+=a2*(-2*dy+3);
		else{
			d2+=b2*(2*dx+2)+a2*(-2*dy+3);
			dx++;
		}
		dy--;
	}
}
void Graphics::elipFill(int32_t x,int32_t y,uint16_t width,uint16_t height,uint16_t c){
	int32_t a=width>>1;
	int32_t b=height>>1;
	if(b==0)return;

	for(int32_t iy=-b;iy<=b;iy++){
		float fy=(float)iy/b;
		int32_t ix=(int32_t)(a*sqrtf(1.0f-fy*fy));
		lineH(x-ix,y+iy,ix*2+1,c);
	}
}
void Graphics::triFrame(int32_t x1,int32_t y1,int32_t x2,int32_t y2,int32_t x3,int32_t y3,uint16_t c){
	line(x1,y1,x2,y2,c);
	line(x2,y2,x3,y3,c);
	line(x3,y3,x1,y1,c);
}
void Graphics::triFill(int32_t x1,int32_t y1,int32_t x2,int32_t y2,int32_t x3,int32_t y3,uint16_t c){
	int32_t sx1=x1,sy1=y1;
	int32_t sx2=x2,sy2=y2;
	int32_t sx3=x3,sy3=y3;
	if(sy1>sy2){swap16(sy1,sy2);swap16(sx1,sx2);}
	if(sy2>sy3){swap16(sy2,sy3);swap16(sx2,sx3);}
	if(sy1>sy2){swap16(sy1,sy2);swap16(sx1,sx2);}
	auto edgeInterp=[](int32_t x0,int32_t y0,int32_t x1,int32_t y1,int32_t y){if(y1==y0)return x0;return x0+(y-y0)*(x1-x0)/(y1-y0);};
	for(int32_t y=sy1;y<=sy3;y++){
		int32_t xa,xb;
		if(y<sy2){
			xa=edgeInterp(sx1,sy1,sx2,sy2,y);
			xb=edgeInterp(sx1,sy1,sx3,sy3,y);
		}else{
			xa=edgeInterp(sx2,sy2,sx3,sy3,y);
			xb=edgeInterp(sx1,sy1,sx3,sy3,y);
		}
		if(xa>xb){int32_t t=xa;xa=xb;xb=t;}
		lineH(xa,y,xb-xa+1,c);
	}
}
void Graphics::setFont(const char* fontname){
	for(int i=0;i<fnt.count;i++){
		if(strcmp(fonts[i].name,fontname)==0){
			fnt.index=i;
			return;
		}
	}
	fnt.index=0;
}
const char* Graphics::getFont(){
	return fonts[fnt.index].name;
}
uint8_t Graphics::getFontWidth(){
	return fonts[fnt.index].width;
}
uint8_t Graphics::getFontHeight(){
	return fonts[fnt.index].height;
}
uint16_t Graphics::getTextWidth(const char* text){
	if(!text)return 0;
	return strlen(text)*fonts[fnt.index].width;
}
void Graphics::glyph(char ch,int32_t x,int32_t y,uint16_t c){
	const font& f=fonts[fnt.index];
	int index=resolveGlyphIndex(f,(unsigned char)ch);
	int glyphSize=(f.bufw*f.bufh)/8;
	int ox=f.offsetX;
	int oy=f.offsetY;
	const uint8_t*glyph;
	if(index==-1)glyph=f.repl;
	else glyph=f.data+index*glyphSize;
	for(int gy=0;gy<f.height;gy++)
		for(int gx=0;gx<f.width;gx++)
			if(fontPixel(f,glyph,gx,gy))
				setPixel(x+gx+ox,y+gy+oy,c);
}
void Graphics::text(const char* text,int32_t x,int32_t y,uint16_t c){
	if(!text)return;
	const font&f=fonts[fnt.index];
	int16_t cx=x,cy=y;
	while(*text){
		if(*text=='\n'){
			cx=x;cy+=f.height;
			text++;
			continue;
		}
		glyph(*text,cx,cy,c);
		cx+=f.width;text++;
	}
}
void Graphics::rectLoad(int32_t x,int32_t y,uint16_t w,uint16_t h,uint16_t c,uint8_t value){
	rectFrame(x,y,w,h,c);
	const time_t t=millis()/50;
	const uint16_t ih=h-4,iw=w-4;
	for(int i=0;i<ih;i++){
		for(int j=0;j<iw;j++){
			time_t q=j+t+i;
			if((q/value)%2==0)setPixel(x+j+2,y+i+2,c);
		}
	}
}
void Graphics::rectProgress(int32_t x,int32_t y,uint16_t w,uint16_t h,uint16_t c,uint8_t value){
	rectFrame(x,y,w,h,c);
	rectFill(x+2,y+2,((w-4)/255.0f)*value,h-4,c);
}
void Graphics::lineEdge(int32_t x,int32_t y,uint16_t length,uint16_t width,uint16_t c,uint8_t direction){
	for(int i=0;i<width;i++){
		switch(direction){
			case 1:lineV(x-i,y+i,length-i*2,c);break;
			case 2:lineH(x+i,y-i,length-i*2,c);break;
			case 3:lineV(x+i,y+i,length-i*2,c);break;
			default:lineH(x+i,y+i,length-i*2,c);break;
		}
	}
}
void Graphics::rectPop(int32_t x,int32_t y,uint16_t w,uint16_t h,uint16_t c,uint16_t lightcolor,uint16_t darkcolor,uint16_t border,bool invert,bool flat){
	rectFill(x,y,w,h,c);
	if(!flat){
		lineEdge(x,y,w,border,invert?darkcolor:lightcolor,0);
		lineEdge(x,y,h,border,invert?darkcolor:lightcolor,3);
		lineEdge(x,y+h-1,w,border,invert?lightcolor:darkcolor,2);
		lineEdge(x+w-1,y,h,border,invert?lightcolor:darkcolor,1);
	}
}
void Graphics::setImageTone(uint16_t c){
	imgGr=c;
}
void Graphics::setImageChannels(uint8_t r,uint8_t g,uint8_t b,uint8_t a){
	imgRb=r;imgGb=g;
	imgBb=b;imgAb=a;
	imgSi=false;
}
void Graphics::setImageChannels(uint8_t g,uint8_t a){
	imgGb=g;imgAb=a;
	imgSi=true;
}
void Graphics::setImageCropPosition(uint16_t x,uint16_t y){
	imgSX=x;imgSY=y;
}
void Graphics::setImageCropSize(uint16_t w,uint16_t h){
	imgCW=w;imgCH=h;
}
void Graphics::setImageData(const uint8_t* data,uint16_t w,uint16_t h){
	imgD=data;imgW=w;imgH=h;
}
uint16_t Graphics::getImageWidth(){
	return imgW;
}
uint16_t Graphics::getImageHeight(){
	return imgH;
}
void Graphics::renderImage(int32_t x,int32_t y,uint8_t rotate,float scale){
	if(!imgD)return;
	if(!imgW||!imgH)return;
	if(scale<=0.0f)return;
	rotate&=3;
	const bool cropped=imgCW!=0&&imgCH!=0;
	uint16_t
		srcW=imgW,
		srcH=imgH;
	if(rotate&1){
		srcW=imgH;
		srcH=imgW;
	}
	uint16_t
		renderW=cropped?imgCW:srcW,
		renderH=cropped?imgCH:srcH;
	if(renderW>srcW)renderW=srcW;
	if(renderH>srcH)renderH=srcH;
	uint8_t bitsPerPixel;
	if(imgSi)bitsPerPixel=imgGb+imgAb;
	else bitsPerPixel=imgRb+imgGb+imgBb+imgAb;
	if(!bitsPerPixel)return;
	for(uint16_t dy=0;dy<renderH;dy++){
		for(uint16_t dx=0;dx<renderW;dx++){
			uint16_t
				rx=(uint16_t)((float)dx/scale),
				ry=(uint16_t)((float)dy/scale);
			if(rx>=renderW||ry>=renderH)continue;
			int32_t sx,sy;
			switch (rotate) {
				case 1:sx=ry;sy=imgH-1-rx;break;
				case 2:sx=imgW-1-rx;sy=imgH-1-ry;break;
				case 3:sx=imgW-1-ry;sy=rx;break;
				default:sx=rx;sy=ry;break;
			}
			if(cropped){
				sx+=imgSX;sy+=imgSY;
				sx%=imgW;sy%=imgH;
				if(sx<0)sx+=imgW;
				if(sy<0)sy+=imgH;
			}
			if(sx<0||sy<0||sx>=imgW||sy>=imgH)continue;
			uint32_t
				pixelIndex=(uint32_t)sy*imgW+(uint32_t)sx,
				bitPos=pixelIndex*bitsPerPixel;
			uint8_t
				r=0,
				g=0,
				b=0,
				a=255;
			if(imgSi){
				uint32_t
					gv=imgIRB(imgD,bitPos,imgGb),
					av=0;
				if(imgAb){
					av=imgIRB(imgD,bitPos,imgAb);
					a=imgIE(av,imgAb);
				}
				uint8_t gray=imgIE(gv,imgGb);
				if(imgGr==0xFFFF){
					r=gray;g=gray;b=gray;
				}else{ 
					uint8_t
						tr=(uint8_t)(((imgGr>>11)&0x1F)<<3),
						tg=(uint8_t)(((imgGr>>5)&0x3F)<<2),
						tb=(uint8_t)((imgGr&0x1F)<<3);
					r=(uint8_t)(((uint16_t)tr*gray)/255);
					g=(uint8_t)(((uint16_t)tg*gray)/255);
					b=(uint8_t)(((uint16_t)tb*gray)/255);
				}
			}else{
				uint32_t
					rv=imgIRB(imgD,bitPos,imgRb),
					gv=imgIRB(imgD,bitPos,imgGb),
					bv=imgIRB(imgD,bitPos,imgBb),
					av=0;
				if(imgAb){
					av=imgIRB(imgD,bitPos,imgAb);
					a=imgIE(av,imgAb);
				}
				r=imgIE(rv,imgRb);
				g=imgIE(gv,imgGb);
				b=imgIE(bv,imgBb);
			}
			int32_t
				px=x+(int32_t)((float)dx*scale),
				py=y+(int32_t)((float)dy*scale),
				scaledW=(int32_t)scale,
				scaledH=(int32_t)scale;
			if(scaledW<1)scaledW=1;
			if(scaledH<1)scaledH=1;
			if (a == 0)continue;
			for(int32_t yy=0;yy<scaledH;yy++){
				for(int32_t xx=0;xx<scaledW;xx++){
					int32_t
						fx=px+xx,
						fy=py+yy;
					uint16_t
						dst=gfx.getPixel(fx,fy),
						src=(uint16_t)(((r>>3)<<11)|((g>>2)<<5)|(b>>3)),
						finalColor=getBlend(dst,src,a);
					gfx.setPixel(fx,fy,finalColor);
				}
			}
		}
	}
}