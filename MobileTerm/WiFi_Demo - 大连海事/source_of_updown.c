/******************************************************************************************
Copyright (c)   2008-2058	Shenzhen Smart Card Technology CO.,LTD.

File:			main.c

Version:		V1.0

Author:			Sail.5

Created:		2009.01.08

Compiler:		ARM Developer Suite v1.2 (ADS1.2)

Description:	

*******************************************************************************************/
#include "api.h"
#include "usb.h"
#include "D12ci.h"

static void CalCrc16_13239(unsigned char* input, unsigned char* Crc16,unsigned long len)  
{												// ISO/IEC 13239 CRC计算 (x^16+x^12+x^5+1)
	unsigned short 	temp=0xFFFF;
	unsigned long 	i;
	int		j;

	for( i=0; i<len; i++ )
	{	
		temp = temp ^((unsigned short)input[i]);
	  	for (j = 0; j < 8; j++)
	  	{
			if (temp & 0x0001)
			{
		  		temp = (temp >> 1) ^ 0x8408;
	        	}
			else
			{
		 		temp = (temp >> 1);
			}
	  	}
	}
	
	Crc16[0] = (char)temp;
  	Crc16[1] = (char)(temp>>8);  	
}

static short UART_Wait_Char(unsigned short delay)
{
	typ_UART_stat_word Ustat;
	
	SPT_set(0);
  	SPT_set(delay);
  	do
  	{
    		Ustat.l_word = UART_Stat();
    		if (Ustat.bits.buff_data_available)
      			return UART_Rev_Char();
  	}while(SPT_read());

  	return -1;	
}

int	EXT_Up_232(unsigned char *file_buf,unsigned long file_len)
{
	short			ch;							// 接收返回值
	short			ret = -1;					// 函数返回值
	
	int				blk_cnt;					// 块数量
	int				blk_res;					// 不足1024字节的剩余字节数
	int				blk_idx;					// 循环变量
	int				chr_idx;					// 块内循环变量
	int				cnt_now;					// 本次发送字节数
	
	unsigned char	crcbuf[4];					// 校验字节
	unsigned char 	recvbuf[4];					// 接收缓冲区
	unsigned char 	tmpbuf[4];					// 临时缓冲区

	UART_Init(UART_232_ON|UART_BAUD_115200);

again:
	if(KEY_Read() == KEY_F1)	goto end;
	if( UART_Wait_Char(16)!='S' )				// 等待起始同步字符'S'
		goto again;

	tmpbuf[0] = (char)file_len;					// 发送文件长度
	tmpbuf[1] = (char)(file_len>>8);
	tmpbuf[2] = (char)(file_len>>16);
	tmpbuf[3] = (char)(file_len>>24);
	for(chr_idx=0;chr_idx<4;chr_idx++)
	{
		UART_Send_Char(tmpbuf[chr_idx]);
	}
	for(chr_idx=0;chr_idx<4;chr_idx++)			// 接收并检查文件长度(四字节)
	{
		ch = UART_Wait_Char(16);	
		if(ch==-1)		goto end;
		recvbuf[chr_idx] = ch;
	}
	if( memcmp(recvbuf,tmpbuf,4) != 0 )
		goto end;
	
	blk_cnt = file_len/1024;					// 计算参数
	blk_res = file_len%1024;
	blk_cnt += ( (blk_res>0) ? 1 : 0 );
	blk_res = ((blk_res==0) ? 1024 : blk_res);
		
	for(blk_idx=0;blk_idx<blk_cnt;blk_idx++)	// 发送数据块+CRC
	{
		cnt_now =( (blk_idx!=(blk_cnt-1)) ? 1024 : blk_res );
		CalCrc16_13239(file_buf+blk_idx*1024,crcbuf,cnt_now);
		
		for(chr_idx=0; chr_idx<cnt_now; chr_idx++)	       
		{
			if(KEY_Read() == KEY_F1)	goto end;
			UART_Send_Char(file_buf[blk_idx*1024+chr_idx]);
		}
		for(chr_idx=0; chr_idx<2; chr_idx++)	       
		{
			UART_Send_Char(crcbuf[chr_idx]);
		}
		ch = UART_Wait_Char(16);
		if(ch == 'W' || ch != 'E' )
			goto end;
	}
	ret = 0;
end:
	UART_Init(UART_OFF);
	return ret;
}

int EXT_Up_USB(unsigned char *file_buf,unsigned long file_len)
{
	unsigned short	i_st;						// 中断类型
	short			ret = -1;					// 函数返回值，传输过程中中断的值 by chen
	
	int				blk_cnt;					// 块数量
	int				blk_res;					// 不足1024字节的剩余字节数
	int				blk_idx=0;					// 循环变量
	int				cnt_now;					// 本次发送字节数
	int				chr_idx;					// 块内循环变量
	
	unsigned char 	recvbuf[4];					// 接收缓冲区
	
	if(USB_Init())
	{
		ret = -2;	//USB未能连接的值
		return ret;
	}

	
	blk_cnt = file_len/64;						// 计算参数
	blk_res = file_len%64;
	blk_cnt += ( (blk_res>0) ? 1 : 0 );
	blk_res = ((blk_res==0) ? 64 : blk_res);
	
	for(;;)
	{
		if(KEY_Read() == KEY_F1)	goto end;
		i_st = D12_Read_Interrupt_Register();				// 读取PDIUSBD12中断寄存器值
		if(i_st != 0) 
		{
			if(i_st & D12_INT_SUSPENDCHANGE)
				USB_Suspend();								// 总线挂起改变
			if(i_st & D12_INT_ENDP0IN)
				USB_EP0_Txdone();							// 控制端点发送数据处理
			if(i_st & D12_INT_ENDP0OUT)
				USB_EP0_Rxdone();							// 控制端点接收数据处理
			if(i_st & D12_INT_ENDP1OUT)
			{
				D12_Read_Last_Status(2);
				D12_Read_Endpoint(2,1,recvbuf);
				if(recvbuf[0] == 'S')
				{
					D12_Read_Last_Status(3);
					D12_Write_Endpoint(3,4,(unsigned char*)&file_len);			
				}
				if(recvbuf[0] == 'E') 
				{
					break;
				}				
			}
			if(i_st & D12_INT_ENDP2OUT)
			{	
				D12_Read_Last_Status(4);
				D12_Read_Endpoint(4,1,recvbuf);
				if(recvbuf[0] == 'S')
				{
					for(chr_idx = 0;chr_idx<2;chr_idx++)	// 一次发送 128 byte
					{
						if(blk_idx >= blk_cnt)
							break;
							 		
						cnt_now =( (blk_idx!=(blk_cnt-1)) ? 64 : blk_res );
						D12_Read_Last_Status(5);
						D12_Write_Endpoint(5,cnt_now,file_buf+64*blk_idx);
						blk_idx++;	
					}
				}
			}
		}
	}
	ret = 0;
end:
	USB_Disconnect();
	return ret;
}

