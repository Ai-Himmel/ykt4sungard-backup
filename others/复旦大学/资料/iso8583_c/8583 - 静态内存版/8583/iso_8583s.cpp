#include <stdlib.h>
#include <string.h>
#include "iso_8583s.h"
/*
 * 组包解包是否压缩数据，通常在POS中需压缩
 */
static int s_iCompress = 0;		//零：不压	非零：压

static ISO_DEF s_isodef[] = {
    /*000*/ {TYP_BCD, 0, 4}, // 消息类型
    /*001*/ {TYP_BIT, 0, 16}, // 位图
    /*002*/ {TYP_BCD, 2, 22}, // 主账号
    /*003*/ {TYP_BCD, 0, 6}, // 交易处理码
    /*004*/ {TYP_BCD, 0, 12}, // 交易金额
    /*005*/ {TYP_BCD, 0, 12}, // "Amount, Reconciliation"
    /*006*/ {TYP_BCD, 0, 12}, // "Amount, Cardholder billing"
    /*007*/ {TYP_BCD, 0, 10}, // "Date and time, transmission"
    /*008*/ {TYP_BCD, 0, 8}, // "Amount, Cardholder billing fee"
    /*009*/ {TYP_BCD, 0, 8}, // "Conversion rate, Reconciliation"
    /*010*/ {TYP_BCD, 0, 8}, // "Conversion rate, Cardholder billing"
    /*011*/ {TYP_BCD, 0, 6}, // "Systems trace audit number"
    /*012*/ {TYP_BCD, 0, 12}, // "Date and time, Local transaction"
    /*013*/ {TYP_BCD, 0, 4}, // "Date, Effective"
    /*014*/ {TYP_BCD, 0, 4}, // "Date, Expiration"
    /*015*/ {TYP_BCD, 0, 6}, // "Date, Settlement"
    /*016*/ {TYP_BCD, 0, 4}, // "Date, Conversion"
    /*017*/ {TYP_BCD, 0, 4}, // "Date, Capture"
    /*018*/ {TYP_BCD, 0, 4}, // "Merchant type"
    /*019*/ {TYP_BCD, 0, 3}, // "Country code, Acquiring institution"
    /*020*/ {TYP_BCD, 0, 3}, // "Country code, Primary account number"
    /*021*/ {TYP_BCD, 0, 3}, // "Country code, Forwarding institution"
    /*022*/ {TYP_ASC, 0, 12}, // "Point of service data code"
    /*023*/ {TYP_BCD, 0, 3}, // "Card sequence number"
    /*024*/ {TYP_BCD, 0, 3}, // "Function code"
    /*025*/ {TYP_BCD, 0, 4}, // "Message reason code"
    /*026*/ {TYP_BCD, 0, 4}, // "Card acceptor business code"
    /*027*/ {TYP_BCD, 0, 1}, // "Approval code length"
    /*028*/ {TYP_BCD, 0, 6}, // "Date, Reconciliation"
    /*029*/ {TYP_BCD, 0, 3}, // "Reconciliation indicator"
    /*030*/ {TYP_BCD, 0, 24}, // "Amounts, original"
    /*031*/ {TYP_ASC, 2, 99}, // "Acquirer reference data"
    /*032*/ {TYP_BCD, 2, 11}, // "Acquirer institution identification code"
    /*033*/ {TYP_BCD, 2, 11}, // "Forwarding institution identification code"
    /*034*/ {TYP_ASC, 2, 28}, // "Primary account number, extended"
    /*035*/ {TYP_ASC, 2, 37}, // "Track 2 data"
    /*036*/ {TYP_ASC, 3, 104}, // "Track 3 data"
    /*037*/ {TYP_ASC, 0, 12}, // "Retrieval reference number"
    /*038*/ {TYP_ASC, 0, 6}, // "Approval code"
    /*039*/ {TYP_BCD, 0, 3}, // "Action code"
    /*040*/ {TYP_BCD, 0, 3}, // "Service code"
    /*041*/ {TYP_ASC, 0, 8}, // "Card acceptor terminal identification"
    /*042*/ {TYP_ASC, 0, 15}, // "Card acceptor identification code"
    /*043*/ {TYP_ASC, 2, 99}, // "Card acceptor name/location"
    /*044*/ {TYP_ASC, 2, 99}, // "Additional response data"
    /*045*/ {TYP_ASC, 2, 76}, // "Track 1 data"
    /*046*/ {TYP_ASC, 3, 204}, // "Amounts, Fees"
    /*047*/ {TYP_ASC, 3, 999}, // "Additional data - national"
    /*048*/ {TYP_ASC, 3, 999}, // "Additional data - private"
    /*049*/ {TYP_ASC, 0, 3}, // "Currency code, Transaction"
    /*050*/ {TYP_ASC, 0, 3}, // "Currency code, Reconciliation"
    /*051*/ {TYP_ASC, 0, 3}, // "Currency code, Cardholder billing"
    /*052*/ {TYP_BIN, 0, 8}, // "Personal identification number, PIN) data"
    /*053*/ {TYP_BIN, 2, 48}, // "Security related control information"
    /*054*/ {TYP_ASC, 3, 120}, // "Amounts, additional"
    /*055*/ {TYP_BIN, 3, 255}, // "IC card system related data"
    /*056*/ {TYP_BIN, 3, 255}, // "Original data elements"
    /*057*/ {TYP_BCD, 0, 3}, // "Authorization life cycle code"
    /*058*/ {TYP_BCD, 2, 11}, // "Authorizing agent institution Id Code"
    /*059*/ {TYP_ASC, 3, 999}, // "Transport data"
    /*060*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
    /*061*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
    /*062*/ {TYP_ASC, 3, 999}, // "Reserved for private use"
    /*063*/ {TYP_ASC, 3, 999}, // "Reserved for private use"
    /*064*/ {TYP_BIN, 0, 8}  // "Message authentication code field"
#if ISO_FLDS==128
	,
	/*065*/ {TYP_BIN, 0, 8}, // "Reserved for ISO use"
	/*066*/ {TYP_ASC, 3, 204}, // "Amounts, original fees"
	/*067*/ {TYP_BCD, 0, 2}, // "Extended payment data"
	/*068*/ {TYP_BCD, 0, 3}, // "Country code, receiving institution"
	/*069*/ {TYP_BCD, 0, 3}, // "Country code, settlement institution"
	/*070*/ {TYP_BCD, 0, 3}, // "Country code, authorizing agent Inst."
	/*071*/ {TYP_BCD, 0, 8}, // "Message number"
	/*072*/ {TYP_ASC, 3, 999}, // "Data record"
	/*073*/ {TYP_BCD, 0, 6}, // "Date, action"
	/*074*/ {TYP_BCD, 0, 10}, // "Credits, number"
	/*075*/ {TYP_BCD, 0, 10}, // "Credits, reversal number"
	/*076*/ {TYP_BCD, 0, 10}, // "Debits, number"
	/*077*/ {TYP_BCD, 0, 10}, // "Debits, reversal number"
	/*078*/ {TYP_BCD, 0, 10}, // "Transfer, number"
	/*079*/ {TYP_BCD, 0, 10}, // "Transfer, reversal number"
	/*080*/ {TYP_BCD, 0, 10}, // "Inquiries, number"
	/*081*/ {TYP_BCD, 0, 10}, // "Authorizations, number"
	/*082*/ {TYP_BCD, 0, 10}, // "Inquiries, reversal number"
	/*083*/ {TYP_BCD, 0, 10}, // "Payments, number"
	/*084*/ {TYP_BCD, 0, 10}, // "Payments, reversal number"
	/*085*/ {TYP_BCD, 0, 10}, // "Fee collections, number"
	/*086*/ {TYP_BCD, 0, 16}, // "Credits, amount"
	/*087*/ {TYP_BCD, 0, 16}, // "Credits, reversal amount"
	/*088*/ {TYP_BCD, 0, 16}, // "Debits, amount"
	/*089*/ {TYP_BCD, 0, 16}, // "Debits, reversal amount"
	/*090*/ {TYP_BCD, 0, 10}, // "Authorizations, reversal number"
	/*091*/ {TYP_BCD, 0, 3}, // "Country code, transaction Dest. Inst."
	/*092*/ {TYP_BCD, 0, 3}, // "Country code, transaction Orig. Inst."
	/*093*/ {TYP_BCD, 2, 11}, // "Transaction Dest. Inst. Id code"
	/*094*/ {TYP_BCD, 2, 11}, // "Transaction Orig. Inst. Id code"
	/*095*/ {TYP_ASC, 2, 99}, // "Card issuer reference data"
	/*096*/ {TYP_BIN, 3, 999}, // "Key management data"
	/*097*/ {TYP_BCD, 0, 1+16}, // "Amount, Net reconciliation"/* was ISO_AMOUNT */
	/*098*/ {TYP_ASC, 0, 25}, // "Payee"
	/*099*/ {TYP_ASC, 2, 11}, // "Settlement institution Id code"
	/*100*/ {TYP_BCD, 2, 11}, // "Receiving institution Id code"
	/*101*/ {TYP_ASC, 2, 17}, // "File name"
	/*102*/ {TYP_ASC, 2, 28}, // "Account identification 1"
	/*103*/ {TYP_ASC, 2, 28}, // "Account identification 2"
	/*104*/ {TYP_ASC, 3, 100}, // "Transaction description"
	/*105*/ {TYP_BCD, 0, 16}, // "Credits, Chargeback amount"
	/*106*/ {TYP_BCD, 0, 16}, // "Debits, Chargeback amount"
	/*107*/ {TYP_BCD, 0, 10}, // "Credits, Chargeback number"
	/*108*/ {TYP_BCD, 0, 10}, // "Debits, Chargeback number"
	/*109*/ {TYP_ASC, 2, 84}, // "Credits, Fee amounts"
	/*110*/ {TYP_ASC, 2, 84}, // "Debits, Fee amounts"
	/*111*/ {TYP_ASC, 3, 999}, // "Reserved for ISO use"
	/*112*/ {TYP_ASC, 3, 999}, // "Reserved for ISO use"
	/*113*/ {TYP_ASC, 3, 999}, // "Reserved for ISO use"
	/*114*/ {TYP_ASC, 3, 999}, // "Reserved for ISO use"
	/*115*/ {TYP_ASC, 3, 999}, // "Reserved for ISO use"
	/*116*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
	/*117*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
	/*118*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
	/*119*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
	/*120*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
	/*121*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
	/*122*/ {TYP_ASC, 3, 999}, // "Reserved for national use"
	/*123*/ {TYP_ASC, 3, 999}, // "Reserved for private use"
	/*124*/ {TYP_ASC, 3, 999}, // "Reserved for private use"
	/*125*/ {TYP_ASC, 3, 999}, // "Reserved for private use"
	/*126*/ {TYP_ASC, 3, 999}, // "Reserved for private use"
	/*127*/ {TYP_ASC, 3, 999}, // "Reserved for private use"
	/*128*/ {TYP_BIN, 0, 8} // "Message authentication code field"
#endif /*ISO_FLDS==128*/
};

