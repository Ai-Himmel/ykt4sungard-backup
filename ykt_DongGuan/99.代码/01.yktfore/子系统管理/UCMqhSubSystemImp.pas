unit UCMqhSubSystemImp;
                                                                
interface                                                                
                                                                
uses                                                                
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                                                                
  KSCmdModules, WVCmdProc, KCWVProcBinds, Db, BDAImpEx, KCDataAccess,         
  WVCmdTypeInfo,IniFiles;         
              
type              
  TdmSubSystemImp = class(TCommandModule)              
    Dataset: TKCDataset;     
    cqSetPOSInfo: TKCWVQuery;  
    cpSetPOSInfo: TKCWVProcessor; 
    cqDevRepair: TKCWVQuery;
    KCDevBusiBind: TKCWVProcessor;
    KCDevBusiQ: TKCWVQuery;
    cqSetBusiInfo: TKCWVQuery;
  private              
  public                                                                
    { Public declarations }                                                                
  end;                                                                
                                                                
var                                                                
  dmSubSystemImp: TdmSubSystemImp;                                                                
                                                                
implementation                            
                    
{$R *.DFM}                                                        
initialization       
  dmSubSystemImp:=TdmSubSystemImp.Create(Application);                                                             
                                                                
end.                                                                
                                                               
                                                              
                                                             
                                                            
                                                           
                                                          
                                                         
                                                        
                                                       
                                                      
                                                     
                                                    
                                                   
                                                  
                                                 
                                                
                                               
                                              
                                             
                                            
                                           
                                          
                                         
                                        
                                       
                                      
                                     
                                    
                                   
                                  
                                 
                                
                               
                              
                             
                            
                           
                          
                         
                        
                       
                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

