unit UWaterTransDef_nmg;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, WVCmdTypeInfo;

type
  TcmWaterTransDef_nmg = class(TCommandModule)
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  cmWaterTransDef_nmg: TcmWaterTransDef_nmg;

implementation

{$R *.DFM}
initialization             
 cmWaterTransDef_nmg := TcmWaterTransDef_nmg.Create(Application);

end.
