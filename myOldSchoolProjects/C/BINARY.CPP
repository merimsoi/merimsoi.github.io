#include<stdio.h>
#include<conio.h>
main()
{clrscr();
int k,j,i,c,h=8;
i=3 ;
for(k=1;k<=9;k++)printf(" ");
for(j=1;j<=8;j++)
{
c=i%2;
printf("\b\b%d",c);
i=i/2;
}
}