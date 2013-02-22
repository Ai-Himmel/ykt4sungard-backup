#include "reg52.h"
#include <INTRINS.h>
#include "z18pos.h"
#include "Include/LibFuntion.h"
#include <string.h>
#include "stdio.h"
#include <stdlib.h>
#include "crc.h"
#include "communication.h"
#include "z18pos.h"

#if USE_INFRARED_COMM
// 红外模块处理
static uint8 z18infrared_open(COMM_TYPE_T *comm)
{
	if(comm->port_no > 1)
		return Z18_FAILED;
	SerialCtl_1(comm->port_no,comm->band);
	Init_Infrared_comm(comm->band);
	debug_string("open port[%d][%lu]\n",(uint16)comm->port_no,comm->band);
	return 0;
}
static uint8 z18infrared_close(COMM_TYPE_T *comm)
{
	debug_string("close port[%d]",(uint16)comm->port_no);
	return 0;
}
static uint16 z18infrared_send_data(COMM_TYPE_T *comm,uint16 len)
{
	uint16 i;
	//debug_string("send data[%d]\n",comm->buflen);
	if(comm->use_ext)
	{
		for(i = 0; i < comm->buflen; ++i)
			set_char_1(comm->buffer[i]);
		for(i = 0; i < comm->ext_buf_len; ++i)
			set_char_1(comm->ext_buffer[i]);
		//debug_string("cmd[%d]\n",(uint16)(comm->buflen+comm->ext_buf_len));
		//debug_hex(comm->buffer,comm->buflen);
		//debug_hex(comm->ext_buffer,comm->ext_buf_len);
	}
	else
	{
		// 发送成功
		for(i = 0;i < len;++i)
			set_char_1(comm->buffer[comm->buf_begin+(uint8)i]);
		debug_hex(comm->buffer+comm->buf_begin,len);
	}
	return i;
}
static uint8 z18infrared_recv_request(COMM_TYPE_T *comm)
{
	uint8 data b;
	uint8 data i;
	uint16 pack_len,recv_len;
	comm->buf_begin=0;
	// recv STX
	do
	{
		if(get_char_1(&(comm->buffer[0]))==0)
		{
			return 0;
		}
	}while(comm->buffer[0] != STX1);

	comm->buf_begin++;
	comm->ext_buf_len = 61;
	recv_len = 1;

	i = 0;
	debug_string("recv header\n");
	set_char_1(0x47);
	while(1)
	{	
		if(get_char_1(&b)==0)
		{
			if(get_char_1(&b)==0)
			{
				if(get_char_1(&b)==0)
				{
					//debug_string("i[%d][%d]\n",(uint16)i,recv_len);
					//debug_hex(comm->buffer,recv_len);
					break;
				}
			}
		}
		recv_len++;
		// 等待一下
		if(recv_len <= MAIN_PACK_LEN)
		{
			comm->buffer[comm->buf_begin++] = b;
		}
		else
		{
			/*
			if(recv_len-comm->buf_begin+61 > comm->ext_buf_len)
				return 0;
			*/
			comm->ext_buffer[comm->ext_buf_len] = b;
			comm->ext_buf_len++;
		}
		if(++i == 22)
		{
			set_char_1(0x47);
			i = 0;
		}
		if(recv_len == 3)
		{
			pack_len = get_2byte_int(comm->buffer+1);
		}
		else if(recv_len > 3)
		{
			// 接收完成
			if(recv_len - 3 >= pack_len)
				break;
		}
		//set_char_1(0x47);
	}
	if(recv_len < 6)
	{
		debug_string("pack len err,[%d]\n",recv_len);
		return 0;
	}
	pack_len = get_2byte_int(comm->buffer+1);
	if(pack_len < recv_len - 3)
	{
		debug_string("recv err,[%d][%d]\n",pack_len,recv_len);
		return 0;
	}
	if(recv_len <= MAIN_PACK_LEN)
	{
		if(comm->buffer[recv_len-1] != ETX1)
		{
			debug_string("recv buf ext1![%d]\n",recv_len);
			return 0;
		}
		comm->ext_buf_len = 0;
	}
	else
	{
		if(comm->ext_buffer[comm->ext_buf_len-1] != ETX1)
		{
			debug_string("recv buf ext1![%d]\n",recv_len);
			return 0;
		}
		// 将包体拷贝到 ext_buffer
		memcpy(comm->ext_buffer,comm->buffer+3,61);
		comm->use_ext = 1;
	}
	return 1;

}

static uint16 z18infrared_recv_data(COMM_TYPE_T *comm)
{
	return 0;
}
static uint16 z18infrared_recv_timeout(COMM_TYPE_T *comm)
{
	uint16 recv_len;
	uint16 i;
	//debug_string("recv str\n");
	for(i=0,recv_len=0;i<comm->timeout;++i)
	{
		recv_len+=z18infrared_recv_data(comm);
		if(recv_len >= comm->bufmaxlen
		   || recv_len >= comm->buflen)
			return recv_len;
		kng_sleep(1);
	}
	return recv_len;
}

