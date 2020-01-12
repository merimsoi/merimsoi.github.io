// MyTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "MyTreeView.h"
#include "forms.h"
#include "WorldConstructKitDoc.h"
#include "NewNodeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{
}

CMyTreeView::~CMyTreeView()
{
	delete m_pTreeImageList;
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	//{{AFX_MSG_MAP(CMyTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(TVN_SELCHANGING, OnSelchanging)
	//}}AFX_MSG_MAP
	ON_MESSAGE(CHANGE_SCENE_ID,OnChangeSceneId)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView drawing

void CMyTreeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView diagnostics

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView message handlers

void CMyTreeView::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
	CTreeCtrl& treeCtrl = GetTreeCtrl();

	BOOL isSuccess;

	// create the CImageList with 16x16 images
	m_pTreeImageList= new CImageList();
	VERIFY (m_pTreeImageList->Create (16, 16, ILC_COLOR16, 4, 0));
	CBitmap bm;
	bm.LoadBitmap (IDB_TREE_IMAGES);
	// This will automatically parse the bitmap into nine images.
	m_pTreeImageList->Add (&bm, RGB(0,0,0));
	
	isSuccess = treeCtrl.ModifyStyle(0,TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS);
	treeCtrl.SetImageList(m_pTreeImageList,TVSIL_NORMAL);

	HTREEITEM worldItem;
	HTREEITEM sceneItem;
	HTREEITEM sceneListItem;
  HTREEITEM tempItem;

	for (int i = 0; i < ROOT_NUM; i++)
	{
		if (strcmp(WORLD_STR,rootNodes[i].lpszName) == 0)
		{
			worldItem = treeCtrl.InsertItem(rootNodes[i].lpszName , TEMPLATE_DYNAMIC_NODE,TEMPLATE_DYNAMIC_NODE);
			treeCtrl.SetItemData(worldItem,TEMPLATE_NODE);
		}
		else
		{
			tempItem = treeCtrl.InsertItem(rootNodes[i].lpszName, CLOSE_TREE_NODE,OPEN_TREE_NODE);
			treeCtrl.SetItemData(tempItem,TEMPLATE_NODE);
		}		
	}

	for (i = 0 ; i < WORLD_LEVEL_NUM; i++)
	{
		if (strcmp(SCENE_DEFINITION_STR,worldLevelNodes[i].lpszName) == 0)
		{
			sceneListItem = treeCtrl.InsertItem(SCENES_LIST_STR , LIST_NODE,LIST_NODE,worldItem);
			treeCtrl.SetItemData(sceneListItem,UNDEFINED_NODE);

			sceneItem = treeCtrl.InsertItem(worldLevelNodes[i].lpszName , TEMPLATE_DYNAMIC_NODE,TEMPLATE_DYNAMIC_NODE,sceneListItem);
			treeCtrl.SetItemData(sceneItem,TEMPLATE_NODE);
		}
		else
		{
			tempItem = treeCtrl.InsertItem(worldLevelNodes[i].lpszName, CLOSE_TREE_NODE,OPEN_TREE_NODE,worldItem);
			treeCtrl.SetItemData(tempItem,TEMPLATE_NODE);
		}		
	}

	for (i = 0; i < SCENE_DEFINITION_NUM; i++)
	{
		if (strcmp(STAGING_INFO_STR,sceneDefinitionNodes[i].lpszName) == 0)
		{
			tempItem = treeCtrl.InsertItem(sceneDefinitionNodes[i].lpszName, CHILD_TREE_NODE,CHILD_TREE_NODE,sceneItem);
			treeCtrl.SetItemData(tempItem,TEMPLATE_NODE);
		}
		else
		{
			tempItem = treeCtrl.InsertItem(sceneDefinitionNodes[i].lpszName, CLOSE_TREE_NODE,OPEN_TREE_NODE,sceneItem);
			treeCtrl.SetItemData(tempItem,TEMPLATE_NODE);
		}
	}		

	treeCtrl.Expand(worldItem,TVE_EXPAND);   
}

void CMyTreeView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	if (pNMTreeView->itemNew.hItem == NULL)
		return;

	CFormView* currFormPtr = STATIC_DOWNCAST(CFormView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,1));
	currFormPtr->SendMessage(RUNTIME_SAVE_MESSAGE,0,0);

	NodeType nodeType = (NodeType)GetTreeCtrl().GetItemData(pNMTreeView->itemNew.hItem);

	int resId = formData.GetResID(GetTreeCtrl().GetItemText(pNMTreeView->itemNew.hItem).GetBuffer(0));

	if (resId != 0)
	{
		if (nodeType == DYNAMIC_NODE ||
  			resId == IDD_WORLD ||
	  		resId == IDD_SCENE_DEFINITION ||
		  	resId == IDD_STAGING_INFO)
		{
			m_pSplitterWnd->ChangeView(0, 1,formData.GetViewClass(resId));	
		}
		else
		{
			m_pSplitterWnd->ChangeView(0, 1,RUNTIME_CLASS(TemplateFormView));		
		}
	}
	else
	{
		m_pSplitterWnd->ChangeView(0, 1,RUNTIME_CLASS(TemplateFormView));		
	}
		
	formData.SetCurrentForm(resId);
	*pResult = 0;
}

DWORD CMyTreeView::GetCurrWorldID()
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();	
	HTREEITEM hParentItem;
	HTREEITEM currItem = treeCtrl.GetSelectedItem();
	
  while((hParentItem = treeCtrl.GetParentItem(currItem)) != NULL)
	{
		currItem = hParentItem;
	}

	CString worldNodeText = treeCtrl.GetItemText(currItem);
	if (worldNodeText == (CString)WORLD_STR)
	{
		return DEFAULT_WORLD_ID;
	}
	else
	{
		int indx = worldNodeText.Find(')',0);
    CString IDStr = worldNodeText.Left(indx);
    IDStr = IDStr.Right(IDStr.GetLength() - 1);
		DWORD ID = atoi(IDStr.GetBuffer(0));
		return ID;
	}
}

CString CMyTreeView::GetParentName()
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();	
	HTREEITEM hParentItem;
	HTREEITEM currItem = treeCtrl.GetSelectedItem();
	
  hParentItem = treeCtrl.GetParentItem(currItem);
	CString nodeText = treeCtrl.GetItemText(hParentItem);
	return nodeText;
}


CString CMyTreeView::GetCurrNodeName()
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();	
	HTREEITEM currItem = treeCtrl.GetSelectedItem();
	
	CString nodeText = treeCtrl.GetItemText(currItem);
	return nodeText;
}

DWORD CMyTreeView::GetCurrSceneId()
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();	
	HTREEITEM hParentItem;
	HTREEITEM currItem = treeCtrl.GetSelectedItem();
	
  while((hParentItem = treeCtrl.GetParentItem(currItem)) != NULL)
	{
		CString nodeText = treeCtrl.GetItemText(hParentItem);
		if (nodeText == (CString)SCENE_DEFINITION_STR)
		{
			return DEFAULT_SCENE_ID;
		}
		else
		{
			int indx = nodeText.Find(')',0);
			CString textWithoutID = nodeText.Right(nodeText.GetLength() - indx - 1);
			if (textWithoutID == (CString)SCENE_DEFINITION_STR)
			{
				indx = nodeText.Find(')',0);
				CString IDStr = nodeText.Left(indx);
				IDStr = IDStr.Right(IDStr.GetLength() - 1);
				DWORD ID = atoi(IDStr.GetBuffer(0));
				return ID;			
			}		
		}
		currItem = hParentItem;
	}
	return NOT_FOUND;
}

