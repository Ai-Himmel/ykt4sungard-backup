unit UAposSerialManager;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhposSerialManager = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label19: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label22: TLabel;
    Label23: TLabel;
    Label24: TLabel;
    Label25: TLabel;
    Label26: TLabel;
    Label27: TLabel;
    edtQDate: TWVEdit;
	WVEdit3: TWVEdit;
    edtDate: TWVEdit;
    edtTime: TWVEdit;
    WVDigitalEdit23: TWVDigitalEdit;
    WVDigitalEdit24: TWVDigitalEdit;
    WVDigitalEdit25: TWVDigitalEdit;
    WVDigitalEdit26: TWVDigitalEdit;
    Label2: TLabel;
    WVEdit2: TWVEdit;
    Label9: TLabel;
    Label10: TLabel;
    WVEdit4: TWVEdit;
    WVComboBox6: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox3: TWVComboBox;
    WVComboBox4: TWVComboBox;
    WVCheck: TWorkView;
    WVRCheck: TWVRequest;
    btnCheck: TBitBtn;
    edtBusiNo: TWVEdit;
    edtSeriNo: TWVEdit;
    edtQCardNo: TWVEdit;
    edtCardNo: TWVEdit;
    edtTradeNum: TWVEdit;
    edtPackageNo: TWVEdit;
    edtDevNo: TWVEdit;
    edtBusiCardNo: TWVEdit;
    lbl1: TLabel;
    btnPatchDel: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    Label33: TLabel;
    edtDelPatchNo: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnChangeClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnCheckClick(Sender: TObject);
    procedure btnPatchDelClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhposSerialManager: TfaqhposSerialManager;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhposSerialManager.Init;
begin
  inherited;
end;

procedure TfaqhposSerialManager.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhposSerialManager.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhposSerialManager.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('U');
  edtTradeNum.Enabled := False;
  edtCardNo.Enabled := False;
  edtPackageNo.Enabled := False;
end;

procedure TfaqhposSerialManager.btnQueryClick(Sender: TObject);
begin
  if Trim(edtBusiNo.Text)='' then
    edtBusiNo.Text := '0';
  if Trim(edtSeriNo.Text)='' then
    edtSeriNo.Text := '0';
  if Trim(edtQCardNo.Text)='' then
    edtQCardNo.Text := '0';
  if Trim(edtQDate.Text)<>'' then
    if CheckInputDateFormat(edtQDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('日期输入有误，格式yyyymmdd');
      edtQDate.SetFocus;
      Exit;
    end;
  WorkView.FieldByName('操作标志').Data.SetString('R');
  inherited;
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    btnCheck.Enabled := False;
    btnPatchDel.Enabled := False;
  end
  else
  begin
    btnCheck.Enabled := True;
    btnPatchDel.Enabled := true;
  end;
end;

procedure TfaqhposSerialManager.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('A');
  edtTradeNum.Enabled := True;
  edtCardNo.Enabled := True;
  edtPackageNo.Enabled := True;

end;

procedure TfaqhposSerialManager.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('D');
end;

procedure TfaqhposSerialManager.btnOKClick(Sender: TObject);
begin
  if Trim(edtCardNo.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('卡号不能为空，请输入！');
    edtCardNo.SetFocus;
    Exit;
  end;
  if Trim(edtTradeNum.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('卡交易次数不能为空，请输入！');
    edtTradeNum.SetFocus;
    Exit;
  end;
  if Trim(edtPackageNo.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('钱包号不能为空，请输入！');
    edtPackageNo.SetFocus;
    Exit;
  end;
  if Trim(edtDevNo.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('设备流水号不能为空，请输入！');
    edtDevNo.SetFocus;
    Exit;
  end;
  if Trim(edtBusiCardNo.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('商户卡号不能为空，请输入！');
    edtBusiCardNo.SetFocus;
    Exit;
  end;
  if Trim(edtDate.Text)<>'' then
    if CheckInputDateFormat(edtDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('日期输入有误，格式yyyymmdd');
      edtDate.SetFocus;
      Exit;
    end;
  if Trim(edtTime.Text)<>'' then
    if CheckInputTimeFormat(edtTime.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('时间输入有误，格式hhmmss');
      edtTime.SetFocus;
      Exit;
    end;
  inherited;
  btnQueryClick(Sender);
end;

procedure TfaqhposSerialManager.btnCheckClick(Sender: TObject);
var
  cardNo:Integer;
  tradeNo:Integer;
  pkgNo:Integer;
  patchNo:string;
  tmpDataset:TDataSet;
begin
  if Application.MessageBox('你确定要审核POS流水吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  tmpDataset := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  tmpDataset.First;
  while not tmpDataset.Eof do
  begin
    cardNo := tmpDataset.fieldbyname('lvol0').AsInteger;
    tradeNo := tmpDataset.fieldbyname('lvol6').AsInteger;
    pkgNo := tmpDataset.fieldbyname('lvol3').AsInteger;
    patchNo := tmpDataset.fieldbyname('scust_limit').AsString;
    WVCheck.FieldByName('卡号').Data.SetInteger(cardNo);
    WVCheck.FieldByName('交易次数').Data.SetInteger(tradeNo);
    WVCheck.FieldByName('钱包号').Data.SetInteger(pkgNo);
    WVCheck.FieldByName('批次号').Data.SetString(patchNo);
    WVRCheck.SendCommand;
    Sleep(100);
    tmpDataset.Next;
  end;
  Context.GetDialogSystem.ShowMessage('Pos流水审核完成！');
end;

procedure TfaqhposSerialManager.btnPatchDelClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要删除该批次号的POS流水吗？',PChar(Application.Title),MB_YESNO)=idno then
    Exit;
  if edtDelPatchNo.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('请输入要批量删除的批次号！');
    Exit;
  end;
  WorkView1.FieldByName('操作标志').Data.SetString('D');
  WorkView1.FieldByName('批量标志').Data.SetInteger(1);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('返回码').Data.AsInteger=0 then
    edtDelPatchNo.Text :='';
  Context.GetDialogSystem.ShowMessage(WorkView1.fieldbyname('返回信息').Data.AsString);
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('POS流水管理',TfaqhposSerialManager);

end.