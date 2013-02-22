#include "iso8583.h"

void Set8583BitMap(char bitmap[16], ...)
{
	va_list ap;
	int arg;
	va_start(ap, bitmap);
	while ((arg = va_arg(ap, int)) != 0)
	{
		(*(bitmap + ((arg - 1) >> 3))) |= 0x01 << ((arg - 1) & 0x07);
	}
	va_end(ap);
	return ;
}

int TwoAndHex(char *binary_data, unsigned char *hex_data, int flag)
{
	int i = 0;
	int j = 0;
	int n = 0;
	int sum = 0;
	char a[9] = "";
	unsigned char b = 0;

	if (NULL == binary_data || NULL == hex_data) { return -1; }

	if (XCHANGE_IN == flag)
	{
		for (i = 0; i < 8; i++)
		{
			if (binary_data[i] == '1')
			{
				n = 1;
				for (j = 0; j < 7 - i; j++) { n *= 2; }
				sum += n;	
			}
		}
		*hex_data = sum;
	}
	else if (XCHANGE_OUT == flag)
	{
		b = *hex_data;
		for (i = 0; i < 8; i++)
		{
			if (b % 2 != 0)
			{
				a[7 - i] = '1';
				b = (b - 1) / 2;
			}
			else
			{
				b = b / 2;
				a[7 - i] = '0';
			}
		}

		a[8] = '\0';
		strcpy(binary_data, a);	
	}
	else
	{
		return -3;
	}

	return 0;
}

int ChangeBitBuf(char asc_bit[128], char bcd_bit[16], int bit_flag)
{
	int ret = 0;
	int i = 0;
	int len = 0; 
	int n = 0;
	unsigned char buf[17] = "";
	
	if (XCHANGE_IN == bit_flag)
	{
		memset(buf, 0, sizeof(buf));
		len = strlen(asc_bit);
		n = 1 + len / 8;
		for(i = 0; i < 16; i++)
		{
			if (i < n)
			{
				ret = TwoAndHex(asc_bit + 8 * i, &buf[i], bit_flag);
				if (ret) { return ret; }
			}
			else
				buf[i] = 0x00;
		}

		memcpy(bcd_bit, buf, 16);
	}
	else if (XCHANGE_OUT == bit_flag)
	{
		for (i = 0; i < 8; i++)
		{
			ret = TwoAndHex(asc_bit + 8 * i, (unsigned char *)&bcd_bit[i], bit_flag);
			if (ret) { return ret; }
		}
	}	

	return 0;
}

int GetStrLength(char *src_str, char end_chr)
{
	char *pdest = NULL;
	int result = 0;

	pdest = strchr(src_str, end_chr);
	result = pdest - src_str;

	return result > 0 ? result : 0;
}

int ChangePacktTo8583(void *src_packet, ISO8583 *iso_8583_packet, int flag)
{
	int ret = 0;
	int count = 0;
	int add_length = 0;
	int str_length = 0;		// 8583包实际长度
	char *packet_point = NULL;
	unsigned char all_bit_map[16] = "";
	add_length += MSG_LENGTH;

	memcpy(all_bit_map, (char *)src_packet + add_length, sizeof(all_bit_map));

	for (int i = 0; i < 128; i++)
	{
		if (all_bit_map[i / 8] & (1 << (i % 8)))	
		{
			if (XCHANGE_IN == flag)
			{
				packet_point = iso_8583_packet[i].data = ((char *)src_packet + add_length);												// 取8583包中的数据地址						
				if (0 == iso_8583_packet[i].variable_flag)			// firm length
				{
					iso_8583_packet[i].length_in_byte = iso_8583_packet[i].length;
				}
				else
				{
					str_length = GetStrLength(packet_point, SPLIT_VL1);																		// 取某位的实际长度	
					if (str_length > 0 && str_length < iso_8583_packet[i].length) { iso_8583_packet[i].length_in_byte = str_length; }
					else { iso_8583_packet[i].length_in_byte = iso_8583_packet[i].length; }	
				}
				add_length += iso_8583_packet[i].length;																				// 加上src_packet包长度			
			}
			else if (XCHANGE_OUT == flag)
			{
				// 拷贝8583包数据到结构体
				if (iso_8583_packet[i].data) 
				{
					memcpy((char *)src_packet + add_length, iso_8583_packet[i].data, iso_8583_packet[i].length_in_byte); 
				}			
				add_length += iso_8583_packet[i].length;
			}
			else { return 0; }																	
		}
		else 
		{
			NULL;	
		}
	}

	return 0;
}


