unit KSMenuAdmin;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSMenuAdmin
   <What>菜单管理
   <Written By> 程用明、黄燕来
   <History>
**********************************************}

interface

uses SysUtils, Classes, Contnrs;

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

  AuthLength = 800;

  PowerChars: array[Boolean] of Char = ('0', '1');

  AuthChars: array[0..2] of Char = ('0', '1', '2');

type
  TKSMetaMenu = class
  private
    FId: string;
    FCaption: string;
    FAuthNo: Integer;
    FMenuType: string;
    FFunctionSet: string;
    FDescription: string;
    FKeywords: string;
    FSee: string;
    FCaptionSpell: string;
    FHideInManageTree: Boolean;
    FVirtualMenu: Boolean;
    FCaptionSpellSet: Boolean;
    procedure SetCaption(const Value: string);
    procedure SetAuthNo(const Value: Integer);
    procedure SetCaptionSpell(const Value: string);
  protected

  public
    constructor Create;
    function HaveAuth(const Auth: string): Integer;
    procedure SetAuth(var Auth: string; HavePower: Integer);
    function CanAuth: Boolean;
    property Id: string read FId write FId;
    property Caption: string read FCaption write SetCaption;
    property AuthNo: Integer read FAuthNo write SetAuthNo;
    property MenuType: string read FMenuType write FMenuType;
    property FunctionSet: string read FFunctionSet write FFunctionSet;
    property Description: string read FDescription write FDescription;
    property Keywords: string read FKeywords write FKeywords;
    property See: string read FSee write FSee;
    property CaptionSpell: string read FCaptionSpell write SetCaptionSpell;
    // 是否在权限管理的界面里面隐藏
    property HideInManageTree: Boolean read FHideInManageTree write
      FHideInManageTree;
    // 是否不显示在真正的菜单里面
    property VirtualMenu: Boolean read FVirtualMenu write FVirtualMenu;
  end;

  TKSMenuStructure = class
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

  TKSMetaFunction = class
  private
    FId: Integer;
    FCaption: string;
    FNo: Integer;
    procedure SetNo(const Value: Integer);
  protected

  public
    function HaveAuth(const Auth: string): Integer;
    procedure SetAuth(var Auth: string; HavePower: Integer);
    property Id: Integer read FId write FId;
    property Caption: string read FCaption write FCaption;
    property No: Integer read FNo write SetNo;
  end;

  TMenuSearchType = (mstTitle, mstKeywords, mstDescription, mstSpell);
  TMenuSearchTypes = set of TMenuSearchType;

  TMenuList = class(TObjectList)
  private
    function GetItems(Index: Integer): TKSMetaMenu;

  protected

  public
    function Find(const Id: string): TKSMetaMenu;
    procedure Search(SearchTypes: TMenuSearchTypes; const Text: string;
      ResultList: TList);
    procedure GetAuthedItems(const Auth: string; List: TList; OnlyLeaf: Boolean
      = True; NoVirtual: Boolean = True);
    property Items[Index: Integer]: TKSMetaMenu read GetItems; default;
  end;

  TMenuStructureList = class(TObjectList)
  private
    function GetItems(Index: Integer): TKSMenuStructure;

  protected

  public
    procedure Find(ChildrenMenus: TList; const ParentId: string);
    property Items[Index: Integer]: TKSMenuStructure read GetItems; default;
  end;

  TMetaFunctionList = class(TObjectList)
  private
    function GetItems(Index: Integer): TKSMetaFunction;

  protected

  public
    function Find(Id: Integer): TKSMetaFunction;
    property Items[Index: Integer]: TKSMetaFunction read GetItems; default;
  end;

  TUIMenu = class;

  TUITreeNode = class
  private
    FParent: TUIMenu;
  protected

  public
    constructor Create(AParent: TUIMenu);
    destructor Destroy; override;
    property Parent: TUIMenu read FParent;
  end;

  TUIFunction = class(TUITreeNode)
  private
    FMetaFunction: TKSMetaFunction;
  protected

  public
    constructor Create(AParent: TUIMenu; AMetaFunction: TKSMetaFunction);
    destructor Destroy; override;
    property MetaFunction: TKSMetaFunction read FMetaFunction;
  end;

  TUIMenuGroup = class;

  TUIMenu = class(TUITreeNode)
  private
    FDescription: string;
    FMetaMenu: TKSMetaMenu;
    FCaption: string;
    FUICode: string;
  public
    constructor Create(AParent: TUIMenuGroup; MetaMenu: TKSMetaMenu);
    destructor Destroy; override;
    property Description: string read FDescription write FDescription;
    property MetaMenu: TKSMetaMenu read FMetaMenu;
    property Caption: string read FCaption write FCaption;
    property UICode: string read FUICode write FUICode;
  end;

  TUIMenuItem = class(TUIMenu)
  private
    FFunctions: TList;
    FReferencedItems: TList;
    FReferences: TStrings;
    function GetCount: integer;
    function GetItems(index: integer): TUIFunction;
  protected

  public
    constructor Create(AParent: TUIMenuGroup; MetaMenu: TKSMetaMenu);
    destructor Destroy; override;
    procedure Add(Item: TUITreeNode);
    procedure Clear;
    property Count: integer read GetCount;
    property Items[index: integer]: TUIFunction read GetItems;
    property References: TStrings read FReferences;
    property ReferencedItems: TList read FReferencedItems;
  end;

  TUIMenuGroup = class(TUIMenu)
  private
    FList: TObjectList;
    function GetCount: integer;
    function GetItems(index: integer): TUIMenu;
  protected

  public
    constructor Create(AParent: TUIMenuGroup; MetaMenu: TKSMetaMenu);
    destructor Destroy; override;
    procedure Add(Item: TUIMenu);
    procedure Extract(UIMenu: TUIMenu);
    procedure Clear;
    function Clone(AParent: TUIMenuGroup; IncludeFuncs: Boolean = False;
      NoVirtual: Boolean = True): TUIMenuGroup;
    function FindMenuItem(const ID: string): TUIMenuItem;
    function FindMenuGroup(const ID: string): TUIMenuGroup;
    function Containes(UIMenu: TUIMenu): Boolean;
    property Count: integer read GetCount;
    property Items[index: integer]: TUIMenu read GetItems;
  end;

  TMenuAdmin = class
  private
    FFunctionList: TMetaFunctionList;
    FMenuList: TMenuList;
    FMenuStructureList: TMenuStructureList;
    FRoot: TUIMenuGroup;
    FOnGetMenus: TNotifyEvent;
    FOnGetMenuStructures: TNotifyEvent;
    FOnGetFunctions: TNotifyEvent;
    //FFavoritesIDs: TStrings;
    //FFavorites: TUIMenuGroup;
  protected
    procedure GetMenus;
    procedure GetMenuStructures;
    procedure GetFunctions;
  public
    constructor Create;
    destructor Destroy; override;
    procedure Init;

    property Root: TUIMenuGroup read FRoot;
    //property    Favorites : TUIMenuGroup read FFavorites;

    property FunctionList: TMetaFunctionList read FFunctionList;
    property MenuList: TMenuList read FMenuList;
    property MenuStructureList: TMenuStructureList read FMenuStructureList;
    //property    FavoritesIDs      : TStrings read FFavoritesIDs;

    property OnGetMenus: TNotifyEvent read FOnGetMenus write FOnGetMenus;
    property OnGetMenuStructures: TNotifyEvent read FOnGetMenuStructures write
      FOnGetMenuStructures;
    property OnGetFunctions: TNotifyEvent read FOnGetFunctions write
      FOnGetFunctions;
  end;

  {
    <Function>CreateUIMenuGroupFromIDs
    <What>创建一个简单的菜单组。基本数据来自MenuAdmin
    <Params>
      Caption - 标题
      IDs - ','分割的子菜单的ID。
    <Return>
    <Exception>
  }

