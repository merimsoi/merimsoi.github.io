#if !defined(AFX_MUSICSCRIPT_H__DB1D5FC9_52B2_11D6_A110_A019DCED575B__INCLUDED_)
#define AFX_MUSICSCRIPT_H__DB1D5FC9_52B2_11D6_A110_A019DCED575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MusicScriptView.h : header file
//
#include "WorldConstructKitDoc.h"

/////////////////////////////////////////////////////////////////////////////
// MusicScriptView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"

class MusicScriptView : public CFormView
{
protected:
	MusicScriptView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(MusicScriptView)

// Form Data
public:
	//{{AFX_DATA(MusicScriptView)
	enum { IDD = IDD_MUSIC_SCRIPT };
	CSpinButtonCtrl	m_spinRepeatCommand;
	CSpinButtonCtrl	m_spinLoopStart;
	CSpinButtonCtrl	m_spinLoopEnd;
	CSpinButtonCtrl	m_spinCurrentMusic;
	CListBox	m_sampleIDList;
	CComboBox	m_comboSampleID;
	CComboBox	m_comboCommandArr;
	DWORD	m_commandEndTime;
	DWORD	m_commandStartTime;
	BOOL	m_isObeyCommand;
	BOOL	m_isWaitCommandFinish;
	short	m_scriptID;
	short	m_loopEnd;
	short	m_loopStart;
	short	m_repeatCommand;
	short	m_currentCommand;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

private:
	DWORD m_worldID;
	World m_world;
	MusicScript* m_currMusicScriptPtr;
	CMap<DWORD,DWORD,short,short> m_listMap;
	BOOL GetMyWorld();
  CWorldConstructKitDoc* GetDocument();
	DWORD GetCurrMusicScriptID();
	void FillMusicFileDetails(int selIndx,MusicScript& musicScript);
	int IsExistMusicSample(short musicSampleID);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MusicScriptView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~MusicScriptView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(MusicScriptView)
	afx_msg void OnAddMusic();
	afx_msg void OnEditMusic();
	afx_msg void OnSelchangeListSampleId();
	afx_msg void OnDeleteMusic();
	afx_msg void OnDown();
	afx_msg void OnUp();
	//}}AFX_MSG
	afx_msg void OnRuntimeSave();
	afx_msg void OnUpdateWorldObject();
  afx_msg void OnKillfocus();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUSICSCRIPT_H__DB1D5FC9_52B2_11D6_A110_A019DCED575B__INCLUDED_)
