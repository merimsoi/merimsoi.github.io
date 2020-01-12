#include<stdio.h>
#include<alloc.h>
#include<conio.h>
#define n 10

struct bin_tree
{int info;
struct bin_tree *left,*right;
};
typedef bin_tree *pointer;
pointer root;
int a[n];
void insert(pointer *,pointer);
void build_tree(void);
void rebuild(pointer);
main()
{ int i;
clrscr();
printf("enter numbers");
for(i=0;i<n;i++)scanf("%d",&a[i]);
build_tree();
rebuild(root);
for(i=0;i<n;i++)printf("%d ",a[i]);
getch();
}
void build_tree(void)
{int i;
pointer newnode;
for(i=0;i<n;i++)
{
newnode=(pointer)malloc(sizeof(struct bin_tree));
newnode->info=a[i];
newnode->left=newnode->right=NULL;
insert(&root,newnode);
}
}
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