// XPack.h: interface for the CXPack class.
//
//////////////////////////////////////////////////////////////////////

/***********************************************************************************
  编码日志记录
  编码者: 陈永华
  编码日期 2004-10-10 15:07:25
  版本: V1.00 
  说明: 
      本类用于上层与业务相关的，并且提供类似与CPACK中的函数，但是仍然符合C＋＋编程
  以便前台VC程序方便调用本类功能。同时利用C＋＋的优势，
  例如利用两个实例分别处理CPACK兼容报文和其他PACK报文格式，通过上层程序完成协议转换工作
  为了兼容早期CPACK接口模式，在本类构造函数中直接装载CPACK.DAT文件(即证券CPACK打包方式)，
  如果没有该文件，则也不提示错误，以便直接使用新的结构定义文件。
      在本协议中，增加了传输交换自定义的报文中数据结构，如raw data block, 即位图表中
  不设置任何有效字段（数据列项），以便于自定义传输文件数据内容的协议。这时候，数据包中的
  数据字节序和对齐都提交给协议编程者控制，本基础模块不再作任何控制了。
      2004-10-14: CYH
      注意：在RAWDATA模式下，编码和解包中的数据包体中，使用ST_SDPACK结构，在ST_SDPACK::data
  部分为实际数据，主机字节序交给上层控制，但是作为数据长度的ST_SDPACK::usDataLength的字节序
  则仍然由本类控制转换，ST_SDPACK::usDataLength指的就是ST_SDPACK::data的长度，不包括自身的长度！！！
 ***********************************************************************************/


#if !defined(AFX_XPACK_H_)
#define AFX_XPACK_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PackB.h"
#include "PackHandle.h"

#ifdef XPACK_INC
#define XPACK_API 
#else
#ifdef PACKC_EXPORTS
#define XPACK_API __declspec(dllexport)
#else
#ifdef _WINDOWS
#define XPACK_API __declspec(dllimport)
#else
#define XPACK_API 
#endif
#endif
#endif

//设置位图的结束标志
#define END_FIELDMARK  -1

class XPACK_API CXPack  
{
private:
   CPackHandle phandle;
   
public:
	bool IsValidField(ST_PACKHEAD *phead, char *fieldname);
	bool IsValidField(ST_PACKHEAD *phead, int fidx);

   // 函数名: HostByteOrder
   // 编程  : 陈永华 2004-10-14 15:50:16
   // 描述  : 得到打包过程中的数据字节序转换
   // 返回  : void 
   // 参数  : void *data 
   // 参数  : unsigned int datalength
	void HostByteOrder(void *data, unsigned int datalength);

   // 函数名: GetPackLength
   // 编程  : 陈永华 2004-10-14 15:51:23
   // 描述  : 得到ST_PACK的完整长度
   // 返回  : int ：即sizeof(ST_PACK)
	int GetPackLength();

   // 函数名: IsRawDataPack
   // 编程  : 陈永华 2004-10-14 15:52:08
   // 描述  : 判断是否为RAW-DATA Mode
   // 返回  : bool 
   // 参数  : const ST_PACKHEAD *phead
	bool IsRawDataPack(const ST_PACKHEAD *phead);

   // 函数名: rev_data
   // 编程  : 陈永华 2004-10-14 15:52:37
   // 描述  : 数据的字节序转换
   // 返回  : static void 
   // 参数  : void *data
   // 参数  : unsigned int datalen
	static void rev_data(void *data,unsigned int datalen);

   static char * LRTrim(char *str);

	static unsigned short xmk_crc16(const void *ptr, int count);

   // 函数名: AddField
   // 编程  : 陈永华 2004-10-11 13:19:51
   // 描述  : 对记录prec中的名为fieldname的字段赋值，如果报文头phead!=NULL，则同时设置报头中相应的位图
   // 返回  : bool 赋值成功与否
   // 参数  : void *prec (OUT): 数据记录
   // 参数  : char *fieldname(IN): 字段名称
   // 参数  : double dvalue(IN): 字段的值
   // 参数  : ST_PACKHEAD *phead(OUT): 记录的相关报文头，
   //          如果不为NULL，则对此报头中的位图作相应的设置
   //          否则，仅作赋值处理
   bool AddField(void *prec, const char *fieldname, double dvalue, ST_PACKHEAD *phead=NULL);

