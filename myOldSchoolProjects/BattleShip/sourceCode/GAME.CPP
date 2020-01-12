#include <owl\owlpch.h>
#pragma hdrstop
#include "shipapp.h"
#include "game.h"
#include "dialogs.h"
#include "info.h"
#include <stdio.h>
#define CM_SELECT 1023
//*************** class shipSpace ****************************************
 DEFINE_RESPONSE_TABLE1(shipSpace, TWindow)
 EV_COMMAND_AND_ID(IDB_SHIP1, CmShip),
 EV_COMMAND_AND_ID(IDB_SHIP2, CmShip),
 EV_COMMAND_AND_ID(IDB_SHIP3, CmShip),
 EV_COMMAND_AND_ID(IDB_SHIP4, CmShip),
 EV_COMMAND(CM_MOVE,CmMove),
 EV_COMMAND(CM_EXIT,CmExit),
 EV_COMMAND(CM_KIND,CmKind),
 EV_COMMAND(CM_INFO, CmInfo),
 EV_COMMAND(CM_SPEEDFAST,CmSpeedFast),
 EV_COMMAND(CM_SOUNDYES,CmSoundYes),
 EV_COMMAND(CM_REMOVE,CmRemove),
 EV_COMMAND(CM_CONNECT,CmConnect),
 EV_COMMAND(CM_GAMENEW, CmGameNew),
 EV_COMMAND(CM_ANIMATIONYES,CmAnimationYes),
 EV_COMMAND_ENABLE(CM_ANIMATIONYES,CeAnimationYes),
 EV_COMMAND(CM_RANDOMIZE,CmRandomize),
 EV_COMMAND(IDM_DISCONNECT,CmUnConnect),
 EV_COMMAND(CM_GAMESTART, CmCommonStart),
 EV_COMMAND(CM_STOP, CmStop),
 EV_COMMAND(BT_FIRST, CmGameFirst),
 EV_COMMAND_ENABLE(BT_FIRST, CeGameFirst),
 EV_COMMAND(BT_SECOND, CmGameSecond),
 EV_COMMAND_ENABLE(BT_SECOND, CeGameSecond),
 EV_COMMAND_ENABLE(CM_KIND, CeKind),
 EV_COMMAND_ENABLE(CM_MOVE, CeMove),
 EV_COMMAND_ENABLE(CM_STOP, CeStop),
 EV_COMMAND_ENABLE(CM_GAMENEW, CeGameNew),
 EV_COMMAND_ENABLE(IDM_DISCONNECT,CeDisconnect),
 EV_COMMAND_ENABLE(CM_REMOVE, CeRemove),
 EV_COMMAND_ENABLE(CM_CONNECT, CeConnect),
 EV_COMMAND_ENABLE(CM_SOUNDYES, CeSound),
 EV_COMMAND_ENABLE(CM_SPEEDFAST, CeSpeedFast),
 EV_COMMAND_ENABLE(CM_RANDOMIZE,CeRandomize),
 EV_COMMAND_ENABLE(CM_GAMESTART, CeGameStart),
 EV_MESSAGE (WM_USER,CmSquareClick),
 EV_MESSAGE (WM_USER+1,CmShipMove),
 EV_MESSAGE (WM_USER+2,ReceivePoint),
 EV_MESSAGE (WM_USER+3,Comp),
 EV_MESSAGE (WM_USER+4,End),
 EV_MESSAGE (WM_USER+5,ToCorrect),
 EV_WM_ERASEBKGND,
 EV_WM_MOUSEMOVE,
 EV_WM_LBUTTONDOWN,
 EV_WM_KEYDOWN,
 EV_WM_TIMER,
 EV_WM_SETCURSOR,
 EV_WM_COMMNOTIFY,
 END_RESPONSE_TABLE;
//constructor
 shipSpace::shipSpace (TWindow* parent, const char far* title, TModule* module)
		: TWindow(parent, title, module)
 {
		m_WhoFirst=0;
		WasEnd=0;
		m_Connected=false;
		m_EventComm=SmesNone;
		ConnectTimer=0;

		m_pMyGame=new TGame();
		m_pGameMyView=new TGameView(*m_pMyGame,65,20);
		m_pGameMyView->Info=new TInfo(this,-1,"In 1 field:" ,92,264,200,80);
		m_pOpt=1;
		pause=0;
		play=0;
		cur=1;
		color=TColor(0,0,0);
		for(int i=0;i<NUM_COLORS;i++)
		aColors[i]=TColor(255,255,255);

		m_pOpponentGame=new TGame();
		m_pGameOpponentView=new TGameView(*m_pOpponentGame,30,10);
		m_pGameOpponentView->Info=new TInfo(this,-2,"In 2 field:" ,340,264,200,80);
		int row=65,col=385;
		for( i=0;i<4;i++)
		{
		 Ship_View[i]=new TShipView(this,i+1,col,row);
		 Ship_View[i]->Insert(*new TButtonGadget(IDB_SHIP1+i,IDB_SHIP1+i,
		 TButtonGadget::Command,true));
		 Ship_View[i]->EnableWindow(TRUE);
		 row+=30;
		 col-=10;
		}
	  for (i=0;i<4;i++)
	  for(int j=0;j<4;j++)
	  {
		if(!j)
		{
		 pImage[i][j]=new TBitmap(GetApplication()->GetInstance(), IDB_IMAGE1);
		 pMask[i][j]=new TBitmap(GetApplication()->GetInstance(), IDB_MASK1);
		}
		else
		{
		 pImage[i][j]=new TBitmap(GetApplication()->GetInstance(), IDB_IMAGE1+3*i+j);
		 pMask[i][j]=new TBitmap(GetApplication()->GetInstance(), IDB_MASK1+3*i+j);
		}
	  m_count[i]=4-i;
	  }
		ShipInField=0;
		pDrag=NULL;
		m_pTTY=NULL;
		for(i=0;i<10;i++)
		for(int j=0;j<10;j++) places[i][j]=0;
 }
//initialization of static members of class shipSpace
 int shipSpace::Animation=0;
 int shipSpace::Speed=1;
 int shipSpace::Snd=0;
 int shipSpace::Info=0;
 int shipSpace::new_flag=1;
 int shipSpace::a=0;
 int shipSpace::b=0;
 int shipSpace::c=0;
 int shipSpace::d=0;
 int shipSpace::Pos=0;
//involved when choosed option of toolbar STOP
 void shipSpace::CmStop()
 {
  if(WasEnd) return;
  WasEnd=1;
  if(m_timer)KillTimer(1);
  m_timer=FALSE;
  new_flag=0;
  m_pGameMyView->EnableWindow(true);
  m_pGameOpponentView->EnableWindow(false);
  MessageBox("Game was stoped!","Game Over",MB_ICONHAND| MB_OK);
  Drag:: m_event=-1;
  if(!m_pOpt && TGame::Playing)
  {
	int nums=SmesStop;
	if (m_pTTY)
	 m_pTTY->WriteCommBlock(  (LPSTR)&nums,sizeof(nums));
  }
  TGame::Playing=false;
  if(m_pOpt==2)
  {
  GetApplication()->GetMainWindow()->RestoreMenu();
  }
 }

// involved when choosed option of right button REMOVE
 void shipSpace::CmRemove()
 {
	 if (!pDrag)
	  {
	  PostMessage(WM_USER+1,37,1);
	  }
	 return;
 }

// involved when choosed option of toolbar EXIT
 void shipSpace::CmExit()
  {
	if(TGame::Playing &&!m_pOpt)
	 {
	  int nums=SmesExit;
	  if (m_pTTY)
	  m_pTTY->WriteCommBlock(  (LPSTR)&nums,sizeof(nums));
	 }
	PostQuitMessage(0);
 }

// involved when choosed option of right button MOVE
 void shipSpace::CmMove()
 {
	if (!pDrag)
	  {
		PostMessage(WM_USER+1,37,0);
	  }
	return;
 }

// involved when choosed option of toolbar OPTIONS FOR GAME
void shipSpace::CmKind()
 {
	TOptionDialog(this,&m_pOpt).Execute();
	UpdateWindow();
 }

