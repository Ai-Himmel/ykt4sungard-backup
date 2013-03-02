

public class xpacklib
{

   // 函数名: NewXpackHandle
   // 编程  : 陈永华 2005-11-14 17:57:39
   // 描述  : 构件一个用于XPack数据交换的数据区
   // 返回  : long : 返回该XPack数据区的句柄；==0(NULL): 失败
   // 参数  : byte[] XpackDescribleFile [IN]: XPack结构定义文件名，不能超过1024字节长，如: "/xpacks/cpack.dat"
	public native long NewXpackHandle(byte[] XpackDescribleFile);

   // 函数名: ResetPackHandle
   // 编程  : 陈永华 2005-11-14 18:01:30
   // 描述  : 重置数据区内容，主要用于准备首包请求时，填写具体请求数据字段之前调用
   // 返回  : boolean : false - 往往为错误的Handle(==NULL的时候)
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
	public native boolean ResetPackHandle(long Handle);

   // 函数名: CopyHandle
   // 编程  : 陈永华 2005-11-14 18:04:56
   // 描述  : 将SourceHandle中的状态、格式、数据等信息复制到DestHandle中
   // 返回  : boolean : false - 往往为错误的Handle(==NULL的时候)
   // 参数  : long SourceHandle [IN]: 被复制的原XPack数据区句柄
   // 参数  : long DestHandle   [OUT]: 被复制的目标XPack数据区句柄，内部数据被覆盖，但不会新派生一个句柄
	public native boolean CopyHandle(long SourceHandle,long DestHandle);

   // 函数名: DeleteXpackHandle
   // 编程  : 陈永华 2005-11-14 18:08:08
   // 描述  : 将已经用NewXpackHandle得到的数据区释放(卸构)
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
	public native boolean DeleteXpackHandle(long Handle);

   // 函数名: GetFieldTypeByCol
   // 编程  : 陈永华 2005-11-14 18:08:31
   // 描述  : 取得对应字段索引号的类型(与NewXpackHandle中输入的结构定义文件相关)
   // 返回  : int  : 0 - 空字段; 1-char; 2-vs_char; 3-unsigned char; 4-int; 5-double 
   //                -1 字段索引不存在或Handle错误
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Col [IN]: 字段索引号
	public native int GetFieldTypeByCol(long Handle,int Col);

   // 函数名: GetFieldTypeByName
   // 编程  : 陈永华 2005-11-14 18:08:37
   // 描述  : 取得对应字段的类型(与NewXpackHandle中输入的结构定义文件相关)
   // 返回  : int  : 0 - 空字段; 1-char; 2-vs_char; 3-unsigned char; 4-int; 5-double 
   //                -1 字段索引不存在或Handle错误
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : byte[] FieldName [IN]: 指定的字段名称,如"vsmess"
	public native int GetFieldTypeByName(long Handle,byte[] FieldName);


   // 函数名: GetIntFieldByCol
   // 编程  : 陈永华 2005-11-14 18:08:45
   // 描述  : 从数据区读取第Row条记录中的对应字段的值 (int)
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : int Col [IN]: 字段索引号
   // 参数  : int[] Value [OUT]: 返回得到的值
	public native boolean GetIntFieldByCol(long Handle,int Row,int Col,int[] Value);

   // 函数名: GetDoubleFieldByCol
   // 编程  : 陈永华 2005-11-14 18:09:14
   // 描述  : 从数据区读取第Row条记录中的对应字段的值 (double)
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : int Col [IN]: 字段索引号
   // 参数  : double[] Value [OUT]: 返回得到的值
	public native boolean GetDoubleFieldByCol(long Handle,int Row,int Col,double[] Value);

   // 函数名: GetStringFieldByCol
   // 编程  : 陈永华 2005-11-14 18:09:20
   // 描述  : 从数据区读取第Row条记录中的对应字段的值 (C中表示的单字节字符串)
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : int Col [IN]: 字段索引号
   // 参数  : byte[] Value [OUT]: 返回得到的值
   // 参数  : int ValueBufferSize [IN]: Value缓存区的长度（即可以存放的最大长度） 一般可以为 <=256
	public native boolean GetStringFieldByCol(long Handle,int Row,int Col,byte[] Value,int ValueBufferSize);
	

