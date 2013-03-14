unit UCMqhAreaTableImp;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, Db, BDAImpEx, KCDataAccess, KCWVProcBinds, WVCmdProc;

type
  TdmAreaTableImp = class(TCommandModule)
    cqQueryAreaTableByKey: TKCWVQuery;
    cpAddAreaTableInfo: TKCWVProcessor;
    cpChangeAreaTableInfo: TKCWVProcessor;
    cpDelAreaTableInfo: TKCWVProcessor;
    Dataset: TKCDataset;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  dmAreaTableImp: TdmAreaTableImp;

implementation

{$R *.DFM}
initialization
  dmAreaTableImp:=TdmAreaTableImp.Create(Application);

end.
