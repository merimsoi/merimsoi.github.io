#ifndef FORM_DATA
#define FORM_DATA

#include "basic.h"
#include "AnimationInfoView.h"
#include "CameraDefinitionView.h"
#include "CharacterContextView.h"
#include "CharacterInfoView.h"
#include "HotSpotInfoView.h"
#include "ImageInfoView.h"
#include "ItemDefinitionView.h"
#include "KeyboardTriggerView.h"
#include "MusicSampleView.h"
#include "MusicScriptView.h"
#include "SceneDefinitionView.h"
#include "SFXInfoView.h"
#include "SkyDefinitionView.h"
#include "StagingInfoView.h"
#include "TextDisplayView.h"
#include "WorldDefinitionView.h"
#include "TemplateFormView.h"
#include <afxtempl.h>
#include "engineclasses.h"

// This structure links form index to form name and view class
struct NodeData
{
	 UINT             resID;       // resource ID 
   LPCTSTR          lpszName;    // Display name
   CRuntimeClass*   pClass;      // MFC runtime class
};
struct DynamicNodeData
{
	UINT resId;
	LPCTSTR lpszName;    
	inline bool operator== (const DynamicNodeData& data) const
	{
		if (resId == data.resId &&
			  strcmp(lpszName,data.lpszName) == 0)
		{
			return true;
		}		
		else
		{
			return false;
		}
	}
};
// Global information about forms.
// Class hides implementation of mapping.

class CFormData 
{
private:
    UINT  m_nCurrentForm;
		DWORD m_currWorldId;
 
public:
    CFormData();
		~CFormData();
    CRuntimeClass*    GetViewClass(UINT iWhich);
    LPCTSTR           GetDisplayName(UINT iWhich);
		UINT              GetResID(LPCTSTR nodeStr);
    UINT              GetCurrentForm() { return  m_nCurrentForm; }
    void              SetCurrentForm(UINT iWhich);
		void              SetCurrentWorlId(DWORD id);
		DWORD             GetCurrentWorldId() { return  m_currWorldId; }

		StdListClass<DynamicNodeData> m_dynamicNodeMap;		
};

extern NodeData rootNodes[ROOT_NUM];
extern NodeData worldLevelNodes[WORLD_LEVEL_NUM];
extern NodeData sceneDefinitionNodes[SCENE_DEFINITION_NUM];

extern CFormData formData; // global instance to access through

#endif //FORM_DATA