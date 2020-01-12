// ImageInfoView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "ImageInfoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ImageInfoView

IMPLEMENT_DYNCREATE(ImageInfoView, CFormView)

ImageInfoView::ImageInfoView()
	: CFormView(ImageInfoView::IDD)
{
	//{{AFX_DATA_INIT(ImageInfoView)
	m_alphaFileName = _T("");
	m_currentFrame = 0;
	m_currentFrameClockValue = 0;
	m_endClockValue = 0;
	m_fileName = _T("");
	m_frameCount = 0;
	m_frameInterval = 0;
	m_heightEnd = 0;
	m_heightStart = 0;
	m_imageID = 0;
	m_isImageVisible = FALSE;
	m_leftAlpha = 0;
	m_leftEnd = 0;
	m_leftStart = 0;
	m_loopRemaining = 0;
	m_startClockValue = 0;
	m_topAlpha = 0;
	m_topEnd = 0;
	m_topStart = 0;
	m_widthEnd = 0;
	m_widthStart = 0;
	m_zEnd = 0;
	m_zStart = 0;
	//}}AFX_DATA_INIT
	m_currImagePtr = NULL;
}

ImageInfoView::~ImageInfoView()
{

}

void ImageInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ImageInfoView)
	DDX_Control(pDX, IDC_SPIN_MAP_OFFSET_Y, m_mapOffsetY);
	DDX_Control(pDX, IDC_SPIN_MAP_OFFSET_X, m_mapOffsetX);
	DDX_Control(pDX, IDC_SPIN_INIT_Y, m_spinInitY);
	DDX_Control(pDX, IDC_SPIN_INIT_X, m_spinInitX);
	DDX_Control(pDX, IDC_SPIN_INIT_WIDTH, m_spinInitWidth);
	DDX_Control(pDX, IDC_SPIN_INIT_HEIGHT, m_spinInitHeight);
	DDX_Control(pDX, IDC_SPIN_INIT_DIST, m_spinInitDist);
	DDX_Control(pDX, IDC_SPIN_FINISH_Y, m_spinFinishY);
	DDX_Control(pDX, IDC_SPIN_FINISH_X, m_spinFinishX);
	DDX_Control(pDX, IDC_SPIN_FINISH_WIDTH, m_spinFinishWidht);
	DDX_Control(pDX, IDC_SPIN_FINISH_HEIGHT, m_spinFinishHeight);
	DDX_Control(pDX, IDC_SPIN_FINISH_DIST, m_spinFinishDist);
	DDX_Text(pDX, IDC_ALPHA_FILE_NAME, m_alphaFileName);
	DDX_Text(pDX, IDC_CURRENT_FRAME, m_currentFrame);
	DDX_Text(pDX, IDC_CURRENT_FRAME_CLOCK_VALUE, m_currentFrameClockValue);
	DDX_Text(pDX, IDC_END_CLOCK_VALUE, m_endClockValue);
	DDX_Text(pDX, IDC_FILE_NAME, m_fileName);
	DDX_Text(pDX, IDC_FRAME_COUNT, m_frameCount);
	DDX_Text(pDX, IDC_FRAME_INTERVAL, m_frameInterval);
	DDX_Text(pDX, IDC_HEIGHT_END, m_heightEnd);
	DDX_Text(pDX, IDC_HEIGHT_START, m_heightStart);
	DDX_Text(pDX, IDC_IMAGE_ID, m_imageID);
	DDX_Check(pDX, IDC_IS_IMAGE_VISIBLE, m_isImageVisible);
	DDX_Text(pDX, IDC_LEFT_ALPHA, m_leftAlpha);
	DDX_Text(pDX, IDC_LEFT_END, m_leftEnd);
	DDX_Text(pDX, IDC_LEFT_START, m_leftStart);
	DDX_Text(pDX, IDC_LOOP_REMAINING, m_loopRemaining);
	DDX_Text(pDX, IDC_START_CLOCK_VALUE, m_startClockValue);
	DDX_Text(pDX, IDC_TOP_ALPHA, m_topAlpha);
	DDX_Text(pDX, IDC_TOP_END, m_topEnd);
	DDX_Text(pDX, IDC_TOP_START, m_topStart);
	DDX_Text(pDX, IDC_WIDTH_END, m_widthEnd);
	DDX_Text(pDX, IDC_WIDTH_START, m_widthStart);
	DDX_Text(pDX, IDC_Z_END, m_zEnd);
	DDX_Text(pDX, IDC_Z_START, m_zStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ImageInfoView, CFormView)
	//{{AFX_MSG_MAP(ImageInfoView)
	ON_BN_CLICKED(IDC_BROWSE_ALPHA_FILE_NAME, OnBrowseAlphaFileName)
	//}}AFX_MSG_MAP
	ON_MESSAGE(RUNTIME_SAVE_MESSAGE,OnRuntimeSave)	
	ON_MESSAGE(UPDATE_DELETING_IN_WORLD,OnUpdateWorldObject)
	ON_EN_KILLFOCUS(IDC_LOOP_REMAINING, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_WIDTH_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_HEIGHT_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LEFT_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TOP_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_Z_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_START_CLOCK_VALUE, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_WIDTH_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_HEIGHT_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LEFT_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TOP_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_Z_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_END_CLOCK_VALUE, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_FRAME_COUNT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_FRAME_INTERVAL, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_CURRENT_FRAME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_CURRENT_FRAME_CLOCK_VALUE, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LEFT_ALPHA, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TOP_ALPHA, OnKillfocus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ImageInfoView diagnostics

#ifdef _DEBUG
void ImageInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

void ImageInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ImageInfoView message handlers
CWorldConstructKitDoc* ImageInfoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));
	return (CWorldConstructKitDoc*)m_pDocument;
}

