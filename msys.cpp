#include"main.h"

System sys;

const char*markerInstruction=R"(
Markers:
(!-) Note
(++) Started
(--) Success
(==) Failed
(!!) Warning
)";
//0~4
uint16_t lineCount=0;

#if defined(ARDUINO) 
	const bool System::emulation=false;
	void System::lightCrash(uint8_t err){
		/*So cfg area*/
		const uint16_t
			hi=1000,	/*Dah*/
			lo=500,		/*Dit*/
			be=250,		/*Space*/
			pa=2000;	/*Pause*/
		/*Eo cfg area*/
		while(true){
			for(uint8_t i=0;i<4;i++){
				#if defined(SysDebugLight)
					#if defined(GfxInvertedBacklight)
						digitalWrite(SysDebugLight,false);
					#else
						digitalWrite(SysDebugLight,true);
					#endif
					bool bit=(err>>i)&1;
					delay(bit?hi:lo);
					#if defined(GfxInvertedBacklight)
						digitalWrite(SysDebugLight,true);
					#else
						digitalWrite(SysDebugLight,false);
					#endif
				#endif
				delay(be);
			}
			delay(pa);
		}
	}
	void System::log(const char* text,int8_t type){
		if(logLC){
			char buf[6],out[8];
			sprintf(buf,"%d",lineCount++);
			Serial.print("[");
			Serial.print(utl.spacer(out,buf,6));
			Serial.print("]");
		}
		if(type>-1){
			const char*marker[5]={"!-","++","--","==","!!"};
			Serial.print("(");
			Serial.print(marker[type]);
			Serial.print(")");
		}
		if(logLC||type>-1)Serial.print(" ");
		Serial.print(text);
		if(logNL)Serial.print("\n");
	}
	bool System::bootInput(){
		return !digitalRead(SysBootInput);
	}
#else
	const bool System::emulation=true;
	void System::lightCrash(uint8_t err){
		std::cout<<"POST-E:"<<err<<"\n";
		while(true)delay(10);
	}
	void System::log(const char* text,int8_t type){
		if(logLC){
			char buf[6],out[8];
			sprintf(buf,"%d",lineCount++);
			std::cout<<"["<<utl.spacer(out,buf,6)<<"]";
		}
		if(type>-1){
			const char*marker[5]={"!-","++","--","==","!!"};
			std::cout<<"("<<marker[type]<<")";
		}
		if(logLC||type>-1)std::cout<<" ";
		std::cout<<text;
		if(logNL)std::cout<<"\n";
	}
	bool System::bootInput(){
		const Uint8*keys=SDL_GetKeyboardState(nullptr);
		return keys[SDL_SCANCODE_ESCAPE];
	}
#endif

void System::begin(){
	delay(1000);
	#if defined(ARDUINO)
		Serial.begin(115200);
	#endif
	logNL=false;
	log("Modev ");
	log(versionName);
	if(prototype)log(" Prototype");
	log("\nVersion ");
	log(versionString);
	log("\n\nWelcome to Modev!\n");
	log("Started log.\n");

	logNL=true;
	log(markerInstruction);
	logLC=true;
	//log("Welcome",2);
}