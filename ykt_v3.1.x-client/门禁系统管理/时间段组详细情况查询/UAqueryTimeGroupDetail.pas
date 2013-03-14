unit UAqueryTimeGroupDetail;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox, EditExts;

type
  TfaqhqueryTimeGroupDetail = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Panel2: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    edtNo: TWVDigitalEdit;
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
  faqhqueryTimeGroupDetail: TfaqhqueryTimeGroupDetail;

implementation

uses KsFrameworks;
     
{$R *.DFM}

procedure TfaqhqueryTimeGroupDetail.Init;
begin
  inherited;
  WorkView.FieldByName('时间段组编号').DefaultValue := 0;
  WorkView.FieldByName('星期').DefaultValue := 0;
  WorkView.Reset;
end;

procedure TfaqhqueryTimeGroupDetail.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhqueryTimeGroupDetail.btnQueryClick(Sender: TObject);
begin
  if (Trim(edtNo.Text)='') then
  begin
    ShowMessage('请选择要查询信息的时间段组！');
    exit;
  end;
  inherited;

end;

initialization
  TUIStdClassFactory.Create('时间段组详细情况查询',TfaqhqueryTimeGroupDetail);

end.