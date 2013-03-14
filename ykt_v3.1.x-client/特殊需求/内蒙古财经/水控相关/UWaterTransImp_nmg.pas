unit UWaterTransImp_nmg;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, WVCmdProc, KCWVProcBinds, Db, BDAImpEx, KCDataAccess;

type
  TcmWaterTransImp_nmg = class(TCommandModule)
    Dataset: TKCDataset;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  cmWaterTransImp_nmg: TcmWaterTransImp_nmg;

implementation

{$R *.DFM}
initialization             
 cmWaterTransImp_nmg := TcmWaterTransImp_nmg.Create(Application);
end.
