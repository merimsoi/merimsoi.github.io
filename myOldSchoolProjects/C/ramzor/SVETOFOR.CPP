#include<a:\ira\svetofor.h>
//**********************  main function   *************************************
void main()
{
int i;
graph_mode();
menu(1,3,3,3);
emp_tr();
instructions();
frame();
owner();
auto_mode();
getch();
}
//********************   automatic mode   *************************************
void auto_mode()
{
char msg[1];
int i;
close_mouse();
menu(1,3,3,3);
see_mouse();
qwer:
//********************************
cleen(118,93,200,110);
setcolor(YELLOW);
outtextxy(138,100," AUTO   ");
setcolor(8);
res=0;
avto=1;
man=0;
cleen(95,124,110,320);
int num=2;
close_mouse();
top(1);                              //   RED STABLE
mid(0);
bot(0);
see_mouse();
lock(1);
setcolor(RED);
sprintf(msg,"%d",num);
outtextxy(100,130,msg);
my_clock(10);
num--;
setcolor(RED);
sprintf(msg,"%d",num);
outtextxy(100,140,msg);
my_clock(10);
num--;
setcolor(RED);
sprintf(msg,"%d",num);
outtextxy(100,150,msg);
my_clock(10);
setcolor(8);
//************************           //   RED AND YELLOW STABLE
cleen(95,124,110,320);
num=1;
close_mouse();
mid(1);
see_mouse();
lock(5);
setcolor(YELLOW);
sprintf(msg,"%d",num);
outtextxy(100,195,msg);
num--;
my_clock(10);
setcolor(YELLOW);
sprintf(msg,"%d",num);
outtextxy(100,205,msg);
my_clock(5);
setcolor(8);
//************************
cleen(95,124,110,320);
num=2;
close_mouse();
top(0);                              //   GREEN STABLE
mid(0);
bot(1);
see_mouse();
lock(2);
setcolor(GREEN);
sprintf(msg,"%d",num);
outtextxy(100,260,msg);
my_clock(10);
num--;
setcolor(GREEN);
sprintf(msg,"%d",num);
outtextxy(100,270,msg);
my_clock(10);
num--;
setcolor(GREEN);
sprintf(msg,"%d",num);
outtextxy(100,280,msg);
my_clock(10);
setcolor(8);
//************************
cleen(95,124,110,320);
num=3;
int str=250;
for(i=1;i<4;i++)                     //   GREEN BLINKING
{
setcolor(8);
num--;
str+=10;
close_mouse();
bot(0);
see_mouse();
lock(0);
my_clock(6);
close_mouse();
bot(1);
see_mouse();
lock(2);
setcolor(LIGHTGREEN);
sprintf(msg,"%d",num);
outtextxy(100,str,msg);
my_clock(6);
}
setcolor(8);
//************************
cleen(95,124,110,320);
num=1;
close_mouse();
bot(0);                              //   YELLOW STABLE
mid(1);
lock(4);
see_mouse();
setcolor(YELLOW);
sprintf(msg,"%d",num);
outtextxy(100,195,msg);
num--;
my_clock(10);
setcolor(YELLOW);
sprintf(msg,"%d",num);
outtextxy(100,205,msg);
my_clock(5);
//************************
goto qwer;
}
//*******************  reset function   **************************************
void reset()
{
cleen(118,93,200,110);
lock(0);
close_mouse();
menu(3,1,3,3);
see_mouse();
setcolor(YELLOW);
outtextxy(135,100," RESET   ");
setcolor(8);
res=1;
avto=0;
man=0;
cleen(95,124,110,320);
top(0);
mid(0);
bot(0);
my_clock(1000);
}
//*************************  manual function  ********************************
void manual()
{
cleen(118,93,200,110);
lock(0);
close_mouse();
menu(3,3,1,3);
see_mouse();
setcolor(YELLOW);
outtextxy(132,100," MANUAL   ");
res=0;
avto=0;
man++;
cleen(95,124,110,320);
top(0);
mid(0);
bot(0);
my_clock(1000);
}
//****************  defining graphic screen mode  ****************************
void graph_mode()
{
int gdriver = DETECT, gmode, errorcode;
initgraph(&gdriver, &gmode, "a:\\ira");
errorcode = graphresult();
if (errorcode != grOk)
{
   printf("Graphics error: %s\n", grapherrormsg(errorcode));
   printf("Press any key to halt:");
   getch();
   exit(1);
}
}
//***************    empty traffic ligths  ***********************************
void emp_tr()
{
setcolor(8);
setfillstyle(1,8);
bar(120,120,200,320);
}
//********************   top color  ******************************************************
void top(int col)
{
setcolor(8);
midx = 160;
midy = 153;
xradius=23;
yradius=23;
if(col) setfillstyle(1,RED);
else setfillstyle(3,RED);
fillellipse(midx, midy, xradius, yradius);
}
//********************   middle color  *****************************************************
void mid(int col)
{
setcolor(8);
midx = 160;
midy = 220;
xradius=23;
yradius=23;
if(col) setfillstyle(1,YELLOW);
else setfillstyle(3,YELLOW);
fillellipse(midx, midy, xradius, yradius);
}
//********************   bottom color   *****************************************************
void bot(int col)
{
setcolor(8);
midx = 160;
midy = 285;
xradius=23;
yradius=23;
if(col) setfillstyle(1,GREEN);
else setfillstyle(3,GREEN);
fillellipse(midx, midy, xradius, yradius);
}
//********************  current time  *****************************************************
void my_clock(long lg)
{
long i;
char mes[10];
struct clock{
	    int hour;
	    int minute;
	    int second;
	    }my_time;
for (i=0;i<lg;i++)
{
click_mouse();
arrows();
_AH=0x2c;
geninterrupt(0x21);
my_time.hour=_CH;
my_time.minute=_CL;
my_time.second=_DH;
gotoxy(70,2);
if(my_time.hour>=10) printf("%d:",my_time.hour); else  printf("0%d:",my_time.hour);
if(my_time.minute>=10) printf("%d:",my_time.minute); else  printf("0%d:",my_time.minute);
if(my_time.second>=10) printf("%d",my_time.second); else  printf("0%d",my_time.second);

delay(100);
}
}
//***************  click mouse  **********************************************
void click_mouse()
{
  int j;
     see_mouse();
     for(j=0;j<1;j++)
   {
     _AX=0x05;
     geninterrupt(0x33);
     if((xmouse!=_CX)&&(ymouse!=_DX)) {xmouse=_CX;ymouse=_DX;}
     else goto pl;
     xmouse=_CX;
     ymouse=_DX;
     check_mouse();
  }
  pl:
 }
