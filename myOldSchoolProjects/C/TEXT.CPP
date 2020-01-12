#include<stdio.h>
#include<string.h>
#include<conio.h>
main()
{
clrscr();
char text[200][200];
char text2[40][40][40];
char text3[50][50];
int i=0,m,j,k,n,sum;
int b[10];int c[10];
char str[100]="";
for(j=0;j<=10;j++) {b[j]=0;c[j]=0;}
while(gets(text[i++])!=NULL) b[i-1]=strlen(text[i-1]);
n=i-1;
for(j=0;j<n;j++)
{k=0;m=0;
for(i=0;i<b[j];i++)
 if (text[j][i]!=' ')
   { if (i!=b[j]-1) {str[m++]=text[j][i];str[m]='\0';}
     else  {str[m++]=text[j][i];str[m]='\0';
	    strcpy(text2[j][k],str);
	    strcpy(str,"\0");c[j]=k+1; }
   }
   else {if(text[j][i-1]!=' ')
	{ strcpy(text2[j][k],str);
	 m=0;k++;strcpy(str,"\0");}}
}k=0;sum=0;
for(j=0;j<n;j++) sum=sum+c[j];
for(i=0;i<n;i++)
{
for(j=0;j<c[i];j++)
{strcpy(text3[k++],text2[i][j]);
 puts(text2[i][j]);
}
 }
 getch();
 printf("*************DICTIONARY************************\n");
 for(k=0;k<sum-1;k++)
 for(j=0;j<sum-k-1;j++)
 if (strcmp(text3[j],text3[j+1])>0)
 {strcpy(str,text3[j]);
  strcpy(text3[j],text3[j+1]);
  strcpy(text3[j+1],str);
 }
 for(k=0;k<sum;k++) puts(text3[k]);
 getch();
 printf("*************IN WHAT LINE?***************");
 for(k=0;k<sum;k++)
 {
 if (strcmp(text3[k],text3[k+1])!=0)
 {
 printf("\n%s ==>",text3[k]);
 for(i=0;i<n;i++)
 for(j=0;j<c[i];j++)
if (strcmp(text3[k],text2[i][j])==0) printf("the line is %d ",i+1);
 }}
 getch();
 }