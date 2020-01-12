/****************************************************************************/

/*                       PROJECT CREATED BY PINY STOLERO                    */

/****************************************************************************/


#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include"a:pass2.h"
struct Time_ZZ{
	      int hour;
	      int min;
	      int sec;

	    } my_time;
int left_press=0;
int i;
int x1=_CX;
int x2,y2;
int y1=_DX;
void draw_traffic();
void malben();
void color_red();
void color_yellow();
void color_green();
void blink_color_green();
void timer_red();
void timer_green();
void blink_timer_green();
void timer_yellow();
void mouse_functions();
void see_mouse();
void automatic_option();
void manual_option();
void reset_option();
void see_mouse();
void close_mouse();
int click_mouse();
void creat_door();
void open_door();
void close_door();
void close_T_C_C_door();
void delete_board();
void TIMER();



void main()
{
textbackground(BLACK);
textcolor(WHITE);
_setcursortype(_NOCURSOR);

clrscr();
cod();
clrscr();
TIMER();
draw_traffic();
malben();
creat_door();
mouse_functions();

}
//////////////////////////  DRAW TRAFFICLIGET  /////////////////////////////

/*    THIS FUNCTION IS PRINTING PICTURE OF TRAFFICLIGHT ON THE SCREEN    */

void draw_traffic()
{
TIMER();
for(k=1;k<79;k++){gotoxy(k,1);textcolor(9);cprintf("%c",205);delay(1);}
for(k=79;k>1;k--){gotoxy(k,25);textcolor(9);cprintf("%c",205);delay(1);}
gotoxy(1,1);textcolor(9);cprintf("%c",201);
gotoxy(79,1);textcolor(9);cprintf("%c",187);
gotoxy(1,25);textcolor(9);cprintf("%c",200);
gotoxy(79,25);textcolor(9);cprintf("%c",188);
for(k=2;k<25;k++){gotoxy(1,k);textcolor(9);cprintf("%c",186);delay(1);}
for(k=2;k<25;k++){gotoxy(79,k);textcolor(9);cprintf("%c",186);delay(1);}



gotoxy(14,6);textcolor(9);cprintf("%c",201);
for(k=15;k<25;k++){gotoxy(k,6);textcolor(9);cprintf("%c",205);delay(10);}
gotoxy(25,6);textcolor(9);cprintf("%c",187);
for(k=7;k<16;k++){gotoxy(25,k);textcolor(9);cprintf("%c",186);delay(10);}
gotoxy(25,16);textcolor(9);cprintf("%c",188);
for(k=24;k>14;k--){gotoxy(k,16);textcolor(9);cprintf("%c",205);delay(15);}
gotoxy(14,16);textcolor(9);cprintf("%c",200);
for(k=15;k>6;k--){gotoxy(14,k);textcolor(9);cprintf("%c",186);delay(15);}


/*gotoxy(14,6);textcolor(9);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,
205,205,205,205,205,205,205,187);
gotoxy(14,7);textcolor(9);cprintf("%c",186);
gotoxy(14,8);textcolor(9);cprintf("%c",186);
gotoxy(14,9);textcolor(9);cprintf("%c",186);
gotoxy(14,10);textcolor(9);cprintf("%c",186);
gotoxy(14,11);textcolor(9);cprintf("%c",186);
gotoxy(14,12);textcolor(9);cprintf("%c",186);
gotoxy(14,13);textcolor(9);cprintf("%c",186);
gotoxy(14,14);textcolor(9);cprintf("%c",186);
gotoxy(14,15);textcolor(9);cprintf("%c",186);
gotoxy(25,7);textcolor(9);cprintf("%c",186);
gotoxy(25,8);textcolor(9);cprintf("%c",186);
gotoxy(25,9);textcolor(9);cprintf("%c",186);
gotoxy(25,10);textcolor(9);cprintf("%c",186);
gotoxy(25,11);textcolor(9);cprintf("%c",186);
gotoxy(25,12);textcolor(9);cprintf("%c",186);
gotoxy(25,13);textcolor(9);cprintf("%c",186);
gotoxy(25,14);textcolor(9);cprintf("%c",186);
gotoxy(25,15);textcolor(9);cprintf("%c",186);

gotoxy(14,16);textcolor(9);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,
205,205,205,205,205,205,205,188);               */

gotoxy(16,5);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c",220,220,220,220,220
,220,220,220,220,220,220);

gotoxy(26,6);textcolor(BLUE);cprintf("%c",219);
gotoxy(26,7);textcolor(BLUE);cprintf("%c",219);
gotoxy(26,8);textcolor(BLUE);cprintf("%c",219);
gotoxy(26,9);textcolor(BLUE);cprintf("%c",219);
gotoxy(26,10);textcolor(BLUE);cprintf("%c",219);
gotoxy(26,11);textcolor(BLUE);cprintf("%c",219);
gotoxy(26,12);textcolor(BLUE);cprintf("%c",219);
gotoxy(26,13);textcolor(BLUE);cprintf("%c",219);
gotoxy(26,14);textcolor(BLUE);cprintf("%c",219);
gotoxy(26,15);textcolor(BLUE);cprintf("%c",219);


