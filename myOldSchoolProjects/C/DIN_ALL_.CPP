#include<stdio.h>
#include<alloc.h>
#include<string.h>
#define MAXSTRING 10
main()
{
int i=0,j;
char str[256];
char *list[MAXSTRING];
printf("\n enter string (to stop press CTRL/Z ENTER)==>");
while((i<MAXSTRING)&&(gets(str)!=NULL))
{list[i]=(char *)malloc(strlen(str)+1);
strcpy(list[i],str);
i++;
printf("\nenter string(to stop press CTRL/Z ENTER)==>");
}
printf("\NTHE FOLLOWING %d STRINGS WERE ENTERED\n",i);
for(j=0;j<i;j++)
{
printf("%d)",j+1);
puts(list[j]);
}
printf("\n");
for(j=0;j<i;j++);
free(list[j]);
}