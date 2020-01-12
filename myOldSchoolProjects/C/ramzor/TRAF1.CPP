#include <a:\ira\headtraf.h>

  int x,y,l = 245;
//***********************************************************************
	       void poly(int x1,int y1,int x2,int y2,int stile,int color)
{
   int poly[8];
   setfillstyle(stile,color);
   setcolor(color);
   poly[0] = x1;        /* 1st vertex */
   poly[1] = y1;

   poly[2] = x2; /* 2nd */
   poly[3] = y1;

   poly[4] = x2; /* 3rd */
   poly[5] = y2;

   poly[6] = x1;    /*4th*/
   poly[7] = y2;

   fillpoly(4, poly);
}
//**********************************************************************
			  void mouse_close()
{ _AX=0x02;
  geninterrupt(0x33);
}
//**********************************************************************
			  void sea_mouse()
{ _AX=0x01;
  geninterrupt(0x33);
}
//**********************************************************************
			   void mouse_zero(void)
{
       _AX=0x01;
     geninterrupt(0x33);
    _AX=0x05;
     geninterrupt(0x33);
      x =_CX;
      y =_DX;
 }
//**********************************************************************
			int arrow (int control)
{
   char a;
   char hetz[1]={0x11};
   setcolor(2);
       if(kbhit())
       {
		a=getch();
		switch(a)
	 {
	   case 'H':
		    if(l!=175)
		    l = l-35;
		    poly(617,170,640,300,1,0);
		    setcolor(2);
		    outtextxy(620,l,hetz);
		    break;
	   case 'P':
		    if(l!=280)
		    l = l+35;
		    poly(617,170,640,300,1,0);
		    setcolor(2);
		    outtextxy(620,l,hetz);
		    break;
	   case 0x1b:
		     return (3);
	   default:
		     return(control);
	   case 13:
		    switch(l)
		      {
			case 175: control=0;x=550;y=170; break;//return(0);
			case 210: control=1;x=550;y=200; break;//return(1);
			case 245: control=2;x=550;y=240; break;//return(2);
			case 280: control=3;x=550;y=280; break;//return(3);
		       }
	      }
	 }

     setcolor(0);
	return(control);
}


//***********************************************************************
			   int mouse(int control)
{

      int key;
    _AX=0x01;
     geninterrupt(0x33);
    _AX=0x05;
     geninterrupt(0x33);
      x =_CX;
      y =_DX;


   if ((x<590)&&(x>510)&&(y<190)&&(y>160))
     {
      control=0;
      geninterrupt(0x33);
      y=175;
      x=580;
     }
   if ((x<590)&&(x>510)&&(y<225)&&(y>195))
    { control=1;
    geninterrupt(0x33);
     y=200;
     x=580;
     }
   if ((x<590)&&(x>510)&&(y<260)&&(y>230))
     {
      control=2;
      geninterrupt(0x33);
      y=245;
      x=580;
     }
   if ((x<590)&&(x>510)&&(y<295)&&(y>265))  control=3;

    //if(key!=control)
    // {
       key=arrow(control);
     //	cout<<control<< x<< y <<"\r";
       return(key);

    // }

      //	return(control);

 }

