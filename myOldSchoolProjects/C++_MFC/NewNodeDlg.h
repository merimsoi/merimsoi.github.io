#if !defined(AFX_NEWNODEDLG_H__A81EE621_5609_11D6_A110_F9B6CB3B035E__INCLUDED_)
#define AFX_NEWNODEDLG_H__A81EE621_5609_11D6_A110_F9B6CB3B035E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewNodeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// NewNodeDlg dialog

class NewNodeDlg : public CDialog
{
// Construction
public:
	NewNodeDlg(CWnd* pParent = NULL);   // standard constructor
  CString m_title;
	BOOL m_isIDEnable;
	BOOL m_isFileNameEnable;
	BOOL m_isCharContext;
	BOOL m_isCharInfo;

	CString m_defExt;
	CString m_openTitle;
	CString m_filterStr;
	
// Dialog Data
	//{{AFX_DATA(NewNodeDlg)
	enum { IDD = IDD_NEW_NODE };
	CComboBox	m_combo_sceneID;
	CString	m_fileName;
	CString	m_ID;
	//}}AFX_DATA
	CString m_comboVal;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NewNodeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(NewNodeDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWNODEDLG_H__A81EE621_5609_11D6_A110_F9B6CB3B035E__INCLUDED_)
