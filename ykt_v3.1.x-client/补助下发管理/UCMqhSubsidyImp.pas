unit UCMqhSubsidyImp;
         
interface         
         
uses         
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,         
  KSCmdModules, Db, BDAImpEx, KCDataAccess, WVCmdProc, KCWVProcBinds;      
         
type         
  TdmSubsidyImp = class(TCommandModule)         
    Dataset: TKCDataset;  
    cqimportSublidyList: TKCWVProcessor;  
    cqSublidySend: TKCWVProcessor;  
    cqsetSubsidyInfo: TKCWVQuery; 
    cpsetSubsidyInfo: TKCWVProcessor;
    cpPatchdel: TKCWVProcessor;
    cpCheck: TKCWVProcessor;
    kcSubsidyRcv: TKCWVProcessor;
  private         
    { Private declarations }         
  public         
    { Public declarations }         
  end;         
         
var         
  dmSubsidyImp: TdmSubsidyImp;         
         
implementation         
         
{$R *.DFM}         
initialization
dmSubsidyImp:=TdmSubsidyImp.Create(Application);         
         
end.         
        
       
      
     
    
   
  
 

