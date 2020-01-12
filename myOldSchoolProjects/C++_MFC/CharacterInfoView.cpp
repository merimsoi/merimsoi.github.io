// CharacterInfoView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "CharacterInfoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CharacterInfoView

IMPLEMENT_DYNCREATE(CharacterInfoView, CFormView)

CharacterInfoView::CharacterInfoView()
	: CFormView(CharacterInfoView::IDD)
{
	//{{AFX_DATA_INIT(CharacterInfoView)
	m_characterId = 0;
	m_characterName = _T("");
	m_colorFile = _T("");
	m_defaultClip = 0;
	m_clipFileName = _T("");
	m_firstFrame = 0;
	m_lastFrame = 0;
	m_loopCount = 0;
	m_numPerSecond = 0;
	m_vertexFile = _T("");
	m_typeId = 0;
	//}}AFX_DATA_INIT
	m_currCharacterInfoPtr = NULL;
}

CharacterInfoView::~CharacterInfoView()
{

}

void CharacterInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CharacterInfoView)
	DDX_Control(pDX, IDC_CLIP_LIST, m_clipList);
	DDX_Text(pDX, IDC_CHARACTER_ID, m_characterId);
	DDX_Text(pDX, IDC_FILE_NAME, m_characterName);
	DDX_Text(pDX, IDC_COLOR_FILE, m_colorFile);
	DDX_Text(pDX, IDC_DEFAULT_CLIP, m_defaultClip);
	DDX_Text(pDX, IDC_CLIP_FILE_NAME, m_clipFileName);
	DDX_Text(pDX, IDC_FIRST_FRAME, m_firstFrame);
	DDX_Text(pDX, IDC_LAST_FRAME, m_lastFrame);
	DDX_Text(pDX, IDC_LOOP_COUNT, m_loopCount);
	DDX_Text(pDX, IDC_NUM_PER_SECOND, m_numPerSecond);
	DDX_Text(pDX, IDC_VERTEX_FILE, m_vertexFile);
	DDX_Text(pDX, IDC_TYPE_ID, m_typeId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CharacterInfoView, CFormView)
	//{{AFX_MSG_MAP(CharacterInfoView)
	ON_BN_CLICKED(IDC_BROWSE_FILE_NAME, OnBrowseFileName)
	ON_BN_CLICKED(IDC_BROWSE_COLOR_FILE, OnBrowseColorFile)
	ON_BN_CLICKED(IDC_BROWSE_VERTEX_FILE, OnBrowseVertexFile)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_LBN_SELCHANGE(IDC_CLIP_LIST, OnSelchangeClipList)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	ON_BN_CLICKED(IDC_UP, OnUp)
	//}}AFX_MSG_MAP
	ON_MESSAGE(RUNTIME_SAVE_MESSAGE,OnRuntimeSave)	
	ON_MESSAGE(UPDATE_DELETING_IN_WORLD,OnUpdateWorldObject)
	ON_EN_KILLFOCUS(IDC_DEFAULT_CLIP, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TYPE_ID, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_FIRST_FRAME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LAST_FRAME, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_NUM_PER_SECOND, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LOOP_COUNT, OnKillfocus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CharacterInfoView diagnostics

#ifdef _DEBUG
void CharacterInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CharacterInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CharacterInfoView message handlers
CWorldConstructKitDoc* CharacterInfoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));
	return (CWorldConstructKitDoc*)m_pDocument;
}

BOOL CharacterInfoView::GetMyWorld()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	m_worldId = pTreeView->GetCurrWorldID();	
	
	CWorldConstructKitDoc* doc = GetDocument();
	BOOL result = doc->m_worldMap.Lookup(m_worldId,m_world);	
  return result;
}


void CharacterInfoView::GetCurrFileName(CString& fileName)
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	pTreeView->GetCurrNodeFileName(fileName);
}

DWORD CharacterInfoView::GetCurrCharacterInfoID()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrNodeID();
}

