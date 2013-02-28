unit UParamsRptTemp;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>USetParamsTemp
   <What>参数设置操作界面模版
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}


interface

uses SysUtils, Windows, Messages, Classes, Graphics, Controls,Forms, KSFrameWorks, KSFrames, KSClientConsts,
  ComCtrls, Grids, DBGrids, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,Commctrl,
  WVDBBinders, WVCmdReq, WorkViews, Db, WVCommands, DBCtrls, DBActns,
  ActnList, RzDBGrid, RzTabs, RzDBNav, RzButton, RzRadChk,Dialogs, Buttons,
  ImgList, RM_e_Xls, RM_e_Jpeg, RM_e_Graphic, RM_e_bmp, RM_Common,
  RM_Class, RM_e_main, RM_e_htm, RM_Preview, RM_Designer, RM_Dataset,
  RzPanel;
{
const
  TabMargin = 3;
}
type
  // 参数设置界面的状态
  TSettingStatus = (
    ssBrowse,         // 浏览状态
    ssAdd,            // 增加状态
    ssChange,         // 修改状态
    ssDelete,         // 删除状态
    ssViewDetail      // 浏览细节数据状态
    );

  // 数据维护形式
  TParamMaintainType = (
    pmtCenter,        // 总部维护数据
    pmtDepartment     // 营业部维护数据
    );

  TfaParamsRptTemp = class(TKSFrame)
    DataSource: TDataSource;
    WorkView: TWorkView;
    QueryRequest: TWVRequest;
    QueryBinder: TWVDBBinder;
    AddRequest: TWVRequest;
    DeleteRequest: TWVRequest;
    ChangeRequest: TWVRequest;
    WVDataSource: TWVDataSource;
    alDatasetActions: TActionList;
    DataSetFirst: TDataSetFirst;
    DataSetPrior: TDataSetPrior;
    DataSetNext: TDataSetNext;
    DataSetLast: TDataSetLast;
    pcPages: TRzPageControl;
    tsQuery: TRzTabSheet;
    tsEdit: TRzTabSheet;
    UIPanel2: TUIPanel;
    btnOK: TBitBtn;
    btnCancel: TBitBtn;
    DBNavigator: TRzDBNavigator;
    UIPanel1: TUIPanel;
    btnQuery: TBitBtn;
    btnAdd: TBitBtn;
    btnChange: TBitBtn;
    btnDelete: TBitBtn;
    btnViewDetail: TBitBtn;
    ckAutoSetNewParams: TRzCheckBox;
    UIPnlQueryCount: TUIPanel;
    LabRecordCount: TLabel;
    Grid: TRzDBGrid;
    rmprvwP: TRMPreview;
    rmhtmxprt1: TRMHTMExport;
    rmbmpxprt1: TRMBMPExport;
    rmjpgxprt1: TRMJPEGExport;
    rmxlsxprt1: TRMXLSExport;
    ImageList1: TImageList;
    SaveDialog: TSaveDialog;
    dlgOpenRpt: TOpenDialog;
    rmdsgnrD: TRMDesigner;
    rmDS1: TRMDBDataSet;
    rptQRpt: TRMReport;
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
    btnOpenRpt: TRzToolButton;
    procedure   btnAddClick(Sender: TObject);
    procedure   btnChangeClick(Sender: TObject);
    procedure   btnQueryClick(Sender: TObject);
    procedure   btnDeleteClick(Sender: TObject);
    procedure   btnOKClick(Sender: TObject);
    procedure   btnCancelClick(Sender: TObject);
    procedure   CheckReturnData(Request: TWVRequest;
      Command: TWVCommand);
    procedure   pcPagesDrawTab(Control: TCustomTabControl; TabIndex: Integer;
      const Rect: TRect; Active: Boolean);
    procedure   DataSourceDataChange(Sender: TObject; Field: TField);
    procedure   DataSourceStateChange(Sender: TObject);
    procedure   btnViewDetailClick(Sender: TObject);
    procedure   CheckEditFieldValid(WorkField: TWVField);
    procedure   DBNavigatorClick(Sender: TObject; Button: TNavigateBtn);
    procedure   GridDrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
    procedure   GridKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure alDatasetActionsExecute(Action: TBasicAction;
      var Handled: Boolean);
    procedure alDatasetActionsUpdate(Action: TBasicAction;
      var Handled: Boolean);
    procedure GridTitleClick(Column: TColumn);
    procedure pcPagesPaintTabBackground(Sender: TObject; ACanvas: TCanvas;
      ATabIndex: Integer; const ARect: TRect; var Handled: Boolean);
    procedure pcPagesChanging(Sender: TObject; NewIndex: Integer;
      var AllowChange: Boolean);
    procedure DataSetPriorExecute(Sender: TObject);
    procedure GridDblClick(Sender: TObject);
    procedure GridMouseEnter(Sender: TObject);
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
    FStatus:    TSettingStatus;
    FAutoRefresh : Boolean;
    FCanEdit : Boolean;   //允许增加、修改、删除
    FCanDelete: Boolean;  // 允许删除
    FCanAdd: Boolean;     // 允许增加
    FCanChange: Boolean;  // 允许修改
    FLocalDepartment : string;  // 发起营业部代码
    procedure   SetStatus(const Value: TSettingStatus);

    procedure   CheckDataCanEdit;
    {wsn20041230 处理鼠标滚动的消息}
    Procedure OnMouseWheel (Var Msg :TMsg;var Handled:Boolean);
    procedure RedrawBorder(const Clip: HRGN);
  protected
    FEditSucceed : Boolean;
    FDepartmentFieldName : string;
    FDepartmentWVField : TWVField;
    FMaintainType: TParamMaintainType;
    procedure   Init; override;
    procedure   EnableEditCtrls(AEnabled : Boolean); virtual; // 控制控件是否可以编辑
    procedure   BeforeAdd; virtual; // 继承该方法，增加初始化部分
    procedure   BeforeChange; virtual; // 继承该方法，增加初始化部分
    procedure   BeforeDelete; virtual; // 继承该方法，增加初始化部分
    procedure   BeforeViewDetail{(IsFirst : Boolean=True)}; virtual; // 继承该方法，增加初始化部分
    procedure   CancelEdit; virtual; // 继承该方法，增加清除数据部分
    procedure   DoAdd; virtual; // 继承该方法，设置EditRequest
    procedure   DoChange; virtual; // 继承该方法，设置EditRequest
    procedure   DoDelete; virtual; // 继承该方法，设置EditRequest
    procedure   SendEditCommand(Request : TWVRequest); virtual; // 继承该方法，处理设置（增加、修改、删除）错误，设置FEditSucceed
    function    GetCurrentRecordInfo : string; virtual; // 继承该方法，返回一行数据的描述（用于删除数据）
    procedure   DoQuery; virtual; // 继承该方法，设置查询数据
    procedure   SendQueryCommand; virtual; // 继承该方法，处理查询错误
    procedure   EnableEdit(CanEdit : Boolean);  // 废除
    procedure   UpdateButton; // 更新按键的Enabled状态
    function    InternalGetCanEdit : Boolean; virtual; // 判断是否可以修改：根据数据维护类型和当前营业部控制FCanEdit属性
    procedure   InitEx; override;   // 特殊的初始化，支持自动查询
    procedure   StatusChanged; virtual; // 界面操作状态发生改变，调用 DisplayData
    procedure   DisplayData; virtual;   // 将数据从数据集里面显示出来（同步到工作视图）。如果使用特殊的特殊的控件需要重载此方法。
    procedure   SaveModifiedData; virtual;  // 将修改的数据同步到工作视图。如果使用特殊的控件需要重载此方法。
    function    ConfirmEdit : Boolean; virtual; // 返回是否允许修改。在按下确认的时候被调用。可以在这里弹出对话框提示确认或者复核。
    //20050316 wsn 在框架中加入取得当前数据集查询的数量的过程
    function    GetCurrentRecordCount:Integer;virtual;

  public
    constructor Create(AOwner : TComponent); override;
    
    procedure   SetCanAdd(const Value: Boolean);
    procedure   SetCanChange(const Value: Boolean);
    procedure   SetCanDelete(const Value: Boolean);

    procedure   CloseDataset; override;
    property    Status : TSettingStatus read FStatus write SetStatus;
    property    AutoRefresh : Boolean read FAutoRefresh write FAutoRefresh default True;
    property    CanAdd : Boolean read FCanAdd write SetCanAdd default True;
    property    CanChange : Boolean read FCanChange write SetCanChange default True;
    property    CanDelete : Boolean read FCanDelete write SetCanDelete default True;
    property    MaintainType : TParamMaintainType read FMaintainType;
  end;