   // 函数名: AddField
   // 编程  : 陈永华 2004-10-11 13:21:58
   // 描述  : 对记录prec中的名为fieldname的字段赋值，如果报文头phead!=NULL，则同时设置报头中相应的位图
   // 返回  : bool 赋值成功与否
   // 参数  : void *prec (OUT): 数据记录
   // 参数  : char *fieldname(IN): 字段名称
   // 参数  : int ivalue(IN): 字段的值
   // 参数  : ST_PACKHEAD *phead(OUT): 记录的相关报文头，
   //          如果不为NULL，则对此报头中的位图作相应的设置
   //          否则，仅作赋值处理
   bool AddField(void *prec, const char *fieldname, int ivalue, ST_PACKHEAD *phead=NULL);

   // 函数名: AddField
   // 编程  : 陈永华 2004-10-11 13:23:05
   // 描述  : 对记录prec中的名为fieldname的字段赋值，如果报文头phead!=NULL，则同时设置报头中相应的位图
   // 返回  : bool 赋值成功与否
   // 参数  : void *prec (OUT): 数据记录
   // 参数  : char *fieldname(IN): 字段名称
   // 参数  : char *data(IN): 字段的值，当字段为PDL_UCHAR类型，可以为0x????或用其他的，但是建议采用0x?????
   // 参数  : ST_PACKHEAD *phead(OUT): 记录的相关报文头，
   //          如果不为NULL，则对此报头中的位图作相应的设置
   //          否则，仅作赋值处理
   bool AddField(void *prec, const char *fieldname, const char *data, ST_PACKHEAD *phead=NULL);

   // 函数名: AddField
   // 编程  : 陈永华 2004-10-11 13:23:15
   // 描述  : 对记录prec中的名为fieldname的字段赋值，如果报文头phead!=NULL，则同时设置报头中相应的位图
   // 返回  : bool 赋值成功与否
   // 参数  : void *prec (OUT): 数据记录
   // 参数  : int fidx(IN): 赋值的字段编号
   // 参数  : double dvalue(IN): 字段的值
   // 参数  : ST_PACKHEAD *phead(OUT): 记录的相关报文头，
   //          如果不为NULL，则对此报头中的位图作相应的设置
   //          否则，仅作赋值处理
   bool AddField(void *prec, int fidx, double dvalue, ST_PACKHEAD *phead=NULL);

   // 函数名: AddField
   // 编程  : 陈永华 2004-10-11 13:23:26
   // 描述  : 对记录prec中的名为fieldname的字段赋值，如果报文头phead!=NULL，则同时设置报头中相应的位图
   // 返回  : bool 赋值成功与否
   // 参数  : void *prec (OUT): 数据记录
   // 参数  : int fidx(IN): 赋值的字段编号
   // 参数  : int ivalue(IN): 字段的值
   // 参数  : ST_PACKHEAD *phead(OUT): 记录的相关报文头，
   //          如果不为NULL，则对此报头中的位图作相应的设置
   //          否则，仅作赋值处理
   bool AddField(void *prec, int fidx, int ivalue, ST_PACKHEAD *phead=NULL);

   // 函数名: AddField
   // 编程  : 陈永华 2004-10-11 13:23:38
   // 描述  : 对记录prec中的名为fieldname的字段赋值，如果报文头phead!=NULL，则同时设置报头中相应的位图
   // 返回  : bool 赋值成功与否
   // 参数  : void *prec (OUT): 数据记录
   // 参数  : int fidx(IN): 赋值的字段编号
   // 参数  : char *data(IN): 字段的值，当字段为PDL_UCHAR类型，可以为0x????或用其他的，但是建议采用0x?????
   // 参数  : ST_PACKHEAD *phead(OUT): 记录的相关报文头，
   //          如果不为NULL，则对此报头中的位图作相应的设置
   //          否则，仅作赋值处理
   bool AddField(void *prec, int fidx, const char *data, ST_PACKHEAD *phead=NULL);

   // 函数名: CheckValidField
   // 编程  : 陈永华 2004-10-11 13:23:48
   // 描述  : 检查报文头，判断是否指定的字段列项为有效值
   // 返回  : bool ：true－有效的字段列项；false－无效的字段列项
   // 参数  : const ST_PACKHEAD *phead(IN):相关的报文头
   // 参数  : int fidx（IN）：指定字段列项
	bool CheckValidField(const ST_PACKHEAD *phead, int fidx);

