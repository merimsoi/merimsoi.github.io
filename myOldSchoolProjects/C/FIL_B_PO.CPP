#include<stdio.h>
#include<string.h>
#include<alloc.h>
#define MAX_PH 100
typedef struct
{
  struct
   {char *first;
    char *last;
   }name;
  char *number;
}phone_rec;
phone_rec *list[100];
int next,next1;
char first[256],last[256],number[256];

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
list[next]=(phone_rec*)malloc(sizeof(phone_rec));
printf("\nenter first name: ");
gets(first);
list[next]->name.first=(char *)malloc(strlen(first)+1);
strcpy(list[next]->name.first,first);
printf("enter last name: ");
gets(last);
list[next]->name.last=(char *)malloc(strlen(last)+1);
strcpy(list[next]->name.last,last);
printf("enter %s's number ",list[next]->name.first);
gets(number);
list[next]->number=(char *)malloc(strlen(number)+1);
strcpy(list[next]->number,number);
next++;
}
void print_list(void)
{
int i;
printf("name\t\tnumber\n");
for(i=0;i<next;i++)
printf("%s %s  %s\n",list[i]->name.first,list[i]->name.last,list[i]->number);
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
fprintf(fp,"%s %s %s\n",list[i]->name.first,list[i]->name.last,list[i]->number);
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
fscanf(fp,"%d",&next1);
for(i=0;i<next1;)
{
fscanf(fp,"%s",first);
fscanf(fp,"%s",last);
fscanf(fp,"%s",number);
if (next==0) {
	     list[i]=(phone_rec*)malloc(sizeof(phone_rec));
	     list[i]->name.first=(char *)malloc(strlen(first)+1);
	     list[i]->name.last=(char *)malloc(strlen(last)+1);
	     list[i]->number=(char *)malloc(strlen(number)+1);
	     }
strcpy(list[i]->name.first,first);
strcpy(list[i]->name.last,last);
strcpy(list[i]->number,number);
i++;
}
next=next1;
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
