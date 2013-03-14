unit UCPUWaterDef;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, WVCmdTypeInfo;

type
  TcmCPUWaterDef = class(TCommandModule)
    ctRollBack: TWVCommandTypeInfo;
    cqwaterTrans: TWVCommandTypeInfo;
    cqTradeCode: TWVCommandTypeInfo;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  cmCPUWaterDef: TcmCPUWaterDef;

implementation

{$R *.DFM}
initialization        
  cmCPUWaterDef := TcmCPUWaterDef.Create(Application);                         

end.
