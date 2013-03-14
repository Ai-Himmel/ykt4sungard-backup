unit UAsetSubsidyInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ExtCtrls, UICtrls, 
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhsetSubsidyInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label15: TLabel;
    Label21: TLabel;
	WVEdit2: TWVEdit;
	WVEdit4: TWVEdit;
    edtPatchNo: TWVEdit;
    edtNo: TWVDigitalEdit;
    WVEdit11: TWVEdit;
    WVDigitalEdit12: TWVDigitalEdit;
    WVDigitalEdit15: TWVDigitalEdit;
    WVDigitalEdit21: TWVDigitalEdit;
    cbbType: TWVComboBox;
    edtQCustNo: TWVEdit;
    edtQPatchNo: TWVEdit;
    edtQCardNo: TWVEdit;
    Label1: TLabel;
    WVEdit6: TWVEdit;
    btnPatchDel: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    Label33: TLabel;
    edtDelPatchNo: TWVEdit;
    Label8: TLabel;
    WVComboBox1: TWVComboBox;
    Label13: TLabel;
    edtBDate: TWVEdit;
    Label14: TLabel;
    edtEDate: TWVEdit;
    cbbDept: TWVComboBox;
    lbl1: TLabel;
    Label16: TLabel;
    WVComboBox2: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnPatchDelClick(Sender: TObject);
    procedure btnCheckClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetSubsidyInfo: TfaqhsetSubsidyInfo;

implementation

uses KsFrameworks, KSDataDictionary,KSFrames,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhsetSubsidyInfo.Init;
begin
  inherited;
end;

procedure TfaqhsetSubsidyInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetSubsidyInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetSubsidyInfo.btnQueryClick(Sender: TObject);
begin
  if Trim(edtEDate.Text)<>'' then
    if CheckInputDateFormat(edtEDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('请输入结束日期,格式:yyyymmdd');
      edtEDate.SetFocus;
      Exit;
    end;
  if Trim(edtBDate.Text)<>'' then
    if CheckInputDateFormat(edtBDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('请输入开始日期,格式:yyyymmdd');
      edtBDate.SetFocus;
      Exit;
    end;
  if (Trim(edtEDate.Text)<>'') and (Trim(edtBDate.Text)<>'') then
    if Trim(edtBDate.Text)>Trim(edtEDate.Text) then
      Context.GetDialogSystem.ShowMessage('开始日期不能大于结束日期!');
  if Trim(edtQPatchNo.Text)='' then
    edtQPatchNo.Text := '0';
  if Trim(edtQCustNo.Text)='' then
    edtQCustNo.Text := '0';
  if Trim(edtQCardNo.Text)='' then
    edtQCardNo.Text := '0';
  WorkView.FieldByName('交易类型').Data.SetString('R');
  inherited;
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    btnPatchDel.Enabled := False;
  end
  else
  begin
    btnPatchDel.Enabled :=True;
  end;

end;

procedure TfaqhsetSubsidyInfo.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('交易类型').Data.SetString('U');
  edtPatchNo.ReadOnly := True;
  edtNo.ReadOnly := True;
end;

procedure TfaqhsetSubsidyInfo.btnDeleteClick(Sender: TObject);
var
  tmpdataset : TDataSet;
  impPatchNo:string;
  impNo:Integer;
  status:string;
begin
    inherited;
    WorkView.FieldByName('交易类型').Data.SetString('D');
end;

procedure TfaqhsetSubsidyInfo.btnOKClick(Sender: TObject);
begin
  inherited;
  btnQueryClick(Sender);
end;

procedure TfaqhsetSubsidyInfo.btnPatchDelClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要删除该批次号的补助名单吗？',PChar(Application.Title),MB_YESNO)=idno then
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

procedure TfaqhsetSubsidyInfo.btnCheckClick(Sender: TObject);
begin
  ShowMessage('暂时没有实现该功能！');

end;

initialization
  TUIStdClassFactory.Create('补助信息管理',TfaqhsetSubsidyInfo);

end.