BOOL ImageInfoView::GetMyWorld()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	m_worldId = pTreeView->GetCurrWorldID();	
	
	CWorldConstructKitDoc* doc = GetDocument();
	BOOL result = doc->m_worldMap.Lookup(m_worldId,m_world);	
  return result;
}

DWORD ImageInfoView::GetCurrImageID()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrNodeID();
}

void ImageInfoView::GetCurrFileName(CString& fileName)
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	pTreeView->GetCurrNodeFileName(fileName);
}

DWORD ImageInfoView::GetCurrSceneId()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrSceneId();
}

void ImageInfoView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (GetMyWorld())
	{
		DWORD sceneId = GetCurrSceneId();
		CString fileName;
		DWORD id = GetCurrImageID();
		GetCurrFileName(fileName);

		for (int i = 0 ; i < m_world.m_numberOfScenes; i++)
		{
			if (m_world.m_scenes[i].m_sceneID == sceneId)
			{				
				m_world.m_scenes[i].m_images.ScanInit(DIRECTION_FORWARD);
				for (int j = 0; j < m_world.m_scenes[i].m_imageCount; j++)
				{
					m_currImagePtr = &m_world.m_scenes[i].m_images.NextElement(); 
					if (m_currImagePtr->m_imageID == id &&
						  m_currImagePtr->m_fileName == (CStdString)fileName)
					{
						m_alphaFileName = m_currImagePtr->m_aplhaFileName;
						m_currentFrame = m_currImagePtr->m_currentFrame;
						m_currentFrameClockValue = m_currImagePtr->m_currentFrameClockValue;
						m_endClockValue = m_currImagePtr->m_endClockValue;
						m_fileName = m_currImagePtr->m_fileName;
						m_frameCount = m_currImagePtr->m_frameCount;
						m_frameInterval = m_currImagePtr->m_frameInterval;
						m_heightEnd = m_currImagePtr->m_heightEnd;
						m_heightStart = m_currImagePtr->m_heightStart;
						m_imageID = m_currImagePtr->m_imageID;
						m_isImageVisible = m_currImagePtr->m_imageIsVisible;
						m_leftAlpha = m_currImagePtr->m_leftAlpha;
						m_leftEnd = m_currImagePtr->m_leftEnd;
						m_leftStart = m_currImagePtr->m_leftStart;
						m_loopRemaining = m_currImagePtr->m_loopsRemaining;
						m_startClockValue = m_currImagePtr->m_startClockValue;
						m_topAlpha = m_currImagePtr->m_topAlpha;
						m_topEnd = m_currImagePtr->m_topEnd;
						m_topStart = m_currImagePtr->m_topStart;
						m_widthEnd = m_currImagePtr->m_widthEnd;
						m_widthStart = m_currImagePtr->m_widthStart;
						m_zEnd = m_currImagePtr->m_zEnd;
						m_zStart = m_currImagePtr->m_zStart;

						UpdateData(FALSE);
						break;
					}		
				}
			}
		}
	}	
}