DWORD CMyTreeView::GetCurrNodeID()
{
	CString nodeText = GetTreeCtrl().GetItemText(GetTreeCtrl().GetSelectedItem());
	int indx = nodeText.Find(')',0);
	CString IDStr = nodeText.Left(indx);
	IDStr = IDStr.Right(IDStr.GetLength() - 1);
	DWORD ID = atoi(IDStr.GetBuffer(0));
	return ID;		
}

void CMyTreeView::GetCurrNodeFileName(CString& fileName)
{
	CString nodeText = GetTreeCtrl().GetItemText(GetTreeCtrl().GetSelectedItem());
	int indx = nodeText.Find(')',0);
	fileName = nodeText.Right(nodeText.GetLength() - indx - 1);
}

void CMyTreeView::AddNode()
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();
  UINT resID = formData.GetCurrentForm();
	HTREEITEM currItem = treeCtrl.GetSelectedItem();
	HTREEITEM parentItem = treeCtrl.GetParentItem(currItem);

	CString newNodeTitle(NEW_STR);
  BOOL isNeedID = TRUE;
	BOOL isNeedFileName = TRUE;
	BOOL isCharContext = FALSE;

	CString filterStr;
	CString defExt;
	CString openFileTitle;

  switch(resID)
	{
		case IDD_WORLD:
			newNodeTitle += WORLD_STR;
			isNeedFileName = FALSE;			
			break;
		case IDD_SCENE_DEFINITION:
			newNodeTitle += SCENE_DEFINITION_STR;						
			isNeedFileName = FALSE;
			break;		
		case IDD_MUSIC_SCRIPT:			
			newNodeTitle += MUSIC_SCRIPT_STR;			
			isNeedFileName = FALSE;
			break;
		case IDD_MUSIC_SAMPLE:			
			newNodeTitle += MUSIC_SAMPLE_STR;

			filterStr	= ("Music sample files (*.ogg)"); 
			filterStr += (TCHAR)NULL;
			filterStr += "*.ogg";
			filterStr += (TCHAR)NULL;

      defExt = "*.ogg";              
			break;
		case IDD_CHARACTER_INFO:	
			newNodeTitle += CHARACTER_INFO_STR;

			filterStr	= ("Video files (*.avi)"); 
			filterStr += (TCHAR)NULL;
			filterStr += "*.avi";
			filterStr += (TCHAR)NULL;
      filterStr += ("Video files (*.cha)");
			filterStr += (TCHAR)NULL;
			filterStr += "*.cha";
			filterStr += (TCHAR)NULL;

      defExt = "*.avi";             

			break;
		case IDD_CAMERA_DEFINITION:			
			newNodeTitle += CAMERA_DEFINITION_STR;
			isNeedFileName = FALSE;
			isNeedID = FALSE;
			break;
		case IDD_SKY_DEFINITION:	
			newNodeTitle += SKY_DEFINITION_STR;

			filterStr	= ("Sky definition files (*.jpg)"); 
			filterStr += (TCHAR)NULL;
			filterStr += "*.jpg";
			filterStr += (TCHAR)NULL;
	    filterStr += ("Sky definition files(*.jpeg)");
			filterStr += (TCHAR)NULL;
			filterStr += "*.jpeg";
			filterStr += (TCHAR)NULL;

      defExt = "*.jpg";             

			break;
		case IDD_ITEM_DEFINITION:
			newNodeTitle += ITEM_DEFINITION_STR;

			filterStr	= ("Icon files (*.ico)"); 
			filterStr += (TCHAR)NULL;
			filterStr += "*.ico";
			filterStr += (TCHAR)NULL;
			
			defExt = "*.ico";              
			
			break;
		case IDD_IMAGE_INFO:			
			newNodeTitle += IMAGE_INFO_STR;

			filterStr	= ("Image files (*.jpeg)"); 
			filterStr += (TCHAR)NULL;
			filterStr += "*.jpeg";
			filterStr += (TCHAR)NULL;
	    filterStr += ("Image files (*.png)");
			filterStr += (TCHAR)NULL;
			filterStr += "*.png";
			filterStr += (TCHAR)NULL;
			
			defExt = "*.jpeg";             
			break;
		case IDD_ANIMATION_INFO:		
			newNodeTitle += ANIMATION_INFO_STR;

			filterStr	= ("Video files (*.avi)"); 
			filterStr += (TCHAR)NULL;
			filterStr += "*.avi";
			filterStr += (TCHAR)NULL;
	    filterStr += ("Video files (*.cha)");
			filterStr += (TCHAR)NULL;
			filterStr += "*.cha";
			filterStr += (TCHAR)NULL;

      defExt = "*.avi";             

			break;
		case IDD_CHARACTER_CONTEXT:
			newNodeTitle += CHARACTER_CONTEXT_STR;
			isNeedFileName = FALSE;
			isNeedID = FALSE;
			isCharContext = TRUE;
			break;
		case IDD_SFX_INFO:
			newNodeTitle += SFX_INFO_STR;

			filterStr	= ("Sound files (*.ogg)"); 
			filterStr += (TCHAR)NULL;
			filterStr += "*.ogg";
			filterStr += (TCHAR)NULL;
			filterStr += ("Sound files (*.wav)");
			filterStr += (TCHAR)NULL;
			filterStr += "*.wav";
			filterStr += (TCHAR)NULL;

      defExt = "*.ogg";             

			break;			
		case IDD_TEXT_DISPLAY:
			newNodeTitle += TEXT_DISPLAY_STR;
			isNeedFileName = FALSE;
			break;
		case IDD_HOT_SPOT_INFO:
			newNodeTitle += HOT_SPOT_INFO_STR;
			isNeedFileName = FALSE;
			break;
		case IDD_KEYBOARD_TRIGGER:		
			newNodeTitle += KEYBOARD_TRIGGER_STR;			
			isNeedFileName = FALSE;
			break;			
	}

	NewNodeDlg newDlg;
	newDlg.m_title = newNodeTitle;
	newDlg.m_isFileNameEnable = isNeedFileName;
	newDlg.m_isIDEnable = isNeedID;
	newDlg.m_isCharContext = isCharContext;
	newDlg.m_openTitle = newNodeTitle; 
	newDlg.m_defExt = defExt;
	newDlg.m_filterStr = filterStr;
	if (resID == IDD_CHARACTER_INFO)
	{
		newDlg.m_isCharInfo = TRUE;		
	}
	else
	{
		newDlg.m_isCharInfo = FALSE;
	}
	int result = newDlg.DoModal();
	if (result == IDOK)
	{
		CString newNodeTitleStr;
		if (!isNeedFileName &&
			  !isNeedID)
		{
			newNodeTitleStr.Format("(%s)%s",newDlg.m_comboVal,formData.GetDisplayName(resID));
		}
		else
		{
			if(isNeedID)
			{
				newNodeTitleStr.Format("(%s)",newDlg.m_ID);
				if(isNeedFileName)
				{
					newNodeTitleStr += newDlg.m_fileName;
				}
				else
				{
					newNodeTitleStr += formData.GetDisplayName(resID);
				}
			}
			else
			{
				if (resID == IDD_WORLD)
				{
					newNodeTitleStr.Format("%s(%s)",WORLD_STR,newDlg.m_fileName);
				}
				else
				{
					newNodeTitleStr = newDlg.m_fileName;
				}		
			}
		}

		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));	
		CWorldConstructKitDoc* doc = STATIC_DOWNCAST(CWorldConstructKitDoc,m_pDocument);

		DWORD id;
    CString	fileName;
  	if (!isNeedFileName && !isNeedID)
		{
			id = _atoi64(newDlg.m_comboVal.GetBuffer(0));
		}
		else
		{
			if (isNeedID)
			{
				id	= _atoi64(newDlg.m_ID.GetBuffer(0));
			}
			if (isNeedFileName)
			{
				fileName = newDlg.m_fileName;
			}
		}
		bool alreadyExist = false;
		switch(resID)
		{
		case IDD_WORLD:
			{
				if (doc->NewWorld(id))
				{
					AddWorldNode(newNodeTitleStr.GetBuffer(0));
				}
				else
				{
					alreadyExist = true;
				}				
			}
			break;
		case IDD_SCENE_DEFINITION:
			{
				if (doc->NewScene(id))
				{
					AddSceneNode(newNodeTitleStr.GetBuffer(0),parentItem);
				}
				else
				{
					alreadyExist = true;
				}				
			}			
			break;		
		case IDD_MUSIC_SCRIPT:			
			{
				if (doc->NewMusicScript(id))
				{
					AddChildNode(newNodeTitleStr.GetBuffer(0),currItem,DYNAMIC_NODE,resID);
				}	
				else
				{
					alreadyExist = true;
				}
			}
			break;
		case IDD_MUSIC_SAMPLE:			
			{
				if (doc->NewMusicFile(id,fileName.GetBuffer(0)))
				{
					AddChildNode(newNodeTitleStr.GetBuffer(0),currItem,DYNAMIC_NODE,resID);
				}
				else
				{
					alreadyExist = true;
				}				
			}
			break;
		case IDD_SKY_DEFINITION:			
			{
				if (doc->NewSky(id,fileName.GetBuffer(0)))
				{
					AddChildNode(newNodeTitleStr.GetBuffer(0),currItem,DYNAMIC_NODE,resID);
				}
				else
				{
					alreadyExist = true;
				}
			}
			break;
		case IDD_IMAGE_INFO:			
			{
				if (doc->NewImageInfo(id,fileName.GetBuffer(0)))
				{
					AddChildNode(newNodeTitleStr.GetBuffer(0),currItem,DYNAMIC_NODE,resID);
				}
				else
				{
					alreadyExist = true;
				}
			}
			break;
		case IDD_ANIMATION_INFO:			
			{
				if (doc->NewAnimationInfo(id,fileName.GetBuffer(0)))
				{
					AddChildNode(newNodeTitleStr.GetBuffer(0),currItem,DYNAMIC_NODE,resID);
				}
				else
				{
					alreadyExist = true;
				}
			}
			break;
    case IDD_SFX_INFO:
			{
				if (doc->NewSFXInfo(id,fileName.GetBuffer(0)))
				{
					AddChildNode(newNodeTitleStr.GetBuffer(0),currItem,DYNAMIC_NODE,resID);
				}
				else
				{
					alreadyExist = true;
				}
			}
			break;
		case IDD_TEXT_DISPLAY:
			{
				if (doc->NewTextDisplay(id))
				{
					AddChildNode(newNodeTitleStr.GetBuffer(0),currItem,DYNAMIC_NODE,resID);
				}
				else
				{
					alreadyExist = true;
				}
			}
			break;
		case IDD_HOT_SPOT_INFO:
			{
				if(doc->NewHotSpot(id))
				{
					AddChildNode(newNodeTitleStr.GetBuffer(0),currItem,DYNAMIC_NODE,resID);
				}
				else
				{
					alreadyExist = true;
				}
			}
			break;
		case IDD_KEYBOARD_TRIGGER:		
			{
				if (doc->NewKeyboard(id))
				{
					AddChildNode(newNodeTitleStr.GetBuffer(0),currItem,DYNAMIC_NODE,resID);
				}
				else
				{
					alreadyExist = true;
				}
			}
			break;
		case IDD_CHARACTER_CONTEXT:		
			{
				if (doc->NewCharacterContext(id))
				{
					AddChildNode(newNodeTitleStr.GetBuffer(0),currItem,DYNAMIC_NODE,resID);
				}
				else
				{
					alreadyExist = true;
				}
			}
			break;
		case IDD_CHARACTER_INFO:	
			{
				if (doc->NewCharacterInfo(id,fileName))
				{
					AddChildNode(newNodeTitleStr.GetBuffer(0),currItem,DYNAMIC_NODE,resID);
				}
				else
				{
					alreadyExist = true;
				}				
			}
			break;
		case IDD_CAMERA_DEFINITION:				
			{
				if (doc->NewCamera(id))
				{
					AddChildNode(newNodeTitleStr.GetBuffer(0),currItem,DYNAMIC_NODE,resID);
				}
				else
				{
					alreadyExist = true;
				}
			}
			break;
		case IDD_ITEM_DEFINITION:			
			{
				if (doc->NewItem(id,fileName))
				{
					AddChildNode(newNodeTitleStr.GetBuffer(0),currItem,DYNAMIC_NODE,resID);
				}
				else
				{
					alreadyExist = true;
				}
			}			
			break;			
		}

		if (alreadyExist)
		{
			MessageBox("Node with this name already exist","Error",MB_OK + MB_ICONINFORMATION);
		}
		else
		{
			CString dynMapStr;
			DWORD worldId = GetCurrWorldID();;
			
			DWORD sceneId = GetCurrSceneId();
			if (sceneId == UNDEFINED_SCENE)
			{
				CString nodeText = GetTreeCtrl().GetItemText(parentItem);
				if (nodeText == SCENES_LIST_STR)
				{
					dynMapStr.Format("%d--%s-%s",worldId,SCENES_LIST_STR,newNodeTitleStr.GetBuffer(0));
				}
				else
				{
					if (resID == IDD_WORLD)
					{
						worldId = id;
						dynMapStr.Format("%d--(%d)%s-%s",worldId,worldId,WORLD_STR,newNodeTitleStr.GetBuffer(0));
					}
					else
					{						
						dynMapStr.Format("%d--%s-%s",worldId,GetCurrNodeName(),newNodeTitleStr.GetBuffer(0));
					}					
				}					
			}
			else
			{
				dynMapStr.Format("%d-%d-%s-%s",worldId,sceneId,GetCurrNodeName(),newNodeTitleStr.GetBuffer(0));
			}

			DynamicNodeData nodeData;
			nodeData.lpszName = strdup(dynMapStr.GetBuffer(0));
			nodeData.resId = resID;
			formData.m_dynamicNodeMap.PushBack(nodeData);
			treeCtrl.Invalidate();
			treeCtrl.Expand(currItem,TVE_EXPAND);
		}
	}
}

