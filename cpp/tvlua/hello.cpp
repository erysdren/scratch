/*---------------------------------------------------------*/
/*                                                         */
/*   Turbo Vision Hello World Demo Source File             */
/*                                                         */
/*---------------------------------------------------------*/
/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
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

const int cmRun = 100;

ushort _messageBox(std::string msg, ushort options)
{
	return messageBox(msg, options);
}

class THelloApp : public TApplication
{

public:

    THelloApp();

    virtual void handleEvent( TEvent& event );
    static TMenuBar *initMenuBar( TRect );
    static TStatusLine *initStatusLine( TRect );

	void openScript()
	{
		char fileName[MAXPATH];
		strcpy(fileName, "*.*");

		if (executeDialog(new TFileDialog("*.lua", "Open script", "~N~ame", fdOpenButton, 100), fileName) != cmCancel)
			this->program = this->lua.load_file(fileName);
	}

	void runScript()
	{
		this->program();
	}

private:
	sol::state lua;
	sol::load_result program;
};

THelloApp::THelloApp() :
    TProgInit( &THelloApp::initStatusLine,
               &THelloApp::initMenuBar,
               &THelloApp::initDeskTop
             )
{
	this->lua.open_libraries(sol::lib::base, sol::lib::table, sol::lib::string);

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
	lua["messageBox"] = &_messageBox;
}

void THelloApp::handleEvent( TEvent& event )
{
    TApplication::handleEvent( event );
    if( event.what == evCommand )
        {
        switch( event.message.command )
            {
			case cmOpen:
				openScript();
				clearEvent( event );
				break;
			case cmRun:
				runScript();
				clearEvent( event );
				break;
			default:
                break;
            }
        }
}

TMenuBar *THelloApp::initMenuBar( TRect r )
{
    r.b.y = r.a.y+1;

    return new TMenuBar( r,
      *new TSubMenu( "~H~ello", kbAltH ) +
		*new TMenuItem( "~O~pen Script...", cmOpen, kbAltO ) +
		*new TMenuItem( "~R~un Script...", cmRun, kbAltR ) +
         newLine() +
        *new TMenuItem( "E~x~it", cmQuit, cmQuit, hcNoContext, "Alt-X" )
        );

}

TStatusLine *THelloApp::initStatusLine( TRect r )
{
    r.a.y = r.b.y-1;
    return new TStatusLine( r,
        *new TStatusDef( 0, 0xFFFF ) +
            *new TStatusItem( "~Alt-X~ Exit", kbAltX, cmQuit ) +
            *new TStatusItem( 0, kbF10, cmMenu )
            );
}

int main(int argc, char **argv)
{
    THelloApp helloWorld;
    helloWorld.run();
    return 0;
}