// involved when choosed option of menu INFORMATION
 void shipSpace::CmInfo()
 {
	if (TInfoDialog(this,&Info).Execute()==IDOK)
	 {
	  switch(Info)
	  {
	  case 0:
				 m_pGameMyView->Info->Show(SW_SHOW);
				 if(TGame::Playing||new_flag==0) m_pGameOpponentView->Info->Show(SW_SHOW);
				 break;
	  case 1:
				 m_pGameMyView->Info->Show(SW_HIDE);
				 m_pGameOpponentView->Info->Show(SW_HIDE);
				 break;
	 }
	  m_pGameMyView->Info->Invalidate();
	  if(TGame::Playing) m_pGameOpponentView->Info->Invalidate();
  }
 }
// involved when choosed option of toolbar FAST
void shipSpace::CmSpeedFast()
 {
	Speed=!Speed;
 }

// involved when choosed option of toolbar Yes Animation
 void shipSpace::CmAnimationYes()
 {
  Animation=!Animation;
  HMENU hMenu;
  hMenu=GetApplication()->GetMainWindow() ->GetMenu();
  CheckMenuItem(hMenu, CM_ANIMATIONYES, MF_CHECKED);
  CheckMenuItem(hMenu, CM_ANIMATIONNO, MF_UNCHECKED);
 }

// involved when choosed option of toolbar Yes Sound
 void shipSpace::CmSoundYes()
 {
  Snd=!Snd;
 }

// involved when choosed option of toolbar RANDOMIZE
 void shipSpace::CmRandomize()
 {
  int squares[4];
  TDir dir;
  int squ;
  ShipInField=0;
  cur=0;
  for(int p=0;p<4;p++)
  {
  Ship_View[p]->ShowWindow(SW_HIDE);
  TRect rect(345,55,448,195);
  InvalidateRect(rect,FALSE);
 }

 randomize();
 m_pGameMyView->CmGameNew();
 for(int i=3;i>=0;i--)
 {
	m_ind=i+1;
	int k=0;
	 for(int j=0;j<4-i;j++)
	  {
	  squ=random(100);
	  dir=(TDir)random(4);
	  if (!(m_pGameMyView->IsPlace(squ,m_ind,squares,dir)))
		 {j--;
		  continue;
		 }
	m_pGameMyView->m_Drag=true;
	for (int i=0;i<m_ind;i++)
	{
	m_pGameMyView->EvCommand(squares[i]+CM_SQUARE,0,0);
	switch (m_ind)
	 {
	  case 1:m_pGameMyView->ones[k++]=squares[i];break;
	  case 2:m_pGameMyView->two[k++]=squares[i];break;
	  case 3:m_pGameMyView->three[k++]=squares[i];break;
	  case 4:m_pGameMyView->four[k++]=squares[i];break;
	  }
	}

	ShipInField++;
	m_pGameMyView->m_Drag=false;
 }
 }
 CorrectData(0);
 //
/* int k=0;
 int nums[20];
 for (i=0;i<100;i++)
			 if (m_pMyGame->GetState(i)==SqsShip)
			 {
				nums[k]=i;
				k++;
			 }

 FillArrayStatus(nums);*/
 }
// involved when choosed option of toolbar New Game
 void  shipSpace::CmGameNew()
 {
  ShipInField=0;
  m_WhoFirst=0;
  WasEnd=0;
  m_EventComm=SmesNone;
  cur=1;
  m_pGameMyView->CmGameNew();
  m_pGameOpponentView->CmGameNew();
  m_Event=0;
  Drag::m_event=-1;
  for (int i=0;i<4;i++)
		{
		m_count[i]=4-i;
		Ship_View[i]->ShowWindow(SW_SHOW);
		m_pGameMyView->Info->live[i]=0;
		m_pGameOpponentView->Info->live[i]=0;
		}
  m_pGameOpponentView->ShowWindow(SW_HIDE);
  m_pGameOpponentView->Info->Show(SW_HIDE);
  m_ReceiveCom=false;
  WriteText();
  m_pGameMyView->Info->Invalidate();
  new_flag=1;
  if (m_pTTY && m_pTTY->IsConnected())
  if (!ConnectTimer)
				ConnectTimer=SetTimer(2,100);
 }

// involved when choosed option of toolbar CONNECT
 void  shipSpace::CmConnect()
 {
  TOptionConnectDialog* PNew;
			  PNew = new TOptionConnectDialog(this,&(m_pTTY->npTTYInfo));
	  if (  PNew-> Execute()==IDOK)
			 {
				m_pTTY->OpenConnection( );
				if (!ConnectTimer)
				ConnectTimer=SetTimer(2,100);
				m_EventComm=SmesNone;
			 }
			  delete PNew;
 }

// involved when choosed option of menu DISCONNECT
 void  shipSpace::CmUnConnect()
 {
  m_pTTY->CloseConnection();
 }

//check kind of game
 void shipSpace::CmCommonStart()
 {

  switch (m_pOpt)
  {
	case 0:
			CmGameStart();
		  break;
	case 1:
			CmBegin();
		  break;
	case 2:
		  CmComputStart();
		  break;
  }
	WriteText();
 }
// invalidate text near the field of game
 void shipSpace::WriteText()
 {
  TRect Rect1(330,3,580,20);
  TRect Rect2(580,20,600,300);
  TRect Rect3(550,270,600,320);
  InvalidateRect(Rect1);
  InvalidateRect(Rect2);
  InvalidateRect(Rect3);
  return;
 }

// start for game"Computer with computer"
 void shipSpace::CmComputStart()
 {
  Init();
  CmGameNew();
  CmRandomize();
  GetApplication()->GetMainWindow()->SetMenu(0);
  HelpToStart();
  Invalidate(false);
  m_pOpponentGame->Start();
  flag1=0;level1=0;squ1=0;ifVert1=0;current1=0;
  flag=0;level=0;squ=0;ifVert=0;current=0;
  m_Field=1;
  m_timer=TRUE;
  SetTimer(1,750);
 }

//start for game "Player with computer"
 void shipSpace::CmBegin()
 {
 Init();
 m_pGameOpponentView->EnableWindow(true);
 if(ShipInField!=10)
  {
	MessageBox("You haven't enought ships!","Error",MB_ICONEXCLAMATION| MB_OK);
  return;
  }
 randomize();
 HelpToStart();
 m_timer=TRUE;
 flag=0;level=0;squ=0;ifVert=0;current=0;
 m_Field=1;
 SetTimer(1,750);
 }

//enabler for option REMOVE
 void shipSpace::CeRemove(TCommandEnabler& tce)
 {
  tce.Enable(TRUE);
 }
//enabler for option RANDOMIZE
 void shipSpace::CeRandomize(TCommandEnabler& tce)
 {
	if(TGame::Playing)tce.Enable(FALSE);
	if(!new_flag) tce.Enable(false);
 }

//enabler for option NEW GAME
 void shipSpace::CeGameNew(TCommandEnabler& tce)
 {
 if(TGame::Playing)tce.Enable(FALSE);
 }

//enabler for option OPTIONS FOR GAME
 void shipSpace::CeKind(TCommandEnabler& tce)
 {
	 if(TGame::Playing)tce.Enable(FALSE);
 }

//enabler for option SPEED
 void shipSpace::CeSpeedFast(TCommandEnabler& tce)
 {
  if(Animation)
  {
  tce.Enable(FALSE);
  return;
  }
	 if (Speed)
	 {
		tce.SetCheck(0);
		tce.SetText("Slow");
	 }
	 else
	 {
		tce.SetCheck(1);
		tce.SetText("Fast");
	 }
 }


 void shipSpace::CeBegin(TCommandEnabler& tce)
 {
  if(TGame::Playing)tce.Enable(FALSE);
 }

//enabler for option MOVE
 void shipSpace::CeMove(TCommandEnabler& tce)
 {
  tce.Enable(TRUE);
 }

//enabler for option CONNECT
 void shipSpace::CeConnect(TCommandEnabler& ce)
 {
  if(TGame::Playing||m_pOpt!=0|| m_pTTY->IsConnected())ce.Enable(FALSE);
  else
	ce.Enable(TRUE);
 }

//enabler for option ANIMATION
 void shipSpace::CeAnimationYes(TCommandEnabler& ce)
 {
	 if (Animation)
	 {
		ce.SetCheck(1);
		ce.SetText("With Animation");
	 }
	 else
	 {
		ce.SetCheck(0);
		ce.SetText("Without Animation");
	 }
 }

