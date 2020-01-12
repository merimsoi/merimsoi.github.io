#include"hw2.h"
//*************************************************************************
//Function DrawFrame draws the frame of the window
//*************************************************************************
void DrawFrame(int left,int top,int right,int bottom)
 {
 int i;
 for(i=left+1;i<right;i++)
   {
   gotoxy(i,top);
   putch(205);                           //draw ออ
   gotoxy(i,bottom);
   putch(205);
   }
 for(i=top+1;i<bottom;i++)
   {
   gotoxy(left,i);
   putch(186);                           //draw บ
   gotoxy(right,i);
   putch(186);
   }
 gotoxy(left,top);
 putch(201);                             //draw ษ
 gotoxy(right,top);
 putch(187);                             //draw ป
 gotoxy(left,bottom);
 putch(200);                             //draw ศ
 gotoxy(right,bottom);
 putch(188);                             //draw ผ
 };
//***************************************************************************
//Function Create draws the menu window and print approach strings
//***************************************************************************
void Create(int left,int top,int right,int bottom,int FrameColor,int BackColor,int bar,int num_menu)
   {
      window(1,1,80,25);
      textcolor(FrameColor);
      textbackground(BackColor);
      switch(num_menu)                           //choose which menu
       {
	case 0:
	 {
	  DrawFrame(left,top,right,bottom);
	  window(left+1,top+1,right-1,bottom-1);
	  clrscr();
	  for(int i=0;i<4;i++)
	  if(i==bar){
		     textbackground(11);
		     textcolor(1);
		     cprintf("%s",menu[i]);
		     }
	  else {
		textbackground(1);
		textcolor(11);
		cprintf("%s",menu[i]);
	       }
	 break;
	 }//case 0
	case 1:
	case 2:
	case 3:
	{
	 DrawFrame(left,top,right,bottom);
	 window(left+1,top+1,right-1,bottom-1);
	 clrscr();
	 for(int i=0;i<3;i++)
	 if(i==bar){
		    textbackground(11);
		    textcolor(1);
		      switch(num_menu)
		       {
			case 1:cprintf("%s",menu2[i]);break;
			case 2:cprintf("%s",menu3[i]);break;
			case 3:cprintf("%s",menu4[i]);break;
		       } //switch
		    }  //if-then
	 else {
	       textbackground(1);
	       textcolor(11);
	       switch(num_menu)
		  {
		   case 1:cprintf("%s",menu2[i]);break;
		   case 2:cprintf("%s",menu3[i]);break;
		   case 3:cprintf("%s",menu4[i]);break;
		  }//switch
	       }//if-else
	    }//case 1,2,3
       }//switch
}
//*************************************************************************
//Function Road draws the "street"
//*************************************************************************
void Road()
{
  textcolor(14);
  for(int i=1;i<80;i++)
     {
      gotoxy(i,4);
      if(i<45||i>50)
      putch(205);                              //draw ออ
      }
  for(i=1;i<80;i++)
     {
      gotoxy(i,10);
      if(i<27||i>51){putch(196);putch(196);}   //draw ฤฤ
     }
  for(i=1;i<80;i++)
    {
     gotoxy(i,7);
     if(i<27||i>51){putch(196);putch(196);}    //draw ฤ ฤ ฤ
     i+=7;
    }
  for(i=1;i<28;i++)
    {
     gotoxy(i,14);
     putch(205);
     putch(187);                               //draw ป
     gotoxy(80-i,14);
     putch(205);
    }
   gotoxy(wherex()-2,14);
   putch(201);                                 //draw ษ
   for(i=15;i<25;i++)
    {
     gotoxy(28,i);
     putch(186);                              //draw บ
     gotoxy(52,i);
     putch(186);
    }
   for(i=15;i<25;i++)
    {
     gotoxy(40,i);                           //draw ณ
     putch(179);
     i+=3;
     }
     gotoxy(49,1);                           //draw arrows
     putch(27);
     gotoxy(47,1);
     putch(25);
     gotoxy(31,7);
     putch(26);
     gotoxy(47,10);
     putch(27);
     textcolor(9);
   DrawFrame(44,2,50,6);                    //draw frames of semaphors
   DrawFrame(27,8,33,12);
   DrawFrame(44,11,50,15);
     gotoxy(47,7);                         //draw numbers of semaphors
     putch(35);
     putch(49);
     gotoxy(30,13);
     putch(35);
     putch(50);
     gotoxy(47,16);
     putch(35);
     putch(51);
     textcolor(12);
     gotoxy(45,2);
     putch(15);
     window(1,25,80,25);                 //down-menu
     textbackground(WHITE);
     clrscr();
     textcolor(0);
     cputs(" F9-Menu F10-Exit");
}
//**************************************************************************
//Function Change_frequency change approach flags and draw window to input
//frequency
//**************************************************************************
void Change_frequency()
{
input1=1;
window(1,1,80,25);
textcolor(10);
textbackground(1);
DrawFrame(30,18,58,21);
window(31,19,57,20);
clrscr();
gotoxy(1,1);
textcolor(11);
cprintf(" Enter the frequency 1-100 (Default 50):");
}
//************************************************************************
//Function Change_count_cars changes approach flags in case of option
//"Change count of cars"
//************************************************************************
void Change_count_cars()
{
num_menu=1;
bar_menu=0;
Whitch_menu(num_menu);          //involve new menu
}
//*************************************************************************
//Function Change_system_priority changes approach flags in case of option
//"Change system priority"
//*************************************************************************
void Change_system_priority()
{
num_menu=2;
bar_menu=0;
Whitch_menu(num_menu);         //involve new menu
}
//************************************************************************
//Function Change_light changes approach flags in case of option
//"Change Lights"
//*************************************************************************
void Change_light()
{
num_menu=3;
bar_menu=0;
Whitch_menu(num_menu);         //involve new menu
}
//*************************************************************************
//Function Whitch_menu choose which menu active at this moment
//*************************************************************************
void Whitch_menu(int num)
{
 switch(num)
   {
    case 0:Create(5,19,31,24,10,1,bar_menu,num_menu);break;
    case 1:Create(30,18,43,22,10,1,bar_menu,num_menu);break;
    case 2:Create(30,18,48,22,10,1,bar_menu,num_menu);break;
    case 3:Create(30,18,44,22,10,1,bar_menu,num_menu);break;
  }
}

