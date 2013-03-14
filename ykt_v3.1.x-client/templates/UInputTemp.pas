unit UInputTemp;
{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UInputTemp
   <What>�����������ģ��
   <Written By> Huang YanLai (������)
   <History>
**********************************************}


interface

uses SysUtils, Windows, Messages, Classes, Graphics, Controls,Forms, KSFrameWorks, KSFrames, KSClientConsts,
  StdCtrls, ImageCtrls, ExtCtrls, UICtrls, WorkViews, WVCmdReq, WVCommands,
  Buttons;

type
  TfaInputTemp = class(TKSFrame)
    UIPanel1: TUIPanel;
    btnOK: TBitBtn;
    btnCancel: TBitBtn;
    WorkView: TWorkView;
    MainRequest: TWVRequest;
    procedure   btnCancelClick(Sender: TObject);
    procedure   btnOKClick(Sender: TObject);
    procedure   MainRequestAfterExec(Request: TWVRequest;
      Command: TWVCommand);
    procedure   PwdEditKeyPress(Sender: TObject; var Key: Char);
  private
    FTimeStamp: Integer;
  protected
    procedure   DoIt; virtual; // �̳и÷�������������
    procedure   SendCommand; virtual; // �̳и÷������������
    procedure   DoCancel; virtual; // �̳и÷����������������
    procedure   Init; override;
  public
    procedure   Reset; virtual;
    property    TimeStamp : Integer read FTimeStamp;
  end;

var
  faInputTemp: TfaInputTemp;

implementation

uses KSFrameWorkUtils;

{$R *.DFM}

{ TfaInputTemp }

procedure TfaInputTemp.Reset;
begin
  ResetOtherInputBox(Self);
  WorkView.Reset;
  FTimeStamp := WorkView.TimeStamp;
  SelectFirst;
end;

procedure TfaInputTemp.btnCancelClick(Sender: TObject);
begin
  DoCancel;
end;

procedure TfaInputTemp.btnOKClick(Sender: TObject);
begin
  WorkView.SynchronizeCtrlsToFields;
  if btnOK.Enabled then
    DoIt;
end;

procedure TfaInputTemp.DoIt;
begin
  WorkView.SynchronizeCtrlsToFields;
  SendCommand;
end;

procedure TfaInputTemp.SendCommand;
begin
  try
    ShowWaiting(SWaitingOperation);
    MainRequest.SendCommand;
  finally
    CloseWaiting;
    SelectFirst;
  end;
end;

procedure TfaInputTemp.DoCancel;
begin
  if FTimeStamp=WorkView.TimeStamp then
  begin
    if Context.GetDialogSystem.Confirm('�ر�'+Caption)=uaYes then
      Close;
  end else
    Reset;
end;

procedure TfaInputTemp.MainRequestAfterExec(Request: TWVRequest;
  Command: TWVCommand);
begin
  CheckCommandReturnValue(Command);
end;

procedure TfaInputTemp.Init;
begin
  inherited;
  WorkView.Reset;
end;

procedure TfaInputTemp.PwdEditKeyPress(Sender: TObject; var Key: Char);
var
  Field : TWVField;
begin
  Field := WVGetField(Sender);
  if (Field<>nil) and (Key=' ') then
  begin
    Key := #0;
    if InputCustomerPasswordForField(Field) then
      Key := #13;
  end;
end;

end.
