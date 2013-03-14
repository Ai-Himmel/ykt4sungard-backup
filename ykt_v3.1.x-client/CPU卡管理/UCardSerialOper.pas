unit UCardSerialOper;

interface
uses
  Windows, Messages, SysUtils, Classes, Controls, Dialogs, StdCtrls, ExtCtrls,
  INIFiles, Db,ZAbstractRODataset, ZAbstractDataset, ZDataset,UCMqhCardImp,
  WorkViews,WVCmdReq,ZConnection;

  function getSeqNo: Integer;
  procedure incSeqNo(perSeqNo:Integer);

    //��ֵ��֧ȡʧ�ܳ���ҵ����
  function cashOperCancel(workviewIn: TWorkView;wvRequest:TWVRequest;operDate:string;seriId:Integer;stationId:Integer): string;

implementation

uses KsFrameworks,KSClientConsts;

{-------------------------------------------------------------------------------
  ������:    getSeqNoȡ�������ݿ����ˮ�ŷ��͵���̨
  ����:      hanjiwei
  ����:      2009.02.11
  ����:      ��
  ����ֵ:    Integer
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
        ShowMessage('����һ����������ʹ�ñ������ݿ⣬���ȹر���������Ȼ����ʹ��--'+e.Message);
    end;
  finally
    qry.Close;
    qry.Destroy;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    incSeqNo��ɽ��׺󱾵����ݿ����ˮ���Զ����ӣ����´ε���
  ����:      hanjiwei
  ����:      2009.02.11
  ����:      perSeqNo:Integer�ϴεĽ�����ˮ��
  ����ֵ:    ��
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
      ShowMessage('����һ����������ʹ�ñ������ݿ⣬���ȹر���������Ȼ����ʹ��-'+e.Message);
    end;
  finally
    qry.Close;
    qry.Destroy;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    cashOperCancel��ֵ��֧ȡʧ������������
  ����:      hanjiwei
  ����:      2008.07.04
  ����:      workviewIn: TWorkView;wvRequest:TWVRequest
  ����ֵ:    string
-------------------------------------------------------------------------------}
function cashOperCancel(workviewIn: TWorkView;wvRequest:TWVRequest;operDate:string;seriId:Integer;stationId:Integer): string;
var
  reSend:Boolean;
  perSeqNo:Integer;//�������ݿ�Ľ�����ˮ��

begin
  workviewIn.FieldByName('�ն˱��').Data.SetInteger(stationId);
  workviewIn.FieldByName('��ˮ��').Data.SetInteger(seriId);
  workviewIn.FieldByName('ҵ������').Data.SetString(operDate);
  perSeqNo := getSeqNo;
  reSend := False;
  while not reSend do
  begin
    try
      workviewIn.FieldByName('������ˮ��').Data.SetInteger(perSeqNo);
      wvRequest.SendCommand;
      reSend := True;
    except
      on e:Exception do
        Context.GetDialogSystem.ShowMessage(e.Message+'--ϵͳ�����·��͸ý��ף�');
    end;
  end;
  //������ɺ���ˮ���Զ�����
  incSeqNo(perSeqNo);
  
  if workviewIn.FieldByName('������').Data.AsInteger<>0 then
  begin
    context.GetDialogSystem.ShowMessage('����ʧ�ܣ����ڽ��׳����д���ü�¼����������ҵ��');
    Result := '����ʧ��--'+
    workviewIn.fieldbyname('������Ϣ').Data.AsString+ ',���ڽ��׳����д���ü�¼����������ҵ��';
  end
  else
  begin
    context.GetDialogSystem.ShowMessage('ҵ��ʧ�ܣ������²�������ҵ��');
    Result := 'ҵ��ʧ�ܣ������²�������ҵ��';
  end;
end;


end.
