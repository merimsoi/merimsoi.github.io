#include"info.h"
#include"include.h"
//***********************************************************************
//Constructor of Info.It involve the Window's constructor
//Parameters:int,int,int,int-->coordinates of window of message
//***********************************************************************
Info::Info(int x1,int y1,int x2,int y2):Window(x1,y1,x2,y2)
{
 message=new char[30];
 assert(message);
 message=0;             //message is empty
 x1=2;                 //init offset of the message from left coner of window
 y1=2;
}
//************************************************************************
//Destructor of Info
//************************************************************************
Info::~Info()
{
 delete message;
}
//*************************************************************************
//Function Info::ShowWindow shows window with message
//Parameters:none
//Return Value:none
//*************************************************************************
void Info::ShowWindow()
{
 Window::ShowWindow();
 gotoxy(x1,y1);
 cout<<message;
}
//***********************************************************************
//Function Info::SetMessage sets message
//Parameters:char*-->pointer to message
//Return Value:none
//***********************************************************************
void Info::SetMessage(char* mes)
{
 message=mes;
}
//***********************************************************************
//Function Info::SetOffset sets the offset of message
//Parameters:int,int-->coordinates of offset
//Return Value:none
//***********************************************************************
void Info::SetOffset(int x1,int y1)
{
 Info::x1=x1;
 Info::y1=y1;
}
