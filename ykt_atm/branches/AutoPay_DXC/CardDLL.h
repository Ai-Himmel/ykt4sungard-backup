//使用预编译指令保证头文件只能被包含一次
#ifndef __CardDLL_H__
#define __CardDLL_H__

//用预编译指令使C函数能被C++程序直接调用
#ifdef __cplusplus
extern "C" {
#endif

//最后更行 消费限额
int __stdcall SetConsumeLimit(unsigned int max_per_count,unsigned int max_per_day);
int __stdcall ReadConsumeLimit(unsigned int *max_per_count,unsigned int *max_per_day);

#ifdef __cplusplus
}
#endif



#endif
