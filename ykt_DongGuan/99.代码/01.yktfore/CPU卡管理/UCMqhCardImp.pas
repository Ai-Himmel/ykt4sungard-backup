unit UCMqhCardImp;
                                
interface                                
                                
uses                                
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                                
  KSCmdModules, WVCmdProc, KCWVProcBinds, Db, BDAImpEx, KCDataAccess;                                
                                
type                                
  TdmCardImp = class(TCommandModule)            
    Dataset: TKCDataset;            
    cqMoneyIn: TKCWVProcessor;            
    cqMoneyOut: TKCWVProcessor;        
    cqRefreshCard: TKCWVProcessor;       
    cpSetMoney: TKCWVProcessor;       
    cqAccountQ: TKCWVQuery;      
    cqCardSericalQ: TKCWVQuery;  
    cqCardInfoQ: TKCWVQuery;  
    KCLoss_UN: TKCWVProcessor;  
    cqReturnMoney: TKCWVQuery; 
    KCRtnMoney: TKCWVQuery; 
    KCChangeCardA: TKCWVProcessor; 
    KCReNewApp: TKCWVProcessor; 
    KCDestoryApp: TKCWVProcessor; 
    KCRenewOper: TKCWVProcessor; 
    KCChangeCardOper: TKCWVProcessor; 
    KCDestoryOper: TKCWVProcessor; 
    cqappDeal: TKCWVQuery;
    KCCancelApp: TKCWVProcessor;
    KCMakeAnon: TKCWVProcessor;
    KCNonCardchange: TKCWVProcessor;
    KCTradeCancel: TKCWVProcessor;
    cqSetPOSInfo: TKCWVQuery;
    KCMachineConsume: TKCWVProcessor;
    KCConsumeOk: TKCWVProcessor;
    KCConsumeSerial: TKCWVQuery;
  private              
    { Private declarations }                                
  public                                
    { Public declarations }                                
  end;                                
                                
var                                
  dmCardImp: TdmCardImp;                                
                                
implementation                                
                                
{$R *.DFM}                                
initialization                     
  dmCardImp := TdmCardImp.Create(Application);                                
                                
end.                                
                               
                              
                             
                            
                           
                          
                         
                        
                       
                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

