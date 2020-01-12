// HotSpotInfoView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "HotSpotInfoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// HotSpotInfoView

IMPLEMENT_DYNCREATE(HotSpotInfoView, CFormView)

HotSpotInfoView::HotSpotInfoView()
	: CFormView(HotSpotInfoView::IDD)
{
	//{{AFX_DATA_INIT(HotSpotInfoView)
	m_bottomRect = 0;
	m_clickTrigger = 0;
	m_description = _T("");
	m_feedbackString = _T("");
	m_filesetID = 0;
	m_hotSpotID = 0;
	m_hoverScript = 0;
	m_isInteractionEnabled = FALSE;
	m_isTransformCursor = FALSE;
	m_leftRect = 0;
	m_rightRect = 0;
	m_topRect = 0;
	m_triggerScript = 0;
	m_unhoverScript = 0;
	//}}AFX_DATA_INIT
	m_currHotSpotPtr = NULL;
	m_currSceneDefPtr = NULL;
}

HotSpotInfoView::~HotSpotInfoView()
{
}

void HotSpotInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(HotSpotInfoView)
	DDX_Control(pDX, IDC_SPIN_Y2, m_spinY2);
	DDX_Control(pDX, IDC_SPIN_Y1, m_spinY1);
	DDX_Control(pDX, IDC_SPIN_X2, m_spinX2);
	DDX_Control(pDX, IDC_SPIN_X1, m_spinX1);
	DDX_Control(pDX, IDC_LIST_INTERACTION, m_interactionList);
	DDX_Control(pDX, IDC_COMBO_INTERATION_TYPE, m_comboInteractionType);
	DDX_Control(pDX, IDC_COMBO_INTERACTION_SUB_TYPE, m_comboInteractionSubType);
	DDX_Control(pDX, IDC_COMBO_IMAGE_ID, m_comboImageID);
	DDX_Control(pDX, IDC_COMBO_HOT_SPOT_MODE, m_comboHotSpotMode);
	DDX_Control(pDX, IDC_COMBO_CHARACTER_ID, m_comboCharacterID);
	DDX_Control(pDX, IDC_COMBO_ANIMATION_ID, m_comboAnimationID);
	DDX_Text(pDX, IDC_BOTTOM_RECT, m_bottomRect);
	DDX_Text(pDX, IDC_CLICK_TRIGGER, m_clickTrigger);
	DDX_Text(pDX, IDC_DESCRIPTION, m_description);
	DDX_Text(pDX, IDC_FEEDBACK_STRING, m_feedbackString);
	DDX_Text(pDX, IDC_FILESET_ID, m_filesetID);
	DDX_Text(pDX, IDC_HOT_SPOT_ID, m_hotSpotID);
	DDX_Text(pDX, IDC_HOVER_SCRIPT, m_hoverScript);
	DDX_Check(pDX, IDC_IS_INTERACTION_ENABLED, m_isInteractionEnabled);
	DDX_Check(pDX, IDC_IS_TRANSFORM_CURSOR, m_isTransformCursor);
	DDX_Text(pDX, IDC_LEFT_RECT, m_leftRect);
	DDX_Text(pDX, IDC_RIGHT_RECT, m_rightRect);
	DDX_Text(pDX, IDC_TOP_RECT, m_topRect);
	DDX_Text(pDX, IDC_TRIGGER_SCRIPT, m_triggerScript);
	DDX_Text(pDX, IDC_UNHOVER_SCRIPT, m_unhoverScript);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(HotSpotInfoView, CFormView)
	//{{AFX_MSG_MAP(HotSpotInfoView)
	ON_LBN_SELCHANGE(IDC_LIST_INTERACTION, OnSelchangeListInteraction)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_CBN_SELENDOK(IDC_COMBO_INTERATION_TYPE, OnSelendokComboInterationType)
	ON_BN_CLICKED(IDC_UP, OnUp)
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	//}}AFX_MSG_MAP
	ON_MESSAGE(RUNTIME_SAVE_MESSAGE,OnRuntimeSave)
	ON_MESSAGE(UPDATE_DELETING_IN_WORLD,OnUpdateWorldObject)
	ON_EN_KILLFOCUS(IDC_HOVER_SCRIPT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_UNHOVER_SCRIPT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_CLICK_TRIGGER, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LEFT_RECT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TOP_RECT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_RIGHT_RECT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_BOTTOM_RECT, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_FILESET_ID, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TRIGGER_SCRIPT, OnKillfocus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HotSpotInfoView diagnostics

#ifdef _DEBUG
void HotSpotInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

void HotSpotInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// HotSpotInfoView message handlers
CWorldConstructKitDoc* HotSpotInfoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));
	return (CWorldConstructKitDoc*)m_pDocument;
}

