#ifndef _CPUCARD_H_
#define _CPUCARD_H_

#include <sys/types.h>

#define uint32 unsigned int
#define uint16 unsigned short
#define int32 int
#define int16 short
#define byte unsigned char

typedef struct {
	int trade_type; // 0 圈存 1消费
	size_t balance; // 入卡值
	size_t tradeamt; // 交易金额 
	size_t tradecnt; // 交易次数
	char tx_datetime[15]; // 交易日期+时间
	size_t random_key; // 随机数
	size_t termid; // 终端号
	size_t termsno; // 终端交易序号
	byte sk[8];  // 过程密钥
	byte mac1[8]; // mac1
	byte mac2[8]; // mac1
}cpu_trade_t;

size_t cpu_hex2str(const byte *hex,size_t len,char *str);
size_t cpu_str2hex(const char *str,size_t len,byte *hex);

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
int cpu_calc_mac2(cpu_trade_t *trade);

int cpu_calc_mac1(cpu_trade_t *trade);
#endif //  _CPUCARD_H_

