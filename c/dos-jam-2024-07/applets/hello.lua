-- o sweet luna: hello world example appl

function appl:spawn()
	self.grabbed = false
	return 0
end

function appl:event(event)
	if event.type == "mouse" then
		if event.mouse.button > 0 then
			self.grabbed = true
		else
			self.grabbed = false
		end
	end
	return 0
end

function appl:despawn()

end
