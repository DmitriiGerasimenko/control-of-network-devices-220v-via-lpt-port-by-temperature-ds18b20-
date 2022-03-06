
#include "lptport.h"

//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
//---------------------------------------------------------------------------
TLptPort::TLptPort() :
	adress_lo(888),
	adress_hi(890),
	hLib(NULL)
{
	LoadInpout32DLL();  // грузим inpout32.dll
	Reset();	// сбрасываем все пины ЛПТ порта d '0'
	//
}
//---------------------------------------------------------------------------
TLptPort::~TLptPort()
{
	FreeLibrary(hLib);  // зкрываем inpout32.dll
}
//---------------------------------------------------------------------------
int TLptPort::LoadInpout32DLL()
{
	/* Load the library */
	hLib = LoadLibrary(L"inpout32.dll");

	if (hLib == NULL) {
		//ShowMessage("LoadLibrary Failed.");
		return 1;
	}
	/* get the address of the function */
	inp32 = (inpfuncPtr)GetProcAddress(hLib, "Inp32");
	if (inp32 == NULL) {
		//ShowMessage("GetProcAddress for Inp32 Failed.\n");
		return 2;
	}
	/* get the address of the function */
	out32 = (oupfuncPtr)GetProcAddress(hLib, "Out32");
	if (out32 == NULL) {
		//ShowMessage("GetProcAddress for Oup32 Failed.\n");
		return 3;
	}

	return NULL;
}
// ---------------------------------------------------------------------------
short TLptPort::read_adress(const short adress)
{
	if (inp32 != NULL)
		return (inp32)(adress);
	else
		return NULL;
}
// ---------------------------------------------------------------------------
short TLptPort::read_adress_hi()
{
	return read_adress(adress_hi);
}
// ---------------------------------------------------------------------------
short TLptPort::read_adress_lo()
{
	return read_adress(adress_lo);
}
// ---------------------------------------------------------------------------
void TLptPort::output(const short adress, const short data)
{
	(out32)(adress, data);
}
// ---------------------------------------------------------------------------
void TLptPort::output()
{
	output(adress_lo, lptpins_lo.to_ulong());
	output(adress_hi, lptpins_hi.to_ulong());
}
// ---------------------------------------------------------------------------
void TLptPort::Reset()
{
	lptpins_lo.reset();
	//
	lptpins_hi.set(0);
	lptpins_hi.set(1);
	lptpins_hi.reset(2);
	lptpins_hi.set(3);
	//
	output();
}
//---------------------------------------------------------------------------
void TLptPort::Reset(const short i)
{
	switch (i)
	{
		case  0:
		case  1:
		case  2:
		case  3:
		case  4:
		case  5:
		case  6:
		case  7: lptpins_lo.reset(i); 	break;
		case  8: lptpins_hi.set(0); 	break;
		case  9: lptpins_hi.set(1); 	break;
		case 10: lptpins_hi.reset(2);	break;
		case 11: lptpins_hi.set(3); 	break;
	}
	output();
}
//---------------------------------------------------------------------------
void TLptPort::Set()
{
	lptpins_lo.set();
	//
	lptpins_hi.reset(0);
	lptpins_hi.reset(1);
	lptpins_hi.set(2);
	lptpins_hi.reset(3);
	//
	output();
}
//---------------------------------------------------------------------------
void TLptPort::Set(const short i)
{
	switch (i)
	{
		case  0:
		case  1:
		case  2:
		case  3:
		case  4:
		case  5:
		case  6:
		case  7: lptpins_lo.set(i);		break;
		case  8: lptpins_hi.reset(0);	break;
		case  9: lptpins_hi.reset(1);	break;
		case 10: lptpins_hi.set(2);		break;
		case 11: lptpins_hi.reset(3);	break;
	}
	output();
}
//---------------------------------------------------------------------------
bool TLptPort::Test(const short i)
{
	bool result;
	//
	switch (i)
	{
		case  0:
		case  1:
		case  2:
		case  3:
		case  4:
		case  5:
		case  6:
		case  7: result = lptpins_lo.test(i);  break;
		case  8: result = !lptpins_hi.test(0); break;
		case  9: result = !lptpins_hi.test(1); break;
		case 10: result = lptpins_hi.test(2); break;
		case 11: result = !lptpins_hi.test(3); break;
	}
	return result;
}
//---------------------------------------------------------------------------
/*
short __fastcall TLPTPort::EnablePin(short iPinNumber)
{
	//
	//
	short FPortState = (inp32)(FLPTAdress);
	// Index = 0...7
	//
	if (iPinNumber < 0) return FPortState;
	if (iPinNumber > 7) return FPortState;
	//
	bool CheckPin = (FPortState >> iPinNumber) & 1;
	// если бит не равен 1
	if ( !CheckPin )
	{
		FPortState = (FPortState | (1 << iPinNumber));
		//
		Out();
	}
	//
	return FPortState;
}
//---------------------------------------------------------------------------

short __fastcall TLPTPort::DisablePin(short iPinNumber)
{
	//
	//
	FPortState = (inp32)(FLPTAdress);
	//
	// Index = 0...7
	//
	if (iPinNumber < 0) return FPortState;
	if (iPinNumber > 7) return FPortState;
	//
	bool CheckPin = (FPortState >> iPinNumber) & 1;
	// если бит равен 1
	if ( CheckPin )
	{
		FPortState = (FPortState ^ (1 << iPinNumber));
		//
		Out(FPortState);
	}
	//
	return FPortState;
}
//---------------------------------------------------------------------------
short __fastcall TLPTPort::InversionPin(short iPinNumber)
{
	//
	//
	FPortState = (inp32)(FLPTAdress);
	//
	// Index = 0...7
	//
	if (iPinNumber < 0) return FPortState;
	if (iPinNumber > 7) return FPortState;
	//
	bool CheckPin = (FPortState >> iPinNumber) & 1;
	// если бит равен 1
	if ( CheckPin )
		FPortState = (FPortState ^ (1 << iPinNumber));
	else
		FPortState = (FPortState | (1 << iPinNumber));
	//
	Out(FPortState);
	//
	return FPortState;
}
//---------------------------------------------------------------------------
void __fastcall TLPTPort::GetBinaryPortState(AnsiString &FValue)
{
	char _Buffer[10];
	//
	FPortState = (inp32)(FLPTAdress);
	//
	_Buffer[0] = ((FPortState >> 0) & 1) ? '1' : '0';
	_Buffer[1] = ((FPortState >> 1) & 1) ? '1' : '0';
	_Buffer[2] = ((FPortState >> 2) & 1) ? '1' : '0';
	_Buffer[3] = ((FPortState >> 3) & 1) ? '1' : '0';
	_Buffer[4] = ((FPortState >> 4) & 1) ? '1' : '0';
	_Buffer[5] = ((FPortState >> 5) & 1) ? '1' : '0';
	_Buffer[6] = ((FPortState >> 6) & 1) ? '1' : '0';
	_Buffer[7] = ((FPortState >> 7) & 1) ? '1' : '0';
	_Buffer[8] = NULL;
	//
	FValue = _Buffer;
}
//---------------------------------------------------------------------------
bool __fastcall TLPTPort::CheckStatePins(short FValue)
{
	//
	switch (FValue) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7: return ((FPortState >> FValue) & 1);
	//
	default: return false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TLPTPort::intToBin(int valueInt, char *BinaryString)
{
	// перевод в двоичное
	//
	BinaryString[0] = '0';
	BinaryString[1] = '0';
	BinaryString[2] = '0';
	BinaryString[3] = '0';
	BinaryString[4] = '0';
	BinaryString[5] = '0';
	BinaryString[6] = '0';
	BinaryString[7] = '0';
	BinaryString[8] = NULL;
	//
	if(valueInt == 0)	return;
	//
	unsigned char iPos = 0;
	//
	while(valueInt)
	{
		BinaryString[iPos] = char(valueInt % 2 + '0');
		valueInt /= 2;
		iPos ++;
	}
	//
	return;
}
*/
/*
void __fastcall TLPTPort::SetLptPin(const unsigned int index, const bool b)
{
	if ( index >= 0 && index <= 7)
	{

		//FStringPins[index] = ch;
		int invert_index;

		switch (index) {
			case 0: invert_index = 7; break;
			case 1: invert_index = 6; break;
			case 2: invert_index = 5; break;
			case 3: invert_index = 4; break;
			case 4: invert_index = 3; break;
			case 5: invert_index = 2; break;
			case 6: invert_index = 1; break;
			case 7: invert_index = 0; break;

			default:;
		}

		FStringPins[index] = (b == true) ? '1' : '0';
	}
	FStringPins[8]=NULL;

	return;
}
*/
//---------------------------------------------------------------------------
/*
int __fastcall TLPTPort::binToint(std::string &s1) { // перевод строки в 10-е число
	int z1 = 0;
	for (int i = (int)s1.length() - 1; i > -1; --i) {
		if (s1[i] != '0')
			if (s1[i] != '1')
				throw std::runtime_error("not bin symbol");

		if ((s1[i] - '0'))
			z1 = z1 + (int)pow((long double)2, int(s1.length() - 1 - i));
	}
	return z1;
}
*/
//---------------------------------------------------------------------------
/*
int __fastcall TLPTPort::binToint(const char *str) { // перевод строки в 10-е число
	int z1 = 0;
	for (unsigned int i = 0; i <= 7; i++)
	{
		if ( (str[i] != '0') && (str[i] != '1') )
		{
			throw std::runtime_error("not bin symbol");
		}
		//ShowMessage( str[i] );

		if ((str[i] - '0'))
		{
			//ShowMessage( "if ((str[i] - '0'))" );
			z1 = z1 + (int)pow((long double)2, int(6 - i));
		}
	}
	return z1;
}
//---------------------------------------------------------------------------
*/
/*
void __fastcall TLPTPort::operator [](unsigned int index)
{
	if(index < 0 && index >= strlen(FStringPins) )
		return;

	FStringPins[index] = '0';

	return;
}
*/
//---------------------------------------------------------------------------

