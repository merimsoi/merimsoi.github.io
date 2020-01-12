#include "connect.h"
#include "shipapp.rh"
 WORD     gawBaudTable[] = {
									 CBR_110,
									 CBR_300,
									 CBR_600,
									 CBR_1200,
									 CBR_2400,
									 CBR_4800,
									 CBR_9600,
									 CBR_14400,
									 CBR_19200,
									 CBR_38400,
									 CBR_56000,
									 CBR_128000,
									 CBR_256000
									} ;

 WORD     gawParityTable[] = {
										NOPARITY,
										EVENPARITY,
										ODDPARITY,
										MARKPARITY,
										SPACEPARITY
									  } ;

 WORD     gawStopBitsTable[] = {
										  ONESTOPBIT,
										  ONE5STOPBITS,
										  TWOSTOPBITS
										 } ;

 DEFINE_RESPONSE_TABLE1(TOptionConnectDialog, TDialog)
 EV_CHILD_NOTIFY(IDOK, BN_CLICKED, MyOk),
 END_RESPONSE_TABLE;

 // constructor of connection dialog box
 TOptionConnectDialog::TOptionConnectDialog(TWindow* parent,NPTTYINFO pInfo)
							: TDialog(parent, SETTINGSDLGBOX)
 {
  npTTYInfo =pInfo;
  pOkButton   = new TButton(this,IDOK);
  pPort=new TComboBox(this,IDD_PORTCB);
  pBaud=new TComboBox(this,IDD_BAUDCB);
  pDtBt=new TComboBox(this,IDD_DATABITSCB);
  pParity=new TComboBox(this,IDD_PARITYCB);
  pStop=new TComboBox(this, IDD_STOPBITSCB);
  pDtr=new  TCheckBox(this,IDD_DTRDSR);
  pRts=new  TCheckBox(this,IDD_RTSCTS);
  pXon=new  TCheckBox(this,IDD_XONXOFF);
  pLecho=new  TCheckBox(this,IDD_LOCALECHO);
  pReciev=new  TCheckBox(this,IDD_USECNRECEIVE);
  pDErr=new  TCheckBox(this,IDD_DISPLAYERRORS);
 }

 //destructor of connection dialog box
 TOptionConnectDialog::~TOptionConnectDialog()
 {
 delete pOkButton ;
 delete pPort ;
 delete pBaud;
 delete pDtBt ;
 delete pParity;
 delete pStop ;
 delete pDtr;
 delete  pRts;
 delete pXon;
 delete pLecho ;
 delete pReciev;
 delete pDErr ;
 }

 // function to creation connection dialog box
 void TOptionConnectDialog::SetupWindow()
 {
 TDialog::SetupWindow();
 SettingsDlgInit();
 };

 // Function to filling combobox
 void TOptionConnectDialog::FillComboBox( TComboBox *pCB,
  int nIDString,WORD  *npTable, WORD wTableLen,WORD wCurrentSetting )
 {
	  char  szBuffer[ MAXLEN_TEMPSTR ] ;
	  WORD  wCount, wPosition ;
	  for (wCount = 0; wCount < wTableLen; wCount++)
	  {
			 // load the string from the string resources and
			 // add it to the combo box
			 GetApplication()->LoadString( nIDString + wCount, szBuffer, sizeof( szBuffer ) ) ;
			 wPosition = pCB->AddString(szBuffer) ;

			 // use item data to store the actual table value
			 pCB ->SetItemData(wPosition,(uint32)*(npTable + wCount));

			// if this is our current setting, select it

			if (*(npTable + wCount) == wCurrentSetting)
			pCB->SetSelIndex(wPosition);
	 }
}

