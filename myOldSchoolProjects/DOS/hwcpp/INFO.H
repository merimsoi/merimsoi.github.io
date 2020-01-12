#include"window.h"
#ifndef _Info
#define _Info
//***************************************************************************
//Class Info is inherited from Window.Ability show the message in the window
//***************************************************************************
class Info:public Window
{
public:
 Info(int,int,int,int);
 ~Info();
 void ShowWindow();        //show window with message
 void SetMessage(char*);   //set message to window
 void SetOffset(int,int);  //set offset from left coner
private:
 char *message;            //pointer to message
 int x1;                   //offset for message from left coner of window
 int y1;
};
#endif