void CMyTreeView::AddWorldNodeWithData(LPCTSTR newNodeTitleStr,DWORD key,World& world)
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));	
	CWorldConstructKitDoc* doc = STATIC_DOWNCAST(CWorldConstructKitDoc,m_pDocument);

	AddWorldNode(newNodeTitleStr,FALSE);
	doc->NewWorld(key,world);	

	AddToDymamicMap(newNodeTitleStr,WORLD_STR,IDD_WORLD,key,UNDEFINED_SCENE);
	
	int i;
	HTREEITEM parentItem;
	parentItem = FindWorldChildItem(key,MUSIC_SCRIPT_STR);
	if (parentItem != NULL)
	{
		for (i = 0; i < world.m_bgMusicCount; i++)
		{
			AddExistMusicScriptNode(key,world.m_bgMusicScript[i],parentItem);
		}
	}

	parentItem = FindWorldChildItem(key,MUSIC_SAMPLE_STR);
	if (parentItem != NULL)
	{
		for (i = 0; i < world.m_bgMusicFileCount; i++)
		{
			AddExistMusicSampleNode(key,world.m_bgMusicSample[i],parentItem);
		}
	}

	parentItem = FindWorldChildItem(key,CHARACTER_INFO_STR);
	if (parentItem != NULL)
	{
		for (i = 0; i < world.m_numberOfCharacters; i++)
		{
			AddExistCharacterInfoNode(key,world.m_characters[i],parentItem);
		}
	}

	parentItem = FindWorldChildItem(key,SKY_DEFINITION_STR);
	if (parentItem != NULL)
	{
		for (i = 0; i < world.m_numberOfSkies; i++)
		{
			AddExistSkyNode(key,world.m_skies[i],parentItem);
		}
	}

	parentItem = FindWorldChildItem(key,ITEM_DEFINITION_STR);
	if (parentItem != NULL)
	{
		for (i = 0; i < world.m_inventorySize; i++)
		{
			AddExistInventoryNode(key,world.m_inventory[i],parentItem);
		}
	}

	parentItem = FindWorldChildItem(key,CAMERA_DEFINITION_STR);
	if (parentItem != NULL)
	{
		for (i = 0; i < world.m_cameraCount; i++)
		{
			AddExistCameraNode(key,world.m_camera[i],parentItem);
		}
	}

	for (i = 0; i < world.m_numberOfScenes; i++)
	{
		parentItem = FindSceneListItem(key);
		if (parentItem != NULL)
		{
			AddExistSceneNode(key,world.m_scenes[i],parentItem);
		}

		int j;
		parentItem = FindSceneChildItem(key,world.m_scenes[i].m_sceneID,IMAGE_INFO_STR);
		if (parentItem != NULL)
		{
			for (j = 0; j < world.m_scenes[i].m_imageCount; j++)
			{
				AddExistImage(key,world.m_scenes[i].m_sceneID, world.m_scenes[i].m_images[j],parentItem);
			}
		}
    
		parentItem = FindSceneChildItem(key,world.m_scenes[i].m_sceneID,ANIMATION_INFO_STR);
		if (parentItem != NULL)
		{
			for (j = 0; j < world.m_scenes[i].m_animationCount; j++)
			{
				AddExistAnimation(key,world.m_scenes[i].m_sceneID, world.m_scenes[i].m_animations[j],parentItem);
			}
		}

		parentItem = FindSceneChildItem(key,world.m_scenes[i].m_sceneID,CHARACTER_CONTEXT_STR);
		if (parentItem != NULL)
		{
			for (j = 0; j < world.m_scenes[i].m_characterCount; j++)
			{
				AddExistCharacter(key,world.m_scenes[i].m_sceneID, world.m_scenes[i].m_sceneCharacters[j],parentItem);
			}
		}

		parentItem = FindSceneChildItem(key,world.m_scenes[i].m_sceneID,SFX_INFO_STR);
		if (parentItem != NULL)
		{
			for (j = 0; j < world.m_scenes[i].m_sfxCount; j++)
			{
				AddExistSFX(key,world.m_scenes[i].m_sceneID, world.m_scenes[i].m_sfx[j],parentItem);
			}
		}

		parentItem = FindSceneChildItem(key,world.m_scenes[i].m_sceneID,TEXT_DISPLAY_STR);
		if (parentItem != NULL)
		{
			for (j = 0; j < world.m_scenes[i].m_textOverlayCount; j++)
			{
				AddExistText(key,world.m_scenes[i].m_sceneID, world.m_scenes[i].m_textOverlays[j],parentItem);
			}
		}

		parentItem = FindSceneChildItem(key,world.m_scenes[i].m_sceneID,HOT_SPOT_INFO_STR);
		if (parentItem != NULL)
		{
			for (j = 0; j < world.m_scenes[i].m_clickCount; j++)
			{
				AddExistHotSpot(key,world.m_scenes[i].m_sceneID, world.m_scenes[i].m_clickSpots[j],parentItem);
			}
		}

		parentItem = FindSceneChildItem(key,world.m_scenes[i].m_sceneID,KEYBOARD_TRIGGER_STR);
		if (parentItem != NULL)
		{
			for (j = 0; j < world.m_scenes[i].m_keyCount; j++)
			{
				AddExistKeyboard(key,world.m_scenes[i].m_sceneID, world.m_scenes[i].m_keys[j],parentItem);
			}
		}
	}
}

