unit UAcardTradeQuery;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll;

type
  TfaqhcardTradeQuery = class(TfaqhSimpleQueryTemp)
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
    edtBDate: TWVEdit;
    edtEDate: TWVEdit;
    edtSeriNo: TWVEdit;
    WVEdit6: TWVEdit;
    edtCustNo: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit9: TWVEdit;
    edtCardNo: TWVEdit;
    WVComboBox3: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox4: TWVComboBox;
    btnReadCard: TBitBtn;
    Label13: TLabel;
    edtTBDate: TWVEdit;
    Label14: TLabel;
    edtTEDate: TWVEdit;
    Label15: TLabel;
    cbbNetConn: TWVComboBox;
    Label16: TLabel;
    edtBTime: TWVEdit;
    Label17: TLabel;
    edtEtime: TWVEdit;
    lbl1: TLabel;
    cbb1: TWVComboBox;
    Label18: TLabel;
    WVComboBox5: TWVComboBox;
    procedure btnQueryClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhcardTradeQuery: TfaqhcardTradeQuery;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhcardTradeQuery.Init;
begin
  inherited;
  edtBDate.Text := sysDate;
  edtEDate.Text := sysDate;
end;

procedure TfaqhcardTradeQuery.btnQueryClick(Sender: TObject);
begin
  if Trim(edtSeriNo.Text)='' then
    edtSeriNo.Text := '0';
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  if Trim(edtBDate.Text)<>'' then
    if CheckInputDateFormat(edtBDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('记账开始日期输入不正确，格式：yyyymmdd');
      edtbdate.SetFocus;
      Exit;
    end;
  if Trim(edtEDate.Text)<>'' then
    if CheckInputDateFormat(edtEDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('记账开始日期输入不正确，格式：yyyymmdd');
      edtEDate.SetFocus;
      Exit;
    end;
  if (Trim(edtBDate.Text)<>'') and (Trim(edtEDate.Text)<>'') then

  if Trim(edtBDate.Text)>Trim(edtEDate.Text) then
  begin
    Context.GetDialogSystem.ShowMessage('记账开始日期不能大于结束日期，请重新输入！');
    edtBDate.SetFocus;
    Exit;
  end;

  if Trim(edtTBDate.Text)<>'' then
    if CheckInputDateFormat(edtTBDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('交易开始日期输入不正确，格式：yyyymmdd');
      edtTBDate.SetFocus;
      Exit;
    end;
  if Trim(edtTEDate.Text)<>'' then
    if CheckInputDateFormat(edtTEDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('交易开始日期输入不正确，格式：yyyymmdd');
      edtTEDate.SetFocus;
      Exit;
    end;
  if (Trim(edtBDate.Text)<>'') and (Trim(edtEDate.Text)<>'') then

  if Trim(edttBDate.Text)>Trim(edttEDate.Text) then
  begin
    Context.GetDialogSystem.ShowMessage('交易开始日期不能大于结束日期，请重新输入！');
    edttBDate.SetFocus;
    Exit;
  end;
  if Trim(edtBTime.Text)<>'' then
    if CheckInputTimeFormat(edtBTime.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('开始时间输入不正确，请重新输入！');
      edtBTime.SetFocus;
      Exit;
    end;
  if Trim(edteTime.Text)<>'' then
    if CheckInputTimeFormat(edteTime.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('结束时间输入不正确，请重新输入！');
      edteTime.SetFocus;
      Exit;
    end;
  if Trim(edtBTime.Text)>Trim(edtEtime.Text) then
  begin
    Context.GetDialogSystem.ShowMessage('开始时间不能大于结束时间，请重新输入！');
    edtBTime.SetFocus;
    Exit;
  end;


  WorkView.FieldByName('钱包号').Data.SetInteger(0);
  //WorkView.FieldByName('联机状态').Data.SetInteger(33);
  inherited;

end;

procedure TfaqhcardTradeQuery.btnReadCardClick(Sender: TObject);
var
  cardNo:string;
begin
  edtCardNo.Text:='0';
  cardNo := readCardOneInfo(CARD_NO);
  if (cardNo='') or (cardNo='0') then
  begin
    Context.GetDialogSystem.ShowMessage('读卡查询失败，卡号为零或不存在!');
    Exit;
  end;
  edtCardNo.Text:=cardNo;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('卡交易流水查询',TfaqhcardTradeQuery);

end.