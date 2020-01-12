// CharacterContextView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "CharacterContextView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CharacterContextView

IMPLEMENT_DYNCREATE(CharacterContextView, CFormView)

CharacterContextView::CharacterContextView()
	: CFormView(CharacterContextView::IDD)
{
	//{{AFX_DATA_INIT(CharacterContextView)
	m_characterId = 0;
	m_currentFrame = 0;
	m_isAffectedByLight = FALSE;
	m_isVisible = FALSE;
	m_nextFrame = 0;
	m_time = 0;
	m_timeNextFrame = 0;
	m_timePreviousFrame = 0;
	m_transX = 0;
	m_transY = 0;
	m_transZ = 0;
	//}}AFX_DATA_INIT
	m_currCharacterContextPtr = NULL;
}

CharacterContextView::~CharacterContextView()
{
}

void CharacterContextView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CharacterContextView)
	DDX_Control(pDX, IDC_TYPE_ID_CMB, m_typeId);
	DDX_Control(pDX, IDC_CLIP_LIST, m_clipList);
	DDX_Text(pDX, IDC_CHARACTER_ID, m_characterId);
	DDX_Text(pDX, IDC_CURRENT_FRAME, m_currentFrame);
	DDX_Check(pDX, IDC_IS_CHARACTER_AFFECTED_BY_LIGHT, m_isAffectedByLight);
	DDX_Check(pDX, IDC_IS_CHARACTER_VISIBLE, m_isVisible);
	DDX_Text(pDX, IDC_NEXT_FRAME, m_nextFrame);
	DDX_Text(pDX, IDC_TIME, m_time);
	DDX_Text(pDX, IDC_TIME_OF_THE_NEXT_FRAME, m_timeNextFrame);
	DDX_Text(pDX, IDC_TIME_OF_THE_PREVIOUS_FRAME, m_timePreviousFrame);
	DDX_Text(pDX, IDC_TRANS_X, m_transX);
	DDX_Text(pDX, IDC_TRANS_Y, m_transY);
	DDX_Text(pDX, IDC_TRANS_Z, m_transZ);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CharacterContextView, CFormView)
	//{{AFX_MSG_MAP(CharacterContextView)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_LBN_SELCHANGE(IDC_CLIP_LIST, OnSelchangeClipList)
	ON_BN_CLICKED(IDC_UP, OnUp)
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	//}}AFX_MSG_MAP
	ON_MESSAGE(RUNTIME_SAVE_MESSAGE,OnRuntimeSave)
	ON_MESSAGE(UPDATE_DELETING_IN_WORLD,OnUpdateWorldObject)
	ON_EN_KILLFOCUS(IDC_CURRENT_FRAME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_NEXT_FRAME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TIME_OF_THE_PREVIOUS_FRAME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TIME_OF_THE_NEXT_FRAME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TRANS_X, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TRANS_Y, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TRANS_Z, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TIME, OnKillfocus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CharacterContextView diagnostics

#ifdef _DEBUG
void CharacterContextView::AssertValid() const
{
	CFormView::AssertValid();
}

void CharacterContextView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CharacterContextView message handlers
CWorldConstructKitDoc* CharacterContextView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));
	return (CWorldConstructKitDoc*)m_pDocument;
}

BOOL CharacterContextView::GetMyWorld()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	m_worldId = pTreeView->GetCurrWorldID();	
	
	CWorldConstructKitDoc* doc = GetDocument();
	BOOL result = doc->m_worldMap.Lookup(m_worldId,m_world);	
  return result;
}

DWORD CharacterContextView::GetCurrCharacterContextId()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrNodeID();
}


DWORD CharacterContextView::GetCurrSceneId()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrSceneId();
}



