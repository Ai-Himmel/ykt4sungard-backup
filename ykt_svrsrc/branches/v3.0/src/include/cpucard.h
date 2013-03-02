#ifndef _CPUCARD_H_
#define _CPUCARD_H_

#include <sys/types.h>

#define uint32 unsigned int
#define uint16 unsigned short
#define int32 int
#define int16 short
#define byte unsigned char

typedef struct {
	int trade_type; // 0 Ȧ�� 1����
	size_t balance; // �뿨ֵ
	size_t tradeamt; // ���׽�� 
	size_t tradecnt; // ���״���
	char tx_datetime[15]; // ��������+ʱ��
	size_t random_key; // �����
	size_t termid; // �ն˺�
	size_t termsno; // �ն˽������
	byte sk[8];  // ������Կ
	byte mac1[8]; // mac1
	byte mac2[8]; // mac1
}cpu_trade_t;

size_t cpu_hex2str(const byte *hex,size_t len,char *str);
size_t cpu_str2hex(const char *str,size_t len,byte *hex);

/** 
 * @brief ���������Կ
 * 
 * @param key - ����Կ
 * @param trade - ������Ϣ
 * 
 * @return - 0 ��ʾ�ɹ�
 */
int cpu_calc_sk(const char *key,cpu_trade_t *trade);
/** 
 * @brief ���� MAC1 
 * 
 * @param trade 
 * 
 * @return - 0 ��ʾ�ɹ�
 */
int cpu_calc_mac2(cpu_trade_t *trade);

int cpu_calc_mac1(cpu_trade_t *trade);
#endif //  _CPUCARD_H_

