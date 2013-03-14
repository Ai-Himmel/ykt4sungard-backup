unit UpublishCardDef;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, WVCmdTypeInfo;

type
  TcmPublishCardDef = class(TCommandModule)
    cqPubCardTrunk: TWVCommandTypeInfo;
    cqStuChangeCardTrunk: TWVCommandTypeInfo;
    cqRenewCardtrunk: TWVCommandTypeInfo;
    cqCardReRelease: TWVCommandTypeInfo;
    WVWaterPriceQ: TWVCommandTypeInfo;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  cmPublishCardDef: TcmPublishCardDef;

implementation

{$R *.DFM}
initialization        
  cmPublishCardDef := TcmPublishCardDef.Create(Application);                         

end.
