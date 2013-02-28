unit UASetGlobeParaInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, 
  RzDBNav, RzButton, RzRadChk, RzDBGrid, RzTabs, Buttons;

type
  TfaqhSetGlobeParaInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label7: TLabel;
    edtName: TWVEdit;
    WVEdit4: TWVEdit;
    edtUnit: TWVEdit;
    WVEdit1: TWVEdit;
    WVLabel2: TWVLabel;
    WVEdit5: TWVEdit;
    edtId: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnChangeClick(Sender: TObject);
    procedure WVEdit2KeyPress(Sender: TObject; var Key: Char);
    procedure btnOKClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetGlobeParaInfo: TfaqhSetGlobeParaInfo;

implementation

uses KsFrameworks;
     
{$R *.DFM}

procedure TfaqhSetGlobeParaInfo.Init;
begin
  inherited;
end;

procedure TfaqhSetGlobeParaInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhSetGlobeParaInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;



procedure TfaqhSetGlobeParaInfo.btnChangeClick(Sender: TObject);
begin
  inherited;
  edtId.ReadOnly := True;
  edtName.ReadOnly:=True;
  edtUnit.ReadOnly:=True;
end;

procedure TfaqhSetGlobeParaInfo.WVEdit2KeyPress(Sender: TObject;
  var Key: Char);
begin
  inherited;
  if not (key in ['0'..'9']) then
    exit;
end;

procedure TfaqhSetGlobeParaInfo.btnOKClick(Sender: TObject);
begin
  inherited;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('全局参数设置',TfaqhSetGlobeParaInfo);

end.