void ImageInfoView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	m_mapOffsetY.SetBuddy(GetDlgItem(IDC_TOP_ALPHA));
	m_mapOffsetX.SetBuddy(GetDlgItem(IDC_LEFT_ALPHA));
	m_spinInitY.SetBuddy(GetDlgItem(IDC_TOP_START));
	m_spinInitX.SetBuddy(GetDlgItem(IDC_LEFT_START));
	m_spinInitWidth.SetBuddy(GetDlgItem(IDC_WIDTH_START));
	m_spinInitHeight.SetBuddy(GetDlgItem(IDC_HEIGHT_START));
	m_spinInitDist.SetBuddy(GetDlgItem(IDC_Z_START));
	m_spinFinishY.SetBuddy(GetDlgItem(IDC_TOP_END));
	m_spinFinishX.SetBuddy(GetDlgItem(IDC_LEFT_END));
	m_spinFinishWidht.SetBuddy(GetDlgItem(IDC_WIDTH_END));
	m_spinFinishHeight.SetBuddy(GetDlgItem(IDC_HEIGHT_END));
	m_spinFinishDist.SetBuddy(GetDlgItem(IDC_Z_END));

	m_mapOffsetY.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_mapOffsetX.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinInitY.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinInitX.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinInitWidth.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinInitHeight.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinInitDist.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinFinishY.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinFinishX.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinFinishWidht.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinFinishHeight.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinFinishDist.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);

}

void ImageInfoView::OnRuntimeSave()
{
	UpdateData(TRUE);
	if (m_currImagePtr != NULL)
	{
		m_currImagePtr->m_aplhaFileName = m_alphaFileName;
		m_currImagePtr->m_currentFrame = m_currentFrame ;
		m_currImagePtr->m_currentFrameClockValue = m_currentFrameClockValue ;
		m_currImagePtr->m_endClockValue	= m_endClockValue;
		m_currImagePtr->m_fileName = m_fileName  ;
		m_currImagePtr->m_frameCount = m_frameCount ;
		m_currImagePtr->m_frameInterval =	m_frameInterval ;
		m_currImagePtr->m_heightEnd =	m_heightEnd;
		m_currImagePtr->m_heightStart =	m_heightStart;
		m_currImagePtr->m_imageID =	m_imageID ;
		m_currImagePtr->m_imageIsVisible = m_isImageVisible ? true : false;
		m_currImagePtr->m_leftAlpha =	m_leftAlpha;
		m_currImagePtr->m_leftEnd = m_leftEnd ;
		m_currImagePtr->m_leftStart =	m_leftStart;
		m_currImagePtr->m_loopsRemaining = m_loopRemaining ;
		m_currImagePtr->m_startClockValue =	m_startClockValue;
		m_currImagePtr->m_topAlpha = m_topAlpha ;
		m_currImagePtr->m_topEnd = m_topEnd ;
		m_currImagePtr->m_topStart = m_topStart ;
		m_currImagePtr->m_widthEnd =	m_widthEnd  ;
		m_currImagePtr->m_widthStart =	m_widthStart  ;
		m_currImagePtr->m_zEnd =	m_zEnd  ;
		m_currImagePtr->m_zStart =	m_zStart ;

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

void ImageInfoView::OnBrowseAlphaFileName() 
{
	CFileDialog dlg(TRUE,"*.png");
	//set title
	dlg.m_ofn.lpstrTitle = "Browse alpha file name";
	
	//set filter

	CString filterStr;
	filterStr	= ("Icon files (*.png)"); 
	filterStr += (TCHAR)NULL;
	filterStr += "*.png";
	filterStr += (TCHAR)NULL;

	dlg.m_ofn.lpstrFilter = filterStr;
	
	dlg.m_ofn.Flags &= ~(OFN_EXPLORER);
	if (dlg.DoModal() == IDOK)
	{     
		m_alphaFileName = dlg.m_ofn.lpstrFile;
		int indx = m_alphaFileName.ReverseFind('\\');
		m_alphaFileName = m_alphaFileName.Right(m_alphaFileName.GetLength() - indx - 1);
		UpdateData(FALSE);
	}		
}

void ImageInfoView::OnUpdateWorldObject()
{
  GetMyWorld();
}

void ImageInfoView::OnKillfocus() 
{
	UpdateData(TRUE);	
}
