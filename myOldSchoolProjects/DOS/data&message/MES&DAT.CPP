#include<iostream.h>
#include<fstream.h>
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<dos.h>
void init(void);
void Dt(int pos);
void Rd(int pos);
int Get_count();
void Msg(int pos);
void MMnu(int pos);
void Read_mes(void);
void Read_all(void);
void Delete(char ch);
int  Write_mes(void);
int Write_data(void);
int Get_cntData(void);
void Read_letter(void);
void Delete_data(int ch);
int Is_present(char cnt);
void print(int num,int y);
void Choose_menu(int num);
char* input(int x,int y,int num);
void parameter(int x1,int y1,int x2,int y2);
void Cadre(int x1,int y1,int x2,int y2,int col);
static counter;
typedef struct {
char name[20];
char address[20];
char telephon[20];
}elem;
int cmp_elem(const void *,const void*);
elem dat[20];
int num_data=0;
int (*cmp)(const void*,const void*)={cmp_elem};
//*****************************************************************
class Menu
{
public:
Menu(int x1,int y1,int row,int col,int col1,int col2,char name[10]);
char* GetNameObj(void){return name;}
int Is_Down(int ch);
int Is_Up(int ch);
int Is_Enter(int ch);
int Is_Esc(int ch);
int GetPos(void){return pos;}
void Show(char mes[][16],int row,int col_bar,int fore_bar,int pos);
void Fone(int num);
void Cadre(int col);

private:
int x1,y1,x2,y2,col1,col2;
int pos;
int row;
char name[10];
};
Menu* PMenu;
//*********************************************************************
char main_mes[3][16]={"Messages"," Data"," Exit "};
char mes1[2][16]={"Write Message","Read Messages"};
char mes2[2][16]={"Write Data","Read Data"};
char mes3[2][16]={" All Data","By first letter"};
Menu Main_menu(230,100,3,10,11,1,"Main");
Menu Message(310,120,2,15,12,14,"Mess");
Menu Data(310,160,2,15,10,1,"Data");
Menu Rd_data(420,225,2,15,12,1,"Read");
//********************************************************************
Menu::Menu(int x1,int y1,int row,int col,int col1,int col2,char name[10])
{
Menu::x1=x1;
Menu::y1=y1;
Menu::x2=x1+col*13;
Menu::y2=y1+row*50;
Menu::row=row;
Menu::col1=col1;
Menu::col2=col2;
strcpy(Menu::name,name);
}
//*********************************************************************
Menu::Is_Down(int ch)
{
if(ch==80)
{
if(pos!=row-1)pos++;
else pos=0;
return 1;
}
else return 0;
}
//*********************************************************************
Menu::Is_Up(int ch)
{
if(ch==72)
{
if(pos!=0)pos--;
else pos=row-1;
return 1;
}
else return 0;
}
//**********************************************************************
int Menu::Is_Esc(int ch)
{
if(ch==27)return 1;
else return 0;
}
//**********************************************************************
Menu::Is_Enter(int ch)
{
if(ch==13)
{
if (strcmp(name,"Main")==0) MMnu(pos);
else if(strcmp(name,"Mess")==0) Msg(pos);
     else if(strcmp(name,"Data")==0) Dt(pos);
	  else if(strcmp(name,"Read")==0) Rd(pos);
return 1;
}
else return 0;
}
//**********************************************************************
void Menu::Fone(int num)
{
setfillstyle(1,num);
bar(0,0,640,480);
}
//**********************************************************************
void Menu::Show(char mes[][16],int row,int col_bar,int fore_bar,int pos)
{
Menu::pos=pos;
setcolor(col2);
setfillstyle(1,col1);
bar(x1,y1,x2,y2);
for(int i=0;i<row;i++)
{
if(i==pos)
{
setcolor(fore_bar);
setfillstyle(1,col_bar);
bar(x1+10,y1+15+i*40,x2-10,y1+40+i*40);
}
else
{
setcolor(col2);
setfillstyle(1,col1);
}
settextstyle(4, HORIZ_DIR,3);
outtextxy(x1+20,y1+10+i*40,mes[i]);
}
Cadre(0);
}
//***********************************************************************
void Menu::Cadre(int col)
{
  char i, j;
  setcolor(col);
  line(x1,y1,x2,y1);
  line(x1,y1+5,x2,y1+5);
  line(x1,y1,x1,y2);
  line(x1+5,y1,x1+5,y2);
  line(x2,y1,x2,y2);
  line(x2-5,y1,x2-5,y2);
  line(x1,y2,x2,y2);
  line(x1,y2-5,x2,y2-5);
 }
