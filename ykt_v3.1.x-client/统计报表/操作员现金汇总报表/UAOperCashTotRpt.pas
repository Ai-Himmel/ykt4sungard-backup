unit UAOperCashTotRpt;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  UReportMachineTemp, RM_Common, RM_Class, RM_e_main, RM_e_Xls,
  RM_Designer, RM_Dataset, ImgList, RM_Preview, RzPanel, RzButton,
  ZAbstractRODataset, ZAbstractDataset, ZDataset, RM_e_Jpeg, RM_e_Graphic,
  RM_e_bmp, RM_e_htm;

type
  TfaqhOperCashTotRpt = class(TfaReportMachineTemp)
    Panel1: TPanel;
    Label2: TLabel;
    cbbOperTrans: TWVComboBox;
    WVLabel1: TWVLabel;
    edtBeginDate: TWVEdit;
    WVLabel2: TWVLabel;
    edtEndDate: TWVEdit;
    zqry1: TZQuery;
    lbl1: TLabel;
    cbb1: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
    strBDate,strEDate:string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhOperCashTotRpt: TfaqhOperCashTotRpt;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon,
      UCMqhReportImp, UrptTbl,LogFile;
     
{$R *.DFM}

procedure TfaqhOperCashTotRpt.Init;
begin
  inherited;
  if Context.ParamData(svOperatorNoName).AsString<>'system' then
  begin
    WorkView.FieldByName('����Ա��').DefaultValue := Context.ParamData(svOperatorNoName).AsString;
    WorkView.Reset;
  end
  else
  begin
    cbbOperTrans.ItemIndex := 0;
  end;
  edtBeginDate.Text := bAccountDate;
  edtEndDate.Text := bAccountDate;
end;

procedure TfaqhOperCashTotRpt.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhOperCashTotRpt.btnQueryClick(Sender: TObject);
var
  tmpData:TDataSet;
  qry:TZQuery;
begin
  if Trim(edtEndDate.Text)<>'' then
    if CheckInputDateFormat(edtEndDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����������벻��ȷ����ʽ��yyyymmdd');
      edtEndDate.SetFocus;
      Exit;
    end;
  if Trim(edtBeginDate.Text)<>'' then
    if CheckInputDateFormat(edtBeginDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('��ʼ�������벻��ȷ����ʽ��yyyymmdd');
      edtBeginDate.SetFocus;
      Exit;
    end;
  if (Trim(edtEndDate.Text)<>'') and (Trim(edtBeginDate.Text)<>'') then
    if Trim(edtBeginDate.Text)>Trim(edtEndDate.Text) then
      Context.GetDialogSystem.ShowMessage('��ʼ���ڲ��ܴ��ڽ������ڣ�');
  inherited;
  strBDate := edtBeginDate.Text;
  strEDate := edtEndDate.Text;
  
  tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  if tmpData.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('����ͳ�Ʊ�û����ؼ�¼��������ָ������');
    Exit;
  end;
  if execSQL_SLite(delrptopercash)<>0 then
    Exit;
  //execSQL(delrptopercash);
  qry := nil;
  try
    //execSQL(beginTrans);
    WriteLog('yktsg-��ʼִ�в��뱾������', 0);
    qry := TZQuery.Create(nil);
    qry.Connection := dmReportImp.conSLite;
    if execSQL_SLite(beginTrans)<>0 then
      Exit;
    tmpData.First;
    while not tmpData.Eof do
    begin
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add(irptOperCashTotRptSql(tmpData));
      qry.ExecSQL;
      tmpData.Next;
    end;
    WriteLog('yktsg-���뱾�����ݽ���', 1);
    if execSQL_SLite(commitTrans)<>0 then
      Exit;
    //execSQL(commitTrans);
  finally
    qry.Close;
    qry.Destroy;
  end;
  try
    WriteLog('yktsg-��ʼ�������Ա�ֽ���ܱ���.rmf', 3);
    rptReport.LoadFromFile(sPreAppPath+'report\����Ա�ֽ���ܱ���.rmf');
    WriteLog('yktsg-�������Ա�ֽ���ܱ���.rmf����', 4);
    //ztbl1.TableName := 't_rptsysstat';
    if zqry1.Active=True then
      zqry1.Active := False;
    WriteLog('yktsg-��ʼ�򿪱������ݿ��ѯ', 5);
    zqry1.Active := True;
    WriteLog('yktsg-�����򿪱������ݿ��ѯ', 6);
    rptReport.Dictionary.Variables.AsString['dateRange'] := 'ͳ�����ڣ�'+strBDate+'��'+strEDate;
    rptReport.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
    rptReport.Dictionary.Variables.AsString['rptOper'] := rptOper;
    rptReport.Dictionary.Variables.AsString['checkOper'] := Context.ParamData(svOperatorNameName).AsString;
    rptReport.DoublePass := True;
    rptReport.Preview := rmprvwP;
    WriteLog('yktsg-��ʼ��ʾ����', 7);
    rptReport.ShowReport;
    WriteLog('yktsg-��ʾ�������', 8);
  except
    Context.GetDialogSystem.ShowMessage('��û�а�װ��ӡ�������Ȱ�װ(�����������ӡ��)��');
  end;
end;

initialization
  TUIStdClassFactory.Create('����ԱƱ���ֽ���ܱ���',TfaqhOperCashTotRpt);

end.