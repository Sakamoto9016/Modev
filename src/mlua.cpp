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