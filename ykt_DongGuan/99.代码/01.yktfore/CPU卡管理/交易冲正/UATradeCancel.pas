unit UATradeCancel;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll,
  RzStatus;

type
  TfaqhTradeCancel = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    edtBeginDate: TWVEdit;
    edtEndDate: TWVEdit;
    edtCustName: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit10: TWVEdit;
    WVEdit11: TWVEdit;
    WVComboBox1: TWVComboBox;
    cbbDept: TWVComboBox;
    WVComboBox2: TWVComboBox;
    Label9: TLabel;
    edtAppSerialNo: TWVEdit;
    btnReadCard: TBitBtn;
    WVRTradeCancel: TWVRequest;
    WVTradeCancel: TWorkView;
    RzStatusPane2: TRzStatusPane;
    Label13: TLabel;
    WVComboBox3: TWVComboBox;
    WVComboBox4: TWVComboBox;
    Label14: TLabel;
    procedure btnQueryClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhTradeCancel: TfaqhTradeCancel;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhTradeCancel.Init;
begin
  inherited;
  edtBeginDate.Text := sysDate;
  edtEndDate.Text := sysDate;
end;

procedure TfaqhTradeCancel.btnQueryClick(Sender: TObject);
begin
  if (Trim(edtBeginDate.Text)='') or (Trim(edtEndDate.Text)='') then
  begin
    Context.GetDialogSystem.ShowMessage('请输入开始日期和结束日期！');
    Exit;
  end;
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
  if Trim(edtCustName.Text)='' then
    edtCustName.Text := '0';
  inherited;

end;

procedure TfaqhTradeCancel.btnReadCardClick(Sender: TObject);
var
  cardNo:string;
begin
  edtAppSerialNo.Text:='';
  try
    cardNo := readCardOneInfo(CF_APPSERIALNO);
  except
    Exit;
  end;
  if (cardNo='') or (cardNo='0') then
  begin
    Context.GetDialogSystem.ShowMessage('读卡查询失败，应用序列号为零或不存在!');
    Exit;
  end;
  edtAppSerialNo.Text:=cardNo;
  btnQuery.Click();
end;

procedure TfaqhTradeCancel.btnPrintClick(Sender: TObject);
var
  sDate,sTime:string;
  accDate,sNo:string;
  tOperId:Integer;
  tMoney:Double;
begin
  if psamTermId='' then
  begin
    Context.GetDialogSystem.ShowMessage('请先打开串口，设置PSAM卡座！');
    Exit;
  end;
  if Application.MessageBox('你确定要冲正选中的交易吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=Idno then
    Exit;
  try
    accDate := Grid.DataSource.DataSet.fieldbyname('sdate3').AsString;
    sNo := Grid.DataSource.DataSet.fieldbyname('scert_no').AsString;
    tOperId := Grid.DataSource.DataSet.fieldbyname('semp').AsInteger;
    tMoney := Grid.DataSource.DataSet.fieldbyname('damt2').AsFloat;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('字段错误-'+e.Message);
      Exit;
    end;
  end;
  sDate := FormatDateTime('yyyymmdd',Date);
  sTime := FormatDateTime('hhmmss',Now);
  WVTradeCancel.FieldByName('交易日期').Data.SetString(sDate);
  WVTradeCancel.FieldByName('交易时间').Data.SetString(sTime);
  WVTradeCancel.FieldByName('sam终端号').Data.SetString(psamTermId);
  WVTradeCancel.FieldByName('记账日期').Data.SetString(accDate);
  WVTradeCancel.FieldByName('交易参考号').Data.SetString(sNo);
  WVTradeCancel.FieldByName('冲正操作员').Data.SetInteger(tOperId);
  WVTradeCancel.FieldByName('冲正金额').Data.SetFloat(tMoney);
  WVRTradeCancel.SendCommand;
  Context.GetDialogSystem.ShowMessage(WVTradeCancel.fieldbyname('返回信息').Data.AsString);
  RzStatusPane2.Caption := WVTradeCancel.fieldbyname('返回信息').Data.AsString;
end;

initialization
  TUIStdClassFactory.Create('交易冲正',TfaqhTradeCancel);

end.