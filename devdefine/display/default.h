// These will help replace for those is required
#define ddgfx_pNone GFX_NOT_DEFINED

#ifndef ddgfx_pCommand
	#define ddgfx_pCommand		ddgfx_pNone
#endif
#ifndef ddgfx_pSelect
	#define ddgfx_pSelect		ddgfx_pNone
#endif
#ifndef ddgfx_pClock
	#define ddgfx_pClock		ddgfx_pNone
#endif
#ifndef ddgfx_pWrite
	#define ddgfx_pWrite		ddgfx_pNone
#endif
#ifndef ddgfx_pRead
	#define ddgfx_pRead			ddgfx_pNone
#endif
#ifndef ddgfx_pData0
	#define ddgfx_pData0		ddgfx_pNone
#endif
#ifndef ddgfx_pData1
	#define ddgfx_pData1		ddgfx_pNone
#endif
#ifndef ddgfx_pData2
	#define ddgfx_pData2		ddgfx_pNone
#endif
#ifndef ddgfx_pData3
	#define ddgfx_pData3		ddgfx_pNone
#endif
#ifndef ddgfx_pReset
	#define ddgfx_pReset		ddgfx_pNone
#endif
#ifdef ddgfx_oIps
	#undef ddgfx_oIps
	#define ddgfx_oIps			true
#ifndef ddgfx_oIps
	#define ddgfx_oIps			false
#endif
#ifndef ddgfx_vRotate
	#define ddgfx_vRotate		0
#endif
#ifndef ddgfx_vShiftX
	#define ddgfx_vShiftX		0
#endif
#ifndef ddgfx_vShiftY
	#define ddgfx_vShiftY		0
#endif
#ifndef ddgfx_vSpeed
	#define ddgfx_vSpeed		40000000UL
#endif
#ifndef ddgfx_oSwap
	#define ddgfx_oSwap			false
#endif