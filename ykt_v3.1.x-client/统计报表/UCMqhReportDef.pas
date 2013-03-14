unit UCMqhReportDef;
                                            
interface                                            
                                            
uses                                            
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                                            
  KSCmdModules, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds;
                                            
type                                            
  TdmReportDef = class(TCommandModule)  
    cqUnsuitReport: TWVCommandTypeInfo;    
    cqTransfer: TWVCommandTypeInfo;
    cqUnEqip: TWVCommandTypeInfo;
    cqticketMoneyReport: TWVCommandTypeInfo;
    cqSetOperator: TWVCommandTypeInfo;
    WVOperGroupManager: TWVCommandTypeInfo;
    cqTotSubject: TWVCommandTypeInfo;
    cqtradeSubject: TWVCommandTypeInfo;
    WVSubBalanceRep: TWVCommandTypeInfo;
    WVSystemRunStat: TWVCommandTypeInfo;
    cqCardUsedInfo_R: TWVCommandTypeInfo;
    WVBusiReport: TWVCommandTypeInfo;
    cqTicketCashRpt_R: TWVCommandTypeInfo;
    WVBusiReportPOS: TWVCommandTypeInfo;
    WVBusiReportFC: TWVCommandTypeInfo;
    WVBusiReportDay: TWVCommandTypeInfo;
    WVBusiPayInQ: TWVCommandTypeInfo;
    WVBusiPayIn: TWVCommandTypeInfo;
    WVPayInQuery: TWVCommandTypeInfo;
    cqBusiGatherRep: TWVCommandTypeInfo;
    cqSubject: TWVCommandTypeInfo;
    cqCardUsedInfo: TWVCommandTypeInfo;
    cqTicketCashRpt: TWVCommandTypeInfo;
    cqBusiStatFC: TWVCommandTypeInfo;
    cqBusiRunStatRpt: TWVCommandTypeInfo;
    cqQueryBusinessByKey: TWVCommandTypeInfo;
    cqOperRpt: TWVCommandTypeInfo;
    cqBusiFeeRpt: TWVCommandTypeInfo;
    cqCardDestoryRpt: TWVCommandTypeInfo;
    cqSysAccount: TWVCommandTypeInfo;
    cqSysAccQuery: TWVCommandTypeInfo;
    cqOperCashTot: TWVCommandTypeInfo;
    WVDealBankAccQ: TWVCommandTypeInfo;
    WVDealBankAcc: TWVCommandTypeInfo;
    WVDealBankAccDtlQ: TWVCommandTypeInfo;
    WVDealBankAccDtl: TWVCommandTypeInfo;
    WVBalanceRpt: TWVCommandTypeInfo;
    WVBusiPayIn_nju: TWVCommandTypeInfo;
    WVbusiPayIn_njuE: TWVCommandTypeInfo;
    WVbusipayinQ_nju: TWVCommandTypeInfo;
  private                                            
    { Private declarations }                                            
  public                                            
    { Public declarations }                                            
  end;                                            
                                            
var                                            
  dmReportDef: TdmReportDef;                                
                                            
implementation                                            
                                            
{$R *.DFM}                                
initialization  
dmReportDef:=TdmReportDef.Create(Application);                                
                                            
end.
