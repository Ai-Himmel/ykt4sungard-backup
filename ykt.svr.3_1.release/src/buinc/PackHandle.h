/********************************************************************
	created:	2004/09/23
	created:	23:9:2004   23:25
	filename: 	e:\proj\goldmem\ksbcc\packbase\packhandle.h
	file path:	e:\proj\goldmem\ksbcc\packbase
	file base:	packhandle
	file ext:	h
	author:		陈永华

	purpose:	本数据类型用于CPACK类的基础操作类型，
            注意：iMode=0 为兼容原来的CPACK打包方式
                 否则为新的打包方式
*********************************************************************/
// PackHandle.h: interface for the CPackHandle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKHANDLE_H__5FABD1A8_F02E_485D_9CA8_7825CB168A2C__INCLUDED_)
#define AFX_PACKHANDLE_H__5FABD1A8_F02E_485D_9CA8_7825CB168A2C__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PackB.h"

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


class XPACK_API CPackHandle {
public:
    bool bReverse;                   // 是否在打包中需要反转字节，在打包中按照BigEndian字序（对int/double）
    unsigned char iMode;             // 0: 证券集中交易的编码方式；1: 新的编码方式
    unsigned char iVersionID;        // 打包中用于比较
    char version[20];                // 用于保存版本特征码
    int  iLastPField;                // 最后一个有效字段定义编号
    ST_PDATALIST pdlist[PARMBITS];   // ST_PACK 结构描述表
    int  nPackLength;                // ST_PACK 完整一个记录的长度

public:
    void HostByteOrder(void *data, unsigned int datalength);

    // 函数名: GetPackLength
    // 编程  : 陈永华 2004-10-11 16:58:55
    // 描述  : 取得完整ST_PACK的长度
    // 返回  : int ST_PACK的长度，＝＝ sizeof(ST_PACK)
    int GetPackLength();


    // 函数名: CheckValidField
    // 编程  : 陈永华 2004-10-11 16:59:45
    // 描述  : 在位图表中检查指定的字段编号是否为有效字段
    // 返回  : bool
    // 参数  : const unsigned char *parmbits(IN): 位图表
    // 参数  : int fidx（IN）：指定字段编号
    bool CheckValidField(const unsigned char *parmbits, int fidx);

    // 函数名: GetPackDef
    // 编程  : 陈永华 2004-10-10 22:53:58
    // 描述  : 得到整个完整数据报文结构定义
    // 返回  : const ST_PDATALIST *: 返回报文结构定义数据的位置
    // 参数  : int &ilastvfidx（OUT）：最后一个有效字段/数据列项的编号
    const ST_PDATALIST * GetPackDef(int &ilastvfidx);

    // 函数名: OverwritePack
    // 编程  : 陈永华 2004-10-10 19:12:22
    // 描述  : 将目标报文数据记录中空的数据，用源报文中的有效数据填写（本操作只对单记录有效）
    //          如果目标报文中含有有效的数据，则不用源报文覆盖
    // 返回  : void
    // 参数  : unsigned char *dparmbits（OUT）：目标报文的位图表
    // 参数  : void *dpack（OUT）：目标报文记录
    // 参数  : const unsigned char *sparmbits（IN）：源报文的位图表
    // 参数  : const void *spack（IN）：源报文记录
    void OverwritePack(unsigned char *dparmbits, void *dpack,const unsigned char *sparmbits,const void *spack);

    // 函数名: GetValidFieldCount
    // 编程  : 陈永华 2004-10-9 17:47:56
    // 描述  : 根据位图表，得到有效数据列数/字段数
    // 返回  : int 有效数据列数
    // 参数  : const unsigned char *parmbits：检查的位图表
    int GetValidFieldCount(const unsigned char *parmbits);

    // 函数名: GetValidFieldInfo
    // 编程  : 陈永华 2004-10-9 17:45:04
    // 描述  : 根据当前位图得到有效的vfnumber字段的定义信息
    // 返回  : const ST_PDATALIST *：返回有效字段的定义信息； NULL - 失败，超出有效字段个数；
    // 参数  : const unsigned char *parmbits ：位图表
    // 参数  : int vfnumber： 从0开始的字段有效列号
    const ST_PDATALIST * GetValidFieldInfo(const unsigned char *parmbits,int vfnumber);

