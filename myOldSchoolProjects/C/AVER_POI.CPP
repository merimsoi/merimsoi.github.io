#include<stdio.h>
#include<alloc.h>
main()
{
int *arr;
int i, num,sum=0;
puts("number of elements to be calculated");
scanf("%d",&num);
arr=(int*)malloc(num*sizeof(int));
if(arr==NULL)
{
puts("ERROR upon memory allocation");
return 1;
}
for(i=0;i<num;i++)
{printf("enter %d element:",i+1);
scanf("%d",&arr[i]);
sum+=arr[i];
}
puts("the average of");
for(i=0;i<num;i++)
printf(" %d ",arr[i]);
printf("\n\n is:%.2f",(float)sum/num);
free(arr);
}

