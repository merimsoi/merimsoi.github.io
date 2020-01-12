#include <graphics.h>
#include<dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<string.h>
char name1[20],name2[20];
char k1[2],k2[2],k3[2],k4[2],k5[5],k6[9],previous[30];
char t[30];
void sun(int);
void sound1(void);
void sound2(void);
void cry(int,int);
void kaftorim(void);
void name_c(int,int);
void init(void);
void mouse(void);
void window(int);
void name(int,int,int);
void sun_pos(int,int);
void caftor(int,int,int,int,char num[]);
void press_caftor(int,int,int,int,char num[]);
char player1[20];
char player2[20];
//************************* main ************************************
int main(void)
{
 init();
 strcpy(player1," ");
 strcpy(player2,"");
 kaftorim();
 closegraph();
}
//********************* init ****************************************
void init(void)
{
   int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, "a:\\bgi");
   errorcode = graphresult();
   if (errorcode != grOk)
   { printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
}}
//***************** input name *************************************
void name(int x,int y,int num)
{
char a,*s,b[25];
int i=0;
setcolor(1);
settextstyle(4, HORIZ_DIR,6);
if(num==1) outtextxy(x,y,"Enter name of first player");
else
{ outtextxy(x,y,"Enter name of ");
  outtextxy(x+270,y+=50,"second player");
}
x+=210;y+=65;
setcolor(5);strcpy(b,"");
while((a=getch())!=13)
{if(a!='\r')
{i++;
 s=&a;
 strcat(b,s);
 b[i]='\0';
 outtextxy(x,y,b);
}}
if(num==1)strcpy(name1,b);
else strcpy(name2,b);
}
//********************** window **************************************
void window(int n)
{
setfillstyle(1,n);
bar(0,0,650,480);
}
//******************* sun ********************************************
void sun(int k)
{
name_c(4,14);
if(k==1)sun_pos(150,200);
else sun_pos(450,200);
}
void sun_pos(int x,int y)
{
setfillstyle(1,14);
setcolor(14);
circle(x,y,80);
floodfill(x,y,14);
setfillstyle(1,9);
setcolor(9);
circle(x-35,y-20,10);
floodfill(x-35,y-20,9);
circle(x+35,y-20,10);
floodfill(x+35,y-20,9);
setfillstyle(1,7);
setcolor(7);
circle(x-35,y-20,4);
floodfill(x-35,y-20,7);
circle(x+35,y-20,4);
floodfill(x+35,y-20,7);
setfillstyle(1,0);
setcolor(0);
circle(x-35,y-20,3);
floodfill(x-35,y-20,0);
circle(x+35,y-20,3);
floodfill(x+35,y-20,0);
circle(x-5,y+10,2);
floodfill(x-5,y+10,0);
circle(x+5,y+10,2);
floodfill(x+5,y+10,0);
setcolor(0);
line(x-35,y-30,x-35,y-33);
line(x-33,y-30,x-31,y-33);
line(x-37,y-30,x-39,y-33);
line(x-29,y-30,x-27,y-31);
line(x-41,y-30,x-43,y-31);
line(x+35,y-30,x+35,y-33);
line(x+33,y-30,x+31,y-33);
line(x+37,y-30,x+39,y-33);
line(x+29,y-30,x+27,y-31);
line(x+41,y-30,x+43,y-31);
arc(x,y+10,200,340,40);
arc(x,y+10,200,340,41);
arc(x-35,y-30,30,150,10);
arc(x+35,y-30,30,150,10);
}
//*********************** name ***********************************
void name_c(int color1,int color2)
{
settextstyle(4, HORIZ_DIR,6);
setcolor(color1);
outtextxy(100,20,name1);
setcolor(color2);
outtextxy(400,20,name2);
}
//********************** cry ************************************
void cry(int x,int y)
{
setcolor(14);
arc(x,y+10,200,340,40);
arc(x,y+10,200,340,41);
for(int i=0;i<65;i++)
{
setcolor(0);
arc(x,y+70,89-i,91+i,40);
arc(x,y+70,89-i,91+i,41);
setcolor(0);
pieslice(x+35,y+i,240,300,7);
setcolor(14);
delay(10);
pieslice(x+35,y+i,240,300,7);
delay(10);
if(i>=20)
{setcolor(0);
pieslice(x-35,y+i-30,240,300,7);
setcolor(14);
delay(10);
pieslice(x-35,y+i-30,240,300,7);
delay(5);}
}
}
//******************** kaftor ************************************
 void caftor(int x,int y,int x1,int y1,char num[])
 {
 setcolor(7);
 setfillstyle(1,0);
 bar3d(x,y,x1,y1,0,0);
 setfillstyle(1,11);
 bar3d(x+2,y+2,x1-3,y1-3,0,0);
 setfillstyle(1,3);
 bar3d(x+4,y+4,x1-3,y1-3,0,0);
 settextstyle(0,HORIZ_DIR,4);
 setcolor(4);
 if(strcmp(num,"Exit")==0){settextstyle(0,HORIZ_DIR,2);
			   outtextxy(x+40,(y+y1)/2-10,num);}
 else if(strcmp(num,"New Game")==0){settextstyle(0,HORIZ_DIR,2);
				    outtextxy(x+12,(y+y1)/2-10,num);}
      else outtextxy((x+x1)/2-13,(y+y1)/2-13,num);
       }
 //*********************** press kaftor ****************************
 void press_caftor(int x,int y,int x1,int y1,char num[])
 {
 setcolor(7);
 setfillstyle(1,0);
 bar3d(x,y,x1,y1,0,0);
 setfillstyle(1,11);
 bar3d(x+2,y+2,x1-2,y1-2,0,0);
 setfillstyle(1,3);
 bar3d(x+3,y+3,x1-2,y1-2,0,0);
 settextstyle(0,HORIZ_DIR,4);
 setcolor(12);
 if(strcmp(num,"Exit")==0){settextstyle(0,HORIZ_DIR,2);
			   outtextxy(x+40,(y+y1)/2-10,num);}
 else if(strcmp(num,"New Game")==0){settextstyle(0,HORIZ_DIR,2);
				    outtextxy(x+12,(y+y1)/2-10,num);}
      else outtextxy((x+x1)/2-13,(y+y1)/2-13,num);
 delay(600);
 caftor(x,y,x1,y1,num);
 }
