// KeyboardTriggerView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "KeyboardTriggerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// KeyboardTriggerView

IMPLEMENT_DYNCREATE(KeyboardTriggerView, CFormView)

KeyboardTriggerView::KeyboardTriggerView()
	: CFormView(KeyboardTriggerView::IDD)
{
	//{{AFX_DATA_INIT(KeyboardTriggerView)
	m_keyID = 0;
	m_isTriggerEnabled = FALSE;
	m_triggerScript = 0;
	m_keyCode = 0;
	//}}AFX_DATA_INIT
	m_currKeyboardPtr = NULL;
}

KeyboardTriggerView::~KeyboardTriggerView()
{
}

void KeyboardTriggerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(KeyboardTriggerView)
	DDX_Control(pDX, IDC_SPIN_KEY_CODE, m_spinKeyCode);
	DDX_Text(pDX, IDC_KEY_ID, m_keyID);
	DDX_Check(pDX, IDC_IS_TRIGGER_ENABLED, m_isTriggerEnabled);
	DDX_Text(pDX, IDC_TRIGGER_SCRIPT, m_triggerScript);
	DDX_Text(pDX, IDC_KEY_CODE, m_keyCode);
	DDV_MinMaxInt(pDX, m_keyCode, UNSIGNED_CHAR_MIN, UNSIGNED_CHAR_MAX);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(KeyboardTriggerView, CFormView)
	//{{AFX_MSG_MAP(KeyboardTriggerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE(RUNTIME_SAVE_MESSAGE,OnRuntimeSave)
	ON_MESSAGE(UPDATE_DELETING_IN_WORLD,OnUpdateWorldObject)
	ON_EN_KILLFOCUS(IDC_KEY_CODE, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TRIGGER_SCRIPT, OnKillfocus)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// KeyboardTriggerView diagnostics

#ifdef _DEBUG
void KeyboardTriggerView::AssertValid() const
{
	CFormView::AssertValid();
}

void KeyboardTriggerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// KeyboardTriggerView message handlers
CWorldConstructKitDoc* KeyboardTriggerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));
	return (CWorldConstructKitDoc*)m_pDocument;
}

BOOL KeyboardTriggerView::GetMyWorld()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	m_worldID = pTreeView->GetCurrWorldID();	
	
	CWorldConstructKitDoc* doc = GetDocument();
	BOOL result = doc->m_worldMap.Lookup(m_worldID,m_world);	
  return result;
}

DWORD KeyboardTriggerView::GetCurrKeyboardId()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrNodeID();
}


DWORD KeyboardTriggerView::GetCurrSceneId()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrSceneId();
}

void KeyboardTriggerView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (GetMyWorld())
	{
		DWORD sceneId = GetCurrSceneId();
 		DWORD id = GetCurrKeyboardId();

		for (int i = 0 ; i < m_world.m_numberOfScenes; i++)
		{
			if (m_world.m_scenes[i].m_sceneID == sceneId)
			{				
				m_world.m_scenes[i].m_keys.ScanInit(DIRECTION_FORWARD);
				for (int j = 0; j < m_world.m_scenes[i].m_keyCount; j++)
				{
					m_currKeyboardPtr = &m_world.m_scenes[i].m_keys.NextElement(); 
					if (m_currKeyboardPtr->m_keyID == id)
					{
						m_keyID = m_currKeyboardPtr->m_keyID;
						m_isTriggerEnabled = m_currKeyboardPtr->m_triggerIsEnabled;
						m_keyCode = m_currKeyboardPtr->m_keyCode;
						m_triggerScript = m_currKeyboardPtr->m_triggerScrript;
						
						UpdateData(FALSE);
						break;
					}		
				}
			}
		}
	}	
}

void KeyboardTriggerView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();	
	m_spinKeyCode.SetBuddy(GetDlgItem(IDC_KEY_CODE));
	m_spinKeyCode.SetRange(UNSIGNED_CHAR_MIN,UNSIGNED_CHAR_MAX);	
}

void KeyboardTriggerView::OnRuntimeSave()
{
	UpdateData(TRUE);
	if (m_currKeyboardPtr != NULL)
	{
		m_currKeyboardPtr->m_keyID = m_keyID ;
		m_currKeyboardPtr->m_triggerIsEnabled	=	m_isTriggerEnabled ? true : false;
		m_currKeyboardPtr->m_keyCode = m_keyCode ;
		m_currKeyboardPtr->m_triggerScrript = m_triggerScript;
	
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

void KeyboardTriggerView::OnUpdateWorldObject()
{
  GetMyWorld();
}
void KeyboardTriggerView::OnKillfocus() 
{
	UpdateData(TRUE);	
}