    // 函数名: ResetParmBits
    // 编程  : 陈永华 2004-9-30 18:23:08
    // 描述  : 重置指定的位图表，完全清空整个位图
    // 返回  : void
    // 参数  : unsigned char *parmbits(OUT): 需要被清空的位图表
    void ResetParmBits(unsigned char *parmbits);

    // 函数名: xmk_crc16
    // 编程  : 陈永华 2004-10-6 23:46:39
    // 描述  : 统计一个内存块的crc16值，专门用于复核数据的完整性
    // 返回  : unsigned short: 计算所得的crc16
    // 参数  : void *ptr: 一个内存块
    // 参数  : int count: 内存块的字节数
    static unsigned short xmk_crc16(const void *ptr, int count);

    // 函数名: SetPBIndex
    // 编程  : 陈永华 2004-10-6 23:09:42
    // 描述  : 根据字段序号，设置或清除数据报文位图中相应的字段位图
    // 返回  : int － 成功，则返回>=0的fidx（字段序号）；失败，则返回<0
    // 参数  : unsigned char *parmbits(OUT): 被修改的位图表
    // 参数  : int fidx（IN）：设置或清除的字段序号
    // 参数  : bool bToSet（IN）：true－设置；false－清除
    int SetPBIndex(unsigned char *parmbits,int fidx,bool bToSet=true);


    // 函数名: GetPrintFieldValue
    // 编程  : 陈永华 2004-9-30 20:20:58
    // 描述  : 从数据记录prec中，输出指定字段pfd的值，以显示跟踪格式返回
    // 返回  : char * 返回格式化的字段值，==NULL:非法字段
    //          对于PDL_UCHAR类数据字段，则以0xXX..XX的字符类型返回
    // 参数  : void *prec（IN）：数据记录
    // 参数  : int fidx（IN）：字段编号
    // 参数  : char *pfv（OUT）：输出缓冲区
    //             由于字段定义长度不超过256，因此注意为了安全，本参数的长度应该大于等于256字节
    // 参数  : int prec(IN): 对于PDL_DOUBLE有效，用于定义返回的小数点位数；
    //          -1: 则以%lf返回
    char * GetPrintFieldValue(const void *prec, int fidx, char *pfv, int precision=-1);

    // 函数名: GetFieldValueD
    // 编程  : 陈永华 2004-9-30 20:03:49
    // 描述  : 从数据记录中，读取字段名为fieldname的值（用double方式返回）
    // 返回  : double 返回字段的double值
    // 参数  : void *prec（IN）：数据记录
    // 参数  : char *fieldname（IN）：字段名称
    double GetFieldValueD(const void *prec, const char *fieldname);

    // 函数名: GetFieldValueI
    // 编程  : 陈永华 2004-9-30 20:02:56
    // 描述  : 从数据记录中，读取字段名为fieldname的值（用int方式返回）
    // 返回  : int 返回字段的整数值
    // 参数  : void *prec（IN）：数据记录
    // 参数  : char *fieldname（IN）：字段名称
    int GetFieldValueI(const void *prec, const char *fieldname);

    // 函数名: GetFieldValue
    // 编程  : 陈永华 2004-9-30 20:01:12
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
    // 参数  : char *value（OUT）：返回的字段值（用字符串方式表示）如果为PDL_UCHAR，则为该BIN字段的整个值，应该以BIN分解数据
    //             由于字段定义长度不超过256，因此注意为了安全，本参数的长度应该大于等于256字节
    int GetFieldValue(const void *prec, const char *fieldname, char *value);

    // 函数名: GetFieldValueD
    // 编程  : 陈永华 2004-9-30 20:00:26
    // 描述  : 从数据记录中，读取字段编号为fidx的值（用double方式返回）
    // 返回  : double 返回字段的double值
    // 参数  : void *prec（IN）：数据记录
    // 参数  : int fidx（IN）：字段编号
    double GetFieldValueD(const void *prec, int fidx);

    // 函数名: GetFieldValueI
    // 编程  : 陈永华 2004-9-30 19:59:19
    // 描述  : 从数据记录中，读取字段编号为fidx的值（用int方式返回）
    // 返回  : int 返回字段的整数值
    // 参数  : void *prec（IN）：数据记录
    // 参数  : int fidx（IN）：字段编号
    int GetFieldValueI(const void *prec, int fidx);

