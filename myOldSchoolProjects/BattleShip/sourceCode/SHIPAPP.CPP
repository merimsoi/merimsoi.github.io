#include <owl\owlpch.h>
#pragma hdrstop
#include "shipapp.h"
#include "game.h"                        // Definition of client class.
#include "about.h"                        // Definition of about dialog.
#include "dialogs.h"
#include"logo.cpp"

const char HelpFileName[] = "ship.hlp";
SDIDecFrame* This =0;

DEFINE_RESPONSE_TABLE1(shipApp, TApplication)
	 EV_COMMAND(CM_HELPCONTENTS, CmHelpContents),
	 EV_COMMAND(CM_HELPUSING, CmHelpUsing),
	 EV_COMMAND(CM_HELPABOUT, CmHelpAbout),
END_RESPONSE_TABLE;
//********************* ShipApp ******************************************
//constructor
shipApp::shipApp () : TApplication("BattleShip")
{
	 HelpState = false;
	 ContextHelp = false;
	 HelpCursor = 0;
	 FileData.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	 FileData.SetFilter("All Files (*.*)|*.*|");
}
//destructor
shipApp::~shipApp ()
{
}

bool shipApp::CanClose ()
{
	 bool result = TApplication::CanClose();
	 if (result && HelpState)
	 GetMainWindow()->WinHelp(HelpFileName, HELP_QUIT, 0L);
	  return result;
}
//set toolbar of the program
void shipApp::SetupSpeedBar (TDecoratedFrame *frame)
{
	 TControlBar* cb = new TControlBar(frame);
	 cb->Insert(*new TButtonGadget(CM_KIND, CM_CONNECT,
					TButtonGadget::Command,true));
	 cb->Insert(*new TButtonGadget(CM_GAMENEW, CM_GAMENEW,
					TButtonGadget::Command,true));
	 cb->Insert(*new TButtonGadget(CM_GAMESTART, CM_GAMESTART,
					TButtonGadget::Command,true));
	 cb->Insert(*new TSeparatorGadget(6));

	 cb->Insert(*new TButtonGadget(BT_FIRST, BT_FIRST,
					TButtonGadget::Exclusive,TRUE,
									TButtonGadget::Up));
	 cb->Insert(*new TButtonGadget(BT_SECOND, BT_SECOND,
					TButtonGadget::Exclusive,TRUE,
									TButtonGadget::Up));
	 cb->Insert(*new TSeparatorGadget(6));

	 cb->Insert(*new TButtonGadget(CM_FILESAVE, CM_KIND,
					TButtonGadget::Command,true));
	 cb->Insert(*new TButtonGadget(CM_REMOVE, CM_RANDOMIZE,
					TButtonGadget::Command,true));
	 cb->Insert(*new TSeparatorGadget(6));

	 cb->Insert(* new  TButtonGadget(IDM_QUICK ,CM_SPEEDFAST,
									TButtonGadget::Command,true));
	 cb->Insert(* new  TButtonGadget(IDM_ANIMATION ,CM_ANIMATIONYES,
									TButtonGadget::Command,true));

	 cb->Insert(* new  TButtonGadget(IDM_SOUND ,CM_SOUNDYES,
									TButtonGadget::Command,true));

	 cb->Insert(*new TSeparatorGadget(6));
	 cb->Insert(*new TSeparatorGadget(6));
	 cb->Insert(*new TButtonGadget(CM_STOP, CM_STOP,
					TButtonGadget::Command,true));
	 cb->Insert(*new TButtonGadget(CM_EXIT, CM_EXIT,
					TButtonGadget::Command,true));

	 cb->SetHintMode(TGadgetWindow::EnterHints);
	 frame->Insert(*cb, TDecoratedFrame::Top);
}
// initialization the main window of program
void shipApp::InitMainWindow ()
{
	 nCmdShow =SW_SHOWMAXIMIZED;
	 SDIDecFrame *frame = new SDIDecFrame(0, GetName(), 0, true);
	 frame->SetIcon(this, IDI_SDIAPPLICATION);
	 frame->AssignMenu(SDI_MENU);
	 frame->Attr.AccelTable = SDI_MENU;
	 SetupSpeedBar(frame);
	 TStatusBar *sb = new TStatusBar(frame, TGadget::Recessed,
												TStatusBar::CapsLock        |
												TStatusBar::NumLock         |
												TStatusBar::ScrollLock      |
												TStatusBar::Overtype);
	 frame->Insert(*sb, TDecoratedFrame::Bottom);
	 SetMainWindow(frame);
	 frame->SetMenuDescr(TMenuDescr(SDI_MENU));
	 EnableBWCC();

	 }

