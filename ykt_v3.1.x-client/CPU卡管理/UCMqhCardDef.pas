unit UCMqhCardDef;
                         
interface                         
                         
uses                         
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                         
  KSCmdModules, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds, Db, BDAImpEx,     
  KCDataAccess;     
                         
type                         
  TdmCardDef = class(TCommandModule)                         
    ctLossCard: TWVCommandTypeInfo;                         
    ctChangeCardPwd: TWVCommandTypeInfo;     
    WVMoneyIn: TWVCommandTypeInfo;                         
    ctTradeBusiInfo: TWVCommandTypeInfo;     
    cqManualTradeQ: TWVCommandTypeInfo;     
    cpManualTrade: TWVCommandTypeInfo;     
    ctCardDestory: TWVCommandTypeInfo;           
    cqPatchAccount: TWVCommandTypeInfo;     
    cqPatchAccQuery: TWVCommandTypeInfo;     
    cqinAccountByMan: TWVCommandTypeInfo;     
    ctinAccountByMan: TWVCommandTypeInfo;     
    cpPubAuthCard: TWVCommandTypeInfo;     
    cpauthCardOper: TWVCommandTypeInfo;     
    cpmodifyAuthCard: TWVCommandTypeInfo;     
    cpReturnAuthCard: TWVCommandTypeInfo;     
    cpLoseAuthCard: TWVCommandTypeInfo;     
    cpRLoseAuthCard: TWVCommandTypeInfo;     
    WVCardCustInfoQuery: TWVCommandTypeInfo;     
    WVFeeQuery: TWVCommandTypeInfo;     
    WVRelCardOk: TWVCommandTypeInfo;     
    WVCardInfoQuery: TWVCommandTypeInfo;     
    ctFreezeCard: TWVCommandTypeInfo;     
    WVMoneyOut: TWVCommandTypeInfo;     
    WVcashOperCancel: TWVCommandTypeInfo;     
    WVAccountQuery: TWVCommandTypeInfo;     
    cqcardTradeQuery: TWVCommandTypeInfo;    
    WVTradeReserse: TWVCommandTypeInfo;    
    WVReverseOpenCard: TWVCommandTypeInfo;    
    cqaccountTradeQuery: TWVCommandTypeInfo;   
    WVRevSaveMoney: TWVCommandTypeInfo;   
    WVRevConsume: TWVCommandTypeInfo;  
    cpbadCardManage: TWVCommandTypeInfo; 
    WVRefreshCard: TWVCommandTypeInfo; 
    cqcardLibNotBalance: TWVCommandTypeInfo;
    cqcqcardLibNotBal: TWVCommandTypeInfo;
    cqPubPASMCard: TWVCommandTypeInfo;
    cqPASMEdit: TWVCommandTypeInfo;
    cqPASMDel: TWVCommandTypeInfo;
    cqPASMQuery: TWVCommandTypeInfo;
    cqSetMoney: TWVCommandTypeInfo;
    cqCollSerial_CPU: TWVCommandTypeInfo;
    cqsmlPacket: TWVCommandTypeInfo;
    cqReturnSml: TWVCommandTypeInfo;
    cqFeeCardLock: TWVCommandTypeInfo;
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
                        
                       
                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

