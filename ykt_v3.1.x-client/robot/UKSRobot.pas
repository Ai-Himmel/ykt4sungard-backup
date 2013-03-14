unit UKSRobot;

interface

uses SysUtils, Classes, Controls,  Contnrs, Menus,
  ObjDir, WorkViews, WVCommands, KSFrameWorks, KSClientConsts;

type
  TKSUsedDataItems = class;

  TKSUsedDataItem = class
  private
    FID : string;
    FStrData : string;
    FParent: TKSUsedDataItems;
  public
    constructor Create(const AID : string;    // ID
                  const StrData : string;     // Data in string format
                  PtrData : Pointer           // Data in pointer format
                  ); virtual;                 // notes : virtual constructor
    function    GetID : string; virtual;
    function    GetCaption : string; virtual;
    procedure   SetFieldData(Field : TWVField); virtual;
    property    Parent : TKSUsedDataItems read FParent;
  end;

  TKSUsedDataItemClass = class of TKSUsedDataItem;

  //TMenuSelectedEvent = procedure (PopupComponent: TComponent; Item : TKSUsedDataItem) of object;

  TKSUsedDataItems = class(TObjectCategory)
  private
    FMaxSavedCount: Integer;
    FPopupMenu : TPopupMenu;
    FDataCategory: string;
    //FOnMenuSelected: TMenuSelectedEvent;
    function    GetItems(Index: Integer): TKSUsedDataItem;
    procedure   MenuItemClick(Sender : TObject);
  public
    constructor Create(const ADataCategory : string; AMaxSavedCount : Integer=MaxSavedDataItemCount);
    destructor  Destroy;override;
    function    IndexOfItem(const ID : string) : Integer;
    function    GetPopupMenu : TPopupMenu; virtual;
    class function GetObjectCategoryName(const DataCategory : string) : string;
    class function GetUsedDataItems(const DataCategory: string): TKSUsedDataItems;
    function    PutData(const AID : string;         // ID
                  const StrData : string;           // Data in string format
                  PtrData : Pointer;                // Data in pointer format
                  ItemClass : TKSUsedDataItemClass  // Item Class. notes : class constructor is virtual !
                  ) : Boolean;                      // return create new item or already have the same data
    procedure   ItemListChanged;
    function    GetFirstItem : TKSUsedDataItem;
    procedure   ReferItem(const ID : string);
    property    Items[Index : Integer] : TKSUsedDataItem read GetItems;
    property    MaxSavedCount : Integer read FMaxSavedCount;
    property    DataCategory : string read FDataCategory;
    //property    OnMenuSelected : TMenuSelectedEvent read FOnMenuSelected write FOnMenuSelected;
  end;

  TRobotMonitorFilter = class(TWVCommandFilter)
  private

  protected
    procedure   Process(Command : TWVCommand); override;
  public

  end;

  TKSMonitorType = (mtFieldValueChange, mtPopupMenu);
  TKSMonitorTypes = set of TKSMonitorType;

  TKSRobotSystem = class(TInterfacedObject, IRobotSystem)
  private
    FCustomers : TKSUsedDataItems;
    FGridMenu  : TPopupMenu;
    FFilter    : TRobotMonitorFilter;
    procedure   LMWorkViewNotify(var Message:TWVMessage); message LM_WorkViewNotify;
    procedure   MoniterFieldChange(Field : TWVField);
    function    IsMonitorField(Field : TWVField; var DataCategory : string) : TKSMonitorTypes;
    function    IsMonitorControl(Control : TControl; var Field : TWVField; var DataCategory : string) : TKSMonitorTypes;
    procedure   GridMenuClick(Sender : TObject);
    procedure   AddGridMenuItem(const DataCategory : string);
    procedure   MonitorControl(Control : TControl);
    procedure   MonitorWorkView(WorkView : TWorkView);
    procedure   InitControl(Control : TControl);
    procedure   MenuSelected(PopupComponent: TComponent; Item : TKSUsedDataItem);
    procedure   ClearDataItems(const DataCategory : string);
  protected
    // IRobotSystem
    procedure   MonitorComponent(AComponent : TComponent);
    procedure   InitComponent(AComponent : TComponent);
    procedure   SaveData(const DataCategory , ID, Caption : string);
    procedure   OperatorChanged(const OperatorNo : string);
  public
    constructor Create;
    destructor  Destroy; override;
  end;

