#ifndef H_TTYTTAB
#define H_TTYTAB
#include "master.h"
#include <commdlg.h>
#include <string.h>
#define GWW_NPTTYINFO       0
#define ABOUTDLG_USEBITMAP  1
#define ATOM_TTYINFO       0x100
#define MAXROWS         25
#define MAXCOLS         80
#define MAXBLOCK        80
#define MAXLEN_TEMPSTR  81
#define RXQUEUE         4096
#define TXQUEUE         4096
#define CS_HIDE         0x00
#define CS_SHOW         0x01
#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04
#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13
#define GETHINST( hWnd )  ((HINSTANCE) GetWindowWord( hWnd, GWW_HINSTANCE ))

#define COMDEV( x ) (x . idComDev)
#define PORT( x )   (x . bPort)
#define CONNECTED( x ) (x . fConnected)
#define XONXOFF( x ) (x . fXonXoff)
#define LOCALECHO( x ) (x . fLocalEcho)
#define NEWLINE( x ) (x . fNewLine)
#define AUTOWRAP( x ) (x . fAutoWrap)
#define BYTESIZE( x ) (x . bByteSize)
#define FLOWCTRL( x ) (x . bFlowCtrl)
#define PARITY( x ) (x . bParity)
#define STOPBITS( x ) (x . bStopBits)
#define BAUDRATE( x ) (x . wBaudRate)
#define CURSORSTATE( x ) (x . wCursorState)
#define USECNRECEIVE( x ) (x . fUseCNReceive)
#define DISPLAYERRORS( x ) (x . fDisplayErrors)
#define SET_PROP( x, y, z )  SetProp( x, MAKEINTATOM( y ), z )
#define GET_PROP( x, y )     GetProp( x, MAKEINTATOM( y ) )
#define REMOVE_PROP( x, y )  RemoveProp( x, MAKEINTATOM( y ) )
// data structures
typedef struct tagTTYINFO
{
	  int     idComDev ;
	  BYTE    bPort  ;
	  BOOL    fConnected, fXonXoff, fLocalEcho, fNewLine, fAutoWrap,
				 fUseCNReceive, fDisplayErrors;
	  BYTE    bByteSize, bFlowCtrl, bParity, bStopBits ;
	  WORD    wBaudRate, wCursorState ;
	  int     xSize, ySize, xScroll, yScroll, xOffset, yOffset,
				 nColumn, nRow, xChar, yChar ;

} TTYINFO, *NPTTYINFO ;

class _export TTY
{
public:
HWND hWnd;
TWindow *parent;
TTYINFO   npTTYInfo ;
ofpstream out;
HFILE hFile;
long offset;
		TTY(TWindow *parent);
		~TTY();
		LRESULT CreateTTYInfo() ;
		BOOL DestroyTTYInfo( );
		BOOL OpenConnection( );
		BOOL SetupConnection( );
		BOOL CloseConnection();
		void Flush();
		int ReadCommBlock(  LPSTR lpszBlock, int nMaxLength );
		int GetInputCount();
		void EnableComm(short count);
		void DisplayError( int nErr );
		BOOL WriteCommBlock(  LPSTR lpBlock, int nLength );
		BOOL IsConnected()
		{
		 return CONNECTED( npTTYInfo );
		};
		void ClearEvent();
} ;
// macros ( for easier readability )
class _export __rtti  TOptionConnectDialog: public TDialog
{
	  public:
	  NPTTYINFO npTTYInfo ;
	  TComboBox *pPort;
 //COMBOBOX        IDD_PORTCB
	  TComboBox *pBaud;
 //COMBOBOX        IDD_BAUDCB
	  TComboBox *pDtBt;
 //COMBOBOX        IDD_DATABITSCB
	  TComboBox *pParity;
 //COMBOBOX        IDD_PARITYCB
	  TComboBox *pStop;
 //COMBOBOX        IDD_STOPBITSCB
	  TCheckBox *pDtr;
 //CONTROL         "DTR/DSR",IDD_DTRDSR,
	  TCheckBox *pRts;
 //    CONTROL         "RTS/CTS",IDD_RTSCTS
	  TCheckBox *pXon;
 //    CONTROL         "XON/XOFF",IDD_XONXOFF
	  TCheckBox *pLecho;
 //    CONTROL         "Local Echo",IDD_LOCALECHO
	  TCheckBox *pReciev;
 //    CONTROL         "Use CN_RECEIVE Notifications"
	  TCheckBox *pDErr;
 //    CONTROL         "Display Errors",IDD_DISPLAYERRORS
	 TButton *pOkButton;
	 TOptionConnectDialog(TWindow* , NPTTYINFO);
	 ~TOptionConnectDialog();
	 void SetupWindow();
	 BOOL  SettingsDlgInit();
	 void FillComboBox(TComboBox *pCB,int nIDString,WORD  *npTable, WORD wTableLen,
							 WORD wCurrentSetting );
	 BOOL SettingsDlgTerm();
	 void MyOk();
	 DECLARE_RESPONSE_TABLE(TOptionConnectDialog);
};
#endif
