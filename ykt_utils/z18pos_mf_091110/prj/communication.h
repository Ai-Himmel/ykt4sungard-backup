#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include "include/datatype.h"
#include <stdarg.h>
#define	STX1	0xC0
#define	ETX1	0xC1
#define	STX2	0xC2
#define	ETX2	0xC3

#define MAIN_PACK_LEN 64
typedef struct {
	uint8 ver; // 通讯版本
	uint8 port_no; // 端口号
	uint8 port_type; // 通讯类别， 1 串口 2 红外 3 GRPS 4 WIFI
	uint32 band;
	uint8 *buffer;
	uint8 *buffer2;
	uint16 buf_begin;
	uint16 buflen;
	uint16 bufmaxlen;
	uint16 timeout;
	uint8 use_ext;
	uint8 *ext_buffer;
	uint16 ext_buf_len;
}COMM_TYPE_T;

typedef struct {
	uint8 (*open)(COMM_TYPE_T *comm);
	uint8 (*close)(COMM_TYPE_T *comm);
	uint16 (*send_data)(COMM_TYPE_T *comm,uint16 len);
	uint16 (*send_data_ext)(COMM_TYPE_T *comm);
	uint16 (*recv_data)(COMM_TYPE_T *comm,uint16 len);
	uint16 (*recv_timeout)(COMM_TYPE_T *comm);
	uint8 (*recv_request)(COMM_TYPE_T *comm);
	uint8 (*is_closed)(COMM_TYPE_T *comm);
}COMM_OPERATION_T;

// 通讯操作接口
// extern COMM_OPERATION_T *g_comm_op;

uint8 register_infrared(COMM_TYPE_T *comm,COMM_OPERATION_T *op);
uint8 register_commport(COMM_TYPE_T *comm,COMM_OPERATION_T *op);
uint8 register_gprs(COMM_TYPE_T *comm,COMM_OPERATION_T *op);
uint8 register_wifi(COMM_TYPE_T *comm,COMM_OPERATION_T *op);


#endif // _COMMUNICATION_H_