void CharacterInfoView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (GetMyWorld())
	{
		CString fileName;
		DWORD id = GetCurrCharacterInfoID();

		GetCurrFileName(fileName);

		m_world.m_characters.ScanInit(DIRECTION_FORWARD);
		for (int i = 0; i < m_world.m_numberOfCharacters; i++)
		{
			m_currCharacterInfoPtr = &m_world.m_characters.NextElement(); 
			if (m_currCharacterInfoPtr->m_characterName == (CStdString)fileName &&
				  m_currCharacterInfoPtr->m_characterId == id)
			{
				m_characterId = m_currCharacterInfoPtr->m_characterId;
				m_characterName = m_currCharacterInfoPtr->m_characterName; 
				m_defaultClip = m_currCharacterInfoPtr->m_defaultClip;
			  
				m_clipList.ResetContent();
				for (int j = 0; j < m_currCharacterInfoPtr->m_clipCount;j++)
				{					
					int indx = m_clipList.AddString(m_currCharacterInfoPtr->m_fileName[j]);
					m_clipList.SetItemData(indx,j);
				}
				if (m_currCharacterInfoPtr->m_clipCount > 0)
				{
					m_clipList.SetCurSel(0);
				}
				int selIndx = m_clipList.GetCurSel();
				FillCharacterInfoDetails(selIndx,*m_currCharacterInfoPtr);

				UpdateData(FALSE);
				break;
			}		
		}
	}	
}

void CharacterInfoView::FillCharacterInfoDetails(int selIndx,CharacterInfo & characterInfo)
{
	if (selIndx != CB_ERR)
	{
		m_clipFileName = characterInfo.m_fileName[selIndx];
		m_colorFile = characterInfo.m_colorFile[selIndx];
		m_vertexFile = characterInfo.m_vertexTable[selIndx];
		m_typeId  = characterInfo.m_typeId[selIndx];
		m_firstFrame = characterInfo.m_frameStart[selIndx];
		m_lastFrame = characterInfo.m_frameEnd[selIndx];
		m_numPerSecond = characterInfo.m_framesPerSecond[selIndx];
		m_loopCount = characterInfo.m_loopCount[selIndx];
	}
	else
	{
		m_clipFileName = "";
		m_colorFile = "";
		m_vertexFile = "";
		m_typeId = 0;
		m_firstFrame = 0;
		m_lastFrame = 0;
		m_numPerSecond = 0;
		m_loopCount = 0;
	}
	UpdateData(FALSE);
}

void CharacterInfoView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();	
}