const
  MenuCaptionFormat = '从选择的单元格获取-%s';

implementation

uses DB, KSEdits, DataTypes, WVCtrls, DBGrids;

var
  RobotSystem : TKSRobotSystem = nil;

type
  TControlAccess = class(TControl);

procedure InstallRobotSystem;
begin
  if Context<>nil then
    Context.SetRobotSystem(TKSRobotSystem.Create);
end;

procedure UnInstallRobotSystem;
begin
  if Context<>nil then
    Context.SetRobotSystem(nil);
end;

{ TKSUsedDataItem }

constructor TKSUsedDataItem.Create(const AID, StrData: string;
  PtrData: Pointer);
begin
  inherited Create;
  FID := AID;
  FStrData := StrData;
end;

function TKSUsedDataItem.GetCaption: string;
begin
  Result := FStrData;
end;

function TKSUsedDataItem.GetID: string;
begin
  Result := FID;
end;

procedure TKSUsedDataItem.SetFieldData(Field: TWVField);
begin
  Field.Data.AsString := FID;
end;

{ TKSUsedDataItems }

constructor TKSUsedDataItems.Create(const ADataCategory: string; AMaxSavedCount : Integer);
begin
  Assert(AMaxSavedCount>0);
  inherited Create(GetObjectCategoryName(ADataCategory),True);
  FDataCategory := ADataCategory;
  FMaxSavedCount := AMaxSavedCount;
  FPopupMenu := TPopupMenu.Create(nil);
  FPopupMenu.AutoHotkeys := maManual;
end;

destructor TKSUsedDataItems.Destroy;
begin
  FreeAndNil(FPopupMenu);
  inherited;
end;

function TKSUsedDataItems.GetFirstItem: TKSUsedDataItem;
begin
  if Count>0 then
    Result := Items[0] else
    REsult := nil;
end;

function TKSUsedDataItems.GetItems(Index: Integer): TKSUsedDataItem;
begin
  Result := TKSUsedDataItem(inherited Items[Index]);
end;

class function TKSUsedDataItems.GetObjectCategoryName(
  const DataCategory: string): string;
begin
  Result := Format('KSROBOT.DATA.%s',[DataCategory]);
end;

class function TKSUsedDataItems.GetUsedDataItems(
  const DataCategory: string): TKSUsedDataItems;
begin
  Result := TKSUsedDataItems(GetCategory(GetObjectCategoryName(DataCategory)));
end;

function TKSUsedDataItems.GetPopupMenu: TPopupMenu;
begin
  Result := FPopupMenu;
end;

function TKSUsedDataItems.IndexOfItem(const ID: string): Integer;
var
  I : Integer;
begin
  Result := -1;
  for I:=0 to Count-1 do
  begin
    if Items[I].GetID=ID then
    begin
      Result := I;
      Break;
    end;
  end;
end;

procedure TKSUsedDataItems.ItemListChanged;
var
  I : Integer;
  MenuItem : TMenuItem;
  Item : TKSUsedDataItem;
begin
  if FPopupMenu<>nil then
  begin
    FPopupMenu.Items.Clear;
    for I:=0 to Count-1 do
    begin
      Item := Items[I];
      MenuItem := TMenuItem.Create(FPopupMenu);
      MenuItem.Caption := Item.GetCaption;
      MenuItem.Tag := Integer(Item);
      MenuItem.OnClick := MenuItemClick;
      FPopupMenu.Items.Add(MenuItem);
    end;
  end;
end;

procedure TKSUsedDataItems.MenuItemClick(Sender: TObject);
var
  Item : TKSUsedDataItem;