function CreateUIMenuGroupFromIDs(const Caption, IDs: string): TUIMenuGroup;

procedure GetUIMenuGroupFromIDs(Root: TUIMenuGroup; Strings: TStrings);

{
  <Procedure>DeleteUnauthParts
  <What>删除菜单组里面没有权限的部分
  <Params>
    -
  <Exception>
}
procedure DeleteUnauthParts(Root: TUIMenuGroup; const Auth: string);

procedure FormatAuth(var Auth: string);

var
  MenuAdmin: TMenuAdmin;

implementation

uses KSClientConsts, KSStrUtils, KSChineseSpell, SafeCode;

function CreateUIMenuGroupFromIDs(const Caption, IDs: string): TUIMenuGroup;
var
  Strings: TStringList;
begin
  Result := TUIMenuGroup.Create(nil, nil);
  Result.Caption := Caption;
  if IDs <> '' then
  begin
    Strings := TStringList.Create;
    try
      SeperateStr(IDs, [','], Strings, True);
      GetUIMenuGroupFromIDs(Result, Strings);
    finally
      Strings.Free;
    end;
  end;
end;

procedure GetUIMenuGroupFromIDs(Root: TUIMenuGroup; Strings: TStrings);
var
  I: Integer;
  MetaMenu: TKSMetaMenu;
