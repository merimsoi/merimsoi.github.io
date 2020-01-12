#include<stdio.h>
#include<string.h>
main()
{
char line[256],*s,delch;
gets(line);
s=line;
scanf("%c",&delch);
while(*s)
{
if (*s==delch) strcpy(s,s+1);
else s++;
}puts(line);
}