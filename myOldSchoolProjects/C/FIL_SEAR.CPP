#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<alloc.h>
struct
{
struct
{
char first[6];
char last[12];
}name;
char phone[7];
}pers;
char findname[15];
int binary_search()
{
int i,num,cur_pos;
int high,low=0,mid=0,cond,cur=0;
FILE *fp;
char *filename="irina1.txt";
if((fp=fopen(filename,"r"))==NULL)
{
printf("/nerror opening file %s for reading.",filename);
return(-1);
}
fseek(fp,0,SEEK_END);
num=(ftell(fp)/sizeof(pers));
low=0;
high=num-1;
rewind(fp);
while(low<=high)
{
cur=mid;
mid=(high+low)/2;
fseek(fp,(mid-cur-1)*sizeof(pers),SEEK_CUR);
fread(&pers,sizeof(pers),1,fp);
if((cond=strcmp(pers.name.last,findname))>0)
high=mid-1;
else if(cond<0)
low=mid+1;
else {fclose(fp);
      return 0;
      }
   }
  fclose(fp);
  return 1;
  }
  main()
  {
  int bin;
  printf("\nenter name of person to find: ");
  gets(findname);
  if((bin=binary_search())==0)
  printf("\nname-%s %s \ntel -%s",pers.name.first,pers.name.last,pers.phone);
  else if(bin==1)
  printf("\nperson is not in list.");
  }

