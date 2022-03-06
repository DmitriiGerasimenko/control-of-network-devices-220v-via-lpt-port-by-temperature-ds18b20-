
//---------------------------------------------------------------------------

#include <vcl.h>
#include <System.hpp>
#include <Xml.Win.msxmldom.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>

#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <iterator>
#include <iostream>

#include <ctime>
#include <stdio.h>
#include <dos.h>
#include <mmsystem.h>

#pragma hdrstop

#include "owsinterface.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TOWSInterface::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
//
//
//		Common
//
//---------------------------------------------------------------------------
void commonLogFile(const AnsiString &FileName,  const AnsiString &message)
{
	std::ofstream logfile(FileName.c_str(), std::ios_base::out | std::ios_base::app);
	if ( logfile.is_open() )
	{
		TDateTime dt;
		unsigned short hour, min, sec, msec;
		AnsiString dtstring, buffer;

		dt = Now();
		dt.DecodeTime(&hour, &min, &sec, &msec);
		dtstring = dt.DateTimeString();
		buffer.sprintf("%.3d", msec);

//		logfile << "[" << dtstring.c_str() << "." << std::cout.fill('0') << std::cout.width(3) << msec << "]" << std::endl;
//		logfile << "[" << dtstring.c_str() << "." << logfile.fill('0') << logfile.width(3) << msec << "]" << std::endl;
		//logfile << "[" ;
		logfile << dtstring.c_str() << "." << buffer.c_str();
		//logfile << "]";
		logfile << '\t' << message.c_str();
		logfile << std::endl;
		logfile.close();
	}
}
//---------------------------------------------------------------------------
//
//
//
//	COM port
//
//
//---------------------------------------------------------------------------
ostream& operator<<(ostream& os, const TOWComport& port)
{
	TDateTime dt;
	unsigned short hour, min, sec, msec;
	AnsiString dtstring;

	dt = Now();
	dt.DecodeTime(&hour, &min, &sec, &msec);
	dtstring = dt.DateTimeString();

	os << "[" << dtstring.c_str() << "." << msec << "] - ";
	os << "[Name: " << port.name.c_str() << ", ";
	os << "ID: " << port.id << ", ";
	os << "Handle: " << port.id << ", ";
	os << "Preparation: " << port.preparation << " ";
	return os;
}
//------------------------------------------------------------------------
TOWComport::TOWComport():
	name(""),
	id(0),
	handle(0),
	debug_log_output(false)
{

}
//---------------------------------------------------------------------------
TOWComport::TOWComport(AnsiString NAME, int ID, int HANDLE) :
	name(NAME),
	id(ID),
	handle(HANDLE),
	debug_log_output(false)
{
}
//---------------------------------------------------------------------------
TOWComport::~TOWComport()
{

}
//-----------------------------------------------------------------------
void TOWComport::_debug(const AnsiString &message)
{
	if (debug_log_output)
	{
		AnsiString FileName = "_" + name +  ".debug";
		commonLogFile(FileName, message);
	}
}
//---------------------------------------------------------------------------
void TOWComport::Preparation()
{
	_debug("void TOWComport::Preparation() [INPUT]");
	if ( OW_SkipROM(id) ) //
	{
		//ShowMessage("2");
		if ( OW_ConvertT(id) )
		{
			//ShowMessage("3");

			_debug("void TOWComport::Preparation() [OUTPUT] [true]");
			preparation = true;
			return;
		}
	}
	//
	_debug("void TOWComport::Preparation() [OUTPUT] [false]");
	//
	preparation = false;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//
//
//
//		PORTS Interface
//
//

__fastcall TOWSInterface::TOWSInterface(bool CreateSuspended) : TThread(CreateSuspended)
{
	debug_log_output = false;
	Timer = 750; // Sleep(Timer);
	guiHandle = NULL;
	//
	//FreeOnTerminate = true;
}
//---------------------------------------------------------------------------
__fastcall TOWSInterface::~TOWSInterface()
{

}
//-----------------------------------------------------------------------
void __fastcall TOWSInterface::_debug(const AnsiString &message)
{
	if (debug_log_output)
	{
		AnsiString FileName = "comports.debug";
		commonLogFile(FileName, message);
	}
}
//---------------------------------------------------------------------------
void __fastcall TOWSInterface::search_sensors()
{
	_debug("void __fastcall TOWSInterface::search_sensors() [INPUT]");
	//
	TOWComport comport;
	//
	for ( comport.id = 1; comport.id <= 30; comport.id ++)
	{
		comport.name = "COM" + IntToStr(comport.id);
		comport.handle = OW_OpenPort(comport.name, comport.id);
		//
		AnsiString tmp = "comport.name = " + comport.name + ", " +
						"comport.id = " + IntToStr(comport.id) + ", " +
						"comport.handle = " + comport.handle;
		_debug(tmp);
		//
		if ( comport.handle != NULL )
		{
			if ( search_sensors(comport) > 0 )
			{
				//
				comports.push_back(comport);
			}
		}
	}
	//MessageDlg( comports.size(), mtError, TMsgDlgButtons() << mbOK, 0);
	_debug("void __fastcall TOWSInterface::search_sensors() [OUTPUT]");
}
//---------------------------------------------------------------------------
int __fastcall TOWSInterface::search_sensors(TOWComport &comport)
{
	_debug("TOWComPort::SearchSensors() [INPUT]");
	//
	std::vector<TOWSensor> local_sensors;
	//
	// Функция ищет устройства 1Wire в сети. Если не находит, то возвращает NULL
	if ( OW_SearchROM_Reset() )
	{
		_debug("TOWComPort::SearchSensors() [1]");
		while(true)
		{
			_debug("TOWComPort::SearchSensors() [2]");
			TOWSensor sensor;
			// ищем по очереди все устройства 1Wire в сети
			if ( OW_SearchROM_Enum(sensor.ow_sn, comport.id) != NULL)
			{
				_debug("TOWComPort::SearchSensors() [3]");
				switch(sensor.ow_sn.DevType)
				{
					case 0x10:	sensor.type = "DS1820 или DS18S20";	break;
					case 0x28:	sensor.type = "DS18B20";			break;
					default:	sensor.type = "Unknow";				break;
				}
				//
				unsigned long ui_sn;
				AnsiString as_sn;
				AnsiString _buffer;
				//
				//sensor.sn = '_';
				sensor.sn += IntToHex(sensor.ow_sn.DevType, 2) + '-';
				//
				for (int x = 5; x >= 0; x--)
				{
					sensor.sn += IntToHex(sensor.ow_sn.Number[x], 2);
				}
				sensor.sn += ("-" + IntToHex(sensor.ow_sn.CRC, 2));
				//
				memcpy(&sensor.comport, &comport, sizeof(TOWComport));
				//
				// Добавляем найденный датчик в вектор
				sensors.push_back(sensor);
				// Добавляем найденный датчик во временный вектор для
				// подсчёта сенсоров на текущем порте
				local_sensors.push_back(sensor);
				//
				//
			} else break;
		}
	}
	_debug("TOWComPort::SearchSensors() [OUTPUT]");
	return local_sensors.size();
}
//---------------------------------------------------------------------------
void __fastcall TOWSInterface::send_message_to_gui_form(TOWSensor *ows, const HWND _Handle)
{
	_debug("TOWSInterface::send_message_to_gui_form(TOWSensor *ows, const HWND guiHandle) [INPUT]");
	if ( _Handle != NULL )
	{
		COPYDATASTRUCT cd;              //
		memset(&cd, 0, sizeof(COPYDATASTRUCT)); //

		//TOWSensor _sensor;
		//_sensor.value = 66.66;
		//
		cd.dwData = 0;							// Идентификатор
		cd.cbData = sizeof(TOWSensor);  		//
		cd.lpData = ows; //_sensor;
		SendMessage(_Handle, WM_COPYDATA, (WPARAM)_Handle, (LPARAM) (LPVOID) &cd);
		_debug("TOWSInterface::send_message_to_gui_form(TOWSensor *ows, const HWND guiHandle) [SendMessage(_Handle, WM_COPYDATA, (WPARAM)_Handle, (LPARAM) (LPVOID) &cd);]");
	}
	_debug("TOWSInterface::send_message_to_gui_form(TOWSensor *ows, const HWND guiHandle) [OUTPUT]");
}
//---------------------------------------------------------------------------
void __fastcall TOWSInterface::update_algoritms_gui_forms()
{
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
		_debug("TOWSInterface::send_message_to_gui_form(TOWSensor *ows, const HWND guiHandle) [SendMessage(_Handle, WM_COPYDATA, (WPARAM)_Handle, (LPARAM) (LPVOID) &cd);]");


	}
	return;

	//--------------------------------------------
	_debug("void __fastcall TOWSInterface::update_algoritms_gui_forms() [INPUT]");
	//
	_debug("void __fastcall TOWSInterface::update_algoritms_gui_forms() [( guiHandle != NULL )]");
	std::vector<TOWSensor>::iterator itows;
	//
	for ( itows = sensors.begin(); itows != sensors.end(); ++itows)
	{
		send_message_to_gui_form( &*itows, guiHandle);
		//send_message_to_gui_form( &Sensor, itows->guiHandle);
	}
	_debug("void __fastcall TOWSInterface::update_algoritms_gui_forms() [OUTPUT]");
}
//---------------------------------------------------------------------------
void __fastcall TOWSInterface::update_sensors_gui_forms()
{

	_debug("void __fastcall TOWSInterface::update_sensors_gui_forms() [INPUT]");
	//
	std::vector<TOWSensor>::iterator itows;
	//
	for ( itows = sensors.begin(); itows != sensors.end(); ++itows)
	{
		send_message_to_gui_form( &*itows, itows->guiHandle);
		//send_message_to_gui_form( &Sensor, itows->guiHandle);
	}
	_debug("void __fastcall TOWSInterface::update_sensors_gui_forms()void __fastcall TOWSInterface::update_sensors_gui_forms() [OUTPUT]");
}
//---------------------------------------------------------------------------
void __fastcall TOWSInterface::Execute()
{
	_debug("void __fastcall TOWSInterface::Execute() [INPUT]");
	//
	while ( !Terminated )
	{
		//MessageBeep( MB_ICONERROR );
		_debug("void __fastcall TOWSInterface::Execute() [while ( !Terminated )] [INPUT]");
		//
		// подготавливаем ком порты
		std::for_each(comports.begin(), comports.end(), std::mem_fun_ref( &TOWComport::Preparation ));
		//
		Sleep(Timer);
		//
		_debug("void __fastcall TOWSInterface::Execute() [Update Sensor Value] [INPUT]");
		std::for_each(sensors.begin(), sensors.end(), std::mem_fun_ref( &TOWSensor::update_value));
		_debug("void __fastcall TOWSInterface::Execute() [Update Sensor Value] [OUTPUT]");
		//
		//
		/*
		std::copy(comports.begin(),
					comports.end(),
					std::ostream_iterator<TOWComport>(std::cout, "\n"));
		//
		std::copy(sensors.begin(),
				  sensors.end(),
				  std::ostream_iterator<TOWSensor>(std::cout, "\n"));
		*/
		//-----------------------------------------------------------------
		//
		//   UPDATE GUI
		//
		update_sensors_gui_forms();
		update_algoritms_gui_forms();
		//
		//std::for_each(sensors.begin(), sensors.end(), bind2nd(std::mem_fun_ref( &TOWSensor::update_gui_form), hWindowsGui ));
		//
		_debug("void __fastcall TOWSInterface::Execute() [while ( !Terminated )] [OUTPUT]");
	}
	_debug("void __fastcall TOWSInterface::Execute() [OUTPUT]");
}
//---------------------------------------------------------------------------
/*
std::ofstream& operator<<(std::ofstream& ofs, TOWSensor& ows)
{
	TDateTime dt;
	unsigned short hour, min, sec, msec;
	AnsiString dtstring;

	dt = Now();
	dt.DecodeTime(&hour, &min, &sec, &msec);
	dtstring = dt.DateTimeString();

	ofs << "[" << dtstring.c_str() << "." << msec << "] - ";
	ofs << "[Sn: " << ows.sn.c_str() << "; ";
	ofs << "Measure: " << ows.value << "]" << std::endl;
	return ofs;
}
*/
//---------------------------------------------------------------------------
TOWSensor::TOWSensor():
	measure_log_output(true),
	debug_log_output(false),
	measure_database_output(true),
	measure_common_database_output(true),
	measure_common_txt_output(true),
	value(0.0),
	guiHandle(NULL),
	min_gui(0.0),
	max_gui(100.0),
	Caption("You super/best caption...")
{
}
//---------------------------------------------------------------------------
TOWSensor::TOWSensor(const TOWSensor * Sensor):
	measure_log_output(Sensor->measure_log_output),
	debug_log_output(Sensor->debug_log_output),
	measure_database_output(Sensor->measure_database_output),
	measure_common_database_output(Sensor->measure_common_database_output),
	measure_common_txt_output(Sensor->measure_common_txt_output),
	value(Sensor->value),
	guiHandle(Sensor->guiHandle),
	min_gui(Sensor->min_gui),
	max_gui(Sensor->max_gui),
	Caption(Sensor->Caption),
	comport(Sensor->comport),
	ow_sn(Sensor->ow_sn),
	ow_ram(Sensor->ow_ram),
	type(Sensor->type),
	sn(Sensor->sn)

