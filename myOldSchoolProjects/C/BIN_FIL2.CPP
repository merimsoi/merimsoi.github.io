#include<stdio.h>
#include<string.h>

int main()
{
FILE *fp;
char msg[]="this is a test message";
char str[80],ch;
fp=fopen("TEST.txt","w+");
if(fp==NULL)
{
printf("\nerror upon opening file.");
return 1;
}
fwrite(msg,strlen(msg)+1,1,fp);

fseek(fp,0L,SEEK_SET);
printf("\ncurrent position of pointer: %ld",ftell(fp));
fread(str,strlen(msg)+1,1,fp);
printf("\n%s",str);

fseek(fp,10L,SEEK_SET);
printf("\ncurrent position of pointer: %ld",ftell(fp));
fread(str,strlen(msg)+1,1,fp);
printf("\n%s",str);

fseek(fp,-5L,SEEK_END);
printf("\ncurrent position of pointer: %ld",ftell(fp));
fread(str,strlen(msg)+1,1,fp);
printf("\n%s\n\n",str);

rewind(fp);
while(!feof(fp))
{
fseek(fp,1,SEEK_CUR);
fread(&ch,sizeof(char),1,fp);
printf("%c ",ch);
}
fclose(fp);
return 0;
}
