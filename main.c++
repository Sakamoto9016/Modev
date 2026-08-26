/*
Compile:
	g++ lua/*.o *.cpp  main.c++ -lSDL2 -o modev -w
Execute:
	./modev
*/
#include"main.h"

uint32_t millis(){return SDL_GetTicks();}
void delay(uint32_t ms){SDL_Delay(ms);}
long random(long max){return std::rand()%max;}
long random(long min,long max){return min+std::rand()%(max-min);}

#include <fstream>
#include <filesystem>
namespace fs=std::filesystem;
fs::file_time_type bootFileTime;
bool bootFileTracked=false;
bool update(){
	if(!fs::exists("boot.lua"))return false;
	std::ifstream file("boot.lua",std::ios::binary);
	if(!file)return false;
	file.read(boot,m_ScriptSize-1);
	size_t len=file.gcount();
	boot[len]='\0';
	bootFileTime=fs::last_write_time("boot.lua");
	bootFileTracked=true;
	return true;
}
bool changed(){
	if(!fs::exists("boot.lua"))return false;
	auto time=fs::last_write_time("boot.lua");
	if(!bootFileTracked){
		bootFileTime=time;
		bootFileTracked=true;
		return false;
    }
	return time!=bootFileTime;
}
void reload(){
	if(fs::exists("boot.lua")){if(!update())return;}
	err=lua.begin(erno);
	if(!err)sys.bootTime=millis();
}
int main(int argc,char** argv){
	if(argc>1){
		int w,h;
		if(sscanf(argv[1],"%dx%d",&w,&h)==2&&w>0&&h>0){
			gfx.width=w;
			gfx.height=h;
		}
	}
	setup();
	bool running=true;
	while(running){
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type==SDL_QUIT)running=false;
			if(e.type==SDL_KEYDOWN&&e.key.keysym.sym==SDLK_F12){reload();}
		}
		if(changed())reload();
		loop();
		int winW,winH;
		SDL_GetWindowSize(window, &winW, &winH);
		int scaleX=winW/gfx.width;
		int scaleY=winH/gfx.height;
		int scale=std::max(1,std::min(scaleX, scaleY));
		int dstW=gfx.width*scale;
		int dstH=gfx.height*scale;
		SDL_Rect dst={(winW-dstW)/2,(winH-dstH)/2,dstW,dstH};
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer,texture,nullptr,&dst);
		SDL_RenderPresent(renderer);
	}
	return 0;
}