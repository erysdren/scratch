-- o sweet luna: hello world appl

function appl:spawn()
	self.hello = "test1a"
end

function appl:draw(w, h)
	luna.drawfill(0, 0, #self.hello + 2, 3, 14)
	luna.drawstring(1, 1, 0, self.hello)
end
