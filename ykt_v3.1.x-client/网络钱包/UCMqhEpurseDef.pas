unit UCMqhEpurseDef;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, WVCmdTypeInfo;

type
  TdmEPurseReg = class(TCommandModule)
    cqEpurseReg: TWVCommandTypeInfo;
    WVEPurseDestory: TWVCommandTypeInfo;
    cqEPurseDestory: TWVCommandTypeInfo;
    WVEPurseIn: TWVCommandTypeInfo;
    WVEPurseOut: TWVCommandTypeInfo;
    WVFreeze: TWVCommandTypeInfo;
    WVEpurseTrans: TWVCommandTypeInfo;
    WVchangepwd: TWVCommandTypeInfo;
    WVresetpwd: TWVCommandTypeInfo;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  dmEPurseReg: TdmEPurseReg;

implementation

{$R *.DFM}
initialization                                                                                                                                                                                                   
                                                                                                                                                                                                   
  dmEPurseReg := TdmEPurseReg.Create(Application);

end.
