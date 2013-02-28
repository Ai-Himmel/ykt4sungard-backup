unit UQueryTemp;
{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UQueryTemp
   <What>查询操作界面模版
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}


interface

uses SysUtils, Windows, Messages, Classes, Graphics, Controls,Forms, KSFrameWorks, KSFrames, KSClientConsts,
  WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls, ComCtrls, Grids, DBGrids, Db,
  WVDBBinders, DataUsageUtils, WVCommands, UIStyles, Buttons;

type
  TfaQueryTemp = class(TKSFrame)
    WorkView: TWorkView;
    MainRequest: TWVRequest;
    pcPages: TPageControl;
    tsSearchConditions: TTabSheet;
    tsResults: TTabSheet;
    UIPanel1: TUIPanel;
    btnQuery: TBitBtn;
    UIPanel2: TUIPanel;
    btnClear: TBitBtn;
    DataSource: TDataSource;
    Grid: TDBGrid;
    WVDBBinder: TWVDBBinder;
    btnPrint: TImageButton;
    procedure   btnQueryClick(Sender: TObject);
    procedure   btnClearClick(Sender: TObject);
    procedure   btnPrintClick(Sender: TObject);
    procedure   MainRequestAfterExec(Request: TWVRequest;
      Command: TWVCommand);
  private

  protected
    FHaveGotData : Boolean;
    procedure   Init; override;
    procedure   DoIt; virtual; // 继承该方法，设置数据
    procedure   SendCommand; virtual; // 继承该方法，处理错误(设置FHaveGotData=False，禁止切换page)
    procedure   DoClear; virtual; // 继承该方法，清除输入数据
    function    CanDoAction(const ActionID : TCommonActionID) : Boolean; override;
    procedure   InitEx; override;
  public
    constructor Create(AOwner : TComponent); override;
  end;

var
  faQueryTemp: TfaQueryTemp;

implementation

uses KSFrameWorkUtils;

{$R *.DFM}

type
  TWinControlAccess = class(TWinControl);

constructor TfaQueryTemp.Create(AOwner: TComponent);
begin
  inherited;
  DataGrid := Grid;
end;

procedure TfaQueryTemp.btnQueryClick(Sender: TObject);
begin
  WorkView.SynchronizeCtrlsToFields;
  if btnQuery.Enabled then
    DoIt;
end;

procedure TfaQueryTemp.Init;
begin
  inherited;
  pcPages.ActivePageIndex := 0;
  TWinControlAccess(tsSearchConditions).SelectFirst;
end;

procedure TfaQueryTemp.btnClearClick(Sender: TObject);
begin
  DoClear;
end;

procedure TfaQueryTemp.DoIt;
begin
  WorkView.SynchronizeCtrlsToFields;
  FHaveGotData := True;
  SendCommand;
  if FHaveGotData then
    pcPages.ActivePageIndex := 1;
end;

procedure TfaQueryTemp.SendCommand;
begin
  try
    ShowWaiting(SWaitingQuery);
    MainRequest.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaQueryTemp.DoClear;
begin
  ResetOtherInputBox(Self);
  WorkView.Reset;
  pcPages.ActivePageIndex := 0;
  TWinControlAccess(tsSearchConditions).SelectFirst;
end;

procedure TfaQueryTemp.btnPrintClick(Sender: TObject);
begin
  DoPrint;
end;

procedure TfaQueryTemp.MainRequestAfterExec(Request: TWVRequest;
  Command: TWVCommand);
begin
  CheckCommandReturnValue(Command);
end;

function TfaQueryTemp.CanDoAction(
  const ActionID: TCommonActionID): Boolean;
begin
  Result := inherited CanDoAction(ActionID);
  if ActionID=caPrint then
    btnPrint.Enabled := Result;
end;

procedure TfaQueryTemp.InitEx;
begin
  inherited;
  if btnQuery.Enabled then
    DoIt;
end;

end.
