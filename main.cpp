#include"main.h"
#include"modevSplash.h"

char boot[ScriptSize]PROGMEM=R"(
	f.manifest={}
	dw=gfx.getWidth()
	dh=gfx.getHeight()
	
	bg=gfx.getRgb222(0,0,1)
	vertical=dw<dh
	function BOOT()
		fps=gfx.getFps()
		fpsc=60
	
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
				gfx.lineVert(x//1,fh,l,co)
			end
		end
		gfx.flush()
	
		gfx.setFlushClip(0,b,dw,dh-b)
			gfx.clear(100)
			-- rotating reflective cube benchmark
	
			cubeAngle=cubeAngle or 0
			cubeAngle=cubeAngle+0.035
			
			cx=dw/2
			cy=b+((dh-b)/2)
			
			size=math.min(dw,dh-b)*0.32
			
			-- RGB565 helpers
			function rgb565(r,g,bl)
				return ((r>>3)<<11)|((g>>2)<<5)|(bl>>3)
			end
			
			function unpack565(c)
				return (c>>11)&31,(c>>5)&63,c&31
			end
			
			function shade565(c,s)
				local r,g,bl=unpack565(c)
				r=math.floor(r*s)
				g=math.floor(g*s)
				bl=math.floor(bl*s)
				return (r<<11)|(g<<5)|bl
			end
			
			-- 3D rotation
			function rot(x,y,z)
				local cy=math.cos(cubeAngle)
				local sy=math.sin(cubeAngle)
				local cxr=math.cos(cubeAngle*0.73)
				local sxr=math.sin(cubeAngle*0.73)
			
				-- Y rotation
				local xx=x*cy-z*sy
				local zz=x*sy+z*cy
			
				-- X rotation
				local yy=y*cxr-zz*sxr
				zz=y*sxr+zz*cxr
			
				return xx,yy,zz
			end
			
			-- Perspective projection
			function project(x,y,z)
				local d=4.0
				local p=d/(d-z)
			
				return cx+x*size*p,
					cy+y*size*p,
					z
			end
			
			-- Cube vertices
			verts={
				{-1,-1,-1},
				{ 1,-1,-1},
				{ 1, 1,-1},
				{-1, 1,-1},
				{-1,-1, 1},
				{ 1,-1, 1},
				{ 1, 1, 1},
				{-1, 1, 1}
			}
			
			pv={}
			
			for i=1,8 do
				local x,y,z=rot(verts[i][1],verts[i][2],verts[i][3])
				local sx,sy,sz=project(x,y,z)
				pv[i]={sx,sy,sz}
			end
			
			-- Triangle rasterizer
			function triangle(v1,v2,v3,baseColor)
				local minx=math.floor(math.min(v1[1],v2[1],v3[1]))
				local maxx=math.floor(math.max(v1[1],v2[1],v3[1]))
				local miny=math.floor(math.min(v1[2],v2[2],v3[2]))
				local maxy=math.floor(math.max(v1[2],v2[2],v3[2]))
			
				if minx<0 then minx=0 end
				if maxx>=dw then maxx=dw-1 end
				if miny<b then miny=b end
				if maxy>=dh then maxy=dh-1 end
			
				local ax,ay=v1[1],v1[2]
				local bx,by=v2[1],v2[2]
				local cx2,cy2=v3[1],v3[2]
			
				local den=(by-cy2)*(ax-cx2)+(cx2-bx)*(ay-cy2)
				if den==0 then return end
			
				for y=miny,maxy do
					for x=minx,maxx do
						local w1=((by-cy2)*(x-cx2)+(cx2-bx)*(y-cy2))/den
						local w2=((cy2-ay)*(x-cx2)+(ax-cx2)*(y-cy2))/den
						local w3=1-w1-w2
			
						if w1>=0 and w2>=0 and w3>=0 then
							local rx=math.floor(cx-(x-cx)*0.35)
							local ry=math.floor(cy-(y-cy)*0.35)
			
							local reflected
			
							if rx>=0 and rx<dw and ry>=b and ry<dh then
								reflected=gfx.getPixel(rx,ry)
							else
								reflected=baseColor
							end
			
							local r1,g1,b1=unpack565(reflected)
							local r2,g2,b2=unpack565(baseColor)
			
							local r=math.floor(r1*0.55+r2*0.45)
							local g=math.floor(g1*0.55+g2*0.45)
							local bl=math.floor(b1*0.55+b2*0.45)
			
							local spec=math.sin(x*0.035+y*0.021+cubeAngle*5)
			
							if spec>0.82 then
								local k=(spec-0.82)/0.18
								r=math.min(31,r+math.floor(k*18))
								g=math.min(63,g+math.floor(k*28))
								bl=math.min(31,bl+math.floor(k*18))
							end
			
							gfx.setPixel(x,y,(r<<11)|(g<<5)|bl)
						end
					end
				end
			end
			
			-- Faces.
			-- Back faces are intentionally rendered first.
			triangle(pv[1],pv[2],pv[3],0x39E7)
			triangle(pv[1],pv[3],pv[4],0x39E7)
			
			triangle(pv[5],pv[8],pv[7],0x7BEF)
			triangle(pv[5],pv[7],pv[6],0x7BEF)
			
			triangle(pv[1],pv[5],pv[6],0x4210)
			triangle(pv[1],pv[6],pv[2],0x4210)
			
			triangle(pv[2],pv[6],pv[7],0x6318)
			triangle(pv[2],pv[7],pv[3],0x6318)
			
			triangle(pv[3],pv[7],pv[8],0x5294)
			triangle(pv[3],pv[8],pv[4],0x5294)
			
			triangle(pv[4],pv[8],pv[5],0x2945)
			triangle(pv[4],pv[5],pv[1],0x2945)	gfx.flush()
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