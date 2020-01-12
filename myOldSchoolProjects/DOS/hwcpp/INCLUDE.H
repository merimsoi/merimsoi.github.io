#ifndef _Include
#define _Include
#include<iostream.h>
#include<conio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<strstream.h>
#include<dos.h>
#include<iomanip.h>
void clear();                   //function to clear the window
void Message();
void Message1();                //Message()...Message6() functions to messages
void Message2();                //for user
void Message3();
void Message4();
void Message5();
void Message6();
void NewCount();                //function for opening new account
void PutTo(long);               //function for puting money
void Close(long);               //function for closing the account
double Enter_sum();             //function for entering suma
void TakeFrom(long);            //function for taking money from account
void InitMainMenu();            //function of main menu
void GetName(char*);            //function for inputing name
int Bound(double,int);          //function for checking the suma from input
void Check_count(long);         //function for geting information about the account
void GetAddress(char*);         //function for inputing the address
void Operation(int,long);       //function to operations
long GetTd(int,int,int,int);    //function for getting i.d

int LittleMenu(int,int,int,int);//functions to menu
int LittleMenu2(int,int,int,int);
#endif
