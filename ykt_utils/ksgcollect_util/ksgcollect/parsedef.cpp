#include "stdafx.h"
#include "parsedef.h"

parser_ops_t g_parser_ops[MAX_PARSER_COUNT];
int g_parser_count = 0;
std::map<std::string,std::string> dllMap;
std::map<std::string,std::string>::iterator mapIter;

typedef int (__stdcall* lp_parseHead)(char *head);
typedef int (__stdcall* lp_parseLine)(char *line,TRADE_SERIAL &tradeSerial);

int initDLL()
{
	HINSTANCE	hDLL;
	for (mapIter = dllMap.begin();mapIter != dllMap.end();mapIter++)
	{
		hDLL = LoadLibrary(mapIter->second.c_str());
		if (!hDLL)
			return -1;
		g_parser_ops[g_parser_count].parse_head = (lp_parseHead)GetProcAddress(hDLL,"parse_head");
		g_parser_ops[g_parser_count].parse_line = (lp_parseLine)GetProcAddress(hDLL,"parse_line");
		g_parser_count++;
	}
	return 0;
}