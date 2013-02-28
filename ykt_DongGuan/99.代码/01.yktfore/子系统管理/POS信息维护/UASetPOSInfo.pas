unit UASetPOSInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhSetPOSInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label19: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label22: TLabel;
    Label23: TLabel;
    Label24: TLabel;
    Label26: TLabel;
	WVEdit4: TWVEdit;
	WVEdit5: TWVEdit;
	WVEdit8: TWVEdit;
    WVEdit19: TWVEdit;
    WVEdit20: TWVEdit;
    edtPosName: TWVEdit;
    edtDate: TWVEdit;
    WVComboBox3: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox4: TWVComboBox;
    WVComboBox5: TWVComboBox;
    WVComboBox6: TWVComboBox;
    WVComboBox7: TWVComboBox;
    edtPosIdQ: TWVEdit;
    edtBusiIdQ: TWVEdit;
    edtPosId: TWVEdit;
    edtBusiId: TWVEdit;
    Label1: TLabel;
    WVComboBox8: TWVComboBox;
    Label11: TLabel;
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
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetPOSInfo: TfaqhSetPOSInfo;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhSetPOSInfo.Init;
begin
  inherited;
  {
  WorkView.FieldByName('��ѯ.������־').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�豸���').DefaultValue := 0;
  WorkView.FieldByName('��ѯ.�����̻���').DefaultValue := 0;
  WorkView.FieldByName('��ѯ.�豸�ն˺�').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�ն����к�').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�豸�ͺ�').DefaultValue := 0;
  WorkView.FieldByName('��ѯ.�豸����').DefaultValue := 0;
  WorkView.FieldByName('��ѯ.�豸����').DefaultValue := '';
  WorkView.FieldByName('��ѯ.��;').DefaultValue := 0;
  WorkView.FieldByName('��ѯ.�豸״̬').DefaultValue := '';
  WorkView.FieldByName('��ѯ.��������').DefaultValue := '';
  WorkView.FieldByName('��ѯ.ע������').DefaultValue := '';
  WorkView.FieldByName('��ѯ.ɾ������').DefaultValue := '';
  WorkView.FieldByName('��ѯ.������ʱ��').DefaultValue := '';
  WorkView.FieldByName('��ѯ.��ע').DefaultValue := ;
  WorkView.FieldByName('������־').DefaultValue := '';
  WorkView.FieldByName('�豸�����').DefaultValue := 0;
  WorkView.FieldByName('�����̻���').DefaultValue := 0;
  WorkView.FieldByName('�豸�ն˺�').DefaultValue := '';
  WorkView.FieldByName('�ն����к�').DefaultValue := '';
  WorkView.FieldByName('�豸�ͺ�').DefaultValue := 0;
  WorkView.FieldByName('�豸����').DefaultValue := 0;
  WorkView.FieldByName('�豸����').DefaultValue := '';
  WorkView.FieldByName('��;').DefaultValue := 0;
  WorkView.FieldByName('�豸״̬').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('ע������').DefaultValue := '';
  WorkView.FieldByName('ɾ������').DefaultValue := '';
  WorkView.FieldByName('������ʱ��').DefaultValue := '';
  WorkView.FieldByName('��ע').DefaultValue := ;
  WorkView.Reset;
  }
end;

procedure TfaqhSetPOSInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  //btnQuery.Enabled:=Valid;
end;


procedure TfaqhSetPOSInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhSetPOSInfo.btnQueryClick(Sender: TObject);
begin
  if Trim(edtBusiIdQ.Text)='' then
    edtBusiIdQ.Text := '0';
  WorkView.FieldByName('������־').Data.SetString('R');
  inherited;
end;

procedure TfaqhSetPOSInfo.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('A');
  edtPosId.Text := '0';
  edtPosId.Enabled := False;
end;

procedure TfaqhSetPOSInfo.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('E');
  edtPosId.Enabled := False;
end;

procedure TfaqhSetPOSInfo.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('D');
  edtPosId.Enabled := False;
end;

procedure TfaqhSetPOSInfo.btnOKClick(Sender: TObject);
begin
  if Trim(edtDate.Text)<>'' then
    if CheckInputDateFormat(edtDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����������벻��ȷ����ʽ��yyyymmdd');
      edtDate.SetFocus;
      Exit;
    end;
  if Trim(edtPosName.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('�豸���Ʋ���Ϊ��');
    edtPosName.SetFocus;
    Exit;
  end;
  if WorkView.FieldByName('��������').Data.AsString='' then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��������룡');
    Exit;
  end;
  if Trim(edtBusiId.Text)='' then
    edtBusiId.Text := '0';
  inherited;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('�豸��Ϣά��',TfaqhSetPOSInfo);

end.