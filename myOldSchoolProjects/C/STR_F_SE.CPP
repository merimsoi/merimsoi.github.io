#include<stdio.h>
#include<conio.h>
#include<string.h>
main()
{
FILE *fp;
int i,a[100],j=0,k;
long leng1,leng2;
fpos_t cur,sof;
char *str,*s,*dup_str,*dup_s;
char t[256];
char *filename="d:\\borlandc\\bin\\irina.txt";
clrscr();
if((fp=fopen(filename,"r"))==NULL)
{
printf("/nerror opening file %s for reading.",filename);
return(-1);
}
printf("enter the string==>");
gets(t);str=t; dup_str=strdup(str);
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
fscanf(fp,"%s",s); dup_s=strdup(s);
str=strdup(dup_str);
fgetpos(fp,&cur);
if (cur>a[i]) ++i;
if(strcmp(str,s)==0) printf("\n%s==>line is %d",dup_s,i);
while(*str!='*') if (*str==*s) {s++;str++;j++;}
		 else break;
if (*str=='*') {str++;
		leng1=strlen(str); leng2=strlen(s);
		for(k=0;k<leng2-leng1;k++) s++;
		if(strcmp(str,s)==0) printf("\n%s==>line is %d",dup_s,i);}
}
fclose(fp);
getch();
return 0;
}
