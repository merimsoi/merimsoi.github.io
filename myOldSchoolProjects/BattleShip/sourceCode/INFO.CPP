#include <owl\owlpch.h>
#pragma hdrstop
#include "shipapp.h"
#include "game.h"
#include "info.h"
DEFINE_RESPONSE_TABLE1( TInfo, TWindow )
EV_WM_ERASEBKGND,
END_RESPONSE_TABLE;
//***************************************************************************
//Function to draw the field of information that tell how many ship in "live"
// you or your opponent have
//****************************************************************************
void TInfo::Paint(TDC& dc, BOOL , TRect&)
 {
	TFont *pf=GetFont(12,FW_BOLD);
	dc.SelectObject (*pf);
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(10,2,text);
	delete pf;

  TMemoryDC memDC;
  TBitmap resBmp1(GetApplication()->GetInstance(),IDB_SHIP1);
  TBitmap resBmp2(GetApplication()->GetInstance(),IDB_SHIP2);
  TBitmap resBmp3(GetApplication()->GetInstance(),IDB_SHIP3);
  TBitmap resBmp4(GetApplication()->GetInstance(),IDB_SHIP4);
  TRect rc=GetClientRect();
  memDC.SelectObject(resBmp1);
  dc.BitBlt(15,20,resBmp1.Width(),resBmp1.Height(),memDC,0,0,SRCCOPY);

  memDC.SelectObject(resBmp2);
  dc.BitBlt(15,50,resBmp2.Width(),resBmp2.Height(),memDC,0,0,SRCCOPY);

  memDC.SelectObject(resBmp3);
  dc.BitBlt(85,20,resBmp3.Width(),resBmp3.Height(),memDC,0,0,SRCCOPY);

  memDC.SelectObject(resBmp4);
  dc.BitBlt(85,50,resBmp4.Width(),resBmp4.Height(),memDC,0,0,SRCCOPY);
  char buf[2];
  wsprintf(buf,"%d",live[0]);
  dc.TextOut(65,25,buf);

  wsprintf(buf,"%d",live[1]);
  dc.TextOut(65,55,buf);

  wsprintf(buf,"%d",live[2]);
  dc.TextOut(175,25,buf);

  wsprintf(buf,"%d",live[3]);
  dc.TextOut(175,55,buf);

  dc.RestoreObjects();

 }

//****************************************************************************
//Function to set kind of font
//****************************************************************************
 TFont * TInfo ::GetFont(int h,int w,const char * name)
{  LOGFONT  LogFont;
	 memset(&LogFont,0,sizeof(LogFont));
	 lstrcpy( LogFont.lfFaceName,name);
	 LogFont.lfHeight = h ;
	 LogFont.lfWeight=w;
			TFont *PFont = new TFont(&LogFont);

	return PFont;
}
//***************************************************************************
//Function to redraw backgrount of the field of information
//***************************************************************************
 bool TInfo::EvEraseBkgnd( HDC dc)
 {
  RECT BRect;
  ::GetClientRect(HWindow,&BRect);
  FillRect(dc,&BRect,TBrush(brs));
  DrawFrame(dc, BRect)    ;
  SelectObject(dc, brs);
	  return  true;
 }
 //**************************************************************************
 //Function to draw frame of the field of information
 //**************************************************************************
void TInfo::DrawFrame(HDC hDC, RECT& BoardRect)
{
	 int x1, y1, x2, y2;
	 POINT pArray[3];
	 HPEN hPen, hOldPen;
	 HBRUSH hOldBrush=(HBRUSH)SelectObject(hDC, GetStockObject(WHITE_BRUSH));
	 HBRUSH hNewBrush=(HBRUSH)SelectObject(hDC, GetStockObject(LTGRAY_BRUSH));
	 x1 = BoardRect.left;
	 x2 = BoardRect.right;
	 y1 = BoardRect.top;
	 y2 = BoardRect.bottom;

	 hOldPen = (HPEN)SelectObject(hDC, GetStockObject(WHITE_PEN));

	 Rectangle(hDC, x1, y1, x2, y2);
	 SelectObject(hDC, hPen = CreatePen(PS_SOLID, 1, RGB(192, 192, 192)));
	 Rectangle(hDC, x1+1, y1+1, x2-1, y2-1);
	 DeleteObject(SelectObject(hDC, GetStockObject(WHITE_PEN)));

	 pArray[0].x = x1 + 2;
	 pArray[1].y = pArray[0].y = y2 - 3;
	 pArray[2].x = pArray[1].x = x2 - 3;
	 pArray[2].y = y1 + 2;

	 Polyline(hDC, pArray, 3);
	 hPen = CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
	 SelectObject(hDC, hPen);
	 pArray[0].x = x1;
	 pArray[1].y = pArray[0].y = y2-1;
	 pArray[2].x = pArray[1].x = x2-1;
	 pArray[2].y = y1;

	 Polyline(hDC, pArray, 3);
	 pArray[1].x = pArray[0].x = x1 + 2;
	 pArray[0].y = y2 - 3;
	 pArray[2].y = pArray[1].y = y1 + 2;
	 pArray[2].x = x2 - 3;
	 Polyline(hDC, pArray, 3);
	 SelectObject(hDC, hOldBrush);
	 DeleteObject(SelectObject(hDC, hOldPen));
}

