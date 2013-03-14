unit UAsetFillEquOperInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, RzListVw,
  UIncrementComboBox, Buttons;

type
  TfaqhsetFillEquOperInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label4: TLabel;
    grp1: TGroupBox;
    Label7: TLabel;
    Label11: TLabel;
    Label8: TLabel;
    edtMoney: TWVDigitalEdit;
    cbbFillOper: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    Label1: TLabel;
    WVComboBox3: TWVComboBox;
    Label3: TLabel;
    WVComboBox4: TWVComboBox;
    WVComboBox5: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnOKClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetFillEquOperInfo: TfaqhsetFillEquOperInfo;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhsetFillEquOperInfo.Init;
begin
  inherited;
end;

procedure TfaqhsetFillEquOperInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhsetFillEquOperInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetFillEquOperInfo.btnOKClick(Sender: TObject);
begin
  if (Trim(cbbFillOper.Text)='')or(cbbFillOper.Text='-') then
  begin
    ShowMessage('请选择要分配的充值操作员');
    Exit;
  end;
  inherited;
  FreeIDObjects(-51);  // update the data dict
  WVComboBox5.ItemsDataEntry := '';
  WVComboBox5.itemsdataentry := '-51';
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('充值设备操作员设置',TfaqhsetFillEquOperInfo);

end.