/***********************************************************************
		module		:	[8583协议]
		function		:	[变更是否需要压缩成BCD或者解压]
  		return			:	[无]
		comment	:	[全局普通函数]
		machine		:	[]
		language	:	[CHN]
 		keyword		:	[s_iCompress零为不压，非零压缩]
		date			:	[11/08/10]
 		author		:	[chen-zhengkai]
************************************************************************/
void iso8583_compress(int c)
{
	s_iCompress = c;
}

/***********************************************************************
		module		:	[8583协议]
		function		:	[对ISO_MSG变量m进行初始化，
								最开始必须先调用此函数]
  		return			:	[无]
		comment	:	[全局普通函数]
		machine		:	[无]
		language	:	[CHN]
 		keyword		:	[无]
		date			:	[11/08/10]
 		author		:	[chen-zhengkai]
************************************************************************/
void iso8583_init(ISO_MSG *m)
{
	int i;
	for (i=0; i<=ISO_FLDS; i++) {
		memset (m->fld[i].buf, 0x00, NUM);
		m->fld[i].len = 0;
	}
}
/***********************************************************************
		module		:	[8583协议]
		function		:	[设置ISO_MSG变量m中第idx位的值为data, data长度为len.]
  		return			:	[零：异常
								其他：data数据的长度]
		comment	:	[全局普通函数]
		machine		:	[无]
		language	:	[CHN]
 		keyword		:	[内部有MALLOC操作，用完需要函数iso8583_free进行释放]
		date			:	[11/08/10]
 		author		:	[chen-zhengkai]
************************************************************************/
int iso8583_set(ISO_MSG *m, int idx, const unsigned char *data, int len)
{
	memset(m->fld[idx].buf, 0x00, NUM);
	m->fld[idx].len = 0;
	if (len > s_isodef[idx].len) {		//长度大于定长，返回0
		return 0;
	}
	m->fld[idx].len = len;
	memcpy(m->fld[idx].buf, data, m->fld[idx].len);
	return len;
}
/***********************************************************************
		module		:	[8583协议]
		function		:	[取得ISO_MSG变量m中第idx位的值到data, 希望最大长度为len.]
  		return			:	[零：异常
								其他：data数据的长度]
		comment	:	[全局普通函数]
		machine		:	[无]
		language	:	[CHN]
 		keyword		:	[无]
		date			:	[11/08/10]
 		author		:	[chen-zhengkai]
************************************************************************/
int iso8583_get(const ISO_MSG *m, int idx, unsigned char *data, int len)
{
	if (m == NULL || data == NULL) {
		return 0;
	}
 
	if (m->fld[idx].len > len) {
		return 0;
	}
	memcpy(data, m->fld[idx].buf, m->fld[idx].len);
	return m->fld[idx].len;
}

