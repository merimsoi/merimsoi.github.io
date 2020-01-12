// StagingInfoView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "StagingInfoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StagingInfoView

IMPLEMENT_DYNCREATE(StagingInfoView, CFormView)

StagingInfoView::StagingInfoView()
	: CFormView(StagingInfoView::IDD)
{
	//{{AFX_DATA_INIT(StagingInfoView)
	m_alphaFileName = _T("");
	m_cameraAngle = 0;
	m_cameraHeight = 0;
	m_colorCount = 0;
	m_endClockValue = 0;
	m_heightEnd = 0;
	m_heightStart = 0;
	m_imageFileName = _T("");
	m_leftAlpha = 0;
	m_leftEnd = 0;
	m_leftStart = 0;
	m_lightB = 0;
	m_lightG = 0;
	m_lightR = 0;
	m_mapFileName = _T("");
	m_mapHeight = 0;
	m_mapLeft = 0;
	m_mapTop = 0;
	m_mapWidth = 0;
	m_topAlpha = 0;
	m_topEnd = 0;
	m_topStart = 0;
	m_widthEnd = 0;
	m_widthStart = 0;
	m_startClockValue = 0;
	m_lightingFileName = _T("");
	m_indx = 0;
	m_lightAngleX = 0;
	m_lightAngleY = 0;
	m_lightAngleZ = 0;
	m_height = 0;
	//}}AFX_DATA_INIT
	m_currStagingInfoPtr = NULL;
}

StagingInfoView::~StagingInfoView()
{
}

void StagingInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(StagingInfoView)
	DDX_Control(pDX, IDC_SPIN_MAP_OFFSET_Y, m_spinMapOffsetY);
	DDX_Control(pDX, IDC_SPIN_MAP_OFFSET_X, m_spinMapOffsetX);
	DDX_Control(pDX, IDC_SPIN_MAP_HEIGHT, m_spinMapHeight);
	DDX_Control(pDX, IDC_SPIN_IMAGE_Y, m_spinImageY);
	DDX_Control(pDX, IDC_SPIN_IMAGE_X, m_spinImageX);
	DDX_Control(pDX, IDC_SPIN_IMAGE_WIDTH, m_spinImageWidth);
	DDX_Control(pDX, IDC_SPIN_IMAGE_HEIGHT, m_spinImageHeight);
	DDX_Control(pDX, IDC_SPIN_CAMERA_HEIGHT, m_spinCameraHeight);
	DDX_Control(pDX, IDC_SPIN_CAMERA_ANGLE, m_spinCameraAngle);
	DDX_Control(pDX, IDC_SPIN_BACK_INIT_Y, m_spinBackInitY);
	DDX_Control(pDX, IDC_SPIN_BACK_INIT_X, m_spinBackInitX);
	DDX_Control(pDX, IDC_SPIN_BACK_INIT_WIDTH, m_spinBackInitWidht);
	DDX_Control(pDX, IDC_SPIN_BACK_INIT_HEIGHT, m_spinBackInitHeight);
	DDX_Control(pDX, IDC_SPIN_BACK_FINISH_Y, m_spinBackFinishY);
	DDX_Control(pDX, IDC_SPIN_BACK_FINISH_X, m_spinBackFinishX);
	DDX_Control(pDX, IDC_SPIN_BACK_FINISH_WIDTH, m_spinBackFinishWidht);
	DDX_Control(pDX, IDC_SPIN_BACK_FINISH_HEIGHT, m_spinBackFinishHeight);
	DDX_Control(pDX, IDC_SPIN_RED, m_spinred);
	DDX_Control(pDX, IDC_SPIN_GREEN, m_spinGreen);
	DDX_Control(pDX, IDC_SPIN_BLUE, m_spinBlue);
	DDX_Control(pDX, IDC_LIST_MAP_ALTITUDE_INDEX, m_altitudeIndexMapList);
	DDX_Control(pDX, IDC_LIGHTING_MODE, m_comboLightingMode);
	DDX_Text(pDX, IDC_ALPHA_FILE_NAME, m_alphaFileName);
	DDX_Text(pDX, IDC_CAMERA_ANGLE, m_cameraAngle);
	DDX_Text(pDX, IDC_CAMERA_HEIGHT, m_cameraHeight);
	DDX_Text(pDX, IDC_COLOR_COUNT, m_colorCount);
	DDX_Text(pDX, IDC_END_CLOCK_VALUE, m_endClockValue);
	DDX_Text(pDX, IDC_HEIGHT_END, m_heightEnd);
	DDX_Text(pDX, IDC_HEIGHT_START, m_heightStart);
	DDX_Text(pDX, IDC_IMAGE_FILE_NAME, m_imageFileName);
	DDX_Text(pDX, IDC_LEFT_ALPHA, m_leftAlpha);
	DDX_Text(pDX, IDC_LEFT_END, m_leftEnd);
	DDX_Text(pDX, IDC_LEFT_START, m_leftStart);
	DDX_Text(pDX, IDC_LIGHT_B, m_lightB);
	DDV_MinMaxInt(pDX, m_lightB, RGB_MIN_VAL, RGB_MAX_VAL);
	DDX_Text(pDX, IDC_LIGHT_G, m_lightG);
	DDV_MinMaxInt(pDX, m_lightG, RGB_MIN_VAL, RGB_MAX_VAL);
	DDX_Text(pDX, IDC_LIGHT_R, m_lightR);
	DDV_MinMaxInt(pDX, m_lightR, RGB_MIN_VAL, RGB_MAX_VAL);
	DDX_Text(pDX, IDC_MAP_FILE_NAME, m_mapFileName);
	DDX_Text(pDX, IDC_MAP_HEIGHT, m_mapHeight);
	DDX_Text(pDX, IDC_MAP_LEFT, m_mapLeft);
	DDX_Text(pDX, IDC_MAP_TOP, m_mapTop);
	DDX_Text(pDX, IDC_MAP_WIDTH, m_mapWidth);
	DDX_Text(pDX, IDC_TOP_ALPHA, m_topAlpha);
	DDX_Text(pDX, IDC_TOP_END, m_topEnd);
	DDX_Text(pDX, IDC_TOP_START, m_topStart);
	DDX_Text(pDX, IDC_WIDTH_END, m_widthEnd);
	DDX_Text(pDX, IDC_WIDTH_START, m_widthStart);
	DDX_Text(pDX, IDC_START_CLOCK_VALUE1, m_startClockValue);
	DDX_Text(pDX, IDC_LIGHTING_FILE_NAME, m_lightingFileName);
	DDX_Text(pDX, IDC_INDEX, m_indx);
	DDX_Text(pDX, IDC_LIGHT_ANGLE_X, m_lightAngleX);
	DDX_Text(pDX, IDC_LIGHT_ANGLE_Y, m_lightAngleY);
	DDX_Text(pDX, IDC_LIGHT_ANGLE_Z, m_lightAngleZ);
	DDX_Text(pDX, IDC_HEIGHT, m_height);
	//}}AFX_DATA_MAP
	DDV_MinMaxInt(pDX, m_cameraAngle, MIN_ANGLE, MAX_ANGLE);
}


