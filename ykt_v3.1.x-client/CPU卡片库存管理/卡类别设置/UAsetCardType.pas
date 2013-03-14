unit UAsetCardType;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox, BDAImpEx, KCDataAccess;

type
  TfaqhsetCardType = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label19: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label23: TLabel;
    edtCardType: TWVDigitalEdit;
    WVDigitalEdit15: TWVDigitalEdit;
    edtName: TWVEdit;
    WVEdit17: TWVEdit;
    WVDigitalEdit23: TWVDigitalEdit;
    WVComboBox1: TWVComboBox;
    WVComboBox3: TWVComboBox;
    WVComboBox4: TWVComboBox;
    WVComboBox5: TWVComboBox;
    Label1: TLabel;
    cbbNMK: TWVComboBox;
    Label2: TLabel;
    cbbFeeType: TWVComboBox;
    cbbCardType: TWVComboBox;
    Label3: TLabel;
    cbbPhyType: TWVComboBox;
    WVLabel3: TWVLabel;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure cbbNMKChange(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetCardType: TfaqhsetCardType;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary, UCMqhCardLibraryImp;
     
{$R *.DFM}

procedure TfaqhsetCardType.Init;
begin
  inherited;
  edtCardType.Enabled := False;
  cbbFeeType.Enabled := False;
end;

procedure TfaqhsetCardType.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetCardType.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetCardType.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('交易类型').Data.SetString('R');
  inherited;

end;

procedure TfaqhsetCardType.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('交易类型').Data.SetString('A');
  edtCardType.Enabled := False;
  edtCardType.Text := '0';
  cbbNMKChange(Sender);
end;

procedure TfaqhsetCardType.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('交易类型').Data.SetString('U');
  edtCardType.ReadOnly := True;
  cbbNMKChange(Sender);
end;

procedure TfaqhsetCardType.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('交易类型').Data.SetString('D');
  edtCardType.ReadOnly := True;

end;

procedure TfaqhsetCardType.btnOKClick(Sender: TObject);
begin
  if Trim(edtName.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('请输入卡类别名称！');
    edtName.SetFocus;
    Exit;
  end;
  if (Trim(cbbPhyType.Text)='') or (Trim(cbbPhyType.Text)='') then
  begin
    Context.GetDialogSystem.ShowMessage('请选择卡物理类别！');
    Exit;
  end;
  inherited;
  FreeIDObjects(-5);  // update the data dict
  //cbbCardType.ItemsDataEntry := '';
  cbbCardType.itemsdataentry := '-5';
  btnQueryClick(Sender);
end;

procedure TfaqhsetCardType.cbbNMKChange(Sender: TObject);
begin
  inherited;
  if cbbNMK.ItemIndex=2 then
  begin
    cbbFeeType.Enabled := True;
  end
  else
  begin
    cbbFeeType.ItemIndex:=0;
    cbbFeeType.Enabled := False;
    WorkView.FieldByName('默认收费类别').Data.SetInteger(0);
  end;
end;

initialization
  TUIStdClassFactory.Create('卡类别设置',TfaqhsetCardType);

end.