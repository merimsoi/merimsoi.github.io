// AnimationInfoView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "AnimationInfoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// AnimationInfoView

IMPLEMENT_DYNCREATE(AnimationInfoView, CFormView)

AnimationInfoView::AnimationInfoView()
	: CFormView(AnimationInfoView::IDD)
{
	//{{AFX_DATA_INIT(AnimationInfoView)
	m_animationID = 0;
	m_fileNameVideo = _T("");
	m_fileNameAudio = _T("");
	m_widthEnd = 0;
	m_widthStart = 0;
	m_zEnd = 0;
	m_currentFrame = 0;
	m_endClockValue = 0;
	m_endFrame = 0;
	m_endVolumeTime = 0;
	m_frameExpar = 0;
	m_heightEnd = 0;
	m_heightStart = 0;
	m_isDoAudio = FALSE;
	m_isDoVideo = FALSE;
	m_leftEnd = 0;
	m_leftStart = 0;
	m_loopRemaining = 0;
	m_startClockValue = 0;
	m_startFrame = 0;
	m_startPlayTime = 0;
	m_startVolumeTime = 0;
	m_topEnd = 0;
	m_topStart = 0;
	m_volumeEnd = 0;
	m_volumeStart = 0;
	m_zStart = 0;
	//}}AFX_DATA_INIT
	m_currAnimationInfo = NULL;
}

AnimationInfoView::~AnimationInfoView()
{
	
}

void AnimationInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AnimationInfoView)
	DDX_Control(pDX, IDC_SPIN_INIT_Y_VALUE, m_spinInitYValue);
	DDX_Control(pDX, IDC_SPIN_INIT_X_VALUE, m_spinInitXValue);
	DDX_Control(pDX, IDC_SPIN_INIT_WIDTH, m_spinInitWidth);
	DDX_Control(pDX, IDC_SPIN_INIT_HEIGHT, m_spinInitHeight);
	DDX_Control(pDX, IDC_SPIN_INIT_DISTANCE, m_spinInitDistance);
	DDX_Control(pDX, IDC_SPIN_FINAL_Y_VALUE, m_spinFinalYValue);
	DDX_Control(pDX, IDC_SPIN_FINAL_X_VALUE, m_spinFinalXValue);
	DDX_Control(pDX, IDC_SPIN_FINAL_WIDTH, m_spinFinalWidth);
	DDX_Control(pDX, IDC_SPIN_FINAL_HEIGHT, m_spinFinalHeight);
	DDX_Control(pDX, IDC_SPIN_FINAL_DISTANCE, m_spinFinalDistance);
	DDX_Text(pDX, IDC_ANIMATION_ID, m_animationID);
	DDX_Text(pDX, IDC_FILE_NAME_VIDEO, m_fileNameVideo);
	DDX_Text(pDX, IDC_FILE_NAME_AUDIO, m_fileNameAudio);
	DDX_Text(pDX, IDC_WIDTH_END, m_widthEnd);
	DDX_Text(pDX, IDC_WIDTH_START, m_widthStart);
	DDX_Text(pDX, IDC_Z_END, m_zEnd);
	DDX_Text(pDX, IDC_CURRENT_FRAME, m_currentFrame);
	DDX_Text(pDX, IDC_END_CLOCK_VALUE, m_endClockValue);
	DDX_Text(pDX, IDC_END_FRAME, m_endFrame);
	DDX_Text(pDX, IDC_END_VOLUME_TIME, m_endVolumeTime);
	DDX_Text(pDX, IDC_FRAME_EXPIRATION, m_frameExpar);
	DDX_Text(pDX, IDC_HEIGHT_END, m_heightEnd);
	DDX_Text(pDX, IDC_HEIGHT_START, m_heightStart);
	DDX_Check(pDX, IDC_IS_DO_AUDIO, m_isDoAudio);
	DDX_Check(pDX, IDC_IS_DO_VIDEO, m_isDoVideo);
	DDX_Text(pDX, IDC_LEFT_END, m_leftEnd);
	DDX_Text(pDX, IDC_LEFT_START, m_leftStart);
	DDX_Text(pDX, IDC_LOOP_REMAINING, m_loopRemaining);
	DDX_Text(pDX, IDC_START_CLOCK_VALUE, m_startClockValue);
	DDX_Text(pDX, IDC_START_FRAME, m_startFrame);
	DDX_Text(pDX, IDC_START_PLAY_TIME, m_startPlayTime);
	DDX_Text(pDX, IDC_START_VOLUME_TIME, m_startVolumeTime);
	DDX_Text(pDX, IDC_TOP_END, m_topEnd);
	DDX_Text(pDX, IDC_TOP_START, m_topStart);
	DDX_Text(pDX, IDC_VOLUME_END, m_volumeEnd);
	DDV_MinMaxInt(pDX, m_volumeEnd, VOLUME_MIN, VOLUME_MAX);
	DDX_Text(pDX, IDC_VOLUME_START, m_volumeStart);
	DDV_MinMaxInt(pDX, m_volumeStart, VOLUME_MIN, VOLUME_MAX);
	DDX_Text(pDX, IDC_Z_START, m_zStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AnimationInfoView, CFormView)
	//{{AFX_MSG_MAP(AnimationInfoView)
	ON_BN_CLICKED(IDC_BROWSE_AUDIO_FILE_NAME, OnBrowseAudioFileName)
	//}}AFX_MSG_MAP
	ON_MESSAGE(RUNTIME_SAVE_MESSAGE,OnRuntimeSave)
	ON_MESSAGE(UPDATE_DELETING_IN_WORLD,OnUpdateWorldObject)
	ON_EN_KILLFOCUS(IDC_START_PLAY_TIME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LOOP_REMAINING, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LEFT_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TOP_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_WIDTH_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_HEIGHT_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_Z_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_START_CLOCK_VALUE, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LEFT_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TOP_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_WIDTH_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_HEIGHT_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_Z_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_END_CLOCK_VALUE, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_START_VOLUME_TIME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_END_VOLUME_TIME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_VOLUME_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_VOLUME_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_START_FRAME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_END_FRAME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_CURRENT_FRAME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_FRAME_EXPIRATION, OnKillfocus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AnimationInfoView diagnostics

#ifdef _DEBUG
void AnimationInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

void AnimationInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// AnimationInfoView message handlers

void AnimationInfoView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	m_spinInitYValue.SetBuddy(GetDlgItem(IDC_TOP_START));  
	m_spinInitXValue.SetBuddy(GetDlgItem(IDC_LEFT_START));  
	m_spinInitWidth.SetBuddy(GetDlgItem(IDC_WIDTH_START));   
	m_spinInitHeight.SetBuddy(GetDlgItem(IDC_HEIGHT_START));  
	m_spinInitDistance.SetBuddy(GetDlgItem(IDC_Z_START));
	m_spinFinalYValue.SetBuddy(GetDlgItem(IDC_TOP_END)); 
	m_spinFinalXValue.SetBuddy(GetDlgItem(IDC_LEFT_END)); 
	m_spinFinalWidth.SetBuddy(GetDlgItem(IDC_WIDTH_END));  
	m_spinFinalHeight.SetBuddy(GetDlgItem(IDC_HEIGHT_END)); 
	m_spinFinalDistance.SetBuddy(GetDlgItem(IDC_Z_END));

	m_spinInitYValue.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);  
	m_spinInitXValue.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);  
	m_spinInitWidth.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);   
	m_spinInitHeight.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);  
	m_spinInitDistance.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinFinalYValue.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE); 
	m_spinFinalXValue.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE); 
	m_spinFinalWidth.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);  
	m_spinFinalHeight.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE); 
	m_spinFinalDistance.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);	
}

