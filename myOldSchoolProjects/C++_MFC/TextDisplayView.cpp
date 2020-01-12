// TextDisplayView.cpp : implementation file
//

#include "stdafx.h"
#include "WorldConstructKit.h"
#include "TextDisplayView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TextDisplayView

IMPLEMENT_DYNCREATE(TextDisplayView, CFormView)

TextDisplayView::TextDisplayView()
	: CFormView(TextDisplayView::IDD)
{
	//{{AFX_DATA_INIT(TextDisplayView)
	m_displayString = _T("");
	m_endClockValue = 0;
	m_fontName = _T("");
	m_isShowText = FALSE;
	m_startClockValue = 0;
	m_textID = 0;
	m_colorBEnd = 0;
	m_colorBStart = 0;
	m_colorgEnd = 0;
	m_colorGStart = 0;
	m_colorREnd = 0;
	m_colorRStart = 0;
	m_fontSizeEnd = 0;
	m_fontSizeStart = 0;
	m_heightEnd = 0;
	m_heightStart = 0;
	m_leftEnd = 0;
	m_leftStart = 0;
	m_topEnd = 0;
	m_topStart = 0;
	m_widthEnd = 0;
	m_widthStart = 0;
	//}}AFX_DATA_INIT
	m_currTextDisplayPtr = NULL;
}

TextDisplayView::~TextDisplayView()
{
}

