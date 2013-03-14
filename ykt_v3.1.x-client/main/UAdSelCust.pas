unit UAdSelCust;
{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UAdSelCust
   <What>根据各种条件查询客户
   <Written By> Huang YanLai (黄燕来),周耀亮
   <History>
**********************************************}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  WVDBBinders, WVCmdReq, WorkViews, Db, StdCtrls, ImageCtrls, Grids,
  DBGrids, Mask, WVCtrls, ExtCtrls, UICtrls, KSFrameWorks, WVCommands,
  BDAImpEx, KCDataAccess, WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  UIncrementComboBox;

const
  CustomerNoFieldName = 'scust_no';

type
  TdlgAdvancedSelectCustomer = class(TForm)
    UIPanel1: TUIPanel;
    UIPanel2: TUIPanel;
    Label1: TLabel;
    WVComboBox1: TWVComboBox;
    WVEdit1: TWVEdit;
    Label2: TLabel;
    UIPanel3: TUIPanel;
    DBGrid1: TDBGrid;
    btnQuery: TImageButton;
    btnOk: TImageButton;
    btnCancel: TImageButton;
    DataSource: TDataSource;
    WorkView: TWorkView;
    QueryRequest: TWVRequest;
    WVDBBinder: TWVDBBinder;
    ctQueryCustNo: TWVCommandTypeInfo;
    cpQueryCustNo: TKCWVQuery;
    KCDataset: TKCDataset;
    procedure DataSourceDataChange(Sender: TObject; Field: TField);
    procedure WorkViewFieldsMonitors0ValidChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure QueryRequestAfterExec(Request: TWVRequest;
      Command: TWVCommand);
    procedure DataSourceStateChange(Sender: TObject);
  private
    { Private declarations }
    FCustomerNo: string;
    procedure UpdateData;
    procedure HandleException;
  public
    { Public declarations }
    function Execute(var CustomerNo: string): Boolean;
  end;

var
  dlgAdvancedSelectCustomer: TdlgAdvancedSelectCustomer;

function AdvancedSelectCustomer(var CustomerNo: string): Boolean;

implementation

uses KSFrameWorkUtils;

{$R *.DFM}

function AdvancedSelectCustomer(var CustomerNo: string): Boolean;
var
  Dialog: TdlgAdvancedSelectCustomer;
begin
  Dialog := TdlgAdvancedSelectCustomer.Create(Application);
  try
    Result := Dialog.Execute(CustomerNo);
  finally
    Dialog.Free;
  end;
end;

{ TdlgAdvancedSelectCustomer }

procedure TdlgAdvancedSelectCustomer.DataSourceDataChange(Sender: TObject;
  Field: TField);
begin
  if Field = nil then
    UpdateData;
end;

function TdlgAdvancedSelectCustomer.Execute(
  var CustomerNo: string): Boolean;
begin
  FCustomerNo := '';
  WorkView.Reset;
  btnOk.Enabled := False;
  Result := ShowModal = mrOK;
  if Result then
    CustomerNo := FCustomerNo
  else
    CustomerNo := '';
end;

procedure TdlgAdvancedSelectCustomer.UpdateData;
begin
  if (DataSource.DataSet = nil) or (DataSource.DataSet.IsEmpty) or not
    DataSource.DataSet.Active then
    btnOk.Enabled := False
  else
  begin
    btnOk.Enabled := True;
    FCustomerNo := DataSource.DataSet.FieldByName(CustomerNoFieldName).AsString;
  end;
end;

procedure TdlgAdvancedSelectCustomer.WorkViewFieldsMonitors0ValidChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  btnQuery.Enabled := Valid;
end;

procedure TdlgAdvancedSelectCustomer.btnQueryClick(Sender: TObject);
begin
  try
    QueryRequest.SendCommand;
  except
    HandleException;
  end;
end;

procedure TdlgAdvancedSelectCustomer.HandleException;
var
  E: Exception;
begin
  E := Exception(ExceptObject);
  if E <> nil then
    Context.GetExceptionHandler.HandleException(E);
end;

procedure TdlgAdvancedSelectCustomer.FormCreate(Sender: TObject);
begin
  RegisterModule(Self);
end;

procedure TdlgAdvancedSelectCustomer.QueryRequestAfterExec(
  Request: TWVRequest; Command: TWVCommand);
begin
  CheckCommandReturnValue(Command);
end;

procedure TdlgAdvancedSelectCustomer.DataSourceStateChange(
  Sender: TObject);
begin
  UpdateData;
end;

end.
