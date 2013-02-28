unit UCMqhDGSpecAppImp;
                          
interface                          
                          
uses                          
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                          
  KSCmdModules, Db, BDAImpEx, KCDataAccess, KCWVProcBinds, WVCmdProc;                      
                          
type                          
  TdmDGSpecAppImp = class(TCommandModule)                      
    Dataset: TKCDataset;
  private        
    { Private declarations }                          
  public                          
    { Public declarations }        
  end;                          
                          
var                          
  dmDGSpecAppImp: TdmDGSpecAppImp;
                          
implementation                          
                          
{$R *.DFM}                      
initialization        
  dmDGSpecAppImp:=TdmDGSpecAppImp.Create(Application);
                          
end.                          
                         
                        
                       
                      
                     
                    
                   
                  
                 
                
               
              
             
        
           
          
         
        
       
      
     
    
   
  
 

