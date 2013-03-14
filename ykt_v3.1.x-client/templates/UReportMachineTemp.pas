unit UReportMachineTemp;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>USimpleQueryTemp
   <What>简单查询界面模版
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}


interface

uses SysUtils, Windows, Messages, Classes, Graphics, Controls,Forms, KSFrameWorks, KSFrames, KSClientConsts,
  Grids, DBGrids, StdCtrls, ImageCtrls, ExtCtrls, UICtrls, WVCmdReq,Commctrl,
  WorkViews, WVCommands, Db, WVDBBinders, RzDBGrid, Dialogs, Buttons,
  ComCtrls, ImgList, ToolWin, RM_Dataset, RM_Common, RM_Class, RM_Preview,
  RM_Designer, RzPanel, RzButton, RM_e_main, RM_e_Xls, RM_e_Jpeg,
  RM_e_Graphic, RM_e_bmp, RM_e_htm;

type
  TfaReportMachineTemp = class(TKSFrame)
    upnlBottom: TUIPanel;
    WorkView: TWorkView;
    MainRequest: TWVRequest;
    WVDBBinder: TWVDBBinder;
    DataSource: TDataSource;
    UIPnlQueryCount: TUIPanel;
    UIPanel2: TUIPanel;
    Image1: TImage;
    LabRecordCount: TLabel;
    Grid: TRzDBGrid;
    ImageList1: TImageList;
    rptReport: TRMReport;
    rmDS: TRMDBDataSet;
    rmdsgnrD: TRMDesigner;
    rmprvwP: TRMPreview;
    tlb1: TRzToolbar;
    btn100: TRzToolButton;
    btnPageWidth: TRzToolButton;
    btnFirst: TRzToolButton;
    btnprevious: TRzToolButton;
    btnNext: TRzToolButton;
    btnLast: TRzToolButton;
    btnExpXls: TRzToolButton;
    btnPagePrint: TRzToolButton;
    btnSetup: TRzToolButton;
    btnDesign: TRzToolButton;
    rzspcr1: TRzSpacer;
    rzspcr2: TRzSpacer;
    rzspcr3: TRzSpacer;
    btnQuery: TBitBtn;
    rmhtmxprt1: TRMHTMExport;
    rmbmpxprt1: TRMBMPExport;
    rmjpgxprt1: TRMJPEGExport;
    SaveDialog: TSaveDialog;
    rmxlsxprt1: TRMXLSExport;
    dlgOpenRpt: TOpenDialog;
    btnOpenRpt: TRzToolButton;
    procedure  btnQueryClick(Sender: TObject);
    procedure  MainRequestAfterExec(Request: TWVRequest;
      Command: TWVCommand);
    procedure DataSourceDataChange(Sender: TObject; Field: TField);
    procedure GridKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure btn100Click(Sender: TObject);
    procedure btnPageWidthClick(Sender: TObject);
    procedure btnFirstClick(Sender: TObject);
    procedure btnpreviousClick(Sender: TObject);
    procedure btnNextClick(Sender: TObject);
    procedure btnLastClick(Sender: TObject);
    procedure btnExpXlsClick(Sender: TObject);
    procedure btnPagePrintClick(Sender: TObject);
    procedure btnSetupClick(Sender: TObject);
    procedure btnDesignClick(Sender: TObject);
    procedure btnOpenRptClick(Sender: TObject);
  private
    {wsn20041230 处理鼠标滚动的消息}
    //Procedure OnMouseWheel (Var Msg :TMsg;var Handled:Boolean);
    //20050316 wsn 在框架中加入取得当前数据集查询的数量的过程
    function  GetCurrentRecordCount:Integer;

  protected
    procedure   DoIt; virtual; // 继承该方法，设置数据
    procedure   SendCommand; virtual; // 继承该方法，处理错误(设置FHaveGotData=False，禁止切换page)
    function    CanDoAction(const ActionID : TCommonActionID) : Boolean; override;
    procedure   InitEx; override;
    procedure   Init; override; //重写workview 中类型为integer,float的值，hanjiwei add it 
  public
    constructor Create(AOwner : TComponent); override;
  end;

var
  faReportMachineTemp: TfaReportMachineTemp;

implementation

{$R *.DFM}

uses KSFrameWorkUtils, SmartCardCommon,TypInfo, DBAIntf,DataTypes,RM_Const, RM_Utils;

{TfaSimpleQueryTemp}

constructor TfaReportMachineTemp.Create(AOwner: TComponent);
begin
  inherited;
  InitializeFlatSB(Grid.Handle);

  DataGrid := Grid;
  //Application.OnMessage:=OnMouseWheel;
end;

function  TfaReportMachineTemp.GetCurrentRecordCount:Integer;
begin
  if (FDataSource<>nil) and
    (FDataSource.Dataset<>nil) and
    (not FDataSource.Dataset.IsEmpty) and
    (FDataSource.DataSet.Active)
  then
  begin
    //ShowMessage(IntToStr(FDataSource.Dataset.RecordCount));
    Result:=FDataSource.Dataset.RecordCount;
  end
  else Result:=0;
end;

