#include"input.h"
#include"include.h"
//*************************************************************************
//The constructor of class Input.It involve the Info's constructor
//Parameters:int,int,int,int-->coordinates of window of input
//*************************************************************************
Input::Input(int x1,int y1,int x2,int y2):Info(x1,y1,x2,y2)
{
}
//*************************************************************************
//Function Input::Enter_data(long) for entering number i.d
//Parameters:long-->need for overloading function
//Return Value:long-->i.d
//*************************************************************************
long Input::Enter_data(long data)
{
 char td[30];
 _setcursortype(_NORMALCURSOR);
 while(1)
 {
  cin>>td;
  if(strlen(td)!=9) return -1;       //if not 9 numbers
  else
    for(int i=0;i<9;i++)
     if(!isdigit(td[i])) return -1;  //if not all digits
  break;
}
 data=atol(td);
 _setcursortype(_NOCURSOR);
 return data;
}
//*************************************************************************
//Function Input::Enter_Data() for entering the name,adress
//Parameters:none
//Return Value:char *-->inputed text
//*************************************************************************
char* Input::Enter_data()
{
 char *data=new char[20];
 assert(data);
 char ch;
 int x=wherex();
 int y=wherey();
 char array[30];
 ostrstream str(array,sizeof(array));
 _setcursortype(_NORMALCURSOR);
while(1)
 {
  cin.get(ch);
  if(ch!='\n')str<<ch;
  else if(str.pcount())                 //if pressed Enter before input
	     {
	      str<<ends;
	      strcpy(data,array);
	      break;
	     }
       else gotoxy(x,y);                //return to begining position
 }
 _setcursortype(_NOCURSOR);
 return data;
}
