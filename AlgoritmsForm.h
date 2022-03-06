//---------------------------------------------------------------------------

#ifndef AlgoritmsFormH
#define AlgoritmsFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <map>
#include <set>
#include "owsinterface.h"
//---------------------------------------------------------------------------
class TfrmAlgoritms : public TForm
{
__published:	// IDE-managed Components
	TStatusBar *StatusBar1;
	TPanel *Panel1;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TPageControl *ChartPageControl;
	TTabSheet *CommonTabSheet;
	TChart *ChartSensors;
	TActionList *ActionList1;
	TImageList *ImageList1;
	TAction *StartAlgoritmAction;
	TAction *StopAlgoritmAction;
	TToolButton *ToolButton3;
	TToolButton *ToolButton4;
	TAction *PauseAlgoritmAction;
	TPageControl *PageControl1;
	TSplitter *Splitter1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TMemo *AlgoritmMemo;
	TTabSheet *TabSheet3;
	TChart *Chart1;
	TMainMenu *MainMenu1;
	TMenuItem *Algoritm1;
	TMenuItem *StartAlgoritmAction1;
	TMenuItem *Stopalgoritm1;
	TMenuItem *N1;
	TMenuItem *Pausealgoritm1;
	TMenuItem *Setting1;
	TAction *LptPortTestingAction;
	TMenuItem *Lptporttest1;
	void __fastcall StartAlgoritmActionExecute(TObject *Sender);
	void __fastcall StopAlgoritmActionExecute(TObject *Sender);
	void __fastcall LptPortTestingActionExecute(TObject *Sender);
private:	// User declarations

	bool AlgoritmRunning;
	void __fastcall StartAlgoritm();
	void __fastcall StopAlgoritm();
	void __fastcall PauseAlgoritm();

	//TOWSensor *FOWSensor;
	//std::map<AnsiString, TOWSensor*> mapSensors;
	std::map<AnsiString, TFastLineSeries*> mapChartSensors;
	std::multimap<AnsiString, TOWEventTag> alrgoritm;
	//
	//TLptPort FLptPort;

	TDistillerAlgoritm FDistillerAlgoritm;
	//std::set<AnsiString> setSensors;

	void __fastcall CreateGroupChartPageControl(const TOWSensor &sensor);
	void __fastcall CreatePersonalChartPageControl(const TOWSensor &sensor);


public:		// User declarations
	__fastcall TfrmAlgoritms(TComponent* Owner);

	void __fastcall UM_update_gui_form(TMessage &Message);

BEGIN_MESSAGE_MAP
  MESSAGE_HANDLER(WM_COPYDATA, TMessage, UM_update_gui_form)
END_MESSAGE_MAP(TForm)

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAlgoritms *frmAlgoritms;
//---------------------------------------------------------------------------
#endif