   // 函数名: GetIntFieldByName
   // 编程  : 陈永华 2005-11-14 18:09:26
   // 描述  : 从数据区读取第Row条记录中的对应字段的值 (int)
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : byte[] FieldName [IN]: 字段名称 如"vsmess"
   // 参数  : int[] Value [OUT]: 返回得到的值
	public native boolean GetIntFieldByName(long Handle,int Row,byte[] FieldName,int[] Value);

   // 函数名: GetDoubleFieldByName
   // 编程  : 陈永华 2005-11-14 18:09:31
   // 描述  : 从数据区读取第Row条记录中的对应字段的值 (double)
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : byte[] FieldName [IN]: 字段名称 如"vsmess"
   // 参数  : double[] Value [OUT]: 返回得到的值
	public native boolean GetDoubleFieldByName(long Handle,int Row,byte[] FieldName,double[] Value);

   // 函数名: GetStringFieldByName
   // 编程  : 陈永华 2005-11-14 18:09:36
   // 描述  : 从数据区读取第Row条记录中的对应字段的值 (double)
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : byte[] FieldName [IN]: 字段名称 如"vsmess"
   // 参数  : byte[] Value [OUT]: 返回得到的值
   // 参数  : int ValueBufferSize [IN]: Value缓存区的长度（即可以存放的最大长度） 一般可以为 <=256
	public native boolean GetStringFieldByName(long Handle,int Row,byte[] FieldName,byte[] Value,int ValueBufferSize);
	

   // 函数名: SetIntFieldByCol
   // 编程  : 陈永华 2005-11-14 18:09:41
   // 描述  : 设置指定数据区中第Row条记录中的对应字段的值
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : int Col [IN]: 字段索引号
   // 参数  : int Value [IN]: 数据值
	public native boolean SetIntFieldByCol(long Handle,int Row,int Col,int Value);

   // 函数名: SetDoubleFieldByCol
   // 编程  : 陈永华 2005-11-14 18:09:47
   // 描述  : 设置指定数据区中第Row条记录中的对应字段的值
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : int Col [IN]: 字段索引号
   // 参数  : double Value [IN]: 数据值
	public native boolean SetDoubleFieldByCol(long Handle,int Row,int Col,double Value);

   // 函数名: SetStringFieldByCol
   // 编程  : 陈永华 2005-11-14 18:09:52
   // 描述  : 设置指定数据区中第Row条记录中的对应字段的值
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : int Col [IN]: 字段索引号
   // 参数  : byte[] Value [IN]: 数据值，不可以超过255长度
	public native boolean SetStringFieldByCol(long Handle,int Row,int Col,byte[] Value);
	

   // 函数名: SetIntFieldByName
   // 编程  : 陈永华 2005-11-14 18:09:57
   // 描述  : 设置指定数据区中第Row条记录中的对应字段的值
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : byte[] FieldName [IN]: 字段名称 如"vsmess"
   // 参数  : int Value [IN]: 数据值
	public native boolean SetIntFieldByName(long Handle,int Row,byte[] FieldName,int Value);

   // 函数名: SetDoubleFieldByName
   // 编程  : 陈永华 2005-11-14 18:10:02
   // 描述  : 设置指定数据区中第Row条记录中的对应字段的值
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : byte[] FieldName [IN]: 字段名称 如"vsmess"
   // 参数  : double Value [IN]: 数据值
	public native boolean SetDoubleFieldByName(long Handle,int Row,byte[] FieldName,double Value);

   // 函数名: SetStringFieldByName
   // 编程  : 陈永华 2005-11-14 18:10:07
   // 描述  : 设置指定数据区中第Row条记录中的对应字段的值
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 本包中指定的记录号 [0..RecordCount-1]
   // 参数  : byte[] FieldName [IN]: 字段名称 如"vsmess"
   // 参数  : byte[] Value [IN]: 数据值，不可以超过255长度
	public native boolean SetStringFieldByName(long Handle,int Row,byte[] FieldName,byte[] Value);
	

