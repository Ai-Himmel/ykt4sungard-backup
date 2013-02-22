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
#include "consume.h"


#define OLD_INFRARED 1

//typedef uint8 (code *getchar_func)(uint8 *b);
//typedef uint8 (code *setchar_func)(uint8 b);


#if USE_INFRARED_COMM
// 红外模块处理
static uint8 z18infrared_open(COMM_TYPE_T xdata *comm)
{
	if(comm->port_no > 1)
		return Z18_FAILED;
	SerialCtl_1(comm->port_no,comm->band);
	Init_Infrared_comm(comm->band);
	debug_string(("open port[%d][%lu]\n",(uint16)comm->port_no,comm->band));
	return 0;
}
static uint8 z18infrared_close(COMM_TYPE_T xdata *comm)
{
	debug_string(("close port[%d]",(uint16)comm->port_no));
	return 0;
}
#if OLD_INFRARED
static uint16 z18infrared_send_data(COMM_TYPE_T xdata *comm,uint16 len)
{
	uint16 i;
	//debug_string(("send data[%d]\n",comm->buflen));
	//print_line(1,20,"send data...");
	if(comm->use_ext)
	{
		for(i = 0; i < comm->buflen; ++i)
			set_char_1(comm->buffer[i]);
		for(i = 0; i < comm->ext_buf_len; ++i)
			set_char_1(comm->ext_buffer[i]);
		//debug_string(("cmd[%d]\n",(uint16)(comm->buflen+comm->ext_buf_len)));
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
static uint8 z18infrared_recv_request(COMM_TYPE_T xdata *comm)
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
	debug_string(("recv header\n"));
	set_char_1(0x47);
	while(1)
	{	
		if(get_char_1(&b)==0)
		{
			//debug_string(("i[%d][%d]\n",(uint16)i,recv_len));
			//debug_hex(comm->buffer,recv_len);
			break;
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
		debug_string(("pack len err,[%d]\n",recv_len));
		return 0;
	}
	pack_len = get_2byte_int(comm->buffer+1);
	if(pack_len < recv_len - 3)
	{
		debug_string(("recv err,[%d][%d]\n",pack_len,recv_len));
		return 0;
	}
	if(recv_len <= MAIN_PACK_LEN)
	{
		if(comm->buffer[recv_len-1] != ETX1)
		{
			debug_string(("recv buf ext1![%d]\n",recv_len));
			return 0;
		}
		comm->ext_buf_len = 0;
	}
	else
	{
		if(comm->ext_buffer[comm->ext_buf_len-1] != ETX1)
		{
			debug_string(("recv buf ext1![%d]\n",recv_len));
			return 0;
		}
		// 将包体拷贝到 ext_buffer
		memcpy(comm->ext_buffer,comm->buffer+3,61);
		comm->use_ext = 1;
	}
	return 1;

}

static uint16 z18infrared_recv_data(COMM_TYPE_T xdata *comm)
{
	return 0;
}

#endif

#if 0
uint8 register_infrared(COMM_TYPE_T *comm,COMM_OPERATION_T *op)
{
	debug_string(("register infrared port\n"));
	op->open = z18infrared_open;
	op->close = z18infrared_close;
	op->recv_data = z18infrared_recv_data;
	op->send_data = z18infrared_send_data;
	//op->recv_timeout = z18infrared_recv_timeout;
	op->recv_request = z18infrared_recv_request;
	op->is_closed = NULL;
	return 0;
}
#endif

#endif
static uint8 z18comm_open(COMM_TYPE_T xdata *comm)
{
	if(comm->port_no > 1)
		return Z18_FAILED;
	bp_SerialCtl(comm->port_no,comm->band);
	debug_string(("open comm port[%d][%lu]\n",(uint16)comm->port_no,comm->band));
	return 0;

}
static uint8 z18comm_close(COMM_TYPE_T xdata *comm)
{
	debug_string(("close comm port[%d]\n",(uint16)comm->port_no));
	return 0;
}
static uint8 z18comm_recv_request(COMM_TYPE_T xdata *comm)
{
	uint8 data b;
	uint8 data i;
	uint16 pack_len,recv_len;
	comm->buf_begin=0;
	// recv STX
	do
	{
		//if((*g_getchar_func[g_com_func])(&(comm->buffer[0]))==0)
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
//		if((*g_getchar_func[g_com_func])(&b)==0)
        if(get_char(&b)==0)
		{
			//debug_string(("i[%d][%d]\n",(uint16)i,recv_len));
			//debug_hex(comm->buffer,recv_len);
			break;
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
			//(*g_setchar_func[g_com_func])(0x47);
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
		debug_string(("pack len err,[%d]\n",recv_len));
		return 0;
	}
	pack_len = get_2byte_int(comm->buffer+1);
	if(pack_len < recv_len - 3)
	{
		debug_string(("recv err,[%d][%d]\n",pack_len,recv_len));
		return 0;
	}
	if(recv_len <= MAIN_PACK_LEN)
	{
		if(comm->buffer[recv_len-1] != ETX1)
		{
			debug_string(("recv buf ext1![%d]\n",recv_len));
			return 0;
		}
		comm->ext_buf_len = 0;
	}
	else
	{
		if(comm->ext_buffer[comm->ext_buf_len-1] != ETX1)
		{
			debug_string(("recv buf ext1![%d]\n",recv_len));
			return 0;
		}
		// 将包体拷贝到 ext_buffer
		memcpy(comm->ext_buffer,comm->buffer+3,61);
		comm->use_ext = 1;
	}
	return 1;
}
static uint16 z18comm_recv_data(COMM_TYPE_T xdata *comm,uint16 len)
{
	uint8 b;
    uint16 times;
   // for(i=0;i<1;++i)
   // {
   times=0;
   //print_line(1,30,"begin recv");
   for(;;)
   {
    	if(get_char(&b))
    	{
            
            if(len <= comm->bufmaxlen)
            {
    		    comm->buffer[comm->buf_begin++] = b;
                if(comm->buf_begin >= len)
                {
                    comm->use_ext = 0;
                    return comm->buf_begin;
                }
            }
            else
            {
                
                comm->ext_buffer[comm->buf_begin++] = b;
                if(comm->buf_begin>= len)
                {
                    comm->use_ext = 1;
                    return comm->buf_begin;
                }
            }
            times=comm->timeout;
    	}
        else
        {
            //print_line(1,10,"no data");
            if(++times<comm->timeout)
            {
                delay_1ms(10);
                continue;
            }
            else break;
        }
   }
    //}
	return comm->buf_begin;
}
static uint16 z18comm_send_data(COMM_TYPE_T xdata *comm,uint16 len)
{
	uint16 i;
	//debug_string(("send data[%d]\n",comm->buflen));
	//print_line(1,20,"comm send data");
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


#if 0
static uint16 z18comm_recv_timeout(COMM_TYPE_T xdata *comm)
{
	uint16 recv_len;
	uint16 i;
	uint8 b;
	bit flag;
	//debug_string(("recv str\n"));
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
#endif

#if 0
uint8 register_commport(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op)
{
	debug_string(("register comm port\n"));
	op->open = z18comm_open;
	op->close = z18comm_close;
	op->send_data = z18comm_send_data;
	//op->recv_timeout = z18comm_recv_timeout;
	op->is_closed = NULL;
	op->recv_request = z18comm_recv_request;
    op->recv_data = z18comm_recv_data;
	return 0;
}

#if USE_GPRS
uint8 register_gprs(COMM_TYPE_T xdata *comm, COMM_OPERATION_T code *op)
{
    print_line(1,0,"register gprs");
	return register_commport(comm,op);
}

uint8 register_wifi(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op)
{
	return 0;
}

#endif

#endif

#if USE_GPRS

#define MAX_GPRS_BUF 64

static uint8 gprs_sendcmd(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op)
{
    uint16 len;
    len = strlen(comm->buffer);
    comm->buf_begin = 0;
    op->send_data(comm,len);
    if(op->recv_data(comm,MAX_GPRS_BUF)==0)
    {
        return KNG_POS_DAIL;
    }
    delay_1ms(30);
    comm->buffer[comm->buf_begin] = 0;
    if(strstr(comm->buffer,"OK")==NULL)
    {
        return KNG_POS_DAIL_ERR;
    }
    return 0;
}

static uint8 gprs_netsend(COMM_TYPE_T xdata *comm,uint8 xdata *buf,uint8 len,uint8 xdata *outbuf,COMM_OPERATION_T code *op)
{
    uint8 *p;
    uint16 i;
    //uint8 xdata temp[5];
    comm->buflen = 0;
    comm->bufmaxlen = 64;
    comm->use_ext = 1;
    memset(comm->buffer,0,comm->bufmaxlen);
    memset(comm->ext_buffer,0,256);
    sprintf(comm->ext_buffer,"AT+MIPSEND=%d,\"",(uint16)g_z18pos.local_sock);
    comm->ext_buf_len = strlen(comm->ext_buffer);
    hex2str(buf,len,comm->ext_buffer+comm->ext_buf_len);
    comm->ext_buf_len += len<<1;
    strcpy(comm->ext_buffer+comm->ext_buf_len,"\"\r");
    comm->ext_buf_len+=2;
    comm->ext_buffer[comm->ext_buf_len]=0;
//    print_line(1,40,"1[%s]",comm->ext_buffer);
//    memcpy(comm->buffer,comm->ext_buffer,comm->ext_buf_len);
//    comm->buflen = comm->ext_buf_len;
//    comm->use_ext = 0;
    comm->buf_begin = 0;
    op->send_data(comm,comm->ext_buf_len);
    comm->buflen = 0;
    comm->ext_buf_len = 340;
    delay_1ms(50);
    if(op->recv_data(comm,340)==0)
    {
        print_line(1,20,"recv err1");
        return KNG_POS_DAIL_ERR;
    }
    comm->ext_buffer[comm->buf_begin] = 0;
    //print_line(1,40,"recv ok[%d]",comm->buf_begin);
    //print_line(1,40,"recv ok[%s]",comm->ext_buffer);
    if(strstr(comm->ext_buffer,"OK")==NULL)
    {
        //print_line(1,20,"recv err2[%d]",comm->buf_begin);
        return KNG_POS_DAIL_ERR;
    }
    
    sprintf(comm->ext_buffer,"AT+MIPPUSH=%d\r",(uint16)g_z18pos.local_sock);
    comm->use_ext = 1;
    op->send_data(comm,comm->ext_buf_len);
    op->recv_data(comm,20);
    delay_1ms(50);
    comm->buf_begin = 0;
    op->recv_data(comm,340);
    comm->ext_buffer[comm->buf_begin] = 0;
    //print_line(1,60,"3[%s]",comm->ext_buffer);
    if((p=strstr(comm->ext_buffer,"+MIPRTCP"))==NULL)
    {
        print_line(1,20,"recv err3");
        return KNG_POS_GPRS_RECV;
    }
#if 0
    i = 0;
    while(p[i] != ',' && p[i] != '\r') ++i;
    j = i+1;
    while(p[j] != ',' && p[j] != 0) ++j;
    if(j > i)
    {
        memset(temp,0,sizeof temp);
        memcpy(temp,p+i+1,j-i);
        ret = atoi(temp);
        if(ret > 0)
        {
            // 没有接收完
            return KNG_POS_GPRS_RECV;
        }
        i = i+1;
        while(p[i] != ',' && p[i] != 0) ++i;
        if(p[i] == 0)
        {
            return KNG_POS_GPRS_RECV;
        }
        str2hex(p+i+1,comm->ext_buf_len-i-1,outbuf);
        return KNG_POS_GPRS_RECV;
    }
#else
    i = comm->buf_begin-1;
    while(p[i]!=',' && i > 0) --i; 
    if(i == 0)
        return KNG_POS_DAIL_ERR;
    str2hex(p+i+1,comm->buf_begin-i,outbuf);
    //print_line(1,60,"[%s",p+i+1);
#endif
    
    return 0;
}

uint8 gprs_send_record(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op)
{
#if 1
    uint32 addr;
    uint8 ret,retries;
    uint16 t;
    uint8 xdata rec_buf[80];
    uint8 xdata recv_buf[20];
    t = get_serial_count();
    if(t == 0)
	{
		//KNG_AUDIO(AU_COL_FINISH,Z18_AUDIO_DELAY);
		goto L_UPDTIME;
		//return 0;
	}
    rec_buf[0] = STX1;
    //set_2byte_int(64+6,rec_buf+1);
    set_2byte_int(48+6,rec_buf+1);
    rec_buf[3] = 0x70; // 上传流水
    rec_buf[4] = 0x99;
    rec_buf[5] = 0x01;
    rec_buf[6] = 48; // 64 - 16
    rec_buf[56] = ETX1;//rec_buf[72] = ETX1;
    retries = 3;
    while(get_serial_count()!=0)
    {
        if(g_z18pos.rec_rd_ptr == 0x00)
            addr = POS_RECORD_BEGIN_ADDR;
        else
            addr = g_z18pos.rec_rd_ptr;
        if(EeSysRead(addr,64,rec_buf+7)!=Z18_OK)
            return KNG_POS_HARDWARE_ERROR;
        //rec_buf[71] = calc_sum(rec_buf+3,68);
        rec_buf[55] = calc_sum(rec_buf+3,52);
        rec_buf[56] = ETX1;
        //print_line(1,10,"send record[%lu]",addr);
        
        if(gprs_netsend(comm,rec_buf,57 /* 73-16 */,recv_buf,op)==0)
        {
            //print_line(1,50,"2[%x][%x]",(uint16)recv_buf[3],(uint16)recv_buf[4]);
            // 检查返回的流水号
            if(memcmp(rec_buf+7+5,recv_buf+6,4)==0 && recv_buf[3] == 0x70 && recv_buf[4] == 0x00)
            {
                // 采集成功
                ret = update_record_read_ptr();
                if(ret!=0)
                    return ret;
                //print_line(1,0,"collect succ");
                retries = 3;
            }
            else
            {
                // retry
                if(--retries==0) return KNG_POS_DAIL_ERR;
            }
        }
        else
        {
            print_line(1,30,"upload rec err");
            return KNG_POS_DAIL;
        }
        
    }

L_UPDTIME:
    // 更新采集时间
    if(g_z18pos.uncoll_days>0)
    {
        ReadRtcTime(rec_buf);
    	calc_not(rec_buf+1,3,rec_buf+4);
    	if(EeSysWrite(POS_COL_DATE_ADDR,6,rec_buf+1)!=Z18_OK)
    	{
    		return KNG_POS_HARDWARE_ERROR;
    	}
    	g_z18pos.uncoll_days = 0;
    }
    if(t>0)
    {
    	KNG_AUDIO(AU_COL_FINISH,Z18_AUDIO_DELAY_100);
    }
#else
    uint8 xdata buf[64];
    strcpy(buf,"DD");
    gprs_netsend(comm,buf,2,buf,op);
#endif
    return 0;
}
uint8 gprs_download_black(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op)
{
    uint8 ret,retries,i,j;
    uint8 xdata rec_buf[30];
    uint8 xdata recv_buf[80];
    rec_buf[0] = STX1;
    //set_2byte_int(64+6,rec_buf+1);
    set_2byte_int(10+6,rec_buf+1);
    rec_buf[3] = 0x71; // 下载黑名单
    rec_buf[4] = 0x99;
    rec_buf[5] = 0x01;
    rec_buf[6] = 10; // 64 - 16
    rec_buf[18] = ETX1;//rec_buf[72] = ETX1;
    retries = 0;
    do{
        memcpy(rec_buf+7,g_z18pos.device_id,4);
        memcpy(rec_buf+11,g_z18pos.blk_ver,6);
        rec_buf[17] = calc_sum(rec_buf+3,14);
        print_line(1,0,"download blk...");
        retries++;
        if(gprs_netsend(comm,rec_buf,19,recv_buf,op)==0)
        {
            //print_line(1,40,"b[%X][%X]",(uint16)recv_buf[3],(uint16)recv_buf[4]);   
            if(recv_buf[3] == 0x71)
            {
                if(recv_buf[4] == 0x5D)
                {
                    //print_line(1,20,"dl blk succ");
                    return 0;
                }
                else if(recv_buf[4] != 0x00)
                {
                    if(retries<3) continue;
                    else break;
                }
                else
                {
                    // TEST : 多条名单处理
                    // 更新黑名单
                    j = recv_buf[5]-7;
                    for(i = 0;i < j;i+=4)
                    {
                        ret = do_update_blksheet(recv_buf+6+i);
                        if(ret)
                            return ret;
                    }
                    ret = do_update_blksheet_ver(recv_buf+6+i);
                    if(ret)
                        break;
                    // 没有黑名单了
                    if(recv_buf[i+6+6]==0x00)
                    {
                        KNG_AUDIO(AU_DING,Z18_AUDIO_DELAY);
                        return 0;
                    }
                    retries = 0;
                }
            }
            else
                return KNG_POS_DAIL;
        }
        else
        {
            print_line(1,0,"blk err...");
            if(retries >= 3) return KNG_POS_DAIL;;
        }
    }while(1);
    return ret;
}
static uint8 gprs_logon(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op)
{
	uint16 len;
 
	len = 0;
    comm->timeout = 1000;
	// TCP IP 
	print_line(1,20,"initial dail");
	strcpy(comm->buffer,"AT\r");
    if(gprs_sendcmd(comm,op))
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

    gprs_sendcmd(comm,op);
    /*
    if(gprs_sendcmd(comm,op))
	{
        print_line(1,10,"ipcall error");
	//	return KNG_POS_DAIL;
	}
    */
    //print_line(1,0,"recv mipcall");
    #if 0
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
                    print_line(1,0,"mipcall ok");
                    return 0;
                }
            }
        }
    }
    #endif
    delay_1ms(50);
    return 0;
}

#define GPRS_MAX_SOCKET 4

//static uint8 xdata grps_conn_cmd[]="AT+MIPOPEN=%d,%d,\"%d.%d.%d.%d\",%d,0\r";

static uint8 gprs_connect_svr(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op)
{

    if(memcmp(g_z18pos.svr_ip,"\0x00\0x00\0x00\0x00",4)==0 ||
        g_z18pos.svr_port == 0)
    {
        return KNG_POS_PARAM_ERROR;
    }
    comm->timeout = 100;
    print_line(1,0,"conn svr ...");
    g_z18pos.local_port = 1234;
    for(g_z18pos.local_sock= 1;g_z18pos.local_sock <= GPRS_MAX_SOCKET;++g_z18pos.local_sock)
    {
        sprintf(comm->buffer,"AT+MIPOPEN=%d,%d,\"%d.%d.%d.%d\",%d,0\r",
            (uint16)g_z18pos.local_sock,g_z18pos.local_port,
            (uint16)g_z18pos.svr_ip[0],(uint16)g_z18pos.svr_ip[1],
            (uint16)g_z18pos.svr_ip[2],(uint16)g_z18pos.svr_ip[3],
            g_z18pos.svr_port);
        if(gprs_sendcmd(comm,op))
        {
            sprintf(comm->buffer,"AT+MIPCLOSE=%d\r",(uint16)g_z18pos.local_sock);
            gprs_sendcmd(comm,op);
            //print_line(1,1,"open sock err[%d]",(uint16)g_z18pos.local_sock);
            g_z18pos.local_port++;
        }
        else
        {
            break;
        }
    }
    if(g_z18pos.local_sock > GPRS_MAX_SOCKET)
    {
        g_z18pos.local_sock = 0;
        print_line(1,30,"mipopen error");
        return KNG_POS_DAIL;
    }

    //print_line(1,0,"mipsets");
    #if 0
    sprintf(comm->buffer,"AT+MIPSETS=%d,340\r",(uint16)g_z18pos.local_sock);
    if(gprs_sendcmd(comm,op))
    {
        print_line(1,30,"mipsets error");
        return KNG_POS_DAIL;
    }
    #endif
    // now ready for send/recieve data 

    //FIXME: send test data
    /*
    print_line(1,0,"send data...");
    sprintf(comm->buffer,"AT+MIPSEND=%d,\"4444\"\r",(uint16)g_z18pos.local_sock);
    if(gprs_sendcmd(comm,op))
    {
        print_line(1,30,"mipsend error");
        return KNG_POS_DAIL;
    }

    print_line(1,0,"push data");
    sprintf(comm->buffer,"AT+MIPPUSH=%d\r",(uint16)g_z18pos.local_sock);
    if(gprs_sendcmd(comm,op))
    {
        print_line(1,30,"mippush error");
        return KNG_POS_DAIL;
    }
    */
    
    return 0;
}
uint8 gprs_connect(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op)
{
    uint8 ret;
    memset(g_rec_data,0,sizeof g_rec_data);
	comm->buffer = g_rec_data;
    comm->use_ext = 0;
    comm->bufmaxlen = sizeof(g_rec_data);
    memset(g_global_buf,0,sizeof g_global_buf);
    comm->ext_buffer = g_global_buf;
    comm->ext_buf_len = sizeof(g_global_buf);
    // connect to server 
    //my_op = *op;
    ret = gprs_logon(comm,op);
    if(ret)
    {
        print_line(1,30,"conn cmnet err");
        return ret;
    }
    if(gprs_connect_svr(comm,op))
    {
        return KNG_POS_DAIL;
    }
    return 0;
    
}
uint8 gprs_disconnect(COMM_TYPE_T xdata *comm,COMM_OPERATION_T code *op)
{
    // disconnect from server
    uint8 i;
    for(i = 1;i<=GPRS_MAX_SOCKET;++i)
    {
    //if(g_z18pos.local_sock>=1 && g_z18pos.local_sock <= 4)
    //{
        sprintf(comm->buffer,"AT+MIPCLOSE=%d\r",(uint16)i);
        gprs_sendcmd(comm,op);
        
        //print_line(1,3,"mipclose...");
    //}
    }
    //print_line(1,20,"mipcall close");
    strcpy(comm->buffer,"AT+MIPCALL=0\r");
    gprs_sendcmd(comm,op);
    return 0;
}

#endif

COMM_OPERATION_T code g_COM_op = 
{
    z18comm_open,
    z18comm_close,
    z18comm_send_data,
    z18comm_recv_data,
    z18comm_recv_request,
    NULL
};

#if USE_INFRARED_COMM
#if OLD_INFRARED
COMM_OPERATION_T code g_Infrared_op = 
{
    z18infrared_open,
    z18infrared_close,
    z18infrared_send_data,
    z18infrared_recv_data,
    z18infrared_recv_request,
    NULL
};
#else
/*
COMM_OPERATION_T code g_Infrared_op = 
{
    z18infrared_open,
    z18infrared_close,
    z18comm_send_data,
    z18comm_recv_data,
    z18comm_recv_request,
    NULL
};
*/
#endif
#endif



