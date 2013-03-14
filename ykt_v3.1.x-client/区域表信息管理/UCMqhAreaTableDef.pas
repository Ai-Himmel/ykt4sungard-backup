unit UCMqhAreaTableDef;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, WVCmdTypeInfo;

type
  TdmAreaTableDef = class(TCommandModule)
    cqQueryAreaTable: TWVCommandTypeInfo;
    cpAddAreaTableInfo: TWVCommandTypeInfo;
    cpChangeAreaTableInfo: TWVCommandTypeInfo;
    cpDelAreaTableInfo: TWVCommandTypeInfo;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  dmAreaTableDef: TdmAreaTableDef;

implementation

{$R *.DFM}
initialization
  dmAreaTableDef:=TdmAreaTableDef.Create(Application);

end.