void TextDisplayView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TextDisplayView)
	DDX_Control(pDX, IDC_SPIN_FONT_SIZE_START, m_spinFontSizeStart);
	DDX_Control(pDX, IDC_SPIN_FONT_SIZE_END, m_spinFontSizeEnd);
	DDX_Control(pDX, IDC_SPIN_WIDTH_REGION_START, m_widthRegionStart);
	DDX_Control(pDX, IDC_SPIN_WIDTH_REGION_END, m_spinWidthRegionEnd);
	DDX_Control(pDX, IDC_SPIN_TOP_REGION_START, m_topRegionStart);
	DDX_Control(pDX, IDC_SPIN_TOP_REGION_END, m_topRegionEnd);
	DDX_Control(pDX, IDC_SPIN_LEFT_REGION_START, m_leftRegionRight);
	DDX_Control(pDX, IDC_SPIN_LEFT_REGION_END, m_leftRegionEnd);
	DDX_Control(pDX, IDC_SPIN_HEIGHT_REGION_START, m_heightRegionStart);
	DDX_Control(pDX, IDC_SPIN_HEIGHT_REGION_END, m_spinHeightRegionEnd);
	DDX_Control(pDX, IDC_SPIN_COLOR_R_START, m_spinColorRStart);
	DDX_Control(pDX, IDC_SPIN_COLOR_R_END, m_spinColorREnd);
	DDX_Control(pDX, IDC_SPIN_COLOR_G_START, m_spinColorGStart);
	DDX_Control(pDX, IDC_SPIN_COLOR_G_END, m_spinColorGEnd);
	DDX_Control(pDX, IDC_SPIN_COLOR_B_START, m_spinColorBStart);
	DDX_Control(pDX, IDC_SPIN_COLOR_B_END, m_spinColorBEnd);
	DDX_Control(pDX, IDC_COMBO_TEXT_TYPE, m_comboTextType);
	DDX_Text(pDX, IDC_DISPLAY_STRING, m_displayString);
	DDX_Text(pDX, IDC_END_CLOCK_VALUE, m_endClockValue);
	DDX_Text(pDX, IDC_FONT_NAME, m_fontName);
	DDX_Check(pDX, IDC_IS_SHOW_TEXT, m_isShowText);
	DDX_Text(pDX, IDC_START_CLOCK_VALUE, m_startClockValue);
	DDX_Text(pDX, IDC_TEXT_ID, m_textID);
	DDX_Text(pDX, IDC_COLOR_B_END, m_colorBEnd);
	DDV_MinMaxInt(pDX, m_colorBEnd, RGB_MIN_VAL, RGB_MAX_VAL);
	DDX_Text(pDX, IDC_COLOR_B_START, m_colorBStart);
	DDV_MinMaxInt(pDX, m_colorBStart, RGB_MIN_VAL, RGB_MAX_VAL);
	DDX_Text(pDX, IDC_COLOR_G_END, m_colorgEnd);
	DDV_MinMaxInt(pDX, m_colorgEnd, RGB_MIN_VAL, RGB_MAX_VAL);
	DDX_Text(pDX, IDC_COLOR_G_START, m_colorGStart);
	DDV_MinMaxInt(pDX, m_colorGStart, RGB_MIN_VAL, RGB_MAX_VAL);
	DDX_Text(pDX, IDC_COLOR_R_END, m_colorREnd);
	DDV_MinMaxInt(pDX, m_colorREnd, RGB_MIN_VAL, RGB_MAX_VAL);
	DDX_Text(pDX, IDC_COLOR_R_START, m_colorRStart);
	DDV_MinMaxInt(pDX, m_colorRStart, RGB_MIN_VAL, RGB_MAX_VAL);
	DDX_Text(pDX, IDC_FONT_SIZE_END, m_fontSizeEnd);
	DDX_Text(pDX, IDC_FONT_SIZE_START, m_fontSizeStart);
	DDX_Text(pDX, IDC_HEIGHT_REGION_END, m_heightEnd);
	DDX_Text(pDX, IDC_HEIGHT_REGION_START, m_heightStart);
	DDX_Text(pDX, IDC_LEFT_REGION_END, m_leftEnd);
	DDX_Text(pDX, IDC_LEFT_REGION_START, m_leftStart);
	DDX_Text(pDX, IDC_TOP_REGION_END, m_topEnd);
	DDX_Text(pDX, IDC_TOP_REGION_START, m_topStart);
	DDX_Text(pDX, IDC_WIDTH_REGION_END, m_widthEnd);
	DDX_Text(pDX, IDC_WIDTH_REGION_START, m_widthStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TextDisplayView, CFormView)
	//{{AFX_MSG_MAP(TextDisplayView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE(RUNTIME_SAVE_MESSAGE,OnRuntimeSave)
	ON_MESSAGE(UPDATE_DELETING_IN_WORLD,OnUpdateWorldObject)
	ON_EN_KILLFOCUS(IDC_START_CLOCK_VALUE, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_FONT_SIZE_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_COLOR_R_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_COLOR_G_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_COLOR_B_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LEFT_REGION_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TOP_REGION_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_WIDTH_REGION_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_HEIGHT_REGION_START, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_END_CLOCK_VALUE, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_FONT_SIZE_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_COLOR_R_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_COLOR_G_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_COLOR_B_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_LEFT_REGION_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_TOP_REGION_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_WIDTH_REGION_END, OnKillfocus)
	ON_EN_KILLFOCUS(IDC_HEIGHT_REGION_END, OnKillfocus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TextDisplayView diagnostics

#ifdef _DEBUG
void TextDisplayView::AssertValid() const
{
	CFormView::AssertValid();
}

void TextDisplayView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// TextDisplayView message handlers
CWorldConstructKitDoc* TextDisplayView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldConstructKitDoc)));
	return (CWorldConstructKitDoc*)m_pDocument;
}

BOOL TextDisplayView::GetMyWorld()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	m_worldID = pTreeView->GetCurrWorldID();	
	
	CWorldConstructKitDoc* doc = GetDocument();
	BOOL result = doc->m_worldMap.Lookup(m_worldID,m_world);	
  return result;
}

DWORD TextDisplayView::GetCurrTextDisplayId()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrNodeID();
}


