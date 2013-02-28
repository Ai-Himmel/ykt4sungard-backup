using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace SunGard.SmartCard.KSLibInteropServices
{
    public class BCCHelper
    {
        // 函数名: BCCCLTInit
        // 编程  : 陈永华 2005-11-15 11:22:35
        // 描述  : 初试化本系统将直接连接多少个业务通讯平台节点个数
        //		Notice: 系统只能调用一次
        // 返回  : bool 
        // 参数  : int maxnodes=1 [IN]: 设置最多会有多少个连接节点
        //BCCCLT_API  bool BCCCLTInit(int maxnodes);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "BCCCLTInit", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool BCCCLTInit(int maxnodes);

        // 函数名: XPackInit
        // 编程  : 陈永华 2005-11-15 11:18:52
        // 描述  : 预先设置本系统一共将有多少个XpackDescribleFile文件，相同的即使有多个XPack数据区句柄，仍然算一个
        //		Notice: 一个系统只能调用设置一次
        // 返回  : bool 
        // 参数  : int maxXPackDefs [IN]: 设置的XpackDescribleFile文件数，参考NewXpackHandle()方法
        //BCCCLT_API  bool XPackInit(int maxXPackDefs);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "XPackInit", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool XPackInit(int maxXPackDefs);

        // 函数名: NewXpackHandle
        // 编程  : 陈永华 2005-11-14 17:57:39
        // 描述  : 构件一个用于XPack数据交换的数据区
        // 返回  : XDHANDLE : 返回该XPack数据区的句柄；==0(NULL): 失败
        // 参数  : const char * XpackDescribleFile [IN]: XPack结构定义文件名，不能超过1024字节长，如: "/xpacks/cpack.dat"
        //BCCCLT_API  XDHANDLE NewXpackHandle(const char * XpackDescribleFile);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "NewXpackHandle", CallingConvention = CallingConvention.Cdecl)]
        public static extern int NewXpackHandle(string XpackDescribleFile);

        // 函数名: ResetPackHandle
        // 编程  : 陈永华 2005-11-14 18:01:30
        // 描述  : 重置数据区内容，主要用于准备首包请求时，填写具体请求数据字段之前调用
        // 返回  : bool : false - 往往为错误的Handle(==NULL的时候)
        // 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
        //BCCCLT_API  bool ResetPackHandle(XDHANDLE Handle);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "ResetPackHandle", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ResetPackHandle(int Handle);

        // 函数名: CopyHandle
        // 编程  : 陈永华 2005-11-14 18:04:56
        // 描述  : 将SourceHandle中的状态、格式、数据等信息复制到DestHandle中
        // 返回  : bool : false - 往往为错误的Handle(==NULL的时候)
        // 参数  : XDHANDLE SourceHandle [IN]: 被复制的原XPack数据区句柄
        // 参数  : XDHANDLE DestHandle   [OUT]: 被复制的目标XPack数据区句柄，内部数据被覆盖，但不会新派生一个句柄
        //BCCCLT_API  bool CopyHandle(XDHANDLE SourceHandle,XDHANDLE DestHandle);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "CopyHandle", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool CopyHandle(int SourceHandle, int DestHandle);

        // 函数名: DeleteXpackHandle
        // 编程  : 陈永华 2005-11-14 18:08:08
        // 描述  : 将已经用NewXpackHandle得到的数据区释放(卸构)
        // 返回  : bool 
        // 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
        //BCCCLT_API  bool DeleteXpackHandle(XDHANDLE Handle);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "DeleteXpackHandle", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool DeleteXpackHandle(int Handle);



        // 函数名: IsEof
        // 编程  : 陈永华 2005-11-14 18:10:17
        // 描述  : 是否已经是最后一个应答包了，和HaveNextPack正好相反
        // 返回  : bool : true - 表示已经没有后续应答数据包了；false - 要通过调用EncodeXpackForNext后续包
        // 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
        //BCCCLT_API  bool IsEof(XDHANDLE Handle);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "IsEof", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool IsEof(int Handle);


        // 函数名: SetDebugSwitch
        // 编程  : 陈永华 2006-8-24 10:26:51
        // 描述  : 设置是否打开调试跟踪文件
        // 返回  : void 
        // 参数  : bool bDebug [IN]: 0(false) - off; 1(true) - on
        //BCCCLT_API  void SetDebugSwitch(bool bDebug);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "SetDebugSwitch", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetDebugSwitch(bool bDebug);

        // 函数名: AddDrtpNode
        // 编程  : 陈永华 2005-11-15 11:24:25
        // 描述  : 增加一个要直接连接的业务通讯平台节点
        //       作为系统初试化部分，建议在调用BCCCLTInit后，在统一一个线程里一次性的设置完毕，供整个环境使用
        // 返回  : int  增加的业务通讯平台节点编号 >=0:成功；否则，可能没有正确调用BCCCLTInit()
        // 参数  : char * ip [IN]: 该业务通讯平台的IP地址
        // 参数  : int port [IN]: 该业务通讯平台提供的端口号port
        //BCCCLT_API  int AddDrtpNode(char * ip,int port);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "AddDrtpNode", CallingConvention = CallingConvention.Cdecl)]
        public static extern int AddDrtpNode(string ip, int port);


        // 函数名: SetRequestType
        // 编程  : 陈永华 2005-11-14 18:10:12
        // 描述  : 设置请求数据中的功能号 （在EncodeXpackForRequest之前一定要设置）
        // 返回  : bool 
        // 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
        // 参数  : int RequestType [IN]: 对应的业务功能号
        //BCCCLT_API  bool SetRequestType(XDHANDLE Handle,int RequestType);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "SetRequestType", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool SetRequestType(int Handle, int RequestType);

        // 函数名: CallRequest
        // 编程  : 陈永华 2005-11-15 11:27:07
        // 描述  : 将前面设置好XPack请求数据打包发送给指定的通讯平台和应用服务器
        // 返回  : bool : true 成功发送，并且接收解码了应答数据；false 操作失败，具体错误，参见错误码
        // 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
        // 参数  : int drtpno [IN]: 从那个直联的业务通讯平台节点发送和接收数据，参见AddDrtpNode()的返回值
        // 参数  : int branchno [IN]: 目标应用服务器连接的业务通讯平台节点编号（参见业务通讯平台的配置参数表）
        // 参数  : int function [IN]: 目标应用服务器注册在业务通讯平台的功能号 (参见BCC配置文件中的BASEFUNCNO)
        // 参数  : int timeout [IN]: 发送接收数据的超时时间，以毫秒计
        // 参数  : int* errcode [OUT]: 返回的错误码
        // 参数  : char * errormessage [OUT]: 返回的错误信息
        //BCCCLT_API  bool CallRequest(XDHANDLE Handle, int drtpno, int branchno,int function, int timeout, int *errcode,char * errormessage);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "CallRequest", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool CallRequest(int Handle, int drtpno, int branchno, int function, int timeout, ref  int errcode, StringBuilder errormessage);

        // 函数名: GetRetCode
        // 编程  : 陈永华 2005-11-14 18:10:28
        // 描述  : 解包后读取其返回码
        // 返回  : bool 
        // 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
        // 参数  : int* RetCode [OUT]: 返回收到数据包中的返回码
        //BCCCLT_API  bool GetRetCode(XDHANDLE Handle,int * RetCode);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "GetRetCode", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool GetRetCode(int Handle, ref int RetCode);

        // 函数名: GetRecordCount
        // 编程  : 陈永华 2005-11-14 18:10:22
        // 描述  : 解包后读取本包中的记录数RecordCount
        // 返回  : bool 
        // 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
        // 参数  : int * RecordCount [OUT]: 返回解包后的记录数
        //BCCCLT_API  bool GetRecordCount(XDHANDLE Handle,int * RecordCount);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "GetRecordCount", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool GetRecordCount(int Handle, ref int RecordCount);


        // 函数名: HaveNextPack
        // 编程  : 陈永华 2005-11-14 22:01:15
        // 描述  : 当解码后，通过本函数判断是否还有后续应答包
        // 返回  : bool : true-表示还有后续应答包；false－无后续包
        // 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
        //BCCCLT_API  bool HaveNextPack(XDHANDLE Handle);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "HaveNextPack", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool HaveNextPack(int Handle);


        // 函数名: CallNext
        // 编程  : 陈永华 2005-11-15 11:30:38
        // 描述  : 取下一个后续应答包
        //          在成功调用CallRequest后，如果检查到HaveNextPack()后，则用本功能获取下一个后续应答包
        // 返回  : bool ：true 成功发送，并且接收解码了应答数据；false 操作失败，具体错误，参见错误码
        // 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
        // 参数  : int timeout [IN]: 发送接收数据的超时时间，以毫秒计
        // 参数  : int* errcode [OUT]: 返回的错误码
        // 参数  : char * errormessage [OUT]: 返回的错误信息
        //	BCCCLT_API  bool CallNext(XDHANDLE Handle, int timeout, int* errcode,char * errormessage);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "CallNext", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool CallNext(int Handle, int timeout, ref int errcode, StringBuilder errormessage);


        // 函数名: SetStringFieldByName
        // 编程  : 陈永华 2005-11-14 18:10:07
        // 描述  : 设置指定数据区中第Row条记录中的对应字段的值
        // 返回  : bool 
        // 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
        // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
        // 参数  : char * FieldName [IN]: 字段名称 如"vsmess"
        // 参数  : char * Value [IN]: 数据值，不可以超过255长度
        //BCCCLT_API  bool SetStringFieldByName(XDHANDLE Handle,int Row,char * FieldName,char * Value);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "SetStringFieldByName", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool SetStringFieldByName(int Handle, int Row, string FieldName, string Value);

        // 函数名: GetStringFieldByName
        // 编程  : 陈永华 2005-11-14 18:09:36
        // 描述  : 从数据区读取第Row条记录中的对应字段的值 (double)
        // 返回  : bool 
        // 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
        // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
        // 参数  : char * FieldName [IN]: 字段名称 如"vsmess"
        // 参数  : char * Value [OUT]: 返回得到的值
        // 参数  : int ValueBufferSize [IN]: Value缓存区的长度（即可以存放的最大长度） 一般可以为 <=256
        //BCCCLT_API  bool GetStringFieldByName(XDHANDLE Handle,int Row,char * FieldName,char * Value,int ValueBufferSize);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "GetStringFieldByName", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool GetStringFieldByName(int Handle, int Row, string FieldName, StringBuilder Value, int ValueBufferSize);

        // 函数名: SetIntFieldByName
        // 编程  : 陈永华 2005-11-14 18:09:57
        // 描述  : 设置指定数据区中第Row条记录中的对应字段的值
        // 返回  : bool 
        // 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
        // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
        // 参数  : char * FieldName [IN]: 字段名称 如"vsmess"
        // 参数  : int Value [IN]: 数据值
        //BCCCLT_API  bool SetIntFieldByName(XDHANDLE Handle,int Row,char * FieldName,int Value);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "SetIntFieldByName", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool SetIntFieldByName(int Handle, int Row, string FieldName, int Value);

        // 函数名: GetIntFieldByName
        // 编程  : 陈永华 2005-11-14 18:09:26
        // 描述  : 从数据区读取第Row条记录中的对应字段的值 (int)
        // 返回  : bool 
        // 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
        // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
        // 参数  : char * FieldName [IN]: 字段名称 如"vsmess"
        // 参数  : int* Value [OUT]: 返回得到的值
        //BCCCLT_API  bool GetIntFieldByName(XDHANDLE Handle,int Row,char * FieldName,int * Value);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "GetIntFieldByName", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool GetIntFieldByName(int Handle, int Row, string FieldName, ref int Value);

        // 函数名: SetDoubleFieldByName
        // 编程  : 陈永华 2005-11-14 18:10:02
        // 描述  : 设置指定数据区中第Row条记录中的对应字段的值
        // 返回  : bool 
        // 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
        // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
        // 参数  : char * FieldName [IN]: 字段名称 如"vsmess"
        // 参数  : double Value [IN]: 数据值
        //BCCCLT_API  bool SetDoubleFieldByName(XDHANDLE Handle,int Row,char * FieldName,double Value);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "SetDoubleFieldByName", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool SetDoubleFieldByName(int Handle, int Row, string FieldName, double Value);

        // 函数名: GetDoubleFieldByName
        // 编程  : 陈永华 2005-11-14 18:09:31
        // 描述  : 从数据区读取第Row条记录中的对应字段的值 (double)
        // 返回  : bool 
        // 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
        // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
        // 参数  : char * FieldName [IN]: 字段名称 如"vsmess"
        // 参数  : double* Value [OUT]: 返回得到的值
        //BCCCLT_API  bool GetDoubleFieldByName(XDHANDLE Handle,int Row,char * FieldName,double * Value);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "GetDoubleFieldByName", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool GetDoubleFieldByName(int Handle, int Row, string FieldName, ref double Value);

        // 函数名: GetFieldTypeByName
        // 编程  : 陈永华 2005-11-14 18:08:37
        // 描述  : 取得对应字段的类型(与NewXpackHandle中输入的结构定义文件相关)
        // 返回  : int  : 0 - 空字段; 1-char; 2-vs_char; 3-unsigned char; 4-int; 5-double 
        //                -1 字段索引不存在或Handle错误
        // 参数  : XDHANDLE Handle [IN]: 指定的XPack数据区句柄
        // 参数  : char * FieldName [IN]: 指定的字段名称,如"vsmess"
        //BCCCLT_API  int GetFieldTypeByName(XDHANDLE Handle,char * FieldName);
        [DllImport(@"KSLib\bccclt.dll", EntryPoint = "GetFieldTypeByName", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetFieldTypeByName(int Handle, string FieldName);



        //wrapped functions
        public static string  GetStringFieldByName(int Handle, int Row, string FieldName)
        {
            bool retVal = false;
            StringBuilder sb = new StringBuilder(256);
            retVal = GetStringFieldByName(Handle, Row, FieldName, sb, 256);
            return retVal ? sb.ToString() : string.Empty;

           

        }


    }
}
