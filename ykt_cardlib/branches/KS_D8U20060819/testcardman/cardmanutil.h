#ifndef _CARDMAN_UTIL_H
#define _CARDMAN_UTIL_H
//////////////////////////////////////////////////////////////////////////
// ∂®“Â cardman dll
typedef void (CALLBACK * LPProcessCallBack)(int step);
typedef void (* LPGetBlockData)(int sect,int block,BYTE buf[16]
							   ,BYTE key[6],long flag);

typedef int (CALLBACK *LPInitNewCard) (int * err_code,const char *showcardno
									   ,LPProcessCallBack lpCallBack);
typedef int (CALLBACK *LPReadCardMainKey) (BYTE * main_key
										   ,short wantflag,short * readflag);
typedef int (CALLBACK *LPRefineCard) (int * err_code,LPProcessCallBack lpCallBack);
typedef int (CALLBACK *LPOpenCOM) (int port,long band);
typedef int (CALLBACK *LPCloseCOM) ();
typedef int (CALLBACK *LPResetAuthCard)(int * err_code,LPProcessCallBack lpCallBack);
typedef int (CALLBACK *LPNewAuthCard)(BYTE main_key[8],short pri_sect
								   ,short pri_block,short pri_startpos
								   ,LPProcessCallBack lpCallBack);
typedef int (CALLBACK *LPReadCardPhyID)(BYTE card_id[4],BYTE card_type[2]);
typedef int (CALLBACK *LPReadCardBlock)(int startSect,int endSect,
										short block,LPGetBlockData lpFunc);
typedef int (CALLBACK *LPSetCardMainKey)(BYTE key[8]);

int LoadCardManDLL();
void FreeCardManDLL();

extern HINSTANCE hCardManDLL;

extern LPInitNewCard		InitNewCard;
extern LPReadCardMainKey	ReadCardMainKey;
extern LPRefineCard			RefineCard;
extern LPOpenCOM			OpenCOM;
extern LPCloseCOM			CloseCOM;
extern LPResetAuthCard		ResetAuthCard;
extern LPNewAuthCard		NewAuthCard;
extern LPReadCardPhyID		ReadCardPhyID;
extern LPReadCardBlock		ReadCardBlock;
extern LPSetCardMainKey		SetCardMainKey;

#endif // _CARDMAN_UTIL_H