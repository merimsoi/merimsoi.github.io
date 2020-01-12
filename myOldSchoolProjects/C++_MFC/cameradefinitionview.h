#if !defined(AFX_CAMERADEFINITION_H__DB1D5FC1_52B2_11D6_A110_A019DCED575B__INCLUDED_)
#define AFX_CAMERADEFINITION_H__DB1D5FC1_52B2_11D6_A110_A019DCED575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CameraDefinitionView.h : header file
//
#include "WorldConstructKitDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CameraDefinitionView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"

class CameraDefinitionView : public CFormView
{
protected:
	CameraDefinitionView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CameraDefinitionView)

// Form Data
public:
	//{{AFX_DATA(CameraDefinitionView)
	enum { IDD = IDD_CAMERA_DEFINITION };
	CComboBox	m_comboSceneID;
	CSpinButtonCtrl	m_spinTransparencyStart;
	CSpinButtonCtrl	m_spinTrasparencyEnd;
	CSpinButtonCtrl	m_spinColorSEnd;
	CSpinButtonCtrl	m_spinColorSStart;
	CSpinButtonCtrl	m_spinColorLStart;
	CSpinButtonCtrl	m_spinColorLEnd;
	CSpinButtonCtrl	m_spinColorHStart;
	CSpinButtonCtrl	m_spinColorHEnd;
	CComboBox	m_comboLayer;
	DWORD	m_endClockValue;
	BOOL	m_isApplyColorFilter;
	BOOL	m_isApplyTrasparency;
	BOOL	m_isCameraEnabled;
	BOOL	m_isFrozenCamera;
	BOOL	m_isSceneInitialized;
	DWORD	m_startClockValue;
	short	m_colorHEnd;
	short	m_colorHStart;
	short	m_colorLEnd;
	short	m_colorLStart;
	short	m_colorSEnd;
	short	m_colorSStart;
	short	m_transparencyEnd;
	short	m_transparencyStart;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

private:
	World m_world;
	DWORD m_worldId;
	CameraDefinition* m_currCameraPtr;
	BOOL GetMyWorld();
  CWorldConstructKitDoc* GetDocument();
	DWORD GetCurrCameraDefinitionId();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CameraDefinitionView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CameraDefinitionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CameraDefinitionView)
	afx_msg void OnSelendokComboSceneId();
	afx_msg void OnKillfocus();
	//}}AFX_MSG
	afx_msg void OnRuntimeSave();
	afx_msg void OnUpdateWorldObject();

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMERADEFINITION_H__DB1D5FC1_52B2_11D6_A110_A019DCED575B__INCLUDED_)
