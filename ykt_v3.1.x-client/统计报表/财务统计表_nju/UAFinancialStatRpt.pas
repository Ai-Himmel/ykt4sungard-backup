unit UAFinancialStatRpt;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ComCtrls, RzTreeVw, RzGrids,
  RzCmboBx, RzPanel, RzSplit, UIncrementComboBox,
  Buttons, UReportMachineTemp, RM_Common, RM_Class, RM_e_main, RM_e_Xls,
  RM_Designer, RM_Dataset, ImgList, RM_Preview, RzButton,
  ZAbstractRODataset, ZAbstractDataset, ZAbstractTable, ZDataset, RM_e_htm,
  RM_e_Graphic, RM_e_Jpeg, RM_e_bmp, RM_GridReport;
type
  PMyRec = ^TMyRec;
  TMyRec = record
    id: Integer;
    name: string;
end;
type
  TfaqhFinancialStatRpt = class(TfaReportMachineTemp)
    Panel1: TPanel;
    lblBusiName: TLabel;
    WVLabel1: TWVLabel;
    edtBeginDate: TWVEdit;
    WVLabel2: TWVLabel;
    edtEndDate: TWVEdit;
    ztbl1: TZTable;
    rmgrdrprt1: TRMGridReport;
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
  faqhFinancialStatRpt: TfaqhFinancialStatRpt;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSClientConsts,SmartCardCommon,
  UCMqhReportImp, UrptTbl;

{$R *.DFM}

procedure TfaqhFinancialStatRpt.Init;
begin
  inherited;
  edtBeginDate.Text := bAccountDate;
  edtEndDate.Text := bAccountDate;
end;

procedure TfaqhFinancialStatRpt.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhFinancialStatRpt.btnQueryClick(Sender: TObject);
var
  tmpData:TDataSet;
  qry:TZQuery;
begin
  if Trim(edtEndDate.Text)<>'' then
    if CheckInputDateFormat(edtEndDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('结束日期输入不正确，格式：yyyymmdd');
      edtEndDate.SetFocus;
      Exit;
    end;
  if Trim(edtBeginDate.Text)<>'' then
    if CheckInputDateFormat(edtBeginDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('开始日期输入不正确，格式：yyyymmdd');
      edtBeginDate.SetFocus;
      Exit;
    end;
  if (Trim(edtEndDate.Text)<>'') and (Trim(edtBeginDate.Text)<>'') then
    if Trim(edtBeginDate.Text)>Trim(edtEndDate.Text) then
      Context.GetDialogSystem.ShowMessage('开始日期不能大于结束日期！');
  inherited;
  strBDate := edtBeginDate.Text;
  strEDate := edtEndDate.Text;
  
  tmpData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  if tmpData.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('数据统计表没有相关记录，请重新指定条件');
    Exit;
  end;
  {
  execSQL(delrptsubjbal);
  qry := nil;
  try
    qry := TZQuery.Create(nil);
    qry.Connection := dmReportImp.conFB;
    tmpData.First;
    while not tmpData.Eof do
    begin
      if Trim(tmpData.fieldbyname('sdate3').AsString)='' then
      begin
        tmpData.Next;
        Continue;
      end;
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add(irptsubjbalSql(tmpData));
      qry.ExecSQL;
      tmpData.Next;
    end;
  finally
    qry.Close;
    qry.Destroy;
  end;
  }
  try
    rmgrdrprt1.LoadFromFile(sPreAppPath+'report\财务统计表_nju.rls');
    {
    ztbl1.TableName := 'T_RPTSUBJBAL';
    if ztbl1.Active=True then
      ztbl1.Active := False;
    ztbl1.Active := True;
    }
    rmgrdrprt1.Dictionary.Variables.AsString['statDate'] := '统计日期：'+strBDate+'至'+strEDate;
    rmgrdrprt1.Dictionary.Variables.AsString['userDept'] := '使用单位：'+rptTitle;
    rmgrdrprt1.Dictionary.Variables.AsString['c1'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c2'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c3'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c4'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c5'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c6'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c7'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c8'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c9'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c10'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c11'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c12'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c13'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c14'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c15'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c16'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c17'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c18'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c19'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c20'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c21'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c22'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c23'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c24'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c25'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c26'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c27'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c28'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c29'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c30'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c31'] := '12345';
    rmgrdrprt1.Dictionary.Variables.AsString['c32'] := '12345';

    rmgrdrprt1.Dictionary.Variables.AsString['f1'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f2'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f3'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f4'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f5'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f6'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f7'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f8'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f9'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f10'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f11'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f12'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f13'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f14'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f15'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f16'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f17'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f18'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f19'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f20'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f21'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f22'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f23'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f24'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f25'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f26'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f27'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f28'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f29'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f30'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f31'] := '67890';
    rmgrdrprt1.Dictionary.Variables.AsString['f32'] := '67890';

    rmgrdrprt1.Dictionary.Variables.AsString['bBal'] := '期初余额：'+'000';
    rmgrdrprt1.Dictionary.Variables.AsString['eBal'] := '期末余额：'+'000';
    rmgrdrprt1.Dictionary.Variables.AsString['factBal'] := '实际余额：'+'000';
    rmgrdrprt1.Dictionary.Variables.AsString['balance'] := '平衡关系：'+'平衡';
    rmgrdrprt1.Dictionary.Variables.AsString['totNum'] := '在册人数：'+'000';
    rmgrdrprt1.Dictionary.Variables.AsString['useNum'] := '使用人数：'+'000';
    rmgrdrprt1.Dictionary.Variables.AsString['useRate'] := '使用率：'+'000';
    rmgrdrprt1.Dictionary.Variables.AsString['payMoney'] := '应交现金：'+'000';
    rmgrdrprt1.Dictionary.Variables.AsString['oper'] := '制表人：'+'111';
    rmgrdrprt1.Dictionary.Variables.AsString['makeRptDate'] := '制表时间：'+formatdatetime('yyyymmdd hh:mm:ss',Now);

    rmgrdrprt1.DoublePass := True;
    rmgrdrprt1.Preview := rmprvwP;
    rmgrdrprt1.ShowReport;
  except
    Context.GetDialogSystem.ShowMessage('你没有安装打印机，请先安装(可以是虚拟打印机)！');
  end;
end;

initialization
  TUIStdClassFactory.Create('财务统计表',TfaqhFinancialStatRpt);

end.