gotoxy(17,7);textcolor(WHITE);cprintf("%c",218);
for(k=18;k<22;k++){gotoxy(k,7);textcolor(WHITE);cprintf("%c",196);delay(10);}
gotoxy(22,7);textcolor(WHITE);cprintf("%c",191);
for(k=8;k<9;k++){gotoxy(22,k);textcolor(WHITE);cprintf("%c",179);delay(10);}
gotoxy(22,9);textcolor(WHITE);cprintf("%c",217);
for(k=21;k>17;k--){gotoxy(k,9);textcolor(WHITE);cprintf("%c",196);delay(15);}
gotoxy(17,9);textcolor(WHITE);cprintf("%c",192);
for(k=8;k>7;k--){gotoxy(17,k);textcolor(WHITE);cprintf("%c",179);delay(15);}

gotoxy(17,10);textcolor(WHITE);cprintf("%c",218);
for(k=18;k<22;k++){gotoxy(k,10);textcolor(WHITE);cprintf("%c",196);delay(10);}
gotoxy(22,10);textcolor(WHITE);cprintf("%c",191);
for(k=11;k<12;k++){gotoxy(22,k);textcolor(WHITE);cprintf("%c",179);delay(10);}
gotoxy(22,12);textcolor(WHITE);cprintf("%c",217);
for(k=21;k>17;k--){gotoxy(k,12);textcolor(WHITE);cprintf("%c",196);delay(15);}
gotoxy(17,12);textcolor(WHITE);cprintf("%c",192);
for(k=11;k>10;k--){gotoxy(17,k);textcolor(WHITE);cprintf("%c",179);delay(15);}

gotoxy(17,13);textcolor(WHITE);cprintf("%c",218);
for(k=18;k<22;k++){gotoxy(k,13);textcolor(WHITE);cprintf("%c",196);delay(10);}
gotoxy(22,13);textcolor(WHITE);cprintf("%c",191);
for(k=14;k<15;k++){gotoxy(22,k);textcolor(WHITE);cprintf("%c",179);delay(10);}
gotoxy(22,15);textcolor(WHITE);cprintf("%c",217);
for(k=21;k>17;k--){gotoxy(k,15);textcolor(WHITE);cprintf("%c",196);delay(15);}
gotoxy(17,15);textcolor(WHITE);cprintf("%c",192);
for(k=14;k>13;k--){gotoxy(17,k);textcolor(WHITE);cprintf("%c",179);delay(15);}


TIMER();
}
////////////////////////////////  RED COLOR  ////////////////////////////////

/* THIS FUNCTION IS PRINTING THE RED
   COLOR OF THE TRAFFICLIGHT ON THE SCREEN   */

void color_red()
{
TIMER();
gotoxy(18,8);textcolor(RED);cprintf("%c",219);
gotoxy(19,8);textcolor(RED);cprintf("%c",219);
gotoxy(20,8);textcolor(RED);cprintf("%c",219);
gotoxy(21,8);textcolor(RED);cprintf("%c",219);
TIMER();
timer_red();
}

///////////////////////////   YELLOW COLOR    ///////////////////////////////

/* THIS FUNCTION IS PRINTING THE YELLOW
   COLOR OF THE TRAFFICLIGHT ON THE SCREEN      */


void color_yellow()
{
TIMER();
gotoxy(18,11);textcolor(YELLOW);cprintf("%c",219);
gotoxy(19,11);textcolor(YELLOW);cprintf("%c",219);
gotoxy(20,11);textcolor(YELLOW);cprintf("%c",219);
gotoxy(21,11);textcolor(YELLOW);cprintf("%c",219);
TIMER();
timer_yellow();
}

//////////////////////////  GRENN  COLOR  //////////////////////////////////

/* THIS FUNCTION IS PRINTING THE GREEN
   COLOR OF THE TRAFFICLIGHT ON THE SCREEN   */


void color_green()
{
TIMER();
gotoxy(18,14);textcolor(GREEN);cprintf("%c",219);
gotoxy(19,14);textcolor(GREEN);cprintf("%c",219);
gotoxy(20,14);textcolor(GREEN);cprintf("%c",219);
gotoxy(21,14);textcolor(GREEN);cprintf("%c",219);
TIMER();
timer_green();
}

//////////////////////////// BLINK GREEN COLOR //////////////////////////////

/* THIS FUNCTION IS PRINTING THE BLINKING
   GREEN COLOR OF THE TRAFFICLIGHT ON THE SCREEN                          */


void blink_color_green()
{
TIMER();
gotoxy(18,14);textcolor(138);cprintf("%c",219);
gotoxy(19,14);textcolor(138);cprintf("%c",219);
gotoxy(20,14);textcolor(138);cprintf("%c",219);
gotoxy(21,14);textcolor(138);cprintf("%c",219);
TIMER();
blink_timer_green();
}


