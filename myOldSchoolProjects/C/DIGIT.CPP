#include<stdio.h>
#include<conio.h>
#include<alloc.h>
#include<math.h>
#define max 10
struct digit_node{
		  char digit;
		  digit_node *next;
		  }*p,*last;
struct header{
	      int counter;
	      digit_node *next;
	      }*head;
typedef struct header* element;
typedef struct digit_node* pointer_to_digit;
element *a[max] ;
int size;
int *k=&size;
element read(void);
element comp(element head1,element head2);
element same_size(element head1,element head2);
void input(element *a[max],int *k);
int find_min(element *a[max],int size);
void print(element *a[max],int min);
void main()
{
clrscr();
input(a,k);
print(a,find_min(a,size));
}
element read(void)
{
char ch;int valid=1,sign=1;
head=(header*)malloc(sizeof(header));
head->counter=0; head->next=NULL;
while((ch=getche())!='\r'&&valid)
{
switch(ch)
{
case'-':if(head->counter==0) sign=-1;
	else valid=0;break;
case'+':if(head->counter==0) sign=1;
	else valid=0;break;
default:if(ch>='0'&&ch<='9')
	{
	head->counter++;
	p=(digit_node*)malloc(sizeof(digit_node));
	p->digit=ch;
	p->next=NULL;
	if(head->next==NULL)
	  {
	  head->next=p;
	  last=p;
	  }
	else
	 {
	 last->next=p;
	 last=p;
	 }
      }
     else valid=0;
}}
if(valid){head->counter=sign*head->counter;
	  return(head);
	  }
else return(NULL);
}
element comp(element head1,element head2)
{
if(head1->counter<0) //first negative
 { if(head2->counter>0) return(head1); //first negative,second positive
   else //both negative
    if(abs(head1->counter)<abs(head2->counter)) return(head2);
    else
      if(abs(head1->counter)>abs(head2->counter)) return(head1);
      else return(same_size(head1,head2));
 }
else
 if(head2->counter>0) //both positive
  {
   if(abs(head1->counter)<abs(head2->counter)) return(head1);
   else
    if(abs(head1->counter)>abs(head2->counter)) return(head2);
    else same_size(head1,head2);
   }
 else return(head2);//first positive,second negative
 }
 element same_size(element head1,element head2)
 {
  pointer_to_digit p1,p2;
  int equal=1;
  p1=head1->next; p2=head2->next;
  while(equal && (p1!=0))
  if(p1->digit!=p2->digit) equal=0;
  else {
	p1=p1->next;
	p2=p2->next;
	}
  if(p1==NULL) return(head1);//numbers are equal
  else if(p1->digit<p2->digit)
	   if(head1->counter<0) return(head2); //both negative
	   else return(head1);
       else if(head1->counter<0) return(head1);
	    else return(head2);
}
void input(element *a[max],int *k)
{
int cnt=0;
element p;
printf("how many numbers? ");
scanf("%d",&size);
while(cnt<size)
{
p=read();
printf("\n");
if(p!=NULL){
	    cnt++;
	    a[cnt]=(element*)malloc(sizeof(element));
	    *a[cnt]=p;
	     }
else printf("\ninvalid number! try again...");
}}
int find_min(element *a[max],int size)
{
int i,min_index=1;
for(i=2;i<=size;i++)
if(comp(*a[min_index],*a[i])==*a[i]) min_index=i;
return(min_index);
}
void print(element *a[max],int min)
{
pointer_to_digit p;
printf("min is==>");
if((*a[min])->counter<0)printf("-");
p=(*a[min])->next;
while(p!=NULL)
{
printf("%c",p->digit);
p=p->next;
}
printf("\n");
}