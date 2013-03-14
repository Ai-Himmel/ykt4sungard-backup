unit UCMqhEpurseImp;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, WVCmdProc, KCWVProcBinds, Db, BDAImpEx, KCDataAccess;

type
  TdmEpurseRegImp = class(TCommandModule)
    Dataset: TKCDataset;
    cqEpurseReg: TKCWVProcessor;
    KCWEPurseDestory: TKCWVQuery;
    cqEPurseDestory: TKCWVProcessor;
    cqEPurseIn: TKCWVProcessor;
    cqEPurseOut1: TKCWVProcessor;
    cqFreeze: TKCWVProcessor;
    cqEPurseTrans: TKCWVProcessor;
    cqchangepwd: TKCWVProcessor;
    cqresetpwd: TKCWVProcessor;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  dmEpurseRegImp: TdmEpurseRegImp;

implementation

{$R *.DFM}
initialization                                                                                                                                                                                                   

  dmEpurseRegImp := TdmEpurseRegImp.Create(Application);

end.