begin
  Root.Clear;
  for I := 0 to Strings.Count - 1 do
  begin
    MetaMenu := MenuAdmin.MenuList.Find(Strings[I]);
    if (MetaMenu <> nil) and (MetaMenu.MenuType = LeafValue) then
    begin
      TUIMenuItem.Create(Root, MetaMenu);
    end;
  end;
end;

procedure DeleteUnauthParts(Root: TUIMenuGroup; const Auth: string);
var
  I: Integer;
  Menu: TUIMenu;
begin
  for I := Root.Count - 1 downto 0 do
  begin
    Menu := Root.Items[I];
    // 必须是 meta menu
    if Menu.MetaMenu <> nil then
    begin
      // 判断是否有权限
      if Menu.MetaMenu.HaveAuth(Auth) = 1 then
      begin
        // 有权限，如果是 MenuGroup 则要继续检查子菜单
        if Menu is TUIMenuGroup then
        begin
          DeleteUnauthParts(TUIMenuGroup(Menu), Auth);
          // 如果没有可用的子菜单项，就删除自己
          if TUIMenuGroup(Menu).Count = 0 then
            FreeAndNil(Menu);
        end
      end
      else
      begin
        // 没有权限，直接删除自己
        // ? 如果是 MenuGroup 则不需要删除其子菜单吗？虽然没有显示，但是否已释放子菜单内存?
        {
         if Menu is TUIMenuGroup then
         begin
         需要检查
         end;
        }
        FreeAndNil(Menu);
      end;
    end;
  end;
end;

procedure FormatAuth(var Auth: string);
var
  L: Integer;
begin
  L := Length(Auth);
  if L < AuthLength then
  begin
    Auth := Auth + StringOfChar('0', AuthLength - L);
  end;
end;

{ TMenuList }

function TMenuList.Find(const Id: string): TKSMetaMenu;
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

procedure TMenuList.GetAuthedItems(const Auth: string; List: TList; OnlyLeaf,
  NoVirtual: Boolean);
var
  I: Integer;
  Item: TKSMetaMenu;
begin
  List.Clear;
  for I := 0 to Count - 1 do
  begin
    Item := Items[I];
    if (not OnlyLeaf or (Item.MenuType = LeafValue)) and
      (not NoVirtual or not Item.VirtualMenu) and
      (Item.HaveAuth(Auth) = 1) then
      List.Add(Item);
  end;
end;

function TMenuList.GetItems(Index: Integer): TKSMetaMenu;
begin
  Result := TKSMetaMenu(inherited Items[Index]);
