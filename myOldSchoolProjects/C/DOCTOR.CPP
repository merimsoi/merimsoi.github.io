#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
void menu(int k);
int menu2(int k); void menu1(int x,int y,int x1,int y1,int k);
void fix(int k,int doc);int scan(void);void set(int k);int input(void);
void teud(void);void help(void);void del(void);void del1(void);
int cancel (int num,long array[11]);void prog_doc(int a,long array[11]);
void teudat2(int num,long array[11]);void row(int x,int x1,int i,long array[11]);
void odaa(void);void odaa1(int num,long array[11]);void odaa2(void);
void watch(void);void cold_boot(void);
unsigned int offset_cold=0,segment_cold=0xffff;
long artur[11]={0,0,0,0,0,-1,-1,-1,0,0,0};
long bani[11]={0,0,0,0,0,-1,-1,-1,0,0,0};
long ziko[11]={0,0,0,0,0,-1,-1,-1,0,0,0};
long dani[11]={0,0,0,0,0,-1,-1,-1,0,0,0};
//-------------------------MAIN----------------------------
void main()
{int k=1;clrscr();menu(k);}
// ---------------- -- COMMON MENU -----------------------
void menu(int k)
{watch();
 int x,y,x1,y1,m,a,status;
 int k1=0;int k2=0;int k3=0;int k4=0;
 if (k==1) k1=1;if (k==2) k2=1;if (k==3) k3=1;if (k==4) k4=1;
 x=26;y=9;x1=51;y1=10;  menu1(x,y,x1,y1,0);
 cprintf("                        ");
 x=26;y=10;x1=51;y1=11;  menu1(x,y,x1,y1,k1);
 cprintf("       ˜…ˆ š’‰—        ");
 x=26;y=11;x1=51;y1=12;  menu1(x,y,x1,y1,k2);
 cprintf("       ˜…ˆ Œ…ˆ‰        ");
 x=26;y=12;x1=51;y1=13;  menu1(x,y,x1,y1,k3);
 cprintf(" …‰Œ „ƒ…’ š‰‹…š š‚–„ ");
 x=26;y=13;x1=51;y1=14;  menu1(x,y,x1,y1,k4);
 cprintf("        „€‰–‰           ");
 x=26;y=14;x1=51;y1=15;  menu1(x,y,x1,y1,0);
 cprintf("                        ");
_setcursortype(_NOCURSOR);
do
{m=scan();
if ((m==13)&&(k4==1)) {del1();menu1(35,12,41,13,1);cprintf(" IRINA ");
		       delay(1000);exit(status - '0');}
else if (m==80) {k++;if (k==5) k=1;menu(k);}
     else if (m==72) {k--;if (k==0) k=4;menu(k);}
	  else  if ((m==13)&&(k1==1)) set(1);
		else if ((m==13)&&(k2==1)) set(2);
		     else if ((m==13)&&(k3==1))
			      {a=menu2(1); del1();
			       if (a==1) prog_doc(a,artur);
				else if (a==2) prog_doc(a,bani);
				     else if (a==3) prog_doc(a,ziko);
					  else if (a==4) prog_doc(a,dani);
					  getch();del1();menu(1);}}
while ((m!=13)&&(m!=72)&&(m!=80));}
//----------------HELP MENU-------------------
void menu1(int x,int y,int x1,int y1,int k)
{window(x,y,x1,y1);
if(k==1){ textcolor(1);textbackground(3);}
else if (k==0) {textcolor(0);textbackground(7);}
     else {textcolor(3);textbackground(9);}}
