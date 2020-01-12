#include"include.h"
#include"window.h"
#include"info.h"
#include"menu.h"
#include"input.h"
#include"count.h"
int Common(Data&,int);
List list_of_client;                               //list of client
//*************************************************************************
//Function main() involve the main menu
//Parameters:none
//Return Value:none
//*************************************************************************
void main()
 {
 InitMainMenu();
 }
//***************************************************************************
//Function clear() clears the screen
//Parameters:none
//Return Value:none
//***************************************************************************
void clear()
{
 window(1,1,80,25);
 textbackground(0);
 clrscr();
}
//***************************************************************************
//Function InitMainMenu  shows main menu
//Parameters:none
//Return Value:none
//***************************************************************************
void InitMainMenu()
{
 int pos;
 long id;
 clear();
 char *array[4]={"New account\n","Close account\n","Operation","Exit"};
 Window* PointToWindow=new Menu(33,10,48,15);//create main menu
 assert(PointToWindow);                      //check memory
 ((Menu*)PointToWindow)->SetNumRows(4);      //set number the rows in the menu
 ((Menu*)PointToWindow)->Set_Rows(4,array);  //set text of menu
 PointToWindow->ShowWindow();                //show menu
 pos=((Menu*)PointToWindow)->GetPosition();   //get position of bar
 switch(pos)
  {
   //ESC
   case 1:exit(0);                          //exit
   //new account
   case 2:NewCount();break;
   //close account
   case 3: id=GetTd(40,14,67,16);           //function to enter i.d
	   if(list_of_client.IsPresent(id)) //if present account to this i.d
	     {
	      Close(id);                    //yes?function to close account
	      break;
	     }
	   else
	       {
	       Message();                   //no? error message
	       getch();
	       InitMainMenu();
	       }
   //operations
   case 4: id=GetTd(40,14,67,16);          //function to enter i.d
	   if(list_of_client.IsPresent(id))//if present account to this i.d
	     {
	      Operation(1,id);             //yes?function to operations
	      break;
	     }
	   else
	       {
	       Message();                   //no? error message
	       getch();
	       InitMainMenu();
	       }
   //exit
   case 5:exit(0);                         //exit
  }
 delete PointToWindow;
}
//**************************************************************************
//Function NewCount opens new account
//Parameters:none
//Return Value:none
//**************************************************************************
void NewCount()
{
 int pos;
 clear();
 Count_priv* client_pr;
 Count_bisn* client_bs;
 Window* PointToWindow;
 char* name=new char[30];
 assert(name);
 GetName(name);                       //involve function to input name
 char* address=new char[30];
 assert(address);
 GetAddress(address);                 //involve function to input address
 long id=GetTd(25,9,65,11);           //involve function to input i.d
 if(list_of_client.IsPresent(id))     //check if client exist
   {                                  //if yes ->message
    PointToWindow=new Info(20,14,64,16);
    assert(PointToWindow);
    ((Info*)PointToWindow)->SetMessage(" You have the account yet!Press any key...");
    ((Info*)PointToWindow)->SetColor(4);
    ((Window*)PointToWindow)->SetColorDraw(14);
    ((Info*)PointToWindow)->SetOffset(2,2);
    PointToWindow->ShowWindow();
    delete PointToWindow;
    getch();
    }
 else
    {
    do
     {
     pos=LittleMenu(30,11,49,14);       //sub menu
     }while(pos==1);
    switch(pos)
     {
     //selected private in sub menu
      case 2:
	     client_pr=new Count_priv(name,address,id);//create private account
	     assert(client_pr);
	     list_of_client.Add(client_pr);            //add to list of client
	     break;
      //selected business in sub menu
      case 3:
	     client_bs=new Count_bisn(name,address,id);//create private account
	     assert(client_bs);
	     list_of_client.Add(client_bs);            //add to list of client
	     break;
     }
 Window* PointToWindow=new Info(16,16,64,18);         //message
 assert(PointToWindow);
 ((Info*)PointToWindow)->SetMessage(" Thank you for opening the account in our bank.");
 ((Info*)PointToWindow)->SetColor(1);
 ((Window*)PointToWindow)->SetColorDraw(5);
 ((Info*)PointToWindow)->SetOffset(2,2);
 PointToWindow->ShowWindow();
 delete PointToWindow;
 delete name;
 delete address;
 delay(1200);
 }
 InitMainMenu();
}
//**************************************************************************
//Function Close is closed the account
//Parameters:long-->number i.d
//Return Value:none
//**************************************************************************
void Close(long id)
{
 double sum,dol;
 Data& ptr=list_of_client.Find(id);              //find client in list
 int ch=Common(ptr,1);                       //check kind of account
 if(ch==1)                                   //if private?
	  {
	  sum=((Count_priv&)ptr).GetShkalim();   //if remain in shekels is positive
	  if(sum<0) Message2();                  //no? message
	  else Message4();                       //yes?message
	   }
 else if (ch==0)                             //if bussiness?
	  {
	   dol=((Count_bisn &)ptr).GetDollars(); //get remain in dollars
	   sum=dol*((Count_bisn &)ptr).GetStan();//sum=dollars-->shekels
	   ptr.AddToRemain(sum,0);               //add sum to remain shekel
	   ptr.SubFromRemain(dol,1);             //sub sum from remain dollars
	   clear();
	   Message3();
	   Check_count(id);                      //show information about account
	   if(((Count_priv&)ptr).GetShkalim()<0) //if remain in shekels is positive
	    Message2();                          //no?message
	   else Message4();                      //yes?message
	  }
 list_of_client.Delete(id);
 InitMainMenu();
}
//**************************************************************************
//Function Operation shows sub menu with operations
//Parameters:int,long-->variable to help,number i.d
//Return Value:none
//**************************************************************************
void Operation(int k,long id)
{
 int pos;
 Window* PointToWindow;
 Message6();
 char *array[3]={"Check balance\n","Take from account\n","Put to account"};
 if(k)
  PointToWindow=new Menu(45,16,65,20);        //create operation menu
 else PointToWindow=new Menu(30,11,50,15);
 assert(PointToWindow);                        //check memory
 ((Menu*)PointToWindow)->SetNumRows(3);        //set number the rows in the menu
 ((Menu*)PointToWindow)->Set_Rows(3,array);    //set rows of menu
 ((Window*)PointToWindow)->SetColor(2);
 PointToWindow->ShowWindow();                  //show menu
 pos=((Menu*)PointToWindow)->GetPosition();    //get position of sub menu
 switch(pos)
  {
  //Esc
  case 1:InitMainMenu();break;              //involve main menu
  //check balance
  case 2:clear();Check_count(id);           //show information about account
	 Operation(0,id);
	 break;
  //take from account
  case 3:TakeFrom(id);break;                //involve function to take from account
  //end to account
  case 4:PutTo(id);break;                  //involve function to put to account
  }
 delete PointToWindow;
}
//***************************************************************************
//Function Check_count shows information about current state of account
//Parameters:long-->number i.d
//Return Value:none
//***************************************************************************
void Check_count(long id)
{
 Data& ptr=list_of_client.Find(id);           //find client in list

 Window* PointToWindow=new Info(10,5,70,15);
 assert(PointToWindow);
 ((Info*)PointToWindow)->SetColor(5);
 ((Window*)PointToWindow)->SetColorDraw(14);
 ((Info*)PointToWindow)->SetMessage("Information about your account.");
 ((Info*)PointToWindow)->SetOffset(3,2);
 PointToWindow->ShowWindow();
  ptr.show(3,4);
  gotoxy(3,10);
  cout<<" Press any key...";
  delete PointToWindow;
  getch();
  clear();
}
//*************************************************************************
//Function PutTo adds inputed suma to account(shekels or $)
//Parameters:long-->number i.d
//Return Value:none
//*************************************************************************
void PutTo(long id)
{
 Data& ptr=list_of_client.Find(id);       //find client in list
 int ch=Common(ptr,0);                    //get kind of account
 if(ch==2)                                //if Esc in sub menu
   {
   clear();
   Operation(0,id);
   }
 if(ch==1)clear();
 double sum=Enter_sum();                  //involve function to inputing sum
 if(ch) ptr.AddToRemain(sum,0);           //add to shekels
 else ptr.AddToRemain(sum,1);             //add to $
 Message1();
 Operation(0,id);
}
//***************************************************************************
//Function TakeFrom subs inputed suma from account(shekels or $)
//Parameters:long-->number i.d
//Return Value:none
//***************************************************************************
void TakeFrom(long id)
{
 Data& ptr=list_of_client.Find(id);       //find client in list
 int ch=Common(ptr,0);                    //get kind of account
 if(ch==2)                                //if Esc in sub menu
   {
   clear();
   Operation(0,id);
   }
 if(ch==1)clear();
 double sum=Enter_sum();                  //involve function to inputing sum
 if(Bound(sum,ch))                        //check bound of suma
   {
   if(ch) ptr.SubFromRemain(sum,0);       //sub. from shekels
   else ptr.SubFromRemain(sum,1);         //sub. from $
   Message1();
   }
   Operation(0,id);
}
//**************************************************************************
//Function LittleMenu shows the sub menu for kind of account
//Parameters:int,int,int,int-->coordinates of sub menu
//Return Value:int-->position of bar menu
//**************************************************************************
int LittleMenu(int x1,int y1,int x2,int y2)
{
 char *array[2]={"Private account\n","Business account\n"};
 Window* PointToWindow=new Menu(x1,y1,x2,y2);
 assert(PointToWindow);
 ((Menu*)PointToWindow)->SetNumRows(2);        //set number the rows in the menu
 ((Menu*)PointToWindow)->Set_Rows(2,array);    //set rows of menu
 ((Menu*)PointToWindow)->SetColor(5);
 PointToWindow->ShowWindow();                  //show menu
 int pos=((Menu*)PointToWindow)->GetPosition();
 delete PointToWindow;
 return pos;
}
//***************************************************************************
//Function LittleMenu2 shows sub menu for kind of money
//Parameters:int,int,int,int-->coordinates of sub menu
//Return Value:int-->position of bar menu
//***************************************************************************
int LittleMenu2(int x1,int y1,int x2,int y2)
{
 char *array[2]={"Shekeles\n","Dollars\n"};
 Window* PointToWindow=new Menu(x1,y1,x2,y2);
 assert(PointToWindow);
 ((Menu*)PointToWindow)->SetNumRows(2);        //set number the rows in the menu
 ((Menu*)PointToWindow)->Set_Rows(2,array);    //set rows of menu
 ((Menu*)PointToWindow)->SetColor(14);
 PointToWindow->ShowWindow();                  //show menu
 int pos=((Menu*)PointToWindow)->GetPosition();
 delete PointToWindow;
 clear();
 return pos;
}
//***************************************************************************
//Function Message shows message for user
//Parameters:none
//Return Value:none
//***************************************************************************
void Message()
{
 Window* PointToWindow=new Info(13,6,67,8);
 assert(PointToWindow);
 ((Info*)PointToWindow)->SetMessage("You haven't the account in our bank.Press any key...");
 ((Info*)PointToWindow)->SetColor(4);
 ((Window*)PointToWindow)->SetColorDraw(14);
 ((Info*)PointToWindow)->SetOffset(3,2);
 PointToWindow->ShowWindow();
 delete PointToWindow;
}
//***************************************************************************
//Function Message1 shows message for user
//Parameters:none
//Return Value:none
//***************************************************************************
void Message1()
{
 Window* PointToWindow=new Info(25,10,55,12);
 assert(PointToWindow);
 ((Info*)PointToWindow)->SetColor(5);
 ((Window*)PointToWindow)->SetColorDraw(14);
 ((Info*)PointToWindow)->SetMessage("Operation was successfull.");
 ((Info*)PointToWindow)->SetOffset(3,2);
 PointToWindow->ShowWindow();
 delay(1200);
 delete PointToWindow;
 clear();
}
//***************************************************************************
//Function Message2 shows message for user
//Parameters:none
//Return Value:none
//***************************************************************************
void Message2()
{
 Window* PointToWindow=new Info(10,18,73,20);
 assert(PointToWindow);
 ((Info*)PointToWindow)->SetColor(4);
 ((Window*)PointToWindow)->SetColorDraw(14);
 ((Info*)PointToWindow)->SetMessage("You are in minus!Imposible close the account!Press any key...");
 ((Info*)PointToWindow)->SetOffset(3,2);
 PointToWindow->ShowWindow();
 getch();
 delete PointToWindow;
 clear();
 InitMainMenu();
}
//***************************************************************************
//Function Message3 shows message for user
//Parameters:none
//Return Value:none
//***************************************************************************
void Message3()
{
 Window* PointToWindow=new Info(15,17,67,19);
 assert(PointToWindow);
 ((Info*)PointToWindow)->SetColor(1);
 ((Window*)PointToWindow)->SetColorDraw(14);
 ((Info*)PointToWindow)->SetMessage("Remittance all dollars to shekels was successful!");
 ((Info*)PointToWindow)->SetOffset(3,2);
 PointToWindow->ShowWindow();
 delete PointToWindow;
 }
