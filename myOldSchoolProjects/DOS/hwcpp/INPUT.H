#include"info.h"
#ifndef _Input
#define _Input
//************************************************************************
//Class Input is inherited from Info.Ability input the data
//************************************************************************
class Input:public Info
{
public:
 Input(int,int,int,int);
 long Enter_data(long);         //enter i.d(digits)
 char* Enter_data();            //enter text
};
#endif