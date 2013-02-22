
#include <windows.h>
#include <stdio.h>

extern "C" __declspec(dllexport) int __stdcall gOpenCom(int nPort);
extern "C" __declspec(dllexport) int __stdcall gCloseCom();
extern "C" __declspec(dllexport) int __stdcall ZTCloseMagCard();
extern "C" __declspec(dllexport) int __stdcall ZTMagCardRead(char *pchTrk2,char *pchTrk3);
extern "C" __declspec(dllexport) int __stdcall ZTMagCardStart(int nTrackNum);

