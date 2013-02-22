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
#include "gprs.h"

static uint8 gprs_logon(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op)
{
	uint16 len;
    uint8 i;
	
    
	len = 0;
    comm->timeout = 1000;
	// TCP IP 
	print_line(1,20,"initial dail");
	strcpy(comm->buffer,"AT\r");
    len = strlen(comm->buffer);
    comm->buf_begin = 0;
    op->send_data(comm,len);
    len = 20;
    if(op->recv_data(comm,len)==0)
    {
        print_line(1,30,"initial error!");
        return KNG_POS_DAIL;
    }
    
    comm->buffer[comm->buf_begin] = 0;
   
    if(strstr(comm->buffer, "\r\nOK\r\n") == NULL)
	{
        print_line(1,30,"AT error");
		return KNG_POS_DAIL;
	}
    
	// send & recv
	print_line(1,20,"dail cmnet...");

    //print_line(1,1,"b[%04x]",op->recv_data);
    //print_line(2,20,"b[%04x]",op->send_data);

	strcpy(comm->buffer,"AT+MIPCALL=1,\"cmnet\"\r");
	len = strlen(comm->buffer);
    comm->buf_begin = 0;
	op->send_data(comm,len);
    len = 50;
    //print_line(1,1,"recv req");
    // ÅÐ¶Ï²¦ºÅ³É¹¦
    if(op->recv_data(comm,len)==0)
    {
        print_line(1,20,"fail mipcall");
        return KNG_POS_DAIL;
    }
    comm->buffer[comm->buf_begin] = 0;
    //print_line(2,30,"[%s]",comm->buffer);
    if(strstr(comm->buffer, "\r\nOK\r\n") == NULL)
	{
        print_line(1,10,"ipcall error");
		return KNG_POS_DAIL;
	}

    print_line(1,0,"recv mipcall");
    if(strstr(comm->buffer,"MIPCALL:") == NULL)
    {
        comm->buf_begin = 0;
        len = 50;
        for(i=0;i < 3;++i)
        {
            if(op->recv_data(comm,len)==0)
            {
                if(i >= 2)
                {
                    print_line(1,3,"mipcall error");
                    return KNG_POS_DAIL;
                }
            }
            else
            {
                comm->buffer[comm->buf_begin] = 0;
                //print_line(2,30,"len[%d]",comm->buf_begin);
                //print_line(2,30,"[%s]",comm->buffer);
                if(strstr(comm->buffer, "MIPCALL:") != NULL)
                {
                    print_line("mipcall ok");
                    return 0;
                }
            }
        }
    }
    return 0;
}

static uint8 gprs_connect_svr(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op)
{
    return 0;
}
uint8 gprs_connect(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op)
{
    uint8 ret;
    COMM_OPERATION_T xdata my_op;
    memset(g_rec_data,0,sizeof g_rec_data);
	comm->buffer = g_rec_data;
    comm->use_ext = 0;
    comm->bufmaxlen = sizeof(g_rec_data);
    // connect to server 
    //my_op = *op;
    ret = gprs_logon(comm,op);
    if(ret)
    {
        print_line(1,30,"conn cmnet err");
        return ret;
    }
    else
    {
        print_line(1,30,"connect success");
    }
    return 0;
    
}
uint8 gprs_disconnect(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op)
{
    // disconnect from server
    uint16 len;
    comm->buf_begin = 0;
    strcpy(comm->buffer,"AT+MIPCALL=0\r");
    len = strlen(comm->buffer);
    op->send_data(comm,len);
    
    return 0;
}
