#include<stdio.h>
#include<conio.h>
#include<alloc.h>
struct node
       {int info;
	struct node *next;};
typedef struct node* pointer;
struct queue
	 {
	 pointer head,tail;
	 }q,t;
typedef struct queue* poin_queue;
poin_queue q1=&q,t1=&t;
void create(poin_queue);
void insert(poin_queue,int);
int remove(poin_queue);
void print(poin_queue);
int empty(poin_queue);
void create(poin_queue q)
{
int num;
q->head=q->tail=NULL;
do
{
scanf("%d",&num);
if(num)insert(q,num);
}while (num!=0);
}
int empty(poin_queue q)
{
if(q->head==NULL&&q->tail==NULL)return(1);
else return(0);
}
void insert(poin_queue q,int num)
{
pointer p;
p=(pointer)malloc(sizeof(node));
p->info=num;
p->next=NULL;
if(empty(q))q->head=q->tail=p;
else{q->tail->next=p;
     q->tail=p;
     }
}
int remove(poin_queue q)
{
int x;
pointer tmp;
if (q->head==q->tail){tmp=q->head;q->head=q->tail=NULL;}
else
    {
     tmp=q->head;
     q->head=q->head->next;
    }
  x=tmp->info;
  free(tmp);
  return(x);
}
void print(poin_queue q)
{
pointer p;
p=q->head;
while(p!=NULL){printf("%d ",p->info);p=p->next;}
}
void main()
{
int i,n,x,y,z;
clrscr();
printf("ENTER THE MEMBERS OF QUEUE Q(0 to exit)\n");
create(q1);
printf("ENTER THE MEMBERS OF QUEUE T(0 to exit)\n");
create(t1);
if (empty(q1)||empty(t1)) printf("NO ENOUGTH MEMBERS");
else {
      printf("ENTER N:");
      scanf("%d",&n);
      for(i=0;i<n;i++)
      {
      x=remove(q1);
      y=remove(t1);
      z=x*y;
      insert(q1,z);
      insert(t1,x);
      }
     printf("\nNEW QUEUE Q\n");
     print(q1);
     printf("\nNEW QUEUE T\n");
     print(t1);
   }
     getch();
}
