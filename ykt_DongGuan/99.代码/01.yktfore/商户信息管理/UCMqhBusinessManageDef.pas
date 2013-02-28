unit UCMqhBusinessManageDef;    
                          
interface                      
                          
uses                          
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                          
  KSCmdModules, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds;        
                          
type                          
  TdmBusinessManageDef = class(TCommandModule)                         
    cqQueryBusinessByOther: TWVCommandTypeInfo;                      
    cqQueryBusinessByKey: TWVCommandTypeInfo;        
    cqsetBusiFate: TWVCommandTypeInfo;        
    cpsetBusiFate: TWVCommandTypeInfo;        
    cqfillBusiSaveMoney: TWVCommandTypeInfo;        
    cqsetFillBusiEquInfo: TWVCommandTypeInfo;        
    cpsetFillBusiEquInfo: TWVCommandTypeInfo;        
    cpsetFillBusiEquInfoDel: TWVCommandTypeInfo;        
    cqsetFillEquOperInfo: TWVCommandTypeInfo;        
    cpsetFillEquOperInfo: TWVCommandTypeInfo;        
    cpsetFillEquOperInfoEdit: TWVCommandTypeInfo;        
    cpsetFillEquOperInfoDel: TWVCommandTypeInfo;        
    cqfillOperEquBanding: TWVCommandTypeInfo;        
    cpfillOperEquBanding: TWVCommandTypeInfo;        
    cpfillOperEquBandingDel: TWVCommandTypeInfo;        
    cpSetBusinessInfo: TWVCommandTypeInfo;        
    cqSetBusiFee: TWVCommandTypeInfo;        
    cpSetBusiFee: TWVCommandTypeInfo;      
    cqBusiSubjectLink: TWVCommandTypeInfo;     
    cpBusiSubjectLink: TWVCommandTypeInfo;    
    cqSetBusiStruct: TWVCommandTypeInfo;    
    cqQBusiStruct: TWVCommandTypeInfo;    
    cqSetBusiInfo: TWVCommandTypeInfo;   
    cpSetBusiInfo: TWVCommandTypeInfo;  
    cqSetBusiDev: TWVCommandTypeInfo; 
    cpSetBusiDev: TWVCommandTypeInfo;
  private        
    { Private declarations }                          
  public        
    { Public declarations }           
  end;                          
                      
                      
                        
var                          
  dmBusinessManageDef: TdmBusinessManageDef;                      
                      
implementation                          
                          
{$R *.DFM}                      
initialization        
  dmBusinessManageDef:=TdmBusinessManageDef.Create(Application);                      
                          
end.                          
                         
                      
                       
                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

