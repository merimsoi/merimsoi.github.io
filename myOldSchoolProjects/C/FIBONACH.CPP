#include<stdio.h>
#include<alloc.h>
#include<conio.h>
#define max 150
struct node
	  {int info;
	  struct node *left,*rigth;
	  };
typedef  struct node* pointer;
     //functions
pointer init(int);
pointer add(pointer,pointer);
pointer insert(pointer,pointer);
pointer kill(pointer);
void print(pointer);
    //main
main()
{
pointer first,second,third;
int cnt;
clrscr();
first=init(0);
second=init(1);
for(cnt=3;cnt<=max;++cnt)
{
third=add(first,second);
first=kill(first);
first=second;
second=third;
}
print(third);
getch();
return 0;
}
  //init
pointer init(int value)
{pointer p,head;
head=(pointer)malloc(sizeof(node));
p=(pointer)malloc(sizeof(node));
head->rigth=p;
head->left=p;
p->left=head;
p->rigth=head;
p->info=value;
return(head);
}
  //print
void print(pointer head)
{
pointer p=head->rigth;
printf("the fibonacci number in place %d is :\n",max);
while(p!=head)
{
printf("%d",p->info);
p=p->rigth;
}
putchar('\n');
}
   //insert
pointer insert(pointer head,pointer f)
{
pointer p;
p=(pointer)malloc(sizeof(node));
p->rigth=f->rigth;
p->left=head->left;
head->left=p;
f->rigth=p;
return(p);
}
  //add
pointer add(pointer first,pointer second)
{
pointer p,q,head,f,last;
int sum,carry=0;
p=first->left;
q=second->left;
head=(pointer)malloc(sizeof(node));
f=(pointer)malloc(sizeof(node));
head->rigth=f;
head->left=f;
f->rigth=head;
f->left=head;
last=f;
while(p!=first&&q!=second)
{
sum=p->info+q->info+carry;
carry=0;
if (sum<10){
	    f->info=sum;
	    if(p->left!=first&&q->left!=second){
						head=insert(head,last);
						f=head->rigth;
					       }
	    else if(p->left==first&&q->left==second);
		 else if(p->left==first){
					 head->info=q->left->info;
					 head=insert(head,last);
					}
	   p=p->left;
	   q=q->left;
	    }
else { carry=sum/10;
       f->info=sum%10;
       if(p->left!=first&&q->left!=second){
					   head=insert(head,last);
					   f=head->rigth;
					   }
       else if(p->left==first&&q->left==second){
						head->info=carry;
						head=insert(head,last);
						}
       else if(p->left==first){
			       head->info=carry+q->left->info;
			       head=insert(head,last);
			       }
	     p=p->left;
	     q=q->left;
} }
return(head);
}
  //kill
pointer kill(pointer first)
{
pointer p,q;
p=first->left;
while(p!=first)
{
q=p->left;
free(p);
p=q;
}
free(first);
return(first);
}