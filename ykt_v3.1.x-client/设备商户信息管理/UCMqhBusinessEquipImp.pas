unit UCMqhBusinessEquipImp;  
                 
interface                 
                 
uses                 
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                 
  KSCmdModules, Db, BDAImpEx, KCDataAccess, KCWVProcBinds, WVCmdProc,WVCommands;             
                 
type                 
  TdmBusinessEquipImp = class(TCommandModule)                
    cqQueryBusinessEquipByOther: TKCWVQuery;      
    cpSetBusinessEquipInfo: TKCWVProcessor;      
    Dataset: TKCDataset;             
    cqSetBusinessEquipInfo: TKCWVQuery;             
    cqQueryEquipmentByKey3: TKCWVQuery;             
    cqQueryBusinessByKey2: TKCWVQuery;             
    cqQueryBusinessByOther2: TKCWVQuery;             
    cqQueryEquipmentByOther2: TKCWVQuery;            
    cqsetMealOrder: TKCWVQuery;           
    cpsetMealOrder: TKCWVProcessor;      
    cqImpDevCustInfo: TKCWVProcessor;    
    cqdevBusiImpManage: TKCWVQuery;   
    cpdevBusiImpManage: TKCWVProcessor;  
    cqDevBusiImpCheck: TKCWVProcessor;  
    cpPatchdel: TKCWVProcessor;  
    cqsetBusiCC: TKCWVQuery; 
    cpsetBusiCC: TKCWVProcessor;
  private                 
    { Private declarations }                 
  public                 
    { Public declarations }             
  end;                 
                 
var                 
  dmBusinessEquipImp: TdmBusinessEquipImp;             
                 
implementation                 
                 
{$R *.DFM}             
initialization             
  dmBusinessEquipImp:=TdmBusinessEquipImp.Create(Application);             
                 
end.                 
             
             
             
             
            
           
          
         
        
       
      
     
    
   
  
 

