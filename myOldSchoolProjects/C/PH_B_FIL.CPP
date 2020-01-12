#include<stdio.h>
#define MAX_PH 100

typedef struct
{
struct
{char first[10];
char last[15];
}name;
char number[15];
}phone_rec;
phone_rec list[MAX_PH];
int next;
void init_list(void)
{next=0;}
void skip_line(void)
{
char c;
while((c=getchar())!='\n')
;
}
void add_phone(void)
{
printf("\nenter first name: ");
gets(list[next].name.first);
printf("enter last name: ");
gets(list[next].name.last);
printf("enter %s's number ",list[next].name.first);
gets(list[next].number);
next++;
}
void print_list(void)
{
int i;
printf("\tname\t\t\tnumber\n");
for(i=0;i<next;i++)
printf("%-10s %-15s  %-15s\n",list[i].name.first,list[i].name.last,list[i].number);
printf("\n...hit enter to continue...");
skip_line();
}
int save_list()
{
int i;
FILE *fp;
fp=fopen("per_list.txt","w");
if(fp==NULL)
{
printf("\nerror upon opening file.");
return(1);
}
fprintf(fp,"%d\n",next);
for(i=0;i<next;i++)
fprintf(fp,"%s %s %s\n",list[i].name.first,list[i].name.last,list[i].number);
fclose(fp);
return(0);
}
int load_list()
{
int i=0;
FILE *fp;
fp=fopen("per_list.txt","r");
if(fp==NULL)
{
printf("\nerror upon opening file.");
return(1);
}
fscanf(fp,"%d",&next);
for(i=0;i<next;i++)
fscanf(fp,"%s %s %s",&list[i].name.first,&list[i].name.last,&list[i].number);
fclose(fp);
return(0);
}
main()
{int ans;
init_list();
do{
printf("\nenter \n\t0)to exit\n\t1)to add record");
printf("\n\t2)to print the list\n\t3)save list");
printf("\n\t4)load list from file\n");
scanf("%d",&ans);
skip_line();
switch(ans)
{
case 0:break;
case 1:add_phone();
break;
case 2:print_list();
break;
case 3:save_list();
break;
case 4:load_list();
break;
default:break;
}
}while(ans);
}
