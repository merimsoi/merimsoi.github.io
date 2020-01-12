#include<stdio.h>
#include<string.h>
#include<conio.h>
main()
{
clrscr();
FILE *fp;
FILE *fp2;
int cur,cur2,sof,sof2;
char str[30],str2[30];
char *filename="text1.txt";
char *filenam2="text2.txt";
if((fp=fopen(filename,"r"))==NULL)
{
printf("\nnerror opening file %s for reading.",filename);
return(-1);
}
if((fp2=fopen(filenam2,"r"))==NULL)
{
printf("\nerror opening file %s for reading.",filenam2);
return(-1);
}
fseek(fp,0,SEEK_END);sof=ftell(fp);
rewind(fp);cur=ftell(fp);
fseek(fp2,0,SEEK_END);sof2=ftell(fp2);
rewind(fp2);cur2=ftell(fp2);
while((cur<sof)&&(cur2<sof2))
{
fgets(str,70,fp);
fgets(str2,70,fp2);
if(strcmp(str,str2)!=0) {
			 printf("1 file==>%s\n",str);
			 printf("2 file==>%s\n",str2);
			 cur=ftell(fp);
                         cur2=ftell(fp2);
			}
else {cur=ftell(fp);
      cur2=ftell(fp2);
     }
}
getch();
}