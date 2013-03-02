/********************************************************************
	created:	2006/07/12
	created:	12:7:2006   10:59
	filename: 	D:\proj\ksbass\bcclink\bccsvr\bccsvr.h
	file path:	D:\proj\ksbass\bcclink\bccsvr
	file base:	bccsvr
	file ext:	h
	author:		CHENYH
	
	purpose: 为了给C/C++提供与JAVA类似的接口	
*********************************************************************/
#ifndef BCCSVR_H
#define BCCSVR_H


#ifdef BCCSVR_EXPORTS
#include "XPData.h"
#define BCCSVR_API __declspec(dllexport)
#else
typedef void * XDHANDLE;
#ifdef _WINDOWS
#define BCCSVR_API __declspec(dllimport)
#else
#define BCCSVR_API 
#endif
#endif

#ifdef __cplusplus
extern "C" {
#else
   typedef unsigned char bool;
/* ****** Updated by CHENYH at 2006-7-12 11:04:58 ****** 
   #define true 1
   #define false 0
*******************************************************/
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
/// 下列函数与具体的数据无关，只是用于初试化XPACK，或对XPACK结构信息读取

// 描述  : 构件一个用于XPack数据交换的数据区
// 返回  : XDHANDLE : 返回该XPack数据区的句柄；==NULL: 失败
// 参数  : const char *XpackDescribleFile [IN]: XPack结构定义文件名，不能超过1024字节长，如: "/xpacks/cpack.dat"
BCCSVR_API XDHANDLE NewXpackHandle(const char * XpackDescribleFile);

// 描述  : 将已经用NewXpackHandle得到的数据区释放(卸构)
// 返回  : bool 
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
BCCSVR_API bool DeleteXpackHandle(XDHANDLE Handle);

// 描述  : 获取本格式的XPack中最大的有效字段索引值，与当时数据块不同
// 返回  : int 返回ST_PACK中的最大有效字段索引值
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
BCCSVR_API int GetMaxColumn(XDHANDLE Handle);

// 函数名: GetFieldColumn
// 编程  : 陈永华 2005-11-14 21:11:29
// 描述  : 根据字段名称，获得字段索引号
// 返回  : int >=0 为本XPACK中有效字段，返回的值即为索引号；<0为本XPACK中没有这个字段
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
// 参数  : const char *fieldname [IN]: 字段名称 如"vsmess"
BCCSVR_API int GetFieldColumn(XDHANDLE Handle, const char *fieldname);

// 描述  : 读取指定字段的信息
// 返回  : bool : true-为有效字段
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
// 参数  : int Col [IN]: 指定的字段索引号
// 参数  : char *fieldname [OUT]: 返回指定的字段名称
// 参数  : int *fieldtype [OUT]: 指定的字段类型
// 参数  : int *fieldlength [OUT]: 指定的字段长度
BCCSVR_API bool GetFieldInfo(XDHANDLE Handle,int Col, char *fieldname, int *fieldtype, int *fieldlength);

// 描述  : 取得对应字段的类型(与NewXpackHandle中输入的结构定义文件相关)
// 返回  : int  : 0 - 空字段; 1-char; 2-vs_char; 3-unsigned char; 4-int; 5-double 
//                -1 字段索引不存在或Handle错误
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
// 参数  : const char *fieldname [IN]: 指定的字段名称,如"vsmess"
BCCSVR_API int GetFieldTypeByName(XDHANDLE Handle,const char *fieldname);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 下列接口则操作指定句柄缓存区的数据，与具体数据相关

/////////////////////////////////////////////////////////////////////////////
// 取接收到的请求或消息数据内容：

// 描述  : 从数据区读取第Row条记录中的对应字段的值 (int)
// 返回  : bool 
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
// 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
// 参数  : const char *fieldname [IN]: 字段名称 如"vsmess"
// 参数  : long *value [OUT]: 返回得到的值
BCCSVR_API bool GetIntFieldByName(XDHANDLE Handle,int Row,const char *fieldname,long *value);

// 描述  : 从数据区读取第Row条记录中的对应字段的值 (double)
// 返回  : bool 
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
// 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
// 参数  : const char *fieldname [IN]: 字段名称 如"vsmess"
// 参数  : double *value [OUT]: 返回得到的值
BCCSVR_API bool GetDoubleFieldByName(XDHANDLE Handle,int Row,const char *fieldname,double *value);

// 描述  : 从数据区读取第Row条记录中的对应字段的值 (double)
// 返回  : bool 
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
// 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
// 参数  : const char *fieldname [IN]: 字段名称 如"vsmess"
// 参数  : char *value [OUT]: 返回得到的值
// 参数  : int ValueBufferSize [IN]: value缓存区的长度（即可以存放的最大长度） 一般可以为 <=256
BCCSVR_API bool GetStringFieldByName(XDHANDLE Handle,int Row,const char *fieldname,char *value,int ValueBufferSize);

// 函数名: GetRecordCount
// 编程  : 陈永华 2005-11-14 18:10:22
// 描述  : 读取本请求包中的记录数RecordCount
// 返回  : int 返回接收数据的记录数
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
BCCSVR_API int GetRecordCount(XDHANDLE Handle);

// 函数名: GetXPackType
// 编程  : 陈永华 2005-11-14 21:11:05
// 描述  : 查询当前数据块中数据记录类型
// 返回  : int 返回数据记录类型 0-标准ST_PACK记录；1-ST_SDPACK的RawData记录
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
BCCSVR_API int GetXPackType(XDHANDLE Handle); 


// 描述  : 当用GetXPackType返回为1即ST_SDPACK类的记录，则可以用本函数获取各个有效记录中的RawData记录
// 返回  : int : >=0 - 成功返回RawData的数据长度(字节数)
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
// 参数  : int Row [IN]: 指定的记录号 [0..RecordCount-1]
// 参数  : char *RawData [OUT]: 存放读取的RawData数据块，在不定的情况下需分配8K字节的缓存
// 参数  : int RawDataSize [IN]: RawData数据块的可存放的最长长度
BCCSVR_API int GetRawRecord(XDHANDLE Handle, int Row, char *RawData, int RawDataSize);

// 描述  : 取ReceiveMsg后得到数据的请求功能号
// 返回  : int 请求功能号
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
BCCSVR_API int GetRequestType(XDHANDLE Handle);

// 描述  : 取ReceiveMsg后得到数据的RetCode值
// 返回  : int 消息或请求数据中的RetCode值
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
BCCSVR_API int GetRetCode(XDHANDLE Handle);

// 描述  : 取ReceiveMsg后>0的得到数据是从哪个SvrID中取得的
// 返回  : int 消息或请求数据是从哪个SvrID中取得的
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
BCCSVR_API int GetSvrID(XDHANDLE Handle);

// 描述  : 用于0、1类消息，取消息编号，消息编号在XPACK协议中，是用Number*100+Day(两位日期)组成的
// 返回  : int 返回消息编号即XPACK头中的hook.UserID
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
BCCSVR_API int GetMsgID(XDHANDLE Handle);


// 描述  : 用于0、1类消息，取消息的来源ID
// 返回  : int 返回消息来源ID即XPACK头中的hook.queuetype
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
BCCSVR_API int GetMsgSource(XDHANDLE Handle);


// 描述  : 用于0、1类消息，取消息的批次号
// 返回  : int 返回消息批次号即XPACK头中的userdata
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
BCCSVR_API int GetMsgBatchNo(XDHANDLE Handle);
//////////////////////////////////////////////////////////////////////////
// 设置应答记录的内容：
	
// 描述  : 设置指定数据区中第Row条记录中的对应字段的值
// 返回  : bool 
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
// 参数  : const char *fieldname [IN]: 字段名称 如"vsmess"
// 参数  : long value [IN]: 数据值
BCCSVR_API bool SetIntFieldByName(XDHANDLE Handle,const char *fieldname,long value);

// 描述  : 设置指定数据区中第Row条记录中的对应字段的值
// 返回  : bool 
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
// 参数  : const char *fieldname [IN]: 字段名称 如"vsmess"
// 参数  : double value [IN]: 数据值
BCCSVR_API bool SetDoubleFieldByName(XDHANDLE Handle,const char *fieldname,double value);

// 描述  : 设置指定数据区中第Row条记录中的对应字段的值
// 返回  : bool 
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
// 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
// 参数  : const char *fieldname [IN]: 字段名称 如"vsmess"
// 参数  : const char *value [IN]: 数据值，一般不可以超过255长度，除非该字段为binary类型，用0xXXXXXX...表示的数据值
BCCSVR_API bool SetStringFieldByName(XDHANDLE Handle,const char *fieldname,const char *value);

// 函数名: SetAPackMaxRows
// 编程  : 陈永华 2005-11-14 21:11:00
// 描述  : 设置应答包每次返回的最多记录数
// 返回  : bool 
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
// 参数  : int MaxRetCount [IN]: 指定的最多记录数，0则由自动控制 [0..100]; 
BCCSVR_API bool SetAPackMaxRows(XDHANDLE Handle,int MaxRows);

/// 对XPACK中RawData的读写操作：
// 描述  : 设置指定记录为指定的RawData记录
// 返回  : bool 
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
// 参数  : const char *RawData [IN]: 要设置数据块
// 参数  : int RawDataLength [IN]: 要设置数据块长度
BCCSVR_API bool SetRawRecord(XDHANDLE Handle, const char *RawData, int RawDataLength);


///////////////////////////////////////////////////////////////////////////////////////
// 与业务通讯平台相关的函数：

// 描述  : 增加一个通讯服务，包括连接的业务通讯平台节点参数，和为了接收消息或请求需要的通讯功能号，
//          注意：basefno和privfno两者其中至少必须一个是有效的。
// 返回  : int 返回业务通讯平台服务ID号；<0: 失败
// 参数  : const char *ip [IN]: 该业务通讯平台的IP地址
// 参数  : int port [IN]: 该业务通讯平台提供的端口号port
// 参数  : int basefno [IN]: 在业务通讯平台上注册的公共的功能号（没有则，填写0）
// 参数  : int privfno [IN]: 在业务通讯平台上注册的私有的功能号（没有则，填写0）
// 参数  : bool bretry [IN]: 是否当断开连接后，继续retry连接。
//                           true, 则当接收错误连接断开的时候，会重新不停连接，恢复接收，但ReceiveMsg不出现-2信息
//                           false，则当连接断开时候，相关的ReceiveMsg过程中会接收到-2的信息，退出服务。
BCCSVR_API int AddService(int branchno,const char *ip,int port,int basefno, int privfno, bool bretry);

// 描述  : 将XPack数据处理句柄绑定通讯服务ID
// 返回  : int 返回业务通讯平台服务ID号；<0: 失败
// 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
// 参数  : int svrID [IN]: 通讯服务ID，即AddService(...)返回的ID
BCCSVR_API int BindService(XDHANDLE Handle,int svrID);

// 描述  : 作为服务，以被设置的通讯功能号，扫描接收消息或请求数据
// 返回  : int    1－0类通知消息；2－1类通知消息；3－正常客户端请求数据，需要用PutRow/DataDone给出应答
//                0: 一个后续数据返回处理完成，同-1一样继续处理；
//                -1: 表示本次扫描各个Bind的Service都没有收到新的消息或请求（注意这种情况下不要狂扫描，本线程中加入少许等待）
//                -2: 表示绑定的svrID连接出现问题了，errormessage中将会给出具体信息 
//                <-2: 属于错误，参考errormessage信息 -3: 解码错误
// 参数  : XDHANDLE Handle [IN] : 等待接收的XPACK数据缓存句柄
// 参数  : char *errormessage [OUT] : 当返回码为<0的时候的错误信息
// 参数  : int emlen[IN] : errormessage的缓存长度
BCCSVR_API int ReceiveMsg(XDHANDLE Handle,char *errormessage, int emlen);


// 描述  : 将当前缓存中的已经设置的数据(Row=0的)作为一条记录，准备完毕，可以提交给对方
//          注意：在XPACK、CPACK协议中，该记录不会即时发送给对方，除非成为一个完整的包
//             （属于挤压出去的模式），每次都要用PutRow表示一条记录准备完毕，最后，
//             通过调用DataDone，表示本次请求处理结束，没有更多的数据要给请求方。
// 返回  : int : 返回成功>=0 或失败<0
// 参数  : XDHANDLE Handle [IN] : 被操作的XPACK数据缓存句柄
// 参数  : int retCode [IN] : 当前的返回码，一般在XPACK协议中0表示成功
BCCSVR_API int PutRow(XDHANDLE Handle, int retCode);


// 描述  : 本次对请求数据处理结束，不再有信息返回给请求方
// 返回  : int : 返回成功>=0 或失败<0
// 参数  : XDHANDLE Handle [IN] : 被操作的XPACK数据缓存句柄
// 参数  : int retCode [IN] : 当前的返回码，一般在XPACK协议中0表示成功
BCCSVR_API int DataDone(XDHANDLE Handle, int retCode);

// 描述  : 清除此前通过SetXXXXFieldByName或SetRawData的数据，或更改返回记录的内容的字段项
//          这个时候就会将前面的结果提交给请求方的。
// 返回  : int >=0: 成功；<0: 失败 
// 参数  : XDHANDLE Handle [IN] : 被操作的XPACK数据缓存句柄
BCCSVR_API int ClearRow(XDHANDLE Handle);
////////////////////////////////////////////////////////////////////////////////
// 公共函数

// 描述  : 将信息记录到KLG文件中（只有用KLGOpen成功后有效）
// 返回  : void 
// 参数  : char *fmt ：信息的格式化串
// 参数  : ... ：信息的数量参数，类似sprintf中的参数输入方式
BCCSVR_API void KLGMsg(char *fmt,...);

// 描述  : 打开KLG文件记录模式，注意只可以调用一次，并且往往在初试化的时候
// 返回  : bool ：返回是否成功打开
// 参数  : char *path ：KLG存放的路径
BCCSVR_API bool KLGOpen(char *path);

// 描述  : 记录XPACK数据包的数据到KLG文件中（只有用KLGOpen成功后有效）
// 返回  : bool ：返回是否成功
// 参数  : void *pBuf ：XPACK的数据块
// 参数  : int nBufLen：XPACK数据块的长度
// 参数  : const char *pszPackHint：数据块的标注信息，有限长度
BCCSVR_API bool KLGWritePack(void *pBuf, int nBufLen,const char *pszPackHint);


// 描述  : 删除过期文件
// 返回  : int 返回被删除文件的个数
// 参数  : char *path_mark ：删除的文件路径，不包括文件本身
// 参数  : char *ext ：删除的文件扩展名，包括.xxx
// 参数  : int overdue : 过期的自然天数
BCCSVR_API int RemoveOverdueFile(const char *path_mark,char *ext,int overdue);


#ifdef __cplusplus
}
#endif

#undef BCCSVR_API

#endif