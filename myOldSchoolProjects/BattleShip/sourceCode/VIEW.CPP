#include <owl/dialog.h>
#include "view.h"
#include"game.h"
#include "shipapp.rh"
#define CM_SELECT 1023
//*********************** class TGame **************************************
 TGame::TGame(TGame*, int dim)
 {
	Playing = false;
	Arranging=true;
	Dim = dim;
	randomize();
	for (int i=0;i<dim*dim;i++) m_state[i]=SqsEmptySel;
 }
//initialization of static members
 bool TGame::Playing=false;
 bool TGame::Arranging=true;
//initialization for new game
 void TGame::New()
 {
  Playing = false;
  Arranging=true;
  for (int i=0;i<Dim*Dim;i++) m_state[i]=SqsEmptySel;
 }
 //initialization for start game
 void TGame::Start()
 {
  Playing = true;
  Arranging=false;
 }
//get state of square in the field of game
 TSquareState TGame::GetState(int sq) const
 {
  return (TSquareState)m_state[sq];
 }
//set state of square in the field of game
 void TGame::SetState(int sq, TSquareState state)
 {
	m_state[sq]=state;
 }
//********************** class TSquare *************************************
TCelArray* TSquare::StateCels[SqsCount]; // entry for each state
static TResId StateResId[SqsCount] =
												{
												 IDB_EMPTY,
												 IDB_EMPTY_SEL,
												 IDB_SHIP ,
												 IDB_KILLSHIP ,
												 IDB_SHIPNO
												};
// constructor
TSquare::TSquare(int id)
: TButtonGadget(IDB_EMPTY, id, NonExclusive, true, Up, false),
  Glyph(0) { }

 void TSquare::SetGlyph(int g)
 {
	Glyph = g;
	SetButtonState(Glyph ? Down : Up);
	Invalidate();
 }

 int TSquare::GetGlyph()
 {
	return  Glyph;
 }
//*************************************************************************
 void TSquare::Paint(TDC& dc)
 {
	// Fool button gadget into making our special state cel arrays
  //
	delete CelArray;   // delete any that might have been created
	for (int i = 0; i < SqsCount; i++)
	 if (!StateCels[i])
	 {
		 ResId = StateResId[i];
		 CelArray = 0;     // leak?
		 BuildCelArray();
		 StateCels[i] = CelArray;
	 }

  // slip in the correct cel array just before painting
  CelArray = StateCels[Glyph];
  TButtonGadget::Paint(dc);
  CelArray = 0;
 }

 void TSquare::Activate(TPoint& pt)
 {
	if (!Glyph)
		{
	  Window->PostMessage(WM_COMMAND, GetId());
	  CancelPressed(pt);
		}
	else CancelPressed(pt);
 }
//********************* class TShipView ************************************
 DEFINE_RESPONSE_TABLE1(TShipView, TToolBox)
 END_RESPONSE_TABLE;

// constructor
 TShipView::TShipView(TWindow *papa,int Mode,int x,int y)
 :TToolBox(papa, 1, AS_MANY_AS_NEEDED, Horizontal)
 {
	Attr.X=x;
	Attr.Y=y;
	m_count=m_CurrentCount=5-Mode;
	m_Mode=Mode;
	Attr.Style|=WS_CHILDWINDOW;
 }
// destructor
TShipView::~TShipView()
 {}
// creating field of game
 void TShipView::SetupWindow()
 {
	TToolBox::SetupWindow();
 }

 void TShipView::CleanupWindow()
 {
	TToolBox::CleanupWindow();
 }
//******************** class TGameView *****************************************
 DEFINE_RESPONSE_TABLE1(TGameView, TToolBox)
  EV_COMMAND(CM_GAMESTART, CmGameStart),

  EV_WM_RBUTTONDOWN,
  EV_WM_LBUTTONDOWN,
  EV_WM_LBUTTONDBLCLK,
  END_RESPONSE_TABLE;

  //initialization of static members
  int TGameView::whoPlay=1;
  // constructor