/***********************************************************************
		module		:	[8583协议]
		function		:	[把ISO_MSG变量m中数据按定义好的格式组包到buf中]
  		return			:	[-1：异常
								其他：buf的长度]
		comment	:	[全局普通函数]
		machine		:	[无]
		language	:	[CHN]
 		keyword		:	[buf格式：0字段--1位图字段--(2-128)中有数据的字段......]
		date			:	[11/08/10]
 		author		:	[chen-zhengkai]
************************************************************************/
int iso8583_pack(const ISO_MSG *m, char *buf)
{
	char *start = buf;
	int flds, i;
	char fmt[8] = {0};
	char tmp[8] = {0};

	//0域操作
	if (m->fld[0].len != s_isodef[0].len || s_isodef[0].fmt != FMT_FIXED) {
		MY_TRACE("flds = %d", 0);
		return -1;
	}

	if (s_iCompress) {	//是否压缩数据，asc2bcd
		buf += ASC2BCD((unsigned char*)buf, (char*)m->fld[0].buf, s_isodef[0].len, s_isodef[0].fmt);
	}
	else {
		memcpy(buf, m->fld[0].buf, s_isodef[0].len);		//0字段（消息类型）操作
		buf += s_isodef[0].len;
	}

	//（1域）位图域操作
	if (m->fld[1].buf == NULL || s_isodef[1].len != 16) {
		MY_TRACE("flds = %d", 1);
		return -1;
	}
#if ISO_FLDS==128
	if ((m->fld[1].len == s_isodef[1].len) && (m->fld[1].buf[0] & 0x80)) {
		memcpy(buf, m->fld[1].buf, s_isodef[0].len);
		buf += s_isodef[1].len;
		flds = 128;
	}
	else {
		if ((m->fld[1].len == 8) && !(m->fld[1].buf[0] & 0x80)) {
			memcpy(buf, m->fld[1].buf, 8);
			buf += 8;
			flds = 64;
		}
		else {
			MY_TRACE("flds = %d", 1);
			return -1;
		}
	}
#else
	if ((m->fld[1].len != 8) || (m->fld[1].buf[0] & 0x80)) {	//不是64位版则返回
		MY_TRACE("flds = %d", 1);
		return -1;
	}
	memcpy(buf, m->fld[1].buf, m->fld[1].len);	//位图字段操作
	buf += m->fld[1].len;
	flds = 64;
#endif
	for (i = 2; i <= flds; i++) {
		if (BITGET(m->fld[1].buf, i)) {	//第i字段不为零
			if (m->fld[i].buf == NULL || m->fld[i].len <= 0 || m->fld[i].len > s_isodef[i].len) {	//异常情况
				MY_TRACE("flds = %d", i);
				return -1;
			}
			if (s_isodef[i].fmt) {  //不定长
				if (s_iCompress) {	//需要压缩
					sprintf(fmt, "%%0%dd", s_isodef[i].fmt);		//格式化成 %0?d
					sprintf(tmp, fmt, m->fld[i].len);		//最终格式化,  tmp里面存的是长度
					buf += ASC2BCD((unsigned char*)buf, tmp, s_isodef[i].fmt, 0);		//把长度转BCD压缩
				}
				else {	//无需压缩
					sprintf(fmt, "%%0%dd", s_isodef[i].fmt);	//格式化成 %0?d
					sprintf(buf, fmt, m->fld[i].len);	//最终格式化,  tmp里面存的是长度
					buf += s_isodef[i].fmt;		//把长度存入BUFF
				}
			}
			switch (s_isodef[i].typ) {	//确认类型，BCD，ASC，BIN
				case TYP_BCD:
					if (s_iCompress) {		//需要压缩
						buf += ASC2BCD((unsigned char*)buf, (char*)m->fld[i].buf, m->fld[i].len, s_isodef[i].fmt);
						break;
					}
				case TYP_ASC:
				case TYP_BIN:
					memcpy(buf, m->fld[i].buf, m->fld[i].len);
					buf += m->fld[i].len;
					break;
				default:
					MY_TRACE("flds = %d", i);
					return -1;
					break;
			}
		}
	}
	return (buf-start);		//返回总的buf长度
}

