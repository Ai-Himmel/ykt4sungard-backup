unit UCMqhGlobeParaDef;
                             
interface                             
                             
uses                             
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,         
  KSCmdModules, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds;         
                             
type                             
  TdmGlobeParaDef = class(TCommandModule)                             
    cpAddGlobeParaInfo: TWVCommandTypeInfo;                         
    cpChangeGlobeParaInfo: TWVCommandTypeInfo;                         
    cpDelGlobeParaInfo: TWVCommandTypeInfo;                         
    cqQueryGlobeParaByOther: TWVCommandTypeInfo;           
    cqQueryGlobeParaByKey: TWVCommandTypeInfo;    
    cpAddSetChargePara: TWVCommandTypeInfo;    
    cpChargeSetChargePara: TWVCommandTypeInfo;    
    cpDelSetChargePara: TWVCommandTypeInfo;    
    cqSetChargePara: TWVCommandTypeInfo;  
    cqSetChargeType: TWVCommandTypeInfo;
  private                             
    { Private declarations }                             
  public                             
    { Public declarations }                             
  end;                             
                             
var                             
  dmGlobeParaDef: TdmGlobeParaDef;                             
                             
implementation                             
                             
{$R *.DFM}                    
initialization         
  dmGlobeParaDef:=TdmGlobeParaDef.Create(Application);                         
                             
end.         
                            
         
                         
                         
                        
                       
                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

