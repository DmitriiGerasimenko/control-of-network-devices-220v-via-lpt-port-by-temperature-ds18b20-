//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AlgoritmsForm.h"
#include "lptporttestingdlg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAlgoritms *frmAlgoritms;
//---------------------------------------------------------------------------
__fastcall TfrmAlgoritms::TfrmAlgoritms(TComponent* Owner)
	: TForm(Owner)
{
	FDistillerAlgoritm.load_from_xmlfile();
	FDistillerAlgoritm.multimap_to_txt();
	//
	AlgoritmRunning = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlgoritms::UM_update_gui_form(TMessage &Message)
{
	//MessageBeep(MB_OK);
	//ShowMessage("111");
	//return;
	//MessageBeep( MB_ICONERROR );
	//
	COPYDATASTRUCT *pcds = (COPYDATASTRUCT*) Message.LParam;
	TOWSensor *ptr_sensor = (TOWSensor*)pcds->lpData;
	//
	int count_sensors = (int)pcds->dwData;
	std::vector<TOWSensor> test(count_sensors); //(pcds->lpData, pcds->lpData+10);
	std::copy ( ptr_sensor, ptr_sensor + count_sensors, test.begin() );
	//
	for ( std::vector<TOWSensor>::iterator it = test.begin(); it != test.end(); ++it)
	{
		//send_message_to_gui_form( &*itows, guiHandle);
		AnsiString buf;
		buf = it->sn + "<>" + it->type + "<>" + it->value + "<>"  + it->comport.name;
		AlgoritmMemo->Lines->Add(buf);
	}
	//

	/// первичное добавление
	if (!mapChartSensors.size())
	{
		for ( std::vector<TOWSensor>::iterator it = test.begin(); it != test.end(); ++it)
		{
			if (!mapChartSensors.count(it->sn)) // (mapSensors.find(FOWSensor->sn) != setSensors.end()) {
			{
				TFastLineSeries * Series = new TFastLineSeries(ChartSensors);
				Series->Pen->Width = 2;
				Series->Pen->Style = psDash;
				Series->Title = it->sn;
				//
				ChartSensors->AddSeries(Series);
				mapChartSensors[it->sn] = Series;
				//
			}
			//
			//TFastLineSeries * Series = mapSensors[sensor.sn];
		}
	} else
		{
			for ( std::vector<TOWSensor>::iterator it = test.begin(); it != test.end(); ++it)
			{
				if (mapChartSensors.count(it->sn))
				{
					mapChartSensors[it->sn]->AddY(it->value, "");
				}
			}

		}



	//

	/*
	if ( guiHandle != NULL )
	{
		COPYDATASTRUCT cd;              //
		memset(&cd, 0, sizeof(COPYDATASTRUCT)); //
		//
		cd.dwData = sensors.size();
		cd.cbData = sensors.size() * sizeof(TOWSensor);
		cd.lpData = &sensors[0];
		//
		SendMessage(guiHandle, WM_COPYDATA, (WPARAM)guiHandle, (LPARAM) (LPVOID) &cd);

	*/
	return;
	//////////////////////////////
	//---------------------------------------------------------------------
	// Draw groupe chart
	//---------------------------------------------------------------------
	//
	//CreateGroupChartPageControl(sensor);
	//
	//---------------------------------------------------------------------
	// Draw personal chart
	//---------------------------------------------------------------------
	//
	//CreatePersonalChartPageControl(const TOWSensor &sensor)
	//----------------------------------------------------------------------
	//  AI. Algoritms
	//----------------------------------------------------------------------
	//if (AlgoritmRunning)
	//	FDistillerAlgoritm.start_algoritm( sensor );

	//AnsiString algoritm_result;
	//Memo1->Lines->Add(algoritm_result );


	//int check_parametrs_sensor(const TOWSensor &owsensor)

	//check_parametrs_sensor()

	//Series->AddY(sensor.value, "");
	/*
	if (!mapSensors.count(FOWSensor->sn)) // (mapSensors.find(FOWSensor->sn) != setSensors.end()) {
	{
		Series = new TFastLineSeries(ChartSensors);
		Series->Pen->Width = 2;
		Series->Pen->Style = psDash;
		Series->Title = FOWSensor->sn;
		//
		ChartSensors->Axes->Left->Minimum = 0.0;
		ChartSensors->Axes->Left->Maximum = 100.0;
		ChartSensors->AddSeries(Series);
		mapSensors[FOWSensor->sn] = Series;
	}
		else
		{
			Series = mapSensors[FOWSensor->sn];
		}
	//
	Series->AddY(FOWSensor->value, "");
	*/
	//
	//
	//
	//
	//
	//AnsiString tmp =  "SN: " + pSensor->sn + " Value: " + pSensor->value;
	//AnsiString f;
	//f.sprintf("%.4f", pSensor->value);
	//ValuePanel->Caption = f;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlgoritms::CreateGroupChartPageControl(const TOWSensor &sensor)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlgoritms::CreatePersonalChartPageControl(const TOWSensor &sensor)
{
/*
	if (chartSensors.count(sensor.sn)) // (mapSensors.find(FOWSensor->sn) != setSensors.end()) {
	{
		TFastLineSeries * Series = new TFastLineSeries(ChartSensors);
		Series->Pen->Width = 2;
		Series->Pen->Style = psDash;
		Series->Title = sensor.sn;
		//
		//ChartSensors->Axes->Left->Minimum = 0.0;
		//ChartSensors->Axes->Left->Maximum = 100.0;
		ChartSensors->AddSeries(Series);
		chartSensors[sensor.sn] = Series;
	}

	//
	TTabSheet *chartSheet = new TTabSheet(this);
	chartSheet->Parent = this;
	chartSheet->PageControl = ChartPageControl;
	chartSheet->Caption = sensor.sn;
	chartSheet->Align = alClient;
	chartSheet->BorderWidth = 10;
	chartSheet->Enabled = false;
	//

	TChart *Chart = new TChart(this);
	Chart->Parent = chartSheet;
	Chart->Align = alClient;
	Chart->View3D = false;
	Chart->LeftAxis->Minimum = 0;
	Chart->LeftAxis->Maximum = 100;
	Chart->LeftAxis->Automatic = false;

	//
	ChartPageControl->ActivePageIndex = 0;
	//
	//Chart->AddSeries(chartSensors[sensor.sn]);
	//
*/
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlgoritms::StartAlgoritm()
{
	AlgoritmRunning = true;
	AlgoritmMemo->Lines->Add( Now().DateTimeString() + " Start algoritm...");
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlgoritms::StopAlgoritm()
{
	AlgoritmRunning = false;
	AlgoritmMemo->Lines->Add( Now().DateTimeString() + " Stop algoritm...");
	FDistillerAlgoritm.stop_algoritm();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlgoritms::PauseAlgoritm()
{
	AlgoritmRunning = false;
	AlgoritmMemo->Lines->Add( Now().DateTimeString() + " Paused algoritm...");
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlgoritms::StartAlgoritmActionExecute(TObject *Sender)
{
	StartAlgoritm();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlgoritms::StopAlgoritmActionExecute(TObject *Sender)
{
	StopAlgoritm();
}
//---------------------------------------------------------------------------


void __fastcall TfrmAlgoritms::LptPortTestingActionExecute(TObject *Sender)
{
    frmLptPortTesting->ShowModal();
}
//---------------------------------------------------------------------------

