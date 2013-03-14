unit UAsubSendListQuery;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox, Buttons;

type
  TfaqhsubSendListQuery = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    Label5: TLabel;
    WVComboBox3: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsubSendListQuery: TfaqhsubSendListQuery;

implementation

uses KsFrameworks, 
     UCMqhSubSystemImp;
     
{$R *.DFM}

procedure TfaqhsubSendListQuery.Init;
begin
  inherited;
end;

procedure TfaqhsubSendListQuery.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

initialization
  TUIStdClassFactory.Create('外接系统名单同步查询',TfaqhsubSendListQuery);

end.