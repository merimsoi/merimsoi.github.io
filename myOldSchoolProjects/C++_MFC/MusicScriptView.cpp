// MusicScriptView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "MusicScriptView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MusicScriptView

IMPLEMENT_DYNCREATE(MusicScriptView, CFormView)

MusicScriptView::MusicScriptView()
	: CFormView(MusicScriptView::IDD)
{
	//{{AFX_DATA_INIT(MusicScriptView)
	m_commandEndTime = 0;
	m_commandStartTime = 0;
	m_isObeyCommand = FALSE;
	m_isWaitCommandFinish = FALSE;
	m_scriptID = 0;
	m_loopEnd = 0;
	m_loopStart = 0;
	m_repeatCommand = 0;
	m_currentCommand = 0;
	//}}AFX_DATA_INIT
	m_currMusicScriptPtr = NULL;
}

MusicScriptView::~MusicScriptView()
{
}

void MusicScriptView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MusicScriptView)
	DDX_Control(pDX, IDC_SPIN_REPEAT_COMMAND, m_spinRepeatCommand);
	DDX_Control(pDX, IDC_SPIN_LOOP_START, m_spinLoopStart);
	DDX_Control(pDX, IDC_SPIN_LOOP_END, m_spinLoopEnd);
	DDX_Control(pDX, IDC_SPIN_CURRENT_MUSIC, m_spinCurrentMusic);
	DDX_Control(pDX, IDC_LIST_SAMPLE_ID, m_sampleIDList);
	DDX_Control(pDX, IDC_COMBO_SAMPLE_ID, m_comboSampleID);
	DDX_Control(pDX, IDC_COMBO_COMMAND_ARR, m_comboCommandArr);
	DDX_Text(pDX, IDC_COMMAND_END_TIME, m_commandEndTime);
	DDX_Text(pDX, IDC_COMMAND_START_TIME, m_commandStartTime);
	DDX_Check(pDX, IDC_IS_OBEY_COMMAND, m_isObeyCommand);
	DDX_Check(pDX, IDC_IS_WAIT_COMMAND_FINISH, m_isWaitCommandFinish);
	DDX_Text(pDX, IDC_SCRIPT_ID, m_scriptID);
	DDX_Text(pDX, IDC_LOOP_END, m_loopEnd);
	DDX_Text(pDX, IDC_LOOP_START, m_loopStart);
	DDX_Text(pDX, IDC_REPEAT_COMMAND, m_repeatCommand);
	DDX_Text(pDX, IDC_CURRENT_COMMAND, m_currentCommand);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MusicScriptView, CFormView)
	//{{AFX_MSG_MAP(MusicScriptView)
	ON_BN_CLICKED(IDC_ADD_MUSIC, OnAddMusic)
	ON_BN_CLICKED(IDC_EDIT_MUSIC, OnEditMusic)
	ON_LBN_SELCHANGE(IDC_LIST_SAMPLE_ID, OnSelchangeListSampleId)
	ON_BN_CLICKED(IDC_DELETE_MUSIC, OnDeleteMusic)
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	ON_BN_CLICKED(IDC_UP, OnUp)
	//}}AFX_MSG_MAP
	ON_MESSAGE(RUNTIME_SAVE_MESSAGE,OnRuntimeSave)
	ON_MESSAGE(UPDATE_DELETING_IN_WORLD,OnUpdateWorldObject)
	ON_EN_KILLFOCUS(IDC_LOOP_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LOOP_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_CURRENT_COMMAND, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_REPEAT_COMMAND, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_COMMAND_START_TIME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_COMMAND_END_TIME, OnKillfocus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MusicScriptView diagnostics

#ifdef _DEBUG
void MusicScriptView::AssertValid() const
{
	CFormView::AssertValid();
}

void MusicScriptView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MusicScriptView message handlers

void MusicScriptView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	m_spinCurrentMusic.SetBuddy(GetDlgItem(IDC_CURRENT_COMMAND));
	m_spinLoopEnd.SetBuddy(GetDlgItem(IDC_LOOP_END));
	m_spinLoopStart.SetBuddy(GetDlgItem(IDC_LOOP_START));
	m_spinRepeatCommand.SetBuddy(GetDlgItem(IDC_REPEAT_COMMAND));

	m_spinCurrentMusic.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinLoopEnd.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinLoopStart.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinRepeatCommand.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
}

CWorldConstructKitDoc* MusicScriptView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));
	return (CWorldConstructKitDoc*)m_pDocument;
}

BOOL MusicScriptView::GetMyWorld()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	m_worldID = pTreeView->GetCurrWorldID();	
	
	CWorldConstructKitDoc* doc = GetDocument();
	BOOL result = doc->m_worldMap.Lookup(m_worldID,m_world);	
  return result;
}

DWORD MusicScriptView::GetCurrMusicScriptID()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrNodeID();
}

