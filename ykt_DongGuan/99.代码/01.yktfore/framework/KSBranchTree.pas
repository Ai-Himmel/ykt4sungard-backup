unit KsBranchTree;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KsBranchTree
   <What>分支机构管理
   <Written By> 周耀亮
   <History>
**********************************************}

interface

uses SysUtils, Classes, Contnrs, Dialogs;

const
  {
  +MetaRoot
    +Root
      +Group
        -Leaf
        -Leaf
      +Group
        -Leaf
        -Leaf
    +Root
      +Group
        -Leaf
        -Leaf
      +Group
        -Leaf
        -Leaf

  }

  GroupValue = '1';
  RootValue = '2';
  LeafValue = '0';
  MetaRootValue = '3';

type
  TKSMetaNode = class
  private
    FId: string;
    FCaption: string;
    FType: string;
    FDescription: string;
    procedure SetCaption(const Value: string);
  protected

  public
    constructor Create;
    property Id: string read FId write FId;
    property Caption: string read FCaption write SetCaption;
    property NodeType: string read FType write FType;
    property Description: string read FDescription write FDescription;
  end;

  TKSTreeStructure = class
  private
    FParentId: string;
    FChildId: string;
    FSequenceNo: Integer;
  protected

  public
    property ParentId: string read FParentId write FParentId;
    property ChildId: string read FChildId write FChildId;
    property SequenceNo: Integer read FSequenceNo write FSequenceNo;
  end;

  TInfoList = class(TObjectList)
  private
    function GetItems(Index: Integer): TKSMetaNode;
  protected

  public
    function Find(const Id: string): TKSMetaNode;
    //    procedure   Search(SearchTypes : TMenuSearchTypes; const Text : string; ResultList : TList);
    property Items[Index: Integer]: TKSMetaNode read GetItems; default;
  end;

  TStructureList = class(TObjectList)
  private
    function GetItems(Index: Integer): TKSTreeStructure;
  protected

  public
    procedure Find(ChildrenInfos: TList; const ParentId: string);
    property Items[Index: Integer]: TKSTreeStructure read GetItems; default;
  end;

  TUIInfo = class;

  TBranchTreeNode = class
  private
    FParent: TUIInfo;
  protected

  public
    constructor Create(AParent: TUIInfo);
    destructor Destroy; override;
    property Parent: TUIInfo read FParent;
  end;

  TUIInfoGroup = class;

  TUIInfo = class(TBranchTreeNode)
  private
    FDescription: string;
    FMetaNode: TKSMetaNode;
    FCaption: string;
    FUICode: string;
  public
    constructor Create(AParent: TUIInfoGroup; MetaNode: TKSMetaNode);
    destructor Destroy; override;
    property Description: string read FDescription write FDescription;
    property MetaNode: TKSMetaNode read FMetaNode;
    property Caption: string read FCaption write FCaption;
    property UICode: string read FUICode write FUICode;
  end;

  TUIInfoItem = class(TUIInfo)
  private
  protected

  public
    constructor Create(AParent: TUIInfoGroup; MetaNode: TKSMetaNode);
    destructor Destroy; override;
  end;

  TUIInfoGroup = class(TUIInfo)
  private
    FList: TObjectList;
    function GetCount: integer;
    function GetItems(index: integer): TUIInfo;
  protected

  public
    constructor Create(AParent: TUIInfoGroup; MetaNode: TKSMetaNode);
    destructor Destroy; override;
    procedure Add(Item: TUIInfo);
    procedure Extract(UIInfo: TUIInfo);
    procedure Clear;
    function Clone(AParent: TUIInfoGroup; Include: Boolean = False):
      TUIInfoGroup;
    function FindInfoItem(const ID: string): TUIInfoItem;
    function FindInfoGroup(const ID: string): TUIInfoGroup;
    function Containes(UIInfo: TUIInfo): Boolean;
    property Count: integer read GetCount;
    property Items[index: integer]: TUIInfo read GetItems;
  end;

  TInfoAdmin = class
  private
    FInfoList: TInfoList;
    FStructureList: TStructureList;
    FRoot: TUIInfoGroup;
    FOnGetInfos: TNotifyEvent;
    FOnGetStructures: TNotifyEvent;
  protected
    procedure GetInfos;
    procedure GetStructures;
  public
    constructor Create;
    destructor Destroy; override;
    procedure Init;

    property Root: TUIInfoGroup read FRoot;

    property InfoList: TInfoList read FInfoList;
    property StructureList: TStructureList read FStructureList;

    property OnGetInfos: TNotifyEvent read FOnGetInfos write FOnGetInfos;
    property OnGetStructures: TNotifyEvent read FOnGetStructures write
      FOnGetStructures;
  end;