end;

procedure TMenuList.Search(SearchTypes: TMenuSearchTypes;
  const Text: string; ResultList: TList);
var
  Words: TStringList;
  MenuIndex, WordIndex: Integer;
  Item: TKSMetaMenu;
  MatchAll, MatchOne: Boolean;
  AWord: string;
begin
  Assert(ResultList <> nil);
  ResultList.Clear;
  if (SearchTypes <> []) and (Trim(Text) <> '') then
  begin
    Words := TStringList.Create;
    try
      seperateStrByBlank(Text, Words);
      if Words.Count > 0 then
        for MenuIndex := 0 to Count - 1 do
        begin
          Item := Items[MenuIndex];
          if Item.MenuType = LeafValue then
          begin
            MatchAll := True;
            for WordIndex := 0 to Words.Count - 1 do
            begin
              MatchOne := False;
              AWord := Words[WordIndex];
              if (mstTitle in SearchTypes) and (Pos(AWord, Item.Caption) > 0)
                then
                MatchOne := True;
              if (mstKeywords in SearchTypes) and (Pos(AWord, Item.Keywords) > 0)
                then
                MatchOne := True;
              if (mstDescription in SearchTypes) and (Pos(AWord,
                Item.Description) > 0) then
                MatchOne := True;
              if (mstSpell in SearchTypes) and (Pos(AWord, Item.CaptionSpell) >
                0) then
                MatchOne := True;
              if not MatchOne then
              begin
                MatchAll := False;
                Break;
              end;
            end;
            if MatchAll then
              ResultList.Add(Item);
          end;
        end;
    finally
      Words.Free;
    end;
  end;
end;

{ TMenuStructureList }

procedure TMenuStructureList.Find(ChildrenMenus: TList; const ParentId: string);
var
  I: Integer;
begin
  Assert(ChildrenMenus <> nil);
  ChildrenMenus.Clear;
  for I := 0 to Count - 1 do
    if Items[I].ParentId = ParentId then
      ChildrenMenus.Add(Items[I]);
end;

function TMenuStructureList.GetItems(Index: Integer): TKSMenuStructure;
begin
  Result := TKSMenuStructure(inherited Items[Index]);
end;

{ TMetaFunctionList }

function TMetaFunctionList.Find(Id: Integer): TKSMetaFunction;
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

function TMetaFunctionList.GetItems(Index: Integer): TKSMetaFunction;
begin
  Result := TKSMetaFunction(inherited Items[Index]);
end;

{TUITreeNode}

constructor TUITreeNode.Create(AParent: TUIMenu);
begin
  FParent := AParent;
end;

destructor TUITreeNode.Destroy;
begin
  FParent := nil;
  inherited;
end;
{ TUIMenuItem }

procedure TUIMenuItem.Add(Item: TUITreeNode);
begin
  FFunctions.Add(Item);
end;

procedure TUIMenuItem.Clear;
begin
  FFunctions.Clear;
end;

constructor TUIMenuItem.Create(AParent: TUIMenuGroup; MetaMenu: TKSMetaMenu);
begin
  inherited Create(AParent, MetaMenu);
  FReferencedItems := TList.Create;
  FFunctions := TList.Create;
end;

destructor TUIMenuItem.Destroy;
begin
  FreeAndNil(FFUnctions);
  FreeAndNil(FReferencedItems);
  inherited;
end;

function TUIMenuItem.GetCount: integer;
begin
  Result := FFunctions.Count;
end;

function TUIMenuItem.GetItems(index: integer): TUIFunction;
begin
  Result := TUIFunction(FFunctions[index]);
end;

{ TUIMenu }

constructor TUIMenu.Create(AParent: TUIMenuGroup; MetaMenu: TKSMetaMenu);
begin
  inherited Create(AParent);
  if FParent <> nil then
    TUIMenuGroup(FParent).Add(self);
  FMetaMenu := MetaMenu;
  if FMetaMenu <> nil then
  begin
    FCaption := FMetaMenu.Caption;
    FUICode := FMetaMenu.Id;
  end;
