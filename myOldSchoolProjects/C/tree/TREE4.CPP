#include<stdio.h>
#include<alloc.h>
#include<conio.h>
#define n 10
//---------------global variables -------------------
struct bin_tree
{int info;
struct bin_tree *left,*right;
};
typedef bin_tree *pointer;
pointer root;
int a[n];
int counter;
//----------------define function---------------------
void insert(pointer *,pointer);
pointer search_and_parent(pointer *,pointer *,int);
void build_tree(void);
void rebuild(pointer);
main()
{
clrscr();
int i;
printf("enter numbers");
for(i=0;i<n;i++)scanf("%d",&a[i]);
build_tree();
rebuild(root);
for(i=0;i<n-counter;i++)printf("%d ",a[i]);
getch();
}
void build_tree(void)
{int i;
pointer newnode,parent;
for(i=0;i<n;i++)
{
if((newnode=search_and_parent(&root,&parent,a[i]))!=NULL)
counter++;
else
{
newnode=(pointer)malloc(sizeof(struct bin_tree));
newnode->info=a[i];
newnode->left=newnode->right=NULL;
insert(&root,newnode);
}}}
void insert(pointer *p,pointer newnode)
{
if(*p==NULL)*p=newnode;
else if(newnode->info<(*p)->info)insert(&((*p)->left),newnode);
     else insert(&((*p)->right),newnode);
}
void rebuild(pointer p)
{static int i=0;
if(p)
{
rebuild(p->left);
a[i++]=p->info;
rebuild(p->right);
}
}
//--------------------------------------------------
pointer search_and_parent(pointer *p,pointer *parent,int x)
{
if(*p==NULL) return(NULL);
else if((*p)->info==x)
{
if(*p==root)*parent=NULL;
return(*p);
}
else{*parent=*p;
if(x<(*p)->info)
search_and_parent(&((*p)->left),&(*parent),x);
else search_and_parent(&((*p)->right),&(*parent),x);
}
}