unit UCPUWaterImp;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSCmdModules, Db, BDAImpEx, KCDataAccess, WVCmdProc, KCWVProcBinds;

type
  TcmCPUWaterImp = class(TCommandModule)
    cpRollBack: TKCWVProcessor;
    cpWaterTrans: TKCWVProcessor;
    Dataset: TKCDataset;
    cpTradeCode: TKCWVProcessor;
    cqQueryGlobeParaByKey: TKCWVQuery;
    cpSaveFeeType: TKCWVProcessor;
    kcFeeTypeQ: TKCWVQuery;
    kcFeeTypeDel: TKCWVQuery;
    kcSmlTradeSerial: TKCWVQuery;
    KCsmlSerialRcv: TKCWVQuery;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  cmCPUWaterImp: TcmCPUWaterImp;

implementation

{$R *.DFM}
initialization        
  cmCPUWaterImp := TcmCPUWaterImp.Create(Application);                         

end.
