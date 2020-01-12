#if !defined(AFX_TEMPLATEFORMVIEW_H__3FC67FE2_5526_11D6_A110_D49EFE6A6D5A__INCLUDED_)
#define AFX_TEMPLATEFORMVIEW_H__3FC67FE2_5526_11D6_A110_D49EFE6A6D5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TemplateFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TemplateFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class TemplateFormView : public CFormView
{
protected:
	TemplateFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(TemplateFormView)

// Form Data
public:
	//{{AFX_DATA(TemplateFormView)
	enum { IDD = IDD_EMPTY_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TemplateFormView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~TemplateFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(TemplateFormView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEMPLATEFORMVIEW_H__3FC67FE2_5526_11D6_A110_D49EFE6A6D5A__INCLUDED_)
