unit KSMenus;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSMenus
   <What>菜单
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}


interface

uses SysUtils, Classes, Contnrs, KSFrameWorks, KSStrUtils, Dialogs;

type
  TUIMenuGroup = class;

  TUIMenu = class
  private
    FDescription: string;
    FCaption: string;
    FParent: TUIMenuGroup;
    FMenuType: Integer;
    FVisible: Boolean;
    FMenuId: string;
  public
    constructor Create(AParent : TUIMenuGroup); virtual;
    destructor  Destroy; override;
    property    Parent : TUIMenuGroup read FParent;
    property    Caption : string read FCaption write FCaption;
    property    Description : string read FDescription write FDescription;
    property    MenuType : Integer read FMenuType write FMenuType;
    property    Visible : Boolean read FVisible write FVisible;
    property    MenuId : string read FMenuId write FMenuId;
  end;

  TUIMenuItem = class(TUIMenu)
  private
    FUICode: TUICode;
    FReferencedItems: TList;
    FReferences: TStrings;
  public
    constructor Create(AParent : TUIMenuGroup); override;
    destructor  Destroy;override;
    property    UICode : TUICode read FUICode Write FUICode;
    property    References : TStrings read FReferences;
    property    ReferencedItems : TList read FReferencedItems;
  end;

  TUIMenuGroup = class(TUIMenu)
  private
    FList : TObjectList;
    function    GetCount: integer;
    function    GetItems(index: integer): TUIMenu;
    procedure   Add(Item : TUIMenu);
    procedure   Extract(UIMenu: TUIMenu);
  public
    constructor Create(AParent : TUIMenuGroup); override;
    Destructor  Destroy;override;
    procedure   Clear;
    property    Count : integer read GetCount ;
    property    Items[index:integer] : TUIMenu read GetItems;
    function    FindMenuItem(AUICode : TUICode): TUIMenuItem;
  end;

procedure LoadMenusFromFile(MenuCatalogs : TUIMenuGroup; const FileName:string);

procedure ReadMenuInfo(const s:string; AMenu:TUIMenu);

implementation

(*
procedure ReadMenuInfo(const s:string; AMenu:TUIMenu);
var
  i : integer;
  s1,s2,s3 : string;
begin
  i := pos(',',s);
  if i<=0 then
    AMenu.Caption:=s
  else
  begin
    AMenu.Caption:=copy(s,1,i-1);
    s1:=copy(s,i+1,length(s));
    i:=pos(',',s1);
    if i<=0 then
    begin
      s2 := s1;
      s3 := '';
    end
    else
    begin
      s2 := copy(s1,1,i-1);
      s3 := copy(s1,i+1,length(s1));
    end;
    if AMenu is TUIMenuItem then
    begin
      TUIMenuItem(AMenu).UICode:=s2;
      TUIMenuItem(AMenu).Description:=s3;
    end
    else
      AMenu.Description:=s1;
  end;
  // set default UICode=Caption
  if AMenu is TUIMenuItem then
    With TUIMenuItem(AMenu) do
      if UICode='' then UICode:=Caption;
  if AMenu.Description='' then
    AMenu.Description := AMenu.Caption;
  // new add
  if (Pos('设置',AMenu.Caption)>0) or (Pos('参数',AMenu.Caption)>0) then
    AMenu.MenuType := 4
  else if (Pos('查询',AMenu.Caption)>0) or (Pos('排行',AMenu.Caption)>0) or (Pos('统计',AMenu.Caption)>0) or (Pos('汇总',AMenu.Caption)>0) then
    AMenu.MenuType := 2
  else if (Pos('表',AMenu.Caption)>0) then
    AMenu.MenuType := 3
  else if (Pos('金',AMenu.Caption)>0) or (Pos('款',AMenu.Caption)>0) or (Pos('产',AMenu.Caption)>0) then
    AMenu.MenuType := 1
  else if (Pos('客户',AMenu.Caption)>0) or (Pos('账号',AMenu.Caption)>0) or (Pos('帐号',AMenu.Caption)>0) or (Pos('代码',AMenu.Caption)>0)  then
    AMenu.MenuType := 0
  else
    AMenu.MenuType := 5;
end;
*)

procedure ReadMenuInfo(const s:string; AMenu:TUIMenu);
var
  MenuItem : TUIMenuItem;
begin
  if not (AMenu is TUIMenuItem) then
  begin
    AMenu.Caption := S;
  end else
  begin
    MenuItem := TUIMenuItem(AMenu);
    seperateStr(S,[',',';'],MenuItem.References,True);
    if MenuItem.References.Count>0 then
    begin
      MenuItem.Caption := MenuItem.References[0];
      MenuItem.References.Delete(0);
    end;
    if MenuItem.References.Count>0 then
    begin
      MenuItem.UICode:= MenuItem.References[0];
      MenuItem.References.Delete(0);
    end;
    if MenuItem.References.Count>0 then
    begin
      MenuItem.Description:= MenuItem.References[0];
      MenuItem.References.Delete(0);
    end;
    if MenuItem.UICode='' then
      MenuItem.UICode:=MenuItem.Caption;
    if MenuItem.Description='' then
      MenuItem.Description:=MenuItem.Caption;
  end;
