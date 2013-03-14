unit UCMPubCardImp_nmg;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, WVCmdProc, KCWVProcBinds, Db, BDAImpEx, KCDataAccess;

type
  TcmPubCardImp_nmg = class(TCommandModule)
    cpPubCard_nmg: TKCWVProcessor;
    Dataset: TKCDataset;
    cqcashOperCancel: TKCWVProcessor;
    cpSetSmlMoney: TKCWVProcessor;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  cmPubCardImp_nmg: TcmPubCardImp_nmg;

implementation

{$R *.DFM}
initialization        
  cmPubCardImp_nmg := TcmPubCardImp_nmg.Create(Application);

end.