HTREEITEM CMyTreeView::FindItem(CString itemText)
{
	BOOL isFound = FALSE;
	HTREEITEM item = GetTreeCtrl().GetRootItem();
	HTREEITEM hChildItem;
	CString text; 
	while(item != NULL)
	{
		text = GetTreeCtrl().GetItemText(item);
		if (text == itemText)
		{
			hChildItem = item;
			isFound = TRUE;
			break;
		}		
		else
		{
			if (GetTreeCtrl().ItemHasChildren(item))
			{
				HTREEITEM hNextItem;
				hChildItem = GetTreeCtrl().GetChildItem(item);
				
				while (hChildItem != NULL)
				{
					hNextItem = GetTreeCtrl().GetNextItem(hChildItem, TVGN_NEXT);
					text = GetTreeCtrl().GetItemText(hChildItem);
					if (text == itemText)
					{
						isFound = TRUE;
						break;   
					}						
					else
					{
						hChildItem = hNextItem;
					}					  
				}
			}
			if (isFound)
			{
				break;
			}
			item = GetTreeCtrl().GetNextItem(item,TVGN_NEXT);
		}			
	}
	if (isFound)
	{
		return  hChildItem;
	}
	else
	{
		return NULL;
	}
	return item;
}

HTREEITEM CMyTreeView::FindItemBetweenChildren(HTREEITEM item,CString itemText)
{
	HTREEITEM hChildItem;
	BOOL isFound = FALSE;
	CString text;
	if (GetTreeCtrl().ItemHasChildren(item))
	{
		HTREEITEM hNextItem;
		hChildItem = GetTreeCtrl().GetChildItem(item);
		
		while (hChildItem != NULL)
		{
			hNextItem = GetTreeCtrl().GetNextItem(hChildItem, TVGN_NEXT);
			text = GetTreeCtrl().GetItemText(hChildItem);
			if (text == itemText)
			{
				isFound = TRUE;
				break;   
			}						
			else
			{
				hChildItem = hNextItem;
			}					  
		}
	}

	if (isFound)
	{
		return hChildItem;
	}
	else
	{
		return NULL;
	}
}

