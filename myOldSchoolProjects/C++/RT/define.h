#include<stdio.h>                   //include files stdio.h,alloc.h,conio.h
#include<alloc.h>
#include<conio.h>
#ifndef Bool                       //If Bool not defined
typedef enum {false=0,true}Bool;   //Define type Bool
#endif
extern void *TlsAlloc(void);          //Define extern function TlsAlloc
extern Bool TlsFree(void*);           //Define extern function TlsFree
extern void* TlsGetValue(void*);      //Define extern function TlsGetValue
extern Bool TlsSetValue(void*,void*); //Define extern function TlsSetValue