unit UAfillBusiSaveMoney;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, EditExts, UIncrementComboBox,
  RzLabel, RzEdit, RzStatus, RzPanel, Buttons;

type
  TfaqhfillBusiSaveMoney = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    grp1: TGroupBox;
    edtSveMoney: TWVDigitalEdit;
    lbl1: TRzLabel;
    RzLabel1: TRzLabel;
    grpSuccInfo: TGroupBox;
    RzLabel2: TRzLabel;
    RzLabel3: TRzLabel;
    RzLabel6: TRzLabel;
    RzLabel8: TRzLabel;
    RzLabel10: TRzLabel;
    RzLabel12: TRzLabel;
    RzLabel14: TRzLabel;
    RzLabel16: TRzLabel;
    lblBl: TRzLabel;
    RzLabel18: TRzLabel;
    lblAccMoney: TRzLabel;
    WorkView1: TWorkView;
    QueryRequest: TWVRequest;
    lbl2: TLabel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    edtSeriId: TRzEdit;
    edtBusiId: TRzEdit;
    edtBusiName: TRzEdit;
    edtDate: TRzEdit;
    edtTc: TRzEdit;
    edtAccMoney: TRzEdit;
    edtSaveMoney: TRzEdit;
    cbbBusiName: TWVComboBox;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    btnSaveMoney: TImageButton;
    RzLabel4: TRzLabel;
    cbbType: TWVComboBox;
    RzLabel5: TRzLabel;
    edtTicketNo: TRzEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure cbbBusiNameChange(Sender: TObject);
    procedure btnSaveMoneyClick(Sender: TObject);
    procedure cbbTypeChange(Sender: TObject);
  private

    { Private declarations }
    procedure clearSuccInfo;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhfillBusiSaveMoney: TfaqhfillBusiSaveMoney;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhfillBusiSaveMoney.Init;
begin
  inherited;
  {
  WorkView1.FieldByName('查询.商户号').DefaultValue := 0;
  WorkView1.FieldByName('查询.商户名称').DefaultValue := '';
  WorkView1.FieldByName('查询.商户负责人名称').DefaultValue := '';
  WorkView1.FieldByName('查询.商户证件类型').DefaultValue := 0;
  WorkView1.FieldByName('查询.商户提成比率').DefaultValue := 0.00;
  WorkView1.FieldByName('查询.商户证件号码').DefaultValue := '';
  WorkView1.Reset;
  WorkView.FieldByName('商户号').DefaultValue := 0;
  WorkView.FieldByName('存款金额').DefaultValue := 0.00;
  WorkView.Reset;
  }
  cbbBusiName.ItemIndex := -1;
  //btnSaveMoney.Caption := '商户存款';
end;

procedure TfaqhfillBusiSaveMoney.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhfillBusiSaveMoney.cbbBusiNameChange(Sender: TObject);
var
  busiId:string;
  tmpDataSet:TDataSet;
begin
  //inherited;
  clearSuccInfo;
  lblBl.Caption := '';
  lblAccMoney.Caption := '';
  busiId := Copy(cbbBusiName.Text,1,Pos('-',cbbBusiName.Text)-1);

  WorkView1.FieldByName('查询.商户号').Data.SetInteger(StrToInt(busiId));
  WorkView1.FieldByName('操作标志').Data.SetString('R');
  //WorkView1.FieldByName('查询.商户提成比率').Data.SetFloat(0);
  QueryRequest.SendCommand;
  try
    tmpDataSet := TDataSet(WorkView1.FieldByName('查询结果集').Data.AsObject);
    lblBl.Caption := FloatToStr(tmpDataSet.fieldbyname('drate1').AsFloat);
    lblAccMoney.Caption := tmpDataSet.fieldbyname('damt0').AsString;
  except
  end;
end;

procedure TfaqhfillBusiSaveMoney.clearSuccInfo;
var
  i:Integer;
begin
  for i := 0 to grpSuccInfo.ControlCount-1 do
  begin
    if grpSuccInfo.Controls[i] is TRzEdit then
      TRzEdit(grpSuccInfo.Controls[i]).Text := '';
  end;
end;

procedure TfaqhfillBusiSaveMoney.btnSaveMoneyClick(Sender: TObject);
var
  fillType:string;
begin
  //inherited;
  if (cbbBusiName.Text='')or(cbbBusiName.Text='-') then
  begin
    Context.GetDialogSystem.ShowMessage('请选择要充值的商户！');
    Exit;
  end;
  fillType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
  if (fillType='')or (fillType='-') then
  begin
    Context.GetDialogSystem.ShowMessage('请选择充值类型！');
    cbbType.SetFocus;
    exit;
  end;
  if StrToInt(fillType)<>1 then
    if Trim(edtTicketNo.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('请输入票据号码！');
      edtTicketNo.SetFocus;
      Exit;
    end;
  if Application.MessageBox('你确定要为该充值商户存款吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  WorkView.FieldByName('充值类型').Data.SetInteger(StrToInt(fillType));
  WorkView.FieldByName('票据号码').Data.SetString(edtTicketNo.Text);
  MainRequest.SendCommand;
  if WorkView.FieldByName('返回码').Data.AsInteger=0 then
  begin
    Context.GetDialogSystem.ShowMessage('该充值商户充值成功！');
    edtSeriId.Text := WorkView.fieldbyname('后台流水号').Data.AsString;
    edtBusiId.Text := WorkView.fieldbyname('商户号').Data.AsString;
    edtBusiName.Text := WorkView.fieldbyname('商户名称').Data.AsString;
    edtDate.Text := WorkView.fieldbyname('交易日期').Data.AsString;
    edtSaveMoney.Text := WorkView.fieldbyname('存款金额').Data.AsString;
    edtTc.Text := WorkView.fieldbyname('提成金额').Data.AsString;
    edtAccMoney.Text := WorkView.fieldbyname('帐户余额').Data.AsString;
    RzStatusPane1.Caption := WorkView.fieldbyname('返回信息').Data.AsString;
  end;
end;

procedure TfaqhfillBusiSaveMoney.cbbTypeChange(Sender: TObject);
begin
  edtTicketNo.Text:='';
  if (cbbType.ItemIndex = 0) then
    edtTicketNo.Enabled := False
  else
    edtTicketNo.Enabled := True;

end;

initialization
  TUIStdClassFactory.Create('充值商户存款',TfaqhfillBusiSaveMoney);

end.