BEGIN_MESSAGE_MAP(StagingInfoView, CFormView)
	//{{AFX_MSG_MAP(StagingInfoView)
	ON_LBN_SELCHANGE(IDC_LIST_MAP_ALTITUDE_INDEX, OnSelchangeListMapAltitudeIndex)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_BROWSE_ALPHA_FILE, OnBrowseAlphaFile)
	ON_BN_CLICKED(IDC_BROWSE_MAP_FILE, OnBrowseMapFile)
	ON_BN_CLICKED(IDC_BROWSE_LIGHT_FILE, OnBrowseLightFile)
	ON_BN_CLICKED(IDC_BROWSE_IMAGE_FILE_NAME, OnBrowseImageFileName)
	//}}AFX_MSG_MAP
	ON_MESSAGE(RUNTIME_SAVE_MESSAGE,OnRuntimeSave)
	ON_MESSAGE(UPDATE_DELETING_IN_WORLD,OnUpdateWorldObject)
	ON_EN_KILLFOCUS(IDC_CAMERA_ANGLE, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_CAMERA_HEIGHT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LEFT_ALPHA, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TOP_ALPHA, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_HEIGHT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_WIDTH_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_HEIGHT_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_START_CLOCK_VALUE1, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LEFT_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TOP_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_WIDTH_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_HEIGHT_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_END_CLOCK_VALUE, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LEFT_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TOP_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_MAP_WIDTH, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_MAP_HEIGHT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_MAP_LEFT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_MAP_TOP, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_COLOR_COUNT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LIGHT_R, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LIGHT_B, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LIGHT_G, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LIGHT_ANGLE_X, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LIGHT_ANGLE_Y, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LIGHT_ANGLE_Z, OnKillfocus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StagingInfoView diagnostics

#ifdef _DEBUG
void StagingInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

void StagingInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// StagingInfoView message handlers
CWorldConstructKitDoc* StagingInfoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));
	return (CWorldConstructKitDoc*)m_pDocument;
}

