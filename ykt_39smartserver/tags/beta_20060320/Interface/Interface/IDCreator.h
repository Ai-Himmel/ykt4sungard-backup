#ifndef IDCREATOR_H
#define IDCREATOR_H

#ifdef  IDCREATOR_EXPORTS
#define KSID_API __declspec (dllexport)
#else
#define KSID_API __declspec (dllimport)

#ifdef  _DEBUG
#pragma comment(lib, "..\\lib\\IDCreatorD.lib")
#pragma message("Automatically link IDCreatorD.dll")
#else
#pragma comment(lib, "..\\lib\\IDCreator.lib")
#pragma message("Automatically link IDCreator.dll")
#endif
#endif

KSID_API bool InitCreater(char *szFile);
KSID_API long CreateID(char *szPzdm, char *szJgq);
bool UpdateFile(char *szPzdm, int ikey);

#endif
