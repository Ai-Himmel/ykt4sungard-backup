unit UDoubleCheck;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  WVCmdReq, WorkViews, StdCtrls, ImageCtrls, Mask, WVCtrls, ExtCtrls,
  UICtrls, WVCommands;

type
  TdlgDoubleCheck = class(TForm)
    UIPanel1: TUIPanel;
    Label2: TLabel;
    Label3: TLabel;
    edOperator: TWVEdit;
    WVEdit3: TWVEdit;
    btnOk: TImageButton;
    btnCancel: TImageButton;
    WorkView: TWorkView;
    MainRequest: TWVRequest;
    procedure btnCancelClick(Sender: TObject);
    procedure MainRequestAfterExec(Request: TWVRequest;
      Command: TWVCommand);
    procedure btnOkClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure WorkViewFieldsMonitors0ValidChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewWorkFields0CheckValid(WorkField: TWVField);
  private
    { Private declarations }
    FValid: Boolean;
  public
    { Public declarations }
    function Execute(
      const AOperation: string;
      var CheckerNo, CheckerPassword: string;
      FuncNo: Integer = 0;
      const CustomerNo: string = '';
      const CurrentType: string = '';
      const ACaption: string = ''
      ): Boolean;

  end;

var
  dlgDoubleCheck: TdlgDoubleCheck;

function DoSingleStationCheck(
  const AOperation: string;
  var CheckerNo, CheckerPassword: string;
  FuncNo: Integer = 0;
  const CustomerNo: string = '';
  const CurrentType: string = '';
  const ACaption: string = ''
  ): Boolean;

implementation

{$R *.DFM}

uses KSFrameWorks, KSFrameWorkUtils, KSClientConsts;

function DoSingleStationCheck(
  const AOperation: string;
  var CheckerNo, CheckerPassword: string;
  FuncNo: Integer = 0;
  const CustomerNo: string = '';
  const CurrentType: string = '';
  const ACaption: string = ''
  ): Boolean;

var
  Dialog: TdlgDoubleCheck;
begin
  Dialog := TdlgDoubleCheck.Create(Application);
  try
    Result := Dialog.Execute(
      AOperation,
      CheckerNo,
      CheckerPassword,
      FuncNo,
      CustomerNo,
      CurrentType,
      ACaption);
  finally
    Dialog.Free;
  end;
end;

{ TdlgDoubleCheck }

function TdlgDoubleCheck.Execute(
  const AOperation: string;
  var CheckerNo, CheckerPassword: string;
  FuncNo: Integer = 0;
  const CustomerNo: string = '';
  const CurrentType: string = '';
  const ACaption: string = ''
  ): Boolean;
begin
  if ACaption <> '' then
    Caption := ACaption;
  FValid := False;
  WorkView.FieldByName('功能号').DefaultValue := FuncNo;
  WorkView.FieldByName('货币类型').DefaultValue := CurrentType;
  WorkView.FieldByName('客户号').DefaultValue := CustomerNo;
  WorkView.Reset;
  ActiveControl := edOperator;
  ShowModal;
  Result := FValid;
  if Result then
  begin
    CheckerNo := WorkView.FieldByName('复核柜员代码').Data.AsString;
    CheckerPassword := WorkView.FieldByName('复核密码').Data.AsString;
  end;
end;

procedure TdlgDoubleCheck.btnCancelClick(Sender: TObject);
begin
  FValid := False;
  Close;
end;

procedure TdlgDoubleCheck.MainRequestAfterExec(Request: TWVRequest;
  Command: TWVCommand);
begin
  CheckCommandReturnValue(Command);
end;

procedure TdlgDoubleCheck.btnOkClick(Sender: TObject);
begin
  Context.GetDialogSystem.ShowWaiting(SWaitingOperation);
  try
    try
      MainRequest.SendCommand;
      FValid := True;
      Close;
    finally
      Context.GetDialogSystem.CloseWaiting;
    end;
  except
    on E: Exception do
    begin
      FValid := False;
      Context.GetExceptionHandler.HandleException(E);
      SelectFirst;
    end;
  end;
end;

procedure TdlgDoubleCheck.FormCreate(Sender: TObject);
begin
  RegisterModule(Self);
end;

procedure TdlgDoubleCheck.WorkViewFieldsMonitors0ValidChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  btnOk.Enabled := Valid;
end;

procedure TdlgDoubleCheck.WorkViewWorkFields0CheckValid(
  WorkField: TWVField);
begin
  if WorkField.Data.AsString = Context.ParamData(svOperatorNoName).AsString then
    WorkField.Valid := False;
end;

end.
