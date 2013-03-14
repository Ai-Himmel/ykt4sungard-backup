unit UReportTemp;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UReportTemp
   <What>������ӡ���������ģ��
   <Written By> Huang YanLai (������)
   <History>
**********************************************}

interface

uses
  SysUtils, Windows, Messages, Classes, Graphics, Controls,Forms, KSFrameWorks,
  KSFrames, KSClientConsts, StdCtrls, ExtCtrls, ImageCtrls, UICtrls, ComCtrls,
  Spin, WVCmdReq, WorkViews, Dialogs, WVCommands, RPDesignInfo, RPDBDesignInfo,Printers,
  WVDBBinders, RPEasyReports, RPDBVCL,RPCtrls,RPDefines,RPProcessors,Db,RPDB;

type
  TfaReportTemp = class(TKSFrame)
    pcPages: TPageControl;
    tsSearchConditions: TTabSheet;
    UIPanel1: TUIPanel;
    btnQuery: TImageButton;
    btnClear: TImageButton;
    tsResults: TTabSheet;
    UIPanel2: TUIPanel;
    btnPrint: TImageButton;
    btnSetPrinter: TImageButton;
    GroupBox1: TGroupBox;
    rbToPrinter: TRadioButton;
    rbToFile: TRadioButton;
    edFileName: TEdit;
    rbPreview: TRadioButton;
    btnSelectFile: TImageButton;
    ckPageRange: TCheckBox;
    Label3: TLabel;
    WorkView: TWorkView;
    MainRequest: TWVRequest;
    DBReportInfo: TDBReportInfo;
    SaveDialog: TSaveDialog;
    lbPrinterInfo: TLabel;
    GroupBox2: TGroupBox;
    Label1: TLabel;
    edStart: TSpinEdit;
    Label2: TLabel;
    edEnd: TSpinEdit;
    lbStartPage: TLabel;
    lbEndPage: TLabel;
    DataSource: TDataSource;
    WVDBBinder: TWVDBBinder;
    procedure   btnQueryClick(Sender: TObject);
    procedure   btnPrintClick(Sender: TObject);
    procedure   btnClearClick(Sender: TObject);
    procedure   btnSetPrinterClick(Sender: TObject);
    procedure   MainRequestAfterExec(Request: TWVRequest;
                  Command: TWVCommand);
    procedure   btnSelectFileClick(Sender: TObject);
    procedure   ckPageRangeClick(Sender: TObject);
    procedure   rbToFileClick(Sender: TObject);
  private
    FSendCommandWhenDoIt: Boolean;
    FOldOrientation : TPrinterOrientation;
    procedure   UpdatePrinterInfo;
    procedure   UpdatePrintChioceControls;
    
  protected
    FHaveGotData : Boolean;
    FPrinterInstalled : Boolean;
    procedure   DefaultPrint;
    procedure   Init; override;
    procedure   DoIt; virtual; // �̳и÷�������������
    procedure   SendCommand; virtual; // �̳и÷������������(����FHaveGotData=False����ֹ�л�page)
    procedure   InternalSendCommand; virtual; // �̳и÷��������Ͷ������
    procedure   DoPrintReport; virtual; // �̳и÷�������ɱ����ӡ
    procedure   DoPrintToFile; virtual; // �̳и÷��������������ļ�
    function    PrintOneFile(desFileName:string;Attach:boolean):boolean;
    procedure   DoClear; virtual; // �̳и÷����������������
    procedure   BeforePrint; virtual; // �̳и÷�������ɴ�ӡ��ǰ��׼��������������ı����ʽ�ļ���
    procedure   AfterPrint; virtual;  // �̳и÷�������ɴ�ӡ�Ժ����������
    procedure   AfterPreparePrint; virtual; // �̳и÷����������޸Ĳ��ִ�ӡ�ؼ��Ƿ��ӡ�����ԡ�
    function    CanDoAction(const ActionID : TCommonActionID) : Boolean; override;
    procedure   DebugDataSource; override;
    procedure   SystemNotify(NotifyCode : Integer); override;
    procedure   CloseDatasets; virtual; // �����������仯��ʱ��������еĽ������ͬʱ���ô�ӡ������Ч
    property    SendCommandWhenDoIt : Boolean read FSendCommandWhenDoIt write FSendCommandWhenDoIt;
    destructor  Destroy;virtual;
  public
    constructor Create(AOwner : TComponent); override;
  end;

var
  faReportTemp: TfaReportTemp;

implementation

uses KSFrameWorkUtils, DataTypes,DataUsageUtils,TextoutScripts,FileCtrl;

{$R *.DFM}

type
  TWinControlAccess = class(TWinControl);

{ TfaReportTemp }