   // 函数名: FindFieldIndex
   // 编程  : 陈永华 2004-10-10 23:32:29
   // 描述  : 查找字段名为fieldname的字段编号
   // 返回  : int >=0: 成功，返回该字段编号；<0: 在定义表中没有该名称的字段
   // 参数  : char *fieldname（IN）：字段名称，注意大小写敏感
   int FindFieldIndex(char *fieldname);

   // 为JNI接口中string类型调用
	int FindCFieldIndex(const char *fieldname);

   // 函数名: GetPrintFieldValue
   // 编程  : 陈永华 2004-10-10 23:28:59
   // 描述  : 从数据记录prec中，输出指定字段pfd的值，以显示跟踪格式返回
   // 返回  : char * 返回格式化的字段值，==NULL:非法字段
   //          对于PDL_UCHAR类数据字段，则以0xXX..XX的字符串返回
   // 参数  : void *prec（IN）：数据记录
   // 参数  : int fidx（IN）：字段编号
   // 参数  : char *pfv（OUT）：输出缓冲区
   //             由于字段定义长度不超过256，因此注意为了安全，本参数的长度应该大于等于256字节
   // 参数  : int prec(IN): 对于PDL_DOUBLE有效，用于定义返回的小数点位数；
   //          -1: 则以%lf返回
   char * GetPrintFieldValue(const void *prec, int fidx, char *pfv, int precision=-1);


   // 函数名: GetFieldValueD
   // 编程  : 陈永华 2004-10-11 14:55:09
   // 描述  : 从数据记录中，读取字段名为fieldname的值（用double方式返回）
   // 返回  : double 返回字段的double值
   // 参数  : void *prec（IN）：数据记录
   // 参数  : char *fieldname（IN）：字段名称
   double GetFieldValueD(const void *prec, const char *fieldname);

   // 函数名: GetFieldValueD
   // 编程  : 陈永华 2004-10-11 14:55:04
   // 描述  : 从数据记录中，读取字段编号为fidx的值（用double方式返回）
   // 返回  : double 返回字段的double值
   // 参数  : void *prec（IN）：数据记录
   // 参数  : int fidx（IN）：字段编号
   double GetFieldValueD(const void *prec, int fidx);

   // 函数名: GetFieldValueI
   // 编程  : 陈永华 2004-10-11 14:54:58
   // 描述  : 从数据记录中，读取字段名为fieldname的值（用int方式返回）
   // 返回  : int 返回字段的整数值
   // 参数  : void *prec（IN）：数据记录
   // 参数  : char *fieldname（IN）：字段名称
   int GetFieldValueI(const void *prec, const char *fieldname);

   // 函数名: GetFieldValueI
   // 编程  : 陈永华 2004-10-11 14:54:45
   // 描述  : 从数据记录中，读取字段编号为fidx的值（用int方式返回）
   // 返回  : int 返回字段的整数值
   // 参数  : void *prec（IN）：数据记录
   // 参数  : int fidx（IN）：字段编号
   int GetFieldValueI(const void *prec, int fidx);
   
   
   // 函数名: GetFieldValue
   // 编程  : 陈永华 2004-10-10 23:04:20
   // 描述  : 从数据记录中，读取字段名为fieldname的值（用字符串方式返回）
   // 返回  : char * 返回字段的值，==NULL:表示无效的字段名
   // 参数  : void *prec（IN）：数据记录
   // 参数  : char *fieldname（IN）：字段名称
   // 参数  : char *value（OUT）：返回的字段值（用字符串方式表示）
   //             如果为PDL_UCHAR，则为该BIN字段的整个值，应该以BIN分解数据；
   //                 为PDL_INT,则为%d方式返回；
   //                 为PDL_DOUBLE字段，则为%lf方式转换为字符串；
   //             由于字段定义长度不超过256，因此注意为了安全，本参数的长度应该大于等于256字节
   char * GetFieldValue(const void *prec, const char *fieldname, char *value);