var
  InfoAdmin: TInfoAdmin;
  FInfoAdmin: TInfoAdmin;

implementation

{ TKSMetaNode }

constructor TKSMetaNode.Create;
begin

end;

procedure TKSMetaNode.SetCaption(const Value: string);
begin
  FCaption := Value;
end;

{ TInfoList }

function TInfoList.Find(const Id: string): TKSMetaNode;
var
  I: Integer;
begin
  Result := nil;
  for I := 0 to Count - 1 do
    if Items[I].Id = Id then
    begin
      Result := Items[I];
      Break;
    end;
end;

function TInfoList.GetItems(Index: Integer): TKSMetaNode;
begin
  Result := TKSMetaNode(inherited Items[Index]);
end;

{ TStructureList }

procedure TStructureList.Find(ChildrenInfos: TList;
  const ParentId: string);
var
  I: Integer;
begin
  Assert(ChildrenInfos <> nil);
  ChildrenInfos.Clear;
  for I := 0 to Count - 1 do
    if Items[I].ParentId = ParentId then
      ChildrenInfos.Add(Items[I]);
end;

function TStructureList.GetItems(Index: Integer): TKSTreeStructure;
begin
  Result := TKSTreeStructure(inherited Items[Index]);
end;

{ TInfoAdmin }

constructor TInfoAdmin.Create;
begin
  inherited;
  FInfoList := TInfoList.Create;
  FStructureList := TStructureList.Create;
  FRoot := nil;
end;

destructor TInfoAdmin.Destroy;
begin
  FreeAndNil(FInfoList);
  FreeAndNil(FStructureList);
  FreeAndNil(FRoot);
  inherited;
end;

procedure TInfoAdmin.GetInfos;
begin
  if Assigned(OnGetInfos) then
    OnGetInfos(Self);
end;

procedure TInfoAdmin.GetStructures;
begin
  if Assigned(OnGetStructures) then
    OnGetStructures(Self);
end;

procedure TInfoAdmin.Init;
var
  MetaNode: TKSMetaNode;

  procedure InitRoot;
  var
    Parent: TUIInfoGroup;
    AMetaNode: TKSMetaNode;
    AUIInfo: TUIInfo;
    GroupInfoQueue, ChildrenInfos: TList;
    I: Integer;
    //    S: string;
  begin
    //    showmessage('');
    FreeAndNil(FRoot);
    //    FRoot := TUIInfoGroup.Create(nil,MetaNode);
    GroupInfoQueue := nil;
    ChildrenInfos := nil;
    try
      // 创建和初始化工作对象
      GroupInfoQueue := TList.Create;
      ChildrenInfos := TList.Create;
      for I := 0 to FInfoList.Count - 1 do
      begin
        if TKSMetaNode(FInfoList[I]).NodeType = RootValue then
        begin
          FRoot := TUIInfoGroup.Create(nil, InfoList[I]);
          GroupInfoQueue.Add(FRoot);
        end;
      end;
      // 处理菜单组队列，正确连接各个子菜单。

      if (GroupInfoQueue.Count = 0) and (FInfoList.Count = 1) then
      begin
        AMetaNode := FInfoList.Items[0];
        FRoot := TUIInfoGroup.Create(nil, AMetaNode);
      end;

      while GroupInfoQueue.Count > 0 do
      begin
        Parent := TUIInfoGroup(GroupInfoQueue[0]);
        GroupInfoQueue.Delete(0);
        FStructureList.Find(ChildrenInfos, Parent.MetaNode.Id);
        for I := 0 to ChildrenInfos.Count - 1 do
        begin
          AMetaNode :=
            InfoList.Find(TKSTreeStructure(ChildrenInfos[I]).ChildId);
          //          showmessage(AMetaNode.ID);
          if AMetaNode <> nil then
          begin
            if AMetaNode.NodeType <> LeafValue then
            begin
              // 处理菜单组
              AUIInfo := TUIInfoGroup.Create(Parent, AMetaNode);
              GroupInfoQueue.Add(AUIInfo);
              //              showmessage(AMetaNode.ID);
            end
            else
            begin
              // 处理叶菜单
              AUIInfo := TUIInfoItem.Create(Parent, AMetaNode);
              //              S := AUIInfo.MetaNode.Caption;
            end;
          end;
        end;
      end;
    finally
      ChildrenInfos.Free;
      GroupInfoQueue.Free;
    end;
  end;
begin
  // 获取基本数据
  GetInfos;
  GetStructures;

  // 创建抽象的唯一根节点，包含其他根节点