//----------------------MENU DOCTORS---------------------------
int menu2(int k)
{int x,y,x1,y1,m;
int k1=0;int k2=0;int k3=0;int k4=0;
if (k==1) k1=1;if (k==2) k2=1;if (k==3) k3=1;if (k==4) k4=1;
x=26;y=9;x1=51;y1=10;  menu1(x,y,x1,y1,0);
cprintf("                        ");
x=26;y=10;x1=51;y1=11;  menu1(x,y,x1,y1,k1);
cprintf("      ˜…ˆ˜€  €”…˜       ");
x=26;y=11;x1=51;y1=12;  menu1(x,y,x1,y1,k2);
cprintf("        ‰  €”…˜       ");
x=26;y=12;x1=51;y1=13;  menu1(x,y,x1,y1,k3);
cprintf("       …—‰–  €”…˜       ");
x=26;y=13;x1=51;y1=14;  menu1(x,y,x1,y1,k4);
cprintf("        ‰ƒ  €”…˜       ");
x=26;y=14;x1=51;y1=15;  menu1(x,y,x1,y1,0);
cprintf("                        ");
do{m=scan();
   if (m==80) {k++;if (k==5) k=1;menu2(k);}
   if (m==72) {k--;if (k==0) k=4;menu2(k);}
   if (m==13) return(k);}
 while ((m!=13)&&(m!=72)&&(m!=80)); }
//-------------------MENU TIME-WORK------------------------
void set(int k)
{int doc,i,x=18,x1=21; doc=menu2(1); help();
if ((k==1)||(k==2))
{  switch(doc) { case 1:{for(i=0;i<11;i++) {x+=3;x1+=3; row(x,x1,i,artur);}
					    fix(k,doc);break; }
		 case 2: { for(i=0;i<11;i++) {x+=3;x1+=3;row(x,x1,i,bani);}
					      fix(k,doc);break;}
		 case 3:{ for(i=0;i<11;i++) {x+=3;x1+=3;row(x,x1,i,ziko);}
					     fix(k,doc);break; }
		 case 4:{ for(i=0;i<11;i++) {x+=3; x1+=3;row(x,x1,i,dani);}
					     fix(k,doc);break; }}}}
//----------------------GET SCAN---------------
int scan(void)
{int a; a=getch();
if (a==0) a=getch();return(a);}
//-----------------------SET AND CANCEL------------------------
void fix(int k,int doc)
{int num,num1;
 switch(k)
   { case 1:{ switch(doc)
	       {case 1:{num=input();num=num-8;
			if (artur[num]==0) odaa1(num,artur);
			else  odaa2(); del();menu(1);}
	       case 2:{num=input();num=num-8;
		       if (bani[num]==0) odaa1(num,bani);
		       else odaa2();del();menu(1);}
	       case 3:{num=input();num=num-8;
		       if (ziko[num]==0) odaa1(num,ziko);
		       else odaa2();del();menu(1);}
	       case 4:{num=input();num=num-8;
		      if (dani[num]==0) odaa1(num,dani);
		      else odaa2();del();menu(1);}}}
    case 2: { switch(doc)
	      { case 1:{num=input();num=num-8;
		       if ((artur[num]!=0)&&(artur[num]!=-1))teudat2(num,artur);
		       else odaa();del();menu(1);}
	       case 2:{num=input();num=num-8;
		       if ((bani[num]!=0)&&(bani[num]!=-1))teudat2(num,bani);
		       else odaa();del();menu(1);}
	       case 3:{num=input();num=num-8;
		       if ((ziko[num]!=0)&&(ziko[num]!=-1))teudat2(num,ziko);
		       else odaa();del();menu(1);}
	       case 4:{num=input();num=num-8;
		       if ((dani[num]!=0)&&(dani[num]!=-1))teudat2(num,dani);
		       else odaa();del();menu(1);}}}}}
//---------------------GET TIME------------------------
 int input(void)
 {int num;
 do{menu1(32,17,42,19,1);
    cprintf(" „’™ „†‰€Œ ");cprintf("           ");
   _setcursortype(_NORMALCURSOR); gotoxy(5,2); scanf("%d",&num);}
 while ((num<8)||(num>18)||(num==13)||(num==14)||(num==15));
 return(num);}
