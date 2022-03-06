//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------
USEFORM("SearchSensorsForm.cpp", frmSearchSensors);
USEFORM("SelectAlgoritmForm.cpp", SelectAlgoritmDlg);
USEFORM("RectificationForm.cpp", frmRectification);
USEFORM("AlgoritmsForm.cpp", frmAlgoritms);
USEFORM("ChartSensorForm.cpp", frmChartSensor);
USEFORM("c:\embarcadero\studio\16.0\ObjRepos\EN\Cpp\okcancl1.CPP", OKBottomDlg);
USEFORM("about.cpp", AboutBox);
USEFORM("lptporttestingdlg.cpp", frmLptPortTesting);
USEFORM("MAIN.CPP", MainForm);
USEFORM("ChildWin.cpp", MDIChild);
USEFORM("DistillerForm.cpp", frmDistiller);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	Application->Initialize();
	Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(TfrmSearchSensors), &frmSearchSensors);
		Application->CreateForm(__classid(TfrmRectification), &frmRectification);
		Application->CreateForm(__classid(TfrmDistiller), &frmDistiller);
		Application->CreateForm(__classid(TSelectAlgoritmDlg), &SelectAlgoritmDlg);
		Application->CreateForm(__classid(TfrmLptPortTesting), &frmLptPortTesting);
		Application->Run();
	return 0;
}
//---------------------------------------------------------------------
