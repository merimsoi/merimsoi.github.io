#include"hw2.h"
void interrupt ( *oldhandler)(__CPPARGS);
//********************* init of extern variable  ********************************
int ch;
int count=0;                               //counter of ticks
float priority[3]={5,5,5};                 //array of priority of semaphor
float count_cars[3]={50,50,50};            //array of count cars
int frequency=50;                           //frequency of system
int active=1;                              //flag,which semaphor is active
int num_menu=-1;                            //flag,which menu is active
int bar_menu=0;                            //flag of position in menu
int time1,time2,time3;                     //count of puls,to every semaphor
int input1=0,input2=0,input3=0,input4=0;   //flags of input
int buffer=0;                              //var. to help in input
int change_menu=0;                         //flag,which say if was change of menu
int error=0;                               //flag of error in input
int light_activity=1;       		   //flag,whith light of keyboard is active
int led1=3,led2=1,led3=1;                  //flag of color to every semaphor
int change_led=0;                          //flag,which say if was change of leds
int change_color=0;                        //flag,which say if was change color
float ticks_in_puls=18.2;                  //default count ticks in puls
int twocolor=0;                            //flag,which say that semaphor have red and yellow
char menu[4][26]={" Change System Frequency ",
		  " Change Count of cars    ",
		  " Change System Priority  ",
		  " Change LEDS          "};
char menu2[3][13]={" For 1 Road ",
		   " For 2 Road ",
		   " For 3 Road"};
char menu3[3][20]={" For Semaphor #1 ",
		   " For Semaphor #2 ",
		   " For Semaphor #3"};
char menu4[3][14]={" Semaphor #1 ",
		   " Semaphor #2 ",
		   " Semaphor #3"};
//********************** main ***********************************************
void main()
{
Init();
Loop();
}
//************************************************************************
//Function handler is the new handler of interrupt 0x1c
//************************************************************************
void interrupt handler(__CPPARGS)
{
/* increase the global counter */
   count++;
/* call the old routine */
   oldhandler();
}
//************************************************************************
//Function Init execute initialization of first status of system
//************************************************************************
void Init()
{
_setcursortype(_NOCURSOR);
textbackground(BLACK);
window(1,1,80,25);
clrscr();
Road();                                    //draw "street"
Semaphor(1,3,1);                           //init the semaphors
Semaphor(2,1,1);
Semaphor(3,1,1);
Change_leds(1);
time1=Time_of_semaphor(1);                //calculate time for every semaphor
time2=Time_of_semaphor(2);
time3=Time_of_semaphor(3);
change_color=0;
oldhandler = getvect(INTR);               // save the old interrupt vector
setvect(INTR, handler);                   //install the new interrupt handler
}
//*************************************************************************
void Loop()
{
for(;;)
 {  _AH=0x0B;
    geninterrupt(0x21);
    if(_AL) Check();	        	   //if pressed key?
    if(change_menu)                        //if changed menu?
      {
	switch(active)                     //if changed menu in time of yellow
	 {                                 //immediately green to next
	 case 1:if(count>=time1-TIME_TO_YELLOW) Change_color(1,1);break;
	 case 2:if(count>=time2-TIME_TO_YELLOW) Change_color(2,1);break;
	 case 3:if(count>=time2-TIME_TO_YELLOW) Change_color(3,1);break;
	 }
       time1=Time_of_semaphor(1);          //calculate new time for
       time2=Time_of_semaphor(2);          //each semaphor
       time3=Time_of_semaphor(3);
      }
    if(change_color||change_led)          //if changed color of semaphors
     {                                   //or changed semaphor to show leds

      if(twocolor) Change_leds(6);       //if semaphor in color red and yellow
      else
	 switch(light_activity)          //if active only one color
	  {
	  case 1:Change_leds(led1);break; //red
	  case 2:Change_leds(led2);break; //yellow
	  case 3:Change_leds(led3);break; //green
	  } //switch
     } //if-then
       switch(active)                     //who is active?
      {
       case 1: {               //if according to new calculation time is over?
	       if(count>time1) {
				count=0;
				Change_color(active,1);
			       }
			      //if now time to change color to yellow
	       else if(count==time1-TIME_TO_YELLOW)
				 Change_color(active,0);
			      //if semaphor finished his work
		    else if(count==time1 )
				 Change_color(active,1);
				 break;
	       } //case 1
	case 2:{
		if(count>time2) {
				count=0;
				Change_color(active,1);
				}
		else if(count==time2-TIME_TO_YELLOW)
				 Change_color(active,0);
		     else if(count==time2)
				 Change_color(active,1);
				 break;
	       } //case 2
	case 3:
	       {
		if(count>time3) {
				 count=0;
				 Change_color(active,1);
				 }
		else if(count==time3-TIME_TO_YELLOW)
				 Change_color(active,0);
		     else if(count==time3)
				 Change_color(active,1);
				 break;
	       }//case 3
      } //end of switch
      change_menu=0;
}//end of for
/* reset the old interrupt handler */
   setvect(INTR, oldhandler);
}
//***************************************************************************
//Function Change_leds changes the leds of keyboard.It receives one parameter
// num that means which led will turn on
//***************************************************************************
void Change_leds(int num)
{
outport(0x60,0xED);
outport(0x60,num);
change_color=0;
change_led=0;
twocolor=0;
}
//************************************************************************
//Fuction Change color.It receives two parametres
// num - which semaphor needed to change color
// status  - 0:to yellow(active semaphor is not changed)
//           1:to red or green(active semaphor is changed)
//************************************************************************
void Change_color(int num,int status)
{ int next=num+1;                            //if next is first
  if(next>3)next=1;
  change_color=1;
  switch(status)
   {
    case 0:Semaphor(num,2,0);                 //yellow for current semaphor
	   Semaphor(next,2,1);                //yellow for next semaphor
	   break;
    case 1:active=num+1;
	   if(active==4) active=1;           //after semaphor 3 active is 1
	   Semaphor(next,3,1);               //green to next semaphor
	   Semaphor(num,1,1);                //red for current semaphor
	   count=0;break;
   }
}
//*************************************************************************
//Function Time of Semaphor received number of semaphor needed to calculation
//time.The time is calculated according to
//                                      ticks in puls
//		  	                priority
//			                count of cars
//*************************************************************************
int Time_of_semaphor(int num)
{
int sum_priority=priority[0]+priority[1]+priority[2];
int sum_cars=count_cars[0]+count_cars[1]+count_cars[2];

float for_preority=
     (float)(100*ticks_in_puls)/sum_priority*priority[num-1]*(float)1/3;


float for_count_car=
      (float)(100*ticks_in_puls)/sum_cars*count_cars[num-1]*(float)2/3;

return(for_preority+for_count_car);
}

