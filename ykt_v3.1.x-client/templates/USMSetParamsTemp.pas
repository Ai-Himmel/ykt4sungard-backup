unit USMSetParamsTemp;

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
  ComCtrls, Grids, DBGrids, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  WVDBBinders, WVCmdReq, WorkViews, Db, WVCommands, DBCtrls, DBActns,
  ActnList, RzDBGrid, RzTabs, RzDBNav, RzButton, RzRadChk;
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

  TfaSMSetParamsTemp = class(TKSFrame)
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
    Grid: TRzDBGrid;
    tsEdit: TRzTabSheet;
    UIPanel2: TUIPanel;
    btnOK: TImageButton;
    btnCancel: TImageButton;
    DBNavigator: TRzDBNavigator;
    ImageButton1: TImageButton;
    ImageButton2: TImageButton;
    UIPanel1: TUIPanel;
    btnQuery: TImageButton;
    btnAdd: TImageButton;
    btnChange: TImageButton;
    btnDelete: TImageButton;
    btnViewDetail: TImageButton;
    ckAutoSetNewParams: TRzCheckBox;
    procedure   btnAddClick(Sender: TObject);
    procedure   btnChangeClick(Sender: TObject);
    procedure   pcPagesChanging(Sender: TObject; var AllowChange: Boolean);
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
    procedure   GridDblClick(Sender: TObject);
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
  private
    FStatus:    TSettingStatus;
    FAutoRefresh : Boolean;
    FCanEdit : Boolean;   //允许增加、修改、删除
    FCanDelete: Boolean;  // 允许删除
    FCanAdd: Boolean;     // 允许增加
    FCanChange: Boolean;  // 允许修改
    FLocalDepartment : string;  // 发起营业部代码
    procedure   SetStatus(const Value: TSettingStatus);
    procedure   SetCanAdd(const Value: Boolean);
    procedure   SetCanChange(const Value: Boolean);
    procedure   SetCanDelete(const Value: Boolean);
    procedure   CheckDataCanEdit;
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
  public
    constructor Create(AOwner : TComponent); override;
    procedure   CloseDataset; override;
    property    Status : TSettingStatus read FStatus write SetStatus;
    property    AutoRefresh : Boolean read FAutoRefresh write FAutoRefresh default True;
    property    CanAdd : Boolean read FCanAdd write SetCanAdd default True;
    property    CanChange : Boolean read FCanChange write SetCanChange default True;
    property    CanDelete : Boolean read FCanDelete write SetCanDelete default True;
    property    MaintainType : TParamMaintainType read FMaintainType;
  end;

var
  faSMSetParamsTemp: TfaSMSetParamsTemp;

implementation

uses KSFrameWorkUtils, DataUsageUtils, LogFile;

{$R *.DFM}

type
  TWinControlAccess = class(TWinControl);

{ TfaSetParamsTemp }

constructor TfaSMSetParamsTemp.Create(AOwner: TComponent);
begin
  inherited;
  DataGrid := Grid;
  FStatus := ssBrowse;
  FCanEdit := True;
  FCanDelete := True;
  FCanAdd := True;
  FCanChange := True;
  FAutoRefresh := True;
end;

procedure TfaSMSetParamsTemp.btnAddClick(Sender: TObject);
begin
  Status := ssAdd;
end;

procedure TfaSMSetParamsTemp.Init;
begin
  inherited;
  //FAutoRefresh := False;
  FAutoRefresh := True;
  ckAutoSetNewParams.Checked := True;
  FDepartmentFieldName := 'sbranch_code0';
  FDepartmentWVField := nil;
  FLocalDepartment := Context.ParamData(svDepartNoName).AsString;
  FMaintainType := pmtCenter;
  pcPages.ActivePageIndex := 0;
  //pcPages.OwnerDraw := True;
  tsEdit.Caption := SSet;
  TWinControlAccess(tsQuery).SelectFirst;
  CheckDataCanEdit;
end;

procedure TfaSMSetParamsTemp.btnChangeClick(Sender: TObject);
begin
  Status := ssChange;
end;

procedure TfaSMSetParamsTemp.SetStatus(const Value: TSettingStatus);
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
      tsEdit.Caption := SSet;
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

