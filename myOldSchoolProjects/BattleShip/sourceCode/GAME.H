#if !defined(__shipspac_h)       // Sentry, use file only if it's not already included.
#define __shipspac_h
#include <owl\owlpch.h>
#pragma hdrstop
#include "drag.h"
#include "connect.h"
#include "shipapp.rh"            // Definition of all resources.
#include "view.h"
#define NUM_COLORS  256

//******************** class shipSpace *************************************
class shipSpace : public TWindow
{
 public:
	 shipSpace (TWindow* parent, const char far* title = 0, TModule* module = 0);
	 virtual ~shipSpace ();

	 int WasEnd;
	 int m_ind;
	 long speed;

	 bool m_Connected;
	 TMesState m_EventComm;
	 int ConnectTimer;

	 int cur;
	 static int a,b,c,d;
	 HBRUSH hBrush ;
	 TColor color;
	 TColor aColors[NUM_COLORS];
	 static int new_flag;
    static Pos;
	 int m_pOpt;
	 int pause;
	 int play;
	 int flag1,level1,squ1,ifVert1,current1;
	 int flag,level,squ,ifVert,current;
	 int m_Field;
	 int m_WhoFirst;
	 Drag *pDrag;
	 TTY *m_pTTY;
	 int position;
	 short m_Event;
	 int m_count[4];
	 static int Snd;
	 static int Info;
	 int ShipInField;
	 static int Speed;
	 TGame *m_pMyGame;

	 bool m_ReceiveCom;
	 char m_Block[300];
	 short m_IndexBlock;
	 int places[10][10];
	 int plac[10][10];

	 TBitmap *pMask[4][4];
	 static int Animation;
	 TPoint m_CursorPoint;
	 TBitmap *pImage[4][4];
	 TGame *m_pOpponentGame;
	 TPopupMenu   PopupMenu;
	 TGameView *m_pGameMyView;
	 TShipView * Ship_View[4];
	 TGameView *m_pGameOpponentView;
	 bool m_timer;
	 void Init();
	 bool EvEraseBkgnd( HDC hdc);
	 void WriteText();
	 void Fly(int);
	 void Fly2(int);
	 void CmInfo();
	 void CmExit();
	 void CmMove();
	 void CmKind();
	 void CmBegin();
	 void CmSpeedFast();
	 void CmSpeedSlow();
	 void CmSoundYes();
	 void CmSoundNo();
	 void CmPause();
	 void CmPlay();
	 void CmRemove();
	 void CmConnect();
	 void CmGameNew();
	 void CmKillShip();
	 void CmAnimationYes();
	 void CmAnimationNo();
	 void CmRandomize();
	 void HelpToStart();
	 void CmGameStart();
	 void IDMColors();
	 void SetupWindow();
	 int CheckPlace(int);
	 int CheckPlace2(int);
	 void  CmUnConnect();
	 void ReadCommData();
	 void CmCommonStart();
	 void CmComputStart();
	 void CmStop();
	 int  CheckBound(int);
	 void CorrectData(int);
	 void CmShip(WPARAM id);
	 void HelpCheck(int,int);
	 void HelpCheck2(int,int);
	 int  Next(int&,int,int,int&);
	 int IfNotBound(int,int,int,int);
	 void ExcludeClipRect(TWindow *pView,TDC &dc);
	 void  CmGameFirst();
	void  CmGameSecond();
	void CeGameSecond(TCommandEnabler& ce);
	void FillArrayStatus(int*);
	void CeGameFirst(TCommandEnabler& ce);
	 void CeAnimationYes(TCommandEnabler& ce);
	 void CeSound(TCommandEnabler& ce);
	 void CeMove(TCommandEnabler& ce);
	 void CeDisconnect(TCommandEnabler& ce);
	 void CeKind(TCommandEnabler& ce);
	 void CeGameNew(TCommandEnabler& ce);
	 void CeStop(TCommandEnabler& ce);
	 void InitFlag(int& ,int& ,int& );
	 void CeBegin(TCommandEnabler& ce);
	 LRESULT ToCorrect(WPARAM ,LPARAM );
	 LRESULT ToInfo(WPARAM ,LPARAM );
	 LRESULT End(WPARAM ,LPARAM );
	 BOOL EvSetCursor(HWND, UINT, UINT);
	 void CeRemove(TCommandEnabler& ce);
	 void CePause(TCommandEnabler& ce);
	 void CeSpeedSlow(TCommandEnabler& ce);
	 void CeSpeedFast(TCommandEnabler& ce);
	 void CePlay(TCommandEnabler& ce);
	 int GetShipBegin(int squ,int *dir);
	 void CeConnect(TCommandEnabler& ce);
	 int DeleteShip(int squ,TDirShip dir);
	 void CeGameStart(TCommandEnabler& ce);
	 void CeRandomize(TCommandEnabler& ce);
	 void ChangeImage(TPoint &pnt,int key);
	 void BeginDrag(TPoint& pos,int count);
	 void EvTimer(UINT timerId);
	 LRESULT Comp(WPARAM wp,LPARAM lp);
	 void CompTurn();
	 void CompTurn2();
	 LRESULT CmShipMove(WPARAM wp,LPARAM lp);
	 void EvLButtonDown(UINT , TPoint& point) ;
	 LRESULT ReceivePoint(WPARAM wp,LPARAM lp);
	 LRESULT CmSquareClick(WPARAM wp,LPARAM lp);
	 void EvCommNotify(UINT wParam,UINT  lParam);
	 int WhoNext(int& ,int ,int ,int& ,int& ,int);
	 void EvMouseMove(uint modKeys, TPoint& point) ;
	 void BroadcastBlock(int *Block,TMesState state);
	 void EvKeyDown (uint key, uint repeatCount, uint flags);
	 void ReceiveBlock(TGame* m_pMyGame,TGameView *m_pGameMyView,
							 TGame* m_pOpponentGame,TGameView *m_pGameOpponentView,
							 int *Block,TMesState state);
public:
DECLARE_RESPONSE_TABLE(shipSpace);
 };
#endif
