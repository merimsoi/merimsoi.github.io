#include<stdio.h>
#include<conio.h>
#include<string.h>
void strcatt(char *str1,char *str2);
main()
{
char str1[20],str2[20];
puts("*********************");
gets(str1);
gets(str2);
strcatt(str1,str2);
puts(str1);
puts("*****************");
}
void strcatt(char *str1,char *str2)
{
while(*str1) str1++;
while(*str1++=*str2++);
}