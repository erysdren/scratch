/*
 * Copyright (c) 1994 by Borland International
 * All Rights Reserved.
 */

#include <string>

#define Uses_TKeys
#define Uses_TApplication
#define Uses_TEvent
#define Uses_TRect
#define Uses_TDialog
#define Uses_TStaticText
#define Uses_TButton
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TStatusLine
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TDeskTop
#define Uses_MsgBox
#define Uses_TFileDialog
#include <tvision/tv.h>

#include <sol/sol.hpp>

#include "tvlua.h"

enum {
	cmRun = 100
};

ushort L_messageBox(std::string msg, ushort options)
{
	return messageBox(msg, options);
}

class TScriptApp : public TApplication
{
public:
	TScriptApp();

	virtual void handleEvent(TEvent &event);
	static TMenuBar *initMenuBar(TRect);
	static TStatusLine *initStatusLine(TRect);

	void openScript();
	void runScript();

private:
	sol::state lua;
	sol::load_result program;
};

TScriptApp::TScriptApp() : TProgInit(&TScriptApp::initStatusLine, &TScriptApp::initMenuBar, &TScriptApp::initDeskTop)
{
	lua.open_libraries(sol::lib::base, sol::lib::table, sol::lib::string);

	registerTurboTypes(lua);
}

void TScriptApp::openScript()
{
	char fileName[MAXPATH];
	strcpy(fileName, "*.lua");

	if (executeDialog(new TFileDialog("*.lua", "Open script", "~N~ame", fdOpenButton, 100), fileName) != cmCancel)
	{
		program = lua.load_file(fileName);
		if (!program.valid())
		{
			messageBox("Script failed to load", mfOKButton);
		}
		else
		{
			if (messageBox("Run script now?", mfYesButton | mfNoButton | mfConfirmation) == cmYes)
				runScript();
		}
	}
}

void TScriptApp::runScript()
{
	program();
}

void TScriptApp::handleEvent(TEvent &event)
{
	TApplication::handleEvent(event);

	if (event.what == evCommand)
	{
		switch (event.message.command)
		{
			case cmOpen:
				openScript();
				clearEvent(event);
				break;

			case cmRun:
				runScript();
				clearEvent(event);
				break;

			default:
				break;
		}
	}
}

TMenuBar *TScriptApp::initMenuBar(TRect r)
{
	r.b.y = r.a.y + 1;

	return
		new TMenuBar(r,
			*new TSubMenu("~F~ile", kbAltF) +
			*new TMenuItem("~O~pen Script...", cmOpen, kbAltO) +
			*new TMenuItem("~R~un Script...", cmRun, kbAltR) +
			newLine() +
			*new TMenuItem("E~x~it", cmQuit, cmQuit, hcNoContext, "Alt-X")
		);
}

TStatusLine *TScriptApp::initStatusLine(TRect r)
{
	r.a.y = r.b.y - 1;

	return
		new TStatusLine(r,
			*new TStatusDef(0, 0xFFFF) +
			*new TStatusItem("~Alt-X~ Exit", kbAltX, cmQuit) +
			*new TStatusItem(0, kbF10, cmMenu)
		);
}

int main(int argc, char **argv)
{
	TScriptApp app;
	app.run();
	return 0;
}
