#include<stdio.h>
#include<conio.h>
#include<string.h>
int index(char *s,char *t);
main()
{
int a;
char s[20],t[20];
gets(s);
gets(t);
a=index(s,t);
printf("%d",a);
}
int index(char *s,char *t)
{ char *k,*f;
int coun=0;
k=t,f=s;
while(*s)
{
t=k;
while((*s++==*t++)&&(*s)&&(*t));
if((!*t)&&(*(--s)==*(--t))) coun++;
if ((!*s)&&(!*t)) break;
else s=++f;
}
return(coun);
}
