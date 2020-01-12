#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<alloc.h>
#define MAX 256
typedef struct
{
char *kword;
int kcount;
}key_word;

key_word *word_list[100];
int next=0;
void print_occurances();
int search(char*);
int get_next_word(char*,char*);
main()
{
int n;
char line[MAX],word[20];
gets(line);
while(get_next_word(line,word)!=EOF)
if((n=search(word))>=0) word_list[n]->kcount++;
else {
      word_list[next]=(key_word*)malloc(sizeof(key_word));
      word_list[next]->kword=(char*)malloc(strlen(word)+1);
      strcpy(word_list[next]->kword,word);
      word_list[next]->kcount=1;
      next++;
    }
    print_occurances();
    }

 void print_occurances()
 {
 int n;
 puts("***** printing occurances of word ******");
 for(n=0;n<next;n++)
 if(word_list[n]->kcount>0)
 printf("count=%d word=%s\n",word_list[n]->kcount,word_list[n]->kword);
 }

 int get_next_word(char *line,char *word)
 {
 char *s;
 s=line;
 while(!isalpha(*s)&&*s)s++;
 if (*s=='\0')return(EOF);
 else {s=line;}
 while(*s)
 {
 if(isalpha(*s)) s++;
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

 int search(char *word)
 {
 int i=0;
 while(strcmp(word,word_list[i]->kword)!=0 && i<next)
 i++;
 if(i==next)return(-1);
 else return(i);
 }
