#include<stdio.h>
main(int argc,char *argv[])
{
int i;
if(argc>1)
{
printf("%darguments passed\n\n",(argc-1));
for(i=1;i<argc;i++)
printf("arguments %d is %s \n",i,argv[i]);
}
else printf("no arguments passed\n");
}