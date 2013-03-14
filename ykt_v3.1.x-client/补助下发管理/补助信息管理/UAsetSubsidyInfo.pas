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
      Context.GetDialogSystem.ShowMessage('�������������,��ʽ:yyyymmdd');
      edtEDate.SetFocus;
      Exit;
    end;
  if Trim(edtBDate.Text)<>'' then
    if CheckInputDateFormat(edtBDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����뿪ʼ����,��ʽ:yyyymmdd');
      edtBDate.SetFocus;
      Exit;
    end;
  if (Trim(edtEDate.Text)<>'') and (Trim(edtBDate.Text)<>'') then
    if Trim(edtBDate.Text)>Trim(edtEDate.Text) then
      Context.GetDialogSystem.ShowMessage('��ʼ���ڲ��ܴ��ڽ�������!');
  if Trim(edtQPatchNo.Text)='' then
    edtQPatchNo.Text := '0';
  if Trim(edtQCustNo.Text)='' then
    edtQCustNo.Text := '0';
  if Trim(edtQCardNo.Text)='' then
    edtQCardNo.Text := '0';
  WorkView.FieldByName('��������').Data.SetString('R');
  inherited;
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
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
  WorkView.FieldByName('��������').Data.SetString('U');
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
    WorkView.FieldByName('��������').Data.SetString('D');
end;

procedure TfaqhsetSubsidyInfo.btnOKClick(Sender: TObject);
begin
  inherited;
  btnQueryClick(Sender);
end;

procedure TfaqhsetSubsidyInfo.btnPatchDelClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫɾ�������κŵĲ���������',PChar(Application.Title),MB_YESNO)=idno then
    Exit;
  if edtDelPatchNo.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('������Ҫ����ɾ�������κţ�');
    Exit;
  end;
  WorkView1.FieldByName('������־').Data.SetString('D');
  WorkView1.FieldByName('������־').Data.SetInteger(1);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('������').Data.AsInteger=0 then
    edtDelPatchNo.Text :='';
  Context.GetDialogSystem.ShowMessage(WorkView1.fieldbyname('������Ϣ').Data.AsString);
  btnQuery.Click;

end;

procedure TfaqhsetSubsidyInfo.btnCheckClick(Sender: TObject);
begin
  ShowMessage('��ʱû��ʵ�ָù��ܣ�');

end;

initialization
  TUIStdClassFactory.Create('������Ϣ����',TfaqhsetSubsidyInfo);

end.