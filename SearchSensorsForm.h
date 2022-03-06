//---------------------------------------------------------------------------

#ifndef SearchSensorsFormH
#define SearchSensorsFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "owsinterface.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TfrmSearchSensors : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *SensorPanel;
	TPanel *ComportsPanel;
	TButton *Button1;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations

public:		// User declarations
	__fastcall TfrmSearchSensors(TComponent* Owner);
	TOWSInterface *FOWSInterface;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSearchSensors *frmSearchSensors;
//---------------------------------------------------------------------------
#endif
