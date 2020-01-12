#include<stdio.h>
#include<conio.h>
#include<alloc.h>
struct node
       {int info;
	struct node *next;};
typedef struct node* pointer;
typedef struct
	 {
	 pointer head,tail;
	 }queue;
queue t,q;
void create(queue&);
void insert(queue&,int);
int remove(queue&);
void print(queue&);
int empty(queue&);
void create(queue& q)
{
int num;
q.head=q.tail=NULL;
do
{
scanf("%d",&num);
if(num)insert(q,num);
}while (num!=0);
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
int remove(queue& q)
{
int x;
pointer tmp;
if (q.head==q.tail){tmp=q.head;q.head=q.tail=NULL;}
else
    {
     tmp=q.head;
     q.head=q.head->next;
    }
  x=tmp->info;
  free(tmp);
  return(x);
}
void print(queue& q)
{
pointer p;
p=q.head;
while(p!=NULL){printf("%d ",p->info);p=p->next;}
}
void main()
{
int i,n,x,y,z;
clrscr();
printf("ENTER THE MEMBERS OF QUEUE Q(0 to exit)\n");
create(q);
printf("ENTER THE MEMBERS OF QUEUE T(0 to exit)\n");
create(t);
if (empty(q)||empty(t)) printf("NO ENOUGTH MEMBERS");
else {
      printf("ENTER N:");
      scanf("%d",&n);
      for(i=0;i<n;i++)
      {
      x=remove(q);
      y=remove(t);
      z=x*y;
      insert(q,z);
      insert(t,x);
      }
     printf("\nNEW QUEUE Q\n");
     print(q);
     printf("\nNEW QUEUE T\n");
     print(t);
   }
     getch();
}
