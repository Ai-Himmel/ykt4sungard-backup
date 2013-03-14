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
  ������:    addType��Ӳ���
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      operName:string;workview:Tworkview
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure addType(operName:string;workview:Tworkview);
begin
  WorkView.FieldByName('����Ա').Data.SetString(operName);
  WorkView.FieldByName('��־').Data.SetString('A');
  opertype:='A';
end;
{-------------------------------------------------------------------------------
  ������:    queryType��ѯ����
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      operName:string;workview:Tworkview
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure queryType(operName:string;workview:Tworkview);
begin
  WorkView.FieldByName('����Ա').Data.SetString(operName);
  WorkView.FieldByName('��־').Data.SetString('R');
  opertype:='R';
end;
{-------------------------------------------------------------------------------
  ������:    deleteTypeɾ������
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      operName:string;workview:Tworkview
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure deleteType(operName:string;workview:Tworkview);
begin
  WorkView.FieldByName('����Ա').Data.SetString(operName);
  WorkView.FieldByName('��־').Data.SetString('D');
  opertype:='D';
end;
{-------------------------------------------------------------------------------
  ������:    chargeType�޸Ĳ���
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      operName:string;workview:Tworkview
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure chargeType(operName:string;workview:Tworkview);
begin
  WorkView.FieldByName('����Ա').Data.SetString(operName);
  WorkView.FieldByName('��־').Data.SetString('U');
  opertype:='U';
end;
{-------------------------------------------------------------------------------
  ������:    okClick��ɺ�ȷ������
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      requestType:TWVRequest
  ����ֵ:    ��
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
  ������:    checkInputDate�������������Ƿ���ȷ
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      input:string
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
function checkInputDate(input:string):Boolean ;
begin
  Result := False;
  if trim(input) = '' then
  begin
    Showmessage('ʱ�䲻��Ϊ�գ������룡');
    Result := False;
    Exit;
  end;
  if length(input) = 4 then
  begin
    try
      StrToDateTime(SpliteDateStr(input));
      Result := True;
    except
      // ������ȷ�����ڸ�ʽ
    end;
  end;
  if not Result then
     ShowMessage(Format('�����������[%s]��ʽ����ȷ!'#13
      + '���Ҫ����6��18��,������0618',[input]));
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
  ������:    checkInputTime��������ʱ���Ƿ���ȷ
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      input:string
  ����ֵ:    Boolean
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
    Showmessage('ʱ�䲻��Ϊ�գ������룡');
    Result := False;
    exit;
  end;
  Result := True;
end;
{-------------------------------------------------------------------------------
  ������:    checkQueryEdit���������Ƿ�Ϊ�ջ�Ϊ��
  ����:      ����ΰ
  ����:      2005.12.30
  ����:      panel:TPanel
  ����ֵ:    Boolean
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
  ������:    checkQueryCbb��������б���Ƿ�ѡ������
  ����:      ����ΰ
  ����:      2005.12.30
  ����:      panel:TPanel
  ����ֵ:    Boolean
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

