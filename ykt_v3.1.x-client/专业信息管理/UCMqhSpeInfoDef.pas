unit UCMqhSpeInfoDef;
               
interface               
               
uses               
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,               
  KSCmdModules, WVCmdTypeInfo, KCWVProcBinds, Db, BDAImpEx, KCDataAccess,
  WVCmdProc;
               
type               
  TdmSpeInfoDef = class(TCommandModule)               
    cqQuerySpeInfoByKey: TWVCommandTypeInfo;          
    cqQuerySpeInfoByOther: TWVCommandTypeInfo;
    cpSetSpeInfo: TWVCommandTypeInfo;
    KCQuerySpeInfoByKey: TKCWVQuery;
    Dataset: TKCDataset;
    KCQuerySpeInfoByOther: TKCWVQuery;
    KCSetSpeInfo: TKCWVProcessor;
  private               
    { Private declarations }               
  public               
    { Public declarations }               
  end;               
               
var               
  dmSpeInfoDef: TdmSpeInfoDef;               
               
implementation               
            
{$R *.DFM}            
initialization          
  dmSpeInfoDef:=TdmSpeInfoDef.Create(Application);               
               
end.               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

