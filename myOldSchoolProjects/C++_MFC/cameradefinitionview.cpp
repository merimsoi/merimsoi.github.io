// CameraDefinitionView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "CameraDefinitionView.h"
#include "forms.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CameraDefinitionView

IMPLEMENT_DYNCREATE(CameraDefinitionView, CFormView)

CameraDefinitionView::CameraDefinitionView()
	: CFormView(CameraDefinitionView::IDD)
{
	//{{AFX_DATA_INIT(CameraDefinitionView)
	m_endClockValue = 0;
	m_isApplyColorFilter = FALSE;
	m_isApplyTrasparency = FALSE;
	m_isCameraEnabled = FALSE;
	m_isFrozenCamera = FALSE;
	m_isSceneInitialized = FALSE;
	m_startClockValue = 0;
	m_colorHEnd = 0;
	m_colorHStart = 0;
	m_colorLEnd = 0;
	m_colorLStart = 0;
	m_colorSEnd = 0;
	m_colorSStart = 0;
	m_transparencyEnd = 0;
	m_transparencyStart = 0;
	//}}AFX_DATA_INIT
	m_currCameraPtr = NULL;
}

CameraDefinitionView::~CameraDefinitionView()
{
}

void CameraDefinitionView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CameraDefinitionView)
	DDX_Control(pDX, IDC_COMBO_SCENE_ID, m_comboSceneID);
	DDX_Control(pDX, IDC_SPIN_TRANSPARENT_START, m_spinTransparencyStart);
	DDX_Control(pDX, IDC_SPIN_TRANSPARENCY_END, m_spinTrasparencyEnd);
	DDX_Control(pDX, IDC_SPIN_COLOR_S_END, m_spinColorSEnd);
	DDX_Control(pDX, IDC_SPIN_COLOR_S_START, m_spinColorSStart);
	DDX_Control(pDX, IDC_SPIN_COLOR_L_START, m_spinColorLStart);
	DDX_Control(pDX, IDC_SPIN_COLOR_L_END, m_spinColorLEnd);
	DDX_Control(pDX, IDC_SPIN_COLOR_H_START, m_spinColorHStart);
	DDX_Control(pDX, IDC_SPIN_COLOR_H_END, m_spinColorHEnd);
	DDX_Control(pDX, IDC_COMBO_LAYER, m_comboLayer);
	DDX_Text(pDX, IDC_END_CLOCK_VALUE, m_endClockValue);
	DDX_Check(pDX, IDC_IS_APPLY_COLOR_FILTER, m_isApplyColorFilter);
	DDX_Check(pDX, IDC_IS_APPLY_TRANSPARENCY, m_isApplyTrasparency);
	DDX_Check(pDX, IDC_IS_CAMERA_ENABLED, m_isCameraEnabled);
	DDX_Check(pDX, IDC_IS_FROZEN_CAMERA, m_isFrozenCamera);
	DDX_Check(pDX, IDC_IS_SCENE_INITIALIZED, m_isSceneInitialized);
	DDX_Text(pDX, IDC_START_CLOCK_VALUE, m_startClockValue);
	DDX_Text(pDX, IDC_COLOR_H_END, m_colorHEnd);
	DDV_MinMaxInt(pDX, m_colorHEnd, COLOR_MIN, COLOR_MAX);
	DDX_Text(pDX, IDC_COLOR_H_START, m_colorHStart);
	DDV_MinMaxInt(pDX, m_colorHStart, COLOR_MIN, COLOR_MAX);
	DDX_Text(pDX, IDC_COLOR_L_END, m_colorLEnd);
	DDV_MinMaxInt(pDX, m_colorLEnd, COLOR_MIN, COLOR_MAX);
	DDX_Text(pDX, IDC_COLOR_L_START, m_colorLStart);
	DDV_MinMaxInt(pDX, m_colorLStart, COLOR_MIN, COLOR_MAX);
	DDX_Text(pDX, IDC_COLOR_S_END, m_colorSEnd);
	DDV_MinMaxInt(pDX, m_colorSEnd, COLOR_MIN, COLOR_MAX);
	DDX_Text(pDX, IDC_COLOR_S_START, m_colorSStart);
	DDV_MinMaxInt(pDX, m_colorSStart, COLOR_MIN, COLOR_MAX);
	DDX_Text(pDX, IDC_TRANSPARENCY_END, m_transparencyEnd);
	DDV_MinMaxInt(pDX, m_transparencyEnd, UNSIGNED_CHAR_MIN, UNSIGNED_CHAR_MAX);
	DDX_Text(pDX, IDC_TRANSPARENT_START, m_transparencyStart);
	DDV_MinMaxInt(pDX, m_transparencyStart, UNSIGNED_CHAR_MIN, UNSIGNED_CHAR_MAX);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CameraDefinitionView, CFormView)
	//{{AFX_MSG_MAP(CameraDefinitionView)
	ON_CBN_SELENDOK(IDC_COMBO_SCENE_ID, OnSelendokComboSceneId)
	ON_EN_KILLFOCUS(IDC_COLOR_H_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TRANSPARENCY_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_COLOR_L_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_COLOR_H_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_COLOR_L_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_COLOR_S_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_COLOR_S_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TRANSPARENT_START, OnKillfocus)
	//}}AFX_MSG_MAP
	ON_EN_KILLFOCUS(IDC_START_CLOCK_VALUE, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_END_CLOCK_VALUE, OnKillfocus)
	ON_MESSAGE(RUNTIME_SAVE_MESSAGE,OnRuntimeSave)
	ON_MESSAGE(UPDATE_DELETING_IN_WORLD,OnUpdateWorldObject)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CameraDefinitionView diagnostics

