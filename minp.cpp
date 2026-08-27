#include"main.h"
#include"minp.h"
Input inp;

#if defined(ARDUINO)
	bool Input::checkTouch(){
		#ifdef dd_TouchPanel
			return true;
		#else
			return false;
		#endif
	}
	#ifdef dd_TouchPanel
		#ifdef ddtpi_oTpiCST816
			CST816S tdsp(ddtpi_pData,ddtpi_pClock,ddtpi_pReset,ddtpi_pInterrupt);
		#elifdef ddtpi_oTpiFT6336G
			FT6336U tdsp(ddtpi_pData,ddtpi_pClock,ddtpi_pReset,ddtpi_pInterrupt);
		#endif
		void Input::begin(){
			#ifdef ddtpi_oTpiCST816
				tdsp.begin(Wire,RISING);
			#elifdef ddtpi_oTpiFT6336G
				tdsp.begin();
			#endif
		}
		void Input::tick(){
			if(touchEnable){
				#ifdef ddtpi_oTpiCST816
					touchX=tdsp.data.x;
					touchY=tdsp.data.y;
					touchActive=tdsp.data.event!=0;
				#elifdef ddtpi_oTpiFT6336G
					if(tdsp.read_td_status()){
						touchX=tdsp.read_touch1_x();
						touchY=tdsp.read_touch1_y();
						touchActive=true;
					}else{
						touchActive=false;
					}
				#else
					touchEnable=false;
				#endif
			}else{
				touchX=0;
				touchY=0;
				touchActive=false;
			}
		}
	#else
		void Input::begin(){}
		void Input::tick(){}
	#endif
#else
	bool Input::checkTouch(){return true;}
	void Input::begin(){
		touchActive=false;
		touchX=0;
		touchY=0;
	}
	void Input::tick(){
		if(touchEnable){
			int winW,winH;
			SDL_GetWindowSize(window,&winW,&winH);
			int
				scaleX=winW/gfx.width,
				scaleY=winH/gfx.height,
				scale=std::max(1,std::min(scaleX,scaleY)),
				dstW=gfx.width*scale,
				dstH=gfx.height*scale,
				offsetX=(winW-dstW)/2,
				offsetY=(winH-dstH)/2,
				mouseX,mouseY;
			uint32_t buttons=SDL_GetMouseState(&mouseX,&mouseY);
			if(mouseX<offsetX||mouseY<offsetY||
				mouseX>=offsetX+dstW||mouseY>=offsetY+dstH){
				touchActive=false;
				return;
			}
			touchActive=(buttons&SDL_BUTTON(SDL_BUTTON_LEFT))!=0;
			if(touchActive){
				touchX=(mouseX-offsetX)/scale;
				touchY=(mouseY-offsetY)/scale;
			}
		}else{
			touchX=0;
			touchY=0;
			touchActive=false;
		}
	}
#endif