int Change8583ToBuf(ISO8583 *iso_8583_packet, char *buf, int flag)
{
	int ret = 0;
	int j = 0;
	int buf_length = 0;
	char strlength[4] = "";
	unsigned char all_bit_map[16] = "";
	
	memcpy(all_bit_map, buf + MSG_LENGTH, sizeof(all_bit_map));
	buf_length += MSG_LENGTH;

	for (int i = 0; i < 16; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (XCHANGE_IN == flag)
			{
				// 1. 读取位图
				// 2. 拷贝数据
				if (iso_8583_packet[0].data[i] & (0x01 << j))							// 1域存储8583位图, 有位图存在
				{
					if (0 == iso_8583_packet[i * 8 + j].variable_flag)
					{
						// 固定8583数据
						memcpy(buf + buf_length, iso_8583_packet[i * 8 + j].data, iso_8583_packet[i * 8 + j].length);
						printf("buf =[%20.20s] buf_length=[%d] \n", buf + buf_length, iso_8583_packet[i * 8 + j].length);
						buf_length += iso_8583_packet[i * 8 + j].length;	
					}
					else if (2 == iso_8583_packet[i * 8 + j].variable_flag)
					{
						sprintf(buf + buf_length, "%02d", iso_8583_packet[i * 8 + j].length_in_byte);
						buf_length += 2;
						memcpy(buf + buf_length, iso_8583_packet[i * 8 + j].data, iso_8583_packet[i * 8 + j].length_in_byte);
						printf("buf =[%20.20s] buf_length=[%d] \n", buf + buf_length, iso_8583_packet[i * 8 + j].length_in_byte);
						buf_length += iso_8583_packet[i * 8 + j].length_in_byte;
					}
					else if (3 == iso_8583_packet[i * 8 + j].variable_flag)			// 8583 to buf压包
					{
						sprintf(buf + buf_length, "%03d", iso_8583_packet[i * 8 + j].length_in_byte);
						buf_length += 3;
						memcpy(buf + buf_length, iso_8583_packet[i * 8 + j].data, iso_8583_packet[i * 8 + j].length_in_byte);
						printf("buf =[%20.20s] buf_length=[%d] \n", buf + buf_length, iso_8583_packet[i * 8 + j].length_in_byte);
						buf_length += iso_8583_packet[i * 8 + j].length_in_byte;
					}	
				}
			}
			else if (XCHANGE_OUT == flag)
			{
				// 1. 拷贝位图
				// 2. 判断位图
				// 3. 解析位图, 拷贝数据到8583包(8583包的指针指向buf)					// buf to 8583解包							// 找到位图地址
				if (all_bit_map[i] & (0x01 << j))							// 有标志位图的情况
				{
					if (0 == iso_8583_packet[i * 8 + j].variable_flag)
					{
						// 固定8583数据
						iso_8583_packet[i * 8 + j].length_in_byte = iso_8583_packet[i * 8 + j].length;
						iso_8583_packet[i * 8 + j].data = buf + buf_length;
						buf_length += iso_8583_packet[i * 8 + j].length;
					}
					else if (2 == iso_8583_packet[i * 8 + j].variable_flag)
					{
						// 变长2
						memset(strlength, 0x00, sizeof(strlength));
						memcpy(strlength, buf + buf_length, 2);
						iso_8583_packet[i * 8 + j].length_in_byte = atoi(strlength);
						buf_length += 2;
						iso_8583_packet[i * 8 + j].data = buf + buf_length;
						buf_length += iso_8583_packet[i * 8 + j].length_in_byte;
					}
					else if (3 == iso_8583_packet[i * 8 + j].variable_flag)			// 8583 to buf压包
					{
						// 变长3
						memset(strlength, 0x00, sizeof(strlength));
						memcpy(strlength, buf + buf_length, 3);
						iso_8583_packet[i * 8 + j].length_in_byte = atoi(strlength);
						buf_length += 3;
						iso_8583_packet[i * 8 + j].data = buf + buf_length;
						buf_length += iso_8583_packet[i * 8 + j].length_in_byte;
					}	
				}
				else
				{
					iso_8583_packet[i * 8 + j].data = NULL;
				}
			}
			else { return 0; }
		}
	}

	return 0;
}

void Get8583DataLength(char bitmap[16], ISO8583 *iso_8583_packet, int *data_length)
{
	for (int jj = 0; jj < 128; jj++)
	{
		if (bitmap[jj / 8] & (1 << (jj % 8)))
		{
			*data_length += iso_8583_packet[jj].length_in_byte + iso_8583_packet[jj].variable_flag;				// length_in_byte + 0 or 2 or 3							// 	packet data length
			printf("bitmap =[%d] buf_data_length=[%d] \n", jj, iso_8583_packet[jj].length_in_byte + iso_8583_packet[jj].variable_flag);
		}
	}
	return ;	
}

