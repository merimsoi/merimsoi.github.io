#if !defined(AFX_SFXINFO_H__DB1D5FCB_52B2_11D6_A110_A019DCED575B__INCLUDED_)
#define AFX_SFXINFO_H__DB1D5FCB_52B2_11D6_A110_A019DCED575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SFXInfoView.h : header file
//
#include "WorldConstructKitDoc.h"

/////////////////////////////////////////////////////////////////////////////
// SFXInfoView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"

class SFXInfoView : public CFormView
{
protected:
	SFXInfoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(SFXInfoView)

// Form Data
public:
	//{{AFX_DATA(SFXInfoView)
	enum { IDD = IDD_SFX_INFO };
	CSpinButtonCtrl	m_spinVolumeStart;
	CSpinButtonCtrl	m_spinVolumeEnd;
	CString	m_fileName;
	BOOL	m_isAudioEnable;
	short	m_loopRemaining;
	short	m_SFXID;
	DWORD	m_startClockValue;
	DWORD	m_volumeEndTime;
	DWORD	m_volumeStartTime;
	short	m_volumeEnd;
	short	m_volumeStart;
	DWORD	m_endPosition;
	DWORD	m_startPosition;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
private:
	World m_world;
	DWORD m_worldId;
	SFXInfo* m_currSfxPtr;
	BOOL GetMyWorld();
	DWORD GetCurrSFXInfoID();
	void GetCurrFileName(CString& fileName);
	DWORD GetCurrSceneId();
  CWorldConstructKitDoc* GetDocument();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SFXInfoView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~SFXInfoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(SFXInfoView)
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

#endif // !defined(AFX_SFXINFO_H__DB1D5FCB_52B2_11D6_A110_A019DCED575B__INCLUDED_)