/////////////////////////////////   MALBEN  ///////////////////////////////////

/* THIS FUNCTION IS PRINTING THE TRRAFFICLIGHT CONTROL PANEL ON THE SCREEN */

void malben()
{
TIMER();
gotoxy(45,6);textcolor(9);cprintf("%c",201);
for(k=46;k<60;k++){gotoxy(k,6);textcolor(9);cprintf("%c",205);delay(10);}
gotoxy(60,6);textcolor(9);cprintf("%c",187);
for(k=7;k<16;k++){gotoxy(60,k);textcolor(9);cprintf("%c",186);delay(10);}
gotoxy(60,16);textcolor(9);cprintf("%c",188);
for(k=59;k>45;k--){gotoxy(k,16);textcolor(9);cprintf("%c",205);delay(15);}
gotoxy(45,16);textcolor(9);cprintf("%c",200);
for(k=15;k>6;k--){gotoxy(45,k);textcolor(9);cprintf("%c",186);delay(15);}
TIMER();

gotoxy(46,5);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",220,220,220,220,220
,220,220,220,220,220,220,220,220,220,220,220);

gotoxy(61,6);textcolor(BLUE);cprintf("%c",219);
gotoxy(61,7);textcolor(BLUE);cprintf("%c",219);
gotoxy(61,8);textcolor(BLUE);cprintf("%c",219);
gotoxy(61,8);textcolor(BLUE);cprintf("%c",219);
gotoxy(61,9);textcolor(BLUE);cprintf("%c",219);
gotoxy(61,10);textcolor(BLUE);cprintf("%c",219);
gotoxy(61,11);textcolor(BLUE);cprintf("%c",219);
gotoxy(61,12);textcolor(BLUE);cprintf("%c",219);
gotoxy(61,13);textcolor(BLUE);cprintf("%c",219);
gotoxy(61,14);textcolor(BLUE);cprintf("%c",219);
gotoxy(61,15);textcolor(BLUE);cprintf("%c",219);



gotoxy(22,3);textcolor(WHITE);cprintf("TRAFFICLIGHTS   CONTROL   CENTER");

gotoxy(45,4);textcolor(WHITE);cprintf("control board");

gotoxy(48,8);textcolor(11);cprintf("1.AUTOMATIC");
gotoxy(48,10);textcolor(11);cprintf("2.MANUAL");
gotoxy(48,12);textcolor(11);cprintf("3.RESET");
gotoxy(48,14);textcolor(11);cprintf("4.EXIT");

gotoxy(42,18);textcolor(WHITE);cprintf("open control board");
gotoxy(62,18);textcolor(GREEN);cprintf("%c",30);


}
//////////////////////////  TIMER RED  ///////////////////////////////////////

/* THIS FUNCTION IS CONTROLING THE TRAFFICLIGHT RED COLOR , AND PRINTING
   THE TIMER RED COLOR ON THE SCREEN */


void timer_red()
{
TIMER();
int i;
for(i=1;i<4;i++){
TIMER();
gotoxy(27,8);textcolor(7);cprintf("%d",i);delay(1000);
}
}
///////////////////////////////// YELLOW  TIMER ///////////////////////////////////

/* THIS FUNCTION IS CONTROLING THE TRAFFICLIGHT YELLOW COLOR , AND PRINTING
   THE TIMER YELLOW COLOR ON THE SCREEN */

void timer_yellow()
{
TIMER();
int i;
gotoxy(27,8);;textcolor(BLACK);cprintf("    ");
for(i=1;i<2;i++){
TIMER();
gotoxy(27,11);textcolor(7);cprintf("%d",i);delay(1200);
}
}
///////////////////////////// GREEN TIMER///////////////////////////////////////

/* THIS FUNCTION IS CONTROLING THE TRAFFICLIGHT GREEN COLOR , AND PRINTING
   THE TIMER GREEN COLOR ON THE SCREEN */


void timer_green()
{
TIMER();
int i;
gotoxy(27,11);textcolor(BLACK);cprintf("    ");
for(i=1;i<4;i++){
TIMER();
gotoxy(27,14);textcolor(7);cprintf("%d",i);delay(1000);
gotoxy(27,14);textcolor(BLACK);cprintf("    ");
}
}

////////////////////////// BLINK GREEN TIMER /////////////////////////////////

/* THIS FUNCTION IS CONTROLING THE TRAFFICLIGHT BLINKING GREEN COLOR,AND PRINTING
   THE TIMER BLINKING GREEN COLOR ON THE SCREEN */


void blink_timer_green()
{
TIMER();
int i;
gotoxy(27,11);textcolor(BLACK);cprintf("    ");
for(i=1;i<2;i++){
TIMER();
gotoxy(27,14);textcolor(7);cprintf("%d",i);delay(1000);
gotoxy(27,14);textcolor(BLACK);cprintf("    ");
}
}
//////////////////////////  MOUSE FUNCTIONS  //////////////////////////////////