//-----------------------MENU TEUDAT.ZEUT-------------------
 void teud(void)
 { menu1(32,19,42,21,1);
   cprintf(" †.š ˜”‘  ");cprintf("           ");gotoxy(2,2);}
 //-------------------HELP TIME-------------------------
 void help(void)
 { menu1(62,3,69,4,1); cprintf(" ‰…” ");
 menu1(62,4,69,5,2); cprintf(" ‘…”š ");
 menu1(62,5,69,6,0); cprintf(" „—‘”„"); }
 //-------------DELETE WINDOW-------------------
 void del(void)
 { int i;
 for(i=3;i<6;i++)
 {window(20,i,70,i+1); textcolor(0);textbackground(0);
 cprintf("                                                  ");}
 for(i=17;i<23;i++)
 {window(30,i,45,i+1); textcolor(0);textbackground(0);
  cprintf("                      ");}}
 //-------------------CANCEL------------------
 int cancel (int num,long array[11])
 { long teudat; teud(); scanf("%ld",&teudat);
  if (teudat==array[num]) { array[num]=0; menu1(34,22,39,23,1);
			    cprintf(".šŒˆ‰"); delay(1000);return(1); }
  else return(0); }
 //---------------TEST NUBER TEUDAT------------------
 void teudat2(int num,long array[11])
 {int a,count=0;

  count++; a=cancel(num,array);
  if ((count==1)&&(a==0)) {count++; a=cancel(num,array);}
			   if ((count>1)&&(a==0)) cold_boot();}
  //-----------------NOTICE 1--------------
  void odaa(void)
  { menu1(32,22,43,23,1);cprintf(".ŒšŒ „ ‰€");delay(1000); }
  //---------------NOTICE 2------------------
  void odaa1(int num,long array[11])
  {teud(); scanf("%ld",&array[num]); menu1(35,22,40,23,1);
  cprintf(".š™˜");delay(1000); }
  //--------------NOTICE 3-----------------------
  void odaa2(void)
  { menu1(35,22,40,23,1);cprintf(".‘…”š");delay(1000); }
  //-----------------ROW-----------------------
  void row(int x,int x1,int i,long array[11])
  {if (array[i]==0) { menu1(x,3,x1,4,1); cprintf(" %d ",i+8);}
   else if (array[i]==-1) { menu1(x,3,x1,4,0);cprintf(" %d ",i+8);}
	else { menu1(x,3,x1,4,2);cprintf(" %d ",i+8);}}
//--------------PROGRAM DOCTORS-------------------
void prog_doc(int a,long array[11])
{int i,y=7,y1=8;
 char text[13];
 if(a==1) strcpy(text," ˜…ˆ˜€  €”…˜ ");
 if(a==2) strcpy(text,"   ‰  €”…˜ ");
 if(a==3) strcpy(text,"  …—‰–  €”…˜ ");
 if(a==4) strcpy(text,"   ‰ƒ  €”…˜ " );
 menu1(40,2,50,3,1);cprintf("Œ™ š‹˜’ ");
 menu1(27,2,40,3,1);cprintf("%s",text);
 menu1(28,5,50,6,0);cprintf("  †.š ˜”‘      †  ");
 menu1(30,6,48,7,2);cprintf("                 ");
 for(i=8;i<=18;i++)
{menu1(30,y,46,y1,2);
 if (array[i-8]==0) cprintf(" ‰…”   <==== %d  ",i);
 else if (array[i-8]==-1) cprintf(" „—‘”„  <==== %d ",i);
      else cprintf(" %ld<== %d  ",array[i-8],i);y++;y1++;}
	   menu1(30,18,46,19,2);cprintf("                 ");
 y=6,y1=7;
 for(i=8;i<=20;i++)
 {menu1(47,y,59,y1,2);cprintf("  ");
  menu1(28,y,30,y1,2);cprintf("  ");
  y++;y1++;}
 menu1(26,22,53,23,1);cprintf(" PRESS ANY KEY TO CONTINUE ");}
 //--------------DELETE MIDDLE-----------------
 void del1(void)
 {
 int i;
 for(i=2;i<23;i++)
 {window(20,i,60,i+1); textcolor(0);textbackground(0);
 cprintf("                                                  ");}
 }
 //-----------WATCH---------------------
 void watch(void)
 {int hour,minute,second;
  _AH=0X2C;
  geninterrupt(0x21);
  hour=_CH; minute=_CL;second=_DH;
  menu1(5,3,14,4,0);
  cprintf(" %d:%d:%d ",hour,minute,second); }
//-------------COLD BOOT--------------------
void cold_boot(void)
{asm JMP DWORD PTR offset_cold;}