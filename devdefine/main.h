#if defined(ARDUINO)
	/*Breadboard device*/
		//#include"DevB4RES3.h"
		//#include"DevB4REC3.h"
		//#include"DevB4REC6.h"

	/*Premade device*/
		/*Has a color issue*/
			#include"DevES3C28P.h"

		/*Has a display issue*/
			//#include"DevJC4827W543.h"
		
		//#include"DevES3C19P.h"







	/*Custom*/
		//#include"DevTEMPL.h"

		#include"DevB4CKUP.h"
#else
	#define DevDefineVersion	1
	#define GfxWidth			480
	#define GfxHeight			272
	#define GfxScale			1
#endif

#define DDVSupport				10
#if defined(DevDefineVersion)&&(DevDefineVersion<DDVSupport)
	#warning"PP: Outdated DDV is fine, but consider updating the device header file if it has any issues."
#endif