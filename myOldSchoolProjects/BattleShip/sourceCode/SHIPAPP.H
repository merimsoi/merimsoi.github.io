#if !defined(__shipapp_h)              // Sentry, use file only if it's not already included.
#define __shipapp_h
#define LPTSTR LPSTR
#include <owl\owlpch.h>
#include"info.h"
#pragma hdrstop
#include <ddeml.h>
#include "shipapp.rh"            // Definition of all resources.
#define MAX_COMPUTERNAME_LENGTH 9

class shipApp;
class TDecoratedFrame;
class shipApp : public TApplication {
private:
	 bool            HelpState;             // Has the help engine been used.
	 bool            ContextHelp;           // SHIFT-F1 state (context sensitive HELP)
	 HCURSOR         HelpCursor;            // Context sensitive help cursor
	 void SetupSpeedBar (TDecoratedFrame *frame);

public:
	 shipApp ();
	 virtual ~shipApp ();
	 TOpenSaveDialog::TData FileData;        // Data to control open/saveas standard dialog.
	 void OpenFile (const char *fileName = 0);
	 BOOL IdleAction(long);
	 int TermInstance(int status);
public:
	 virtual void InitMainWindow();
	 virtual bool CanClose ();
	 virtual bool ProcessAppMsg (MSG& msg);
protected:
	 void CmHelpContents ();
	 void CmHelpUsing ();
	 void CmHelpAbout ();
	 void EvRButtonDown (uint modKeys, TPoint& point);
DECLARE_RESPONSE_TABLE(shipApp);
};
//*************************************************************************
class SDIDecFrame : public TDecoratedFrame {
public:
	 SDIDecFrame (TWindow *parent, const char far *title,
					  TWindow *clientWnd, bool trackMenuSelection = false,
					  TModule *module = 0);
	 ~SDIDecFrame ();
	 bool EvEraseBkgnd( HDC hdc);
	 void DrawBitmap(HDC,HBITMAP ,int ,int);
	 void SetupWindow();

  DECLARE_RESPONSE_TABLE(SDIDecFrame);

protected:
	 void EvRButtonDown (uint modKeys, TPoint& point);
};

#endif                                      // __shipapp_h sentry.