end;

destructor TUIMenu.Destroy;
begin
  if FParent <> nil then
    TUIMenuGroup(FParent).Extract(self);
  FParent := nil;
  inherited;
end;

{ TUIMenuGroup }

procedure TUIMenuGroup.Add(Item: TUIMenu);
begin
  FList.Add(Item);
end;

procedure TUIMenuGroup.Clear;
begin
  FList.Clear;
end;

function TUIMenuGroup.Clone(AParent: TUIMenuGroup; IncludeFuncs, NoVirtual:
  Boolean): TUIMenuGroup;
var
  I, J: Integer;
  UIMenu: TUIMenu;
  NewMenuItem: TUIMenuItem;
begin
  Result := TUIMenuGroup.Create(AParent, MetaMenu);
  Result.Caption := Self.Caption;
  Result.UICode := Self.UICode;
  for I := 0 to Count - 1 do
  begin
    UIMenu := Items[I];
    // 过滤掉不需要显示的虚拟菜单
    if NoVirtual and UIMenu.MetaMenu.VirtualMenu then
      Continue;
    if UIMenu is TUIMenuGroup then
    begin
      TUIMenuGroup(UIMenu).Clone(Result, IncludeFuncs);
    end
    else
    begin
      NewMenuItem := TUIMenuItem.Create(Result, UIMenu.MetaMenu);
      if IncludeFuncs then
      begin
        for J := 0 to NewMenuItem.Count - 1 do
        begin
          TUIFunction.Create(NewMenuItem, NewMenuItem.Items[J].MetaFunction);
        end;
      end;
    end;
  end;
end;

function TUIMenuGroup.Containes(UIMenu: TUIMenu): Boolean;
begin
  Result := False;
  while UIMenu <> nil do
  begin
    if UIMenu = Self then
    begin
      Result := True;
      Break;
    end;
    UIMenu := UIMenu.Parent;
  end;
end;

constructor TUIMenuGroup.Create(AParent: TUIMenuGroup; MetaMenu: TKSMetaMenu);
begin
  inherited Create(AParent, MetaMenu);
  FList := TObjectList.Create;
end;

destructor TUIMenuGroup.Destroy;
var
  Temp: TObject;
begin
  Temp := FList;
  FList := nil;
  Temp.Free;
  inherited;
end;

procedure TUIMenuGroup.Extract(UIMenu: TUIMenu);
begin
  if FList <> nil then
    FList.Extract(UIMenu);
end;

function TUIMenuGroup.FindMenuGroup(const ID: string): TUIMenuGroup;
var
  I: Integer;
begin
  if ID <> '' then
    for I := 0 to Count - 1 do
    begin
      if Items[I] is TUIMenuGroup then
      begin
        Result := TUIMenuGroup(Items[I]);
        if SameText(Result.UICode, ID) then
          Exit;
      end;
    end;
  Result := nil;
end;

function TUIMenuGroup.FindMenuItem(const ID: string): TUIMenuItem;
var
  I: Integer;
begin
  if ID <> '' then
    for I := 0 to Count - 1 do
    begin
      if Items[I] is TUIMenuItem then
      begin
        Result := TUIMenuItem(Items[I]);
        if SameText(Result.UICode, ID) then
          Exit;
      end
      else if Items[I] is TUIMenuGroup then
      begin
        Result := TUIMenuGroup(Items[I]).FindMenuItem(ID);
        if Result <> nil then
          Exit;
      end;
    end;
  Result := nil;
end;

function TUIMenuGroup.GetCount: integer;
begin
  Result := FList.Count;
end;

function TUIMenuGroup.GetItems(index: integer): TUIMenu;
begin
  Result := TUIMenu(FList[index]);
end;

{ TMenuAdmin }