//**************************************************************************
//Function Clear rebuild approath part of window after cancel of menus
//**************************************************************************
void Clear()
{
textcolor(14);
textbackground(0);
window(5,17,80,24);
clrscr();
 for(int i=1;i<9;i++)
     {
      gotoxy(24,i);
      putch(186);
      gotoxy(48,i);
      putch(186);
     }
 for(i=3;i<9;i++)
     {
      gotoxy(36,i);
      putch(179);
      i+=3;
      }
  if(num_menu==1||num_menu==2||num_menu==3) //if not main menu return to main
   {
     num_menu=0;
     bar_menu=0;
     Whitch_menu(num_menu);
   }
  else num_menu=-1;
}
//***************************************************************************
//Function Road_car change approach flag and draw window to input
//new count of cars
//***************************************************************************
void Road_car()
{
input2=1;
window(1,1,80,25);
textcolor(10);
textbackground(1);
DrawFrame(40,17,70,20);
window(41,18,69,19);
clrscr();
gotoxy(1,1);
textcolor(11);
cprintf("Enter the count of cars 1-100 (Default 50):");
}
//**************************************************************************
//Function Pr_Semaphor change approach flag and draw window to input
//new priority of semaphors
//**************************************************************************
void Pr_Semaphor(void)
{
input3=1;
window(1,1,80,25);
textcolor(10);
textbackground(1);
DrawFrame(44,17,80,20);
window(45,18,79,19);
clrscr();
gotoxy(1,1);
textcolor(11);
cprintf("Enter the priority of semaphor 1-10(Default 5):");
}
//**************************************************************************
