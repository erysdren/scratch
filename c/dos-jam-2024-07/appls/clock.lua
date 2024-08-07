-- o sweet luna: clock appl

function appl:spawn()
	self.time = os.date("%X")
end

function appl:think()
	self.time = os.date("%X")
end

function appl:draw(w, h)
	luna.drawfill(w - #self.time, h - 1, #self.time, 1, 0)
	luna.drawstring(w - #self.time, h - 1, 10, self.time)
end
