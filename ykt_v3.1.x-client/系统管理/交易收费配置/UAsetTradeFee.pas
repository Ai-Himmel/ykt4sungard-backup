unit UAsetTradeFee;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhsetTradeFee = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    lblBit: TLabel;
    edtMoney: TWVDigitalEdit;
    WVComboBox4: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox3: TWVComboBox;
    WVComboBox5: TWVComboBox;
    cbbTradeCode: TWVComboBox;
    cbbFeeType: TWVComboBox;
    cbbCardType: TWVComboBox;
    cbbFee: TWVComboBox;
    cbbTradeType: TWVComboBox;
    Label1: TLabel;
    WVComboBox11: TWVComboBox;
    lbl1: TLabel;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure cbbFeeTypeChange(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure cbbTradeTypeChange(Sender: TObject);
  private

    { Private declarations }
    function checkValue(cbb:TWVComboBox): Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetTradeFee: TfaqhsetTradeFee;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhsetTradeFee.Init;
begin
  inherited;

end;

procedure TfaqhsetTradeFee.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetTradeFee.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetTradeFee.cbbFeeTypeChange(Sender: TObject);
var
  feeType:string;
begin
  feeType := Copy(cbbFeeType.Text,1,Pos('-',cbbFeeType.Text)-1);
  if feeType = '1' then
    lblBit.Caption := '收费金额'
  else
    lblBit.Caption := '收费比率';
    edtMoney.Text := '0';
end;

procedure TfaqhsetTradeFee.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('操作标志').Data.SetString('R');
  inherited;

end;

procedure TfaqhsetTradeFee.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('A');
  cbbTradeCode.Enabled := True;
  cbbCardType.Enabled := True;
  cbbFee.Enabled := True;
  cbbTradeType.Enabled := True;
  cbbTradeTypeChange(Sender);
end;

procedure TfaqhsetTradeFee.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('U');
  cbbTradeCode.Enabled := false;
  cbbCardType.Enabled := False;
  cbbFee.Enabled := False;
  cbbTradeType.Enabled := False;
end;

procedure TfaqhsetTradeFee.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('D');

end;

procedure TfaqhsetTradeFee.btnOKClick(Sender: TObject);
begin
  if checkValue(cbbTradeCode)<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('请选择交易码！');
    cbbTradeCode.SetFocus;
    Exit;
  end;
  if checkValue(cbbCardType)<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('请选择卡类型！');
    cbbCardType.SetFocus;
    Exit;
  end;
  if checkValue(cbbTradeType)<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('请选择交易类型！');
    cbbTradeType.SetFocus;
    Exit;
  end;
  if checkValue(cbbFee)<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('请选择收费类别！');
    cbbFee.SetFocus;
    Exit;
  end;
  {
  if checkValue(cbbFeeType)<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('请选择收费方式！');
    cbbFeeType.SetFocus;
    Exit;
  end;
  }
  inherited;
  btnQuery.Click;
end;

function TfaqhsetTradeFee.checkValue(cbb: TWVComboBox): Integer;
var
  str:string;
begin
  str := Copy(cbb.Text,1,Pos('-',cbb.Text)-1);
  if (str='') or (str='-') then
    Result := -1
  else
    Result := 0;
end;

procedure TfaqhsetTradeFee.cbbTradeTypeChange(Sender: TObject);
var
  ss:string;
begin
  inherited;
  ss:=Copy(cbbTradeType.Text,1,Pos('-',cbbTradeType.Text)-1);
  if ss='99' then
  begin
    cbbFeeType.ItemIndex := 0;
    edtMoney.Text := '0';
    cbbFeeType.Enabled := False;
    edtMoney.Enabled := False;

  end
  else
  begin
    cbbFeeType.Enabled := True;
    edtMoney.Enabled := True;
  end;
end;

initialization
  TUIStdClassFactory.Create('交易收费配置',TfaqhsetTradeFee);

end.