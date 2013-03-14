unit UCMPubCardDef_nmg;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, WVCmdTypeInfo;

type
  TcmPubCardDef_nmg = class(TCommandModule)
    cqPubCard_nmg: TWVCommandTypeInfo;
    WVcashOperCancel: TWVCommandTypeInfo;
    cqSetSmlMoney: TWVCommandTypeInfo;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  cmPubCardDef_nmg: TcmPubCardDef_nmg;

implementation

{$R *.DFM}
initialization        
  cmPubCardDef_nmg := TcmPubCardDef_nmg.Create(Application);

end.
