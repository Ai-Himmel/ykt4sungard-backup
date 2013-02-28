unit UCMqhCustomerDef;  
                 
interface                 
                 
uses                 
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                 
  KSCmdModules, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds;                 
                 
type                 
  TdmCustomerDef = class(TCommandModule)      
    cpSetCustInfo: TWVCommandTypeInfo;     
    cqSetCustInfo: TWVCommandTypeInfo;     
    cqCustPay: TWVCommandTypeInfo;    
    WVMakeCardCQ: TWVCommandTypeInfo;    
    WVMakeCardCheck: TWVCommandTypeInfo;    
    WVFeeQuery: TWVCommandTypeInfo;    
    cqExpMakeCardList: TWVCommandTypeInfo;   
    WVFeePay: TWVCommandTypeInfo;   
    WVSavePhoto: TWVCommandTypeInfo;   
    WVImpCardInfo: TWVCommandTypeInfo;   
    WVtwoCheckQ: TWVCommandTypeInfo;   
    WVTwoCheck: TWVCommandTypeInfo;   
    WVMakeCard2Q: TWVCommandTypeInfo;   
    WVImpPhoneNo: TWVCommandTypeInfo;   
    cqSetPhoneNo: TWVCommandTypeInfo;  
    WVSet: TWVCommandTypeInfo;
  private                 
    { Private declarations }                 
  public                 
    { Public declarations }                 
  end;                 
                 
var                 
  dmCustomerDef: TdmCustomerDef;                 
                 
implementation                 
                 
{$R *.DFM}                 
initialization                 
  dmCustomerDef := TdmCustomerDef.Create(Application);                 
                 
end.                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

