#include<stdio.h>
main()
{
FILE *fp;
char filename[20];
int arr[]={34,65,66,4};
int arrread[4],i;
printf("\n\nenter name of file to be created=>");
gets(filename);
fp=fopen(filename,"wb");
if(fp==NULL)
{printf("\nerror upon opening file(for output)");
return(1);
}
fwrite(arr,sizeof(arr),1,fp);
fclose(fp);
printf("a binary file %s was created.\n",filename);
printf("we are going now to read the file and print its content\n");
fp=fopen(filename,"rb");
if(fp==NULL)
{printf("\nerror upon opening file(for input)!");
return(1);
}
fread(arrread,sizeof(arrread),1,fp);
fclose(fp);
for(i=0;i<sizeof(arrread)/sizeof(int);i++)
printf("%d " ,arrread[i]);
printf("\ntry to print the file '%s' by getting to DOS ",filename);
printf("and using TYPE\n");
}