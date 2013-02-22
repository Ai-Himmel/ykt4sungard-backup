#ifndef _KSG_PARSEDEF_H_
#define _KSG_PARSEDEF_H_

#include <string>
#include <map>

#pragma  pack(1)
enum { COSUMER_TYPE = 1, DEPOSIT_TYPE };

typedef struct {
	int serial_type;
	int serial_no;
	int card_no;
	char tx_date[9];
	char tx_time[7];
	char device_id[13];
	int in_balance;
	int out_balance;
	int trade_fee;
	int trade_count;
	int manage_fee;
	int tx_mark;
}TRADE_SERIAL;

typedef struct {
	int (__stdcall *parse_head)(char *head);
	int (__stdcall *parse_line)(char *line,TRADE_SERIAL &tradeSerial);
}parser_ops_t;

extern std::map<std::string,std::string> dllMap;

#define  MAX_PARSER_COUNT  10
extern parser_ops_t g_parser_ops[MAX_PARSER_COUNT];
extern int g_parser_count;

int initDLL();

#pragma pack()

#endif // _KSG_PARSEDEF_H_