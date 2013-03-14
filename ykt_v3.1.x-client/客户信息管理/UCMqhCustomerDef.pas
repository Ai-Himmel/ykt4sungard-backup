unit UCMqhCustomerDef;
        
interface        
        
uses        
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,        
  KSCmdModules, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds;        
        
type        
  TdmCustomerDef = class(TCommandModule)     
    cqQueryCustomer: TWVCommandTypeInfo;     
    WVsetCustInfo: TWVCommandTypeInfo;     
    cqQueryCustomerKind: TWVCommandTypeInfo;     
    cpSetCustomerKindInfo: TWVCommandTypeInfo;   
    cpImportCustomerInfo: TWVCommandTypeInfo;     
    cpShImportCustomerInfo: TWVCommandTypeInfo;     
    cqimpCustOper: TWVCommandTypeInfo;    
    cpimpCustOper: TWVCommandTypeInfo;   
    WVCImportBankCard: TWVCommandTypeInfo;   
    WVCIMPBankCardManger: TWVCommandTypeInfo;   
    WVCIMPBankCardQuery: TWVCommandTypeInfo;   
    cqPatchDel: TWVCommandTypeInfo;   
    cqcustPatchDel: TWVCommandTypeInfo;   
    cqPhotoQuery: TWVCommandTypeInfo;   
    cqBatchEditStuNo: TWVCommandTypeInfo;   
    cqImpNewStu: TWVCommandTypeInfo;   
    cqImpNewStuManage: TWVCommandTypeInfo;   
    cqImpNewStuQ: TWVCommandTypeInfo;   
    cqImpBankCardLink: TWVCommandTypeInfo;   
    cqBankImpLinkQ: TWVCommandTypeInfo;   
    cqImpBankCardMangLink: TWVCommandTypeInfo;   
    cqbankPatchDel: TWVCommandTypeInfo;   
    cqLinkBinding: TWVCommandTypeInfo;   
    cqBankLinkQuery: TWVCommandTypeInfo;  
    cqBankBingdingQuery: TWVCommandTypeInfo;
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
       
      
     
    
   
  
 

