
local MSG_BUTTON_CLICKED = "BTNCLK"

local HelloApp = Application:new()

HelloApp.signature = "application/x-vnd.HelloApp"

function HelloApp:Init()
	print("HelloApp starting!")
end

function HelloApp:RecieveMessage(msg)
	if msg.what == MSG_BUTTON_CLICKED then
		print("Button clicked!")
	else
		Application:RecieveMessage(msg)
	end
end

function HelloApp:Quit()
	print("HelloApp shutting down!")
end

return HelloApp
