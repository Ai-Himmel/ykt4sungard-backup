unit UCMqhCustomerImp;  
                 
interface                 
              
uses                 
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                 
  KSCmdModules, Db, BDAImpEx, KCDataAccess, KCWVProcBinds, WVCmdProc,              
  WVCmdTypeInfo;              
                 
type                 
  TdmCustomerImp = class(TCommandModule)                 
    Dataset: TKCDataset;       
    cqSetCustInfo: TKCWVQuery;      
    cpSetCustInfo: TKCWVProcessor;     
    cqCustPay: TKCWVQuery;    
    KCMakeCardCQ: TKCWVQuery;    
    KCMakeCardCheck: TKCWVQuery;    
    KCFeeQuery: TKCWVQuery;    
    cqExpMakeCardList: TKCWVQuery;   
    KCFeePay: TKCWVQuery;   
    KCSavePhoto: TKCWVQuery;   
    KCImpCardInfo: TKCWVQuery;   
    KCTwoCheckQ: TKCWVQuery;   
    KCTwoCheck: TKCWVQuery;   
    KCMakeCard2Q: TKCWVQuery;   
    KCImpPhoneNo: TKCWVQuery;   
    cqSetPhoneNo: TKCWVQuery;  
    KCSet: TKCWVQuery;
  private                 
    { Private declarations }                 
  public                 
    { Public declarations }                 
  end;                 
                 
var                 
  dmCustomerImp: TdmCustomerImp;                 
                 
implementation                 
                 
{$R *.DFM}                 
initialization                 
  dmCustomerImp := TdmCustomerImp.Create(Application);                 
                 
                 
end.                 
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

