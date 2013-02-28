unit UCMqhSetSystemImp;
                     
interface                     
                     
uses                     
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                     
  KSCmdModules, KCWVProcBinds, WVCmdProc, Db, BDAImpEx, KCDataAccess,                  
  WVCmdTypeInfo;                  
                     
type                     
  TdmSetSystemImp = class(TCommandModule)                   
    Dataset: TKCDataset;               
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
    cqCheck: TKCWVProcessor; 
    WVCheck: TWVCommandTypeInfo; 
    cqqueryOperLog: TKCWVQuery;
    WVQueryOperLog: TWVCommandTypeInfo;
    cqCardFee: TWVCommandTypeInfo;
    KCWcardFee: TKCWVQuery;
    cpCardFee: TKCWVProcessor;
    cqCardFeeSet: TWVCommandTypeInfo;
    WVCsetCardType: TWVCommandTypeInfo;
    WVQsetCardType: TWVCommandTypeInfo;
    cqsetCardType: TKCWVQuery;
    cpsetCardType: TKCWVProcessor;
    KCPKGQuery: TKCWVQuery;
    WVPKGQuery: TWVCommandTypeInfo;
    KCPKGOper: TKCWVProcessor;
    WVPKGOper: TWVCommandTypeInfo;
    KCFileQ: TKCWVQuery;
    WVFielQ: TWVCommandTypeInfo;
    KCFileOper: TKCWVProcessor;
    WVFileOper: TWVCommandTypeInfo;
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
                    
                   
                  
                 
                
   
              
             
            
           
          
         
        
       
      
     
    
   
  
 

