unit KSFrames;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSFrames
   <What>提供了操作界面的基本父类，实现了基本的操作界面的行为。
   <Written By> Huang YanLai (黄燕来)
   <History>
   1.1 2003-5-28 by 黄燕来 增加了数据集排序的功能
   使用方法：按住CTRL然后用鼠标点击DBGrid的某一列，就会排序，再点一次反向排序，再点一次恢复。

   1.0 long ago  by 黄燕来
**********************************************}

interface

uses Windows, Messages, SysUtils, Classes, Controls, Forms, KSFrameWorks,
UICtrls, DBGrids,
  DataUsageUtils, WorkViews, DB, comctrls, Dialogs, Grids, RzDBGrid, 
    RzDBNav, RzButton, RzRadChk;

type
  TKSFrame = class(TUIFrame, IUIInstance)
  private
    FHelpID: THelpID;
    FInstanceRecord: TUIInstanceRecord;
    FDataGrid: TDBGrid;
    FCanNextSearch: Boolean;
    //wsn 20041113
    FInLTitle: string;
    FInRTitle: string;
    FDateSpotTitle: string;

    procedure CMRelease(var Message: TMessage); message CM_RELEASE;
    procedure SetDataGrid(const Value: TDBGrid);
  protected
    FSearchOptions: TDataSearchOptions;
    FUICode: string;
    FWorkView: TWorkView;
    FDataSource: TDataSource;
    FStringGrid: TStringGrid;

    function CanSave: Boolean; virtual;
    function CanClose: Boolean; virtual;
    function GetCaption: string; virtual;
    procedure SetCaption(const Value: string); virtual;
    function GetHelpID: THelpID; virtual;
    procedure SetInstanceRecord(InstanceRecord: TUIInstanceRecord); virtual;
    procedure Init; virtual;
    procedure InitEx; virtual;
    function GetGridInfoFileName: string;
    function CanDoAction(const ActionID: TCommonActionID): Boolean; virtual;
    procedure DoAction(const ActionID: TCommonActionID); virtual;
    procedure SystemNotify(NotifyCode: Integer); virtual;
    function IsDataReady: Boolean; virtual;
    procedure DoPrint; virtual;
    procedure DoPrintListView(ListView: TListView; DataSet: TDataSet); virtual;
    //wsn 20041113 加入打印stringgrid 的方法
    procedure DoPrintStringGrid; virtual;
    procedure DebugDataset; virtual;
    procedure DebugWorkView; virtual;
    procedure DebugUI; virtual;
    procedure DebugDataSource; virtual;
    procedure DoDBGrid1TitleClick(Column: TColumn);

  public

    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;

    procedure ShowWaiting(const Msg: string);
    procedure CloseWaiting;
    procedure Close;
    procedure HandleException;

    procedure AdjustGrid;
    procedure SearchData;
    {    procedure   SmartSearchData;          }
    procedure NextSearch;
    procedure FocusGrid;
    procedure CloseDataset; virtual;

    property InstanceRecord: TUIInstanceRecord read FInstanceRecord;
    property UICode: string read FUICode write FUICode;
    property DataGrid: TDBGrid read FDataGrid write SetDataGrid;
    property LTitle: string read FInLTitle write FInLTitle;
    property RTitle: string read FInRTitle write FInRTitle;
    property DateSpotTitle: string read FDateSpotTitle write FDateSpotTitle;
    property StringGrid: TStringGrid read FStringGrid write FStringGrid;

  published
    property HelpID: THelpID read FHelpID write FHelpID;
    property Caption;
  end;

implementation

uses KSFrameWorkUtils, KSClientConsts, WVCtrls, KSStrUtils,
  DBAIntf, BDAImpEx, BDAViewers, KSKeyBoard;

{ TKSFrame }

function TKSFrame.CanClose: Boolean;
begin
  Result := True;
end;

function TKSFrame.CanSave: Boolean;
begin
  Result := True;
end;

constructor TKSFrame.Create(AOwner: TComponent);
begin
  inherited;
  if (Context <> nil) and not (csDesigning in ComponentState) then
    RegisterModule(Self);
  FCanNextSearch := False;
  FSearchOptions.IsFromFirst := False;
  FSearchOptions.IsForward := True;
end;

function TKSFrame.GetCaption: string;
begin
  Result := Caption;
end;

function TKSFrame.GetHelpID: THelpID;
begin
  Result := FHelpID;
  if Result = '' then
    Result := Caption;
end;

procedure TKSFrame.SetInstanceRecord(InstanceRecord: TUIInstanceRecord);
begin
  FInstanceRecord := InstanceRecord;
  if FInstanceRecord <> nil then
    FUICode := FInstanceRecord.UIClassFactory.UICode;
end;

procedure TKSFrame.ShowWaiting(const Msg: string);
begin
  Context.GetDialogSystem.ShowWaiting(Msg);
end;

procedure TKSFrame.CloseWaiting;
begin
  Context.GetDialogSystem.CloseWaiting;
end;

