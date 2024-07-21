local Application = require("application")

local MyApp = Application:new{
	title = "My Application"
}

function MyApp:startup()
	print("MyApp:startup")
end

function MyApp:event(ev)
	Application:event(ev)
end

function MyApp:shutdown()
	print("MyApp:shutdown")
end

MyApp:run()
