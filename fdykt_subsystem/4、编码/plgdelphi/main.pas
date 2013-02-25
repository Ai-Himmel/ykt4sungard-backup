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

/// �����������ݰ��ĺ���
/// ����0 ��ʾ���óɹ�,ʧ�ܱ�ʾ����ʧ��
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
  // 1.�ú������ݹ��ܺ����ж��Ƿ�Ҫ�������ݰ�,�Լ����ݰ��ĸ�ʽ
  // 2.ͬһ���ܺŵ����ݰ�XML��ʽ��һ����.
  // 3.�ú����Ĵ���ʱ�䲻Ҫ̫��,������20 ��
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
  // ����ɹ�������Ϊ RET_OK
  // ֻҪ��һ��ʧ�ܾ�����Ϊ RET_FAILD, ͨ��ǰ�û����·������ݰ�
  ret^.ret := RET_OK;
  Result := 0;
end;

/// �������,��ģ�鱻��ϵͳ����ʱ,����ϵͳ����
/// ���� 0 ��ʾ���óɹ�, -1 ��ʾ���ò��ɹ�
function module_init :Integer; stdcall;
begin
  Result := 0;
end;
/// �������,��ģ�鱻��ϵͳ�ͷ�ʱ,����ϵͳ����
/// ���� 0 ��ʾ���óɹ�, -1 ��ʾ���ò��ɹ�
function module_release :Integer; stdcall;
begin
  Result := 0;
end;

/// DLL�ӿں���,
function registe_module(module : Pksf_plugin_module):Integer;stdcall;
begin
  CopyMemory(module,@simple_module,SizeOf(ksf_plugin_module));
  Output := TFileStream.Create('c:\output.txt',fmOpenReadWrite);
  Output.Seek(0,soFromEnd);
  Result := 0;
end;
/// DLL�ӿں���
function unregiste_module(module: Pksf_plugin_module):Integer;stdcall;
begin
  ZeroMemory(module,SizeOf(ksf_plugin_module));
  FreeAndNil(Output);
  CoUninitialize();
  Result := 0;
end;
/// ��ʼ��ģ��ṹ,DLL�ڱ�����ʱ�ᱻ����
procedure init_library;
begin
  StrCopy(simple_module.module_name,'����');
  StrCopy(simple_module.module_path,'');     	// ģ������
  StrCopy(simple_module.date,'20050906');
  StrCopy(simple_module.author,'����');
  simple_module.major_ver := 1;
  simple_module.minor_ver := 1;
  simple_module.module_init := nil;
  simple_module.module_release := nil;
  simple_module.module_receive := module_receive;
  CoInitialize(nil);
  dmMain := TdmMain.Create(nil);
end;
end.
