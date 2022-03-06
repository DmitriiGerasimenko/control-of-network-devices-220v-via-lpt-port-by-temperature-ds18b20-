#ifndef owsinterfaceH
#define owsinterfaceH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <vector>
#include <bitset>
#include <map>
//---------------------------------------------------------------------------
#include "OWire_Module.hpp"
//---------------------------------------------------------------------------
// пользовательские сообщения – это WM_USER + некая величина
#define  UM_UPDATE_GUI_FORM_MESSAGE (WM_USER + 1001)
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void commonLogFile(const AnsiString &FileName,  const AnsiString &message);
unsigned search_sensors_in_port(const id_port);
//---------------------------------------------------------------------------
class TOWComport
{
	private:

	public:
		AnsiString	name;
		int			id;
		int			handle;
		int 		preparation;
		//
		bool debug_log_output;

	public:
		void _debug(const AnsiString &message);

	public:
		void Preparation();

		friend ostream& operator<<(ostream& os, const TOWComport& port);

	public:
		TOWComport();
		TOWComport(AnsiString NAME, int ID, int HANDLE);
		~TOWComport();
};
//---------------------------------------------------------------------------
//
//    Event atom
//
//---------------------------------------------------------------------------
//
class TOWEventTag
{
	public:
		AnsiString sn;
		float	value;
		int		lptport;
		int		upper;
		int		down;

	public:

		TOWEventTag();
		TOWEventTag(const TOWEventTag *EventRecord);
		~TOWEventTag() {};
};

//---------------------------------------------------------------------------
class TOWSensor
{
	public:

		OW_SN	   	ow_sn;
		OW_RAM 		ow_ram;
		//
		TOWComport comport;
		AnsiString	type;
		AnsiString	sn;
		//
		float 		value;
		//std::vector<double> data;
		//typedef std::vector<double>::iterator itdata;
		//
		friend ostream& operator<<(std::ostream& os, const TOWSensor& ows);
		//----------------------------------------------------------------
		//
		//  GUI
		//
		float min_gui, max_gui;
		AnsiString	Caption;
		//----------------------------------------------------------------
		//
		//  Alarm section.
		//
		//----------------------------------------------------------------
		//
		std::vector<TOWEventTag> Events;
		//
		void load_events_from_xml(const AnsiString &XmlFileName) {};
		//float ll,l,h,hh;
		//float min, max;
		//UnicodeString _alarm_file_name;
		//
		//bool check_min_alarm();
		//bool check_max_alarm();
		//bool check_alarms();
		//void play_sound_alarms();

	public:
	//---------------------------------------------------------------------
	bool debug_log_output;
	bool measure_log_output;
	bool measure_database_output;
	bool measure_common_database_output;
	bool measure_common_txt_output;
	//---------------------------------------------------------------------
	//void saveSensorInfoToTxtFile();
	//
	//    I/O sections
	//
	void save_measure_to_log_file();
	void save_measure_to_database(TFDCommand *fdc);
	void create_table_sensor(TFDCommand *fdc);
	void save_measure_to_common_database_table(TFDCommand *fdc);
	void save_measure_to_common_log_file();
	//---------------------------------------------------------------------
	// Ini section
	//
	void _debug(const AnsiString &message);
	AnsiString get_ini_file();
	void save_setting_to_ini_file();
	bool load_setting_from_ini_file();
	//---------------------------------------------------------------------
	//
	//  GUI section
	//
	HWND guiHandle;
	//
	//void gui_interface_update(HWND hwnd);
	//---------------------------------------------------------------------
	//void sendmessage_sensor_to_mdichildform(TOWSensor &ows);
	void update_gui_form(HWND hwnd);
	void update_common_gui_form(HWND hwnd);
	//void test(HWND hwnd);
	//---------------------------------------------------------------------
	//
	//  I/O
	//
	//void update_sensor(int _id_port);
	void update_value();
	//
	TOWSensor();
	TOWSensor(const TOWSensor * Sensor);
	//
	~TOWSensor() {};
};
//---------------------------------------------------------------------------
class TOWSInterface : public TThread
{
private:
	bool	debug_log_output;
	int		Timer;

public:
	HWND	guiHandle;

public:
	//-----------------------------------------------------------------
	std::vector<TOWSensor> sensors;
	std::vector<TOWComport> comports;
	//
	typedef std::vector<TOWComport>::iterator itcp;
	typedef std::vector<TOWSensor>::iterator its;
	//
	void __fastcall search_sensors();
	int __fastcall search_sensors(TOWComport &comport);
	//
	void __fastcall send_message_to_gui_form(TOWSensor *ows, const HWND hwnd);
	void __fastcall update_algoritms_gui_forms();
	void __fastcall update_sensors_gui_forms();
//	void __fastcall update_gui();
	//------------------------------------------------------------------
	//
	//
	//
	//
	void __fastcall _debug(const AnsiString &message);

private:

protected:
	void __fastcall Execute();
public:

	__fastcall TOWSInterface(bool CreateSuspended);
	__fastcall ~TOWSInterface();

};

//---------------------------------------------------------------------------
class TDistillerAlgoritm
{
	private:
		AnsiString FAlgoritmXMLFileName;
		//TXMLDocument *XMLDocument;

	public:
		//
		//
		void load_from_xmlfile();
		//
		std::multimap<AnsiString, TOWEventTag> alrgoritm;
		//TLptPort FLptPort;

	public:
		//
		//
		void _debug(const AnsiString &message);
		void multimap_to_txt();
		//
		//AnsiString start_algoritm(const TOWSensor &owsensor);
		//TOWEventTag & start_algoritm(const TOWSensor &owsensor);
		void start_algoritm(const TOWSensor &owsensor);
		bool do_event(const TOWEventTag &EventTag, int command);
		//
		void stop_algoritm();

	public:
		TDistillerAlgoritm();
		~TDistillerAlgoritm();
};
//---------------------------------------------------------------------------
#endif
