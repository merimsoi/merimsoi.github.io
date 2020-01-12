#include<stdio.h>
#include<ctype.h>
#include<string.h>
typedef struct
{
char *keyword;
int keycount;
}key_word;
key_word keytab[]={"break",0,
		   "case",0,
		   "char",0,
		   "for",0};
#define NKEYS (sizeof(keytab)/sizeof(key_word))
#define MAX 256

void print_occurances();
int binary_search(char*);
int get_next_word(char*,char*);
main()
{
int n;
char line[MAX],word[20];
gets(line);
while(get_next_word(line,word)!=EOF)
 if((n=binary_search(word))>=0)
    keytab[n].keycount++;
   print_occurances();
}
void print_occurances()
{
int n;
puts("***** printing occurances of keywords *****");
for(n=0;n<NKEYS;n++)
if(keytab[n].keycount>0)
printf("\ncount=%d word=%s",keytab[n].keycount,keytab[n].keyword);
}
int get_next_word(char *line,char *word)
{
char *s;
s=line;
while(!isalpha(*s)&&*s) s++;
if(*s=='\0') return(EOF);
else {
strcpy(line,s);
s=line;
}
while(*s)
{if(isalpha(*s)) s++;
else
{
*s='\0';
strcpy(word,line);
strcpy(line,++s);
return(0);
}
}
strcpy(word,line);
strcpy(line,s);
return(0);
}
int binary_search(char *word)
{
int low=0,high=NKEYS-1;
int mid,cond;
while(low<=high)
{
mid=(low+high)/2;
if((cond=strcmp(word,keytab[mid].keyword))<0)
high=mid-1;
else if(cond>0)
low=mid+1;
else
return(mid);
}
return(-1);
}
