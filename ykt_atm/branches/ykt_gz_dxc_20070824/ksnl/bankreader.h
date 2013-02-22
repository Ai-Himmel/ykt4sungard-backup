#ifndef _BANKREADER_H_
#define _BANKREADER_H_

#pragma  once

class KSBankReader
{
private:
	int port_;
	int load_dllfunc();
	HINSTANCE h_magdll;
public:
	KSBankReader();
	~KSBankReader();
	int open();
	int close();
	int ReadBankCard(int timeout,char *bank_no);
};
#endif // _BANKREADER_H_
