unit UAccountMgrDef;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, WVCmdTypeInfo;

type
  TcmAccountMgrDef = class(TCommandModule)
    ctinAccountByMan: TWVCommandTypeInfo;
    cqVoucherAdd: TWVCommandTypeInfo;
    cqVoucherMgr: TWVCommandTypeInfo;
    cqVOper: TWVCommandTypeInfo;
    cqOperPermissionQ: TWVCommandTypeInfo;
    cqOperPermission: TWVCommandTypeInfo;
    cqAccountRptQ: TWVCommandTypeInfo;
    cq850061: TWVCommandTypeInfo;
    cq850062: TWVCommandTypeInfo;
    cq850063: TWVCommandTypeInfo;
    cq850065: TWVCommandTypeInfo;
    cq850070: TWVCommandTypeInfo;
    cq850071: TWVCommandTypeInfo;
    cq850072: TWVCommandTypeInfo;
    cqQSubject: TWVCommandTypeInfo;
    cqSetSubject: TWVCommandTypeInfo;
    WVBusiDtlAcc: TWVCommandTypeInfo;
    WVBusiStatAcc: TWVCommandTypeInfo;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  cmAccountMgrDef: TcmAccountMgrDef;

implementation

{$R *.DFM}
initialization        
  cmAccountMgrDef := TcmAccountMgrDef.Create(Application);

end.