begin
  if Sender is TMenuItem then
  begin
    Item := TKSUsedDataItem(TMenuItem(Sender).Tag);
  end else
    Item := nil;
  {
  if Assigned(OnMenuSelected) then
    OnMenuSelected(FPopupMenu.PopupComponent,Item);
  }
  if RobotSystem<>nil then
    RobotSystem.MenuSelected(FPopupMenu.PopupComponent,Item);
end;

function TKSUsedDataItems.PutData(const AID, StrData: string;
  PtrData: Pointer; ItemClass: TKSUsedDataItemClass): Boolean;
var
  Index : Integer;
  Item : TKSUsedDataItem;
begin
  Index := IndexOfItem(AID);
  Result := Index<0;
  if Result then
  begin
    // delete garbage
    if Count>=MaxSavedCount then
      Delete(Count-1);
    // put a new item in top
    Item := TKSUsedDataItemClass.Create(AID,StrData,PtrData);
    Item.FParent := Self;
    Insert(0,Item);
  end
  else
  begin
    // already have the same data, move it to top
    Move(Index,0);
  end;
  ItemListChanged;
end;

procedure TKSUsedDataItems.ReferItem(const ID: string);
var
  Index : Integer;
begin
  Index := IndexOfItem(ID);
  if Index>0 then
    Move(Index,0);
end;

{ TKSRobotSystem }

constructor TKSRobotSystem.Create;
begin
  inherited;
  RobotSystem := Self;
  
  FCustomers := TKSUsedDataItems.Create(DCCustomer);
  {
  TKSUsedDataItems.Create(DCDate);
  TKSUsedDataItems.Create(DCSequenceNo);
  TKSUsedDataItems.Create(DCContractNo);
  TKSUsedDataItems.Create(DCAccount);
  TKSUsedDataItems.Create(DCBrokerNo);
  TKSUsedDataItems.Create(DCSecurity);
  TKSUsedDataItems.Create(DCOperator);
  TKSUsedDataItems.Create(DCBankAccount);
  }
  if Context<>nil then                    
  begin
    FFilter := TRobotMonitorFilter.Create(Context);
    Context.CommandBus.AddAfterFilter(FFilter);
  end else
    FFilter := nil;

  FGridMenu  := TPopupMenu.Create(nil);

  {
  AddGridMenuItem(DCCustomer);
  AddGridMenuItem(DCDate);
  AddGridMenuItem(DCSequenceNo);
  AddGridMenuItem(DCContractNo);
  AddGridMenuItem(DCAccount);
  AddGridMenuItem(DCBrokerNo);
  AddGridMenuItem(DCSecurity);
  AddGridMenuItem(DCOperator);
  AddGridMenuItem(DCBankAccount);
  }
  //FGridMenu.AutoHotkeys := maManual;
end;

destructor TKSRobotSystem.Destroy;
begin
  RobotSystem := nil;
  RemoveClientForAll(Self);
  FFilter.Free;

  FreeAndNil(FGridMenu);
  inherited;
end;

procedure TKSRobotSystem.AddGridMenuItem(const DataCategory: string);
var
  MenuItem : TMenuItem;
  Items : TKSUsedDataItems;
begin
  Items := TKSUsedDataItems.GetUsedDataItems(DataCategory);
  Assert(Items<>nil);
  MenuItem := TMenuItem.Create(FGridMenu);
  MenuItem.Caption := Format(MenuCaptionFormat,[DataCategory]);
  MenuItem.Tag := Integer(Items);
  MenuItem.OnClick := GridMenuClick;
  FGridMenu.Items.Add(MenuItem);
end;

procedure TKSRobotSystem.GridMenuClick(Sender: TObject);
var
  Items : TKSUsedDataItems;
  Grid : TDBGrid;
  ID : string;
begin
  Assert(Sender is TMenuItem);
  Items := TKSUsedDataItems(TMenuItem(Sender).Tag);
  if FGridMenu.PopupComponent is TDBGrid then
  begin
    Grid := TDBGrid(FGridMenu.PopupComponent);
    if (Grid.DataSource<>nil) and
      (Grid.DataSource.Dataset<>nil) and
      (Grid.SelectedField<>nil) then
    begin
      ID := Grid.SelectedField.AsString;
      Items.PutData(ID,Items.DataCategory+ID,nil,TKSUsedDataItem);
    end;
  end;