   // 函数名: GetFieldValue
   // 编程  : 陈永华 2004-10-10 23:00:30
   // 描述  : 从数据记录中，读取字段编号为fidx的值（用字符串方式返回）
   // 返回  : char * 返回字段的值，==NULL:表示无效的字段编号
   //          注意：当本字段为PDL_UCHAR，则返回的数据以raw-data复制返回的
   // 参数  : void *prec（IN）：数据记录
   // 参数  : int fidx（IN）：字段编号
   // 参数  : char *value（OUT）：返回的字段值（用字符串方式表示）
   //             如果为PDL_UCHAR，则为该BIN字段的整个值，应该以BIN分解数据
   //                 为PDL_INT,则为%d方式返回；
   //                 为PDL_DOUBLE字段，则为%lf方式转换为字符串；
   //             由于字段定义长度不超过256，因此注意为了安全，本参数的长度应该大于等于256字节
   char * GetFieldValue(const void *prec, int fidx, char *value);


   // 函数名: GetFieldValue
   // 编程  : 陈永华 2004-10-10 23:04:20
   // 描述  : 从数据记录中，读取字段名为fieldname的值（用字符串方式返回）
   // 2006-6-1 9:47:08 为了提高处理效率，能够同时返回该字段的类型给上层
   // 返回 : int 字段类型：
   //          PDL_CHAR=1,          普通字符串模式，约定长度，最长不超过255
   //          PDL_VCHAR=2,         变长字符，最长不超过255
   //          PDL_UCHAR=3,         用于存放二进制数据的字段，比如权限等
   //          PDL_INT=4,           整数字段，（由于在64位机中，long属于64位，而在32位机中则为32位，对于int则是固定的，因此本协议中不再采用long）
   //          PDL_DOUBLE=5         double类型字段
   ////         // 返回  : char * 返回字段的值，==NULL:表示无效的字段名
   // 参数  : void *prec（IN）：数据记录
   // 参数  : char *fieldname（IN）：字段名称
   // 参数  : char *value（OUT）：返回的字段值（用字符串方式表示）
   //             如果为PDL_UCHAR，则为该BIN字段的整个值，应该以BIN分解数据；
   //                 为PDL_INT,则为%d方式返回；
   //                 为PDL_DOUBLE字段，则为%lf方式转换为字符串；
   //             由于字段定义长度不超过256，因此注意为了安全，本参数的长度应该大于等于256字节
   int IGetFieldValue(const void *prec, const char *fieldname, char *value);

   // 函数名: GetFieldValue
   // 编程  : 陈永华 2004-10-10 23:00:30
   // 描述  : 从数据记录中，读取字段编号为fidx的值（用字符串方式返回）
   // 2006-6-1 9:47:08 为了提高处理效率，能够同时返回该字段的类型给上层
   // 返回 : int 字段类型：
   //          PDL_CHAR=1,          普通字符串模式，约定长度，最长不超过255
   //          PDL_VCHAR=2,         变长字符，最长不超过255
   //          PDL_UCHAR=3,         用于存放二进制数据的字段，比如权限等
   //          PDL_INT=4,           整数字段，（由于在64位机中，long属于64位，而在32位机中则为32位，对于int则是固定的，因此本协议中不再采用long）
   //          PDL_DOUBLE=5         double类型字段
   ////         // 返回  : char * 返回字段的值，==NULL:表示无效的字段名
   // 参数  : void *prec（IN）：数据记录
   // 参数  : int fidx（IN）：字段编号
   // 参数  : char *value（OUT）：返回的字段值（用字符串方式表示）
   //             如果为PDL_UCHAR，则为该BIN字段的整个值，应该以BIN分解数据
   //                 为PDL_INT,则为%d方式返回；
   //                 为PDL_DOUBLE字段，则为%lf方式转换为字符串；
   //             由于字段定义长度不超过256，因此注意为了安全，本参数的长度应该大于等于256字节
   int IGetFieldValue(const void *prec, int fidx, char *value);
   
   // 函数名: GetPackDef
   // 编程  : 陈永华 2004-10-10 22:53:58
   // 描述  : 得到整个完整数据报文结构定义
   // 返回  : const ST_PDATALIST *: 返回报文结构定义数据的位置
   // 参数  : int &ilastvfidx（OUT）：最后一个有效字段/数据列项的编号
   const ST_PDATALIST * GetPackDef(int &ilastvfidx);

   // 函数名: GetValidFieldCount
   // 编程  : 陈永华 2004-10-10 22:47:49
   // 描述  : 根据数据报文头，得到有效数据列数/字段数
   // 返回  : int 有效数据列数
   // 参数  : const ST_PACKHEAD *phead（IN）：数据报文头
	int GetValidFieldCount(const ST_PACKHEAD *phead);

