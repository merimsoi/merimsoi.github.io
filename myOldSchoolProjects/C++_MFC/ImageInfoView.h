#if !defined(AFX_IMAGEINFO_H__DB1D5FC5_52B2_11D6_A110_A019DCED575B__INCLUDED_)
#define AFX_IMAGEINFO_H__DB1D5FC5_52B2_11D6_A110_A019DCED575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageInfoView.h : header file
//
#include "WorldConstructKitDoc.h"

/////////////////////////////////////////////////////////////////////////////
// ImageInfoView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"

class ImageInfoView : public CFormView
{
protected:
	ImageInfoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(ImageInfoView)

// Form Data
public:
	//{{AFX_DATA(ImageInfoView)
	enum { IDD = IDD_IMAGE_INFO };
	CSpinButtonCtrl	m_mapOffsetY;
	CSpinButtonCtrl	m_mapOffsetX;
	CSpinButtonCtrl	m_spinInitY;
	CSpinButtonCtrl	m_spinInitX;
	CSpinButtonCtrl	m_spinInitWidth;
	CSpinButtonCtrl	m_spinInitHeight;
	CSpinButtonCtrl	m_spinInitDist;
	CSpinButtonCtrl	m_spinFinishY;
	CSpinButtonCtrl	m_spinFinishX;
	CSpinButtonCtrl	m_spinFinishWidht;
	CSpinButtonCtrl	m_spinFinishHeight;
	CSpinButtonCtrl	m_spinFinishDist;
	CString	m_alphaFileName;
	short	m_currentFrame;
	DWORD	m_currentFrameClockValue;
	DWORD	m_endClockValue;
	CString	m_fileName;
	short	m_frameCount;
	DWORD	m_frameInterval;
	short	m_heightEnd;
	short	m_heightStart;
	short	m_imageID;
	BOOL	m_isImageVisible;
	short	m_leftAlpha;
	short	m_leftEnd;
	short	m_leftStart;
	short	m_loopRemaining;
	DWORD	m_startClockValue;
	short	m_topAlpha;
	short	m_topEnd;
	short	m_topStart;
	short	m_widthEnd;
	short	m_widthStart;
	short	m_zEnd;
	short	m_zStart;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
private:
	World m_world;
	DWORD m_worldId;	
	ImageInfo* m_currImagePtr;
	BOOL GetMyWorld();
  CWorldConstructKitDoc* GetDocument();
	DWORD GetCurrImageID();
	void GetCurrFileName(CString& fileName);
	DWORD GetCurrSceneId();
		
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ImageInfoView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~ImageInfoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(ImageInfoView)
	afx_msg void OnBrowseAlphaFileName();
	//}}AFX_MSG
	afx_msg void OnRuntimeSave();
	afx_msg void OnUpdateWorldObject();
  afx_msg void OnKillfocus();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEINFO_H__DB1D5FC5_52B2_11D6_A110_A019DCED575B__INCLUDED_)
