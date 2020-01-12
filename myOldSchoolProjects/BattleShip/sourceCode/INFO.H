#ifndef  _Info        // Sentry, use file only if it's not already included.
#define _Info
#include <owl\owlpch.h>
#pragma hdrstop
#include "drag.h"
#include "shipapp.rh" // Definition of all resources.
#include "view.h"
class TInfo : public TWindow
{
 HBRUSH brs;
 char text[20];
 public:

 TInfo(TWindow* parent,int id, const char far* title, int x, int y, int w, int h)
		 :TWindow(parent)
			 {
			 Attr.X=x;              //set left corner of field of information
			 Attr.Y=y;
			 Attr.W=w;             //set width of field of information
			 Attr.H=h;             //set hight of field of information
			 lstrcpy(text,title);
			Attr.Style|=WS_CLIPCHILDREN;
			 for(int i=0;i<4;i++) live[i]=0;
			 };
 int live[4];
 void Paint(TDC& dc, BOOL erase, TRect&);
 bool EvEraseBkgnd( HDC dc);
 TFont * GetFont(int h=12,int=FW_BOLD,const char * a="Helv");
 void DrawFrame(HDC, RECT&);
 DECLARE_RESPONSE_TABLE( TInfo);
};
#endif _Info
