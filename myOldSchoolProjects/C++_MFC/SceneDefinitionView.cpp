// SceneDefinitionView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "SceneDefinitionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SceneDefinitionView

IMPLEMENT_DYNCREATE(SceneDefinitionView, CFormView)

SceneDefinitionView::SceneDefinitionView()
	: CFormView(SceneDefinitionView::IDD)
{
	//{{AFX_DATA_INIT(SceneDefinitionView)
	m_entranceScript = 0;
	m_exitScript = 0;
	m_filesetID = 0;
	m_inventoryHeight = 0;
	m_inventoryLeft = 0;
	m_inventoryTop = 0;
	m_inventoryWidth = 0;
	m_isDisplayInventory = FALSE;
	m_isSceneNavigable = FALSE;
	m_sceneID = 0;
	m_activeText = 0;
	//}}AFX_DATA_INIT
	m_currSceneDefinitionPtr = NULL;
}

SceneDefinitionView::~SceneDefinitionView()
{
}

void SceneDefinitionView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SceneDefinitionView)
	DDX_Control(pDX, IDC_SPIN_HEIGHT, m_spinHeight);
	DDX_Control(pDX, IDC_SPIN_Y_VALUE, m_spinY);
	DDX_Control(pDX, IDC_SPIN_X_VALUE, m_spinX);
	DDX_Control(pDX, IDC_SPIN_WIDTH, m_spinWidth);
	DDX_Control(pDX, IDC_COMBO_SKY_ID, m_comboSkyID);
	DDX_Control(pDX, IDC_COMBO_MUSIC_SCRIPT, m_comboMusicScript);
	DDX_Text(pDX, IDC_ENTRANCE_SCRIPT, m_entranceScript);
	DDX_Text(pDX, IDC_EXIT_SCRIPT, m_exitScript);
	DDX_Text(pDX, IDC_FILESET_ID, m_filesetID);
	DDX_Text(pDX, IDC_INVENTORY_HEIGHT, m_inventoryHeight);
	DDX_Text(pDX, IDC_INVENTORY_LEFT, m_inventoryLeft);
	DDX_Text(pDX, IDC_INVENTORY_TOP, m_inventoryTop);
	DDX_Text(pDX, IDC_INVENTORY_WIDTH, m_inventoryWidth);
	DDX_Check(pDX, IDC_IS_DISPLAY_INVENTORY, m_isDisplayInventory);
	DDX_Check(pDX, IDC_IS_SCENE_NAVIGABLE, m_isSceneNavigable);
	DDX_Text(pDX, IDC_SCENE_ID, m_sceneID);
	DDX_Text(pDX, IDC_ACTIVE_TEXT, m_activeText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SceneDefinitionView, CFormView)
	//{{AFX_MSG_MAP(SceneDefinitionView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE(RUNTIME_SAVE_MESSAGE,OnRuntimeSave)
	ON_MESSAGE(UPDATE_WORLD_OBJECT,OnUpdateWorldObject)
	ON_MESSAGE(UPDATE_DELETING_IN_WORLD,OnUpdateWorldObject)
	ON_EN_KILLFOCUS(IDC_FILESET_ID, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_ENTRANCE_SCRIPT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_EXIT_SCRIPT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_ACTIVE_TEXT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_INVENTORY_LEFT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_INVENTORY_TOP, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_INVENTORY_WIDTH, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_INVENTORY_HEIGHT, OnKillfocus)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SceneDefinitionView diagnostics

#ifdef _DEBUG
void SceneDefinitionView::AssertValid() const
{
	CFormView::AssertValid();
}

void SceneDefinitionView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// SceneDefinitionView message handlers
CWorldConstructKitDoc* SceneDefinitionView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));
	return (CWorldConstructKitDoc*)m_pDocument;
}

BOOL SceneDefinitionView::GetMyWorld()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	m_worldId = pTreeView->GetCurrWorldID();	
	
	CWorldConstructKitDoc* doc = GetDocument();
	BOOL result = doc->m_worldMap.Lookup(m_worldId,m_world);	
  return result;
}

DWORD SceneDefinitionView::GetCurrSceneId()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrNodeID();
}