void MusicScriptView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	UpdateData(TRUE);
	if (GetMyWorld())
	{
		DWORD id = GetCurrMusicScriptID();
		m_world.m_bgMusicScript.ScanInit(DIRECTION_FORWARD);
		for (int i = 0; i < m_world.m_bgMusicCount; i++)
		{
			m_currMusicScriptPtr = &m_world.m_bgMusicScript.NextElement(); 
			if (m_currMusicScriptPtr->m_scriptID == id)
			{
				m_scriptID = m_currMusicScriptPtr->m_scriptID;
				m_loopStart = m_currMusicScriptPtr->m_loopStart;
				m_loopEnd = m_currMusicScriptPtr->m_loopEnd;
				m_currentCommand = m_currMusicScriptPtr->m_currentCommand;
				CString sampleIdStr;
				m_world.m_bgMusicSample.ScanInit(DIRECTION_FORWARD);
				m_comboSampleID.ResetContent();
				for(int k = 0; k < m_world.m_bgMusicFileCount; k++)
				{
					MusicSample& musicSample = m_world.m_bgMusicSample.NextElement();
					sampleIdStr.Format("%d",musicSample.m_sampleID);
					m_comboSampleID.AddString(sampleIdStr);	
				}
				if (m_world.m_bgMusicFileCount == 0)
				{
  					GetDlgItem(IDC_COMBO_SAMPLE_ID)->EnableWindow(FALSE);
						GetDlgItem(IDC_REPEAT_COMMAND)->EnableWindow(FALSE);
						GetDlgItem(IDC_SPIN_REPEAT_COMMAND)->EnableWindow(FALSE);
						GetDlgItem(IDC_COMMAND_START_TIME)->EnableWindow(FALSE);
						GetDlgItem(IDC_COMMAND_END_TIME)->EnableWindow(FALSE);
						GetDlgItem(IDC_COMBO_COMMAND_ARR)->EnableWindow(FALSE);
						GetDlgItem(IDC_IS_WAIT_COMMAND_FINISH)->EnableWindow(FALSE);
						GetDlgItem(IDC_IS_OBEY_COMMAND)->EnableWindow(FALSE);
				}
				m_sampleIDList.ResetContent();
				for (int j = 0; j < m_currMusicScriptPtr->m_commandCount;j++)
				{
					sampleIdStr.Format("%d - %d",j + 1,m_currMusicScriptPtr->m_sampleID[j]);
					int indx = m_sampleIDList.AddString(sampleIdStr);
					m_sampleIDList.SetItemData(indx,j);
					m_listMap.SetAt(j,m_currMusicScriptPtr->m_sampleID[j]);
				}
				if (m_currMusicScriptPtr->m_commandCount > 0)
				{
					m_sampleIDList.SetCurSel(0);
				}
				int selIndx = m_sampleIDList.GetCurSel();
				FillMusicFileDetails(selIndx,*m_currMusicScriptPtr);
				
				UpdateData(FALSE);
				Invalidate();
				break;
			}
		}		
	}	
}

void MusicScriptView::FillMusicFileDetails(int selIndx,MusicScript& musicScript)
{
	if (selIndx != CB_ERR)
	{
		CString sampleIdStr;
		sampleIdStr.Format("%d",musicScript.m_sampleID[selIndx]);
		m_comboSampleID.SelectString(-1,sampleIdStr);
		m_comboCommandArr.SetCurSel(musicScript.m_command[selIndx]);
		m_repeatCommand = musicScript.m_repeatCommand[selIndx];
		m_commandStartTime = musicScript.m_commandStartTime[selIndx];
		m_commandEndTime = musicScript.m_commandEndTime[selIndx];
		m_isObeyCommand = musicScript.m_obeyCommand[selIndx];
		m_isWaitCommandFinish = musicScript.m_waitForCommandFinish[selIndx];
	}
	else
	{
		m_comboSampleID.SetCurSel(-1);
		m_comboCommandArr.SetCurSel(CMD_PLAY);
		m_repeatCommand = 0;
		m_commandStartTime = 0;
		m_commandEndTime = 0;
		m_isObeyCommand = FALSE;
		m_isWaitCommandFinish = FALSE;
	}
	UpdateData(FALSE);
}

