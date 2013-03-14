unit UASetCustomerKindInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, 
  RzDBNav, RzButton, RzRadChk, RzDBGrid, RzTabs, UIncrementComboBox,
  Buttons;

type
  TfaqhSetCustomerKindInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVEdit3: TWVEdit;
    WVComboBox1: TWVComboBox;
    WVEdit2: TWVEdit;
    Label9: TLabel;
    WVComboBox5: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnChangeClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetCustomerKindInfo: TfaqhSetCustomerKindInfo;

implementation

uses KsFrameworks,KSDataDictionary;

{$R *.DFM}

procedure TfaqhSetCustomerKindInfo.Init;
begin
  inherited;
  WVComboBox1.ItemIndex := 0;
end;

procedure TfaqhSetCustomerKindInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;


procedure TfaqhSetCustomerKindInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled := Valid;
end;

procedure TfaqhSetCustomerKindInfo.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('交易类型').Data.SetString('U');
  WVEdit2.Enabled := False;
end;

procedure TfaqhSetCustomerKindInfo.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('交易类型').Data.SetString('A');
  WVEdit2.Enabled := True;
end;

procedure TfaqhSetCustomerKindInfo.btnOKClick(Sender: TObject);
begin
  if ((trim(WVEdit2.Text) = '') or (WVEdit2.Text = '0')) then
  begin
    Context.GetDialogSystem.ShowWarning('客户类别代码不能为空或零！');
    WVEdit2.SetFocus;
    WVEdit2.SelectAll;
    Exit;
  end;
  if Trim(WVEdit3.Text) = '' then
  begin
    Context.GetDialogSystem.ShowWarning('请输入客户类别名称！');
    WVEdit3.SetFocus;
    WVEdit3.SelectAll;
    Exit;
  end;
  inherited;
  FreeIDObjects(-34);  // update the data dict
  WVComboBox1.ItemsDataEntry := '';
  WVComboBox1.itemsdataentry := '*-34';
  btnQuery.Click;
end;

procedure TfaqhSetCustomerKindInfo.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('交易类型').Data.SetString('R');
  inherited;

end;

procedure TfaqhSetCustomerKindInfo.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('交易类型').Data.SetString('D');
end;

initialization
  TUIStdClassFactory.Create('客户类别设置', TfaqhSetCustomerKindInfo);

end.


