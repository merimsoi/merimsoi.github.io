#ifndef _HW2
#define _HW2
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#define INTR 0X1C    /* The clock tick interrupt */
#ifdef __cplusplus
    #define __CPPARGS ...
#else
    #define __CPPARGS
#endif
#define TIME_TO_YELLOW 18
//**************** define functions *************************************
void DrawFrame(int,int,int,int);
void Road(void);
void Loop(void);
void Init(void);
void Check(void);
void Clear(void);
void Road_car(void);
float Count_tick(int);
void Change_leds(int);
void Check_input(int);
void Whitch_menu(int);
void Pr_Semaphor(void);
void Where_enter(void);
void Change_light(void);
int Time_of_semaphor(int);
void Semaphor(int,int,int);
void Change_color(int,int);
void Change_frequency(void);
void Change_count_cars(void);
void Change_system_priority(void);
void Create(int,int,int,int,int,int,int,int);
//********************* definition variable  ********************************
extern int ch;
extern int count;                         //counter of ticks
extern float priority[3];                 //array of priority of semaphor
extern float count_cars[3];               //array of count cars
extern int frequency;                     //frequency of system
extern int active;                        //flag,which semaphor is active
extern int num_menu;                      //flag,which menu is active
extern int bar_menu;                      //flag of position in menu
extern int time1,time2,time3;             //count of puls,to every semaphor
extern int input1,input2,input3,input4;   //flags of input
extern int buffer;                        //var. to help in input
extern int change_menu;                   //flag,which say if was change of menu
extern int error;                         //flag of error in input
extern int light_activity;       	  //flag,whith light of keyboard is active
extern int led1,led2,led3;                //flag of color to every semaphor
extern int change_led;                    //flag,which say if was change of leds
extern int change_color;                  //flag,which say if was change color
extern float ticks_in_puls;               //default count ticks in puls
extern int twocolor;                      //flag,which say that semaphor have red and yellow
extern char menu[4][26];                  //arrays of menus
extern char menu2[3][13];
extern char menu3[3][20];
extern char menu4[3][14];
#endif