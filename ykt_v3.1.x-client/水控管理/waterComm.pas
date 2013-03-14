unit waterComm;

interface
uses
  Windows, Messages, SysUtils, Classes, ExtCtrls,Graphics,WVCtrls,Controls, WorkViews,Dialogs,
  RzTabs,WVCmdReq,KSFrameWorks;
var
  operType:string;
  
  procedure queryType(operName:string;workview:Tworkview);
  procedure addType(operName:string;workview:Tworkview);
  procedure deleteType(operName:string;workview:Tworkview);
  procedure chargeType(operName:string;workview:Tworkview);
  procedure okClick(AddRequest,DeleteRequest,ChangeRequest:TWVRequest);
  function checkInputDate(input:string):Boolean ;
  function checkInputTime(input:string):Boolean;
  function SpliteDateStr(str: string): string;
  function checkQueryCbb(panel:TPanel): Boolean;
  function checkQueryEdit(panel:TPanel): Boolean;
implementation

{-------------------------------------------------------------------------------
  过程名:    addType添加操作
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      operName:string;workview:Tworkview
  返回值:    无
-------------------------------------------------------------------------------}
procedure addType(operName:string;workview:Tworkview);
begin
  WorkView.FieldByName('操作员').Data.SetString(operName);
  WorkView.FieldByName('标志').Data.SetString('A');
  opertype:='A';
end;
{-------------------------------------------------------------------------------
  过程名:    queryType查询操作
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      operName:string;workview:Tworkview
  返回值:    无
-------------------------------------------------------------------------------}
procedure queryType(operName:string;workview:Tworkview);
begin
  WorkView.FieldByName('操作员').Data.SetString(operName);
  WorkView.FieldByName('标志').Data.SetString('R');
  opertype:='R';
end;
{-------------------------------------------------------------------------------
  过程名:    deleteType删除操作
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      operName:string;workview:Tworkview
  返回值:    无
-------------------------------------------------------------------------------}
procedure deleteType(operName:string;workview:Tworkview);
begin
  WorkView.FieldByName('操作员').Data.SetString(operName);
  WorkView.FieldByName('标志').Data.SetString('D');
  opertype:='D';
end;
{-------------------------------------------------------------------------------
  过程名:    chargeType修改操作
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      operName:string;workview:Tworkview
  返回值:    无
-------------------------------------------------------------------------------}
procedure chargeType(operName:string;workview:Tworkview);
begin
  WorkView.FieldByName('操作员').Data.SetString(operName);
  WorkView.FieldByName('标志').Data.SetString('U');
  opertype:='U';
end;
{-------------------------------------------------------------------------------
  过程名:    okClick完成后确定操作
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      requestType:TWVRequest
  返回值:    无
-------------------------------------------------------------------------------}
procedure okClick(AddRequest,DeleteRequest,ChangeRequest:TWVRequest);
begin
  if operType='A' then
    AddRequest.SendCommand;
  if operType='D' then
    DeleteRequest.SendCommand;
  if operType='U' then
    ChangeRequest.SendCommand;
end;

{-------------------------------------------------------------------------------
  过程名:    checkInputDate检查输入的日期是否正确
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      input:string
  返回值:    Boolean
-------------------------------------------------------------------------------}
function checkInputDate(input:string):Boolean ;
begin
  Result := False;
  if trim(input) = '' then
  begin
    Showmessage('时间不能为空，请输入！');
    Result := False;
    Exit;
  end;
  if length(input) = 4 then
  begin
    try
      StrToDateTime(SpliteDateStr(input));
      Result := True;
    except
      // 不是正确的日期格式
    end;
  end;
  if not Result then
     ShowMessage(Format('您输入的日期[%s]格式不正确!'#13
      + '如果要输入6月18日,请输入0618',[input]));
end;
function SpliteDateStr(str: string): string;
begin
  Result := '';
  if length(str) <> 4 then
    Exit;
  Result := Format('%s-%s',
    [Copy(str,1,2),Copy(str,3,2)]);
end;
{-------------------------------------------------------------------------------
  过程名:    checkInputTime检查输入的时间是否正确
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      input:string
  返回值:    Boolean
-------------------------------------------------------------------------------}
function checkInputTime(input:string):Boolean;
  function SpliteTimeStr(input: string) : string;
  begin
    Result := '';
    if length(input) <> 6 then
      Exit;
    Result := Format('%s:%s:%s',
      [Copy(input,1,2),Copy(input,3,2),Copy(input,5,2)]);
  end;
begin
  Result := False;
  if trim(input) = '' then
  begin
    Showmessage('时间不能为空，请输入！');
    Result := False;
    exit;
  end;
  Result := True;
end;
{-------------------------------------------------------------------------------
  过程名:    checkQueryEdit检查输入框是否为空或为零
  作者:      韩纪伟
  日期:      2005.12.30
  参数:      panel:TPanel
  返回值:    Boolean
-------------------------------------------------------------------------------}
function checkQueryEdit(panel:TPanel): Boolean;
var
  i:Integer;
begin
  Result := False;
  for i := 0 to panel.ControlCount-1 do
  begin
    if (panel.Controls[i] is TWVEdit) then
      if (Trim(TWVEdit(panel.Controls[i]).Text) <> '')and(Trim(TWVEdit(panel.Controls[i]).Text) <> '0') then
        Result := True;
  end;
end;
{-------------------------------------------------------------------------------
  过程名:    checkQueryCbb检查下拉列表框是否选择内容
  作者:      韩纪伟
  日期:      2005.12.30
  参数:      panel:TPanel
  返回值:    Boolean
-------------------------------------------------------------------------------}
function checkQueryCbb(panel:TPanel): Boolean;
var
  i:Integer;
begin
  Result := False;
  for i := 0 to panel.ControlCount-1 do
  begin
    if (panel.Controls[i] is TWVComboBox) then
      if (TWVComboBox(panel.Controls[i]).ItemIndex<> -1)and(TWVComboBox(panel.Controls[i]).ItemIndex<>0) then
        Result := True;
  end;
end;

end.

