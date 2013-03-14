unit UCMqhGateBanDef;
                                                                                                     
interface                                                                                                     
                                                                                                     
uses                                                                                                     
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                                                                                                     
  KSCmdModules, WVCmdProc, KCWVProcBinds, Db,                                                                                  
  KCDataAccess, BDAImpEx, WVCmdTypeInfo;        
                                                                                 
type                                                                                                     
  TdmGateBanDef = class(TCommandModule)                         
    cqsetGateHoliday: TWVCommandTypeInfo;                        
    cpsetGateHoliday: TWVCommandTypeInfo;                       
    cqsetGateTime: TWVCommandTypeInfo;                      
    cpsetGateTime: TWVCommandTypeInfo;                     
    cqsetDayTimeGroup: TWVCommandTypeInfo;                    
    cqsetTimeGroup: TWVCommandTypeInfo;                   
    cpsetTimeGroup: TWVCommandTypeInfo;                  
    cqqueryTimeGroupDetail: TWVCommandTypeInfo;   
    WVholidayDetailSet: TWVCommandTypeInfo;   
    cqsetGateGroup: TWVCommandTypeInfo;               
    cpsetGateGroup: TWVCommandTypeInfo;              
    cqsetGateGroupForGate: TWVCommandTypeInfo;             
    cpsetGateGroupForGate: TWVCommandTypeInfo;            
    cqsetGateOperLimit: TWVCommandTypeInfo;           
    cpsetGateOperLimit: TWVCommandTypeInfo;          
    cqsetGateGroupOperLimit: TWVCommandTypeInfo;         
    cpsetGateGroupOperLimit: TWVCommandTypeInfo;        
    cqQueryEquipmentByOther: TWVCommandTypeInfo;        
    WVHolidayQuery: TWVCommandTypeInfo;        
    cqsetWeekTimeGroup: TWVCommandTypeInfo;       
    cpsetWeekTimeGroup: TWVCommandTypeInfo;      
    cqallotCustGate: TWVCommandTypeInfo;     
    cqGateListQuery: TWVCommandTypeInfo;    
    cqGateListDelete: TWVCommandTypeInfo;   
    WVGateGroupOper: TWVCommandTypeInfo;   
    cqgateSerialDetailQuery: TWVCommandTypeInfo;  
    cqattendDetailQuery: TWVCommandTypeInfo; 
    cqattendDetailstat: TWVCommandTypeInfo;
    cqSetGateOpenAlong: TWVCommandTypeInfo;
    cqQueryGateOpenAlong: TWVCommandTypeInfo;
    cqgatebansetinfo: TWVCommandTypeInfo;
    cqSetGateTimeWeek: TWVCommandTypeInfo;
    cqGateTimeWeekManager: TWVCommandTypeInfo;
    cqGateTimeWeekDel: TWVCommandTypeInfo;
    cqQueryCustomerByOther: TWVCommandTypeInfo;
    cqSetGateMgrOpen: TWVCommandTypeInfo;
    cqQGateMgrOpen: TWVCommandTypeInfo;
  private                         
    { Private declarations }                                                                                                     
  public                                                                                                     
    { Public declarations }                                                                                                     
  end;                                                                                                     
                                                                                                     
var                                                                                                     
  dmGateBanDef: TdmGateBanDef;                                                                                                     
                                                                                                     
implementation                                                                                                     
                                                                                                     
{$R *.DFM}                                                                                                     
initialization                                                                                                     
  dmGateBanDef := TdmGateBanDef.Create(Application);                                                                                                     
                                                                                                     
end.

