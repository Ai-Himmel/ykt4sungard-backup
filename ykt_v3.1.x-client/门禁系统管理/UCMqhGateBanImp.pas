unit UCMqhGateBanImp;
                                                                                                      
interface                                                                                                      
                                                                                                      
uses                                                                                                      
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                                                                                                      
  KSCmdModules, WVCmdProc, KCWVProcBinds, Db, BDAImpEx, KCDataAccess;        
                                                                                                      
type                                                                                                      
  TdmGateBanImp = class(TCommandModule)                         
    cqsetGateHoliday: TKCWVQuery;                        
    cpsetGateHoliday: TKCWVProcessor;                       
    cqsetGateTime: TKCWVQuery;                      
    cpsetGateTime: TKCWVProcessor;                     
    cqsetDayTimeGroup: TKCWVQuery;                    
    cqsetTimeGroup: TKCWVQuery;                   
    cpsetTimeGroup: TKCWVProcessor;                  
    cqqueryTimeGroupDetail: TKCWVQuery;                 
    cqsetGateHolidayDetail: TKCWVQuery;                
    cqsetGateGroup: TKCWVQuery;               
    cpsetGateGroup: TKCWVProcessor;              
    cqsetGateGroupForGate: TKCWVQuery;             
    cpsetGateGroupForGate: TKCWVProcessor;            
    cqsetGateOperLimit: TKCWVQuery;           
    cpsetGateOperLimit: TKCWVProcessor;          
    cqsetGateGroupOperLimit: TKCWVQuery;         
    cpsetGateGroupOperLimit: TKCWVProcessor;        
    Dataset: TKCDataset;        
    cqQueryEquipmentByOther: TKCWVQuery;        
    KCHolidayQuery: TKCWVQuery;        
    cqsetWeekTimeGroup: TKCWVQuery;       
    cpsetWeekTimeGroup: TKCWVProcessor;     
    KCallotCustGate: TKCWVProcessor;     
    cqGateListQuery: TKCWVQuery;    
    cqGateListDelete: TKCWVQuery;   
    KCGateGroupOper: TKCWVQuery;   
    cqgateSerialDetailQuery: TKCWVQuery;  
    cqattendDetailQuery: TKCWVQuery; 
    cqattendDetailstat: TKCWVQuery;
    cqQueryGateOpenAlong: TKCWVQuery;
    cqSetGateOpenAlong: TKCWVProcessor;
    cqsetgatebaninfo: TKCWVProcessor;
    cpSetGateTimeWeek: TKCWVProcessor;
    cqGateTimeWeekManager: TKCWVQuery;
    kcGateTimeWeekDel: TKCWVQuery;
    cqQueryCustomerByOther: TKCWVQuery;
    kcSetGateOpenMgr: TKCWVQuery;
    kcQgateMgrOpen: TKCWVQuery;
  private                                          
    { Private declarations }                                                                                                      
  public                                                                                                      
    { Public declarations }                                                                                                      
  end;                                                                                                      
                                                                                                      
var                                                                                                      
  dmGateBanImp: TdmGateBanImp;                                                                                                      
                                                                                                      
implementation                                                                                                      
                                                                                                      
{$R *.DFM}                                                                                                      
initialization                                                                                                      
  dmGateBanImp := TdmGateBanImp.Create(Application);                                                                                                      
                                                                                                      
end.