//****************************************************************************
// Function puts current settings into dialog box (via CheckRadioButton() etc.)
//****************************************************************************

 BOOL  TOptionConnectDialog:: SettingsDlgInit()
 {
	  char       szBuffer[ MAXLEN_TEMPSTR ], szTemp[ MAXLEN_TEMPSTR ] ;
	  WORD       wCount, wMaxCOM, wPosition ;
	  wMaxCOM = LOWORD( EscapeCommFunction( NULL, GETMAXCOM ) ) + 1 ;

	  // load the COM prefix from resources
	  LoadString( (HINSTANCE)GetWindowWord(GWW_HINSTANCE ),
						IDS_COMPREFIX, szTemp, sizeof( szTemp ) ) ;

	  // fill port combo box and make initial selection
	  for (wCount = 0; wCount < wMaxCOM; wCount++)
	  {
			 wsprintf( szBuffer, "%s%d", (LPSTR) szTemp, wCount + 1 ) ;
			  pPort->AddString(szBuffer) ;

	  }
		pPort->SetSelIndex(npTTYInfo->bPort-1 );
		// disable COM port combo box if connection has already been
		// established (e.g. OpenComm() already successful)
		// fill baud combo box and make initial selection

			 FillComboBox(pBaud,IDS_BAUD110, gawBaudTable,
							  sizeof( gawBaudTable ) / sizeof( WORD ),
							  npTTYInfo->wBaudRate  ) ;

		// fill data bits combo box and make initial selection
		for (wCount = 5; wCount < 9; wCount++)
		{
		 wsprintf( szBuffer, "%d", wCount ) ;
		 wPosition = pDtBt->AddString(szBuffer) ; ;

		 // if current selection, tell the combo box
		 if (wCount ==  npTTYInfo ->bByteSize)
		 pDtBt->SetSelIndex(wPosition);
		}

		// fill parity combo box and make initial selection
		FillComboBox(pParity,IDS_PARITYNONE, gawParityTable,
						 sizeof( gawParityTable ) / sizeof( WORD ),
						 npTTYInfo -> bParity ) ;

	  // fill stop bits combo box and make initial selection
	  // FillComboBox((HINSTANCE)GetWindowWord(GWW_HINSTANCE ),
	  FillComboBox(pStop ,IDS_ONESTOPBIT, gawStopBitsTable,
						sizeof( gawStopBitsTable ) / sizeof ( WORD ),
						npTTYInfo -> bStopBits ) ;

	  // initalize the flow control settings
	  pDtr->SetCheck(( npTTYInfo->bFlowCtrl  & FC_DTRDSR) > 0 ) ;
	  pRts->SetCheck(( npTTYInfo->bFlowCtrl  & FC_RTSCTS) > 0 ) ;
	  pXon->SetCheck(( npTTYInfo->bFlowCtrl  & FC_XONXOFF) > 0 ) ;

	  // other TTY settings
	  pLecho->SetCheck( npTTYInfo->fLocalEcho);

	  // control options
	  pReciev->SetCheck( npTTYInfo->fUseCNReceive);

	  // disable Use CN_RECEIVE option if connection has already been
	  // established (e.g. OpenComm() already successful)
	  pDErr->SetCheck( npTTYInfo->fDisplayErrors);
	  return ( TRUE ) ;
 }
//*************************************************************************
// Function puts dialog contents into TTY info structure.
//************************************************************************
 BOOL TOptionConnectDialog::SettingsDlgTerm()
 {
	WORD       wSelection ;
	// get port selection
	npTTYInfo ->bPort=pPort->GetSelIndex()+1;
	// get baud rate selection
	wSelection = pBaud->GetSelIndex();
	npTTYInfo->wBaudRate=pBaud->GetItemData(wSelection );
	// get data bits selection
	npTTYInfo->bByteSize =pDtBt->GetSelIndex()+5;
	// get parity selection
	wSelection = pParity->GetSelIndex();
	npTTYInfo->bParity =pParity->GetItemData(wSelection );
	// get stop bits selection
	wSelection =pStop ->GetSelIndex();
	npTTYInfo->bStopBits = pStop ->GetItemData(wSelection );
	// get flow control settings
	npTTYInfo->bFlowCtrl = 0 ;
	if (pDtr->GetCheck()& BF_CHECKED)
		 npTTYInfo->bFlowCtrl  |= FC_DTRDSR ;
	if ( pRts->GetCheck()& BF_CHECKED)
		 npTTYInfo->bFlowCtrl  |= FC_RTSCTS ;
	if (pXon->GetCheck()& BF_CHECKED )
		 npTTYInfo->bFlowCtrl  |= FC_XONXOFF ;
	// get other various settings
		 npTTYInfo->fLocalEcho =pLecho  ->GetCheck()& BF_CHECKED ;
	// control options
	npTTYInfo->fUseCNReceive = pReciev->GetCheck()& BF_CHECKED ;
	npTTYInfo->fDisplayErrors =pDErr->GetCheck()& BF_CHECKED ;
	return ( TRUE ) ;
 }
