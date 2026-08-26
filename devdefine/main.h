#if defined(ARDUINO)
	/*Prototype device*/
		#include"DevB4RES3.h"
		//#include"DevB4REC3.h"
		//#include"DevB4REC6.h"
		/*Under development*/
			//#include"DevB4RE82.h"

	/*Premade device*/
		/*Has a color issue*/
			//#include"DevES3C28P.h"

		/*Has a display issue*/
			//#include"DevJC4827W543.h"
		
		//#include"DevES3C19P.h"



	/*Custom*/
		//#include"DevTEMPL.h"

	#include"DevB4CKUP.h"
#else
	#define dd_Version		1
	#define dd_GfxWidth		160
	#define dd_GfxHeight	80
	#define dd_GfxScale		1
#endif

#define dd_VerTarget		10
#if defined(dd_Version)&&(dd_Version<dd_VerTarget)
	#warning"PP: Outdated DevDefine is fine, but consider updating the device header file if it has any issues."
#endif