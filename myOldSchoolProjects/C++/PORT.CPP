#include <stdio.h>
#include <dos.h>
#include<conio.h>
int main(void)
{
  int result;
  int port =0x60;
  clrscr();

  outport(0x60,0xEE);
  result = inport(port);
  printf("Word 1 read from port %X = 0x%X\n", port, result);

  outport(0x60,0xED);
//  result = inport(port);
  delay(10);
  outport(0x60,1);
  result = inport(port);
  printf("Word 2 read from port %X = 0x%X\n", port, result);

  return 0;
}