   // 函数名: GetValidFieldInfo
   // 编程  : 陈永华 2004-10-10 22:46:17
   // 描述  : 根据当前数据报文头得到有效的vfnumber字段的定义信息
   // 返回  : const ST_PDATALIST *：返回有效字段的定义信息； NULL - 失败，超出有效字段个数；
   // 参数  : const ST_PACKHEAD *phead(IN): 被检查统计的数据报文头
   // 参数  : int vfnumber(IN)： 从0开始的字段有效列号
	const ST_PDATALIST * GetValidFieldInfo(const ST_PACKHEAD *phead,int vfnumber);

   // 函数名: OverwritePack
   // 编程  : 陈永华 2004-10-10 22:39:12
   // 编程  : 陈永华 2004-10-10 19:12:22
   // 描述  : 将目标报文数据记录中空的数据，用源报文中的有效数据填写（本操作只对单记录有效）
   //          如果目标报文中含有有效的数据，则不用源报文覆盖
   // 返回  : void 
   // 参数  : ST_PACKHEAD *dhead(OUT): 目标报文头
   // 参数  : void *dpack（OUT）：目标报文记录
   // 参数  : const ST_PACKHEAD *shead(IN): 源报文头
   // 参数  : const void *spack（IN）：源报文记录
	void OverwritePack(ST_PACKHEAD *dhead, void *dpack, const ST_PACKHEAD *shead,const void *spack);

   // 函数名: ClearParmBit
   // 编程  : 陈永华 2004-10-10 22:34:22
   // 描述  : 对用编号fidx指定的字段的相应位图进行清除
   // 返回  : int <0: 失败，非法字段位图编码；>=0: 成功，即为该字段编号
   // 参数  : ST_PACKHEAD *phead (OUT): 被设置的数据报文头
   // 参数  : int fidx（IN）：被指定要清除的字段（数据列项）
	int ClearParmBit(ST_PACKHEAD *phead,int fidx);

   // 函数名: SetParmBit
   // 编程  : 陈永华 2004-10-10 22:31:12
   // 描述  : 对用编号fidx指定的字段的相应位图进行设置
   // 返回  : int <0: 失败，非法字段位图编码；>=0: 成功，即为该字段编号
   // 参数  : ST_PACKHEAD *phead (OUT): 被设置的数据报文头
   // 参数  : int fidx（IN）：被指定的字段（数据列项）
	int SetParmBit(ST_PACKHEAD *phead,int fidx);

   // 函数名: EmulateEncodeLength
   // 编程  : 陈永华 2004-10-10 22:26:51
   // 描述  : 根据已经设置的位图表，估算一条记录（或数据块）最大占用的编码缓冲区的长度
   // 返回  : int ：返回编码需要最大的缓冲区长度
   // 参数  : const ST_PACKHEAD *phead(IN): 已经设置位图表的数据报文头
	int EmulateEncodeLength(const ST_PACKHEAD *phead);

   // 函数名: DecodeRow
   // 编程  : 陈永华 2004-10-10 22:21:37
   // 描述  : 根据报文头phead将编码缓冲区ebuf进行解码，解码到的数据pdata中
   // 返回  : int
   /* 
         >=0:成功，返回编码占用的长度；
         <0:解码失败 
            -1: 编码位图有误(有未定义的位图设置); 
            -2: 编码中字段数据超出定义;
            -10: 缓冲区长度不足
   */
   // 参数  : ST_PACKHEAD *phead (IN): 解码的位图表
   // 参数  : void *ebuf（IN）：编码缓冲区
   // 参数  : int eblen（IN）：编码缓冲区的长度
   // 参数  : void *pdata（OUT）：用于存放解码的数据
	int DecodeRow(const ST_PACKHEAD *phead, const void *ebuf, int eblen, void *pdata);

   // 函数名: DecodeHead
   // 编程  : 陈永华 2004-10-10 22:10:29
   // 描述  : 将编码缓冲区中解码到包头中
   // 返回  : int >0:解码成功，返回编码长度 ；<0 - 缓冲区长度太小
   // 参数  : void *buf [IN] : 编码缓冲区 
   // 参数  : int blen [IN] : 编码缓冲区长度
   // 参数  : ST_PACKHEAD *pHead [OUT]: 包头指针
	int DecodeHead(const void *buf, int blen, ST_PACKHEAD *pHead);

