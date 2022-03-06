//---------------------------------------------------------------------------

#ifndef lptporttestingdlgH
#define lptporttestingdlgH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ButtonGroup.hpp>
#include <Vcl.CheckLst.hpp>
#include "lptport.h"
#include <Vcl.Samples.Spin.hpp>
//---------------------------------------------------------------------------
class TfrmLptPortTesting : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TCheckListBox *LptPinsCheckBox;
	TButton *ButtonClose;
	TButton *SetAllPinsBtn;
	TButton *ResetAllPins;
	TGroupBox *GroupBox2;
	TSpinEdit *AdressLo_SpinEdit;
	TLabel *Label1;
	TLabel *Label2;
	TSpinEdit *AdressHi_SpinEdit;
	void __fastcall SetAllPinsBtnClick(TObject *Sender);
	void __fastcall ResetAllPinsClick(TObject *Sender);
	void __fastcall LptPinsCheckBoxClickCheck(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall AdressLo_SpinEditChange(TObject *Sender);
	void __fastcall AdressHi_SpinEditChange(TObject *Sender);
private:	// User declarations
	TLptPort FLptPort;
	void __fastcall UpdateGUI();
public:		// User declarations
	__fastcall TfrmLptPortTesting(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmLptPortTesting *frmLptPortTesting;
//---------------------------------------------------------------------------
#endif