//enabler for option SOUND
 void shipSpace::CeSound(TCommandEnabler& ce)
 {
	 if (Snd)
	 {
		ce.SetCheck(1);
		ce.SetText("With Sound");
	 }
	 else
	 {
		ce.SetCheck(0);
		ce.SetText("Without Sound");
	 }
 }

//enabler for option DISCONNECT
 void shipSpace::CeDisconnect(TCommandEnabler& ce)
 {
  ce.Enable(m_pTTY->IsConnected());
 }

//enabler for option STOP
 void shipSpace::CeStop(TCommandEnabler& ce)
 {
  if(!TGame::Playing)ce.Enable(FALSE);
 }
//enabler for option START
 void shipSpace::CeGameStart(TCommandEnabler& ce)
 {
  bool enable;
  switch(TGame::Playing)
  {

  case FALSE:
				 if (!m_pOpt)
				{
				 enable=(ShipInField==10 && m_pTTY->IsConnected() && m_WhoFirst
							&& m_Connected);
				}
				else
				 if (m_pOpt==1)
				  {
					if(TGame::Playing) enable=(FALSE);
				  }
				 else
					enable=true;
				break;
  case TRUE:enable=false;
 }
 if(!new_flag) enable=false;
 ce.Enable(enable);
 }
// initialization of variables
 void shipSpace::Init()
 {

  for(int i=0;i<10;i++)
	 for(int j=0;j<10;j++)
							{
							places[i][j]=0;
							m_pGameOpponentView->place[i][j]=0;
							}
 }

 LRESULT shipSpace::Comp(WPARAM ,LPARAM )
 {
 m_Field=1;
 CompTurn();
 return 0;
 }

