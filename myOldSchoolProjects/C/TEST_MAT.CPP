#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
void main()
{int i,a,b,d,f,k,n,t,wrong,sof;
char c,answer;
n=0;wrong=0;
for(i=1;i<11;i++)
{ clrscr();
  do {gotoxy(20,3);textcolor(15);
      cprintf("CHOOSE OPERATION ==> +,-,%,* ==>");
      scanf("%c",&c);
      clrscr();}
  while ((c!='+')&&(c!='-')&&(c!='*')&&(c!='%'));
  gotoxy(25,10);textcolor(14);
  cprintf("QUESTON %d",i);
  randomize();
  a=random(100);b=random(100);
  d=random(10);f=random(10);
  if (c=='+') t=b-a;
   else if (c=='-')t=a-b;
      else if (c=='*') t=d*f;
	   else t=d%f;
     gotoxy(10,5);textcolor(13);
     cprintf("%d",n);
     sof=0;
     while (sof<2)
     {if ((c=='+')||(c=='-')) { gotoxy(18,11);
				printf("                                       ");
				gotoxy(25,12);textcolor(15);
				cprintf("ENTER NUMBER %d%c   =%d",a,c,b);
				gotoxy(41,12);scanf("%d",&k);}
     else { gotoxy(18,11);
	    printf("                                       ");
	    gotoxy(25,12);textcolor(15);
	    cprintf("ENTER NUMBER %d%c%d=",d,c,f);
	    gotoxy(43,12);scanf("%d",&k);}
     if (t==k) break;
     else sof++;
     if (sof==1) { clrscr();
		  gotoxy(10,5);textcolor(13);
		  cprintf("%d",n);
		  gotoxy(18,11);
		  cprintf("WRONG.DO YOU WANT RETURN TO QUESTION ?");
		  gotoxy(18,24);textcolor(15);
		  cprintf("PRESS 'ESC' TO EXIT,ANY KEY TO CONTINUE");
		  answer=getch();
		  if (answer==0x1b) break; } }
  if (answer==0x1b) break;
  if (sof==0) n+=10;else if (sof==1)n+=5;
  if ((sof==0)||(sof==1)) {gotoxy(25,14);textcolor(11);
			   cprintf("CORRECT");
			   gotoxy(10,5);textcolor(13);
			   cprintf("%d",n);
			   gotoxy(18,24);textcolor(15);
			   cprintf("PRESS 'ESC' TO EXIT,ANY KEY TO CONTINUE");
			   answer=getch();
			   if (answer==0x1b) break;}
   else    {wrong++;if (wrong==5) { gotoxy(25,14);textcolor(14);
				    cprintf("GO TO LEARN");
				    getch();break;}
				    gotoxy(25,14);textcolor(14);
				    cprintf("THE CORRECT ANSWER IS %d",t);
				    gotoxy(18,24);textcolor(15);
				    cprintf("PRESS 'ESC' TO EXIT,ANY KEY TO CONTINUE");
				    answer=getch();
				    if (answer==0x1b) break; } } }
