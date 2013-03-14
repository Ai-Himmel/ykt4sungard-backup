unit UAsetMoneyInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhsetMoneyInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label8: TLabel;
    Label9: TLabel;
    WVEdit8: TWVEdit;
    edtMoneyId: TWVDigitalEdit;
    Label1: TLabel;
    WVDigitalEdit1: TWVDigitalEdit;
    Label2: TLabel;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnChangeClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetMoneyInfo: TfaqhsetMoneyInfo;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhsetMoneyInfo.Init;
begin
  inherited;
end;

procedure TfaqhsetMoneyInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetMoneyInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetMoneyInfo.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('交易类型').Data.SetString('U');
  edtMoneyId.ReadOnly := True;
end;

procedure TfaqhsetMoneyInfo.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('交易类型').Data.SetString('R');
  inherited;

end;

procedure TfaqhsetMoneyInfo.btnOKClick(Sender: TObject);
begin
  inherited;
  btnQueryClick(Sender);
end;

initialization
  TUIStdClassFactory.Create('钱包管理',TfaqhsetMoneyInfo);

end.