uint8 register_infrared(COMM_TYPE_T *comm,COMM_OPERATION_T *op)
{
	debug_string("register infrared port\n");
	op->open = z18infrared_open;
	op->close = z18infrared_close;
	op->recv_data = z18infrared_recv_data;
	op->send_data = z18infrared_send_data;
	op->recv_timeout = z18infrared_recv_timeout;
	op->recv_request = z18infrared_recv_request;
	op->is_closed = NULL;
	return 0;
}
#endif
static uint8 z18comm_open(COMM_TYPE_T *comm)
{
	if(comm->port_no > 1)
		return Z18_FAILED;
	bp_SerialCtl(comm->port_no,comm->band);
	debug_string("open comm port[%d][%lu]\n",(uint16)comm->port_no,comm->band);
	return 0;

}
static uint8 z18comm_close(COMM_TYPE_T *comm)
{
	debug_string("close comm port[%d]\n",(uint16)comm->port_no);
	return 0;
}
static uint8 z18comm_recv_request(COMM_TYPE_T *comm)
{
	uint8 data b;
	uint8 data i;
	uint16 pack_len,recv_len;
	comm->buf_begin=0;
	// recv STX
	do
	{
		if(get_char(&(comm->buffer[0]))==0)
		{
			return 0;
		}
	}while(comm->buffer[0] != STX1);

	comm->buf_begin++;
	comm->ext_buf_len = 61;
	recv_len = 1;

	i = 0;
	set_char(0x47);
	while(1)
	{	
		if(get_char(&b)==0)
		{
			if(get_char(&b)==0)
			{
				if(get_char(&b)==0)
				{
					//debug_string("i[%d][%d]\n",(uint16)i,recv_len);
					//debug_hex(comm->buffer,recv_len);
					break;
				}
			}
		}
		recv_len++;
		// 等待一下
		if(recv_len <= MAIN_PACK_LEN)
		{
			comm->buffer[comm->buf_begin++] = b;
		}
		else
		{
			/*
			if(recv_len-comm->buf_begin+61 > comm->ext_buf_len)
				return 0;
			*/
			comm->ext_buffer[comm->ext_buf_len] = b;
			comm->ext_buf_len++;
		}
		if(++i == 22)
		{
			set_char(0x47);
			i = 0;
		}
		if(recv_len == 3)
		{
			pack_len = get_2byte_int(comm->buffer+1);
		}
		else if(recv_len > 3)
		{
			if(recv_len -3 >= pack_len )
				break;
		}
	}
	if(recv_len < 6)
	{
		debug_string("pack len err,[%d]\n",recv_len);
		return 0;
	}
	pack_len = get_2byte_int(comm->buffer+1);
	if(pack_len < recv_len - 3)
	{
		debug_string("recv err,[%d][%d]\n",pack_len,recv_len);
		return 0;
	}
	if(recv_len <= MAIN_PACK_LEN)
	{
		if(comm->buffer[recv_len-1] != ETX1)
		{
			debug_string("recv buf ext1![%d]\n",recv_len);
			return 0;
		}
		comm->ext_buf_len = 0;
	}
	else
	{
		if(comm->ext_buffer[comm->ext_buf_len-1] != ETX1)
		{
			debug_string("recv buf ext1![%d]\n",recv_len);
			return 0;
		}
		// 将包体拷贝到 ext_buffer
		memcpy(comm->ext_buffer,comm->buffer+3,61);
		comm->use_ext = 1;
	}
	return 1;
}
static uint16 z18comm_recv_data(COMM_TYPE_T *comm,uint16 len)
{
	uint8 i;
	uint8 b;
	if(get_char(&b))
	{
		comm->buffer[comm->buf_begin] = b;
		return 1;
	}
	return 0;
}
static uint16 z18comm_send_data(COMM_TYPE_T *comm,uint16 len)
{
	uint16 i;
	//debug_string("send data[%d]\n",comm->buflen);
	if(comm->use_ext)
	{
		for(i = 0; i < comm->buflen; ++i)
			set_char(comm->buffer[i]);
		for(i = 0; i < comm->ext_buf_len; ++i)
			set_char(comm->ext_buffer[i]);
	}
	else
	{
		// 发送成功
		for(i = 0;i < len;++i)
			set_char(comm->buffer[comm->buf_begin+(uint8)i]);
	}
	return i;
}
static uint16 z18comm_recv_timeout(COMM_TYPE_T *comm)
{
	uint16 recv_len;
	uint16 i;
	uint8 b;
	bit flag;
	//debug_string("recv str\n");
	for(i=0,recv_len=0,flag=0;i<comm->timeout;++i)
	{
		while(1)
		{
			if(get_char(&b)==0)
			{
				continue;
			}
			comm->buffer[recv_len++] = b;
		}
	}
	return recv_len;

}
uint8 register_commport(COMM_TYPE_T *comm,COMM_OPERATION_T *op)
{
	debug_string("register comm port\n");
	op->open = z18comm_open;
	op->close = z18comm_close;
	op->recv_data = z18comm_recv_data;
	op->send_data = z18comm_send_data;
	op->recv_timeout = z18comm_recv_timeout;
	op->is_closed = NULL;
	op->recv_request = z18comm_recv_request;
	return 0;
}

#if USE_GPRS
uint8 register_gprs(COMM_TYPE_T *comm,COMM_OPERATION_T *op)
{
	return register_commport(comm,op);
}

uint8 register_wifi(COMM_TYPE_T *comm,COMM_OPERATION_T *op)
{
	return 0;
}

#endif


