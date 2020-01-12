#include<stdio.h>
#include<conio.h>
#include<string.h>
main()
{
FILE *fp;
int i,a[100];
fpos_t cur,sof;
char *str,*s;
char t[256];
char *filename="irina.txt";
clrscr();
if((fp=fopen(filename,"r"))==NULL)
{
printf("/nerror opening file %s for reading.",filename);
return(-1);
}
printf("enter the string==>");
gets(t); str=t;
fseek(fp,0,SEEK_END);fgetpos(fp,&sof);
rewind(fp);fgetpos(fp,&cur);
a[0]=0;i=1;
while(cur<sof)
{fgets(s,70,fp);
fgetpos(fp,&cur);
a[i++]=cur;
}
rewind(fp);fgetpos(fp,&cur);i=1;
while(cur<sof)
{
fscanf(fp,"%s",s);
fgetpos(fp,&cur);
if (cur>a[i]) ++i;
if(strcmp(s,str)==0) printf("\n%s line is %d",str,i);
}
fclose(fp);
getch();
}