   // 函数名: SetRequestType
   // 编程  : 陈永华 2005-11-14 18:10:12
   // 描述  : 设置请求数据中的功能号 （在EncodeXpackForRequest之前一定要设置）
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int RequestType [IN]: 对应的业务功能号
	public native boolean SetRequestType(long Handle,int RequestType);
	

   // 函数名: IsEof
   // 编程  : 陈永华 2005-11-14 18:10:17
   // 描述  : 是否已经是最后一个应答包了，和HaveNextPack正好相反
   // 返回  : boolean : true - 表示已经没有后续应答数据包了；false - 要通过调用EncodeXpackForNext后续包
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
	public native boolean IsEof(long Handle);
	

   // 函数名: GetRecordCount
   // 编程  : 陈永华 2005-11-14 18:10:22
   // 描述  : 解包后读取本包中的记录数RecordCount
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int[] RecordCount [OUT]: 返回解包后的记录数
	public native boolean GetRecordCount(long Handle,int[] RecordCount);

   // 函数名: GetRetCode
   // 编程  : 陈永华 2005-11-14 18:10:28
   // 描述  : 解包后读取其返回码
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int[] RetCode [OUT]: 返回收到数据包中的返回码
	public native boolean GetRetCode(long Handle,int[] RetCode);


   // 函数名: EnCodeXpackForRequest
   // 编程  : 陈永华 2005-11-14 21:10:33
   // 描述  : 对XPack数据块进行编码。将已经设置了的XPack数据打包到指定的数据块(PackBuffer)中
   //       Notice: 在目前的应用服务器系统中，通过设置请求记录中的数据后，调用本方法，将数据打包为请求包。
   //                然后便于将打包的请求数据用业务通讯平台发送到应用服务器或对端。
   // 返回  : boolean : 打包成功与否
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : byte[] PackBuffer [OUT]: 打包成功后存放的打包数据 
   // 参数  : int PackBufferSize [IN]: PackBuffer的缓冲区字节长度（可打包的最大长度）
   // 参数  : int[] PackDataLength [OUT]: 返回打包后数据长度（字节数）
	public native boolean EnCodeXpackForRequest(long Handle,byte[] PackBuffer,int PackBufferSize,int[] PackDataLength);

   // 函数名: EnCodeXpackForNext
   // 编程  : 陈永华 2005-11-14 21:10:39
   // 描述  : 根据上次解码数据，获得读取后续数据包的请求包
   //       Notice: 当用HaveNextPack()确定还有后续应答数据包的时候，用本函数得到获取后续数据的请求包。
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : byte[] PackBuffer [OUT]: 打包成功后存放的打包数据 
   // 参数  : int PackBufferSize [IN]: PackBuffer的缓冲区字节长度（可打包的最大长度）
   // 参数  : int[] PackDataLength [OUT]: 返回打包后数据长度（字节数）
	public native boolean EnCodeXpackForNext(long Handle,byte[] PackBuffer,int PackBufferSize,int[] PackDataLength);

   // 函数名: DeCodeXpack
   // 编程  : 陈永华 2005-11-14 21:10:44
   // 描述  : 对指定的编码数据块进行解码。
   //         Notice: 当收到对方返回打包数据后，用本函数将数据解包为常规数据
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : byte[] PackData [IN]: 编码的数据，对此进行解码
   // 参数  : int PackDataLength [IN]: 编码数据长度
	public native boolean DeCodeXpack(long Handle,byte[] PackData,int PackDataLength);

   // 函数名: GetPrivateFunctionForNext
   // 编程  : 陈永华 2005-11-14 21:10:48
   // 描述  : 根据收得解码后的数据，从中得到属于可以获取后续应答数据包的应用服务器专用通讯功能号
   //          详细技术请参考KSBCC使用说明书
   // 返回  : int : >0 - 可获取后续数据的专用通讯功能号；否则失败
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
	public native int GetPrivateFunctionForNext(long Handle);

