//----------------------------------------------------------------------------
#ifndef MainH
#define MainH
//----------------------------------------------------------------------------
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Winapi.Windows.hpp>
#include <System.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.ToolWin.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include "ChildWin.h"
#include "owsinterface.h"
#include <Xml.Win.msxmldom.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>

//----------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Window1;
	TMenuItem *Help1;
	TMenuItem *N1;
	TMenuItem *FileExitItem;
	TMenuItem *WindowCascadeItem;
	TMenuItem *WindowTileItem;
	TMenuItem *WindowArrangeItem;
	TMenuItem *HelpAboutItem;
	TMenuItem *FileSaveAsItem;
	TMenuItem *WindowMinimizeItem;
	TStatusBar *StatusBar;
	TActionList *ActionList1;
	TWindowCascade *WindowCascade1;
	TWindowTileHorizontal *WindowTileHorizontal1;
	TWindowArrange *WindowArrangeAll1;
	TWindowMinimizeAll *WindowMinimizeAll1;
	TAction *HelpAbout1;
	TWindowTileVertical *WindowTileVertical1;
	TMenuItem *WindowTileItem2;
	TToolBar *ToolBar2;
	TToolButton *ToolButton8;
	TToolButton *ToolButton10;
	TToolButton *ToolButton11;
	TImageList *ImageList1;
	void __fastcall HelpAbout1Execute(TObject *Sender);
	void __fastcall FileExit1Execute(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
private:

	void __fastcall CreateChartForms();
	void __fastcall CreateAlgoritmsForm();
	//
	TOWSInterface *FOWSInterface;
	TDistillerAlgoritm FDistillerAlgoritm;
public:
	virtual __fastcall TMainForm(TComponent *Owner);
	//
};
//----------------------------------------------------------------------------
extern TMainForm *MainForm;
extern TMDIChild *__fastcall MDIChildCreate(void);
//----------------------------------------------------------------------------
#endif