    // 函数名: GetFieldValue
    // 编程  : 陈永华 2004-9-30 19:45:03
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
    // 参数  : char *value（OUT）：返回的字段值（用字符串方式表示）如果为PDL_UCHAR，则为该BIN字段的整个值，应该以BIN分解数据
    //             由于字段定义长度不超过256，因此注意为了安全，本参数的长度应该大于等于256字节
    int GetFieldValue(const void *prec, int fidx, char *value);

    // 函数名: AddField
    // 编程  : 陈永华 2004-9-30 18:03:15
    // 描述  : 对记录prec中的名为fieldname的字段赋值，如果位图表parmbits!=NULL，则同时设置相应的位图
    // 返回  : bool 赋值成功与否
    // 参数  : void *prec (OUT): 数据记录
    // 参数  : char *fieldname(IN): 字段名称
    // 参数  : double dvalue(IN): 字段的值
    // 参数  : unsigned char *parmbits(OUT): 记录的位图表，
    //          如果不为NULL，则对此表的位图作相应的设置
    //          否则，仅作赋值处理
    bool AddField(void *prec, const char *fieldname, double dvalue, unsigned char *parmbits=NULL);
    // 函数名: AddField
    // 编程  : 陈永华 2004-9-30 18:07:30
    // 描述  : 对记录prec中的名为fieldname的字段赋值，如果位图表parmbits!=NULL，则同时设置相应的位图
    // 返回  : bool 赋值成功与否
    // 参数  : void *prec (OUT): 数据记录
    // 参数  : char *fieldname(IN): 字段名称
    // 参数  : int ivalue(IN): 字段的值
    // 参数  : unsigned char *parmbits(OUT): 记录的位图表，
    //          如果不为NULL，则对此表的位图作相应的设置
    //          否则，仅作赋值处理
    bool AddField(void *prec, const char *fieldname, int ivalue, unsigned char *parmbits=NULL);
    // 函数名: AddField
    // 编程  : 陈永华 2004-9-30 18:08:26
    // 描述  : 对记录prec中的名为fieldname的字段赋值，如果位图表parmbits!=NULL，则同时设置相应的位图
    // 返回  : bool 赋值成功与否
    // 参数  : void *prec (OUT): 数据记录
    // 参数  : char *fieldname(IN): 字段名称
    // 参数  : char *data(IN): 字段的值，当字段为PDL_UCHAR类型，可以为0x????或用其他的，但是建议采用0x?????
    // 参数  : unsigned char *parmbits(OUT): 记录的位图表，
    //          如果不为NULL，则对此表的位图作相应的设置
    //          否则，仅作赋值处理
    bool AddField(void *prec, const char *fieldname, const char *data, unsigned char *parmbits=NULL);


    // 函数名: AddField
    // 编程  : 陈永华 2004-9-30 18:09:32
    // 描述  : 对记录prec中的编号为fidx的字段赋值，如果位图表parmbits!=NULL，则同时设置相应的位图
    // 返回  : bool 赋值成功与否
    // 参数  : void *prec (OUT): 数据记录
    // 参数  : int fidx(IN): 赋值的字段编号
    // 参数  : double dvalue(IN): 字段的值
    // 参数  : unsigned char *parmbits(OUT): 记录的位图表，
    //          如果不为NULL，则对此表的位图作相应的设置
    //          否则，仅作赋值处理
    bool AddField(void *prec, int fidx, double dvalue, unsigned char *parmbits=NULL);
    // 函数名: AddField
    // 编程  : 陈永华 2004-9-30 18:11:45
    // 描述  : 对记录prec中的编号为fidx的字段赋值，如果位图表parmbits!=NULL，则同时设置相应的位图
    // 返回  : bool 赋值成功与否
    // 参数  : void *prec (OUT): 数据记录
    // 参数  : int fidx(IN): 赋值的字段编号
    // 参数  : int ivalue(IN): 字段的值
    // 参数  : unsigned char *parmbits(OUT): 记录的位图表，
    //          如果不为NULL，则对此表的位图作相应的设置
    //          否则，仅作赋值处理
    bool AddField(void *prec, int fidx, int ivalue, unsigned char *parmbits=NULL);
    // 函数名: AddField
    // 编程  : 陈永华 2004-9-30 18:12:29
    // 描述  : 对记录prec中的编号为fidx的字段赋值，如果位图表parmbits!=NULL，则同时设置相应的位图
    // 返回  : bool 赋值成功与否
    // 参数  : void *prec (OUT): 数据记录
    // 参数  : int fidx(IN): 赋值的字段编号
    // 参数  : char *data(IN): 字段的值，当字段为PDL_UCHAR类型，可以为0x????或用其他的，但是建议采用0x?????
    // 参数  : unsigned char *parmbits(OUT): 记录的位图表，
    //          如果不为NULL，则对此表的位图作相应的设置
    //          否则，仅作赋值处理
    bool AddField(void *prec, int fidx, const char *data, unsigned char *parmbits=NULL);


