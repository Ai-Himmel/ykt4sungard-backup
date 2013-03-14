unit UCMqhSetSystemImp;
                            
interface                            
                            
uses                            
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                            
  KSCmdModules, KCWVProcBinds, WVCmdProc, Db, BDAImpEx, KCDataAccess,                         
  WVCmdTypeInfo;                         
                            
type                            
  TdmSetSystemImp = class(TCommandModule)                            
    cqSetGridShowModle: TKCWVQuery;                           
    cpSetGridShowModle: TKCWVProcessor;                          
    Dataset: TKCDataset;                          
    cqSetGridShow: TKCWVQuery;                         
    ctSetGridShowModle: TWVCommandTypeInfo;                         
    ckSetGridShowModle: TWVCommandTypeInfo;                         
    ckSetGridShow: TWVCommandTypeInfo;                      
    cqsetPlanTask: TKCWVQuery;                     
    cpsetPlanTask: TKCWVProcessor;                    
    WVQueryPlanTask: TWVCommandTypeInfo;                    
    WVSetPlanTask: TWVCommandTypeInfo;                   
    cqqueryPlanTask: TKCWVQuery;                  
    WVQueryPlanTaskInfo: TWVCommandTypeInfo;                  
    cqsetMesList: TKCWVQuery;                 
    cpsetMesList: TKCWVProcessor;                
    WVQueryMesList: TWVCommandTypeInfo;                
    WVSetMesList: TWVCommandTypeInfo;              
    cqsetNetInfo: TKCWVQuery;             
    cpsetNetInfo: TKCWVProcessor;            
    WVNetInfoQuery: TWVCommandTypeInfo;            
    WVSetNetInfo: TWVCommandTypeInfo;            
    cqsetTradeFee: TKCWVQuery;           
    cpsetTradeFee: TKCWVProcessor;          
    WVQTradeFee: TWVCommandTypeInfo;          
    WVSetTradeFee: TWVCommandTypeInfo;          
    cqposSerialManager: TKCWVQuery;         
    cpposSerialManager: TKCWVProcessor;        
    WVposSerialManager: TWVCommandTypeInfo;        
    WVposSerialManager1: TWVCommandTypeInfo;        
    cqPosSerialImport: TKCWVProcessor;        
    WVPosSerialImport: TWVCommandTypeInfo;        
    cqCheck: TKCWVProcessor;        
    WVCheck: TWVCommandTypeInfo;        
    cqqueryOperLog: TKCWVQuery;       
    WVQueryOperLog: TWVCommandTypeInfo;       
    cqCardFee: TWVCommandTypeInfo;       
    KCWcardFee: TKCWVQuery;       
    cpCardFee: TKCWVProcessor;       
    cqCardFeeSet: TWVCommandTypeInfo;       
    cpposSerManager: TKCWVProcessor;       
    WVposSeManager1: TWVCommandTypeInfo;       
    cqposSerManager: TKCWVQuery;       
    WVposSeManager: TWVCommandTypeInfo;       
    cqPatchDel: TWVCommandTypeInfo;       
    cpPatchdel: TKCWVProcessor;     
    cqSetWaterPrice: TKCWVQuery; 
    cpSetWaterPrice: TKCWVProcessor;
    WVSetWaterPrice: TWVCommandTypeInfo;
    WVSetWaterPriceQ: TWVCommandTypeInfo;
  private                            
    { Private declarations }                            
  public                            
    { Public declarations }                            
  end;                            
                            
var                            
  dmSetSystemImp: TdmSetSystemImp;                            
                            
implementation                            
                            
{$R *.DFM}                            
initialization          
dmSetSystemImp:=TdmSetSystemImp.Create(Application);          
                            
end.                            
                           
                          
                         
                        
                       
          
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

