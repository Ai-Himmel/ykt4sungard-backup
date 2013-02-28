unit UCMqhCardDef;
                                
interface                                
                                
uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                                
  KSCmdModules, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds, Db, BDAImpEx,            
  KCDataAccess;            
                                
type                                
  TdmCardDef = class(TCommandModule)            
    WVMoneyIn: TWVCommandTypeInfo;            
    WVMoneyOut: TWVCommandTypeInfo;        
    WVRefreshCard: TWVCommandTypeInfo;       
    cqSetMoney: TWVCommandTypeInfo;       
    cqAccountQ: TWVCommandTypeInfo;      
    cqCardSericalQ: TWVCommandTypeInfo;  
    cqCardInfoQ: TWVCommandTypeInfo;  
    WVLoss_UN: TWVCommandTypeInfo;  
    cqReturnMoney: TWVCommandTypeInfo; 
    WVRtnMoney: TWVCommandTypeInfo; 
    WVChangeCardA: TWVCommandTypeInfo; 
    WVReNewApp: TWVCommandTypeInfo; 
    WVDestoryApp: TWVCommandTypeInfo; 
    WVReNewOper: TWVCommandTypeInfo; 
    WVChangeCardOper: TWVCommandTypeInfo; 
    WVDestoryOper: TWVCommandTypeInfo; 
    cqappDeal: TWVCommandTypeInfo;
    WVCancelApp: TWVCommandTypeInfo;
    WVMakeAnonCNo: TWVCommandTypeInfo;
    WVNonCardChange: TWVCommandTypeInfo;
    WVTradeCancel: TWVCommandTypeInfo;
    cqSetPOSInfo: TWVCommandTypeInfo;
    WVMachineConsume: TWVCommandTypeInfo;
    WVConsumeOk: TWVCommandTypeInfo;
    WVConsumeSerial: TWVCommandTypeInfo;
  private                                
    { Private declarations }                                
  public                                
    { Public declarations }                                
  end;                                
                                
var                                
  dmCardDef: TdmCardDef;                                
                                
implementation                                
                                
{$R *.DFM}                                
initialization               
  dmCardDef := TdmCardDef.Create(Application);                                
                                
end.                                
                               
                              
                             
                            
                           
                          
                         
                        
                       
                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

