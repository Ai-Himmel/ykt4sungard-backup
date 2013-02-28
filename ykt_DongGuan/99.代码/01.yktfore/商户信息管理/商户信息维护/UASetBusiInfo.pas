unit UASetBusiInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhSetBusiInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label25: TLabel;
    Label26: TLabel;
	WVEdit3: TWVEdit;
	WVEdit4: TWVEdit;
	WVEdit5: TWVEdit;
	WVEdit6: TWVEdit;
	WVEdit7: TWVEdit;
    WVDigitalEdit26: TWVDigitalEdit;
    edtBusiId: TWVEdit;
    WVComboBox8: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    grp1: TGroupBox;
    Label28: TLabel;
    WVEdit28: TWVEdit;
    Label27: TLabel;
    WVEdit27: TWVEdit;
    Label29: TLabel;
    edtBusiName: TWVEdit;
    Label30: TLabel;
    edtBusiEngName: TWVEdit;
    Label31: TLabel;
    WVEdit31: TWVEdit;
    Label32: TLabel;
    Label33: TLabel;
    Label47: TLabel;
    WVEdit47: TWVEdit;
    Label41: TLabel;
    WVDigitalEdit41: TWVDigitalEdit;
    GroupBox1: TGroupBox;
    Label34: TLabel;
    WVEdit34: TWVEdit;
    Label35: TLabel;
    WVEdit35: TWVEdit;
    Label36: TLabel;
    WVEdit36: TWVEdit;
    Label37: TLabel;
    WVEdit37: TWVEdit;
    Label38: TLabel;
    WVEdit38: TWVEdit;
    Label39: TLabel;
    WVEdit39: TWVEdit;
    Label40: TLabel;
    WVEdit40: TWVEdit;
    grp2: TGroupBox;
    Label42: TLabel;
    Label43: TLabel;
    WVEdit43: TWVEdit;
    Label44: TLabel;
    WVEdit44: TWVEdit;
    Label45: TLabel;
    WVEdit45: TWVEdit;
    cbb1: TWVComboBox;
    WVComboBox3: TWVComboBox;
    edt1: TWVEdit;
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
  faqhSetBusiInfo: TfaqhSetBusiInfo;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhSetBusiInfo.Init;
begin
  inherited;
  {
  WorkView.FieldByName('��ѯ.������־').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�̻����').DefaultValue := 0;
  WorkView.FieldByName('��ѯ.�����̻���').DefaultValue := '';
  WorkView.FieldByName('��ѯ.ʡ�̻����').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�̻���').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�̻�Ӣ������').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�̻����').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�̻�����').DefaultValue := '';
  WorkView.FieldByName('��ѯ.��ҵ����').DefaultValue := '';
  WorkView.FieldByName('��ѯ.��ϵ��').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�绰').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�ֻ�').DefaultValue := '';
  WorkView.FieldByName('��ѯ.��������').DefaultValue := '';
  WorkView.FieldByName('��ѯ.����').DefaultValue := '';
  WorkView.FieldByName('��ѯ.Ӫҵ��ַ').DefaultValue := ;
  WorkView.FieldByName('��ѯ.��������').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�������').DefaultValue := 0.00;
  WorkView.FieldByName('��ѯ.��������').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�����˺�').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�����ʻ���').DefaultValue := '';
  WorkView.FieldByName('��ѯ.���к�').DefaultValue := '';
  WorkView.FieldByName('��ѯ.��������').DefaultValue := '';
  WorkView.FieldByName('��ѯ.��������').DefaultValue := '';
  WorkView.FieldByName('��ѯ.����״̬').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�̻�״̬').DefaultValue := '';
  WorkView.FieldByName('�̻����').DefaultValue := 0;
  WorkView.FieldByName('�����̻���').DefaultValue := '';
  WorkView.FieldByName('ʡ�̻����').DefaultValue := '';
  WorkView.FieldByName('�̻���').DefaultValue := '';
  WorkView.FieldByName('�̻�Ӣ������').DefaultValue := '';
  WorkView.FieldByName('�̻����').DefaultValue := '';
  WorkView.FieldByName('�̻�����').DefaultValue := '';
  WorkView.FieldByName('��ҵ����').DefaultValue := '';
  WorkView.FieldByName('��ϵ��').DefaultValue := '';
  WorkView.FieldByName('�绰').DefaultValue := '';
  WorkView.FieldByName('�ֻ�').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('����').DefaultValue := '';
  WorkView.FieldByName('Ӫҵ��ַ').DefaultValue := ;
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('�������').DefaultValue := 0.00;
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('�����˺�').DefaultValue := '';
  WorkView.FieldByName('�����ʻ���').DefaultValue := '';
  WorkView.FieldByName('���к�').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('����״̬').DefaultValue := '';
  WorkView.FieldByName('�̻�״̬').DefaultValue := '';
  WorkView.Reset;
  }
end;

procedure TfaqhSetBusiInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhSetBusiInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhSetBusiInfo.btnQueryClick(Sender: TObject);
begin
  if Trim(edtBusiId.Text)='' then
    edtBusiId.Text := '0';
  WorkView.FieldByName('������־').Data.SetString('R');
  inherited;
end;

procedure TfaqhSetBusiInfo.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('A');
end;

procedure TfaqhSetBusiInfo.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('E');
end;

procedure TfaqhSetBusiInfo.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('D');
end;

procedure TfaqhSetBusiInfo.btnOKClick(Sender: TObject);
begin
  if Trim(edtBusiName.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('�̻����Ʋ���Ϊ�գ�');
    edtBusiName.SetFocus;
    Exit;
  end;
  inherited;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('�̻���Ϣ����',TfaqhSetBusiInfo);

end.