//Function involved if pressed button Ok in dialog box
 void TOptionConnectDialog::MyOk()
 {
	SettingsDlgTerm();
	TDialog::CmOk();
 }
// Constructor
 TTY:: TTY(TWindow *parnt)
 {
  hWnd=parnt->HWindow;
  parent =parnt;
  CreateTTYInfo();
 }
 // Destructor
 TTY:: ~TTY()
 {
	DestroyTTYInfo() ;
 }
//**************************************************************************
//  Function creates the tty information structure and sets
//     menu option availability.  Returns -1 if unsuccessful.
//**************************************************************************
 LRESULT TTY:: CreateTTYInfo()
 {
	// initialize TTY info structure
	COMDEV( npTTYInfo )        = 0 ;
	CONNECTED( npTTYInfo )     = FALSE ;
	LOCALECHO( npTTYInfo )     = FALSE ;
	AUTOWRAP( npTTYInfo )      = TRUE ;
	PORT( npTTYInfo )          = 1 ;
	BAUDRATE( npTTYInfo )      = CBR_1200 ;
	BYTESIZE( npTTYInfo )      = 8 ;
	FLOWCTRL( npTTYInfo )      = FC_RTSCTS ;
	PARITY( npTTYInfo )        = NOPARITY ;
	STOPBITS( npTTYInfo )      = ONESTOPBIT ;
	XONXOFF( npTTYInfo )       = FALSE ;
	USECNRECEIVE( npTTYInfo )  = TRUE ;
	DISPLAYERRORS( npTTYInfo ) = FALSE ;
	return ( (LRESULT) TRUE ) ;
 }
//***************************************************************************
//  Function destroys block associated with TTY window handle.
//***************************************************************************
 BOOL TTY:: DestroyTTYInfo( )
 {
	  // force connection closed (if not already closed)
	  if (CONNECTED( npTTYInfo ))	 CloseConnection() ;
	  return ( TRUE ) ;

 }
 void TTY::ClearEvent()
 {
		// reset the event word so we are notified
		// when the next event occurs
		if (!CONNECTED( npTTYInfo ))
		 {
		  parent->MessageBox("Connect to Com!!","Missing connection",
									 MB_ICONINFORMATION|MB_OK	) ;
		  return ;
		 }
	  GetCommEventMask( COMDEV( npTTYInfo ), EV_RXCHAR ) ;
 }
