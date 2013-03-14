unit ULogin;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>ULogin
   <What>操作员登录界面
   <Written By> Huang YanLai (黄燕来)
   <History>
   <Notes>
   MainRequest调用不需要检查返回值。返回值的检查在TdmCommData.cpLoginBindOutput里面完成的。

   wlj 20031113 修改登录，使用期货的登录
   wsn 20041230 修改登录，使用复旦一卡通的登录
**********************************************}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Mask, WVCtrls, ExtCtrls, UICtrls, WorkViews, ImageCtrls,
  WVCmdReq, Winsock, Registry, NB30,TLHelp32, jpeg, AAFont, AACtrls,
  Buttons,CardDll, IdBaseComponent, IdComponent, IdTCPConnection,
  IdTCPClient, IdHTTP;

type
  TdlgLogin = class(TForm)
    UIPanel1: TUIPanel;
    WorkView: TWorkView;
    MainRequest: TWVRequest;
    Label2: TLabel;
    edOperator: TWVEdit;
    Label3: TLabel;
    edtPwd: TWVEdit;
    btnOk: TBitBtn;
    btnClose: TBitBtn;
    AALabel1: TAALabel;
    WVStationReg: TWorkView;
    WVRStationReg: TWVRequest;
    img1: TImage;
    wvSysDate: TWorkView;
    wvrSysDate: TWVRequest;
    idhtp1: TIdHTTP;
    WorkView1: TWorkView;
    QueryRequest: TWVRequest;
    wvWaterStr: TWorkView;
    wvrWaterStr: TWVRequest;
    procedure btnCloseClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure edtPwdKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
  private
    { Private declarations }
    //machineCode:string;
    procedure LoginClick(Sender: TObject);
    procedure UnLockClick(Sender: TObject);
    //function KillExe(strFileName: string): Boolean;
    //function MyFun_GetProcessID(ProcessName: string): Cardinal;

    function getIpAddr: String;

    function MacAddress: string;
    function getWaterPrice(price:Integer):Integer;
    procedure getWaterStrs;
  public
    { Public declarations }
    procedure Execute(var ExitApp: Boolean);
    procedure DoUnLock(var ExitApp: Boolean);
  end;

var
  dlgLogin: TdlgLogin;

procedure DoLogin(var ExitApp: Boolean);

procedure DoUnLock(var ExitApp: Boolean);

resourcestring
  SWait = '正在登录...';
  SLoginError = '登录错误！';
  SUnlockError = '密码不正确';
  Sykt = '一卡通管理系统';

implementation

uses KSFrameWorks, KSFrameWorkUtils, KSClientConsts, UCommData, WVCommands,
  DB, SafeCode, KCDataAccess, UQhClientConsts;

const
  LoginStatusFieldName = '登录状态';
  DepartFieldName = '营业部';
  DepartNameFieldName = '营业部名称';
  OperatorFieldName = '操作员';
  PasswordFieldName = '密码';

{$R *.DFM}

procedure DoLogin(var ExitApp: Boolean);
var
  Dialog: TdlgLogin;
begin
  Dialog := TdlgLogin.Create(Application);
  try
    Dialog.Execute(ExitApp);
  finally
    Dialog.Free;
  end;
end;

procedure DoUnLock(var ExitApp: Boolean);
var
  Dialog: TdlgLogin;
begin
  Dialog := TdlgLogin.Create(Application);
  try
    Dialog.DoUnlock(ExitApp);
  finally
    Dialog.Free;
  end;
end;

{ TdlgLogin }

procedure TdlgLogin.FormCreate(Sender: TObject);
var
  MyStream:TMemoryStream;
  verFileName:string;
  sVer,sversion:string;
  F:file;
  cArr: array[0..100] of Char;
  num: Integer;