{
Procedure TfaReportMachineTemp.OnMouseWheel (Var Msg :TMsg;var Handled:Boolean);
begin 
  if Msg.message = WM_MouseWheel then
  begin
    if Msg.wParam > 0 then
    begin
      if Grid.Focused then
         SendMessage(Grid.Handle,WM_VSCROLL,SB_PAGEUP,0);
    end
    else
    begin
      if Grid.Focused then
         SendMessage(Grid.Handle,WM_VSCROLL,SB_PAGEDOWN,0);
    end;
    Handled:= True;
  end;
end;
}

procedure TfaReportMachineTemp.btnQueryClick(Sender: TObject);
begin
  WorkView.SynchronizeCtrlsToFields;
  if btnQuery.Enabled then
    DoIt;
end;

procedure TfaReportMachineTemp.DoIt;
begin
  WorkView.SynchronizeCtrlsToFields;
  SendCommand;    
end;

procedure TfaReportMachineTemp.SendCommand;
begin
  try
    ShowWaiting(SWaitingQuery);
    MainRequest.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaReportMachineTemp.MainRequestAfterExec(Request: TWVRequest;
  Command: TWVCommand);
begin
  LabRecordCount.Caption:='查询到 '+IntToStr(GetCurrentRecordCount)+' 条记录';
  CheckCommandReturnValue(Command, False);
end;

procedure TfaReportMachineTemp.InitEx;
begin
  inherited;
  if btnQuery.Enabled then
    DoIt;
end;

function TfaReportMachineTemp.CanDoAction(
  const ActionID: TCommonActionID): Boolean;
begin
  Result := inherited CanDoAction(ActionID);
  if ActionID=caPrint then
    //btnPrint.Enabled := Result;
    //pnlReportTool.Visible := Result;
end;

procedure TfaReportMachineTemp.DataSourceDataChange(Sender: TObject;
  Field: TField);
begin
  LabRecordCount.Caption:='查询到 '+IntToStr(GetCurrentRecordCount)+' 条记录';
end;

procedure TfaReportMachineTemp.GridKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if (Key=VK_F8) then
  begin
     DBGridAutoSize(Grid);
  end;

end;

procedure TfaReportMachineTemp.Init;
var
  iwv:Integer;
  icomp:Integer;
  wv:TWorkView;
begin
  inherited;
  //自动初始化Integer的值,hanjiwei add it 20080421
  for icomp := 0 to Self.ComponentCount-1 do
  begin
    if Self.Components[icomp] is TWorkView then
    begin
      wv := TWorkView(Self.Components[icomp]);
      for iwv := 0 to wv.FieldCount-1 do
      begin
        if (wv.Fields[iwv].DataType = kdtInteger) or (wv.Fields[iwv].DataType = kdtFloat) then
          wv.FieldByName(wv.Fields[iwv].Name).DefaultValue := 0
        else if wv.Fields[iwv].DataType = kdtstring then
          wv.FieldByName(wv.Fields[iwv].Name).DefaultValue := '';
      end;
      wv.Reset;
    end;
  end;
end;

procedure TfaReportMachineTemp.btn100Click(Sender: TObject);
begin
  rmprvwP.Zoom := 100;
end;

procedure TfaReportMachineTemp.btnPageWidthClick(Sender: TObject);
begin
  rmprvwP.PageWidth;
end;

procedure TfaReportMachineTemp.btnFirstClick(Sender: TObject);
begin
  rmprvwP.First;
end;

procedure TfaReportMachineTemp.btnpreviousClick(Sender: TObject);
begin
  rmprvwP.Prev;
end;

procedure TfaReportMachineTemp.btnNextClick(Sender: TObject);
begin
  rmprvwP.Next;
end;

procedure TfaReportMachineTemp.btnLastClick(Sender: TObject);
begin
  rmprvwP.Last;
end;

type
  THackExport = class(TRMExportFilter)
  end;

procedure TfaReportMachineTemp.btnExpXlsClick(Sender: TObject);
var
  i: Integer;
  s: string;
begin
  if rmprvwP.Report = nil then
    Exit;

  s := RMLoadStr(SRepFile) + ' (*.rmp)|*.rmp';
  for i := 0 to RMFiltersCount - 1 do
    s := s + '|' + RMFilters(i).FilterDesc + '|' +
        RMFilters(i).FilterExt;

  SaveDialog.Filter := s;
  SaveDialog.FilterIndex := 1;
  if SaveDialog.Execute then
  begin
    rmprvwP.SaveToFile(SaveDialog.FileName, SaveDialog.FilterIndex);
  end;
end;

procedure TfaReportMachineTemp.btnPagePrintClick(Sender: TObject);
begin
  rmprvwP.Print;
end;

procedure TfaReportMachineTemp.btnSetupClick(Sender: TObject);
begin
  rmprvwP.DlgPageSetup;
end;

procedure TfaReportMachineTemp.btnDesignClick(Sender: TObject);
begin
  if Application.MessageBox('对报表设计将影响显示效果，继续进行该操作吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  rptReport.DesignReport;

end;


procedure TfaReportMachineTemp.btnOpenRptClick(Sender: TObject);
begin
  try
  if dlgOpenRpt.Execute then
    rmprvwP.LoadFromFile(dlgOpenRpt.FileName);
  except

  end;
end;

end.
