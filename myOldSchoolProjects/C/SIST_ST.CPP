#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>
int main(void)
{
char buffer[128],**error_symb;long decimal;
int in_radix,out_radix;
*error_symb=buffer;**error_symb='\0';
fputs("sistema stislenia of number"\
       ":",stdout);
scanf("%d",&in_radix);
fputs("number "\
       ":",stdout);
fflush(stdin);
gets(buffer);
decimal=strtol(buffer,error_symb,in_radix);
if(decimal==LONG_MIN || decimal==LONG_MAX)
{perror("error\a");return 254;}
if(**error_symb)
{printf("\ano can be"\
	 "number %c\n",**error_symb);
	 return 255;}

fputs("sistema stislenia dla output of number(2..32)"\
      " :",stdout);
scanf("%d",&out_radix);
ltoa(decimal,buffer,out_radix);
fputs("result "\
       ":",stdout);
puts(buffer);
if(out_radix>10)
printf("simbols ot A do %c sootvetstvuut"\
       "desatichn znakam ot 10 do %2d\n",
       'A'+(out_radix-11),out_radix-1);
       return 0;
       }