#if !defined(AFX_MYTREEVIEW_H__B485C909_4892_11D6_A110_E4B8626FC259__INCLUDED_)
#define AFX_MYTREEVIEW_H__B485C909_4892_11D6_A110_E4B8626FC259__INCLUDED_

#include <afxcview.h>
#include "mainfrm.h"
#include "basic.h"
#include "engineClasses.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTreeView.h : header file
//
class CWorldConstructKitView;

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView view

class CMyTreeView : public CTreeView
{
protected:
	CMyTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyTreeView)

// Attributes
public:

// Operations
public:
   void SetSplitterWnd(CMySplitterWnd* pSplitterWnd) {m_pSplitterWnd = pSplitterWnd; }
	 void AddNode();
	 void AddWorldNode(LPCTSTR newNodeTitleStr,BOOL isNeedScene = TRUE);
	 void AddSceneNode(LPCTSTR newNodeTitleStr,HTREEITEM sceneListItem);
	 void AddChildNode(LPCTSTR newNodeTitleStr,HTREEITEM parentItem,NodeType nodeType,UINT resID);	 
	 void SaveNode();
	 void DeleteNode();
	 NodeType IsGetNodeType();
	 DWORD GetCurrWorldID();
	 DWORD GetCurrSceneId();
	 DWORD GetCurrNodeID();
	 CString GetCurrNodeName();
   CString GetParentName();
	 void GetCurrNodeFileName(CString& fileName);
	 void AddWorldNodeWithData(LPCTSTR newNodeTitleStr,DWORD key,World& world);
	 void AddExistMusicScriptNode(DWORD key,MusicScript& musicScript,HTREEITEM parentItem);
	 void AddExistMusicSampleNode(DWORD key,MusicSample& musicSample,HTREEITEM parentItem);
   void AddExistCharacterInfoNode(DWORD key,CharacterInfo& characterInfo,HTREEITEM parentItem);
	 void AddExistSkyNode(DWORD key,SkyDefinition& skyDefinition,HTREEITEM parentItem);
	 void AddExistInventoryNode(DWORD key,ItemDefinition& inventory,HTREEITEM parentItem);
	 void AddExistCameraNode(DWORD key,CameraDefinition& cameraDef,HTREEITEM parentItem);
	 void AddExistSceneNode(DWORD key,SceneDefinition& sceneDef,HTREEITEM parentItem);
	 void AddExistImage(DWORD key,DWORD sceneId,ImageInfo& image,HTREEITEM parentItem);
	 void AddExistAnimation(DWORD key,DWORD sceneId,AnimationInfo& animation,HTREEITEM parentItem);
	 void AddExistCharacter(DWORD key,DWORD sceneId,CharacterContext& context,HTREEITEM parentItem);
	 void AddExistSFX(DWORD key,DWORD sceneId,SFXInfo& sfx,HTREEITEM parentItem);
	 void AddExistText(DWORD key,DWORD sceneId, TextDisplay& textDisp,HTREEITEM parentItem);
	 void AddExistHotSpot(DWORD key,DWORD sceneId,HotspotInfo& hotSpot,HTREEITEM parentItem);
	 void AddExistKeyboard(DWORD key,DWORD sceneId, KeyboardTrigger& keyboard,HTREEITEM parentItem);
	 HTREEITEM FindItem(CString itemText);
	 HTREEITEM FindItemBetweenChildren(HTREEITEM item,CString itemText);
   HTREEITEM FindWorldChildItem(DWORD key,LPCTSTR itemText);
	 HTREEITEM FindSceneChildItem(DWORD key,DWORD sceneId,LPCTSTR itemText);
	 HTREEITEM FindSceneListItem(DWORD key);
	 void AddToDymamicMap(CString nodeTitle,CString nodeStr,UINT resId,DWORD worldId,DWORD sceneId);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTreeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
		
	CImageList*     m_pTreeImageList;
	CMySplitterWnd* m_pSplitterWnd;

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyTreeView)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg void OnChangeSceneId(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREEVIEW_H__B485C909_4892_11D6_A110_E4B8626FC259__INCLUDED_)
