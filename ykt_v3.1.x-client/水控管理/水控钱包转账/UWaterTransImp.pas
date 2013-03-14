unit UWaterTransImp;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, WVCmdProc, KCWVProcBinds, Db, BDAImpEx, KCDataAccess;

type
  TcmWaterTransImp = class(TCommandModule)
    cpRollBack: TKCWVProcessor;
    cpWaterTrans: TKCWVProcessor;
    Dataset: TKCDataset;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  cmWaterTransImp: TcmWaterTransImp;

implementation

{$R *.DFM}
initialization             
 cmWaterTransImp := TcmWaterTransImp.Create(Application);             
end.
