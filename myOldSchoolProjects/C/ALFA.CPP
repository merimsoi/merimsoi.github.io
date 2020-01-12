#include<stdio.h>
#include<conio.h>
#include<string.h>
main()
{   int cmp;
char s[20],g[20];
gets(s);
gets(g);
cmp=strcmp(s,g);
if(cmp==0)printf("\nstrings are equal\n");
else if (cmp<0) printf("\n '%s'is greater than '%s'\n",g,s);
else printf("\n '%s' is greater than '%s'\n",s,g);
}






