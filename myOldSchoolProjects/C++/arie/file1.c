#include"file.h"
//**************************** main ***************************************
int main(void)
{
int num_word;
while(1)
  {
  error_flag=0;
  strcpy(input,"");
  i=0;num_in_row=0;
  if(!input_command())continue;
  if(error_flag)continue;
  num_word=uncoding_input(input);
  build_result(input,num_word);
  }
}
//************************************************************************
//function build_result() calls to functions build1(),build2(),build3()
//or error() according to number of words in the input command.
//************************************************************************ 
void build_result(char* input,int num_word)
{
switch(num_word)
{case 1:build1();
 if(!error_flag)execute(result);
 break;
 case 2:build1();build2();
 if(!error_flag)execute(result);
 break;
 case 3:build1();build2();build3();
 if(!error_flag)execute(result);
 break;
 default:error();}
}
//************************************************************************
//function build1() is called if input command have only one word,
//copy it to array result.
//************************************************************************ 
void build1(void)
{
if (strcmp(words[0],"exit")==0)exit(0);
else if(strcmp(words[0],"list_files")==0)strcpy(result,"ls ");
     else if (strcmp(words[0],"user_list")==0)strcpy(result,"finger ");
       	  else error();
}
//***********************************************************************
//function build2() is called if input command have two words,
//adds second to array result,that already contains first word.
//*********************************************************************** 
void build2(void)
{
if(strcmp(words[1],"-long")==0)strcat(result,"-l ");
else if(strcmp(words[1],"-short")==0)strcat(result,"-s ");
     else if(strcmp(words[1],"-execute")==0)strcat(result,"-l | grep -e '^-..x......'" );
          else strcat(result,words[1]);
}
//************************************************************************
//function build3() is called if input command have 3 words,
//add third word(username) to array result.
//************************************************************************ 
void build3(void)
{strcat(result,words[2]);}



