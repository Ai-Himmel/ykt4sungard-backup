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
  过程名:    addType添加操作
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      operName:string;workview:Tworkview
  返回值:    无
-------------------------------------------------------------------------------}
procedure addType(workview:Tworkview);
begin
  WorkView.FieldByName('操作标志').Data.SetString('A');
  opertype:='A';
end;
{-------------------------------------------------------------------------------
  过程名:    queryType查询操作
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      operName:string;workview:Tworkview
  返回值:    无
-------------------------------------------------------------------------------}
procedure queryType(workview:Tworkview);
begin
  WorkView.FieldByName('操作标志').Data.SetString('R');
  opertype:='R';
end;
{-------------------------------------------------------------------------------
  过程名:    deleteType删除操作
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      operName:string;workview:Tworkview
  返回值:    无
-------------------------------------------------------------------------------}
procedure deleteType(workview:Tworkview);
begin
  WorkView.FieldByName('操作标志').Data.SetString('D');
  opertype:='D';
end;
{-------------------------------------------------------------------------------
  过程名:    chargeType修改操作
  作者:      韩纪伟
  日期:      2005.09.21
  参数:      operName:string;workview:Tworkview
  返回值:    无
-------------------------------------------------------------------------------}
procedure chargeType(workview:Tworkview);
begin
  WorkView.FieldByName('操作标志').Data.SetString('U');
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

end.
