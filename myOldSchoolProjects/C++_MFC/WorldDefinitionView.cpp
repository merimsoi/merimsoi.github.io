// WorldDefinitionView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "WorldDefinitionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// WorldDefinitionView

IMPLEMENT_DYNCREATE(WorldDefinitionView, CFormView)

WorldDefinitionView::WorldDefinitionView()
	: CFormView(WorldDefinitionView::IDD)
{
	//{{AFX_DATA_INIT(WorldDefinitionView)
	m_cameraCount = 0;
	m_characterNum = 0;
	m_inventorySize = 0;
	m_isClockPowered = FALSE;
	m_musicFileCount = 0;
	m_musicScriptCount = 0;
	m_scenesNumber = 0;
	m_skyNumber = 0;
	m_trackID = 0;
	m_trackValue = 0;
	m_clockValue = 0;
	//}}AFX_DATA_INIT
}

WorldDefinitionView::~WorldDefinitionView()
{
}

void WorldDefinitionView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(WorldDefinitionView)
	DDX_Control(pDX, IDC_LIST_TRACK_RECORD, m_trackRecordList);
	DDX_Text(pDX, IDC_CAMERA_COUNT, m_cameraCount);
	DDX_Text(pDX, IDC_CHARACTER_NUMBER, m_characterNum);
	DDX_Text(pDX, IDC_INVENTORY_SIZE, m_inventorySize);
	DDX_Check(pDX, IDC_IS_CLOCK_POWERED, m_isClockPowered);
	DDX_Text(pDX, IDC_MUSIC_FILE_COUNT, m_musicFileCount);
	DDX_Text(pDX, IDC_MUSIC_SCRIPT_COUNT, m_musicScriptCount);
	DDX_Text(pDX, IDC_SCENES_NUMBER, m_scenesNumber);
	DDX_Text(pDX, IDC_SKY_NUMBER, m_skyNumber);
	DDX_Text(pDX, IDC_TRACK_ID, m_trackID);
	DDX_Text(pDX, IDC_TRACK_VALUE, m_trackValue);
	DDX_Text(pDX, IDC_CLOCK_VALUE, m_clockValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(WorldDefinitionView, CFormView)
	//{{AFX_MSG_MAP(WorldDefinitionView)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_LBN_SELCHANGE(IDC_LIST_TRACK_RECORD, OnSelchangeListTrackRecord)
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	ON_BN_CLICKED(IDC_UP, OnUp)
	//}}AFX_MSG_MAP
	ON_MESSAGE(RUNTIME_SAVE_MESSAGE,OnRuntimeSave)
	ON_MESSAGE(UPDATE_WORLD_OBJECT,OnUpdateWorldObject)
	ON_MESSAGE(UPDATE_DELETING_IN_WORLD,OnUpdateWorldObject)
	ON_EN_KILLFOCUS(IDC_CLOCK_VALUE, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TRACK_ID, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TRACK_VALUE, OnKillfocus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WorldDefinitionView diagnostics

#ifdef _DEBUG
void WorldDefinitionView::AssertValid() const
{
	CFormView::AssertValid();
}

void WorldDefinitionView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// WorldDefinitionView message handlers

void WorldDefinitionView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
}

CWorldConstructKitDoc* WorldDefinitionView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));
	return (CWorldConstructKitDoc*)m_pDocument;
}
BOOL WorldDefinitionView::GetMyWorld()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	m_worldId = pTreeView->GetCurrWorldID();	
	
	CWorldConstructKitDoc* doc = GetDocument();
	BOOL result = doc->m_worldMap.Lookup(m_worldId,m_world);	
  return result;
}


void WorldDefinitionView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	OnUpdateWorldObject();

	m_clockValue = m_world.m_clockValue;
	m_isClockPowered = m_world.m_clockIsPowered;
	m_musicScriptCount = m_world.m_bgMusicCount;
	m_musicFileCount = m_world.m_bgMusicFileCount;
	m_characterNum = m_world.m_numberOfCharacters;
	m_scenesNumber = m_world.m_numberOfScenes;
	m_skyNumber = m_world.m_numberOfSkies;
	m_inventorySize = m_world.m_inventorySize;
	m_cameraCount = m_world.m_cameraCount;


	CString trackRecordStr;
	m_trackRecordList.ResetContent();
	for (int j = 0; j < m_world.m_recordCount;j++)
	{
		trackRecordStr.Format("%d -> %d",m_world.m_trackID[j],m_world.m_trackRecord[j]);
		int indx = m_trackRecordList.AddString(trackRecordStr);
		m_trackRecordList.SetItemData(indx,m_world.m_trackID[j]);
	}

	if (m_world.m_recordCount > 0)
	{
		m_trackRecordList.SetCurSel(0);
	}
	int selIndx = m_trackRecordList.GetCurSel();
	FillTrackDetails(selIndx);

	UpdateData(FALSE);
}

void WorldDefinitionView::FillTrackDetails(int selIndx)
{
	if (selIndx >= 0)
	{
		m_trackID = m_world.m_trackID[selIndx];
		m_trackValue = m_world.m_trackRecord[selIndx];
	}
	else
	{
		m_trackID = 0;
		m_trackValue = 0;
	}
	UpdateData(FALSE);
}

int WorldDefinitionView::IsExistTrack(short trackId)
{
	for (int i = 0 ; i < m_world.m_recordCount;i++)
	{		
		if (m_world.m_trackID[i] == trackId)
		{
			return i;
		}
	}
	return NOT_FOUND;
}