//*******************   check  mouse  ****************************************
void check_mouse()
{
//  auto   ****************************
if((avto==0)&&((xmouse<570)&&(xmouse>470)&&(ymouse<165)&&(ymouse>135)))  {mark=1;auto_mode();}
//  exit   **************************
if((xmouse<570)&&(xmouse>470)&&(ymouse<315)&&(ymouse>285))
   {close_mouse();menu(3,3,3,1);see_mouse();delay(100); closegraph();exit(0);}
//  reset  **************************
if((res==0)&&((xmouse<570)&&(xmouse>470)&&(ymouse<215)&&(ymouse>185)))  {mark=2;reset();}
//  manual **************************
if((man==0)&&((xmouse<570)&&(xmouse>470)&&(ymouse<265)&&(ymouse>230)))  {mark=3;manual();}


//  only for manual function ********
if((man==1)&&((xmouse<190)&&(xmouse>140)&&(ymouse<175)&&(ymouse>130)))
			   {close_mouse();top(1);mid(0);bot(0);see_mouse();}
if((man==1)&&((xmouse<190)&&(xmouse>140)&&(ymouse<240)&&(ymouse>195)))
			   {close_mouse();top(0);mid(1);bot(0);see_mouse();}
if((man==1)&&((xmouse<190)&&(xmouse>140)&&(ymouse<305)&&(ymouse>260)))
			   {close_mouse();top(0);mid(0);bot(1);see_mouse();}
}
//************************   keyboard lights   *******************************
void lock(int z)
{
outportb(0x60,0xed);
delay(7);
outportb(0x60,z);
}
//*************************  meny function   *********************************
void menu(int col1,int col2,int col3,int col4)
{
setfillstyle(1,col1);
setcolor(GREEN);
fillellipse(520,150,50,15);
setcolor(BLACK);
outtextxy(485,148,"AUTOMATIC");

setfillstyle(1,col2);
setcolor(GREEN);
fillellipse(520,200,50,15);
setcolor(BLACK);
outtextxy(503,198,"RESET");

setfillstyle(1,col3);
setcolor(GREEN);
fillellipse(520,250,50,15);
setcolor(BLACK);
outtextxy(500,248,"MANUAL");

setfillstyle(1,col4);
setcolor(GREEN);
fillellipse(520,300,50,15);
setcolor(BLACK);
outtextxy(506,298,"EXIT");

setcolor(8);
}
//********************  arrows function ( 1 )  ********************************
void arrows()
{
char arr;
while(kbhit())
{
arr=getch();
switch(arr)
{
case 'H'  : mark--;if(mark==0) mark=1;check_mark();break;
case 'P'  : mark++;if(mark==5) mark=4;check_mark();break;
case 13   :
	   switch(mark)
	    {
	    case 1 :if(avto==0) auto_mode();break;
	    case 2 :if(res ==0) reset();    break;
	    case 3 :if(man ==0) manual();   break;
	    case 4 :closegraph(); exit(0);
	    }
default  : break;
}
}
}
//*************************  arrows function ( 2 )  **************************
void check_mark()
{
switch(mark)
{
case 1 : close_mouse();menu(1,3,3,3);see_mouse();break;
case 2 : close_mouse();menu(3,1,3,3);see_mouse();break;
case 3 : close_mouse();menu(3,3,1,3);see_mouse();break;
case 4 : close_mouse();menu(3,3,3,1);see_mouse();break;
}
}
//************************  cleening function ********************************
void cleen(int x_left_top,int y_left_top,int x_right_bottom,int y_right_bottom)
{
setfillstyle(1,0);
bar(x_left_top,y_left_top,x_right_bottom,y_right_bottom);
}
//************************  frame function   *********************************
void frame()
{
setfillstyle(2,8);
bar(0,0,639,10);
bar(0,469,639,479);
bar(0,0,10,479);
bar(629,0,639,479);
}
//***********************   MY NAME !!!    ***********************************
void owner()
{
gotoxy(1,1);
printf("!!! âÉÄ âóëÅåëÜå öÖòÖéô öÖâÖãÜÑ åã ");
}
//**********************  showing a mouse  ***********************************
void see_mouse()
{
 _AX=0x01;
  geninterrupt(0x33);
}
//********************   hiding a mouse   ************************************
void close_mouse()
{
 _AX=0x02;
  geninterrupt(0x33);
}
//******************  instructions  for  user  *******************************
void instructions()
{
gotoxy(1,24);
printf("              INSTRUCTIONS:\n");
printf("            -----------------\n");
printf("  1. Use <UP> / <DOWN> arrows + <ENTER> or mouse\n     to press the operation buttons.\n");
printf("  2. After pressing 'MANUAL' button use mouse\n     to turn on and off the traffic lights.");
}
//****************************************************************************