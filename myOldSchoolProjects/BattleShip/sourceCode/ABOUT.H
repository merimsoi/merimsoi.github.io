#if !defined(__shpabtdl_h)              // Sentry, use file only if it's not already included.
#define __shpabtdl_h
#include <owl\owlpch.h>
#pragma hdrstop
#include "shipapp.rh"                  // Definition of all resources.
// class for about box
class shipAboutDlg : public TDialog {
public:
	 shipAboutDlg (TWindow *parent, TResId resId = IDD_ABOUT,
	               TModule *module = 0);
	 virtual ~shipAboutDlg ();
	 void SetupWindow ();
};
#endif  