/* THIS FUNCTION IS INCLUDING SEVERAL MOUSE FUNCTIONS FOR A DIFFRENT
   MISSIONS */

void mouse_functions()
{
TIMER();
see_mouse();
while(!kbhit())
{

      left_press=click_mouse();
      delay(30);//because the mouse have bounce .... we delay the program 30ms
      while(left_press==0) {left_press=click_mouse();}




}

clrscr();
delay(1000);
close_mouse();
}




void see_mouse()//by the function we can see the cursor of the mouse
{
TIMER();
  _AX=0x01;   //fun 01 can see the cursor;
  geninterrupt(0x33);
}


void close_mouse()// this function turn the cursor to invisible on the scrren
 {
 TIMER();
  _AX=0x02;   //02 delete the cursor of the screen;
  geninterrupt(0x33);
  x2=_CX;y2=_DX;
  _AX=0x04;  // printing the cursor in a constant place in the screen
  x2=1;    // start X cordinate
  y2=1;    // start Y cordinate
  geninterrupt(0x33); // activeting the mouse
}

int click_mouse() //cheak if one of mouse key pressed
{ _AX=0x05 ;  //0x05 is the number of the function on the 0x33 interrupt
  //_BX=0x05;   //
  geninterrupt(0x33);
  left_press=1;
  x1=_CX;y1=_DX; //_DX is the row cordinate and _CX is the colom cordinate

  x2=(x1-1)/8;   //chacge x from graffic text to regular text
  y2=(y1-1)/8;   //chacge y from graffic text to regular text

  see_mouse();
  if(((x2==46) && (y2==6)) || ((x2==47) && (y2==6))
  || ((x2==48) && (y2==6)) || ((x2==49) && (y2==6)) || ((x2==50) && (y2==6))
  || ((x2==51) && (y2==6)) || ((x2==52) && (y2==6)) || ((x2==53) && (y2==6))
  || ((x2==54) && (y2==6)) || ((x2==55) && (y2==6)) || ((x2==56) && (y2==6)))
  {automatic_option();} /* if the cursor is
  at this cordinates and the mouse button was pressed the automatic_option
  will start */
  if(((x2==46) && (y2==8)) || ((x2==47) && (y2==8))
  || ((x2==48) && (y2==8)) || ((x2==49) && (y2==8)) || ((x2==50) && (y2==8))
  || ((x2==51) && (y2==8)) || ((x2==52) && (y2==8)) || ((x2==53) && (y2==6)))
  {manual_option();  }    /* if the cursor is
  at this cordinates and the mouse button was pressed the manual_option
  will start */

  if((x2==9) && (y2==17))
  {
  TIMER();
  gotoxy(10,21);textcolor(4);cprintf("on ");
  gotoxy(20,21);textcolor(9);cprintf("off");
  gotoxy(29,21);textcolor(9);cprintf("off");

  gotoxy(18,8);textcolor(RED);cprintf("%c",219);
  gotoxy(19,8);textcolor(RED);cprintf("%c",219);
  gotoxy(20,8);textcolor(RED);cprintf("%c",219);
  gotoxy(21,8);textcolor(RED);cprintf("%c",219);delay(250);
  if(left_press==1)
  {
  TIMER();
  gotoxy(18,8);textcolor(BLACK);cprintf("%c",219);
  gotoxy(19,8);textcolor(BLACK);cprintf("%c",219);
  gotoxy(20,8);textcolor(BLACK);cprintf("%c",219);
  gotoxy(21,8);textcolor(BLACK);cprintf("%c",219);

  gotoxy(10,21);textcolor(9);cprintf("off");
  gotoxy(20,21);textcolor(9);cprintf("off");
  gotoxy(29,21);textcolor(9);cprintf("off");

  TIMER();
  }
  }


   if((x2==18) && (y2==17)){
   gotoxy(10,21);textcolor(9);cprintf("off");
   gotoxy(20,21);textcolor(4);cprintf("on ");
   gotoxy(29,21);textcolor(9);cprintf("off");

   gotoxy(18,11);textcolor(YELLOW);cprintf("%c",219);
   gotoxy(19,11);textcolor(YELLOW);cprintf("%c",219);
   gotoxy(20,11);textcolor(YELLOW);cprintf("%c",219);
   gotoxy(21,11);textcolor(YELLOW);cprintf("%c",219); delay(250);
   if(left_press==1)
  {
  TIMER();
  gotoxy(18,11);textcolor(BLACK);cprintf("%c",219);
  gotoxy(19,11);textcolor(BLACK);cprintf("%c",219);
  gotoxy(20,11);textcolor(BLACK);cprintf("%c",219);
  gotoxy(21,11);textcolor(BLACK);cprintf("%c",219);

  gotoxy(10,21);textcolor(9);cprintf("off ");
  gotoxy(20,21);textcolor(9);cprintf("off");
  gotoxy(29,21);textcolor(9);cprintf("off");


  TIMER();
  }
  }


   if((x2==28) && (y2==17)){
   gotoxy(10,21);textcolor(9);cprintf("off");
   gotoxy(20,21);textcolor(9);cprintf("off");
   gotoxy(29,21);textcolor(4);cprintf("on ");

   gotoxy(18,14);textcolor(GREEN);cprintf("%c",219);
   gotoxy(19,14);textcolor(GREEN);cprintf("%c",219);
   gotoxy(20,14);textcolor(GREEN);cprintf("%c",219);
   gotoxy(21,14);textcolor(GREEN);cprintf("%c",219); delay(250);
   if(left_press==1)
  {
  TIMER();
  gotoxy(18,14);textcolor(BLACK);cprintf("%c",219);
  gotoxy(19,14);textcolor(BLACK);cprintf("%c",219);
  gotoxy(20,14);textcolor(BLACK);cprintf("%c",219);
  gotoxy(21,14);textcolor(BLACK);cprintf("%c",219);


  gotoxy(10,21);textcolor(9);cprintf("off ");
  gotoxy(20,21);textcolor(9);cprintf("off");
  gotoxy(29,21);textcolor(9);cprintf("off");

  TIMER();
  }
  }
  if(((x2==46) && (y2==10)) || ((x2==47) && (y2==10))
  || ((x2==48) && (y2==10))|| ((x2==49) && (y2==10)) || ((x2==50) && (y2==10))
  || ((x2==51) && (y2==10)) || ((x2==52) && (y2==10)))
  {reset_option();} /*  if the cursor is
  at this cordinates and the mouse button was pressed the reset_option
  will start */

  if(((x2==46) && (y2==12)) || ((x2==47) && (y2==12))
  || ((x2==48) && (y2==12))|| ((x2==49) && (y2==12)) || ((x2==50) && (y2==12))
  || ((x2==51) && (y2==12)))
  {delete_board();close_door();
  close_mouse();close_T_C_C_door();exit(0);} 
  /* if the cursor is at this cordinates and the mouse button
     was pressed the user will logout from the program */


  if((x2==60) && (y2==16)) {open_door();}

  if((x2==62) && (y2==16)) {close_door();}

  return(_AX);


}


