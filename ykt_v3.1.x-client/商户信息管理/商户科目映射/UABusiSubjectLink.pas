unit UABusiSubjectLink;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhBusiSubjectLink = class(TfaqhSetParamsTemp)
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label10: TLabel;
    edtBusiId: TWVDigitalEdit;
    edtBusiName: TWVEdit;
    WVEdit10: TWVEdit;
    Label1: TLabel;
    WVEdit1: TWVEdit;
    pnl1: TPanel;
    pnl2: TPanel;
    pnl3: TPanel;
    btnQry: TBitBtn;
    btnSel: TBitBtn;
    btnCommon: TBitBtn;
    btnCnl: TBitBtn;
    RzDBGrid1: TRzDBGrid;
    btnSelect: TSpeedButton;
    WorkView1: TWorkView;
    MainRequest: TWVRequest;
    cbbSubJNo: TWVComboBox;
    WVDBBinder: TWVDBBinder;
    DataSource1: TDataSource;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQryClick(Sender: TObject);
    procedure btnCommonClick(Sender: TObject);
    procedure btnSelClick(Sender: TObject);
    procedure btnCnlClick(Sender: TObject);
    procedure btnSelectClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhBusiSubjectLink: TfaqhBusiSubjectLink;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhBusiSubjectLink.Init;
begin
  inherited;
  pnl1.Visible := False;
end;

procedure TfaqhBusiSubjectLink.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhBusiSubjectLink.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhBusiSubjectLink.btnQryClick(Sender: TObject);
begin
  WorkView1.FieldByName('操作标志').Data.SetString('');
  WorkView1.FieldByName('商户类别').Data.SetInteger(0);
  WorkView1.FieldByName('收搭伙费').Data.SetString('');
  MainRequest.SendCommand;
end;

procedure TfaqhBusiSubjectLink.btnCommonClick(Sender: TObject);
begin
  WorkView.FieldByName('商户号').Data.SetInteger(0);
  WorkView.FieldByName('商户名称').Data.SetString('通用商户');
  pnl1.Visible := False;
end;

procedure TfaqhBusiSubjectLink.btnSelClick(Sender: TObject);
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

procedure TfaqhBusiSubjectLink.btnCnlClick(Sender: TObject);
begin
  pnl1.Visible := False;
end;

procedure TfaqhBusiSubjectLink.btnSelectClick(Sender: TObject);
begin
  pnl1.Visible := True;
  WorkView1.FieldByName('商户名称').Data.SetString('');
  btnQry.Click;
end;

procedure TfaqhBusiSubjectLink.btnCancelClick(Sender: TObject);
begin
  inherited;
  pnl1.Visible := False;

end;

procedure TfaqhBusiSubjectLink.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('标志').Data.SetString('A');
  edtBusiId.ReadOnly := True;
  edtBusiName.ReadOnly := True;
  btnSelect.Enabled := True;
end;

procedure TfaqhBusiSubjectLink.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('标志').Data.SetString('U');
  edtBusiId.ReadOnly := True;
  edtBusiName.ReadOnly := True;
  btnSelect.Enabled := False;
end;

procedure TfaqhBusiSubjectLink.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('标志').Data.SetString('D');
  edtBusiId.ReadOnly := True;
  edtBusiName.ReadOnly := True;
  btnSelect.Enabled := False;
end;

procedure TfaqhBusiSubjectLink.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('标志').Data.SetString('R');
  inherited;

end;

procedure TfaqhBusiSubjectLink.btnOKClick(Sender: TObject);
begin
  inherited;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('商户科目映射',TfaqhBusiSubjectLink);

end.