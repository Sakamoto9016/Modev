/*
_p	pin
_o	option
_v	variable
*/
#if defined(ARDUINO)
	/*Prototype device*/
		#include"device/b4reEsp32C6.h"
//		#include"device/b4reEsp32C3.h"
//		#include"device/b4reEsp32S3.h"
	/*Under development*/
//		#include"device/b4reEsp8266.h"

	/*Premade device*/
		/*Has a color issue*/
//			#include"device/es3c28p.h"

		/*Has a display issue*/
//			#include"device/jc4827w543.h"
		
//		#include"device/es3c19p.h"
	#include"display/default.h"
#else
	#define dd_Version		1
	#define ddgfx_vWidth	160
	#define ddgfx_vHeight	80
	#define ddgfx_vScale	1
#endif