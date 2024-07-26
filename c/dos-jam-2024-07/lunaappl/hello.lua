
local val = 0

function appl_init(args)
	print("hello!")
	for i,v in ipairs(args) do
		print(v)
	end
end

function appl_quit()
	print("goodbye!")
end

function appl_tick()
	if val == 0 then
		print("tick!")
		val = 1
	else
		print("tock!")
		val = 0
	end
end