procedure TKSFrame.Init;
var
  I: Integer;
begin
  SelectFirst;
  if DataGrid <> nil then
  begin
    ReadGridInfo(DataGrid, GridInvisibleColor, GetGridInfoFileName);
    if not Assigned(DataGrid.OnTitleClick) then
      DataGrid.OnTitleClick := DoDBGrid1TitleClick;
  end;

  FWorkView := nil;
  for I := 0 to ComponentCount - 1 do
  begin
    if Components[I] is TWorkView then
    begin
      FWorkView := TWorkView(Components[I]);
      Break;
    end;
  end;

  if FWorkView <> nil then
    LinkCtrl2WorkView(TWorkView(FWorkView), Self, True);

  FDataSource := nil;
  for I := 0 to ComponentCount - 1 do
  begin
    if Components[I] is TDataSource then
    begin
      FDataSource := TDataSource(Components[I]);
      Break;
    end;
  end;
end;

procedure TKSFrame.AdjustGrid;
begin
  Assert(DataGrid <> nil);
  if SetupGrid(DataGrid, GridInvisibleColor) then
    SaveGridInfo(DataGrid, GetGridInfoFileName);
end;

function TKSFrame.GetGridInfoFileName: string;
begin
  Result := AddPathAndName(Context.GetDir(dkSavedConfig), UICode +
    GridInfoFilePostfix);
end;

procedure TKSFrame.NextSearch;
begin
  Assert(DataGrid <> nil);
  FCanNextSearch := False;
  if DataGrid.DataSource.DataSet <> nil then
  begin
    if SearchDataset(DataGrid.DataSource.DataSet, FSearchOptions) then
    begin
      FCanNextSearch := True;
    end
    else
      Context.GetDialogSystem.ShowMessage(SNotFound);
  end;
end;

{procedure TKSFrame.SmartSearchData;
begin
  Assert(DataGrid<>nil);
  FCanNextSearch := False;
  if DataGrid.DataSource.DataSet<>nil then
  begin
    if IsSearchSmartDataset(DataGrid,FSearchOptions) then
    begin
      if SearchDataset(DataGrid.DataSource.DataSet,FSearchOptions) then
        FCanNextSearch := True else
      Context.GetDialogSystem.ShowMessage(SNotFound);
    end;
  end;
end;   }

procedure TKSFrame.SearchData;
begin
  Assert(DataGrid <> nil);
  FCanNextSearch := False;
  if DataGrid.DataSource.DataSet <> nil then
  begin
    if IsSearchDataset(DataGrid, FSearchOptions) then
    begin
      if SearchDataset(DataGrid.DataSource.DataSet, FSearchOptions) then
        FCanNextSearch := True
      else
        Context.GetDialogSystem.ShowMessage(SNotFound);
    end;
  end;
end;

procedure TKSFrame.Close;
begin
  PostMessage(Handle, CM_RELEASE, 0, 0);
end;

procedure TKSFrame.CMRelease(var Message: TMessage);
begin
  InstanceRecord.Release;
end;

function TKSFrame.CanDoAction(const ActionID: TCommonActionID): Boolean;
var
  GridDataReady: Boolean;
begin
  GridDataReady := IsDataReady;
  case ActionID of
    caPrint: Result := GridDataReady and not
      DataGrid.DataSource.DataSet.IsEmpty;
    caSearchData: Result := GridDataReady and (DataGrid <> nil);
    caNextSearchData: Result := GridDataReady and (DataGrid <> nil) and
      FCanNextSearch;
    caFocusGrid: Result := GridDataReady and (DataGrid <> nil) and
      (DataGrid.CanFocus);
    caAdjustGrid: Result := FDataGrid <> nil;
    caDebugDataset: Result := GridDataReady and (DataGrid <> nil);
    caDebugWorkView: Result := FWorkView <> nil;
    caDebugUI: Result := True;
    caDebugDataSource: Result := (FDataSource <> nil);
    //wsn 20041013 单独定义追加查询
    caSmartSearchData: Result := GridDataReady and (DataGrid <> nil);
  else
    Result := False;
  end;
end;

procedure TKSFrame.DoAction(const ActionID: TCommonActionID);
begin
  case ActionID of
    caPrint: DoPrint;
    caSearchData: SearchData;
    caNextSearchData: NextSearch;
    caAdjustGrid: AdjustGrid;
    caFocusGrid: FocusGrid;
    caDebugDataset: DebugDataset;
    caDebugWorkView: DebugWorkView;
    caDebugUI: DebugUI;
    caDebugDataSource: DebugDataSource;
    {    caSmartSearchData: SmartSearchData;       }
  end;
end;

function TKSFrame.IsDataReady: Boolean;
begin
  Result := (DataGrid <> nil) and (DataGrid.DataSource <> nil)
    and (DataGrid.DataSource.DataSet <> nil) and
      DataGrid.DataSource.DataSet.Active;
end;

