unit UCMqhReportImp;
                                            
interface                                            
  
uses  
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                                            
  KSCmdModules, WVCmdProc, KCWVProcBinds, Db, BDAImpEx, KCDataAccess,
  ZConnection,NativeXml;

type                                            
  TdmReportImp = class(TCommandModule)
    cqUnsuitReport: TKCWVQuery;
    cqTransfer: TKCWVQuery;
    cqEquip: TKCWVQuery;
    cqticketMoneyReport: TKCWVQuery;
    cqSetOperator: TKCWVQuery;
    cqOperGroupManager: TKCWVQuery;
    KCTradeSubject: TKCWVQuery;
    KCTotSubject: TKCWVQuery;
    KCWSubBalanceRep: TKCWVQuery;
    KCWSystemRunStat: TKCWVQuery;
    KCWBusiReport: TKCWVQuery;
    cqCardUsedInfo_R: TKCWVQuery;
    kcTicketCashRpt_R: TKCWVQuery;
    KCWBusiReportPOS: TKCWVQuery;
    KCWBusiReportFC: TKCWVQuery;
    KCWBusiReportDay: TKCWVQuery;
    KCWBusiPayIn: TKCWVQuery;
    cqfillBusiPayIn: TKCWVProcessor;
    KCWPayInQuery: TKCWVQuery;
    Dataset: TKCDataset;
    kcBusiGatherRep: TKCWVQuery;
    kcSubject: TKCWVQuery;
    conFB: TZConnection;
    cqCardUsedInfo: TKCWVQuery;
    kcTicketCashReport: TKCWVQuery;
    kcBusiStatFC: TKCWVQuery;
    kcBusiRunStatRpt: TKCWVQuery;
    kcQBusiByKey: TKCWVQuery;
    kcOperRpt: TKCWVQuery;
    kcBusiFeeRpt: TKCWVQuery;
    kcCardDestoryRpt: TKCWVQuery;
    kcSysAccount: TKCWVQuery;
    kcSysAccQuery: TKCWVQuery;
    kcOperCashTot: TKCWVQuery;
    conSLite: TZConnection;
    KCDealBankAccQ: TKCWVQuery;
    KCDealBankAcc: TKCWVQuery;
    KCDealBankAccDtlQ: TKCWVQuery;
    KCDealBankAccDtl: TKCWVQuery;
    KCBalanceRpt: TKCWVQuery;
    KCBusiPayIn_nju: TKCWVQuery;
    kcBusiPay_nju: TKCWVProcessor;
    KCBusiPayInQ_nju: TKCWVQuery;
  private  
    { Private declarations }  
  public  
    { Public declarations }
    procedure Init; override;
  end;                                            
                                            
var  
  dmReportImp: TdmReportImp;                                
                                            
implementation                                            

uses SmartCardCommon,KSClientConsts;
{$R *.DFM}
                                
{ TdmReportImp }

procedure TdmReportImp.Init;
var
  dbPath:string;
begin
  inherited;
  dbPath := ExtractFilePath(Application.ExeName);
  {
  try
    if conFB.Connected then
      conFB.Connected := False;
    conFB.Database := dbPath+'\YKTDB.FDB';
    conFB.Connected;
  except
    on e:Exception do
      ShowMessage('打开FB数据库失败-'+e.Message);
  end;
  }
  try
    if conSLite.Connected then
      conSLite.Connected := False;
    conSLite.Database := sdAnsiToUtf8(dbPath+'\YKTDB.db3');
    conSLite.Connected;
  except
    on e:Exception do
      ShowMessage('打开SQLite数据库失败，安装目录不能是中文-'+e.Message);
  end;
end;

initialization
dmReportImp:=TdmReportImp.Create(Application);                                
                                            
end.                                            
                                           
                                          
                                         
                                        

                                      
  
                                    
                                   
                                  
                                 
                                
                               
                              
                             
                            
                           
                          
                         
                        
                       
                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