/***********************************************************************
		module		:	[8583协议]
		function		:	[把buf中数据按定义好的格式解包到ISO_MSG变量m中]
  		return			:	[-1：异常
								其他：buf的长度]
		comment	:	[全局普通函数]
		machine		:	[无]
		language	:	[CHN]
 		keyword		:	[内部有MALLOC操作，用完需要函数iso8583_free进行释放]
		date			:	[11/08/10]
 		author		:	[chen-zhengkai]
************************************************************************/
int iso8583_unpack(ISO_MSG *m, const char *buf)
{
	const char* start = buf;
	int flds, i;
	char fmt[8];
	memset(fmt, 0, sizeof(fmt));

	//0域的操作
	if (m->fld[0].buf != NULL || s_isodef[0].fmt != FMT_FIXED) {	//异常处理
		MY_TRACE("flds = %d", 0);
		return -1;
	}
	m->fld[0].len = s_isodef[0].len;
	memset(m->fld[0].buf, 0x00, NUM);
	if (s_iCompress) {
		buf += BCD2ASC((char*)m->fld[0].buf, (unsigned char*)buf, m->fld[0].len, s_isodef[0].fmt);
	}
	else {
		memcpy(m->fld[0].buf, buf, m->fld[0].len);
		buf += m->fld[0].len;
	}

	//操作1域，位图域
#if ISO_FLDS==128
	if(buf[0] & 0x80) {		//128位版
		flds = 128;
	} 
	else {
		flds = 64;
	}
#else
	if( buf[0] & 0x80 ) {	//128位版
		MY_TRACE("flds = %d", 1);
		return -1;
	}
	flds = 64;
#endif
	m->fld[1].len = flds/8;		//64位8字节，128位16字节
	memset(m->fld[1].buf, 0x00, NUM);
	memcpy(m->fld[1].buf, buf, m->fld[1].len);
	buf += m->fld[1].len;	//偏移
	//2--64（128）域操作
	for (i = 2; i <= flds; i++) {
		if (BITGET(m->fld[1].buf, i)) {	//第i字段不为零
			//长度处理
			if ( s_isodef[i].fmt) {	//不定长
				if ( s_iCompress ) {	//需解压
					buf += BCD2INT(&(m->fld[i].len), (unsigned char*)buf, s_isodef[i].fmt, 0);
				}
				else {
					sprintf(fmt, "%%0%dd", s_isodef[i].fmt);		//格式化成 %0?d
					sscanf(buf, fmt, &(m->fld[i].len));		//把buf内容格式化成整数存入len
					buf += s_isodef[i].fmt;	//偏移
				}
				if (m->fld[i].len > s_isodef[i].len) {	//异常处理
					MY_TRACE("flds = %d", i);
					return -1;
				}
			}
			else {	//定长
				m->fld[i].len = s_isodef[i].len;
			}
			//内容处理
			memset(m->fld[i].buf, 0x00, NUM);
			switch (s_isodef[i].typ) {
				case TYP_BCD:
					if (s_iCompress) {
						buf += BCD2ASC((char*)m->fld[i].buf, (unsigned char*)buf, m->fld[i].len, s_isodef[i].fmt); 
						break;
					}
				case TYP_ASC:
				case TYP_BIN:
					memcpy(m->fld[i].buf, buf, m->fld[i].len);
					buf += m->fld[i].len;
					break;
				default:
					MY_TRACE("flds = %d", i);
					return -1;
			}
		}
	}
	return (buf-start);	//返回长度
}


