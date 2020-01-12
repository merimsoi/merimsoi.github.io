#ifndef H_DRAG
#define H_DRAG
#include "master.h"
// class to drag-drop of the ships to the field of game
class Drag
{
 HDC hSaveDC;
 POINT LastPoint;
 HBITMAP hOldBmp, hDragPiece, hDragMask;
 HCURSOR hPrevCursor;
 HCURSOR hCursorNull;
 BOOL IsDragging;
 POINT StartPoint;
 POINT CurPoint;
 TBitmap *pBitmap;
 TBitmap *pBmImage;
 TBitmap *pBmMask;
 HWND hWndMain;
 TRect rect;


 public:
  static int m_event;
  time_t m_Current;
  Drag(HWND hWndMain,TPoint point,TBitmap *pBitmap,TBitmap *pBmpMask);
  Drag(HWND hWndMain,TBitmap *pBitmap,TBitmap *pBmpMask);
  ~Drag();
  void ChangeImage(TBitmap *pBmp,TBitmap *pBmpMask);
  void SaveBackground(POINT& p);
  void RestoreBackground();
  void ShowPiece(POINT& p);
  BOOL Intersect(RECT& r1, RECT& r2);
  void UpdateScreen(POINT& p);
  void DragStart(POINT& point);
  void DragEnd();
  void DragImage(POINT& p);
  void Animation(TPoint p1,TPoint p2);
  void  SetAnimationSpeed(int k);
  int AnimationSpeed;
}  ;
#endif