   // 函数名: EncodeRow
   // 编程  : 陈永华 2004-10-10 21:49:11
   // 描述  : 根据数据报文头，对数据pdata进行编码，将编码结果存放到ebuf中。
   //          正常报文头中的位图设置了有效位图，则作正常报文定义的字段内容编码；
   //          但是如果有效位图都为空，则采用raw-data编码，以支持raw-data协议（自定义数据协议）
   // 返回  : int >0，则编码成功，返回实际编码使用的长度；
   //             <=0, 编码失败：
   //                  0: phead->recCount<=0或pdata==NULL
   //                 -1: 编码位图有误(有未定义的位图设置); 
   //                 -10: 普通情况下的缓冲区不足
   //                 -11: 自定义类情况下的缓冲区长度不足
   // 参数  : const ST_PACKHEAD *phead（IN）：编码使用的数据报文头
   // 参数  : const void *pdata（IN）：被编码的数据内容
   // 参数  : void *ebuf（OUT）：用于存放编码结果的缓冲区
   // 参数  : int ebsize（IN）：编码缓冲区的最大长度
   int EncodeRow(const ST_PACKHEAD *phead, const void *pdata, void *ebuf, int ebsize);

   // 函数名: EncodeHead
   // 编程  : 陈永华 2004-10-10 21:38:51
   // 描述  : 将包头数据编码到指定的缓冲区
   // 返回  : int >0:编码成功，返回编码后使用编码缓冲区的长度
   // 参数  : ST_PACKHEAD *pHead 〔IN〕 被编码的包头数据
   // 参数  : void *buf 〔OUT〕存放编码的缓冲区
	int EncodeHead(const ST_PACKHEAD *pHead, void *buf);

   // 函数名: ResetPackHead
   // 编程  : 陈永华 2004-10-10 21:01:05
   // 描述  : 根据本报文基本约定，对数据报文头作重置
   //          如果有参考报文头（如因上下文要求，对读取后续报文数据的时候，
   //          需要将上次收到的应答报文头中的hook复制到初试报文头中；
   //          而对于应答报文头，则请求报文头作为参考报文头，需要将客户端请求的userdata，
   //          复制到作应答的重置报文头中）
   //          对于其他变量，则留给上层程序控制，这里都一概置为0（包括位图表）
   // 返回  : void 
   // 参数  : ST_PACKHEAD *phead
   // 参数  : const ST_PACKHEAD *refphead=NULL
	void ResetPackHead(ST_PACKHEAD *phead, const ST_PACKHEAD *refphead=NULL);

   // 函数名: Initialize
   // 编程  : 陈永华 2004-10-10 19:04:25
   // 描述  : 初始化本数据包句柄，装载数据包结构定义文件
   // 返回  : int 
   //           >=0  - 成功 返回版本号；
   //            -1  - 包格式文件不能打开；
   //            -2  - 指定文件格式错误；不能被本版本所辨别 
   // 参数  : char *szPackDefFile：包格式文件名称
   /* ****** designed by CHENYH at 2004-9-23 23:48:16 ****** 
   包格式文件的格式定义：
      int i1;  本文件生成的机器上整数1的表示值，以免本文件最终使用的机器与生成的机器字序格式的不同导致结构紊乱
      int iMode;
      char version[20];
      int iVersionID;
      int iLastPField;
      ST_PDATALIST pdlist[255];
   */
	int Initialize(const char *szPackDefFile="cpack.dat");

	explicit CXPack(const char *szPackDefFile="cpack.dat");  // 缺省装载"cpack.dat"

	virtual ~CXPack();


   // 函数名: SetPackHead
   // 编程  : 王明松 2005-9-20 10:52:45
   // 描述  : 通过本功能，设置一个XPack包头的主要参数，包括有效字段位图，同时firstflag=1;nextflag=0; 其他被设置为0
   // 返回  : int : 0 
   // 参数  : ST_PACKHEAD *head[OUT]: 被设置的包头
   // 参数  : int recCount[IN]: 记录条数
   // 参数  : int retCode[IN]: 返回码
   // 参数  : ... [IN]: 用F_xxxxx指定有效字段位图(编号)，用END_FIELDMARK(-1)结束
	int SetPackHead(ST_PACKHEAD *head,int recCount,int retCode,...);

};

#undef XPACK_API

#endif // !defined(AFX_XPACK_H__5F12942D_DCBC_4055_A561_7031DBD4BCB8__INCLUDED_)
