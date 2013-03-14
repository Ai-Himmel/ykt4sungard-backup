unit UAQGateMgrOpen;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, UIncrementComboBox, Buttons;

type
  TfaqhQGateMgrOpen = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label4: TLabel;
    Label7: TLabel;
    edtCardNo: TWVEdit;
    edtDevNo: TWVEdit;
    cbbUes: TWVComboBox;
    Label13: TLabel;
    cbbOper: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhQGateMgrOpen: TfaqhQGateMgrOpen;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhQGateMgrOpen.Init;
begin
  inherited;
  cbbUes.ItemIndex := 0;
  cbbOper.ItemIndex := 0;
end;

procedure TfaqhQGateMgrOpen.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhQGateMgrOpen.btnQueryClick(Sender: TObject);
begin
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';

  if Trim(edtDevNo.Text)='' then
    edtDevNo.Text := '0';
  WorkView.FieldByName('操作标志').Data.SetString('R');
  inherited;

end;

initialization
  TUIStdClassFactory.Create('管理卡常开卡查询',TfaqhQGateMgrOpen);

end.