constructor TMenuAdmin.Create;
begin
  inherited;
  FFunctionList := TMetaFunctionList.Create;
  FMenuList := TMenuList.Create;
  FMenuStructureList := TMenuStructureList.Create;
  //FFavoritesIDs := TStringList.Create;
  FRoot := nil;
  //FFavorites := nil;
end;

destructor TMenuAdmin.Destroy;
begin
  //FreeAndNil(FFavorites);
  //FreeAndNil(FFavoritesIDs);
  FreeAndNil(FFunctionList);
  FreeAndNil(FMenuList);
  FreeAndNil(FMenuStructureList);
  FreeAndNil(FRoot);
  inherited;
end;

procedure TMenuAdmin.GetFunctions;
begin
  if Assigned(OnGetFunctions) then
    OnGetFunctions(Self);
end;

procedure TMenuAdmin.GetMenus;
begin
  if Assigned(OnGetMenus) then
    OnGetMenus(Self);
end;

procedure TMenuAdmin.GetMenuStructures;
begin
  if Assigned(OnGetMenuStructures) then
    OnGetMenuStructures(Self);
end;

procedure TMenuAdmin.Init;
var
  MetaMenu: TKSMetaMenu;

  procedure InitRoot;
  var
    Parent: TUIMenuGroup;
    AMetaMenu: TKSMetaMenu;
    AUIMenu: TUIMenu;
    MetaFunc: TKSMetaFunction;
    Func: TUIFunction;
    GroupMenuQueue, ChildrenMenus: TList;
    Strings: TStringList;
    I, J: Integer;
    S: string;
  begin
    FreeAndNil(FRoot);
    FRoot := TUIMenuGroup.Create(nil, MetaMenu);
    GroupMenuQueue := nil;
    ChildrenMenus := nil;
    Strings := nil;
    try
      // 创建和初始化工作对象
      GroupMenuQueue := TList.Create;
      ChildrenMenus := TList.Create;
      Strings := TStringList.Create;
      for I := 0 to FMenuList.Count - 1 do
        if TKSMetaMenu(FMenuList[I]).MenuType = RootValue then
        begin
          //AUIMenu := TUIMenuGroup.Create(FRoot,FMenuList.Find(TKSMetaMenu(FMenuList[I]).Id));
          Parent := TUIMenuGroup.Create(Root, MenuList[I]);
          GroupMenuQueue.Add(Parent);
        end;
      // 处理菜单组队列，正确连接各个子菜单。
      while GroupMenuQueue.Count > 0 do
      begin
        Parent := TUIMenuGroup(GroupMenuQueue[0]);
        GroupMenuQueue.Delete(0);
        FMenuStructureList.Find(ChildrenMenus, Parent.MetaMenu.Id);
        for I := 0 to ChildrenMenus.Count - 1 do
        begin
          AMetaMenu :=
            MenuList.Find(TKSMenuStructure(ChildrenMenus[I]).ChildId);
          if AMetaMenu <> nil then
          begin
            if AMetaMenu.MenuType <> LeafValue then
            begin
              // 处理菜单组
              AUIMenu := TUIMenuGroup.Create(Parent, AMetaMenu);
              GroupMenuQueue.Add(AUIMenu);
            end
            else
            begin
              // 处理叶菜单
              AUIMenu := TUIMenuItem.Create(Parent, AMetaMenu);
              // 增加功能项目
              S := AUIMenu.MetaMenu.FunctionSet;
              for J := 1 to Length(S) do
                if S[J] = ',' then
                  S[J] := #13;
              Strings.Text := S;
              for J := 0 to Strings.Count - 1 do
              try
                MetaFunc := FunctionList.Find(StrToInt(Strings[J]));
                if MetaFunc <> nil then
                begin
                  Func := TUIFunction.Create(AUIMenu, MetaFunc);
                  TUIMenuItem(AUIMenu).Add(Func);
                end;
              except
              end;
            end;
          end;
        end;
      end;
    finally
      Strings.Free;
      ChildrenMenus.Free;
      GroupMenuQueue.Free;
    end;
  end;
  {
  procedure InitFavorites;
  var
    I : Integer;
    MetaMenu : TKSMetaMenu;
  begin
    FreeAndNil(FFavorites);
    FFavorites := TUIMenuGroup.Create(nil,nil);
    FFavorites.Caption := FavoritesCaption;
    for I:=0 to FavoritesIDs.Count-1 do
    begin
      MetaMenu := MenuList.Find(FavoritesIDs[I]);
      if (MetaMenu<>nil) and (MetaMenu.MenuType=LeafValue) then
        TUIMenuItem.Create(FFavorites,MetaMenu);
    end;
  end;
  }
