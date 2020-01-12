#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<alloc.h>
struct
{struct
 {char first[6];
  char last[12];
  }name;
 char phone[7];
}pers;
char findname[15];
int search()
{
int cur,m;
FILE *fp;
char *filename="irina1.txt";
if((fp=fopen(filename,"r"))==NULL)
{
printf("/nerror opening file %s for reading.",filename);
return(-1);
}
fseek(fp,0,SEEK_END);cur=ftell(fp);
rewind(fp);m=ftell(fp);
while(m<cur)
{
fscanf(fp,"%s%s%s",&pers.name.first,&pers.name.last,&pers.phone);
if (strcmp(pers.name.last,findname)==0) {fclose(fp);
					 return 0;
					 }
else m=ftell(fp);
}
  fclose(fp); return 1; }
  main()
  {
  int bin;
  printf("\nenter name of person to find: ");
  gets(findname);
  if((bin=search())==0)  printf("%s %s %s",pers.name.first,pers.name.last,pers.phone);
  else if(bin==1) printf("person is not in list.");
  getch();
  }