BOOL StagingInfoView::GetMyWorld()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	m_worldId = pTreeView->GetCurrWorldID();	
	
	CWorldConstructKitDoc* doc = GetDocument();
	BOOL result = doc->m_worldMap.Lookup(m_worldId,m_world);	
  return result;
}

DWORD StagingInfoView::GetCurrSceneId()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrSceneId();
}


void StagingInfoView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (GetMyWorld())
	{
		DWORD sceneId = GetCurrSceneId();

		for (int i = 0 ; i < m_world.m_numberOfScenes; i++)
		{
			if (m_world.m_scenes[i].m_sceneID == sceneId)
			{		
				m_currStagingInfoPtr = &m_world.m_scenes[i].stage;

				m_comboLightingMode.SetCurSel(m_currStagingInfoPtr->m_lightingMode);
				m_colorCount = m_currStagingInfoPtr->m_mapColorCount;			
				m_alphaFileName = m_currStagingInfoPtr->m_alphaFileName;
				m_cameraAngle = m_currStagingInfoPtr->m_cameraAngle;
				m_cameraHeight = m_currStagingInfoPtr->m_cameraHeight;			
				m_endClockValue = m_currStagingInfoPtr->m_endClockValue;
				m_heightEnd = m_currStagingInfoPtr->m_heightEnd;
				m_heightStart = m_currStagingInfoPtr->m_heightStart;
				m_imageFileName = m_currStagingInfoPtr->m_imageFileName;
				m_leftAlpha = m_currStagingInfoPtr->m_leftAlpha;
				m_leftEnd = m_currStagingInfoPtr->m_leftEnd;
				m_leftStart = m_currStagingInfoPtr->m_leftStart;
				m_lightB = m_currStagingInfoPtr->m_lightB;
				m_lightG = m_currStagingInfoPtr->m_lightG;
				m_lightR = m_currStagingInfoPtr->m_lightR;
				m_lightingFileName = m_currStagingInfoPtr->m_lighterFileName;
				m_mapFileName = m_currStagingInfoPtr->m_mapFileName;
				m_mapHeight =m_currStagingInfoPtr->m_mapHeight;
				m_mapLeft = m_currStagingInfoPtr->m_mapLeft;
				m_mapTop = m_currStagingInfoPtr->m_mapTop;
				m_mapWidth = m_currStagingInfoPtr->m_mapWidth;
				m_topAlpha = m_currStagingInfoPtr->m_topAlpha;
				m_topEnd = m_currStagingInfoPtr->m_topEnd;
				m_topStart = m_currStagingInfoPtr->m_topStart;
				m_widthEnd = m_currStagingInfoPtr->m_widthEnd;
				m_widthStart = m_currStagingInfoPtr->m_widthStart;
				m_startClockValue = m_currStagingInfoPtr->m_startClockValue;
				m_lightAngleX = m_currStagingInfoPtr->m_lightAngleX;
				m_lightAngleY = m_currStagingInfoPtr->m_lightAngleY;
				m_lightAngleZ = m_currStagingInfoPtr->m_lightAngleZ;

				UpdateData(FALSE);
				CString mapLineStr;
				for (int j = 1; j <= ALTITUDE_MAP_COUNT; j++)
				{
					mapLineStr.Format("%d --> %d",j,m_currStagingInfoPtr->m_mapAltitudeIndex[j]);
					int indx = m_altitudeIndexMapList.AddString(mapLineStr);
					m_altitudeIndexMapList.SetItemData(indx,j);
					m_altitudeIndexMapList.SetCurSel(0);
					OnSelchangeListMapAltitudeIndex();
				}
				
				break;
			}
		}
	}	
}

