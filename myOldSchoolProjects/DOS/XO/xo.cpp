#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<dos.h>
void set(void);
void win(void);
void field(void);
void review(void);
void you_win(void);
void scratch(void);
void mouse_off(void);
int answer(int count);
void mouse_cursor_g(void);
void mouse_cursor_on(void);
void where(int *row,int *col);
void square(int *row,int *col);
void square_nul(int row,int col);
void mouse_vrange(int min,int max);
void mouse_hrange(int min,int max);
void line1(int row,int col,int d1,int d2);
void line2(int row,int col,int d1,int d2);
void nul(int x,int y,int x1,int y1,int k);
void krest(int x,int y,int x1,int y1,int k);
int mouse_release(int *row,int *col,int button);
int count=0;
int a[3][3]={{0,0,0},
	     {0,0,0},
	     {0,0,0}};
int sum_row[3]={0,0,0};
int sum_row1[3]={0,0,0};
int sum_col[3]={0,0,0};
int sum_col1[3]={0,0,0};
int diag1=0,diag2=0,diag11=0,diag12=0;
//----------------------main--------------------------------
int main(void)
{  int i;
   set();
   field();
   review();
   getch();
   closegraph();
   return 0;
}
//--------------------review---------------------------------
void review(void)
{
  int *row,*col,*button,st;
  mouse_cursor_on();mouse_cursor_g();
  int  control=1;
   while(control)
   {
     mouse_hrange(200,380);
     mouse_vrange(90,240);
    if((st=mouse_release(row,col,0x00))!=0)
   {
    mouse_off();
    square(row,col);
    if(a[*row][*col]==0)
    {
      where(row,col);
      count++;
      control=answer(count);
      if(control){ mouse_cursor_on();mouse_cursor_g();}
     }
    else{ mouse_cursor_on();mouse_cursor_g();}
   }
   }
}
//-----------------------answer----------------------------------
int answer(int count)
{
int b,i,j;
switch (count)
{
case 1:{if (a[1][1]==0) square_nul(1,1);
	else {randomize();
	      b=random(3);
	      if(b==0) square_nul(0,0);
	      else if(b==1)square_nul(0,2);
		   else if(b==2)square_nul(2,0);
			else square_nul(2,2);}
	  return(1);}
case 2:{for(i=0;i<3;i++)
	if(sum_row[i]==2)
	   for(j=0;j<3;j++)if(a[i][j]==0){square_nul(i,j);return(1);}
	for(j=0;j<3;j++)
	  if(sum_col[j]==2)
	   for(i=0;i<3;i++)if(a[i][j]==0){square_nul(i,j);return(1);}
        if (diag1==2)
           for(i=0,j=0;i<3;i++,j++)if(a[i][j]==0){square_nul(i,j);return(1);}
        if (diag2==2)
           for(i=0,j=2;i<3;i++,j--)if(a[i][j]==0){square_nul(i,j);return(1);}

        if(diag11==2)
          for(i=0,j=0;i<3;i++,j++)if(a[i][j]==0){square_nul(i,j);return(1);}
        if(diag12==2)
          for(i=0,j=2;i<3;i++,j--)if(a[i][j]==0){square_nul(i,j);return(1);}
        for(i=0;i<3;i++)
	if(sum_row1[i]==2)
	   for(j=0;j<3;j++)if(a[i][j]==0){square_nul(i,j);return(1);}
        for(j=0;j<3;j++)
	if(sum_col1[j]==2)
	   for(i=0;i<3;i++)if(a[i][j]==0){square_nul(i,j);return(1);}
 }
case 3:{
       for(i=0;i<3;i++) if(sum_row[i]==3){you_win();line2(i,-1,-1,-1);return(0);}
       for(j=0;j<3;j++) if(sum_col[j]==3){you_win();line2(-1,j,-1,-1);return(0); }
       if (diag1==3) {you_win();line2(-1,-1,1,-1);return(0);}
       if( diag2==3){you_win();line2(-1,-1,-1,1);return(0);}
       if(diag11==4)
	 for(i=0,j=0;i<3;i++,j++)if(a[i][j]==0){square_nul(i,j);
						line1(-1,-1,1,-1);
						win();return(0);}
       if(diag12==4)
	  for(i=0,j=2;i<3;i++,j--)if(a[i][j]==0){square_nul(i,j);
						 line1(-1,-1,-1,1);
						 win();return(0);}
       for(i=0;i<3;i++)
	  if(sum_row1[i]==4)
	   for(j=0;j<3;j++)if(a[i][j]==0){square_nul(i,j);
					  line1(i,-1,-1,-1);
					  win();return(0);}
       for(j=0;j<3;j++)
	  if(sum_col1[j]==4)
	   for(i=0;i<3;i++)if(a[i][j]==0){square_nul(i,j);
					  line1(-1,j,-1,-1);
					  win();return(0);}

       for(i=0;i<3;i++)
	 if(sum_row[i]==2)
	   for(j=0;j<3;j++)if(a[i][j]==0){square_nul(i,j);return(1);}
       for(j=0;j<3;j++)
	 if(sum_col[j]==2)
	   for(i=0;i<3;i++)if(a[i][j]==0){square_nul(i,j);return(1);}
       if (diag1==2)
	  for(i=0,j=0;i<3;i++,j++)if(a[i][j]==0){square_nul(i,j);return(1);}
       if (diag2==2)
	  for(i=0,j=2;i<3;i++,j--)if(a[i][j]==0){square_nul(i,j);return(1);}
       }
case 4:{
       for(i=0;i<3;i++) if(sum_row[i]==3){you_win();line2(i,-1,-1,-1);return(0);}
       for(j=0;j<3;j++) if(sum_col[j]==3){you_win();line2(-1,j,-1,-1);return(0); }
       if (diag1==3){you_win();line2(-1,-1,1,-1);return(0);}
       if(diag2==3){you_win();line2(-1,-1,-1,1);return(0);}

       if(diag11==4)
       for(i=0,j=0;i<3;i++,j++)if(a[i][j]==0){square_nul(i,j);
					      line1(-1,-1,1,-1);
					      win();return(0);}
       if(diag12==4)
       for(i=0,j=2;i<3;i++,j--)if(a[i][j]==0){square_nul(i,j);
					      line1(-1,-1,-1,1);
					      win();return(0);}
       for(i=0;i<3;i++)
	  if(sum_row1[i]==4)
	   for(j=0;j<3;j++)if(a[i][j]==0){square_nul(i,j);
					  line1(i,-1,-1,-1);
					  win();return(0);}
      for(j=0;j<3;j++)
	  if(sum_col1[j]==4)
	   for(i=0;i<3;i++)if(a[i][j]==0){square_nul(i,j);
					  line1(-1,j,-1,-1);
					  win();return(0);}

       for(i=0;i<3;i++)
	  if(sum_row[i]==2)
	   for(j=0;j<3;j++)if(a[i][j]==0){square_nul(i,j);return(1);}
       for(j=0;j<3;j++)
	  if(sum_col[j]==2)
	   for(i=0;i<3;i++)if(a[i][j]==0){square_nul(i,j);return(1);}
       if (diag1==2)
	for(i=0,j=0;i<3;i++,j++)if(a[i][j]==0){square_nul(i,j);return(1);}
       if (diag2==2)
       for(i=0,j=2;i<3;i++,j--)if(a[i][j]==0){square_nul(i,j);return(1);}
       for(i=0;i<3;i++)
       for(j=0;j<3;j++)
       if (a[i][j]==0) {square_nul(i,j);return(1);}
	}
default:{scratch();return(0);}

}
}                         
//----------------------line1-----------------------------
void line1(int row,int col,int d1,int d2)
{
if(row==0) {nul(200,90,260,140,1);nul(260,90,320,140,1);nul(320,90,380,140,1);}
if(row==1) {nul(200,140,260,190,1);nul(260,140,320,190,1);nul(320,140,380,190,1);}
if(row==2) {nul(200,190,260,240,1);nul(260,190,320,240,1);nul(320,190,380,240,1);}
if(col==0) {nul(200,90,260,140,1);nul(200,140,260,190,1);nul(200,190,260,240,1);}
if(col==1) {nul(260,90,320,140,1);nul(260,140,320,190,1);nul(260,190,320,240,1);}
if(col==2) {nul(320,90,380,140,1);nul(320,140,380,190,1);nul(320,190,380,240,1);}
if(d1==1)  {nul(200,90,260,140,1);nul(260,140,320,190,1);nul(320,190,380,240,1);}
if(d2==1)  {nul(320,90,380,140,1);nul(260,140,320,190,1);nul(200,190,260,240,1);}
}
//--------------------line2------------------------------------
void line2(int row,int col,int d1,int d2)
{
if(row==0) {krest(200,90,260,140,1);krest(260,90,320,140,1);krest(320,90,380,140,1);}
if(row==1) {krest(200,140,260,190,1);krest(260,140,320,190,1);krest(320,140,380,190,1);}
if(row==2) {krest(200,190,260,240,1);krest(260,190,320,240,1);krest(320,190,380,240,1);}
if(col==0) {krest(200,90,260,140,1);krest(200,140,260,190,1);krest(200,190,260,240,1);}
if(col==1) {krest(260,90,320,140,1);krest(260,140,320,190,1);krest(260,190,320,240,1);}
if(col==2) {krest(320,90,380,140,1);krest(320,140,380,190,1);krest(320,190,380,240,1);}
if(d1==1)  {krest(200,90,260,140,1);krest(260,140,320,190,1);krest(320,190,380,240,1);}
if(d2==1)  {krest(320,90,380,140,1);krest(260,140,320,190,1);krest(200,190,260,240,1);}
}