{
}
//---------------------------------------------------------------------------
void TOWSensor::save_measure_to_log_file()
{
	if (measure_log_output)
	{
		AnsiString FileName;
		AnsiString VALUE;
		//
		FileName = sn + ".measure";
		VALUE.sprintf("%.4f", value);
		commonLogFile(FileName,  VALUE);
	}
}
//---------------------------------------------------------------------------
void TOWSensor::_debug(const AnsiString &message)
{
	if (debug_log_output)
	{
		AnsiString FileName;
		//
		FileName = sn + ".debug";
		commonLogFile(FileName, message);
	}
}
//---------------------------------------------------------------------------
void TOWSensor::save_measure_to_database(TFDCommand *fdc)
{
	if ( !measure_database_output ) return;
	//
	_debug("void TOWSensor::insert_into_table(TFDCommand *fdc)");

	std::auto_ptr<TStringList> SQL(new TStringList);
	std::auto_ptr<TStringList> Buffer(new TStringList);
	//-----------------------------------------------------
	Buffer->Clear();
	Buffer->Add("INSERT INTO [%s]     ");
	Buffer->Add("(                    ");
	Buffer->Add("[VALUE], [DATETIME]  ");
	Buffer->Add(")                    ");
	Buffer->Add("VALUES               ");
	Buffer->Add("('%f', '%s')         ");
	Buffer->Add(";                    ");
	//-----------------------------------------------------
	SQL->Assign(Buffer.get());
	//-----------------------------------------------------
	AnsiString dt = Now();
	SQL->Strings[0] = Format( Buffer->Strings[0], ARRAYOFCONST(( sn )));
	SQL->Strings[5] = Format( Buffer->Strings[5], ARRAYOFCONST(( value, dt )));
	//--------------------------------------------------------------
	fdc->CommandText = SQL.get();

	try
	{
		fdc->Execute();
	}
	catch (Exception& E)
	{
			//debugLogFile("void __fastcall TOWSInterface::CreateTableSensors(). FDCommand->Execute() [Insert into sensors]" + E.Message);
	}
}
//---------------------------------------------------------------------------
void TOWSensor::create_table_sensor(TFDCommand *FDCommand)
{
	std::auto_ptr<TStringList> SQL(new TStringList);
	std::auto_ptr<TStringList> Buffer(new TStringList);
	//-----------------------------------------------------

	Buffer->Clear();
	Buffer->Add("CREATE TABLE [%s]    ");
	Buffer->Add("(                    ");
	Buffer->Add("[ID] AUTOINCREMENT,  ");
	Buffer->Add("[VALUE] REAL,        ");
	Buffer->Add("[DATETIME] DATETIME, ");
	Buffer->Add("PRIMARY KEY ([ID])   ");
	Buffer->Add(");                   ");
	//-----------------------------------------------------
	SQL->Assign(Buffer.get());
	//-----------------------------------------------------
	SQL->Strings[0] = Format( Buffer->Strings[0], ARRAYOFCONST(( sn )));
	//--------------------------------------------------------------
	FDCommand->CommandText = SQL.get();

	try
	{
		FDCommand->Execute();
	}
	catch (Exception& E)
	{
			//debugLogFile("void __fastcall TOWSInterface::CreateTableSensors(). FDCommand->Execute() [Insert into sensors]" + E.Message);
	}
	//*************************************************************
	//-----------------------------------------------------
	SQL->Clear();
	SQL->Add("CREATE TABLE SENSORS ");
	SQL->Add("(                    ");
	SQL->Add("[ID] AUTOINCREMENT,  ");
	SQL->Add("[VALUE] REAL,        ");
	SQL->Add("[DATETIME] DATETIME, ");
	SQL->Add("[SN] CHAR(20),       ");
	SQL->Add("PRIMARY KEY ([ID])   ");
	SQL->Add(");                   ");
	//--------------------------------------------------------------
	FDCommand->CommandText = SQL.get();
	try
	{
		FDCommand->Execute();
	}
	catch (Exception& E)
	{
			//debugLogFile("void __fastcall TOWSInterface::CreateTableSensors(). FDCommand->Execute() [Insert into sensors]" + E.Message);
	}
}
//---------------------------------------------------------------------------
void TOWSensor::save_setting_to_ini_file()
{
	_debug("void TOWSensor::save_setting_to_ini_file() [INPUT]");
	//--------------------------------------------------------------------
	std::auto_ptr<TIniFile> Ini(new TIniFile( get_ini_file() ) );
	Ini->WriteBool("I/O", "debug_log_output",  				debug_log_output);
	Ini->WriteBool("I/O", "measure_log_output", 			measure_log_output);
	Ini->WriteBool("I/O", "measure_database_output",		measure_database_output);
	Ini->WriteBool("I/O", "measure_common_database_output", measure_common_database_output);
	Ini->WriteBool("I/O", "measure_common_txt_output",      measure_common_txt_output);
	//
	Ini->WriteFloat("GUI", "min_gui",  min_gui);
	Ini->WriteFloat("GUI", "max_gui",  max_gui);
	Ini->WriteString("GUI", "Caption", Caption);
	//
	//Ini->WriteFloat("Alarms", "min", min);
	//Ini->WriteFloat("Alarms", "max", max);
	//
	//Ini->WriteString("Alarms", "alarm_file_name", _alarm_file_name);

	//
	Ini->UpdateFile();
	//--------------------------------------------------------------------
	_debug("void TOWSensor::save_setting_to_ini_file() [OUTPUT]");
}
//---------------------------------------------------------------------------
bool TOWSensor::load_setting_from_ini_file()
{
	_debug("bool TOWSensor::load_setting_from_ini_file() [INPUT]");
	//-------------------------------------------------------------------
	if ( FileExists( get_ini_file() ))
	{
		std::auto_ptr<TIniFile> Ini(new TIniFile( get_ini_file() ) );
		//
		debug_log_output = Ini->ReadBool("I/O", "debug_log_output",        false);
		measure_log_output = Ini->ReadBool("I/O", "measure_log_output",      true);
		measure_database_output = Ini->ReadBool("I/O", "measure_database_output", true);
		measure_common_database_output = Ini->ReadBool("I/O", "measure_common_database_output",  true);
		measure_common_txt_output = Ini->ReadBool("I/O", "measure_common_txt_output",  true);
		//
		min_gui = Ini->ReadFloat("GUI", "min_gui",  0.0);
		max_gui = Ini->ReadFloat("GUI", "max_gui",  100.0);
		Caption = Ini->ReadString("GUI", "Caption", Caption);

		//
		//min = Ini->ReadFloat("Alarms", "min", 20);
		//max = Ini->ReadFloat("Alarms", "max", 30);
		//
		//_alarm_file_name = Ini->ReadString("Alarms", "alarm_file_name", "default.wav");
		//
		_debug("bool TOWSensor::load_setting_from_ini_file() [return TRUE]");
		return true;
		//
	} else
		{
			save_setting_to_ini_file();
			_debug("bool TOWSensor::load_setting_from_ini_file() [return FALSE]");
			return false;
		}
}
//---------------------------------------------------------------------------
AnsiString TOWSensor::get_ini_file()
{
	_debug("AnsiString TOWSensor::get_ini_file() [INPUT]");
	AnsiString FilePath, _ini_file_name;
	//
	FilePath = ExtractFilePath(Application->ExeName);
	_ini_file_name = FilePath + '\\' + sn + ".ini";
	//
	_debug("AnsiString TOWSensor::get_ini_file() [INPUT], Application->ExeName = " + Application->ExeName);
	_debug("AnsiString TOWSensor::get_ini_file() [INPUT], ExtractFilePath(Application->ExeName) = " + FilePath);
	_debug("AnsiString TOWSensor::get_ini_file() [INPUT], _ini_file_name = " + _ini_file_name);
	_debug("AnsiString TOWSensor::get_ini_file() [OUTPUT]");
	return _ini_file_name;
}
//---------------------------------------------------------------------------
void TOWSensor::save_measure_to_common_database_table(TFDCommand *FDCommand)
{
	_debug("void TOWSensor::save_measure_to_common_database_table(TFDCommand *FDCommand) [INPUT]");
	//
	std::auto_ptr<TStringList> SQL(new TStringList);
	std::auto_ptr<TStringList> Buffer(new TStringList);
	//-----------------------------------------------------
	Buffer->Clear();
	Buffer->Add("INSERT INTO SENSORS        ");
	Buffer->Add("(                          ");
	Buffer->Add("[VALUE], [DATETIME], [SN]  ");
	Buffer->Add(")                          ");
	Buffer->Add("VALUES                     ");
	Buffer->Add("('%f', '%s', '%s')         ");
	Buffer->Add(";                          ");
	//-----------------------------------------------------
	SQL->Assign(Buffer.get());
	//-----------------------------------------------------
	AnsiString dt = Now();
	SQL->Strings[5] = Format( Buffer->Strings[5], ARRAYOFCONST(( value, dt, sn )));
	//--------------------------------------------------------------
	FDCommand->CommandText = SQL.get();

	try
	{
		FDCommand->Execute();
	}
	catch (Exception& E)
	{
			//debugLogFile("void __fastcall TOWSInterface::CreateTableSensors(). FDCommand->Execute() [Insert into sensors]" + E.Message);
	}
	_debug("void TOWSensor::save_measure_to_common_database_table(TFDCommand *FDCommand) [OUTPUT]");
}
//---------------------------------------------------------------------------
void TOWSensor::save_measure_to_common_log_file()
{
	if ( !measure_common_txt_output)
		return;

	AnsiString message;
	AnsiString FileName;
	//message << "Value: " << it->value;
	//commonLogFile("sensors.measure",  message);
	message.sprintf("%s\t%.4f", sn.c_str(), value);
	FileName = "sensors.measure";
	commonLogFile(FileName,  message );
}
//---------------------------------------------------------------------------
void  TOWSensor::update_value()
{
	_debug("TOWSensor::updateSensor(TOWSensor & ows) [INPUT]");
	if ((ow_sn.DevType == 0x10) || (ow_sn.DevType == 0x28))
	{
		_debug("TOWSensor::updateSensor(TOWSensor & ows) [1]");
		if (OW_SelectROM(ow_sn, comport.id))
		{
			_debug("TOWSensor::updateSensor(TOWSensor & ows) [2]");
			if (OW_ReadRAM(ow_ram, comport.id))
			{
				_debug("TOWSensor::updateSensor(TOWSensor & ows) [3]");
				if (OW_GetCRC(&ow_ram, 8) == ow_ram.CRC) // ???
				{
					_debug("TOWSensor::updateSensor(TOWSensor & ows) [4]");
					//
					short buffer[3];
					buffer[0] = ow_ram.H_Termo << 8;
					buffer[1] = buffer[0] | ow_ram.L_Termo;
					//
					switch(ow_sn.DevType)
					{
						case 0x28: value = ((float)buffer[1]/(float)16.0); break;
						case 0x10: value = ((float)buffer[1]/(float)2.0);  break;
						default: break;
					}
					///////////////////////////////////////////////////
					// сохраняем значение ьемпературы в Векторе.
					//ows.data.push_back(ows.value);
					_debug( "TOWSensor::updateSensor(TOWSensor & ows) [OUTPUT]" );
					///////////////////////////////////////////////////
				}  else
						_debug( "if (OW_GetCRC(&ow_ram, 8) == ow_ram.CRC) [ERROR]");
			}
		}
	}
}
//---------------------------------------------------------------------------
void TOWSensor::update_common_gui_form(HWND hwnd)
{
	update_gui_form(hwnd);
}
//---------------------------------------------------------------------------
void TOWSensor::update_gui_form(HWND hwnd)
{

}
//---------------------------------------------------------------------------
/*
 void  TOWSensor::sendmessage_sensor_to_mdichildform(TOWSensor &ows)
{
	_debug("void  TOWSensor::sendmessage_sensor_to_mdichildform(TOWSensor &ows) [INPUT]");
	if ( ows.hwndGui != NULL)
	{
		_debug("void  TOWSensor::sendmessage_sensor_to_mdichildform(TOWSensor &ows) [if ( ows.hwndGui != NULL)]");
		COPYDATASTRUCT cd;
		cd.dwData= 0;					// Идентификатор
		cd.cbData = sizeof(TOWSensor);
		cd.lpData= &ows; // ???
		SendMessage(ows.hwndGui, WM_COPYDATA, (WPARAM)ows.hwndGui, (LPARAM) (LPVOID) &cd);
	}
	_debug("void  TOWSensor::sendmessage_sensor_to_mdichildform(TOWSensor &ows) [OUTPUT]");
}
*/
//---------------------------------------------------------------------------
//bool TOWSensor::check_min_alarm()
//{
//	return (value < min);
//}
//---------------------------------------------------------------------------
//bool TOWSensor::check_max_alarm()
//{
//	return (value > max);
//}
//---------------------------------------------------------------------------
//bool TOWSensor::check_alarms()
//{
//	return (check_min_alarm() || check_max_alarm());
//}
//---------------------------------------------------------------------------
/*
void TOWSensor::play_sound_alarms()
{
	_debug("TOWSensor::check_alarms()  [INPUT]");
	if ( check_alarms() )
	{
		//const wchar_t *p = _alarm_file_name. w_str();
		//PlaySound( (const wchar_t*)_alarm_file_name.c_str(), 0, SND_FILENAME | SND_ASYNC);

		//PlaySound(ExtractFilePath(_alarm_file_name));

		UnicodeString FileName;

		FileName = ExtractFilePath(Application->ExeName) + "\\WAV\\" + _alarm_file_name;
		PlaySound(FileName.w_str(), 0, SND_FILENAME | SND_ASYNC);

		_debug("TOWSensor::check_alarms()  [if ( check_min_alarm() || check_max_alarm() )]");
		_debug("TOWSensor::check_alarms()  [FileName = ]" + FileName);

		//PlaySound(PChar(FileName.c_str()), 0, SND_FILENAME | SND_ASYNC);
		//PlaySound( L"alarm.wav", 0, SND_FILENAME | SND_ASYNC);
		//sndPlaySoundW(L"alarm.wav", SND_SYNC);
		//sndPlaySoundW(AnsiLastChar(_alarm_file_name), SND_SYNC);
		//PlaySound( AnsiLastChar(_alarm_file_name), 0, SND_FILENAME | SND_ASYNC);
		//sndPlaySound(AnsiLastChar(OpenDialo g1->FileName), SND_ASYNC | SND_FILENAME);
	}
	_debug("TOWSensor::check_alarms()  [OUTPUT]");
}
//---------------------------------------------------------------------------
void TOWSensor::test(HWND hwnd)
{
}
//------------------------------------------------------------------------
*/
std::ostream& operator<<(std::ostream& os, const TOWSensor& ows)
{
	TDateTime dt;
	unsigned short hour, min, sec, msec;
	AnsiString dtstring;

	dt = Now();
	dt.DecodeTime(&hour, &min, &sec, &msec);
	dtstring = dt.DateTimeString();

	os << "[" << dtstring.c_str() << "." << msec << "] - ";
	os << "[" << ows.comport.name.c_str() << ", ";
	os << "Sn: " << ows.sn.c_str() << ", ";
	os << "Type: " << ows.type.c_str() << ", ";
	os << "Measure: " << ows.value << "]";
	return os;
}
//---------------------------------------------------------------------------
//
//
//  Events record tag section
//
//
//
//---------------------------------------------------------------------------
TOWEventTag::TOWEventTag() :
		sn('0'),
		value(0.0),
		lptport(0),
		upper(0),
		down(0)
{
}
//---------------------------------------------------------------------------
TOWEventTag::TOWEventTag(const TOWEventTag *EventRecord) :
		sn(EventRecord->sn),
		value(EventRecord->value),
		lptport(EventRecord->lptport),
		upper(EventRecord->upper),
		down(EventRecord->down)
{

}
//---------------------------------------------------------------------------
//
//
//  Algoritm section
//
//
//
//---------------------------------------------------------------------------
TDistillerAlgoritm::TDistillerAlgoritm() :
	FAlgoritmXMLFileName("distiller.xml")
{
	//IXMLDOMDocument *u;

}
//---------------------------------------------------------------------------
TDistillerAlgoritm::~TDistillerAlgoritm()
{
	stop_algoritm();
}
//---------------------------------------------------------------------------
void TDistillerAlgoritm::load_from_xmlfile()
{
/*
	_debug("void THomeDistillerAlgoritm::load_from_xmlfile() [INPUT]");
	XMLDocument = new TXMLDocument(NULL);
	if (XMLDocument)
	{
		_debug("void THomeDistillerAlgoritm::load_from_xmlfile() [if (XMLDocument)]");
		XMLDocument->LoadFromFile(FAlgoritmXMLFileName);
		_debug("void THomeDistillerAlgoritm::load_from_xmlfile() [XMLDocument->LoadFromXML(FAlgoritmXMLFileName);]");
		XMLDocument->Active = true;
		_debug("void THomeDistillerAlgoritm::load_from_xmlfile() [XMLDocument->Active = true;]");
		//XMLDocument->
	}
	//
	delete XMLDocument;
	_debug("void THomeDistillerAlgoritm::load_from_xmlfile() [OTPUT]");
*/
	//
	//---------------------------------------------------------------------
	//
	AnsiString nodeName("algoritms");
	_debug("void THomeDistillerAlgoritm::load_from_xmlfile() [INPUT]");
	const _di_IXMLDocument document = interface_cast<Xmlintf::IXMLDocument>
		(new TXMLDocument(NULL));
	document->LoadFromFile(FAlgoritmXMLFileName);
//	document->Active = true; // ?

	// Find a specific node.

	const _di_IXMLNode nodeAlgoritms = document->ChildNodes->FindNode(nodeName);
	const _TCHAR* attrName;
	TOWEventTag owEventRecord;

	if (nodeAlgoritms != NULL)
	{
		_debug("void THomeDistillerAlgoritm::load_from_xmlfile() [if (nodeElement != NULL)]");
		//
		for (int i = 0; i < nodeAlgoritms->ChildNodes->Count; i++)
		{
			const _di_IXMLNode nodeSensors = nodeAlgoritms->ChildNodes->Get(i);
			_debug(nodeSensors->NodeName);
			//
			const _TCHAR* attrName = _TEXT("sn");
			if (nodeSensors->HasAttribute(attrName))
			{
				const _TCHAR* attrValue = nodeSensors->Attributes[attrName];
				owEventRecord.sn = nodeSensors->Attributes[attrName];
				_debug(attrValue);
				// <<<<<<<<<<<<<
			}
			//-------------------------------------------------------------
			// E V E N T S
			for (int i = 0; i < nodeSensors->ChildNodes->Count; i++)
			{
				const _di_IXMLNode nodeEvent = nodeSensors->ChildNodes->Get(i);
				//_debug(AnsiString("i =") + IntToStr(i) );
				_debug(nodeEvent->NodeName);
				//-----------------------------------------------------------
				attrName = _TEXT("value");
				if (nodeEvent->HasAttribute(attrName))
				{
					const _TCHAR* attrValue = nodeEvent->Attributes[attrName];
					owEventRecord.value = StrToFloat(attrValue);
					_debug(attrValue);
				}
				//-----------------------------------------------------------
				attrName = _TEXT("lptpin");
				if (nodeEvent->HasAttribute(attrName))
				{
					const _TCHAR* attrValue = nodeEvent->Attributes[attrName];
					owEventRecord.lptport = StrToInt(attrValue);
					_debug(attrValue);
				}
				//-----------------------------------------------------------
				const _TCHAR* attrName = _TEXT("upper");
				if (nodeEvent->HasAttribute(attrName))
				{
					const _TCHAR* attrValue = nodeEvent->Attributes[attrName];
					owEventRecord.upper = StrToInt(attrValue);
					_debug(attrValue);
				}
				//-----------------------------------------------------------
				attrName = _TEXT("down");
				if (nodeEvent->HasAttribute(attrName))
				{
					const _TCHAR* attrValue = nodeEvent->Attributes[attrName];
					owEventRecord.down = StrToInt(attrValue);
					_debug(attrValue);
				}
				//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				//
				alrgoritm.insert(std::pair<AnsiString,TOWEventTag>(owEventRecord.sn, owEventRecord));
				//
				//multimap<const char*, int, ltstr> m;
				//m.insert(pair<const char* const, int>("a", 1));
			}
		}
	}

	_debug("void THomeDistillerAlgoritm::load_from_xmlfile() [OTPUT]");
}
//---------------------------------------------------------------------------
void TDistillerAlgoritm::multimap_to_txt()
{
  for (std::multimap<AnsiString, TOWEventTag>::iterator it = alrgoritm.begin();
	   it != alrgoritm.end();
	   ++it)
  {
   AnsiString buffer;

   buffer =
		"[ sn="      + (*it).first 		    + ", " +
		"value = "   + (*it).second.value   + ", " +
		"lptport = " + (*it).second.lptport + ", " +
		"upper = "   + (*it).second.upper   + ", " +
		"down = "    + (*it).second.down    + "]";

   _debug(buffer);
  }
}
//---------------------------------------------------------------------------
void TDistillerAlgoritm::_debug(const AnsiString &message)
{
	//if (debug_log_output)
	{
		AnsiString FileName = FAlgoritmXMLFileName +  ".debug";
		commonLogFile(FileName, message);
	}
}
//---------------------------------------------------------------------------
void TDistillerAlgoritm::start_algoritm(const TOWSensor &owsensor)
{
	AnsiString buffer;
	//
	int i = alrgoritm.count(owsensor.sn);
	if (i)
	{

	}

	std::pair <std::multimap<AnsiString,TOWEventTag>::iterator, std::multimap<AnsiString,TOWEventTag>::iterator> ret;

	ret = alrgoritm.equal_range(owsensor.sn);
	//
	//
	//
	for (std::multimap<AnsiString,TOWEventTag>::iterator it = ret.first;
		it != ret.second;
		++it)
	{
		buffer += (
			"[ sn="      + (*it).first 		    + ", " +
			"value = "   + (*it).second.value   + ", " +
			"lptport = " + (*it).second.lptport + ", " +
			"upper = "   + (*it).second.upper   + ", " +
			"down = "    + (*it).second.down    + "]"
			);
		//
		buffer += "\n";
		//--------------------------------------------------------------
		//TOWEventTag *myEvent;
		//myEvent = &(*it).second;
		//--------------------------------------------------------------
		int state = (owsensor.value >= (*it).second.value) ? 0 : 1;

		//TOWEventTag *ptrEvent = &(*it).second;
		//
		switch (state)
		{
			case 0:	do_event( (*it).second, (*it).second.upper);	break; // выше уставки
			case 1:	do_event( (*it).second, (*it).second.down);		break; // ниже уставки
		}
	}
	//return buffer;
}
//---------------------------------------------------------------------------
bool TDistillerAlgoritm::do_event(const TOWEventTag &EventTag, int command)
{
	switch (command)
	{
		case -1: break;
		//case 0: FLptPort.Reset( EventTag.lptport);	break;
		//case 1: FLptPort.Set( EventTag.lptport);	break;
		//
		case 666: return false; // STOP Algoritm
	}
	return true;
}
//---------------------------------------------------------------------------
void TDistillerAlgoritm::stop_algoritm()
{
	//FLptPort.Reset();
}


