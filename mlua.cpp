#include"main.h"
Moon lua;
lua_State*Moon::L=luaL_newstate();

const luaL_Reg
	Moon::fnclib[]={
		{"a0",Moon::func::a0},
		{"aa0",Moon::func::aa0},{"aa1",Moon::func::aa1},{"aa2",Moon::func::aa2},
		{"aaa0",Moon::func::aaa0},{"aaa1",Moon::func::aaa1},{"aaa2",Moon::func::aaa2},
		{"aab0",Moon::func::aab0},{"aab1",Moon::func::aab1},{"aab2",Moon::func::aab2},{"aab3",Moon::func::aab3},
		{"ab0",Moon::func::ab0},{"ab1",Moon::func::ab1},{"ab2",Moon::func::ab2},
		{"ac0",Moon::func::ac0},
		{"aca0",Moon::func::aca0},{"aca1",Moon::func::aca1},
		{"acb0",Moon::func::acb0},{"acb1",Moon::func::acb1},
		{"b0",Moon::func::b0},{"b1",Moon::func::b1},{"b2",Moon::func::b2},{"b3",Moon::func::b3},
		{"ba0",Moon::func::ba0},{"ba1",Moon::func::ba1},{"ba2",Moon::func::ba2},
		{"bba0",Moon::func::bba0},{"bba1",Moon::func::bba1},
		{"bbb0",Moon::func::bbb0},{"bbb1",Moon::func::bbb1},
		{"bc0",Moon::func::bc0},{"bc1",Moon::func::bc1},
		{"bd0",Moon::func::bd0},{"bd1",Moon::func::bd1},{"bd2",Moon::func::bd2},
		{"be0",Moon::func::be0},{"be1",Moon::func::be1},
		{"bf0",Moon::func::bf0},{"bf1",Moon::func::bf1},{"bf2",Moon::func::bf2},
		{"bfa0",Moon::func::bfa0},{"bfa1",Moon::func::bfa1},{"bfa2",Moon::func::bfa2},
		{"bg0",Moon::func::bg0},{"bg1",Moon::func::bg1},{"bg2",Moon::func::bg2},{"bg3",Moon::func::bg3},{"bg4",Moon::func::bg4},
		{"bh0",Moon::func::bh0},{"bh1",Moon::func::bh1},{"bh2",Moon::func::bh2},
		{"bha0",Moon::func::bha0},{"bha1",Moon::func::bha1},{"bha2",Moon::func::bha2},
		{"bhb0",Moon::func::bhb0},{"bhb1",Moon::func::bhb1},{"bhb2",Moon::func::bhb2},
		{"bi0",Moon::func::bi0},{"bi1",Moon::func::bi1},
		{"bj0",Moon::func::bj0},{"bj1",Moon::func::bj1},
		{"bk0",Moon::func::bk0},{"bk1",Moon::func::bk1},
		{"bl0",Moon::func::bl0},{"bl1",Moon::func::bl1},{"bl2",Moon::func::bl2},{"bl3",Moon::func::bl3},{"bl4",Moon::func::bl4},
		{"bla0",Moon::func::bla0},{"bla1",Moon::func::bla1},{"bla2",Moon::func::bla2},
		{"blb0",Moon::func::blb0},{"blb1",Moon::func::blb1},
		{"blm0",Moon::func::blm0},{"blm1",Moon::func::blm1},{"blm2",Moon::func::blm2},{"blm3",Moon::func::blm3},{"blm4",Moon::func::blm4},{"blm5",Moon::func::blm5},{"blm6",Moon::func::blm6},{"blm7",Moon::func::blm7},{"blm8",Moon::func::blm8},
		{"c0",Moon::func::c0},
		{"ca0",Moon::func::ca0},{"ca1",Moon::func::ca1},{"ca2",Moon::func::ca2},
		{"caa0",Moon::func::caa0},{"caa1",Moon::func::caa1},		
		{"zer0",Moon::func::zer0},{NULL,NULL}
	},
	Moon::syslib[]={
		{"getBootInput",Moon::func::a0},
		{"getScriptSize",Moon::func::aa0},
		{"isProto",Moon::func::aa1},
		{"isEmu",Moon::func::aa2},
		{"getVerValue",Moon::func::aaa0},
		{"getVerString",Moon::func::aaa1},
		{"getVerName",Moon::func::aaa2},
		{"getDistVerValue",Moon::func::aab0},
		{"getDistVerString",Moon::func::aab1},
		{"getDistVerName",Moon::func::aab2},
		{"getDistName",Moon::func::aab3},
		{"getTime",Moon::func::ab0},
		{"getBootTime",Moon::func::ab1},
		{"getUnixTime",Moon::func::ab2},
		{"log",Moon::func::ac0},
		{"getLogNewlineState",Moon::func::aca0},
		{"setLogNewlineState",Moon::func::aca1},
		{"getLogLinenumState",Moon::func::acb0},
		{"setLogLinenumState",Moon::func::acb1},
		{NULL,NULL}
	},
	Moon::gfxlib[]={
		{"flush",Moon::func::b0},
		{"antiBurn",Moon::func::b1},
		{"getFps",Moon::func::b2},
		{"getBlend",Moon::func::b3},
		{"getWidth",Moon::func::ba0},
		{"getHeight",Moon::func::ba1},
		{"getSize",Moon::func::ba2},
		{"setBufClip",Moon::func::bba0},
		{"cancelBufClip",Moon::func::bba1},
		{"setFlushClip",Moon::func::bbb0},
		{"cancelFlushClip",Moon::func::bbb1},
		{"getBrightness",Moon::func::bc0},
		{"setBrightness",Moon::func::bc1},
		{"getRgb565",Moon::func::bd0},
		{"getRgb111",Moon::func::bd1},
		{"getRgb222",Moon::func::bd2},
		{"getPixel",Moon::func::be0},
		{"setPixel",Moon::func::be1},
		{"clear",Moon::func::bf0},
		{"clearQuick",Moon::func::bf1},
		{"clearDither",Moon::func::bf2},
		{"clearGrad",Moon::func::bfa0},
		{"clearGradVert",Moon::func::bfa1},
		{"clearGradHori",Moon::func::bfa2},
		{"line",Moon::func::bg0},
		{"lineVert",Moon::func::bg1},
		{"lineHori",Moon::func::bg2},
		{"lineDash",Moon::func::bg3},
		{"lineEdge",Moon::func::bg4},
		{"rectFrame",Moon::func::bh0},
		{"rectSolid",Moon::func::bh1},
		{"rectDither",Moon::func::bh2},
		{"rectEmboss",Moon::func::bha0},
		{"rectProgress",Moon::func::bha1},
		{"rectLoading",Moon::func::bha2},
		{"rectGrad",Moon::func::bhb0},
		{"rectGradVert",Moon::func::bhb1},
		{"rectGradHori",Moon::func::bhb2},
		{"circFrame",Moon::func::bi0},
		{"circSolid",Moon::func::bi1},
		{"elipFrame",Moon::func::bj0},
		{"elipSolid",Moon::func::bj1},
		{"triFrame",Moon::func::bk0},
		{"triSolid",Moon::func::bk1},
		{"getFont",Moon::func::bl0},
		{"setFont",Moon::func::bl1},
		{"getFontIndex",Moon::func::bl2},
		{"setFontIndex",Moon::func::bl3},
		{"getFontCount",Moon::func::bl4},
		{"getFontWidth",Moon::func::bla0},
		{"getFontHeight",Moon::func::bla1},
		{"getTextWidth",Moon::func::bla2},
		{"glyph",Moon::func::blb0},
		{"text",Moon::func::blb1},
		{"renderImage",Moon::func::blm0},
		{"setImageGraytone",Moon::func::blm1},
		{"setImageRGBA",Moon::func::blm2},
		{"setImageGA",Moon::func::blm3},
		{"setImageCropPos",Moon::func::blm4},
		{"setImageCropSize",Moon::func::blm5},
		{"setImageData",Moon::func::blm6},
		{"getImageWidth",Moon::func::blm7},
		{"getImageHeight",Moon::func::blm8},
		{NULL,NULL}
	},
	Moon::nonlib[]={
		{"dummy",Moon::func::zer0},
		{"getNull",Moon::func::zer0},
		{"setNull",Moon::func::zer0},
		{"null",Moon::func::zer0},
		{"iDontKnowWhatInTheFuckingShitHappenedHere",Moon::func::zer0},
		{NULL,NULL}
	},
	Moon::inplib[]={
		{"isTouchSupported",Moon::func::c0},
		{"isTouchActive",Moon::func::ca0},
		{"getTouchXPos",Moon::func::ca1},
		{"getTouchYPos",Moon::func::ca2},
		{"isTouchEnabled",Moon::func::caa0},
		{"setTouchEnable",Moon::func::caa1},
		{NULL,NULL}
	};