DWORD TextDisplayView::GetCurrSceneId()
{
	CMyTreeView* pTreeView = STATIC_DOWNCAST(CMyTreeView,((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	return pTreeView->GetCurrSceneId();
}

void TextDisplayView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (GetMyWorld())
	{
		DWORD sceneId = GetCurrSceneId();
 		DWORD id = GetCurrTextDisplayId();

		for (int i = 0 ; i < m_world.m_numberOfScenes; i++)
		{
			if (m_world.m_scenes[i].m_sceneID == sceneId)
			{				
				m_world.m_scenes[i].m_textOverlays.ScanInit(DIRECTION_FORWARD);
				for (int j = 0; j < m_world.m_scenes[i].m_textOverlayCount; j++)
				{
					m_currTextDisplayPtr = &m_world.m_scenes[i].m_textOverlays.NextElement(); 
					if (m_currTextDisplayPtr->m_textID == id)
					{
						m_comboTextType.SetCurSel(m_currTextDisplayPtr->m_textType);
						m_displayString = m_currTextDisplayPtr->m_displayString;
						m_endClockValue = m_currTextDisplayPtr->m_endClockValue;
						m_fontName = m_currTextDisplayPtr->m_fontName;
						m_isShowText = m_currTextDisplayPtr->m_showText;
						m_startClockValue = m_currTextDisplayPtr->m_startClockValue;
						m_textID = m_currTextDisplayPtr->m_textID;
						m_colorBEnd = m_currTextDisplayPtr->m_colorBEnd;
						m_colorBStart = m_currTextDisplayPtr->m_colorBStart;
						m_colorgEnd = m_currTextDisplayPtr->m_colorGEnd;
						m_colorGStart = m_currTextDisplayPtr->m_colorGStart;
						m_colorREnd = m_currTextDisplayPtr->m_colorREnd;
						m_colorRStart = m_currTextDisplayPtr->m_colorRStart;
						m_fontSizeEnd = m_currTextDisplayPtr->m_fontSizeEnd;
						m_fontSizeStart = m_currTextDisplayPtr->m_fontSizeStart;
						m_heightEnd = m_currTextDisplayPtr->m_heightRegionEnd;
						m_heightStart = m_currTextDisplayPtr->m_heightRegionStart;
						m_leftEnd = m_currTextDisplayPtr->m_leftRegionEnd;
						m_leftStart = m_currTextDisplayPtr->m_leftRegionStart;
						m_topEnd = m_currTextDisplayPtr->m_topRegionEnd;
						m_topStart = m_currTextDisplayPtr->m_topRegionStart;
						m_widthEnd = m_currTextDisplayPtr->m_widthRegionEnd;
						m_widthStart = m_currTextDisplayPtr->m_widthRegionStart;

						UpdateData(FALSE);
						break;
					}		
				}
			}
		}
	}	
}

void TextDisplayView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	m_spinColorBEnd.SetBuddy(GetDlgItem(IDC_COLOR_B_END));
	m_spinColorBStart.SetBuddy(GetDlgItem(IDC_COLOR_B_START));
	m_spinColorGEnd.SetBuddy(GetDlgItem(IDC_COLOR_G_END));
	m_spinColorGStart.SetBuddy(GetDlgItem(IDC_COLOR_G_START));
	m_spinColorREnd.SetBuddy(GetDlgItem(IDC_COLOR_R_END));
	m_spinColorRStart.SetBuddy(GetDlgItem(IDC_COLOR_R_START));
	m_spinFontSizeEnd.SetBuddy(GetDlgItem(IDC_FONT_SIZE_END));
	m_spinFontSizeStart.SetBuddy(GetDlgItem(IDC_FONT_SIZE_START));
	m_widthRegionStart.SetBuddy(GetDlgItem(IDC_WIDTH_REGION_START));
	m_spinWidthRegionEnd.SetBuddy(GetDlgItem(IDC_WIDTH_REGION_END));
	m_topRegionStart.SetBuddy(GetDlgItem(IDC_TOP_REGION_START));
	m_topRegionEnd.SetBuddy(GetDlgItem(IDC_TOP_REGION_END));
	m_leftRegionRight.SetBuddy(GetDlgItem(IDC_LEFT_REGION_START));
	m_leftRegionEnd.SetBuddy(GetDlgItem(IDC_LEFT_REGION_END));
	m_heightRegionStart.SetBuddy(GetDlgItem(IDC_HEIGHT_REGION_START));
	m_spinHeightRegionEnd.SetBuddy(GetDlgItem(IDC_HEIGHT_REGION_END));	

	m_spinColorBEnd.SetRange(RGB_MIN_VAL,RGB_MAX_VAL);
	m_spinColorBStart.SetRange(RGB_MIN_VAL,RGB_MAX_VAL);
	m_spinColorGEnd.SetRange(RGB_MIN_VAL,RGB_MAX_VAL);
	m_spinColorGStart.SetRange(RGB_MIN_VAL,RGB_MAX_VAL);
	m_spinColorREnd.SetRange(RGB_MIN_VAL,RGB_MAX_VAL);
	m_spinColorRStart.SetRange(RGB_MIN_VAL,RGB_MAX_VAL);
	m_spinFontSizeEnd.SetRange(FONT_MIN_SIZE,FONT_MAX_SIZE );
	m_spinFontSizeStart.SetRange(FONT_MIN_SIZE,FONT_MAX_SIZE);
	m_widthRegionStart.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinWidthRegionEnd.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_topRegionStart.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_topRegionEnd.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_leftRegionRight.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_leftRegionEnd.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_heightRegionStart.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);
	m_spinHeightRegionEnd.SetRange(SHORT_MIN_VALUE,SHORT_MAX_VALUE);	
}

