unit UAAtmRpt;

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
  TfaqhAtmRpt = class(TfaReportMachineTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    cbbOperTrans: TWVComboBox;
    cbbNetInfo: TWVComboBox;
    WVLabel1: TWVLabel;
    edtBeginDate: TWVEdit;
    WVLabel2: TWVLabel;
    edtEndDate: TWVEdit;
    zqry1: TZQuery;
    Label3: TLabel;
    WVEdit1: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
    endSign:Boolean;
    strBDate,strEDate:string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhAtmRpt: TfaqhAtmRpt;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon,
      UCMqhReportImp, UrptTbl;
     
{$R *.DFM}

procedure TfaqhAtmRpt.Init;
begin
  inherited;
  endSign := True;
  {
  if Context.ParamData(svOperatorNoName).AsString<>'system' then
  begin
    WorkView.FieldByName('����Ա��').DefaultValue := Context.ParamData(svOperatorNoName).AsString;
    WorkView.Reset;
  end
  else
  begin
    cbbOperTrans.ItemIndex := 0;
  end;
  }
  edtBeginDate.Text := bAccountDate;
  edtEndDate.Text := bAccountDate;
end;

procedure TfaqhAtmRpt.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhAtmRpt.btnQueryClick(Sender: TObject);
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
  if endSign = False then
    Exit;
  endSign := False;
  //if execSQL_SLite(delrptopercash)<>0 then
    //Exit;
  execSQL_SLite(delrptopercash);
  qry := nil;
  try
    qry := TZQuery.Create(nil);
    qry.Connection := dmReportImp.conSLite;
    
    qry.SQL.Clear;
    qry.SQL.Add(beginTrans);
    qry.ExecSQL;
    //if execSQL_SLite(beginTrans)<>0 then
      //Exit;
    tmpData.First;
    while not tmpData.Eof do
    begin
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add(irptAtmRptSql(tmpData));
      qry.ExecSQL;
      tmpData.Next;
    end;
    qry.Close;
    qry.SQL.Clear;
    qry.SQL.Add(commitTrans);
    qry.ExecSQL;
  finally
    qry.Close;
    qry.Destroy;
  end;
  try
    rptReport.LoadFromFile(sPreAppPath+'report\Ȧ��ͳ�Ʊ���.rmf');
    //ztbl1.TableName := 't_rptsysstat';
    if zqry1.Active=True then
      zqry1.Active := False;
    zqry1.Active := True;
    rptReport.Dictionary.Variables.AsString['dateRange'] := 'ͳ�����ڣ�'+strBDate+'��'+strEDate;
    rptReport.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
    rptReport.Dictionary.Variables.AsString['rptOper'] := rptOper;
    rptReport.Dictionary.Variables.AsString['checkOper'] := Context.ParamData(svOperatorNameName).AsString;
    rptReport.DoublePass := True;
    rptReport.Preview := rmprvwP;
    rptReport.ShowReport;
  except
    Context.GetDialogSystem.ShowMessage('��û�а�װ��ӡ�������Ȱ�װ(�����������ӡ��)��');
  end;
  endSign:=True;
end;

initialization
  TUIStdClassFactory.Create('Ȧ���ն�ͳ�Ʊ���',TfaqhAtmRpt);

end.