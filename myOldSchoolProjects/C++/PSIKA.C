#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

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
(*userkbd)();
(*oldkbd)();
}

void kbd_new()
{
char scan_code;
scan_code=inportb(0x60);
if (scan_code==0x01) exit_flag=1;
}

void main()
{
long i;
clrscr();
intkbdinstall(kbd_new);
for (;;)
{
for (i=0;i<100000;i++)
{
gotoxy(35,12);
printf("%ld",i);
delay(50);
if (exit_flag) break;
}
if (exit_flag) break;
}
intkbdremove();
exit(0);
}