unit UCMqhBusinessEquipDef;  
                 
interface                 
                 
uses                 
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                 
  KSCmdModules, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds;             
             
type                 
  TdmBusinessEquipDef = class(TCommandModule)                
    cqQueryBusinessEquipByOther: TWVCommandTypeInfo;      
    cpSetBusinessEquipInfo: TWVCommandTypeInfo;      
    cqSetBusinessEquipInfo: TWVCommandTypeInfo;             
    cqQueryEquipmentByKey3: TWVCommandTypeInfo;             
    cqQueryBusinessByKey2: TWVCommandTypeInfo;             
    cqQueryBusinessByOther2: TWVCommandTypeInfo;             
    cqQueryEquipmentByOther2: TWVCommandTypeInfo;            
    cqsetMealOrder: TWVCommandTypeInfo;           
    cpsetMealOrder: TWVCommandTypeInfo;    
    WVDevBusiImp: TWVCommandTypeInfo;    
    cqdevBusiImpManage: TWVCommandTypeInfo;   
    cpdevBusiImpManage: TWVCommandTypeInfo;  
    WVdevBusiImpCheck: TWVCommandTypeInfo;  
    cqPatchDel: TWVCommandTypeInfo;  
    cqsetBusiCC: TWVCommandTypeInfo; 
    cpsetBusiCC: TWVCommandTypeInfo;
  private                 
    { Private declarations }                 
  public                 
    { Public declarations }                 
  end;             
             
var                 
  dmBusinessEquipDef: TdmBusinessEquipDef;             
                 
implementation                 
                 
{$R *.DFM}             
initialization      
  dmBusinessEquipDef:=TdmBusinessEquipDef.Create(Application);             
end.                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

