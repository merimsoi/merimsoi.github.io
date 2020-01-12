#include<stdio.h>
#include<string.h>
#define NUM_STR 5
void bubble_sort(char *str[],int size);
char *lines[NUM_STR]={"another string",
		       "a string",
		       "third string",
		       "twentysix character string"};
main()
{
int i;
printf("\n strings before sorting\n");
for(i=0;i<NUM_STR;i++)
puts(lines[i]);
bubble_sort(lines,NUM_STR);
printf("\n strings after sorting\n");
for(i=0;i<NUM_STR;i++)
puts(lines[i]);
}
void bubble_sort(char *str[],int size)
{
char *tmp;
int low,hi,top;
top=size;
while(top>0)
{
for(low=0,hi=1;hi<top;low++,hi++)
{if (strcmp(str[low],str[hi])>0)
{
tmp=str[low];
str[low]=str[hi];
str[hi]=tmp;
}}
top--;
}}