begin
  RegisterModule(Self);
  //CnCpuID := TCnCpuID.Create;
  //CnCpuID.CPUIdFormat := ifDashed;
  //machineCode := CnCpuID.FirstCPUId;
  WVStationReg.FieldByName('机器码').Data.SetString(MacAddress);
  WVStationReg.FieldByName('IP地址').Data.SetString(getIpAddr);
  WVRStationReg.SendCommand;
  //检测版本
  if verIfTip=0 then
    Exit;
  verFileName := sAppPath+'version';
  if FileExists(verFileName) then
    DeleteFile(verFileName);
  try
    MyStream:=TMemoryStream.Create;
   // verFileName
    try
      idhtp1.Get(verHttpPath,MyStream);
    except
      on e:exception do
      begin
        Context.GetDialogSystem.Showmessage('下载版本信息失败，不能比较程序版本，请检查配置文件是否正确--'+e.Message);
        Exit;
      end;
    end;
    MyStream.SaveToFile(verFileName);
    try
      AssignFile(F,verFileName);
      Reset(F,1);
      BlockRead(F,cArr,Length(cArr),num);
      sversion :=Copy(cArr,Pos('=',cArr)+1,Length(cArr));
      sVer :=Copy(sversion,1,11); //固定长度，不能修改
      CloseFile(F);
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage('读取文件错误-'+e.Message);
        Exit;
      end;
    end;
    if sVer='' then
    begin
      Context.GetDialogSystem.ShowMessage('获取服务器版本文件内容为空，请确认服务器版本信息是否正确！');
      Exit;
    end;

    if Trim(sVer)<>Trim(yktVersion) then
      Context.GetDialogSystem.ShowWarning('服务器版本为:'+sver+',现使用版本为：'+yktversion+#13#10 +'请先更新版本然后再使用，否则业务可能无法正常操作！');
  finally
    MyStream.Free;
  end;
end;

procedure TdlgLogin.Execute(var ExitApp: Boolean);
var
  ConfigSystem: IConfigSystem;
  node_id: string;
begin
  Caption := '系统登录';
  WorkView.Reset;
  WorkView.FieldByName(DepartFieldName).Data.SetString(Context.ParamData(svDepartNoName).AsString);
  WorkView.FieldByName(DepartNameFieldName).Data.SetString(Context.ParamData(svDepartNameName).AsString);
  WorkView.FieldByName(OperatorFieldName).Data.SetString(
    Context.GetConfigSystem.ReadString(
    ccAllUsers,
    Format(ckUser, [Context.GetParamValue(svDepartNoName)]),
    cdUser));

  WorkView.FieldByName('接收信息标记').Data.SetString(Context.GetConfigSystem.ReadString(ccServer, 'RecieveInfo','1'));

  WorkView.FieldByName('接收回报标记').Data.SetString(Context.GetConfigSystem.ReadString(ccServer, 'RecievePush','0'));

  WorkView.FieldByName('应用程序标识').Data.SetString('B');

  WSACleanup;
  WorkView.FieldByName('当前ip地址').Data.SetString(getIpAddr);
  WorkView.FieldByName('机器码').Data.SetString(MacAddress);

  //wlj 20031114 取通信平台节点号
  ConfigSystem := Context.GetConfigSystem;
  Node_ID := ConfigSystem.ReadString(ccServer, 'Node_ID', '0');
  WorkView.FieldByName('通信平台节点号').Data.SetString(Node_ID);

  edOperator.Enabled := True;
  btnOk.OnClick := LoginClick;
  ExitApp := ShowModal = mrAbort;
end;

procedure TdlgLogin.DoUnLock(var ExitApp: Boolean);
begin
  Caption := '解除锁定';
  WorkView.FieldByName(OperatorFieldName).DefaultValue :=
    Context.GetParamValue(svOperatorNoName);
  WorkView.Reset;
  WorkView.FieldByName(DepartFieldName).Data.SetString(Context.ParamData(svDepartNoName).AsString);
  WorkView.FieldByName(DepartNameFieldName).Data.SetString(Context.ParamData(svDepartNameName).AsString);
  edOperator.Enabled := False;
  btnOk.OnClick := UnLockClick;
  ExitApp := ShowModal <> mrOK;
end;

procedure TdlgLogin.LoginClick(Sender: TObject);
var
  HasException: Boolean;
  dataset: TDataset;
  OperName: string;
  TmpStr: string;
  operPwd:String;
  dateVer:string;
begin
  HasException := False;
  try
    Context.GetDialogSystem.ShowWaiting(SWait);
    try
      operPwd := encOperPwd(Trim(edOperator.Text),Trim(edtPwd.Text));
      if operPwd = '' then
        Exit;
      WorkView.FieldByName('密码').Data.SetString(operPwd);
      MainRequest.SendCommand;
      if WorkView.fieldByname('返回码').Data.AsInteger <> 0 then
        exit
      else
      begin
        smartCardPwd:=WorkView.fieldbyname('密钥').Data.AsString;
        scSiteNo := WorkView.fieldbyname('站点号').Data.AsString;
        try
          backVer := WorkView.fieldbyname('后台版本').Data.AsString;
        except
          backVer := '';
        end;
        {
        if backVer='' then
        begin
          Context.GetDialogSystem.ShowError('没有取到后台版本号，系统存在风险，请和开发人员联系！');
        end
        else
        begin
          dateVer := Copy(backVer,Length(backVer)-8,8);
          try
            if StrToInt(dateVer)<0 then
              //
          except
            Context.GetDialogSystem.ShowError('后台版本号错误，系统存在风险，请和开发人员联系！');
            Exit;
          end;
          if dateVer<buSmlVer then
          begin
            Context.GetDialogSystem.ShowError('后台版本号低于最低版本，必须升级后台才能使用该前台！');
            Exit;
          end;
          if (dateVer>=buSmlVer) and (dateVer<buCurrVer) then
            Context.GetDialogSystem.ShowMessage('后台版本号低于当前版本，系统存在风险，建议升级后台！');
          
        end;
        }
        scOperNo := Trim(edOperator.Text);
        sAppPath := ExtractFilePath(Application.ExeName);
        sPreAppPath :=Copy(sAppPath,1,Length(sAppPath)-4);
        //判断安装目录是否有中文，如果有则提示退出
        if ifDebug=0 then
        begin
          if Length(widestring(sAppPath))<>Length(sAppPath) then
          begin
            Context.GetDialogSystem.ShowMessage('安装目录含有中文，请退出重新安装到英文目录！');
            Exit;
          end;
        end;
        Context.ParamData(svBatchNoName).SetInteger(TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject).fieldbyname('lbank_acc_type').AsInteger);
        Context.ParamData(svFuncNoName).SetInteger(TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject).fieldbyname('lvol12').AsInteger);
        TmpStr :=
          TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject).fieldbyname('vsvarstr0').AsString +
          TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject).fieldbyname('vsvarstr1').AsString +
          TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject).fieldbyname('vsvarstr2').AsString +
          TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject).fieldbyname('vsvarstr3').AsString;
        Context.ParamData(svOperatorMenuAuthName).SetString(TmpStr)
      end;
    finally
      Context.GetDialogSystem.CloseWaiting;
    end;
  except
    on E: Exception do
    begin
      HasException := True;
      Context.GetExceptionHandler.HandleException(E);
    end;
  end;

  //更新相关日期值
  try
    wvrSysDate.SendCommand;
    sysDate := wvSysDate.fieldbyname('系统日期').Data.AsString;
    accountDate := wvSysDate.fieldbyname('结算日期').Data.AsString;
    accountTime := wvSysDate.fieldbyname('系统时间').Data.AsString;
    bAccountDate := wvSysDate.fieldbyname('前结算日期').Data.AsString;
    eaccountDate := wvSysDate.fieldbyname('后结算日期').Data.AsString;
  except
    on ex:Exception do
      Context.GetDialogSystem.ShowMessage(ex.Message);
  end;
  with WorkView.FieldByName(LoginStatusFieldName).Data do
    if not IsEmpty and (AsBoolean = True) then
    begin
      // wlj 20031114 登录成功 取姓名信息
      try
        dataset := TDataset(WorkView.FieldByName('查询结果集').Data.AsObject);

        if (dataset <> nil) then
        begin
          dataset.First;
          // 修改操作员姓名
          OperName := Dataset.Fields.FieldByName('scust_limit2').AsString;
          Context.ParamData(svOperatorNameName).SetString(OperName);
        end;

        ModalResult := mrOk; //登录成功

        cpuWaterPrice1 := getWaterPrice(157);
        cpuWaterPrice2 := getWaterPrice(158);
        cpuWaterPrice3 := getWaterPrice(159);
        //取水控钱包，用来初始化
        getWaterStrs;
      except //wlj 20031114 取信息有可能失败
        Context.GetDialogSystem.ShowWarning('取登录信息失败!');
      end;
    end
    else
    begin
      if not HasException then
        Context.GetDialogSystem.ShowError(SLoginError);
      SelectFirst;
    end;

