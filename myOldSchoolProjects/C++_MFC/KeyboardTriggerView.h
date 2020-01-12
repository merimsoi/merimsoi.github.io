#if !defined(AFX_KEYBOARDTRIGGER_H__DB1D5FC7_52B2_11D6_A110_A019DCED575B__INCLUDED_)
#define AFX_KEYBOARDTRIGGER_H__DB1D5FC7_52B2_11D6_A110_A019DCED575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KeyboardTriggerView.h : header file
//
#include "WorldConstructKitDoc.h"

/////////////////////////////////////////////////////////////////////////////
// KeyboardTriggerView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"

class KeyboardTriggerView : public CFormView
{
protected:
	KeyboardTriggerView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(KeyboardTriggerView)

// Form Data
public:
	//{{AFX_DATA(KeyboardTriggerView)
	enum { IDD = IDD_KEYBOARD_TRIGGER };
	CSpinButtonCtrl	m_spinKeyCode;
	short	m_keyID;
	BOOL	m_isTriggerEnabled;
	short	m_triggerScript;
	short	m_keyCode;
	//}}AFX_DATA
	

// Attributes
public:

// Operations
public:
private:
	World m_world;
	DWORD m_worldID;
	KeyboardTrigger* m_currKeyboardPtr;
	BOOL GetMyWorld();
	DWORD GetCurrKeyboardId();
	DWORD GetCurrSceneId();
  CWorldConstructKitDoc* GetDocument();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(KeyboardTriggerView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~KeyboardTriggerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(KeyboardTriggerView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg void OnRuntimeSave();
	afx_msg void OnUpdateWorldObject();
	afx_msg void OnKillfocus();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYBOARDTRIGGER_H__DB1D5FC7_52B2_11D6_A110_A019DCED575B__INCLUDED_)
