#include<stdio.h>
#include<alloc.h>
main()
{
int num_rows,num_cols;
int j,i;
int *(*arrpoint);//pointer to pointer to int
printf("\nenter number of rows==>");scanf("%d",&num_rows);
printf("\nenter number of colomns==>");scanf("%d",&num_cols);

 //allocation
 arrpoint=(int**)malloc(num_rows*sizeof(int*));
 for(j=0;j<num_rows;j++)
 *(arrpoint+j)=(int*)malloc(num_cols*sizeof(int));

 //giving values to matrix entries
 for(j=0;j<num_rows;j++)
 for(i=0;i<num_cols;i++)
 *((*(arrpoint+j))+i)=i+j*3;
 //arrpoint[j][i]=i+j*3

 //print the matrix
 printf("\n the matrix is:\n\n");
 for(j=0;j<num_rows;j++)
 {
 for(i=0;i<num_cols;i++)
 printf("%4d",arrpoint[j][i]);
 printf("\n");
 }
 //free
 for(j=0;j<num_rows;j++)
 free(arrpoint[j]);
 free(arrpoint);
 }
