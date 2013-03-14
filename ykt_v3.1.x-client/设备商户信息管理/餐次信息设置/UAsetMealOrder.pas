unit UAsetMealOrder;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, 
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, Buttons;

type
  TfaqhsetMealOrder = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label8: TLabel;
    WVDigitalEdit4: TWVDigitalEdit;
    edtName: TWVEdit;
    edtBegin: TWVEdit;
    Label9: TLabel;
    edtEnd: TWVEdit;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    edtMemo: TWVEdit;
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
    OperatorNoName:string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetMealOrder: TfaqhsetMealOrder;

implementation

uses KsFrameworks, 
     KSClientConsts, operComm, UCMqhBusinessEquipImp;
     
{$R *.DFM}

procedure TfaqhsetMealOrder.Init;
begin
  inherited;
  {
  WorkView.FieldByName('���').DefaultValue := 0;
  WorkView.FieldByName('�ʹ�����').DefaultValue := '';
  WorkView.FieldByName('��ʼʱ��').DefaultValue := '';
  WorkView.FieldByName('����ʱ��').DefaultValue := '';
  WorkView.Reset;
  }
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
end;

procedure TfaqhsetMealOrder.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetMealOrder.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;



procedure TfaqhsetMealOrder.btnQueryClick(Sender: TObject);
begin
  queryType(operatorNoName,WorkView);
  inherited;

end;

procedure TfaqhsetMealOrder.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('���').Data.SetInteger(0);
  addType(operatorNoName,WorkView);

end;

procedure TfaqhsetMealOrder.btnChangeClick(Sender: TObject);
begin
  inherited;
  chargeType(operatorNoName,WorkView);
  edtName.Enabled := False;
  edtBegin.Enabled := False;
  edtMemo.Enabled := False;
end;

procedure TfaqhsetMealOrder.btnDeleteClick(Sender: TObject);
begin
  inherited;
  deleteType(operatorNoName,WorkView);

end;

procedure TfaqhsetMealOrder.btnOKClick(Sender: TObject);
begin
  if edtName.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('�ʹ����Ʋ���Ϊ�գ������룡');
    edtName.SetFocus;
    exit;
  end;
  if (checkInputTime(edtend.Text)=false) or (checkInputTime(edtbegin.Text)=false) then
  begin
    Context.GetDialogSystem.ShowMessage('��ʼʱ��ͽ���ʱ�������������飡');
    exit;
  end;
  inherited;
  btnQuery.Click;

end;

initialization
  TUIStdClassFactory.Create('�ʹ���Ϣ����',TfaqhsetMealOrder);

end.