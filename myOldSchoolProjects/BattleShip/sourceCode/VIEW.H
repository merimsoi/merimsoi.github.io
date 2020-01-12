#ifndef _Ship
#define _Ship
#include "master.h"
#include"info.h"
#include <owl\owlpch.h>
#include <ddeml.h>
#include "shipapp.rh"
#define FAST 0.8
#define SLOW 10
class TInfo;
// states of squares in the field of game
enum TSquareState
{
  SqsEmpty,
  SqsEmptySel,
  SqsShip,
  SqsKillShip,
  SqsShipNo,
  SqsCount
};
// kinds of clicks in time of game
enum TMesState
{
  SmesNone=101,
  SmesConnect=102,
  SmesReply=103,
  SmesPlace=104,
  SmesClick=105,
  SmesStop=106,
  SmesExit=107,
  SmesCount
};
// directions of the ships
enum TDir
{
  DirRight,
  DirLeft,
  DirUp,
  DirDown
};
// arrows in the keyboard
enum TDirShip
{
  DirShipRight=39,
  DirShipLeft=37,
  DirShipUp=38,
  DirShipDown=40,
  DirShipNone=0
};

//************************* class TGame ***********************************
class TGame {
  public:
	 static bool  Playing;
	 static bool  Arranging;

	 TGame(TGame* p = 0, int dim=10);

	 void New();
	 void Start();
	 bool IsPlaying() const {return Playing;}
	 bool IsArrange()  const {return Arranging;}
	 TSquareState GetState(int sq) const;
	 void SetState(int sq, TSquareState state);
	 int  GetDimension() const {return Dim;}
	 void SetView(TWindow* view) { View = view; }


  private:
	 int          Dim;
	 TWindow*     View;
	 TSquareState UserSide;

	 int          m_state[100];
	 int          UserBoardMap;
	 int          ComputerBoardMap;
	 bool         ComputerGoesFirst;

	 friend class TGameView;
};
//********************** class TSquare ***********************************

class TSquare : public TButtonGadget
{
  public:
	 TSquare(int id);
	~TSquare(){CelArray = 0;
				  for (int i=0;i<SqsCount;++i)
				  {
				  if (StateCels[i])
					{
					 delete StateCels[i];
					 StateCels[i]=0;
					}
				  }
				 }
	 int       GetGlyph();
	 void      Paint(TDC& dc);
	 void      SetGlyph(int g);
  protected:
	 int       Glyph;
	 void      Activate(TPoint& p);
  private:
	 static TCelArray*  StateCels[SqsCount];
	 friend class TGameView;
};
typedef TSquare* PTSquare;
//*********************** class TGameView *********************************
class TGameView : public TToolBox
{
  public:

	 TGameView(TGame& game,int x,int y);
	~TGameView();

	 void   CmGameNew();
	 void   CmGameStart();
	 BOOL IsShip(int square);
	 void SetState(TPoint &point);
	 void SetGlyph(int square,int gl);
	 int GetSquareFromPoint(TPoint& point);
	 int GetKillShipCount(bool isOppon=false);
	 static const char far* StaticName() {return "TGameView";}
	 BOOL IsPlace(int Square,int Mode,int *squares,TDir Direction=DirRight);

	 bool EvEraseBkgnd( HDC hdc);
	 void EvKeyDown (uint key, uint repeatCount, uint flags);
	 LRESULT   EvCommand(UINT id, HWND hWndCtl, UINT notifyCode);

	 bool m_Drag;
	 bool m_Receive;
	 TInfo* Info;
	 TGame& Game;
	 int ones[4];
	 int two[6];
	 int three[6];
	 int four[4];
	 int live[4];
	 int place[10][10];
	 static int whoPlay;


	private:
	 int       Dim;
	 TSquare** Board;
	 bool      IsEmbedded;
	 TControlBar* ToolBar;
	 char*  ContainerName;
	 void   SetupWindow();
	 void   CmGameOptions();
	 void   CleanupWindow();
	 void EvCommandEnable(TCommandEnabler& ce);
	 void EvRButtonDown (uint modKeys, TPoint& point);
	 void EvLButtonDown (uint modKeys, TPoint& point);
	 void EvLButtonDblClk(uint modKeys, TPoint& point);
	 LRESULT   EvGameViewSync(WPARAM wParam, LPARAM lParam);

  DECLARE_RESPONSE_TABLE(TGameView);
};
//*********************** class TShipView ************************************
class TShipView : public TToolBox
{
  public:
	 TShipView(TWindow *,int Mode,int x,int y);
	~TShipView();
	 int m_count;
	 int m_Mode;// 1 2 3 4
	 int m_CurrentCount;

	private:
	 void CmShip();
	 void      SetupWindow();
	 void      CleanupWindow();


  DECLARE_RESPONSE_TABLE(TShipView);
};
#endif