///////////////////////// AUOTMATIC OPTION  ///////////////////////////////



/* THIS OPTION IS CONTROLING THE TFAFFICLIGHT COLORS AUTOMATICLLY.

   FIRST THE RED COLOR WILL BE APPEAR ON THE SCREEN FOR 3 SECONDS,
   NEXT THE RED AND THE YELLOW COLORS WILL BE APPEAR FOR 1.2 SECONDS.
   AFTER THAT THE RED AND YELLOW COLORS BOTH WILL BE ERASE FROM THE SCREEN
   AND THE GREEN COLOR WILL BE APPEAR ON THE SCREEN FOR 3 SECONDS.
   LATER ON THE BLINKING GREEN COLOR WILL BE APPEAR INSTAD THE GREEN COLOR
   FOR 3 SECONDS.
   THEN THE BLINKING GREEN WILL BE ERASE FROM THE SCREEN AND THE YELLOW
   COLOR WILL APPEAR ON THE SCREEN FOR 1.2 SECONDS AGAIN .
   AFTER THAT THE YELLOW COLOR WILL BE ERASE AND THE RED COLOR WILL BE
   APPAER ON THE SCREEN AGAIN FOR 3 SECONDS.

   THIS WILL GO ON AUTOMATICLLY UNTILL ANOTHER OPTION WILL START OR UNTILL
   THE INDEX WILL GET TO HIS MAXIMUM LIMIT .  */

