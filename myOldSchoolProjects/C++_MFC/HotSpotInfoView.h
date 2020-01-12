#if !defined(AFX_HOTSPOTINFO_H__DB1D5FC4_52B2_11D6_A110_A019DCED575B__INCLUDED_)
#define AFX_HOTSPOTINFO_H__DB1D5FC4_52B2_11D6_A110_A019DCED575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HotSpotInfoView.h : header file
//
#include "WorldConstructKitDoc.h"

/////////////////////////////////////////////////////////////////////////////
// HotSpotInfoView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"

class HotSpotInfoView : public CFormView
{
protected:
	HotSpotInfoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(HotSpotInfoView)

// Form Data
public:
	//{{AFX_DATA(HotSpotInfoView)
	enum { IDD = IDD_HOT_SPOT_INFO };
	CSpinButtonCtrl	m_spinY2;
	CSpinButtonCtrl	m_spinY1;
	CSpinButtonCtrl	m_spinX2;
	CSpinButtonCtrl	m_spinX1;
	CListBox	m_interactionList;
	CComboBox	m_comboInteractionType;
	CComboBox	m_comboInteractionSubType;
	CComboBox	m_comboImageID;
	CComboBox	m_comboHotSpotMode;
	CComboBox	m_comboCharacterID;
	CComboBox	m_comboAnimationID;
	short	m_bottomRect;
	short	m_clickTrigger;
	CString	m_description;
	CString	m_feedbackString;
	short	m_filesetID;
	short	m_hotSpotID;
	short	m_hoverScript;
	BOOL	m_isInteractionEnabled;
	BOOL	m_isTransformCursor;
	short	m_leftRect;
	short	m_rightRect;
	short	m_topRect;
	short	m_triggerScript;
	short	m_unhoverScript;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
private:
	World m_world;
	DWORD m_worldId;
	HotspotInfo* m_currHotSpotPtr;
	SceneDefinition* m_currSceneDefPtr;
	CMap<DWORD,DWORD,short,short> m_listMap;
	BOOL GetMyWorld();
	DWORD GetCurrHotSpotID();
	DWORD GetCurrSceneId();
  CWorldConstructKitDoc* GetDocument();
	void FillItemDetails(int selIndx,HotspotInfo& itemDefinition);
	int IsExistInventory(short fileSetId);
  void FillIterationList();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HotSpotInfoView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~HotSpotInfoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(HotSpotInfoView)
	afx_msg void OnSelchangeListInteraction();
	afx_msg void OnAdd();
	afx_msg void OnEdit();
	afx_msg void OnDelete();
	afx_msg void OnSelendokComboInterationType();
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

#endif // !defined(AFX_HOTSPOTINFO_H__DB1D5FC4_52B2_11D6_A110_A019DCED575B__INCLUDED_)