// involved in time of event WM_TIMER
 void shipSpace::EvTimer(UINT timerId)
 {
 if (timerId==1)
  switch(m_pOpt)
  {
  case 1:if (m_Field==2)CompTurn();
			break;
  case 2:
			if(m_Field==1) CompTurn2();
			else
			  if (m_Field==2)CompTurn();
			break;
  }

 if (timerId==2)
 {
		if (m_pTTY && m_pTTY->IsConnected())
		{
		TMesState ev=SmesConnect;
		m_pTTY->WriteCommBlock(  (LPSTR)&ev,sizeof(short));
		}
 }
 }

 void shipSpace::CompTurn()
 {
 m_Field=0;
 int num=1,ch;

 randomize();
 while(1)
 {
  if(!flag)
			  {
				squ=random(100);        //if before was ship
				current=squ;
			  }   //if-then
  ch=squ;
  num=CheckPlace(squ);
		if(num==3)                    // if plays two computers and empty sell
					 {
					  m_Field=1;
					  return ;
					 }
		if(num==0)                          //if empty  sell
		  {
		  if(flag==0)
						  {
							m_Field=1;
							return ;           //if checked all near killed ship

							}
		  else
				 {
				  if(ifVert>=2&&level>1)     //if ship vertical
							 {
							 InitFlag(flag,level,ifVert);
							 m_Field=1;
							 return ;
							 }//if (ifVert>=2)
				  level++;
				  squ=current;
				  if(level>3)
							 {
							  InitFlag(flag,level,ifVert);
							  m_Field=1;
							  return ;
							 }
				  squ=WhoNext(level,squ,ch,flag,ifVert,current);
				  m_Field=1;
				  return ;
				 } //else(flag!=0)
			}  //if (num==0)
		else if(num==1)          //if choosed killed ship or selected empty
				{
				 m_Field=2;
				 if(flag==0)
								  {
											int event=Drag::m_event;
											if (event!=-1)
											{
											if (event==WM_QUIT)
											::PostQuitMessage(0);
											else
											GetApplication()->GetMainWindow()->PostMessage(WM_COMMAND,-event,0);
											 }

									  continue;
								  }
				 else
				  {
				  if(ifVert>=2&&level>1)     //if ship vertical
					 {
					 InitFlag(flag,level,ifVert);
					 return;
					 }//if (ifVert>=2)

				  level++;
				  squ=current;
				  if(level>3)
							 {
							 InitFlag(flag,level,ifVert);
							 return ;
							 }
				  squ=WhoNext(level,squ,ch,flag,ifVert,current);
				  if(squ==-1) return ;
				  }
				}//if(num==1)
				else if(num==2)
					  {
						m_Field=2;
						if(flag==0)flag=1;
						if(level==0||level==1)ifVert++;
						squ=WhoNext(level,squ,ch,flag,ifVert,current);
						if(squ==-1) return ;
					  }//if(num==2)
  }//while
 }

 void shipSpace::CompTurn2()
 {
 int num1=1,ch1;
 m_Field=0;
 randomize();
 while(1)
 {
  if(!flag1)
			  {
				squ1=random(100);             //if before was ship
				current1=squ1;
			  }   //if-then
  ch1=squ1;
  num1=CheckPlace2(squ1);
		if(num1==3)
				  {
					m_Field=2;
					return ;
				  }

		if(num1==0)                        //if empty  sell
		  {
		  if(flag1==0)
		  {
		  m_Field=2;
		  return ;                       //if checked all near killed ship
		  }
		  else
				 {
				  if(ifVert1>=2&&level1>1)  //if ship vertical
							 {
							 InitFlag(flag1,level1,ifVert1);
							 m_Field=2;
							 return ;
							 }//if (ifVert>=2)
				  level1++;
				  squ1=current1;
				  if(level1>3)
							 {
							  InitFlag(flag1,level1,ifVert1);
							  m_Field=2;
							  return;
							 }
				  squ1=WhoNext(level1,squ1,ch1,flag1,ifVert1,current1);
				  m_Field=2;
				  return ;
				 } //else(flag!=0)
			}  //if (num==0)
		else if(num1==1)                 //if choosed killed ship or selected empty
				{
				 m_Field=1;
				 if(flag1==0) {
										int event=Drag::m_event;
										if (event!=-1)
										{
										if (event==WM_QUIT)
										::PostQuitMessage(0);
										else
										GetApplication()->GetMainWindow()->PostMessage(WM_COMMAND,-event,0);
										  }

								 continue;
								 }
				 else
				  {
					if(ifVert1>=2&&level1>1)     //if ship vertical
							 {
							 InitFlag(flag1,level1,ifVert1);
							 return ;
							 }//if (ifVert>=2)
				  level1++;
				  squ1=current1;
				  if(level1>3)
							 {
							 InitFlag(flag1,level1,ifVert1);
							 return ;
							 }

				  squ1=WhoNext(level1,squ1,ch1,flag1,ifVert1,current1);
				  if(squ1==-1) return ;
				  }
				}//if(num==1)
				else if(num1==2)
					  {
						m_Field=1;
						if(flag1==0)flag1=1;
						if(level1==0||level1==1)ifVert1++;
						squ1=WhoNext(level1,squ1,ch1,flag1,ifVert1,current1);
						if(squ1==-1)return ;
					  }//if(num==2)
	  }//while
 }

 LRESULT shipSpace::ToCorrect(WPARAM /*wp*/,LPARAM )
  {
  CorrectData(1);
  return 0;
  }

 LRESULT shipSpace::End(WPARAM ,LPARAM )
  {
  if(m_timer)KillTimer(1);
  m_timer=FALSE;
  MessageBox("Player won!","Game Over",MB_ICONINFORMATION| MB_OK);
  TGame::Playing=false;
  new_flag=0;
 return 0;
 }

 void shipSpace::InitFlag(int& flag,int& level,int& ifVert)
 {
 flag=0;               //init all flags
 level=0;
 ifVert=0;
 }

 int shipSpace::WhoNext(int& level,int squ,int ch,int& flag,int& ifVert,int current)
 {
 if (level>3)                          //which square next to check
 {
 InitFlag(flag,level,ifVert);
 return -1;
 }
 while(1)
 {
 squ=IfNotBound(level,squ,ch,flag);
 if(squ==-1) {
				  if(flag!=0)level++;
				  squ=current;
				  if(level>3)
					{
					 InitFlag(flag,level,ifVert);
					 break;
					}
				 }
 else break;
 }//while
 return squ;
}

 int shipSpace::IfNotBound(int level,int squ,int ch,int flag)
 {                              //check if we have place around killed ship
 int squ1;
 squ1=Next(level,squ,ch,flag);
 if(squ1==squ)  return -1;
 else 	squ=squ1;
 return squ;
 }

 int shipSpace::Next(int& level,int squ,int ch,int& flag)
 {
 switch(level)              //which squares near killed ship
 {
 case 0:if(CheckBound(squ+10)) squ=squ+10;
		  else
		  {
		  squ=ch;
		  level++;
		  }
		  break;
 case 1:if (CheckBound(squ-10)) squ=squ-10;
		  else
		  {
		  level++;
		  squ=ch;
		  }
		  break;
 case 2:if (!CheckBound(squ+1)|| squ%10==9)
		  {
		  level++;
		  squ=ch;
		  }
		  else squ=squ+1;
		  break;
 case 3:if (!CheckBound(squ-1)||squ%10==0)
		 {
		 flag=0;
		 level=0;
		 }
		 else  squ=squ-1;
		 break;
		 } //switch
 return squ;
 }

 int shipSpace::CheckBound(int squ)
 {
 return (squ>=0&&squ<100);
 }

 int shipSpace::CheckPlace2(int squ)
 {
 int i=squ/10;
 int j=squ%10;
 if(m_pOpponentGame->GetState(squ)==SqsShip)
	  {
		m_pOpponentGame->SetState(squ, SqsKillShip);
		if(!Animation)Fly2(squ);
		if(!Snd)
		sndPlaySound("charge.wav",SND_ASYNC);
		m_pGameOpponentView->EvCommand(squ+CM_SQUARE,0,0);
		m_pGameOpponentView->Invalidate(false);
		UpdateWindow();
		CorrectData(1);
		m_pGameMyView->EnableWindow(false);
		if (m_pGameOpponentView->GetKillShipCount()==20)
		  {
		  if(m_timer)KillTimer(1);
			m_timer=FALSE;
		  MessageBox("First won!","Game Over",MB_ICONINFORMATION| MB_OK);
		  TGame::Playing=false;
		  GetApplication()->GetMainWindow()->RestoreMenu();
		  new_flag=0;
		  m_pGameMyView->EnableWindow(true);
		  return 0;
			}
		HelpCheck2(i,j);
		m_pGameOpponentView->place[i][j]=1;
		return 2;
	  }
 else if(m_pOpponentGame->GetState(squ)==SqsEmptySel&&m_pGameOpponentView->place[squ/10][squ%10]==0)
			 {
			  m_pGameMyView->EnableWindow(true);
			  m_pOpponentGame->SetState(squ, SqsEmptySel);
			  if(!Animation) Fly2(squ);
			  if(!Snd)
			  sndPlaySound("click5.wav",SND_ASYNC);
			  m_pGameOpponentView->EvCommand(squ+CM_SQUARE,0,0);
			  m_pGameOpponentView->Invalidate(false);
			  m_pGameOpponentView->place[i][j]=2;
			  if(m_pOpt==2)  return 3;
			  return 0;

			 }
		 else return 1;
 }

 int shipSpace::CheckPlace(int squ)
 {
 int i=squ/10;
 int j=squ%10;
 if(m_pMyGame->GetState(squ)==SqsShip)
	  {
		m_pMyGame->SetState(squ, SqsKillShip);
		if(!Animation)Fly(squ);
		if(!Snd)
		sndPlaySound("charge.wav",SND_ASYNC);
		m_pGameMyView->EvCommand(squ+CM_SQUARE,0,0);
		m_pGameMyView->Invalidate(false);
		UpdateWindow();
		CorrectData(0);
		m_pGameOpponentView->EnableWindow(false);
		if (m_pGameMyView->GetKillShipCount()==20)
		  {
		  if(m_timer)KillTimer(1);
		  m_timer=FALSE;
		  if(m_pOpt!=2)
		  MessageBox("Computer won!","Game Over",MB_ICONINFORMATION| MB_OK);
		  else
		  MessageBox("Second won!","Game Over",MB_ICONINFORMATION| MB_OK);
		  shipSpace::new_flag=0;
		  TGame::Playing=false;
		  GetApplication()->GetMainWindow()->RestoreMenu();
		  return 0;
			}
		HelpCheck(i,j);
		places[i][j]=1;
		return 2;
	  }
 else if(m_pMyGame->GetState(squ)==SqsEmptySel&&places[squ/10][squ%10]==0)
			 {
			  m_pGameOpponentView->EnableWindow(true);
			  m_pMyGame->SetState(squ, SqsEmptySel);
			  if(!Animation) Fly(squ);
			  if(!Snd)
			  sndPlaySound("click5.wav",SND_ASYNC);
			  m_pGameMyView->EvCommand(squ+CM_SQUARE,0,0);
			  m_pGameMyView->Invalidate(false);
			  places[i][j]=2;
			  return 0;
			 }
		 else return 1;

 }


 void shipSpace::Fly(int squ)
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
 point.x=squ%10*25+72;
 point.y=squ/10*25+35;
 TBitmap* pImage=new TBitmap(GetApplication()->GetInstance(), IDB_IMGCORE);
 TBitmap* pMask=new TBitmap(GetApplication()->GetInstance(), IDB_MSCORE);
 Drag *pd=new Drag(this->HWindow,pImage,pMask);
 if(!Speed) pd->SetAnimationSpeed(SLOW);
 else pd->SetAnimationSpeed(FAST);
 pd->Animation(TPoint(545,275),point);
 delete pImage;
 delete pMask;
 delete pd;

 }

 void shipSpace::Fly2(int squ)
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
 point.x=squ%10*25+340;
 point.y=squ/10*25+35;
 TBitmap* pImage=new TBitmap(GetApplication()->GetInstance(), IDB_IMGCORE);
 TBitmap* pMask=new TBitmap(GetApplication()->GetInstance(), IDB_MSCORE);
 Drag *pd=new Drag(this->HWindow,pImage,pMask);
 if(!Speed) pd->SetAnimationSpeed(SLOW);
 else pd->SetAnimationSpeed(FAST);
 pd->Animation(TPoint(75,275),point);
 delete pImage;
 delete pMask;
 delete pd;
 }

 void shipSpace::CorrectData(int num)
 {
 int flag=0;
 int i,j;
 TRect rc(65,25,66,25);
 TRect rc1(65,55,66,55);
 TRect rc2(175,25,176,25);
 TRect rc3(175,55,176,55);
 switch(num)
  {
	case 0:
			for(i=0;i<4;i++) m_pGameMyView->live[i]=0;
			for(i=0;i<4;i++)
			 {
			  if(m_pGameMyView->IsShip(m_pGameMyView->ones[i]))
			  m_pGameMyView->live[0]++;
			  if(!m_pGameMyView->IsShip(m_pGameMyView->four[i])) flag=1;
			 } //for
			 if(!flag) m_pGameMyView->live[3]=1;
			 flag=0;
			 for(i=0;i<2;i++)
			 {
			  for(j=0;j<3;j++)
			  if(!m_pGameMyView->IsShip(m_pGameMyView->three[i*3+j]))flag=1;
			  if(!flag) m_pGameMyView->live[2]++;
			  flag=0;
			 } //for
			 flag=0;
			 for(i=0;i<3;i++)
			 {
			  for(j=0;j<2;j++)
			  if(!m_pGameMyView->IsShip(m_pGameMyView->two[i*2+j]))flag=1;
			  if(!flag) m_pGameMyView->live[1]++;
			  flag=0;
			 } //for
			 for(i=0;i<4;i++)
			 m_pGameMyView->Info->live[i]=m_pGameMyView->live[i];
			 m_pGameMyView->Info->Invalidate();
			// InvalidateRect(rc);
			break;
  case 1:
			 for(i=0;i<4;i++)m_pGameOpponentView->live[i]=0;
			for(i=0;i<4;i++)
			 {
			  if(m_pGameOpponentView->IsShip(m_pGameOpponentView->ones[i]))
			  m_pGameOpponentView->live[0]++;
			  if(!m_pGameOpponentView->IsShip(m_pGameOpponentView->four[i])) flag=1;
			 }  //for
			 if(!flag) m_pGameOpponentView->live[3]=1;
			 flag=0;
			 for(i=0;i<2;i++)
			 {
			  for(j=0;j<3;j++)
			  if(!m_pGameOpponentView->IsShip(m_pGameOpponentView->three[i*3+j]))flag=1;
			  if(!flag) m_pGameOpponentView->live[2]++;
			  flag=0;
			 }  //for
			 flag=0;
			 for(i=0;i<3;i++)
			 {
			  for(j=0;j<2;j++)
			  if(!m_pGameOpponentView->IsShip(m_pGameOpponentView->two[i*2+j]))flag=1;
			  if(!flag) m_pGameOpponentView->live[1]++;
			  flag=0;
			 }  //for
			for(i=0;i<4;i++)
			m_pGameOpponentView->Info->live[i]=m_pGameOpponentView->live[i];
			m_pGameOpponentView->Info->Invalidate();
			break;
 }  //switch
 }

 void shipSpace::HelpCheck(int i,int j)  //here exactly no ships
{
if(i==0&&j==0) places[1][1]=3;        //coner
else if(i==0&&j==9) places[1][8]=3;         //coner
	  else if(i==9&&j==0) places[8][1]=3;            //coner
			 else if(i==9&&j==9) places[8][8]=3;              //coner
					else if(i==0)  {                     //first row
										 places[i+1][j-1]=3;
										 places[i+1][j+1]=3;
										}
						  else if(i==9)                   // last row
										{
										 places[i-1][j-1]=3;
										 places[i-1][j+1]=3;
										}
								 else if(j==0)             //first column
										{
										 places[i-1][j+1]=3;
										 places[i+1][j+1]=3;
										}
										else if(j==9)        //last column
											  {
												places[i-1][j-1]=3;
												places[i+1][j-1]=3;
											  }
											 else           //else
											  {
												places[i-1][j-1]=3;
												places[i-1][j+1]=3;
												places[i+1][j-1]=3;
												places[i+1][j+1]=3;
											  }
  }


 void shipSpace::HelpCheck2(int i,int j) //here exactly no ships
{
if(i==0&&j==0) m_pGameOpponentView->place[1][1]=3;        //coner
else if(i==0&&j==9) m_pGameOpponentView->place[1][8]=3;         //coner
	  else if(i==9&&j==0) m_pGameOpponentView->place[8][1]=3;            //coner
			 else if(i==9&&j==9) m_pGameOpponentView->place[8][8]=3;              //coner
					else if(i==0)  {                     //first row
										 m_pGameOpponentView->place[i+1][j-1]=3;
										 m_pGameOpponentView->place[i+1][j+1]=3;
										}
						  else if(i==9)                   // last row
										{
										 m_pGameOpponentView->place[i-1][j-1]=3;
										 m_pGameOpponentView->place[i-1][j+1]=3;
										}
								 else if(j==0)             //first column
										{
										 m_pGameOpponentView->place[i-1][j+1]=3;
										 m_pGameOpponentView->place[i+1][j+1]=3;
										}
										else if(j==9)        //last column
											  {
												m_pGameOpponentView->place[i-1][j-1]=3;
												m_pGameOpponentView->place[i+1][j-1]=3;
											  }
											 else           //else
											  {
												m_pGameOpponentView->place[i-1][j-1]=3;
												m_pGameOpponentView->place[i-1][j+1]=3;
												m_pGameOpponentView->place[i+1][j-1]=3;
												m_pGameOpponentView->place[i+1][j+1]=3;
											  }
  }


 void shipSpace::HelpToStart()
 {
 int squares[4];
 TDir dir;
 int squ;
 m_pMyGame->Start();
 m_pGameOpponentView->CmGameNew();
 for(int i=3;i>=0;i--)
 {
	m_ind=i+1;
	int k=0;
	 for(int j=0;j<4-i;j++)
	  {
	  squ=random(100);
	  dir=(TDir)random(4);
	  if (!(m_pGameOpponentView->IsPlace(squ,m_ind,squares,dir)))
		 {j--;
		  continue;
		 }
	m_pGameOpponentView->m_Drag=true;
	for (int r=0;r<m_ind;r++)
	{
	m_pGameOpponentView->EvCommand(squares[r]+CM_SQUARE,0,0);
	switch (m_ind)
	 {
	  case 1:m_pGameOpponentView->ones[k++]=squares[r];break;
	  case 2:m_pGameOpponentView->two[k++]=squares[r];break;
	  case 3:m_pGameOpponentView->three[k++]=squares[r];break;
	  case 4:m_pGameOpponentView->four[k++]=squares[r];break;
	  }
	}
	m_pGameOpponentView->m_Drag=false;
  }
 }
	if(m_pOpt!=2)
	m_pGameOpponentView->CmGameStart();
	else  m_pGameMyView->Game.Start();
	m_pGameOpponentView->ShowWindow(SW_SHOW);
	CorrectData(1);
	if(TGame::Playing&&!Info) m_pGameOpponentView->Info->Show(SW_SHOW);
 }

 void  shipSpace::CmGameFirst()
 {
	if (!m_WhoFirst)
		  m_WhoFirst=1;
 }
 void  shipSpace::CmGameSecond()
 {
	if (!m_WhoFirst)
		  m_WhoFirst=2;
 }

 void shipSpace::CeGameFirst(TCommandEnabler& ce)
 {
	switch (m_pOpt)
	{
	case 0:
 if (m_pTTY->IsConnected()&& !m_pOpt && (!m_WhoFirst || m_WhoFirst==1))
	ce.Enable(true);
 else
  ce.Enable(false);
 if (m_WhoFirst==1)
 {
  ce.SetCheck(1);
  if (m_ReceiveCom)
	 ce.Enable(false);
  else
	 ce.Enable(true);
 }
 else
  ce.SetCheck(0);
  break;
default:ce.Enable(false);
  }
}

