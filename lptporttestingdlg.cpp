//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "lptporttestingdlg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmLptPortTesting *frmLptPortTesting;
//---------------------------------------------------------------------------
__fastcall TfrmLptPortTesting::TfrmLptPortTesting(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmLptPortTesting::SetAllPinsBtnClick(TObject *Sender)
{
	FLptPort.Set();
    UpdateGUI();
}
//---------------------------------------------------------------------------
void __fastcall TfrmLptPortTesting::ResetAllPinsClick(TObject *Sender)
{
	FLptPort.Reset();
	UpdateGUI();
}
//---------------------------------------------------------------------------
void __fastcall TfrmLptPortTesting::UpdateGUI()
{
	for( int iPinIndex =0; iPinIndex < LptPinsCheckBox->Count; iPinIndex++)
	{
	LptPinsCheckBox->Checked[iPinIndex] = FLptPort.Test(iPinIndex) ? true : false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmLptPortTesting::LptPinsCheckBoxClickCheck(TObject *Sender)
{
	int iPinIndex = LptPinsCheckBox->ItemIndex;
	LptPinsCheckBox->Checked[iPinIndex] ? FLptPort.Set(iPinIndex) : FLptPort.Reset(iPinIndex);
}
//---------------------------------------------------------------------------
void __fastcall TfrmLptPortTesting::FormActivate(TObject *Sender)
{
	AdressLo_SpinEdit->Value = FLptPort.adress_lo;
	AdressHi_SpinEdit->Value = FLptPort.adress_hi;
}
//---------------------------------------------------------------------------

void __fastcall TfrmLptPortTesting::AdressLo_SpinEditChange(TObject *Sender)
{
	FLptPort.adress_lo = AdressLo_SpinEdit->Value;
}
//---------------------------------------------------------------------------

void __fastcall TfrmLptPortTesting::AdressHi_SpinEditChange(TObject *Sender)
{
	FLptPort.adress_hi = AdressHi_SpinEdit->Value;
}
//---------------------------------------------------------------------------

