#include<stdio.h>
#include<alloc.h>
#define forever 1
struct bin_tree
{
int info;
struct bin_tree *left,*right;
};
typedef bin_tree *pointer;
pointer root;
void init(void);
void build_tree(void);
void insert(pointer*,pointer);
void print_tree(pointer);
void delete_node(pointer,pointer);
void delete_0(pointer,pointer);
void delete_1(pointer,pointer);
void delete_2(pointer);
void connect(pointer,pointer,pointer);
pointer search_and_parent(pointer*,pointer*,int);
//----------------------------------------------------
main()
{
int x;
pointer p,parent;
init();
build_tree();
print_tree(root);
putchar('\n');
while(forever)
{
printf("node to delete-0 to exit");
scanf("%d",&x);
if(x==0)break;
if((p=search_and_parent(&root,&parent,x))==NULL)
printf("the node not exist\n");
else{
delete_node(p,parent);
printf("the tree after delete");
print_tree(root);
printf("\n\n\n");
}
}
return 0;
}
//-------------------------------------------------
void init(void)
{
root=NULL;
}
//----------------------------------------
void build_tree(void)
{
int num;
pointer newnode;
while(forever)
{
printf("number ");
scanf("%d",&num);
if(num==0)break;
else
{
newnode=(pointer)malloc(sizeof(struct bin_tree));
newnode->info=num;
newnode->left=newnode->right=NULL;
if (root==NULL) root=newnode;
else insert(&root,newnode);
}}}
//------------------------------------------------
void print_tree(pointer p)
{
if(p)
{
print_tree(p->left);
printf("%3d",p->info);
print_tree(p->right);
}}
//------------------------------------------------
void insert(pointer *p,pointer newnode)
{
if(*p==NULL) *p=newnode;
else if(newnode->info<(*p)->info)
insert(&((*p)->left),newnode);
else insert(&((*p)->right),newnode);
}
//---------------------------------------------
void delete_node(pointer p,pointer parent)
{
if(p->left&&p->right)delete_2(p);
else if(p->left||p->right)
	  delete_1(p,parent);
	  else delete_0(p,parent);
	  }
//------------------------------------------------
void delete_0(pointer p,pointer parent)
{
if(parent==NULL) root=NULL;
else if (parent->left==p)parent->left=NULL;
else parent->right=NULL;
free(p);
}
//---------------------------------------------
void delete_1(pointer p,pointer parent)
{
if(p->left==NULL)connect(parent,p,p->right);
else connect(parent,p,p->left);
free(p);
}
//----------------------------------------------
void delete_2(pointer p)
{
pointer q,parent;
q=p->right;
parent=p;
while(q->left)
{parent=q;q=q->left;}
p->info=q->info;
connect(parent,q,q->right);
free(q);
}
//--------------------------------------------------
void connect(pointer parent,pointer p,pointer son_of_p)
{
if(p==root)
root=son_of_p;
else
if(parent->left==p)parent->left=son_of_p;
else parent->right=son_of_p;
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
