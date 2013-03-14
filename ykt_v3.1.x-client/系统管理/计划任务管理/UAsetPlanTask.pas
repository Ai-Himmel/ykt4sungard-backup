unit UAsetPlanTask;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ExtCtrls, UICtrls, 
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhsetPlanTask = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label19: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label23: TLabel;
    edtTaskId: TWVDigitalEdit;
    WVEdit13: TWVEdit;
    WVEdit14: TWVEdit;
    WVEdit15: TWVEdit;
    WVEdit16: TWVEdit;
    WVEdit20: TWVEdit;
    WVEdit21: TWVEdit;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox3: TWVComboBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVComboBox4: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetPlanTask: TfaqhsetPlanTask;

implementation

uses KsFrameworks,KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhsetPlanTask.Init;
begin
  inherited;
end;

procedure TfaqhsetPlanTask.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetPlanTask.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;



procedure TfaqhsetPlanTask.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('交易类型').Data.SetString('R');
  inherited;

end;

procedure TfaqhsetPlanTask.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('交易类型').Data.SetString('A');
  edtTaskId.ReadOnly := True;
end;

procedure TfaqhsetPlanTask.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('交易类型').Data.SetString('U');
  edtTaskId.ReadOnly := True;
end;

procedure TfaqhsetPlanTask.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('交易类型').Data.SetString('D');
  edtTaskId.ReadOnly := True;
end;

procedure TfaqhsetPlanTask.btnOKClick(Sender: TObject);
begin
  inherited;
  btnQueryClick(Sender);
end;

initialization
  TUIStdClassFactory.Create('计划任务设置',TfaqhsetPlanTask);

end.