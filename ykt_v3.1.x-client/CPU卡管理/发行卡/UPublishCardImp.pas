unit UPublishCardImp;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, Db, BDAImpEx, KCDataAccess, WVCmdProc, KCWVProcBinds,
  WVCmdTypeInfo, WorkViews, WVCmdReq;

type
  TcmPublishCardImp = class(TCommandModule)
    cppubCardTrunk: TKCWVProcessor;
    Dataset: TKCDataset;
    cpStuChangeCard: TKCWVProcessor;
    cpRenewCard: TKCWVProcessor;
    cpCardReRelease: TKCWVProcessor;
    cqQWaterPrice: TKCWVQuery;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  cmPublishCardImp: TcmPublishCardImp;
implementation

{$R *.DFM}
{ TcmPublishCardImp }
initialization
  cmPublishCardImp := TcmPublishCardImp.Create(Application);                         

end.
