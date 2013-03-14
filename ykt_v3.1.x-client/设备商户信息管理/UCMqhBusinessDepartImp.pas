unit UCMqhBusinessDepartImp;   
                      
interface                      
                      
uses                      
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                      
  KSCmdModules, KCWVProcBinds, WVCmdProc, Db, BDAImpEx, KCDataAccess;   
                      
type                      
  TdmBusinessDepartImp = class(TCommandModule)                      
    cqQueryBusinessDepartByOther: TKCWVQuery;           
    cqQueryBusinessDepartByKey: TKCWVQuery;         
    KCDataset1: TKCDataset;   
    cqSetBusinessDepartInfo: TKCWVQuery; 
    cpSetBusinessDepartInfo: TKCWVProcessor;
  private                      
    { Private declarations }                      
  public                      
    { Public declarations }                      
  end;                      
                      
var                      
  dmBusinessDepartImp: TdmBusinessDepartImp;                      
                      
implementation                      
                      
{$R *.DFM}                      
initialization                      
  dmBusinessDepartImp:=TdmBusinessDepartImp.Create(Application);                      
                      
end.                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

