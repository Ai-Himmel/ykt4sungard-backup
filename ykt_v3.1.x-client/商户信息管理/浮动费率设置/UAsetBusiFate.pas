unit UAsetBusiFate;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, UIncrementComboBox,
  Buttons;

type
  TfaqhsetBusiFate = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    lblMemo: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    edtMemo: TWVEdit;
    WVDigitalEdit8: TWVDigitalEdit;
    edtBusiRate: TWVDigitalEdit;
    edtBusiName: TWVEdit;
    Label1: TLabel;
    btnSelect: TSpeedButton;
    pnl1: TPanel;
    pnl2: TPanel;
    pnl3: TPanel;
    RzDBGrid1: TRzDBGrid;
    WVDBBinder: TWVDBBinder;
    DataSource1: TDataSource;
    lbl1: TLabel;
    btnQry: TBitBtn;
    btnSel: TBitBtn;
    btnCommon: TBitBtn;
    edtBusiId: TWVEdit;
    Label10: TLabel;
    btnCnl: TBitBtn;
    edtQBid: TWVEdit;
    MainRequest: TWVRequest;
    WorkView1: TWorkView;
    edtMoney: TWVEdit;
    WVDigitalEdit1: TWVDigitalEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnCommonClick(Sender: TObject);
    procedure btnQryClick(Sender: TObject);
    procedure btnSelClick(Sender: TObject);
    procedure btnSelectClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure RzDBGrid1DblClick(Sender: TObject);
    procedure RzDBGrid1DrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
    procedure btnCnlClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetBusiFate: TfaqhsetBusiFate;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhsetBusiFate.Init;
begin
  inherited;
  btnQry.Caption := '&Q ��ѯ';
  btnSel.Caption := '&S ѡ��';
  btnCommon.Caption := 'ͨ���̻�';
  btnCnl.Caption := 'ȡ ��';
  pnl1.Visible := False;
end;

procedure TfaqhsetBusiFate.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetBusiFate.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetBusiFate.btnCommonClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('���').Data.SetInteger(0);
  WorkView.FieldByName('�̻�����').Data.SetString('ͨ���̻�');
  pnl1.Visible := False;
end;

procedure TfaqhsetBusiFate.btnQryClick(Sender: TObject);
begin
  //inherited;
  WorkView1.FieldByName('������־').Data.SetString('R');
  //WorkView1.FieldByName('�Ƿ�ΪҶ�ڵ�').Data.SetString('1');
  WorkView1.FieldByName('�̻����').Data.SetInteger(1);
  WorkView1.FieldByName('Ӷ������').Data.SetString('1');
  MainRequest.SendCommand;
end;

procedure TfaqhsetBusiFate.btnSelClick(Sender: TObject);
var
  busiId:Integer;
  busiName:string;
begin
  busiId := RzDBGrid1.DataSource.DataSet.fieldbyname('lvol3').AsInteger;
  busiName := RzDBGrid1.DataSource.DataSet.fieldbyname('sall_name').AsString;
  //inherited;
  WorkView.FieldByName('���').Data.SetInteger(busiId);
  WorkView.FieldByName('�̻�����').Data.SetString(busiName);
  pnl1.Visible := False;
end;

procedure TfaqhsetBusiFate.btnSelectClick(Sender: TObject);
begin
  pnl1.Visible := True;
  WorkView1.FieldByName('�̻�����').Data.SetString('');
  btnQry.Click;
end;

procedure TfaqhsetBusiFate.btnCancelClick(Sender: TObject);
begin
  inherited;
  pnl1.Visible := False;
end;

procedure TfaqhsetBusiFate.btnOKClick(Sender: TObject);
begin
  WorkView.FieldByName('���').Data.SetInteger(StrToInt(edtBusiId.Text));
  WorkView.FieldByName('�ۿ۱���').Data.SetFloat(StrToFloat(edtBusiRate.Text)/100);
  inherited;
  pnl1.Visible := False;
  btnQuery.Click;
end;

procedure TfaqhsetBusiFate.btnQueryClick(Sender: TObject);
begin
  try
    if StrToInt(edtQBid.Text)<-1 then
    begin
      ShowMessage('��������Ч���̻���ţ�');
      exit;
    end;
  except
    ShowMessage('��������Ч���̻���ţ�');
    exit;
  end;
  if Trim(edtMoney.Text)='' then
    edtMoney.Text := '0';
  WorkView.FieldByName('��־').Data.SetString('R');
  inherited;
end;

procedure TfaqhsetBusiFate.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('��־').Data.SetString('A');
  try
    WorkView.FieldByName('�̻�����').Data.SetString(Grid.DataSource.DataSet.fieldbyname('scusttypes').AsString);
    edtBusiRate.Text := FloatToStr(Grid.DataSource.DataSet.fieldbyname('damt1').AsFloat);
  except
  end;
  edtBusiId.ReadOnly := True;                                 
  edtBusiName.ReadOnly := True;
  edtMemo.Visible := False;
  lblMemo.Visible := False;
end;

procedure TfaqhsetBusiFate.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('�̻�����').Data.SetString(Grid.DataSource.DataSet.fieldbyname('scusttypes').AsString);
  WorkView.FieldByName('��־').Data.SetString('D');
  try
    edtBusiRate.Text := FloatToStr(Grid.DataSource.DataSet.fieldbyname('damt1').AsFloat*100);
  except
  end;
  edtMemo.Visible := True;
  lblMemo.Visible := True;
end;

procedure TfaqhsetBusiFate.RzDBGrid1DblClick(Sender: TObject);
begin
  //inherited;
  btnSel.Click;
end;

procedure TfaqhsetBusiFate.RzDBGrid1DrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  //inherited;

end;

procedure TfaqhsetBusiFate.btnCnlClick(Sender: TObject);
begin
  //inherited;
  pnl1.Visible := False;
end;

initialization
  TUIStdClassFactory.Create('������������',TfaqhsetBusiFate);

end.