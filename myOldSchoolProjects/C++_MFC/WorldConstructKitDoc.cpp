// WorldConstructKitDoc.cpp : implementation of the CWorldConstructKitDoc class
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "forms.h"
#include "WorldConstructKitDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorldConstructKitDoc

IMPLEMENT_DYNCREATE(CWorldConstructKitDoc, CDocument)

BEGIN_MESSAGE_MAP(CWorldConstructKitDoc, CDocument)
	//{{AFX_MSG_MAP(CWorldConstructKitDoc)
	ON_COMMAND(ID_NEW, OnNew)
	ON_COMMAND(ID_SAVE, OnSave)
	ON_COMMAND(ID_DELETE, OnDelete)
	ON_UPDATE_COMMAND_UI(ID_NEW, OnUpdateNew)
	ON_UPDATE_COMMAND_UI(ID_DELETE, OnUpdateDelete)
	ON_COMMAND(ID_GET_DATA_FROM_DB, OnGetDataFromDb)
	ON_COMMAND(ID_ADD_WORLD, OnAddWorld)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorldConstructKitDoc construction/destruction

CWorldConstructKitDoc::CWorldConstructKitDoc()
{
	// TODO: add one-time construction code here

}

CWorldConstructKitDoc::~CWorldConstructKitDoc()
{
	 m_worldMap.RemoveAll();
}

BOOL CWorldConstructKitDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	if (m_worldMap.GetCount() == 0)
	{
		NewWorld(DEFAULT_WORLD_ID);
	}	
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWorldConstructKitDoc serialization

void CWorldConstructKitDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWorldConstructKitDoc diagnostics

#ifdef _DEBUG
void CWorldConstructKitDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWorldConstructKitDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

bool CWorldConstructKitDoc::NewWorld(DWORD id)
{
	World worldItem;

	SceneDefinition newScene(DEFAULT_SCENE_ID);
	worldItem.m_scenes.PushBack(newScene);
	worldItem.m_numberOfScenes++;	

	World tempWorld;
	if(m_worldMap.Lookup(id,tempWorld))
	{
		return false;
	}
	else
	{
		m_worldMap.SetAt(id,worldItem);	
		SetModifiedFlag();  // Mark the document as having been modified						   	
		return true;
	}	
}

void CWorldConstructKitDoc::NewWorld(DWORD key,World& world)
{
	World worldItem;

	worldItem = world;

	m_worldMap.SetAt(key,worldItem);

	SetModifiedFlag();  // Mark the document as having been modified						   	
}

bool CWorldConstructKitDoc::NewMusicScript(DWORD id)
{
	World worldItem;
	DWORD worldID = m_pTreeView->GetCurrWorldID();
	m_worldMap.Lookup(worldID,worldItem);
	MusicScript newMusicScript(id);
	bool isExist = false;
	for (int i = 0; i < worldItem.m_bgMusicCount; i++)
	{
		if (newMusicScript.m_scriptID == worldItem.m_bgMusicScript[i].m_scriptID)
		{
			isExist = true;
			break;
		}
	}
	if (!isExist)
	{
		worldItem.m_bgMusicScript.PushBack(newMusicScript);
		worldItem.m_bgMusicCount++;
		m_worldMap.SetAt(worldID,worldItem);
		return true;
	}
	else
	{
		return false;
	}	
}

bool CWorldConstructKitDoc::NewMusicFile(DWORD id,LPCTSTR fileName)
{
	World worldItem;
	DWORD worldID = m_pTreeView->GetCurrWorldID();
	m_worldMap.Lookup(worldID,worldItem);
	MusicSample newMusicSample(id,fileName);

	bool isExist = false;
	for (int i = 0; i < worldItem.m_bgMusicFileCount; i++)
	{
		if (newMusicSample.m_sampleID == worldItem.m_bgMusicSample[i].m_sampleID &&
			  newMusicSample.m_fileName == worldItem.m_bgMusicSample[i].m_fileName)
		{
			isExist = true;
			break;
		}
	}
	if (!isExist)
	{
		worldItem.m_bgMusicSample.PushBack(newMusicSample);
		worldItem.m_bgMusicFileCount++;	
		m_worldMap.SetAt(worldID,worldItem);
		return true;
	}
	else
	{
		return false;
	}
}

bool CWorldConstructKitDoc::NewSky(DWORD id,LPCTSTR fileName)
{
	World worldItem;
	DWORD worldID = m_pTreeView->GetCurrWorldID();
	m_worldMap.Lookup(worldID,worldItem);
	SkyDefinition newSky(id,fileName);

	bool isExist = false;
	for (int i = 0; i < worldItem.m_numberOfSkies; i++)
	{
		if (newSky.m_skyID == worldItem.m_skies[i].m_skyID &&
			  newSky.m_fileName == worldItem.m_skies[i].m_fileName)
		{
			isExist = true;
			break;
		}
	}
	if (!isExist)
	{
		worldItem.m_skies.PushBack(newSky);
		worldItem.m_numberOfSkies++;	
		m_worldMap.SetAt(worldID,worldItem);
		return true;
	}
	else
	{
		return false;
	}
}

bool CWorldConstructKitDoc::NewCamera(DWORD id)
{
	World worldItem;
	DWORD worldID = m_pTreeView->GetCurrWorldID();
	m_worldMap.Lookup(worldID,worldItem);
	CameraDefinition newCamera(id);
	bool isExist = false;
	for (int i = 0; i < worldItem.m_cameraCount; i++)
	{
		if (newCamera.m_sceneID == worldItem.m_camera[i].m_sceneID)
		{
			isExist = true;
			break;
		}
	}
	if (!isExist)
	{
		worldItem.m_camera.PushBack(newCamera);
		worldItem.m_cameraCount++;	
		m_worldMap.SetAt(worldID,worldItem);
		return true;
	}
	else
	{
		return false;
	}
}

