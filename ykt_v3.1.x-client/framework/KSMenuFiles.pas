unit KSMenuFiles;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSMenuFiles
   <What>从文件读取菜单休息
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}

interface

uses SysUtils, Classes, KSMenuAdmin;

procedure ReadMenuAdminFromFile(AMenuAdmin: TMenuAdmin;
  const FileName: string;
  AutoCreateNewMenu: Boolean = True);

procedure ReadMenuAdminFromDataFile(AMenuAdmin: TMenuAdmin;
  const FileName, Key: string;
  AutoCreateNewMenu: Boolean = True);

procedure WriteMenuAdminToFile(AMenuAdmin: TMenuAdmin;
  const FileName: string);

implementation

uses TextUtils, Contnrs, FilterStreams;

const
  DefineSection = '[menus]';
  StructureSection = '[tree]';
  //FavoritesSection  = '[Favorites]';
  IDKey = 'ID';
  NoKey = '.no';
  TypeKey = '.type';
  CaptionKey = '.caption';
  KeywordKey = '.keyword';
  SeeKey = '.see';
  FuncKey = '.func';
  DesKey = '.des';
  SpellKey = '.spell';
  HideKey = '.hide';
  VirtualKey = '.virtual';

  GroupType = 'group';
  RootType = 'root';
  LeafType = '';

procedure IntenalReadMenuAdmin(AMenuAdmin: TMenuAdmin; Stream: TStream;
  AutoCreateNewMenu: Boolean);
type
  TReadSection = (rsNone, rsDefine, rsStructure {, rsFavorites});
var
  Line: string;
  //Values  : TStringList;
  Reader: TTextReader;
  Section: TReadSection;
  LastMenu: TKSMetaMenu;
  ParentStack: TList;
  CountStack: TList;

  // 读取菜单定义行的数据
  procedure ProcDefineLine;
  var
    Key: string;
    Value: string;
    I: Integer;
  begin
    I := Pos('=', Line);
    if I > 0 then
    begin
      Key := Copy(Line, 1, I - 1);
      Value := Copy(Line, I + 1, Length(Line));
      if SameText(Key, IDKey) then
      begin
        if Trim(Value) <> '' then
        begin
          LastMenu := TKSMetaMenu.Create;
          LastMenu.ID := Value;
          LastMenu.Caption := Value;
          LastMenu.AuthNo := 0;
          LastMenu.MenuType := LeafValue;
          AMenuAdmin.MenuList.Add(LastMenu);
        end
        else
        begin
          LastMenu := nil;
        end;
      end
      else if LastMenu <> nil then
      begin
        if SameText(Key, NoKey) then
        begin
          LastMenu.AuthNo := StrToIntDef(Value, 0);
        end
        else if SameText(Key, TypeKey) then
        begin
          if SameText(Value, GroupType) then
            LastMenu.MenuType := GroupValue
          else if SameText(Value, RootType) then
            LastMenu.MenuType := RootValue
          else
            LastMenu.MenuType := LeafValue
        end
        else if SameText(Key, CaptionKey) then
        begin
          if Value <> '' then
            LastMenu.Caption := Value;
        end
        else if SameText(Key, KeywordKey) then
          LastMenu.Keywords := Value
        else if SameText(Key, SeeKey) then
          LastMenu.See := Value
        else if SameText(Key, FuncKey) then
          LastMenu.FunctionSet := Value
        else if SameText(Key, DesKey) then
          LastMenu.Description := Value
        else if SameText(Key, SpellKey) then
          LastMenu.CaptionSpell := Lowercase(Value)
        else if SameText(Key, HideKey) then
          LastMenu.HideInManageTree := Value = '1'
        else if SameText(Key, VirtualKey) then
          LastMenu.VirtualMenu := Value = '1';
      end;
    end;
  end;

  // 读取菜单结构部分的数据
  procedure ProcStructureLine;
  var
    Level: Integer;
    I, Len: Integer;
    ID: string;
    Menu: TKSMetaMenu;
    MenuStructure: TKSMenuStructure;
    MenuType: string;
  begin
    //Level := 2;
    Level := 1;
    I := 1;
    Len := Length(Line);
    MenuType := LeafValue;
    while (I < Len) and (Line[I] in ['-', '+', '#', '*', '%']) do
    begin
      case Line[I] of
        '-':
          Inc(Level);
        //'*' : Level := 1;   // 1 Level
        '%':
          begin
            Level := 0; // Root
            MenuType := RootValue;
          end;
        '#', '*', '+':
          MenuType := GroupValue;
      end;
      Inc(I);
    end;
    ID := Copy(Line, I, Len);
    Menu := AMenuAdmin.MenuList.Find(ID);
    if (Menu = nil) and AutoCreateNewMenu and (ID <> '') then
    begin
      Menu := TKSMetaMenu.Create;
      AMenuAdmin.MenuList.Add(Menu);
      Menu.ID := ID;
      Menu.Caption := ID;
      Menu.MenuType := MenuType;
      if Menu.MenuType = RootValue then
        Menu.AuthNo := 0
      else
        Menu.AuthNo := AMenuAdmin.MenuList.Count;
    end;
    if Menu <> nil then
    begin
      if Level = 0 then
      begin
        ParentStack.Clear;
        ParentStack.Add(Menu);
        CountStack.Clear;
        CountStack.Add(Pointer(0));
      end
      else if (Level > 0) and (Level <= ParentStack.Count) then
      begin
        ParentStack.Count := Level;
        MenuStructure := TKSMenuStructure.Create;
        AMenuAdmin.MenuStructureList.Add(MenuStructure);
        MenuStructure.ParentId := TKSMetaMenu(ParentStack[Level - 1]).Id;
        MenuStructure.ChildId := Menu.Id;
        MenuStructure.SequenceNo := Integer(CountStack[Level - 1]) + 1;
        CountStack[Level - 1] := Pointer(MenuStructure.SequenceNo);
        if Menu.MenuType <> LeafValue then
        begin
          ParentStack.Add(Menu);
          CountStack.Add(Pointer(0));
        end;
      end;
    end;
  end;
  {
  procedure ProcFavoritesLine;
  begin
    //if AMenuAdmin.MenuList.Find();
    AMenuAdmin.FavoritesIDs.Add(Line);
  end;
  }
