// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HDPARSER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HDPARSER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#include "../ksgcollect/parsedef.h."


#ifdef HDPARSER_EXPORTS	
#define HDPARSER_API __declspec(dllexport)
#else
#define HDPARSER_API __declspec(dllimport)
#endif

// This class is exported from the hdparser.dll
class HDPARSER_API Chdparser {
public:
	Chdparser(void);
	// TODO: add your methods here.
};

extern HDPARSER_API int nhdparser;

#ifdef __cplusplus
extern "C" {
#endif 
HDPARSER_API int fnhdparser(void);


HDPARSER_API int parse_head(char *pFileName);

HDPARSER_API int parse_line(TRADE_SERIAL &tradeSerial);

#ifdef __cplusplus
}
#endif 