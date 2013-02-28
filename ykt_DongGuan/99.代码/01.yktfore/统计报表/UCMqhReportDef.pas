unit UCMqhReportDef;
                                            
interface                                            
                                            
uses                                            
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                                            
  KSCmdModules, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds;
                                            
type                                            
  TdmReportDef = class(TCommandModule)
    cqSetOperator: TWVCommandTypeInfo;
    cqTotSubject: TWVCommandTypeInfo;
    cqtradeSubject: TWVCommandTypeInfo;
    WVSubBalanceRep: TWVCommandTypeInfo;
    WVBusiReport: TWVCommandTypeInfo;
    cqTicketCashRpt_R: TWVCommandTypeInfo;
    WVBusiReportDay: TWVCommandTypeInfo;
    cqBusiGatherRep: TWVCommandTypeInfo;
    cqSubject: TWVCommandTypeInfo;
    cqTicketCashRpt: TWVCommandTypeInfo;
    cqBusiRunStatRpt: TWVCommandTypeInfo;
    cqOperRpt: TWVCommandTypeInfo;
    cqOperCashTot: TWVCommandTypeInfo;
    cqSetBusiInfo: TWVCommandTypeInfo;
    WVAtmRpt: TWVCommandTypeInfo;
    WVReFillTermRtp: TWVCommandTypeInfo;
    WVExpendRpt: TWVCommandTypeInfo;
    WVPkgFileRpt: TWVCommandTypeInfo;
    WVTradeStat: TWVCommandTypeInfo;
    WVPersonStat: TWVCommandTypeInfo;
    WVPubCardStat: TWVCommandTypeInfo;
    WVBusiBalQ: TWVCommandTypeInfo;
    WVPatchPay: TWVCommandTypeInfo;
    cqPayFileQ: TWVCommandTypeInfo;
    cqPayDetailQ: TWVCommandTypeInfo;
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
