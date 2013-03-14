unit UCMqhDayClearAccImp;
    
interface    
    
uses    
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,    
  KSCmdModules, WVCmdProc, KCWVProcBinds, Db, BDAImpEx, KCDataAccess;
    
type    
  TdmDayClearAccImp = class(TCommandModule)    
    cqDayAccount: TKCWVQuery;  
    cqconsumeBalance: TKCWVQuery; 
    cqreConsumeBalance: TKCWVQuery;
    Dataset: TKCDataset;
    cpfillTrans: TKCWVProcessor;
    cqTradeLogDetailed: TKCWVQuery;
    cpfillReTrans: TKCWVProcessor;
  private    
    { Private declarations }    
  public    
    { Public declarations }    
  end;    
    
var    
  dmDayClearAccImp: TdmDayClearAccImp;    
    
implementation    
    
{$R *.DFM}    
initialization    
  dmDayClearAccImp:=TdmDayClearAccImp.Create(Application);    
    
end.    
   
  
 