//**************************************************************************
//  Function opens communication port specified in the TTYINFO struct.
//     It also sets the CommState and notifies the window via
//     the fConnected flag in the TTYINFO struct.
//**************************************************************************
 BOOL TTY::  OpenConnection( )
 {
	  char       szPort[ 10 ], szTemp[ 10 ] ;
	  BOOL       fRetVal ;
	  HCURSOR    hOldCursor, hWaitCursor ;
	  // show the hourglass cursor
	  hWaitCursor = LoadCursor( NULL, IDC_WAIT ) ;
	  hOldCursor = SetCursor( hWaitCursor ) ;

	  // load the COM prefix string and append port number
	  parent->GetApplication()->LoadString(IDS_COMPREFIX, szTemp, sizeof( szTemp ) ) ;
	  wsprintf( szPort, "%s%d", (LPSTR) szTemp, PORT( npTTYInfo ) ) ;

	  // open COMM device
	  if ((COMDEV( npTTYInfo ) = OpenComm( szPort, RXQUEUE, TXQUEUE )) < 0)
	  {
		char CommStr[200];
		int nCommT= PORT( npTTYInfo );
		wsprintf(CommStr, "COM%d", nCommT);
		switch (COMDEV( npTTYInfo ))
			 {
				case IE_BADID:
					  wsprintf(CommStr, "Cannot open COM%d\n"
								  "This COMM is invalid or unsupported.", nCommT);
					  break;
				case IE_BAUDRATE:
					  wsprintf(CommStr, "Cannot open COM%d\n"
								  "This baud rate is unsupported.", nCommT);
					  break;
				case IE_BYTESIZE:
					  wsprintf(CommStr, "Cannot open COM%d\n"
								  "The specified byte size is invalid.", nCommT);
					  break;
				case IE_DEFAULT:
					  wsprintf(CommStr, "Cannot open COM%d\n"
								  "The default parameters are in error.", nCommT);
					  break;
				case IE_HARDWARE:
					  wsprintf(CommStr, "Cannot open COM%d\n"
								  "This COMM is not available (is locked by another device).", nCommT);
					  break;
				case IE_MEMORY:
					  wsprintf(CommStr, "Cannot open COM%d\n"
								  "The function cannot allocate the queues.", nCommT);
					  break;
				case IE_NOPEN:
					  wsprintf(CommStr, "Cannot open COM%d\n"
								  "The device is not open.", nCommT);
					  break;
				case IE_OPEN:
					  wsprintf(CommStr, "Cannot open COM%d\n"
								  "This COMM is already open.", nCommT);
					  break;
				default:
					  wsprintf(CommStr, "Cannot open COM%d\nError %d", nCommT, COMDEV( npTTYInfo ));
			 }
			 MessageBox(0, CommStr, "COMM PORT ERROR", MB_OK | MB_ICONEXCLAMATION);
			 return ( FALSE ) ;
	  }
	  fRetVal = SetupConnection() ;
	  if (fRetVal)
	  {
		CONNECTED( npTTYInfo ) = TRUE ;
		// set up notifications from COMM.DRV
		{
		// Enable notification for CN_RECEIVE events.
		 SetCommEventMask( COMDEV( npTTYInfo ), EV_RXCHAR ) ;
		 EnableCommNotification( COMDEV( npTTYInfo ), hWnd, 4, -1 ) ;
		}
		// assert DTR
		EscapeCommFunction( COMDEV( npTTYInfo ), SETDTR ) ;
	  }
	  else
	  {
			 CONNECTED( npTTYInfo ) = FALSE ;
			 CloseComm( COMDEV( npTTYInfo ) ) ;
	  }

	  // restore cursor
	  SetCursor( hOldCursor ) ;

	  return ( fRetVal ) ;

 }
 void TTY::Flush()
 {
	  FlushComm(COMDEV( npTTYInfo ), 0);
	  FlushComm(COMDEV( npTTYInfo ), 1);
 }
 void TTY::EnableComm(short )
 {
 if (!CONNECTED( npTTYInfo ))
 {
	parent->MessageBox("Connect to Com!!","Missing connection",
			  MB_ICONINFORMATION|MB_OK	) ;
		return ;
 }
}
//***************************************************************************
//  Description:
//     This routines sets up the DCB based on settings in the
//     TTY info structure and performs a SetCommState().
//---------------------------------------------------------------------------
 BOOL TTY::  SetupConnection( )
 {
	  BOOL       fRetVal ;
	  BYTE       bSet ;
	  DCB        dcb ;
	  GetCommState( COMDEV( npTTYInfo ), &dcb ) ;
	  dcb.BaudRate = BAUDRATE( npTTYInfo ) ;
	  dcb.ByteSize = BYTESIZE( npTTYInfo ) ;
	  dcb.Parity = PARITY( npTTYInfo ) ;
	  dcb.StopBits = STOPBITS( npTTYInfo ) ;

	  // setup hardware flow control
	  bSet = (BYTE) ((FLOWCTRL( npTTYInfo ) & FC_DTRDSR) != 0) ;
	  dcb.fOutxDsrFlow = dcb.fDtrflow = bSet ;
	  dcb.DsrTimeout = (bSet) ? 30 : 0 ;

	  bSet = (BYTE) ((FLOWCTRL( npTTYInfo ) & FC_RTSCTS) != 0) ;
	  dcb.fOutxCtsFlow = dcb.fRtsflow = bSet ;
	  dcb.CtsTimeout = (bSet) ? 30 : 0 ;

	 // setup software flow control
	 bSet = (BYTE) ((FLOWCTRL( npTTYInfo ) & FC_XONXOFF) != 0) ;
	 dcb.fInX = dcb.fOutX = bSet ;
	 dcb.XonChar = ASCII_XON ;
	 dcb.XoffChar = ASCII_XOFF ;
	 dcb.XonLim = 100 ;
	 dcb.XoffLim = 100 ;

	// other various settings
	dcb.fBinary = TRUE ;
	dcb.fParity = TRUE ;
	dcb.fRtsDisable = FALSE ;
	dcb.fDtrDisable = FALSE ;

	fRetVal = !(SetCommState( &dcb ) < 0) ;
	return ( fRetVal ) ;
 }
