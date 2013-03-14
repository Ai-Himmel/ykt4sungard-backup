unit UAsetGateTime;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, 
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, Buttons;

type
  TfaqhsetGateTime = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label4: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label10: TLabel;
    WVEdit1: TWVEdit;
    WVDigitalEdit4: TWVDigitalEdit;
    edtName: TWVEdit;
    edtBTime: TWVEdit;
    edtETime: TWVEdit;
    Label5: TLabel;
    edtNo: TWVDigitalEdit;
    Label11: TLabel;
    Label12: TLabel;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
  private

    { Private declarations }
    OperatorNoName : string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetGateTime: TfaqhsetGateTime;

implementation

uses KsFrameworks, 
     KSClientConsts, gateComm;
     
{$R *.DFM}

procedure TfaqhsetGateTime.Init;
begin
  inherited;
  WorkView.FieldByName('��ѯ.ʱ�������').DefaultValue := '';
  WorkView.FieldByName('��ѯ.��ʼʱ��').DefaultValue := '';
  WorkView.FieldByName('��ѯ.����ʱ��').DefaultValue := '';
  WorkView.FieldByName('��ѯ.��ʶ').DefaultValue := 0;
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('ʱ�������').DefaultValue := '';
  WorkView.FieldByName('��ʼʱ��').DefaultValue := '';
  WorkView.FieldByName('����ʱ��').DefaultValue := '';
  WorkView.FieldByName('��ʶ').DefaultValue := 0;
  WorkView.Reset;
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
end;

procedure TfaqhsetGateTime.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetGateTime.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetGateTime.btnAddClick(Sender: TObject);
begin
  inherited;
  edtNo.ReadOnly := True;
  WorkView.FieldByName('��ʶ').Data.SetInteger(0);
  addType(operatorNoName,WorkView);
end;

procedure TfaqhsetGateTime.btnChangeClick(Sender: TObject);
begin
  inherited;
  edtNo.ReadOnly := True;
  chargeType(operatorNoName,WorkView);
end;

procedure TfaqhsetGateTime.btnDeleteClick(Sender: TObject);
begin
  inherited;
  edtNo.ReadOnly := True;
  deleteType(operatorNoName,WorkView);
end;

procedure TfaqhsetGateTime.btnQueryClick(Sender: TObject);
begin
  queryType(operatorNoName,WorkView);
  inherited;
end;

procedure TfaqhsetGateTime.btnOKClick(Sender: TObject);
begin
  if Trim(edtName.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('ʱ������Ʋ���Ϊ�գ�');
    edtName.SetFocus;
    Exit;
  end;
  if (checkInputTime(edtBTime.Text)=False)or(checkInputTime(edtETime.Text)=False) then
    Exit;
  inherited;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('ʱ��β�������',TfaqhsetGateTime);

end.