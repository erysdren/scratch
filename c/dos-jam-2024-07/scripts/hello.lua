local Application = require("Application")
local Window = require("Window")
local Rect = require("Rect")
local Button = require("Button")
local MessageBox = require("MessageBox")

-- create our application
local HelloApp = Application:new()

-- our custom events
local EV_BUTTON_CLICKED = "EVBTNCLK"

-- called once at application startup
function HelloApp:init()
	-- create window
	self.window = Window:new{
		-- position and size of window
		frame=Rect:new(2, 2, 24, 16),
		-- title of window
		title="Hello World"
	}
	-- create button
	local button = Button:new{
		-- identiifer of button
		id="clickme",
		-- position and size of button
		frame=Rect:new(0, 0, 20, 1),
		-- text on the button
		title="Click me!",
		-- event to fire when the button is pressed
		event=EV_BUTTON_CLICKED
	}
	-- place button into the window
	self.window:addChild(button)
end

-- called whenever the application recieves an event
function HelloApp:event(ev)
	if ev.what == EV_BUTTON_CLICKED then
		local alert = MessageBox:new("Hello World!", "Ok")
	else
		-- defer to main application class
		Application:event(ev)
	end
end

-- called at application shutdown
function HelloApp:quit()
	-- no manual cleanup needed in this application
end

-- run our application
HelloApp:run()
