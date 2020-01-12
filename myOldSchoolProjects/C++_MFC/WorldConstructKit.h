// WorldConstructKit.h : main header file for the WORLDCONSTRUCTKIT application
//

#if !defined(AFX_WORLDCONSTRUCTKIT_H__B485C8F9_4892_11D6_A110_E4B8626FC259__INCLUDED_)
#define AFX_WORLDCONSTRUCTKIT_H__B485C8F9_4892_11D6_A110_E4B8626FC259__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWorldConstructKitApp:
// See WorldConstructKit.cpp for the implementation of this class
//

class CWorldConstructKitApp : public CWinApp
{
public:
	CWorldConstructKitApp();
	CDocument* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorldConstructKitApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWorldConstructKitApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORLDCONSTRUCTKIT_H__B485C8F9_4892_11D6_A110_E4B8626FC259__INCLUDED_)
