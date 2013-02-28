unit UCMqhSetSystemDef;               
                     
interface                     
                     
uses                     
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                     
  KSCmdModules, WVCmdTypeInfo;                  
                     
type                     
  TdmSetSystemDef = class(TCommandModule)
  private                     
    { Private declarations }                     
  public                     
    { Public declarations }                     
  end;                     
                     
var                     
  dmSetSystemDef: TdmSetSystemDef;                     
                     
implementation                     
                     
{$R *.DFM}                     
initialization                     
dmSetSystemDef:=TdmSetSystemDef.Create(Application);                     
                     
end.                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

