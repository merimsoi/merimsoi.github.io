// ItemDefinitionView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "ItemDefinitionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ItemDefinitionView

IMPLEMENT_DYNCREATE(ItemDefinitionView, CFormView)

ItemDefinitionView::ItemDefinitionView()
	: CFormView(ItemDefinitionView::IDD)
{
	//{{AFX_DATA_INIT(ItemDefinitionView)
	m_description = _T("");
	m_feedbackString = _T("");
	m_fileName = _T("");
	m_fileSetID = 0;
	m_hoverScript = 0;
	m_isInteractionEnabled = FALSE;
	m_isStashedItem = FALSE;
	m_itemID = 0;
	m_triggerScript = 0;
	//}}AFX_DATA_INIT
	m_currItemDefinitionPtr = NULL;
}

ItemDefinitionView::~ItemDefinitionView()
{

}

void ItemDefinitionView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ItemDefinitionView)
	DDX_Control(pDX, IDC_LIST_INTERACTION, m_interactionList);
	DDX_Control(pDX, IDC_COMBO_INTERATION_TYPE, m_comboInteractionType);
	DDX_Control(pDX, IDC_COMBO_INTERACTION_SUB_TYPE, m_comboInteractionSubType);
	DDX_Text(pDX, IDC_DESCRIPTION, m_description);
	DDX_Text(pDX, IDC_FEEDBACK_STRING, m_feedbackString);
	DDX_Text(pDX, IDC_FILE_NAME, m_fileName);
	DDX_Text(pDX, IDC_FILESET_ID, m_fileSetID);
	DDX_Text(pDX, IDC_HOVER_SCRIPT, m_hoverScript);
	DDX_Check(pDX, IDC_IS_INTERACTION_ENABLED, m_isInteractionEnabled);
	DDX_Check(pDX, IDC_IS_STASHED_ITEM, m_isStashedItem);
	DDX_Text(pDX, IDC_ITEM_ID, m_itemID);
	DDX_Text(pDX, IDC_TRIGGER_SCRIPT, m_triggerScript);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ItemDefinitionView, CFormView)
	//{{AFX_MSG_MAP(ItemDefinitionView)
	ON_LBN_SELCHANGE(IDC_LIST_INTERACTION, OnSelchangeListInteraction)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_CBN_SELENDOK(IDC_COMBO_INTERATION_TYPE, OnSelendokComboInterationType)
	ON_BN_CLICKED(IDC_UP, OnUp)
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	//}}AFX_MSG_MAP
	ON_MESSAGE(RUNTIME_SAVE_MESSAGE,OnRuntimeSave)
	ON_MESSAGE(UPDATE_DELETING_IN_WORLD,OnUpdateWorldObject)
	ON_EN_KILLFOCUS(IDC_HOVER_SCRIPT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_FILESET_ID, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TRIGGER_SCRIPT, OnKillfocus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ItemDefinitionView diagnostics

#ifdef _DEBUG
void ItemDefinitionView::AssertValid() const
{
	CFormView::AssertValid();
}

void ItemDefinitionView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ItemDefinitionView message handlers
CWorldConstructKitDoc* ItemDefinitionView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));
	return (CWorldConstructKitDoc*)m_pDocument;
}

BOOL ItemDefinitionView::GetMyWorld()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	m_worldId = pTreeView->GetCurrWorldID();	
	
	CWorldConstructKitDoc* doc = GetDocument();
	BOOL result = doc->m_worldMap.Lookup(m_worldId,m_world);	
  return result;
}

DWORD ItemDefinitionView::GetCurrInventoryID()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrNodeID();
}

void ItemDefinitionView::GetCurrFileName(CString& fileName)
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	pTreeView->GetCurrNodeFileName(fileName);
}


void ItemDefinitionView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (GetMyWorld())
	{
		CString fileName;
		DWORD id = GetCurrInventoryID();
		GetCurrFileName(fileName);

		m_world.m_inventory.ScanInit(DIRECTION_FORWARD);
		for (int i = 0; i < m_world.m_inventorySize; i++)
		{
			m_currItemDefinitionPtr = &m_world.m_inventory.NextElement(); 
			if (m_currItemDefinitionPtr->m_itemID == id &&
				  m_currItemDefinitionPtr->m_iconFileName == (CStdString)fileName)
			{
				m_itemID = m_currItemDefinitionPtr->m_itemID;
				m_fileName = m_currItemDefinitionPtr->m_iconFileName; 
				m_hoverScript = m_currItemDefinitionPtr->m_hoverScript;
				m_feedbackString = m_currItemDefinitionPtr->m_feedbackString;
				m_isStashedItem = m_currItemDefinitionPtr->m_itemIsStashed;
				
				FillIterationList();
				if (m_currItemDefinitionPtr->m_interactionCount > 0)
				{
					m_interactionList.SetCurSel(0);
				}
				int selIndx = m_interactionList.GetCurSel();
				FillItemDetails(selIndx,*m_currItemDefinitionPtr);
				
				UpdateData(FALSE);
				Invalidate();
				break;
			}
		}		
	}	
}

