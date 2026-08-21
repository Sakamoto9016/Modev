#ifdef ARDUINO
	#ifdef TouchModuleCST816
		#include <CST816S.h>
	#elifdef TouchModuleFT6336G
		#include <FT6336U.h>
	#endif
#endif