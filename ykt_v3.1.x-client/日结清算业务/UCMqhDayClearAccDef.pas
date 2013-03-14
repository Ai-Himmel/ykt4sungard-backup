unit UCMqhDayClearAccDef;    
    
interface    
    
uses    
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,    
  KSCmdModules, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds;    
    
type    
  TdmDayClearAccDef = class(TCommandModule)    
    cqDayAccount: TWVCommandTypeInfo;    
    cqfillTrans: TWVCommandTypeInfo;   
    cqfillReTrans: TWVCommandTypeInfo;  
    cqconsumeBalance: TWVCommandTypeInfo; 
    cqreConsumeBalance: TWVCommandTypeInfo;
    cqTradeLogDetailed: TWVCommandTypeInfo;
  private    
    { Private declarations }    
  public    
    { Public declarations }    
  end;    
    
var    
  dmDayClearAccDef: TdmDayClearAccDef;    
    
implementation    
    
{$R *.DFM}    
initialization    
  dmDayClearAccDef:=TdmDayClearAccDef.Create(Application);    
    
end.    
   
  
 