HTREEITEM CMyTreeView::FindWorldChildItem(DWORD key,LPCTSTR itemText)
{
	CString worldNodeStr;
	if (key == 0)
	{
		worldNodeStr = WORLD_STR;
	}
	else
	{
		worldNodeStr.Format("(%d)%s",key,WORLD_STR);
	}

	HTREEITEM worldItem;
	HTREEITEM parentItem = NULL;
	worldItem = FindItem(worldNodeStr);
	if (worldItem != NULL)
	{
		parentItem = FindItemBetweenChildren(worldItem,itemText);
	}
	return parentItem;
}

HTREEITEM CMyTreeView::FindSceneListItem(DWORD key)
{
	CString worldNodeStr;
	if (key == 0)
	{
		worldNodeStr = WORLD_STR;
	}
	else
	{
		worldNodeStr.Format("(%d)%s",key,WORLD_STR);
	}

	HTREEITEM worldItem;
	HTREEITEM parentItem = NULL;
	worldItem = FindItem(worldNodeStr);
	if (worldItem != NULL)
	{
		parentItem = FindItemBetweenChildren(worldItem,SCENES_LIST_STR);
	}
	return parentItem;
}

HTREEITEM CMyTreeView::FindSceneChildItem(DWORD key,DWORD sceneId,LPCTSTR itemText)
{
	CString worldNodeStr;
	if (key == 0)
	{
		worldNodeStr = WORLD_STR;
	}
	else
	{
		worldNodeStr.Format("(%d)%s",key,WORLD_STR);
	}
	
	CString scenesStr;
	if (sceneId == 0)
	{
		scenesStr = SCENE_DEFINITION_STR;
	}
	else
	{
		scenesStr.Format("(%d)%s",sceneId,SCENE_DEFINITION_STR);
	}
	
	HTREEITEM worldItem;
	HTREEITEM parentItem = NULL;
	HTREEITEM scenesListItem;
	HTREEITEM sceneItem;
	worldItem = FindItem(worldNodeStr);
	if (worldItem != NULL)
	{
		scenesListItem = FindItemBetweenChildren(worldItem,SCENES_LIST_STR);
		if (scenesListItem != NULL)
		{
			sceneItem = FindItemBetweenChildren(scenesListItem,scenesStr);
			if (sceneItem != NULL)
			{
				parentItem = FindItemBetweenChildren(sceneItem,itemText);
			}			
		}
	}
	return parentItem;
}

void CMyTreeView::AddToDymamicMap(CString nodeTitle,CString nodeStr,UINT resId,DWORD worldId,DWORD sceneId)
{
	CString dynMapStr;
	if (resId == IDD_SCENE_DEFINITION)
	{
		dynMapStr.Format("%d--%s-%s",worldId,SCENES_LIST_STR,nodeTitle.GetBuffer(0));
	}
	else
	{
		if (sceneId == UNDEFINED_SCENE)
		{
			if (resId == IDD_WORLD)
			{
				dynMapStr.Format("%d--(%d)%s-%s",worldId,worldId,WORLD_STR,nodeTitle.GetBuffer(0));
			}
			else
			{			
				dynMapStr.Format("%d--%s-%s",worldId,nodeStr,nodeTitle.GetBuffer(0));
			}
		}
		else
		{
			dynMapStr.Format("%d-%d-%s-%s",worldId,sceneId,sceneDefinitionNodes[resId - IDD_STAGING_INFO].lpszName,nodeTitle.GetBuffer(0));
		}
	}
	
	DynamicNodeData nodeData;
	nodeData.lpszName = strdup(dynMapStr.GetBuffer(0));
	nodeData.resId = resId;
	formData.m_dynamicNodeMap.PushBack(nodeData);
}

void CMyTreeView::AddExistMusicScriptNode(DWORD key,MusicScript& musicScript,HTREEITEM parentItem)
{
	CString newNodeTitleStr;
	newNodeTitleStr.Format("(%d)%s",musicScript.m_scriptID,MUSIC_SCRIPT_STR);

	AddToDymamicMap(newNodeTitleStr,MUSIC_SCRIPT_STR, IDD_MUSIC_SCRIPT,key,UNDEFINED_SCENE);
	
	AddChildNode(newNodeTitleStr.GetBuffer(0),parentItem,DYNAMIC_NODE,IDD_MUSIC_SCRIPT);
}

void CMyTreeView::AddExistMusicSampleNode(DWORD key,MusicSample& musicSample,HTREEITEM parentItem)
{
	CString newNodeTitleStr;
	newNodeTitleStr.Format("(%d)%s",musicSample.m_sampleID,musicSample.m_fileName.operator PCTSTR());

	AddToDymamicMap(newNodeTitleStr,MUSIC_SAMPLE_STR,IDD_MUSIC_SAMPLE,key,UNDEFINED_SCENE);

	AddChildNode(newNodeTitleStr.GetBuffer(0),parentItem,DYNAMIC_NODE,IDD_MUSIC_SAMPLE);
}

void CMyTreeView::AddExistCharacterInfoNode(DWORD key,CharacterInfo& characterInfo,HTREEITEM parentItem)
{
	CString newNodeTitleStr;
	newNodeTitleStr.Format("(%d)%s",characterInfo.m_characterId,characterInfo.m_characterName.operator PCTSTR());

	AddToDymamicMap(newNodeTitleStr,CHARACTER_INFO_STR,IDD_CHARACTER_INFO,key,UNDEFINED_SCENE);

	AddChildNode(newNodeTitleStr.GetBuffer(0),parentItem,DYNAMIC_NODE,IDD_CHARACTER_INFO);
}

void CMyTreeView::AddExistSkyNode(DWORD key,SkyDefinition& skyDefinition,HTREEITEM parentItem)
{
	CString newNodeTitleStr;
	newNodeTitleStr.Format("(%d)%s",skyDefinition.m_skyID,skyDefinition.m_fileName.operator PCTSTR());

	AddToDymamicMap(newNodeTitleStr,SKY_DEFINITION_STR,IDD_SKY_DEFINITION,key,UNDEFINED_SCENE);

	AddChildNode(newNodeTitleStr.GetBuffer(0),parentItem,DYNAMIC_NODE,IDD_SKY_DEFINITION);
}

void CMyTreeView::AddExistInventoryNode(DWORD key,ItemDefinition& inventory,HTREEITEM parentItem)
{
	CString newNodeTitleStr;
	newNodeTitleStr.Format("(%d)%s",inventory.m_itemID,inventory.m_iconFileName.operator PCTSTR());

	AddToDymamicMap(newNodeTitleStr,ITEM_DEFINITION_STR,IDD_ITEM_DEFINITION,key,UNDEFINED_SCENE);

	AddChildNode(newNodeTitleStr.GetBuffer(0),parentItem,DYNAMIC_NODE,IDD_ITEM_DEFINITION);
}

void CMyTreeView::AddExistCameraNode(DWORD key,CameraDefinition& cameraDef,HTREEITEM parentItem)
{
	CString newNodeTitleStr;
	newNodeTitleStr.Format("(%d)%s",cameraDef.m_sceneID,CAMERA_DEFINITION_STR);

	AddToDymamicMap(newNodeTitleStr,CAMERA_DEFINITION_STR,IDD_CAMERA_DEFINITION,key,UNDEFINED_SCENE);

	AddChildNode(newNodeTitleStr.GetBuffer(0),parentItem,DYNAMIC_NODE,IDD_CAMERA_DEFINITION);
}