//----------------------you win---------------------------
void you_win(void)
{
setfillstyle(1,11);
fillellipse(295,50,44,15);
setcolor(5);
outtextxy(256,47," YOU WON !");
fillellipse(300,300,100,20);
outtextxy(220,297,"PRESS ANY KEY TO EXIT");
}
//-----------------scratch---------------------------------
void scratch(void)
{
setfillstyle(1,11);
fillellipse(295,50,40,15);
setcolor(5);
outtextxy(259,47," SCRATCH.");
fillellipse(300,300,100,20);
outtextxy(220,297,"PRESS ANY KEY TO EXIT");
}
//---------------------win------------------------------------------
void win(void)
{
setfillstyle(1,11);
fillellipse(295,50,40,15);
setcolor(5);
outtextxy(263,47," I WON !");
fillellipse(300,300,100,20);
outtextxy(220,297,"PRESS ANY KEY TO EXIT");
}
//------------------square_nul-------------------------------------
void square_nul(int row,int col)
{
if(col==0&&row==0){nul(200,90,260,140,0);a[row][col]=2;}
if(col==1&&row==0){nul(260,90,320,140,0);a[row][col]=2;}
if(col==2&&row==0){nul(320,90,380,140,0);a[row][col]=2;}
if(col==0&&row==1){nul(200,140,260,190,0);a[row][col]=2;}
if(col==1&&row==1){nul(260,140,320,190,0);a[row][col]=2;}
if(col==2&&row==1){nul(320,140,380,190,0);a[row][col]=2;}
if(col==0&&row==2){nul(200,190,260,240,0);a[row][col]=2;}
if(col==1&&row==2){nul(260,190,320,240,0);a[row][col]=2;}
if(col==2&&row==2){nul(320,190,380,240,0);a[row][col]=2;}
sum_row1[row]+=a[row][col];
sum_col1[col]+=a[row][col];
if(row+col==2) diag12+=a[row][col];
if(row==col)diag11+=a[row][col];
}
//------------------------set graphica------------------------------
void set(void)
{
 int gdriver = VGA, gmode =EGAHI, errorcode;
   initgraph(&gdriver, &gmode, "a:\\bgi");
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1); /* terminate with an error code */
   }
   cleardevice();
}
//------------------draw field---------------------------
void field(void)
{
   int i,j;
   setbkcolor(3);
   for(i=0;i<150;i+=50)
   for(j=0;j<180;j+=60)
    {setcolor(1); bar3d(200+j,90+i, 260+j,140+i, 10, 1);}
    setfillstyle(1, 1); bar(200,90,380,240);setcolor(3);
    for(i=0;i<120;i+=60) line(260+i,90,260+i,240);
    for(i=0;i<100;i+=50) line(200,140+i,380,140+i);
}
//-----------------square pressed----------------------------
void square(int *row,int *col)
{
if(*col>=200&&*col<=260&&*row>=90&&*row<=140) {*row=0;*col=0;}
if(*col>=260&&*col<=320&&*row>=90&&*row<=140) {*row=0;*col=1;}
if(*col>=320&&*col<=380&&*row>=90&&*row<=140) {*row=0;*col=2;}
if(*col>=200&&*col<=260&&*row>=140&&*row<=190){*row=1;*col=0;}
if(*col>=260&&*col<=320&&*row>=140&&*row<=190){*row=1;*col=1;}
if(*col>=320&&*col<=380&&*row>=140&&*row<=190){*row=1;*col=2;}
if(*col>=200&&*col<=260&&*row>=190&&*row<=240){*row=2;*col=0;}
if(*col>=260&&*col<=320&&*row>=190&&*row<=240){*row=2;*col=1;}
if(*col>=320&&*col<=380&&*row>=190&&*row<=240){*row=2;*col=2;}
}
//--------------------where pressed--------------------------
 void where(int *row,int *col)
   {
   if(*col==0&&*row==0){krest(200,90,260,140,0);a[*row][*col]=1;}
   if(*col==1&&*row==0){krest(260,90,320,140,0);a[*row][*col]=1;}
   if(*col==2&&*row==0){krest(320,90,380,140,0);a[*row][*col]=1;}
   if(*col==0&&*row==1){krest(200,140,260,190,0);a[*row][*col]=1;}
   if(*col==1&&*row==1){krest(260,140,320,190,0);a[*row][*col]=1;}
   if(*col==2&&*row==1){krest(320,140,380,190,0);a[*row][*col]=1;}
   if(*col==0&&*row==2){krest(200,190,260,240,0);a[*row][*col]=1;}
   if(*col==1&&*row==2){krest(260,190,320,240,0);a[*row][*col]=1;}
   if(*col==2&&*row==2){krest(320,190,380,240,0);a[*row][*col]=1;}
   sum_row[*row]+=a[*row][*col];
   sum_col[*col]+=a[*row][*col];
   if(*row+*col==2) diag2+=a[*row][*col];
   if(*row==*col)diag1+=a[*row][*col];
    }
