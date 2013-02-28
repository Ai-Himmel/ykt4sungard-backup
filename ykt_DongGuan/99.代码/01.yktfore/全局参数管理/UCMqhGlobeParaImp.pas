unit UCMqhGlobeParaImp;
                              
interface                              
                              
uses                              
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                              
  KSCmdModules, KCWVProcBinds, WVCmdProc, Db, BDAImpEx, KCDataAccess;                          
                              
type                              
  TdmGlobeParaImp = class(TCommandModule)                              
    cpAddGlobeParaInfo: TKCWVProcessor;                          
    Dataset: TKCDataset;                          
    cpChangeGlobeParaInfo: TKCWVProcessor;                          
    cpDelGlobeParaInfo: TKCWVProcessor;                          
    cqQueryGlobeParaByOther: TKCWVQuery;            
    cqQueryGlobeParaByKey: TKCWVQuery;          
    cpAddSetChargePara: TKCWVProcessor;     
    cpChargeSetChargePara: TKCWVProcessor;     
    cpDelSetChargePara: TKCWVProcessor;     
    cqSetChargePara: TKCWVQuery;  
    cqSetChargeType: TKCWVQuery;
  private                              
    { Private declarations }                              
  public                              
    { Public declarations }                              
  end;                              
                              
var                              
  dmGlobeParaImp: TdmGlobeParaImp;                              
                              
implementation                              
                              
{$R *.DFM}                     
initialization
  dmGlobeParaImp:=TdmGlobeParaImp.Create(Application);                     
          
end.                              
                             
                            
                           
                          
                         
                        
                       
                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

