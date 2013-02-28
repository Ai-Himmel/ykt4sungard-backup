unit UACardDestoryRpt;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  UReportMachineTemp, RM_Common, RM_Class, RM_e_main, RM_e_Xls,
  RM_Designer, RM_Dataset, ImgList, RM_Preview, RzPanel, RzButton,
  ZAbstractRODataset, ZAbstractDataset, ZDataset, ZAbstractTable,
  RM_e_Jpeg, RM_e_Graphic, RM_e_bmp, RM_e_htm;

type
  TfaqhCardDestoryRpt = class(TfaReportMachineTemp)
    Panel1: TPanel;
    Label2: TLabel;
    cbbOperTrans: TWVComboBox;
    WVLabel1: TWVLabel;
    edtBeginDate: TWVEdit;
    WVLabel2: TWVLabel;
    edtEndDate: TWVEdit;
    ztbl1: TZTable;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
    strBDate,strEDate:string;
    endSign:Boolean;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardDestoryRpt: TfaqhCardDestoryRpt;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, SmartCardCommon,
     KSClientConsts,KSDataDictionary,DataUsageUtils, UCMqhReportImp,
  UrptTbl;
     
{$R *.DFM}

procedure TfaqhCardDestoryRpt.Init;
begin
  inherited;
  if Context.ParamData(svOperatorNoName).AsString='system' then
  begin
    cbbOperTrans.ItemIndex := 0;
  end
  else
  begin
    WorkView.FieldByName('����Ա��').DefaultValue  := Context.ParamData(svOperatorNoName).AsString;
    WorkView.Reset;
  end;
  edtBeginDate.Text := baccountDate;
  edtEndDate.Text := baccountDate;
  endSign := True;
end;

procedure TfaqhCardDestoryRpt.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhCardDestoryRpt.btnQueryClick(Sender: TObject);
var
  tmpData:TDataSet;
  qry:TZQuery;
  i:Integer;
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
  if endSign = False then
    Exit;
  endSign := False;
  if execSQL_SLite(delrptdailyacc)<>0 then
    Exit;
  //execSQL(delrptdailyacc);
  qry := nil;
  i:= 1;
  try
    qry := TZQuery.Create(nil);
    qry.Connection := dmReportImp.conSLite;
    if execSQL_SLite(beginTrans)<>0 then
      Exit;
    tmpData.First;
    while not tmpData.Eof do
    begin
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add(irptDestoryCardSql(tmpData,i));
      qry.ExecSQL;
      inc(i);
      tmpData.Next;
    end;
    if execSQL_SLite(commitTrans)<>0 then
      Exit;
  finally
    qry.Close;
    qry.Destroy;
  end;
  try
    rptReport.LoadFromFile(sPreAppPath+'report\�����ֽ𱨱�.rmf');
    ztbl1.TableName := 'T_RPTDAILYACC';
    if ztbl1.Active=True then
      ztbl1.Active := False;
    ztbl1.Active := True;
    if (strBDate<>'') and (strEDate<>'') then
      rptReport.Dictionary.Variables.AsString['dateRange'] := 'ͳ�����ڣ�'+strBDate+'��'+strEDate;
    rptReport.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
    rptReport.Dictionary.Variables.AsString['rptOper'] := rptOper;
    rptReport.Dictionary.Variables.AsString['checkOper'] := Context.ParamData(svOperatorNameName).AsString;
    //rptReport.DoublePass := True;
    rptReport.Preview := rmprvwP;
    rptReport.ShowReport;
  except
    Context.GetDialogSystem.ShowMessage('��û�а�װ��ӡ�������Ȱ�װ(�����������ӡ��)��');
  end;
  endSign := True;
end;

initialization
  TUIStdClassFactory.Create('�����ֽ𱨱�',TfaqhCardDestoryRpt);

end.