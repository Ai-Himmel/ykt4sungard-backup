#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <vector>
#include "kscard.h"
#include "YCTReaderInterface.h"
using namespace std;
#define KNG_CARD_READ_MODE 0 
#define KNG_CARD_WRITE_MODE 1

#define KNG_CARD_MASK 0
#define KNG_CARD_SN KNG_CARD_MASK + 1
#define KNG_STUEMP_NO KNG_CARD_MASK + 2
#define KNG_EXPIRED_DATE KNG_CARD_MASK + 18
#define MAIN_CCK	"\x53\x89\x19\x80\x11\x23\x19\x76\x11\x13\xAA\xBB\xCC\x88\x00\xAE"

//1为羊城通读写器  0为金仕达读写器
#define		YCT_READER		0
//extern HANDLE			g_nHandle;
//测试用
extern ST_CARDMAINKEY  g_MainKey;
extern vector<ST_CARDTABLEINDEX> g_VsCardInfo;
extern vector<ST_READCARDINFO>     g_VsReadCardInfo;
extern vector<ST_WRITECARDINFO>     g_VsWriteCardInfo;

void YCT_InitIndexTable();
//extern void TestLog( char* sMsg);
int GenMacData( unsigned char*sData, byte ucDataLen, unsigned char* OutData);


extern	CYCTReaderInterface m_Reader;
extern	ST_CARDMAINKEY  g_MainKey;

extern	vector<ST_CARDTABLEINDEX> g_VsCardInfo;
extern	vector<ST_READCARDINFO>     g_VsReadCardInfo;
extern	vector<ST_WRITECARDINFO>     g_VsWriteCardInfo;

#endif //_GLOBAL_H_