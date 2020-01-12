#include<stdio.h>
#include<dos.h>
#include<conio.h>
void fill(char ot)
{
char far *pvideo;
int i;
pvideo=(char far*)MK_FP(0xB800,0);
for(i=0;i<2000;i++)
{
*pvideo++=ot;
*pvideo++=i;
}}
void writechar(char *tav,int atr,int row,int col)
{
char far *pvideo;
//pointer to 0  0 on normal screen and init the video memory
pvideo=(char far*)MK_FP(0xB800,0);
//formula for move in video memory
pvideo+=160*(row-1)+col*2;

for(;*tav;tav++)
{
//enter ch
*pvideo=*tav;
pvideo++;
//enter atribut
*pvideo=atr;
pvideo++;
}}
main()
{
 char ch[80];
 clrscr();
 gets(ch);
 writechar(ch,100,12,40);
}