procedure TfaSMSetParamsTemp.pcPagesChanging(Sender: TObject;
  var AllowChange: Boolean);
begin
  if ((pcPages.ActivePageIndex=0) and (Status=ssBrowse))
    or ((pcPages.ActivePageIndex=1) and (Status<>ssBrowse)) then
    AllowChange := False;
end;

procedure TfaSMSetParamsTemp.btnQueryClick(Sender: TObject);
begin
  WorkView.SynchronizeCtrlsToFields;
  if btnQuery.Enabled then
    DoQuery;
end;

procedure TfaSMSetParamsTemp.BeforeAdd;
begin
  tsEdit.Caption := SAdd;
  // 所有的输入项目可以编辑
  EnableEditCtrls(True);
  // 初始化所有输入项目
  WorkView.Reset(WVDataSource.GroupIndex);
end;

procedure TfaSMSetParamsTemp.BeforeChange;
begin
  tsEdit.Caption := SChange;
  // 所有的输入项目可以编辑
  // 由子类重载该方法，禁止主键可以编辑
  EnableEditCtrls(True);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetParamsTemp.BeforeDelete;
begin
  tsEdit.Caption := SDelete;
  // 所有的输入项目都不可以编辑
  EnableEditCtrls(False);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetParamsTemp.btnDeleteClick(Sender: TObject);
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

function TfaSMSetParamsTemp.GetCurrentRecordInfo: string;
begin
  Result := '';
end;

procedure TfaSMSetParamsTemp.CancelEdit;
begin
  Status := ssBrowse;
end;

