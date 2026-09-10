_.manifest={}
dw=gfx.getWidth()
dh=gfx.getHeight()

bg=gfx.getRgb222(0,0,1)
vertical=dw<dh

angleY=0
angleX=0

wasTouching=false

function cube()
	local cx=dw/ 2
	local cy=b+(dh-b)//2
	local size=math.min(dw,dh-b)*1
	local ca=math.cos(angleY)
	local sa=math.sin(angleY)
	local cb=math.cos(angleX)
	local sb=math.sin(angleX)

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

stage=0
ppone=5
snap=16
iter=snap*8
rend={}
send={}
startren=0
getren=0
startpush=0
getpush=0
starttime=0
gettime=0
function BOOT()
	b=fpsMeter()
	gfx.setFlushClip(0,b,dw,dh-b)
	gfx.clear(100)

	if stage==0 then
		local _a="Starting in "..(ppone-sys.getTime()//1000).."..."
		gfx.text(_a,(dw-gfx.getTextWidth(_a))/2,(b+dh-gfx.getFontHeight())/2,0xFFFF)
		if sys.getTime()//1000==ppone then stage=1 starttime=sys.getTime() end
		gfx.flush()
	elseif stage==1 then
		startren=sys.getTime()
		gfx.text(iter,0,b,0xFFFF)
		cube()
		getren=sys.getTime()-startren


		startpush=sys.getTime()
		gfx.flush()
		getpush=sys.getTime()-startpush
		if iter%snap==0 then
			rend[#rend+1]=getren
			send[#send+1]=getpush
		end
		iter=iter-1
		if iter<=0 then
			stage=2
			gettime=sys.getTime()-starttime
			getren=0
			for i=1,#rend do
				getren=getren+rend[i]
			end
			getren=getren/#rend
			getpush=0
			for i=1,#send do
				getpush=getpush+send[i]
			end
			getpush=getpush/#send
		end
	else
		local _a="Time: "..(gettime/1000).."s\nRend Avg: "..getren.."ms\nSend Avg: "..getpush.."ms"
		gfx.text(_a,4,b+4,0xFFFF)
		if sys.getTime()//1000==ppone then stage=1 end
		gfx.flush()
	end
end