void ItemDefinitionView::FillIterationList()
{
	CString listStr;
	m_interactionList.ResetContent();
	for (int j = 0; j < m_currItemDefinitionPtr->m_interactionCount;j++)
	{
		switch(m_currItemDefinitionPtr->m_interactionType[j])
		{
		case MN_INVENTORY:
						listStr.Format("%d - Inventory,Item #%d",m_currItemDefinitionPtr->m_interactionFileSet[j],m_currItemDefinitionPtr->m_interactionSubType[j]);
						break;
		case MN_SENSES:
						switch(m_currItemDefinitionPtr->m_interactionSubType[j])
						{
						case 	SUB_LOOK:
							listStr.Format("%d - Senses,Look",m_currItemDefinitionPtr->m_interactionFileSet[j]);
							break;
						case SUB_SMELL:
							listStr.Format("%d - Senses,Smell",m_currItemDefinitionPtr->m_interactionFileSet[j]);
							break;
						case SUB_TASTE:
							listStr.Format("%d - Senses,Taste",m_currItemDefinitionPtr->m_interactionFileSet[j]);
							break;
						case SUB_TEXTURE:
							listStr.Format("%d - Senses,Texture",m_currItemDefinitionPtr->m_interactionFileSet[j]);
							break;
						case SUB_SOUND:
							listStr.Format("%d - Senses,Sound",m_currItemDefinitionPtr->m_interactionFileSet[j]);
							break;
						}					
						break;
						case MN_ACTION:
							listStr.Format("%d - Action",m_currItemDefinitionPtr->m_interactionFileSet[j]);
							break;
						case MN_NAVIGATE:
							listStr.Format("%d - Navigate",m_currItemDefinitionPtr->m_interactionFileSet[j]);
							break;
		}
		int indx = m_interactionList.AddString(listStr);
		
		m_interactionList.SetItemData(indx,j);
		m_listMap.SetAt(j,m_currItemDefinitionPtr->m_interactionFileSet[j]);
	}
}

void ItemDefinitionView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();	
	
}


void ItemDefinitionView::FillItemDetails(int selIndx,ItemDefinition& itemDefinition)
{
	if (selIndx != CB_ERR)
	{
		m_fileSetID = itemDefinition.m_interactionFileSet[selIndx];
		m_comboInteractionType.SetCurSel(itemDefinition.m_interactionType[selIndx]);

		UpdateData(FALSE);
		OnSelendokComboInterationType();

		if (itemDefinition.m_interactionType[selIndx] == MN_ACTION ||
			  itemDefinition.m_interactionType[selIndx] == MN_NAVIGATE)
		{
			m_comboInteractionSubType.EnableWindow(FALSE);
			m_comboInteractionSubType.SetCurSel(-1);
		}
		else
		{
			if (itemDefinition.m_interactionType[selIndx] != MN_INVENTORY)
			{
				m_comboInteractionSubType.SetCurSel(itemDefinition.m_interactionSubType[selIndx]);
			}
			else
			{
				int inventNum = itemDefinition.m_interactionSubType[selIndx];
				CString inventStr;
				inventStr.Format("%d",inventNum);
				m_comboInteractionSubType.SelectString(-1 , inventStr);
			}  		
		}
		m_triggerScript = itemDefinition.m_interactionTriggerScript[selIndx];
		m_description = itemDefinition.m_interactionDescription[selIndx];
		m_isInteractionEnabled = itemDefinition.m_interactionOptionIsEnabled[selIndx];
	}
	else
	{
		m_fileSetID = 0;
		m_comboInteractionType.SetCurSel(0);
		m_comboInteractionSubType.SetCurSel(0);
		m_triggerScript = 0;
		m_description = "";
		m_isInteractionEnabled = FALSE;
	}
	UpdateData(FALSE);	
}

