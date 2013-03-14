unit UAQueryGlobeParaByOther;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons;

type
  TfaqhQueryGlobeParaByOther = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label6: TLabel;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    WVEdit6: TWVEdit;
    WVLabel1: TWVLabel;
    WVEdit1: TWVEdit;
    WVLabel2: TWVLabel;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhQueryGlobeParaByOther: TfaqhQueryGlobeParaByOther;

implementation

uses KsFrameworks;
     
{$R *.DFM}

procedure TfaqhQueryGlobeParaByOther.Init;
begin
  inherited;
end;

procedure TfaqhQueryGlobeParaByOther.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



initialization
  TUIStdClassFactory.Create('全局参数查询',TfaqhQueryGlobeParaByOther);

end.