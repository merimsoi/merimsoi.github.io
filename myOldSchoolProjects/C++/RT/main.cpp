#include"define.h"              //Include file with definition.
struct Data                     //Define struct Data.
{
int a;                          //Define member of
int b;                          //struct Data(a,b).
};
struct MyTlsIndex               //Define struct MyTlsIndex.
{
void* Ptr;                      //Define member of struct MyTlsIndex(Ptr).
};
extern void *DwTlsIndex,*Pdata; //Define two extern poiners to type void*.
void main()
{
int ch,flag=1;char ans;        //Define local variables.
void *P,*Previos;              //Define two local pointers to type void*.
DwTlsIndex=TlsAlloc();         //Involking the function TlsAlloc() for
			       //allocation memory to MyTlsIndex.
			       //DwTlsIndex pointed to it.
((struct MyTlsIndex*)DwTlsIndex)->Ptr=NULL;//Initializing pointer Ptr
					   //in struct MyTlsIndex.
Pdata=NULL;                                //Initializing pointer Pdata.
do                                         //Loop do-while.
{
clrscr();                                  //Clear the screen.
printf("\nTlsIndex was allocated\n");     //Print menu.
puts("\
       1-For enter Data\n\
       2-For set Data in TlsIndex\n\
       3-For get Data from TlsIndex\n\
       4-For exit");
scanf("%d",&ch);                   //Input operation from menu in variable ch.
switch (ch)                       //Check operation
{
//Operation 1:check if Pdata pointed to Data or no.
//If no-->allocate memory for Data,if yes-->assign to Previos  Pdata,
//and for Pdata allocate new memory.After this receive from user two
//values (a and b) and assign them to memory allocating to Pdata.
case 1:if(!Pdata)Pdata=malloc(sizeof(Data));
       else{Previos=Pdata;Pdata=malloc(sizeof(Data));}
       printf("Enter a:");
       scanf("%d",&(((struct Data*)Pdata)->a));
       printf("Enter b:");
       scanf("%d",&(((struct Data*)Pdata)->b));
       break;
//Operation 2:check if MyTlsIndex save Data(involke function TlsGetValue).
//If yes-->question about the previos Data.If user want overwrite it-->
//release previos Data and save new(involke function TlsSetValue),
//else return to menu.
//If no-->save Data(involke function TlsSetValue)if it was entered.
case 2:if(TlsGetValue(DwTlsIndex))
	 {
	  for(;;)
	   {
	   printf("\nOVERWRITE PREVIOUS DATA?(Y/N):");
	   fflush(stdin);
	   scanf("%c",&ans);
	   if(ans=='y'||ans=='Y'||ans=='n'||ans=='N')break;
	   }
	   if(ans=='y'||ans=='Y')
	       {
	       free(Previos);
	       if(TlsSetValue(DwTlsIndex,Pdata))
	       printf("\nNew Data saved in TlsIndex");
	       }
	 }
      else if(TlsSetValue(DwTlsIndex,Pdata))
	   printf("\nYou saved Data in TlsIndex");
	   else printf("\nNo existing Data");
      getch();
      break;
//Operation 3:check if MyTlsIndex save Data(involke function TlsGetValue)
//if yes-->print it,if no-->print about absence of Data.
case 3:if(P=TlsGetValue(DwTlsIndex))
       printf(" A=%d\n B=%d",((struct Data*)P)->a,((struct Data*)P)->b);
       else printf("No Data in TlsIndex");
       getch();
       break;
//Operation 4:exit from menu.Assign to flag=0.
case 4:flag=0;break;
//Ather operation-->error.
default:printf("\nIllegal operation");getch();break;
}
}while(flag);               //Loop body executed if flag=1
free(Pdata);               //Release memory that allocated for Data
if(TlsFree(DwTlsIndex))    //Release memory that allocated for MyTlsIndex
			   //(involke function TlsFree)
printf("\nThe TlsIndex was released");
getch();
}
