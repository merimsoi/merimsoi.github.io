#include"window.h"
#ifndef _Menu
#define _Menu
//**************************************************************************
//Class Menu is inherited from Window.Ability to show menu
//**************************************************************************
class Menu:public Window
{
 public:
  Menu(int,int,int,int);
  ~Menu();
  void Is_Down(int);               //if pressed arrow down?
  void Is_Up(int);                 //if pressed arrow up?
  void ShowWindow();               //function to show menu
  void Set_Rows(int,char**);       //seting text in menu
  void SetNumRows(int);            //set number of rows
  void SetColorBar(int);           //set color of bar
  void MoveMenu();                 //function to moving menu
  int GetPosition();               //function to returning position of bar
 private:
  int position;                     //position the bar in menu
  int color_bar;                    //color the bar of menu
  int num_row;                      //number rows in menu
  char *rows[3];                    //text of menu
};
#endif