end;

procedure TdlgLogin.UnLockClick(Sender: TObject);
var
  operCode:string;
  operPwd:string;
begin
  operCode := edOperator.Text;
  operPwd := encOperPwd(Trim(edOperator.Text),Trim(edtPwd.Text));
  if operPwd=Context.GetParamValue(svOperatorPasswordName) then//WorkView.FieldByName(PasswordFieldName).Data.AsString =
    ModalResult := mrOK
  else
  begin
    Context.GetDialogSystem.ShowError(SUnlockError);
    //ShowMsg(SUnlockError,Sykt,'',SB_OK,0,-1);
    SelectFirst;
  end;
end;

procedure TdlgLogin.btnCloseClick(Sender: TObject);
begin
  ModalResult := mrAbort;
end;

procedure TdlgLogin.FormActivate(Sender: TObject);
begin
  SelectFirst;
end;

procedure TdlgLogin.edtPwdKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
    btnOk.Click;

end;

{
function TdlgLogin.KillExe(strFileName: string): Boolean;
var  
   ProcessID:  THandle;
   FHandle:  THandle;
begin
  ProcessID  :=  MyFun_GetProcessID(strFileName);
  FHandle  :=  OpenProcess(PROCESS_ALL_ACCESS ,False,ProcessID);
  Result  :=  TerminateProcess(FHandle,0);
end;


function TdlgLogin.MyFun_GetProcessID(ProcessName: string): Cardinal;
var  
   FSnapshotHandle:  THandle;  
   FProcessEntry32:  TProcessEntry32;  
   Ret:  Boolean;  
   TmpProcessName:  string;  
   TmpProcessID:  DWORD;  
begin
    //如果没有找到
   TmpProcessID  :=  0;
   //创建系统快照  
   FSnapshotHandle  :=  CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,  0);  
   //先初始化  FProcessEntry32  的大小  
   FProcessEntry32.dwSize  :=  SizeOf(FProcessEntry32);  
   Ret  :=  Process32First(FSnapshotHandle,  FProcessEntry32);  
   //循环枚举出系统开启的所有进程，找出“ProcessName”所指定的进程  
   while  Ret  do  
   begin  
       TmpProcessName  :=  ExtractFileName(FProcessEntry32.szExeFile);  
       if  TmpProcessName  =  ProcessName  then  
       begin  
           TmpProcessID  :=  FProcessEntry32.th32ProcessID;  
           Break;  
       end;  
       Ret  :=  Process32Next(FSnapshotHandle,  FProcessEntry32);  
   end;  
   CloseHandle(FSnapshotHandle);  
   Result  :=  TmpProcessID;
   end;
}
function TdlgLogin.getIpAddr: String;
type
  TaPInAddr = array[0..10] of PInAddr;
  PaPInAddr = ^TaPInAddr;