void CMyTreeView::AddExistSceneNode(DWORD key,SceneDefinition& sceneDef,HTREEITEM parentItem)
{
	CString newNodeTitleStr;
	if (sceneDef.m_sceneID != 0)
	{
		newNodeTitleStr.Format("(%d)%s",sceneDef.m_sceneID,SCENE_DEFINITION_STR);
	}
	else
	{
		newNodeTitleStr.Format("%s",SCENE_DEFINITION_STR);
	}
	AddToDymamicMap(newNodeTitleStr,SCENE_DEFINITION_STR,IDD_SCENE_DEFINITION,key,sceneDef.m_sceneID);
	AddSceneNode(newNodeTitleStr,parentItem);					
}


void CMyTreeView::AddExistImage(DWORD key,DWORD sceneId,ImageInfo& image,HTREEITEM parentItem)
{
	CString newNodeTitleStr;
	newNodeTitleStr.Format("(%d)%s",image.m_imageID,image.m_fileName.operator PCTSTR());

	AddToDymamicMap(newNodeTitleStr,IMAGE_INFO_STR,IDD_IMAGE_INFO,key,sceneId);

	AddChildNode(newNodeTitleStr.GetBuffer(0),parentItem,DYNAMIC_NODE,IDD_IMAGE_INFO);
}

void CMyTreeView::AddExistAnimation(DWORD key,DWORD sceneId,AnimationInfo& animation,HTREEITEM parentItem)
{
	CString newNodeTitleStr;
	newNodeTitleStr.Format("(%d)%s",animation.m_animationID,animation.m_fileNameVideo.operator PCTSTR());

	AddToDymamicMap(newNodeTitleStr,ANIMATION_INFO_STR,IDD_ANIMATION_INFO,key,sceneId);

	AddChildNode(newNodeTitleStr.GetBuffer(0),parentItem,DYNAMIC_NODE,IDD_ANIMATION_INFO);				
}

void CMyTreeView::AddExistCharacter(DWORD key,DWORD sceneId,CharacterContext& context,HTREEITEM parentItem)
{
	CString newNodeTitleStr;
	newNodeTitleStr.Format("(%d)%s",context.m_characterId,CHARACTER_CONTEXT_STR);

	AddToDymamicMap(newNodeTitleStr,CHARACTER_CONTEXT_STR,IDD_CHARACTER_CONTEXT,key,sceneId);

	AddChildNode(newNodeTitleStr.GetBuffer(0),parentItem,DYNAMIC_NODE,IDD_CHARACTER_CONTEXT);
}

void CMyTreeView::AddExistSFX(DWORD key,DWORD sceneId,SFXInfo& sfx,HTREEITEM parentItem)
{
	CString newNodeTitleStr;
	newNodeTitleStr.Format("(%d)%s",sfx.m_sfxID,sfx.m_fileName.operator PCTSTR());

	AddToDymamicMap(newNodeTitleStr,SFX_INFO_STR,IDD_SFX_INFO,key,sceneId);

	AddChildNode(newNodeTitleStr.GetBuffer(0),parentItem,DYNAMIC_NODE,IDD_SFX_INFO);
}

void CMyTreeView::AddExistText(DWORD key,DWORD sceneId, TextDisplay& textDisp,HTREEITEM parentItem)
{
	CString newNodeTitleStr;
	newNodeTitleStr.Format("(%d)%s",textDisp.m_textID,TEXT_DISPLAY_STR);

	AddToDymamicMap(newNodeTitleStr,TEXT_DISPLAY_STR,IDD_TEXT_DISPLAY,key,sceneId);

  AddChildNode(newNodeTitleStr.GetBuffer(0),parentItem,DYNAMIC_NODE,IDD_TEXT_DISPLAY);
}

void CMyTreeView::AddExistHotSpot(DWORD key,DWORD sceneId,HotspotInfo& hotSpot,HTREEITEM parentItem)
{
	CString newNodeTitleStr;
	newNodeTitleStr.Format("(%d)%s",hotSpot.m_hotSpotID,HOT_SPOT_INFO_STR);

	AddToDymamicMap(newNodeTitleStr,HOT_SPOT_INFO_STR,IDD_HOT_SPOT_INFO,key,sceneId);

	AddChildNode(newNodeTitleStr.GetBuffer(0),parentItem,DYNAMIC_NODE,IDD_HOT_SPOT_INFO);
}

void CMyTreeView::AddExistKeyboard(DWORD key,DWORD sceneId, KeyboardTrigger& keyboard,HTREEITEM parentItem)
{
	CString newNodeTitleStr;
	newNodeTitleStr.Format("(%d)%s",keyboard.m_keyID,KEYBOARD_TRIGGER_STR);

	AddToDymamicMap(newNodeTitleStr,KEYBOARD_TRIGGER_STR,IDD_KEYBOARD_TRIGGER,key,sceneId);

	AddChildNode(newNodeTitleStr.GetBuffer(0),parentItem,DYNAMIC_NODE,IDD_KEYBOARD_TRIGGER);				
}

void CMyTreeView::AddWorldNode(LPCTSTR newNodeTitleStr,BOOL isNeedScene)
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	
	HTREEITEM worldItem;
	worldItem = treeCtrl.InsertItem(newNodeTitleStr, TEMPLATE_DYNAMIC_NODE,TEMPLATE_DYNAMIC_NODE);
	treeCtrl.SetItemData(worldItem,TEMPLATE_NODE);
	AddChildNode(NULL,worldItem,TEMPLATE_NODE,IDD_MUSIC_SCRIPT);
	AddChildNode(NULL,worldItem,TEMPLATE_NODE,IDD_MUSIC_SAMPLE);
  AddChildNode(NULL,worldItem,TEMPLATE_NODE,IDD_CHARACTER_INFO);

	HTREEITEM sceneListItem;			
	sceneListItem = treeCtrl.InsertItem(SCENES_LIST_STR , LIST_NODE,LIST_NODE,worldItem);
	treeCtrl.SetItemData(sceneListItem,UNDEFINED_NODE);	
	if (isNeedScene)
	{
		AddSceneNode(NULL,sceneListItem);
	}	
	
  AddChildNode(NULL,worldItem,TEMPLATE_NODE,IDD_SKY_DEFINITION);
  AddChildNode(NULL,worldItem,TEMPLATE_NODE,IDD_ITEM_DEFINITION);
  AddChildNode(NULL,worldItem,TEMPLATE_NODE,IDD_CAMERA_DEFINITION);
}

void CMyTreeView::AddSceneNode(LPCTSTR newNodeTitleStr,HTREEITEM sceneListItem)
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();

	HTREEITEM sceneItem;

	sceneItem = treeCtrl.InsertItem(
		newNodeTitleStr == NULL ? formData.GetDisplayName(IDD_SCENE_DEFINITION) : newNodeTitleStr,
		TEMPLATE_DYNAMIC_NODE,TEMPLATE_DYNAMIC_NODE,sceneListItem);
	treeCtrl.SetItemData(sceneItem,TEMPLATE_NODE);
	AddChildNode(NULL,sceneItem,TEMPLATE_NODE,IDD_STAGING_INFO);
	AddChildNode(NULL,sceneItem,TEMPLATE_NODE,IDD_IMAGE_INFO);
	AddChildNode(NULL,sceneItem,TEMPLATE_NODE,IDD_ANIMATION_INFO);
	AddChildNode(NULL,sceneItem,TEMPLATE_NODE,IDD_CHARACTER_CONTEXT);
	AddChildNode(NULL,sceneItem,TEMPLATE_NODE,IDD_SFX_INFO);
	AddChildNode(NULL,sceneItem,TEMPLATE_NODE,IDD_TEXT_DISPLAY);
	AddChildNode(NULL,sceneItem,TEMPLATE_NODE,IDD_HOT_SPOT_INFO);
	AddChildNode(NULL,sceneItem,TEMPLATE_NODE,IDD_KEYBOARD_TRIGGER);
}

