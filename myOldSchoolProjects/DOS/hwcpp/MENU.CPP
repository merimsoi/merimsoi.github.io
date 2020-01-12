#include"menu.h"
#include"include.h"
//**************************************************************************
//Constructor Menu
//Parameters:int,int,int,int-->coordinates of window of menu
//***************************************************************************
Menu::Menu(int x1,int y1,int x2,int y2):Window(x1,y1,x2,y2)
{
 position=2;
 color_bar=1;
}
//***************************************************************************
//Destructor Menu
//***************************************************************************
Menu::~Menu()
{
 delete rows;
}
//**************************************************************************
//Function Menu::ShowWindow shows the menu
//Parameters:none
//Return Value:none
//**************************************************************************
void Menu::ShowWindow()
{
 Window::ShowWindow();
 int x=wherex();
 int y=wherey();
 for(int i=0;i<num_row+1;i++)
  {
   if (position==i+1) {
		       textbackground(color_bar);
		       window(x1+1,y1+y,x2-1,y1+y);   //show bar of menu
		       clrscr();
		       window(x1,y1,x2,y2);
		       gotoxy(x+2,y+1);
		       cout<<rows[i-1];               //show row of text
		       y++;
		      }
   else              {
		      if(!i)continue;
		      else
			{
			 gotoxy(x+2,y+1);
			 cout<<rows[i-1];            //show row of text
			 y++;
			}
		      }
  }
 MoveMenu();
}
//**************************************************************************
//Function Menu::Is_Down is chenged the position of bar if pressed arrow down
//Parameters:int ch-->code of pressed key
//Return Value:none
//**************************************************************************
void Menu::Is_Down(int ch)
{
 if(ch==80)
   if(position!=num_row+1)position++;
   else position=2;
}
//**************************************************************************
//Function Menu::Is_Down is chenged the position of bar if pressed arrow up
//Parameters:int ch-->code of pressed key
//Return Value:none
//**************************************************************************
void Menu::Is_Up(int ch)
{
 if(ch==72)
  if(position!=2)position--;
  else position=num_row+1;
}
//**************************************************************************
//Function Menu::GetPosition is returns the positin of bar
//Parameters:none
//Return Value:int-->position of bar
//**************************************************************************
int Menu::GetPosition()
 {
 return position;
 }
//**************************************************************************
//Function Menu::SetColorBar sets color of the bar
//Parameters:int-->color
//Return Value:none
//**************************************************************************
 void Menu::SetColorBar(int color)
 {
 color_bar=color;
 }
//**************************************************************************
//Function Menu::SetNumRows  sets number rows of menu
//Parameters:int-->number of rows
//Return Value:none
//***********************************************************************
void Menu::SetNumRows(int num)
{
 num_row=num;
}
//**************************************************************************
//Function Menu::Set_Rows sets the text of menu
//Parameters:int,char**->number of rows and array of pointers to text
//Return Value:none
//**************************************************************************
void Menu::Set_Rows(int num,char* array[])
{
 for(int i=0;i<num;i++)
  {
  rows[i]=new char[strlen(array[i])+1];
  assert(rows[i]);
  strcpy(rows[i],array[i]);
  }
}
//**************************************************************************
//Function Menu::MoveMenu checks the moving in menu
//Parameters:none
//Return Value:none
//**************************************************************************
void Menu::MoveMenu()
{
 int ch=getch();
 if(ch==27)                 //if Esc
   {
    position=1;
    return;
   }
 if(ch==13) return;        //if Enter
 if(!ch) ch=getch();
 Is_Down(ch);              //if arrow down
 Is_Up(ch);                //if arrow up
 ShowWindow();
}
