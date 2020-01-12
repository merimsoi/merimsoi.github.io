// MusicSampleView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "MusicSampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MusicSampleView

IMPLEMENT_DYNCREATE(MusicSampleView, CFormView)

MusicSampleView::MusicSampleView()
	: CFormView(MusicSampleView::IDD)
{
	//{{AFX_DATA_INIT(MusicSampleView)
	m_musicSampleFileName = _T("");
	m_sampleID = 0;
	m_startSample = 0;
	m_endSample = 0;
	//}}AFX_DATA_INIT
	m_currMusicSamplePtr = NULL;
}

MusicSampleView::~MusicSampleView()
{
}

void MusicSampleView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MusicSampleView)
	DDX_Text(pDX, IDC_MUSIC_SAMPLE_FILE_NAME, m_musicSampleFileName);
	DDX_Text(pDX, IDC_SAMPLE_ID, m_sampleID);
	DDX_Text(pDX, IDC_START_SAMPLE, m_startSample);
	DDX_Text(pDX, IDC_END_SAMPLE, m_endSample);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MusicSampleView, CFormView)
	//{{AFX_MSG_MAP(MusicSampleView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE(RUNTIME_SAVE_MESSAGE,OnRuntimeSave)	
	ON_MESSAGE(UPDATE_DELETING_IN_WORLD,OnUpdateWorldObject)
	ON_EN_KILLFOCUS(IDC_START_SAMPLE, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_END_SAMPLE, OnKillfocus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MusicSampleView diagnostics

#ifdef _DEBUG
void MusicSampleView::AssertValid() const
{
	CFormView::AssertValid();
}

void MusicSampleView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MusicSampleView message handlers
CWorldConstructKitDoc* MusicSampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));
	return (CWorldConstructKitDoc*)m_pDocument;
}

BOOL MusicSampleView::GetMyWorld()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	m_worldID = pTreeView->GetCurrWorldID();	
	
	CWorldConstructKitDoc* doc = GetDocument();
	BOOL result = doc->m_worldMap.Lookup(m_worldID,m_world);	
  return result;
}

DWORD MusicSampleView::GetCurrMusicFileID()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrNodeID();
}
void MusicSampleView::GetCurrFileName(CString& fileName)
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	pTreeView->GetCurrNodeFileName(fileName);
}

void MusicSampleView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (GetMyWorld())
	{
		CString fileName;
		DWORD id = GetCurrMusicFileID();
		GetCurrFileName(fileName);

		m_world.m_bgMusicSample.ScanInit(DIRECTION_FORWARD);
		for (int i = 0; i < m_world.m_bgMusicFileCount; i++)
		{
			m_currMusicSamplePtr = &m_world.m_bgMusicSample.NextElement(); 
			if (m_currMusicSamplePtr->m_sampleID == id &&
				  m_currMusicSamplePtr->m_fileName == (CStdString)fileName)
			{				
				m_sampleID = m_currMusicSamplePtr->m_sampleID;
				m_musicSampleFileName = m_currMusicSamplePtr->m_fileName;				
				m_startSample = m_currMusicSamplePtr->m_startSample;				
				m_endSample = m_currMusicSamplePtr->m_endSample;
				
				UpdateData(FALSE);
				break;
			}		
		}
	}	
}

void MusicSampleView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();	
}


void MusicSampleView::OnRuntimeSave()
{
	UpdateData(TRUE);
	if (m_currMusicSamplePtr != NULL)
	{
		m_currMusicSamplePtr->m_startSample = m_startSample;
		m_currMusicSamplePtr->m_endSample = m_endSample;

		CWorldConstructKitDoc* doc = GetDocument();

		int countBefore = doc->m_worldMap.GetCount();
		doc->m_worldMap.SetAt(m_worldID,m_world);	
		int countAfter = doc->m_worldMap.GetCount();
		if (countBefore != countAfter)
		{
			ASSERT(FALSE);
		}
	}
}

void MusicSampleView::OnUpdateWorldObject()
{
  GetMyWorld();
}
void MusicSampleView::OnKillfocus() 
{
	UpdateData(TRUE);	
}
