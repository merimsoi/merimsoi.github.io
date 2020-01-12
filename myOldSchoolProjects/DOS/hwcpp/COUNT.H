#include"include.h"
#ifndef _Count
#define _Count
class List;
extern List list_of_client;
//***************************************************************************
//Class Data is absract class for creating one item in the list of client
//***************************************************************************
class Data
{
 public:
   friend class List;
   Data() { next=NULL;  }
   virtual void show(int,int)=0;             //virtual functions of Data
   virtual void AddToRemain(double,int)=0;
   virtual void SubFromRemain(double,int)=0;
   virtual char* GetN()=0;
   void SetNext(Data* new_block) { next=new_block; }
 private:
   Data* next;
};
//**************************************************************************
//Class List is list of client
//**************************************************************************
class List
 {
 public:
  List() { Head=NULL; End=NULL; }
  void Add(Data *new_block);          //function to add new client
  void Delete(long);                  //function to delete the client
  int IsPresent(long);                //function to check if client present yet
  Data& Find(long);                   //function to find the client
 private:
  Data *Head;                         //pointer to head of list
  Data *End;                          //pointer to end of list
};
//****************************************************************************
//Class Count_priv is inherited from Data to create client with private account
//****************************************************************************
class Count_priv:public Data
{
 public:
  friend class List;
  Count_priv(char*,char*,long);
  ~Count_priv();
  inline void AddToRemain(double,int);  //function to add money
  inline void SubFromRemain(double,int);//function to sub money
  inline char* GetN();                  //function to get name of class
  inline void show(int,int);            //function to show state of account
  inline double GetShkalim();           //function to get remain in shekels
 protected:
  char* name;                          //name of the client
  char* address;                       //address of the client
  long id;                             //i.d of the client
  double remain_shekel;                //remain in shekels of the client
};
//****************************************************************************
//Class Count_bisn is inherited from Count_priv to create client with business
//account
//****************************************************************************
class Count_bisn:public Count_priv
{
 public:
  Count_bisn(char*,char*,long);
  inline float GetStan();               //function to get the standard
  inline void AddToRemain(double,int);  //function to add money
  inline void SubFromRemain(double,int);//function to sub money
  inline void show(int,int);            //function to show remain in $
  inline char* GetN();                  //function to get name of class
  inline double GetDollars();           //function to get remain in $
 private:
  float standard;                      //standard
  double remain_dollar;                //remain in $
};
#endif