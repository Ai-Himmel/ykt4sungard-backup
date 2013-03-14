unit UCMqhSpeInfoImp;
               
interface               
               
uses               
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,               
  KSCmdModules, WVCmdProc, KCWVProcBinds, Db, BDAImpEx, KCDataAccess;          
               
type               
  TdmSpeInfoImp = class(TCommandModule)
  private               
    { Private declarations }               
  public               
    { Public declarations }               
  end;               
               
var               
  dmSpeInfoImp: TdmSpeInfoImp;               
               
implementation               
            
{$R *.DFM}          
initialization
  dmSpeInfoImp:=TdmSpeInfoImp.Create(Application);               
               
end.               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

