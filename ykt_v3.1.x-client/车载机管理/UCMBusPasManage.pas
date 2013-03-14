unit UCMBusPasManage;
       
interface       
       
uses       
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,       
  KSCmdModules, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds;
       
type       
  TdmBusPosManage = class(TCommandModule)
    wvgetworkkey: TWVCommandTypeInfo;
    kcworkkey: TKCWVQuery;
    WVgetblacklist: TWVCommandTypeInfo;
    kcwgetblacklist: TKCWVQuery;
    getcardtypeinfo: TWVCommandTypeInfo;
    kcgetcardtypeinfo: TKCWVQuery;
    uploadwater: TWVCommandTypeInfo;
    kcupload: TKCWVQuery;
    kcBusPosSerialQ: TKCWVQuery;
    cqBusPosSerialQ: TWVCommandTypeInfo;
    cqBusPosSerStat: TWVCommandTypeInfo;
    kcBusPosSerStat: TKCWVQuery;
    cq1BusPosserial: TWVCommandTypeInfo;
    kc1BusPosSerial: TKCWVQuery;
    cq1BusPosStat: TWVCommandTypeInfo;
    kcBusPosStat: TKCWVQuery;
  private
    { Private declarations }       
  public       
    { Public declarations }       
  end;       
       
var
  dmBusPosManage: TdmBusPosManage;
       
implementation       
       
{$R *.DFM}       
initialization       
dmBusPosManage:=TdmBusPosManage.Create(Application);

end.       
      
     
    
   
  
 

