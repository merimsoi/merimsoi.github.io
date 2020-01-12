//*****************   LIST OF LIBRARIES    ***********************************
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<stdlib.h>
//*****************   LIST OF FUNCTIONS    ***********************************
void instructions();
void see_mouse();
void close_mouse();
void owner();
void frame();
void cleen(int,int,int,int);
void manual();
void arrows();
void check_mark();
void graph_mode();
void my_clock(long);
void check_mouse();
void reset();
void click_mouse();
void menu(int,int,int,int);
void emp_tr();
void top(int);
void lock(int);
void mid(int);
void bot(int);
void auto_mode();
//*****************   GLOBAL VARIABLES     ***********************************
int midx,midy,xradius,yradius;
int ifmouse,xmouse,ymouse;
int mark=1;
int man,avto,res;
//****************************************************************************