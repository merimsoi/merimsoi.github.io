#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int scan(void);
int scan(void)
{int a; a=getch();
if (a==0) a=getch();return(a);}
main()
{
clrscr();
FILE *fp;
char k;
char str[6];
int r[100];
int i,j,m,cur,status;
if ((fp=fopen("d:\\borlandc\\bin\\ira\\irina.txt","r"))==NULL)
{printf("\nerror upon opening file");
return 1;
}
fseek(fp,0,SEEK_END);
cur=ftell(fp);
rewind(fp);
m=ftell(fp);
i=0;
while (m<cur)
{
m=ftell(fp);
k=scan();
	if((m==0)&&(k=='b')) {printf("START.");getch();fclose(fp);exit(status-'0');}
	r[0]=0;
	if (k==13)  {
		     for(j=0;j<10;j++)
		    { fgets(str,70,fp);printf("%s",str);
		     m=ftell(fp);if(cur==m) {printf("\nEND.");getch();fclose(fp);exit(status-'0');}
		     }
		    r[++i]=ftell(fp);
		    }

	else if(k=='b') {i--;
			 fseek(fp,r[i],SEEK_SET);
			 for(j=0;j<10;j++)
			{fgets(str,70,fp);printf("%s",str);m=ftell(fp);
			if((m==0)&&(k=='b')) {printf("START.");getch();fclose(fp);exit(status-'0');}
			}
			fseek(fp,r[i],SEEK_SET);
			}
}
}