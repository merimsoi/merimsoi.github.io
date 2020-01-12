#if !defined(AFX_MUSICSAMPLE_H__DB1D5FC8_52B2_11D6_A110_A019DCED575B__INCLUDED_)
#define AFX_MUSICSAMPLE_H__DB1D5FC8_52B2_11D6_A110_A019DCED575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MusicSampleView.h : header file
//
#include "WorldConstructKitDoc.h"

/////////////////////////////////////////////////////////////////////////////
// MusicSampleView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"

class MusicSampleView : public CFormView
{
protected:
	MusicSampleView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(MusicSampleView)

// Form Data
public:
	//{{AFX_DATA(MusicSampleView)
	enum { IDD = IDD_MUSIC_SAMPLE };
	CString	m_musicSampleFileName;
	short	m_sampleID;
	DWORD	m_startSample;
	DWORD	m_endSample;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
private:
	DWORD m_worldID;
	World m_world;
	MusicSample* m_currMusicSamplePtr;

	BOOL GetMyWorld();
  CWorldConstructKitDoc* GetDocument();
	DWORD GetCurrMusicFileID();
	void GetCurrFileName(CString& fileName);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MusicSampleView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~MusicSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(MusicSampleView)
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

#endif // !defined(AFX_MUSICSAMPLE_H__DB1D5FC8_52B2_11D6_A110_A019DCED575B__INCLUDED_)