//  MetaNode := TKSMetaNode.Create;
//  MetaNode.ID := '<Root>';
//  MetaNode.NodeType := MetaRootValue;
//  MetaNode.Caption := '111';
//  InfoList.Add(MetaNode);
  InitRoot; {注意}
end;

{ TBranchTreeNode }

constructor TBranchTreeNode.Create(AParent: TUIInfo);
begin
  FParent := AParent;
end;

destructor TBranchTreeNode.Destroy;
begin
  FParent := nil;
  inherited;
end;

{ TUIInfo }

constructor TUIInfo.Create(AParent: TUIInfoGroup; MetaNode: TKSMetaNode);
begin
  inherited Create(AParent);
  if FParent <> nil then
    TUIInfoGroup(FParent).Add(self);
  FMetaNode := MetaNode;
  if FMetaNode <> nil then
  begin
    FCaption := FMetaNode.Caption;
    FUICode := FMetaNode.Id;
  end;
end;

destructor TUIInfo.Destroy;
begin
  if FParent <> nil then
    TUIInfoGroup(FParent).Extract(self);
  FParent := nil;
  inherited;
end;

{ TUIInfoItem }

constructor TUIInfoItem.Create(AParent: TUIInfoGroup;
  MetaNode: TKSMetaNode);
begin
  inherited Create(AParent, MetaNode);
end;

destructor TUIInfoItem.Destroy;
begin
  inherited;
end;

{ TUIInfoGroup }

procedure TUIInfoGroup.Add(Item: TUIInfo);
begin
  FList.Add(Item);
end;

procedure TUIInfoGroup.Clear;
begin
  FList.Clear;
end;

function TUIInfoGroup.Clone(AParent: TUIInfoGroup;
  Include: Boolean): TUIInfoGroup;
var
  I: Integer;
  UIInfo: TUIInfo;
  NewInfoItem: TUIInfoItem;
begin
  Result := TUIInfoGroup.Create(AParent, MetaNode);
  Result.Caption := Self.Caption;
  Result.UICode := Self.UICode;
  for I := 0 to Count - 1 do
  begin
    UIInfo := Items[I];
    // 过滤掉不需要显示的虚拟菜单
    if UIInfo is TUIInfoGroup then
    begin
      TUIInfoGroup(UIInfo).Clone(Result, Include);
    end
    else
    begin
      NewInfoItem := TUIInfoItem.Create(Result, UIInfo.MetaNode);
    end;
  end;
end;

function TUIInfoGroup.Containes(UIInfo: TUIInfo): Boolean;
begin
  Result := False;
  while UIInfo <> nil do
  begin
    if UIInfo = Self then
    begin
      Result := True;
      Break;
    end;
    UIInfo := UIInfo.Parent;
  end;
end;

constructor TUIInfoGroup.Create(AParent: TUIInfoGroup;
  MetaNode: TKSMetaNode);
begin
  inherited Create(AParent, MetaNode);
  FList := TObjectList.Create;
end;

destructor TUIInfoGroup.Destroy;
var
  Temp: TObject;
begin
  Temp := FList;
  FList := nil;
  Temp.Free;
  inherited;
end;

procedure TUIInfoGroup.Extract(UIInfo: TUIInfo);
begin
  if FList <> nil then
    FList.Extract(UIInfo);
end;

function TUIInfoGroup.FindInfoGroup(const ID: string): TUIInfoGroup;
var
  I: Integer;
begin
  if ID <> '' then
    for I := 0 to Count - 1 do
    begin
      if Items[I] is TUIInfoGroup then
      begin
        Result := TUIInfoGroup(Items[I]);
        if SameText(Result.UICode, ID) then
          Exit;
      end;
    end;
  Result := nil;
end;

function TUIInfoGroup.FindInfoItem(const ID: string): TUIInfoItem;
var
  I: Integer;
begin
  if ID <> '' then
    for I := 0 to Count - 1 do
    begin
      if Items[I] is TUIInfoItem then
      begin
        Result := TUIInfoItem(Items[I]);
        if SameText(Result.UICode, ID) then
          Exit;
      end
      else if Items[I] is TUIInfoGroup then
      begin
        Result := TUIInfoGroup(Items[I]).FindInfoItem(ID);
        if Result <> nil then
          Exit;
      end;
    end;
  Result := nil;
end;

function TUIInfoGroup.GetCount: integer;
begin
  Result := FList.Count;
end;

function TUIInfoGroup.GetItems(index: integer): TUIInfo;
begin
  Result := TUIInfo(FList[index]);
end;

end.