    // 函数名: EmulateEncodeLength
    // 编程  : 陈永华 2004-9-30 18:13:31
    // 描述  : 根据已经设置的位图表，估算一条记录最大占用的编码缓冲区的长度
    // 返回  : int ：返回编码需要最大的缓冲区长度
    // 参数  : unsigned char *parmbits（IN）：已经设置的数据记录位图表
    int EmulateEncodeLength(const unsigned char *parmbits);


    // 函数名: ClearParmBitByFIndex
    // 编程  : 陈永华 2004-9-30 18:16:02
    // 描述  : 对用编号fidx指定的字段的相应位图进行清除
    // 返回  : int <0: 失败，非法字段位图编码；>=0: 成功，即为该字段编号
    // 参数  : unsigned char *parmbits（IN/OUT）：位图表
    // 参数  : int fidx（IN）： 字段编号
    int ClearParmBitByFIndex(unsigned char *parmbits, int fidx);
    // 函数名: ClearParmBit
    // 编程  : 陈永华 2004-9-30 18:18:33
    // 描述  : 对用位图编码表示的字段的相应位图进行清除
    // 返回  : int <0: 失败，非法字段位图编码；>=0: 成功，即为该字段编号
    // 参数  : unsigned char parmbits（IN/OUT）：位图表
    // 参数  : int fpb（IN）： 字段位图编码
    int ClearParmBit(unsigned char *parmbits, int fpb);


    // 函数名: SetParmBitByFIndex
    // 编程  : 陈永华 2004-9-30 18:15:44
    // 描述  : 对用编号fidx指定的字段的相应位图进行设置
    // 返回  : int <0: 失败，非法字段位图编码；>=0: 成功，即为该字段编号
    // 参数  : unsigned char *parmbits（IN/OUT）：位图表
    // 参数  : int fidx（IN）： 字段编号
    int SetParmBitByFIndex(unsigned char *parmbits,int fidx);
    // 函数名: SetParmBit
    // 编程  : 陈永华 2004-9-30 18:22:17
    // 描述  : 对用位图编码表示的字段的相应位图进行设置
    // 返回  : int <0: 失败，非法字段位图编码；>=0: 成功，即为该字段编号
    // 参数  : unsigned char *parmbits（IN/OUT）：位图表
    // 参数  : int fpb（IN）： 字段位图编码
    int SetParmBit(unsigned char *parmbits,int fparmbit);



    // 函数名: FindFieldIndex
    // 编程  : 陈永华 2004-9-30 18:24:18
    // 描述  : 查找字段名为fieldname的字段编号
    // 返回  : int >=0: 成功，返回该字段编号；<0: 在定义表中没有该名称的字段
    // 参数  : char *fieldname（IN）：字段名称
    int FindFieldIndex(const char *fieldname);


    // 函数名: DecodeRow
    // 编程  : 陈永华 2004-9-30 18:25:48
    // 描述  : 根据位图表parmbits将编码缓冲区ebuf进行解码，解码到的数据记录prec中
    // 返回  : int
    /*
          >=0:成功，返回编码占用的长度；
          <0:解码失败
             -1: 编码位图有误(有未定义的位图设置);
             -2: 编码中字段数据超出定义;
             -10: 缓冲区长度不足
    */
    // 参数  : unsigned char *parmbits(IN): 解码的位图表
    // 参数  : void *ebuf（IN）：编码缓冲区
    // 参数  : int eblen（IN）：编码缓冲区的长度
    // 参数  : void *prec（OUT）：用于存放解码的数据记录
    int DecodeRow(const unsigned char *parmbits, const void *ebuf, int eblen, void *prec);

