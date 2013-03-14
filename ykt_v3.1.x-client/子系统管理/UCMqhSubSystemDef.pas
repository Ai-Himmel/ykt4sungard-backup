unit UCMqhSubSystemDef;
                                                             
interface                                                             
                                                             
uses                                                             
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                                                             
  KSCmdModules, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds;        
                                                             
type                                                             
  TdmSubSystemDef = class(TCommandModule)                                                 
    cqQuerySubSystemByOther: TWVCommandTypeInfo;                                    
    cpAddSubSystemInfo: TWVCommandTypeInfo;                            
    cpChangeSubSystemInfo: TWVCommandTypeInfo;               
    cqQuerySubSystemByKey: TWVCommandTypeInfo;         
    cqQueryEquipmentByKey: TWVCommandTypeInfo;         
    cpAddEquipmentInfo: TWVCommandTypeInfo;         
    cpChangeEquipmentInfo: TWVCommandTypeInfo;         
    cpDelEquipmentInfo: TWVCommandTypeInfo;         
    cqQueryEquipmentByOther: TWVCommandTypeInfo;         
    cqDownMagFeePortion: TWVCommandTypeInfo;         
    cqDownConsumeLimit: TWVCommandTypeInfo;         
    cpDelSubSystemInfo: TWVCommandTypeInfo;         
    cpDownEquipClock: TWVCommandTypeInfo;         
    cpUpEquipClock: TWVCommandTypeInfo;         
    cqQueryEquipmentCanEdit: TWVCommandTypeInfo;        
    cpCollectConsumeSer: TWVCommandTypeInfo;         
    cpCollectAddMoneySer: TWVCommandTypeInfo;         
    cpEquipCompellOut: TWVCommandTypeInfo;        
    cpSetHisSumMoney: TWVCommandTypeInfo;        
    cqQueryEquipmentTree: TWVCommandTypeInfo;      
    cqsubSendListQuery: TWVCommandTypeInfo;     
    cqsetEquipPara2: TWVCommandTypeInfo;    
    cqCustomerKindByKey: TWVCommandTypeInfo;    
    cqEquGroup: TWVCommandTypeInfo;    
    cqsetCommCfParam: TWVCommandTypeInfo;   
    cpsetCommCfParam: TWVCommandTypeInfo;  
    WVGateOpen: TWVCommandTypeInfo;  
    WVDevInfoImp: TWVCommandTypeInfo;  
    cqdevImpManage: TWVCommandTypeInfo; 
    cpdevImpManage: TWVCommandTypeInfo;
    WVdevBusiImpCheck: TWVCommandTypeInfo;
    cqPatchDel: TWVCommandTypeInfo;
    cqFeeType: TWVCommandTypeInfo;
    WVchange: TWVCommandTypeInfo;
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
                                                            
                                                           
                                                          
                                                         
                                                        
                                                       
                                                      
                                                     
                                                    
                                                   
                                                  
                                                 
                                                
                                               
                                              
                                             
                                            
                                           
                                          
                                         
                                        
                                       
                                      
                                     
                                    
                                   
                                  
                                 
                                
                               
                              
                             
                            
                           
                          
                         
                        
                       
                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