void automatic_option()
{
TIMER();

gotoxy(45,20);textcolor(BLACK);cprintf("                ");
open_door();
gotoxy(48,8);textcolor(132);cprintf("1.AUTOMATIC");
gotoxy(48,10);textcolor(11);cprintf("2.MANUAL");
gotoxy(48,12);textcolor(11);cprintf("3.RESET");
gotoxy(48,14);textcolor(11);cprintf("4.EXIT");

int red=1;    /* when the red color is appear on the screen
		 the right keyboard light will light on .  */

int yellow=4; /* when the yellow color is appear on the screen
	       the center keyboard light will light on .  */

int green=2;  /* when the green color is appear on the screen
		 the left keyboard light will light on .  */

int red_yellow=5;

delete_board();

outport(0x60,0xed); // reset the keyboard for interrupt
color_red();
outport(0x60,red);

outport(0x60,0xed);
color_yellow();
outport(0x60,red_yellow);

gotoxy(18,8);textcolor(BLACK);cprintf("%c",219);
gotoxy(19,8);textcolor(BLACK);cprintf("%c",219);
gotoxy(20,8);textcolor(BLACK);cprintf("%c",219);
gotoxy(21,8);textcolor(BLACK);cprintf("%c",219);
TIMER();

gotoxy(18,11);textcolor(BLACK);cprintf("%c",219);
gotoxy(19,11);textcolor(BLACK);cprintf("%c",219);
gotoxy(20,11);textcolor(BLACK);cprintf("%c",219);
gotoxy(21,11);textcolor(BLACK);cprintf("%c",219);
TIMER();

outport(0x60,0xed);
color_green();
outport(0x60,green);

blink_color_green();

gotoxy(18,14);textcolor(BLACK);cprintf("%c",219);
gotoxy(19,14);textcolor(BLACK);cprintf("%c",219);
gotoxy(20,14);textcolor(BLACK);cprintf("%c",219);
gotoxy(21,14);textcolor(BLACK);cprintf("%c",219);
TIMER();

outport(0x60,0xed);
color_yellow();
outport(0x60,yellow);

gotoxy(27,11);textcolor(BLACK);cprintf("      ");
gotoxy(18,11);textcolor(BLACK);cprintf("%c",219);
gotoxy(19,11);textcolor(BLACK);cprintf("%c",219);
gotoxy(20,11);textcolor(BLACK);cprintf("%c",219);
gotoxy(21,11);textcolor(BLACK);cprintf("%c",219);
TIMER();

outport(0x60,0xed);
color_red();
outport(0x60,red);
gotoxy(18,8);textcolor(BLACK);cprintf("%c",219);
gotoxy(19,8);textcolor(BLACK);cprintf("%c",219);
gotoxy(20,8);textcolor(BLACK);cprintf("%c",219);
gotoxy(21,8);textcolor(BLACK);cprintf("%c",219);
gotoxy(27,8);textcolor(BLACK);cprintf("      ");
TIMER();
}

///////////////////////////  MANUAL OPTION  //////////////////////////////////



/* IN THIS OPTION THE CONTROLING OF THE COLORS APPEARANCE ON THE SCREEN
   IS BY THE USER AND NOT AUTOMATICLLY.
   A PANEL WITH ALL THREE COLORS WILL BE APPEAR ON THE SCREEN:

 * IF THE USER PUT THE CURSOR ON THE RED COLOR IN THE PANEL AND PRESS THE
   MOUSE LEFT BUTTON,THE RED TRAFFICLIGHT COLOR WILL BE APPEAR ON THE SCREEN
   AND THE OTHERS COLORS WILL NOT BE APPEAR ON THE SCREEN.

 * IF THE USER PUT THE CURSOR ON THE YELLOW COLOR IN THE PANEL AND PRESS THE
   MOUSE LEFT BUTTON,THE YELLOW TRAFFICLIGHT COLOR WILL BE APPEAR ON THE SCREEN
   AND THE OTHERS COLORS WILL NOT BE APPEAR ON THE SCREEN.

 * IF THE USER PUT THE CURSOR ON THE GREEN COLOR IN THE PANEL AND PRESS THE
   MOUSE LEFT BUTTON,THE GREEN TRAFFICLIGHT COLOR WILL BE APPEAR ON THE SCREEN
   AND THE OTHERS COLORS WILL NOT BE APPEAR ON THE SCREEN.     */

void manual_option()
{

TIMER();

gotoxy(45,20);textcolor(BLACK);cprintf("                ");

gotoxy(48,8);textcolor(11);cprintf("1.AUTOMATIC");
gotoxy(48,10);textcolor(132);cprintf("2.MANUAL");
gotoxy(48,12);textcolor(11);cprintf("3.RESET");
gotoxy(48,14);textcolor(11);cprintf("4.EXIT");

TIMER();
gotoxy(8,18);textcolor(9);cprintf("%c",201);
for(k=9;k<32;k++){gotoxy(k,18);textcolor(9);cprintf("%c",205);delay(10);}
gotoxy(32,18);textcolor(9);cprintf("%c",187);
for(k=19;k<23;k++){gotoxy(32,k);textcolor(9);cprintf("%c",186);delay(10);}
gotoxy(32,22);textcolor(9);cprintf("%c",188);
for(k=31;k>8;k--){gotoxy(k,22);textcolor(9);cprintf("%c",205);delay(15);}
gotoxy(8,22);textcolor(9);cprintf("%c",200);
for(k=21;k>18;k--){gotoxy(8,k);textcolor(9);cprintf("%c",186);delay(15);}

gotoxy(9,17);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);

gotoxy(33,18);textcolor(BLUE);cprintf("%c",219);
gotoxy(33,19);textcolor(BLUE);cprintf("%c",219);
gotoxy(33,20);textcolor(BLUE);cprintf("%c",219);
gotoxy(33,21);textcolor(BLUE);cprintf("%c",219);


gotoxy(10,23);textcolor(9);cprintf("color board");



/*gotoxy(8,17);textcolor(9);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
,218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);

gotoxy(32,18);textcolor(9);cprintf("%c",179);
gotoxy(32,19);textcolor(9);cprintf("%c",179);
gotoxy(32,20);textcolor(9);cprintf("%c",179);
gotoxy(8,18);textcolor(9);cprintf("%c",179);
gotoxy(8,19);textcolor(9);cprintf("%c",179);
gotoxy(8,20);textcolor(9);cprintf("%c",179);

gotoxy(8,21);textcolor(9);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
,192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);

gotoxy(33,17);textcolor(BLACK);cprintf("%c",219);
gotoxy(33,21);textcolor(BLACK);cprintf("%c",219);  */