   // 函数名: GetBranchNoForNext
   // 编程  : 陈永华 2005-11-14 21:10:52
   // 描述  : 根据收得解码后的数据，从中得到属于可以获取后续应答数据包的目标通讯平台节点编号
   //          详细技术请参考KSMBCC使用说明书
   // 返回  : int >0: 获取后续应答数据包的目标通讯平台节点编号; 否则还是用原来的节点编号
   //                当该功能是用Transfer实现的时候，需要这个可能被变更了的节点号
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
	public native int GetBranchNoForNext(long Handle);

   // 函数名: SetRecordCount
   // 编程  : 陈永华 2005-11-14 21:10:56
   // 描述  : 预设置请求数据中的记录数
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int RecordCount [IN]: 设置的记录数
	public native boolean SetRecordCount(long Handle,int RecordCount);

   // 函数名: SetMaxRetCount
   // 编程  : 陈永华 2005-11-14 21:11:00
   // 描述  : 设置应答包每次返回的最多记录数
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int MaxRetCount [IN]: 指定的最多记录数，0则由应用服务器端 [0..100]; 
	public native boolean SetMaxRetCount(long Handle,int MaxRetCount);

   // 函数名: GetXPackType
   // 编程  : 陈永华 2005-11-14 21:11:05
   // 描述  : 查询当前数据块中数据记录类型
   // 返回  : int 返回数据记录类型 0-标准ST_PACK记录；1-ST_SDPACK的RawData记录
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
	public native int GetXPackType(long Handle); 

   // 函数名: SetRawRecord
   // 编程  : 陈永华 2005-11-14 21:11:11
   // 描述  : 设置指定记录为指定的RawData记录
   // 返回  : boolean 
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 指定设置的记录号 [0..RecordCount-1]
   // 参数  : byte[] RawData [IN]: 要设置数据块
   // 参数  : int RawDataLength [IN]: 要设置数据块长度
	public native boolean SetRawRecord(long Handle, int Row, byte[] RawData, int RawDataLength);

   // 函数名: GetRawRecord
   // 编程  : 陈永华 2005-11-14 21:11:15
   // 描述  : 当用GetXPackType返回为1即ST_SDPACK类的记录，则可以用本函数获取各个有效记录中的RawData记录
   // 返回  : int : >=0 - 成功返回RawData的数据长度(字节数)
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Row [IN]: 指定的记录号 [0..RecordCount-1]
   // 参数  : byte[] RawData [OUT]: 存放读取的RawData数据块 
   // 参数  : int RawDataSize [IN]: RawData数据块的可存放的最长长度
	public native int GetRawRecord(long Handle, int Row, byte[] RawData, int RawDataSize);

   // 函数名: GetMaxColumn
   // 编程  : 陈永华 2005-11-14 21:11:20
   // 描述  : 获取本格式的XPack中最大的有效字段索引值，与当时数据块不同
   // 返回  : int 返回ST_PACK中的最大有效字段索引值
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
	public native int GetMaxColumn(long Handle);

   // 函数名: IsValidColumn
   // 编程  : 陈永华 2005-11-14 21:11:24
   // 描述  : 结合当前数据，确定指定字段索引号是否为有效字段
   // 返回  : boolean : true-为有效字段
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : int Col [IN]: 指定的字段索引号
	public native boolean IsValidColumn(long Handle, int Col);

   // 函数名: GetFieldColumn
   // 编程  : 陈永华 2005-11-14 21:11:29
   // 描述  : 根据字段名称，获得字段索引号
   // 返回  : int >=0 为本XPACK中有效字段，返回的值即为索引号；<0为本XPACK中没有这个字段
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
   // 参数  : byte[] FieldName [IN]: 字段名称 如"vsmess"
	public native int GetFieldColumn(long Handle, byte[] FieldName);

   // 函数名: HaveNextPack
   // 编程  : 陈永华 2005-11-14 22:01:15
   // 描述  : 当解码后，通过本函数判断是否还有后续应答包
   // 返回  : boolean : true-表示还有后续应答包；false－无后续包
   // 参数  : long Handle [IN]: 指定的XPack数据区句柄
	public native boolean HaveNextPack(long Handle);

	static 
	{
		System.loadLibrary("xpacklib");
	}
}