bool CWorldConstructKitDoc::NewItem(DWORD id,LPCTSTR fileName)
{
	World worldItem;
	DWORD worldID = m_pTreeView->GetCurrWorldID();
	m_worldMap.Lookup(worldID,worldItem);
	ItemDefinition newItem(id,fileName);
	bool isExist = false;
	for (int i = 0; i < worldItem.m_inventorySize; i++)
	{
		if (newItem.m_itemID == worldItem.m_inventory[i].m_itemID &&
			  newItem.m_iconFileName == worldItem.m_inventory[i].m_iconFileName)
		{
			isExist = true;
			break;
		}
	}
	if (!isExist)
	{
		worldItem.m_inventory.PushBack(newItem);
		worldItem.m_inventorySize++;	
		m_worldMap.SetAt(worldID,worldItem);
		return true;
	}
	else
	{
		return false;
	}
}

bool CWorldConstructKitDoc::NewCharacterInfo(short characterId,LPCTSTR characterName)
{
	World worldItem;
	DWORD worldID = m_pTreeView->GetCurrWorldID();
	m_worldMap.Lookup(worldID,worldItem);
	CharacterInfo newCharacterInfo(characterId,characterName);
	bool isExist = false;
	for (int i = 0; i < worldItem.m_numberOfCharacters; i++)
	{
		if (newCharacterInfo.m_characterName == worldItem.m_characters[i].m_characterName &&
			  newCharacterInfo.m_characterId == worldItem.m_characters[i].m_characterId)
		{
			isExist = true;
			break;
		}
	}
	if (!isExist)
	{
		worldItem.m_characters.PushBack(newCharacterInfo);
		worldItem.m_numberOfCharacters++;	
		m_worldMap.SetAt(worldID,worldItem);
		return true;
	}
	else
	{
		return false;
	}
}

bool CWorldConstructKitDoc::NewScene(DWORD id)
{
	World worldItem;
	DWORD worldID = m_pTreeView->GetCurrWorldID();
	m_worldMap.Lookup(worldID,worldItem);
	SceneDefinition newScene(id);
	bool isExist = false;
	for (int i = 0; i < worldItem.m_numberOfScenes; i++)
	{
		if (newScene.m_sceneID == worldItem.m_scenes[i].m_sceneID)
		{
			isExist = true;
			break;
		}
	}
	if (!isExist)
	{
		worldItem.m_scenes.PushBack(newScene);
		worldItem.m_numberOfScenes++;	
		m_worldMap.SetAt(worldID,worldItem);
		return true;
	}
	else
	{
		return false;
	}
}

