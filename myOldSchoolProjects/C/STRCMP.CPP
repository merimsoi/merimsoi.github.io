#include<stdio.h>
#include<string.h>
int strcm(char *str1,char *str2);
main()
{
int cmp;
char str1[256];
char str2[256];
gets(str1);
gets(str2);
cmp=strcm(str1,str2);
if(cmp==0)printf("\nstrings are equal\n");
else if (cmp<0) printf("\n '%s'is greater than '%s'\n",str2,str1);
else printf("\n '%s' is greater than '%s'\n",str1,str2);
}
int strcm(char *st1,char *st2)
{
while(*st1 && *st2)
{if (*st1<*st2)return(-1);
else if(*st1>*st2)return(1);
else {st1++;st2++;}}
if (!*st1&&!*st2) return(0);
else if (!*st1) return(-1);
else if (!*st2) return(1);
	}