BOOL HotSpotInfoView::GetMyWorld()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	m_worldId = pTreeView->GetCurrWorldID();	
	
	CWorldConstructKitDoc* doc = GetDocument();
	BOOL result = doc->m_worldMap.Lookup(m_worldId,m_world);	
  return result;
}

DWORD HotSpotInfoView::GetCurrHotSpotID()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrNodeID();
}

DWORD HotSpotInfoView::GetCurrSceneId()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrSceneId();
}


void HotSpotInfoView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (GetMyWorld())
	{		

		DWORD sceneId = GetCurrSceneId();
 		DWORD id = GetCurrHotSpotID();

		for (int i = 0 ; i < m_world.m_numberOfScenes; i++)
		{
			if (m_world.m_scenes[i].m_sceneID == sceneId)
			{				
				m_currSceneDefPtr = &m_world.m_scenes[i];
				m_world.m_scenes[i].m_clickSpots.ScanInit(DIRECTION_FORWARD);
				for (int j = 0; j < m_world.m_scenes[i].m_clickCount; j++)
				{
					m_currHotSpotPtr = &m_world.m_scenes[i].m_clickSpots.NextElement(); 
					if (m_currHotSpotPtr->m_hotSpotID == id)
					{
						CString animationIdStr;
						m_world.m_scenes[i].m_animations.ScanInit(DIRECTION_FORWARD);
						m_comboAnimationID.ResetContent();
						for(int k = 0; k < m_world.m_scenes[i].m_animationCount; k++)
						{
							AnimationInfo& animation = m_world.m_scenes[i].m_animations.NextElement();
							animationIdStr.Format("%d",animation.m_animationID);
							int indx = m_comboAnimationID.AddString(animationIdStr);	
							m_comboAnimationID.SetItemData(indx,animation.m_animationID);
						}

						if (m_world.m_scenes[i].m_animationCount == 0)
						{
							m_comboAnimationID.EnableWindow(FALSE);
						}

						CString characterIdStr;
						m_world.m_scenes[i].m_sceneCharacters.ScanInit(DIRECTION_FORWARD);
						m_comboCharacterID.ResetContent();
						for( k = 0; k < m_world.m_scenes[i].m_characterCount; k++)
						{
							CharacterContext& character = m_world.m_scenes[i].m_sceneCharacters.NextElement();
							characterIdStr.Format("%d",character.m_characterId);
							int indx = m_comboCharacterID.AddString(characterIdStr);	
							m_comboCharacterID.SetItemData(indx,character.m_characterId);
						}

						if (m_world.m_scenes[i].m_characterCount == 0)
						{
							m_comboCharacterID.EnableWindow(FALSE);
						}

						CString imageIdStr;
						m_world.m_scenes[i].m_images.ScanInit(DIRECTION_FORWARD);
						m_comboImageID.ResetContent();
						for(k = 0; k < m_world.m_scenes[i].m_imageCount; k++)
						{
							ImageInfo& image = m_world.m_scenes[i].m_images.NextElement();
							imageIdStr.Format("%d",image.m_imageID);
							int indx = m_comboImageID.AddString(imageIdStr);	
							m_comboImageID.SetItemData(indx,image.m_imageID);
						}

						if (m_world.m_scenes[i].m_imageCount == 0)
						{
							m_comboImageID.EnableWindow(FALSE);
						}


						animationIdStr.Format("%d",m_currHotSpotPtr->m_animationInfo.m_animationID);
						m_comboAnimationID.SelectString(-1,animationIdStr);

						characterIdStr.Format("%d",m_currHotSpotPtr->m_characterInfo.m_characterId);
						m_comboCharacterID.SelectString(-1,characterIdStr);

						imageIdStr.Format("%d",m_currHotSpotPtr->m_imageInfo.m_imageID);
						m_comboImageID.SelectString(-1,imageIdStr);

						m_comboHotSpotMode.SetCurSel(m_currHotSpotPtr->m_hotSpotMode);
						
						m_clickTrigger = m_currHotSpotPtr->m_clickTrigger;
						m_feedbackString = m_currHotSpotPtr->m_feedbackString;						
						m_hotSpotID = m_currHotSpotPtr->m_hotSpotID;						
						m_isTransformCursor = m_currHotSpotPtr->m_transformCursor;
            m_bottomRect = m_currHotSpotPtr->m_bottomRect;
						m_leftRect = m_currHotSpotPtr->m_leftRect;
						m_rightRect = m_currHotSpotPtr->m_rightRect;
						m_topRect = m_currHotSpotPtr->m_topRect;
						m_unhoverScript = m_currHotSpotPtr->m_unHoverScript;			
						m_hoverScript = m_currHotSpotPtr->m_hoverScript;
						FillIterationList();
						
						if (m_currHotSpotPtr->m_interactionCount > 0)
						{
							m_interactionList.SetCurSel(0);
						}
						int selIndx = m_interactionList.GetCurSel();
						FillItemDetails(selIndx,*m_currHotSpotPtr);						
						
						UpdateData(FALSE);
						break;
					}		
				}
			}
		}				
	}	
}

