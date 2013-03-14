unit UCardSerialOper;

interface
uses
  Windows, Messages, SysUtils, Classes, Controls, Dialogs, StdCtrls, ExtCtrls,
  INIFiles, Db,ZAbstractRODataset, ZAbstractDataset, ZDataset,UCMqhCardImp,
  WorkViews,WVCmdReq,ZConnection;

  function getSeqNo: Integer;
  procedure incSeqNo(perSeqNo:Integer);

    //充值，支取失败冲正业务处理
  function cashOperCancel(workviewIn: TWorkView;wvRequest:TWVRequest;operDate:string;seriId:Integer;stationId:Integer): string;

implementation

uses KsFrameworks,KSClientConsts;

{-------------------------------------------------------------------------------
  过程名:    getSeqNo取本地数据库的流水号发送到后台
  作者:      hanjiwei
  日期:      2009.02.11
  参数:      无
  返回值:    Integer
-------------------------------------------------------------------------------}
function getSeqNo: Integer;
var
  qry:TZQuery;
  sqlStr:string;
begin
  qry := nil;
  sqlstr := 'select SITENO,SITESEQNO from T_SITE';
  try
    try
      qry := TZQuery.Create(nil);
      qry.Connection := dmCardImp.confb;
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add(sqlStr);
      qry.Open;
      Result := qry.fieldbyname('SITESEQNO').AsInteger;
    except
      on e:Exception do
        ShowMessage('另外一个程序正在使用本地数据库，请先关闭其它程序，然后再使用--'+e.Message);
    end;
  finally
    qry.Close;
    qry.Destroy;
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    incSeqNo完成交易后本地数据库的流水号自动增加，供下次调用
  作者:      hanjiwei
  日期:      2009.02.11
  参数:      perSeqNo:Integer上次的交易流水号
  返回值:    无
-------------------------------------------------------------------------------}
procedure incSeqNo(perSeqNo:Integer);
var
  qry:TZQuery;
  sqlStr:string;
begin
  qry := nil;
  sqlstr := 'update T_SITE set SITESEQNO='+inttostr(perSeqNo+1);           //
  try
    try
      qry := TZQuery.Create(nil);
      qry.Connection := dmCardImp.confb;
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add(sqlStr);
      qry.ExecSQL;
    except
      on e:Exception do
      ShowMessage('另外一个程序正在使用本地数据库，请先关闭其它程序，然后再使用-'+e.Message);
    end;
  finally
    qry.Close;
    qry.Destroy;
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    cashOperCancel充值、支取失败做冲正交易
  作者:      hanjiwei
  日期:      2008.07.04
  参数:      workviewIn: TWorkView;wvRequest:TWVRequest
  返回值:    string
-------------------------------------------------------------------------------}
function cashOperCancel(workviewIn: TWorkView;wvRequest:TWVRequest;operDate:string;seriId:Integer;stationId:Integer): string;
var
  reSend:Boolean;
  perSeqNo:Integer;//本地数据库的交易流水号

begin
  workviewIn.FieldByName('终端编号').Data.SetInteger(stationId);
  workviewIn.FieldByName('流水号').Data.SetInteger(seriId);
  workviewIn.FieldByName('业务日期').Data.SetString(operDate);
  perSeqNo := getSeqNo;
  reSend := False;
  while not reSend do
  begin
    try
      workviewIn.FieldByName('本地流水号').Data.SetInteger(perSeqNo);
      wvRequest.SendCommand;
      reSend := True;
    except
      on e:Exception do
        Context.GetDialogSystem.ShowMessage(e.Message+'--系统将重新发送该交易！');
    end;
  end;
  //交易完成后流水号自动增加
  incSeqNo(perSeqNo);
  
  if workviewIn.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    context.GetDialogSystem.ShowMessage('冲正失败，请在交易冲正中处理该记录并重新做该业务！');
    Result := '冲正失败--'+
    workviewIn.fieldbyname('返回信息').Data.AsString+ ',请在交易冲正中处理该记录并重新做该业务！';
  end
  else
  begin
    context.GetDialogSystem.ShowMessage('业务失败，请重新操作该项业务！');
    Result := '业务失败，请重新操作该项业务！';
  end;
end;


end.
