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
{												// ISO/IEC 13239 CRC���� (x^16+x^12+x^5+1)
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
	short			ch;							// ���շ���ֵ
	short			ret = -1;					// ��������ֵ
	
	int				blk_cnt;					// ������
	int				blk_res;					// ����1024�ֽڵ�ʣ���ֽ���
	int				blk_idx;					// ѭ������
	int				chr_idx;					// ����ѭ������
	int				cnt_now;					// ���η����ֽ���
	
	unsigned char	crcbuf[4];					// У���ֽ�
	unsigned char 	recvbuf[4];					// ���ջ�����
	unsigned char 	tmpbuf[4];					// ��ʱ������

	UART_Init(UART_232_ON|UART_BAUD_115200);

again:
	if(KEY_Read() == KEY_F1)	goto end;
	if( UART_Wait_Char(16)!='S' )				// �ȴ���ʼͬ���ַ�'S'
		goto again;

	tmpbuf[0] = (char)file_len;					// �����ļ�����
	tmpbuf[1] = (char)(file_len>>8);
	tmpbuf[2] = (char)(file_len>>16);
	tmpbuf[3] = (char)(file_len>>24);
	for(chr_idx=0;chr_idx<4;chr_idx++)
	{
		UART_Send_Char(tmpbuf[chr_idx]);
	}
	for(chr_idx=0;chr_idx<4;chr_idx++)			// ���ղ�����ļ�����(���ֽ�)
	{
		ch = UART_Wait_Char(16);	
		if(ch==-1)		goto end;
		recvbuf[chr_idx] = ch;
	}
	if( memcmp(recvbuf,tmpbuf,4) != 0 )
		goto end;
	
	blk_cnt = file_len/1024;					// �������
	blk_res = file_len%1024;
	blk_cnt += ( (blk_res>0) ? 1 : 0 );
	blk_res = ((blk_res==0) ? 1024 : blk_res);
		
	for(blk_idx=0;blk_idx<blk_cnt;blk_idx++)	// �������ݿ�+CRC
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
	unsigned short	i_st;						// �ж�����
	short			ret = -1;					// ��������ֵ������������жϵ�ֵ by chen
	
	int				blk_cnt;					// ������
	int				blk_res;					// ����1024�ֽڵ�ʣ���ֽ���
	int				blk_idx=0;					// ѭ������
	int				cnt_now;					// ���η����ֽ���
	int				chr_idx;					// ����ѭ������
	
	unsigned char 	recvbuf[4];					// ���ջ�����
	
	if(USB_Init())
	{
		ret = -2;	//USBδ�����ӵ�ֵ
		return ret;
	}

	
	blk_cnt = file_len/64;						// �������
	blk_res = file_len%64;
	blk_cnt += ( (blk_res>0) ? 1 : 0 );
	blk_res = ((blk_res==0) ? 64 : blk_res);
	
	for(;;)
	{
		if(KEY_Read() == KEY_F1)	goto end;
		i_st = D12_Read_Interrupt_Register();				// ��ȡPDIUSBD12�жϼĴ���ֵ
		if(i_st != 0) 
		{
			if(i_st & D12_INT_SUSPENDCHANGE)
				USB_Suspend();								// ���߹���ı�
			if(i_st & D12_INT_ENDP0IN)
				USB_EP0_Txdone();							// ���ƶ˵㷢�����ݴ���
			if(i_st & D12_INT_ENDP0OUT)
				USB_EP0_Rxdone();							// ���ƶ˵�������ݴ���
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
					for(chr_idx = 0;chr_idx<2;chr_idx++)	// һ�η��� 128 byte
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
	short			ch;							// ���շ���ֵ
	short			ret = -1;					// ��������ֵ
	
	int				blk_cnt;					// ������
	int				blk_res;					// ����1024�ֽڵ�ʣ���ֽ���
	int				blk_idx;					// ѭ������
	int				chr_idx;					// ����ѭ������
	int				cnt_now;					// ���η����ֽ���
	unsigned long	expect_len;
	unsigned long	real_len=0;
	
	unsigned char	crcbuf[4];					// У���ֽ�
	unsigned char 	recvbuf[1026];				// ���ջ�����	
	
	
	UART_Init(UART_232_ON|UART_BAUD_115200);
	
again:
	if(KEY_Read() == KEY_F1)	goto end;
	if( UART_Wait_Char(16)!='S' )				// �ȴ���ʼͬ���ַ�'S'
		goto again;
	UART_Send_Char('N');
		
	for(chr_idx=0;chr_idx<4;chr_idx++)			// ���ղ����ͳ���
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
	unsigned short	i_st;						// �ж�����
	short			ret = -1;					// ��������ֵ
	
	short			cnt_now;
	unsigned long	expect_len;
	unsigned long	real_len=0;
	
	unsigned char 	recvbuf[64];				// ���ջ�����
	
	if(USB_Init())
	{
		ret = -2;
		return ret;
	}
	
	for(;;)
	{
		if(KEY_Read() == KEY_F1)	goto end;
		i_st = D12_Read_Interrupt_Register();				// ��ȡPDIUSBD12�жϼĴ���ֵ
		if(i_st != 0) 
		{
			if(i_st & D12_INT_SUSPENDCHANGE)
				USB_Suspend();								// ���߹���ı�
			if(i_st & D12_INT_ENDP0IN)
				USB_EP0_Txdone();							// ���ƶ˵㷢�����ݴ���
			if(i_st & D12_INT_ENDP0OUT)
				USB_EP0_Rxdone();							// ���ƶ˵�������ݴ���
			if(i_st & D12_INT_ENDP1OUT)
			{
				D12_Read_Last_Status(2);
				D12_Read_Endpoint(2,16,recvbuf);
				if(recvbuf[0] == 'E') 
				{
					break;
				}
				else if(recvbuf[0] != 'S')					// ����ϴ�ģʽ
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