void WorldDefinitionView::OnRuntimeSave()
{
	UpdateData(TRUE);

	m_world.m_clockValue = m_clockValue ;
	m_world.m_clockIsPowered = m_isClockPowered ? true : false;
	UpdateMap();
}

void WorldDefinitionView::UpdateMap()
{
	CWorldConstructKitDoc* doc = GetDocument();

	int countBefore = doc->m_worldMap.GetCount();
	doc->m_worldMap.SetAt(m_worldId,m_world);	
	int countAfter = doc->m_worldMap.GetCount();
	if (countBefore != countAfter)
	{
		ASSERT(FALSE);
	}

}
void WorldDefinitionView::OnUpdateWorldObject()
{
  GetMyWorld();
}

void WorldDefinitionView::OnAdd() 
{
	if (UpdateData(TRUE))
	{
		if (IsExistTrack(m_trackID) == NOT_FOUND)
		{
				m_world.m_trackID.PushBack(m_trackID);
				m_world.m_trackRecord.PushBack(m_trackValue);
				
				CString trackStr;
				trackStr.Format("%d -> %d",m_trackID,m_trackValue);
				int indx = m_trackRecordList.AddString(trackStr);
				m_trackRecordList.SetItemData(indx,m_trackID);
				m_world.m_recordCount++;
				UpdateMap();
		}		
		else
		{
			MessageBox("This Track ID already exist!","Error",MB_OK + MB_ICONWARNING);
		}	
	}	
}

void WorldDefinitionView::OnEdit() 
{
	if (UpdateData(TRUE))
	{
		int listIndx = m_trackRecordList.GetCurSel();
		short trackId = m_trackRecordList.GetItemData(listIndx);
		
		int indx;
		if ((indx = IsExistTrack(m_trackID)) != NOT_FOUND)
		{
			if (m_trackID != trackId)
			{
				MessageBox("Can't update Track ID","Error",MB_OK + MB_ICONWARNING);
			}
			else
			{
				m_world.m_trackID[indx] = m_trackID;
				m_world.m_trackRecord[indx] = m_trackValue;


				m_trackRecordList.DeleteString(listIndx);
				
				CString lineStr;
				lineStr.Format("%d -> %d",m_trackID,m_trackValue);
				int indx = m_trackRecordList.InsertString(listIndx,lineStr);
				m_trackRecordList.SetItemData(indx,m_trackID);

				UpdateMap();
			}
		}		
		else
		{
			MessageBox("This Track ID not exist!","Error",MB_OK + MB_ICONWARNING);
		}
	}
}

void WorldDefinitionView::OnDelete() 
{
	int indx = m_trackRecordList.GetCurSel();
	short trackID = m_trackRecordList.GetItemData(indx);
	int indxInArr;

	if ((indxInArr = IsExistTrack(trackID)) != NOT_FOUND)
	{		
			m_world.m_trackID.RemoveByIndex(indxInArr);
			m_world.m_trackRecord.RemoveByIndex(indxInArr);
			m_world.m_recordCount--;
			UpdateMap();
	}
	m_trackRecordList.DeleteString(indx);
	m_trackRecordList.SetCurSel(0);
	OnSelchangeListTrackRecord();	
}

void WorldDefinitionView::OnSelchangeListTrackRecord() 
{
	UpdateData(TRUE);
	int indx = m_trackRecordList.GetCurSel();
	short trackID = m_trackRecordList.GetItemData(indx);

	int indxArr = IsExistTrack(trackID);
	FillTrackDetails(indxArr);		
}


void WorldDefinitionView::OnDown() 
{
	int listIndx = m_trackRecordList.GetCurSel();
	if (listIndx != m_trackRecordList.GetCount() - 1)
	{
		m_world.m_trackID.Replace(listIndx,listIndx + 1);
		m_world.m_trackRecord.Replace(listIndx,listIndx + 1);
		
		CString trackRecordStr;
		m_trackRecordList.ResetContent();
		for (int j = 0; j < m_world.m_recordCount;j++)
		{
			trackRecordStr.Format("%d -> %d",m_world.m_trackID[j],m_world.m_trackRecord[j]);
			int indx = m_trackRecordList.AddString(trackRecordStr);
			m_trackRecordList.SetItemData(indx,m_world.m_trackID[j]);
		}	
		m_trackRecordList.SetCurSel(listIndx + 1);
	}
}

void WorldDefinitionView::OnUp() 
{
	int listIndx = m_trackRecordList.GetCurSel();
	if (listIndx != 0)
	{
		m_world.m_trackID.Replace(listIndx - 1,listIndx);
		m_world.m_trackRecord.Replace(listIndx - 1,listIndx);
		
		CString trackRecordStr;
		m_trackRecordList.ResetContent();
		for (int j = 0; j < m_world.m_recordCount;j++)
		{
			trackRecordStr.Format("%d -> %d",m_world.m_trackID[j],m_world.m_trackRecord[j]);
			int indx = m_trackRecordList.AddString(trackRecordStr);
			m_trackRecordList.SetItemData(indx,m_world.m_trackID[j]);
		}	
		m_trackRecordList.SetCurSel(listIndx - 1);
	}
}
void WorldDefinitionView::OnKillfocus() 
{
	UpdateData(TRUE);	
}
