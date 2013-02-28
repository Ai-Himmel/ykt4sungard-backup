unit UCMqhDGSpecAppDef;
                          
interface                      
                          
uses                          
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                          
  KSCmdModules, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds;        
                          
type                          
  TdmDGSpecAppDef = class(TCommandModule)
  private        
    { Private declarations }                          
  public        
    { Public declarations }           
  end;                          
                      
                      
                        
var                          
  dmDGSpecAppDef: TdmDGSpecAppDef;
                      
implementation                          
                          
{$R *.DFM}                      
initialization        
  dmDGSpecAppDef:=TdmDGSpecAppDef.Create(Application);
                          
end.                          
                         
                      
                       
                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

