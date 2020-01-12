#include "drag.h"
#include "shipapp.rh"
#undef max
#undef min
#define max(a, b)  (((a) > (b)) ? (a) : (b))
#define min(a, b)  (((a) < (b)) ? (a) : (b))
void FAR PASCAL ReturnHome(int X, int Y, Drag *pDrag);
#pragma argsused
void FAR PASCAL ReturnHome(int X, int Y, Drag *pDrag)
{
  if (Drag::m_event!=-1)
	 return;
	static i=0;
	i=(i+1);
	if (i>20)i=0;
	MSG msg;
	 if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				if (( msg.message == WM_TIMER))
					  return ;
				if (msg.message == WM_QUIT )
				 {
					Drag::m_event=-CM_EXIT;
					return;
				 }
				if (msg.message == WM_COMMAND &&
					 (msg.wParam==CM_STOP || msg.wParam==CM_EXIT ||
					  msg.wParam==IDM_QUICK ||
					  msg.wParam==IDM_ANIMATION ||
					  msg.wParam==IDM_SOUND))
				{
				  Drag::m_event=-(msg.wParam);
					return;
				}

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

	while (GetTickCount()-pDrag->m_Current<pDrag->AnimationSpeed)
	if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				if (( msg.message == WM_TIMER))
					  return ;
				if (msg.message == WM_QUIT )
				 {
					Drag::m_event=-CM_EXIT;
					return;
				 }
				if (msg.message == WM_COMMAND &&
					 (msg.wParam==CM_STOP || msg.wParam==CM_EXIT))
				{
				  Drag::m_event=-(msg.wParam);
					return;
				}

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

	pDrag->DragImage(TPoint(X,Y));
	pDrag->m_Current = GetTickCount();
}
//***********************************************************************
 Drag::~Drag()
 {
 }
 //***********************************************************************
 int Drag:: m_event=-1;
