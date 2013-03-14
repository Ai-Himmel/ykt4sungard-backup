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
  WorkView.FieldByName('��ѯ.�Ž�����').DefaultValue := 0;
  WorkView.FieldByName('��ѯ.�Ž�������').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('�Ž�����').DefaultValue := 0;
  WorkView.FieldByName('�Ž�������').DefaultValue := '';
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
  WorkView.FieldByName('�Ž�����').Data.SetInteger(0);
  addType(operatorNoName,WorkView);

end;

procedure TfaqhsetGateGroup.btnOKClick(Sender: TObject);
begin
  if Trim(edtName.Text)='' then
  begin
    ShowMessage('�Ž������Ʋ���Ϊ�գ�');
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
  TUIStdClassFactory.Create('�Ž�������1',TfaqhsetGateGroup);

end.