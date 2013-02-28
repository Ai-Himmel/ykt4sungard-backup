unit UAccountMgrImp;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, Db, BDAImpEx, KCDataAccess, WVCmdProc, KCWVProcBinds,
  ZConnection, ZAbstractRODataset, ZAbstractDataset, ZAbstractTable,
  ZDataset,NativeXml;

type
  TcmAccountMgrImp = class(TCommandModule)
    Dataset: TKCDataset;
    conFB: TZConnection;
    KCWAccountByMan: TKCWVQuery;
    kcVoucherAdd: TKCWVQuery;
    cqVoucherMgr: TKCWVQuery;
    kcVOper: TKCWVQuery;
    kcOperPermissionQ: TKCWVQuery;
    kcOperPermission: TKCWVQuery;
    kcAccountRptQ: TKCWVQuery;
    kc850061: TKCWVQuery;
    kc850062: TKCWVQuery;
    kc850063: TKCWVQuery;
    kc850065: TKCWVQuery;
    kc850070: TKCWVQuery;
    kc850071: TKCWVQuery;
    kc850072: TKCWVQuery;
    kcQSubject: TKCWVQuery;
    cpSetSubject: TKCWVProcessor;
    KCBusiDtlAcc: TKCWVQuery;
    KCBusiStatAcc: TKCWVQuery;
  private
    { Private declarations }
  public
    { Public declarations }
    procedure Init; override;
  end;

var
  cmAccountMgrImp: TcmAccountMgrImp;

implementation
uses KSClientConsts;
{$R *.DFM}
{ TcmAccountMgrImp }

procedure TcmAccountMgrImp.Init;
var
  dbPath:string;
begin
  inherited;
  dbPath := ExtractFilePath(Application.ExeName);
  if conFB.Connected then
    conFB.Connected := False;
  conFB.Database := sdAnsiToUtf8(dbPath+'\YKTFINAN.db3');
  try
    conFB.Connected;
  except
    on e:Exception do
      ShowMessage(e.Message);
  end;
end;

initialization
  cmAccountMgrImp := TcmAccountMgrImp.Create(Application);

end.