//************************************************************************
Drag::Drag(HWND hWnd,TPoint point,TBitmap *pBmp,TBitmap *pBmpMask)
{
 AnimationSpeed=0;
 hWndMain=hWnd;
 pBitmap=pBmp;
 IsDragging = FALSE;
 pBmImage=pBmp;
 pBmMask=pBmpMask;
 DragStart(point);

}
//*************************************************************************
void Drag::ChangeImage(TBitmap *pBmp,TBitmap *pBmpMask)
{

pBmImage=pBmp;
pBmMask=pBmpMask;
}
//*************************************************************************
Drag:: Drag(HWND hWnd,TBitmap *pBmp,TBitmap *pBmpMask)
{
 AnimationSpeed=0;
 hWndMain=hWnd;
 pBitmap=pBmp;
 IsDragging = FALSE;
 pBmImage=pBmp;
 pBmMask=pBmpMask;
}
//*************************************************************************
void Drag:: SetAnimationSpeed(int k)
{
	AnimationSpeed=k;
}
//*************************************************************************
void Drag:: Animation(TPoint P1,TPoint P2)
{
 POINT p1,p2;
 p1.x=P1.x;
 p1.y=P1.y;
 p2.x=P2.x;
 p2.y=P2.y;
 BITMAP Bitmap;
 pBmMask->GetObject(Bitmap);
 hDragPiece = (HBITMAP)*pBmImage;
 hDragMask = (HBITMAP)*pBmMask;
 SaveBackground(p1);
 ShowPiece(p1);
 m_Current = GetTickCount();
 LineDDA(p1.x, p1.y, p2.x, p2.y, LINEDDAPROC(ReturnHome),(LPARAM) this);
 RestoreBackground();
}
//**************************************************************************
void Drag:: SaveBackground(POINT& p)
{
	HDC hDC;
	BITMAP Bitmap;
	LastPoint = p;
	hDC = GetDC(hWndMain);
	pBmMask->GetObject(Bitmap);
	hSaveDC = CreateCompatibleDC(hDC);
	hOldBmp = (HBITMAP)SelectObject(hSaveDC,
	CreateCompatibleBitmap(hDC, Bitmap.bmWidth,Bitmap.bmHeight));
	BitBlt(hSaveDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight,hDC, p.x, p.y, SRCCOPY);
	ReleaseDC(hWndMain, hDC);
}
//****************************************************************************
void Drag:: RestoreBackground()
{
	HDC hDC;
	BITMAP Bitmap;
	hDC = GetDC(hWndMain);
	pBmMask->GetObject(Bitmap);
	BitBlt(hDC,
	LastPoint.x, LastPoint.y, Bitmap.bmWidth, Bitmap.bmHeight,hSaveDC, 0, 0, SRCCOPY);
	DeleteObject(SelectObject(hSaveDC, hOldBmp));
	DeleteDC(hSaveDC);
	ReleaseDC(hWndMain, hDC);
}
//**************************************************************************
void Drag:: ShowPiece(POINT& p)
{
	HBITMAP hOldBmp;
	BITMAP Bitmap;
	HDC hMemoryDC, hDC;
	hDC = GetDC(hWndMain);
	hMemoryDC = CreateCompatibleDC(hDC);
	pBmMask->GetObject(Bitmap);
	hOldBmp = (HBITMAP)SelectObject(hMemoryDC, hDragMask);
	BitBlt(hDC,
	p.x, p.y, Bitmap.bmWidth, Bitmap.bmHeight,hMemoryDC, 0, 0, SRCAND);
	SelectObject(hMemoryDC, hDragPiece);
	BitBlt(hDC,
	p.x, p.y, Bitmap.bmWidth, Bitmap.bmHeight,hMemoryDC, 0, 0, SRCINVERT);
	pBitmap->GetObject(Bitmap);
	BitBlt(hDC, 0,0,Bitmap.bmWidth, Bitmap.bmHeight,hDC,0,0, SRCCOPY);
	SelectObject(hMemoryDC, hOldBmp);
	DeleteDC(hMemoryDC);
	ReleaseDC(hWndMain, hDC);
}
//*************************************************************************
BOOL Drag:: Intersect(RECT& r1, RECT& r2)
{
	POINT p;
	p.x = r1.left;
	p.y = r1.top;
	if (PtInRect(&r2, p))return TRUE;
	p.y = r1.bottom;
	if (PtInRect(&r2, p))return TRUE;
	p.x = r1.right;
	if (PtInRect(&r2, p))return TRUE;
	p.y = r1.top;
	if (PtInRect(&r2, p))return TRUE;
	return FALSE;
}
//************************************************************************
void Drag:: UpdateScreen(POINT& p)
{
	HDC hDC, hUpdateDC, hNewSaveDC;
	HBITMAP hUOldBmp, hNewOldBmp;
	BITMAP Bitmap;
	RECT rect0, rect1, rect2;
	int Width, Height;
	pBmMask->GetObject(Bitmap);
	rect1.left = p.x;
	rect1.top = p.y;
	rect1.right = p.x + Bitmap.bmWidth;
	rect1.bottom = p.y + Bitmap.bmHeight;
	rect2.left = LastPoint.x;
	rect2.top = LastPoint.y;
	rect2.right = LastPoint.x + Bitmap.bmWidth;
	rect2.bottom = LastPoint.y + Bitmap.bmHeight;
	if (!Intersect(rect1, rect2))
		{
		RestoreBackground();
		SaveBackground(p);
		ShowPiece(p);
		return;
		}
	hDC = GetDC(hWndMain);
	hNewSaveDC = CreateCompatibleDC(hDC);
	hNewOldBmp = (HBITMAP)SelectObject(hNewSaveDC,
	CreateCompatibleBitmap(hDC, Bitmap.bmWidth, Bitmap.bmHeight));
	rect0.left = min(rect1.left, rect2.left);
	rect0.top = min(rect1.top, rect2.top);
	rect0.bottom = max(rect1.bottom, rect2.bottom);
	rect0.right = max(rect1.right, rect2.right);
	Width = rect0.right - rect0.left;
	Height = rect0.bottom - rect0.top;
	hUpdateDC = CreateCompatibleDC(hDC);
	hUOldBmp = (HBITMAP)SelectObject(hUpdateDC,CreateCompatibleBitmap(hDC, Width,Height));

	/* get new section */
	BitBlt(hUpdateDC, 0, 0, Width, Height,hDC,
	 rect0.left, rect0.top, SRCCOPY);

	/* restore old section */
	BitBlt(hUpdateDC, abs(rect0.left - rect2.left), abs(rect0.top - rect2.top),
		Bitmap.bmWidth, Bitmap.bmHeight, hSaveDC, 0, 0, SRCCOPY);

	/* save new background */
	BitBlt(hNewSaveDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight,
		hUpdateDC, abs(rect0.left - rect1.left), abs(rect0.top - rect1.top),
		SRCCOPY);

	/* blit the mask */
	DeleteObject(SelectObject(hSaveDC, hDragMask));

	BitBlt(hUpdateDC, abs(rect0.left - rect1.left), abs(rect0.top - rect1.top),
		Bitmap.bmWidth, Bitmap.bmHeight, hSaveDC, 0, 0, SRCAND);

	/* blit the piece */
	SelectObject(hSaveDC, hDragPiece);
	BitBlt(hUpdateDC, abs(rect0.left - rect1.left), abs(rect0.top - rect1.top),
		Bitmap.bmWidth, Bitmap.bmHeight, hSaveDC, 0, 0, SRCINVERT);

	/* put it on the screen */
	BitBlt(hDC,
	 rect0.left, rect0.top, Width, Height, hUpdateDC, 0, 0, SRCCOPY);

	SelectObject(hSaveDC, hOldBmp); // don't delete current bmp (hDragPiece)
	DeleteDC(hSaveDC);
	hSaveDC = hNewSaveDC;
	hOldBmp = hNewOldBmp;
	LastPoint = p;
	DeleteObject(SelectObject(hUpdateDC, hUOldBmp));
	DeleteDC(hUpdateDC);
	pBitmap->GetObject(Bitmap);
		BitBlt(hDC, 0,0,
		 Bitmap.bmWidth, Bitmap.bmHeight,
		hDC,0,0, SRCCOPY);

	ReleaseDC(hWndMain, hDC);
}
//************************************************************************
void Drag:: DragStart(POINT& point)

{
	BITMAP Bitmap;
	pBmMask->GetObject(Bitmap);
	point.x -= Bitmap.bmHeight/2;
	point.y -= Bitmap.bmHeight/2;
	hDragPiece = (HBITMAP)*pBmImage;
	hDragMask = (HBITMAP)*pBmMask;
	SaveBackground(point);
	ShowPiece(point);
	IsDragging = TRUE;
}
//************************************************************************
void Drag:: DragEnd()

{
	if (!IsDragging)	return;
	RestoreBackground();
	IsDragging = FALSE;
}
//*************************************************************************
void Drag:: DragImage(POINT& p)
{
	BITMAP Bitmap;
	pBmMask->GetObject(Bitmap);
	p.x -= Bitmap.bmHeight/2;
	p.y -= Bitmap.bmHeight/2;
	CurPoint = p;
	UpdateScreen(p);
}


