#ifndef _CONFIG_H_
#define _CONFIG_H_

#define DEBUG 0 // 调试模式

#define SAVE_CARD_REC 0 // 保存卡流水模式
#define CHECK_CARD_INVTERVAL 1

#define ENABLE_MIFARE_CARD 1 // mifare card 模式

#define IMMC_CPU_CARD	0	//内蒙医学院cpu卡

//#define USE_DOG 1 // 使用看门狗

#define USE_INFRARED_COMM 1 // 使用红外模式
#define USE_GPRS 1 // 使用GPRS 

#define USE_WIFI 0 // 使用 wifi

#define ENABLE_AUDIO 1 // 谁用语音

#define ENABLE_BLKLST 1 // 启用黑名单

// 定义版本信息
// N 表示标准串口版本
// I 表示红外端口版本
// W 表示 wifi 版本
// M 表示 MIFARE 卡版本
// C 表示 CPU 卡版本
// G 表示 GPRS 版本
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

