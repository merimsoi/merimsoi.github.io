#include<stdio.h>
#include<conio.h>
#include<alloc.h>
#define max_flight 5
#define error "invalid option-press enter\n"
//---------data types-----------------------
typedef struct node
{int id;
struct node *next;};
typedef node *pointer;
typedef struct
	     {int flight_no,capacity,occupied;
	     pointer head,tail;
	     pointer first;
	     }flight;
flight a[max_flight];
//-------------function prototipes------------------
void display_menu(void);
void init(void);
void get(void);
int search(int);
void print(void);
void insert(int,int);
void del(void);
void del_waiting(void);
//----------------------------------------------
main()
{
char answer;
clrscr();
init();
for(;;)
{
clrscr();
display_menu();
switch(answer=getche())
{
case '1':getch();get();break;
case '2':getch();del();break;
case '3':getch();del_waiting();break;
case '4':getch();print();break;
case '5':getch();return(0);
default:printf(error);
getch();
}}}
//--------------------------------------------------
void display_menu(void)
{
printf("1\tget new invoice\n");
printf("2\tdelete invoice\n");
printf("3\tdelete from waiting list\n");
printf("4\tprint invoices\n");
printf("5\texit\n");
printf("\n\n\n\n");
printf("press your choice\t");
return;
}
//----------------------------------------------------
void init(void)
{int i;
for(i=0;i<max_flight;++i)
{
printf("flight_number\t");
scanf("%d",&a[i].flight_no);
printf("places in flight\t");
scanf("%d",&a[i].capacity);
a[i].occupied=0;
a[i].head=a[i].tail=a[i].first=NULL;
}}
//------------------------------------------
void get(void)
{
int fl_no,pos,id,n;
pointer p;
clrscr();
printf("\nnumber of flight\t");
scanf("%d",&fl_no);
if((pos=search(fl_no))==-1)
printf("no such flight\n");
else {
clrscr();
printf("your id\t");
scanf("%d",&id);
if(a[pos].occupied==a[pos].capacity)
{
printf("you are in waiting list\n");
insert(id,pos);
}
else {
p=(pointer)malloc(sizeof(node));
p->next=NULL;
p->id=id;
if(a[pos].first==NULL)
a[pos].first=p;
else{
p->next=a[pos].first;
a[pos].first=p;
}
a[pos].occupied++;printf("ok.\n");
}}
printf("press any key...");
getch();
}
//-----------------------------------------------
int search(int num)
{
int i;for(i=0;i<max_flight;++i)
if (a[i].flight_no==num)
return(i);
return(-1);
}
//-----------------------------------------
void print(void)
{
int fl_no,i,pos;
pointer p;
clrscr();
printf("flight number\t");
scanf("%d",&fl_no);
if((pos=search(fl_no))==-1)
printf("no such flight\n");
else{
      printf("flight\t%d\n",a[pos].flight_no);
      printf("capacity\t%d\n",a[pos].capacity);
      printf("occupied\t%d\n",a[pos].occupied);
      for(p=a[pos].first;p!=NULL;p=p->next)
	  printf("\tid\t%d\n",p->id);
	  printf("\n\nwaiting list\n");
	  p=a[pos].head;
	  while(p!=NULL)
	  {printf("%d\n",p->id);
	  p=p->next;
	  }
	  }
      printf("press any key...");
      getch();
      }
//----------------------------------------------------
void insert(int id,int pos)
{
pointer p;
p=(pointer)malloc(sizeof(node));
p->id=id;
p->next=NULL;
if(a[pos].head==NULL) a[pos].head=a[pos].tail=p;
else
{
a[pos].tail->next=p;
a[pos].tail=p;
}}
//-------------------------------------------------------
void del(void)
{ int fl_no,pos,id;
pointer th,oneback;
printf("\nnumber of flight\t");
scanf("%d",&fl_no);
if((pos=search(fl_no))==-1) {printf("no such flight\n");
			     printf("press any key...");
			     getch();}
else
  if(a[pos].first==NULL){printf("impossible,all seates free\n");
			 printf("press any key...");
			 getch();}
  else
   {
    printf("your id\t");
    scanf("%d",&id);
    th=a[pos].first;
    if(th->id==id){a[pos].first=th->next;free(th);
		   a[pos].occupied--;
		   printf("ok.\n");
		   printf("press any key...");
		   getch();}
    else
      {
      for(oneback=th;th!=NULL;oneback=th,th=th->next)
      if(th->id==id) {oneback->next=th->next;free(th);a[pos].occupied--;
		      printf("ok.\n");
		      printf("press any key...");
		      getch();break;}
      if(th==NULL){printf("error in id\n");
		   printf("press any key...");
		   getch();}
      }
    }
}
//------------------------------------------------------------
void del_waiting(void)
{ int fl_no,pos,id;
pointer tmp,p;
printf("\nnumber of flight\t");
scanf("%d",&fl_no);
if((pos=search(fl_no))==-1){printf("no such flight\n");
			    printf("press any key...");
			    getch();}
if(a[pos].occupied==a[pos].capacity){printf("impossible,no free seates\n");
				     printf("press any key...");
				     getch();}
else if(a[pos].head==NULL){printf("impossible,no queue waiting\n");
			   printf("press any key...");
			   getch();}
     else
      {tmp=a[pos].head;
      id=tmp->id;
      if(a[pos].head==a[pos].tail){a[pos].head=a[pos].tail=NULL;}
      else a[pos].head=a[pos].head->next;
      free(tmp);
      p=(pointer)malloc(sizeof(node));
      p->next=NULL;
      p->id=id;
      if(a[pos].first==NULL)a[pos].first=p;
      else{
	   p->next=a[pos].first;
	   a[pos].first=p;
	   }
      a[pos].occupied++;printf("ok.\n");
      printf("press any key...");
      getch();
      }
}