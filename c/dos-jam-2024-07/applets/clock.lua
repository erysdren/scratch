-- o sweet luna: clock appl

-- spawn(): called once at appl startup
function appl:spawn()
	-- init time value
	self.time = os.date("%X")
end

-- despawn(): called once at appl shutdown
function appl:despawn()
	-- nothing to manually clean up
end

-- think(): called every tick
function appl:think()
	-- update time value
	self.time = os.date("%X")
end

-- draw(): called whenever a redraw is required
function appl:draw(w, h)
	-- draw time string in the bottom right corner of the desktop
	luna.drawstring(self.time, w - #self.time, h - 1)
end
