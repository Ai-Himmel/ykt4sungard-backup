unit UCMqhSubsidyDef;
         
interface         
         
uses         
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,         
  KSCmdModules, WVCmdTypeInfo;         
         
type         
  TdmSubsidyDef = class(TCommandModule)  
    cqSublidyImport: TWVCommandTypeInfo;  
    cqsendSublidyList: TWVCommandTypeInfo;  
    cqsetSubsidyInfo: TWVCommandTypeInfo; 
    cpsetSubsidyInfo: TWVCommandTypeInfo;
    cqPatchDel: TWVCommandTypeInfo;
    cqCheck: TWVCommandTypeInfo;
    WVSubsidyRcv: TWVCommandTypeInfo;
  private         
    { Private declarations }         
  public         
    { Public declarations }         
  end;         
         
var         
  dmSubsidyDef: TdmSubsidyDef;         
         
implementation         
         
{$R *.DFM}         
initialization         
dmSubsidyDef:=TdmSubsidyDef.Create(Application);         
         
end.         
        
       
      
     
    
   
  
 

