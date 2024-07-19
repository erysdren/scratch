
local GreetThemCmd = 100

function TApplication:greetingBox()
	local d = TDialog.new(TRect.new(25, 5, 55, 16), "Hello, World!")
	d:insert(TStaticText.new(TRect.new(3, 5, 15, 6), "How are you?"));
	d:insert(TButton.new(TRect.new(16, 2, 28, 4), "Terrific", tv.cm.Cancel, tv.bf.Normal));
	d:insert(TButton.new(TRect.new(16, 4, 28, 6), "Ok", tv.cm.Cancel, tv.bf.Normal));
	d:insert(TButton.new(TRect.new(16, 6, 28, 8), "Lousy", tv.cm.Cancel, tv.bf.Normal));
	d:insert(TButton.new(TRect.new(16, 8, 28, 10), "Cancel", tv.cm.Cancel, tv.bf.Normal));
	self.deskTop.execView(d);
end

function TApplication:initStatusLine(r)
	r.a.y = r.b.y - 1
	local items = {}
	table.insert(items, tv.statusItem("~Alt-X~ Exit", tv.kb.AltX, tv.cm.Quit))
	table.insert(items, tv.statusItem(nil, tv.kb.F10, tv.cm.Menu))
	local def = tv.statusDef(0, 0xFFFF, items)
	return tv.statusLine(r, def)
end

function TApplication:initMenuBar(r)
	r.b.y = r.a.y + 1
	local items = {}
	table.insert(items, TMenuItem.new("~G~reeting...", GreetThemCmd, tv.kb.AltG))
	table.insert(items, TNewLine.new())
	table.insert(items, TMenuItem.new("E~x~it", tv.cm.Quit, tv.cm.Quit, tv.hc.NoContext, "Alt-X"))
	local submenu = TSubMenu.new("~H~ello", tv.kb.AltH, items)
	return TMenuBar.new(r, submenu)
end

function TApplication:handleEvent(ev)
	if ev.what == tv.ev.Command then
		if ev.message.command == GreetThemCmd then
			greetingBox()
			tv.clearEvent(ev)
		end
	end
end