void CharacterInfoView::OnRuntimeSave()
{
	UpdateData(TRUE);
	if (m_currCharacterInfoPtr != NULL)
	{
		m_currCharacterInfoPtr->m_defaultClip = m_defaultClip;

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

void CharacterInfoView::OnUpdateWorldObject()
{
  GetMyWorld();
}

void CharacterInfoView::OnBrowseFileName() 
{
	CFileDialog dlg(TRUE,"*.md2");
	//set title
	dlg.m_ofn.lpstrTitle = "Browse file name";
	
	//set filter

	CString filterStr;
	filterStr	= ("Character files (*.md2)"); 
	filterStr += (TCHAR)NULL;
	filterStr += "*.md2";
	filterStr += (TCHAR)NULL;

	dlg.m_ofn.lpstrFilter = filterStr;
	
	dlg.m_ofn.Flags &= ~(OFN_EXPLORER);
	if (dlg.DoModal() == IDOK)
	{     
		m_clipFileName = dlg.m_ofn.lpstrFile;
		int indx = m_clipFileName.ReverseFind('\\');
		m_clipFileName = m_clipFileName.Right(m_clipFileName.GetLength() - indx - 1);
		UpdateData(FALSE);
	}	
	
}

void CharacterInfoView::OnBrowseColorFile() 
{
		CFileDialog dlg(TRUE,"*.ccd");
	//set title
	dlg.m_ofn.lpstrTitle = "Browse color file name";
	
	//set filter

	CString filterStr;
	filterStr	= ("Color files (*.ccd)"); 
	filterStr += (TCHAR)NULL;
	filterStr += "*.ccd";
	filterStr += (TCHAR)NULL;

	dlg.m_ofn.lpstrFilter = filterStr;
	
	dlg.m_ofn.Flags &= ~(OFN_EXPLORER);
	if (dlg.DoModal() == IDOK)
	{     
		m_colorFile = dlg.m_ofn.lpstrFile;
		int indx = m_colorFile.ReverseFind('\\');
		m_colorFile = m_colorFile.Right(m_colorFile.GetLength() - indx - 1);
		UpdateData(FALSE);
	}
}

void CharacterInfoView::OnBrowseVertexFile() 
{
		CFileDialog dlg(TRUE,"*.vnt");
	//set title
	dlg.m_ofn.lpstrTitle = "Browse vertex file name";
	
	//set filter

	CString filterStr;
	filterStr	= ("Vertex files (*.vnt)"); 
	filterStr += (TCHAR)NULL;
	filterStr += "*.vnt";
	filterStr += (TCHAR)NULL;

	dlg.m_ofn.lpstrFilter = filterStr;
	
	dlg.m_ofn.Flags &= ~(OFN_EXPLORER);
	if (dlg.DoModal() == IDOK)
	{     
		m_vertexFile = dlg.m_ofn.lpstrFile;
		int indx = m_vertexFile.ReverseFind('\\');
		m_vertexFile = m_vertexFile.Right(m_vertexFile.GetLength() - indx - 1);
		UpdateData(FALSE);
	}	
}

void CharacterInfoView::OnAdd() 
{
	UpdateData(TRUE);
	if (!m_clipFileName.IsEmpty())
	{			
		if (m_currCharacterInfoPtr != NULL)
		{
			int indx ;
			m_currCharacterInfoPtr->m_fileName.PushBack(m_clipFileName.GetBuffer(0));
			m_currCharacterInfoPtr->m_colorFile.PushBack(m_colorFile.GetBuffer(0));
			m_currCharacterInfoPtr->m_vertexTable.PushBack(m_vertexFile.GetBuffer(0));
			m_currCharacterInfoPtr->m_typeId.PushBack(m_typeId);
			m_currCharacterInfoPtr->m_frameStart.PushBack(m_firstFrame);
			m_currCharacterInfoPtr->m_frameEnd.PushBack(m_lastFrame);
			m_currCharacterInfoPtr->m_framesPerSecond.PushBack(m_numPerSecond);
			m_currCharacterInfoPtr->m_loopCount.PushBack(m_loopCount);
			
			indx = m_clipList.AddString(m_clipFileName);
			m_clipList.SetItemData(indx,m_currCharacterInfoPtr->m_clipCount);
			m_currCharacterInfoPtr->m_clipCount++;
		}
	}
	else
	{
		MessageBox("You must file name!","Error",MB_OK + MB_ICONWARNING);
	}	
}

void CharacterInfoView::OnEdit() 
{
	if (UpdateData(TRUE))
	{
		int listIndx = m_clipList.GetCurSel();
		if (listIndx != CB_ERR)
		{
			short clipIndx = m_clipList.GetItemData(listIndx);
			
			CStdString fileName = m_currCharacterInfoPtr->m_fileName[clipIndx];
			
			if (m_clipFileName != fileName)
			{
				MessageBox("Can't update file name","Error",MB_OK + MB_ICONWARNING);
			}
			else
			{
				if (m_currCharacterInfoPtr != NULL)
				{
					m_currCharacterInfoPtr->m_colorFile[clipIndx] = m_colorFile.GetBuffer(0);
					m_currCharacterInfoPtr->m_vertexTable[clipIndx] = m_vertexFile.GetBuffer(0);
					m_currCharacterInfoPtr->m_typeId[clipIndx] = m_typeId;
					m_currCharacterInfoPtr->m_frameStart[clipIndx] = m_firstFrame;
					m_currCharacterInfoPtr->m_frameEnd[clipIndx] = m_lastFrame;
					m_currCharacterInfoPtr->m_framesPerSecond[clipIndx] = m_numPerSecond;
					m_currCharacterInfoPtr->m_loopCount[clipIndx] = m_loopCount;
				}
			}			
		}
	}	
}

void CharacterInfoView::OnSelchangeClipList() 
{
	UpdateData(TRUE);
	int indx = m_clipList.GetCurSel();
	int indxInArr = m_clipList.GetItemData(indx);

	if (m_currCharacterInfoPtr != NULL)
	{
			FillCharacterInfoDetails(indxInArr,*m_currCharacterInfoPtr);
	}	
}

void CharacterInfoView::OnDelete() 
{
	int indx = m_clipList.GetCurSel();

	int indxInArr = m_clipList.GetItemData(indx);

		if (m_currCharacterInfoPtr != NULL)
		{
			m_currCharacterInfoPtr->m_fileName.RemoveByIndex(indxInArr);
			m_currCharacterInfoPtr->m_colorFile.RemoveByIndex(indxInArr);
			m_currCharacterInfoPtr->m_vertexTable.RemoveByIndex(indxInArr);
			m_currCharacterInfoPtr->m_typeId.RemoveByIndex(indxInArr);
			m_currCharacterInfoPtr->m_frameStart.RemoveByIndex(indxInArr);
			m_currCharacterInfoPtr->m_frameEnd.RemoveByIndex(indxInArr);
			m_currCharacterInfoPtr->m_framesPerSecond.RemoveByIndex(indxInArr);
			m_currCharacterInfoPtr->m_loopCount.RemoveByIndex(indxInArr);
			m_currCharacterInfoPtr->m_clipCount--;
		}
		
	
	m_clipList.DeleteString(indx);

	for (int i = indxInArr; i <= m_currCharacterInfoPtr->m_clipCount - 1 ;i++)
	{
		int indxOldInArr = m_clipList.GetItemData(i);
		m_clipList.SetItemData(i,indxOldInArr - 1);
	}

	m_clipList.SetCurSel(0);
	OnSelchangeClipList();	
}

void CharacterInfoView::OnDown() 
{
	int listIndx = m_clipList.GetCurSel();
	if (listIndx != m_clipList.GetCount() - 1)
	{
		if (m_currCharacterInfoPtr != NULL)
		{
  		m_currCharacterInfoPtr->m_fileName.Replace(listIndx,listIndx + 1);
			m_currCharacterInfoPtr->m_colorFile.Replace(listIndx,listIndx + 1);
			m_currCharacterInfoPtr->m_vertexTable.Replace(listIndx,listIndx + 1);
			m_currCharacterInfoPtr->m_typeId.Replace(listIndx,listIndx + 1);
			m_currCharacterInfoPtr->m_frameStart.Replace(listIndx,listIndx + 1);
			m_currCharacterInfoPtr->m_frameEnd.Replace(listIndx,listIndx + 1);
			m_currCharacterInfoPtr->m_framesPerSecond.Replace(listIndx,listIndx + 1);
			m_currCharacterInfoPtr->m_loopCount.Replace(listIndx,listIndx + 1);

			m_clipList.ResetContent();
			//fill list
			for (int j = 0; j < m_currCharacterInfoPtr->m_clipCount;j++)
			{					
				int indx = m_clipList.AddString(m_currCharacterInfoPtr->m_fileName[j]);
				m_clipList.SetItemData(indx,j);
			}
   		m_clipList.SetCurSel(listIndx + 1);
		}	
	}	
}

void CharacterInfoView::OnUp() 
{
	int listIndx = m_clipList.GetCurSel();
	if (listIndx != 0)
	{
		if (m_currCharacterInfoPtr != NULL)
		{
  		m_currCharacterInfoPtr->m_fileName.Replace(listIndx - 1,listIndx);
			m_currCharacterInfoPtr->m_colorFile.Replace(listIndx - 1,listIndx);
			m_currCharacterInfoPtr->m_vertexTable.Replace(listIndx - 1,listIndx);
			m_currCharacterInfoPtr->m_typeId.Replace(listIndx - 1,listIndx);
			m_currCharacterInfoPtr->m_frameStart.Replace(listIndx - 1,listIndx);
			m_currCharacterInfoPtr->m_frameEnd.Replace(listIndx - 1,listIndx);
			m_currCharacterInfoPtr->m_framesPerSecond.Replace(listIndx - 1,listIndx);
			m_currCharacterInfoPtr->m_loopCount.Replace(listIndx - 1,listIndx);

			m_clipList.ResetContent();
			//fill list
			for (int j = 0; j < m_currCharacterInfoPtr->m_clipCount;j++)
			{					
				int indx = m_clipList.AddString(m_currCharacterInfoPtr->m_fileName[j]);
				m_clipList.SetItemData(indx,j);
			}
			m_clipList.SetCurSel(listIndx - 1);
		}		
	}
}
void CharacterInfoView::OnKillfocus() 
{
	UpdateData(TRUE);	
}
