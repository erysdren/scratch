-- o sweet luna: hello world appl

function appl:spawn()
	self.hello = "hello world!"
end

function appl:draw(w, h)
	luna.drawfill(15, 4, 4, #self.hello + 2, 3)
	luna.drawstring(self.hello, 0, 5, 5)
end
