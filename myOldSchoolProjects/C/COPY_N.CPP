#include<stdio.h>
#include<string.h>
main()
{int i,num;
char str[256],str1[256];
printf("\n enter a string ");
gets(str);
printf("enter a number :");
scanf("%d",&num);
for(i=0;i<num;i++)
str1[i]=str[i];
str1[i]='\0';
puts(str1);
}
