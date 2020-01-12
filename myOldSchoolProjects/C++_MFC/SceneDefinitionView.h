#if !defined(AFX_SCENEDEFINITION_H__DB1D5FCA_52B2_11D6_A110_A019DCED575B__INCLUDED_)
#define AFX_SCENEDEFINITION_H__DB1D5FCA_52B2_11D6_A110_A019DCED575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SceneDefinitionView.h : header file
//
#include "WorldConstructKitDoc.h"

/////////////////////////////////////////////////////////////////////////////
// SceneDefinitionView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"

class SceneDefinitionView : public CFormView
{
protected:
	SceneDefinitionView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(SceneDefinitionView)

// Form Data
public:
	//{{AFX_DATA(SceneDefinitionView)
	enum { IDD = IDD_SCENE_DEFINITION };
	CSpinButtonCtrl	m_spinHeight;
	CSpinButtonCtrl	m_spinY;
	CSpinButtonCtrl	m_spinX;
	CSpinButtonCtrl	m_spinWidth;
	CComboBox	m_comboSkyID;
	CComboBox	m_comboMusicScript;
	short	m_entranceScript;
	short	m_exitScript;
	short	m_filesetID;
	short	m_inventoryHeight;
	short	m_inventoryLeft;
	short	m_inventoryTop;
	short	m_inventoryWidth;
	BOOL	m_isDisplayInventory;
	BOOL	m_isSceneNavigable;
	short	m_sceneID;
	short	m_activeText;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

private:
	World m_world;
	DWORD m_worldId;
	SceneDefinition* m_currSceneDefinitionPtr;
	BOOL GetMyWorld();
  CWorldConstructKitDoc* GetDocument();
	DWORD GetCurrSceneId();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SceneDefinitionView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~SceneDefinitionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(SceneDefinitionView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnRuntimeSave();
	afx_msg void OnUpdateWorldObject();
	afx_msg void OnKillfocus(); 
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCENEDEFINITION_H__DB1D5FCA_52B2_11D6_A110_A019DCED575B__INCLUDED_)
