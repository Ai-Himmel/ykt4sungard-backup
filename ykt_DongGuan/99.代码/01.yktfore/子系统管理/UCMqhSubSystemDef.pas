unit UCMqhSubSystemDef;
                                                                  
interface                                                                  
                                                                  
uses                                                                  
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                                                                  
  KSCmdModules, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds;             
                                                                  
type                                                                  
  TdmSubSystemDef = class(TCommandModule)   
    cqSetPOSInfo: TWVCommandTypeInfo;  
    cpSetPOSInfo: TWVCommandTypeInfo; 
    cqDevRepair: TWVCommandTypeInfo;
    WVDevBusiBind: TWVCommandTypeInfo;
    WVDevBusiQ: TWVCommandTypeInfo;
    cqSetBusiInfo: TWVCommandTypeInfo;
  private                                                                  
    { Private declarations }                                                                  
  public                                                                  
    { Public declarations }                              
  end;                                 
                              
var                                 
  dmSubSystemDef: TdmSubSystemDef;                                    
                                                                  
implementation                                    
                                                                  
{$R *.DFM}                                                                  
                                                          
initialization                                                          
  dmSubSystemDef:=TdmSubSystemDef.Create(Application);                                                          
                                                          
end.                                                                  
                                                                 
                                                                
                                                               
                                                              
                                                             
                                                            
                                                           
                                                          
                                                         
                                                        
                                                       
                                                      
                                                     
                                                    
                                                   
                                                  
                                                 
                                                
                                               
                                              
                                             
                                            
                                           
                                          
                                         
                                        
                                       
                                      
                                     
                                    
                                   
                                  
                                 
                                
                               
                              
                             
                            
                           
                          
                         
                        
                       
                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

