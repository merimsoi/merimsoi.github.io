#if !defined(AFX_CHARACTERINFO_H__DB1D5FC3_52B2_11D6_A110_A019DCED575B__INCLUDED_)
#define AFX_CHARACTERINFO_H__DB1D5FC3_52B2_11D6_A110_A019DCED575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CharacterInfoView.h : header file
//
#include "WorldConstructKitDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CharacterInfoView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"

class CharacterInfoView : public CFormView
{
protected:
	CharacterInfoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CharacterInfoView)

// Form Data
public:
	//{{AFX_DATA(CharacterInfoView)
	enum { IDD = IDD_CHARACTER_INFO };
	CListBox	m_clipList;
	short	m_characterId;
	CString	m_characterName;
	CString	m_colorFile;
	short	m_defaultClip;
	CString	m_clipFileName;
	short	m_firstFrame;
	short	m_lastFrame;
	short	m_loopCount;
	short	m_numPerSecond;
	CString	m_vertexFile;
	DWORD	m_typeId;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
private:
	World m_world;
	DWORD m_worldId;
	CharacterInfo* m_currCharacterInfoPtr;
	
	BOOL GetMyWorld();
  CWorldConstructKitDoc* GetDocument();
	void GetCurrFileName(CString& fileName);
  DWORD GetCurrCharacterInfoID();
	void FillCharacterInfoDetails(int selIndx,CharacterInfo & characterInfo);

	 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CharacterInfoView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CharacterInfoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CharacterInfoView)
	afx_msg void OnBrowseFileName();
	afx_msg void OnBrowseColorFile();
	afx_msg void OnBrowseVertexFile();
	afx_msg void OnAdd();
	afx_msg void OnEdit();
	afx_msg void OnSelchangeClipList();
	afx_msg void OnDelete();
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

#endif // !defined(AFX_CHARACTERINFO_H__DB1D5FC3_52B2_11D6_A110_A019DCED575B__INCLUDED_)
