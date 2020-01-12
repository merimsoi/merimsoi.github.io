// NewNodeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "NewNodeDlg.h"
#include "MyTreeView.h"
#include "engineClasses.h"
#include "WorldConstructKitDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// NewNodeDlg dialog


NewNodeDlg::NewNodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(NewNodeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(NewNodeDlg)
	m_fileName = _T("");
	m_ID = _T("");
	//}}AFX_DATA_INIT
	m_isIDEnable = TRUE;
	m_isFileNameEnable = TRUE;
}


void NewNodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(NewNodeDlg)
	DDX_Control(pDX, IDC_COMBO_SCENE_ID, m_combo_sceneID);
	DDX_Text(pDX, IDC_FILE_NAME, m_fileName);
	DDX_Text(pDX, IDC_ID, m_ID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(NewNodeDlg, CDialog)
	//{{AFX_MSG_MAP(NewNodeDlg)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NewNodeDlg message handlers


BOOL NewNodeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  SetWindowText(m_title);

  if(!m_isIDEnable && !m_isFileNameEnable)
  {
		if (!m_isCharContext)
		{
		  GetDlgItem(IDC_ID)->ShowWindow(FALSE);
		  GetDlgItem(IDC_LABEL2)->ShowWindow(FALSE);
		  GetDlgItem(IDC_LABEL)->ShowWindow(TRUE);
		  GetDlgItem(IDC_COMBO_SCENE_ID)->ShowWindow(TRUE);
		  GetDlgItem(IDC_FILE_NAME)->EnableWindow(FALSE);
		  GetDlgItem(IDC_BROWSE)->EnableWindow(FALSE);

			CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
			
		  World world;
		  CWorldConstructKitDoc* doc = STATIC_DOWNCAST(CWorldConstructKitDoc,((CWorldConstructKitApp*)AfxGetApp())->GetDocument());
		  BOOL result = doc->m_worldMap.Lookup(pTreeView->GetCurrWorldID(),world);	
			for (int i = 0 ; i < world.m_numberOfScenes; i++)
			{
				CString sceneIdStr;
				sceneIdStr.Format("%d",world.m_scenes[i].m_sceneID);
				m_combo_sceneID.AddString(sceneIdStr);			
			}
		}
		else
		{
				GetDlgItem(IDC_ID)->ShowWindow(FALSE);
				GetDlgItem(IDC_LABEL2)->ShowWindow(FALSE);
				GetDlgItem(IDC_LABEL)->ShowWindow(TRUE);
				GetDlgItem(IDC_LABEL)->SetWindowText("Character ID");
				GetDlgItem(IDC_COMBO_SCENE_ID)->ShowWindow(TRUE);
				GetDlgItem(IDC_FILE_NAME)->EnableWindow(FALSE);
				GetDlgItem(IDC_BROWSE)->EnableWindow(FALSE);
				
				CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
				
				World world;
				CWorldConstructKitDoc* doc = STATIC_DOWNCAST(CWorldConstructKitDoc,((CWorldConstructKitApp*)AfxGetApp())->GetDocument());
				BOOL result = doc->m_worldMap.Lookup(pTreeView->GetCurrWorldID(),world);	
				for (int i = 0 ; i < world.m_numberOfCharacters; i++)
				{
					CString charIdStr;
					charIdStr.Format("%d",world.m_characters[i].m_characterId);
					m_combo_sceneID.AddString(charIdStr);			
				}
		}
  }
  else
  {
	  if (!m_isIDEnable)
	  {
		  GetDlgItem(IDC_ID)->EnableWindow(FALSE);
	  }
	  if (!m_isFileNameEnable)
	  {
		  GetDlgItem(IDC_FILE_NAME)->EnableWindow(FALSE);
		  GetDlgItem(IDC_BROWSE)->EnableWindow(FALSE);
	  }
  }
  if (m_isCharInfo)
	{
		GetDlgItem(IDC_FILE_NAME_LABEL)->SetWindowText("Character name");
		GetDlgItem(IDC_BROWSE)->ShowWindow(FALSE);
	}
	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void NewNodeDlg::OnOK() 
{
	bool isClose = true;
	UpdateData(TRUE);	
	if (!m_isFileNameEnable &&
		  !m_isIDEnable)
	{		
		int indx = m_combo_sceneID.GetCurSel();
		if (indx != CB_ERR)
		{
			m_combo_sceneID.GetLBText(indx,m_comboVal);
		}		
		else
		{
			MessageBox("Value can't be empty","Error",MB_OK + MB_ICONWARNING);
			isClose = false;
		}
	}
	else
	{
		if (m_isIDEnable)
		{
			__int64	id = _atoi64(m_ID.GetBuffer(0));
			if (id < SHORT_MIN_VALUE || id > SHORT_MAX_VALUE)
			{
				MessageBox("ID is out of range","Error",MB_OK + MB_ICONWARNING);
				isClose = false;
			}
		}
		if (m_isFileNameEnable)
		{
			if (m_fileName.IsEmpty())
			{
				MessageBox("File name can't be empty","Error",MB_OK + MB_ICONWARNING);
				isClose = false;
			}
		}
	}

	if (isClose)
	{
		CDialog::OnOK();
	}	
}

void NewNodeDlg::OnBrowse() 
{
	UpdateData(TRUE);
	CFileDialog dlg(TRUE,m_defExt.GetBuffer(0));
	//set title
	dlg.m_ofn.lpstrTitle = m_openTitle.GetBuffer(0);
	
	//set filter
	dlg.m_ofn.lpstrFilter = m_filterStr;
	
	dlg.m_ofn.Flags &= ~(OFN_EXPLORER);
	if (dlg.DoModal() == IDOK)
	{     
		m_fileName = dlg.m_ofn.lpstrFile;
		int indx = m_fileName.ReverseFind('\\');
		m_fileName = m_fileName.Right(m_fileName.GetLength() - indx - 1);
		UpdateData(FALSE);
	}	
}