var
  faParamsRptTemp: TfaParamsRptTemp;

implementation

uses KSFrameWorkUtils, DataUsageUtils, LogFile, SmartCardCommon,TypInfo, DBAIntf,DataTypes
  ,RM_Const, RM_Utils;

{$R *.DFM}

type
  TWinControlAccess = class(TWinControl);

{ TfaSetParamsTemp }

constructor TfaParamsRptTemp.Create(AOwner: TComponent);
begin
  inherited;
  DataGrid := Grid;
  FStatus := ssBrowse;
  FCanEdit := True;
  FCanDelete := True;
  FCanAdd := True;
  FCanChange := True;
  FAutoRefresh := True;
  InitializeFlatSB(Grid.Handle);
  //Application.OnMessage:=OnMouseWheel;
end;


function  TfaParamsRptTemp.GetCurrentRecordCount:Integer;
begin
  if (FDataSource<>nil) and
    (FDataSource.Dataset<>nil) and
    (not FDataSource.Dataset.IsEmpty) and
    (FDataSource.DataSet.Active)
  then
    Result:=FDataSource.Dataset.RecordCount
  else Result:=0;
end;


Procedure TfaParamsRptTemp.OnMouseWheel (Var Msg :TMsg;var Handled:Boolean);
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



procedure TfaParamsRptTemp.btnAddClick(Sender: TObject);
begin
  Status := ssAdd;
