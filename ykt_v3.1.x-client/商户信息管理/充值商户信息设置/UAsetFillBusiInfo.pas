unit UAsetFillBusiInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, UIncrementComboBox,
  RzStatus, RzPanel, Buttons;

type
  TfaqhsetFillBusiInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    lblBusiNo: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit4: TWVEdit;
    WVDigitalEdit5: TWVDigitalEdit;
    edtBusiNo: TWVDigitalEdit;
    WVEdit8: TWVEdit;
    WVEdit9: TWVEdit;
    WVEdit11: TWVEdit;
    WVComboBox2: TWVComboBox;
    WVComboBox1: TWVComboBox;
    Label6: TLabel;
    WVDigitalEdit1: TWVDigitalEdit;
    Label7: TLabel;
    Label12: TLabel;
    cbbStatus: TWVComboBox;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnOKClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
    sign:string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetFillBusiInfo: TfaqhsetFillBusiInfo;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhsetFillBusiInfo.Init;
begin
  inherited;
  WorkView.FieldByName('��ѯ.�̻���').DefaultValue := 0;
  WorkView.FieldByName('��ѯ.�̻�����').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�̻�����������').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�̻�֤������').DefaultValue := 0;
  WorkView.FieldByName('��ѯ.�̻�֤������').DefaultValue := '';
  WorkView.FieldByName('��ѯ.�̻���ɱ���').DefaultValue := 0.00;
  WorkView.FieldByName('�̻���').DefaultValue := 0;
  WorkView.FieldByName('�̻�����').DefaultValue := '';
  WorkView.FieldByName('�̻�����������').DefaultValue := '';
  WorkView.FieldByName('�̻�֤������').DefaultValue := 0;
  WorkView.FieldByName('�̻�֤������').DefaultValue := '';
  WorkView.FieldByName('�̻���ɱ���').DefaultValue := 0.00;
  WorkView.Reset;
  //operNo := Context.ParamData(svOperatorNoName).AsString;
  btnAdd.Caption := '&O ����';
  btnDelete.Caption := '&D ����';
  cbbStatus.ItemIndex := 1;
end;

procedure TfaqhsetFillBusiInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhsetFillBusiInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetFillBusiInfo.btnOKClick(Sender: TObject);
begin
  inherited;
  if sign='del' then
    if WorkView.FieldByName('������').Data.AsInteger=0 then
    begin
      ShowMessage(WorkView.fieldbyname('������Ϣ').Data.AsString);
      RzStatusPane1.Caption := WorkView.fieldbyname('������Ϣ').Data.AsString;
    end;
  btnQuery.Click;
end;

procedure TfaqhsetFillBusiInfo.btnDeleteClick(Sender: TObject);
begin
  inherited;
  sign := 'del';
end;

procedure TfaqhsetFillBusiInfo.btnAddClick(Sender: TObject);
begin
  inherited;
  sign := '';
  RzStatusPane1.Caption := '';
end;

procedure TfaqhsetFillBusiInfo.btnChangeClick(Sender: TObject);
begin
  inherited;
  sign := '';
  RzStatusPane1.Caption := '';
end;

procedure TfaqhsetFillBusiInfo.btnQueryClick(Sender: TObject);
var
  sstatus:string;
begin
  sstatus := Copy(cbbStatus.Text,1,Pos('-',cbbStatus.Text)-1);
  if sstatus='-' then
    WorkView.FieldByName('��ѯ.�̻�״̬').Data.SetString('')
  else
    WorkView.FieldByName('��ѯ.�̻�״̬').Data.SetString(sstatus);
  inherited;

end;

initialization
  TUIStdClassFactory.Create('��ֵ�̻���Ϣ����',TfaqhsetFillBusiInfo);

end.