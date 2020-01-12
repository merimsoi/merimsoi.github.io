// TemplateFormView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "TemplateFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TemplateFormView

IMPLEMENT_DYNCREATE(TemplateFormView, CFormView)

TemplateFormView::TemplateFormView()
	: CFormView(TemplateFormView::IDD)
{
	//{{AFX_DATA_INIT(TemplateFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

TemplateFormView::~TemplateFormView()
{
}

void TemplateFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TemplateFormView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TemplateFormView, CFormView)
	//{{AFX_MSG_MAP(TemplateFormView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TemplateFormView diagnostics

#ifdef _DEBUG
void TemplateFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void TemplateFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// TemplateFormView message handlers
