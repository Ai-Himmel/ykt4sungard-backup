unit UCMqhCardImp;
                         
interface                         
                         
uses                         
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                         
  KSCmdModules, WVCmdProc, KCWVProcBinds, Db, BDAImpEx, KCDataAccess;                         
                         
type                         
  TdmCardImp = class(TCommandModule)     
    cpChangeCardPwd: TKCWVProcessor;     
    cqTradeBusiQuery: TKCWVQuery;     
    cqManualTrade: TKCWVProcessor;     
    cpLossCard: TKCWVProcessor;     
    cpCardDestory: TKCWVProcessor;     
    KCWPatchAccQuery: TKCWVQuery;     
    cqPatchAcc: TKCWVProcessor;     
    cpinAccountByMan: TKCWVProcessor;     
    KCWAccountByMan: TKCWVQuery;     
    KCWManualTradeQ: TKCWVQuery;     
    Dataset: TKCDataset;     
    cqPubAuthCard1: TKCWVProcessor;     
    cqauthCardOper: TKCWVQuery;     
    cqmodifyAuthCard: TKCWVQuery;     
    cqReturnCardAuth: TKCWVProcessor;     
    cqLoseAuthCard: TKCWVProcessor;     
    cqRLoseAuthCard: TKCWVProcessor;     
    KCWCardCustInfoQuery: TKCWVQuery;     
    cqFeeQuery: TKCWVProcessor;     
    cqReleaseCard: TKCWVProcessor;     
    cqRelCardOk: TKCWVProcessor;     
    cqRenewCard: TKCWVProcessor;     
    KCWCardInfoQuery: TKCWVQuery;     
    cqFreezeCard: TKCWVProcessor;     
    cqCardReRelease: TKCWVProcessor;     
    cqMoneyIn: TKCWVProcessor;     
    cqMoneyOut: TKCWVProcessor;     
    cqcashOperCancel: TKCWVProcessor;     
    KCWAccountQuery: TKCWVQuery;     
    cqcardTradeQuery: TKCWVQuery;    
    cqTradeReserse: TKCWVProcessor;    
    cqReverseOpenCard: TKCWVProcessor;    
    cqaccountTradeQuery: TKCWVQuery;   
    cqRevSaveMoney: TKCWVProcessor;   
    cqRevConsume: TKCWVProcessor;  
    cpbadCardManage: TKCWVProcessor; 
    cqRefreshCard: TKCWVProcessor; 
    cpStuChangeCard: TKCWVProcessor; 
    cqcardLibNotBalance: TKCWVQuery;
    cpCardLibBal: TKCWVProcessor;
    cpSetMoney: TKCWVProcessor;
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
                        
                       
                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

