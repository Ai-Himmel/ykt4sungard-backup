unit UCMqhDeviceSuperviseDef;
      
interface      
      
uses      
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,      
  KSCmdModules, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds, Db, BDAImpEx,     
  KCDataAccess;     
      
type      
  TdmDeviceSuperviseDef = class(TCommandModule)      
    cpSmartTermUpSerial: TWVCommandTypeInfo;     
    cqSmartTermSetParam: TWVCommandTypeInfo;    
    cqGetSysWorkKey: TWVCommandTypeInfo;    
    cqSmartTermDownBlkCard: TWVCommandTypeInfo;   
    cpUpdateVersion: TWVCommandTypeInfo;  
    cqsendSmartTermList: TWVCommandTypeInfo; 
    cqacceptSmartTermList: TWVCommandTypeInfo;
    cqSmartTermQueryList: TWVCommandTypeInfo;
    WVCommandTypeInfo1: TWVCommandTypeInfo;
    KCWVProcessor1: TKCWVProcessor;
    KCWVQuery1: TKCWVQuery;
    KCWVQuery2: TKCWVQuery;
    KCWVQuery3: TKCWVQuery;
    KCWVProcessor2: TKCWVProcessor;
    KCWVQuery4: TKCWVQuery;
    kcSmartTermQueryList: TKCWVQuery;
    KCWVProcessor3: TKCWVProcessor;
    KCacceptSmartTermList: TKCWVProcessor;
    Dataset: TKCDataset;
    ckDeleteList: TKCWVProcessor;
    cqDeleteList: TWVCommandTypeInfo;
    WVCommandTypeInfo2: TWVCommandTypeInfo;
    KCWVProcessor4: TKCWVProcessor;
    WVAttendSerial: TWVCommandTypeInfo;
    kcAttendSerial: TKCWVProcessor;
  private      
    { Private declarations }      
  public      
    { Public declarations }      
  end;      
      
var      
  dmDeviceSuperviseDef: TdmDeviceSuperviseDef;      
      
implementation      
      
{$R *.DFM}      
 initialization      
  dmDeviceSuperviseDef:=TdmDeviceSuperviseDef.Create(Application);      
      
end.      
     
    
   
  
 

