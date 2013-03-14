unit UCMqhWaterControlDef;  
              
interface              
              
uses              
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,              
  KSCmdModules, Db, BDAImpEx, KCDataAccess, WVCmdProc, KCWVProcBinds,             
  WVCmdTypeInfo;             
              
type              
  TWaterControlDef = class(TCommandModule)
  private              
    { Private declarations }              
  public              
    { Public declarations }              
  end;              
              
var              
  WaterControlDef: TWaterControlDef;              
              
implementation              
              
{$R *.DFM}              
initialization  
  WaterControlDef := tWaterControlDef.Create(Application);              
end.              
             
            
  
          
         
        
       
      
     
    
   
  
 

