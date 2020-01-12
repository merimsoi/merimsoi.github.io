// SFXInfoView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "SFXInfoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SFXInfoView

IMPLEMENT_DYNCREATE(SFXInfoView, CFormView)

SFXInfoView::SFXInfoView()
	: CFormView(SFXInfoView::IDD)
{
	//{{AFX_DATA_INIT(SFXInfoView)
	m_fileName = _T("");
	m_isAudioEnable = FALSE;
	m_loopRemaining = 0;
	m_SFXID = 0;
	m_startClockValue = 0;
	m_volumeEndTime = 0;
	m_volumeStartTime = 0;
	m_volumeEnd = 0;
	m_volumeStart = 0;
	m_endPosition = 0;
	m_startPosition = 0;
	//}}AFX_DATA_INIT
	m_currSfxPtr = NULL;
}

SFXInfoView::~SFXInfoView()
{
}

void SFXInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SFXInfoView)
	DDX_Control(pDX, IDC_SPIN_VOLUME_START, m_spinVolumeStart);
	DDX_Control(pDX, IDC_SPIN_VOLUME_END, m_spinVolumeEnd);
	DDX_Text(pDX, IDC_FILE_NAME, m_fileName);
	DDX_Check(pDX, IDC_IS_AUDIO_ENABLED, m_isAudioEnable);
	DDX_Text(pDX, IDC_LOOP_REMAINING, m_loopRemaining);
	DDX_Text(pDX, IDC_SFX_ID, m_SFXID);
	DDX_Text(pDX, IDC_START_CLOCK_VALUE, m_startClockValue);
	DDX_Text(pDX, IDC_VOLUME_END_TIME, m_volumeEndTime);
	DDX_Text(pDX, IDC_VOLUME_START_TIME, m_volumeStartTime);
	DDX_Text(pDX, IDC_VOLUME_END, m_volumeEnd);
	DDV_MinMaxInt(pDX, m_volumeEnd, VOLUME_MIN, VOLUME_MAX);
	DDX_Text(pDX, IDC_VOLUME_START, m_volumeStart);
	DDV_MinMaxInt(pDX, m_volumeStart, VOLUME_MIN, VOLUME_MAX);
	DDX_Text(pDX, IDC_END_POSTION, m_endPosition);
	DDX_Text(pDX, IDC_START_POSITION, m_startPosition);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SFXInfoView, CFormView)
	//{{AFX_MSG_MAP(SFXInfoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE(RUNTIME_SAVE_MESSAGE,OnRuntimeSave)
	ON_MESSAGE(UPDATE_DELETING_IN_WORLD,OnUpdateWorldObject)
	ON_EN_KILLFOCUS(IDC_START_CLOCK_VALUE, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LOOP_REMAINING, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_VOLUME_START_TIME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_VOLUME_END_TIME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_VOLUME_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_VOLUME_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_START_POSITION, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_END_POSTION, OnKillfocus)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SFXInfoView diagnostics

#ifdef _DEBUG
void SFXInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

void SFXInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// SFXInfoView message handlers
CWorldConstructKitDoc* SFXInfoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));
	return (CWorldConstructKitDoc*)m_pDocument;
}

BOOL SFXInfoView::GetMyWorld()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	m_worldId = pTreeView->GetCurrWorldID();	
	
	CWorldConstructKitDoc* doc = GetDocument();
	BOOL result = doc->m_worldMap.Lookup(m_worldId,m_world);	
  return result;
}

DWORD SFXInfoView::GetCurrSFXInfoID()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrNodeID();
}

void SFXInfoView::GetCurrFileName(CString& fileName)
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	pTreeView->GetCurrNodeFileName(fileName);
}

DWORD SFXInfoView::GetCurrSceneId()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrSceneId();
}


void SFXInfoView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (GetMyWorld())
	{
		DWORD sceneId = GetCurrSceneId();
		CString fileName;
		DWORD id = GetCurrSFXInfoID();
		GetCurrFileName(fileName);

		for (int i = 0 ; i < m_world.m_numberOfScenes; i++)
		{
			if (m_world.m_scenes[i].m_sceneID == sceneId)
			{				
				m_world.m_scenes[i].m_sfx.ScanInit(DIRECTION_FORWARD);
				for (int j = 0; j < m_world.m_scenes[i].m_sfxCount; j++)
				{
					m_currSfxPtr = &m_world.m_scenes[i].m_sfx.NextElement(); 
					if (m_currSfxPtr->m_sfxID == id &&
						  m_currSfxPtr->m_fileName == (CStdString)fileName)
					{
						m_fileName = m_currSfxPtr->m_fileName;
						m_isAudioEnable = m_currSfxPtr->m_audioIsEnabled;
						m_loopRemaining = m_currSfxPtr->m_loopsRemaining;
						m_SFXID = m_currSfxPtr->m_sfxID;
						m_startClockValue = m_currSfxPtr->m_startClockValue;
						m_startPosition = m_currSfxPtr->m_startPosition;
						m_endPosition = m_currSfxPtr->m_endPosition;
						m_volumeEndTime = m_currSfxPtr->m_volEndClock;
						m_volumeStartTime = m_currSfxPtr->m_volStartClock;
						m_volumeEnd = m_currSfxPtr->m_volumeEnd;
						m_volumeStart = m_currSfxPtr->m_volumeStart;

						UpdateData(FALSE);
						break;
					}		
				}
			}
		}
	}	
}

void SFXInfoView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	m_spinVolumeEnd.SetBuddy(GetDlgItem(IDC_VOLUME_END));
	m_spinVolumeStart.SetBuddy(GetDlgItem(IDC_VOLUME_START));

	m_spinVolumeEnd.SetRange(VOLUME_MIN,VOLUME_MAX);
	m_spinVolumeStart.SetRange(VOLUME_MIN,VOLUME_MAX);
}

void SFXInfoView::OnRuntimeSave()
{
	UpdateData(TRUE);
	if (m_currSfxPtr != NULL)
	{
		m_currSfxPtr->m_fileName = m_fileName  ;
		m_currSfxPtr->m_audioIsEnabled = m_isAudioEnable ? true : false;
		m_currSfxPtr->m_loopsRemaining = m_loopRemaining;
		m_currSfxPtr->m_sfxID	= m_SFXID;
		m_currSfxPtr->m_startClockValue =	m_startClockValue;
		m_currSfxPtr->m_startPosition =	m_startPosition;
		m_currSfxPtr->m_endPosition	= m_endPosition;
		m_currSfxPtr->m_volEndClock	= m_volumeEndTime;
		m_currSfxPtr->m_volStartClock =	m_volumeStartTime;
		m_currSfxPtr->m_volumeEnd	= m_volumeEnd;
		m_currSfxPtr->m_volumeStart =	m_volumeStart;
		
		CWorldConstructKitDoc* doc = GetDocument();

		int countBefore = doc->m_worldMap.GetCount();
		doc->m_worldMap.SetAt(m_worldId,m_world);	
		int countAfter = doc->m_worldMap.GetCount();
		if (countBefore != countAfter)
		{
	    ASSERT(FALSE);
		}

	}
}

void SFXInfoView::OnUpdateWorldObject()
{
  GetMyWorld();
}
void SFXInfoView::OnKillfocus() 
{
	UpdateData(TRUE);	
}
