
local GreetThemCmd = 100

function greetingBox()
	local d = tv.dialog(tv.rect(25, 5, 55, 16), "Hello, World!")
	d.insert(tv.staticText(tv.rect(3, 5, 15, 6), "How are you?"));
	d.insert(tv.button(tv.rect(16, 2, 28, 4), "Terrific", tv.cm.Cancel, tv.bf.Normal));
	d.insert(tv.button(tv.rect(16, 4, 28, 6), "Ok", tv.cm.Cancel, tv.bf.Normal));
	d.insert(tv.button(tv.rect(16, 6, 28, 8), "Lousy", tv.cm.Cancel, tv.bf.Normal));
	d.insert(tv.button(tv.rect(16, 8, 28, 10), "Cancel", tv.cm.Cancel, tv.bf.Normal));
	tv.deskTop.execView(d);
end

function tv.initStatusLine(r)
	r.a.y = r.b.y - 1
	local items = {}
	table.insert(items, tv.statusItem("~Alt-X~ Exit", tv.kb.AltX, tv.cm.Quit))
	table.insert(items, tv.statusItem(nil, tv.kb.F10, tv.cm.Menu))
	local def = tv.statusDef(0, 0xFFFF, items)
	return tv.statusLine(r, def)
end

function tv.initMenuBar(r)
	r.b.y = r.a.y + 1
	local items = {}
	table.insert(items, tv.menuItem("~G~reeting...", GreetThemCmd, tv.kb.AltG))
	table.insert(items, tv.newLine())
	table.insert(items, tv.menuItem("E~x~it", tv.cm.Quit, tv.cm.Quit, tv.hc.NoContext, "Alt-X"))
	local submenu = tv.subMenu("~H~ello", tv.kb.AltH, items)
	return tv.menuBar(r, submenu)
end

function tv.handleEvent(ev)
	if ev.what == tv.ev.Command then
		if ev.message.command == GreetThemCmd then
			greetingBox()
			tv.clearEvent(ev)
		end
	end
end
