//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SearchSensorsForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSearchSensors *frmSearchSensors;
//---------------------------------------------------------------------------
__fastcall TfrmSearchSensors::TfrmSearchSensors(TComponent* Owner)
	: TForm(Owner)
{
	FOWSInterface = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearchSensors::FormActivate(TObject *Sender)
{
	if (FOWSInterface)
	{
		FOWSInterface->search_sensors();
		//
		//
		//AnsiString output;

		//output += "COM pors : " + Sysutils::IntToStr((int)FOWSInterface->comports.size());
		//output += "\n";
		//output += "Sensors found : " + Sysutils::IntToStr((int)FOWSInterface->sensors.size());
		//
		//ShowMessage( output );
		//
		ComportsPanel->Caption = IntToStr((int)FOWSInterface->comports.size());
		SensorPanel->Caption = IntToStr((int)FOWSInterface->sensors.size());
		//
		//SensorsInformationGrid->Cells[0][0] = "0";
		//SensorsInformationGrid->Cells[1][0] = "1";
		//SensorsInformationGrid->Cells[2][0] = "2";
		/*
		SensorsInformationGrid->RowCount = (int)FOWSInterface->sensors.size();
		//
		for ( int i = 0; i < FOWSInterface->sensors.size(); i++ )
		{
			SensorsInformationGrid->Cells[0][i] = FOWSInterface->sensors[i].comport.name;
			SensorsInformationGrid->Cells[1][i] = FOWSInterface->sensors[i].type;
			SensorsInformationGrid->Cells[2][i] = FOWSInterface->sensors[i].sn;
		}
		*/
	}

}
//---------------------------------------------------------------------------
void __fastcall TfrmSearchSensors::Button1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