//**********************************************************************
void Choose_menu(int num)
{
//cleardevice();
Main_menu.Fone(8);
PMenu=&Main_menu;
Main_menu.Show(main_mes,3,1,11,0);
if (num==1){PMenu=&Data;PMenu->Show(mes2,2,1,10,0);num=0;}
for(;;)
{
int ch=getch();
if(ch==0)
{
ch=getch();
if(PMenu->Is_Down(ch)||PMenu->Is_Up(ch))
{
if(strcmp(PMenu->GetNameObj(),"Main")==0)
PMenu->Show(main_mes,3,1,11,PMenu->GetPos());
if(strcmp(PMenu->GetNameObj(),"Mess")==0)
PMenu->Show(mes1,2,14,12,PMenu->GetPos());
if(strcmp(PMenu->GetNameObj(),"Data")==0)
PMenu->Show(mes2,2,1,10,PMenu->GetPos());
if(strcmp(PMenu->GetNameObj(),"Read")==0)
PMenu->Show(mes3,2,1,12,PMenu->GetPos());
}
}
else if(PMenu->Is_Enter(ch));
     else if(PMenu->Is_Esc(ch))
	  {
	  if(strcmp(PMenu->GetNameObj(),"Read")==0)Choose_menu(1);
	  else Choose_menu(0);
	  }
}}
//**********************************************************************
void init(void)
 {
 int gdriver = DETECT, gmode, errorcode;
/* initialize graphics and local
   variables */
initgraph(&gdriver, &gmode, "a:\\bgi");
/* read result of initialization */
errorcode = graphresult();
if (errorcode != grOk)  /* an error
    occurred */
  {
   cout<<"Graphics error: %s\n"<< grapherrormsg(errorcode);
   cout<<"Press any key to halt:";
   getch();
   exit(1); /* terminate with an error
	       code */
  }
}
//********************************************************************
void MMnu(int pos)
{
switch(pos)
 {
case 0:PMenu=&Message;PMenu->Show(mes1,2,14,12,0);break;
case 1:PMenu=&Data;PMenu->Show(mes2,2,1,10,0);break;
case 2:exit(0);break;
 }
}
//********************************************************************
void Msg(int pos)
{
switch(pos)
{
case 0:Write_mes();break;
case 1:Read_mes();break;
}
}
//*********************************************************************
void Dt(int pos)
{
switch(pos)
{
case 0:Write_data();break;
case 1:PMenu=&Rd_data;PMenu->Show(mes3,2,1,12,0);break;
}
}
//*******************************************************************
void Rd(int pos)
{
switch(pos)
{
case 0:Read_all();break;
case 1:Read_letter();break;
}
}
//*****************************************************************
int Write_mes(void)
{
char num;
static int flag=0;
counter=Get_count();
if (counter>4)flag=1;
else flag=0;
if(flag)
{setcolor(11);
 settextstyle(4,HORIZ_DIR,4);
 outtextxy(70,350,"I'm sorry,but you limit 5 messages");
 delay(1200);
 setcolor(8);
 settextstyle(4,HORIZ_DIR,4);
 outtextxy(65,350,"I'm sorry,but you limit 5 messages");
 PMenu=&Main_menu;
 Main_menu.Fone(8);
 Main_menu.Show(main_mes,3,1,11,0);
 return 0;
 }
long t;
Main_menu.Fone(8);
ofstream mes;
if(!mes)
{
cout<<"Can't open file Message.txt";
return 0;
}
char a,*s,str[45];
int i=0;
int cnt=0,x,y;
parameter(50,150,580,200);
outtextxy(70,100,"Enter your message here(1-30 letters):");
strcpy(str,input(60,150,30));
mes.open("message.txt",ios::app);
mes<<"  ";
num='1';
while(Is_present(num)){num++;}
mes<<num;
mes<<"       ";
mes<<str;
mes<<endl;
mes<<"                                   ";
t=time(0);
mes<<ctime(&t);
setcolor(12);
outtextxy(40,300,"Your message was successfully entered!");
delay(1500);
mes.close();
PMenu=&Main_menu;
Main_menu.Fone(8);
Main_menu.Show(main_mes,3,1,11,0);
return 0;
}
//********************************************************************
void Read_mes()
{
int i=0;
char buf[256];
strcpy(buf," ");
Main_menu.Fone(0);
ifstream mes("message.txt");
if(!mes)
{
cout<<"Can't open file Message.txt";
return ;
}
setcolor(14);
settextstyle(4,HORIZ_DIR,3);
outtextxy(200,2,"All messages");
setcolor(12);
outtextxy(5,30,"Number  Message               Date&Time");
setfillstyle(1,1);
bar(0,60,640,430);
setcolor(14);
settextstyle(4,HORIZ_DIR,3);
outtextxy(60,435,"Enter number of message to delete(0 to ignore)");
while(!mes.eof())
{
mes.getline(buf,60,'\n');
setcolor(3);
settextstyle(7,HORIZ_DIR,1);
outtextxy(10,58+i,buf);
i+=25;
}
char ch;
do
{
ch=getch();
if(ch>=48&&ch<=53)break;
}while(1);
int flag1=0;
if(!Is_present(ch)) flag1=1;
setcolor(14);
settextstyle(4,HORIZ_DIR,3);
switch(ch)
{
case '0':flag1=0;outtextxy(545,435,"0");break;
case '1':outtextxy(545,435,"1");Delete(ch);break;
case '2':outtextxy(545,435,"2");Delete(ch);break;
case '3':outtextxy(545,435,"3");Delete(ch);break;
case '4':outtextxy(545,435,"4");Delete(ch);break;
case '5':outtextxy(545,435,"5");Delete(ch);break;
}
ch=getch();
PMenu=&Main_menu;
Main_menu.Fone(8);
Main_menu.Show(main_mes,3,1,11,0);
if(flag1)
{
 setcolor(11);
 settextstyle(4,HORIZ_DIR,4);
 outtextxy(100,350,"Sorry,but message not found");
 delay(1200);
 setcolor(8);
 settextstyle(4,HORIZ_DIR,4);
 outtextxy(100,350,"Sorry,but message not found");
 }
}
//********************************************************************
int Get_count()
{
int c=0;
char buf[256];
ifstream mes("message.txt");
if(!mes)
{
cout<<"Can't open file Message.txt";
return 0;
}
while(mes)
{
mes.getline(buf,256,'\n');
if(!strcmp(buf,""))break;
c++;
}
return c/2;
}
//***********************************************************************
void Delete(char ch)
{
int c=0;
counter--;
char buf[256];
char buf1[256];
fstream mes;
fstream mes1;
mes.open("message.txt",ios::in);
if(!mes)
{
cout<<"Can't open file Message.txt";
return ;
}
mes1.open("message1.txt",ios::out);
if(!mes1)
{
cout<<"Can't open file Message1.txt";
return ;
}
while(mes)
{
mes.getline(buf,256,'\n');
mes.getline(buf1,256,'\n');
if(!strcmp(buf,""))break;
c++;
if(buf[2]!=ch)
  {
   for(int i=0;i<strlen(buf);i++)
   mes1.put(buf[i]);
   mes1.put('\n');
   for(i=0;i<strlen(buf1);i++)
   mes1.put(buf1[i]);
   mes1.put('\n');
  }
}
mes.close();
mes1.close();
mes.open("message.txt",ios::out);
mes1.open("message1.txt",ios::in);
if(!mes)
{
cout<<"Can't open a file message to write";
return;
}
if(!mes1)
{
cout<<"Can't open a file message1 to read";
return;
}
while(mes1)
{
mes1.getline(buf,256,'\n');
mes1.getline(buf1,256,'\n');
if(!strcmp(buf,""))break;
   for(int i=0;i<strlen(buf);i++)
   mes.put(buf[i]);
   mes.put('\n');
   for(i=0;i<strlen(buf1);i++)
   mes.put(buf1[i]);
   mes.put('\n');
}
mes.close();
mes1.close();
}
//***********************************************************************
void Cadre(int x1,int y1,int x2,int y2,int col)
{
  char i, j;
  setcolor(col);
  line(x1,y1,x2,y1);
  line(x1,y1+5,x2,y1+5);
  line(x1,y1,x1,y2);
  line(x1+5,y1,x1+5,y2);
  line(x2,y1,x2,y2);
  line(x2-5,y1,x2-5,y2);
  line(x1,y2,x2,y2);
  line(x1,y2-5,x2,y2-5);
 }