//***************************************************************************
//Function Message4 shows message for user
//Parameters:none
//Return Value:none
//***************************************************************************
void Message4()
{
 clear();
 Window* PointToWindow=new Info(15,10,65,12);
 assert(PointToWindow);
 ((Info*)PointToWindow)->SetColor(5);
 ((Window*)PointToWindow)->SetColorDraw(14);
 ((Info*)PointToWindow)->SetMessage("Get back your cash per shekels!Press any key...");
 ((Info*)PointToWindow)->SetOffset(3,2);
 PointToWindow->ShowWindow();
 getch();
 delete PointToWindow;
 clear();
}
//***************************************************************************
//Function Message5 shows message for user
//Parameters:none
//Return Value:none
//***************************************************************************
void Message5()
{
 Window* PointToWindow=new Info(30,18,47,20);
 assert(PointToWindow);
 ((Info*)PointToWindow)->SetColor(4);
 ((Window*)PointToWindow)->SetColorDraw(14);
 ((Info*)PointToWindow)->SetMessage("Wrong input!!!");
 ((Info*)PointToWindow)->SetOffset(3,2);
 PointToWindow->ShowWindow();
 delay(1500);
 window(30,18,47,20);
 textbackground(0);
 clrscr();
 delete PointToWindow;
}
//***************************************************************************
//Function Message6 shows message for user
//Parameters:none
//Return Value:none
//***************************************************************************
void Message6()
{
 Window* PointToWindow=new Info(25,22,53,24);
 assert(PointToWindow);
 ((Info*)PointToWindow)->SetColor(1);
 ((Window*)PointToWindow)->SetColorDraw(14);
 ((Info*)PointToWindow)->SetMessage("To return back press Esc.");
 ((Info*)PointToWindow)->SetOffset(3,2);
 PointToWindow->ShowWindow();
 delete PointToWindow;
}
//****************************************************************************
//Function GetName input the name
//Parameters:char*-->pointer to name
//Return Value:none
//****************************************************************************
void GetName(char* name)
{
 Window* PointToWindow=new Input(15,5,55,7);
 assert(PointToWindow);
 ((Input*)PointToWindow)->SetMessage(" Enter your name:");
 ((Input*)PointToWindow)->SetColor(1);
 ((Window*)PointToWindow)->SetColorDraw(5);
 ((Input*)PointToWindow)->SetOffset(2,2);
 PointToWindow->ShowWindow();
 strcpy(name,((Input*)PointToWindow)->Enter_data());
 strcat(name,NULL);
 delete PointToWindow;
}
//***************************************************************************
//Function GetAddress input the address
//Parameters:char*-->pointer to address
//Return Value:none
//***************************************************************************
void GetAddress(char *address)
{
 Window* PointToWindow=new Input(20,7,75,9);
 assert(PointToWindow);
 ((Input*)PointToWindow)->SetMessage(" Enter your address:");
 ((Input*)PointToWindow)->SetColor(5);
 ((Input*)PointToWindow)->SetOffset(2,2);
 PointToWindow->ShowWindow();
 strcpy(address,((Input*)PointToWindow)->Enter_data());
 strcat(address,NULL);
 delete PointToWindow;
}
//***************************************************************************
//Function GetTd input the i.d
//Parameters:int,int,int,int-->coordinates of window to input
//Return Value:long-->number i.d
//***************************************************************************
long GetTd(int x1,int y1,int x2,int y2)
{
 long id;
 do
 {
 Window* PointToWindow=new Input(x1,y1,x2,y2);
 assert(PointToWindow);
 ((Input*)PointToWindow)->SetMessage(" Enter your i.d:");
 ((Input*)PointToWindow)->SetColor(1);
 ((Window*)PointToWindow)->SetColorDraw(5);
 ((Input*)PointToWindow)->SetOffset(2,2);
 PointToWindow->ShowWindow();
 id=((Input*)PointToWindow)->Enter_data(id);
 delete PointToWindow;
 if(id==-1) Message5();
 }while(id==-1);
 return id;
}
//***************************************************************************
//Function Enter_sum input the suma
//Parameters:none
//Return Value:double-->suma
//***************************************************************************
double Enter_sum()
{
  int flag,point=0;
  char suma[30];
  do
  {
  flag=1;
  Window* PointToWindow=new Input(25,5,54,7);
  assert(PointToWindow);
  ((Input*)PointToWindow)->SetMessage(" Enter the sum:");
  ((Input*)PointToWindow)->SetColor(1);
  ((Window*)PointToWindow)->SetColorDraw(5);
  ((Input*)PointToWindow)->SetOffset(2,2);
  PointToWindow->ShowWindow();
  cin>>suma;
  for(int i=0;i<strlen(suma);i++)
   {
   if(suma[i]=='.')point++;                 //if suma have '.'
    if((!isdigit(suma[i])&&suma[i]!='.')||(suma[i]=='.'&& point>1))
			 {
			 Message5();       //if suma have not digit
			 flag=-1;          //or more then one '.'
			 break;
			 }
   }
  delete PointToWindow;
  if(flag==1)break;
  }while(flag==-1);
  double sum=_atold(suma);
  return sum;
 }
