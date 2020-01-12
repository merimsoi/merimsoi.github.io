#if !defined(AFX_SKYDEFINITION_H__DB1D5FCC_52B2_11D6_A110_A019DCED575B__INCLUDED_)
#define AFX_SKYDEFINITION_H__DB1D5FCC_52B2_11D6_A110_A019DCED575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkyDefinitionView.h : header file
//
#include "WorldConstructKitDoc.h"

/////////////////////////////////////////////////////////////////////////////
// SkyDefinitionView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"

class SkyDefinitionView : public CFormView
{
protected:
	SkyDefinitionView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(SkyDefinitionView)

// Form Data
public:
	//{{AFX_DATA(SkyDefinitionView)
	enum { IDD = IDD_SKY_DEFINITION };
	CSpinButtonCtrl	m_spinSkyWidth;
	CSpinButtonCtrl	m_spinSkyTop;
	CSpinButtonCtrl	m_spinSkyLeft;
	CSpinButtonCtrl	m_spinSkyHeight;
	CSpinButtonCtrl	m_spinFrameCount;
	CSpinButtonCtrl	m_spinCurrentFrame;
	CString	m_skyFileName;
	DWORD	m_startingTime;
	short	m_skyId;
	short	m_skyWidth;
	short	m_skyTop;
	short	m_skyLeft;
	short	m_skyHeight;
	short	m_frameCount;
	short	m_currFrame;
	DWORD	m_frameInterval;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
private:
	World m_world;
	DWORD m_worldID;
	SkyDefinition* m_currSkyPtr;

	BOOL GetMyWorld();
  CWorldConstructKitDoc* GetDocument();
	DWORD GetCurrSkyID();
	void GetCurrFileName(CString& fileName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SkyDefinitionView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~SkyDefinitionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(SkyDefinitionView)
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

#endif // !defined(AFX_SKYDEFINITION_H__DB1D5FCC_52B2_11D6_A110_A019DCED575B__INCLUDED_)
