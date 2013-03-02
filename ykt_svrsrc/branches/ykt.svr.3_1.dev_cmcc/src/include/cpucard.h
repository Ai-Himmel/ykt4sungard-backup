#ifndef _CPUCARD_H_
#define _CPUCARD_H_

#include <sys/types.h>

#define uint32 unsigned int
#define uint16 unsigned short
#define int32 int
#define int16 short
#define uint8 unsigned char

typedef struct {
	int trade_type; // 0 圈存 1消费
	size_t balance; // 入卡值
	size_t tradeamt; // 交易金额 
	size_t tradecnt; // 交易次数
	char tx_datetime[15]; // 交易日期+时间
	char random_key[9]; // 随机数
	char  termno[13]; // 终端号
	size_t termsno; // 终端交易序号
	char  cardphyid[17];	//物理卡号
	unsigned char sk[9];  // 过程密钥
	char mac1[9]; // mac1
	char mac2[9]; // mac2
}cpu_trade_t;

size_t cpu_hex2str(const uint8 *hex,size_t len,char *str);
size_t cpu_str2hex(const char *str,size_t len,uint8 *hex);
size_t cpu_str2bcd(const char *str,size_t len,uint8 *bcd);

/** 
 * @brief 计算过程密钥
 * 
 * @param key - 主密钥
 * @param trade - 交易信息
 * 
 * @return - 0 表示成功
 */
int cpu_calc_sk(const char *key,cpu_trade_t *trade);
/** 
 * @brief 计算 MAC1 
 * 
 * @param trade 
 * 
 * @return - 0 表示成功
 */

unsigned char* pboc_diver_key ( unsigned char cardno[9], unsigned char key_in[17], unsigned char key_out[17] );
int cpu_calc_mac(cpu_trade_t *trade);

//int cpu_calc_mac1(cpu_trade_t *trade);
#endif //  _CPUCARD_H_