void HotSpotInfoView::FillIterationList()
{
	CString listStr;
	m_interactionList.ResetContent();
	for (int j = 0; j < m_currHotSpotPtr->m_interactionCount;j++)
	{
		switch(m_currHotSpotPtr->m_interactionType[j])
		{
		case MN_INVENTORY:
			listStr.Format("%d - Inventory,Item #%d",m_currHotSpotPtr->m_interactionFileSet[j],m_currHotSpotPtr->m_interactionSubType[j]);
			break;
		case MN_SENSES:
			switch(m_currHotSpotPtr->m_interactionSubType[j])
			{
			case 	SUB_LOOK:
				listStr.Format("%d - Senses,Look",m_currHotSpotPtr->m_interactionFileSet[j]);
				break;
			case SUB_SMELL:
				listStr.Format("%d - Senses,Smell",m_currHotSpotPtr->m_interactionFileSet[j]);
				break;
			case SUB_TASTE:
				listStr.Format("%d - Senses,Taste",m_currHotSpotPtr->m_interactionFileSet[j]);
				break;
			case SUB_TEXTURE:
				listStr.Format("%d - Senses,Texture",m_currHotSpotPtr->m_interactionFileSet[j]);
				break;
			case SUB_SOUND:
				listStr.Format("%d - Senses,Sound",m_currHotSpotPtr->m_interactionFileSet[j]);
				break;
			}					
			break;
			case MN_ACTION:
				listStr.Format("%d - Action",m_currHotSpotPtr->m_interactionFileSet[j]);
				break;
			case MN_NAVIGATE:
				listStr.Format("%d - Navigate",m_currHotSpotPtr->m_interactionFileSet[j]);
				break;
		}
		int indx = m_interactionList.AddString(listStr);
		
		m_interactionList.SetItemData(indx,j);
		m_listMap.SetAt(j,m_currHotSpotPtr->m_interactionFileSet[j]);
	}
}

void HotSpotInfoView::FillItemDetails(int selIndx,HotspotInfo& itemDefinition)
{
	if (selIndx != CB_ERR)
	{
		m_filesetID = itemDefinition.m_interactionFileSet[selIndx];
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
		m_filesetID = 0;
		m_comboInteractionType.SetCurSel(0);
		m_comboInteractionSubType.SetCurSel(0);
		m_triggerScript = 0;
		m_description = "";
		m_isInteractionEnabled = FALSE;
	}
	UpdateData(FALSE);	
}


