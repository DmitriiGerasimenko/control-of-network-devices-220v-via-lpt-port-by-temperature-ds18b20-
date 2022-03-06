// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'OWire_Module.pas' rev: 6.00

#ifndef OWire_ModuleHPP
#define OWire_ModuleHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Owire_module
{
//-- type declarations -------------------------------------------------------
#pragma pack(push, 1)
struct OW_RAM
{
	Byte L_Termo;
	Byte H_Termo;
	Byte Max_Termo;
	Byte Min_Termo;
	Byte Config;
	Byte x[3];
	Byte CRC;
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct OW_Write_RAM
{
	Byte Max_Termo;
	Byte Min_Termo;
	Byte Config;
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct OW_SN
{
	Byte DevType;
	Byte Number[6];
	Byte CRC;
} ;
#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
static const Shortint OW_Err_OK = 0x0;
static const Shortint OW_Err_Port = 0x1;
static const Shortint OW_Err_NoDevice = 0x2;
static const Shortint OW_Err_IO = 0x3;
static const Shortint OW_Err_BaudRate = 0x4;
static const Shortint OW_Err_Search = 0x5;
static const Shortint OW_Err_BadParam = 0x6;
static const Shortint OW_Err_NoData = 0x7;
static const Shortint OW_Mode_CPU_MinUsage = 0x1;
static const Shortint OW_Mode_Invert = 0x2;
static const Shortint OW_Mode_NoControlPin = 0x4;
static const Shortint SP_Pin_DTR = 0x1;
static const Shortint SP_Pin_RTS = 0x2;
static const Shortint SP_Pin_TXD = 0x4;
static const Shortint SP_Pin_RI = 0x0;
static const Shortint SP_Pin_DCD = 0x1;
static const Shortint SP_Pin_DSR = 0x2;
static const Shortint SP_Pin_CTS = 0x3;
extern "C" int __stdcall OW_GetMode(void);
extern "C" int __stdcall OW_SetMode(int Mode);
extern "C" int __stdcall OW_GetLastError(void);
extern "C" bool __stdcall OW_ClosePort(int Port = 0x0);
extern "C" int __stdcall OW_OpenPort(AnsiString ComPort, int Port = 0x0);
extern "C" bool __stdcall OW_Reset(int Port = 0x0);
extern "C" Byte __stdcall OW_ReadByte(int Port = 0x0);
extern "C" Byte __stdcall OW_WriteByte(Byte Byte, int Port = 0x0);
extern "C" Byte __stdcall OW_GetCRC(void * Buff, int Count);
extern "C" bool __stdcall OW_ReadMultiByte(void * Buff, int Count, int Port = 0x0);
extern "C" bool __stdcall OW_WriteMultiByte(void * Buff, int Count, int Port = 0x0);
extern "C" bool __stdcall OW_ReadROM(OW_SN &Info, int Port = 0x0);
extern "C" bool __stdcall OW_SelectROM(OW_SN &Info, int Port = 0x0);
extern "C" bool __stdcall OW_SkipROM(int Port = 0x0);
extern "C" int __stdcall OW_SearchROM_Reset(void);
extern "C" bool __stdcall OW_SearchROM_Enum(OW_SN &Sensor, int Port = 0x0);
extern "C" int __stdcall OW_SearchAlarm_Reset(void);
extern "C" bool __stdcall OW_SearchAlarm_Enum(OW_SN &Sensor, int Port = 0x0);
extern "C" bool __stdcall OW_ReadRAM(OW_RAM &Info, int Port = 0x0);
extern "C" bool __stdcall OW_WriteRAM(OW_Write_RAM &Info, int Port = 0x0);
extern "C" bool __stdcall OW_CopyRAM(int Port = 0x0);
extern "C" bool __stdcall OW_ConvertT(int Port = 0x0);
extern "C" bool __stdcall OW_Recall(int Port = 0x0);
extern "C" bool __stdcall OW_ReadPowerSupply(int Port = 0x0);
extern "C" int __stdcall SP_PortID(int Port = 0x0);
extern "C" int __stdcall SP_CountInBytes(int Port = 0x0);
extern "C" Byte __stdcall SP_ReadByte(int Port = 0x0);
extern "C" int __stdcall SP_WriteByte(Byte Byte, int Port = 0x0);
extern "C" int __stdcall SP_GetControlPin(int Pin, int Port = 0x0);
extern "C" bool __stdcall SP_SetControlPin(int Pin, bool Value, int Port = 0x0);

}	/* namespace Owire_module */
using namespace Owire_module;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// OWire_Module
