#include"count.h"
#include"include.h"
//**************************************************************************
//Function List::Add adds new client to list
//Parameters: Data  *new block -->pointer to new client
//Return Value:none
//**************************************************************************
void List::Add(Data *new_block)
{
 if(!Head) Head=new_block;               //if first  ?
 else End->SetNext(new_block);           //else add after last
 End=new_block;
}
//**************************************************************************
//Function List::Delete  deletes client from list
//Parameters:long num_id -->i.d of client
//Return Value:none
//**************************************************************************
void List::Delete(long num_id)
{
 if(!Head) return;                         //if empty ?
 Data* pt=Head;
 if(((Count_priv*)Head)->id==num_id)       //if first ?
   {
    Head=pt->next;
    delete pt;
    pt=Head;
    return;
   }
 Data* prv=Head;
 pt=Head->next;
 while(pt)
  {
   if(((Count_priv*)pt)->id==num_id)
     {
      prv->next=pt->next;
      if(End==pt) End=prv;                 //if last ?
      delete pt;
      pt=prv->next;
      return;
      }
   else
      {
       prv=pt;
       pt=pt->next;
      }
     }
  }
//***************************************************************************
//Function List::IsPresent checks if client present yet
//Parameters:long num_id -->i.d of client
//Return Value:int-->1-client exist,0-no
//**************************************************************************
int List::IsPresent(long num_id)
{
 if(!Head) return 0;
 if(((Count_priv*)Head)->id==num_id||((Count_priv*)End)->id==num_id)
   return 1;                                      //if first or last
   if(Head->next==NULL) return 0;
   Data *pt=Head->next;
   for(;pt!=NULL;pt=pt->next)
   if(((Count_priv*)pt)->id==num_id)return 1;     //present

  return 0;                                       //not present
}
//**************************************************************************
//Function List::Find return reference to needed client(if here exactly exist)
//Parameters:long num_id -->i.d of client
//Return Value:Data&-->reference to client
//**************************************************************************
Data& List::Find(long num_id)
{
 Data* pt=Head;
  for(;pt!=NULL;pt=pt->next)
   if(((Count_priv*)pt)->id==num_id)
   {
   Data& ptr=*pt;
   return ptr;              //return reference to client
   }
  return (Data&)pt;         //against the warning in time compiling
 }
//****************************************************************************
//Constructor of Client_priv.It init name,address,i.d and remain in shekel
//of client
//Parameters:char *,char*,long-->to init data
//****************************************************************************
Count_priv::Count_priv(char* n,char* add,long num_id)
  {
   name=new char[strlen(n)+1];
   assert(name);
   strcpy(name,n);
   address=new char[strlen(add)+1];
   assert(address);
   strcpy(address,add);
   id=num_id;
   remain_shekel=0;
  }
//***************************************************************************
//Destructor of Count_priv
//***************************************************************************
Count_priv::~Count_priv()
{
delete name;
delete address;
}
//***************************************************************************
//Function Count_priv returns name of class
//Parameters:none
//Return Value:char*-->pointer to name
//**************************************************************************
char* Count_priv::GetN()
{
return"Count_priv";
}
//************************************************************************
//Function Count_priv::AddToRemain adds sum to remain in shekels
//Parameters:int,int-->sum,second need definition of function
//Return Value:none
//**************************************************************************
void Count_priv::AddToRemain(double sum,int)
 {
 remain_shekel+=sum;
 }

//************************************************************************
//Function Count_priv::SubFromRemain sub. sum from remain in shekels
//Parameters:int,int-->sum,second need definition of function
//Return Value:none
//**************************************************************************
void Count_priv::SubFromRemain(double sum,int)
 {
 remain_shekel-=sum;
 }
//**************************************************************************
//Function Count_priv::GetShkalim returns the remain in shekels
//Parameters:none
//Return Value:double-->return sum
//**************************************************************************
double Count_priv::GetShkalim()
{
return remain_shekel;
}
//**************************************************************************
//Function Count_priv::show shows the current state of account
//Parameters:int,int-->for coordinates
//Return Value:none
//**************************************************************************
void Count_priv::show(int x,int y)
 {
 gotoxy(x,y);
 cout<<" Name         :"<<name;
 gotoxy(x,y+1);
 cout<<" Address      :"<<address;
 gotoxy(x,y+2);
 cout<<" Number of i.d:"<<id;
 gotoxy(x,y+3);
 cout.setf(ios::fixed);
 cout<<" You have     :"<<setprecision(2)<<remain_shekel<<" shekel";
 }
//****************************************************************************
//Constructor of Count_bisn.It involve the Count_priv's constractors,init
//remain in $ and standard.
//Parameters:char *,char*,long-->to init data
//****************************************************************************
Count_bisn::Count_bisn(char* n,char* add,long num_id):Count_priv(n,add,num_id)
{
standard=3;
remain_dollar=0;
}
//***************************************************************************
//Function Count_priv returns name of class
//Parameters:none
//Return Value:char*-->pointer to name
//**************************************************************************
char* Count_bisn::GetN()
{
return"Count_bisn";
}
//*************************************************************************
//Function Count_bisn::GetStan returns the standard
//Parameters:none
//Return Value:float-->return the standard
//**************************************************************************
float Count_bisn::GetStan()
 {
 return standard;
 }
//***************************************************************************
//Function Count_priv::AddToRemain adds sum to remain in shekels
//if k=0,else adds to dollars
//Parameters:int,int-->sum,k
//Return Value:none
//***************************************************************************
void Count_bisn::AddToRemain(double sum,int k)
 {
 if(k) remain_dollar+=sum;
 else Count_priv::AddToRemain(sum,0);
 }

//***************************************************************************
//Function Count_priv::SubFromRemain sub. sum from remain in shekels
//if k=0,else sub to dollars
//Parameters:int,int-->sum,k
//Return Value:none
//**************************************************************************
void Count_bisn::SubFromRemain(double sum,int k)
 {
 if(k) remain_dollar-=sum;
 else Count_priv::SubFromRemain(sum,0);
 }
//************************************************************************
//Function Count_bisn::GetDollars returns remain in dollars
//Parameters:none
//Return Value:double-->return remain in $
//**************************************************************************
double Count_bisn::GetDollars()
{
return remain_dollar;
}
//************************************************************************
//Function Count_bisn::show(int x,int y) shows the remain in $
//Parameters:int,int-->coordinates
//Return Value:none
//**************************************************************************
void Count_bisn::show(int x,int y)
 {
 Count_priv::show(x,y);
 gotoxy(x,y+4);
 cout.setf(ios::fixed);
 cout<<" You have     :"<<setprecision(2)<<remain_dollar<<" dollars";
 }

