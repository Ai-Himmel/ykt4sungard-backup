unit UAQuerySpeInfoByOther;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons;

type
  TfaqhQuerySpeInfoByOther = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVLabel1: TWVLabel;
    WVEdit3: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhQuerySpeInfoByOther: TfaqhQuerySpeInfoByOther;

implementation

uses KsFrameworks;
     
{$R *.DFM}

procedure TfaqhQuerySpeInfoByOther.Init;
begin
  inherited;
  {
  WorkView.FieldByName('רҵ����').DefaultValue := '';
  WorkView.FieldByName('רҵ����').DefaultValue := '';
  WorkView.FieldByName('��ע').DefaultValue := '';
  WorkView.Reset;
  }
end;

procedure TfaqhQuerySpeInfoByOther.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



initialization
  TUIStdClassFactory.Create('רҵ��Ϣ��ѯ',TfaqhQuerySpeInfoByOther);

end.