void MusicScriptView::OnRuntimeSave()
{
	UpdateData(TRUE);
	if (m_currMusicScriptPtr != NULL)
	{
		m_currMusicScriptPtr->m_loopStart = m_loopStart;
		m_currMusicScriptPtr->m_loopEnd = m_loopEnd;
		m_currMusicScriptPtr->m_currentCommand = m_currentCommand;
		
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

int MusicScriptView::IsExistMusicSample(short musicSampleID)
{
	if (m_currMusicScriptPtr != NULL)
	{
		for (int i = 0 ; i < m_currMusicScriptPtr->m_commandCount;i++)
		{		
			if (m_currMusicScriptPtr->m_sampleID[i] == musicSampleID)
			{
				return i;
			}
		}
	}
	return NOT_FOUND;
}

void MusicScriptView::OnAddMusic() 
{
	UpdateData(TRUE);
	int selIndx = m_comboSampleID.GetCurSel();
	if (selIndx != CB_ERR)
	{			
		CString idText;
		m_comboSampleID.GetLBText(selIndx,idText);
    short sampleID = atoi(idText.GetBuffer(0));
		
		if (m_currMusicScriptPtr != NULL)
		{
			int indx = m_currMusicScriptPtr->m_commandCount;
			m_currMusicScriptPtr->m_sampleID.PushBack(sampleID);
			m_currMusicScriptPtr->m_command.PushBack((MusicCommandType)m_comboCommandArr.GetCurSel());
			m_currMusicScriptPtr->m_repeatCommand.PushBack(m_repeatCommand);
			m_currMusicScriptPtr->m_commandStartTime.PushBack(m_commandStartTime);
			m_currMusicScriptPtr->m_commandEndTime.PushBack(m_commandEndTime);
			m_currMusicScriptPtr->m_obeyCommand.PushBack(m_isObeyCommand ? true : false);
			m_currMusicScriptPtr->m_waitForCommandFinish.PushBack(m_isWaitCommandFinish ? true : false);

			CString listStr;
			int id = m_sampleIDList.GetCount() + 1;
			listStr.Format("%d - %d",id,sampleID);
			m_listMap.SetAt(m_currMusicScriptPtr->m_commandCount,sampleID);
			
			indx = m_sampleIDList.AddString(listStr);
			m_sampleIDList.SetItemData(indx,m_currMusicScriptPtr->m_commandCount);
			m_currMusicScriptPtr->m_commandCount++;
		}
	}
	else
	{
		MessageBox("You must Sample ID!","Error",MB_OK + MB_ICONWARNING);
	}
}

void MusicScriptView::OnEditMusic() 
{
	UpdateData(TRUE);
	int selIndx = m_comboSampleID.GetCurSel();
	if (selIndx != CB_ERR)
	{			
		CString idText;
		m_comboSampleID.GetLBText(selIndx,idText);
    short sampleID = atoi(idText.GetBuffer(0));

		int listIndx = m_sampleIDList.GetCurSel();
		int indxInArr = m_sampleIDList.GetItemData(listIndx);
		short listSampleID;
		m_listMap.Lookup(indxInArr,listSampleID);

		if ((IsExistMusicSample(sampleID)) != NOT_FOUND)
		{
			if (sampleID != listSampleID)
			{
				MessageBox("Can't update Sample ID","Error",MB_OK + MB_ICONWARNING);
			}
			else
			{
				if (m_currMusicScriptPtr != NULL)
				{
					m_currMusicScriptPtr->m_command[indxInArr] = (MusicCommandType)m_comboCommandArr.GetCurSel();
					m_currMusicScriptPtr->m_repeatCommand[indxInArr] = m_repeatCommand;
					m_currMusicScriptPtr->m_commandStartTime[indxInArr] = m_commandStartTime;
					m_currMusicScriptPtr->m_commandEndTime[indxInArr] = m_commandEndTime;
					m_currMusicScriptPtr->m_obeyCommand[indxInArr] = m_isObeyCommand ? true : false;
					m_currMusicScriptPtr->m_waitForCommandFinish[indxInArr] = m_isWaitCommandFinish ? true : false;			
				}
			}
		}		
		else
		{
			MessageBox("This Sample ID not exist!","Error",MB_OK + MB_ICONWARNING);
		}
	}
}


void MusicScriptView::OnSelchangeListSampleId() 
{
	UpdateData(TRUE);
	int indx = m_sampleIDList.GetCurSel();

	int listIndx = m_sampleIDList.GetCurSel();
	if (listIndx != CB_ERR)
	{
		int indxInArr = m_sampleIDList.GetItemData(listIndx);
		short listSampleID;
		m_listMap.Lookup(indxInArr,listSampleID);
		
		if (m_currMusicScriptPtr != NULL)
		{
			if (m_currMusicScriptPtr->m_sampleID[indxInArr] == listSampleID)
			{
				FillMusicFileDetails(indxInArr,*m_currMusicScriptPtr);
			}
		}
	}
}

void MusicScriptView::OnDeleteMusic() 
{
	int listIndx = m_sampleIDList.GetCurSel();
	if (listIndx != CB_ERR)
	{
		int indxInArr = m_sampleIDList.GetItemData(listIndx);
		short listSampleID;
		m_listMap.Lookup(indxInArr,listSampleID);
		
		if ((IsExistMusicSample(listSampleID)) != NOT_FOUND)
		{		
			if (m_currMusicScriptPtr != NULL)
			{
				if (m_currMusicScriptPtr->m_sampleID[indxInArr] == listSampleID)
				{
					m_currMusicScriptPtr->m_sampleID.RemoveByIndex(indxInArr );
					m_currMusicScriptPtr->m_command.RemoveByIndex(indxInArr);
					m_currMusicScriptPtr->m_repeatCommand.RemoveByIndex(indxInArr);
					m_currMusicScriptPtr->m_commandStartTime.RemoveByIndex(indxInArr);
					m_currMusicScriptPtr->m_commandEndTime.RemoveByIndex(indxInArr);
					m_currMusicScriptPtr->m_obeyCommand.RemoveByIndex(indxInArr);
					m_currMusicScriptPtr->m_waitForCommandFinish.RemoveByIndex(indxInArr);
					m_currMusicScriptPtr->m_commandCount--;
				}
				else
				{
					ASSERT(FALSE);
				}
			}
		}
		m_listMap.RemoveKey(indxInArr);
		m_sampleIDList.DeleteString(listIndx);
		for (int i = indxInArr; i <= m_currMusicScriptPtr->m_commandCount - 1 ;i++)
		{
			int indxOldInArr = m_sampleIDList.GetItemData(i);
			m_sampleIDList.SetItemData(i,indxOldInArr - 1);
			m_listMap.SetAt(indxOldInArr - 1,m_currMusicScriptPtr->m_sampleID[indxOldInArr - 1]);
		}
		m_sampleIDList.SetCurSel(0);
		OnSelchangeListSampleId();
	}
}

void MusicScriptView::OnUpdateWorldObject()
{
  GetMyWorld();
}

void MusicScriptView::OnDown() 
{
	int listIndx = m_sampleIDList.GetCurSel();
	if (listIndx != m_sampleIDList.GetCount() - 1)
	{
		if (m_currMusicScriptPtr != NULL)
		{
			m_currMusicScriptPtr->m_sampleID.Replace(listIndx,listIndx + 1);
			m_currMusicScriptPtr->m_command.Replace(listIndx,listIndx + 1);
			m_currMusicScriptPtr->m_repeatCommand.Replace(listIndx,listIndx + 1);
			m_currMusicScriptPtr->m_commandStartTime.Replace(listIndx,listIndx + 1);
			m_currMusicScriptPtr->m_commandEndTime.Replace(listIndx,listIndx + 1);
			m_currMusicScriptPtr->m_obeyCommand.Replace(listIndx,listIndx + 1);
			m_currMusicScriptPtr->m_waitForCommandFinish.Replace(listIndx,listIndx + 1);

			CString sampleIdStr;
			m_sampleIDList.ResetContent();
			for (int j = 0; j < m_currMusicScriptPtr->m_commandCount;j++)
			{
				sampleIdStr.Format("%d - %d",j + 1,m_currMusicScriptPtr->m_sampleID[j]);
				int indx = m_sampleIDList.AddString(sampleIdStr);
				m_sampleIDList.SetItemData(indx,j);
				m_listMap.SetAt(j,m_currMusicScriptPtr->m_sampleID[j]);
			}
			m_sampleIDList.SetCurSel(listIndx + 1);
		}	
	}
}

void MusicScriptView::OnUp() 
{
	int listIndx = m_sampleIDList.GetCurSel();
	if (listIndx != 0)
	{
		if (m_currMusicScriptPtr != NULL)
		{
			m_currMusicScriptPtr->m_sampleID.Replace(listIndx - 1,listIndx);
			m_currMusicScriptPtr->m_command.Replace(listIndx - 1,listIndx);
			m_currMusicScriptPtr->m_repeatCommand.Replace(listIndx - 1,listIndx);
			m_currMusicScriptPtr->m_commandStartTime.Replace(listIndx - 1,listIndx);
			m_currMusicScriptPtr->m_commandEndTime.Replace(listIndx - 1,listIndx);
			m_currMusicScriptPtr->m_obeyCommand.Replace(listIndx - 1,listIndx);
			m_currMusicScriptPtr->m_waitForCommandFinish.Replace(listIndx - 1,listIndx);

			CString sampleIdStr;
			m_sampleIDList.ResetContent();
			for (int j = 0; j < m_currMusicScriptPtr->m_commandCount;j++)
			{
				sampleIdStr.Format("%d - %d",j + 1,m_currMusicScriptPtr->m_sampleID[j]);
				int indx = m_sampleIDList.AddString(sampleIdStr);
				m_sampleIDList.SetItemData(indx,j);
				m_listMap.SetAt(j,m_currMusicScriptPtr->m_sampleID[j]);
			}
			m_sampleIDList.SetCurSel(listIndx - 1);
		}	
	}	
}
void MusicScriptView::OnKillfocus() 
{
	UpdateData(TRUE);	
}
