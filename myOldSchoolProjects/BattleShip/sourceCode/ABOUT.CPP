#include <owl\owlpch.h>
#pragma hdrstop
#if !defined(__FLAT__)
#include <ver.h>
#endif
#include "shipapp.h"
#include "about.h"
// constructor
shipAboutDlg::shipAboutDlg (TWindow *parent, TResId resId, TModule *module)
	 : TDialog(parent, resId, module)
{

}
// destructor
shipAboutDlg::~shipAboutDlg ()
{
	 Destroy();
}
// creating about box
void shipAboutDlg::SetupWindow ()
{
	 TDialog::SetupWindow();
}