procedure TfaSMSetParamsTemp.DoAdd;
begin
  // 同步修改的数据到工作视图，提交请求，如果成功(FEditSucceed=True而且没有意外抛出)，恢复状态为浏览
  SaveModifiedData;
  SendEditCommand(AddRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSMSetParamsTemp.DoChange;
begin
  // 同步修改的数据到工作视图，提交请求，如果成功(FEditSucceed=True而且没有意外抛出)，恢复状态为浏览
  SaveModifiedData;
  SendEditCommand(ChangeRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSMSetParamsTemp.DoDelete;
begin
  // 同步修改的数据到工作视图，提交请求，如果成功(FEditSucceed=True而且没有意外抛出)，恢复状态为浏览
  SaveModifiedData;
  SendEditCommand(DeleteRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSMSetParamsTemp.DoQuery;
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

procedure TfaSMSetParamsTemp.SendQueryCommand;
begin
  try
    ShowWaiting(SWaitingQuery);
    QueryRequest.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaSMSetParamsTemp.btnOKClick(Sender: TObject);
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
      ssChange :
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
      DoQuery;
  end;
end;

procedure TfaSMSetParamsTemp.btnCancelClick(Sender: TObject);
begin
  CancelEdit;
end;

procedure TfaSMSetParamsTemp.SendEditCommand(Request : TWVRequest);
begin
  FEditSucceed := True;
  try
    ShowWaiting(SWaitingOperation);
    Request.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaSMSetParamsTemp.EnableEdit(CanEdit: Boolean);
begin
  //FCanEdit := CanEdit;
  //UpdateButton;
end;

procedure TfaSMSetParamsTemp.CheckReturnData(Request: TWVRequest;
  Command: TWVCommand);
begin
  CheckCommandReturnValue(Command);
end;

procedure TfaSMSetParamsTemp.pcPagesDrawTab(Control: TCustomTabControl;
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

procedure TfaSMSetParamsTemp.EnableEditCtrls(AEnabled: Boolean);
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

procedure TfaSMSetParamsTemp.DataSourceDataChange(Sender: TObject;
  Field: TField);
begin
  if Field=nil then
  begin
    CheckDataCanEdit;
    if Status=ssViewDetail then
      DisplayData;
  end;
end;

procedure TfaSMSetParamsTemp.SetCanAdd(const Value: Boolean);
begin
  FCanAdd := Value;
  UpdateButton;
end;

procedure TfaSMSetParamsTemp.SetCanChange(const Value: Boolean);
begin
  FCanChange := Value;
  UpdateButton;
end;

procedure TfaSMSetParamsTemp.SetCanDelete(const Value: Boolean);
begin
  FCanDelete := Value;
  UpdateButton;
end;

procedure TfaSMSetParamsTemp.UpdateButton;
begin
  FCanEdit := InternalGetCanEdit;
  btnAdd.Enabled := FCanEdit and CanAdd;
  btnDelete.Enabled := FCanEdit and CanDelete;
  btnChange.Enabled := FCanEdit and CanChange;
end;

procedure TfaSMSetParamsTemp.CloseDataset;
begin
  inherited;
  if QueryBinder.Field<>nil then
    QueryBinder.Field.Data.Clear;
end;

function TfaSMSetParamsTemp.InternalGetCanEdit: Boolean;
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

procedure TfaSMSetParamsTemp.DataSourceStateChange(Sender: TObject);
begin
  CheckDataCanEdit;
end;

procedure TfaSMSetParamsTemp.CheckDataCanEdit;
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

procedure TfaSMSetParamsTemp.BeforeViewDetail{(IsFirst : Boolean=True)};
begin
  tsEdit.Caption := SViewDetail;
  // 所有的输入项目都不可以编辑
  EnableEditCtrls(False);
end;

procedure TfaSMSetParamsTemp.btnViewDetailClick(Sender: TObject);
begin
  if (DataSource.DataSet<>nil) and (not DataSource.DataSet.IsEmpty) then
    Status := ssViewDetail;
end;

procedure TfaSMSetParamsTemp.GridDblClick(Sender: TObject);
begin
  if (DataSource.DataSet<>nil) and not DataSource.DataSet.IsEmpty and DataSource.DataSet.Active then
    Status := ssViewDetail;
end;

procedure TfaSMSetParamsTemp.CheckEditFieldValid(WorkField: TWVField);
begin
  if not (status in [ssAdd, ssChange]) then
    WorkField.Valid := True;
end;

procedure TfaSMSetParamsTemp.DBNavigatorClick(Sender: TObject;
  Button: TNavigateBtn);
begin
  //BeforeViewDetail(False);
  //DisplayData;
end;

procedure TfaSMSetParamsTemp.InitEx;
begin
  inherited;
  if btnQuery.Enabled then
    DoQuery;
end;

procedure TfaSMSetParamsTemp.StatusChanged;
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

procedure TfaSMSetParamsTemp.DisplayData;
begin
  // 将数据从数据源同步到工作视图（再到各种控件）。注意：一些子类需要重载该方法，控制特殊控件的数据同步。
  WorkView.Reset(WVDataSource.GroupIndex);
  if DataSource.Dataset<>nil then
    WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetParamsTemp.SaveModifiedData;
begin
  // 将修改的数据同步到工作视图。如果使用特殊的控件需要重载此方法。
  WorkView.SynchronizeCtrlsToFields;
end;


procedure TfaSMSetParamsTemp.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  if FDepartmentWVField=nil then Exit;
  if FDepartmentWVField.Data.AsString=CenterDepartNo then
    DrawCellForSysParams(TDBGrid(Sender),Rect,DataCol,Column,State,'')
  else
    DrawCellForSysParams(TDBGrid(Sender),Rect,DataCol,Column,State,FDepartmentFieldName);
end;

procedure TfaSMSetParamsTemp.GridKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if (Key=VK_RETURN) and ([ssCtrl]=Shift) then
  begin
    Key := 0;
    if (DataSource.DataSet<>nil) and not DataSource.DataSet.IsEmpty and DataSource.DataSet.Active then
      Status := ssViewDetail;
  end;
end;

procedure TfaSMSetParamsTemp.alDatasetActionsExecute(Action: TBasicAction;
  var Handled: Boolean);
begin
  Handled := True;
  if Action.HandlesTarget(DataSource) then
    Action.ExecuteTarget(DataSource);
end;

procedure TfaSMSetParamsTemp.alDatasetActionsUpdate(Action: TBasicAction;
  var Handled: Boolean);
begin
  Handled := True;
  Action.UpdateTarget(DataSource);
end;

function TfaSMSetParamsTemp.ConfirmEdit: Boolean;
begin
  Result := True;
end;



end.
