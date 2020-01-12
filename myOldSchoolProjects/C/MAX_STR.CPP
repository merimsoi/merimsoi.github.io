#include<stdio.h>
#include<string.h>
main()
{
char str[10][10];
int b[10];
int i,j,max,m;
i=0;
for(j=1;j<=10;j++) b[j]=0;
while (gets(str[i++])!=NULL) b[i-1]=strlen(str[i-1]);
max=b[0];m=0;
for(j=1;j<=i-1;j++) if (b[j]>max) {max=b[j];m=j;}
puts(str[m]);
}