    // 函数名: EncodeRow
    // 编程  : 陈永华 2004-9-30 18:27:08
    // 描述  : 根据位图表parmbits对数据记录prec进行编码，编码结构存放到编码缓冲区ebuf
    // 返回  : int
    /*
          >=0:成功，返回编码占用的长度；
          <0:编码失败
             -1: 编码位图有误(有未定义的位图设置);
             -10: 缓冲区长度不足
    */
    // 参数  : unsigned char *parmbits(IN): 解码的位图表
    // 参数  : void *prec（IN）：被编码的数据记录
    // 参数  : void *ebuf（OUT）：用于存放编码结果的缓冲区
    // 参数  : int ebsize（IN）：编码缓冲区的最大长度
    int EncodeRow(const unsigned char *parmbits, const void *prec, void *ebuf,int ebsize);


    // 函数名: DecodeHead
    // 编程  : 陈永华 2004-9-24 16:32:51
    // 描述  : 将编码缓冲区中解码到包头中
    // 返回  : int >0:解码成功，返回编码长度 ；<0 - 缓冲区长度太小
    // 参数  : void *buf [IN] : 编码缓冲区
    // 参数  : int blen [IN] : 编码缓冲区长度
    // 参数  : ST_PACKHEAD *pHead [OUT]: 包头指针
    int DecodeHead(const void *buf, int blen, ST_PACKHEAD *pHead);
    // 函数名: EncodeHead
    // 编程  : 陈永华 2004-9-24 16:30:57
    // 描述  : 将包头数据编码到指定的缓冲区
    // 返回  : int >0:编码成功，返回编码后使用编码缓冲区的长度
    // 参数  : ST_PACKHEAD *pHead 〔IN〕 包头数据
    // 参数  : void *buf 〔OUT〕存放编码的缓冲区
    int EncodeHead(const ST_PACKHEAD *pHead, void *buf);


    // 函数名: P_Index
    // 编程  : 陈永华 2004-9-30 18:43:59
    // 描述  : 字段位图编码转换为字段编号
    // 返回  : int >=0：合法的字段，返回字段编号；<0:非法的字段位图编码
    // 参数  : int parmbit：字段位图编码
    int P_Index(int parmbit);

    // 函数名: Initialize
    // 编程  : 陈永华 2004-9-30 18:39:25
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
    int Initialize(const char *szPackDefFile="pack.dat");

    CPackHandle();
    virtual ~CPackHandle();

    static void rev_data(void *data,unsigned int datalen);
    static void Hex2Buffer(unsigned char *buf,int len,char *hex);
    static char * LRTrim(char *str);

private:

    // 函数名: GetPrintFieldValue
    // 编程  : 陈永华 2004-9-30 20:18:02
    // 描述  : 从数据记录prec中，输出指定字段pfd的值，以显示跟踪格式返回
    // 返回  : char * 返回格式化的字段值，==NULL:非法字段
    //          对于PDL_UCHAR类数据字段，则以0xXX..XX的字符类型返回
    // 参数  : void *prec（IN）：数据记录
    // 参数  : ST_PDATALIST *pfd（IN）：指定的字段定义
    // 参数  : char *pfv（OUT）：输出缓冲区
    // 参数  : int precision(IN): 对于PDL_DOUBLE有效，用于定义返回的小数点位数；
    //          -1: 则以%lf返回
    char * GetPrintFieldValue(const void *prec, const ST_PDATALIST *pfd, char *pfv,int precision);
    int GetFieldValue(const void *prec, const ST_PDATALIST *pfd, char *value);
    bool SetFieldValue(void *prec, int fidx, char *data);

    bool SetFieldValue(void *prec, const ST_PDATALIST *pfd, double dvalue);
    bool SetFieldValue(void *prec, const ST_PDATALIST *pfd, int ivalue);
    bool SetFieldValue(void *prec, const ST_PDATALIST *pfd, char *data);

    int GetEncodeFieldLength(const ST_PDATALIST *pfd);
    int DecodeSingleField(const ST_PDATALIST *pfd, const void *pbuf, void *pdata);
    int EncodeSingleField(const ST_PDATALIST *pfd, const void *pdata, void *pbuf);
};

#undef XPACK_API

#endif // !defined(AFX_PACKHANDLE_H__5FABD1A8_F02E_485D_9CA8_7825CB168A2C__INCLUDED_)
