//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SelectAlgoritmForm.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TSelectAlgoritmDlg *SelectAlgoritmDlg;
//--------------------------------------------------------------------- 
__fastcall TSelectAlgoritmDlg::TSelectAlgoritmDlg(TComponent* AOwner)
	: TOKBottomDlg(AOwner)
{
}
//--------------------------------------------------------------------- 
void __fastcall TSelectAlgoritmDlg::HelpBtnClick(TObject *Sender)
{
	Application->HelpContext(HelpContext);
}
//--------------------------------------------------------------------- 
