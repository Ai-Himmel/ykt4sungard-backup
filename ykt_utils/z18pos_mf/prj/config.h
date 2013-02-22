#ifndef _CONFIG_H_
#define _CONFIG_H_

#define DEBUG 0 // ����ģʽ

#define SAVE_CARD_REC 0 // ���濨��ˮģʽ
#define CHECK_CARD_INVTERVAL 1

#define ENABLE_MIFARE_CARD 1 // mifare card ģʽ

#define IMMC_CPU_CARD	0	//����ҽѧԺcpu��

//#define USE_DOG 1 // ʹ�ÿ��Ź�

#define USE_INFRARED_COMM 1 // ʹ�ú���ģʽ
#define USE_GPRS 1 // ʹ��GPRS 

#define USE_WIFI 0 // ʹ�� wifi

#define ENABLE_AUDIO 1 // ˭������

#define ENABLE_BLKLST 1 // ���ú�����

// ����汾��Ϣ
// N ��ʾ��׼���ڰ汾
// I ��ʾ����˿ڰ汾
// W ��ʾ wifi �汾
// M ��ʾ MIFARE ���汾
// C ��ʾ CPU ���汾
// G ��ʾ GPRS �汾
#define _VER_STR "100925"

#if USE_INFRARED_COMM==1 && USE_GPRS == 1
#define  _VER_STR1 _VER_STR "IG"
#elif USE_INFRARED_COMM
#define _VER_STR1 _VER_STR "I"
#elif USE_GPRS 
#define  _VER_STR1 _VER_STR "G"
#endif

#if ENABLE_MIFARE_CARD
#define VER_STR _VER_STR1 "M"
#else
#define VER_STR _VER_STR1 "C"
#endif

#endif // _CONFIG_H_

