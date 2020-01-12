#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<mem.h>
void drow(char);
delete_line(int,int);
void copyd(int,int);
//*************************************** MAIN *********************************
void main()
{
char ch;
clrscr();
printf("enter siman");
ch=getch();

drow(ch);
getch();

delete_line(75,5);
getch();

copyd(75,5);
getch();

}
// fill the screen with 'ot'
void drow(char ot)
{
  char far* pvideo;
  int i;
  pvideo=(char far*)MK_FP(0xB800,0);
  for(i=0;i<2000;i++)
	 {
		*pvideo++=ot;
		*pvideo++=15;
	 }
}

delete_line(int x,int y)
{
 char far *pv;
 pv=(char far *)MK_FP(0xB800,0);
 //end of line
 pv+=160*(y-1)+(x-1)*2;
 //movement to begin of line
 for(int i=0;i<=x;i++)
  {
	 *pv = ' ';
	  pv -= 2;
  }
}


void copyd(int x,int y)
{
char far *buffer;
char far *pv;
//init to 0 0
pv=(char far*)MK_FP(0xB800,0);
//from: sigment , ofset , to: take adress sigment of buf ,  put in buff , count
movedata(0xB800,160*y+x*2+2,FP_SEG((char far *)buffer),
			FP_OFF((char far*)buffer),4000-(160*y+x*2));

pv+=160*(y-1)+(x-1)*2;
for(int i=0;i<4000-160*y+x*2;i++)
{
pv+=2;
*pv=' ';
}
movedata(FP_SEG((char far*)buffer),FP_OFF((char far*)buffer),
0xB800,160*(y-1),4000-(160*y+x*2));
}