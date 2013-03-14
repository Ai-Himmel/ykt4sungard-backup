unit UACardUsedInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  UReportMachineTemp, RM_Common, RM_Class, RM_e_main, RM_e_Xls,
  RM_Designer, RM_Dataset, ImgList, RM_Preview, RzPanel, RzButton,
  ZAbstractRODataset, ZAbstractDataset, ZAbstractTable, ZDataset,
  RM_e_Jpeg, RM_e_Graphic, RM_e_bmp, RM_e_htm;

type
  TfaqhCardUsedInfo = class(TfaReportMachineTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    cbbCardType: TWVComboBox;
    cbbOperTrans: TWVComboBox;
    WVComboBox1: TWVComboBox;
    ztbl1: TZTable;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardUsedInfo: TfaqhCardUsedInfo;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils, UCMqhReportImp,
  UrptTbl;
     
{$R *.DFM}

procedure TfaqhCardUsedInfo.Init;
begin
  inherited;
  if Context.ParamData(svOperatorNoName).AsString='system' then
  begin
    cbbOperTrans.ItemIndex := 0;
  end
  else
  begin
    WorkView.FieldByName('操作员号').DefaultValue := Context.ParamData(svOperatorNoName).AsString;
    WorkView.Reset;
  end;
end;

procedure TfaqhCardUsedInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhCardUsedInfo.btnQueryClick(Sender: TObject);
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
  if execSQL_SLite(delrptOperCard)<>0 then
    Exit;
  //execSQL(delrptOperCard);
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
      qry.SQL.Add(irptOperCardSql(tmpData));
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
    rptReport.LoadFromFile(sPreAppPath+'report\当日操作员卡片使用情况表.rmf');
    ztbl1.TableName := 'T_RPTOPERCARD';
    if ztbl1.Active=True then
      ztbl1.Active := False;
    ztbl1.Active := True;

    rptReport.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
    rptReport.Dictionary.Variables.AsString['rptOper'] := rptOper;
    rptReport.Dictionary.Variables.AsString['checkOper'] := Context.ParamData(svOperatorNameName).AsString;
    rptReport.DoublePass := True;
    rptReport.Preview := rmprvwP;
    rptReport.ShowReport;
  except
    Context.GetDialogSystem.ShowMessage('你没有安装打印机，请先安装(可以是虚拟打印机)！');
  end;

end;

initialization
  TUIStdClassFactory.Create('卡片使用情况汇总',TfaqhCardUsedInfo);

end.