#ifdef _DEBUG
void CameraDefinitionView::AssertValid() const
{
	CFormView::AssertValid();
}

void CameraDefinitionView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CameraDefinitionView message handlers
CWorldConstructKitDoc* CameraDefinitionView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));
	return (CWorldConstructKitDoc*)m_pDocument;
}

BOOL CameraDefinitionView::GetMyWorld()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	m_worldId = pTreeView->GetCurrWorldID();	
	
	CWorldConstructKitDoc* doc = GetDocument();
  BOOL result = doc->m_worldMap.Lookup(m_worldId,m_world);	
  return result;
}

DWORD CameraDefinitionView::GetCurrCameraDefinitionId()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrNodeID();
}

void CameraDefinitionView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (GetMyWorld())
	{
		DWORD id = GetCurrCameraDefinitionId();

		for (int i = 0 ; i < m_world.m_numberOfScenes; i++)
		{
			CString sceneIdStr;
			sceneIdStr.Format("%d",m_world.m_scenes[i].m_sceneID);
			m_comboSceneID.AddString(sceneIdStr);			
		}

		m_world.m_camera.ScanInit(DIRECTION_FORWARD);
		for (i = 0; i < m_world.m_cameraCount; i++)
		{
			m_currCameraPtr = &m_world.m_camera.NextElement(); 
			if (m_currCameraPtr->m_sceneID == id)
			{
				CString sceneIdStr;
				sceneIdStr.Format("%d",m_currCameraPtr->m_sceneID);
				m_comboSceneID.SelectString(-1,sceneIdStr);
				m_comboLayer.SetCurSel(m_currCameraPtr->m_layer);
				m_endClockValue = m_currCameraPtr->m_endClockValue;
				m_isApplyColorFilter = m_currCameraPtr->m_applyColorFilter;
				m_isApplyTrasparency = m_currCameraPtr->m_applyTrasparency;
				m_isCameraEnabled = m_currCameraPtr->m_cameraIsEnabled;
				m_isFrozenCamera = m_currCameraPtr->m_cameraIsFrozen;
				m_isSceneInitialized = m_currCameraPtr->m_sceneIsInitialized;
				m_startClockValue = m_currCameraPtr->m_startClockValue;
				m_colorHEnd = m_currCameraPtr->m_colorHEnd;
				m_colorHStart = m_currCameraPtr->m_colorHStart;
				m_colorLEnd = m_currCameraPtr->m_colorLEnd;
				m_colorLStart = m_currCameraPtr->m_colorLStart;
				m_colorSEnd = m_currCameraPtr->m_colorSEnd;
				m_colorSStart = m_currCameraPtr->m_colorSStart;
				m_transparencyEnd = m_currCameraPtr->m_transparencyEnd;
				m_transparencyStart = m_currCameraPtr->m_transparencyStart;

				UpdateData(FALSE);
				break;
			}		
		}
	}	
}

void CameraDefinitionView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

  m_spinColorHEnd.SetBuddy(GetDlgItem(IDC_COLOR_H_END));
	m_spinColorHStart.SetBuddy(GetDlgItem(IDC_COLOR_H_START));
	m_spinColorLEnd.SetBuddy(GetDlgItem(IDC_COLOR_L_END));
	m_spinColorLStart.SetBuddy(GetDlgItem(IDC_COLOR_L_START));
	m_spinColorSEnd.SetBuddy(GetDlgItem(IDC_COLOR_S_END));
	m_spinColorSStart.SetBuddy(GetDlgItem(IDC_COLOR_S_START));
	m_spinTransparencyStart.SetBuddy(GetDlgItem(IDC_TRANSPARENT_START));
	m_spinTrasparencyEnd.SetBuddy(GetDlgItem(IDC_TRANSPARENCY_END));	

  m_spinColorHEnd.SetRange(COLOR_MIN,COLOR_MAX);
	m_spinColorHStart.SetRange(COLOR_MIN,COLOR_MAX);
	m_spinColorLEnd.SetRange(COLOR_MIN,COLOR_MAX);
	m_spinColorLStart.SetRange(COLOR_MIN,COLOR_MAX);
	m_spinColorSEnd.SetRange(COLOR_MIN,COLOR_MAX);
	m_spinColorSStart.SetRange(COLOR_MIN,COLOR_MAX);
	m_spinTransparencyStart.SetRange(UNSIGNED_CHAR_MIN,UNSIGNED_CHAR_MAX);
	m_spinTrasparencyEnd.SetRange(UNSIGNED_CHAR_MIN,UNSIGNED_CHAR_MAX);	
}