procedure TfaReportTemp.DoIt;
begin
  CloseDatasets;
  //btnPrint.Enabled := False;
  WorkView.SynchronizeCtrlsToFields;
  FHaveGotData := True;
  if SendCommandWhenDoIt then
    SendCommand;
  if FHaveGotData then
  begin
    btnPrint.Enabled := FPrinterInstalled;
    pcPages.ActivePageIndex := 1;
  end;
end;

procedure TfaReportTemp.SendCommand;
begin
  try
    ShowWaiting(SWaitingQuery);
    InternalSendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaReportTemp.btnQueryClick(Sender: TObject);
begin
  WorkView.SynchronizeCtrlsToFields;
  if btnQuery.Enabled then
    DoIt;
end;

procedure TfaReportTemp.btnPrintClick(Sender: TObject);
begin
  if rbToPrinter.Checked or rbPreview.Checked then
  begin
    if (edEnd.Value<>0) and (edEnd.Value<edStart.Value) then
    begin
      Context.GetDialogSystem.ShowWarning(SEndPageTooSmall);
      Exit;
    end;
  end;
  DoPrintReport;
end;

procedure TfaReportTemp.DoPrintReport;
begin
  DefaultPrint;
end;

procedure TfaReportTemp.btnClearClick(Sender: TObject);
begin
  DoClear;
end;

procedure TfaReportTemp.DoClear;
begin
  ResetOtherInputBox(Self);
  WorkView.Reset;
  pcPages.ActivePageIndex := 0;
  TWinControlAccess(tsSearchConditions).SelectFirst;
end;

procedure TfaReportTemp.btnSetPrinterClick(Sender: TObject);
begin
  if MainForm<>nil then
    MainForm.SetupPrinter;
end;

procedure TfaReportTemp.MainRequestAfterExec(Request: TWVRequest;
  Command: TWVCommand);
begin
  CheckCommandReturnValue(Command);
end;

procedure TfaReportTemp.btnSelectFileClick(Sender: TObject);
begin
  if SaveDialog.Execute then
    edFileName.Text := SaveDialog.FileName;
end;

procedure TfaReportTemp.DoPrintToFile;
begin
  PrintOneFile(edFileName.Text,False);
end;

procedure TfaReportTemp.AfterPrint;
begin
  Printer.Orientation := FOldOrientation;
end;

procedure TfaReportTemp.BeforePrint;
begin
  FOldOrientation := Printer.Orientation;
end;

procedure TfaReportTemp.AfterPreparePrint;
begin

end;

procedure TfaReportTemp.Init;
begin
  inherited;
  if DBReportInfo.Title='' then
    DBReportInfo.Title := Caption;
  DBReportInfo.FileName := GetReportFileName(DBReportInfo.FileName);
  DBReportInfo.TextFormatFileName := GetReportFileName(DBReportInfo.TextFormatFileName);
  if (DBReportInfo.TextFormatFileName='') then
  begin
    rbToFile.Visible := False;
    edFileName.Visible := False;
    btnSelectFile.Visible := False;
    GroupBox1.Height := GroupBox1.Height - 90;
  end;
  ckPageRange.Checked := False;
  rbPreview.Checked := True;
  UpdatePrintChioceControls;

  pcPages.ActivePageIndex := 0;
  TWinControlAccess(tsSearchConditions).SelectFirst;
  UpdatePrinterInfo;
  btnSetPrinter.Enabled := MainForm<>nil;
end;

function TfaReportTemp.CanDoAction(
  const ActionID: TCommonActionID): Boolean;
begin
  if ActionID=caDebugDataSource then
    Result := True else
    Result := inherited CanDoAction(ActionID);
end;

procedure TfaReportTemp.DebugDataSource;
var
  I : Integer;
  DebugSystem : IDebugSystem;
begin
  DebugSystem := Context.GetDebugSystem;
  if DebugSystem<>nil then
  begin
    for I:=0 to RPMaxDatasets-1 do
    begin
      if (DBReportInfo.DataSources[I]<>nil) then
        DebugSystem.DebugDataSource(DBReportInfo.DataSources[I],UICode+'-'+DBReportInfo.DatasetNames[I]);
    end;
  end;
end;

procedure TfaReportTemp.SystemNotify(NotifyCode: Integer);
begin
  inherited;
  if NotifyCode=snPrinterChanged then
  begin
    UpdatePrinterInfo;
  end;
end;

procedure TfaReportTemp.UpdatePrinterInfo;
begin
  FPrinterInstalled := GetPrinterInfoToLabel(lbPrinterInfo);
end;

procedure TfaReportTemp.ckPageRangeClick(Sender: TObject);
begin
  UpdatePrintChioceControls;
end;