TGameView::TGameView(TGame& game,int x,int y)
			 :Game(game),
			  TToolBox(0,game.GetDimension(), AS_MANY_AS_NEEDED, Horizontal)

{
  Attr.X=x;
  Attr.Y=y;
  m_Receive=FALSE;
  Dim = Game.GetDimension();
  Board = new PTSquare[Dim*Dim];
  ToolBar = 0;
  ContainerName = new char[255];
  IsEmbedded = false;
  m_Drag=false;
	for (int i = 0; i < Dim; i++)
	 for (int j = 0; j < Dim; j++) {
		TSquare* sq = new TSquare(CM_SQUARE + i*Dim + j);
		Board[i*Dim + j] = sq;
		Insert(*sq);
	 }
	 for(i=0;i<10;i++)
	  for(int j=0;j<10;j++)
		place[i][j]=0;
	for(i=0;i<4;i++) live[i]=0;
	Game.SetView(this);

  }
//destructor
 TGameView::~TGameView()
 {
	delete [] Board;
	delete [] ContainerName;
 }

 void TGameView::SetupWindow()
 {
	TWindow::SetupWindow();
	SetFocus();
 }

 void TGameView::CleanupWindow()
 {
	TToolBox::CleanupWindow();
 }

// Get number of square according from point of the screen
 int TGameView::GetSquareFromPoint(TPoint& point)
 {
  TGadget* gd=GadgetFromPoint( point);
  if (gd)
  {
	 TGadget* gd1=FirstGadget();
	 for (int i=0;i<100;i++)
	 {
		if (gd1==gd)
			return i;
		gd1=NextGadget(*gd1);
	 }
	 return -1;
  }
  else
	return -1;
 }

// Check if possible to set ship in the field begining from square
 BOOL TGameView::IsPlace(int square,int Mode,int *squares,TDir Direction)
 {
  int ids[24];
  TSquareState st=Game.GetState(square);
	if (st==SqsShip)
		return false;

	for (int i=0;i<24;i++) ids[i]=-1;
	int w,h;
	int coefX=1;
	int coefY=1;
	if (Direction==DirRight ||Direction==DirLeft)
	 {
	  w=Mode+2;
	  h=3;
	  if (Direction==DirLeft)
			coefX=-1;
	 }
	else
	 {
	  h=Mode+2;
	  w=3;
	  if (Direction==DirUp)
	  coefY=-1;
	 }
  int x=square%Dim;
  int y=square/Dim;
  if (x+(w-3)*coefX<0 || x+(w-3)*coefX>Dim-1||
		y+(h-3)*coefY<0 || y+(h-3)*coefY>Dim-1)
		return false;
  for (i=0;i<h;i++)
	for (int k=0;k<w;k++)
	 if (!(y-coefY+coefY*i<0 || y-coefY+coefY*i>Dim-1 ||
			 x-coefX+ coefX*k<0 || x-coefX+ coefX*k>Dim-1))
	  ids[i*w+k]=(y-coefY+coefY*i)*Dim+(x-coefX+ coefX*k);
  for (i=0;i<w*h;i++)
	  if (ids[i]!=-1)
		 if (Game.GetState(ids[i])==SqsShip)
		  return false;
  for (i=0;i<Mode;i++)
	if (Direction==DirRight ||Direction==DirLeft)
		*(squares+i)=ids[w+i+1];
	else
		*(squares+i)=ids[w*(i+1)+1];
 return true;
 }
