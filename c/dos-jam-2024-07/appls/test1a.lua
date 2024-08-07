-- o sweet luna: hello world appl

function appl:spawn()
	self.hello = "test1a"
end

function appl:draw(w, h)
	luna.drawfill(14, 3, 3, #self.hello + 2, 3)
	luna.drawstring(self.hello, 0, 4, 4)
end
