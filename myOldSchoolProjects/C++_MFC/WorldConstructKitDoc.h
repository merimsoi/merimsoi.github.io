// WorldConstructKitDoc.h : interface of the CWorldConstructKitDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORLDCONSTRUCTKITDOC_H__28BC180B_4982_11D6_A110_D06D3DF46E59__INCLUDED_)
#define AFX_WORLDCONSTRUCTKITDOC_H__28BC180B_4982_11D6_A110_D06D3DF46E59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "engineClasses.h"
#include <afxtempl.h>
#include "MyTreeView.h"

typedef CMap<DWORD,DWORD,World,World&> WorldMapType;

class CWorldConstructKitDoc : public CDocument
{
protected: // create from serialization only
	CWorldConstructKitDoc();
	DECLARE_DYNCREATE(CWorldConstructKitDoc)

// Attributes
public:
	WorldMapType  m_worldMap;
	CMyTreeView* m_pTreeView; 

// Operations
public:
	bool NewWorld(DWORD id);
	void NewWorld(DWORD key,World& world);
	bool NewMusicScript(DWORD id);
	bool NewMusicFile(DWORD id,LPCTSTR fileName);
	bool NewSky(DWORD id,LPCTSTR fileName);
	bool NewImageInfo(DWORD id,LPCTSTR fileName);
	bool NewAnimationInfo(DWORD id,LPCTSTR fileName);
	bool NewSFXInfo(DWORD id,LPCTSTR fileName);
	bool NewTextDisplay(DWORD id);
	bool NewHotSpot(DWORD id);
	bool NewKeyboard(DWORD id);
	bool NewCharacterContext(DWORD id);
	bool NewCamera(DWORD id);
	bool NewItem(DWORD id,LPCTSTR fileName);
	bool NewCharacterInfo(short characterId,LPCTSTR characterName);
  bool NewScene(DWORD id);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorldConstructKitDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWorldConstructKitDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWorldConstructKitDoc)
	afx_msg void OnNew();
	afx_msg void OnSave();
	afx_msg void OnDelete();
	afx_msg void OnUpdateNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDelete(CCmdUI* pCmdUI);
	afx_msg void OnGetDataFromDb();
	afx_msg void OnAddWorld();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL GetNewDataFromFile(WorldMapType& newWorld);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORLDCONSTRUCTKITDOC_H__28BC180B_4982_11D6_A110_D06D3DF46E59__INCLUDED_)
