unit UATicketCashReport;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox;

type
  TfaqhTicketCashReport = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    cbbOperTrans: TWVComboBox;
    cbbNetInfo: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure GridDrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhTicketCashReport: TfaqhTicketCashReport;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhTicketCashReport.Init;
begin
  inherited;
  WorkView.FieldByName('操作员号').DefaultValue := Context.ParamData(svOperatorNoName).AsString;
  //WorkView.FieldByName('卡类型').DefaultValue := 0;
  WorkView.Reset;
end;

procedure TfaqhTicketCashReport.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



procedure TfaqhTicketCashReport.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
var
  strVal:string;
begin
  inherited;
  strVal := Grid.DataSource.DataSet.FieldByName('Snote').AsString;
  if Pos('合计',strVal)>0 then
  begin
    Grid.Canvas.Font.Color := clWhite;
    Grid.Canvas.Brush.Color := clTeal;
    Grid.DefaultDrawColumnCell(Rect, DataCol, Column, State);
  end;
end;

initialization
  TUIStdClassFactory.Create('票据现金报表',TfaqhTicketCashReport);

end.