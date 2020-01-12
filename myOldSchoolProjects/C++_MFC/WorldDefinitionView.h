#if !defined(AFX_WORLDDEFINITION_H__DB1D5FCF_52B2_11D6_A110_A019DCED575B__INCLUDED_)
#define AFX_WORLDDEFINITION_H__DB1D5FCF_52B2_11D6_A110_A019DCED575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WorldDefinitionView.h : header file
//
#include "WorldConstructKitDoc.h"

/////////////////////////////////////////////////////////////////////////////
// WorldDefinitionView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "resource.h"

class WorldDefinitionView : public CFormView
{
protected:
	WorldDefinitionView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(WorldDefinitionView)

// Form Data
public:
	//{{AFX_DATA(WorldDefinitionView)
	enum { IDD = IDD_WORLD };
	CListBox	m_trackRecordList;
	short	m_cameraCount;
	short	m_characterNum;
	short	m_inventorySize;
	BOOL	m_isClockPowered;
	short	m_musicFileCount;
	short	m_musicScriptCount;
	short	m_scenesNumber;
	short	m_skyNumber;
	short	m_trackID;
	short	m_trackValue;
	DWORD	m_clockValue;
	//}}AFX_DATA

// Attributes
public:
private:
// Operations
public:
private:
	World m_world;
	DWORD m_worldId;
	BOOL GetMyWorld();
  void FillTrackDetails(int selIndx);
	int IsExistTrack(short trackId);
	void UpdateMap();
	CWorldConstructKitDoc* GetDocument();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WorldDefinitionView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~WorldDefinitionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(WorldDefinitionView)
	afx_msg void OnAdd();
	afx_msg void OnEdit();
	afx_msg void OnDelete();
	afx_msg void OnSelchangeListTrackRecord();
	afx_msg void OnDown();
	afx_msg void OnUp();
	//}}AFX_MSG
	afx_msg void OnKillfocus(); 
	afx_msg void OnRuntimeSave();
	afx_msg void OnUpdateWorldObject();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORLDDEFINITION_H__DB1D5FCF_52B2_11D6_A110_A019DCED575B__INCLUDED_)