TIMER();

gotoxy(11,19);textcolor(RED);cprintf("%c",16);
gotoxy(20,19);textcolor(YELLOW);cprintf("%c",16);
gotoxy(30,19);textcolor(GREEN);cprintf("%c",16);

gotoxy(10,21);textcolor(9);cprintf("off");
gotoxy(20,21);textcolor(9);cprintf("off");
gotoxy(29,21);textcolor(9);cprintf("off");


left_press=0;
see_mouse();

}

///////////////////////////  RESET OPTION  //////////////////////////////////



/*                THIS OPTION IS RESETING THE PROGRAM                */

void reset_option()
{
TIMER();
open_door();
gotoxy(48,8);textcolor(11);cprintf("1.AUTOMATIC");
gotoxy(48,10);textcolor(11);cprintf("2.MANUAL");
gotoxy(48,12);textcolor(132);cprintf("3.RESET");
gotoxy(48,14);textcolor(11);cprintf("4.EXIT");

delete_board();
TIMER();
gotoxy(45,20);textcolor(RED);cprintf("choose an option");delay(200);
if(left_press==1){
TIMER();
gotoxy(45,20);textcolor(BLACK);cprintf("                "); mouse_functions();}
draw_traffic();
malben();

}

///////////////////////////////  TIMER  //////////////////////////////////////


/* THIS FUNCTION IS LINKING THE PROGRAM TO THE CLOCK OPERATING SYSTEM
   AND PRINTING THE CORRENT TIME ON THE SCREEN */

void TIMER()
{

  _AH = 0x2a;
  geninterrupt(0x21);
  _AH = 0x2c;
  geninterrupt(0x21);
   my_time.hour = _CH;
  my_time.min  = _CL;
  my_time.sec  = _DH;




  gotoxy(24,23);
  printf("THE TIME IS: %d:%d:%d ",
	  my_time.hour,
	  my_time.min,
	  my_time.sec );


}

///////////////////////////  CREAT DOOR    ////////////////////////////////////



/* THIS FUNCTION IS CREATING THE CONTROL BOARD DOOR  */

void creat_door()
{
TIMER();
gotoxy(46,7);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);
gotoxy(46,8);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);
gotoxy(46,9);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);
gotoxy(46,10);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);
gotoxy(46,11);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);
gotoxy(46,12);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);
gotoxy(46,13);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);
gotoxy(46,14);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);
gotoxy(46,15);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);

TIMER();

}

////////////////////////////  OPEN DOOR //////////////////////////////////////



/* THIS FUNCTION IS OPENNING THE CONTROL BOARD DOOR  */


void open_door()
{

delete_board();
TIMER();
gotoxy(46,15);textcolor(BLACK);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219); delay(100);
gotoxy(46,14);textcolor(BLACK);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219); delay(100);
gotoxy(48,14);textcolor(11);cprintf("4.EXIT");

gotoxy(46,13);textcolor(BLACK);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219); delay(100);
gotoxy(46,12);textcolor(BLACK);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219); delay(100);
gotoxy(48,12);textcolor(11);cprintf("3.RESET");

gotoxy(46,11);textcolor(BLACK);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);  delay(100);
gotoxy(46,10);textcolor(BLACK);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);  delay(100);
gotoxy(48,10);textcolor(11);cprintf("2.MANUAL");

gotoxy(46,9);textcolor(BLACK);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);  delay(100);
gotoxy(46,8);textcolor(BLACK);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);  delay(100);
gotoxy(48,8);textcolor(11);cprintf("1.AUTOMATIC");

gotoxy(46,7);textcolor(BLACK);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);  delay(100);

gotoxy(42,18);textcolor(BLACK);cprintf("                  ");
gotoxy(62,18);textcolor(BLACK);cprintf("%c",30);


gotoxy(42,18);textcolor(WHITE);cprintf("close control board");
gotoxy(64,18);textcolor(RED);cprintf("%c",31);

gotoxy(45,20);textcolor(RED);cprintf("choose an option");delay(500);


}

///////////////////////////  CLOSE DOOR  ///////////////////////////////////////

/* THIS FUNCTION IS CLOSING THE CONTROL BOARD DOOR  */

void close_door()
{

delete_board();
TIMER();

gotoxy(46,7);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219); delay(100);
gotoxy(46,8);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219); delay(100);

gotoxy(46,9);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219); delay(100);
gotoxy(46,10);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219); delay(100);

gotoxy(46,11);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);  delay(100);
gotoxy(46,12);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);  delay(100);

gotoxy(46,13);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);  delay(100);
gotoxy(46,14);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);  delay(100);

gotoxy(46,15);textcolor(BLUE);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,
219,219,219,219,219,219,219);  delay(100);

