unit KSConfigUtils;

interface

uses
  Windows, Messages, SysUtils, Classes, KSFrameWorks, IniFiles, IntfUtils;

const
  CategorySeperateChar = '|';

type
  TIniFileConfigSystem = class(TInterfacedObject, IConfigSystem)
  private
    FIniFile: TMemIniFile;
    FWritable: Boolean;
    FKey: string;
    FFileName: string;
    procedure OpenConfig;
    procedure SaveConfig;
  protected

  public
    constructor Create(const AFileName: string; AWritable: Boolean = False; const
      AKey: string = '');
    destructor Destroy; override;
    function ReadString(const Category, Key: string; const Default: string):
      string;
    function ReadInteger(const Category, Key: string; const Default: Integer):
      Integer;
    function ReadBoolean(const Category, Key: string; const Default: Boolean):
      Boolean;
    function ReadFloat(const Category, Key: string; const Default: Double):
      Double;
    function WriteString(const Category, Key: string; const Value: string):
      Boolean;
    function WriteInteger(const Category, Key: string; const Value: Integer):
      Boolean;
    function WriteBoolean(const Category, Key: string; const Value: Boolean):
      Boolean;
    function WriteFloat(const Category, Key: string; const Value: Double):
      Boolean;
    property Writable: Boolean read FWritable;
    property FileName: string read FFileName;
  end;

  TKSConfigSystem = class(TVCLInterfacedObject, IConfigSystem)
  private
    FCategoriesList: TStringList;
    FConfigSystems: TInterfaceList;
    FDefaultConfigSystem: IConfigSystem;
  protected

  public
    constructor Create;
    destructor Destroy; override;
    // 管理各个子部分的配置
    // 注意AddConfigSystem里面的参数Categories,必须是“|名称|名称|...|”的形式
    procedure AddConfigSystem(const Categories: string; AConfigSystem:
      IConfigSystem);
    procedure RemoveConfigSystem(AConfigSystem: IConfigSystem);
    function GetConfigSystem(const Category: string): IConfigSystem;
    property DefaultConfigSystem: IConfigSystem read FDefaultConfigSystem write
      FDefaultConfigSystem;
    // IConfigSystem
    function ReadString(const Category, Key: string; const Default: string):
      string;
    function ReadInteger(const Category, Key: string; const Default: Integer):
      Integer;
    function ReadBoolean(const Category, Key: string; const Default: Boolean):
      Boolean;
    function ReadFloat(const Category, Key: string; const Default: Double):
      Double;
    function WriteString(const Category, Key: string; const Value: string):
      Boolean;
    function WriteInteger(const Category, Key: string; const Value: Integer):
      Boolean;
    function WriteBoolean(const Category, Key: string; const Value: Boolean):
      Boolean;
    function WriteFloat(const Category, Key: string; const Value: Double):
      Boolean;
  end;

  TKSRunEnvirSystem = class(TVCLInterfacedObject, IConfigSystem)
  private
    FHasHTMLBrowser: Boolean;
    FNoHTMLHint: string;
    procedure GetRunEnvir;
  public
    constructor Create;
    // IConfigSystem
    function ReadString(const Category, Key: string; const Default: string):
      string;
    function ReadInteger(const Category, Key: string; const Default: Integer):
      Integer;
    function ReadBoolean(const Category, Key: string; const Default: Boolean):
      Boolean;
    function ReadFloat(const Category, Key: string; const Default: Double):
      Double;
    function WriteString(const Category, Key: string; const Value: string):
      Boolean;
    function WriteInteger(const Category, Key: string; const Value: Integer):
      Boolean;
    function WriteBoolean(const Category, Key: string; const Value: Boolean):
      Boolean;
    function WriteFloat(const Category, Key: string; const Value: Double):
      Boolean;
  end;

implementation

uses KSClientConsts, SHDocVw, FilterStreams;

{ TIniFileConfigSystem }

constructor TIniFileConfigSystem.Create(const AFileName: string; AWritable:
  Boolean; const AKey: string);
begin
  inherited Create;
  FWritable := AWritable;
  FFileName := AFileName;
  FKey := AKey;
  FIniFile := nil;
  OpenConfig;
end;

destructor TIniFileConfigSystem.Destroy;
begin
  SaveConfig;
  FreeAndNil(FIniFile);
  inherited;
end;

procedure TIniFileConfigSystem.OpenConfig;
var
  Strings: TStringList;
  FileStream: TFileStream;
  FilterStream: TFilterStream;
  Filter: IStreamFilter;
begin
  if FKey = '' then
  begin
    FIniFile := TMemIniFile.Create(FileName);
  end
  else
  begin
    FIniFile := TMemIniFile.Create('');
    FileStream := nil;
    FilterStream := nil;
    Strings := nil;
    try
      Filter := TXorFilter.Create(FKey);
      FileStream := TFileStream.Create(FileName, fmOpenRead or
        fmShareDenyWrite);
      FilterStream := TFilterStream.Create(FileStream, Filter);
      Strings := TStringList.Create;
      Strings.LoadFromStream(FilterStream);
      FIniFile.SetStrings(Strings);
    finally
      Strings.Free;
      FilterStream.Free;
      FileStream.Free;
    end;
  end;
