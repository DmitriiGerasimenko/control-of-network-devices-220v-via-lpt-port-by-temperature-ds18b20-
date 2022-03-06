//---------------------------------------------------------------------------

#ifndef lptportH
#define lptportH
//---------------------------------------------------------------------------
#include <windows.h>
//#include <vector>
#include <bitset>

class TLptPort
{
private:

	//
	typedef short _stdcall (*inpfuncPtr)(short portaddr);
	typedef void  _stdcall (*oupfuncPtr)(short portaddr, short datum);
	//
	//
	HINSTANCE hLib;
	inpfuncPtr inp32;
	oupfuncPtr out32;
	//
	std::bitset<8> lptpins_lo; // 888
	std::bitset<4> lptpins_hi; // 890
	//

public:
	short adress_lo; // 888 default LO
	short adress_hi; // 890 default HI
	//


protected:
	//
	int LoadInpout32DLL();

private:
	void output(const short adress, const short data);
	void output();
	//
	short read_adress(const short adress);

public:
	//
	void Reset();
	void Reset(const short i);
	//
	void Set();
	void Set(const short i);
	//
	short read_adress_lo();
	short read_adress_hi();
	//
	bool Test(const short i);
	//
	TLptPort();
	~TLptPort();
};
//---------------------------------------------------------------------------
#endif
