#ifndef _CRC_H_
#define _CRC_H_
#include "include/datatype.h"

uint16 GenerateCRC16(uint8 *pBuf, uint16 len);
bit check_buf_crc(uint8 *buf,uint16 len);
uint8 calc_sum(uint8 *buf,uint16 len);
uint8 calc_sum2(uint8 *buf,uint16 len,uint8 crc);

void calc_not(uint8 *in_buff,uint16 len,uint8 *out_buff);
void hex2bcd(uint8 *hex,uint8 len,uint8 *bcd);
void bcd2hex(uint8 *bcd,uint8 len,uint8 *hex);

uint16 get_2byte_int(uint8 *buffer);
uint32 get_3byte_int(uint8 *buffer);
uint32 get_4byte_int(uint8 *buffer);
void set_2byte_int(uint16 value,uint8 *buffer);
void set_3byte_int(uint32 value,uint8 *buffer);
void set_4byte_int(uint32 value,uint8 *buffer);


void str2bcd(uint8 *str,uint8 len,uint8 *bcd);
void bcd2str(uint8 *bcd,uint8 len,uint8 *str);

uint8 decrypt_work_key(uint8* text,uint8* mtext);

#endif // _CRC_H_

