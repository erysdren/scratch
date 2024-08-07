-- o sweet luna: hello world appl

function appl:spawn()
	self.hello = "hello world!"
end

function appl:draw(w, h)
	luna.drawfill(0, 0, w, h, 15)
	luna.drawstring(1, 1, 0, self.hello)
end