void CharacterContextView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (GetMyWorld())
	{
		DWORD sceneId = GetCurrSceneId();
 		DWORD id = GetCurrCharacterContextId();

		for (int i = 0 ; i < m_world.m_numberOfScenes; i++)
		{
			if (m_world.m_scenes[i].m_sceneID == sceneId)
			{				
				m_world.m_scenes[i].m_sceneCharacters.ScanInit(DIRECTION_FORWARD);
				for (int j = 0; j < m_world.m_scenes[i].m_characterCount; j++)
				{
					m_currCharacterContextPtr = &m_world.m_scenes[i].m_sceneCharacters.NextElement(); 
					if (m_currCharacterContextPtr->m_characterId == id)
					{
						m_characterId = m_currCharacterContextPtr->m_characterId;
						m_isVisible = m_currCharacterContextPtr->m_characterIsVisible;
						m_isAffectedByLight = m_currCharacterContextPtr->m_adjustForLight;
						m_currentFrame = m_currCharacterContextPtr->m_currentFrame;
						m_nextFrame = m_currCharacterContextPtr->m_nextFrame;
						m_timePreviousFrame = m_currCharacterContextPtr->m_currentFrameClockValue;
						m_timeNextFrame = m_currCharacterContextPtr->m_nextFrameClockValue;

						m_typeId.ResetContent();
						//fill type id combo
						int characterIndx;
						for (int k = 0 ; k < m_world.m_numberOfCharacters; k++)
						{
							if (m_world.m_characters[k].m_characterId == m_currCharacterContextPtr->m_characterId)
							{
								characterIndx = k;
								break;
							}								
						}
            for (k = 0; k < m_world.m_characters[characterIndx].m_clipCount; k++)
						{ 
							CString IdStr;
							IdStr.Format("%d",m_world.m_characters[characterIndx].m_typeId[k]);
							if (m_typeId.FindString(-1,IdStr) == CB_ERR)
							{
								int indx = m_typeId.AddString(IdStr);
						   	m_typeId.SetItemData(indx,j);
							}							
						}							

						m_clipList.ResetContent();
						//fill list
						for (int j = 0; j < m_currCharacterContextPtr->m_nodeCount;j++)
						{			 
            	CString IdStr;
							IdStr.Format("%d",m_currCharacterContextPtr->m_typeId[j]);			        
							int indx = m_clipList.AddString(IdStr);
							m_clipList.SetItemData(indx,j);

						}
						if (m_currCharacterContextPtr->m_nodeCount > 0)
						{
							m_clipList.SetCurSel(0);
						}
						int selIndx = m_clipList.GetCurSel();
						FillCharacterContextDetails(selIndx,*m_currCharacterContextPtr);

						UpdateData(FALSE);
						break;
					}		
				}
			}
		}
	}	
}

void CharacterContextView::FillCharacterContextDetails(int selIndx,CharacterContext & characterContext)
{
	CString IdStr;
	if (selIndx != CB_ERR)
	{
		for (int i = 0; i < m_typeId.GetCount(); i++)
		{			
			m_typeId.GetLBText(i,IdStr);
			if (atoi(IdStr) == characterContext.m_typeId[selIndx])
			{
				m_typeId.SetCurSel(i);
				break;
			}
		}
		m_transX = characterContext.m_transX[selIndx];
		m_transY = characterContext.m_transY[selIndx];
		m_transZ = characterContext.m_transZ[selIndx];
		m_time = characterContext.m_clockValue[selIndx];
	}
	else
	{
		m_typeId.SetCurSel(0);
		m_transX = 0;
		m_transY = 0;
		m_transZ = 0;
		m_time = 0;
	}
	UpdateData(FALSE);
}

void CharacterContextView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();	
}