void CMyTreeView::AddChildNode(LPCTSTR newNodeTitleStr,HTREEITEM parentItem,NodeType nodeType, UINT resID)
{
	HTREEITEM hItem;
	switch(resID)
	{
	case IDD_STAGING_INFO:
		hItem = GetTreeCtrl().InsertItem(
			nodeType == TEMPLATE_NODE ? formData.GetDisplayName(resID) : newNodeTitleStr,
			CHILD_TREE_NODE,
			CHILD_TREE_NODE,
			parentItem);
		break;
	default:	
		hItem = GetTreeCtrl().InsertItem(
			nodeType == TEMPLATE_NODE ? formData.GetDisplayName(resID) : newNodeTitleStr,
			nodeType == TEMPLATE_NODE ? CLOSE_TREE_NODE : CHILD_TREE_NODE,
			nodeType == TEMPLATE_NODE ? OPEN_TREE_NODE : CHILD_TREE_NODE,
			parentItem);
	}
	GetTreeCtrl().SetItemData(hItem,nodeType);
}


void CMyTreeView::SaveNode()
{
	CFormView* currFormPtr = STATIC_DOWNCAST(CFormView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,1));
	currFormPtr->SendMessage(RUNTIME_SAVE_MESSAGE,0,0);
}

void CMyTreeView::DeleteNode()
{
	m_pSplitterWnd->ChangeView(0, 1,RUNTIME_CLASS(TemplateFormView));		

	CTreeCtrl& treeCtrl = GetTreeCtrl();
  UINT resID = formData.GetCurrentForm();
	HTREEITEM currItem = treeCtrl.GetSelectedItem();

	DWORD worldId = GetCurrWorldID();
  World tempWorld;

	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));	
	CWorldConstructKitDoc* doc = STATIC_DOWNCAST(CWorldConstructKitDoc,m_pDocument);

  doc->m_worldMap.Lookup(worldId,tempWorld);

	DWORD id;
	DWORD sceneId;
	CString fileName;

  switch(resID)
	{
		case IDD_WORLD:
			{
				doc->m_worldMap.RemoveKey(worldId);
				treeCtrl.DeleteItem(currItem);
			}
			break;
		case IDD_SCENE_DEFINITION:
			{
				id = GetCurrNodeID();
				if (tempWorld.m_numberOfScenes == 1)
				{
					MessageBox("Can't delete last Scene Definition","Error",MB_OK + MB_ICONWARNING);
				}
				else
				{
					for (int i = 0; i < tempWorld.m_numberOfScenes; i++)
					{
						if (tempWorld.m_scenes[i].m_sceneID == id)
						{
							tempWorld.m_scenes.RemoveByIndex(i);
							tempWorld.m_numberOfScenes--;

							treeCtrl.DeleteItem(currItem);
							break;
						}
					}
					doc->m_worldMap.SetAt(worldId,tempWorld);
				}
			}
			break;		
		case IDD_MUSIC_SCRIPT:			
			{
				id = GetCurrNodeID();
				for (int i = 0; i < tempWorld.m_bgMusicCount; i++)
				{
					if (tempWorld.m_bgMusicScript[i].m_scriptID == id)
					{
						tempWorld.m_bgMusicScript.RemoveByIndex(i);
						tempWorld.m_bgMusicCount--;
						
						treeCtrl.DeleteItem(currItem);
						break;
					}
				}
				doc->m_worldMap.SetAt(worldId,tempWorld);
			}
			break;
		case IDD_MUSIC_SAMPLE:	
			{
				id = GetCurrNodeID();
				GetCurrNodeFileName(fileName);
				for (int i = 0; i < tempWorld.m_bgMusicFileCount; i++)
				{
					if (tempWorld.m_bgMusicSample[i].m_sampleID == id &&
						  tempWorld.m_bgMusicSample[i].m_fileName == (CStdString)fileName)
					{
						tempWorld.m_bgMusicSample.RemoveByIndex(i);
						tempWorld.m_bgMusicFileCount--;
						
						treeCtrl.DeleteItem(currItem);
						break;
					}
				}
				doc->m_worldMap.SetAt(worldId,tempWorld);
			}
			break;
		case IDD_CHARACTER_INFO:	
			{
				id = GetCurrNodeID();
				GetCurrNodeFileName(fileName);
				for (int i = 0; i < tempWorld.m_numberOfCharacters; i++)
				{
					if (tempWorld.m_characters[i].m_characterName == (CStdString)fileName &&
						  tempWorld.m_characters[i].m_characterId == id)
					{
						tempWorld.m_characters.RemoveByIndex(i);
						tempWorld.m_numberOfCharacters--;
						
						treeCtrl.DeleteItem(currItem);
						break;
					}
				}
				doc->m_worldMap.SetAt(worldId,tempWorld);
			}
			break;
		case IDD_CAMERA_DEFINITION:			
			{
				id = GetCurrNodeID();
				for (int i = 0; i < tempWorld.m_cameraCount; i++)
				{
					if (tempWorld.m_camera[i].m_sceneID == id)
					{
						tempWorld.m_camera.RemoveByIndex(i);
						tempWorld.m_cameraCount--;
						
						treeCtrl.DeleteItem(currItem);
						break;
					}
				}
				doc->m_worldMap.SetAt(worldId,tempWorld);
			}
			break;
		case IDD_SKY_DEFINITION:	
			{
				id = GetCurrNodeID();
  			GetCurrNodeFileName(fileName);
				for (int i = 0; i < tempWorld.m_numberOfSkies; i++)
				{
					if (tempWorld.m_skies[i].m_skyID == id &&
						  tempWorld.m_skies[i].m_fileName == (CStdString)fileName)
					{
						tempWorld.m_skies.RemoveByIndex(i);
						tempWorld.m_numberOfSkies--;
						
						treeCtrl.DeleteItem(currItem);
						break;
					}
				}
				doc->m_worldMap.SetAt(worldId,tempWorld);
			}
			break;
		case IDD_ITEM_DEFINITION:
			{
				id = GetCurrNodeID();
				GetCurrNodeFileName(fileName);
				for (int i = 0; i < tempWorld.m_inventorySize; i++)
				{
					if (tempWorld.m_inventory[i].m_itemID == id &&
						  tempWorld.m_inventory[i].m_iconFileName == (CStdString)fileName)
					{
						tempWorld.m_inventory.RemoveByIndex(i);
						tempWorld.m_inventorySize--;
						
						treeCtrl.DeleteItem(currItem);
						break;
					}
				}
				doc->m_worldMap.SetAt(worldId,tempWorld);
			}
			break;
		case IDD_IMAGE_INFO:			
			{
				sceneId = GetCurrSceneId();
				id = GetCurrNodeID();
				GetCurrNodeFileName(fileName);

				for (int i = 0; i < tempWorld.m_numberOfScenes; i++)
				{
					if (tempWorld.m_scenes[i].m_sceneID == sceneId)
					{
						for (int j = 0; j < tempWorld.m_scenes[i].m_imageCount; j++)
						{
							if (tempWorld.m_scenes[i].m_images[j].m_imageID  == id &&
								  tempWorld.m_scenes[i].m_images[j].m_fileName == (CStdString)fileName)
							{
								tempWorld.m_scenes[i].m_images.RemoveByIndex(j);
								tempWorld.m_scenes[i].m_imageCount--;
								
								treeCtrl.DeleteItem(currItem);
								break;
							}							
						}						
					}					
				}
				doc->m_worldMap.SetAt(worldId,tempWorld);
			}
			break;
		case IDD_ANIMATION_INFO:		
			{
				sceneId = GetCurrSceneId();
				id = GetCurrNodeID();
				GetCurrNodeFileName(fileName);

				for (int i = 0; i < tempWorld.m_numberOfScenes; i++)
				{
					if (tempWorld.m_scenes[i].m_sceneID == sceneId)
					{
						for (int j = 0; j < tempWorld.m_scenes[i].m_animationCount; j++)
						{
							if (tempWorld.m_scenes[i].m_animations[j].m_animationID  == id &&
								  tempWorld.m_scenes[i].m_animations[j].m_fileNameVideo == (CStdString)fileName)
							{
								tempWorld.m_scenes[i].m_animations.RemoveByIndex(j);
								tempWorld.m_scenes[i].m_animationCount--;
								
								treeCtrl.DeleteItem(currItem);
								break;
							}							
						}						
					}					
				}
				doc->m_worldMap.SetAt(worldId,tempWorld);

			}
			break;
		case IDD_CHARACTER_CONTEXT:
			{
				sceneId = GetCurrSceneId();
				id = GetCurrNodeID();

				for (int i = 0; i < tempWorld.m_numberOfScenes; i++)
				{
					if (tempWorld.m_scenes[i].m_sceneID == sceneId)
					{
						for (int j = 0; j < tempWorld.m_scenes[i].m_characterCount; j++)
						{
							if (tempWorld.m_scenes[i].m_sceneCharacters[j].m_characterId  == id)
							{
								tempWorld.m_scenes[i].m_sceneCharacters.RemoveByIndex(j);
								tempWorld.m_scenes[i].m_characterCount--;
								
								treeCtrl.DeleteItem(currItem);
								break;
							}							
						}						
					}					
				}
				doc->m_worldMap.SetAt(worldId,tempWorld);
			}
			break;
		case IDD_SFX_INFO:
			{
				sceneId = GetCurrSceneId();
				id = GetCurrNodeID();
				GetCurrNodeFileName(fileName);

				for (int i = 0; i < tempWorld.m_numberOfScenes; i++)
				{
					if (tempWorld.m_scenes[i].m_sceneID == sceneId)
					{
						for (int j = 0; j < tempWorld.m_scenes[i].m_sfxCount; j++)
						{
							if (tempWorld.m_scenes[i].m_sfx[j].m_sfxID  == id &&
								  tempWorld.m_scenes[i].m_sfx[j].m_fileName == (CStdString)fileName)
							{
								tempWorld.m_scenes[i].m_sfx.RemoveByIndex(j);
								tempWorld.m_scenes[i].m_sfxCount--;
								
								treeCtrl.DeleteItem(currItem);
								break;
							}							
						}						
					}					
				}
				doc->m_worldMap.SetAt(worldId,tempWorld);
			}
			break;			
		case IDD_TEXT_DISPLAY:
			{
				sceneId = GetCurrSceneId();
				id = GetCurrNodeID();

				for (int i = 0; i < tempWorld.m_numberOfScenes; i++)
				{
					if (tempWorld.m_scenes[i].m_sceneID == sceneId)
					{
						for (int j = 0; j < tempWorld.m_scenes[i].m_textOverlayCount; j++)
						{
							if (tempWorld.m_scenes[i].m_textOverlays[j].m_textID  == id)
							{
								tempWorld.m_scenes[i].m_textOverlays.RemoveByIndex(j);
								tempWorld.m_scenes[i].m_textOverlayCount--;
								
								treeCtrl.DeleteItem(currItem);
								break;
							}							
						}						
					}					
				}
				doc->m_worldMap.SetAt(worldId,tempWorld);

			}
			break;
		case IDD_HOT_SPOT_INFO:
			{
				sceneId = GetCurrSceneId();
				id = GetCurrNodeID();

				for (int i = 0; i < tempWorld.m_numberOfScenes; i++)
				{
					if (tempWorld.m_scenes[i].m_sceneID == sceneId)
					{
						for (int j = 0; j < tempWorld.m_scenes[i].m_clickCount; j++)
						{
							if (tempWorld.m_scenes[i].m_clickSpots[j].m_hotSpotID == id)
							{
								tempWorld.m_scenes[i].m_clickSpots.RemoveByIndex(j);
								tempWorld.m_scenes[i].m_clickCount--;
								
								treeCtrl.DeleteItem(currItem);
								break;
							}							
						}						
					}					
				}
				doc->m_worldMap.SetAt(worldId,tempWorld);
			}
			break;
		case IDD_KEYBOARD_TRIGGER:		
			{
				sceneId = GetCurrSceneId();
				id = GetCurrNodeID();

				for (int i = 0; i < tempWorld.m_numberOfScenes; i++)
				{
					if (tempWorld.m_scenes[i].m_sceneID == sceneId)
					{
						for (int j = 0; j < tempWorld.m_scenes[i].m_keyCount; j++)
						{
							if (tempWorld.m_scenes[i].m_keys[j].m_keyID == id)
							{
								tempWorld.m_scenes[i].m_keys.RemoveByIndex(j);
								tempWorld.m_scenes[i].m_keyCount--;
								
								treeCtrl.DeleteItem(currItem);
								break;
							}							
						}						
					}					
				}
				doc->m_worldMap.SetAt(worldId,tempWorld);

			}
			break;			
	}

	CFormView* currFormPtr = STATIC_DOWNCAST(CFormView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,1));
	currFormPtr->SendMessage(UPDATE_DELETING_IN_WORLD,0,0);

	((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.ChangeView(0, 1,RUNTIME_CLASS(TemplateFormView));		

}

NodeType CMyTreeView::IsGetNodeType()
{
  HTREEITEM hItem = GetTreeCtrl().GetSelectedItem();
	if (hItem)
	{
		NodeType nodeType = (NodeType)GetTreeCtrl().GetItemData(hItem);
    return nodeType;
	}
	else
	{
		return UNDEFINED_NODE;
	}	
}

void CMyTreeView::OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult) 
{

	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	CFormView* currFormPtr = STATIC_DOWNCAST(CFormView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,1));
	currFormPtr->SendMessage(UPDATE_WORLD_OBJECT,0,0);
	
	*pResult = 0;
}

void CMyTreeView::OnChangeSceneId(WPARAM wParam,LPARAM lParam)
{
  HTREEITEM hItem = GetTreeCtrl().GetSelectedItem();
	CString itemText;
	itemText.Format("(%d)%s",wParam,CAMERA_DEFINITION_STR);
	GetTreeCtrl().SetItemText(hItem,itemText);	
}
