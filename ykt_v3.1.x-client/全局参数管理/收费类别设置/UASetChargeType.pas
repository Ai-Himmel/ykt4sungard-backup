unit UASetChargeType;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, UIncrementComboBox,
  RzListVw, Buttons;

type
  TfaqhSetChargeType = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label5: TLabel;
    edtName: TWVEdit;
    chkif: TRzCheckBox;
    Label1: TLabel;
    WVEdit1: TWVEdit;
    Label2: TLabel;
    Label4: TLabel;
    edtId: TWVDigitalEdit;
    cbbfeetype: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure chkifClick(Sender: TObject);
  private

    { Private declarations }
    ifFee:string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetChargeType: TfaqhSetChargeType;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhSetChargeType.Init;
begin
  inherited;
  {
  WorkView.FieldByName('����־').DefaultValue := 0;
  WorkView.Reset;
  }
end;

procedure TfaqhSetChargeType.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  //btnQuery.Enabled:=Valid;
end;


procedure TfaqhSetChargeType.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhSetChargeType.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('����־').Data.SetInteger(0);
  WorkView.FieldByName('�Ƿ��մ���').Data.SetString('');
  WorkView.FieldByName('��־').Data.SetString('R');
  inherited;

end;

procedure TfaqhSetChargeType.btnAddClick(Sender: TObject);
begin
  inherited;
  //WorkView.FieldByName('�Ƿ��մ���').Data.SetString(ifFee);
  edtId.ReadOnly := False;
  WorkView.FieldByName('��־').Data.SetString('A');
end;

procedure TfaqhSetChargeType.btnChangeClick(Sender: TObject);
var
  ss:string;
begin
  ss := Grid.DataSource.DataSet.fieldbyname('sall_name').AsString;
  if ss='1' then
    chkif.Checked := True
  else
    chkif.Checked := False;
  inherited;
  edtId.ReadOnly := True;
  WorkView.FieldByName('��־').Data.SetString('U');
end;

procedure TfaqhSetChargeType.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('��־').Data.SetString('D');
end;

procedure TfaqhSetChargeType.btnOKClick(Sender: TObject);
begin
  if Trim(edtName.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('�շ������Ϊ�գ�');
    edtName.SetFocus;
    Exit;
  end;
  if (StrToInt(edtId.Text)<10) or (StrToInt(edtId.Text)>255) then
  begin
    Context.GetDialogSystem.ShowMessage('�շ�����ű�����10~255֮��');
    Exit;
  end;
  if Trim(edtName.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('�շ�������Ʋ���Ϊ�գ�');
    edtName.SetFocus;
    Exit;
  end;
  WorkView.FieldByName('�Ƿ��մ���').Data.SetString(ifFee);
  inherited;
  FreeIDObjects(-43);  // update the data dict
  cbbfeetype.ItemsDataEntry := '';
  cbbfeetype.itemsdataentry := '*-43';
  btnQuery.Click;
end;

procedure TfaqhSetChargeType.chkifClick(Sender: TObject);
begin
  if chkif.Checked then
  begin
    ifFee := '1';
  end
  else
  begin
    ifFee := '2';
  end;
end;

initialization
  TUIStdClassFactory.Create('�շ��������',TfaqhSetChargeType);

end.