#include<stdio.h>
#include<dos.h>
void main()
{
union REGS rg;
for(;;)
{
rg.h.ah=0;
int86(0x16,&rg,&rg);
printf("\nscan=%x ascii=%x\n",rg.h.ah,rg.h.al);
if (rg.h.ah==1)break;
}}