end;

procedure TKSRobotSystem.InitControl(Control: TControl);
var
  Item : TKSUsedDataItem;
  DataCategory: string;
  Items : TKSUsedDataItems;
  Field : TWVField;
begin
  if Control is TKSAccountEdit then
  begin
    Item := FCustomers.GetFirstItem;
    if Item<>nil then
      TKSAccountEdit(Control).SetCustomer(Item.GetID);
  end
  else if mtPopupMenu in IsMonitorControl(Control,Field,DataCategory) then
  begin
    Items := TKSUsedDataItems.GetUsedDataItems(DataCategory);
    Assert(Items<>nil);
    Item := Items.GetFirstItem;
    if Item<>nil then
      Item.SetFieldData(Field);
  end;
end;

function TKSRobotSystem.IsMonitorControl(Control: TControl;
  var Field: TWVField; var DataCategory: string): TKSMonitorTypes;
begin
  Field := WVGetField(Control);
  if (Field<>nil) then
    Result := IsMonitorField(Field,DataCategory) else
    Result := [];
end;

function TKSRobotSystem.IsMonitorField(Field: TWVField;
  var DataCategory: string): TKSMonitorTypes;
begin
  DataCategory := '';
  Result := [];
  if (Pos(CPDate, Field.Name)>0) and (Pos('开户日期', Field.Name)<=0) then
  begin
    Result := [mtFieldValueChange, mtPopupMenu];
    DataCategory := DCDate;
  end
  else if Pos(CPSequenceNo, Field.Name)>0 then
  begin
    Result := [mtPopupMenu];
    DataCategory := DCSequenceNo;
  end
  else if (Pos(CPContractNo1, Field.Name)>0) or (Pos(CPContractNo2, Field.Name)>0) then
  begin
    Result := [mtPopupMenu];
    DataCategory := DCContractNo;
  end
  else if (Pos(CPAccount1, Field.Name)>0) or (Pos(CPAccount2, Field.Name)>0) then
  begin
    Result := [mtPopupMenu];
    DataCategory := DCAccount;
  end
  else if (Pos(CPBrokerNo1,Field.Name)>0) or (Pos(CPBrokerNo2, Field.Name)>0) then
  begin
    Result := [mtPopupMenu];
    DataCategory := DCBrokerNo;
  end
  else if (Pos(CPSecurity,Field.Name)>0) then
  begin
    Result := [mtPopupMenu];
    DataCategory := DCSecurity;
  end
  else if (Pos(CPOperator1,Field.Name)>0) or (Pos(CPOperator2, Field.Name)>0) then
  begin
    Result := [mtPopupMenu];
    DataCategory := DCOperator;
  end
  else if (Pos(CPBankAccount1,Field.Name)>0) or (Pos(CPBankAccount2, Field.Name)>0) then
  begin
    Result := [mtPopupMenu];
    DataCategory := DCBankAccount;
  end
end;

procedure TKSRobotSystem.LMWorkViewNotify(var Message: TWVMessage);
begin
  if (Message.NotifyCode=WV_FieldValueChanged) and (Message.Field<>nil) then
    MoniterFieldChange(Message.Field);
end;

procedure TKSRobotSystem.MenuSelected(PopupComponent: TComponent;
  Item: TKSUsedDataItem);
var
  Field : TWVField;
  DataCategory : string;
begin
  if PopupComponent is TKSAccountEdit then
  begin
    TKSAccountEdit(PopupComponent).SetCustomer(Item.GetID);
  end
  else if PopupComponent is TControl then
  begin
    if mtPopupMenu in IsMonitorControl(TControl(PopupComponent),Field,DataCategory) then
      Item.SetFieldData(Field);
  end;
end;

procedure TKSRobotSystem.MoniterFieldChange(Field: TWVField);
var
  StrValue : string;
  DataCategory: string;
  Items : TKSUsedDataItems;