bool Moon::begin(char*err){
	if(L!=nullptr){lua_close(L);L=nullptr;}
	L=luaL_newstate();
	luaL_openlibs(L);
	const luaL_Reg *libs[]={
		fnclib,syslib,gfxlib,nonlib,inplib
	};
	const char *libname[]={
		"_","sys","gfx","non","inp"
	};

	constexpr uint8_t libcount=sizeof(libs)/sizeof(libs[0]);
	for(uint8_t i=0;i<libcount;i++){
		luaL_newlib(L,libs[i]);
		lua_setglobal(L,libname[i]);
	}

	strcat(boot,"\nif type(BOOT)~=\"function\"then error(\"Where is BOOT()? No BOOT(), no runtime. GRRRRR.\")end");
	bool e=false;
	if(luaL_dostring(L,(const char*)boot)!=LUA_OK){
		err;
		sprintf(err,"%s",lua_tostring(L,-1));
		sys.log(err,3);
		e=true;
		lua_pop(L,1);
	}
	return e;
}

bool Moon::tick(char*err){
	bool e=false;
	lua_getglobal(L,"BOOT");
	if(lua_isfunction(L,-1)){
		if(lua_pcall(L,0,0,0)!=LUA_OK){
			err;
			sprintf(err,"%s",lua_tostring(L,-1));
			sys.log(err,3);
			e=true;
			lua_pop(L,1);
		}
	}else lua_pop(L,1);
	return e;
}