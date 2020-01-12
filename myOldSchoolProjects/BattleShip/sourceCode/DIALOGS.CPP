#include "dialogs.h"
#include "shipapp.rh"
#include"view.h"
#include"game.h"
//******************** TInfoDialog *****************************************
// Dialog box for options :
//           Show field of information
//           Hide field of information
//**************************************************************************
DEFINE_RESPONSE_TABLE1(TInfoDialog, TDialog)
EV_COMMAND ( IDOK, CmOk),
END_RESPONSE_TABLE;
//Constructor
TInfoDialog::TInfoDialog(TWindow *Parent,int *Option) :
 TDialog(Parent, IDD_INFO)
{
 pOptM=new  TRadioButton(this,IDC_SHOWINFO);
 pOptA=new  TRadioButton(this,IDC_HIDEINFO);
 Info=Option;
}
//Destructor
TInfoDialog::~TInfoDialog()
{
 delete pOptA;
 delete pOptM;
}
// Function to creating Dialog box
void TInfoDialog::SetupWindow()
{
 TDialog::SetupWindow();

 if( !(*Info))
	 pOptM->SetCheck (BF_CHECKED);
 else
	 if ( *Info==1)
	 pOptA->SetCheck(BF_CHECKED);
}
//Function involved if pressed button Ok in dialog box
void TInfoDialog::CmOk()
{
if (pOptM->GetCheck()& BF_CHECKED)
	 *Info=0;

else
	if (pOptA->GetCheck()& BF_CHECKED)
	*Info=1;
	TDialog::CmOk();
}

//*********************** TOptionDialog *************************************
// Dialog box for options :
//           Player with player
//           Player with computer
//           Computer with computer
//**************************************************************************

DEFINE_RESPONSE_TABLE1(TOptionDialog, TDialog)
EV_COMMAND ( IDOK, CmOk),
END_RESPONSE_TABLE;
// Constructor
TOptionDialog::TOptionDialog(TWindow *Parent,int *pOpt)
				  :TDialog(Parent, IDD_KIND)
{
 pOptM=new  TRadioButton(this,IDC_PLAYER);
 pOptA=new  TRadioButton(this,IDC_PLAYCOM);
 pOptS=new  TRadioButton(this,IDC_COMP);
 m_pOpt=pOpt;
}
// Destructor
TOptionDialog::~TOptionDialog()
{
 delete pOptA;
 delete pOptM;
 delete pOptS;
}
// Function to creating dialog box
void TOptionDialog::SetupWindow()
{
 TDialog::SetupWindow();
 if( !(*m_pOpt))
	 pOptM->SetCheck (BF_CHECKED);
 else
	 if ( *m_pOpt==1)
	 pOptA->SetCheck(BF_CHECKED);
	 else
	  if ( *m_pOpt==2)
			pOptS->SetCheck(BF_CHECKED);
}
//Function involved if pressed button Ok in dialog box
void TOptionDialog::CmOk()
{
if (pOptM->GetCheck()& BF_CHECKED)
	 {*m_pOpt=0;
	 TGameView::whoPlay=0;}
else
	 if(pOptA->GetCheck()& BF_CHECKED)
		{ *m_pOpt=1;
		TGameView::whoPlay=1;}
	 else
		 if (pOptS->GetCheck()& BF_CHECKED)
			{ *m_pOpt=2;
			TGameView::whoPlay=2;}

  TDialog::CmOk();
}


