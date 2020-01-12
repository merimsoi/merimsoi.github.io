#include<stdio.h>
#define MAX_PH 100
typedef struct
{
char number[15];
char name[20];
}phone_rec;
phone_rec list[MAX_PH];
int next;
void init_list(void)
{
next=0;
}
void skip_line(void)
{
char c;
while((c=getchar())!='\n')
 ;
}
void add_phone(void)
{
printf("enter name ");
gets(list[next].name);
printf("enter %s's number ",list[next].name);
gets(list[next].number);
next++;
}
void print_list(void)
{
int i;
printf("name \t\t\tnumber\n");
for(i=0;i<next;i++)
printf("%-20s\t%-15s\n",list[i].name,list[i].number);
printf("...hit enter to continue...");
skip_line();
}
main()
{
int ans;
init_list();
do
{
printf("\nenter\n0)to exit\n1)to add a record\n");
printf("2)to print the list\n");
scanf("%d",&ans);
skip_line();
switch(ans)
{
case 0:break;
case 1:add_phone();break;
case 2:print_list();break;
default:break;}
}while(ans);
}