var
  phe: PHostEnt;
  pptr: PaPInAddr;
  Buffer: array[0..63] of char;
  I: Integer;
  GInitData: TWSADATA;
  res_ip: string;
begin
  WSAStartup($101, GInitData);
  Res_ip := '';
  GetHostName(Buffer, SizeOf(Buffer));
  phe := GetHostByName(buffer);
  if phe = nil then
    Exit;
  pptr := PaPInAddr(Phe^.h_addr_list);

  I := 0;
  while pptr^[I] <> nil do
  begin
    res_ip := StrPas(inet_ntoa(pptr^[I]^));
    Inc(I);
  end;
  Result := res_ip;
end;

function TdlgLogin.MacAddress: string;
var 
  Lib: Cardinal; 
  Func: function(GUID: PGUID): Longint; stdcall; 
  GUID1, GUID2: TGUID; 
begin 
  Result := ''; 
  Lib := LoadLibrary('rpcrt4.dll'); 
  if Lib <> 0 then 
  begin 
    if Win32Platform <>VER_PLATFORM_WIN32_NT then 
      @Func := GetProcAddress(Lib, 'UuidCreate') 
      else @Func := GetProcAddress(Lib, 'UuidCreateSequential'); 
    if Assigned(Func) then 
    begin 
      if (Func(@GUID1) = 0) and 
        (Func(@GUID2) = 0) and 
        (GUID1.D4[2] = GUID2.D4[2]) and 
        (GUID1.D4[3] = GUID2.D4[3]) and 
        (GUID1.D4[4] = GUID2.D4[4]) and 
        (GUID1.D4[5] = GUID2.D4[5]) and 
        (GUID1.D4[6] = GUID2.D4[6]) and 
        (GUID1.D4[7] = GUID2.D4[7]) then 
      begin 
        Result := 
         IntToHex(GUID1.D4[2], 2) + '-' + 
         IntToHex(GUID1.D4[3], 2) + '-' + 
         IntToHex(GUID1.D4[4], 2) + '-' + 
         IntToHex(GUID1.D4[5], 2) + '-' + 
         IntToHex(GUID1.D4[6], 2) + '-' + 
         IntToHex(GUID1.D4[7], 2); 
      end; 
    end; 
    FreeLibrary(Lib); 
  end;
end;

function TdlgLogin.getWaterPrice(price: Integer): Integer;
var
  waterPrice:Integer;
begin

  WorkView1.FieldByName('查询.参数标志').Data.SetInteger(price);
  try
    QueryRequest.SendCommand;
    waterPrice := (WorkView1.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('scard0').AsInteger;
    Result := waterPrice;
  except
    Result := 0;
  end;
end;

procedure TdlgLogin.getWaterStrs;
var
  tempData:TDataSet;
  //ss:TStrings;
begin
  waterStrings := nil;
  wvWaterStr.FieldByName('字典码').Data.SetInteger(-26);
  try
    wvrWaterStr.SendCommand;
    if wvWaterStr.FieldByName('返回码').Data.AsString='0' then
    begin
      tempData := wvWaterStr.FieldByName('查询结果集').Data.AsObject as TDataSet;
      waterStrings:=TStringList.Create;
      if tempData.RecordCount>0 then
      begin
        tempData.First;
        while not tempData.Eof do
        begin
          waterStrings.Add(tempData.fieldbyname('sname').AsString);
          tempData.Next;
        end;
      end;
    end;
  except
    
  end;
end;

end.