end;

procedure LinkReferences(MenuCatalogs : TUIMenuGroup);

  procedure DoLink(Group : TUIMenuGroup);
  var
    I,J : Integer;
    Item : TUIMenu;
    UICode : string;
    ReferMenu : TUIMenuItem;
  begin
    for I:=0 to Group.Count-1 do
    begin
      Item := Group.Items[I];
      if Item is TUIMenuGroup then
        DoLink(TUIMenuGroup(Item)) else
      begin
        Assert(Item is TUIMenuItem);
        for J:=0 to TUIMenuItem(Item).References.Count-1 do
        begin
          UICode := TUIMenuItem(Item).References[J];
          ReferMenu := MenuCatalogs.FindMenuItem(UICode);
          if ReferMenu<>nil then
            TUIMenuItem(Item).ReferencedItems.Add(ReferMenu);
        end;
      end;
    end;
  end;

begin
  DoLink(MenuCatalogs);
end;

procedure LoadMenusFromFile(MenuCatalogs : TUIMenuGroup; const FileName:string);
var
  Strings : TStringList;
  S : string;
  i,j,len : integer;
  MenuGroupStack : TList;
  AMenu : TUIMenu;
  Parent : TUIMenuGroup;
begin
  Strings := nil;
  //MenuGroupStack := nil;
  try
    Strings := TStringList.Create;
    MenuGroupStack := TList.Create;
    MenuCatalogs.Clear;
    Strings.LoadFromFile(FileName);
    for i:=0 to Strings.Count-1 do
    begin
      s := Trim(Strings[i]);
      len := length(s);
      if len>0 then
      begin
        if s[1]='#' then
        begin
          AMenu := TUIMenuGroup.Create(MenuCatalogs);
          ReadMenuInfo(copy(s,2,len),AMenu);
          MenuGroupStack.Clear;
          MenuGroupStack.Add(AMenu);
        end
        else
        begin
          j:=1;
          while (j<=len) and (s[j]='-') do
            inc(j);
          dec(j); // j is the menu level from 1 to ...

          if j>=0 then
          begin
            MenuGroupStack.Count := j;
            if j>0 then
              Parent := TUIMenuGroup(MenuGroupStack[j-1]) else
              Parent := MenuCatalogs;
            if (j+1<=len) and (s[j+1]='+') then
            begin
              AMenu := TUIMenuGroup.Create(Parent);
              s := copy(s,j+2,len-(j+2)+1);
              ReadMenuInfo(s,AMenu);
              MenuGroupStack.Add(AMenu);
            end
            else
            begin
              AMenu := TUIMenuItem.Create(Parent);
              s := copy(s,j+1,len-(j+1)+1);
              ReadMenuInfo(s,AMenu);
            end;
          end;
        end;
      end;
    end;
    LinkReferences(MenuCatalogs);
  finally
    Strings.Free;
  end;
end;

{ TUIMenuGroup }

constructor TUIMenuGroup.Create(AParent : TUIMenuGroup);
begin
  inherited;
  FList := TObjectList.Create;
end;

destructor TUIMenuGroup.Destroy;
var
  Temp : TObject;
begin
  Temp := FList;
  FList := nil;
  Temp.Free;
  inherited;
end;

procedure TUIMenuGroup.Add(Item: TUIMenu);
begin
  FList.Add(Item);
end;

function TUIMenuGroup.GetCount: integer;
begin
  Result := FList.Count;
end;

function TUIMenuGroup.GetItems(index: integer): TUIMenu;
begin
  Result := TUIMenu(FList[index]);
end;

procedure TUIMenuGroup.Clear;
begin
  FList.Clear;
end;

function TUIMenuGroup.FindMenuItem(AUICode: TUICode): TUIMenuItem;
var
  I : Integer;

begin
  for I:=0 to Count-1 do
  begin
    if Items[I] is TUIMenuItem then
    begin
      Result := TUIMenuItem(Items[I]);
      if SameText(Result.UICode,AUICode) then
        Exit;
    end
    else if Items[I] is TUIMenuGroup then
    begin
      Result := TUIMenuGroup(Items[I]).FindMenuItem(AUICode);
      if Result<>nil then Exit;
    end;
  end;
  Result := nil;
end;

procedure TUIMenuGroup.Extract(UIMenu: TUIMenu);
begin
  if FList<>nil then
    FList.Extract(UIMenu);
end;

{ TUIMenu }

constructor TUIMenu.Create(AParent: TUIMenuGroup);
begin
  FParent:=AParent;
  if FParent<>nil then FParent.Add(self);
  MenuType := -1;
  Visible := true;
end;

destructor TUIMenu.Destroy;
begin
  if FParent<>nil then
    FParent.Extract(self);
  FParent:= nil;
  inherited;  
end;

{ TUIMenuItem }

constructor TUIMenuItem.Create(AParent: TUIMenuGroup);
begin
  inherited;
  FReferencedItems := TList.Create;
  FReferences := TStringList.Create;
end;

destructor TUIMenuItem.Destroy;
begin
  FreeAndNil(FReferences);
  FreeAndNil(FReferencedItems);
  inherited;
end;

end.
