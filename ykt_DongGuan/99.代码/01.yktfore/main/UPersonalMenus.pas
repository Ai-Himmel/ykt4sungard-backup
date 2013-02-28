unit UPersonalMenus;
{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UPersonalMenus
   <What>管理个人菜单的对象类
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}

interface

uses SysUtils, Classes, KSMenuAdmin;

type
  {
    <Class>TPersonalMenus
    <What>管理个人菜单的对象类
    负责读取/保存/创建个人菜单。
    <Properties>
      -
    <Methods>
      -
    <Event>
      -
  }
  TPersonalMenus = class(TObject)
  private
    FModified: Boolean;
    FPersonalMenuIDs: TStrings;
    FPersonalMenus: TUIMenuGroup;
    FIDsTimeStamp: Integer;
    FMenusTimeStamp: Integer;
    procedure DoChanged(Sender: TObject);
    function GetPersonalMenus: TUIMenuGroup;
  protected

  public
    constructor Create;
    destructor Destroy; override;
    procedure AfterLogin;
    procedure BeforeLogout;
    procedure RebuildMenus;
    procedure CheckRebuildMenus;
    procedure LoadMenus;
    procedure SaveMenus;
    function AddMenu(const UICode: string): Boolean;

    property PersonalMenus: TUIMenuGroup read GetPersonalMenus;
    property PersonalMenuIDs: TStrings read FPersonalMenuIDs;
    property Modified: Boolean read FModified;
  end;

implementation

uses KSFrameWorks, KSFrameWorkUtils, KSClientConsts;

{ TPersonalMenus }

constructor TPersonalMenus.Create;
begin
  inherited;
  FPersonalMenuIDs := TStringList.Create;
  TStringList(FPersonalMenuIDs).OnChange := DoChanged;
  FPersonalMenus := CreateUIMenuGroupFromIDs(UserMenuRootCaption, '');
  FPersonalMenus.UICode := UserMenuRootID;
  FIDsTimeStamp := 0;
  FMenusTimeStamp := 0;
end;

destructor TPersonalMenus.Destroy;
begin
  FreeAndNil(FPersonalMenus);
  FreeAndNil(FPersonalMenuIDs);
  inherited;
end;

procedure TPersonalMenus.AfterLogin;
begin
  LoadMenus;
  RebuildMenus;
  FModified := False;
end;

procedure TPersonalMenus.BeforeLogout;
begin
  if FModified then
    SaveMenus;
  FPersonalMenuIDs.Clear;
  FPersonalMenus.Clear;
end;

procedure TPersonalMenus.DoChanged(Sender: TObject);
begin
  FModified := True;
  Inc(FIDsTimeStamp);
end;

function TPersonalMenus.GetPersonalMenus: TUIMenuGroup;
begin
  Result := FPersonalMenus;
  CheckRebuildMenus;
end;

procedure TPersonalMenus.CheckRebuildMenus;
begin
  if FMenusTimeStamp < FIDsTimeStamp then
  begin
    RebuildMenus;
  end;
end;

procedure TPersonalMenus.RebuildMenus;
begin
  FMenusTimeStamp := FIDsTimeStamp;
  GetUIMenuGroupFromIDs(FPersonalMenus, FPersonalMenuIDs);
end;

procedure TPersonalMenus.LoadMenus;
var
  Count, I: Integer;
  ID: string;
  ConfigSystem: IConfigSystem;
  Key: string;
begin
  FPersonalMenuIDs.Clear;
  FPersonalMenus.Clear;
  ConfigSystem := Context.GetConfigSystem;
  Count := ConfigSystem.ReadInteger(ccUserMenus, ckUserMenuCount,
    cdUserMenuCount);
  for I := 1 to Count do
  begin
    Key := IntToStr(I);
    ID := ConfigSystem.ReadString(ccUserMenus, Key, '');
    if (ID <> '') and (MenuAdmin.MenuList.Find(ID) <> nil) then
      FPersonalMenuIDs.Add(ID);
  end;
end;

procedure TPersonalMenus.SaveMenus;
var
  Count, I: Integer;
  ID: string;
  ConfigSystem: IConfigSystem;
  Key: string;
begin
  ConfigSystem := Context.GetConfigSystem;
  Count := FPersonalMenuIDs.Count;
  ConfigSystem.WriteInteger(ccUserMenus, ckUserMenuCount, Count);
  for I := 1 to Count do
  begin
    Key := IntToStr(I);
    ID := FPersonalMenuIDs[I - 1];
    ConfigSystem.WriteString(ccUserMenus, Key, ID);
  end;
end;

function TPersonalMenus.AddMenu(const UICode: string): Boolean;
begin
  Result := FPersonalMenuIDs.IndexOf(UICode) < 0;
  if Result then
    FPersonalMenuIDs.Add(UICode);
end;

end.