bool CWorldConstructKitDoc::NewImageInfo(DWORD id,LPCTSTR fileName)
{
	World worldItem;
	DWORD worldID = m_pTreeView->GetCurrWorldID();
	m_worldMap.Lookup(worldID,worldItem);
	DWORD sceneID = m_pTreeView->GetCurrSceneId();
  for (int i = 0 ; i < worldItem.m_numberOfScenes; i++)
	{
		if (worldItem.m_scenes[i].m_sceneID == sceneID)
		{
			ImageInfo  newImage(id,fileName);

			bool isExist = false;
			for (int j = 0; j < worldItem.m_scenes[i].m_imageCount; j++)
			{
				if (newImage.m_imageID == worldItem.m_scenes[i].m_images[j].m_imageID &&
					  newImage.m_fileName == worldItem.m_scenes[i].m_images[j].m_fileName)
				{
					isExist = true;
					break;
				}
			}
			if (!isExist)
			{				
				SceneDefinition* sceneDefPtr = &worldItem.m_scenes[i];
				sceneDefPtr->m_images.PushBack(newImage);
				sceneDefPtr->m_imageCount++;
				m_worldMap.SetAt(worldID,worldItem);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool CWorldConstructKitDoc::NewAnimationInfo(DWORD id,LPCTSTR fileName)
{
	World worldItem;
	DWORD worldID = m_pTreeView->GetCurrWorldID();
	m_worldMap.Lookup(worldID,worldItem);
	DWORD sceneID = m_pTreeView->GetCurrSceneId();

  for (int i = 0 ; i < worldItem.m_numberOfScenes; i++)
	{
		if (worldItem.m_scenes[i].m_sceneID == sceneID)
		{
			AnimationInfo  newAnimation(id,fileName);

			bool isExist = false;
			for (int j = 0; j < worldItem.m_scenes[i].m_animationCount; j++)
			{
				if (newAnimation.m_animationID == worldItem.m_scenes[i].m_animations[j].m_animationID &&
					  newAnimation.m_fileNameVideo == worldItem.m_scenes[i].m_animations[j].m_fileNameVideo)
				{
					isExist = true;
					break;
				}
			}
			if (!isExist)
			{				
				SceneDefinition* sceneDefPtr = &worldItem.m_scenes[i];
				sceneDefPtr->m_animations.PushBack(newAnimation);
				sceneDefPtr->m_animationCount++;
				m_worldMap.SetAt(worldID,worldItem);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool CWorldConstructKitDoc::NewSFXInfo(DWORD id,LPCTSTR fileName)
{
	World worldItem;
	DWORD worldID = m_pTreeView->GetCurrWorldID();
	m_worldMap.Lookup(worldID,worldItem);
	DWORD sceneID = m_pTreeView->GetCurrSceneId();

  for (int i = 0 ; i < worldItem.m_numberOfScenes; i++)
	{
		if (worldItem.m_scenes[i].m_sceneID == sceneID)
		{
			SFXInfo  newSFX(id,fileName);

			bool isExist = false;
			for (int j = 0; j < worldItem.m_scenes[i].m_sfxCount; j++)
			{
				if (newSFX.m_sfxID == worldItem.m_scenes[i].m_sfx[j].m_sfxID &&
					  newSFX.m_fileName == worldItem.m_scenes[i].m_sfx[j].m_fileName)
				{
					isExist = true;
					break;
				}
			}
			if (!isExist)
			{				
				SceneDefinition* sceneDefPtr = &worldItem.m_scenes[i];
				sceneDefPtr->m_sfx.PushBack(newSFX);
				sceneDefPtr->m_sfxCount++;
				m_worldMap.SetAt(worldID,worldItem);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool CWorldConstructKitDoc::NewTextDisplay(DWORD id)
{
	World worldItem;
	DWORD worldID = m_pTreeView->GetCurrWorldID();
	m_worldMap.Lookup(worldID,worldItem);
	DWORD sceneID = m_pTreeView->GetCurrSceneId();

  for (int i = 0 ; i < worldItem.m_numberOfScenes; i++)
	{
		if (worldItem.m_scenes[i].m_sceneID == sceneID)
		{
			TextDisplay newText(id);

			bool isExist = false;
			for (int j = 0; j < worldItem.m_scenes[i].m_textOverlayCount; j++)
			{
				if (newText.m_textID == worldItem.m_scenes[i].m_textOverlays[j].m_textID)
				{
					isExist = true;
					break;
				}
			}
			if (!isExist)
			{				
				SceneDefinition* sceneDefPtr = &worldItem.m_scenes[i];
				sceneDefPtr->m_textOverlays.PushBack(newText);
				sceneDefPtr->m_textOverlayCount++;
				m_worldMap.SetAt(worldID,worldItem);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool CWorldConstructKitDoc::NewCharacterContext(DWORD id)
{
	World worldItem;
	DWORD worldID = m_pTreeView->GetCurrWorldID();
	m_worldMap.Lookup(worldID,worldItem);
	DWORD sceneID = m_pTreeView->GetCurrSceneId();


  for (int i = 0 ; i < worldItem.m_numberOfScenes; i++)
	{
		if (worldItem.m_scenes[i].m_sceneID == sceneID)
		{
			CharacterContext newCharacterContext(id);

			bool isExist = false;
			for (int j = 0; j < worldItem.m_scenes[i].m_characterCount; j++)
			{
				if (newCharacterContext.m_characterId == worldItem.m_scenes[i].m_sceneCharacters[j].m_characterId)
				{
					isExist = true;
					break;
				}
			}
			if (!isExist)
			{				
				SceneDefinition* sceneDefPtr = &worldItem.m_scenes[i];
				sceneDefPtr->m_sceneCharacters.PushBack(newCharacterContext);
				sceneDefPtr->m_characterCount++;
				m_worldMap.SetAt(worldID,worldItem);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool CWorldConstructKitDoc::NewHotSpot(DWORD id)
{
	World worldItem;
	DWORD worldID = m_pTreeView->GetCurrWorldID();
	m_worldMap.Lookup(worldID,worldItem);
	DWORD sceneID = m_pTreeView->GetCurrSceneId();

  for (int i = 0 ; i < worldItem.m_numberOfScenes; i++)
	{
		if (worldItem.m_scenes[i].m_sceneID == sceneID)
		{
			HotspotInfo newHotSpotInfo(id);

			bool isExist = false;
			for (int j = 0; j < worldItem.m_scenes[i].m_clickCount; j++)
			{
				if (newHotSpotInfo.m_hotSpotID == worldItem.m_scenes[i].m_clickSpots[j].m_hotSpotID)
				{
					isExist = true;
					break;
				}
			}
			if (!isExist)
			{				
			SceneDefinition* sceneDefPtr = &worldItem.m_scenes[i];
			sceneDefPtr->m_clickSpots.PushBack(newHotSpotInfo);
			sceneDefPtr->m_clickCount++;
			m_worldMap.SetAt(worldID,worldItem);
			return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool CWorldConstructKitDoc::NewKeyboard(DWORD id)
{
	World worldItem;
	DWORD worldID = m_pTreeView->GetCurrWorldID();
	m_worldMap.Lookup(worldID,worldItem);
	DWORD sceneID = m_pTreeView->GetCurrSceneId();

  for (int i = 0 ; i < worldItem.m_numberOfScenes; i++)
	{
		if (worldItem.m_scenes[i].m_sceneID == sceneID)
		{
			KeyboardTrigger newKeyboardInfo(id);

			bool isExist = false;
			for (int j = 0; j < worldItem.m_scenes[i].m_keyCount; j++)
			{
				if (newKeyboardInfo.m_keyID == worldItem.m_scenes[i].m_keys[j].m_keyID)
				{
					isExist = true;
					break;
				}
			}
			if (!isExist)
			{				
				SceneDefinition* sceneDefPtr = &worldItem.m_scenes[i];
				sceneDefPtr->m_keys.PushBack(newKeyboardInfo);
				sceneDefPtr->m_keyCount++;
				m_worldMap.SetAt(worldID,worldItem);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////
// CWorldConstructKitDoc commands


void CWorldConstructKitDoc::OnNew() 
{
	m_pTreeView->AddNode(); 
}

void CWorldConstructKitDoc::OnSave() 
{	
	m_pTreeView->SaveNode();


	CFileDialog dlg(FALSE,"dat");
	CString str("World files (*.dat)"); str += (TCHAR)NULL;
	str += "*.dat";str += (TCHAR)NULL;
	
	//set title
	dlg.m_ofn.lpstrTitle = "Save worlds";
	
	//set filter
	dlg.m_ofn.lpstrFilter = str;
	
	dlg.m_ofn.Flags &= ~(OFN_EXPLORER);
	if (dlg.DoModal() == IDOK)
	{     
		HANDLE hFile; 
		
		hFile = CreateFile(dlg.m_ofn.lpstrFile,
  											GENERIC_WRITE,                // open for writing 
												0,                            // do not share 
												NULL,                         // no security 
												CREATE_ALWAYS,                // overwrite existing 
												FILE_ATTRIBUTE_NORMAL,        // normal file 
												NULL);                        // no attr. template 
		
		if (hFile != INVALID_HANDLE_VALUE) 
		{   
			BOOL isSuccess;
			DWORD dwBytesWritten;
			int worldNum = m_worldMap.GetCount();
			isSuccess = WriteFile(hFile, 
                  					(const void*)&worldNum,
					                  sizeof(worldNum), 
					                  &dwBytesWritten,
					                  NULL); 
			if (isSuccess)
			{
				POSITION pos = m_worldMap.GetStartPosition();
				DWORD  nKey;
				World  world;
				while (pos != NULL)
				{
					m_worldMap.GetNextAssoc( pos, nKey, world );
					isSuccess &= world.SaveToFile(nKey,hFile);
				}
				if (isSuccess)
				{
					MessageBox(AfxGetMainWnd()->GetSafeHwnd(),"Creating file finished successfully.","Operation complete",MB_OK + MB_ICONINFORMATION);
				}
				else
				{
					MessageBox(AfxGetMainWnd()->GetSafeHwnd(),"Creating file fail.","Error",MB_OK + MB_ICONWARNING);
				}
			}
		} 
		else
		{
			MessageBox(AfxGetMainWnd()->GetSafeHwnd(),"Can't open file to write.","Error",MB_OK + MB_ICONWARNING);
		}
		CloseHandle(hFile);				
	}
}

void CWorldConstructKitDoc::OnDelete() 
{	
	m_pTreeView->DeleteNode();	
}

void CWorldConstructKitDoc::OnUpdateNew(CCmdUI* pCmdUI) 
{
	NodeType nodeType = m_pTreeView->IsGetNodeType();
	UINT resID = formData.GetCurrentForm();
	if (nodeType == TEMPLATE_NODE &&
		!(resID == IDD_STAGING_INFO))
	{
		pCmdUI->Enable(TRUE);	
	}
	else
	{
		pCmdUI->Enable(FALSE);	
	}
}

void CWorldConstructKitDoc::OnUpdateDelete(CCmdUI* pCmdUI) 
{
	NodeType nodeType = m_pTreeView->IsGetNodeType();
	UINT resID = formData.GetCurrentForm();
	if (nodeType == DYNAMIC_NODE ||		 
		resID == IDD_WORLD ||
		resID == IDD_SCENE_DEFINITION)
	{
		pCmdUI->Enable(TRUE);	
	}
	else
	{
		pCmdUI->Enable(FALSE);	
	}
}

void CWorldConstructKitDoc::OnGetDataFromDb() 
{
	((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.ChangeView(0, 1,RUNTIME_CLASS(TemplateFormView));		

	WorldMapType worldMap;
	//remove default
	worldMap.RemoveAll();
	BOOL isSuccess = GetNewDataFromFile(worldMap);	
	if (isSuccess)
	{
		int result = MessageBox(AfxGetMainWnd()->GetSafeHwnd(),"Do you want to save current data?","Question",MB_YESNO + MB_ICONQUESTION);
		if (result == IDYES)
		{
			OnSave();
		}
		m_worldMap.RemoveAll();
		formData.m_dynamicNodeMap.Clear();

    m_pTreeView->GetTreeCtrl().DeleteAllItems();		
		POSITION pos = worldMap.GetStartPosition();
		DWORD  key;
		World  world;
		while (pos != NULL)
		{
       worldMap.GetNextAssoc( pos, key, world );			

			 m_worldMap.SetAt(key,world);

			 CString newNodeTitleStr;	
			 if (key == 0)
			 {
				 newNodeTitleStr = WORLD_STR;
			 }
			 else
			 {
				 newNodeTitleStr.Format("(%d)%s",key,WORLD_STR);
			 }			 
			 m_pTreeView->AddWorldNodeWithData(newNodeTitleStr,key,world);
		}		
		m_pTreeView->GetTreeCtrl().Select(m_pTreeView->GetTreeCtrl().GetRootItem(), TVGN_CARET);			
	}
}

void CWorldConstructKitDoc::OnAddWorld() 
{
	((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.ChangeView(0, 1,RUNTIME_CLASS(TemplateFormView));		

	WorldMapType worldMap;
	BOOL isSuccess = GetNewDataFromFile(worldMap);

	POSITION pos = worldMap.GetStartPosition();
	DWORD  key;
	World  world;
	while (pos != NULL)
	{
		worldMap.GetNextAssoc( pos, key, world );			

		World oldWorld;
		if (m_worldMap.Lookup(key,oldWorld)) //if world already exist
		{
			//merge worlds

			//merge music script
			for ( int i = 0 ; i < world.m_bgMusicCount; i++)
			{
				bool isFound = false;
				for (int j = 0; j < oldWorld.m_bgMusicCount; j++)
				{
					if (world.m_bgMusicScript[i].m_scriptID == oldWorld.m_bgMusicScript[j].m_scriptID)
					{
						isFound = true;
					}
				}
				if (!isFound)
				{
					oldWorld.m_bgMusicScript.PushBack(world.m_bgMusicScript[i]);
					oldWorld.m_bgMusicCount++;

					HTREEITEM parentItem;
					parentItem = m_pTreeView->FindWorldChildItem(key,MUSIC_SCRIPT_STR);
					if (parentItem != NULL)
					{
						m_pTreeView->AddExistMusicScriptNode(key,oldWorld.m_bgMusicScript[oldWorld.m_bgMusicCount - 1],parentItem);
					}
				}
			}

			//merge music sample
			for ( i = 0 ; i < world.m_bgMusicFileCount; i++)
			{
				bool isFound = false;
				for (int j = 0; j < oldWorld.m_bgMusicFileCount; j++)
				{
					if (world.m_bgMusicSample[i].m_sampleID == oldWorld.m_bgMusicSample[j].m_sampleID &&
						  world.m_bgMusicSample[i].m_fileName == oldWorld.m_bgMusicSample[j].m_fileName)
					{
						isFound = true;
					}
				}
				if (!isFound)
				{
					oldWorld.m_bgMusicSample.PushBack(world.m_bgMusicSample[i]);
					oldWorld.m_bgMusicFileCount++;

					HTREEITEM parentItem;
					parentItem = m_pTreeView->FindWorldChildItem(key,MUSIC_SAMPLE_STR);
					if (parentItem != NULL)
					{
						m_pTreeView->AddExistMusicSampleNode(key,oldWorld.m_bgMusicSample[oldWorld.m_bgMusicFileCount - 1],parentItem);
					}
				}
			}

			//merge character info
			for ( i = 0 ; i < world.m_numberOfCharacters; i++)
			{
				bool isFound = false;
				for (int j = 0; j < oldWorld.m_numberOfCharacters; j++)
				{
					if (world.m_characters[i].m_characterName == oldWorld.m_characters[j].m_characterName &&
						  world.m_characters[i].m_characterId == oldWorld.m_characters[j].m_characterId)
					{
						isFound = true;
					}
				}
				if (!isFound)
				{
					oldWorld.m_characters.PushBack(world.m_characters[i]);
					oldWorld.m_numberOfCharacters++;

					HTREEITEM parentItem;
					parentItem = m_pTreeView->FindWorldChildItem(key,CHARACTER_INFO_STR);
					if (parentItem != NULL)
					{
						m_pTreeView->AddExistCharacterInfoNode(key,oldWorld.m_characters[oldWorld.m_numberOfCharacters - 1],parentItem);
					}
				}
			}

			//merge sky
			for ( i = 0 ; i < world.m_numberOfSkies; i++)
			{
				bool isFound = false;
				for (int j = 0; j < oldWorld.m_numberOfSkies; j++)
				{
					if (world.m_skies[i].m_skyID == oldWorld.m_skies[j].m_skyID &&
						  world.m_skies[i].m_fileName == oldWorld.m_skies[j].m_fileName)
					{
						isFound = true;
					}
				}
				if (!isFound)
				{
					oldWorld.m_skies.PushBack(world.m_skies[i]);
					oldWorld.m_numberOfSkies++;

					HTREEITEM parentItem;
					parentItem = m_pTreeView->FindWorldChildItem(key,SKY_DEFINITION_STR);
					if (parentItem != NULL)
					{
						m_pTreeView->AddExistSkyNode(key,oldWorld.m_skies[oldWorld.m_numberOfSkies - 1],parentItem);
					}
				}
			}

			//merge inventory
			for ( i = 0 ; i < world.m_inventorySize; i++)
			{
				bool isFound = false;
				for (int j = 0; j < oldWorld.m_inventorySize; j++)
				{
					if (world.m_inventory[i].m_itemID == oldWorld.m_inventory[j].m_itemID &&
						  world.m_inventory[i].m_iconFileName == oldWorld.m_inventory[j].m_iconFileName)
					{
						isFound = true;
					}
				}
				if (!isFound)
				{
					oldWorld.m_inventory.PushBack(world.m_inventory[i]);
					oldWorld.m_inventorySize++;

					HTREEITEM parentItem;
					parentItem = m_pTreeView->FindWorldChildItem(key,ITEM_DEFINITION_STR);
					if (parentItem != NULL)
					{
						m_pTreeView->AddExistInventoryNode(key,oldWorld.m_inventory[oldWorld.m_inventorySize - 1],parentItem);
					}
				}
			}

			//merge camera
			for ( i = 0 ; i < world.m_cameraCount; i++)
			{
				bool isFound = false;
				for (int j = 0; j < oldWorld.m_cameraCount; j++)
				{
					if (world.m_camera[i].m_sceneID == oldWorld.m_camera[j].m_sceneID)
					{
						isFound = true;
					}
				}
				if (!isFound)
				{
					oldWorld.m_camera.PushBack(world.m_camera[i]);
					oldWorld.m_cameraCount++;

					HTREEITEM parentItem;
					parentItem = m_pTreeView->FindWorldChildItem(key,CAMERA_DEFINITION_STR);
					if (parentItem != NULL)
					{
						m_pTreeView->AddExistCameraNode(key,oldWorld.m_camera[oldWorld.m_cameraCount - 1],parentItem);
					}
				}
			}

			HTREEITEM parentItem;
			//merge scene
			for ( i = 0 ; i < world.m_numberOfScenes; i++)
			{
				bool isFound = false;
				for (int j = 0; j < oldWorld.m_numberOfScenes; j++)
				{
					if (world.m_scenes[i].m_sceneID == oldWorld.m_scenes[j].m_sceneID)
					{
						isFound = true;
						break;
					}
				}
				if (!isFound) // whole scene don't exist ,we can add all childs
				{
					oldWorld.m_scenes.PushBack(world.m_scenes[i]);
					oldWorld.m_numberOfScenes++;

					int lastSceneIndx = oldWorld.m_numberOfScenes - 1;
					parentItem = m_pTreeView->FindSceneListItem(key);
					if (parentItem != NULL)
					{
						m_pTreeView->AddExistSceneNode(key,oldWorld.m_scenes[lastSceneIndx],parentItem);
					}

					//show images
					for (int k = 0; k < oldWorld.m_scenes[lastSceneIndx].m_imageCount; k++)
					{
						parentItem = m_pTreeView->FindSceneChildItem(key,oldWorld.m_scenes[lastSceneIndx].m_sceneID,IMAGE_INFO_STR);
						if (parentItem != NULL)
						{
							m_pTreeView->AddExistImage(key,oldWorld.m_scenes[lastSceneIndx].m_sceneID, oldWorld.m_scenes[lastSceneIndx].m_images[k],parentItem);
						}
					}

					//show animations
					for (k = 0; k < oldWorld.m_scenes[lastSceneIndx].m_animationCount; k++)
					{
						parentItem = m_pTreeView->FindSceneChildItem(key,oldWorld.m_scenes[lastSceneIndx].m_sceneID,ANIMATION_INFO_STR);
						if (parentItem != NULL)
						{
							m_pTreeView->AddExistAnimation(key,oldWorld.m_scenes[lastSceneIndx].m_sceneID, oldWorld.m_scenes[lastSceneIndx].m_animations[k],parentItem);
						}
					}

					//show characters
					for (k = 0; k < oldWorld.m_scenes[lastSceneIndx].m_characterCount; k++)
					{
						parentItem = m_pTreeView->FindSceneChildItem(key,oldWorld.m_scenes[lastSceneIndx].m_sceneID,CHARACTER_CONTEXT_STR);
						if (parentItem != NULL)
						{
							m_pTreeView->AddExistCharacter(key,oldWorld.m_scenes[lastSceneIndx].m_sceneID, oldWorld.m_scenes[lastSceneIndx].m_sceneCharacters[k],parentItem);
						}
					}

					//show sfx info
					for (k = 0; k < oldWorld.m_scenes[lastSceneIndx].m_sfxCount; k++)
					{
						parentItem = m_pTreeView->FindSceneChildItem(key,oldWorld.m_scenes[lastSceneIndx].m_sceneID,SFX_INFO_STR);
						if (parentItem != NULL)
						{
							m_pTreeView->AddExistSFX(key,oldWorld.m_scenes[lastSceneIndx].m_sceneID, oldWorld.m_scenes[lastSceneIndx].m_sfx[k],parentItem);
						}
					}

					//show text display
					for (k = 0; k < oldWorld.m_scenes[lastSceneIndx].m_textOverlayCount; k++)
					{
						parentItem = m_pTreeView->FindSceneChildItem(key,oldWorld.m_scenes[lastSceneIndx].m_sceneID,TEXT_DISPLAY_STR);
						if (parentItem != NULL)
						{
							m_pTreeView->AddExistText(key,oldWorld.m_scenes[lastSceneIndx].m_sceneID, oldWorld.m_scenes[lastSceneIndx].m_textOverlays[k],parentItem);
						}
					}

					//show hot spot
					for (k = 0; k < oldWorld.m_scenes[lastSceneIndx].m_clickCount; k++)
					{
						parentItem = m_pTreeView->FindSceneChildItem(key,oldWorld.m_scenes[lastSceneIndx].m_sceneID,HOT_SPOT_INFO_STR);
						if (parentItem != NULL)
						{
							m_pTreeView->AddExistHotSpot(key,oldWorld.m_scenes[lastSceneIndx].m_sceneID, oldWorld.m_scenes[lastSceneIndx].m_clickSpots[k],parentItem);
						}
					}

					//show keyboard trigger
					for (k = 0; k < oldWorld.m_scenes[lastSceneIndx].m_keyCount; k++)
					{
						parentItem = m_pTreeView->FindSceneChildItem(key,oldWorld.m_scenes[lastSceneIndx].m_sceneID,KEYBOARD_TRIGGER_STR);
						if (parentItem != NULL)
						{
							m_pTreeView->AddExistKeyboard(key,oldWorld.m_scenes[lastSceneIndx].m_sceneID, oldWorld.m_scenes[lastSceneIndx].m_keys[k],parentItem);
						}
					}
				}
				else  //scene already exist, merge scene contant
				{
					int sceneIndx = j;

					//merge images
					for ( int k = 0 ; k < world.m_scenes[i].m_imageCount; k++)
					{
						bool isFound = false;
						for (int q = 0; q < oldWorld.m_scenes[i].m_imageCount; q++)
						{
							int testOldId = oldWorld.m_scenes[i].m_images[q].m_imageID;
							int testNewId = world.m_scenes[i].m_images[k].m_imageID;
							if (world.m_scenes[i].m_images[k].m_imageID == oldWorld.m_scenes[i].m_images[q].m_imageID &&
								  world.m_scenes[i].m_images[k].m_fileName == oldWorld.m_scenes[i].m_images[q].m_fileName)
							{
								isFound = true;
							}
						}

						if (!isFound)
						{
							//copy image
							oldWorld.m_scenes[sceneIndx].m_images.PushBack(world.m_scenes[i].m_images[k]);
							oldWorld.m_scenes[sceneIndx].m_imageCount++;

							parentItem = m_pTreeView->FindSceneChildItem(key,oldWorld.m_scenes[sceneIndx].m_sceneID,IMAGE_INFO_STR);
							if (parentItem != NULL)
							{
								m_pTreeView->AddExistImage(key,
									                         oldWorld.m_scenes[sceneIndx].m_sceneID,
																					 oldWorld.m_scenes[sceneIndx].m_images[oldWorld.m_scenes[sceneIndx].m_imageCount - 1],
																					 parentItem);
							}
						}

					}

					//merge animations
					for ( k = 0 ; k < world.m_scenes[i].m_animationCount; k++)
					{
						bool isFound = false;
						for (int q = 0; q < oldWorld.m_scenes[i].m_animationCount; q++)
						{
							if (world.m_scenes[i].m_animations[k].m_animationID == oldWorld.m_scenes[i].m_animations[q].m_animationID &&
								  world.m_scenes[i].m_animations[k].m_fileNameVideo == oldWorld.m_scenes[i].m_animations[q].m_fileNameVideo)
							{
								isFound = true;
							}
						}
						if (!isFound)
						{
							//copy animations
							oldWorld.m_scenes[sceneIndx].m_animations.PushBack(world.m_scenes[i].m_animations[k]);
							oldWorld.m_scenes[sceneIndx].m_animationCount++;
								
							parentItem = m_pTreeView->FindSceneChildItem(key,oldWorld.m_scenes[sceneIndx].m_sceneID,ANIMATION_INFO_STR);
							if (parentItem != NULL)
							{
								m_pTreeView->AddExistAnimation(key,
									                             oldWorld.m_scenes[sceneIndx].m_sceneID,
																							 oldWorld.m_scenes[sceneIndx].m_animations[oldWorld.m_scenes[sceneIndx].m_animationCount - 1],
																							 parentItem);
							}
						}
					}

					//merge character
					for ( k = 0 ; k < world.m_scenes[i].m_characterCount; k++)
					{
						bool isFound = false;
						for (int q = 0; q < oldWorld.m_scenes[i].m_characterCount; q++)
						{
							if (world.m_scenes[i].m_sceneCharacters[k].m_characterId == oldWorld.m_scenes[i].m_sceneCharacters[q].m_characterId)
							{
								isFound = true;
							}
						}
						if (!isFound)
						{
							//copy character
							oldWorld.m_scenes[sceneIndx].m_sceneCharacters.PushBack(world.m_scenes[i].m_sceneCharacters[k]);
							oldWorld.m_scenes[sceneIndx].m_characterCount++;
								
							parentItem = m_pTreeView->FindSceneChildItem(key,oldWorld.m_scenes[sceneIndx].m_sceneID,CHARACTER_CONTEXT_STR);
							if (parentItem != NULL)
							{
								m_pTreeView->AddExistCharacter(key,
									                             oldWorld.m_scenes[sceneIndx].m_sceneID,
																							 oldWorld.m_scenes[sceneIndx].m_sceneCharacters[oldWorld.m_scenes[sceneIndx].m_characterCount - 1],
																							 parentItem);
							}
						}
					}

					//merge sfx
					for ( k = 0 ; k < world.m_scenes[i].m_sfxCount; k++)
					{
						bool isFound = false;
						for (int q = 0; q < oldWorld.m_scenes[i].m_sfxCount; q++)
						{
							if (world.m_scenes[i].m_sfx[k].m_sfxID == oldWorld.m_scenes[i].m_sfx[q].m_sfxID &&
								  world.m_scenes[i].m_sfx[k].m_fileName == oldWorld.m_scenes[i].m_sfx[q].m_fileName)
							{
								isFound = true;
							}
						}
						if (!isFound)
						{
							//copy sfx
							oldWorld.m_scenes[sceneIndx].m_sfx.PushBack(world.m_scenes[i].m_sfx[k]);
							oldWorld.m_scenes[sceneIndx].m_sfxCount++;
								
							parentItem = m_pTreeView->FindSceneChildItem(key,oldWorld.m_scenes[sceneIndx].m_sceneID,SFX_INFO_STR);
							if (parentItem != NULL)
							{
								m_pTreeView->AddExistSFX(key,
									                       oldWorld.m_scenes[sceneIndx].m_sceneID,
																				 oldWorld.m_scenes[sceneIndx].m_sfx[oldWorld.m_scenes[sceneIndx].m_sfxCount - 1],
																				 parentItem);
							}
						}
					}

					//merge text
					for ( k = 0 ; k < world.m_scenes[i].m_textOverlayCount; k++)
					{
						bool isFound = false;
						for (int q = 0; q < oldWorld.m_scenes[i].m_textOverlayCount; q++)
						{
							if (world.m_scenes[i].m_textOverlays[k].m_textID == oldWorld.m_scenes[i].m_textOverlays[q].m_textID)
							{
								isFound = true;
							}
						}
						if (!isFound)
						{
							//copy text
							oldWorld.m_scenes[sceneIndx].m_textOverlays.PushBack(world.m_scenes[i].m_textOverlays[k]);
							oldWorld.m_scenes[sceneIndx].m_textOverlayCount++;
								
							parentItem = m_pTreeView->FindSceneChildItem(key,oldWorld.m_scenes[sceneIndx].m_sceneID,TEXT_DISPLAY_STR);
							if (parentItem != NULL)
							{
								m_pTreeView->AddExistText(key,
									                        oldWorld.m_scenes[sceneIndx].m_sceneID, 
																					oldWorld.m_scenes[sceneIndx].m_textOverlays[oldWorld.m_scenes[sceneIndx].m_textOverlayCount - 1],
																					parentItem);
							}
						}
					}

					//merge hotSpot
					for ( k = 0 ; k < world.m_scenes[i].m_clickCount; k++)
					{
						bool isFound = false;
						for (int q = 0; q < oldWorld.m_scenes[i].m_clickCount; q++)
						{
							if (world.m_scenes[i].m_clickSpots[k].m_hotSpotID == oldWorld.m_scenes[i].m_clickSpots[q].m_hotSpotID)
							{
								isFound = true;
							}
						}
						if (!isFound)
						{
							//copy hotspot
							oldWorld.m_scenes[sceneIndx].m_clickSpots.PushBack(world.m_scenes[i].m_clickSpots[k]);
							oldWorld.m_scenes[sceneIndx].m_clickCount++;
								
							parentItem = m_pTreeView->FindSceneChildItem(key,oldWorld.m_scenes[sceneIndx].m_sceneID,HOT_SPOT_INFO_STR);
							if (parentItem != NULL)
							{
								m_pTreeView->AddExistHotSpot(key,
									                           oldWorld.m_scenes[sceneIndx].m_sceneID, 
																			  		 oldWorld.m_scenes[sceneIndx].m_clickSpots[oldWorld.m_scenes[sceneIndx].m_clickCount - 1],
																						 parentItem);
							}
						}
					}

					//merge keyboard
					for ( k = 0 ; k < world.m_scenes[i].m_keyCount; k++)
					{
						bool isFound = false;
						for (int q = 0; q < oldWorld.m_scenes[i].m_keyCount; q++)
						{
							if (world.m_scenes[i].m_keys[k].m_keyID == oldWorld.m_scenes[i].m_keys[q].m_keyID)
							{
								isFound = true;
							}
						}
						if (!isFound)
						{
							//copy keyboard
							oldWorld.m_scenes[sceneIndx].m_keys.PushBack(world.m_scenes[i].m_keys[k]);
							oldWorld.m_scenes[sceneIndx].m_keyCount++;
								
							parentItem = m_pTreeView->FindSceneChildItem(key,oldWorld.m_scenes[sceneIndx].m_sceneID,KEYBOARD_TRIGGER_STR);
							if (parentItem != NULL)
							{
								m_pTreeView->AddExistKeyboard(key,
									                            oldWorld.m_scenes[sceneIndx].m_sceneID, 
																							oldWorld.m_scenes[sceneIndx].m_keys[oldWorld.m_scenes[sceneIndx].m_keyCount - 1],
																							parentItem);
							}
						}
					}
				}
			}

			m_worldMap.SetAt(key,oldWorld);
		}
		else
		{
	  	m_worldMap.SetAt(key,world);
			 
			CString newNodeTitleStr;	
			if (key == 0)
			{
				 newNodeTitleStr = WORLD_STR;
			}
			else
			{
				 newNodeTitleStr.Format("(%d)%s",key,WORLD_STR);
			}			 
			m_pTreeView->AddWorldNodeWithData(newNodeTitleStr,key,world);
		}

		m_pTreeView->GetTreeCtrl().Invalidate();
		m_pTreeView->GetTreeCtrl().Select(m_pTreeView->GetTreeCtrl().GetRootItem(), TVGN_CARET);			

	}		
}
	

BOOL CWorldConstructKitDoc::GetNewDataFromFile(WorldMapType& worldMap)
{
	BOOL isSuccess = FALSE;
	CFileDialog dlg(TRUE,"dat");
	//set title
	dlg.m_ofn.lpstrTitle = "Open DB file";


	CString filterStr;	
	filterStr	= ("World files (*.dat)");filterStr += (TCHAR)NULL;
	filterStr += "*.dat";filterStr += (TCHAR)NULL;

	//set filter
	dlg.m_ofn.lpstrFilter = filterStr;
	
	dlg.m_ofn.Flags &= ~(OFN_EXPLORER);
	if (dlg.DoModal() == IDOK)
	{     
		HANDLE hFile;  
		hFile = CreateFile(dlg.m_ofn.lpstrFile,
												GENERIC_READ,              // open for reading 
												FILE_SHARE_READ,           // share for reading 
												NULL,                      // no security 
												OPEN_EXISTING,             // existing file only 
												FILE_ATTRIBUTE_NORMAL,     // normal file 
												NULL);                     // no attr. template 
		
		if (hFile != INVALID_HANDLE_VALUE) 
		{ 
			DWORD dwBytesRead;
			int worldNum;

			isSuccess = ReadFile(hFile, 
													 (void*)&worldNum,
													  sizeof(worldNum), 
														&dwBytesRead,
														NULL); 
			DWORD key;
			if (isSuccess)
			{
				for (int i = 0; i < worldNum; i++)
				{
			    World newWorldObj;
					isSuccess &= newWorldObj.ReadFromFile(key,hFile);
					worldMap.SetAt(key,newWorldObj);
				}
			}			
		}				
		else
		{
			MessageBox(AfxGetMainWnd()->GetSafeHwnd(),"Can't open file to read.","Error",MB_OK + MB_ICONWARNING);
		}

		CloseHandle(hFile);
	}		
	return isSuccess;
}



BOOL CWorldConstructKitDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	int result = MessageBox(AfxGetMainWnd()->GetSafeHwnd(),"Do you want to save current data?","Question",MB_YESNO + MB_ICONQUESTION);
	if (result == IDYES)
	{
		OnSave();		
	}
	return TRUE;
}
