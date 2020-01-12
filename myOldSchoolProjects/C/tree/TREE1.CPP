#include<stdio.h>
#include<alloc.h>
//---------------------global types--------------------
struct node
{
int freq;
char ch;
struct node *left,*right,*next,*parent;
};
typedef node *pointer;
typedef struct
{
pointer address_in_forest;
int freq;
}elem_of_alphabet;
//-----------------------------------------------
struct stack_elem
{
char ch;
struct stack_elem *next;
};
typedef stack_elem *stack;
//---------------global variables----------------
pointer forest;
elem_of_alphabet alphabet[256];
FILE *input;
stack s;
//------------function prototypes------------------
void build_alphabet(void);
void init_forest(void);
void build_huffmann_tree(void);
void print_codes(void);
void insert(pointer*,pointer);
//---------------main function---------------------
main()
{
build_alphabet();
init_forest();
build_huffmann_tree();
print_codes();
return 0;
}
//---------------function called by main----------------
void build_alphabet(void)
{
int i;
char ch;
input=fopen("d:\\borlandc\\bin\\ira\\text.txt","r");
for(i=0;i<256;++i)alphabet[i].freq=0;
while((ch=fgetc(input))!=EOF)
alphabet[ch].freq++;
fclose(input);
}
//---------------------------------------------
void init_forest(void)
{
int i;
pointer p;
forest=NULL;
for(i=0;i<256;++i)
if(alphabet[i].freq)
{
p=(pointer)malloc(sizeof(struct node));
p->next=NULL;
p->parent=NULL;
p->freq=alphabet[i].freq;
p->left=p->right=NULL;
p->ch=i;
alphabet[i].address_in_forest=p;
insert(&forest,p);
}
}
//------------------------------------------
void build_huffmann_tree(void)
{
pointer p;
while(forest->next!=NULL)
{
p=pointer(malloc(sizeof(struct node)));
p->left=forest;
p->right=forest->next;
p->parent=NULL;
p->next=NULL;
p->freq=forest->freq+forest->next->freq;
forest->parent=p;
forest->next->parent=p;
if(forest->next->next==NULL)
forest=NULL;
else forest=forest->next->next;
insert(&forest,p);
}
}
//---------------stack function-------------------
//-----------called by print_codes----------------
int empty(void)
{
return(s==NULL);
}
//------------------------------------------------
void init(void)
{
s=NULL;
}
//-----------------------------------------------
char pop(void)
{
stack temp=s;
char c=temp->ch;
s=s->next;
free(temp);
return(c);
}
//-------------------------------------------
void push(char ch)
{
stack p=(stack)malloc(sizeof(stack_elem));
p->ch=ch;
p->next=NULL;
if(empty()) s=p;
else {
      p->next=s;
      s=p;
      }
}
//-------------------------------------------
void print_codes(void)
{
int ch;
pointer p,back;
for(ch=0;ch<256;++ch)
if(alphabet[ch].freq)
{
p=alphabet[ch].address_in_forest;
init();
back=p->parent;
while(back)
{
if (back->left==p)
push('0');
else push('1');
p=back;
back=back->parent;
}
printf("\nthe code of %c is:",ch);
while(s)
putchar(pop());
}
}
//----------------------called by build_huffmann&init_forest----------
void insert(pointer *head,pointer newnode)
{
pointer back,current;
if(*head==NULL)*head=newnode;
else
if(newnode->freq<=(*head)->freq)
{
newnode->next=*head;
*head=newnode;
}
else
{
back=*head;
current=back->next;
while(current&&current->freq<newnode->freq)
{
back=current;
current=current->next;
}
if(!current)
back->next=newnode;
else{
back->next=newnode;
newnode->next=current;
}
}
}