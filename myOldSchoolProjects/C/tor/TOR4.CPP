#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
struct node
       {int info;
	struct node *next;};
typedef struct node* pointer;
typedef struct
	  {
	  pointer head,tail;
	  }queue;
queue q;
void create(queue&,int);
void insert(queue&,int);
void remove(queue&);
int empty(queue&);
void create(queue& q,int num)
{
int i;
q.head=q.tail=NULL;
for(i=1;i<=num;i++)insert(q,i);
}
int empty(queue& q)
{return(q.head==NULL);}
void insert(queue& q,int num)
{
pointer p;
p=(pointer)malloc(sizeof(node));
p->info=num;
p->next=NULL;
if(empty(q))q.head=q.tail=p;
else{q.tail->next=p;
     q.tail=p;
     }
}
void remove(queue& q)
{
pointer tmp;
tmp=q.head;
if (q.head==q.tail) q.head=q.tail=NULL;
else  q.head=q.head->next;
free(tmp);
}
void main()
{
int i,r,num;
float kupa1=0,kupa2=0;
clrscr();
printf("\nENTER NUMBER OF MEMBER IN QUEUE:");
scanf("%d",&num);
create(q,num);
if (empty(q)) {printf("\nQUEUE EMPTY");getch();}
else
{
randomize();
r=random(2);
for(i=0;i<num-1;i++)
{remove(q);
if(kupa1>kupa2)kupa2+=1;
else if(kupa1<kupa2) kupa1+=1.5;
     else if(r==0) kupa1+=1.5;
	  else kupa2+=1;
}
if(kupa1>kupa2)printf("Kassa number 2====>for %.1f minute",kupa2);
else if(kupa1<kupa2)printf("Kassa number 1====>for %.1f minute",kupa1);
     else if(r==0)printf("Kassa number 1====>for %.1f minute",kupa1);
	  else printf("Kassa number 2====>for %.1f minute",kupa2);
     getch();
}
}