void CameraDefinitionView::OnRuntimeSave()
{
	UpdateData(TRUE);
	if (m_currCameraPtr != NULL)
	{
		m_currCameraPtr->m_layer = (LayerType)m_comboLayer.GetCurSel();
		m_currCameraPtr->m_endClockValue = m_endClockValue ;
		m_currCameraPtr->m_applyColorFilter =	m_isApplyColorFilter ? true : false ;
		m_currCameraPtr->m_applyTrasparency	= m_isApplyTrasparency ? true : false;
		m_currCameraPtr->m_cameraIsEnabled =	m_isCameraEnabled ? true : false;
		m_currCameraPtr->m_cameraIsFrozen	= m_isFrozenCamera ? true : false;
		m_currCameraPtr->m_sceneIsInitialized	= m_isSceneInitialized ? true : false;
		m_currCameraPtr->m_startClockValue =	m_startClockValue ;
		m_currCameraPtr->m_colorHEnd =	m_colorHEnd ;
		m_currCameraPtr->m_colorHStart =	m_colorHStart  ;
		m_currCameraPtr->m_colorLEnd =	m_colorLEnd ;
		m_currCameraPtr->m_colorLStart =	m_colorLStart;
		m_currCameraPtr->m_colorSEnd =	m_colorSEnd ;
		m_currCameraPtr->m_colorSStart =	m_colorSStart ;
		m_currCameraPtr->m_transparencyEnd =	m_transparencyEnd ;
		m_currCameraPtr->m_transparencyStart =	m_transparencyStart;		

		CWorldConstructKitDoc* doc = GetDocument();
		doc->m_worldMap.SetAt(m_worldId,m_world);	
	}
}

void CameraDefinitionView::OnSelendokComboSceneId() 
{
	UpdateData(TRUE);
	if (m_currCameraPtr != NULL)
	{
		//get new ID
		CString newSceneIdStr;
		int indx = m_comboSceneID.GetCurSel();
		if (indx != CB_ERR)
		{
			m_comboSceneID.GetLBText(indx,newSceneIdStr);
		}

		//build str as in tree
		CString 
			newIdStr;
		newIdStr.Format("(%s)%s",newSceneIdStr,CAMERA_DEFINITION_STR);

		//old ID
		CString sceneIdStr;
		sceneIdStr.Format("%d",m_currCameraPtr->m_sceneID);

		//build str as in tree
		CString oldIdStr;
    oldIdStr.Format("(%s)%s",sceneIdStr,CAMERA_DEFINITION_STR);


		DynamicNodeData dynamicNodeData;
		dynamicNodeData.resId = IDD_CAMERA_DEFINITION;
		CString dynMapStr;
		dynMapStr.Format("%d--%s-%s",m_worldId,CAMERA_DEFINITION_STR,newIdStr.GetBuffer(0));

		dynamicNodeData.lpszName = strdup(dynMapStr.GetBuffer(0));

		DynamicNodeData oldDynamicNodeData;
		oldDynamicNodeData.resId = IDD_CAMERA_DEFINITION;
		CString dynOldMapStr;
		dynOldMapStr.Format("%d--%s-%s",m_worldId,CAMERA_DEFINITION_STR,oldIdStr.GetBuffer(0));
		oldDynamicNodeData.lpszName = dynOldMapStr.GetBuffer(0);

		int pos = formData.m_dynamicNodeMap.FindElement(dynamicNodeData);

		if (pos == NOT_FOUND)
		{			
			m_currCameraPtr->m_sceneID  = atoi(newSceneIdStr.GetBuffer(0));
			
			CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
			pTreeView->SendMessage(CHANGE_SCENE_ID,_atoi64(newSceneIdStr.GetBuffer(0)));

			formData.m_dynamicNodeMap.RemoveByIndex(formData.m_dynamicNodeMap.FindElement(oldDynamicNodeData));
			formData.m_dynamicNodeMap.PushBack(dynamicNodeData);

			CWorldConstructKitDoc* doc = GetDocument();
			int countBefore = doc->m_worldMap.GetCount();
			doc->m_worldMap.SetAt(m_worldId,m_world);	
    	int countAfter = doc->m_worldMap.GetCount();
	    if (countBefore != countAfter)
			{
		    ASSERT(FALSE);
			}
		}
		else
		{
			MessageBox("Camera definition with this ID already exist","Error",MB_OK + MB_ICONWARNING);
			m_comboSceneID.SelectString(-1,sceneIdStr);
		}
	}	
}

void CameraDefinitionView::OnUpdateWorldObject()
{
  GetMyWorld();
}

void CameraDefinitionView::OnKillfocus() 
{
	UpdateData(TRUE);	
}