//***************************************************************************
//Function Count_tick returns number ticks in 1 puls according to frequency
//***************************************************************************
float Count_tick(int freq)
{
if(freq>=1&&freq<=49)
return(18.2+(51-freq)*3.276);             // slow
else return(0.728+(100-freq)*0.34944);    // fast
}
//***************************************************************************
//Function Semaphor changes color to "num" semaphor.
// color :color to change
// status:0-blinking
//        1-normal
//***************************************************************************
void Semaphor(int num,int color,int status)
{
 if(status&&color==2)
      {if(light_activity==num) twocolor=1;}     //if state of 2 colors
     else
     {
     textbackground(0);                    //if not state of 2 colors-clear
      switch(num)
      { case 1:window(45,3,49,5);break;        //1
	case 2:window(28,9,32,11);break;       //2
	case 3:window(45,12,49,14);break;      //3
      }
     clrscr();
     }
  switch(color)                                         //which new color
   {
    case 1:{ textbackground(4);                         //red?
	     switch(num)
	       {case 1:window(46,3,48,3);led1=2;break;  //for 1 semaphor
		case 2:window(29,9,31,9);led2=2;break;  //for 2 semaphor
		case 3:window(46,12,48,12);led3=2;break;//for 3 semaphor
	       }
	     clrscr();
	     break;
	   }//case 1
    case 2: {if(status) textcolor(YELLOW);               //yellow?
	     else textcolor(YELLOW+BLINK);
	     switch(num)
	      {case 1:window(46,4,49,4);led1=4;break;   //for 1 semaphor
	       case 2:window(29,10,32,10);led2=4;break; //for 2 semaphor
	       case 3:window(46,13,49,13);led3=4;break; //for 3 semaphor
	      }
	      putch(219);putch(219);putch(219);
	      break;
	    }//case 2
       case 3:{textbackground(10);                       //green?
	       switch(num)
	       {case 1:window(46,5,48,5);led1=1;break;   //for 1 semaphor
		case 2:window(29,11,31,11);led2=1;break; //for 2 semaphor
		case 3:window(46,14,48,14);led3=1;break; //for 3 semaphor
		}
	       clrscr();
	      }//case 3
   }//switch
}

