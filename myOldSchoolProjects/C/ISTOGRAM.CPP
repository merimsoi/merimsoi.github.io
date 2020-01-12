#include<stdio.h>
#include<conio.h>
main()
{ int a[20];
int i,j,n,l,m;
float k;
clrscr();
printf("\nENTER NUMBER OF STUDENTS ");
scanf("%d",&n);
printf("\nenter grades of students\n ");
for(i=1;i<=n;i++) scanf("%d",&a[i]);
for(i=1;i<=n;i++)
{
 for(k=1;k<=10-a[i]/10;k+=1)
  {
  for(j=1;j<=3;j++) printf(" ");
  gotoxy(wherex()-3,wherey()+1);
  }
  for(k=1;k<=a[i]/10;k+=1)
  {
  for(j=1;j<=3;j++) printf("*");
  gotoxy(wherex()-3,wherey()+1);
  }
  l=wherex()+4;
  m=wherey()-10;
  gotoxy(l,m);
}
 }