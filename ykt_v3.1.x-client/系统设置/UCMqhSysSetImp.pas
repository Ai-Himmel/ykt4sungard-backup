unit UCMqhSysSetImp;
                                                                                                                                                                                                   
interface                                                                                                                                                                                                   
                                                                                                                                                                                                   
uses                                                                                                                                                                                                   
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                                                                                                                                                                                                   
  KSCMDMODULES, Db, BDAImpEx, KCDataAccess, KCWVProcBinds, WVCmdProc;                                                                                                                                                       

type                                                                                                                                                                                                   
  TdmSysSetImp = class(TCommandModule)                                                                                                                                                                                                   
    DataSet: TKCDataset;                                                                                                                                                                                         
    cqSetDict: TKCWVQuery;                                                                                                                                                                                    
    cpSetDict: TKCWVProcessor;                                                                                                                                                                                   
    cqSetStation: TKCWVQuery;                                                                                                                                                     
    cpSetStation: TKCWVProcessor;                                                                                                                                                    
    cpUpdOperPwd: TKCWVProcessor;                                                                                                                                        
    cqSetOperator: TKCWVQuery;                                                                                                                                      
    cpSetOperator: TKCWVProcessor;                                                                                                                                     
    cqSetModuleAuth: TKCWVQuery;                                                                                                                                   
    cpSetModuleAuth: TKCWVProcessor;                                      
    cqSetOperStation: TKCWVQuery;                                 
    cpSetOperStation: TKCWVProcessor;
    cpResetOperPwd: TKCWVProcessor;
    cpSetSaveOper: TKCWVProcessor;
    cpOperCardBind: TKCWVProcessor;
    kcQOperCardBind: TKCWVQuery;
    kcCardInfoQuery: TKCWVQuery;
  private                                                                                                                                                                                                   
    { Private declarations }                                                                                                                                                                                                   
  public                                                                                                                                                                                                   
    { Public declarations }                                                                                                                                                                                                   
  end;                                                                                                                                                                                                   

var                                                                                                                                                                                                   
  dmSysSetImp: TdmSysSetImp;                                                                                                                                                                                                   
                                                                                                                                                                                                   
implementation                                                                                                                                                                                                   
                                                                                                                                                                                                   
{$R *.DFM}                                                                                                                                                                                                   

initialization
                                                                                                                                                                                                   
  dmSysSetImp := TdmSysSetImp.Create(Application);                                                                                                                                                                                                   
                                                                                                                                                                                                   
end.                                                                                                                                                                                                   
                                                                                                                                                                                                  
                                                                                                                                                                                                 
                                                                                                                                                                                                
                                                                                                                                                                                               
                                                                                                                                                                                              
                                                                                                                                                                                             

                                                                                                                                                                                           
                                                                                                                                                                                          
                                                                                                                                                                                         
                                                                                                                                                                                        
                                                                                                                                                                                       
                                                                                                                                                                                      
                                                                                                                                                                                     
                                                                                                                                                                                    
                                                                                                                                                                                   
                                                                                                                                                                                  
                                                                                                                                                                                 
                                                                                                                                                                                
                                                                                                                                                                               
                                                                                                                                                                              
                                                                                                                                                                             
                                                                                                                                                                            
                                                                                                                                                                           
                                                                                                                                                                          
                                                                                                                                                                         
                                                                                                                                                                        
                                                                                                                                                                       
                                                                                                                                                                      
                                                                                                                                                                     
                                                                                                                                                                    
                                                                                                                                                                   
                                                                                                                                                                  
                                                                                                                                                                 
                                                                                                                                                                
                                                                                                                                                               
                                                                                                                                                              
                                                                                                                                                             
                                                                                                                                                            
                                                                                                                                                           
                                                                                                                                                          
                                                                                                                                                         
                                                                                                                                                        
                                                                                                                                                       
                                                                                                                                                      
                                                                                                                                                     
                                                                                                                                                    
                                                                                                                                                   
                                                                                                                                                  
                                                                                                                                                 
                                                                                                                                                
                                                                                                                                               
                                                                                                                                              
                                                                                                                                             
                                                                                                                                            
                                                                                                                                           
                                                                                                                                          
                                                                                                                                         
                                                                                                                                        
                                                                                                                                       
                                                                                                                                      
                                                                                                                                     
                                                                                                                                    
                                                                                                                                   
                                                                                                                                  
                                                                                                                                 
                                                                                                                                
                                                                                                                               
                                                                                                                              
                                                                                                                             
                                                                                                                            
                                                                                                                           
                                                                                                                          
                                                                                                                         
                                                                                                                        
                                                                                                                       
                                                                                                                      
                                                                                                                     
                                                                                                                    
                                                                                                                   
                                                                                                                  
                                                                                                                 
                                                                                                                
                                                                                                               
                                                                                                              
                                                                                                             
                                                                                                            
                                                                                                           
                                                                                                          
                                                                                                         
                                                                                                        
                                                                                                       
                                                                                                      
                                                                                                     
                                                                                                    
                                                                                                   
                                                                                                  
                                                                                                 
                                                                                                
                                                                                               
                                                                                              
                                                                                             
                                                                                            
                                                                                           
                                                                                          
                                                                                         
                                                                                        
                                                                                       
                                                                                      
                                                                                     
                                                                                    
                                                                                   
                                                                                  
                                                                                 
                                                                                
                                                                               
                                                                              
                                                                             
                                                                            
                                                                           
                                                                          
                                                                         
                                                                        
                                                                       
                                                                      
                                                                     
                                                                    
                                                                   
                                                                  
                                                                 
                                                                
                                                               
                                                              
                                                             
                                                            
                                                           
                                                          
                                                         
                                                        
                                                       
                                                      
                                                     
                                                    
                                                   
                                                  
                                                 
                                                
                                               
                                              
                                             
                                            
                                           
                                          
                                         
                                        
                                       
                                      
                                     
                                    
                                   
                                  
                                 
                                
                               
                              
                             
                            
                           
                          
                         
                        
                       
                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