gotoxy(42,18);textcolor(BLACK);cprintf("                   ");
gotoxy(64,18);textcolor(BLACK);cprintf("%c",31);

gotoxy(42,18);textcolor(WHITE);cprintf("open control board");
gotoxy(62,18);textcolor(GREEN);cprintf("%c",30);


}

///////////////////////// DELETE BOARD ////////////////////////////////////////


/* THIS FUNCTION DELETE THE MANUAL COLORS BOARD FROM THE SCREEN */

void delete_board()
{
TIMER();

gotoxy(45,20);textcolor(BLACK);cprintf("                ");
gotoxy(11,19);textcolor(BLACK);cprintf("%c",16);
gotoxy(20,19);textcolor(BLACK);cprintf("%c",16);
gotoxy(30,19);textcolor(BLACK);cprintf("%c",16);

gotoxy(10,23);textcolor(BLACK);cprintf("color board");
gotoxy(10,21);textcolor(BLACK);cprintf("   ");
gotoxy(20,21);textcolor(BLACK);cprintf("   ");
gotoxy(29,21);textcolor(BLACK);cprintf("   ");


gotoxy(8,18);textcolor(BLACK);cprintf("%c",201);
for(k=9;k<32;k++){gotoxy(k,18);textcolor(BLACK);cprintf("%c",205);delay(10);}
gotoxy(32,18);textcolor(BLACK);cprintf("%c",187);
for(k=19;k<22;k++){gotoxy(32,k);textcolor(BLACK);cprintf("%c",186);delay(10);}
gotoxy(32,22);textcolor(BLACK);cprintf("%c",188);
for(k=31;k>8;k--){gotoxy(k,22);textcolor(BLACK);cprintf("%c",205);delay(15);}
gotoxy(8,22);textcolor(BLACK);cprintf("%c",200);
for(k=21;k>18;k--){gotoxy(8,k);textcolor(BLACK);cprintf("%c",186);delay(15);}


gotoxy(9,17);textcolor(BLACK);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);

gotoxy(33,18);textcolor(BLACK);cprintf("%c",219);
gotoxy(33,19);textcolor(BLACK);cprintf("%c",219);
gotoxy(33,20);textcolor(BLACK);cprintf("%c",219);
gotoxy(33,21);textcolor(BLACK);cprintf("%c",219);


/*gotoxy(8,17);textcolor(BLACK);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
,218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);

gotoxy(32,18);textcolor(BLACK);cprintf("%c",179);
gotoxy(32,19);textcolor(BLACK);cprintf("%c",179);
gotoxy(32,20);textcolor(BLACK);cprintf("%c",179);
gotoxy(8,18);textcolor(BLACK);cprintf("%c",179);
gotoxy(8,19);textcolor(BLACK);cprintf("%c",179);
gotoxy(8,20);textcolor(BLACK);cprintf("%c",179);

gotoxy(8,21);textcolor(BLACK);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
,192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);

gotoxy(33,17);textcolor(BLACK);cprintf("%c",219);
gotoxy(33,21);textcolor(BLACK);cprintf("%c",219);    */



}

////////////////////////  CLOSE T.C.C DOOR   ////////////////////////////////

void close_T_C_C_door()

{
clrscr();
for(k=15;k<65;k++){gotoxy(k,10);textcolor(9);cprintf("%c",205);delay(10);}
for(k=65;k>15;k--){gotoxy(k,15);textcolor(9);cprintf("%c",205);delay(10);}
gotoxy(15,10);textcolor(9);cprintf("%c",201);
gotoxy(65,10);textcolor(9);cprintf("%c",187);
gotoxy(15,15);textcolor(9);cprintf("%c",200);
gotoxy(65,15);textcolor(9);cprintf("%c",188);
for(k=11;k<15;k++){gotoxy(15,k);textcolor(9);cprintf("%c",186);delay(10);}
for(k=11;k<15;k++){gotoxy(65,k);textcolor(9);cprintf("%c",186);delay(10);}
gotoxy(34,12);textcolor(WHITE);cprintf("GETTING OUT FROM ");
gotoxy(28,13);textcolor(WHITE);cprintf("TRAFFICLIGHTS CONTROL CENTER");

getch();
gotoxy(34,12);textcolor(WHITE);cprintf("                ");
gotoxy(28,13);textcolor(WHITE);cprintf("                            ");

gotoxy(30,12);textcolor(7);cprintf("PROGRAM CREATED BY");
gotoxy(34,13);textcolor(7);cprintf("…˜Œ…ˆ‘ ‰‰”");
getch();
gotoxy(16,11);textcolor(9);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
219,219,219,219,219,219,219,219,219);delay(150);

gotoxy(16,12);textcolor(9);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
219,219,219,219,219,219,219,219,219);delay(150);

gotoxy(16,13);textcolor(9);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
219,219,219,219,219,219,219,219,219);delay(150);

gotoxy(16,14);textcolor(9);cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,
219,219,219,219,219,219,219,219,219);delay(100);

}

