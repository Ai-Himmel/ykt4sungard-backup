unit UABankLinkQuery;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons;

type
  TfaqhBankLinkQuery = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    WVEdit2: TWVEdit;
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
  faqhBankLinkQuery: TfaqhBankLinkQuery;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhBankLinkQuery.Init;
begin
  inherited;
  WorkView.FieldByName('操作标志').DefaultValue := '';
  WorkView.FieldByName('学号').DefaultValue := '';
  WorkView.Reset;
end;

procedure TfaqhBankLinkQuery.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



procedure TfaqhBankLinkQuery.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('操作标志').Data.SetString('Q');
  inherited;

end;

initialization
  TUIStdClassFactory.Create('银行卡联机查询',TfaqhBankLinkQuery);

end.