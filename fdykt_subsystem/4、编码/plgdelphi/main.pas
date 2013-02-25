unit main;

interface
  uses def,SysUtils,Dialogs,Windows,XMLIntf,Classes,ActiveX;
  
  procedure init_library;
  function registe_module(module : Pksf_plugin_module):Integer;stdcall;
  function unregiste_module(module: Pksf_plugin_module):Integer;stdcall;

  function module_init :Integer; stdcall;
  function module_release :Integer; stdcall;
  function module_receive(svr : Pksf_server_conf;
                              data : Pksf_xml_data;
                              ret : Pksf_card_result):Integer; stdcall;

implementation

uses module;
var
  simple_module : ksf_plugin_module;
  Output: TStream;
/////////////////////////////////////////////////////////////////

/// 处理请求数据包的函数
/// 返回0 表示调用成功,失败表示调用失败
function module_receive(svr : Pksf_server_conf;
                              data : Pksf_xml_data;
                              ret : Pksf_card_result):Integer; stdcall;
var
  dataStart : PChar;
  buf : array[0..8192] of char;
  I : Integer;
  Node: IXMLNode;
  value: string;
  cardidname:string;
begin
  // 1.该函数根据功能号来判断是否要处理数据包,以及数据包的格式
  // 2.同一功能号的数据包XML格式是一样的.
  // 3.该函数的处理时间不要太长,不超过20 秒
  dataStart := @(data^.data);
  CopyMemory(PChar(@buf),dataStart,data^.length);
  //ShowMessage(Format('Function NO : %d'#10#13'%s',[data^.func_no,dataStart]));
  //ShowMessage(dataStart);
  with dmMain do
  begin
    XMLDoc.Active := False;
    XMLDoc.XML.Clear;
    value := Copy(buf,0,data^.length);
    XMLDoc.XML.Add(value);
    XMLDoc.XML.Text;

    XMLDoc.Active := True;

    if XMLDoc.DocumentElement <> nil then
    begin
      if data^.func_no = 400000 then
        cardidname := 'cardid'
      else
        cardidname := 'card-id';
      Output.Seek(0,soFromEnd);
      for I := 0 to XMLDoc.DocumentElement.ChildNodes.Count - 1 do
      begin
        Node := XMLDoc.DocumentElement.ChildNodes.Nodes[I];
        value := Format('phy[%s]Card[%s]Stuempno[%s]flag[%s]volume[%s]'#13#10,[
        Node.ChildValues['phy-id'],
          Node.ChildValues[cardidname],Node.ChildValues['stuempno']
          ,Node.ChildValues['flag'],Node.ChildValues['blk-version']]);
        Output.WriteBuffer(value[1],Length(value));
      end;
    end;
  end;
  // 如果成功就设置为 RET_OK
  // 只要有一条失败就设置为 RET_FAILD, 通用前置会重新发送数据包
  ret^.ret := RET_OK;
  Result := 0;
end;

/// 插件函数,当模块被子系统加载时,由子系统调用
/// 返回 0 表示调用成功, -1 表示调用不成功
function module_init :Integer; stdcall;
begin
  Result := 0;
end;
/// 插件函数,当模块被子系统释放时,由子系统调用
/// 返回 0 表示调用成功, -1 表示调用不成功
function module_release :Integer; stdcall;
begin
  Result := 0;
end;

/// DLL接口函数,
function registe_module(module : Pksf_plugin_module):Integer;stdcall;
begin
  CopyMemory(module,@simple_module,SizeOf(ksf_plugin_module));
  Output := TFileStream.Create('c:\output.txt',fmOpenReadWrite);
  Output.Seek(0,soFromEnd);
  Result := 0;
end;
/// DLL接口函数
function unregiste_module(module: Pksf_plugin_module):Integer;stdcall;
begin
  ZeroMemory(module,SizeOf(ksf_plugin_module));
  FreeAndNil(Output);
  CoUninitialize();
  Result := 0;
end;
/// 初始化模块结构,DLL在被加载时会被调用
procedure init_library;
begin
  StrCopy(simple_module.module_name,'测试');
  StrCopy(simple_module.module_path,'');     	// 模块名称
  StrCopy(simple_module.date,'20050906');
  StrCopy(simple_module.author,'汤成');
  simple_module.major_ver := 1;
  simple_module.minor_ver := 1;
  simple_module.module_init := nil;
  simple_module.module_release := nil;
  simple_module.module_receive := module_receive;
  CoInitialize(nil);
  dmMain := TdmMain.Create(nil);
end;
end.
