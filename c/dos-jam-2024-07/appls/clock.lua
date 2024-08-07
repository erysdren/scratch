-- o sweet luna: clock appl

function appl:spawn()
	self.time = os.date("%X")
end

function appl:think()
	self.time = os.date("%X")
end

function appl:draw(w, h)
	luna.drawfill(0, w - #self.time, h - 1, #self.time, 1)
	luna.drawstring(self.time, 10, w - #self.time, h - 1)
end
