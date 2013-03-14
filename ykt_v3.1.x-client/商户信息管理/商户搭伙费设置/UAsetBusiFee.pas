unit UAsetBusiFee;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, UIncrementComboBox,
  Buttons;

type
  TfaqhsetBusiFee = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label4: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
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
    btnCnl: TBitBtn;
    edtQBid: TWVEdit;
    MainRequest: TWVRequest;
    WorkView1: TWorkView;
    cbbFeeType: TWVComboBox;
    WVComboBox1: TWVComboBox;
    Label3: TLabel;
    Label5: TLabel;
    edtSRate: TWVDigitalEdit;
    Label6: TLabel;
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
    procedure btnChangeClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetBusiFee: TfaqhsetBusiFee;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhsetBusiFee.Init;
begin
  inherited;
  btnQry.Caption := '&Q 查询';
  btnSel.Caption := '&S 选择';
  btnCommon.Caption := '通用商户';
  btnCnl.Caption := '取 消';
  pnl1.Visible := False;
end;

procedure TfaqhsetBusiFee.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetBusiFee.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetBusiFee.btnCommonClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('商户号').Data.SetInteger(0);
  WorkView.FieldByName('商户名称').Data.SetString('通用商户');
  pnl1.Visible := False;
end;

procedure TfaqhsetBusiFee.btnQryClick(Sender: TObject);
begin
  //inherited;
  WorkView1.FieldByName('操作标志').Data.SetString('');
  WorkView1.FieldByName('商户类别').Data.SetInteger(1);
  WorkView1.FieldByName('收搭伙费').Data.SetString('1');
  MainRequest.SendCommand;
end;

procedure TfaqhsetBusiFee.btnSelClick(Sender: TObject);
var
  busiId:Integer;
  busiName:string;
begin
  busiId := RzDBGrid1.DataSource.DataSet.fieldbyname('lvol3').AsInteger;
  busiName := RzDBGrid1.DataSource.DataSet.fieldbyname('sall_name').AsString;
  //inherited;
  WorkView.FieldByName('商户号').Data.SetInteger(busiId);
  WorkView.FieldByName('商户名称').Data.SetString(busiName);
  pnl1.Visible := False;
end;

procedure TfaqhsetBusiFee.btnSelectClick(Sender: TObject);
begin
  pnl1.Visible := True;
  WorkView1.FieldByName('商户名称').Data.SetString('');
  btnQry.Click;
end;

procedure TfaqhsetBusiFee.btnCancelClick(Sender: TObject);
begin
  inherited;
  pnl1.Visible := False;
end;

procedure TfaqhsetBusiFee.btnOKClick(Sender: TObject);
var
  feeType:string;
begin
  feeType := Copy(cbbFeeType.Text,1,Pos('-',cbbFeeType.Text)-1);
  if (feeType='') or (feeType='-') then
  begin
    Context.GetDialogSystem.ShowMessage('请选择要设定的收费类别！');
    //cbbFeeType.SetFocus;
    Exit;
  end;
  if Trim(edtBusiId.Text)='' then
    edtBusiId.Text := '0';

  if (StrToFloat(edtBusiRate.Text)<0) or (StrToFloat(edtBusiRate.Text)>100) then
  begin
    Context.GetDialogSystem.ShowMessage('请输入有效的费率值！');
    Exit;
  end;
  WorkView.FieldByName('商户号').Data.SetInteger(StrToInt(edtBusiId.Text));
  inherited;     
  pnl1.Visible := False;
  btnQuery.Click;
end;

procedure TfaqhsetBusiFee.btnQueryClick(Sender: TObject);
begin
  try
    if StrToInt(edtQBid.Text)<-1 then
    begin
      Context.GetDialogSystem.ShowMessage('请输入有效的商户编号！');
      exit;
    end;
  except
    Context.GetDialogSystem.ShowMessage('请输入有效的商户编号！');
    exit;
  end;
  WorkView.FieldByName('操作标志').Data.SetString('R');
  inherited;
end;

procedure TfaqhsetBusiFee.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('A');
  try
    WorkView.FieldByName('商户名称').Data.SetString(Grid.DataSource.DataSet.fieldbyname('vsvarstr0').AsString);
  except
  end;
  cbbFeeType.Enabled := True;
  edtBusiId.ReadOnly := True;
  edtBusiName.ReadOnly := True;
  btnSelect.Enabled := True;
end;

procedure TfaqhsetBusiFee.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('D');
  WorkView.FieldByName('商户名称').Data.SetString(Grid.DataSource.DataSet.fieldbyname('vsvarstr0').AsString);
end;

procedure TfaqhsetBusiFee.RzDBGrid1DblClick(Sender: TObject);
begin
  //inherited;
  btnSel.Click;
end;

procedure TfaqhsetBusiFee.RzDBGrid1DrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  //inherited;

end;

procedure TfaqhsetBusiFee.btnCnlClick(Sender: TObject);
begin
  //inherited;
  pnl1.Visible := False;
end;

procedure TfaqhsetBusiFee.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('U');
  WorkView.FieldByName('商户名称').Data.SetString(Grid.DataSource.DataSet.fieldbyname('vsvarstr0').AsString);
  cbbFeeType.Enabled := False;
  edtBusiId.Enabled := False;
  edtBusiName.Enabled := False;
  btnSelect.Enabled := False;
end;

initialization
  TUIStdClassFactory.Create('商户搭伙费设置',TfaqhsetBusiFee);

end.