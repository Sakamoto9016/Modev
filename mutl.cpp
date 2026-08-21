#include "main.h"

Utility utl;

char*Utility::spacer(char*out,const char*text,uint8_t size,bool left){
	size_t len=strlen(text);
	if(len>size)len=size;
	memset(out,' ',size);
	out[size]='\0';
	if(left)memcpy(out,text,len);
	else memcpy(out+(size-len),text,len);
	return out;
}