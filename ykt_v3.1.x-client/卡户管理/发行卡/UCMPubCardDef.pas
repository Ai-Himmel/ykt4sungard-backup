unit UCMPubCardDef;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, WVCmdTypeInfo;

type
  TcmPubCardDef = class(TCommandModule)
    cqPubCard_trunk: TWVCommandTypeInfo;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  cmPubCardDef: TcmPubCardDef;

implementation

{$R *.DFM}
initialization        
  cmPubCardDef := TcmPubCardDef.Create(Application);

end.
