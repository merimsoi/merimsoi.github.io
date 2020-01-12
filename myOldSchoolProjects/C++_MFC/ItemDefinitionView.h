#if !defined(AFX_ITEMDEFINITION_H__DB1D5FC6_52B2_11D6_A110_A019DCED575B__INCLUDED_)
#define AFX_ITEMDEFINITION_H__DB1D5FC6_52B2_11D6_A110_A019DCED575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ItemDefinitionView.h : header file
//
#include "WorldConstructKitDoc.h"
/////////////////////////////////////////////////////////////////////////////
// ItemDefinitionView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"

class ItemDefinitionView : public CFormView
{
protected:
	ItemDefinitionView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(ItemDefinitionView)

// Form Data
public:
	//{{AFX_DATA(ItemDefinitionView)
	enum { IDD = IDD_ITEM_DEFINITION };
	CListBox	m_interactionList;
	CComboBox	m_comboInteractionType;
	CComboBox	m_comboInteractionSubType;
	CString	m_description;
	CString	m_feedbackString;
	CString	m_fileName;
	short	m_fileSetID;
	short	m_hoverScript;
	BOOL	m_isInteractionEnabled;
	BOOL	m_isStashedItem;
	short	m_itemID;
	short	m_triggerScript;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
private:
	World m_world;
	DWORD m_worldId;
	ItemDefinition* m_currItemDefinitionPtr;
	CMap<DWORD,DWORD,short,short> m_listMap;
	BOOL GetMyWorld();
	DWORD GetCurrInventoryID();
	void GetCurrFileName(CString& fileName);
	void FillItemDetails(int selIndx,ItemDefinition& itemDefinition);
	int  IsExistInventory(short fileSetId);
  CWorldConstructKitDoc* GetDocument();
  void FillIterationList();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ItemDefinitionView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~ItemDefinitionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(ItemDefinitionView)
	afx_msg void OnSelchangeListInteraction();
	afx_msg void OnDelete();
	afx_msg void OnAdd();
	afx_msg void OnEdit();
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

#endif // !defined(AFX_ITEMDEFINITION_H__DB1D5FC6_52B2_11D6_A110_A019DCED575B__INCLUDED_)
