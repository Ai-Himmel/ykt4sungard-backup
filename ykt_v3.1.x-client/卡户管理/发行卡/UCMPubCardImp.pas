unit UCMPubCardImp;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, WVCmdProc, KCWVProcBinds, Db, BDAImpEx, KCDataAccess;

type
  TcmPubCardImp = class(TCommandModule)
    cpPubCard_trunk: TKCWVProcessor;
    Dataset: TKCDataset;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  cmPubCardImp: TcmPubCardImp;

implementation

{$R *.DFM}
initialization        
  cmPubCardImp := TcmPubCardImp.Create(Application);                         

end.
