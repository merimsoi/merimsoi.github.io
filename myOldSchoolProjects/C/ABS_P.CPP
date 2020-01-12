#include<stdio.h>
void chs(int *a);
int x;
main()
{
printf("\nenter number ");
scanf("%d",&x);
printf("***********\n");
chs(&x);
printf("%d",x);
}
void chs(int *a)
{
*a=-(*a);
}