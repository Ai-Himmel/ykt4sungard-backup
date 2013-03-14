unit UCMqhBusinessManageImp;
                      
interface                      
                      
uses                      
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                      
  KSCmdModules, Db, BDAImpEx, KCDataAccess, KCWVProcBinds, WVCmdProc;                  
                      
type                      
  TdmBusinessManageImp = class(TCommandModule)                     
    cqQueryBusinessByOther: TKCWVQuery;                  
    Dataset: TKCDataset;    
    cqQueryBusinessByKey: TKCWVQuery;    
    cqsetBusiFate: TKCWVQuery;    
    cpsetBusiFate: TKCWVProcessor;    
    cqfillBusiSaveMoney: TKCWVProcessor;    
    cqsetFillBusiEquInfo: TKCWVQuery;    
    cpsetFillBusiEquInfo: TKCWVProcessor;    
    cpsetFillBusiEquInfoDel: TKCWVProcessor;    
    cqsetFillEquOperInfo: TKCWVQuery;    
    cpsetFillEquOperInfo: TKCWVProcessor;    
    cpsetFillEquOperInfoEdit: TKCWVProcessor;    
    cpsetFillEquOperInfoDel: TKCWVProcessor;    
    cqfillOperEquBanding: TKCWVQuery;    
    cpfillOperEquBanding: TKCWVProcessor;    
    cpfillOperEquBandingDel: TKCWVProcessor;    
    cpSetBusinessInfo: TKCWVProcessor;    
    cqSetBusiFee: TKCWVQuery;    
    cpBusiFee: TKCWVProcessor;  
    cqBusiSubjectLink: TKCWVQuery; 
    cpBusiSubjectLink: TKCWVProcessor;
    kcQBusiStruct: TKCWVQuery;
    cpSetBusiStruct: TKCWVProcessor;
  private    
    { Private declarations }                      
  public                      
    { Public declarations }    
  end;                      
                      
var                      
  dmBusinessManageImp: TdmBusinessManageImp;                  
                      
implementation                      
                      
{$R *.DFM}                  
initialization    
  dmBusinessManageImp:=TdmBusinessManageImp.Create(Application);                  
                      
end.                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
    
       
      
     
    
   
  
 

