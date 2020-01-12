#include<stdio.h>
#include<string.h>
int index(char s[],char t);
main()
{
char s[256];
char t;
printf("\nenter a string ");
gets(s);
printf("\nenter a char ");
scanf("%c",&t);
printf("%d",index(s,t)+1);
}
int index(char s[],char t)
{ int coun=0,i;
for(i=0;i<strlen(s);i++)
if (s[i]==t){coun++;
	    return(i);
	    }
if (coun==0) return(-2);
}