/***********************************************************************
		module		:	[8583协议]
		function		:	[把ISO_MSG变量m中数据按定义好的格式保存到FILE中]
  		return			:	[无]
		comment	:	[全局普通函数]
		machine		:	[无]
		language	:	[CHN]
 		keyword		:	[无]
		date			:	[11/08/10]
 		author		:	[chen-zhengkai]
************************************************************************/
void iso8583_dump(FILE *fp, ISO_MSG *m)
{
	int i, j;
	
	for (i=0; i<=ISO_FLDS; i++) {
		if (m->fld[i].buf != NULL) {
			fprintf(fp, "\nfield #%02d %03d:", i, m->fld[i].len);
			for (j=0; j<m->fld[i].len; j++) {
				fprintf(fp, " %02X", m->fld[i].buf[j]);
			}
		}
	}
}

/***********************************************************************
		module		:	[8583协议]
		function		:	[释放ISO_MSG变量m中数据及占用空间,unpack之前需要free]
  		return			:	[无]
		comment	:	[全局普通函数]
		machine		:	[无]
		language	:	[CHN]
 		keyword		:	[无]
		date			:	[11/08/10]
 		author		:	[chen-zhengkai]
************************************************************************/
//void iso8583_free(ISO_MSG *m)
//{
//	int i;
//	for (i=0; i<=ISO_FLDS; i++) {
//		if (m->fld[i].buf != NULL) {
//			free(m->fld[i].buf);
//			m->fld[i].buf = NULL;
//			m->fld[i].len = 0;
//		}
//	}
//}
/***********************************************************************
		module		:	[8583协议]
		function		:	[asc转bcd]
  		return			:	[处理的BCD字节长度]
		comment	:	[全局普通函数]
		machine		:	[无]
		language	:	[CHN]
 		keyword		:	[无]
		date			:	[11/08/10]
 		author		:	[chen-zhengkai]
************************************************************************/
int ASC2BCD (unsigned char *bcd, const char *asc, int len, int fmt)/*	参数:
																															bcd: 转化后BCD结果
																															asc: 需转化ASC字符串
																															len: 需转化长度
																															fmt: 转化后的格式，即长度为奇数时，前补还是后补零*/
{
	int i, odd;
	char c;
	
	odd = len&0x01;
 
	if ( odd && !fmt) {
		*bcd++ = (*asc++) & '/x0F';
	}
	len >>= 1;
	for (i=0; i<len; i++) {
		c = (*asc++) << 4;
		c |= (*asc++) & '/x0F';
		*bcd++ = c;
	}
	if ( odd && fmt) {
		*bcd = (*asc) << 4;
	}
	return (i+odd);
}

