#include"define.h"          //Include file with definition
struct Data                 //Define struct Data
{
int a;                      // Define a and b(member of Data)
int b;
};
struct MyTlsIndex           //Define struct MyTlsIndex
{
void *Ptr;                  //Define pointer to void*
};
void *DwTlsIndex,*PData;   //Define two pointers to void*
//------------------Function TlsAlloc---------------------------------------
//This function allocated memory for struct MyTlsIndex and return
//pointer to the first byte of the allocated memory(type void*)
//or a NULL pointer in case of an error
void* TlsAlloc(void)
{
DwTlsIndex=malloc(sizeof(MyTlsIndex));
return(DwTlsIndex);
}
//------------------Function TlsSetValue------------------------------------
//This function receive as parametres two pointers DwTlsIndex(pointed to
//struct MyTlsIndex(type void*)) and PData(pointed to struct Data(type void*))
//and assigned value of pointer Pdata to pointer Ptr(member of struct
//MyTlsIndex).If in beginning position DwTlsIndex or Pdata equal to NULL
//function return false,else executed assignment and return true.
Bool TlsSetValue(void* DwTlsIndex,void* Pdata)
{
if(DwTlsIndex!=NULL&&Pdata!=NULL)
{
((struct MyTlsIndex*)DwTlsIndex)->Ptr=Pdata;
return(true);
}
else return(false);
}
//-----------------Function TlsGetValue-------------------------------------
//This function receive as parameter DwTlsIndex-->pointer to struct
//MyTlsIndex(type void*) and return Ptr-->pointer to struct Data(type void*).
//If Ptr don't point to Data return NULL.
void *TlsGetValue(void *DwTlsIndex)
{
 return(((struct MyTlsIndex*)DwTlsIndex)->Ptr);
}
//----------------Function TlsFree-----------------------------------------
//This function receive as parameter DwTlsIndex-->pointer to struct
//MyTlsIndex(type void*).If DwtlsIndex!=NULL ==>release the storage
//previously allocated and return true,else return false
Bool TlsFree(void *DwTlsIndex)
{
if(DwTlsIndex==NULL)return(false);
else
{
free(DwTlsIndex);
return(true);
}
}