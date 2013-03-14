unit UAimpBankCardOperLink;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox, RzPanel;

type
  TfaqhimpBankCardOperLink = class(TfaqhSetParamsTemp)
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
    edtStuempNo: TWVEdit;
    Label21: TLabel;
    Label32: TLabel;
    Label2: TLabel;
    edtOldBankCardNo: TWVEdit;
    btnPatchDel: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    Label10: TLabel;
    edtDelPatchNo: TWVEdit;
    Label7: TLabel;
    edtCustNo: TWVEdit;
    Label12: TLabel;
    WVEdit1: TWVEdit;
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
  faqhimpBankCardOperLink: TfaqhimpBankCardOperLink;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary,USetParamsTemp,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhimpBankCardOperLink.Init;
begin
  inherited;
end;

procedure TfaqhimpBankCardOperLink.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;



procedure TfaqhimpBankCardOperLink.btnQueryClick(Sender: TObject);
begin
  if edtCustNo.Text = '' then
    edtCustNo.Text := '0';
  WorkView.FieldByName('������־').Data.SetString('R');
  inherited;
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    btnPatchDel.Enabled := False;
  end
  else
  begin
    btnPatchDel.Enabled := True;
  end;
end;

procedure TfaqhimpBankCardOperLink.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('A');
  edtCustId.Enabled := False;
end;

procedure TfaqhimpBankCardOperLink.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('U');
  edtCustId.Enabled := False;
end;

procedure TfaqhimpBankCardOperLink.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('D');
end;

procedure TfaqhimpBankCardOperLink.btnOKClick(Sender: TObject);
begin
  if (Status = ssAdd) then
  begin
    if (Trim(edtCustId.Text)='') and (Trim(edtStuempNo.Text)='') then
    begin
      Context.GetDialogSystem.ShowMessage('�ͻ��ź�ѧ���Ų���ͬʱΪ�գ�');
      Exit;
    end;
  end;
  inherited;
  btnQuery.Click;
end;

procedure TfaqhimpBankCardOperLink.btnPatchDelClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫɾ�������κŵ����п���',PChar(Application.Title),MB_YESNO)=idno then
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

end;

initialization
  TUIStdClassFactory.Create('���п������󶨹���',TfaqhimpBankCardOperLink);

end.