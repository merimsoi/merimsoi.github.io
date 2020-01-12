#if !defined(AFX_STAGINGINFO_H__DB1D5FCD_52B2_11D6_A110_A019DCED575B__INCLUDED_)
#define AFX_STAGINGINFO_H__DB1D5FCD_52B2_11D6_A110_A019DCED575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StagingInfoView.h : header file
//
#include "WorldConstructKitDoc.h"

/////////////////////////////////////////////////////////////////////////////
// StagingInfoView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"

class StagingInfoView : public CFormView
{
protected:
	StagingInfoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(StagingInfoView)

// Form Data
public:
	//{{AFX_DATA(StagingInfoView)
	enum { IDD = IDD_STAGING_INFO };
	CSpinButtonCtrl	m_spinMapOffsetY;
	CSpinButtonCtrl	m_spinMapOffsetX;
	CSpinButtonCtrl	m_spinMapHeight;
	CSpinButtonCtrl	m_spinImageY;
	CSpinButtonCtrl	m_spinImageX;
	CSpinButtonCtrl	m_spinImageWidth;
	CSpinButtonCtrl	m_spinImageHeight;
	CSpinButtonCtrl	m_spinCameraHeight;
	CSpinButtonCtrl	m_spinCameraAngle;
	CSpinButtonCtrl	m_spinBackInitY;
	CSpinButtonCtrl	m_spinBackInitX;
	CSpinButtonCtrl	m_spinBackInitWidht;
	CSpinButtonCtrl	m_spinBackInitHeight;
	CSpinButtonCtrl	m_spinBackFinishY;
	CSpinButtonCtrl	m_spinBackFinishX;
	CSpinButtonCtrl	m_spinBackFinishWidht;
	CSpinButtonCtrl	m_spinBackFinishHeight;
	CSpinButtonCtrl	m_spinred;
	CSpinButtonCtrl	m_spinGreen;
	CSpinButtonCtrl	m_spinBlue;
	CListBox	m_altitudeIndexMapList;
	CComboBox	m_comboLightingMode;
	CString	m_alphaFileName;
	short	m_cameraAngle;
	short	m_cameraHeight;
	short	m_colorCount;
	DWORD	m_endClockValue;
	short	m_heightEnd;
	short	m_heightStart;
	CString	m_imageFileName;
	short	m_leftAlpha;
	short	m_leftEnd;
	short	m_leftStart;
	short	m_lightB;
	short	m_lightG;
	short	m_lightR;
	CString	m_mapFileName;
	short	m_mapHeight;
	short	m_mapLeft;
	short	m_mapTop;
	short	m_mapWidth;
	short	m_topAlpha;
	short	m_topEnd;
	short	m_topStart;
	short	m_widthEnd;
	short	m_widthStart;
	DWORD	m_startClockValue;
	CString	m_lightingFileName;
	short	m_indx;
	short	m_lightAngleX;
	short	m_lightAngleY;
	short	m_lightAngleZ;
	long	m_height;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
private:
	World m_world;
	DWORD m_worldId;
	StagingInfo* m_currStagingInfoPtr;
	BOOL GetMyWorld();
  CWorldConstructKitDoc* GetDocument();
	DWORD GetCurrSceneId();

	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(StagingInfoView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~StagingInfoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(StagingInfoView)
	afx_msg void OnSelchangeListMapAltitudeIndex();
	afx_msg void OnEdit();
	afx_msg void OnBrowseAlphaFile();
	afx_msg void OnBrowseMapFile();
	afx_msg void OnBrowseLightFile();
	afx_msg void OnBrowseImageFileName();
	//}}AFX_MSG

	afx_msg void OnRuntimeSave();
	afx_msg void OnUpdateWorldObject();
	afx_msg void OnKillfocus(); 

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAGINGINFO_H__DB1D5FCD_52B2_11D6_A110_A019DCED575B__INCLUDED_)
