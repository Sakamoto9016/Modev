f.manifest={}
dw=gfx.getWidth()
dh=gfx.getHeight()

bg=gfx.getRgb222(0,0,1)
vertical=dw<dh
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
		
	gfx.flush()
end