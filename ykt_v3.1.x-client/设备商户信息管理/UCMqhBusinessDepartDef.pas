unit UCMqhBusinessDepartDef;                      
                      
interface                      
                      
uses                      
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                      
  KSCmdModules, WVCmdTypeInfo;                  
                      
type                      
  TdmBusinessDepartDef = class(TCommandModule)                      
    cqQueryBusinessDepartByOther: TWVCommandTypeInfo;           
    cqQueryBusinessDepartByKey: TWVCommandTypeInfo;         
    cqSetBusinessDepartInfo: TWVCommandTypeInfo; 
    cpSetBusinessDepartInfo: TWVCommandTypeInfo;
  private                      
    { Private declarations }                      
  public                      
    { Public declarations }                      
  end;                      
                      
var                      
  dmBusinessDepartDef: TdmBusinessDepartDef;                      
                      
implementation                      
                      
{$R *.DFM}                      
initialization                      
  dmBusinessDepartDef:=TdmBusinessDepartDef.Create(Application);                      
                      
end.                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

