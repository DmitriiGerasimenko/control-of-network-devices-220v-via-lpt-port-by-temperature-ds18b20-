//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "About.h"
#include "DistillerForm.h"
#include "RectificationForm.h"
#include "ChartSensorForm.h"
#include "SearchSensorsForm.h"
#include "AlgoritmsForm.h"
#include "SelectAlgoritmForm.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------

__fastcall TMainForm::TMainForm(TComponent *Owner)
	: TForm(Owner)
{
	FOWSInterface = new TOWSInterface(true);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CreateChartForms()
{
	TMDIChild *Child;
	TfrmChartSensor * frmChartSensor;
	//
	int sensorsCount = (int)FOWSInterface->sensors.size();

	//ShowMessage( IntToStr(sensorsCount) );
	for ( int i = 0; i < sensorsCount; i ++ )
	{
		frmChartSensor = new TfrmChartSensor(Application);
		//
		FOWSInterface->sensors[i].guiHandle = frmChartSensor->Handle;
		frmChartSensor->Caption = FOWSInterface->sensors[i].sn;
		//ShowMessage( IntToStr(i) );

	//Child = new TMDIChild(Application);
	//Child->Caption = FOWSInterface->sensors[i].sn;
	}
	//ShowMessage( "End for..." );
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::HelpAbout1Execute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FileExit1Execute(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormActivate(TObject *Sender)
{
	//FHomeDistillerAlgoritm.load_from_xmlfile();
	//FHomeDistillerAlgoritm.multimap_to_txt();
	//return;

	//	TfrmSearchSensors *frmSearchSensors = new TfrmSearchSensors(this);
	//
	//	frmSearchSensors->FOWSInterface = FOWSInterface;
	//	frmSearchSensors->ShowModal();
	//	frmSearchSensors->Free();

	//frmSearchSensors->FOWSInterface = FOWSInterface;
	//frmSearchSensors->Show();
	//FOWSInterface->search_sensors();
	//
	FOWSInterface->search_sensors();
	//
	CreateChartForms();
	CreateAlgoritmsForm();
	//
	FOWSInterface->Start();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CreateAlgoritmsForm()
{
	frmAlgoritms = new TfrmAlgoritms(Application);
	FOWSInterface->guiHandle = frmAlgoritms->Handle;
	frmAlgoritms->Show();
}


