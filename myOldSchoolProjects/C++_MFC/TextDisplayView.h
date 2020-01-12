#if !defined(AFX_TEXTDISPLAY_H__DB1D5FCE_52B2_11D6_A110_A019DCED575B__INCLUDED_)
#define AFX_TEXTDISPLAY_H__DB1D5FCE_52B2_11D6_A110_A019DCED575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextDisplayView.h : header file
//
#include "WorldConstructKitDoc.h"

/////////////////////////////////////////////////////////////////////////////
// TextDisplayView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "resource.h"

class TextDisplayView : public CFormView
{
protected:
	TextDisplayView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(TextDisplayView)

// Form Data
public:
	//{{AFX_DATA(TextDisplayView)
	enum { IDD = IDD_TEXT_DISPLAY };
	CSpinButtonCtrl	m_spinFontSizeStart;
	CSpinButtonCtrl	m_spinFontSizeEnd;
	CSpinButtonCtrl	m_widthRegionStart;
	CSpinButtonCtrl	m_spinWidthRegionEnd;
	CSpinButtonCtrl	m_topRegionStart;
	CSpinButtonCtrl	m_topRegionEnd;
	CSpinButtonCtrl	m_leftRegionRight;
	CSpinButtonCtrl	m_leftRegionEnd;
	CSpinButtonCtrl	m_heightRegionStart;
	CSpinButtonCtrl	m_spinHeightRegionEnd;
	CSpinButtonCtrl	m_spinColorRStart;
	CSpinButtonCtrl	m_spinColorREnd;
	CSpinButtonCtrl	m_spinColorGStart;
	CSpinButtonCtrl	m_spinColorGEnd;
	CSpinButtonCtrl	m_spinColorBStart;
	CSpinButtonCtrl	m_spinColorBEnd;
	CComboBox	m_comboTextType;
	CString	m_displayString;
	DWORD	m_endClockValue;
	CString	m_fontName;
	BOOL	m_isShowText;
	DWORD	m_startClockValue;
	short	m_textID;
	short	m_colorBEnd;
	short	m_colorBStart;
	short	m_colorgEnd;
	short	m_colorGStart;
	short	m_colorREnd;
	short	m_colorRStart;
	short	m_fontSizeEnd;
	short	m_fontSizeStart;
	short	m_heightEnd;
	short	m_heightStart;
	short	m_leftEnd;
	short	m_leftStart;
	short	m_topEnd;
	short	m_topStart;
	short	m_widthEnd;
	short	m_widthStart;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
private:
	World m_world;
	DWORD m_worldID; 
	TextDisplay* m_currTextDisplayPtr;

	BOOL GetMyWorld();
	DWORD GetCurrTextDisplayId();
	DWORD GetCurrSceneId();
  CWorldConstructKitDoc* GetDocument();	
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TextDisplayView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~TextDisplayView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(TextDisplayView)
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

#endif // !defined(AFX_TEXTDISPLAY_H__DB1D5FCE_52B2_11D6_A110_A019DCED575B__INCLUDED_)
