#if !defined(AFX_ANIMATIONINFO_H__CF373E04_513C_11D6_A110_E7533687D154__INCLUDED_)
#define AFX_ANIMATIONINFO_H__CF373E04_513C_11D6_A110_E7533687D154__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnimationInfoView.h : header file
//
#include "WorldConstructKitDoc.h"

/////////////////////////////////////////////////////////////////////////////
// AnimationInfoView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "resource.h"

class AnimationInfoView : public CFormView
{
friend class CWorldConstructKitView;	
protected:
	AnimationInfoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(AnimationInfoView)

// Form Data
public:
	//{{AFX_DATA(AnimationInfoView)
	enum { IDD = IDD_ANIMATION_INFO };
	CSpinButtonCtrl	m_spinInitYValue;
	CSpinButtonCtrl	m_spinInitXValue;
	CSpinButtonCtrl	m_spinInitWidth;
	CSpinButtonCtrl	m_spinInitHeight;
	CSpinButtonCtrl	m_spinInitDistance;
	CSpinButtonCtrl	m_spinFinalYValue;
	CSpinButtonCtrl	m_spinFinalXValue;
	CSpinButtonCtrl	m_spinFinalWidth;
	CSpinButtonCtrl	m_spinFinalHeight;
	CSpinButtonCtrl	m_spinFinalDistance;
	short	m_animationID;
	CString	m_fileNameVideo;
	CString	m_fileNameAudio;
	short	m_widthEnd;
	short	m_widthStart;
	short	m_zEnd;
	short	m_currentFrame;
	DWORD	m_endClockValue;
	short	m_endFrame;
	DWORD	m_endVolumeTime;
	DWORD	m_frameExpar;
	short	m_heightEnd;
	short	m_heightStart;
	BOOL	m_isDoAudio;
	BOOL	m_isDoVideo;
	short	m_leftEnd;
	short	m_leftStart;
	short	m_loopRemaining;
	DWORD	m_startClockValue;
	short	m_startFrame;
	DWORD	m_startPlayTime;
	DWORD	m_startVolumeTime;
	short	m_topEnd;
	short	m_topStart;
	short	m_volumeEnd;
	short	m_volumeStart;
	short	m_zStart;
	//}}AFX_DATA

// Attributes
public:
// Operations
public:

private:
	World m_world;
	DWORD m_worldId;
	AnimationInfo* m_currAnimationInfo;
	BOOL GetMyWorld();
  CWorldConstructKitDoc* GetDocument();
	void GetCurrFileName(CString& fileName);
	DWORD GetCurrSceneId();
	DWORD GetCurrAnimationID();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AnimationInfoView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~AnimationInfoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(AnimationInfoView)
	afx_msg void OnBrowseAudioFileName();
	//}}AFX_MSG
	afx_msg void OnRuntimeSave();
	afx_msg void OnUpdateWorldObject();
	afx_msg void OnKillfocus(); 

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATIONINFO_H__CF373E04_513C_11D6_A110_E7533687D154__INCLUDED_)
