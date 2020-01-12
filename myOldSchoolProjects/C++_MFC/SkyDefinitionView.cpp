// SkyDefinitionView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "SkyDefinitionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SkyDefinitionView

IMPLEMENT_DYNCREATE(SkyDefinitionView, CFormView)

SkyDefinitionView::SkyDefinitionView()
	: CFormView(SkyDefinitionView::IDD)
{
	//{{AFX_DATA_INIT(SkyDefinitionView)
	m_skyFileName = _T("");
	m_startingTime = 0;
	m_skyId = 0;
	m_skyWidth = 0;
	m_skyTop = 0;
	m_skyLeft = 0;
	m_skyHeight = 0;
	m_frameCount = 0;
	m_currFrame = 0;
	m_frameInterval = 0;
	//}}AFX_DATA_INIT
	m_currSkyPtr = NULL;
}

SkyDefinitionView::~SkyDefinitionView()
{

}

void SkyDefinitionView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SkyDefinitionView)
	DDX_Control(pDX, IDC_SPIN_SKY_WIDTH, m_spinSkyWidth);
	DDX_Control(pDX, IDC_SPIN_SKY_TOP, m_spinSkyTop);
	DDX_Control(pDX, IDC_SPIN_SKY_LEFT, m_spinSkyLeft);
	DDX_Control(pDX, IDC_SPIN_SKY_HEIGHT, m_spinSkyHeight);
	DDX_Control(pDX, IDC_SPIN_FRAME_COUNT, m_spinFrameCount);
	DDX_Control(pDX, IDC_SPIN_CURRENT_FRAME, m_spinCurrentFrame);
	DDX_Text(pDX, IDC_SKY_FILE_NAME, m_skyFileName);
	DDX_Text(pDX, IDC_STARTING_TIME, m_startingTime);
	DDX_Text(pDX, IDC_SKY_ID, m_skyId);
	DDX_Text(pDX, IDC_SKY_WIDTH, m_skyWidth);
	DDX_Text(pDX, IDC_SKY_TOP, m_skyTop);
	DDX_Text(pDX, IDC_SKY_LEFT, m_skyLeft);
	DDX_Text(pDX, IDC_SKY_HEIGHT, m_skyHeight);
	DDX_Text(pDX, IDC_FRAME_COUNT, m_frameCount);
	DDX_Text(pDX, IDC_CURRENT_FRAME, m_currFrame);
	DDX_Text(pDX, IDC_FRAME_CLOCK_INTERVAL, m_frameInterval);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SkyDefinitionView, CFormView)
	//{{AFX_MSG_MAP(SkyDefinitionView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE(RUNTIME_SAVE_MESSAGE,OnRuntimeSave)
	ON_MESSAGE(UPDATE_DELETING_IN_WORLD,OnUpdateWorldObject)
	ON_EN_KILLFOCUS(IDC_FRAME_COUNT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_FRAME_CLOCK_INTERVAL, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_CURRENT_FRAME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_STARTING_TIME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_SKY_WIDTH, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_SKY_HEIGHT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_SKY_LEFT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_SKY_TOP, OnKillfocus)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SkyDefinitionView diagnostics

#ifdef _DEBUG
void SkyDefinitionView::AssertValid() const
{
	CFormView::AssertValid();
}

void SkyDefinitionView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// SkyDefinitionView message handlers
CWorldConstructKitDoc* SkyDefinitionView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));
	return (CWorldConstructKitDoc*)m_pDocument;
}

BOOL SkyDefinitionView::GetMyWorld()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	m_worldID = pTreeView->GetCurrWorldID();	
	
	CWorldConstructKitDoc* doc = GetDocument();
	BOOL result = doc->m_worldMap.Lookup(m_worldID,m_world);	
  return result;
}

DWORD SkyDefinitionView::GetCurrSkyID()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrNodeID();
}

void SkyDefinitionView::GetCurrFileName(CString& fileName)
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	pTreeView->GetCurrNodeFileName(fileName);
}

void SkyDefinitionView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (GetMyWorld())
	{
		CString fileName;
		DWORD id = GetCurrSkyID();
		GetCurrFileName(fileName);

		m_world.m_skies.ScanInit(DIRECTION_FORWARD);
		for (int i = 0; i < m_world.m_numberOfSkies; i++)
		{
			m_currSkyPtr = &m_world.m_skies.NextElement(); 
			if (m_currSkyPtr->m_skyID == id &&
				  m_currSkyPtr->m_fileName == (CStdString)fileName)
			{
				m_skyId = m_currSkyPtr->m_skyID ;
				m_skyFileName = m_currSkyPtr->m_fileName; 
				m_startingTime = m_currSkyPtr->m_currentFrameClockValue; 
				m_skyWidth = m_currSkyPtr->m_width;
				m_skyTop = m_currSkyPtr->m_top;
				m_skyLeft = m_currSkyPtr->m_left ;
				m_skyHeight = m_currSkyPtr->m_height;
				m_frameCount = m_currSkyPtr->m_frameCount;
				m_frameInterval = m_currSkyPtr->m_frameClockInterval;
				m_currFrame = m_currSkyPtr->m_currentFrame;			

				UpdateData(FALSE);
				break;
			}		
		}
	}	
}

void SkyDefinitionView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	m_spinCurrentFrame.SetBuddy(GetDlgItem(IDC_CURRENT_FRAME));
	m_spinFrameCount.SetBuddy(GetDlgItem(IDC_FRAME_COUNT));
	m_spinSkyHeight.SetBuddy(GetDlgItem(IDC_SKY_HEIGHT));
	m_spinSkyLeft.SetBuddy(GetDlgItem(IDC_SKY_LEFT));
	m_spinSkyTop.SetBuddy(GetDlgItem(IDC_SKY_TOP));
	m_spinSkyWidth.SetBuddy(GetDlgItem(IDC_SKY_WIDTH));

	m_spinCurrentFrame.SetRange(0,SHORT_MAX_VALUE);
	m_spinFrameCount.SetRange(0,SHORT_MAX_VALUE);
	m_spinSkyHeight.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinSkyLeft.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinSkyTop.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinSkyWidth.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
}

void SkyDefinitionView::OnRuntimeSave()
{
	UpdateData(TRUE);
	if (m_currSkyPtr != NULL)
	{
		m_currSkyPtr->m_skyID = m_skyId;
		m_currSkyPtr->m_fileName = m_skyFileName ; 
		m_currSkyPtr->m_currentFrameClockValue = m_startingTime; 
		m_currSkyPtr->m_width = m_skyWidth;
		m_currSkyPtr->m_top = m_skyTop ;
		m_currSkyPtr->m_left  = m_skyLeft ;
		m_currSkyPtr->m_height = m_skyHeight ;
		m_currSkyPtr->m_frameCount = m_frameCount  ;
		m_currSkyPtr->m_frameClockInterval = m_frameInterval  ;
		m_currSkyPtr->m_currentFrame = m_currFrame;			
		
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

void SkyDefinitionView::OnUpdateWorldObject()
{
  GetMyWorld();
}

void SkyDefinitionView::OnKillfocus() 
{
	UpdateData(TRUE);	
}
