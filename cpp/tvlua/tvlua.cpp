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

//
// messageBox
//

ushort _messageBox(std::string msg, ushort options)
{
	return messageBox(msg, options);
}

ushort _messageBoxRect(const TRect &r, std::string msg, ushort options)
{
	return messageBoxRect(r, msg, options);
}

//
// registerTurboTypes
//

void registerTurboTypes(sol::state &lua)
{
	// messageBox
	lua["mfWarning"] = mfWarning;
	lua["mfError"] = mfError;
	lua["mfInformation"] = mfInformation;
	lua["mfConfirmation"] = mfConfirmation;
	lua["mfYesButton"] = mfYesButton;
	lua["mfNoButton"] = mfNoButton;
	lua["mfOKButton"] = mfOKButton;
	lua["mfCancelButton"] = mfCancelButton;
	lua["mfYesNoCancel"] = mfYesNoCancel;
	lua["mfOKCancel"] = mfOKCancel;
	lua["messageBox"] = _messageBox;
	lua["messageBoxRect"] = _messageBoxRect;
}
