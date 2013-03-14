unit UCPUCardImp;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, Db, BDAImpEx, KCDataAccess, WVCmdProc, KCWVProcBinds;

type
  TcmCPUCardImp = class(TCommandModule)
    cppubCardcqcsgl: TKCWVProcessor;
    Dataset: TKCDataset;
    cpStuChangeCard: TKCWVProcessor;
    cpRenewCard: TKCWVProcessor;
    cpCardReRelease: TKCWVProcessor;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  cmCPUCardImp: TcmCPUCardImp;

implementation

{$R *.DFM}
initialization        
  cmCPUCardImp := TcmCPUCardImp.Create(Application);                         

end.
