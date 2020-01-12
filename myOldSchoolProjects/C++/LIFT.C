#include <graphics.h>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define ESC    27

static void interrupt (*oldkbd)(void);//pointer to func
static void interrupt newint9(void);//int func
static void (*userkbd)(void);
char exit_flag=0;

void intkbdinstall(void (*fptr)(void))
{
oldkbd=getvect(0x09);
userkbd=fptr;
setvect(0x09,newint9);
enable();
}

void intkbdremove(void)
{
disable();
setvect(0x09,oldkbd);
enable();
}

static void interrupt newint9()
{
(userkbd)();
(oldkbd)();
}

void kbd_new()
{
char scan_code;
scan_code=inportb(0x60);
if (scan_code==0x01) exit_flag=1;
}







void pros(int *,int,int);
void main()
{ int koma,koma_kodemet=0; char ch;
int ar[4]={50,150,250,350};//sidur komot
  /* request auto detection */
int gdriver = DETECT, gmode, errorcode;
int midx, midy, i;

/* initialize graphics and local
   variables */
initgraph(&gdriver, &gmode, "d:\\borlandc\\bgi");

/* read result of initialization */
errorcode = graphresult();
if (errorcode != grOk)  /* an error
    occurred */
{
   printf("Graphics error: %s\n", grapherrormsg(errorcode));
   printf("Press any key to halt:");
   getch();
   exit(1); /* terminate with an error
	       code */
}

printf("press the floor you want to go-ESC to exit\n");
setcolor(BLUE);
bar3d(100,ar[0],130,ar[0]+30,20,1);
for (ch=getch();ch!=ESC;ch=getch()) {
koma=ch-'0' ;
intkbdinstall(kbd_new);
if(koma>=0&&koma<4) {

pros(ar,koma,koma_kodemet);
koma_kodemet=koma; }


intkbdremove();
}}

void pros(int *t,int floor,int status)
{  int a,b;
bar3d(100,t[status],130,t[status]+30,20,1);
a=t[floor];b=t[status];
if (floor>status) //elevator goes up

while (a>b) {
setcolor(getbkcolor());
bar3d(100,b,130,b+30,20,1);
b+=5;
delay(100);
setcolor(BLUE);
bar3d(100,b,130,b+30,20,1);
if (exit_flag) break;
		}

else //elevator goes down
while (a<b) {
setcolor(getbkcolor());
bar3d(100,b,130,b+30,20,1);
b-=5;
delay(100);
setcolor(BLUE);
bar3d(100,b,130,b+30,20,1);
if (exit_flag) break;
	}//end of while loop
   }