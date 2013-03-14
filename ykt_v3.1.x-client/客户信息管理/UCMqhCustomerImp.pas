unit UCMqhCustomerImp;   
        
interface        
     
uses        
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,        
  KSCmdModules, Db, BDAImpEx, KCDataAccess, KCWVProcBinds, WVCmdProc,     
  WVCmdTypeInfo;     
        
type        
  TdmCustomerImp = class(TCommandModule)        
    Dataset: TKCDataset;     
    cqQueryCustomer: TKCWVQuery;     
    cqsetCustInfo: TKCWVProcessor;   
    kcQryCustKind: TKCWVQuery;   
    cpSetCustKindInfo: TKCWVProcessor;   
    cpImpCustInfo: TKCWVProcessor;   
    cpSHlImpCustInfo: TKCWVProcessor;   
    cqimpCustOper: TKCWVQuery;    
    cpimpCustOper: TKCWVProcessor;   
    cpImpBankCard: TKCWVProcessor;   
    cpBankCardManger: TKCWVProcessor;   
    KCWVQuery1: TKCWVQuery;   
    cpPatchdel: TKCWVProcessor;   
    cpCustPatchDel: TKCWVProcessor;   
    cpPhotoQuery: TKCWVProcessor;   
    cpBatchEditStuNo: TKCWVProcessor;   
    cpImpNewstu: TKCWVProcessor;   
    cpImpNewStuManage: TKCWVProcessor;   
    kcImpNewStuQ: TKCWVQuery;   
    cpImpBankCardLink: TKCWVProcessor;   
    kcImpBankCardLinkQ: TKCWVQuery;   
    cpImpBankMangLink: TKCWVProcessor;   
    cpPatchDelLink: TKCWVProcessor;   
    cpLinkBinding: TKCWVProcessor;   
    cqBankLinkQuery: TKCWVQuery;  
    cqBankBingdingQuery: TKCWVQuery;
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
        
       
      
     
    
   
  
 

