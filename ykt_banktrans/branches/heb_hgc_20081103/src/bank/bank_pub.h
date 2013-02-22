#ifndef	__BANK_PUB_H__
#define	__BANK_PUB_H__

#include "tcp.h"
#include "bank.h"
#include <errno.h>
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank_gd.h"
#include "mac.h"
#include "Third_Mac.h"
#include "iso8583.h"

#pragma once

void Trace_Bank_Package_GSYH(BANK_GSYH_TRADE_STRUCT *pTransPak, char *stage);
void Trace_Bank_Package_ZGYH_R(BANK_ZGYH_TRADE_STRUCT_TRANS_REQ *pTransPak, char *stage);
void Trace_Bank_Package_ZGYH_A(BANK_ZGYH_TRADE_STRUCT_TRANS_ANS *pTransPak, char *stage);
int send_to_and_recv_from_bank(int const bank_id,char* pSend, int send_len,char* pRecv,int recv_len,ST_BANK_CONFIG *pBank);
void Trace_Bank_Package_YNXH(BANK_YNXH_TRADE_STRUCT_PACKET *pTransPak, char *stage);
void Trace_Bank_Package_YNNH(BANK_YNNH_TRADE_STRUCT_PACKET *pTransPak, char *stage);
void Trace_Bank_Package_HRBZH(BANK_HRBZH_TRADE_STRUCT_PACKET *pTransPak, char *stage);
int Get_Bank_Error_Code(void *pTransPak, int bank_id);

/*================================================================ 
* 函数名:      Trade_Package_YNXH
* 参数1:       [in or out] (BANK_YNXH_TRADE_STRUCT_PACKET *pTransPak)
*			   获取或者设置的报文内容
* 参数2:	   [in or out] (int trade_type) 交易类型: 查询,下账,冲正,对账
* 参数3:	   [in] (int packet_flag) 交易标识: 获取报文(0), 设置报文(1)
* 参数4:       [in] (ST_BANK_CONFIG *pBank) 银行全局配置参数结构
* 参数5:       [in] (INNER_TRANS_REQUEST * pNode) 界面参数结构
* 功能描述:    设置信合交易报文或者获取信合交易报文
* 返回值：     int, 正确返回0, 失败返回其他值
================================================================*/
int Trade_Package_YNXH(BANK_YNXH_TRADE_STRUCT_PACKET *pTransPak, int trade_type, int packet_flag, 
							  ST_BANK_CONFIG *pBank, INNER_TRANS_REQUEST * pNode);

/*================================================================ 
* 函数名:      Packet_Buf_Transform
* 参数1:       [in or out] (char *buf) 转换的buf数据流
* 参数2:	   [in or out] (void *packet) 银行的报文格式
* 参数3:	   [in] (int change_flag) 压包和解包标志: 例如0表示压包
* 			   (packet to buf), 1表示解包(buf to packet)
* 参数4:       [in] (int bank_id) 银行类别: 例如中国银行, 农业银行等
* 参数5:       [in] (int trade_type) 交易类型: 查询, 下账, 冲正, 对账等
* 参数6:       [in] (INNER_TRANS_REQUEST * pNode) 界面传入的结构参数
* 参数7:       [in] (int serial_no) 转帐或者冲正使用的流水号
* 功能描述:    对发往银行端数据进行压包和收到了银行端数据进行解包
* 返回值：     int, 正确返回0, 失败返回其他值
================================================================*/
int Packet_Buf_Transform(char *buf, void *packet, int change_flag, 
							  int bank_id, int trade_type, 
							  INNER_TRANS_REQUEST * pNode, int serial_no); 

void Trace_8583_Package(char *_8583_buf, int _8583_length, int format, char *msg);


#endif 