void TextDisplayView::OnRuntimeSave()
{
	UpdateData(TRUE);
	if (m_currTextDisplayPtr != NULL)
	{
		m_currTextDisplayPtr->m_textType = (TextType)m_comboTextType.GetCurSel();
		m_currTextDisplayPtr->m_displayString =	m_displayString ;
		m_currTextDisplayPtr->m_endClockValue	= m_endClockValue ;
		m_currTextDisplayPtr->m_fontName = m_fontName ;
		m_currTextDisplayPtr->m_showText =	m_isShowText ? true : false;
		m_currTextDisplayPtr->m_startClockValue =	m_startClockValue ;
		m_currTextDisplayPtr->m_textID = m_textID ;
		m_currTextDisplayPtr->m_colorBEnd =	m_colorBEnd  ;
		m_currTextDisplayPtr->m_colorBStart =	m_colorBStart;
		m_currTextDisplayPtr->m_colorGEnd	=	m_colorgEnd ;
		m_currTextDisplayPtr->m_colorGStart	= m_colorGStart ;
		m_currTextDisplayPtr->m_colorREnd =	m_colorREnd ;
		m_currTextDisplayPtr->m_colorRStart =	m_colorRStart;
		m_currTextDisplayPtr->m_fontSizeEnd	=	m_fontSizeEnd;
		m_currTextDisplayPtr->m_fontSizeStart =	m_fontSizeStart;
		m_currTextDisplayPtr->m_heightRegionEnd =	m_heightEnd  ;
		m_currTextDisplayPtr->m_heightRegionStart	=	m_heightStart;
		m_currTextDisplayPtr->m_leftRegionEnd	=	m_leftEnd ;
		m_currTextDisplayPtr->m_leftRegionStart =	m_leftStart;
		m_currTextDisplayPtr->m_topRegionEnd = m_topEnd ;
		m_currTextDisplayPtr->m_topRegionStart = m_topStart;
		m_currTextDisplayPtr->m_widthRegionEnd = m_widthEnd;
		m_currTextDisplayPtr->m_widthRegionStart =	m_widthStart;

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

void TextDisplayView::OnUpdateWorldObject()
{
  GetMyWorld();
}

void TextDisplayView::OnKillfocus() 
{
	UpdateData(TRUE);	
}
