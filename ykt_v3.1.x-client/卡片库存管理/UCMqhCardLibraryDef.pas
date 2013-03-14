unit UCMqhCardLibraryDef;
      
interface      
      
uses      
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,      
  KSCmdModules, WVCmdTypeInfo, Db, BDAImpEx, KCDataAccess, KCWVProcBinds,    
  WVCmdProc;    
      
type      
  TdmCardLibrarytDef = class(TCommandModule)    
    WVQsetCardType: TWVCommandTypeInfo;    
    WVCsetCardType: TWVCommandTypeInfo;   
    cqcardInfoQuery: TWVCommandTypeInfo;   
    WVCardIn: TWVCommandTypeInfo;   
    WVCardOut: TWVCommandTypeInfo;   
    WVCardTrans: TWVCommandTypeInfo;   
    WVCardDestory: TWVCommandTypeInfo;   
    cqsetMoneyInfo: TWVCommandTypeInfo;  
    cpsetMoneyInfo: TWVCommandTypeInfo;
  private      
    { Private declarations }      
  public      
    { Public declarations }      
  end;      
      
var      
  dmCardLibrarytDef: TdmCardLibrarytDef;    
      
implementation      
      
{$R *.DFM}   
initialization    
  dmCardLibrarytDef := TdmCardLibrarytDef.Create(Application);    
    
end.      
     
    
   
  
 

