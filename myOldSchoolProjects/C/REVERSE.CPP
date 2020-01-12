#include<stdio.h>
#include<string.h>
main()
{char str[10],str1[10];
int i,j,n;
printf("\nenter a string ");
gets(str);
n=strlen(str);
for(j=n-1,i=0;j>=0 ;i++,j--) str1[i]=str[j];
str1[i]='\0';
puts(str1);
}