//checks if state of square is ship
 BOOL TGameView::IsShip(int square)
  {
	 TSquareState st=Game.GetState(square);
	 if (st==SqsShip)
		 return true;
	 return false;
  }

 void TGameView::EvLButtonDblClk(uint, TPoint&)
 {
	return;
 }
 void TGameView::EvRButtonDown (uint , TPoint& point)
 {
 TPoint p=point;
 ClientToScreen(point);
 if(point.x>65&&point.x<305&&point.y>98&&point.y<337&& TGame::Playing)return;
 else point=p;

  int squ=GetSquareFromPoint(point);
  if (!TGame::Playing)
	{
	 if (!IsShip(squ)) return;
	 TPoint pnt=point;
	 MapWindowPoints( Parent->HWindow, &pnt, 1);
	 LPARAM  lParam;
	 UINT *pp;
	 pp=(UINT*)&lParam;
	 *pp=pnt.x;
	 *(pp+1)=pnt.y;
	 Parent->SendMessage(WM_USER+2,0,lParam);
	 TPopupMenu* popup=new TPopupMenu();
	 popup->AppendMenu(MF_BYCOMMAND|MF_ENABLED, CM_MOVE,"Move");
	 popup->AppendMenu(MF_SEPARATOR, 0, 0);
	 popup->AppendMenu(MF_BYCOMMAND|MF_ENABLED, CM_REMOVE,"Remove");
	 ClientToScreen(point);
	 popup->TrackPopupMenu(TPM_LEFTALIGN,point,0,*Parent);
	 delete popup;
	 }
	else {
			 if(whoPlay==2) return;
			 if(place[squ/10][squ%10]==0)
			  {
				if(IsShip(squ))place[squ/10][squ%10]=4;
				else place[squ/10][squ%10]=3;
				Game.SetState(squ,SqsShipNo);
				Board[squ]->SetGlyph(SqsShipNo);
			  }
			  else if(place[squ/10][squ%10]==3)
					{
					 Game.SetState(squ,SqsEmptySel);
					 Board[squ]->SetGlyph(SqsEmpty);
					 place[squ/10][squ%10]=0;
					}
					else if(place[squ/10][squ%10]==4)
						  {
						  Game.SetState(squ,SqsShip);
						  Board[squ]->SetGlyph(SqsEmpty);
						  place[squ/10][squ%10]=0;
						  }

		  }
  }

 void TGameView::EvLButtonDown (uint u, TPoint& point)
 {
 if(TGameView::whoPlay==2) return;
 TPoint p=point;
 ClientToScreen(point);
 if(point.x>65&&point.x<305&&point.y>98&&point.y<337)return;
 else point=p;

// TToolBox::EvLButtonDown (u , point);
 if(!TGame::Playing) return;

 if(whoPlay!=1)
 {
  TToolBox::EvLButtonDown (u , point);

 return;
 }

 if(!shipSpace::Animation )
 {
  int event=Drag::m_event;
	if (event!=-1)
 {
	if (event==WM_QUIT)
	 ::PostQuitMessage(0);
	else
	GetApplication()->GetMainWindow()->PostMessage(WM_COMMAND,-event,0);
 }
 TBitmap* pImage=new TBitmap(GetApplication()->GetInstance(), IDB_IMGCORE);
 TBitmap* pMask=new TBitmap(GetApplication()->GetInstance(), IDB_MSCORE);
 Drag *pd=new Drag(Parent->HWindow,pImage,pMask);
 if(!shipSpace::Speed) pd->SetAnimationSpeed(SLOW);
 else pd->SetAnimationSpeed(FAST);
 TPoint point1=point;
 MapWindowPoints( Parent->HWindow, &point1, 1);
 pd->Animation(TPoint(75,275),point1);

 delete pImage;
 delete pMask;
 delete pd;
 }
  int squ=GetSquareFromPoint(point);
  int i=squ/10;
  int j=squ%10;
  if (place[i][j]!=0) return;
	 if (IsShip(squ))
	  {
		place[i][j]=1;
		Game.SetState(squ,SqsKillShip);
		if(!shipSpace::Snd)
		sndPlaySound("charge.wav",SND_ASYNC);
		int event=Drag::m_event;
		if (event!=-1)
		{
		if (event==WM_QUIT)
		::PostQuitMessage(0);
		else
		GetApplication()->GetMainWindow()->PostMessage(WM_COMMAND,-event,0);
		}
		Board[squ]->SetGlyph(SqsKillShip);
		Parent->PostMessage(WM_USER+5,0,0);
		if (GetKillShipCount()==20) Parent->PostMessage(WM_USER+4,0,0);
	  }
	 else
	  {
		if (Game.GetState(squ)==SqsEmpty ||Game.GetState(squ)==SqsEmptySel)
		 {
		if(!shipSpace::Snd)
		sndPlaySound("click5.wav",SND_ASYNC);
		Game.SetState(squ,SqsEmptySel);
		Board[squ]->SetGlyph(SqsEmptySel);
		Parent->PostMessage(WM_USER+3,0,0);
		place[i][j]=2;
		 }
	  }
 }

 int TGameView::GetKillShipCount(bool )
 {
  int count=0;
  for (int i = 0; i < Dim*Dim; i++)
		if (Board[i]->GetGlyph()==SqsKillShip)
			count++;
  return count;
 }

 LRESULT TGameView::EvCommand(UINT id, HWND hWndCtl, UINT notifyCode)
 {

  if (id >= CM_SQUARE
		&& id < CM_SQUARE+Game.GetDimension()*Game.GetDimension()
		&& !hWndCtl) {

	 int square = id - CM_SQUARE;
  if(TGame::Playing)
	 {
		int k=Game.GetState(square);
		if(k==SqsShip)
					k=SqsKillShip;
  if(!shipSpace::Animation && whoPlay==0 && !m_Receive )
  {
	int event=Drag::m_event;
	  if (event!=-1)
	 {
		if (event==WM_QUIT)
		::PostQuitMessage(0);
		else
		GetApplication()->GetMainWindow()->PostMessage(WM_COMMAND,-event,0);
	}
  TPoint point;
  point.x=square%10*25+340;
  point.y=square/10*25+35;
  TBitmap* pImage=new TBitmap(GetApplication()->GetInstance(), IDB_IMGCORE);
  TBitmap* pMask=new TBitmap(GetApplication()->GetInstance(), IDB_MSCORE);
  Drag *pd=new Drag(Parent->HWindow,pImage,pMask);
  if(!shipSpace::Speed) pd->SetAnimationSpeed(SLOW);
  else pd->SetAnimationSpeed(FAST);
  pd->Animation(TPoint(75,275),point);

  delete pImage;
  delete pMask;
  delete pd;
 }

		 Board[square]->SetGlyph(k);

	if(!shipSpace::Snd && k==SqsKillShip)
		{
		sndPlaySound("charge.wav",SND_ASYNC);

		}
	 else if(!shipSpace::Snd) sndPlaySound("click5.wav",SND_ASYNC);
		 shipSpace::Pos=square;
		 Parent->PostMessage(WM_USER,(WPARAM)square,(LPARAM)this);

	 }
	 else
	 {
	  if (m_Drag)
	  {
		Game.SetState(square,SqsShip);
		Board[square]->SetGlyph(SqsShip);
	  }
	 }
		return 0;
  }
  return TToolBox::EvCommand(id, hWndCtl, notifyCode);
 }

 void TGameView::SetState(TPoint &point)
 {
  int square=GetSquareFromPoint( point);
  Game.SetState(square,SqsShip);
  Board[square]->SetGlyph(SqsShip);
 }

 void TGameView::SetGlyph(int square,int gl)
 {
  Board[square]->SetGlyph(gl);
 }

 void TGameView::EvCommandEnable(TCommandEnabler& ce)
 {
  if (ce.Id >= CM_SQUARE
		&& ce.Id < CM_SQUARE+Game.GetDimension()*Game.GetDimension()) {
	 ce.Enable(TGame::Playing||TGame::IsArrange);
  }
  else
	 TToolBox::EvCommandEnable(ce);
 }


 void TGameView::CmGameNew()
 {
  Game.New();
  for (int i = 0; i < Dim*Dim; i++)
		Board[i]->SetGlyph(0);
 }

 void TGameView::CmGameStart()
 {
  Game.Start();
  for (int i = 0; i < Dim*Dim; i++)
		Board[i]->SetGlyph(0);
 }