end;

procedure TfaParamsRptTemp.Init;
var
  iwv:Integer;
  icomp:Integer;
  wv:TWorkView;
begin
  inherited;
  //初始化类型为integer ,float的值为0;hanjiwei add it 
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

  //FAutoRefresh := False;
  FAutoRefresh := True;
  ckAutoSetNewParams.Checked := True;
  FDepartmentFieldName := 'sbranch_code0';
  FDepartmentWVField := nil;
  FLocalDepartment := Context.ParamData(svDepartNoName).AsString;
  FMaintainType := pmtCenter;
  pcPages.ActivePageIndex := 0;
  //pcPages.OwnerDraw := True;
  tsEdit.Caption := '报表';//SSet;
  TWinControlAccess(tsQuery).SelectFirst;
  CheckDataCanEdit;
end;

procedure TfaParamsRptTemp.btnChangeClick(Sender: TObject);
begin
  Status := ssChange;
end;

procedure TfaParamsRptTemp.SetStatus(const Value: TSettingStatus);
begin
  // 完成状态转换
  if FStatus <> Value then
  begin
    FStatus := Value;
    if FStatus=ssBrowse then
    begin
      // 浏览状态
      tsQuery.Enabled := True;
      tsEdit.Enabled := False;
      tsEdit.Caption := '报表';//SSet;
      pcPages.ActivePageIndex := 0;
      TWinControlAccess(tsQuery).SelectFirst;
    end else
    begin
      tsQuery.Enabled := False;
      tsEdit.Enabled := True;
      pcPages.ActivePageIndex := 1;
      case Status of
        ssAdd : BeforeAdd;
        ssChange : BeforeChange;
        ssDelete : BeforeDelete;
        ssViewDetail : BeforeViewDetail{(True)};
      end;
      TWinControlAccess(tsEdit).SelectFirst;
      
    end;
    btnOK.Visible := Status in [ssAdd,ssChange,ssDelete];
    DBNavigator.Visible := Status = ssViewDetail;
    WorkView.CheckValid;
    StatusChanged;
    if (Status = ssDelete) and btnOK.Enabled and btnOK.Visible then btnOK.SetFocus;
  end;
end;

procedure TfaParamsRptTemp.btnQueryClick(Sender: TObject);
begin
  WorkView.SynchronizeCtrlsToFields;
  if btnQuery.Enabled then
    DoQuery;
end;

