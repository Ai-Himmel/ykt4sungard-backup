unit UCMqhSysSetDef;
                                                                                                                                                                                                   
interface                                                                                                                                                                                                   
                                                                                                                                                                                                   
uses                                                                                                                                                                                                   
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                                                                                                                                                                                                   
  KSCMDMODULES, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds;
                                                                                                                                                                                                   
type                                                                                                                                                                                                   
  TdmSysSetDef = class(TCommandModule)                                                                                                                                                                                         
    cqSetDict: TWVCommandTypeInfo;                                                                                                                                                                                    
    cpSetDict: TWVCommandTypeInfo;                                                                                                                                                                                   
    cqSetStation: TWVCommandTypeInfo;  
    cpSetStation: TWVCommandTypeInfo;                                                                                                                                          
    cpResetOperPwd: TWVCommandTypeInfo;                                                                                                                                        
    cqSetOperator: TWVCommandTypeInfo;                                                                                                                                      
    cpSetOperator: TWVCommandTypeInfo;                                                                                                                                     
    cqSetModuleAuth: TWVCommandTypeInfo;                                                                                                                                   
    cpSetModuleAuth: TWVCommandTypeInfo;                                      
    cqSetOperStation: TWVCommandTypeInfo;                                 
    cpSetOperStation: TWVCommandTypeInfo;
    cpUpdOperPwd: TWVCommandTypeInfo;
    cqSetSaveOper: TWVCommandTypeInfo;
    cqQOperCardBind: TWVCommandTypeInfo;
    cqOperCardBind: TWVCommandTypeInfo;
    cqCardInfoQuery: TWVCommandTypeInfo;
  private                                                                                                                                                                                                   
    { Private declarations }                                                                                                                                                                                                   
  public                                                                                                                                                                                                   
    { Public declarations }                                                                                                                                                                                                   
  end;                                                                                                                                                                                                   
                                                                                                                                                                                                   
var                                                                                                                                                                                                   
  dmSysSetDef: TdmSysSetDef;                                                                                                                                                                                                   
                                                                                                                                                                                                   
implementation                                                                                                                                                                                                   
                                                                                                                                                                                                   
{$R *.DFM}                                                                                                                                                                                                   
                                                                                                                                                                                                   
initialization                                                                                                                                                                                                   
                                                                                                                                                                                                   
  dmSysSetDef := TdmSysSetDef.Create(Application);                                                                                                                                                                                                   
                                                                                                                                                                                                   
end.                                                                                                                                                                                                   
                                                                                                                                                                                                  
                                                                                                                                                                                                 
                                                                                                                                                                                                
                                                                                                                                                                                               
                                                                                                                                                                                              
                                                                                                                                                                                             
                                                                                                                                                                                            
                                                                                                                                                                                           
                                                                                                                                                                                          
                                                                                                                                                                                         
                                                                                                                                                                                        
                                                                                                                                                                                       
                                                                                                                                                                                      
                                                                                                                                                                                     
                                                                                                                                                                                    
                                                                                                                                                                                   
                                                                                                                                                                                  
                                                                                                                                                                                 
                                                                                                                                                                                
                                                                                                                                                                               
                                                                                                                                                                              
                                                                                                                                                                             
                                                                                                                                                                            
                                                                                                                                                                           
                                                                                                                                                                          
                                                                                                                                                                         
                                                                                                                                                                        
                                                                                                                                                                       
                                                                                                                                                                      
                                                                                                                                                                     
                                                                                                                                                                    
                                                                                                                                                                   
                                                                                                                                                                  
                                                                                                                                                                 
                                                                                                                                                                
                                                                                                                                                               
                                                                                                                                                              
                                                                                                                                                             
                                                                                                                                                            
                                                                                                                                                           
                                                                                                                                                          
                                                                                                                                                         
                                                                                                                                                        
                                                                                                                                                       
                                                                                                                                                      
                                                                                                                                                     
                                                                                                                                                    
                                                                                                                                                   
                                                                                                                                                  
                                                                                                                                                 
                                                                                                                                                
                                                                                                                                               
                                                                                                                                              
                                                                                                                                             
                                                                                                                                            
                                                                                                                                           
                                                                                                                                          
                                                                                                                                         
                                                                                                                                        
                                                                                                                                       
                                                                                                                                      
                                                                                                                                     
                                                                                                                                    
                                                                                                                                   
                                                                                                                                  
                                                                                                                                 
                                                                                                                                
                                                                                                                               
                                                                                                                              
                                                                                                                             
                                                                                                                            
                                                                                                                           
                                                                                                                          
                                                                                                                         
                                                                                                                        
                                                                                                                       
                                                                                                                      
                                                                                                                     
                                                                                                                    
                                                                                                                   
                                                                                                                  
                                                                                                                 
                                                                                                                
                                                                                                               
                                                                                                              
                                                                                                             
                                                                                                            
                                                                                                           
                                                                                                          
                                                                                                         
                                                                                                        
                                                                                                       
                                                                                                      
                                                                                                     
                                                                                                    
                                                                                                   
                                                                                                  
                                                                                                 
                                                                                                
                                                                                               
                                                                                              
                                                                                             
                                                                                            
                                                                                           
                                                                                          
                                                                                         
                                                                                        
                                                                                       
                                                                                      
                                                                                     
                                                                                    
                                                                                   
                                                                                  
                                                                                 
                                                                                
                                                                               
                                                                              
                                                                             
                                                                            
                                                                           
                                                                          
                                                                         
                                                                        
                                                                       
                                                                      
                                                                     
                                                                    
                                                                   
                                                                  
                                                                 
                                                                
                                                               
                                                              
                                                             
                                                            
                                                           
                                                          
                                                         
                                                        
                                                       
                                                      
                                                     
                                                    
                                                   
                                                  
                                                 
                                                
                                               
                                              
                                             
                                            
                                           
                                          
                                         
                                        
                                       
                                      
                                     
                                    
                                   
                                  
                                 
                                
                               
                              
                             
                            
                           
                          
                         
                        
                       
                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