void HotSpotInfoView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	m_spinY2.SetBuddy(GetDlgItem(IDC_BOTTOM_RECT));
	m_spinY1.SetBuddy(GetDlgItem(IDC_TOP_RECT));
	m_spinX2.SetBuddy(GetDlgItem(IDC_RIGHT_RECT));
	m_spinX1.SetBuddy(GetDlgItem(IDC_LEFT_RECT));

	m_spinY2.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinY1.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinX2.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinX1.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);	
}

void HotSpotInfoView::OnRuntimeSave()
{
	UpdateData(TRUE);
	if (m_currHotSpotPtr != NULL)
	{
		int imageId;
		int indx = m_comboImageID.GetCurSel();
		if (indx != CB_ERR)
		{
			imageId = m_comboImageID.GetItemData(indx);
		}

		int characterId;
		indx = m_comboCharacterID.GetCurSel();
		if (indx != CB_ERR)
		{
			characterId = m_comboCharacterID.GetItemData(indx);
		}

		int animationId;
		indx = m_comboAnimationID.GetCurSel();
		if (indx != CB_ERR)
		{
			animationId = m_comboAnimationID.GetItemData(indx);
		}

		m_currSceneDefPtr->m_animations.ScanInit(DIRECTION_FORWARD);		
		for(int k = 0; k < m_currSceneDefPtr->m_animationCount; k++)
		{
			AnimationInfo& animation = m_currSceneDefPtr->m_animations.NextElement();
			if (animation.m_animationID == animationId)
			{
				m_currHotSpotPtr->m_animationInfo = animation;
				break;
			}			
		}

		m_currSceneDefPtr->m_sceneCharacters.ScanInit(DIRECTION_FORWARD);		
		for(k = 0; k < m_currSceneDefPtr->m_characterCount; k++)
		{
			CharacterContext& character = m_currSceneDefPtr->m_sceneCharacters.NextElement();
			if (character.m_characterId == characterId)
			{
				m_currHotSpotPtr->m_characterInfo = character;
				break;
			}			
		}

		m_currSceneDefPtr->m_images.ScanInit(DIRECTION_FORWARD);		
		for(k = 0; k < m_currSceneDefPtr->m_imageCount; k++)
		{
			ImageInfo& image = m_currSceneDefPtr->m_images.NextElement();
			if (image.m_imageID == imageId)
			{
				m_currHotSpotPtr->m_imageInfo = image;
				break;
			}			
		}

		m_currHotSpotPtr->m_hotSpotMode	=	(HotSpotModeType)m_comboHotSpotMode.GetCurSel();		
		m_currHotSpotPtr->m_clickTrigger = m_clickTrigger;
		m_currHotSpotPtr->m_feedbackString = m_feedbackString;						
		m_currHotSpotPtr->m_hotSpotID =	m_hotSpotID ;						
		m_currHotSpotPtr->m_transformCursor =	m_isTransformCursor ? true : false;
    m_currHotSpotPtr->m_bottomRect = m_bottomRect;
		m_currHotSpotPtr->m_leftRect = m_leftRect;
		m_currHotSpotPtr->m_rightRect	=	m_rightRect;
		m_currHotSpotPtr->m_topRect =	m_topRect;
		m_currHotSpotPtr->m_unHoverScript =	m_unhoverScript;			
		m_currHotSpotPtr->m_hoverScript =	m_hoverScript;
		
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

int HotSpotInfoView::IsExistInventory(short fileSetId)
{
	if (m_currHotSpotPtr != NULL)
	{
		for (int i = 0 ; i < m_currHotSpotPtr->m_interactionCount;i++)
		{		
			if (m_currHotSpotPtr->m_interactionFileSet[i] == fileSetId)
			{
				return i;
			}
		}
	}
	return NOT_FOUND;
}

void HotSpotInfoView::OnSelchangeListInteraction() 
{
	UpdateData(TRUE);
	int indx = m_interactionList.GetCurSel();	
	int indxInArr = m_interactionList.GetItemData(indx);
	short listFilesetID;
	m_listMap.Lookup(indxInArr,listFilesetID);

	if (m_currHotSpotPtr != NULL)
	{
		if (m_currHotSpotPtr->m_interactionFileSet[indxInArr] == listFilesetID)
		{				
			FillItemDetails(indxInArr,*m_currHotSpotPtr);
		}
	}		
}

void HotSpotInfoView::OnAdd() 
{
	if (UpdateData(TRUE))
	{
		if (m_currHotSpotPtr != NULL)
		{
			int indx = m_currHotSpotPtr->m_interactionCount;
			m_currHotSpotPtr->m_interactionFileSet.PushBack(m_filesetID);
			m_currHotSpotPtr->m_interactionType.PushBack((InteractionType)m_comboInteractionType.GetCurSel());
			
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

			m_currHotSpotPtr->m_interactionSubType.PushBack(interactSubType);
			m_currHotSpotPtr->m_interactionTriggerScript.PushBack(m_triggerScript);
			m_currHotSpotPtr->m_interactionDescription.PushBack(m_description.GetBuffer(0));
			m_currHotSpotPtr->m_interactionOptionIsEnabled.PushBack(m_isInteractionEnabled ? true : false);
			
			
			CString listStr;
			int id = m_interactionList.GetCount() + 1;
			switch(indx)
			{
			case MN_INVENTORY:
				listStr.Format("%d - Inventory,Item #%d",m_currHotSpotPtr->m_interactionFileSet[m_currHotSpotPtr->m_interactionCount],interactSubType);
				break;
			case MN_SENSES:
				switch(interactSubType)
				{
				case 	SUB_LOOK:
					listStr.Format("%d - Senses,Look",m_currHotSpotPtr->m_interactionFileSet[m_currHotSpotPtr->m_interactionCount]);
					break;
				case SUB_SMELL:
					listStr.Format("%d - Senses,Smell",m_currHotSpotPtr->m_interactionFileSet[m_currHotSpotPtr->m_interactionCount]);
					break;
				case SUB_TASTE:
					listStr.Format("%d - Senses,Taste",m_currHotSpotPtr->m_interactionFileSet[m_currHotSpotPtr->m_interactionCount]);
					break;
				case SUB_TEXTURE:
					listStr.Format("%d - Senses,Texture",m_currHotSpotPtr->m_interactionFileSet[m_currHotSpotPtr->m_interactionCount]);
					break;
				case SUB_SOUND:
					listStr.Format("%d - Senses,Sound",m_currHotSpotPtr->m_interactionFileSet[m_currHotSpotPtr->m_interactionCount]);
					break;
				}					
				break;
				case MN_ACTION:
					listStr.Format("%d - Action",m_currHotSpotPtr->m_interactionFileSet[m_currHotSpotPtr->m_interactionCount]);
					break;
				case MN_NAVIGATE:
					listStr.Format("%d - Navigate",m_currHotSpotPtr->m_interactionFileSet[m_currHotSpotPtr->m_interactionCount]);
					break;
			}
			m_listMap.SetAt(m_currHotSpotPtr->m_interactionCount,m_filesetID);
			
			int indxList = m_interactionList.AddString(listStr);
			m_interactionList.SetItemData(indxList,m_currHotSpotPtr->m_interactionCount);
			m_currHotSpotPtr->m_interactionCount++;
		}
	}	
}

void HotSpotInfoView::OnEdit() 
{
	if (UpdateData(TRUE))
	{
		int listIndx = m_interactionList.GetCurSel();

		int indxInArr = m_interactionList.GetItemData(listIndx);
		short listFilesetID;
		m_listMap.Lookup(indxInArr,listFilesetID);

		if ((IsExistInventory(m_filesetID)) != NOT_FOUND)
		{
			if (m_filesetID != listFilesetID)
			{
				MessageBox("Can't update Fileset ID","Error",MB_OK + MB_ICONWARNING);
			}
			else
			{
				if (m_currHotSpotPtr != NULL)
				{
					m_currHotSpotPtr->m_interactionFileSet[indxInArr] = m_filesetID;
					m_currHotSpotPtr->m_interactionType[indxInArr] =(InteractionType)m_comboInteractionType.GetCurSel();

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

					m_currHotSpotPtr->m_interactionSubType[indxInArr] = interactSubType;
					m_currHotSpotPtr->m_interactionTriggerScript[indxInArr] = m_triggerScript;
					m_currHotSpotPtr->m_interactionDescription[indxInArr] = m_description.GetBuffer(0);
					m_currHotSpotPtr->m_interactionOptionIsEnabled[indxInArr] = m_isInteractionEnabled ? true : false;
				}
			}
		}		
		else
		{
			MessageBox("This Fileset ID not exist!","Error",MB_OK + MB_ICONWARNING);
		}
	}
}

void HotSpotInfoView::OnDelete() 
{
	int indx = m_interactionList.GetCurSel();

	int indxInArr = m_interactionList.GetItemData(indx);
	short interactionID;
	m_listMap.Lookup(indxInArr,interactionID);

	if ((IsExistInventory(interactionID)) != NOT_FOUND)
	{		
		if (m_currHotSpotPtr != NULL)
		{
			if (m_currHotSpotPtr->m_interactionFileSet[indxInArr] == interactionID)
			{
				m_currHotSpotPtr->m_interactionFileSet.RemoveByIndex(indxInArr);
				m_currHotSpotPtr->m_interactionType.RemoveByIndex(indxInArr);
				m_currHotSpotPtr->m_interactionSubType.RemoveByIndex(indxInArr);
				m_currHotSpotPtr->m_interactionTriggerScript.RemoveByIndex(indxInArr);
				m_currHotSpotPtr->m_interactionDescription.RemoveByIndex(indxInArr);
				m_currHotSpotPtr->m_interactionOptionIsEnabled.RemoveByIndex(indxInArr);
				m_currHotSpotPtr->m_interactionCount--;
			}
		}
	}

	m_listMap.RemoveKey(indxInArr);
	m_interactionList.DeleteString(indx);

	for (int i = indxInArr; i <= m_currHotSpotPtr->m_interactionCount - 1 ;i++)
	{
		int indxOldInArr = m_interactionList.GetItemData(i);
		m_interactionList.SetItemData(i,indxOldInArr - 1);
		m_listMap.SetAt(indxOldInArr - 1,m_currHotSpotPtr->m_interactionFileSet[indxOldInArr - 1]);
	}

	m_interactionList.SetCurSel(0);
	OnSelchangeListInteraction();	
}

void HotSpotInfoView::OnSelendokComboInterationType() 
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

void HotSpotInfoView::OnUpdateWorldObject()
{
  GetMyWorld();
}

void HotSpotInfoView::OnUp() 
{
	int listIndx = m_interactionList.GetCurSel();
	if (listIndx != 0)
	{
		if (m_currHotSpotPtr != NULL)
		{
			m_currHotSpotPtr->m_interactionFileSet.Replace(listIndx - 1,listIndx);
			m_currHotSpotPtr->m_interactionType.Replace(listIndx - 1,listIndx);
			m_currHotSpotPtr->m_interactionSubType.Replace(listIndx - 1,listIndx);
			m_currHotSpotPtr->m_interactionTriggerScript.Replace(listIndx - 1,listIndx);
			m_currHotSpotPtr->m_interactionDescription.Replace(listIndx - 1,listIndx);
			m_currHotSpotPtr->m_interactionOptionIsEnabled.Replace(listIndx - 1,listIndx);

			//fill list
			FillIterationList();
			m_interactionList.SetCurSel(listIndx - 1);
		}	
	}	
}

void HotSpotInfoView::OnDown() 
{
	int listIndx = m_interactionList.GetCurSel();
	if (listIndx != m_interactionList.GetCount() - 1)
	{
		if (m_currHotSpotPtr != NULL)
		{
			m_currHotSpotPtr->m_interactionFileSet.Replace(listIndx,listIndx + 1);
			m_currHotSpotPtr->m_interactionType.Replace(listIndx,listIndx + 1);
			m_currHotSpotPtr->m_interactionSubType.Replace(listIndx,listIndx + 1);
			m_currHotSpotPtr->m_interactionTriggerScript.Replace(listIndx,listIndx + 1);
			m_currHotSpotPtr->m_interactionDescription.Replace(listIndx,listIndx + 1);
			m_currHotSpotPtr->m_interactionOptionIsEnabled.Replace(listIndx,listIndx + 1);

			//fill list
			FillIterationList();	
			m_interactionList.SetCurSel(listIndx + 1);
		}	
	}
}

void HotSpotInfoView::OnKillfocus() 
{
	UpdateData(TRUE);	
}