/***********************************************************************
		module		:	[8583协议]
		function		:	[bcd转asc]
  		return			:	[处理的BCD字节长度]
		comment	:	[全局普通函数]
		machine		:	[无]
		language	:	[CHN]
 		keyword		:	[无]
		date			:	[11/08/10]
 		author		:	[chen-zhengkai]
************************************************************************/
int BCD2ASC (char *asc, const unsigned char *bcd, int len, int fmt)		/* 参数
																																asc: 转化后ASC结果
																																bcd: 需转化BCD字符串
																																len: 需转化长度
																																fmt: 需转化BCD的格式，即长度为奇数时，前补还是后补零*/
{
	int i, odd;
	unsigned char c;
	odd = len&0x01;
	
	if ( odd && !fmt) {
		*asc++ = ((*bcd++)&'/x0F') + '0';
	}
	len >>= 1;
	for (i=0; i<len; i++) {
		c = *bcd++; 
		*asc++ = (c>>4) + '0';
		*asc++ = (c&'/x0F') + '0';
	}
	if ( odd && fmt) {
		*asc = ((*bcd)>>4) + '0';
	}
	return (i+odd);
}
/***********************************************************************
		module		:	[8583协议]
		function		:	[bcd转int]
  		return			:	[处理的BCD字节长度]
		comment	:	[全局普通函数]
		machine		:	[无]
		language	:	[CHN]
 		keyword		:	[无]
		date			:	[11/08/10]
 		author		:	[chen-zhengkai]
************************************************************************/
int BCD2INT(int *plen, const unsigned char *bcd, int len, int fmt)		/* 参数
																															plen: 转化后int结果指针
																															bcd: 需转化BCD字符串
																															len: 需转化长度
																															fmt: 需转化BCD的格式，即长度为奇数时，前补还是后补零*/
{
	int l=0, i, odd;
	unsigned char c;
	
	odd = len&0x01;
	
	if ( odd && !fmt) {
		l = (*bcd++)&'/x0F';
	}
	len >>= 1;
	for (i=0; i<len; i++) {
		c = *bcd++;
		l *= 10;
		l += c>>4;
		l *= 10;
		l += c&'/x0F';
	}
	if ( odd && fmt) {
		l *= 10;
		l += (*bcd)>>4;
	}
	*plen = l;
	return (i+odd);
}
