unit UCMqhUnitInfoImp;
    
interface    
    
uses    
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,    
  KSCmdModules, Db, BDAImpEx, KCDataAccess, KCWVProcBinds, WVCmdProc;
    
type    
  TdmUnitInfoImp = class(TCommandModule)
  private    
    { Private declarations }    
  public    
    { Public declarations }    
  end;    
    
var    
  dmUnitInfoImp: TdmUnitInfoImp;    
    
implementation    

{$R *.DFM}    
initialization    
  dmUnitInfoImp:=TdmUnitInfoImp.Create(Application);    
    
end.    
   
  
 

