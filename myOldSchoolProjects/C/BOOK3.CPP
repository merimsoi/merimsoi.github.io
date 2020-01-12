#include<stdio.h>
#include<alloc.h>
typedef struct rec
{
struct
{
char first[10];
char last[15];
}name;
char number[15];
struct rec *next;
}phone_rec;
phone_rec *start; //pointing to the first record

void init_list(void)
{
start=NULL;
}
void skip_line(void)
{
char c;
while((c=getchar())!='\n')
;
}
void add_phone(void)
{
phone_rec *cur;//pointing to the current structure
if(start==NULL)
{start=(phone_rec*)malloc(sizeof(phone_rec));
cur=start;
}
else
{
cur=start;
while(cur->next!=NULL) cur=cur->next;
cur->next=(phone_rec*)malloc(sizeof(phone_rec));
cur=cur->next;
}
printf("\nenter first name: ");
gets(cur->name.first);
printf("enter last name: ");
gets(cur->name.last);
printf("enter %s's number ",cur->name.first);
gets(cur->number);
cur->next=NULL;
}
void print_list(void)
{
phone_rec *cur;
cur=start;
printf("\tname\t\t\tnumber\n");
while(cur!=NULL)
{
printf("%-10s %-15s %-15s\n",cur->name.first,cur->name.last,cur->number);
cur=cur->next;
}printf("\n...hit enter to continue...");
skip_line();
}
main()
{
int ans;
init_list();
do
{
printf("\nenter\n\t0)to exit\n\t1)to add a record");
printf("\n\t2)to print the list\n");
scanf("%d",&ans);
skip_line();
switch(ans)
{
case 0:break;
case 1:add_phone();
break;
case 2:print_list();
break;
default:break;
}}while(ans);
}
