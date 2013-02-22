#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include "include/datatype.h"
#include "config.h"
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
	uint8 data *buffer;
	uint8 data *buffer2;
	uint16 buf_begin;
	uint16 buflen;
	uint16 bufmaxlen;
	uint16 timeout;
	uint8 use_ext;
	uint8 xdata *ext_buffer;
	uint16 ext_buf_len;
}COMM_TYPE_T;

typedef struct {
	uint8 (*open)(COMM_TYPE_T xdata *comm);
	uint8 (*close)(COMM_TYPE_T xdata *comm);
	uint16 (*send_data)(COMM_TYPE_T xdata *comm,uint16 len);
	uint16 (*recv_data)(COMM_TYPE_T xdata *comm,uint16 len);
	uint8 (*recv_request)(COMM_TYPE_T xdata *comm);
	uint8 (*is_closed)(COMM_TYPE_T xdata *comm);
}COMM_OPERATION_T;

extern COMM_OPERATION_T code g_COM_op;
#if USE_INFRARED_COMM
extern COMM_OPERATION_T code g_Infrared_op;
#endif

// 通讯操作接口
// extern COMM_OPERATION_T *g_comm_op;

#if USE_GPRS
uint8 gprs_connect(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op);
uint8 gprs_disconnect(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op);
uint8 gprs_send_record(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op);
uint8 gprs_download_black(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op);


#endif 


#if 0

#if USE_INFRARED_COMM
uint8 register_infrared(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op);
#endif
uint8 register_commport(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op);
#if USE_GPRS
uint8 register_gprs(COMM_TYPE_T xdata *comm, COMM_OPERATION_T code *op);
uint8 register_wifi(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op);
#endif
#endif

#endif // _COMMUNICATION_H_


