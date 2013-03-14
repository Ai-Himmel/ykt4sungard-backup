unit UAaccountTradeQuery;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,UtCardDll;

type
  TfaqhaccountTradeQuery = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    edtJbDate: TWVEdit;
    edtJEDate: TWVEdit;
    edtTBDate: TWVEdit;
    edtTEdate: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit7: TWVEdit;
    edtSeriId: TWVEdit;
    WVEdit11: TWVEdit;
    edtBusiId: TWVEdit;
    WVEdit13: TWVEdit;
    edtCardNo: TWVEdit;
    WVComboBox3: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox4: TWVComboBox;
    edtStationNo: TWVEdit;
    btnReadCard: TBitBtn;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhaccountTradeQuery: TfaqhaccountTradeQuery;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhaccountTradeQuery.Init;
begin
  inherited;
  edtJbDate.Text := sysDate;
  edtJEDate.Text := sysDate;
end;

procedure TfaqhaccountTradeQuery.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



procedure TfaqhaccountTradeQuery.btnQueryClick(Sender: TObject);
begin
  if edtSeriId.Text='' then
    edtSeriId.Text:='0';
  if edtBusiId.Text='' then
    edtBusiId.Text:='0';
  if edtCardNo.Text='' then
    edtCardNo.Text:='0';
  if edtStationNo.Text='' then
    edtStationNo.Text:='0';
  if Trim(edtJbDate.Text)<>'' then
    if CheckInputDateFormat(edtJbDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('记账开始日期输入不正确，格式：yyyymmdd');
      edtJbDate.SetFocus;
      Exit;
    end;
  if Trim(edtJEDate.Text)<>'' then
    if CheckInputDateFormat(edtJEDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('记账结束日期输入不正确，格式：yyyymmdd');
      edtJEDate.SetFocus;
      Exit;
    end;
  if (Trim(edtJbDate.Text)<>'') and (Trim(edtJEDate.Text)<>'') then
    if Trim(edtJbDate.Text)>Trim(edtJEDate.Text) then
    begin
      Context.GetDialogSystem.ShowMessage('记账开始日期不能大于记账结束日期，请重新输入！');
      edtJbDate.SetFocus;
      Exit;
    end;
  if Trim(edtTBDate.Text)<>'' then
    if CheckInputDateFormat(edtTBDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('交易开始日期输入不正确，格式：yyyymmdd');
      edtTBDate.SetFocus;
      Exit;
    end;

  if Trim(edtTEdate.Text)<>'' then
    if CheckInputDateFormat(edtTEdate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('交易结束日期输入不正确，格式：yyyymmdd');
      edtTEdate.SetFocus;
      Exit;
    end;
  if (Trim(edtTEdate.Text)<>'') and (Trim(edtTEdate.Text)<>'') then
    if Trim(edtTBDate.Text)>Trim(edtTEdate.Text) then
    begin
      Context.GetDialogSystem.ShowMessage('交易开始日期不能大于交易结束日期，请重新输入！');
      edtTBDate.SetFocus;
      Exit;
    end;
  inherited;

end;

procedure TfaqhaccountTradeQuery.btnReadCardClick(Sender: TObject);
begin
  edtCardNo.Text:=readCardNo;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('帐户交易明细查询',TfaqhaccountTradeQuery);

end.