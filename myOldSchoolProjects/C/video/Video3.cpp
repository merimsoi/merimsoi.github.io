#include<mem.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#define MONO_BASE 0xB800
int main(void)
{
clrscr();
int i;
char ch;
int n=0;
void *buf[5];
for(n=0;n<3;n++)
{
buf[n]=malloc(4000);
textcolor(n+2);
textbackground(n);
for(i=0;i<25;i++)
{
gotoxy(i*n,i);
cprintf("i am writing stam shtuiot on %d screen from begining",n);
}
getch();
movedata(MONO_BASE,0,FP_SEG((char far*)buf[n]),FP_OFF((char far *)buf[n]),4000);
clrscr();
}
printf("press key 1 to return to saved screen\n");
printf("press key 2 to go to next scree\n");
printf("press key escape to exit\n");
n--;
do{
fflush(stdin);
ch=getch();
if(ch=='1'&&n==0)n=1;
if(ch=='2'&&n==2)n=1;
if(ch=='1'&&n>=0&&n<3)
{
n--;
movedata(FP_SEG((char far *)buf[n]),FP_OFF((char far*)buf[n]),MONO_BASE,0,4000);
}
if(ch=='2'&&n>=0&&n<3)
{n++;
movedata(FP_SEG((char far *)buf[n]),FP_OFF((char far*)buf[n]),MONO_BASE,0,4000);
}
}
while(ch!=27);
return 0;
}


