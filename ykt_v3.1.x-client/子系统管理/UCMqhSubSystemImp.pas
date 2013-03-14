unit UCMqhSubSystemImp;
                                                           
interface                                                           
                                                           
uses                                                           
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,                                                           
  KSCmdModules, WVCmdProc, KCWVProcBinds, Db, BDAImpEx, KCDataAccess,    
  WVCmdTypeInfo,IniFiles;    
         
type         
  TdmSubSystemImp = class(TCommandModule)         
    Dataset: TKCDataset;                                               
    cqQuerySubSystemByOther: TKCWVQuery;         
    cpAddSubSystemInfo: TKCWVProcessor;                          
    cpChangeSubSystemInfo: TKCWVProcessor;                          
    cpDelSubSystemInfo: TKCWVProcessor;               
    cqQuerySubSystemByKey: TKCWVQuery;         
    cqQueryEquipmentByKey: TKCWVQuery;         
    cqQueryEquipmentByOther: TKCWVQuery;         
    cpAddEquipmentInfo: TKCWVProcessor;         
    cpChangeEquipmenInfo: TKCWVProcessor;         
    cpDelEquipmentInfo: TKCWVProcessor;         
    cpDownMagFeePortion: TKCWVProcessor;         
    cpDownConsumeLimit: TKCWVProcessor;         
    cpDownEquipClock: TKCWVProcessor;         
    cpUpEquipClock: TKCWVProcessor;         
    cqQueryEquipmentCanEdit: TKCWVQuery;         
    cpCollectConsumeSer: TKCWVProcessor;         
    cpCollectAddMoneySer: TKCWVProcessor;         
    cpEquipCompellOut: TKCWVProcessor;        
    cpSetHisSumMoney: TKCWVProcessor;        
    cqQueryEquipmentTree: TKCWVQuery;      
    cqsubSendListQuery: TKCWVQuery;     
    cqsetEquipPara2: TKCWVQuery;    
    cpCustomerKindByKey: TKCWVQuery;    
    cpEquGroup: TKCWVProcessor;    
    cqsetCommCfParam: TKCWVQuery;   
    cpsetCommCfParam: TKCWVProcessor;  
    KCPGateOpen: TKCWVProcessor;  
    cqDevInfoImp: TKCWVProcessor;
    cqdevImpManage: TKCWVQuery;
    cpdevImpManage: TKCWVProcessor;
    cqDevBusiImpCheck: TKCWVProcessor;
    cpPatchdel: TKCWVProcessor;
    cpFeeType: TKCWVProcessor;
    KCChange: TKCWVProcessor;
    procedure DataModuleCreate(Sender: TObject);
  private         
  public                                                           
    { Public declarations }                                                           
  end;                                                           
                                                           
var                                                           
  dmSubSystemImp: TdmSubSystemImp;                                                           
                                                           
implementation                       
               
{$R *.DFM}                                                   
procedure TdmSubSystemImp.DataModuleCreate(Sender: TObject);  
var  
  myFile : TIniFile;  
  sType : Integer;  
  sPath:string;  
begin  
  inherited;  
  sPath := ExtractFilePath(Application.ExeName);  
  if fileexists(sPath+'..\configs\setPara.ini') = false then  
  begin  
    ShowMessage('��ȡ�����ļ����������ļ��Ƿ���ڣ�');  
    Exit;  
  end;  
  try  
    try  
      myFile := TIniFile.Create(sPath+'..\configs\setPara.ini');  
      sType := myFile.ReadInteger('downmsgfee', 'funno',-1);  
      cpDownMagFeePortion.RequestType := sType;  
    except  
      ShowMessage('��ȡ���ܺŴ������������ļ��е������Ƿ���ȷ��');  
    end;  
  finally  
    myFile.Free;  
  end;  
end;  
  
initialization  
  dmSubSystemImp:=TdmSubSystemImp.Create(Application);                                                        
                                                           
end.                                                           
                                                          
                                                         
                                                        
                                                       
                                                      
                                                     
                                                    
                                                   
                                                  
                                                 
                                                
                                               
                                              
                                             
                                            
                                           
                                          
                                         
                                        
                                       
                                      
                                     
                                    
                                   
                                  
                                 
                                
                               
                              
                             
                            
                           
                          
                         
                        
                       
                      
                     
                    
                   
                  
                 
                
               
              
             
            
           
          
         
        
       
      
     
    
   
  
 