//***********************************************************************
int Is_present(char cnt)
{
fstream mes;
char buf[256];
mes.open("message.txt",ios::in);
if(!mes)
{
cout<<"Can't open a file message to read";
return 0;
}
while(mes)
{
mes.getline(buf,256,'\n');
if(buf[2]==cnt)return 1;
}
mes.close();
return 0;
}
//**********************************************************************
int Write_data(void)
{
static int flag=0;
counter=Get_cntData();
if (counter>14)flag=1;
else flag=0;
if(flag)
{setcolor(11);
 settextstyle(4,HORIZ_DIR,4);
 outtextxy(70,350,"I'm sorry,but you limit 15 dates");
 delay(1200);
 setcolor(8);
 settextstyle(4,HORIZ_DIR,4);
 outtextxy(65,350,"I'm sorry,but you limit 15 dates");
 PMenu=&Main_menu;
 Main_menu.Fone(8);
 Main_menu.Show(main_mes,3,1,11,0);
 return 0;
 }
Main_menu.Fone(8);
elem *start,*ptr;
start=dat;
int cnt;
fstream file;
if(!file)
{
cout<<"Can't open file Data.txt";
return 0;
}
file.open("data_fil.txt",ios::in);
while(file)
{
file>>dat[cnt].name;
file>>dat[cnt].address;
file>>dat[cnt].telephon;
cnt++;
num_data=cnt-1;
}
file.close();
parameter(50,80,580,130);
settextstyle(7,HORIZ_DIR,3);
outtextxy(50,50,"Enter name(1-20 letters):");
strcpy(dat[num_data].name,input(65,85,20));
parameter(50,180,580,230);
settextstyle(7,HORIZ_DIR,3);
outtextxy(50,150,"Enter address(1-20 letters):");
strcpy(dat[num_data].address,input(65,185,20));
parameter(50,280,580,330);
settextstyle(7,HORIZ_DIR,3);
outtextxy(50,250,"Enter telephon(1-9 number):");
strcpy(dat[num_data].telephon,input(65,285,9));
num_data++;
qsort(start,num_data,sizeof(elem),cmp);

file.open("data_fil.txt",ios::out);
for(int i=0;i<num_data;i++)
file<<dat[i].name<<"   "<<dat[i].address<<"   "<<dat[i].telephon<<endl;
setcolor(12);
outtextxy(70,370,"Your data was successfully entered!");
delay(1500);
file.close();
PMenu=&Main_menu;
Main_menu.Fone(8);
Main_menu.Show(main_mes,3,1,11,0);
return 0;
}
//**********************************************************************
int cmp_elem(const void* elem1,const void* elem2)
{
return(strcmp(((elem*)elem1)->name,((elem*)elem2)->name));
}
//**********************************************************************
char* input(int x,int y,int num)
{
settextstyle(4,HORIZ_DIR,4);
char a,*s;int i=0,cnt=0;
char str[40];
strcpy(str,"");
while((a=getch())!=13)
{
if(a==' ')a='_';
if(a!='\r')
{
 i++;
 cnt++;
 if(cnt>num)break;
 s=&a;
 strcat(str,s);
 str[i]='\0';
 outtextxy(x,y,str);
}
}
return str;
}
//********************************************************************
void parameter(int x1,int y1,int x2,int y2)
{
setcolor(14);
setfillstyle(1,1);
bar(x1,y1,x2,y2);
Cadre(x1,y1,x2,y2,14);
}
//*********************************************************************
void Read_all()
{
int i=0,cnt=0,y,k,num,num1,num2;
char buf[256],c;
strcpy(buf," ");
Main_menu.Fone(0);
ifstream mes("data_fil.txt");
if(!mes)
{
cout<<"Can't open file Data.txt";
return ;
}
setcolor(14);
settextstyle(4,HORIZ_DIR,3);
outtextxy(250,2,"All data");
setcolor(12);
outtextxy(5,30,"Number    Name            Address           Telephon");
setfillstyle(1,1);
bar(0,60,640,430);
setcolor(14);
settextstyle(4,HORIZ_DIR,3);
outtextxy(60,435,"Enter number of data to delete(0 to ignore)");
char b[3],ch[3];
while(mes)
{
mes>>dat[cnt].name;
mes>>dat[cnt].address;
mes>>dat[cnt].telephon;
if(!strcmp(dat[cnt].name,"")||!strcmp(dat[cnt].address,"")||!strcmp(dat[cnt].telephon,"")) break;
setcolor(3);
if(cnt<9)
{
ch[0]=cnt+49;
ch[1]='\0';
}
else
{
ch[0]=(cnt+1)/10+48;
ch[1]=(cnt+1)%10+48;
ch[2]='\0';
}
strcpy(b,ch);
settextstyle(1,HORIZ_DIR,1);
outtextxy(30,58+i,b);
outtextxy(130,58+i,dat[cnt].name);
outtextxy(340,58+i,dat[cnt].address);
outtextxy(535,58+i,dat[cnt].telephon);
i+=25;
cnt++;
}
do{
num1=getch();
num1-=48;
print(num1,510);
}while(num1<0||num1>9);
do{
c=getch();
if(c!='\r')
{num2=c;
num2-=48;
print(num2,520);
getch();
num=num1*10+num2; }
else num=num1;
}while(num2<0||num2>9&&c!='\r');
Delete_data(num);
PMenu=&Main_menu;
Main_menu.Fone(8);
Main_menu.Show(main_mes,3,1,11,0);
if(num>(Get_cntData()+1))
{
 setcolor(11);
 settextstyle(4,HORIZ_DIR,4);
 outtextxy(150,350,"Sorry,but data not found");
 delay(1200);
 setcolor(8);
 settextstyle(4,HORIZ_DIR,4);
 outtextxy(150,350,"Sorry,but data not found");
 }
}
//***********************************************************************
int Get_cntData()
{
int c=0;
char buf[256];
ifstream mes("data_fil.txt");
if(!mes)
{
cout<<"Can't open file Message.txt";
return 0;
}
while(mes)
{
mes.getline(buf,256,'\n');
if(!strcmp(buf,""))break;
c++;
}
return c;
}
//**********************************************************************
void Delete_data(int ch)
{
int c=0;
char buf[256];
char buf1[256];
fstream mes;
fstream mes1;
mes.open("data_fil.txt",ios::in);
if(!mes)
{
cout<<"Can't open file Data.txt";
return ;
}
mes1.open("data1.txt",ios::out);
if(!mes1)
{
cout<<"Can't open file Data1.txt";
return ;
}
while(mes)
{
mes.getline(buf,256,'\n');
if(!strcmp(buf,""))break;
c++;
if(c!=ch)
  {
   for(int i=0;i<strlen(buf);i++)
   mes1.put(buf[i]);
   mes1.put('\n');
  }
}
mes.close();
mes1.close();
mes.open("data_fil.txt",ios::out);
mes1.open("data1.txt",ios::in);
if(!mes)
{
cout<<"Can't open a file data to write";
return;
}
if(!mes1)
{
cout<<"Can't open a file data1 to read";
return;
}
while(mes1)
{
mes1.getline(buf,256,'\n');
if(!strcmp(buf,""))break;
   for(int i=0;i<strlen(buf);i++)
   mes.put(buf[i]);
   mes.put('\n');
}
mes.close();
mes1.close();
}
//***********************************************************************
void print(int num,int y)
{
setcolor(14);
settextstyle(4,HORIZ_DIR,3);
switch(num)
{
case 0:outtextxy(y,435,"0");break;
case 1:outtextxy(y,435,"1");break;
case 2:outtextxy(y,435,"2");break;
case 3:outtextxy(y,435,"3");break;
case 4:outtextxy(y,435,"4");break;
case 5:outtextxy(y,435,"5");break;
case 6:outtextxy(y,435,"6");break;
case 7:outtextxy(y,435,"7");break;
case 8:outtextxy(y,435,"8");break;
case 9:outtextxy(y,435,"9");break;
}
}
//**********************************************************************
void Read_letter()
{
int cnt=0,i=0,flag=0;
char b[3],ch[3];
char buf[256],c[1];
strcpy(buf," ");
Main_menu.Fone(0);
setcolor(10);
settextstyle(8,HORIZ_DIR,3);
outtextxy(50,50,"Enter first letter of name:");
strcpy(c,input(405,47,1));
Main_menu.Fone(0);
ifstream mes("data_fil.txt");
if(!mes)
{
cout<<"Can't open file Data.txt";
return ;
}
setcolor(14);
settextstyle(4,HORIZ_DIR,3);
outtextxy(200,2,"Data by first letter");
setcolor(12);
outtextxy(5,30,"Number    Name            Address           Telephon");
setfillstyle(1,1);
bar(0,60,640,430);
setcolor(14);
settextstyle(4,HORIZ_DIR,3);
outtextxy(200,435,"Press any key to exit.");
while(mes)
{
mes>>dat[cnt].name;
if(strncmp(dat[cnt].name,c,1)!=0)
{mes>>dat[cnt].address;
 mes>>dat[cnt].telephon;continue;}
flag=1;
mes>>dat[cnt].address;
mes>>dat[cnt].telephon;
if(!strcmp(dat[cnt].name,"")||!strcmp(dat[cnt].address,"")||!strcmp(dat[cnt].telephon,"")) break;
setcolor(3);
if(cnt<9)
{
ch[0]=cnt+49;
ch[1]='\0';
}
else
{
ch[0]=(cnt+1)/10+48;
ch[1]=(cnt+1)%10+48;
ch[2]='\0';
}
strcpy(b,ch);
settextstyle(1,HORIZ_DIR,1);
outtextxy(30,58+i,b);
outtextxy(130,58+i,dat[cnt].name);
outtextxy(340,58+i,dat[cnt].address);
outtextxy(535,58+i,dat[cnt].telephon);
i+=25;
cnt++;
}
if(!flag)
{
 setcolor(11);
 settextstyle(4,HORIZ_DIR,4);
 outtextxy(150,350,"Sorry,but data not found");
 delay(1200);
 setcolor(1);
 settextstyle(4,HORIZ_DIR,4);
 outtextxy(150,350,"Sorry,but data not found");
 }
getch();
PMenu=&Main_menu;
Main_menu.Fone(8);
Main_menu.Show(main_mes,3,1,11,0);
}
//*********************************************************************
void main()
{
init();
Choose_menu(0);
getch();
closegraph();
}