CWorldConstructKitDoc* AnimationInfoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));
	return (CWorldConstructKitDoc*)m_pDocument;
}

BOOL AnimationInfoView::GetMyWorld()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	m_worldId = pTreeView->GetCurrWorldID();	
	
	CWorldConstructKitDoc* doc = GetDocument();
	BOOL result = doc->m_worldMap.Lookup(m_worldId,m_world);	
  return result;
}

DWORD AnimationInfoView::GetCurrAnimationID()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrNodeID();
}

void AnimationInfoView::GetCurrFileName(CString& fileName)
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	pTreeView->GetCurrNodeFileName(fileName);
}

DWORD AnimationInfoView::GetCurrSceneId()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrSceneId();
}


void AnimationInfoView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (GetMyWorld())
	{
		DWORD sceneId = GetCurrSceneId();
		CString fileName;
		DWORD id = GetCurrAnimationID();
		GetCurrFileName(fileName);

		for (int i = 0 ; i < m_world.m_numberOfScenes; i++)
		{
			if (m_world.m_scenes[i].m_sceneID == sceneId)
			{				
				m_world.m_scenes[i].m_animations.ScanInit(DIRECTION_FORWARD);
				
				for (int j = 0; j < m_world.m_scenes[i].m_animationCount; j++)
				{	            
					m_currAnimationInfo = &m_world.m_scenes[i].m_animations.NextElement(); 
					if (m_currAnimationInfo->m_animationID == id &&
						  m_currAnimationInfo->m_fileNameVideo == (CStdString)fileName)
					{
						m_animationID = m_currAnimationInfo->m_animationID;
						m_fileNameVideo = m_currAnimationInfo->m_fileNameVideo;
						m_fileNameAudio = m_currAnimationInfo->m_fileNameAudio;
						m_widthEnd = m_currAnimationInfo->m_widthEnd;
						m_widthStart = m_currAnimationInfo->m_widthStart;
						m_zEnd = m_currAnimationInfo->m_zEnd;
						m_currentFrame = m_currAnimationInfo->m_currentFrame;
						m_endClockValue = m_currAnimationInfo->m_endClockValue;
						m_endFrame = m_currAnimationInfo->m_endFrame;
						m_frameExpar = m_currAnimationInfo->m_frameExparation;
						m_heightEnd = m_currAnimationInfo->m_heightEnd;
						m_heightStart = m_currAnimationInfo->m_heightStart;
						m_isDoAudio = m_currAnimationInfo->m_doAudio;
						m_isDoVideo = m_currAnimationInfo->m_doVideo;
						m_leftEnd = m_currAnimationInfo->m_leftEnd;
						m_leftStart = m_currAnimationInfo->m_leftStart;
						m_loopRemaining = m_currAnimationInfo->m_loopsRemaining;
						m_startClockValue = m_currAnimationInfo->m_startClockValue;
						m_startFrame = m_currAnimationInfo->m_startFrame;
						m_startPlayTime = m_currAnimationInfo->m_playStartValue;
						m_startVolumeTime = m_currAnimationInfo->m_volStartClock;
						m_endVolumeTime = m_currAnimationInfo->m_volEndClock;	
						m_topEnd = m_currAnimationInfo->m_topEnd;
						m_topStart = m_currAnimationInfo->m_topStart;
						m_volumeEnd = m_currAnimationInfo->m_volEnd;
						m_volumeStart = m_currAnimationInfo->m_volStart;
						m_zStart = m_currAnimationInfo->m_zStart;

						UpdateData(FALSE);
						break;
					}		
				}
			}
		}
	}	
}