//***********************************************************************
			void move()
{
  setcolor(0);

  int i,x1=280,y1=450,x=260,y=450,R1=15,r=2,R2=30,r2=30;
   for(i=0;x>220;i++,x--,y-=4,x1--,y1-=4)
      {
	 if(i%6==0)
	   { x1--;R1-=2;R2-=4;r2-=2;}
	 setfillstyle(1,RED);
	 fillellipse(x,y,r,R1);
	 fillellipse(x,y,R1,r);

	 fillellipse(x1,y1,r,R1);
	 fillellipse(x1,y1,R1,r);
	 setfillstyle(1,YELLOW);
	 if(x1>242)
	   {
	    sector(x,y-25,90,120,r2,R2);
	    sector(x1-10,y1-25,90,120,r2,R2);
	   }
  delay(20);
	 setfillstyle(1,0);
	  fillellipse(x,y,r,R1);
	  fillellipse(x,y,R1,r);
	  fillellipse(x1,y1,r,R1);
	  fillellipse(x1,y1,R1,r);
       if(x1>242)
	 {
	  sector(x,y-25,90,120,r2,R2);
	  sector(x1-10,y1-25,90,120,r2,R2);
	 }
      }//for

}//end
//***********************************************************************

			int avto(int control)
{
    int i,a;
    setcolor(0);
 while(control == 0)
 {
     setfillstyle(3, 62);                      //green
   fillellipse(200,200,20,20);
   setfillstyle(3,RED);
   fillellipse(200,150,20,20);
   setfillstyle(1,GREEN);
   fillellipse(200,250,20,20);
   control = mouse(control);
      if(control) return (control);
   outport(0X60,0XED) ;
   delay(5);
   outport(0X60,2);
   time(8,1);

			   //green blinks
   setfillstyle(3,RED);
   fillellipse(200,150,20,20);
   setfillstyle(3, 62);
   fillellipse(200,200,20,20);       //none
   setfillstyle(3,GREEN);
   fillellipse(200,250,20,20);
   control = mouse(control);
    if (control) return(control);
   outport(0X60,0XED) ;
   delay(5);
   outport(0X60,0);
   time(2,1);

   setfillstyle(3,RED);
   fillellipse(200,150,20,20);
   setfillstyle(3, 62);
   fillellipse(200,200,20,20);       //green
   setfillstyle(1,GREEN);
   fillellipse(200,250,20,20);
   control = mouse(control);
     if (control) return(control);
   outport(0X60,0XED) ;
   delay(5);
   outport(0X60,2);
   time(2,1);

   setfillstyle(3,RED);
   fillellipse(200,150,20,20);
   setfillstyle(3, 62);
   fillellipse(200,200,20,20);       //none
   setfillstyle(3,GREEN);
   fillellipse(200,250,20,20);
   control = mouse(control);
      if (control) return(control);
   outport(0X60,0XED) ;
   delay(5);
   outport(0X60,0);
   time(2,1);

   setfillstyle(3,RED);
   fillellipse(200,150,20,20);
   setfillstyle(3, 62);
   fillellipse(200,200,20,20);       //green
   setfillstyle(1,GREEN);
   fillellipse(200,250,20,20);
   control = mouse(control);
      if (control) return(control);
   outport(0X60,0XED) ;
   delay(5);
   outport(0X60,2);
   time(2,1);

   setfillstyle(3,RED);
   fillellipse(200,150,20,20);
   setfillstyle(3, 62);
   fillellipse(200,200,20,20);       //none
   setfillstyle(3,GREEN);
   fillellipse(200,250,20,20);
   control = mouse(control);
      if (control) return(control);
   outport(0X60,0XED) ;
   delay(5);
   outport(0X60,0);
   time(2,1);

   setfillstyle(3,RED);
   fillellipse(200,150,20,20);
   setfillstyle(3, 62);
   fillellipse(200,200,20,20);       //green
   setfillstyle(1,GREEN);
   fillellipse(200,250,20,20);
   control = mouse(control);
      if (control) return(control);
   outport(0X60,0XED) ;
   delay(5);
   outport(0X60,2);
   time(2,1);

   setfillstyle(3,RED);
   fillellipse(200,150,20,20);
   setfillstyle(3, 62);
   fillellipse(200,200,20,20);       //none
   setfillstyle(3,GREEN);
   fillellipse(200,250,20,20);
   control = mouse(control);
      if (control) return(control);
   outport(0X60,0XED) ;
   delay(5);
   outport(0X60,0);
   time(0,0);

   setfillstyle(1, 14);                      //yellow
   fillellipse(200,200,20,20);
   control = mouse(control);
      if (control) return(control);
   outport(0X60,0XED) ;
   delay(5);
   outport(0X60,4);
   time(4,1);

   setfillstyle(3, 62);                      //red
   fillellipse(200,200,20,20);
   setfillstyle(1,RED);
   fillellipse(200,150,20,20);
   control = mouse(control);
      if (control)  return(control);
   outport(0X60,0XED) ;
   delay(5);
   outport(0X60,1);
   time(12,1);
						    //yellow + red
   setfillstyle(1, 62);
   fillellipse(200,200,20,20);
   control = mouse(control);
     if(control) return(control);
   outport(0X60,0XED) ;
   delay(5);
   outport(0X60,5);
   time(6,1);
 }
   /* clean up */
   getch();
  // closegraph();
   return 0;
}
//*********************************************************************
				void time (int t,int mode)
{
 char a,msg[10],count_down[2];
 int i;
 int col,sec;
 long current;
 static float g;
  float s;
  struct tim {
	    int hour;
	    int min;
	    int sec ;
	    int mil;
	      } my_time;
 switch(t)
    {
      case 2  :  col = 250;  break;
      case 6  :  col = 200;  s=3; break;
      case 8  :  col = 250;  g=9.2; break;
      case 12 :  col = 150;  s=6.0; break;
      case 4  :  col = 200;  s=2.00; break;

     }
       _AH=0X2C;
   geninterrupt(0x21);
   my_time.hour=_CH;
   my_time.min=_CL;
   my_time.sec=_DH;
   my_time.mil=_DL;
   const long start=my_time.hour*360000+my_time.min*6000+my_time.sec*100+my_time.mil;
    for(i=0;i<t*25;i++)
{
   if(kbhit())
   break;
     if ( (mode)&&(mouse(0)))
	break;

     if(current>start+10) { s-=0.02; g-=0.02;}
      _AH=0X2C;
   geninterrupt(0x21);
   my_time.hour=_CH;
   my_time.min=_CL;
   my_time.sec=_DH;
   my_time.mil=_DL;
   current=my_time.hour*360000+my_time.min*6000+my_time.sec*100+my_time.mil;
   settextstyle(0,HORIZ_DIR,2);
   sprintf(msg,"%d:%d:%d",my_time.hour,my_time.min,my_time.sec);
   if(sec!=my_time.sec)
   {

   // if((mode)&&(t==8))
    //	move();

    setcolor(0);
    setfillstyle(1,0);
    fillellipse(460,355,70,25);
    setcolor(2);
    outtextxy(350,350,msg);
    sec=my_time.sec;
   }
   setcolor(2);

   if((mode)&&(t!=8)&&(t!=2))
    {
     sprintf(count_down,"%f",s);
     outtextxy(260,col,count_down);
     poly(323,140,405,270,1,0);
     }
    if((mode)&&((t==8)||(t==2)))
      {
       sprintf(count_down,"%f",g);
       outtextxy(260,col,count_down);
       poly(323,140,405,270,1,0);
      }

     delay(10);
     if(mode)
    poly(260,140,322,270,1,0);

  }
  setcolor(0);

}
//************************************************************************
			void tra_lts()
{

  //**
      int i;
      setbkcolor(0);
      poly(200,30,210,107,1,1);
      setfillstyle(0,1);
      bar3d(170,110,230,280,8,1);

      setcolor(0);
      setfillstyle(1,1);
      sector(200, 155, 0, 180, 25, 33);
      setfillstyle(1,0);
      sector(200, 167, 0, 180, 35, 35);

      setfillstyle(1,1);
      sector(200, 205, 0, 180, 25, 33);
      setfillstyle(1,0);
      sector(200, 217, 0, 180, 35, 35);

      setfillstyle(1,1);
      sector(200, 255, 0, 180, 25, 33);
      setfillstyle(1,0);
      sector(200, 267, 0, 180, 35, 35);
      setcolor(1);
      poly(170,110,230,280,0,1);

      setfillstyle(1,1);
      sector(234,122,270,350,20,13);
      sector(234,172,270,350,20,13);
      sector(234,222,270,350,20,13);
      sector(170,125,190,270,20,13);
      sector(170,175,190,270,20,13);
      sector(170,225,190,270,20,13);

      setcolor(0);
      setfillstyle(3,RED);
      fillellipse(200,150,20,20);
      setfillstyle(3, 62);
      fillellipse(200,200,20,20);
      setfillstyle(3,GREEN);
      fillellipse(200,250,20,20);
}
//**********************************************************************
			void buttons(int control)
{
  setbkcolor(0);
       int i,j,c;
      for(i=513,j=156,c=3;i>=510;i--,j++,c++)
       poly(i,j,i+80,j+30,7,1);
      for(i=513,j=193,c=3;i>=510;i--,j++,c++)
       poly(i,j,i+80,j+30,8,2);
      for(i=513,j=230,c=3;i>=510;i--,j++,c++)
       poly(i,j,i+80,j+30,9,3);
      for(i=513,j=267,c=3;i>=510;i--,j++,c++)
       poly(i,j,i+80,j+30,10,4);

      setcolor(WHITE);
      settextstyle(0,HORIZ_DIR,1);
      outtextxy(515,170,"AUTOMATIC");
      outtextxy(528,205,"MANUAL");
      outtextxy(530,245,"RESET");
      outtextxy(535,281,"EXIT");
      switch(control)
      {
       case 0:
	       poly(510,156,593,191,1,0);
	       poly(513,159,592,188,7,1);
	       setcolor(7);
	       outtextxy(517,170,"AUTOMATIC");
	       break;
       case 1:
	       poly(510,193,593,228,1,0);
	       poly(513,196,592,225,8,2);
	       setcolor(7);
	       outtextxy(530,205,"MANUAL");
	       break;
       case 2:
		poly(510,230,593,265,1,0);
		poly(513,233,592,262,9,3);
		setcolor(7);
		outtextxy(532,245,"RESET");
		break;
       case 3:
	       poly(510,267,593,302,1,0);
	       poly(513,270,592,299,10,4);
	       setcolor(7);
	       outtextxy(537,281,"EXIT");
	       break;
       default : break;
       }
 setcolor(0);
}
//**********************************************************************
			void menu()
{
  int gdriver = DETECT, gmode, errorcode;
  initgraph(&gdriver, &gmode, "d:\\borlandc\\bgi");
  errorcode = graphresult();
  if (errorcode != grOk)
  {
    printf("Graphics error: %s\n", grapherrormsg(errorcode));
    printf("Press any key to halt:");
    getch();
    exit(1);
  }
  int a,i,j,c;
  for(i=515,j=135,c=5;i>=500;i--,j++,c--)
  poly(i,j,i+100,j+155,11,8);
  setcolor(7);
  line(0,400,50,400);
  line(350,400,600,400);

  line(50,400,170,270);
  line(50,415,172,270);
  line(50,400,50,415);
  line(0,415,50,415);

  line(350,400,238,278);
  line(350,415,236,280);
  line(350,415,600,415);
  line(350,400,350,415);
  line(0,210,160,210);
  line(250,210,400,210);

 setcolor(7);
 for(a=195;a<206;a++)
  line(a,380,200,285);

   setcolor(0);

  setfillstyle(1,YELLOW);
  fillellipse(100,50,20,20);
  setfillstyle(1,0);
  fillellipse(115,45,25,25);

  setfillstyle(1,YELLOW);
  fillellipse(300,50,2,15);
  fillellipse(300,50,15,2);

  fillellipse(500,80,2,15);
  fillellipse(500,80,15,2);

  fillellipse(400,100,2,15);
  fillellipse(400,100,15,2);


}
//************************************************************************
			int manual(int control)
{
	setfillstyle(3,RED);
	fillellipse(200,150,20,20);
	setfillstyle(3,YELLOW);
	fillellipse(200,200,20,20);
	setfillstyle(3,GREEN);
	fillellipse(200,250,20,20);
    while(control==1)
   {
     time(1,0);
     if((x<=250)&&(x>=150)&&(y<=170)&&(y>=130))
      {
	setfillstyle(1,RED);
	fillellipse(200,150,20,20);
	setfillstyle(3,YELLOW);
	fillellipse(200,200,20,20);
	setfillstyle(3,GREEN);
	fillellipse(200,250,20,20);
	outport(0X60,0XED) ;
	delay(5);
	outport(0X60,1);
       }
     if((x<=250)&&(x>=150)&&(y<=220)&&(y>=180))
      {
	setfillstyle(1,YELLOW);
	fillellipse(200,200,20,20);
       setfillstyle(3,RED);
	fillellipse(200,150,20,20);
	setfillstyle(3,GREEN);
	fillellipse(200,250,20,20);
	outport(0X60,0XED) ;
	delay(5);
	outport(0X60,4);
       }
      if((x<=250)&&(x>=150)&&(y<=270)&&(y>=230))
      {
	setfillstyle(1,GREEN);
	fillellipse(200,250,20,20);
	setfillstyle(3,RED);
	fillellipse(200,150,20,20);
	setfillstyle(3,YELLOW);
	fillellipse(200,200,20,20);
	outport(0X60,0XED) ;
	delay(5);
	outport(0X60,2);
	time(0,0);
	move();
      }
	if(!kbhit())
	control = mouse(control);
	else control = arrow(control);


      }
	 return(control);


}
//*************************************************************************
			int reset(int control)
{
  setcolor(0);
  setfillstyle(3,RED);
  fillellipse(200,150,20,20);
  setfillstyle(3,YELLOW);
  fillellipse(200,200,20,20);
  setfillstyle(3,GREEN);
  fillellipse(200,250,20,20);
 while(control==2)
  {
    time(1,0);
    control = mouse(control);
       return (control);
   }
   return (control);
}
//************************************************************************

			     void main()
{

  int control = 1;
  menu();
  tra_lts();
  buttons(1);
   while(1)
    {

     switch(control)
      {
       case 0: mouse_close();  buttons(0); control = avto(0);mouse_close(); buttons(2);break;
       case 1: mouse_close();  buttons(1); control = manual(1);mouse_close(); buttons(2);break;
       case 2: 	  control = reset(2); break;
       case 3: mouse_close();  buttons(3);delay(1000);closegraph();exit(0);
      }
    }

}