//ʹ��Ԥ����ָ�֤ͷ�ļ�ֻ�ܱ�����һ��
#ifndef __CardDLL_H__
#define __CardDLL_H__

//��Ԥ����ָ��ʹC�����ܱ�C++����ֱ�ӵ���
#ifdef __cplusplus
extern "C" {
#endif

//������ �����޶�
int __stdcall SetConsumeLimit(unsigned int max_per_count,unsigned int max_per_day);
int __stdcall ReadConsumeLimit(unsigned int *max_per_count,unsigned int *max_per_day);

#ifdef __cplusplus
}
#endif



#endif
