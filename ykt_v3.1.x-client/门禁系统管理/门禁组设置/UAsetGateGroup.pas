unit UAsetGateGroup;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, 
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, Buttons;

type
  TfaqhsetGateGroup = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label4: TLabel;
    Label6: TLabel;
    WVDigitalEdit1: TWVDigitalEdit;
	WVEdit2: TWVEdit;
    edtNo: TWVDigitalEdit;
    Label3: TLabel;
    Label7: TLabel;
    edtName: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnAddClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
  private

    { Private declarations }
    OperatorNoName:string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetGateGroup: TfaqhsetGateGroup;

implementation

uses KsFrameworks, 
     KSClientConsts, gateComm;
     
{$R *.DFM}

procedure TfaqhsetGateGroup.Init;
begin
  inherited;
  WorkView.FieldByName('查询.门禁组编号').DefaultValue := 0;
  WorkView.FieldByName('查询.门禁组名称').DefaultValue := '';
  WorkView.FieldByName('交易类型').DefaultValue := '';
  WorkView.FieldByName('门禁组编号').DefaultValue := 0;
  WorkView.FieldByName('门禁组名称').DefaultValue := '';
  WorkView.Reset;
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
end;

procedure TfaqhsetGateGroup.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetGateGroup.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetGateGroup.btnAddClick(Sender: TObject);
begin
  inherited;
  edtNo.ReadOnly := True;
  WorkView.FieldByName('门禁组编号').Data.SetInteger(0);
  addType(operatorNoName,WorkView);

end;

procedure TfaqhsetGateGroup.btnOKClick(Sender: TObject);
begin
  if Trim(edtName.Text)='' then
  begin
    ShowMessage('门禁组名称不能为空！');
    edtName.SetFocus;
    Exit;
  end;
  inherited;
  btnQuery.Click;
end;

procedure TfaqhsetGateGroup.btnQueryClick(Sender: TObject);
begin
  queryType(operatorNoName,WorkView);
  inherited;

end;

procedure TfaqhsetGateGroup.btnChangeClick(Sender: TObject);
begin
  inherited;
  edtNo.ReadOnly := True;
  chargeType(operatorNoName,WorkView);
end;

procedure TfaqhsetGateGroup.btnDeleteClick(Sender: TObject);
begin
  inherited;
  edtNo.ReadOnly := True;
  deleteType(operatorNoName,WorkView);
end;

initialization
  TUIStdClassFactory.Create('门禁组设置1',TfaqhsetGateGroup);

end.