void shipSpace::CeGameSecond(TCommandEnabler& ce)
{
 switch (m_pOpt)
 {
	case 0:
 if (m_pTTY->IsConnected() &&  (!m_WhoFirst || m_WhoFirst==2) && !m_pOpt)
	ce.Enable(true);
 else
  ce.Enable(false);
 if (m_WhoFirst==2)
  {
  ce.SetCheck(1);
  if (m_ReceiveCom)
	 ce.Enable(false);
  else
	 ce.Enable(true);
 }
 else
  ce.SetCheck(0);
  break;
 default:ce.Enable(false);
  }
}

 void shipSpace::CmGameStart()
 {
  char Block[300];
  int nums[22];
  m_pMyGame->Start();
  m_pGameOpponentView->CmGameStart();
  if(TGame::Playing&&!Info) m_pGameOpponentView->Info->Show(SW_SHOW);
  nums[0]=SmesPlace;
  int n=m_pMyGame->GetDimension()*m_pMyGame->GetDimension();
  m_Event=0;
  int k=1;
  for (int i=0;i<n;i++)
			 if (m_pMyGame->GetState(i)==SqsShip)
			 {
				nums[k]=i;
				k++;
				wsprintf(Block+lstrlen(Block)," %.1d",i);
			 }
  nums[21]=m_WhoFirst;
  m_pTTY->EnableComm(22*sizeof(short)-1);
  m_Event=1;
  m_pGameOpponentView->EnableWindow(false);
  m_pGameMyView->EnableWindow(false);
  m_pTTY->WriteCommBlock(  (LPSTR)&nums[0],sizeof(nums));
  m_pGameOpponentView->ShowWindow(SW_SHOW);
 }

 void shipSpace::CmShip(WPARAM id)
 {
 int ind= (id-IDB_SHIP1);
 position=1;
 m_ind=ind+1;
  if (m_count[ind]==1)
  {
			 Ship_View[ind]->ShowWindow(SW_HIDE);
			 TRect rect(345,55,448,195);
			 InvalidateRect(rect,FALSE);
			 UpdateWindow();
  }
 TPoint pos;
 GetCursorPos( pos);
 BeginDrag(pos,ind);
 }

 void shipSpace::BeginDrag(TPoint& pos,int ind)
 {
  ::SetCursor(LoadCursor(GetApplication()->GetInstance(), "ISSELPOINT"));
  SetCapture();
	pDrag=new
	Drag (HWindow,pos, pImage[0][ind],pMask[0][ind]);
 }

 void shipSpace::EvLButtonDown(UINT , TPoint& point)
 {
 if (!pDrag) return;
 if(new_flag==1&& cur)
 {
 cur=0;
 a=0;b=0;c=0;d=0;
 for(int i=0;i<4;i++)
 {
 m_pGameMyView->ones[i]=0;
 m_pGameMyView->four[i]=0;
 }
 for(i=0;i<6;i++)
 {
 m_pGameMyView->two[i]=0;
 m_pGameMyView->three[i]=0;
 }

 }
 int squares[4];
 TDir dir=DirDown;
 if (position==4)
	dir=DirUp;
 else
  if (position==3)
	 dir=DirLeft;
 else
  if (position==1)
		 dir=DirRight;

 MapWindowPoints( m_pGameMyView->HWindow, &point, 1);
 int squ=m_pGameMyView->GetSquareFromPoint(point);
 if (squ<0)
 {
 Ship_View[m_ind-1]->ShowWindow(SW_SHOW);
 ReleaseCapture();
 pDrag->DragEnd();
		position=1;
		delete pDrag;
		pDrag=NULL;
 return;
 }
	 if (m_pGameMyView->IsPlace(squ,m_ind,squares,dir))
	 {
	 ReleaseCapture();
		pDrag->DragEnd();
		delete pDrag;
		pDrag=NULL;
  m_pGameMyView->m_Drag=true;
  for (int i=0;i<m_ind;i++)
	{
	m_pGameMyView->EvCommand(squares[i]+CM_SQUARE,0,0);
	 switch (m_ind)
	  {
		case 1:m_pGameMyView->ones[a++]=squares[i];break;
		case 2:m_pGameMyView->two[b++]=squares[i];break;
		case 3:m_pGameMyView->three[c++]=squares[i];break;
		case 4:m_pGameMyView->four[d++]=squares[i];break;
	  }
	}
  ShipInField++;
  m_pGameMyView->m_Drag=false;
  m_count[m_ind-1]--;
 if (!m_count[m_ind-1])
 {
		Ship_View[m_ind-1]->ShowWindow(SW_HIDE);
		TRect rect(345,55,448,195);
		InvalidateRect(rect,FALSE);
 }
 }
  CorrectData(0);

/* int k=0;
 int nums[20];
 for (int i=0;i<100;i++)
			 if (m_pMyGame->GetState(i)==SqsShip)
			 {
				nums[k]=i;
				k++;
			 }

 FillArrayStatus(nums);*/

}

 LRESULT shipSpace::ReceivePoint(WPARAM ,LPARAM lp)
 {
  m_CursorPoint=(TPoint)lp;
  return 0;
 }

 LRESULT shipSpace::CmShipMove(WPARAM wp,LPARAM lp)
 {
 int i;
 int num,x,y;
 if (pDrag)
	return 0;
 int direction=wp;
 TPoint pnt;
 pnt=m_CursorPoint;
 MapWindowPoints( m_pGameMyView->HWindow, &pnt, 1);
 int squ=m_pGameMyView->GetSquareFromPoint(pnt);
 if (squ<0)
	return 0;
 int dir;
 int begSqu=GetShipBegin(squ,&dir);
  if (!dir)
	dir=DirShipRight;
 int count =DeleteShip(begSqu,dir);
 if (count<=4)
 {
 position=1;
 m_ind=count;
 m_count[m_ind-1]++;
 pnt=m_CursorPoint;
 if (lp==1)
 {
  switch(m_ind)
	 {
		case 1:num=0;x=395;y=75;break;
		case 2:num=1;x=390;y=105;break;
		case 3:num=2;x=375;y=135;break;
		case 4:num=3;x=330;y=155;break;
	 }

 if(!Snd) sndPlaySound("whistlup.wav",SND_ASYNC);
	switch(m_ind)
	{
	case 1:
			 for(i=0;i<4;i++)
			 if(m_pGameMyView->ones[i]==begSqu) a=i;
			 break;
	case 2:
			 for(i=0;i<6;i++)
			 if(m_pGameMyView->two[i]==begSqu)
			 {
			 if(i==0||i==1) b=0;
			 if(i==2||i==3) b=2;
			 if(i==4||i==5) b=4;
			 }
			 break;
	case 3:
			 for(i=0;i<6;i++)
			 if(m_pGameMyView->three[i]==begSqu)
			 {
			 if(i==0||i==1||i==2) c=0;
			 if(i==3||i==4||i==5) c=3;
			 }
			 break;
	case 4:d=0;break;
	}
 CorrectData(0);

 if(!Animation)
 {
 Drag *pd=new Drag(this->HWindow,pImage[0][num],pMask[0][num]);
 if(!Speed) pd->SetAnimationSpeed(SLOW);
 else pd->SetAnimationSpeed(FAST);
 pd->Animation(pnt,TPoint(x,y));
 delete pd;
 }
 Ship_View[m_ind-1]->ShowWindow(SW_SHOW);
 return 0;
 }
 ::ClientToScreen(HWindow,&m_CursorPoint);
 BeginDrag( pnt,count-1);
 ChangeImage(m_CursorPoint,direction);
 }
	switch(m_ind)
	{
	case 1:
			 for(i=0;i<4;i++)
			 if(m_pGameMyView->ones[i]==begSqu) a=i;
			 break;
	case 2:
			 for(i=0;i<6;i++)
			 if(m_pGameMyView->two[i]==begSqu)
			 {
			 if(i==0||i==1) b=0;
			 if(i==2||i==3) b=2;
			 if(i==4||i==5) b=4;
			 }
			 break;
	case 3:
			 for(i=0;i<6;i++)
			 if(m_pGameMyView->three[i]==begSqu)
			 {
			 if(i==0||i==1||i==2) c=0;
			 if(i==3||i==4||i==5) c=3;
			 }
			 break;
	case 4:d=0;break;
	}
  CorrectData(0);

  return 0;
 }

 int shipSpace::DeleteShip(int squ,TDirShip dir)
 {
  int row=squ/10;
  int col=squ%10;
  int i=0;
	switch (dir)
	{
  case DirShipUp:
  {
	while ((row-i)>=0 && m_pGameMyView->IsShip((row-i)*10+col))
	{
	 m_pMyGame->SetState((row-i)*10+col,SqsEmptySel);
	 m_pGameMyView->SetGlyph((row-i)*10+col,0);
	 i++;
	}
	 break;
	}
	case DirShipDown:
	{
	while ((row+i)<10 && m_pGameMyView->IsShip((row+i)*10+col))
	{
	 m_pMyGame->SetState((row+i)*10+col,SqsEmptySel);
	 m_pGameMyView->SetGlyph((row+i)*10+col,0);
	 i++;
	}
	break;
	}
	case DirShipRight:
	{
	while ((col+i)<10 && m_pGameMyView->IsShip(row*10+col+i))
	{
	 m_pMyGame->SetState(row*10+(col+i),SqsEmptySel);
	 m_pGameMyView->SetGlyph(row*10+(col+i),0);
	 i++;
	}
	break;
	}
	case DirShipLeft:
	{
	while ((col-i)>=0 && m_pGameMyView->IsShip(row*10+(col-i)) )
	{
	 m_pMyGame->SetState(row*10+(col-i),SqsEmptySel);
	 m_pGameMyView->SetGlyph(row*10+(col-i),0);
	 i++;
	}
	break;
	}
	}
	ShipInField--;
	return i;

 }

 int shipSpace::GetShipBegin(int squ,int *dir)
 {
  int row=squ/10;
  int col=squ%10;
  {
	int i=0;
	while ((row-i-1)>=0 && m_pGameMyView->IsShip((row-i-1)*10+col))
	{
	 i++;
	}
	if (i)
	{
	 *dir= DirShipDown;
	 return (row-i)*10+col;
	}
	}
	{
	int i=0;
	while ((row+i+1)<10 && m_pGameMyView->IsShip((row+i+1)*10+col))
	{
	 i++;
	}
	if (i)
	{
	 *dir= DirShipUp;
	 return (row+i)*10+col;
	}
	}
	{
	int i=0;
	while ((col-i-1)>=0 && m_pGameMyView->IsShip(row*10+(col-i-1)))
	{
	 i++;
	}
	if (i)
	{
	 *dir= DirShipRight;
	 return row*10+(col-i);
	}
	}
	{
	int i=0;
	while ((col+i+1)<10 && m_pGameMyView->IsShip(row*10+(col+i+1)))
	{
	 i++;
	}
	if (i)
	{
	 *dir= DirShipLeft;
	 return row*10+(col+i);
	}
	}
	 *dir=DirShipNone;  //none;
  return squ;
 }

 void shipSpace::EvKeyDown (uint key, uint , uint )
 {
	 TPoint point;
	 TPoint pnt;
	 ::GetCursorPos( &point);
	 pnt=point;
	 ScreenToClient(point);
	 if(pDrag) ChangeImage(pnt,key);
 }

 void shipSpace::ChangeImage(TPoint &pnt,int key)
 {
	 pDrag->DragEnd();
	 SetCursorPos(pnt.x,pnt.y);
	 switch(key)
	 {
	 case 37:position=3;
				pDrag->ChangeImage(pImage[1][m_ind-1],pMask[1][m_ind-1]);
				break;
	 case 38:position=4;
				pDrag->ChangeImage(pImage[2][m_ind-1],pMask[2][m_ind-1]);
				break;
	 case 39:position=1;
				pDrag->ChangeImage(pImage[0][m_ind-1],pMask[0][m_ind-1]);
				break;
	 case 40:position=2;
				pDrag->ChangeImage(pImage[3][m_ind-1],pMask[3][m_ind-1]);
				break;
  }
  pDrag->DragStart(pnt);
 }

 void shipSpace::EvMouseMove(uint , TPoint& pnt)
 {
	  if (!pDrag)
			 return;

  pDrag->DragImage(pnt);
 }

 BOOL shipSpace::EvSetCursor(HWND, UINT, UINT)
 {
 if(pDrag)
  ::SetCursor(LoadCursor(GetApplication()->GetInstance(), "ISSELPOINT"));

  else ::SetCursor(LoadCursor(NULL, IDC_ARROW));
  return FALSE;

 }

 void shipSpace::SetupWindow ()
 {
 TWindow::SetupWindow();
 m_pGameMyView->SetParent(this);
 m_pGameMyView->Create();

 m_pGameOpponentView->SetParent(this);
 m_pGameOpponentView->Create();
 m_pGameOpponentView->
						 MoveWindow(m_pGameMyView->Attr.X+m_pGameMyView->Attr.W+20,
														m_pGameMyView->Attr.Y,
														m_pGameMyView->Attr.W,
														m_pGameMyView->Attr.H);
 m_pGameOpponentView->ShowWindow(SW_HIDE);
 m_pGameMyView->Info->Show(SW_SHOW);
 m_pGameOpponentView->Info->Show(SW_HIDE);
 m_pTTY=new TTY(this);

 }

 shipSpace::~shipSpace ()
 {
  for(int i=0;i<4;i++)
	 for(int j=0;j<4;j++)
	 {
		delete pMask[i][j];
		delete pImage[i][j];
	 }

		for( i=0;i<4;i++)
			 delete Ship_View[i];
		delete m_pGameMyView->Info;
		delete m_pGameOpponentView->Info;
		delete m_pMyGame;
		delete m_pGameMyView;
		delete m_pOpponentGame;
		delete m_pGameOpponentView;


		if (pDrag)
		{
			 ReleaseCapture();
			 delete pDrag;
		}
		if (m_pTTY)
		{
		 m_pTTY->CloseConnection();
	  delete m_pTTY;
		}
 }
 void shipSpace::ReceiveBlock( TGame* pMyGame,TGameView *pGameMyView,
							TGame* pOpponentGame,TGameView *pGameOpponentView,
							int *placeShip,
							TMesState state)
 {

  switch (state)
  {
  case SmesPlace:
  {

					for (int i=0;i<20;i++)
					{
					  pOpponentGame->SetState(placeShip[i], SqsShip);
					}
					FillArrayStatus(placeShip);
					CorrectData(1);

  }
  break;
  case SmesClick:
			 {

				{
					 if (pMyGame->GetState(placeShip[0])==SqsShip)
					 {

					  pMyGame->SetState(placeShip[0], SqsKillShip);
					  pGameMyView->m_Receive=TRUE;
					  if(!Animation)Fly(placeShip[0]);
					  if(!Snd)
					  sndPlaySound("charge.wav",SND_ASYNC);
					  pGameMyView->EvCommand(placeShip[0]+CM_SQUARE,0,0);
					  pGameMyView->Invalidate(false);
					  pGameOpponentView->EnableWindow(false);
					  pGameMyView->m_Receive=FALSE;

					  CorrectData(0);
					  if (  pGameMyView->GetKillShipCount()==20)
					  {
							MessageBox("Opponent won!",
								"Game Over",MB_ICONINFORMATION| MB_OK);
								TGame::Playing=false;
								m_Event=0;

						}
					 }
					 else
					 {
					  m_ReceiveCom=false;
					  pGameOpponentView->EnableWindow(true);
					  if (pMyGame->GetState(placeShip[0])==SqsEmpty ||
								 pMyGame->GetState(placeShip[0])==SqsEmptySel)
					 {
					  pMyGame->SetState(placeShip[0], SqsEmptySel);
					  pGameMyView->m_Receive=TRUE;
					  if(!Animation)Fly(placeShip[0]);
					  if(!Snd)
					  sndPlaySound("click5.wav",SND_ASYNC);
					  pGameMyView->EvCommand(placeShip[0]+CM_SQUARE,0,0);
					  pGameMyView->Invalidate(false);
					  pGameMyView->m_Receive=FALSE;

					  }
					}
				}
			 }
			 break;

  }
 }

 void shipSpace::BroadcastBlock(int *Block,TMesState state)
 {
 ReceiveBlock( m_pMyGame,m_pGameMyView,m_pOpponentGame,m_pGameOpponentView,Block,state);
 }
