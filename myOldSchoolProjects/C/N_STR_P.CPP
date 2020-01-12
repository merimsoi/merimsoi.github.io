#include<stdio.h>
#include<conio.h>
int index(char *s,char *t);
void main(void)
{
char *arr[5];
char str[10][10];
char seq[10];
int i;
for(i=0;i<5;i++)
 {
 gets(str[i]);
 arr[i]=str[i];
   }
   gets(seq);
  for(i=0;i<5;i++)
if (index(arr[i],seq)>0) printf("%d",i+1);
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

