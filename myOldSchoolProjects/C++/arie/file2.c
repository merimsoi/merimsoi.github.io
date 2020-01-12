#include"file.h"
//**************************************************************************
//fuction input_command() without parametres, 
//recieves input from keyboard to array and return number of letters in row. 
//**************************************************************************
int input_command(void)
{
putc('$',stdout);
do
{
input[i++]=getchar();
num_in_row++;
}while (i-1<=80&&input[i-1]!=10);
input[i-1]=0;
strcpy(input_dup,input);
if(i-1>80) error();
return(num_in_row-1);
}
//************************************************************************
//function uncoding_input() gets as parameter pointer to input array,
//build array of pointers to earch word from input,
//function return number of words of command.
//************************************************************************
int uncoding_input(char* input)
{
int num_word=0;
do{
if (!num_word)
words[num_word]=strtok((input)," ");
else
{a=strtok(NULL," ");
if(a!=NULL) words[num_word]=a;
else break;}
num_word++;
 }while(1);
return(num_word);
 }
//************************************************************************
//function execute() runs system command contained by array result.
//************************************************************************ 
void execute(char* result)
{system(result);}
//***********************************************************************
//function error() prints error message.
//***********************************************************************
void error(void)
{if(!error_flag)
{printf ("my_shell error:%s\n",input_dup);
error_flag=1;}}



