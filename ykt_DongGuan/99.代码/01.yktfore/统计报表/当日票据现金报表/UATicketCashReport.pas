unit UATicketCashReport;

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
  TfaqhTicketCashReport = class(TfaReportMachineTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    cbbOperTrans: TWVComboBox;
    cbbNetInfo: TWVComboBox;
    zqry1: TZQuery;
    Label3: TLabel;
    WVComboBox1: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
    endSign:Boolean;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhTicketCashReport: TfaqhTicketCashReport;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils, UCMqhReportImp,
  UrptTbl;
     
{$R *.DFM}

procedure TfaqhTicketCashReport.Init;
begin
  inherited;
  endSign := True;
  if Context.ParamData(svOperatorNoName).AsString='system' then
  begin
    cbbOperTrans.ItemIndex := 0;
  end
  else
  begin
    WorkView.FieldByName('操作员号').DefaultValue := Context.ParamData(svOperatorNoName).AsString;
    WorkView.Reset;
  end;
  cbbNetInfo.ItemIndex := 0;
end;

procedure TfaqhTicketCashReport.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhTicketCashReport.btnQueryClick(Sender: TObject);
var
  tmpData:TDataSet;
  qry:TZQuery;
begin
  inherited;
  tmpData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  if tmpData.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('数据统计表没有相关记录，请重新指定条件');
    Exit;
  end;

  if endSign = False then
    Exit;
  endSign := False;
  if execSQL_SLite(delrptopercash)<>0 then
    Exit;
  //execSQL(delrptopercash);
  qry := nil;
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
      qry.SQL.Add(irptOperCashSql(tmpData));
      qry.ExecSQL;
      tmpData.Next;
    end;
    if execSQL_SLite(commitTrans)<>0 then
      Exit;
  finally
    qry.Close;
    qry.Destroy;
  end;
  try
    rptReport.LoadFromFile(sPreAppPath+'report\当日操作员票据现金报表.rmf');
    if zqry1.Active=True then
      zqry1.Active := False;
    zqry1.Active := True;
    rptReport.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
    rptReport.Dictionary.Variables.AsString['rptOper'] := rptOper;
    rptReport.Dictionary.Variables.AsString['checkOper'] := Context.ParamData(svOperatorNameName).AsString;
    rptReport.DoublePass := True;
    rptReport.Preview := rmprvwP;
    rptReport.ShowReport;
  except
    Context.GetDialogSystem.ShowMessage('你没有安装打印机，请先安装(可以是虚拟打印机)！');
  end;
  endSign := True;
end;

initialization
  TUIStdClassFactory.Create('票据现金报表',TfaqhTicketCashReport);

end.