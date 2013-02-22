/**********************stdfunc.h***********************/

#ifndef _STD_FUNC_H_
#define _STD_FUNC_H_

/* 
参数
bcd: 转化后BCD结果
asc: 需转化ASC字符串
len: 需转化长度
fmt: 转化后的格式，即长度为奇数时，前补还是后补零
返回值
处理的BCD字节长度
*/
int ASC2BCD(unsigned char *bcd, const char *asc, int len, int fmt);

/* 
参数
asc: 转化后ASC结果
bcd: 需转化BCD字符串
len: 需转化长度
fmt: 需转化BCD的格式，即长度为奇数时，前补还是后补零
返回值
处理的BCD字节长度
*/
int BCD2ASC(char *asc, const unsigned char *bcd, int len, int fmt);

/* 
参数
plen: 转化后int结果指针
bcd: 需转化BCD字符串
len: 需转化长度
fmt: 需转化BCD的格式，即长度为奇数时，前补还是后补零
返回值
处理的BCD字节长度
*/
int BCD2INT(int *plen, const unsigned char *bcd, int len, int fmt);


#endif /* _STD_FUNC_H_ */

