local Application = {
	title = "",
	signature = ""
}

function Application:new(o)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	return o
end

function Application:startup()

end

function Application:shutdown()

end

function Application:__gc()
	self:shutdown()
end

function Application:event(ev)
	print("Event: \"" .. ev.what .. "\"")
end

function Application:run()
	self:startup()
	self:event{
		what = "hello world"
	}
end

return Application
