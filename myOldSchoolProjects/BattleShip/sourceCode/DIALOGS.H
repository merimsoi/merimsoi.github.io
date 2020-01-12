#ifndef H_DIALOGS     // Sentry, use file only if it's not already included.
 #define H_DIALOGS
#include "master.h"
///*********************** TOptionDialog *************************************
// Dialog box for options :
//           Player with player
//           Player with computer
//           Computer with computer
//***************************************************************************
class   TOptionDialog : public TDialog
{
 public:

	int *m_pOpt;
	TRadioButton * pOptA;
	TRadioButton * pOptM;
	TRadioButton * pOptS;
	//constructor
	TOptionDialog(TWindow *Parent,int*);
	//destructor
	~TOptionDialog();

	void CmOk();
	virtual void SetupWindow();
	DECLARE_RESPONSE_TABLE(TOptionDialog);
};
//********************** TInfoDialog ****************************************
// Dialog box for options :
//           Show field of information
//           Hide field of information
//***************************************************************************
class   TInfoDialog : public TDialog
{
 public:
 TRadioButton * pOptA;
 TRadioButton * pOptM;
 int* Info;
 //constructor
 TInfoDialog(TWindow *Parent,int* );
 //destructor
 ~TInfoDialog();

 void CmOk();
 virtual void SetupWindow();
 DECLARE_RESPONSE_TABLE(TInfoDialog);
};

#endif