//***************************************************************************
//Function Bound check bound of suma.(if shekels<1000,$<250)
//Parameters:double,int-->suma,mode(shekel or $)
//Return Value:1-ok
//             0-not ok
//***************************************************************************
int Bound(double sum,int ch)
{
if((sum<=250&&!ch)||(sum<=1000&&ch==1))return 1;
else
  {
   Window* PointToWindow=new Info(20,10,60,12);
   assert(PointToWindow);
   ((Info*)PointToWindow)->SetColor(4);
   ((Window*)PointToWindow)->SetColorDraw(14);
   ((Info*)PointToWindow)->SetMessage("The limit is 250$ or 1000 shekeles!!!");
   ((Info*)PointToWindow)->SetOffset(3,2);
   PointToWindow->ShowWindow();
   delay(1300);
   delete PointToWindow;
   clear();
   return 0;
  }
}
//***************************************************************************
//Functions Common check kin of account,and if k=0 shows sub menu
//Parameters:Data&,int-->reference to client,variable to help
//Return Value:int-->0-operation with $
//                   1-operation with shekel
//                   2-Esc in sub menu
//***************************************************************************
int Common(Data& ptr,int k)
{int pos;
     if(strcmp(ptr.GetN(),"Count_bisn")==0)
	   {
	    if(!k)
	     {
	      pos=LittleMenu2(28,15,40,18);
	      if(pos==1)return 2;
	      }
	    else return 0;
	   }
     else return 1;
    if(pos==2) return 1;
    else if(pos==3)return 0;
return 0;                        //against the warning in time compiling
}