void ItemDefinitionView::OnRuntimeSave()
{
	UpdateData(TRUE);
	if (m_currItemDefinitionPtr != NULL)
	{
		m_currItemDefinitionPtr->m_hoverScript = m_hoverScript;
		m_currItemDefinitionPtr->m_feedbackString	=	m_feedbackString;
		m_currItemDefinitionPtr->m_itemIsStashed = m_isStashedItem ? true : false;
		
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

int ItemDefinitionView::IsExistInventory(short fileSetId)
{
	if (m_currItemDefinitionPtr != NULL)
	{
		for (int i = 0 ; i < m_currItemDefinitionPtr->m_interactionCount;i++)
		{		
			if (m_currItemDefinitionPtr->m_interactionFileSet[i] == fileSetId)
			{
				return i;
			}
		}
	}
	return NOT_FOUND;
}


void ItemDefinitionView::OnSelchangeListInteraction() 
{
	UpdateData(TRUE);
	int indx = m_interactionList.GetCurSel();
	int indxInArr = m_interactionList.GetItemData(indx);
	short listFilesetID;
	m_listMap.Lookup(indxInArr,listFilesetID);

	if (m_currItemDefinitionPtr != NULL)
	{
		if (m_currItemDefinitionPtr->m_interactionFileSet[indxInArr] == listFilesetID)
		{				
			FillItemDetails(indxInArr,*m_currItemDefinitionPtr);
		}
	}	
}

void ItemDefinitionView::OnDelete() 
{
	int indx = m_interactionList.GetCurSel();

	int indxInArr = m_interactionList.GetItemData(indx);
	short interactionID;
	m_listMap.Lookup(indxInArr,interactionID);

	if ((IsExistInventory(interactionID)) != NOT_FOUND)
	{		
		if (m_currItemDefinitionPtr != NULL)
		{
			if (m_currItemDefinitionPtr->m_interactionFileSet[indxInArr] == interactionID)
			{
				m_currItemDefinitionPtr->m_interactionFileSet.RemoveByIndex(indxInArr);
				m_currItemDefinitionPtr->m_interactionType.RemoveByIndex(indxInArr);
				m_currItemDefinitionPtr->m_interactionSubType.RemoveByIndex(indxInArr);
				m_currItemDefinitionPtr->m_interactionTriggerScript.RemoveByIndex(indxInArr);
				m_currItemDefinitionPtr->m_interactionDescription.RemoveByIndex(indxInArr);
				m_currItemDefinitionPtr->m_interactionOptionIsEnabled.RemoveByIndex(indxInArr);
				m_currItemDefinitionPtr->m_interactionCount--;
			}
		}
	}

	m_listMap.RemoveKey(indxInArr);

	m_interactionList.DeleteString(indx);

	for (int i = indxInArr; i <= m_currItemDefinitionPtr->m_interactionCount - 1 ;i++)
	{
		int indxOldInArr = m_interactionList.GetItemData(i);
		m_interactionList.SetItemData(i,indxOldInArr - 1);
		m_listMap.SetAt(indxOldInArr - 1,m_currItemDefinitionPtr->m_interactionFileSet[indxOldInArr - 1]);
	}

	m_interactionList.SetCurSel(0);
	OnSelchangeListInteraction();
}

void ItemDefinitionView::OnAdd() 
{
	if (UpdateData(TRUE))
	{
		if (m_currItemDefinitionPtr != NULL)
		{
			int indx = m_currItemDefinitionPtr->m_interactionCount;
			m_currItemDefinitionPtr->m_interactionFileSet.PushBack(m_fileSetID);
			m_currItemDefinitionPtr->m_interactionType.PushBack((InteractionType)m_comboInteractionType.GetCurSel());
			
			indx = m_comboInteractionType.GetCurSel();
			int interactSubType = 0;
			if (indx == MN_INVENTORY ||
				indx == MN_SENSES)
			{
				if (indx == MN_SENSES)
				{
					interactSubType = m_comboInteractionSubType.GetCurSel();
				}
				else
				{
					CString inventIdStr;
					int comboIndx = m_comboInteractionSubType.GetCurSel();
					if (comboIndx != CB_ERR)
					{
						m_comboInteractionSubType.GetLBText(comboIndx,inventIdStr);
					}
					interactSubType = atoi(inventIdStr);
				}
			}
			
			m_currItemDefinitionPtr->m_interactionSubType.PushBack(interactSubType);
			m_currItemDefinitionPtr->m_interactionTriggerScript.PushBack(m_triggerScript);
			m_currItemDefinitionPtr->m_interactionDescription.PushBack(m_description.GetBuffer(0));
			m_currItemDefinitionPtr->m_interactionOptionIsEnabled.PushBack(m_isInteractionEnabled ? true : false);
			
			CString listStr;
			int id = m_interactionList.GetCount() + 1;
			switch(indx)
			{
			case MN_INVENTORY:
				listStr.Format("%d - Inventory,Item #%d",m_currItemDefinitionPtr->m_interactionFileSet[m_currItemDefinitionPtr->m_interactionCount],interactSubType);
				break;
			case MN_SENSES:
				switch(interactSubType)
				{
				case 	SUB_LOOK:
					listStr.Format("%d - Senses,Look",m_currItemDefinitionPtr->m_interactionFileSet[m_currItemDefinitionPtr->m_interactionCount]);
					break;
				case SUB_SMELL:
					listStr.Format("%d - Senses,Smell",m_currItemDefinitionPtr->m_interactionFileSet[m_currItemDefinitionPtr->m_interactionCount]);
					break;
				case SUB_TASTE:
					listStr.Format("%d - Senses,Taste",m_currItemDefinitionPtr->m_interactionFileSet[m_currItemDefinitionPtr->m_interactionCount]);
					break;
				case SUB_TEXTURE:
					listStr.Format("%d - Senses,Texture",m_currItemDefinitionPtr->m_interactionFileSet[m_currItemDefinitionPtr->m_interactionCount]);
					break;
				case SUB_SOUND:
					listStr.Format("%d - Senses,Sound",m_currItemDefinitionPtr->m_interactionFileSet[m_currItemDefinitionPtr->m_interactionCount]);
					break;
				}					
				break;
				case MN_ACTION:
					listStr.Format("%d - Action",m_currItemDefinitionPtr->m_interactionFileSet[m_currItemDefinitionPtr->m_interactionCount]);
					break;
				case MN_NAVIGATE:
					listStr.Format("%d - Navigate",m_currItemDefinitionPtr->m_interactionFileSet[m_currItemDefinitionPtr->m_interactionCount]);
					break;
			}
			m_listMap.SetAt(m_currItemDefinitionPtr->m_interactionCount,m_fileSetID);
			
			int indxList = m_interactionList.AddString(listStr);
			m_interactionList.SetItemData(indxList,m_currItemDefinitionPtr->m_interactionCount);
			m_currItemDefinitionPtr->m_interactionCount++;
		}
	}
}

void ItemDefinitionView::OnEdit() 
{
	if (UpdateData(TRUE))
	{
		int listIndx = m_interactionList.GetCurSel();
		short interactionID = m_interactionList.GetItemData(listIndx);
		
		int indxInArr = m_interactionList.GetItemData(listIndx);
		short listFilesetID;
		m_listMap.Lookup(indxInArr,listFilesetID);

		if ((IsExistInventory(m_fileSetID)) != NOT_FOUND)
		{
			if (m_fileSetID != listFilesetID)
			{
				MessageBox("Can't update Fileset ID","Error",MB_OK + MB_ICONWARNING);
			}
			else
			{
				if (m_currItemDefinitionPtr != NULL)
				{
					m_currItemDefinitionPtr->m_interactionFileSet[indxInArr] = m_fileSetID;
					m_currItemDefinitionPtr->m_interactionType[indxInArr] = (InteractionType)m_comboInteractionType.GetCurSel();

					int indx = m_comboInteractionType.GetCurSel();
					int interactSubType = 0;
					CString oldStr;
					m_interactionList.GetText(listIndx,oldStr);
					m_interactionList.DeleteString(listIndx);
					int indxNum = oldStr.Find('-');
					oldStr = oldStr.Left(indxNum + 1);

					if (indx == MN_INVENTORY ||
						  indx == MN_SENSES)
					{
						if (indx == MN_SENSES)
						{
							interactSubType = m_comboInteractionSubType.GetCurSel();
							switch(interactSubType)
							{
							case 	SUB_LOOK:
								oldStr += " Senses,Look";
								break;
							case SUB_SMELL:
								oldStr += " Senses,Smell";
								break;
							case SUB_TASTE:
								oldStr += " Senses,Taste";
								break;
							case SUB_TEXTURE:
								oldStr += " Senses,Texture";
								break;
							case SUB_SOUND:
								oldStr += " Senses,Sound";
								break;
							}					

						}
						else
						{
							CString inventIdStr;
							int comboIndx = m_comboInteractionSubType.GetCurSel();
							if (comboIndx != CB_ERR)
							{
								m_comboInteractionSubType.GetLBText(comboIndx,inventIdStr);
							}
							interactSubType = atoi(inventIdStr);
							oldStr += " Inventory,Item #";
							oldStr += inventIdStr;
						}
					}
					else
					{
						if (indx == MN_ACTION)
						{
							oldStr += " Action";
						}
						if (indx == MN_NAVIGATE)
						{
							oldStr += " Navigate";
						}
					}

					int newIndx = m_interactionList.InsertString(listIndx,oldStr);
					m_interactionList.SetItemData(newIndx,indxInArr);

					m_currItemDefinitionPtr->m_interactionSubType[indxInArr] = interactSubType ;
					m_currItemDefinitionPtr->m_interactionTriggerScript[indxInArr] = m_triggerScript;
					m_currItemDefinitionPtr->m_interactionDescription[indxInArr] = m_description.GetBuffer(0);
					m_currItemDefinitionPtr->m_interactionOptionIsEnabled[indxInArr] = m_isInteractionEnabled ? true : false;
				}
			}
		}		
		else
		{
			MessageBox("This Fileset ID not exist!","Error",MB_OK + MB_ICONWARNING);
		}
	}
}

void ItemDefinitionView::OnSelendokComboInterationType() 
{
	UpdateData(TRUE);
	int indx = m_comboInteractionType.GetCurSel();
	if (indx == MN_ACTION ||
		  indx == MN_NAVIGATE)
	{
		m_comboInteractionSubType.EnableWindow(FALSE);
		m_comboInteractionSubType.SetCurSel(-1);
	}
	else
	{
		m_comboInteractionSubType.ResetContent();
		if (indx == MN_INVENTORY)
		{
			for (int i = 0 ; i < m_world.m_inventorySize; i++)
			{
				CString inventoryIdStr;
				inventoryIdStr.Format("%d",m_world.m_inventory[i].m_itemID);
				m_comboInteractionSubType.AddString(inventoryIdStr);
			}
		}
		else
		{
			for (int i = 0; i < SUB_TYPE_LAST; i++)
			{
				m_comboInteractionSubType.AddString(SubTypeStr[i]);
			}
		}
		m_comboInteractionSubType.SetCurSel(0);

		m_comboInteractionSubType.EnableWindow(TRUE);
	}
}

void ItemDefinitionView::OnUpdateWorldObject()
{
  GetMyWorld();
}

void ItemDefinitionView::OnUp() 
{
	int listIndx = m_interactionList.GetCurSel();
	if (listIndx != 0)
	{
		if (m_currItemDefinitionPtr != NULL)
		{
			m_currItemDefinitionPtr->m_interactionFileSet.Replace(listIndx - 1,listIndx);
			m_currItemDefinitionPtr->m_interactionType.Replace(listIndx - 1,listIndx);
			m_currItemDefinitionPtr->m_interactionSubType.Replace(listIndx - 1,listIndx);
			m_currItemDefinitionPtr->m_interactionTriggerScript.Replace(listIndx - 1,listIndx);
			m_currItemDefinitionPtr->m_interactionDescription.Replace(listIndx - 1,listIndx);
			m_currItemDefinitionPtr->m_interactionOptionIsEnabled.Replace(listIndx - 1,listIndx);

			//fill list
			FillIterationList();
			m_interactionList.SetCurSel(listIndx - 1);
		}	
	}	
}

void ItemDefinitionView::OnDown() 
{
	int listIndx = m_interactionList.GetCurSel();
	if (listIndx != m_interactionList.GetCount() - 1)
	{
		if (m_currItemDefinitionPtr != NULL)
		{
			m_currItemDefinitionPtr->m_interactionFileSet.Replace(listIndx,listIndx + 1);
			m_currItemDefinitionPtr->m_interactionType.Replace(listIndx,listIndx + 1);
			m_currItemDefinitionPtr->m_interactionSubType.Replace(listIndx,listIndx + 1);
			m_currItemDefinitionPtr->m_interactionTriggerScript.Replace(listIndx,listIndx + 1);
			m_currItemDefinitionPtr->m_interactionDescription.Replace(listIndx,listIndx + 1);
			m_currItemDefinitionPtr->m_interactionOptionIsEnabled.Replace(listIndx,listIndx + 1);

			//fill list
			FillIterationList();			
			m_interactionList.SetCurSel(listIndx + 1);
		}	
	}
}

void ItemDefinitionView::OnKillfocus() 
{
	UpdateData(TRUE);	
}