procedure TfaParamsRptTemp.BeforeAdd;
begin
  tsEdit.Caption := '报表';//SAdd;
  // 所有的输入项目可以编辑
  EnableEditCtrls(True);
  // 初始化所有输入项目
  WorkView.Reset(WVDataSource.GroupIndex);
end;

procedure TfaParamsRptTemp.BeforeChange;
begin
  tsEdit.Caption := '报表';//SChange;
  // 所有的输入项目可以编辑
  // 由子类重载该方法，禁止主键可以编辑
  EnableEditCtrls(True);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaParamsRptTemp.BeforeDelete;
begin
  tsEdit.Caption := '报表';//SDelete;
  // 所有的输入项目都不可以编辑
  EnableEditCtrls(False);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaParamsRptTemp.btnDeleteClick(Sender: TObject);
begin
  {
  case Context.GetDialogSystem.Confirm(Format('删除%s吗？',[GetCurrentRecordInfo])) of
    uaYes : DoDelete;
    uaNo : ;
    uaCancel : ;
  end;
  }
  Status := ssDelete;
end;

function TfaParamsRptTemp.GetCurrentRecordInfo: string;
begin
  Result := '';
end;

procedure TfaParamsRptTemp.CancelEdit;
begin
  Status := ssBrowse;
end;

