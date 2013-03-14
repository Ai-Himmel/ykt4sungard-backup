unit UDebugReportProj;

interface

uses SysUtils, Classes, KSFrameWorks;

const
  SProjectReport = '程序报告工具';

type
  TKSDebugProjectReport = class(TInterfacedObject, IDebugSubSystem)
  private

  protected
    // IDebugSubSystem
    function  HaveDebugTool(const ToolName : string) : Boolean;
    procedure GetDebugToolNames(ToolNames : TStrings);
    procedure ExecuteDebugTool(CurrentInstanceRecord : TUIInstanceRecord; const ToolName : string);
  public

  end;

implementation

uses UProjectReport;

var
  DebugProjectReport : IDebugSubSystem;

{ TKSDebugProjectReport }

procedure TKSDebugProjectReport.ExecuteDebugTool(
  CurrentInstanceRecord: TUIInstanceRecord; const ToolName: string);
begin
  ShowProjectReport;
end;

procedure TKSDebugProjectReport.GetDebugToolNames(ToolNames: TStrings);
begin
  ToolNames.Add(SProjectReport);
end;

function TKSDebugProjectReport.HaveDebugTool(const ToolName: string): Boolean;
begin
  Result := SameText(ToolName, SProjectReport);
end;

initialization
  DebugProjectReport := TKSDebugProjectReport.Create;
  InstallSubSystem(DebugProjectReport);

finalization
  UnInstallSubSystem(DebugProjectReport);
  DebugProjectReport := nil;

end.
