// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "WorldDefinitionView.h"
#include "MyTreeView.h"
#include "MainFrm.h"
#include "afxpriv.h"
#include "basic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////
// Splitter wnd function to route commands to all splitter panes/views.
//
// This function changes the view in a splitter window
void CMySplitterWnd::ChangeView(int row, int col, CRuntimeClass* pViewClass)
{
    ASSERT(pViewClass->IsDerivedFrom(RUNTIME_CLASS(CView)));

    CView* pView = STATIC_DOWNCAST(CView, GetPane(row, col));
    CFrameWnd* pFrame = pView->GetParentFrame();
    ASSERT(pFrame);

    // set up create context to preserve doc/frame etc.
    CCreateContext cc;
    memset(&cc, sizeof(cc), 0);
    cc.m_pNewViewClass = pViewClass;
    cc.m_pCurrentDoc = pView->GetDocument();
    cc.m_pNewDocTemplate = cc.m_pCurrentDoc ?
        cc.m_pCurrentDoc->GetDocTemplate() : NULL;
    cc.m_pCurrentFrame = pFrame;

    DeleteView(row, col);                // delete old view
    VERIFY(CreateView(row, col,          // create new one
        pViewClass,
        CSize(0,0),                      // will fix in RecalcLayout
        &cc));

    RecalcLayout();                      // recompute layout 

    // initialize the view
    CWnd* pWnd = GetPane(row, col);
    if (pWnd)
        pWnd->SendMessage(WM_INITIALUPDATE);
}


BOOL CMySplitterWnd::OnCmdMsg(UINT nID, int nCode, void* pExtra,AFX_CMDHANDLERINFO* pHandlerInfo)
{
	for (int row = 0; row < GetRowCount(); row++) 
	{
		for (int col = 0; col < GetColumnCount(); col++) 
		{
			if (GetPane(row,col)->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
				return TRUE;
		}
	}
	// Call default routing--very important!
	return CSplitterWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

 	SetWindowPos(&wndTop,0,0,MAIN_WND_WIDTH,MAIN_WND_HEIGHT,SWP_SHOWWINDOW);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// Pass to splitter
	if (m_wndSplitter.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
  	return TRUE;

	// Call default routing--very important!
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;
	
	if (!m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CMyTreeView), CSize(200,100), pContext) ||
		!m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(WorldDefinitionView),CSize(100,100), pContext)) 
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView, m_wndSplitter.GetPane(0,0));
	ASSERT(pTreeView);

  pTreeView->SetSplitterWnd(&m_wndSplitter);

	// Activate the input view. This is important for it to receive commands.
	SetActiveView(pTreeView);

	return TRUE;
}