end;

procedure TIniFileConfigSystem.SaveConfig;
var
  Strings: TStringList;
  FileStream: TFileStream;
  FilterStream: TFilterStream;
  Filter: IStreamFilter;
begin
  if FWritable and (FIniFile <> nil) then
  begin
    if FKey = '' then
    begin
      FIniFile.UpdateFile;
    end
    else
    begin
      FileStream := nil;
      FilterStream := nil;
      Strings := nil;
      try
        Filter := TXorFilter.Create(FKey);
        FileStream := TFileStream.Create(FileName, fmCreate);
        FilterStream := TFilterStream.Create(FileStream, Filter);
        Strings := TStringList.Create;
        FIniFile.GetStrings(Strings);
        Strings.SaveToStream(FilterStream);
      finally
        Strings.Free;
        FilterStream.Free;
        FileStream.Free;
      end;
    end;
  end;
end;

function TIniFileConfigSystem.ReadBoolean(const Category, Key: string;
  const Default: Boolean): Boolean;
begin
  try
    Result := FIniFile.ReadBool(Category, Key, Default);
  except
    Result := Default;
  end;
end;

function TIniFileConfigSystem.ReadFloat(const Category, Key: string;
  const Default: Double): Double;
begin
  try
    Result := FIniFile.ReadFloat(Category, Key, Default);
  except
    Result := Default;
  end;
end;

function TIniFileConfigSystem.ReadInteger(const Category, Key: string;
  const Default: Integer): Integer;
begin
  try
    Result := FIniFile.ReadInteger(Category, Key, Default);
  except
    Result := Default;
  end;
end;

function TIniFileConfigSystem.ReadString(const Category, Key,
  Default: string): string;
begin
  try
    Result := FIniFile.ReadString(Category, Key, Default);
  except
    Result := Default;
  end;
end;

function TIniFileConfigSystem.WriteBoolean(const Category, Key: string;
  const Value: Boolean): Boolean;
begin
  try
    Result := False;
    if Writable then
    begin
      FIniFile.WriteBool(Category, Key, Value);
      Result := True;
    end;
  except
    Result := False;
  end;
end;

function TIniFileConfigSystem.WriteFloat(const Category, Key: string;
  const Value: Double): Boolean;
begin
  try
    Result := False;
    if Writable then
    begin
      FIniFile.WriteFloat(Category, Key, Value);
      Result := True;
    end;
  except
    Result := False;
  end;
end;

function TIniFileConfigSystem.WriteInteger(const Category, Key: string;
  const Value: Integer): Boolean;
begin
  try
    Result := False;
    if Writable then
    begin
      FIniFile.WriteInteger(Category, Key, Value);
      Result := True;
    end;
  except
    Result := False;
  end;
end;

function TIniFileConfigSystem.WriteString(const Category, Key,
  Value: string): Boolean;
begin
  try
    Result := False;
    if Writable then
    begin
      FIniFile.WriteString(Category, Key, Value);
      Result := True;
    end;
  except
    Result := False;
  end;
end;

{ TKSConfigSystem }

constructor TKSConfigSystem.Create;
begin
  inherited Create(False);
  FCategoriesList := TStringList.Create;
  FConfigSystems := TInterfaceList.Create;
end;

destructor TKSConfigSystem.Destroy;
begin
  FDefaultConfigSystem := nil;
  FreeAndNil(FConfigSystems);
  FreeAndNil(FCategoriesList);
  inherited;
end;

function TKSConfigSystem.ReadBoolean(const Category, Key: string;
  const Default: Boolean): Boolean;
var
  AConfigSystem: IConfigSystem;
begin
  AConfigSystem := GetConfigSystem(Category);
  if AConfigSystem <> nil then
    Result := AConfigSystem.ReadBoolean(Category, Key, Default)
  else
    Result := Default;
end;

function TKSConfigSystem.ReadFloat(const Category, Key: string;
  const Default: Double): Double;
var
  AConfigSystem: IConfigSystem;
begin
  AConfigSystem := GetConfigSystem(Category);
  if AConfigSystem <> nil then
    Result := AConfigSystem.ReadFloat(Category, Key, Default)
  else
    Result := Default;
end;

function TKSConfigSystem.ReadInteger(const Category, Key: string;
  const Default: Integer): Integer;
var
  AConfigSystem: IConfigSystem;
begin
  AConfigSystem := GetConfigSystem(Category);
  if AConfigSystem <> nil then
    Result := AConfigSystem.ReadInteger(Category, Key, Default)
  else
    Result := Default;
