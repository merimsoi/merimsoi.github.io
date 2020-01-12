// Logo class
#ifndef H_LOGO
 #define H_LOGO

//#include <bwcc.h>
//#include <owl.h>


_CLASSDEF(TLogo);
class TLogo: public TWindow
{
 public:
  HBITMAP hLogoBmp;
  TLogo(TWindow *parent):
	TWindow(parent)
	{

	}

  ~TLogo()
  {
	DeleteObject(hLogoBmp);
  }

  virtual void SetupWindow()
  {
	TWindow::SetupWindow();
	HWND hWnd = GetApplication()->MainWindow->HWindow;
	 hLogoBmp = LoadBitmap(GetApplication()->GetInstance(), "Logo");


	::SetTimer(HWindow, 1, 5000, NULL);

  }
  void Paint(TDC& hdc, BOOL /*erase*/, TRect& /*PR*/)
  {
	TMemoryDC mDc(hdc);
	HBITMAP hBitmap;
	BITMAP Bitmap;

	TBitmap  bm(hLogoBmp);
	bm.GetObject(Bitmap);
	mDc.SelectObject(bm);

  hdc.BitBlt( 0, 0, Bitmap.bmWidth, Bitmap.bmHeight,
		mDc, 0, 0, SRCCOPY);


  }
  void EvLButtonDown(UINT, TPoint& )
  {
	 delete this;
  }

  void EvRButtonDown(UINT, TPoint&)
  {
	 delete this;
  }

  void EvTimer(UINT)
  {
   delete this;
  }

DECLARE_RESPONSE_TABLE(TLogo);

};

DEFINE_RESPONSE_TABLE1(TLogo, TWindow)
  EV_WM_LBUTTONDOWN,
  EV_WM_RBUTTONDOWN,
  EV_WM_TIMER,
END_RESPONSE_TABLE;

class TFrame : public  TFrameWindow
{ public:
	  TFrame
(TWindow* Parent, const char far* title = 0,
 TWindow* clientWnd = 0, bool shrinkToClient = false, TModule* module = 0)

 :TFrameWindow
 (Parent, title ,
  clientWnd , shrinkToClient , module )
  { HBITMAP hLogoBmp ;
		hLogoBmp = ::LoadBitmap(GetApplication()->GetInstance(), "Logo");
	 BITMAP bm;
	 GetObject(hLogoBmp, sizeof(BITMAP), (LPSTR)&bm);
	 DeleteObject(hLogoBmp);
    HDC hScreenDC = GetDC(NULL);
 int W = GetDeviceCaps(hScreenDC, HORZRES)/2;///2;
 int H= GetDeviceCaps(hScreenDC, VERTRES)/2;
 ReleaseDC(NULL, hScreenDC);
	  Attr.W = bm.bmWidth+2;
	 Attr.H = bm.bmHeight+2;
	 Attr.X =W-Attr.W/2;
	  Attr.Y =H-Attr.H/2;
	 Attr.Y <0?0:Attr.Y;
    Attr.X <0?0:Attr.X;
	  Attr.Style =WS_POPUP|WS_BORDER;
  }

};
class TEntryApp : public TApplication
{
	void InitMainWindow()
	{
//	HBITMAP hLogoBmp ;

	  PTLogo Logo = new TLogo(NULL);
	  TFrame *fw=new TFrame(NULL,NULL,Logo);
		SetMainWindow( fw );
     sndPlaySound("solwini.wav",SND_ASYNC);
	}
};
#endif