void SceneDefinitionView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	OnUpdateWorldObject();

	for (int i = 0 ; i < m_world.m_numberOfSkies; i++)
	{
		CString skyIdStr;
		skyIdStr.Format("%d",m_world.m_skies[i].m_skyID);
		m_comboSkyID.AddString(skyIdStr);			
	}

	for (i = 0 ; i < m_world.m_bgMusicCount; i++)
	{
		CString scriptIdStr;
		scriptIdStr.Format("%d",m_world.m_bgMusicScript[i].m_scriptID);
		m_comboMusicScript.AddString(scriptIdStr);			
	}	
	if (m_world.m_numberOfSkies == 0)
	{
		m_comboSkyID.EnableWindow(FALSE);
	}
	else
	{
		if (m_currSceneDefinitionPtr != NULL)
		{
			CString skyIdStr;
			skyIdStr.Format("%d",m_currSceneDefinitionPtr->m_skyID);
			m_comboSkyID.SelectString(-1,skyIdStr);
		}
	}

	if (m_world.m_bgMusicCount == 0)
	{
		m_comboMusicScript.EnableWindow(FALSE);
	}
	else
	{
		if (m_currSceneDefinitionPtr != NULL)
		{
			CString scriptIdStr;
			scriptIdStr.Format("%d",m_currSceneDefinitionPtr->m_bgMusicCode);		
			m_comboMusicScript.SelectString(-1,scriptIdStr);
		}
	}

	m_entranceScript = m_currSceneDefinitionPtr->m_entranceScript;
	m_exitScript = m_currSceneDefinitionPtr->m_exitScript;
	m_filesetID = m_currSceneDefinitionPtr->m_filesetID;
	m_inventoryHeight = m_currSceneDefinitionPtr->m_heightInventoryDisplay;
	m_inventoryLeft = m_currSceneDefinitionPtr->m_leftInventoryDisplay;
	m_inventoryTop = m_currSceneDefinitionPtr->m_topInventoryDisplay;
	m_inventoryWidth = m_currSceneDefinitionPtr->m_widthInventoryDisplay;
	m_isDisplayInventory = m_currSceneDefinitionPtr->m_displayInventory;
	m_isSceneNavigable = m_currSceneDefinitionPtr->m_sceneIsNavigable;
	m_sceneID = m_currSceneDefinitionPtr->m_sceneID;
	m_activeText = m_currSceneDefinitionPtr->m_activeText;
	
	UpdateData(FALSE);
}

void SceneDefinitionView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	m_spinX.SetBuddy(GetDlgItem(IDC_INVENTORY_LEFT));
	m_spinY.SetBuddy(GetDlgItem(IDC_INVENTORY_TOP));
	m_spinWidth.SetBuddy(GetDlgItem(IDC_INVENTORY_WIDTH));
	m_spinHeight.SetBuddy(GetDlgItem(IDC_INVENTORY_HEIGHT));

	m_spinX.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinY.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinWidth.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinHeight.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
}

void SceneDefinitionView::OnUpdateWorldObject()
{
	if (GetMyWorld())
	{
		DWORD id = GetCurrSceneId();
		for (int i = 0 ; i < m_world.m_numberOfScenes; i++)
		{
			if (m_world.m_scenes[i].m_sceneID == id)
			{
				m_currSceneDefinitionPtr = &m_world.m_scenes[i];
			}
		}
	}
}
void SceneDefinitionView::OnRuntimeSave()
{
	UpdateData(TRUE);
	if (m_currSceneDefinitionPtr != NULL)
	{
		CString skyIdStr;
  	CString scriptIdStr;

		int indx = m_comboSkyID.GetCurSel();
		if (indx != CB_ERR)
		{
			m_comboSkyID.GetLBText(indx,skyIdStr);
		}
		indx = m_comboMusicScript.GetCurSel();
		if (indx != CB_ERR)
		{
			m_comboMusicScript.GetLBText(indx,scriptIdStr);
		}
  	
		m_currSceneDefinitionPtr->m_skyID = atoi(skyIdStr.GetBuffer(0));
		m_currSceneDefinitionPtr->m_bgMusicCode = atoi(scriptIdStr.GetBuffer(0));
		m_currSceneDefinitionPtr->m_entranceScript = m_entranceScript ;
		m_currSceneDefinitionPtr->m_exitScript = m_exitScript ;
		m_currSceneDefinitionPtr->m_filesetID	= m_filesetID ;
		m_currSceneDefinitionPtr->m_heightInventoryDisplay = m_inventoryHeight ;
		m_currSceneDefinitionPtr->m_leftInventoryDisplay = m_inventoryLeft  ;
		m_currSceneDefinitionPtr->m_topInventoryDisplay	= m_inventoryTop ;
		m_currSceneDefinitionPtr->m_widthInventoryDisplay	= m_inventoryWidth ;
		m_currSceneDefinitionPtr->m_displayInventory	= m_isDisplayInventory ? true : false;
		m_currSceneDefinitionPtr->m_sceneIsNavigable	= m_isSceneNavigable ? true : false;
		m_currSceneDefinitionPtr->m_sceneID = m_sceneID ;
		m_currSceneDefinitionPtr->m_activeText	= m_activeText  ;
	
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

void SceneDefinitionView::OnKillfocus() 
{
	UpdateData(TRUE);	
}
