#include<stdio.h>
#include<string.h>
main()
{
char str[256];
int a[26];
int b[9];
int i,k;
for(i=0;i<=26;i++) a[i]=0;
for(i=0;i<=9;i++) b[i]=0;
printf("\nenter a string ");
gets(str);
for(i=0;i<=(strlen(str));i++)
if ((str[i]>='0' && str[i]<='9')?1:0) { k=str[i]-'0';
					b[k]++;}
else if ((str[i]>='a' && str[i]<='z')?1:0) a[str[i]-97]++;
for(i=0;i<26;i++)
if (a[i]!=0) printf("\n%d of occurances of %c",a[i],i+97);
for(i=0;i<9;i++)
if (b[i]!=0) printf("\n%d of occurances of %d",b[i],i);
}