//******************* kaftorim *************************************
void kaftorim()
{
//cleardevice();
char a[2];
int flag=0;
strcpy(k1,"1");
strcpy(k2,"2");
strcpy(k3,"3");
strcpy(k4,"4");
strcpy(k5,"Exit");
strcpy(k6,"New Game");
window(3);
name(10,10,1);
name(1,200,2);
window(1);
sun(1);
sun(2);
caftor(130,340,190,400,k1);
caftor(220,340,280,400,k2);
caftor(310,340,370,400,k3);
caftor(400,340,460,400,k4);

for(int i=1;;i++)
{
for(int j=1;j<=i;j++)
{
strcpy(t,"");
mouse();
if(j==i&&i!=1)strcpy(a,t);
else if(i==1)strcpy(player1,t);
else if(i%2==1)strcat(player1,t);
     else strcat(player2,t);
}
if(i==1){strcpy(previous,player1);sound1();name_c(14,4);}
else
{if(i%2==1)
    {
     if (strcmp(previous,player1)==0){strcpy(previous,player1);
				      strcat(previous,a);
				      sound1(); name_c(14,4);}
     else {sound2();cry(150,200);flag=1;}
     }
 else if (strcmp(previous,player2)==0){strcpy(previous,player2);
				       strcat(previous,a);
				       sound1();name_c(4,14);}

     else {sound2();cry(450,200);flag=1;}

}
strcpy(player1,"");
strcpy(player2,"");
if(flag)break;
}
while(flag)
{
caftor(310,410,460,470,k5);
caftor(130,410,280,470,k6);
strcpy(t,"");
mouse();
if(strcmp(t,"Exit")==0){press_caftor(310,410,460,470,k5);
			flag=0;exit(0);}
else if(strcmp(t,"New Game")==0){press_caftor(130,410,280,470,k6);
				 strcpy(previous,"");
				 flag=0;i=1;
				 kaftorim();}
}
}
//******************* mouse **************************************
void mouse(void)
{
//char* t;
int x,y,is_pressed;
_AX=0x01;
geninterrupt(0x33);
while(1)
{_AX=0x03;
geninterrupt(0x33);
is_pressed=_BX;
x=_CX;
y=_DX;
if(is_pressed)
{if(x>=130&&x<=190&&y>=340&&y<=400){press_caftor(130,340,190,400,k1);
				    strcpy(t,k1);break;}
 if(x>=220&&x<=280&&y>=340&&y<=400) {press_caftor(220,340,280,400,k2);
				     strcpy(t,k2);break;}
 if(x>=310&&x<=370&&y>=340&&y<=400) {press_caftor(310,340,370,400,k3);
				     strcpy(t,k3);break;}
 if(x>=400&&x<=460&&y>=340&&y<=400) {press_caftor(400,340,460,400,k4);
				     strcpy(t,k4);break;}
 if(x>=310&&x<=460&&y>=410&&y<=470) {press_caftor(310,410,460,470,k5);
				     strcpy(t,k5);break;}
 if(x>=130&&x<=280&&y>=410&&y<=470) {press_caftor(130,410,280,470,k6);
				     strcpy(t,k6);break;}

}}
_AX=0x02;
geninterrupt(0x33);
//return(t);
}
void sound1(void)
{
for(int i=450;i<600;i+=70)
{   sound(i);
   delay(70);
   nosound();
}
}
void sound2(void)
{
for(int i=300;i>30;i-=50)
{   sound(i);
   delay(160);
   nosound();
}
}