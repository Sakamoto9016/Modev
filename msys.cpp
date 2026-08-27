#include"main.h"

System sys;

constexpr char*markerInstruction=R"(
Markers:
(!-) Note
(++) Started
(--) Success
(==) Failed
(!!) Warning
)";
//0~4
uint16_t lineCount=0;

#ifdef ARDUINO
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
				#if defined(dd_DebugLight)
					#if defined(GfxInvertedBacklight)
						digitalWrite(dd_DebugLight,false);
					#else
						digitalWrite(dd_DebugLight,true);
					#endif
					bool bit=(err>>i)&1;
					delay(bit?hi:lo);
					#if defined(GfxInvertedBacklight)
						digitalWrite(dd_DebugLight,true);
					#else
						digitalWrite(dd_DebugLight,false);
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
		return !digitalRead(dd_BootInput);
	}
#else
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
		const uint8_t*keys=SDL_GetKeyboardState(nullptr);
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
	log(m_VersionName);
	if(m_UnderConstruction)log(" Prototype");
	log("\nVersion ");
	log(m_VersionString);
	log("\n\nWelcome to Modev!\n");
	log("Started log.\n");

	logNL=true;
	log(markerInstruction);
	logLC=true;
	//log("Welcome",2);
}