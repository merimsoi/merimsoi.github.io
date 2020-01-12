#if !defined(AFX_CHARACTERCONTEXT_H__DB1D5FC2_52B2_11D6_A110_A019DCED575B__INCLUDED_)
#define AFX_CHARACTERCONTEXT_H__DB1D5FC2_52B2_11D6_A110_A019DCED575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CharacterContextView.h : header file
//
#include "WorldConstructKitDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CharacterContextView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"

class CharacterContextView : public CFormView
{
protected:
	CharacterContextView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CharacterContextView)

// Form Data
public:
	//{{AFX_DATA(CharacterContextView)
	enum { IDD = IDD_CHARACTER_CONTEXT };
	CComboBox	m_typeId;
	CListBox	m_clipList;
	short	m_characterId;
	short	m_currentFrame;
	BOOL	m_isAffectedByLight;
	BOOL	m_isVisible;
	short	m_nextFrame;
	DWORD	m_time;
	DWORD	m_timeNextFrame;
	DWORD	m_timePreviousFrame;
	long	m_transX;
	long	m_transY;
	long	m_transZ;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

private:
	World m_world;
	DWORD m_worldId;
	CharacterContext* m_currCharacterContextPtr;
	BOOL GetMyWorld();
  CWorldConstructKitDoc* GetDocument();
	DWORD GetCurrSceneId();
	DWORD GetCurrCharacterContextId();
  void FillCharacterContextDetails(int selIndx,CharacterContext & characterContext);
	 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CharacterContextView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CharacterContextView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CharacterContextView)
	afx_msg void OnAdd();
	afx_msg void OnEdit();
	afx_msg void OnDelete();
	afx_msg void OnSelchangeClipList();
	afx_msg void OnUp();
	afx_msg void OnDown();
	//}}AFX_MSG
	afx_msg void OnRuntimeSave();
	afx_msg void OnUpdateWorldObject();
  afx_msg void OnKillfocus();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARACTERCONTEXT_H__DB1D5FC2_52B2_11D6_A110_A019DCED575B__INCLUDED_)
