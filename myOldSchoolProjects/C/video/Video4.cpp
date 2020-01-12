#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<mem.h>
void drow(char);
delete_line(int,int);
void copyd(int,int);
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

}
void drow(char ot)
{
char far* pvideo;
int i;
pvideo=(char far*)MK_FP(0xB800,0);
for(i=0;i<2000;i++)
{
*pvideo++=ot;
*pvideo++=15;
}}
delete_line(int x,int y)
{
char far *pvideo;
char far *pnew;
pvideo=(char far *)MK_FP(0xB800,0);
int i,delta;
delta=160*(y-1)+(x-1)*2;
pvideo+=delta;
pnew=pvideo;
for(i=x;i<=80;i++)
{*pvideo++=0x20;
pvideo++;
}
getch();
for(i=delta;i<4000;i++)
*pnew++=*pvideo++;
}