begin
  if Field.Valid and (mtFieldValueChange in IsMonitorField(Field,DataCategory)) then
  begin
    Items := TKSUsedDataItems.GetUsedDataItems(DataCategory);
    StrValue := Field.Data.AsString;
    if (Items<>nil) and (StrValue<>'') then
    begin
      Items.PutData(StrValue,StrValue,nil,TKSUsedDataItem);
    end;
  end;
end;

procedure TKSRobotSystem.MonitorControl(Control: TControl);
var
  Field : TWVField;
  DataCategory : string;
  Items : TKSUsedDataItems;
begin
  if Control is TKSAccountEdit then
    TKSAccountEdit(Control).PopupMenu := FCustomers.GetPopupMenu
  else if (Control is TDBGrid) then
  begin
    if TDBGrid(Control).PopupMenu=nil then
      TDBGrid(Control).PopupMenu := FGridMenu;
  end
  else if mtPopupMenu in IsMonitorControl(Control, Field, DataCategory) then
  begin
    Items := TKSUsedDataItems.GetUsedDataItems(DataCategory);
    if (Items<>nil) and (TControlAccess(Control).PopupMenu=nil) then
      TControlAccess(Control).PopupMenu := Items.GetPopupMenu;
  end;
end;

procedure TKSRobotSystem.MonitorWorkView(WorkView: TWorkView);
begin
  WorkView.AddClient(Self);
end;

procedure TKSRobotSystem.InitComponent(AComponent: TComponent);
begin
  if AComponent is TControl then
    InitControl(TControl(AComponent));
end;

procedure TKSRobotSystem.MonitorComponent(AComponent: TComponent);
begin
  if AComponent is TControl then
    MonitorControl(TControl(AComponent))
  else if AComponent is TWorkView then
    MonitorWorkView(TWorkView(AComponent))
end;

procedure TKSRobotSystem.SaveData(const DataCategory, ID, Caption: string);
var
  DataItems : TKSUsedDataItems;
begin
  DataItems := TKSUsedDataItems.GetUsedDataItems(DataCategory);
  if DataItems<>nil then
    DataItems.PutData(ID,Caption,nil,TKSUsedDataItem);
end;

procedure TKSRobotSystem.OperatorChanged(const OperatorNo: string);
var
  SysDate : string;
begin
  ClearDataItems(DCDate);
  ClearDataItems(DCSequenceNo);
  ClearDataItems(DCContractNo);
  ClearDataItems(DCAccount);
  ClearDataItems(DCBrokerNo);
  ClearDataItems(DCSecurity);
  ClearDataItems(DCOperator);
  ClearDataItems(DCBankAccount);

  SysDate := Context.GetParamValue(svWorkDateName);
  SaveData(DCDate,SysDate,SysDate);
end;

procedure TKSRobotSystem.ClearDataItems(const DataCategory: string);
var
  DataItems : TKSUsedDataItems;
begin
  DataItems := TKSUsedDataItems.GetUsedDataItems(DataCategory);
  if DataItems <> nil then DataItems.Clear;
end;

{ TRobotMonitorFilter }

function  GetDataset(Command: TWVCommand; const DatasetParamName, NeedFieldName : string) : TDataset;
var
  Data : TKSDataObject;
  Obj : TObject;
begin
  Result := nil;
  Data := Command.FindParamData(DatasetParamName);
  if (Data<>nil) and (Data.DataType=kdtObject) then
  begin
    Obj := Data.AsObject;
    if Obj is TDataset then
      Result := TDataset(Obj);
    if (Result<>nil) and Result.IsEmpty then
      Result := nil;
    if (Result<>nil) and (NeedFieldName<>'') and (Result.FindField(NeedFieldName)=nil) then
      Result := nil;
  end;
end;

{
function  HasParam(Command: TWVCommand; const ParamName : string; var DataObject : TKSDataObject) : Boolean;
begin
  DataObject := Command.FindParamData(ParamName);
  Result := DataObject<>nil;
end;
}