//--------------------------nul----------------------------
void nul(int x,int y,int x1,int y1,int k)
{
if(k==0) setfillstyle(1, 15);
else setfillstyle(1,11);
bar(x+1,y+1,x1-1,y1-1);
setcolor(1);
line(x1,y,x1,y1);
line(x,y,x1,y);
line(x,y,x,y1);
line(x,y1,x1,y1);
setcolor(5);
ellipse((x+x1)/2,(y+y1)/2,0,360,15,20);
ellipse((x+x1)/2,(y+y1)/2,0,360,14,19);
}
//----------------------krest----------------------------
void krest(int x,int y,int x1,int y1,int k)
{
if(k==0)setfillstyle(1,15);
else setfillstyle(1,11);
bar(x+1,y+1,x1-1,y1-1);
setcolor(1);
line(x1,y,x1,y1);
line(x,y,x1,y);
line(x,y1,x1,y1);
line(x,y,x,y1);
setcolor(5);
line(x+14,y+6,x1-14,y1-6);
line(x+15,y+6,x1-15,y1-6);
line(x+16,y+6,x1-16,y1-6);
line(x1-16,y+6,x+16,y1-6);
line(x1-15,y+6,x+15,y1-6);
line(x1-14,y+6,x+14,y1-6);
}
//---------------------mouse off---------------------------------
void mouse_off(void)
{
 union REGS ireg;
 ireg.x.ax=0x02;
 int86(0x33,&ireg,&ireg);
}
//---------------------mouse_on--------------------------------
void mouse_cursor_on(void)
{
union REGS ireg;
ireg.x.ax=0x01;
int86(0x33,&ireg,&ireg);
}
//--------------mouse_cursor_g-----------------------------
void mouse_cursor_g(void)
{
static unsigned int mask[]=
{
0x3ff,0x1ff,0x0fff,0x7ff,0x3ff,0x1ff,0xff,0x7f,
0x3f,0x1f,0x1ff,0x10ff,0x30ff,0xf87f,0xf87f,0xfc3f,
0x00,0x4000,0x6000,0x7000,0x7800,0x7c00,0x7e00,0x7f00,
0x7f80,0x78c0,0x7c00,0x4600,0x0600,0x0300,0x300,0x0180};
union REGS ireg;
struct SREGS s;
segread(&s);
s.es=s.ds;
ireg.x.ax=0x09;
ireg.x.bx=0x01;
ireg.x.cx=0x01;
ireg.x.dx=(unsigned)mask;
int86x(0x33,&ireg,&ireg,&s);
}
//---------------------mouse release-----------------------------------
int mouse_release(int *row,int *col,int button)
{
union REGS ireg,outregs;
ireg.x.ax=0x06;ireg.x.bx=button;
int86(0x33,&ireg,&outregs);
*col=outregs.x.cx;
*row=outregs.x.dx;
return(outregs.x.bx);
}
//---------------mouse_vrange---------------
void mouse_vrange(int min,int max)
{
union REGS ireg;
ireg.x.ax=0x08;
ireg.x.cx=min;
ireg.x.dx=max;
int86(0x33,&ireg,&ireg);
}
//----------------mouse_hrange-------------
void mouse_hrange(int min,int max)
{
union REGS ireg;
ireg.x.ax=0x07;
ireg.x.cx=min;
ireg.x.dx=max;
int86(0x33,&ireg,&ireg);
}