procedure TKSFrame.DoPrint;
begin
  if (FDataGrid <> nil) and IsDataReady then
  begin
    { TODO : 打印 }
    DbGridPrint(FDataGrid, Caption, LTitle, RTitle, DateSpotTitle);
  end;
end;

procedure TKSFrame.DoPrintStringGrid;
begin
  if (StringGrid <> nil) then
  begin
    { TODO : 打印 }
    StringGridPrint(FStringGrid, Caption, LTitle, RTitle, DateSpotTitle);
  end;
end;

procedure TKSFrame.DoPrintListView(ListView: TListView; DataSet: TDataSet);
begin
  if (ListView <> nil) and (DataSet <> nil) and (DataSet.Active) then
  begin
    { TODO : 打印 }
    DbListViewPrint(ListView, DataSet, Caption, LTitle, RTitle, DateSpotTitle);
  end;
end;

procedure TKSFrame.CloseDataset;
begin
  if (DataGrid <> nil) and (DataGrid.DataSource <> nil)
    and (DataGrid.DataSource.DataSet <> nil) then
    DataGrid.DataSource.DataSet.Close;
end;

procedure TKSFrame.HandleException;
var
  E: Exception;
begin
  E := Exception(ExceptObject);
  if E <> nil then
    Context.GetExceptionHandler.HandleException(E);
end;

procedure TKSFrame.DebugDataset;
begin
  if (Context.GetDebugSystem <> nil)
    and (FDataGrid <> nil)
    and (FDataGrid.DataSource <> nil)
    and (FDataGrid.DataSource.Dataset <> nil) then
    Context.GetDebugSystem.DebugDataset(FDataGrid.DataSource.Dataset, UICode);
end;

procedure TKSFrame.DebugWorkView;
begin
  if (Context.GetDebugSystem <> nil) and (FWorkView <> nil) then
    Context.GetDebugSystem.DebugWorkView(FWorkView, UICode);
end;

procedure TKSFrame.DebugUI;
begin
  if (Context.GetDebugSystem <> nil) then
    Context.GetDebugSystem.DebugUI(Self, UICode);
end;

procedure TKSFrame.DebugDataSource;
begin
  if (Context.GetDebugSystem <> nil)
    and (FDataSource <> nil) then
    Context.GetDebugSystem.DebugDataSource(FDataSource, UICode);
end;

procedure TKSFrame.SetDataGrid(const Value: TDBGrid);
begin
  if FDataGrid <> Value then
  begin
    FDataGrid := Value;
    if DataGrid <> nil then
      FDataSource := DataGrid.DataSource;
  end;
end;

procedure TKSFrame.SetCaption(const Value: string);
begin
  Caption := Value;
  if InstanceRecord <> nil then
    InstanceRecord.WorkSpace.UIStatusChanged(InstanceRecord);
end;

procedure TKSFrame.InitEx;
var
  I: Integer;
  RobotSystem: IRobotSystem;
  Comp: TComponent;
begin
  Init;
  RobotSystem := Context.GetRobotSystem;
  if RobotSystem <> nil then
    for I := 0 to ComponentCount - 1 do
    begin
      Comp := Components[I];
      RobotSystem.InitComponent(Comp);
    end;
end;

procedure TKSFrame.SystemNotify(NotifyCode: Integer);
begin
  //
end;

procedure TKSFrame.FocusGrid;
begin
  Assert(DataGrid <> nil);
  if DataGrid.CanFocus then
    DataGrid.SetFocus;
end;

procedure TKSFrame.DoDBGrid1TitleClick(Column: TColumn);
var
  KCDataset: THCustomStdDataset;
  DBGrid: TCustomDBGrid;
  Viewer: IDatasetView;
  ViewerInstance: TObject;
  SortFieldName: string;
begin
  DBGrid := Column.Grid;
  if (DBGrid.DataSource = nil)
    or not (DBGrid.DataSource.Dataset is THCustomStdDataset) then
    Exit;
  KCDataset := THCustomStdDataset(DBGrid.DataSource.Dataset);
  Viewer := KCDataset.Viewer;
  if KCDataset.Active and (Viewer <> nil) and TKSKeyboard.IsDown(VK_CONTROL)
    then
  begin
    ViewerInstance := Viewer.GetViewer;
    if ViewerInstance is THSortDatasetView then
    begin
      SortFieldName := THSortDatasetView(ViewerInstance).SortFieldNames;
      KCDataset.UseDefaultView; // cancel
      if CompareText(Column.FieldName, SortFieldName) = 0 then
      begin
        KCDataset.Sort('-' + Column.FieldName);
      end
      else if CompareText('-' + Column.FieldName, SortFieldName) = 0 then
      begin
        //allready be canceled
      end
      else
      begin
        // It had been sorted by another field.
        // Now sort it by this
        KCDataset.Sort(Column.FieldName);
      end;
    end
    else
    begin
      // need a new sort
      KCDataset.UseDefaultView;
      KCDataset.Sort(Column.FieldName);
    end;
  end;
end;

destructor TKSFrame.Destroy;
begin
  CloseDataset;
  inherited;
end;

end.
