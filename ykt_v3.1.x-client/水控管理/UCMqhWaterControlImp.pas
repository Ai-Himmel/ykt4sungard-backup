unit UCMqhWaterControlImp;
             
interface             
             
uses             
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,             
  KSCmdModules, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds, Db, BDAImpEx,  
  KCDataAccess;  
             
type             
  TWaterControlImp = class(TCommandModule)  
    cqQueryGlobeParaByKey: TKCWVQuery;  
    Dataset: TKCDataset;  
    WVQueryGlobeParaByKey: TWVCommandTypeInfo;  
    cqwaterCardPatch: TKCWVQuery; 
    WVwaterCardPatch: TWVCommandTypeInfo; 
    cpReCreCardOK: TKCWVProcessor; 
    cpPatchCard: TKCWVProcessor;
    cpModifyWaterState: TKCWVProcessor;
    cqQCIByPatchCard: TKCWVQuery; 
    ctQCIByPathCard: TWVCommandTypeInfo; 
    ctPatchCard: TWVCommandTypeInfo;
    ctModifyWaterState: TWVCommandTypeInfo;
    ctReCreCardOK: TWVCommandTypeInfo;
    ctCollectionWaterTrade: TWVCommandTypeInfo;
    cqCollectionWaterTrade: TKCWVProcessor;
  private             
    { Private declarations }             
  public             
    { Public declarations }             
  end;             
             
var             
  WaterControlImp: TWaterControlImp;             
             
implementation             
             
{$R *.DFM}             
initialization             
 WaterControlImp := TWaterControlImp.Create(Application);             
end.             
            
           
          
         
        
       
      
     
    
   
  
 

