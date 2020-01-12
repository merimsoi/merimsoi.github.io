#include<stdio.h>
#define MAX 256
main()
{
FILE *fp;
char *filename="filetest.txt";
char str[MAX],ch,i;
if((fp=fopen(filename,"w"))==NULL)
{printf("\nerror upon opening file");
return 1;
}
fputs("testing file",fp);
fclose(fp);
if((fp=fopen(filename,"r+"))==NULL)
{
printf("\nerror upon opening file");
return 1;
}
fgets(str,MAX,fp);
puts(str);
fputc(' ',fp);
fputc('+',fp);
fputc('+',fp);
fclose(fp);
if((fp=fopen(filename,"r"))==NULL)
{
printf("\nERROR UPON OPENING FILE");
return 1;
}
for(i=0;i<MAX && !feof(fp);i++)
{
ch=fgetc(fp);
putchar(ch);
}
fclose(fp);
}