procedure TRobotMonitorFilter.Process(Command: TWVCommand);
var
  Dataset : TDataset;
  CustomerNo, CustomerName : string;
  ID, Caption : string;

  function  GetParamValue(const ParamName:string):string;
  var
    MyData : TKSDataObject;
  begin
    MyData := Command.FindParamData(ParamName);
    if MyData<>nil then
      Result := MyData.AsString else
      Result := '';
  end;

  procedure PutData(const DataCategory:string);
  var
    DataItems : TKSUsedDataItems;
  begin
    DataItems := TKSUsedDataItems.GetUsedDataItems(DataCategory);
    Assert(DataItems<>nil);
    DataItems.PutData(ID,Caption,nil,TKSUsedDataItem);
  end;

begin
  try
    // 根据特定的命令对象捕捉数据

    // 客户号
    if Command.ID='客户开户' then
    begin
      ID := GetParamValue('返回客户号');
      if ID<>'' then
      begin
        Caption := Format('%s-%s',
          [ID, GetParamValue('姓名')]);
        PutData(DCCustomer);
      end;
    end
    // 客户号
    else if Command.ID='根据账号取客户列表' then
    begin
      Dataset := GetDataset(Command,'返回结果集','scust_no');
      if Dataset<>nil then
      begin
        CustomerNo := Dataset.FieldByName('scust_no').AsString;
        if CustomerNo<>'' then
        begin
          CustomerName := Dataset.FieldByName('sname').AsString;
          RobotSystem.FCustomers.PutData(CustomerNo,CustomerNo+' '+CustomerName,nil,TKSUsedDataItem);
        end;
      end;
    end
    // 合同号
    else if (Command.ID='普通委托') or (Command.ID='特殊委托') then
    begin
      ID := GetParamValue(CPContractNo1);
      if ID<>'' then
      begin
        Caption := Format('合同号%s-%s,%s,%s',
          [ID, GetParamValue('客户号'), GetParamValue('业务类别'), GetParamValue('证券代码')]);
        PutData(DCContractNo);
      end;
    end
    // 合同号
    else if Command.ID='批量委托' then
    begin
      ID := GetParamValue(CPContractNo2);
      if ID<>'' then
      begin
        Caption := Format('批号%s-%s,%s,%s',
          [ID, GetParamValue('客户号'), GetParamValue('业务类别'), GetParamValue('证券代码')]);
        PutData(DCContractNo);
      end;
    end;

    // 根据命令的参数名称捕捉数据

    ID := GetParamValue(CPSequenceNo);
    if ID<>'' then
    begin
      Caption := Format('流水号%s-%s', [ID, Command.ID]);
      PutData(DCSequenceNo);
    end;

    ID := GetParamValue(CPAccount1);
    if ID='' then
      ID := GetParamValue(CPAccount2);
    if ID<>'' then
    begin
      Caption := Format('股东代码%s', [ID]);
      PutData(DCAccount);
    end;

    ID := GetParamValue(CPBrokerNo1);
    if ID='' then
      ID := GetParamValue(CPBrokerNo2);
    if ID<>'' then
    begin
      Caption := Format('经纪人号%s', [ID]);
      PutData(DCBrokerNo);
    end;

    ID := GetParamValue(CPSecurity);
    if ID<>'' then
    begin
      Caption := Format('证券代码%s', [ID]);
      PutData(DCSecurity);
    end;

    ID := GetParamValue(CPOperator1);
    if ID='' then
      ID := GetParamValue(CPOperator2);
    if ID<>'' then
    begin
      Caption := Format('职工代码%s', [ID]);
      PutData(DCOperator);
    end;

    ID := GetParamValue(CPBankAccount1);
    if ID='' then
      ID := GetParamValue(CPBankAccount2);
    if ID<>'' then
    begin
      Caption := Format('银行帐号%s', [ID]);
      PutData(DCBankAccount);
    end;
  except
    // do not corrupt normal process!
  end;
end;

initialization
  InstallRobotSystem;

finalization
  UnInstallRobotSystem;

end.