procedure TfaParamsRptTemp.DoAdd;
begin
  // 同步修改的数据到工作视图，提交请求，如果成功(FEditSucceed=True而且没有意外抛出)，恢复状态为浏览
  SaveModifiedData;
  SendEditCommand(AddRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaParamsRptTemp.DoChange;
begin
  // 同步修改的数据到工作视图，提交请求，如果成功(FEditSucceed=True而且没有意外抛出)，恢复状态为浏览
  SaveModifiedData;
  SendEditCommand(ChangeRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaParamsRptTemp.DoDelete;
begin
  // 同步修改的数据到工作视图，提交请求，如果成功(FEditSucceed=True而且没有意外抛出)，恢复状态为浏览
  SaveModifiedData;
  SendEditCommand(DeleteRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaParamsRptTemp.DoQuery;
begin
  try
    CloseDataSet;
    WorkView.SynchronizeCtrlsToFields;
    SendQueryCommand;
  except
    HandleException;
    CloseDataSet;
  end;
end;

procedure TfaParamsRptTemp.SendQueryCommand;
begin
  try
    ShowWaiting(SWaitingQuery);
    QueryRequest.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaParamsRptTemp.btnOKClick(Sender: TObject);
var
  NeedDoRefresh : Boolean;
begin
  WorkView.SynchronizeCtrlsToFields;
  TWinControlAccess(tsEdit).SelectFirst;
  if btnOk.Enabled and ConfirmEdit then
  begin
    NeedDoRefresh := True;
    case Status of
      ssAdd :
        DoAdd;
      ssChange:
        DoChange;
      ssDelete :
        DoDelete;
      ssViewDetail :
        begin
          Assert(False,'never run into there!');
          {
          Status := ssBrowse;
          NeedDoRefresh := False; // not Refresh
          }
        end;
    else  Assert(False);
    end;
    if (Status=ssBrowse) and NeedDoRefresh and AutoRefresh then
      //DoQuery;
  end;
end;

procedure TfaParamsRptTemp.btnCancelClick(Sender: TObject);
begin
  CancelEdit;
end;

procedure TfaParamsRptTemp.SendEditCommand(Request : TWVRequest);
begin
  FEditSucceed := True;
  try
    ShowWaiting(SWaitingOperation);
    Request.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaParamsRptTemp.EnableEdit(CanEdit: Boolean);
begin
  //FCanEdit := CanEdit;
  //UpdateButton;
end;

procedure TfaParamsRptTemp.CheckReturnData(Request: TWVRequest;
  Command: TWVCommand);
begin
  LabRecordCount.Caption:='查询到 '+IntToStr(GetCurrentRecordCount)+' 条记录';
  CheckCommandReturnValue(Command);
end;

procedure TfaParamsRptTemp.pcPagesDrawTab(Control: TCustomTabControl;
  TabIndex: Integer; const Rect: TRect; Active: Boolean);
var
  ARect : TRect;
begin
  if pcPages.Pages[TabIndex].Enabled then
    Control.Canvas.Font.Color := clWindowText else
    Control.Canvas.Font.Color := clGrayText;
  ARect := Rect;
  Windows.DrawText(Control.Canvas.Handle,PChar(pcPages.Pages[TabIndex].Caption),-1,
    ARect,DT_CENTER or DT_VCENTER or DT_SINGLELINE);
end;

procedure TfaParamsRptTemp.EnableEditCtrls(AEnabled: Boolean);
{
var
  I : Integer;
  Ctrl : TControl;
}
begin
  {
  for I:=0 to tsEdit.ControlCount-1 do
  begin
    Ctrl := tsEdit.Controls[I];
    if not (Ctrl is TPageControl) then
      Ctrl.Enabled := AEnabled;
  end;
  UIPanel2.Enabled := True;
  }
  MakeChildrenReadOnly(tsEdit,not AEnabled);
  UIPanel2.Enabled := True;
  MakeChildrenReadOnly(UIPanel2,False);
end;

procedure TfaParamsRptTemp.DataSourceDataChange(Sender: TObject;
  Field: TField);
begin
  if Field=nil then
  begin
    CheckDataCanEdit;
    if Status=ssViewDetail then
      DisplayData;
    LabRecordCount.Caption:='查询到 '+IntToStr(GetCurrentRecordCount)+' 条记录';
  end;
end;

procedure TfaParamsRptTemp.SetCanAdd(const Value: Boolean);
begin
  FCanAdd := Value;
  UpdateButton;
end;

procedure TfaParamsRptTemp.SetCanChange(const Value: Boolean);
begin
  FCanChange := Value;
  UpdateButton;
end;

procedure TfaParamsRptTemp.SetCanDelete(const Value: Boolean);
begin
  FCanDelete := Value;
  UpdateButton;
end;

procedure TfaParamsRptTemp.UpdateButton;
begin
  FCanEdit := InternalGetCanEdit;
  btnAdd.Enabled := FCanEdit and CanAdd;
  btnDelete.Enabled := FCanEdit and CanDelete;
  btnChange.Enabled := FCanEdit and CanChange;
end;

procedure TfaParamsRptTemp.CloseDataset;
begin
  inherited;
  if QueryBinder.Field<>nil then
    QueryBinder.Field.Data.Clear;
end;

function TfaParamsRptTemp.InternalGetCanEdit: Boolean;
begin
  // 根据数据维护类型和当前营业部控制FCanEdit属性
  // 少数子类可以重载该方法，提供特殊的控制
{  case FMaintainType of
    pmtCenter : Result := IsCenterDepartment;
    pmtDepartment : Result := (FDepartmentWVField<>nil) and (FLocalDepartment=FDepartmentWVField.Data.AsString);
  else
    Result := False;
  end;
  }
  Result:=True;
end;

procedure TfaParamsRptTemp.DataSourceStateChange(Sender: TObject);
begin
  CheckDataCanEdit;    
end;

procedure TfaParamsRptTemp.CheckDataCanEdit;
var
  DepartField : TField;
  SameDepart : Boolean;
begin
  if (DataSource.DataSet=nil) or (DataSource.DataSet.IsEmpty) or not DataSource.DataSet.Active then
  begin
    //无查询结果数据，禁止修改、删除，允许增加
    FCanDelete := False;
    FCanChange := False;
    FCanAdd := True;
    btnViewDetail.Enabled := False;
  end else
  begin
    //有查询数据，
    if (FDepartmentFieldName<>'') and (FMaintainType=pmtDepartment) then
    begin
      // 如果是营业部维护数据，那么需要根据返回数据检查营业部，只能修改和删除本营业部的数据
      DepartField:= DataSource.DataSet.FindField(FDepartmentFieldName);
      SameDepart := (DepartField<>nil) and (DepartField.AsString=FLocalDepartment);
    end else
      // 否则不需要检查营业部，允许编辑
      SameDepart := True;
    FCanAdd := True;
    FCanDelete := SameDepart;
    FCanChange := SameDepart;
    btnViewDetail.Enabled := True;
  end;
  UpdateButton;
end;

procedure TfaParamsRptTemp.BeforeViewDetail{(IsFirst : Boolean=True)};
begin
  tsEdit.Caption := '报表';//SViewDetail;
  // 所有的输入项目都不可以编辑
  EnableEditCtrls(False);
end;

procedure TfaParamsRptTemp.btnViewDetailClick(Sender: TObject);
begin
  // 如果没有数据集，或数据集为空就返回 add by 汤成
  if (DataSource.DataSet<>nil) and (not DataSource.DataSet.IsEmpty) then
    Status := ssViewDetail
  else
    Exit;
  //
  if datasource.DataSet.RecNo = datasource.DataSet.RecordCount then
    datasource.DataSet.Last;
end;

procedure TfaParamsRptTemp.CheckEditFieldValid(WorkField: TWVField);
begin
  if not (status in [ssAdd, ssChange]) then
    WorkField.Valid := True;
end;

procedure TfaParamsRptTemp.DBNavigatorClick(Sender: TObject;
  Button: TNavigateBtn);
begin
  if datasource.DataSet.RecNo = datasource.DataSet.RecordCount then
  begin
    datasource.DataSet.Last;
  end;
  if datasource.DataSet.RecNo = 0 then
  begin
    datasource.DataSet.First;
  end;

end;

procedure TfaParamsRptTemp.InitEx;
begin
  inherited;
  if btnQuery.Enabled then
    DoQuery;
end;

procedure TfaParamsRptTemp.StatusChanged;
begin
  if (Status in [ssChange,ssDelete,ssViewDetail]) then
    DisplayData
  else if (Status=ssAdd) and
    ckAutoSetNewParams.Checked and
    (WVDataSource.DataSource<>nil) and
    (WVDataSource.DataSource.Dataset<>nil) and
    not WVDataSource.DataSource.Dataset.IsEmpty
  then
    DisplayData;
end;

procedure TfaParamsRptTemp.DisplayData;
begin
  // 将数据从数据源同步到工作视图（再到各种控件）。注意：一些子类需要重载该方法，控制特殊控件的数据同步。
  WorkView.Reset(WVDataSource.GroupIndex);
  if DataSource.Dataset<>nil then
    WVDataSource.DataSourceToWorkView;
end;

procedure TfaParamsRptTemp.SaveModifiedData;
begin
  // 将修改的数据同步到工作视图。如果使用特殊的控件需要重载此方法。
  WorkView.SynchronizeCtrlsToFields;
end;


procedure TfaParamsRptTemp.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
var
  FRect:TRect;
begin
  with Grid do
  begin
    if ((State = [gdSelected]) or (State=[gdSelected,gdFocused])) then
    begin
      Canvas.Font.Color :=ClYellow;
      Canvas.Brush.Color :=ClNavy;
    end
    else
    begin
      if DataSource.DataSet.RecNo mod 2<>0 then {判断当前数据是奇数还是偶数行}
      Canvas.brush.Color :=clInfoBk {如果是奇数行，DBGrid背景以白色显示}
    else
      Canvas.brush.Color :=$00EBDED0; {如果是偶数行$00EBDED0，DBGrid背景以浅灰色显示}
    end;
    DefaultDrawColumnCell(Rect, DataCol, Column, State); {这行很关键的，一定不要遗漏了}
  end;
  DBGridRecordSize(Column);
  if FDepartmentWVField=nil then Exit;
  if FDepartmentWVField.Data.AsString=CenterDepartNo then
    DrawCellForSysParams(TDBGrid(Sender),Rect,DataCol,Column,State,'')
  else
    DrawCellForSysParams(TDBGrid(Sender),Rect,DataCol,Column,State,FDepartmentFieldName);
end;

procedure TfaParamsRptTemp.GridKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if (Key=VK_F8) then
  begin
     DBGridAutoSize(Grid);
  end;
  {if (Key=VK_RETURN) and ([ssCtrl]=Shift) then
  begin
    Key := 0;
    if (DataSource.DataSet<>nil) and not DataSource.DataSet.IsEmpty and DataSource.DataSet.Active then
      Status := ssViewDetail;
  end;}

end;

procedure TfaParamsRptTemp.alDatasetActionsExecute(Action: TBasicAction;
  var Handled: Boolean);
begin
  Handled := True;
  if Action.HandlesTarget(DataSource) then
    Action.ExecuteTarget(DataSource);
end;

procedure TfaParamsRptTemp.alDatasetActionsUpdate(Action: TBasicAction;
  var Handled: Boolean);
begin
  Handled := True;
  Action.UpdateTarget(DataSource);
end;

function TfaParamsRptTemp.ConfirmEdit: Boolean;
begin
  Result := True;
end;



procedure TfaParamsRptTemp.GridTitleClick(Column: TColumn);
begin
  DoDBGrid1TitleClick(Column);
end;

procedure TfaParamsRptTemp.pcPagesPaintTabBackground(Sender: TObject;
  ACanvas: TCanvas; ATabIndex: Integer; const ARect: TRect;
  var Handled: Boolean);
var
  Rect : TRect;
begin
  if pcPages.Pages[ATabIndex].Enabled then
    ACanvas.Font.Color := clWindowText else
    ACanvas.Font.Color := clGrayText;
  Rect := ARect;
  Windows.DrawText(ACanvas.Handle,PChar(pcPages.Pages[ATabIndex].Caption),-1,
    Rect,DT_CENTER or DT_VCENTER or DT_SINGLELINE);
end;

procedure TfaParamsRptTemp.pcPagesChanging(Sender: TObject;
  NewIndex: Integer; var AllowChange: Boolean);
begin
  if ((pcPages.ActivePageIndex=0) and (Status=ssBrowse))
    or ((pcPages.ActivePageIndex=1) and (Status<>ssBrowse)) then
    AllowChange := False;
end;

procedure TfaParamsRptTemp.DataSetPriorExecute(Sender: TObject);
begin
  if DBNavigator.DataSource.DataSet.Eof then
  begin
    DBNavigator.Refresh;
  end;
end;

procedure TfaParamsRptTemp.GridDblClick(Sender: TObject);
begin
  btnViewDetailClick(Sender);
end;

procedure TfaParamsRptTemp.RedrawBorder(const Clip: HRGN);
var
  DC: HDC;
  R: TRect;
  BtnFaceBrush: HBRUSH;
begin
  DC := GetWindowDC(Handle);
  try
    GetWindowRect(Handle, R);
    OffsetRect(R, -R.Left, -R.Top);
    BtnFaceBrush := CreateSolidBrush(ColorToRGB($00FEDEC9));
    FrameRect(DC, R, BtnFaceBrush);
    InitializeFlatSB(Handle);
    //InflateRect(R, -1, -1);
  finally
    ReleaseDC(Handle, DC);
  end;
  DeleteObject(BtnFaceBrush);
end;

procedure TfaParamsRptTemp.GridMouseEnter(Sender: TObject);
begin
  RedrawBorder(3);
end;

procedure TfaParamsRptTemp.btn100Click(Sender: TObject);
begin
  rmprvwP.Zoom := 100;

end;

procedure TfaParamsRptTemp.btnPageWidthClick(Sender: TObject);
begin
  rmprvwP.PageWidth;
end;

procedure TfaParamsRptTemp.btnFirstClick(Sender: TObject);
begin
  rmprvwP.First;
end;

procedure TfaParamsRptTemp.btnpreviousClick(Sender: TObject);
begin
  rmprvwP.Prev;
end;

procedure TfaParamsRptTemp.btnNextClick(Sender: TObject);
begin
  rmprvwP.Next;
end;

procedure TfaParamsRptTemp.btnLastClick(Sender: TObject);
begin
  rmprvwP.Last;
end;

type
  THackExport = class(TRMExportFilter)
  end;
procedure TfaParamsRptTemp.btnExpXlsClick(Sender: TObject);
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

procedure TfaParamsRptTemp.btnPagePrintClick(Sender: TObject);
begin
  rmprvwP.Print;
end;

procedure TfaParamsRptTemp.btnSetupClick(Sender: TObject);
begin
  rmprvwP.DlgPageSetup;
end;

procedure TfaParamsRptTemp.btnDesignClick(Sender: TObject);
begin
  if Application.MessageBox('对报表设计将影响显示效果，继续进行该操作吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  rptQRpt.DesignReport;

end;

procedure TfaParamsRptTemp.btnOpenRptClick(Sender: TObject);
begin
  try
  if dlgOpenRpt.Execute then
    rmprvwP.LoadFromFile(dlgOpenRpt.FileName);
  except

  end;
end;

end.
