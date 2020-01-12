#include "stdafx.h"
#include "forms.h"

CFormData formData; // global instance

NodeData rootNodes[ROOT_NUM] =
{
	{IDD_WORLD, _T(WORLD_STR) ,RUNTIME_CLASS(WorldDefinitionView) }
};

NodeData worldLevelNodes[WORLD_LEVEL_NUM] = 
{
	{IDD_MUSIC_SCRIPT, _T(MUSIC_SCRIPT_STR) ,RUNTIME_CLASS(MusicScriptView) },
	{IDD_MUSIC_SAMPLE, _T(MUSIC_SAMPLE_STR) ,RUNTIME_CLASS(MusicSampleView) },
	{IDD_CHARACTER_INFO, _T(CHARACTER_INFO_STR) ,RUNTIME_CLASS(CharacterInfoView) },
	{IDD_SCENE_DEFINITION, _T(SCENE_DEFINITION_STR) ,RUNTIME_CLASS(SceneDefinitionView) },
	{IDD_SKY_DEFINITION, _T(SKY_DEFINITION_STR) ,RUNTIME_CLASS(SkyDefinitionView) }, 
	{IDD_ITEM_DEFINITION, _T(ITEM_DEFINITION_STR) ,RUNTIME_CLASS(ItemDefinitionView) },
	{IDD_CAMERA_DEFINITION, _T(CAMERA_DEFINITION_STR) ,RUNTIME_CLASS(CameraDefinitionView) }	
};

NodeData sceneDefinitionNodes[SCENE_DEFINITION_NUM] = 
{
	{IDD_STAGING_INFO, _T(STAGING_INFO_STR) ,RUNTIME_CLASS(StagingInfoView)}, 
	{IDD_IMAGE_INFO, _T(IMAGE_INFO_STR) ,RUNTIME_CLASS(ImageInfoView)},
	{IDD_ANIMATION_INFO, _T(ANIMATION_INFO_STR) ,RUNTIME_CLASS(AnimationInfoView)},
	{IDD_CHARACTER_CONTEXT, _T(CHARACTER_CONTEXT_STR) ,RUNTIME_CLASS(CharacterContextView)},
	{IDD_SFX_INFO, _T(SFX_INFO_STR) ,RUNTIME_CLASS(SFXInfoView)},
	{IDD_TEXT_DISPLAY, _T(TEXT_DISPLAY_STR) ,RUNTIME_CLASS(TextDisplayView)},
	{IDD_HOT_SPOT_INFO, _T(HOT_SPOT_INFO_STR) ,RUNTIME_CLASS(HotSpotInfoView)},
	{IDD_KEYBOARD_TRIGGER, _T(KEYBOARD_TRIGGER_STR) ,RUNTIME_CLASS(KeyboardTriggerView)}
};

CFormData::CFormData()
{
//   SetCurrentForm(IDD_WORLD);
}

CFormData::~CFormData()
{
	m_dynamicNodeMap.ScanInit(DIRECTION_FORWARD);
	while (m_dynamicNodeMap.HasMoreElements())
	{			
		DynamicNodeData nodeData = m_dynamicNodeMap.NextElement();
		delete const_cast<LPSTR>(nodeData.lpszName);
	}
}

void CFormData::SetCurrentForm(UINT iWhich)
{  
  m_nCurrentForm = iWhich;    
}

void CFormData::SetCurrentWorlId(DWORD id)
{
	m_currWorldId = id;
}

CRuntimeClass* CFormData::GetViewClass(UINT iWhich)
{	
	for (int i = 0; i < ROOT_NUM ; i++)
	{
		if (iWhich == rootNodes[i].resID)
		{
			return rootNodes[i].pClass;
		}
	}

	for (i = 0 ; i < WORLD_LEVEL_NUM ; i++)
	{
		if (iWhich == worldLevelNodes[i].resID)
		{
			return worldLevelNodes[i].pClass;
		}
	}

	for (i = 0; i < SCENE_DEFINITION_NUM; i++)
	{
		if (iWhich == sceneDefinitionNodes[i].resID)
		{
			return sceneDefinitionNodes[i].pClass;
		}
	}  
	return NULL;
}

UINT CFormData::GetResID(LPCTSTR nodeStr)
{
	for (int i = 0; i < ROOT_NUM ; i++)
	{
		if (strcmp(nodeStr,rootNodes[i].lpszName) == 0)
		{
			return rootNodes[i].resID;
		}
	}

	for (i = 0 ; i < WORLD_LEVEL_NUM ; i++)
	{
		if (strcmp(nodeStr,worldLevelNodes[i].lpszName) == 0)
		{
			return worldLevelNodes[i].resID;
		}
	}

	for (i = 0; i < SCENE_DEFINITION_NUM; i++)
	{
		if (strcmp(nodeStr,sceneDefinitionNodes[i].lpszName) == 0)
		{
			return sceneDefinitionNodes[i].resID;
		}
	}  
	
	m_dynamicNodeMap.ScanInit(DIRECTION_FORWARD);
	while (m_dynamicNodeMap.HasMoreElements())
	{			
		DynamicNodeData nodeData = m_dynamicNodeMap.NextElement();

		CString dynMapStr;
		CMyTreeView*	m_pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));

		DWORD worldId = m_pTreeView->GetCurrWorldID();
		DWORD sceneId = m_pTreeView->GetCurrSceneId();
		if (sceneId == UNDEFINED_SCENE)
		{
			dynMapStr.Format("%d--%s-%s",worldId,m_pTreeView->GetParentName().IsEmpty() ? m_pTreeView->GetCurrNodeName() : m_pTreeView->GetParentName(),nodeStr);
		}
		else
		{
			dynMapStr.Format("%d-%d-%s-%s",worldId,sceneId ,m_pTreeView->GetParentName(),nodeStr);
		}		

		if (strcmp(nodeData.lpszName,dynMapStr.GetBuffer(0)) == 0 )
		{
			return nodeData.resId;
		}
	}

	return 0;
}


LPCTSTR CFormData::GetDisplayName(UINT iWhich)
{    
	for (int i = 0; i < ROOT_NUM ; i++)
	{
		if (iWhich == rootNodes[i].resID)
		{
			return rootNodes[i].lpszName;
		}
	}

	for (i = 0 ; i < WORLD_LEVEL_NUM ; i++)
	{
		if (iWhich == worldLevelNodes[i].resID)
		{
			return worldLevelNodes[i].lpszName;
		}
	}

	for (i = 0; i < SCENE_DEFINITION_NUM; i++)
	{
		if (iWhich == sceneDefinitionNodes[i].resID)
		{
			return sceneDefinitionNodes[i].lpszName;
		}
	}  
	return NULL;
}

