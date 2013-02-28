unit UDebugSystem;

interface

uses SysUtils, Classes, KSFrameWorks, DB, WorkViews;

type
  TKSDebugSystem = class(TInterfacedObject, IDebugSystem)
  private
    FSubSystem  : TInterfaceList;
  protected
    // IDebugSystem
    procedure   DebugDataSource(DataSource : TDataSource; const ACaption:string='');
    procedure   DebugDataset(Dataset : TDataset; const ACaption:string='');
    procedure   DebugWorkView(WorkView : TWorkView; const ACaption:string='');
    procedure   DebugUI(ARoot : TComponent; const ACaption:string='');
    procedure   DebugDatabase;
    procedure   ShowLog;
    procedure   GetDebugToolNames(ToolNames : TStrings);
    procedure   ExecuteDebugTool(CurrentInstanceRecord : TUIInstanceRecord; const ToolName : string);
    procedure   InstallSubSystem(SubSystem : IDebugSubSystem);
    procedure   UnInstallSubSystem(SubSystem : IDebugSubSystem);
  public
    constructor Create;
    destructor  Destroy; override;
  end;

implementation

uses KSClientConsts, KCDataAccess, UDebugDataset, UDebugWorkView, UDebugDatabase, ExtUtils;

procedure InstallDebugSystem;
begin
  if Context<>nil then
    Context.SetDebugSystem(TKSDebugSystem.Create);
end;

procedure UnInstallDebugSystem;
begin
  if Context<>nil then
    Context.SetDebugSystem(nil);
end;


{ TKSDebugSystem }

procedure TKSDebugSystem.DebugDataset(Dataset: TDataset; const ACaption:string='');
begin
  DoDebugDataset(Dataset, ACaption);
end;

procedure TKSDebugSystem.DebugUI(ARoot: TComponent; const ACaption:string='');
begin

end;

procedure TKSDebugSystem.DebugWorkView(WorkView: TWorkView; const ACaption:string='');
begin
  DoDebugWorkView(WorkView, ACaption);
end;

procedure TKSDebugSystem.DebugDataSource(DataSource: TDataSource;
  const ACaption: string);
begin
  DoDebugDataSource(DataSource, ACaption);
end;

procedure TKSDebugSystem.DebugDatabase;
begin
  DoDebugDatabase(TKCDatabase(DatabaseModule.GetDatabase));
end;

procedure TKSDebugSystem.ShowLog;
begin
  ShellOpenFileEx('notepad.exe',ProgramLogFileName);
end;

procedure TKSDebugSystem.GetDebugToolNames(ToolNames: TStrings);
var
  I : Integer;
  SubSystem : IDebugSubSystem;
begin
  ToolNames.Clear;
  for I:=0 to FSubSystem.Count-1 do
  begin
    SubSystem := IDebugSubSystem(FSubSystem[I]);
    SubSystem.GetDebugToolNames(ToolNames);
  end;
end;

procedure TKSDebugSystem.ExecuteDebugTool(
  CurrentInstanceRecord: TUIInstanceRecord; const ToolName: string);
var
  I : Integer;
  SubSystem : IDebugSubSystem;
begin
  for I:=0 to FSubSystem.Count-1 do
  begin
    SubSystem := IDebugSubSystem(FSubSystem[I]);
    if SubSystem.HaveDebugTool(ToolName) then
    begin
      SubSystem.ExecuteDebugTool(CurrentInstanceRecord, ToolName);
      Break;
    end;
  end;
end;

constructor TKSDebugSystem.Create;
begin
  inherited;
  FSubSystem  := TInterfaceList.Create;
end;

destructor TKSDebugSystem.Destroy;
var
  Obj : TObject;
begin
  Obj := FSubSystem;
  FSubSystem := nil;
  Obj.Free;
  inherited;
end;

procedure TKSDebugSystem.InstallSubSystem(SubSystem: IDebugSubSystem);
begin
  FSubSystem.Add(SubSystem);
end;

procedure TKSDebugSystem.UnInstallSubSystem(SubSystem: IDebugSubSystem);
begin
  if FSubSystem<>nil then
    FSubSystem.Remove(SubSystem);
end;

initialization
  InstallDebugSystem;

finalization
  UnInstallDebugSystem;

end.
