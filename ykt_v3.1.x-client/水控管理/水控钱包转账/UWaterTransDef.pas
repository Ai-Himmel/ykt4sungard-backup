unit UWaterTransDef;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, WVCmdTypeInfo;

type
  TcmWaterTransDef = class(TCommandModule)
    cqwaterTrans: TWVCommandTypeInfo;
    ctRollBack: TWVCommandTypeInfo;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  cmWaterTransDef: TcmWaterTransDef;

implementation

{$R *.DFM}
initialization             
 cmWaterTransDef := TcmWaterTransDef.Create(Application);             

end.