//************************************************************************
//Function Check check in every moment which key was presed
//************************************************************************
void Check()
{
_AH=0x08;
geninterrupt(0x21);
ch=_AL;
fflush(stdin);
switch(ch)
{
case 27:                                          //ESC
	if(input1) num_menu=1;                    // to clear as in mode menu 1,2
	input1=0;
	input2=0;
	input3=0;
	Clear();
	if(buffer!=0){buffer=0;num_menu=0;}
	break;
case 67:num_menu=0;                               //F9
	Create(5,19,31,24,10,1,bar_menu,0);break;
case 68:                                          //F10
	exit(0);break;
case 72:if(!input1&&!input2&&!input3)             //arrow up
	 {
	  bar_menu--;
	  if(bar_menu==-1&&!num_menu)bar_menu=3;
	  else if (bar_menu==-1) bar_menu=2;
	  Whitch_menu(num_menu);
	 }
	break;
case 80:if(!input1&&!input2&&!input3)             //arrow down
	 {
	  bar_menu++;
	  if(bar_menu==4)bar_menu=0;
	  else if(bar_menu==3&&num_menu)bar_menu=0;
	  Whitch_menu(num_menu);
	 }
	break;
case 13:Where_enter();break;                      //enter
case 48:                                          //numbers 0..9
case 49:
case 50:
case 51:
case 52:
case 53:
case 54:
case 55:
case 56:
case 57:{
	 Check_input(ch);                         //involve function
	 break;                                   //checks input
	 }
}
}
//*************************************************************************
//Function Where_enter checks where was pressed enter
//*************************************************************************
void Where_enter()
{
  switch(num_menu)                                   //check menu
   {
   case 0:                                           //main menu?
	  {
	    switch(bar_menu)
	     {
	      case 0:Change_frequency();break;
	      case 1:Change_count_cars();break;
	      case 2:Change_system_priority();break;
	      case 3:Change_light();break;
	     }//switch bar_menu
	     break;
	  }//case 0
  case 1: Road_car();break;			//change cars?
  case 2: Pr_Semaphor();break;			//change priority?
  case 3: input4=1;break;		        //change LEDS of keyboard?
    }//switch
 if(input1&&buffer!=0)                          //in input frequency?
  {
   frequency=buffer;
   ticks_in_puls=Count_tick(frequency);        //count number of ticks in puls
   buffer=0;
   change_menu=1;
   num_menu=1;                                 // to clear as in mode menu 1,2
   Clear();
   num_menu=0;                                 //return flag of menu
   input1=0;
  }
   if(input2&&buffer!=0)                       //in input count of cars?
  {
   count_cars[bar_menu]=buffer;
   buffer=0;
   change_menu=1;
   Clear();
   input2=0;
  }
 if(input3&&buffer!=0)                        //in input priority?
  {
   priority[bar_menu]=buffer;
   buffer=0;
   change_menu=1;
   Clear();
   input3=0;
  }
 if(input4)                                  //in input light?
  {
  light_activity=bar_menu+1;
  window(1,1,80,25);
  textcolor(9);
  textbackground(0);
  DrawFrame(44,2,50,6);
  DrawFrame(27,8,33,12);
  DrawFrame(44,11,50,15);
  textcolor(12);
  window(1,1,80,25);
  switch(light_activity)
   {
    case 1:gotoxy(45,2);break;
    case 2:gotoxy(28,8);break;
    case 3:gotoxy(45,11);break;
   }
   putch(15);
   change_led=1;
   Clear();
   input4=0;
 }
}
//************************************************************************
//Function Check_input join all number of input in variable buffer.
//************************************************************************
void Check_input(int ch)
{
int x,y;
textcolor(11);
textbackground(1);
if(input1||input2||input3)                     //if in mode input?
{
 if(input1){x=45;y=20;}                        //coordinates of input
 else if(input2){x=57;y=19;}
       else {x=60;y=19;}
  if(error)                                    //if new input after error
	 {                                     //delete string about old error
	 window(1,1,80,25);
	 gotoxy(x-2,y);
	 cprintf("               ");
	 error=0;
	 }
  if(!buffer)                                  //if number first in input?
   {
    buffer=ch-48;
    window(1,1,80,25);
    gotoxy(x,y);
    if(buffer!=0) cprintf("%d",ch-48);
   }
  else  if(input3&& ch-48!=0)                 //if input priority (1-10)
			{error=1;             //and second number not 0?
			 window(1,1,80,25);
			 gotoxy(x-1,y);
			 cprintf("Error in input");
			 buffer=0;
			 }
	else if(buffer!=0&&buffer<10)         //if second number?
	     {
	     buffer=buffer*10+(ch-48);
	     window(1,1,80,25);
	     gotoxy(x+1,y);
	     cprintf("%d",ch-48);
	     }

	    else if(buffer!=0&&(buffer*10+(ch-48))>100) //if input 1-100
						      //and third number not 0?
						      {error=1;
						       window(1,1,80,25);
						       gotoxy(x-1,y);
						       cprintf("Error in input");
						       buffer=0;
						      }
		 else {                                //if third number?
		       buffer=100;
		       window(1,1,80,25);
		       gotoxy(x+2,y);
		       cprintf("0");
		      }
 }
}
