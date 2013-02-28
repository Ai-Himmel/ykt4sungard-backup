unit syscommon;

interface
uses
  Windows, Messages, SysUtils, Classes, ExtCtrls,Graphics,WVCtrls,Controls, WorkViews,Dialogs,
  RzTabs,WVCmdReq,KSFrameWorks;
var
  operType:string;
  
  procedure queryType(workview:Tworkview);
  procedure addType(workview:Tworkview);
  procedure deleteType(workview:Tworkview);
  procedure chargeType(workview:Tworkview);
  procedure okClick(AddRequest,DeleteRequest,ChangeRequest:TWVRequest);

implementation
{-------------------------------------------------------------------------------
  ������:    addType��Ӳ���
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      operName:string;workview:Tworkview
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure addType(workview:Tworkview);
begin
  WorkView.FieldByName('������־').Data.SetString('A');
  opertype:='A';
end;
{-------------------------------------------------------------------------------
  ������:    queryType��ѯ����
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      operName:string;workview:Tworkview
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure queryType(workview:Tworkview);
begin
  WorkView.FieldByName('������־').Data.SetString('R');
  opertype:='R';
end;
{-------------------------------------------------------------------------------
  ������:    deleteTypeɾ������
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      operName:string;workview:Tworkview
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure deleteType(workview:Tworkview);
begin
  WorkView.FieldByName('������־').Data.SetString('D');
  opertype:='D';
end;
{-------------------------------------------------------------------------------
  ������:    chargeType�޸Ĳ���
  ����:      ����ΰ
  ����:      2005.09.21
  ����:      operName:string;workview:Tworkview
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure chargeType(workview:Tworkview);
begin
  WorkView.FieldByName('������־').Data.SetString('U');
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

end.
