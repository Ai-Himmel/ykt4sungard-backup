unit UCMqhDeviceSuperviseImp;
      
interface      
      
uses      
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,      
  KSCmdModules, WVCmdProc, KCWVProcBinds, Db, BDAImpEx, KCDataAccess;      
      
type      
  TdmDeviceSuperviseImp = class(TCommandModule)
    Dataset: TKCDataset;
  private      
    { Private declarations }      
  public      
    { Public declarations }      
  end;      
      
var      
  dmDeviceSuperviseImp: TdmDeviceSuperviseImp;      
     
implementation      
     
{$R *.DFM}      
  initialization           
  dmDeviceSuperviseImp:=TdmDeviceSuperviseImp.Create(Application);      
      
end.      
     
    
   
  
 

