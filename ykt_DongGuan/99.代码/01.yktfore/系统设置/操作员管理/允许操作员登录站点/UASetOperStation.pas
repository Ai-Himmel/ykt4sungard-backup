unit UASetOperStation;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, StdCtrls, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, 
  USetParamsTemp, UIncrementComboBox, RzDBNav, RzButton, RzRadChk,
  RzDBGrid, RzTabs, Buttons;


type
  TfaqhSetOperStation = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Labeloper_code1: TLabel;
    Labelsite_no2: TLabel;
    WVComboBox1: TWVComboBox;
    WVComboBox6: TWVComboBox;
    Labeloper_code3: TLabel;
    WVComboBox3: TWVComboBox;
    WVComboBox2: TWVComboBox;
    Labelsite_no4: TLabel;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnChangeClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetOperStation: TfaqhSetOperStation;

implementation

uses KsFrameworks;
     
{$R *.DFM}

procedure TfaqhSetOperStation.Init;
begin
  inherited;
end;

procedure TfaqhSetOperStation.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhSetOperStation.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhSetOperStation.btnChangeClick(Sender: TObject);
begin
  inherited;
  WVComboBox3.Enabled := false;
end;

procedure TfaqhSetOperStation.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作类别').Data.SetString('A');
  WVComboBox3.Enabled := true;
end;

procedure TfaqhSetOperStation.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('操作类别').Data.SetString('R');
  inherited;
  btnChange.Enabled := false;
end;

procedure TfaqhSetOperStation.btnOKClick(Sender: TObject);
begin
  inherited;
  btnQuery.Click;
  btnChange.Enabled := false;
end;

procedure TfaqhSetOperStation.btnCancelClick(Sender: TObject);
begin
  inherited;
  btnChange.Enabled := false;
end;

procedure TfaqhSetOperStation.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作类别').Data.SetString('D');
  btnOK.SetFocus;
end;

initialization
  TUIStdClassFactory.Create('操作员登录站点管理',TfaqhSetOperStation);

end.