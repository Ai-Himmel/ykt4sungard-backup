unit UAsetNetInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhsetNetInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label22: TLabel;
    Label23: TLabel;
    Label24: TLabel;
    Label25: TLabel;
    Label26: TLabel;
    Label27: TLabel;
    Label28: TLabel;
    Label29: TLabel;
	WVEdit5: TWVEdit;
    edtNetId: TWVDigitalEdit;
    edtName: TWVEdit;
    WVEdit23: TWVEdit;
    WVEdit24: TWVEdit;
    WVEdit25: TWVEdit;
    WVEdit26: TWVEdit;
    WVEdit27: TWVEdit;
    WVEdit28: TWVEdit;
    WVEdit29: TWVEdit;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox4: TWVComboBox;
    cbbNetType: TWVComboBox;
    WVComboBox3: TWVComboBox;
    cbbNetId: TWVComboBox;
    Label2: TLabel;
    WVEdit1: TWVEdit;
    Label3: TLabel;
    WVComboBox5: TWVComboBox;
    Label4: TLabel;
    WVEdit2: TWVEdit;
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
  faqhsetNetInfo: TfaqhsetNetInfo;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhsetNetInfo.Init;
begin
  inherited;
end;

procedure TfaqhsetNetInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetNetInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;



procedure TfaqhsetNetInfo.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('交易类型').Data.SetString('R');
  inherited;

end;

procedure TfaqhsetNetInfo.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('交易类型').Data.SetString('A');
  edtNetId.ReadOnly := True;
end;

procedure TfaqhsetNetInfo.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('交易类型').Data.SetString('U');
  edtNetId.ReadOnly := True;
end;

procedure TfaqhsetNetInfo.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('交易类型').Data.SetString('D');
  edtNetId.ReadOnly := True;
end;

procedure TfaqhsetNetInfo.btnOKClick(Sender: TObject);
begin
  if Trim(edtName.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('网点名称必须输入！');
    edtName.SetFocus;
    Exit;
  end;
  if (Trim(cbbNetType.Text)='-') or (Trim(cbbNetType.Text)='') then
  begin
    Context.GetDialogSystem.ShowMessage('网点类型必须选择！');
    cbbNetType.SetFocus;
    Exit;
  end;

  inherited;
  btnQuery.Click;
  FreeIDObjects(-2);
  cbbNetId.ItemsDataEntry := '';
  cbbNetId.ItemsDataEntry := '*-2';
end;

initialization
  TUIStdClassFactory.Create('网点信息管理',TfaqhsetNetInfo);

end.