begin
  // 主体部分
  //Values := nil;
  Reader := nil;
  LastMenu := nil;
  ParentStack := nil;
  CountStack := nil;
  try
    //Values := TStringList.Create;
    Reader := TTextReader.Create(Stream);
    Reader.IsFilterLines := True;
    Reader.CommonChar := ';';
    ParentStack := TList.Create;
    CountStack := TList.Create;
    Section := rsNone;
    AMenuAdmin.MenuList.Clear;
    AMenuAdmin.MenuStructureList.Clear;
    //AMenuAdmin.FavoritesIDs.Clear;
    while not Reader.Eof do
    begin
      Line := Reader.Readln;
      if Line <> '' then
      begin
        // 判断是否是新的分段
        if SameText(Line, DefineSection) then
        begin
          Section := rsDefine;
          LastMenu := nil;
        end
        else if SameText(Line, StructureSection) then
        begin
          Section := rsStructure;
          ParentStack.Clear;
        end
          {
          else if SameText(Line,FavoritesSection) then
          begin
            Section := rsFavorites;
            AMenuAdmin.FavoritesIDs.Clear;
          end
          }
        else if Line[1] = '[' then
        begin
          Section := rsNone;
        end
        else
        begin
          // 根据分段调用相应的子程序
          case Section of
            rsDefine: ProcDefineLine;
            rsStructure: ProcStructureLine;
            //rsFavorites : ProcFavoritesLine;
          end;
        end;
      end;
    end;
  finally
    //Values.Free;
    Reader.Free;
    ParentStack.Free;
    CountStack.Free;
  end;
  AMenuAdmin.Init;
end;

procedure ReadMenuAdminFromFile(AMenuAdmin: TMenuAdmin; const FileName: string;
  AutoCreateNewMenu: Boolean = True);
var
  FileStream: TFileStream;
begin
  FileStream := TFileStream.Create(FileName, fmOpenRead or fmShareDenyWrite);
  try
    IntenalReadMenuAdmin(AMenuAdmin, FileStream, AutoCreateNewMenu);
  finally
    FileStream.Free;
  end;
end;

