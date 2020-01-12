#include<stdio.h>
#include<alloc.h>
main()
{
int num_row,num_col;
int i,j;
int sum,sum1,sum2=0,av;
int *(*arrpoint);
printf("enter number of puple");scanf("%d",&num_row);
printf("input number of subject");scanf("%d",&num_col);

arrpoint=(int**)malloc(num_row*sizeof(int*));
for(j=0;j<num_row;j++)
*(arrpoint+j)=(int*)malloc(num_col*sizeof(int));

for(j=0;j<num_row;j++)
for(i=0;i<num_col;i++)
scanf("%d",&arrpoint[j][i]);

for(i=0;i<num_row;i++)
{
sum=0;sum1=0;
for(j=0;j<num_col;j++)
sum=sum+arrpoint[i][j];
sum1=sum/num_col;
printf("\nthe averedge of %d puple is %d",i+1,sum1);
sum2=sum2+sum1;
}
av=sum2/num_row;
printf("\nthe common averedge is %d",av);

for(j=0;j<num_row;j++)
free(arrpoint[j]);
free(arrpoint);
}