void StagingInfoView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	m_spinBlue.SetBuddy(GetDlgItem(IDC_LIGHT_B));
	m_spinGreen.SetBuddy(GetDlgItem(IDC_LIGHT_G));
	m_spinred.SetBuddy(GetDlgItem(IDC_LIGHT_R));

	m_spinMapOffsetY.SetBuddy(GetDlgItem(IDC_TOP_ALPHA));     
	m_spinMapOffsetX.SetBuddy(GetDlgItem(IDC_LEFT_ALPHA));     
	m_spinMapHeight.SetBuddy(GetDlgItem(IDC_HEIGHT));      
	m_spinImageY.SetBuddy(GetDlgItem(IDC_MAP_TOP));         
	m_spinImageX.SetBuddy(GetDlgItem(IDC_MAP_LEFT));         
	m_spinImageWidth.SetBuddy(GetDlgItem(IDC_MAP_WIDTH));     
	m_spinImageHeight.SetBuddy(GetDlgItem(IDC_MAP_HEIGHT));    
	m_spinCameraHeight.SetBuddy(GetDlgItem(IDC_CAMERA_HEIGHT));   
	m_spinCameraAngle.SetBuddy(GetDlgItem(IDC_CAMERA_ANGLE));    
	m_spinBackInitY.SetBuddy(GetDlgItem(IDC_TOP_START));      
	m_spinBackInitX.SetBuddy(GetDlgItem(IDC_LEFT_START));      
	m_spinBackInitWidht.SetBuddy(GetDlgItem(IDC_WIDTH_START));  
	m_spinBackInitHeight.SetBuddy(GetDlgItem(IDC_HEIGHT_START)); 
	m_spinBackFinishY.SetBuddy(GetDlgItem(IDC_TOP_END));    
	m_spinBackFinishX.SetBuddy(GetDlgItem(IDC_LEFT_END));    
	m_spinBackFinishWidht.SetBuddy(GetDlgItem(IDC_WIDTH_END));
	m_spinBackFinishHeight.SetBuddy(GetDlgItem(IDC_HEIGHT_END));
		
	m_spinMapOffsetY.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);     
	m_spinMapOffsetX.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);     
	m_spinMapHeight.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);      
	m_spinImageY.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);         
	m_spinImageX.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);         
	m_spinImageWidth.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);     
	m_spinImageHeight.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);    
	m_spinCameraHeight.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);   
	m_spinCameraAngle.SetRange(MIN_ANGLE,MAX_ANGLE);    
	m_spinBackInitY.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);      
	m_spinBackInitX.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);      
	m_spinBackInitWidht.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);  
	m_spinBackInitHeight.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE); 
	m_spinBackFinishY.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);    
	m_spinBackFinishX.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);    
	m_spinBackFinishWidht.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinBackFinishHeight.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);		

	m_spinBlue.SetRange(RGB_MIN_VAL,RGB_MAX_VAL);
	m_spinGreen.SetRange(RGB_MIN_VAL,RGB_MAX_VAL);
	m_spinred.SetRange(RGB_MIN_VAL,RGB_MAX_VAL);

	CString str;
	CSize   sz;
	int     maxLen = 0;
	CDC*    pDC = m_altitudeIndexMapList.GetDC();
	for (int i = 0;i < m_altitudeIndexMapList.GetCount(); i++)
	{
		m_altitudeIndexMapList.GetText( i, str );
		sz = pDC->GetTextExtent(str);
		
		if (sz.cx > maxLen)
      maxLen = sz.cx;
	}
	m_altitudeIndexMapList.ReleaseDC(pDC);
	
	// Set the column width of the first column to be one and 1/3 units
	// of the largest string. 
	m_altitudeIndexMapList.SetColumnWidth(maxLen + 2);
	
}

