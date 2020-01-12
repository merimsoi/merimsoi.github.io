#include<stdio.h>
#include<dos.h>
#include<conio.h>
#include<math.h>
void fill(char ot)
{
 char far *pvideo;
 int i;
 pvideo=(char far*)MK_FP(0xB800,0);
  for(i=0;i<2000;i++)
	{
	  *pvideo++=ot;
	  *pvideo++=i;
	}
}
void write(int color,int row1,int col1,int row2,int col2,char ch)
{
int i,j;
char far *pvideo;
pvideo=(char far*)MK_FP(0xB800,0);
//begin pos. of rect
pvideo+=160*row1+col1*2;
//for rows
for(i=0;i<abs(row2-row1);i++)
 {
  //for cols
  for(j=0;j<abs(col2-col1);j++)
	 {
	  *pvideo++=ch;
	  *pvideo++=color;
	 }
	//return to begin of rect
	pvideo+=160-((col2-col1)*2);
  }
 }
//***************************************  MAIN ********************************
void main()
{
char ch;int row1,row2,col1,col2,color;
clrscr();
printf("Enter color of letter:");
scanf("%d",&color);
printf("Enter row1:");
scanf("%d",&row1);
printf("Enter col1:");
scanf("%d",&col1);
printf("Enter row2:");
scanf("%d",&row2);
printf("Enter col2:");
scanf("%d",&col2);
printf("Enter letter:");
fflush(stdin);
scanf("%c",&ch);
clrscr();
write(color,row1,col1,row2,col2,ch);
getch();
}