void CharacterContextView::OnRuntimeSave()
{
	UpdateData(TRUE);
	if (m_currCharacterContextPtr != NULL)
	{
	  m_currCharacterContextPtr->m_characterId = m_characterId;
	  m_currCharacterContextPtr->m_characterIsVisible = (bool)m_isVisible;
	  m_currCharacterContextPtr->m_adjustForLight =	(bool)m_isAffectedByLight;
	  m_currCharacterContextPtr->m_currentFrame = m_currentFrame;
	  m_currCharacterContextPtr->m_nextFrame = m_nextFrame;
	  m_currCharacterContextPtr->m_currentFrameClockValue = m_timePreviousFrame;
	  m_currCharacterContextPtr->m_nextFrameClockValue = m_timeNextFrame;

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

void CharacterContextView::OnUpdateWorldObject()
{
  GetMyWorld();
}

void CharacterContextView::OnAdd() 
{
	UpdateData(TRUE);
	int indx = m_typeId.GetCurSel();
	if (indx != CB_ERR )
	{			
		if (m_currCharacterContextPtr != NULL)
		{
			CString IdStr;
			m_typeId.GetLBText(m_typeId.GetCurSel(),IdStr);
			short indx;
	  	m_currCharacterContextPtr->m_typeId.PushBack((unsigned long)atoi(IdStr.GetBuffer(0)));
			m_currCharacterContextPtr->m_transX.PushBack(m_transX);
			m_currCharacterContextPtr->m_transY.PushBack(m_transY);
			m_currCharacterContextPtr->m_transZ.PushBack(m_transZ);
     	m_currCharacterContextPtr->m_clockValue.PushBack(m_time);

			indx = m_clipList.AddString(IdStr);
			m_clipList.SetItemData(indx,m_currCharacterContextPtr->m_nodeCount);
			m_currCharacterContextPtr->m_nodeCount++;			
		}
	}
	else
	{
		MessageBox("You must Type ID!","Error",MB_OK + MB_ICONWARNING);
	}	
}

void CharacterContextView::OnEdit() 
{
	if (UpdateData(TRUE))
	{
		int listIndx = m_clipList.GetCurSel();
		if (listIndx != CB_ERR)
		{
			short clipIndx = m_clipList.GetItemData(listIndx);
			
			unsigned long typeId = m_currCharacterContextPtr->m_typeId[clipIndx];

			CString IdStr;
			m_typeId.GetLBText(m_typeId.GetCurSel(),IdStr);
			

			if (atoi(IdStr.GetBuffer(0)) != typeId)
			{
				MessageBox("Can't update type name","Error",MB_OK + MB_ICONWARNING);
			}
			else
			{
				if (m_currCharacterContextPtr != NULL)
				{
					m_currCharacterContextPtr->m_transX[clipIndx] = m_transX;
					m_currCharacterContextPtr->m_transY[clipIndx] = m_transY;
					m_currCharacterContextPtr->m_transZ[clipIndx] = m_transZ;
					m_currCharacterContextPtr->m_clockValue[clipIndx] = m_time;
				}
			}
		}
	}	
}

void CharacterContextView::OnDelete() 
{
	int indx = m_clipList.GetCurSel();

	int indxInArr = m_clipList.GetItemData(indx);

		if (m_currCharacterContextPtr != NULL)
		{
			m_currCharacterContextPtr->m_typeId.RemoveByIndex(indxInArr);
			m_currCharacterContextPtr->m_transX.RemoveByIndex(indxInArr);
			m_currCharacterContextPtr->m_transY.RemoveByIndex(indxInArr);
			m_currCharacterContextPtr->m_transZ.RemoveByIndex(indxInArr);
     	m_currCharacterContextPtr->m_clockValue.RemoveByIndex(indxInArr);
			m_currCharacterContextPtr->m_nodeCount--;
		}
			
	m_clipList.DeleteString(indx);

	for (int i = indxInArr; i <= m_currCharacterContextPtr->m_nodeCount - 1 ;i++)
	{
		int indxOldInArr = m_clipList.GetItemData(i);
		m_clipList.SetItemData(i,indxOldInArr - 1);
	}

	m_clipList.SetCurSel(0);
	OnSelchangeClipList();	
}

void CharacterContextView::OnSelchangeClipList() 
{
	UpdateData(TRUE);
	int indx = m_clipList.GetCurSel();
	int indxInArr = m_clipList.GetItemData(indx);

	if (m_currCharacterContextPtr != NULL)
	{
			FillCharacterContextDetails(indxInArr,*m_currCharacterContextPtr);
	}
}

void CharacterContextView::OnUp() 
{
	int listIndx = m_clipList.GetCurSel();
	if (listIndx != 0)
	{
		if (m_currCharacterContextPtr != NULL)
		{
			m_currCharacterContextPtr->m_typeId.Replace(listIndx - 1,listIndx);
			m_currCharacterContextPtr->m_transX.Replace(listIndx - 1,listIndx);
			m_currCharacterContextPtr->m_transY.Replace(listIndx - 1,listIndx);
			m_currCharacterContextPtr->m_transZ.Replace(listIndx - 1,listIndx);
		  m_currCharacterContextPtr->m_clockValue.Replace(listIndx - 1,listIndx);			

			m_clipList.ResetContent();
			//fill list
			for (int j = 0; j < m_currCharacterContextPtr->m_nodeCount;j++)
			{			 
				CString IdStr;
				IdStr.Format("%d",m_currCharacterContextPtr->m_typeId[j]);			        
				int indx = m_clipList.AddString(IdStr);
				m_clipList.SetItemData(indx,j);
			}
			m_clipList.SetCurSel(listIndx - 1);
		}		
	}
}

void CharacterContextView::OnDown() 
{
	int listIndx = m_clipList.GetCurSel();
	if (listIndx != m_clipList.GetCount() - 1)
	{
		if (m_currCharacterContextPtr != NULL)
		{
			m_currCharacterContextPtr->m_typeId.Replace(listIndx,listIndx + 1);
			m_currCharacterContextPtr->m_transX.Replace(listIndx,listIndx + 1);
			m_currCharacterContextPtr->m_transY.Replace(listIndx,listIndx + 1);
			m_currCharacterContextPtr->m_transZ.Replace(listIndx,listIndx + 1);
		  m_currCharacterContextPtr->m_clockValue.Replace(listIndx,listIndx + 1);			

			m_clipList.ResetContent();
			//fill list
			for (int j = 0; j < m_currCharacterContextPtr->m_nodeCount;j++)
			{			 
				CString IdStr;
				IdStr.Format("%d",m_currCharacterContextPtr->m_typeId[j]);			        
				int indx = m_clipList.AddString(IdStr);
				m_clipList.SetItemData(indx,j);
			}
			m_clipList.SetCurSel(listIndx + 1);
		}		
	}
}

void CharacterContextView::OnKillfocus() 
{
	UpdateData(TRUE);	
}
