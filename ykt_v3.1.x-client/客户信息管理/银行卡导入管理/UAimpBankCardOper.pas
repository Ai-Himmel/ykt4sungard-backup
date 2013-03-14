unit UAimpBankCardOper;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhimpBankCardOper = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label3: TLabel;
    Label6: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label11: TLabel;
    Label13: TLabel;
    WVEdit3: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit9: TWVEdit;
    WVEdit13: TWVEdit;
    cbbQFeeType: TWVComboBox;
    WVComboBox7: TWVComboBox;
    Label1: TLabel;
    edtCustId: TWVEdit;
    Label17: TLabel;
    cbbBankCode: TWVComboBox;
    edtStuempNo: TWVEdit;
    Label21: TLabel;
    Label32: TLabel;
    Label2: TLabel;
    edtOldBankCardNo: TWVEdit;
    Label4: TLabel;
    cbbArea: TWVComboBox;
    Label5: TLabel;
    edtName: TWVEdit;
    btnPatchDel: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    Label10: TLabel;
    edtDelPatchNo: TWVEdit;
    Label7: TLabel;
    edtCustNo: TWVEdit;
    Label12: TLabel;
    WVEdit1: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnPatchDelClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhimpBankCardOper: TfaqhimpBankCardOper;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary,USetParamsTemp,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhimpBankCardOper.Init;
begin
  inherited;
end;

procedure TfaqhimpBankCardOper.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhimpBankCardOper.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;



procedure TfaqhimpBankCardOper.btnQueryClick(Sender: TObject);
begin
  if edtCustNo.Text = '' then
    edtCustNo.Text := '0';
  WorkView.FieldByName('操作标志').Data.SetString('R');
  inherited;
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    btnPatchDel.Enabled := False;
  end
  else
  begin
    btnPatchDel.Enabled := True;
  end;
end;

procedure TfaqhimpBankCardOper.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('A');
  edtCustId.Enabled := False;
  edtStuempNo.Enabled := False;
  cbbBankCode.Enabled := True;
  cbbArea.Enabled := False;
  edtName.Enabled := False;
end;

procedure TfaqhimpBankCardOper.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('U');
  edtCustId.Enabled := False;
  edtStuempNo.Enabled := False;
  //cbbBankCode.Enabled := False;
  cbbArea.Enabled := False;
  edtName.Enabled := False;
end;

procedure TfaqhimpBankCardOper.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('D');
end;

procedure TfaqhimpBankCardOper.btnOKClick(Sender: TObject);
begin
  if (Status = ssAdd) then
  begin
    if (Trim(edtCustId.Text)='') and (Trim(edtStuempNo.Text)='') then
    begin
      Context.GetDialogSystem.ShowMessage('客户号和学工号不能同时为空！');
      Exit;
    end;
  end;
  inherited;
  btnQuery.Click;
end;

procedure TfaqhimpBankCardOper.btnPatchDelClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要删除该批次号的银行卡吗？',PChar(Application.Title),MB_YESNO)=idno then
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

end;

initialization
  TUIStdClassFactory.Create('银行卡绑定管理',TfaqhimpBankCardOper);

end.