procedure TfaReportTemp.rbToFileClick(Sender: TObject);
begin
  UpdatePrintChioceControls;
end;

procedure TfaReportTemp.UpdatePrintChioceControls;
var
  ToFile : Boolean;
begin
  ToFile := rbToFile.Checked;
  edStart.Enabled := ckPageRange.Checked and not ToFile;
  edEnd.Enabled := ckPageRange.Checked and not ToFile;
  edFileName.Enabled := ToFile;
  btnSelectFile.Enabled := ToFile;
end;

procedure TfaReportTemp.CloseDatasets;
var
  I : Integer;
  Field : TWVField;
  Obj : TObject;
begin
  for I:=0 to WorkView.FieldCount-1 do
  begin
    Field := WorkView.Fields[I];
    if Field.DataType=kdtObject then
    begin
      Obj := Field.Data.AsObject;
      if Obj is TDataset then
        Field.Data.Clear;
    end;
  end;
  btnPrint.Enabled := False;
end;

procedure TfaReportTemp.InternalSendCommand;
begin
  MainRequest.SendCommand;
end;

procedure TfaReportTemp.DefaultPrint;
var
  StartPage, EndPage : Integer;
begin
  BeforePrint;
  try
    if rbToFile.Checked then
    begin
      DoPrintToFile;
    end else
    begin
      DBReportInfo.PrepareReport;
      AddSystemParams(DBReportInfo.VariantValues);
      AfterPreparePrint;
      if ckPageRange.Checked then
      begin
        StartPage := edStart.Value;
        EndPage := edEnd.Value;
      end else
      begin
        StartPage := 0;
        EndPage := 0;
      end;
      if rbToPrinter.Checked then
        DBReportInfo.Print(StartPage,EndPage) else
      begin
        if (EndPage=0) or (EndPage-StartPage>MaxPreviewPageCount) then
          EndPage := StartPage+MaxPreviewPageCount;
        DBReportInfo.Preview(StartPage,EndPage);
      end;
    end;
  finally
    AfterPrint;
  end;
end;

constructor TfaReportTemp.Create(AOwner: TComponent);
begin
  inherited;
  FSendCommandWhenDoIt := True;
end;

destructor TfaReportTemp.Destroy;
begin
  inherited Destroy;
end;

function TfaReportTemp.PrintOneFile(desFileName: string;
  Attach: boolean): boolean;
var
  ScriptContext : TScriptContext;
  Environment:TRPDataEnvironment;
  tofFileName:string;
  OutputStrs:TstringList;
  FullOutputStrs:TstringList;
  i:integer;
  DataSourceName:string;
  oDataSource:TDataSource;
  TempFileName:string;
begin
  Result := False;
  TempFileName := desFileName + '.tmp';
  if not DirectoryExists(ExTractFileDir(desFileName)) then
  begin
    context.GetDialogSystem.ShowError('Ŀ���ļ�·�������ڣ����飡');
    exit;
  end;
  tofFileName:=DBReportInfo.TextFormatFileName;
  tofFileName := GetFileName(dkReport,tofFileName);
  if not FileExists (tofFileName) then
  begin
    context.GetDialogSystem.ShowError('tof�ļ������ڣ�');
    exit;
  end;

  OutputStrs := TstringList.Create;
  FullOutputStrs := TstringList.Create;
  Environment:=TRPDataEnvironment.Create(application);
  ScriptContext := TScriptContext.Create(application);
  Environment.VariantValues :=  DBReportInfo.VariantValues;
  ScriptContext.Environment := Environment;

  ScriptContext.LoadScripts(tofFileName);
  for i := 0 to TRPDBDataEntries(DBReportInfo.DataEntries).DatasetCount-1 do
  begin
    DataSourceName := TRPDBDataEntries(DBReportInfo.DataEntries).Datasets[i].DatasetName;
    oDataSource := TRPDBDataEntries(DBReportInfo.DataEntries).Datasets[i].DataSource;
    ScriptContext.DataEntries.AddDatasource(DataSourceName,oDataSource);
  end;

  try
    if Attach then
    begin
      ScriptContext.Output(TempFileName); //���
      OutputStrs.LoadFromFile(TempFileName);
      if FileExists(desFileName) then
        FullOutputStrs.LoadFromFile(desFileName);
      FullOutputStrs.AddStrings(OutputStrs);
      FullOutputStrs.SaveToFile(desFileName);
    end
    else
    begin
      ScriptContext.Output(desFileName); //���
    end;
    Result := True;
  except
    Context.GetDialogSystem.ShowError('������ı�����');
  end;
  OutputStrs.Free;
  FullOutputStrs.Free;
  Environment.free;
  ScriptContext.Free;
end;

end.
