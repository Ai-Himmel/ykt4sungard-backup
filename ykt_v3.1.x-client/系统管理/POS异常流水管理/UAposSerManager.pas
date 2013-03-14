unit UAposSerManager;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhposSerManager = class(TfaqhSetParamsTemp)
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
    edtPhyId: TWVEdit;
    WVComboBox6: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox3: TWVComboBox;
    WVComboBox4: TWVComboBox;
    edtBusiNo: TWVEdit;
    edtSeriNo: TWVEdit;
    edtQCardNo: TWVEdit;
    edtCardNo: TWVEdit;
    edtTradeNum: TWVEdit;
    edtPackageNo: TWVEdit;
    edtDevNo: TWVEdit;
    edtBusiCardNo: TWVEdit;
    lbl1: TLabel;
    Label8: TLabel;
    edtQEdate: TWVEdit;
    Label11: TLabel;
    WVComboBox5: TWVComboBox;
    Label12: TLabel;
    edtDevid: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnChangeClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
  private

    { Private declarations }
    tradeDate:string;
    seriId:Integer;
    devPhyId:string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhposSerManager: TfaqhposSerManager;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhposSerManager.Init;
begin
  inherited;
  edtQDate.Text := sysDate;
  edtQEdate.Text := sysDate;
end;

procedure TfaqhposSerManager.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhposSerManager.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhposSerManager.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('U');
  WorkView.FieldByName('��ˮ״̬').Data.SetString('1');
  WVComboBox5.Enabled := false;
  try
    //tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
    tradeDate := edtDate.Text;
    seriId := StrToInt(edtDevNo.Text);//tmpData.fieldbyname('sname').AsString;
    devPhyId:= edtPhyId.Text;//tmpData.fieldbyname('lserial0').AsString;

  except
    on ex:Exception do
    ShowMessage(ex.Message);
  end;
end;

procedure TfaqhposSerManager.btnQueryClick(Sender: TObject);
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
      Context.GetDialogSystem.ShowMessage('�����������󣬸�ʽyyyymmdd');
      edtQDate.SetFocus;
      Exit;
    end;
  if Trim(edtDevid.Text)='' then
    edtDevid.Text := '0';
  WorkView.FieldByName('������־').Data.SetString('R');
  inherited;
end;

procedure TfaqhposSerManager.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('A');

end;

procedure TfaqhposSerManager.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('D');
    //tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
    tradeDate := edtDate.Text;
    seriId := StrToInt(edtDevNo.Text);//tmpData.fieldbyname('sname').AsString;
    devPhyId:= edtPhyId.Text;//tmpData.fieldbyname('lserial0').AsString;
end;

procedure TfaqhposSerManager.btnOKClick(Sender: TObject);
begin
  if Trim(edtCardNo.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('���Ų���Ϊ�գ������룡');
    edtCardNo.SetFocus;
    Exit;
  end;
  if Trim(edtTradeNum.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('�����״�������Ϊ�գ������룡');
    edtTradeNum.SetFocus;
    Exit;
  end;
  if Trim(edtPackageNo.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('Ǯ���Ų���Ϊ�գ������룡');
    edtPackageNo.SetFocus;
    Exit;
  end;
  if Trim(edtDevNo.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('�豸��ˮ�Ų���Ϊ�գ������룡');
    edtDevNo.SetFocus;
    Exit;
  end;
  if Trim(edtBusiCardNo.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('�̻����Ų���Ϊ�գ������룡');
    edtBusiCardNo.SetFocus;
    Exit;
  end;
  if Trim(edtDate.Text)<>'' then
    if CheckInputDateFormat(edtDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����������󣬸�ʽyyyymmdd');
      edtDate.SetFocus;
      Exit;
    end;
  if Trim(edtTime.Text)<>'' then
    if CheckInputTimeFormat(edtTime.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('ʱ���������󣬸�ʽhhmmss');
      edtTime.SetFocus;
      Exit;
    end;
  WorkView.FieldByName('��������').Data.SetString(edtDate.Text);
  WorkView.FieldByName('�豸��ˮ��').Data.SetInteger(StrToInt(edtSeriNo.Text));
  WorkView.FieldByName('�豸������').Data.SetString(edtPhyId.Text);
  WorkView.FieldByName('����������').Data.SetString(tradeDate);
  WorkView.FieldByName('���豸��ˮ��').Data.SetInteger(seriId);
  WorkView.FieldByName('���豸������').Data.SetString(devPhyId);
  inherited;
  btnQueryClick(Sender);
end;

initialization
  TUIStdClassFactory.Create('POS�쳣��ˮ����',TfaqhposSerManager);

end.