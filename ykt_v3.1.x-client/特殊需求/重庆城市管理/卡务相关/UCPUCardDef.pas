unit UCPUCardDef;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, WVCmdTypeInfo;

type
  TcmCPUCarddef = class(TCommandModule)
    cqPubCard_cqcsgl: TWVCommandTypeInfo;
    cqChangeCardcqcsgl: TWVCommandTypeInfo;
    cqRenewCard: TWVCommandTypeInfo;
    cqCardReRelease: TWVCommandTypeInfo;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  cmCPUCarddef: TcmCPUCarddef;

implementation

{$R *.DFM}
initialization        
  cmCPUCarddef := TcmCPUCarddef.Create(Application);                         

end.