void AnimationInfoView::OnRuntimeSave()
{
	UpdateData(TRUE);
	if (m_currAnimationInfo != NULL)
	{
		m_currAnimationInfo->m_animationID = m_animationID;
		m_currAnimationInfo->m_fileNameVideo= m_fileNameVideo;
		m_currAnimationInfo->m_fileNameAudio = m_fileNameAudio ;
		m_currAnimationInfo->m_widthEnd	= m_widthEnd ;
		m_currAnimationInfo->m_widthStart =	m_widthStart ;
		m_currAnimationInfo->m_zEnd =	m_zEnd ;
		m_currAnimationInfo->m_currentFrame =	m_currentFrame ;
		m_currAnimationInfo->m_endClockValue =	m_endClockValue ;
		m_currAnimationInfo->m_endFrame	= m_endFrame ;
		m_currAnimationInfo->m_frameExparation =	m_frameExpar ;
		m_currAnimationInfo->m_heightEnd = m_heightEnd;
		m_currAnimationInfo->m_heightStart =	m_heightStart  ;
		m_currAnimationInfo->m_doAudio = m_isDoAudio ? true : false ;
		m_currAnimationInfo->m_doVideo =	m_isDoVideo ? true : false  ;
		m_currAnimationInfo->m_leftEnd =	m_leftEnd ;
		m_currAnimationInfo->m_leftStart =	m_leftStart ;
		m_currAnimationInfo->m_loopsRemaining =	m_loopRemaining ;
		m_currAnimationInfo->m_startClockValue =	m_startClockValue ;
		m_currAnimationInfo->m_startFrame	= m_startFrame ;
		m_currAnimationInfo->m_playStartValue =	m_startPlayTime ;
		m_currAnimationInfo->m_volStartClock =	m_startVolumeTime ;
		m_currAnimationInfo->m_volEndClock = m_endVolumeTime;	
		m_currAnimationInfo->m_topEnd	= m_topEnd;
		m_currAnimationInfo->m_topStart =	m_topStart;
		m_currAnimationInfo->m_volEnd	= m_volumeEnd ;
		m_currAnimationInfo->m_volStart =	m_volumeStart ;
		m_currAnimationInfo->m_zStart	= m_zStart;		
	
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

void AnimationInfoView::OnUpdateWorldObject()
{
  GetMyWorld();
}

void AnimationInfoView::OnBrowseAudioFileName() 
{
	CFileDialog dlg(TRUE,"*.ogg");
	//set title
	dlg.m_ofn.lpstrTitle = "Browse audio file name";
	
	//set filter

	CString filterStr;
	filterStr	= ("Audio files (*.ogg)"); 
	filterStr += (TCHAR)NULL;
	filterStr += "*.ogg";
	filterStr += (TCHAR)NULL;

	dlg.m_ofn.lpstrFilter = filterStr;
	
	dlg.m_ofn.Flags &= ~(OFN_EXPLORER);
	if (dlg.DoModal() == IDOK)
	{     
		m_fileNameAudio = dlg.m_ofn.lpstrFile;
		int indx = m_fileNameAudio.ReverseFind('\\');
		m_fileNameAudio = m_fileNameAudio.Right(m_fileNameAudio.GetLength() - indx - 1);
		UpdateData(FALSE);
	}	
}
void AnimationInfoView::OnKillfocus() 
{
	UpdateData(TRUE);	
}