int	EXT_Down_232(unsigned char *file_buf,unsigned long *file_len)
{
	short			ch;							// 接收返回值
	short			ret = -1;					// 函数返回值
	
	int				blk_cnt;					// 块数量
	int				blk_res;					// 不足1024字节的剩余字节数
	int				blk_idx;					// 循环变量
	int				chr_idx;					// 块内循环变量
	int				cnt_now;					// 本次发送字节数
	unsigned long	expect_len;
	unsigned long	real_len=0;
	
	unsigned char	crcbuf[4];					// 校验字节
	unsigned char 	recvbuf[1026];				// 接收缓冲区	
	
	
	UART_Init(UART_232_ON|UART_BAUD_115200);
	
again:
	if(KEY_Read() == KEY_F1)	goto end;
	if( UART_Wait_Char(16)!='S' )				// 等待起始同步字符'S'
		goto again;
	UART_Send_Char('N');
		
	for(chr_idx=0;chr_idx<4;chr_idx++)			// 接收并发送长度
	{
		ch = UART_Wait_Char(16);	
		if(ch==-1)		goto end;
		recvbuf[chr_idx] = ch;
	}
	for(chr_idx=0;chr_idx<4;chr_idx++)
	{
		UART_Send_Char(recvbuf[chr_idx]);
	}	

	memcpy(&expect_len,recvbuf,4);
	blk_cnt = expect_len/1024;
	blk_res   = expect_len%1024;
	blk_cnt += ( (blk_res>0) ? 1 : 0 );
	blk_res = ((blk_res==0) ? 1024 : blk_res);
	
	for(blk_idx=0; blk_idx<blk_cnt; blk_idx++)
	{		
		cnt_now =( (blk_idx!=(blk_cnt-1)) ? 1024 : blk_res );

		for(chr_idx=0; chr_idx<(cnt_now+2); chr_idx++)	       
		{
			if(KEY_Read() == KEY_F1)	goto end;
			ch = UART_Wait_Char(16);
			if(ch!=-1)
			{
				recvbuf[chr_idx] = ch;
			}
			else
			{
				goto end;
			}
		}
		CalCrc16_13239(recvbuf,crcbuf,cnt_now);
		if( memcmp(recvbuf+cnt_now,crcbuf,2) != 0)		
		{
			UART_Send_Char('W');
			goto end;
		}
		memcpy(file_buf+real_len,recvbuf,cnt_now);
		real_len += cnt_now;
		UART_Send_Char('E');			
	}
	*file_len = real_len;
	if(real_len == expect_len)
		ret = 0;				
end:
	UART_Init(UART_OFF);
	return ret;
}

int	EXT_Down_USB(unsigned char *file_buf,unsigned long *file_len)
{
	unsigned short	i_st;						// 中断类型
	short			ret = -1;					// 函数返回值
	
	short			cnt_now;
	unsigned long	expect_len;
	unsigned long	real_len=0;
	
	unsigned char 	recvbuf[64];				// 接收缓冲区
	
	if(USB_Init())
	{
		ret = -2;
		return ret;
	}
	
	for(;;)
	{
		if(KEY_Read() == KEY_F1)	goto end;
		i_st = D12_Read_Interrupt_Register();				// 读取PDIUSBD12中断寄存器值
		if(i_st != 0) 
		{
			if(i_st & D12_INT_SUSPENDCHANGE)
				USB_Suspend();								// 总线挂起改变
			if(i_st & D12_INT_ENDP0IN)
				USB_EP0_Txdone();							// 控制端点发送数据处理
			if(i_st & D12_INT_ENDP0OUT)
				USB_EP0_Rxdone();							// 控制端点接收数据处理
			if(i_st & D12_INT_ENDP1OUT)
			{
				D12_Read_Last_Status(2);
				D12_Read_Endpoint(2,16,recvbuf);
				if(recvbuf[0] == 'E') 
				{
					break;
				}
				else if(recvbuf[0] != 'S')					// 如非上传模式
				{
					memcpy(&expect_len,recvbuf,4);
					D12_Write_Endpoint(3,4,(unsigned char*)&expect_len);
				}			
			}
			if(i_st & D12_INT_ENDP2OUT)
			{
				D12_Read_Last_Status(4);
				cnt_now = D12_Read_Endpoint(4,64,recvbuf);
				memcpy(file_buf+real_len,recvbuf,cnt_now);
				real_len += cnt_now;
			}
		}
	}
	*file_len = real_len;
	if(real_len == expect_len)
		ret = 0;
end:
	USB_Disconnect();
	return ret;
}