// Click on Opponent field
 LRESULT shipSpace::CmSquareClick(WPARAM wp,LPARAM lp)
 {
  if (m_pOpt==2 ||m_pOpt==1)
	 return 0;
  TGameView *pV=(TGameView*)lp;
  if (pV==m_pGameOpponentView)
  {

  int com[2];
	  com[0]=SmesClick;
	  com[1]=wp;
	  if (m_pOpponentGame->GetState(wp)!=SqsShip)
	  {
		 m_ReceiveCom=true;
		 m_pGameOpponentView->EnableWindow(false);

	  }
	  else
	  {
		 m_ReceiveCom=false;
		 m_pGameOpponentView->EnableWindow(true);
		 m_pOpponentGame->SetState(Pos,SqsKillShip);
		 CorrectData(1);


	  }
	  m_pTTY->WriteCommBlock(  (LPSTR)&com[0],sizeof(com));
	  if (  m_pGameOpponentView->GetKillShipCount(true)==20)
	  {
							MessageBox("You won!",
								"Game Over",MB_ICONINFORMATION| MB_OK);
							TGame::Playing=false;
							m_Event=0;

	  }

  }
  return 0;
}
//***********************************************************************
 void shipSpace::ReadCommData()
 {
 if (!m_pTTY || !m_pTTY->IsConnected())return;

 if (m_pOpt==2 || m_pOpt==1) return;
 if (m_pTTY && m_pTTY->IsConnected())
	 {
	  int Block[22];
	  int count=m_pTTY->GetInputCount();
	  if (count>0)
		 {
		 if (m_EventComm!= SmesPlace && m_EventComm!= SmesClick)
			{
			 if (count>=sizeof(short))
			 {
			  m_pTTY->ReadCommBlock(  (LPSTR) Block, sizeof(short) );
			  m_EventComm=SmesNone;
			  switch (Block[0])
			  {
				case   SmesConnect:
										 Block[0]=SmesReply;
										 m_pTTY->WriteCommBlock((LPSTR)Block,sizeof(short));
										// if (ConnectTimer)
										// KillTimer(ConnectTimer);
										// ConnectTimer=0;
										 return;

			  case   SmesReply:
									  m_Connected=TRUE;
									  if (ConnectTimer)
										 KillTimer(ConnectTimer);
										 ConnectTimer=0;
									  return;

			 case   SmesPlace:
			 case   SmesClick:
									count-=sizeof(short);
									m_EventComm=Block[0];
									break;
			case   SmesStop:
								  TGame::Playing=false;
								  CmStop();
								  return;
		  case   SmesExit:
								  {
									TGame::Playing=false;
									CmUnConnect();

								int res=MessageBox("Opponent was clicked exit!Do you exit too?",
								"Game Over",MB_ICONINFORMATION| MB_YESNO);
								if (res==IDYES)
									PostQuitMessage(0);
								else
									CmGameNew();
									return;
								 }
  }
 }
 }
 if (m_EventComm==SmesPlace && m_Event==1 && count>=21*sizeof(short))
 {
 m_pTTY->ReadCommBlock(  (LPSTR) (Block+1), 21*sizeof(short) );
 if (m_WhoFirst==Block[21])
 {
	 MessageBox("Opponent have the same game.\rGame is stopped",
					"First data is recieved",MB_OK|MB_APPLMODAL|MB_ICONINFORMATION);
	 m_Event=0;
	 TGame::Playing=false;
	 m_WhoFirst=0;
	 m_EventComm=SmesNone;
	 return;
 }
	 TGame::Playing=true;
	  if (m_WhoFirst==2)
	  {
		 m_ReceiveCom=true;
		 m_pGameOpponentView->EnableWindow(false);
		 TGame::Playing=true;
	  }
	  else
	  {
		 m_ReceiveCom=false;
		 m_pGameOpponentView->EnableWindow(true);

	  }

  m_EventComm=SmesNone;
  BroadcastBlock(Block+1, SmesPlace);
  m_Event=2;
 }
 else
 if (TGame::Playing && m_EventComm==SmesClick && m_ReceiveCom && m_Event==2 && count>=1*sizeof(short))
 {
 m_pTTY->ReadCommBlock(  (LPSTR) (Block+1), 1*sizeof(short) );
 m_EventComm=SmesNone;
 BroadcastBlock(Block+1, SmesClick);
 }
 }
}
}
//***********************************************************************
 void shipSpace::EvCommNotify(UINT,UINT )
 {
 if (!TGame::Playing)
	  return;
 {
 ReadCommData();
 if (!TGame::Playing)
	 return;
  m_pTTY->ClearEvent();
  if (m_Event==2)
		m_pTTY->EnableComm(2*sizeof(short)-1);
 }
 }