procedure ReadMenuAdminFromDataFile(AMenuAdmin: TMenuAdmin;
  const FileName, Key: string;
  AutoCreateNewMenu: Boolean = True);
var
  FileStream: TFileStream;
  FilterStream: TFilterStream;
  Filter: IStreamFilter;
begin
  FileStream := nil;
  FilterStream := nil;
  try
    Filter := TXorFilter.Create(Key);
    FileStream := TFileStream.Create(FileName, fmOpenRead or fmShareDenyWrite);
    FilterStream := TFilterStream.Create(FileStream, Filter);

    IntenalReadMenuAdmin(AMenuAdmin, FilterStream, AutoCreateNewMenu);
  finally
    FilterStream.Free;
    FileStream.Free;
  end;
end;

procedure WriteMenuAdminToFile(AMenuAdmin: TMenuAdmin; const FileName: string);
var
  Writer: TTextWriter;

  procedure WriteDefines;
  var
    I: Integer;
    Menu: TKSMetaMenu;
  begin
    Writer.Println(DefineSection);
    with AMenuAdmin.MenuList do
      for I := 0 to Count - 1 do
      begin
        Menu := TKSMetaMenu(Items[I]);
        if Menu.MenuType <> MetaRootValue then
        begin
          Writer.Println(Format('%s=%s', [IDKey, Menu.ID]));
          Writer.Println(Format('%s=%d', [NoKey, Menu.AuthNo]));
          if Menu.MenuType = GroupValue then
            Writer.Println(Format('%s=%s', [TypeKey, GroupType]))
          else if Menu.MenuType = RootValue then
            Writer.Println(Format('%s=%s', [TypeKey, RootType]))
          else
            Writer.Println(Format('%s=%s', [TypeKey, LeafType]));
          Writer.Println(Format('%s=%s', [CaptionKey, Menu.Caption]));
          Writer.Println(Format('%s=%s', [KeywordKey, Menu.Keywords]));
          Writer.Println(Format('%s=%s', [SeeKey, Menu.See]));
          Writer.Println(Format('%s=%s', [FuncKey, Menu.FunctionSet]));
          Writer.Println(Format('%s=%s', [DesKey, Menu.Description]));
          Writer.Println(Format('%s=%s', [SpellKey, Menu.CaptionSpell]));
          if Menu.HideInManageTree then
            Writer.Println(Format('%s=1', [HideKey]));
          if Menu.VirtualMenu then
            Writer.Println(Format('%s=1', [VirtualKey]));
          Writer.Println(';*************');
        end;
      end;
  end;

  procedure WriteStructure;

    procedure WriteMenuGroup(Level: Integer; MenuGroup: TUIMenuGroup);
    var
      I: Integer;
      UIMenu: TUIMenu;
      Line: string;
    begin
      for I := 0 to MenuGroup.Count - 1 do
      begin
        UIMenu := MenuGroup.Items[I];
        Line := '';
        if UIMenu is TUIMenuGroup then
        begin
          case Level of
            -1: Line := '%' + UIMenu.MetaMenu.Id;
            0: Line := '#' + UIMenu.MetaMenu.Id;
          end;
          if Level > 0 then
            Line := StringOfChar('-', Level) + '+' + UIMenu.MetaMenu.Id;
          if Line <> '' then
          begin
            Writer.Println(Line);
            WriteMenuGroup(Level + 1, TUIMenuGroup(UIMenu));
          end;
        end
        else if UIMenu is TUIMenuItem then
        begin
          if Level > 0 then
          begin
            Line := StringOfChar('-', Level) + UIMenu.MetaMenu.Id;
            Writer.Println(Line);
          end;
        end;
      end;
    end;

  begin
    Writer.Println(StructureSection);
    if AMenuAdmin.Root <> nil then
      WriteMenuGroup(-1, AMenuAdmin.Root);
  end;

  {
  procedure WriteFavorites;
  begin
    Writer.Println(FavoritesSection);
    Writer.Print(AMenuAdmin.FavoritesIDs);
  end;
  }

begin
  Writer := nil;
  try
    Writer := TTextWriter.Create(FileName);
    WriteDefines;
    Writer.Println('');
    WriteStructure;
    Writer.Println('');
    //WriteFavorites;
  finally
    Writer.Free;
  end;
end;

end.