//***************************************************************************
//  Function closes the connection to the port.  Resets the connect flag
//     in the TTYINFO struct.
//***************************************************************************
 BOOL TTY::  CloseConnection()
 {
	  // Disable event notification.  Using a NULL hWnd tells
	  // the COMM.DRV to disable future notifications.
	  Flush();
	  EnableCommNotification( COMDEV( npTTYInfo ), NULL, -1, -1 ) ;

	  // drop DTR
	  EscapeCommFunction( COMDEV( npTTYInfo ), CLRDTR ) ;

	  // close comm connection
	  CloseComm( COMDEV( npTTYInfo ) ) ;
	  CONNECTED( npTTYInfo ) = FALSE ;
	  return ( TRUE ) ;
 }

 int TTY::GetInputCount()
 {
  int nError;
  COMSTAT    ComStat ;
  if (!CONNECTED( npTTYInfo ))
  {
	parent->MessageBox("Connect to Com!!","Missing connection",MB_ICONINFORMATION|MB_OK	) ;
	return -1;
  }

 if ( nError = GetCommError( COMDEV( npTTYInfo ), &ComStat ))
 {
  if (DISPLAYERRORS( npTTYInfo ))
		{
		 DisplayError( nError ) ;
		 return -1;
		}
 }
 return	ComStat.cbInQue ;
}
//**************************************************************************
//  Function reads a block from the COM port and stuffs it into
//     the provided block.
//**************************************************************************
 int TTY::  ReadCommBlock(  LPSTR lpszBlock, int nMaxLength )
 {
  int nLength, nError ;
  if (!CONNECTED( npTTYInfo ))
  {
  parent->MessageBox("Connect to Com!!","Missing connection",
  MB_ICONINFORMATION|MB_OK	) ;
  return -1;
 }
 nLength = ReadComm( COMDEV( npTTYInfo ), lpszBlock, nMaxLength ) ;
 if (nLength < 0)
	  {
		 while (nError = GetCommError( COMDEV( npTTYInfo ), NULL ))
			 {
				if (DISPLAYERRORS( npTTYInfo ))
					{
						  DisplayError( nError ) ;
					}
			 }
	  }

	  return ( nLength ) ;
 }
 BOOL TTY::WriteCommBlock(  LPSTR lpBlock, int nLength )
 {
 int nError ;
 if (!CONNECTED( npTTYInfo ))
 {
  parent->MessageBox("Connect to Com!!","Missing connection",
							 MB_ICONINFORMATION|MB_OK	) ;
							 return false;
 }

 int res=WriteComm( COMDEV( npTTYInfo ), lpBlock, nLength ) ;
 if (res < 0)
	 {
	  while (nError = GetCommError( COMDEV( npTTYInfo ), NULL ))
		 {
			if (DISPLAYERRORS( npTTYInfo ))
				{
				  DisplayError( nError) ;
				}
		  }
	  return FALSE;
	 }
  return  TRUE ;
 }

