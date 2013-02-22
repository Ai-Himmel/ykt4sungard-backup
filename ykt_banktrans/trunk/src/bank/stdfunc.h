/**********************stdfunc.h***********************/

#ifndef _STD_FUNC_H_
#define _STD_FUNC_H_

/* 
����
bcd: ת����BCD���
asc: ��ת��ASC�ַ���
len: ��ת������
fmt: ת����ĸ�ʽ��������Ϊ����ʱ��ǰ�����Ǻ���
����ֵ
�����BCD�ֽڳ���
*/
int ASC2BCD(unsigned char *bcd, const char *asc, int len, int fmt);

/* 
����
asc: ת����ASC���
bcd: ��ת��BCD�ַ���
len: ��ת������
fmt: ��ת��BCD�ĸ�ʽ��������Ϊ����ʱ��ǰ�����Ǻ���
����ֵ
�����BCD�ֽڳ���
*/
int BCD2ASC(char *asc, const unsigned char *bcd, int len, int fmt);

/* 
����
plen: ת����int���ָ��
bcd: ��ת��BCD�ַ���
len: ��ת������
fmt: ��ת��BCD�ĸ�ʽ��������Ϊ����ʱ��ǰ�����Ǻ���
����ֵ
�����BCD�ֽڳ���
*/
int BCD2INT(int *plen, const unsigned char *bcd, int len, int fmt);


#endif /* _STD_FUNC_H_ */

