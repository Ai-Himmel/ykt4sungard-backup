extern "C" __stdcall int func_LoadSectorKey(unsigned char *cardid,unsigned char *_Key);
extern "C" __stdcall int func_ActiveCard(int ActiveMode,unsigned char *CardId);
extern "C" __stdcall int func_CloseCard();
extern "C" __stdcall int func_AntiColl( char *cardno );
extern "C" __stdcall void func_CloseComm();
extern "C" __stdcall int func_OpenComm( int port );
