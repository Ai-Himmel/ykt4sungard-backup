unit UCMqhCardLibraryImp;
      
interface      
      
uses      
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,      
  KSCmdModules, Db, BDAImpEx, KCDataAccess, KCWVProcBinds, WVCmdProc,    
  WVCmdTypeInfo;    
      
type      
  TdmCardLibrarytImp = class(TCommandModule)    
    cqsetCardType: TKCWVQuery;    
    cpsetCardType: TKCWVProcessor;    
    Dataset: TKCDataset;   
    cqcardInfoQuery: TKCWVQuery;   
    cqCardIn: TKCWVProcessor;   
    cqCardOut: TKCWVProcessor;   
    cqCardTrans: TKCWVProcessor;   
    cqCardDestory: TKCWVProcessor;   
    cqsetMoneyInfo: TKCWVQuery;  
    cpsetMoneyInfo: TKCWVProcessor;
  private      
    { Private declarations }      
  public      
    { Public declarations }      
  end;      
      
var    
  dmCardLibrarytImp: TdmCardLibrarytImp;    
      
implementation      
      
{$R *.DFM}      
initialization   
  dmCardLibrarytImp := TdmCardLibrarytImp.Create(Application);    
    
end.    
     
    
   
  
 

