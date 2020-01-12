#include"window.h"
#include"include.h"
//*************************************************************************
//Constructor of Window.It init the coordinates,color of window,color of
//frame and text
//Parameters:int,int,int,int-->coordinates of window 
//*************************************************************************
Window::Window(int x1,int y1,int x2,int y2)
{
 Window::x1=x1;
 Window::y1=y1;
 Window::x2=x2;
 Window::y2=y2;
 backcolor=3;
 color_draw=1;
 color_text=15;
}
//*************************************************************************
//Function Window::ShowWindow shows the window
//Parameters:none
//Return Value:none
//*************************************************************************
void Window::ShowWindow()
{
 _setcursortype(_NOCURSOR);
 window(x1,y1,x2,y2);
 textbackground(backcolor);
 clrscr();
 textcolor(color_draw);
 window(1,1,80,24);
 DrawFrame();
 window(x1,y1,x2,y2);
 textcolor(color_text);
}
//**************************************************************************
//Function Window::SetColor set the color of window
//Parameters:int-->color
//Return Value:none
//**************************************************************************
void Window::SetColor(int color)
{
 backcolor=color;
}
//**************************************************************************
//Function Window::SetColorDraw sets the color of frame of window
//Parameters:int-->color
//Return Value:none
//**************************************************************************
void Window::SetColorDraw(int color)
{
 color_draw=color;
}
//**************************************************************************
//Function Window::DrawFrame draw the frame of window
//Parameters:none
//Return Value:none
//**************************************************************************
void Window::DrawFrame()
 {
 int i;
 for(i=x1+1;i<x2;i++)
   {
   gotoxy(i,y1);
   putch(205);                           //draw ออ
   gotoxy(i,y2);
   putch(205);
   }
 for(i=y1+1;i<y2;i++)
   {
   gotoxy(x1,i);
   putch(186);                           //draw บ
   gotoxy(x2,i);
   putch(186);
   }
 gotoxy(x1,y1);
 putch(201);                             //draw ษ
 gotoxy(x2,y1);
 putch(187);                             //draw ป
 gotoxy(x1,y2);
 putch(200);                             //draw ศ
 gotoxy(x2,y2);
 putch(188);                             //draw ผ
 }
