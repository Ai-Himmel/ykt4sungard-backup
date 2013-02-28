unit UCMqhUnitInfoDef;
    
interface    
    
uses    
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,    
  KSCmdModules, WVCmdTypeInfo, Db, BDAImpEx, KCDataAccess, KCWVProcBinds,
  WVCmdProc;
    
type    
  TdmUnitInfoDef = class(TCommandModule)    
    cqQueryUnitInfoByKey: TWVCommandTypeInfo;   
    cqQueryUnitInfoByOther: TWVCommandTypeInfo;
    cpSetUnitInfo: TWVCommandTypeInfo;
    KCQueryUnitInfoByKey: TKCWVQuery;
    KCQueryUnitInfoByOther: TKCWVQuery;
    KCSetUnitInfo: TKCWVProcessor;
    Dataset: TKCDataset;
  private    
    { Private declarations }    
  public    
    { Public declarations }    
  end;    
    
var    
  dmUnitInfoDef: TdmUnitInfoDef;    

implementation    
    
{$R *.DFM}    
initialization    
  dmUnitInfoDef:=TdmUnitInfoDef.Create(Application);    
    
end.    
   
  
 