DEFINE_RESPONSE_TABLE1(SDIDecFrame, TDecoratedFrame)
EV_WM_ERASEBKGND,
END_RESPONSE_TABLE;

//************************ SDIDecFrame **************************************
// constructor
SDIDecFrame::SDIDecFrame (TWindow *parent, const char far *title, TWindow *clientWnd, bool trackMenuSelection, TModule *module)
	 : TDecoratedFrame(parent, title, clientWnd == 0 ? new shipSpace(0, "") : clientWnd, trackMenuSelection, module)
{
}
//destructor
SDIDecFrame::~SDIDecFrame ()
{
}

void SDIDecFrame::SetupWindow()
{
  This = this;
  TDecoratedFrame::SetupWindow();
}

bool SDIDecFrame::EvEraseBkgnd( HDC/* hdc*/)
 {
	return false;
 }

void shipApp::CmHelpContents ()
{
	 HelpState = GetMainWindow()->WinHelp(HelpFileName, HELP_CONTENTS, 0L);
}

void shipApp::CmHelpUsing ()
{
	 HelpState = GetMainWindow()->WinHelp(HelpFileName, HELP_HELPONHELP, 0L);
}
// showing the about box
void shipApp::CmHelpAbout ()
{
	 shipAboutDlg(MainWindow).Execute();
}

bool shipApp::ProcessAppMsg (MSG& msg)
{
	 if (msg.message == WM_COMMAND) {
		  if (ContextHelp || (::GetKeyState(VK_F1) < 0)) {
				ContextHelp = false;
				GetMainWindow()->WinHelp(HelpFileName, HELP_CONTEXT, msg.wParam);
				return true;
		  }
	 } else
		  switch (msg.message)
		  {
			case WM_KEYDOWN:
				if (msg.wParam == VK_F1)
				 {
					 // If the Shift/F1 then set the help cursor and turn on the modal help state.
					 if (::GetKeyState(VK_SHIFT) < 0)
					 {
						  ContextHelp = true;
						  HelpCursor = ::LoadCursor(GetMainWindow()->GetModule()->GetInstance(), MAKEINTRESOURCE(IDC_HELPCURSOR));
						  ::SetCursor(HelpCursor);
						  return true;        // Gobble up the message.
					 }
					else
					 {
						 // If F1 w/o the Shift key then bring up help's main index.
						 GetMainWindow()->WinHelp(HelpFileName, HELP_INDEX, 0L);
						 return true;           // Gobble up the message.
					 }
				}
			  else
				  {
					 if (ContextHelp && (msg.wParam == VK_ESCAPE))
						{
						  if (HelpCursor)	::DestroyCursor(HelpCursor);
						  ContextHelp = false;
						  HelpCursor = 0;
						  GetMainWindow()->SetCursor(0, IDC_ARROW);
						  return true;    // Gobble up the message.
						}
				 }
				break;

		  case WM_MOUSEMOVE:
		  case WM_NCMOUSEMOVE:
				if (ContextHelp)
				{
					 ::SetCursor(HelpCursor);
					 return true;        // Gobble up the message.
				}
				break;

		  case WM_INITMENU:
				if (ContextHelp)
				{
					 ::SetCursor(HelpCursor);
					 return true;        // Gobble up the message.
				}
				break;

		 case WM_ENTERIDLE:
				if (msg.wParam == MSGF_MENU)
					 if (GetKeyState(VK_F1) < 0)
					 {
						  ContextHelp = true;
						  GetMainWindow()->PostMessage(WM_KEYDOWN, VK_RETURN, 0L);
						  return true;       // Gobble up the message.
					 }
				break;

		  default:
				;
		  };  // End of switch
	 // Continue normal processing.
	 return TApplication::ProcessAppMsg(msg);
}

BOOL shipApp::IdleAction(long l)
{
if (GetMainWindow())
{
  shipSpace *client = TYPESAFE_DOWNCAST(GetMainWindow()->GetClientWindow(),shipSpace);
  if (client&& client->HWindow)
  client->ReadCommData();
}
TApplication::IdleAction(l);
  return TRUE;
}

int shipApp::TermInstance(int status)
{

  return TApplication::TermInstance(status);
}
// main function
int OwlMain (int , char* [])
{
	 TEntryApp().Run();
	 try {
		  shipApp    app;
		  return app.Run();
	 }
	 catch (xmsg& x) {
		  ::MessageBox(0, x.why().c_str(), "Exception", MB_OK);
	 }

	 return -1;
}


