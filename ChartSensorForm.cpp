//---------------------------------------------------------------------------

#include <vcl.h>
#include <dos.h>
#pragma hdrstop

#include "ChartSensorForm.h"
#include "owsinterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmChartSensor *frmChartSensor;
//---------------------------------------------------------------------------
__fastcall TfrmChartSensor::TfrmChartSensor(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmChartSensor::UM_update_gui_form(TMessage &Message)
{
	//MessageBeep(MB_OK);
	//ShowMessage("111");
	//return;
    //MessageBeep( MB_ICONERROR );
	//
	COPYDATASTRUCT *pcds = (COPYDATASTRUCT*) Message.LParam;
	//TOWSensor *pSensor = (TOWSensor*)pcds->lpData;
	TOWSensor Sensor( (TOWSensor*)pcds->lpData );
	//
	//AnsiString tmp =  "SN: " + pSensor->sn + " Value: " + pSensor->value;
	//f.sprintf("%.4f", pSensor->value);
	//ValuePanel->Caption = f;
	//
	//----------------------------------------
	//
	// CHART
	//
	Chart1->Title->Text->Text = Sensor.value;
	//
	//
	//TDateTime dt;
	//unsigned short hour, min, sec, msec;
	//AnsiString dtstring, buffer;

	//dt = Now();
	//dt.DecodeTime(&hour, &min, &sec, &msec);
	//dtstring = dt.TimeString();
	//buffer.sprintf("%.3d", msec);
	//dtstring += buffer;

	//
	//
	AnsiString time;
	struct time t;
	gettime(&t);
	time.sprintf("%02d:%02d:%02d", t.ti_min, t.ti_min, t.ti_sec); //, t.ti_hund);
	//time.sprintf("%02d:%02d.%02d\n", t.ti_min, t.ti_sec); //, t.ti_hund);
	//
	Series1->AddY(Sensor.value, time );
	Series1->Title = Sensor.value;

}
