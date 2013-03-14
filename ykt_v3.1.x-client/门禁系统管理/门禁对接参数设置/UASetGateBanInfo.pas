unit UASetGateBanInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, 
  RzDBNav, RzButton, RzRadChk, RzDBGrid, RzTabs, UIncrementComboBox,
  Buttons;

type
  TfaqhSetGateBanInterface = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label6: TLabel;
    Label8: TLabel;
    Label10: TLabel;
    WVEdit3: TWVEdit;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit5: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetGateBanInterface: TfaqhSetGateBanInterface;

implementation

uses KsFrameworks;

{$R *.DFM}

procedure TfaqhSetGateBanInterface.Init;
begin
  inherited;

end;

procedure TfaqhSetGateBanInterface.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;


procedure TfaqhSetGateBanInterface.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled := Valid;
end;



procedure TfaqhSetGateBanInterface.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('操作码').Data.SetString('Q');
  inherited;
end;

procedure TfaqhSetGateBanInterface.btnChangeClick(Sender: TObject);
begin
  WVEdit2.Enabled := False;
  WorkView.FieldByName('操作码').Data.SetString('U');
  inherited;
end;

procedure TfaqhSetGateBanInterface.btnAddClick(Sender: TObject);
begin
  WVEdit2.Enabled := true;
  WorkView.FieldByName('操作码').Data.SetString('I');
  inherited;

end;

procedure TfaqhSetGateBanInterface.btnDeleteClick(Sender: TObject);
begin
  WorkView.FieldByName('操作码').Data.SetString('D');
  inherited;
end;

procedure TfaqhSetGateBanInterface.btnOKClick(Sender: TObject);
begin
  inherited;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('门禁对接参数设置', TfaqhSetGateBanInterface);

end.


