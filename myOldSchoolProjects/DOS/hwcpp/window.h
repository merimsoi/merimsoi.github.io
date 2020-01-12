#ifndef _Window
#define _Window
//****************************************************************************
//Class Window is abstract class to create window with coordinates x1,y1,x2,y2
//****************************************************************************
class Window
{
public:
  Window(int,int,int,int);
  virtual void ShowWindow()=0;           //virtual function to show window
  void SetColor(int);                    //set color of window
  void SetColorDraw(int);                //set color of frame
  void DrawFrame();                      //draw the frame
protected:
  int x1;                           // position of left coner
  int y1;
  int x2;                           // position of right coner
  int y2;
  int backcolor;                    // color of the window
  int color_text;                   // color of the text int window
  int color_draw;                   //color of frame in the window
};
#endif