//**************************************************************************
 void shipSpace::ExcludeClipRect(TWindow *pView,TDC &dc)
 {
 TRect rc=GetClientRect();

	TRect rcMyView= pView->GetWindowRect();
	TPoint pt1=TPoint(rcMyView.left,rcMyView.top);
	TPoint pt2=TPoint(rcMyView.right,rcMyView.bottom);
	pView->ScreenToClient(pt1);
	pView->ScreenToClient(pt2);
	rcMyView=TRect(pt1,pt2);
	pView->MapWindowPoints(this->HWindow, (TPoint*)&rcMyView,2 );
	dc.ExcludeClipRect(rcMyView);

 }
 bool shipSpace::EvEraseBkgnd( HDC hdc)
  {
  TDC dc(hdc);
  BITMAP Bitmap;
  TBitmap bm(GetApplication()->GetInstance(),IDB_FONE );

	TMemoryDC  mDC(dc);
	mDC.SelectObject(bm);
	bm. GetObject(Bitmap);
	TRect rc=GetClientRect();
	ExcludeClipRect(m_pGameMyView,dc);
	if (m_pGameMyView->Info->IsWindowVisible())
		ExcludeClipRect(m_pGameMyView->Info,dc);
	if (m_pGameOpponentView->IsWindowVisible())
	{
	 ExcludeClipRect(m_pGameOpponentView,dc);
	if (m_pGameOpponentView->Info->IsWindowVisible())
		ExcludeClipRect(m_pGameOpponentView->Info,dc);
	}

	int left=rc.Width()/Bitmap.bmWidth+1;
	int top=rc.Height()/Bitmap.bmHeight+1;

	for (int i=0;i<left;i++)
	for (int k=0;k<top;k++)
	dc.BitBlt(  i*Bitmap.bmWidth,k* Bitmap.bmHeight,
					Bitmap.bmWidth, Bitmap.bmHeight,
					mDC, 0,0, SRCCOPY );
	  char buffer[1];
	  dc.SelectObject(TPen(4,3));
	  dc.MoveTo(345,55);
	  dc.LineTo(345,184);
	  TBrush br(6);
	  dc.SetBkMode(TRANSPARENT);
	  dc.SelectObject(br);
	  dc.Rectangle(345,55,448,195);
		for(  i=0;i<10;i++)
		{
		sprintf(buffer,"%c",65+i);
		dc.TextOut(70+i*25,3,buffer);
	  }
	  for(  i=0;i<9;i++)
		{
		sprintf(buffer,"%c",49+i);
		dc.TextOut(45,20+i*25,buffer);
	  }
	  dc.TextOut(40,245,"10");
	if (m_pGameOpponentView->IsWindowVisible())
	{
		for(  i=0;i<10;i++)
		{
		sprintf(buffer,"%c",65+i);
		dc.TextOut(330+i*25,3,buffer);
	  }

  for( int i=0;i<9;i++)
	  {
	  sprintf(buffer,"%c",49+i);
	  dc.TextOut(580,20+i*25,buffer);
	  }
	dc.TextOut(580,245,"10");
	TMemoryDC memDC;
	TBitmap resBmp1(GetApplication()->GetInstance(),IDB_TOTAH);
	memDC.SelectObject(resBmp1);
	dc.BitBlt(550,270,resBmp1.Width(),resBmp1.Height(),memDC,0,0,SRCCOPY);

 }

	TMemoryDC memDC;
	TBitmap resBmp2(GetApplication()->GetInstance(),IDB_TOTAH1);
	memDC.SelectObject(resBmp2);
	dc.BitBlt(30,270,resBmp2.Width(),resBmp2.Height(),memDC,0,0,SRCCOPY);
	dc.RestoreObjects();

	return false;                // don't want windows doing it for us.
 }

 void shipSpace::FillArrayStatus(int arr[20])
 {
 int a=0,b=0,c=0,d=0;
 int horiz;
 int k,i,j;
 int ship[4];
 int count,w,t;

 for(i=0;i<4;i++)
 {
 m_pGameOpponentView->ones[i]=0;
 m_pGameOpponentView->four[i]=0;
 }
 for(i=0;i<6;i++)
 {
 m_pGameOpponentView->two[i]=0;
 m_pGameOpponentView->three[i]=0;
 }
 for (i=0;i<20;i++)
	{
	 horiz=0;
	 if(arr[i]==-1) continue;
	 w=1;
	 for(j=i+1;j<=i+3;j++)
	  {

		 if(arr[i]+w!=arr[j])
			{
			if(j-i>1) horiz=1;
			break;
			}

		 if(arr[i]%10==9)
		  {
			 if(j-i>1) horiz=1;
			 break;
		  }
		  if((arr[i]+w)%10==9)
		  {
			 j++;
			 if(j-i>1) horiz=1;
			 break;
		  }
		 w++;
	  } //for
		 if(j-i==4) horiz=1;
		 switch(j-i)
		 {
		  case 2:
					for(k=0;k<2;k++)
					m_pGameOpponentView->two[b++]=arr[i+k];
					break;
		  case 3:
					for(k=0;k<3;k++)
					m_pGameOpponentView->three[c++]=arr[i+k];
					break;
		  case 4:
					for(k=0;k<4;k++)
					m_pGameOpponentView->four[d++]=arr[i+k];
					break;
		 }//switch

	  if(!horiz)
		 {
			for(t=0;t<4;t++) ship[t]=0;
			t=1;w=10;count=0;ship[0]=arr[i];
			for(j=i+1;j<20;j++)
			 {
			  if (arr[i]+w==arr[j])
									  {
										ship[t++]=arr[j];
										arr[j]=-1;
										w+=10;
									 }
			 } //for
			if (ship[0]==0) count=1;
			for(t=0;t<4;t++)
			  if(ship[t]!=0) count++;

			switch(count)
			{

			  case 1:m_pGameOpponentView->ones[a++]=arr[i];
						break;

			 case 2:for(k=0;k<2;k++)
					  m_pGameOpponentView->two[b++]=ship[k];

					  break;
			 case 3:for(k=0;k<3;k++)
					  m_pGameOpponentView->three[c++]=ship[k];

					  break;
			 case 4:for(k=0;k<4;k++)
					  m_pGameOpponentView->four[d++]=ship[k];

					  break;
		  }//switch
	  }//if (!horiz)
	 else
		{
		if(j-i>1) i=i+(j-i-1);
		continue;
		}
 } //for
}