begin
  // 获取基本数据
  GetMenus;
  GetMenuStructures;
  GetFunctions;

  // 创建抽象的唯一根节点，包含其他根节点
  MetaMenu := TKSMetaMenu.Create;
  MetaMenu.AuthNo := 0;
  MetaMenu.ID := '<Root>';
  MetaMenu.MenuType := MetaRootValue;
  MetaMenu.Caption := SRootMetaMenuCaption;
  MenuList.Add(MetaMenu);

  InitRoot;

  //InitFavorites;
end;

{ TUIFunction }

constructor TUIFunction.Create(AParent: TUIMenu;
  AMetaFunction: TKSMetaFunction);
begin
  inherited Create(AParent);
  FMetaFunction := AMetaFunction;
end;

destructor TUIFunction.Destroy;
begin
  FMetaFunction := nil;
  inherited;
end;

{ TKSMetaMenu }

function TKSMetaMenu.CanAuth: Boolean;
begin
  Result := FAuthNo > 0;
end;

constructor TKSMetaMenu.Create;
begin
  FHideInManageTree := False;
  FVirtualMenu := False;
  FCaptionSpellSet := False;
end;

function TKSMetaMenu.HaveAuth(const Auth: string): Integer;
begin
  if AuthNo <= 0 then
    Result := 1
  else if (AuthNo > Length(Auth)) then
    Result := 0
  else
  begin
    // 1<= Auto <=Len
    if Auth[AuthNo] = AuthChars[1] then
      Result := 1;
    if Auth[AuthNo] = AuthChars[0] then
      Result := 0;
  end;
end;

procedure TKSMetaMenu.SetAuth(var Auth: string; HavePower: Integer);
begin
  FormatAuth(Auth);
  if AuthNo > 0 then
    Auth[AuthNo] := AuthChars[HavePower];
end;

procedure TKSMetaMenu.SetAuthNo(const Value: Integer);
begin
  CheckRange(Value, 0, AuthLength);
  FAuthNo := Value;
end;

procedure TKSMetaMenu.SetCaption(const Value: string);
begin
  FCaption := Value;
  if not FCaptionSpellSet then
    FCaptionSpell := LowerCase(GetChineseFirstSpell(FCaption));
end;

procedure TKSMetaMenu.SetCaptionSpell(const Value: string);
begin
  FCaptionSpell := Value;
  FCaptionSpellSet := True;
end;

{ TKSMetaFunction }

function TKSMetaFunction.HaveAuth(const Auth: string): Integer;
begin
  if No <= 0 then
    Result := 1
  else if (No > Length(Auth)) then
    Result := 2
  else
  begin
    // 1<= Auto <=Len
    if Auth[No] = AuthChars[1] then
      Result := 1;
    if Auth[No] = AuthChars[0] then
      Result := 0;
    if Auth[No] = AuthChars[2] then
      Result := 2;
  end;
end;

procedure TKSMetaFunction.SetAuth(var Auth: string; HavePower: Integer);
begin
  FormatAuth(Auth);
  if No > 0 then
    Auth[No] := AuthChars[HavePower];
end;

procedure TKSMetaFunction.SetNo(const Value: Integer);
begin
  CheckRange(Value, 0, AuthLength);
  FNo := Value;
end;

end.
