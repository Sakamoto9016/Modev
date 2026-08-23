#include"main.h"
#include"modevSplash.h"

char boot[ScriptSize]PROGMEM=R"(
	f.manifest={}
	dw=gfx.getWidth()
	dh=gfx.getHeight()
	
	bg=gfx.getRgb222(0,0,1)
	vertical=dw<dh
	
	angleY=0
	angleX=0
	
	touchSupported=inp.isTouchSupported()
	wasTouching=false
	
	function cube()
		local cx = dw // 2
		local cy = b + (dh - b) // 2
		local size = math.min(dw,dh-b) * 1
	
		local ca = math.cos(angleY)
		local sa = math.sin(angleY)
	
		local cb = math.cos(angleX)
		local sb = math.sin(angleX)
	
		-- cube vertices
		local v = {
			{-1,-1,-1}, {1,-1,-1},
			{1, 1,-1}, {-1, 1,-1},
			{-1,-1, 1}, {1,-1, 1},
			{1, 1, 1}, {-1, 1, 1}
		}
	
		local p = {}
	
		for i=1,8 do
			local x,y,z = v[i][1],v[i][2],v[i][3]
	
			-- rotate around Y
			local x1 = x * ca - z * sa
			local z1 = x * sa + z * ca
	
			-- rotate around X
			local y1 = y * cb - z1 * sb
			local z2 = y * sb + z1 * cb
	
			-- perspective projection
			local distance = 4
			local depth = distance + z2
			local scale = size / depth
	
			p[i] = {
				cx + x1 * scale,
				cy + y1 * scale
			}
		end
	
		local edges = {
			{1,2},{2,3},{3,4},{4,1},
			{5,6},{6,7},{7,8},{8,5},
			{1,5},{2,6},{3,7},{4,8}
		}
	
		for i=1,#edges do
			local a = p[edges[i][1]]
			local c = p[edges[i][2]]
	
			gfx.line(
				math.floor(a[1]),
				math.floor(a[2]),
				math.floor(c[1]),
				math.floor(c[2]),
				0xFFFF
			)
		end
	
		-- Only automatically rotate when touchscreen isn't being used
		if not (touchSupported and inp.isTouchActive()) then
			angleY = angleY + 0.035
			angleX = angleX + 0.0245
		end
	end
	
	function fpsMeter()
		fps=gfx.getFps()
	
		fh=gfx.getFontHeight()
		lh=12
		ls=4
		lst=5
		b=fh+lh
		gfx.setFlushClip(0,0,dw,b)
		gfx.clear(bg)
	
		strr=math.floor(fps).."fps"
		fw=gfx.getTextWidth(strr)
		cc=dw//2
		gfx.text(strr,(dw-fw)//2,0,0xFFFF)
		
		gfx.rectSolid(cc-1,fh,3,lh,gfx.getRgb222(1,1,1))
	
		range=100
		for i=0,range do
			x=cc+(i-fps)*lst
			l=ls
			co=0xFFFF
			q=i
			if q<10 then
				co=gfx.getRgb222(4,0,0)
			elseif q<20 then
				co=gfx.getRgb222(4,2,0)
			elseif q<40 then
				co=gfx.getRgb222(4,4,0)
			elseif q<50 then
				co=gfx.getRgb222(2,4,0)
			elseif q<80 then
				co=gfx.getRgb222(0,4,0)
			elseif q<=100 then
				co=gfx.getRgb222(0,4,2)
			end
			if i%10==0 then l=lh end
			if not(x<0 or x>dw) then
				gfx.lineVert(x,fh,l,co)
			end
		end
		gfx.flush()
		return b
	end
	
	function BOOT()
		gfx.flush()
		b=fpsMeter()
		gfx.setFlushClip(0,b,dw,dh-b)
		gfx.clear(100)
	
		-- Touch controls rotation
		if touchSupported and inp.isTouchActive() then
			local tx=-inp.getTouchXPos()
			local ty=inp.getTouchYPos()
	
			-- Map screen position to rotation angles
			angleY=(tx/dw)*math.pi*2
			angleX=(ty/dh)*math.pi*2
		end
	
		cube()
	
		local colors = {
			{4,0,0}, {4,1,0}, {4,2,0}, {4,3,0}, {4,4,0},
			{3,4,0}, {2,4,0}, {1,4,0}, {0,4,0},
			{0,4,1}, {0,4,2}, {0,4,3}, {0,4,4},
			{0,3,4}, {0,2,4}, {0,1,4}, {0,0,4}
		}
		
		for i, c in ipairs(colors) do
			gfx.rectSolid((i-1)*2,b,2,10,gfx.getRgb222(c[1],c[2],c[3]))
		end
		gfx.flush()
	end
)";
char erno[1024];
bool err=false;
void error(){
	gfx.clip();
	gfx.clipView();
	size_t len=strlen(erno);
	gfx.setFont("6x10");
	uint8_t
		fw=gfx.getFontWidth(),
		fh=gfx.getFontHeight();
	uint16_t ww=gfx.width/fw;
	for(uint16_t i=0;i<len;i++){
		uint16_t
			x=(i%ww)*fw,
			y=(i/ww)*fh;
			gfx.rectFill(x,y,fw,fh,0);
			gfx.glyph(erno[i],x,y,gfx.getRgb111(1,0,0));
	}
	gfx.flush();
}
void setup(){
	sys.begin();
	gfx.begin();
	inp.begin();
	gfx.clearQuick(0);
	gfx.setBrightness(0);
	splashDraw();
	for(int i=0;i<15;i++){
		gfx.setBrightness((i+1)*16-1);
		delay(100);
	}
	err=lua.begin(erno);
	sys.bootTime=millis();
}
void loop(){
	inp.tick();
	sys.elapTime=millis()-sys.bootTime;
	if(err)error();
	else err=lua.tick(erno);
}