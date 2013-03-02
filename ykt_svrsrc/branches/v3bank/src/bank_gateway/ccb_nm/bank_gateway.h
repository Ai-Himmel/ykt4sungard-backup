#ifndef __BANK_GATEWAY_H_
#define __BANK_GATEWAY_H_

#define HEAD_LEN        4
#define TRADECODE_LEN   4
#define TRADE_CHECK         "1003"
#define TRADE_BIND          "1011"
#define TRADE_UNBIND        "1012"

#define BANKCODE            "00"

typedef struct
{
    char drtp_ip[20];
    int drtp_port;
    int main_funcno;
    int drtp_timeout;
    int bank_lisnport;
    int bank_timeout;
}CONFIG_PARA;

#define  E_TRANS_NONSUPPORT        108116	//此功能暂不被支持

#endif