//---------------------------------------------------------------------------

#ifndef ChartSensorFormH
#define ChartSensorFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>
//---------------------------------------------------------------------------
class TfrmChartSensor : public TForm
{
__published:	// IDE-managed Components
	TChart *Chart1;
	TFastLineSeries *Series1;
private:	// User declarations
public:		// User declarations
	__fastcall TfrmChartSensor(TComponent* Owner);
	void __fastcall UM_update_gui_form(TMessage &Message);

BEGIN_MESSAGE_MAP
  MESSAGE_HANDLER(WM_COPYDATA, TMessage, UM_update_gui_form)
END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmChartSensor *frmChartSensor;
//---------------------------------------------------------------------------
#endif
