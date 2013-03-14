unit UAqueryPlanTask;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ExtCtrls, UICtrls, WVDBBinders, Db, 
  RzDBGrid, Buttons;

type
  TfaqhqueryPlanTask = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
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
  faqhqueryPlanTask: TfaqhqueryPlanTask;

implementation

uses KsFrameworks, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhqueryPlanTask.Init;
begin
  inherited;
end;

procedure TfaqhqueryPlanTask.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



procedure TfaqhqueryPlanTask.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('交易类型').Data.SetString('R');
  inherited;

end;

initialization
  TUIStdClassFactory.Create('计划任务日志查询',TfaqhqueryPlanTask);

end.