void TTY::DisplayError( int nErr )
{
 char Errrors[][160]={
 "Hardware detected a break condition",
 "DSR(clear-to-send) timeout. While a character was being transmitted, CTS was low for the duration specified by the fCtsHold member of the COMSTAT structure",
 "Parallel device was not selected",
  "DSR(data-set-ready) timeout. While a character was being transmitted, DSR was low for the duration specified by the fDsrHold member of COMSTAT",
 "Hardware detected a framing error",
 "I/O error occurred during an attempt to communicate with a parallel device",
 "Requested mode is not supported, or the idComDev parameter is invalid. If set, CE_MODE is the only valid error",
 "Parallel device signaled that it is out of paper",
 "Character was not read from the hardware before the next character arrived. The character was lost",
 "Timeout occurred during an attempt to communicate with a parallel device",
 "RLSD(receive-line-signal-detect) timeout. While a character was being transmitted, RLSD was low for the duration specified by the fRlsdHold member of COMSTAT",
 "Receiving queue overflowed. There was either no room in the input queue or a character was received after the end-of-file character was received",
 "Hardware detected a parity error",
 "Transmission queue was full when a function attempted to queue a character"
							 };
{
if (nErr& CE_BREAK  )
	 parent->MessageBox( Errrors[0],"Communication error",MB_ICONINFORMATION|MB_OK	) ;
if (nErr& CE_CTSTO  )
	 parent->MessageBox( Errrors[1],"Communication error",MB_ICONINFORMATION|MB_OK	) ;
if (nErr& CE_DNS  )
	 parent->MessageBox( Errrors[2],"Communication error",MB_ICONINFORMATION|MB_OK	) ;
if (nErr& CE_DSRTO  )
	 parent->MessageBox( Errrors[3],"Communication error",MB_ICONINFORMATION|MB_OK	) ;
if (nErr& CE_FRAME  )
	 parent->MessageBox( Errrors[4],"Communication error",MB_ICONINFORMATION|MB_OK	) ;
if (nErr& CE_IOE  )
	 parent->MessageBox( Errrors[5],"Communication error",MB_ICONINFORMATION|MB_OK	) ;
if (nErr& CE_MODE  )
	 parent->MessageBox( Errrors[6],"Communication error",MB_ICONINFORMATION|MB_OK	) ;
if (nErr& CE_OOP  )
	 parent->MessageBox( Errrors[7],"Communication error",MB_ICONINFORMATION|MB_OK	) ;
if (nErr& CE_PTO  )
	 parent->MessageBox( Errrors[8],"Communication error",MB_ICONINFORMATION|MB_OK	) ;
if (nErr& CE_RLSDTO  )
	 parent->MessageBox( Errrors[9],"Communication error",MB_ICONINFORMATION|MB_OK	) ;
if (nErr& CE_RXOVER  )
	 parent->MessageBox( Errrors[10],"Communication error",MB_ICONINFORMATION|MB_OK	) ;
if (nErr& CE_RXPARITY  )
	 parent->MessageBox( Errrors[11],"Communication error",MB_ICONINFORMATION|MB_OK	) ;
if (nErr& CE_TXFULL  )
	 parent->MessageBox( Errrors[12],"Communication error",MB_ICONINFORMATION|MB_OK	) ;
}
}

