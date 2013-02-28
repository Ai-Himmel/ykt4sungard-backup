unit UAappDeal;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll;

type
  TfaqhappDeal = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    edtAppDate: TWVEdit;
    edtDealDate: TWVEdit;
    edtOrderNo: TWVEdit;
    edtCardNo: TWVEdit;
    WVEdit6: TWVEdit;
    edtAppSerialNo: TWVEdit;
    cbbIDType: TWVComboBox;
    WVComboBox1: TWVComboBox;
    btnReadQ: TBitBtn;
    WVCancelApp: TWorkView;
    WVRCancelApp: TWVRequest;
    procedure btnQueryClick(Sender: TObject);
    procedure btnReadQClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhappDeal: TfaqhappDeal;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhappDeal.Init;
begin
  inherited;
  {
  WorkView.FieldByName('操作标志').DefaultValue := '';
  WorkView.FieldByName('申请日期').DefaultValue := '';
  WorkView.FieldByName('处理日期').DefaultValue := '';
  WorkView.FieldByName('申请单号').DefaultValue := 0;
  WorkView.FieldByName('卡号').DefaultValue := 0;
  WorkView.FieldByName('证件号码').DefaultValue := '';
  WorkView.FieldByName('应用序列号').DefaultValue := '';
  WorkView.FieldByName('申请类型').DefaultValue := 0;
  WorkView.FieldByName('申请状态').DefaultValue := 0;
  WorkView.Reset;
  }
end;

procedure TfaqhappDeal.btnQueryClick(Sender: TObject);
begin
  if Trim(edtAppDate.Text)<>'' then
    if CheckInputDateFormat(edtAppDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('申请日期输入不正确，格式：yyyymmdd');
      edtAppDate.SetFocus;
      Exit;
    end;
  if Trim(edtDealDate.Text)<>'' then
    if CheckInputDateFormat(edtDealDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('处理日期输入不正确，格式：yyyymmdd');
      edtDealDate.SetFocus;
      Exit;
    end;
  if edtCardNo.Text = '' then
    edtCardNo.Text := '0';
  if edtOrderNo.Text = '' then
    edtOrderNo.Text := '0';
  WorkView.FieldByName('操作标志').Data.SetString('R');
  inherited;

end;

procedure TfaqhappDeal.btnReadQClick(Sender: TObject);
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

procedure TfaqhappDeal.btnPrintClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要取消该申请单吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WVCancelApp.FieldByName('操作标志').Data.SetString('C');
  WVCancelApp.FieldByName('申请单号').Data.SetInteger(Grid.DataSource.DataSet.fieldbyname('lvol1').AsInteger);
  WVRCancelApp.SendCommand;
  if WVCancelApp.FieldByName('返回码').Data.AsString='0' then
    Context.GetDialogSystem.ShowMessage('取消申请单成功！')
  else
    Context.GetDialogSystem.ShowMessage(WVCancelApp.FieldByName('返回信息').Data.AsString);
end;

initialization
  TUIStdClassFactory.Create('申请单处理',TfaqhappDeal);

end.