#include <graphics.h>
#include <stdlib.h>
#include<dos.h>
#include <stdio.h>
#include <conio.h>
void init(void);
void ball(int,int,int,int,int);
int main(void)
{  char speed,c;int sped,a,b,bary1=5,bary2=55;
   init();
   setbkcolor(3);
   setcolor(1);
   settextstyle(1, HORIZ_DIR,4);
   outtextxy(80,20,"PLEASE CHOOSE THE SPEED");
   outtextxy(230,60,"1...SLOW");
   outtextxy(230,100,"2...MIDDLE");
   outtextxy(230,140,"3...FAST");
   settextstyle(1, HORIZ_DIR,4);
   setcolor(4);
   outtextxy(30,200,"press F10 or X for stop,P for pause");
   do{
   speed=getch();sped=speed-'0';
    }while(sped<1||sped>3);
   int midx, midy,stx,sty;
   stx=1;sty=1;
   midx=10;midy=10;

for(;;)
{
   while (!(a=kbhit()))
   {if(stx==1)midx++;
    else midx--;
    if(sty==1)midy++;
    else midy--;

    ball(midx,midy,sped,bary1,bary2);
   if(midx==630)stx*=-1;
   if(midy==5)sty*=-1;
   if(midx==5)stx*=-1;
   if(midy==450&&bary1<=midx&&bary2>=midx) sty*=-1;
   else if(midy>=450){ setcolor(4);
		       outtextxy(80,420,"DO YOU WANT CONTINUE(Y/N)");
		       do
		       {
		       c=getch();
		       if(c=='Y'||'y'){midx=10;midy=10;bary1=5;bary2=55;
		       cleardevice();}
		       if(c=='n'||c=='N')exit(0);
		       }while(c!='y'&&c!='n'&&c!='Y'&&c!='N');
		       }
   }
   a=getch();
   if(a=='x'||a=='X')exit(0);
   if(a=='p'||a=='P')while(1)
		      {
			while(!(b=kbhit()))
			{setfillstyle(7,14);
			setcolor(14);
			circle(midx, midy,10);
			floodfill(midx,midy,14);
			delay(1); }
			b=getch();
			if(b=='p'||b=='P'){setfillstyle(1,3);
					   setcolor(3);
					   circle(midx,midy,10);
					   floodfill(midx,midy,3);
					   break;}
					   }
   if(a==77) {setfillstyle(1,3);
	      setcolor(3);
	      bar(bary1,460,bary2,475);
	      if(bary2<=630)
	      {bary1+=10;bary2+=10;}}
   if(a==75){setfillstyle(1,3);
	     setcolor(3);
	     bar(bary1,460,bary2,475);
	     if(bary1>=10)
	     {bary1-=10;bary2-=10;}}
   if(a==68)exit(0);
}
   printf("%c",a);
      /* clean up */
   getch();
   closegraph();
   return 0;
}
void init(void)
{
 /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;
   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "d:\\borlandc\\bgi");
   /* read result of initialization */
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1); /* terminate with an error code */
   }
}
void ball(int midx,int midy,int sped,int bary1,int bary2)
{

 setfillstyle(1,3);
 setcolor(3);
 floodfill(3,3,3);

 setfillstyle(7,14);
 setcolor(14);
 circle(midx, midy,10);
 floodfill(midx,midy,14);
 setfillstyle(1,15);
 setcolor(15);
 bar(bary1,460,bary2,475);
 switch(sped)
 {case 1:delay(10);break;
 case 2:delay(9);break;
 case 3:delay(8);break;
 }
setfillstyle(1,3);
setcolor(3);
circle(midx,midy,10);
floodfill(midx,midy,3);
 }
