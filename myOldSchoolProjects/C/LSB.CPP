#include<stdio.h>
typedef struct
{
unsigned b:1;
}bit;
typedef union
{
int data;
bit lsb;
}
bits;
int isodd(int i)
{
bits b;
b.data=i;
return b.lsb.b;
}
main()
{
int i=7,j=10;
printf("\n%d is %s",i,(isodd(i)?"odd":"even"));
printf("\n%d is %s",j,(isodd(j)?"odd":"even"));
printf("\n");
}