void StagingInfoView::OnRuntimeSave()
{
	UpdateData(TRUE);
	if (m_currStagingInfoPtr != NULL)
	{	  
		m_currStagingInfoPtr->m_lightingMode = (LightingModeType)m_comboLightingMode.GetCurSel();
		m_currStagingInfoPtr->m_mapColorCount =	m_colorCount;			
		m_currStagingInfoPtr->m_alphaFileName	= m_alphaFileName ;
		m_currStagingInfoPtr->m_cameraAngle	= m_cameraAngle;
		m_currStagingInfoPtr->m_cameraHeight = m_cameraHeight;			
		m_currStagingInfoPtr->m_endClockValue = m_endClockValue;
		m_currStagingInfoPtr->m_heightEnd	= m_heightEnd;
		m_currStagingInfoPtr->m_heightStart =	m_heightStart;
		m_currStagingInfoPtr->m_imageFileName = m_imageFileName;
		m_currStagingInfoPtr->m_leftAlpha	= m_leftAlpha;
		m_currStagingInfoPtr->m_leftEnd	= m_leftEnd;
		m_currStagingInfoPtr->m_leftStart	= m_leftStart;
		m_currStagingInfoPtr->m_lightB = m_lightB;
		m_currStagingInfoPtr->m_lightG = m_lightG ;
		m_currStagingInfoPtr->m_lightR = m_lightR;
		m_currStagingInfoPtr->m_lighterFileName	= m_lightingFileName ;
		m_currStagingInfoPtr->m_mapFileName =	m_mapFileName;
		m_currStagingInfoPtr->m_mapHeight	= m_mapHeight;
		m_currStagingInfoPtr->m_mapLeft	= m_mapLeft;
		m_currStagingInfoPtr->m_mapTop = m_mapTop  ;
		m_currStagingInfoPtr->m_mapWidth = m_mapWidth;
		m_currStagingInfoPtr->m_topAlpha =	m_topAlpha;
		m_currStagingInfoPtr->m_topEnd = m_topEnd ;
		m_currStagingInfoPtr->m_topStart = m_topStart ;
		m_currStagingInfoPtr->m_widthEnd = m_widthEnd;
		m_currStagingInfoPtr->m_widthStart =	m_widthStart ;
		m_currStagingInfoPtr->m_startClockValue	= m_startClockValue;
		m_currStagingInfoPtr->m_lightAngleX = m_lightAngleX;
		m_currStagingInfoPtr->m_lightAngleY = m_lightAngleY ;
		m_currStagingInfoPtr->m_lightAngleZ = m_lightAngleZ;


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

void StagingInfoView::OnSelchangeListMapAltitudeIndex() 
{
	UpdateData(TRUE);
	int selIndx = m_altitudeIndexMapList.GetCurSel();	
	int arrIndx = m_altitudeIndexMapList.GetItemData(selIndx);
	m_indx = arrIndx;
	m_height = m_currStagingInfoPtr->m_mapAltitudeIndex[arrIndx];
	UpdateData(FALSE);
}

void StagingInfoView::OnEdit() 
{
	UpdateData(TRUE);
	int arrIndx = m_indx;
	m_currStagingInfoPtr->m_mapAltitudeIndex[arrIndx] = m_height;
	m_altitudeIndexMapList.DeleteString(arrIndx - 1);

	CString mapLineStr;
	mapLineStr.Format("%d --> %d",arrIndx,m_currStagingInfoPtr->m_mapAltitudeIndex[arrIndx]);
	int indx = m_altitudeIndexMapList.InsertString(arrIndx - 1,mapLineStr);
	m_altitudeIndexMapList.SetItemData(indx,arrIndx);
}

void StagingInfoView::OnBrowseAlphaFile() 
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

void StagingInfoView::OnBrowseMapFile() 
{
	CFileDialog dlg(TRUE,"*.png");
	//set title
	dlg.m_ofn.lpstrTitle = "Browse map file name";
	
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
		m_mapFileName= dlg.m_ofn.lpstrFile;
		int indx = m_mapFileName.ReverseFind('\\');
		m_mapFileName = m_mapFileName.Right(m_mapFileName.GetLength() - indx - 1);
		UpdateData(FALSE);
	}				
}

void StagingInfoView::OnBrowseLightFile() 
{
	CFileDialog dlg(TRUE,"*.png");
	//set title
	dlg.m_ofn.lpstrTitle = "Browse lighting file name";
	
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
		m_lightingFileName = dlg.m_ofn.lpstrFile;
		int indx = m_lightingFileName.ReverseFind('\\');
		m_lightingFileName = m_lightingFileName.Right(m_lightingFileName.GetLength() - indx - 1);
		UpdateData(FALSE);
	}				
}

void StagingInfoView::OnBrowseImageFileName() 
{
	CFileDialog dlg(TRUE,"*.png");
	//set title
	dlg.m_ofn.lpstrTitle = "Browse image file name";
	
	//set filter

	CString filterStr;
	filterStr	= ("Image files (*.jpg)"); 
	filterStr += (TCHAR)NULL;
	filterStr += "*.jpg";
	filterStr += (TCHAR)NULL;
	filterStr += ("Image files(*.jpeg)");
	filterStr += (TCHAR)NULL;
	filterStr += "*.jpeg";
	filterStr += (TCHAR)NULL;

	dlg.m_ofn.lpstrFilter = filterStr;
	
	dlg.m_ofn.Flags &= ~(OFN_EXPLORER);
	if (dlg.DoModal() == IDOK)
	{     
		m_imageFileName = dlg.m_ofn.lpstrFile;
		int indx = m_imageFileName.ReverseFind('\\');
		m_imageFileName = m_imageFileName.Right(m_imageFileName.GetLength() - indx - 1);
		UpdateData(FALSE);
	}					
}

void StagingInfoView::OnUpdateWorldObject()
{
  GetMyWorld();
}
void StagingInfoView::OnKillfocus() 
{
	UpdateData(TRUE);	
}
