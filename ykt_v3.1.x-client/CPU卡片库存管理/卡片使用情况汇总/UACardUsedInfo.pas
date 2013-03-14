unit UACardUsedInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox;

type
  TfaqhCardUsedInfo = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    cbbCardType: TWVComboBox;
    cbbOperTrans: TWVComboBox;
    WVComboBox1: TWVComboBox;
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
  faqhCardUsedInfo: TfaqhCardUsedInfo;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhCardUsedInfo.Init;
begin
  inherited;

  //WorkView.FieldByName('网点号').DefaultValue := 0;
  WorkView.FieldByName('操作员号').DefaultValue := Context.ParamData(svOperatorNoName).AsString;
  //WorkView.FieldByName('卡类型').DefaultValue := 0;
  WorkView.Reset;

end;

procedure TfaqhCardUsedInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



procedure TfaqhCardUsedInfo.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
var
  strVal:string;
begin
  inherited;
  strVal := Grid.DataSource.DataSet.FieldByName('Snote').AsString;
  if Pos('总计',strVal)>0 then
  begin
    Grid.Canvas.Font.Color := fontColour;
    Grid.Canvas.Brush.Color := bgColour;
    Grid.DefaultDrawColumnCell(Rect, DataCol, Column, State);
  end;
end;

initialization
  TUIStdClassFactory.Create('卡片使用情况汇总',TfaqhCardUsedInfo);

end.