local BApplication = require("BApplication")
local BWindow = require("BAlert")
local BButton = require("BButton")
local BMessage = require("BMessage")
local BAlert = require("BAlert")

-- our custom messages
local M_BUTTON_CLICKED = "BCLK"

-- create application
local HelloApp = BApplication:new{signature = "application/x-vnd.HelloApp"}

-- application constructor
function HelloApp:init()
	-- create window
	self.window = BWindow:new(BRect:new(100, 100, 500, 400), "Hello")

	-- create button
	local button = BButton:new(BRect:new(10, 10, 11, 11), "clickme", "Click Me!", BMessage:new(M_BUTTON_CLICKED))
	button:setTarget(self)
	button:resizeToPreferred()

	-- add button to window
	self.window:addChild(button)

	-- show window
	self.window:show()
end

-- fired when the application recieves a message
function HelloApp:recieveMessage(msg)
	if msg.what == M_BUTTON_CLICKED then
		local alert = BAlert:new("Alert", "Hello World!", "Ok")
		alert:run()
	else
		Application:recieveMessage(msg)
	end
end

-- destructor
function HelloApp:quit()
	-- does nothing
end

-- run our application
HelloApp:run()