end;

function TKSConfigSystem.ReadString(const Category, Key,
  Default: string): string;
var
  AConfigSystem: IConfigSystem;
begin
  AConfigSystem := GetConfigSystem(Category);
  if AConfigSystem <> nil then
    Result := AConfigSystem.ReadString(Category, Key, Default)
  else
    Result := Default;
end;

procedure TKSConfigSystem.AddConfigSystem(const Categories: string;
  AConfigSystem: IConfigSystem);
begin
  FCategoriesList.Add(Categories);
  FConfigSystems.Add(AConfigSystem);
end;

procedure TKSConfigSystem.RemoveConfigSystem(AConfigSystem: IConfigSystem);
var
  I: Integer;
begin
  I := FConfigSystems.Remove(AConfigSystem);
  if I >= 0 then
    FCategoriesList.Delete(I);
  if FDefaultConfigSystem = AConfigSystem then
    FDefaultConfigSystem := nil;
end;

function TKSConfigSystem.GetConfigSystem(
  const Category: string): IConfigSystem;
var
  I: Integer;
  Part: string;
begin
  Result := FDefaultConfigSystem;
  Part := CategorySeperateChar + Category + CategorySeperateChar;
  for I := 0 to FCategoriesList.Count - 1 do
  begin
    if Pos(Part, FCategoriesList[I]) > 0 then
    begin
      Result := IConfigSystem(FConfigSystems[I]);
      Break;
    end;
  end;
end;

function TKSConfigSystem.WriteBoolean(const Category, Key: string;
  const Value: Boolean): Boolean;
var
  AConfigSystem: IConfigSystem;
begin
  AConfigSystem := GetConfigSystem(Category);
  if AConfigSystem <> nil then
    Result := AConfigSystem.WriteBoolean(Category, Key, Value)
  else
    Result := False;
end;

function TKSConfigSystem.WriteFloat(const Category, Key: string;
  const Value: Double): Boolean;
var
  AConfigSystem: IConfigSystem;
begin
  AConfigSystem := GetConfigSystem(Category);
  if AConfigSystem <> nil then
    Result := AConfigSystem.WriteFloat(Category, Key, Value)
  else
    Result := False;
end;

function TKSConfigSystem.WriteInteger(const Category, Key: string;
  const Value: Integer): Boolean;
var
  AConfigSystem: IConfigSystem;
begin
  AConfigSystem := GetConfigSystem(Category);
  if AConfigSystem <> nil then
    Result := AConfigSystem.WriteInteger(Category, Key, Value)
  else
    Result := False;
end;

function TKSConfigSystem.WriteString(const Category, Key,
  Value: string): Boolean;
var
  AConfigSystem: IConfigSystem;
begin
  AConfigSystem := GetConfigSystem(Category);
  if AConfigSystem <> nil then
    Result := AConfigSystem.WriteString(Category, Key, Value)
  else
    Result := False;
end;

{ TKSRunEnvirSystem }

constructor TKSRunEnvirSystem.Create;
begin
  inherited Create(True);
  GetRunEnvir;
end;

procedure TKSRunEnvirSystem.GetRunEnvir;
begin
  FHasHTMLBrowser := not FindCmdLineSwitch(NoHTMLSwitch, ['-', '/'], True);
  if FHasHTMLBrowser then
  begin
    try
      CoInternetExplorer.Create;
    except
      FHasHTMLBrowser := False;
      FNoHTMLHint := SNoInstallHTML;
    end;
  end
  else
    FNoHTMLHint := SProhibitHTML;
end;

function TKSRunEnvirSystem.ReadBoolean(const Category, Key: string;
  const Default: Boolean): Boolean;
begin
  Result := Default;
  if SameText(Key, ckHTML) then
    Result := FHasHTMLBrowser;
end;

function TKSRunEnvirSystem.ReadFloat(const Category, Key: string;
  const Default: Double): Double;
begin
  Result := Default;
end;

function TKSRunEnvirSystem.ReadInteger(const Category, Key: string;
  const Default: Integer): Integer;
begin
  Result := Default;
end;

function TKSRunEnvirSystem.ReadString(const Category, Key,
  Default: string): string;
begin
  Result := Default;
  if SameText(Key, ckNoHTMLHint) then
    Result := FNoHTMLHint;
end;

function TKSRunEnvirSystem.WriteBoolean(const Category, Key: string;
  const Value: Boolean): Boolean;
begin
  Result := False;
end;

function TKSRunEnvirSystem.WriteFloat(const Category, Key: string;
  const Value: Double): Boolean;
begin
  Result := False;
end;

function TKSRunEnvirSystem.WriteInteger(const Category, Key: string;
  const Value: Integer): Boolean;
begin
  Result := False;
end;

function TKSRunEnvirSystem.WriteString(const Category, Key,
  Value: string): Boolean;
begin
  Result := False;
end;

end.
