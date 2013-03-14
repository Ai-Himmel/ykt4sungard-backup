unit filetrans;

interface

uses Forms;

type
	KSG_File_Handle = Pointer;

	const 
		FILETRANS_DLL = 'filetrans.dll';
		KSG_SUCCESS = 0; // 成功
		KSG_ERR_INITBCCCLT = 1001; { 初始化 bccclt 失败 }
		KSG_ERR_CONNECT_DRTP = 1002; { 连接通讯平台失败 }
		KSG_ERR_ALREADY_INIT = 1003; { bccclt 已经初始化了 }
		KSG_ERR_BCC_HANDLE = 1004; { 申请 bccclt 句柄失败 }
		KSG_ERR_MEMORY	= 1005; { 申请内存失败 }
		KSG_ERR_REQUEST	= 1006; { 请求后台失败 }
		KSG_ERR_WRITEFILE = 1007; { 写文件失败 }
		KSG_ERR_READFILE = 1008; { 读文件失败 }
		KSG_ERR_GET_DATA = 1009; { 获取返回数据失败 }
		KSG_ERR_RET_PACK = 1010; { 返回数据包错误 }
		KSG_ERR_FILE_CRC = 1011; { 文件校验失败 }
		KSG_ERR_FILESIZE_EXCEED = 1012; { 文件大小超过限制 }
	
	function KSG_init(ip:PChar;port,mainfunc:Integer):Integer;stdcall;
	procedure KSG_uninit;stdcall;
	function KSG_last_error:Integer;stdcall;
	function KSG_begin_request:KSG_File_Handle;stdcall;
	procedure KSG_free_request(handle:KSG_File_Handle);stdcall;
	function KSG_send_request(handle:KSG_File_Handle):Integer;stdcall;
	function KSG_set_param(handle:KSG_File_Handle;param_name:PChar;
							value:Pointer;len:Integer):Integer;stdcall;
	function KSG_get_errmsg:PChar;stdcall;
							
	function KSG_Download_File(src_file,dest_file:string):Integer;
	function KSG_Upload_File(src_file,dest_file:string):Integer;
	procedure KSG_test_callback(total_len,len:Integer);stdcall;
	

implementation
	function KSG_init;stdcall;external FILETRANS_DLL;
	procedure KSG_uninit;stdcall;external FILETRANS_DLL;
	function KSG_last_error;stdcall;external FILETRANS_DLL;
	function KSG_begin_request;stdcall;external FILETRANS_DLL;
	procedure KSG_free_request;stdcall;external FILETRANS_DLL;
	function KSG_send_request;stdcall;external FILETRANS_DLL;
	function KSG_set_param;stdcall;external FILETRANS_DLL;
	function KSG_get_errmsg;stdcall;external FILETRANS_DLL;

function KSG_Download_File(src_file,dest_file:string):Integer;
var
	handle :KSG_File_Handle;
begin
	Result := KSG_ERR_MEMORY;
	handle := KSG_begin_request;
	if handle = nil then Exit;
	
	KSG_set_param(handle,'src_filename',PChar(src_file),0);
	KSG_set_param(handle,'dest_filename',PChar(dest_file),0);
	KSG_set_param(handle,'callback',Pointer(@KSG_test_callback),0);
	
	Result := KSG_send_request(handle);
	
	KSG_free_request(handle);
end;

function KSG_Upload_File(src_file,dest_file:string):Integer;
var
	handle :KSG_File_Handle;
  upload :string;
begin
	Result := KSG_ERR_MEMORY;
	handle := KSG_begin_request;
	if handle = nil then Exit;

  upload := '1';
	KSG_set_param(handle,'src_filename',PChar(src_file),0);
	KSG_set_param(handle,'dest_filename',PChar(dest_file),0);
	KSG_set_param(handle,'callback',Pointer(@KSG_test_callback),0);
	KSG_set_param(handle,'upload',PChar(upload),0);
	Result := KSG_send_request(handle);
	
	KSG_free_request(handle);
end;

procedure KSG_test_callback(total_len,len:Integer);
begin
	Application.ProcessMessages;
end;

end.