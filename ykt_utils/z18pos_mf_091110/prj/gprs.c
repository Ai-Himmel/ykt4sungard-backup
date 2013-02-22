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


static uint8 send_and_recv(COMM_TYPE_T *comm)
{
}

uint8 gprs_logon(COMM_TYPE_T *comm)
{
	uin16 len;
	memset(g_global_buf,0,sizeof g_global_buf);
	comm->ext_buffer = g_global_buf;
	len = 0;
	// TCP IP 
	strcpy(g_global_buf+len,"AT\r");
	// send & recv
	print_line(1,1,"dail cmnet...");
	send_and_recv(comm);

	strcpy(g_global_buf+len,"AT+MIPCALL=1,\"");
	strcat(g_global_buf,"cmnet\"\r");

	len = strlen(g_global_buf);
	comm->send_data(comm,len);
    // ÅÐ¶Ï²¦ºÅ³É¹¦
    comm->recv_data(comm);

    return 0;
}

uint8 gprs_connect()
{
    // connect to server 
}
uint8 gprs_disconnect()
{
    // disconnect from server
    
}
