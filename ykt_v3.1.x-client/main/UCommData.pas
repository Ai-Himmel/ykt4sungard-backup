unit UCommData;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UCommData
   <What>提供常用的命令对象的实现（命令实现对象）
   <Written By> Huang YanLai (黄燕来)
   <History>
   0.1 (2001/09/27) - 增加了一个数据集（DatasetForInit），为初始化使用。因为初始化的时候是多线程的
**********************************************}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Db, BDAImpEx, KCDataAccess, WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  WVCommands,
  WorkViews, WVCmdReq, KSDataDictionary, KSEdits, Contnrs, KSFrameWorks,
  KSCustomers;

type
  TdmCommData = class(TDataModule, IKSModule)
    ctLogin: TWVCommandTypeInfo;
    cpLogin: TKCWVProcessor;
    Dataset: TKCDataset;
    cpLoginTest: TWVProcessor;
    ctInitDataDictionary: TWVCommandTypeInfo;
    cpInitDataDictionary: TKCWVProcessor;
    WorkView: TWorkView;
    rqInitDataDictionary: TWVRequest;
    ctInitSystemParams: TWVCommandTypeInfo;
    cpInitSystemParams: TKCWVProcessor;
    rqInitSystemParams: TWVRequest;
    ctGetDataDictionary: TWVCommandTypeInfo;
    cpGetDataDictionary: TKCWVProcessor;
    rqGetDataDictionary: TWVRequest;
    ctGetDataDictionaryCategory: TWVCommandTypeInfo;
    cpGetDataDictionaryCategory: TKCWVProcessor;
    rqGetDataDictionaryCategory: TWVRequest;
    cpGetBankAccounts: TKCWVQuery;
    cpGetEmpInfo: TKCWVQuery;
    ctDoubleCheck: TWVCommandTypeInfo;
    cpDoubleCheck: TKCWVProcessor;
    DatasetForInit: TKCDataset;
    cpQueryStationAuth: TKCWVQuery;
    ctLogout: TWVCommandTypeInfo;
    cpLogout: TKCWVProcessor;
    cpQueyBranch: TKCWVQuery;
    cpInitQueyBranch: TKCWVQuery;
    ctGetInfo: TWVCommandTypeInfo;
    cpGetInfo: TKCWVQuery;
    DataSource1: TDataSource;
    AccountInputMethods: TAccountInputMethods;
    ctQrySettleTradePara: TWVCommandTypeInfo;
    ctQhLogin: TWVCommandTypeInfo;
    cpQhLogin: TKCWVProcessor;
    cpQhLogOut: TKCWVProcessor;
    cpGetSystemDate: TKCWVProcessor;
    WVCommandTypeInfo1: TWVCommandTypeInfo;
    ctGetSystemDate: TWVCommandTypeInfo;
    rqGetSystemDate: TWVRequest;
    cpPLogOut: TKCWVProcessor;
    ctPLogOut: TWVCommandTypeInfo;
    ctQueryOperator: TWVCommandTypeInfo;
    cqQueryOperator: TKCWVQuery;
    ctqPLogOut: TWVCommandTypeInfo;
    cqPLogOut: TKCWVQuery;
    WVStationReg: TWVCommandTypeInfo;
    cqStationReg: TKCWVProcessor;
    cqQGlobeKey: TWVCommandTypeInfo;
    kcQGlobeKey: TKCWVQuery;
    kcWaterStr: TKCWVQuery;
    cqWaterStr: TWVCommandTypeInfo;
    procedure cpLoginTestProcess(Command: TWVCommand);
    procedure cpLoginBindOutput(Dataset: TKCDataset; Command: TWVCommand);
    procedure CheckDataValid(Request: TWVRequest;
      Command: TWVCommand);
    procedure AccountInputMethodsReinput(Sender: TKSAccountEdit;
      var Passed: Boolean);
    procedure AccountInputMethodsInputPassword(Sender: TKSAccountEdit;
      var Passed: Boolean);
    procedure AccountInputMethodsSelectCustomer(Sender: TKSAccountEdit;
      Customers: TObjectList; var SelectedCustomer: TKSAbstractCustomer;
      var Passed: Boolean);
    procedure AccountInputMethodsGetCustomers(Sender: TKSAccountEdit;
      Customers: TObjectList);
    procedure AccountInputMethodsGetMainAccounts(Sender: TKSAccountEdit;
      MainAccounts: TObjectList);
    procedure AccountInputMethodsGetMoneyAccounts(Sender: TKSAccountEdit;
      MoneyAccounts: TObjectList);
    procedure AccountInputMethodsAdvancedSelect(Sender: TKSAccountEdit;
      var Selected: Boolean; var CustomerNo: string);
    procedure DataModuleCreate(Sender: TObject);
    procedure DataModuleDestroy(Sender: TObject);
    procedure AccountInputMethodsException(Sender: TObject);
    procedure AccountInputMethodsWarningCustomerStatus(Sender: TObject);
    procedure AccountInputMethodsShowEditHint(Sender: TObject);
    procedure AccountInputMethodsMethods5FormatAndValidAccount(
      Sender: TAccountInputMethod; var Account: string;
      var Valid: Boolean);
    procedure cpQhLogOutBindOutput(Dataset: TKCDataset;
      Command: TWVCommand);
    procedure rqGetSystemDateAfterExec(Request: TWVRequest;
      Command: TWVCommand);
  private
    { Private declarations }
    FReady: Boolean;
    procedure ReadDataDictionary(Dataset: TDataset);
    procedure ReadSystemParams(Dataset: TDataset);
    procedure GetDataDictionary(IdObjects: TIdObjectList);
    procedure GetBranchDirectory(IdObjects: TIdObjectList);
    procedure ReadOneDataDictionary(Dataset: TDataset; IdObjects:
      TIdObjectList);
    procedure ReadOneDataDictionary2(Dataset: TDataset; IdObjects:
      TIdObjectList); //和GetDataDictionary2配套使用
    procedure GetDictionaryCategory(IdObjects: TIdObjectList);
    procedure CreateOtherDataDictionary;
    procedure GetBusinessFlags(IdObjects: TIdObjectList);
    procedure HandleException;
    procedure SetupInputMethods;
    function GetExistDataEntryName(SourceSL: TStringList; NowDataEntry:
      Integer): string;

  public
    { Public declarations }
//    procedure GetBranchInfos;
    procedure Start;
    procedure ShutDown;
  end;

var
  dmCommData: TdmCommData;

implementation

uses KSClientConsts, KSFrameWorkUtils, StdCtrls, WVCtrls, SafeCode, DataTypes,
  LogFile, UInputTextDlg, { USelCustDlg,} KSComCmdDefs, UAdSelCust,
  KsBranchTree,
  UContext;

{$R *.DFM}

const
  DepartParam = '营业部';
  OperatorParam = '操作员';
  PasswordParam = '密码';
  SReturnDataset = '查询结果集';
  //DatasetParam = '数据集';

procedure GetIdObjects(IdObjects: TIdObjectList);
begin
  // 根据界面需要，读取其他数据字典
  dmCommData.GetDataDictionary(IdObjects);
end;

{procedure GetIdObjects2(IdObjects : TIdObjectList);
begin
  // 根据界面需要，读取其他数据字典
  dmCommData.GetDataDictionary2(IdObjects);
end;  }

{ TdmCommData }

procedure TdmCommData.DataModuleCreate(Sender: TObject);
begin
  SysModule1 := Self;
  FReady := False;
end;

procedure TdmCommData.DataModuleDestroy(Sender: TObject);
begin
  WriteLog('dmCommData Destroying...', lcConstruct_Destroy);
  SysModule1 := nil;
  WriteLog('dmCommData Destroyed', lcConstruct_Destroy);
end;

procedure TdmCommData.cpLoginTestProcess(Command: TWVCommand);
begin
  Command.ParamData(svOperatorNoName).AsString :=
    Command.ParamData(OperatorParam).AsString;

  Command.ParamData(svLoginStatusName).SetBoolean(Command.ParamData(PasswordParam).AsString = '123');
end;

procedure TdmCommData.cpLoginBindOutput(Dataset: TKCDataset;
  Command: TWVCommand);
begin
  CheckCommandReturnValue(Command);
  Context.ParamData(svOperatorNoName).SetString(Command.ParamData(OperatorParam).AsString);
  Context.ParamData(svOperatorPasswordName).SetString(Command.ParamData(PasswordParam).AsString);
  Command.ParamData(svLoginStatusName).SetBoolean(True);
end;

procedure TdmCommData.CheckDataValid(Request: TWVRequest;
  Command: TWVCommand);
begin
  CheckCommandReturnValue(Command);
end;
{
procedure TdmCommData.Start;
begin
  try
    RegisterModule(Self);
  except
    HandleException;
  end;
  try
    // 初始化数据字典
    WriteLog('请求初始化数据字典',lcKSClientStart);
    rqInitDataDictionary.SendCommand;
    WriteLog('读取初始化数据字典',lcKSClientStart);
    ReadDataDictionary(Dataset);
  except
    HandleException;
  end;
  try
    // 初始化系统参数
    WriteLog('初始化系统参数',lcKSClientStart);
    rqInitSystemParams.SendCommand;
    WriteLog('读取初始化系统参数',lcKSClientStart);
    ReadSystemParams(Dataset);
  except
    HandleException;
  end;
  try
    // 其他数据字典
    CreateOtherDataDictionary;
    // 设置输入方式
    SetupInputMethods;
  except
    HandleException;
  end;
end;
}

procedure TdmCommData.Start;
begin
  InfoAdmin := TInfoAdmin.Create;
  RegisterModule(Self);

  // 初始化数据字典
  WriteLog('请求初始化数据字典', lcKSClientStart);
  DatasetForInit.Close;
  rqInitDataDictionary.SendCommand;
  WriteLog('读取初始化数据字典', lcKSClientStart);
  Assert(DatasetForInit.Active);
  ReadDataDictionary(DatasetForInit);

  // 初始化系统参数
  {
  WriteLog('初始化系统参数',lcKSClientStart);
  DatasetForInit.Close;
  rqInitSystemParams.SendCommand;
  WriteLog('读取初始化系统参数',lcKSClientStart);
  Assert(DatasetForInit.Active);
  ReadSystemParams(DatasetForInit);
  }

  //  结算管理不做初始化营业部层次结构
  // 初始化营业部层次结构
  //WriteLog('初始化营业部层次结构',lcKSClientStart);

  //ComCmdDefinition.GetBranchInfoAdmin;

  //ComCmdDefinition.NeedBranchs;

  // 其他数据字典
  CreateOtherDataDictionary;

  // 设置输入方式
  //SetupInputMethods;

  FReady := True;
end;

procedure TdmCommData.ReadDataDictionary(Dataset: TDataset);
var
  CategoryField, CodeField, NameField: TField;
  LastCategory: Integer;
  IdObjectList: TIdObjectList;
begin
  if Dataset <> nil then
  begin
    CategoryField := Dataset.FieldByName('lcert_code');
    CodeField := Dataset.FieldByName('sname');
    //wlj 20040219 修改cpack sdate0为sname
    NameField := Dataset.FieldByName('sall_name');
    LastCategory := deNotUsed;
    Dataset.First;
    IdObjectList := nil;
    while not Dataset.Eof do
    begin
      if CategoryField.AsInteger <> LastCategory then
      begin
        LastCategory := CategoryField.AsInteger;
        IdObjectList := TIdObjectList.Create(LastCategory, CurrentDepartmentNo);
      end;
      Assert(IdObjectList <> nil);
      //  WriteLog(Format('DataDictionary:%d.%s.%s',[IdObjectList.DataEntry,CodeField.AsString,NameField.AsString]),lcKSClientStart);
      IdObjectList.Add(TIdObject.Create(CodeField.AsString,
        NameField.AsString));
      Dataset.Next;
    end;
  end;
end;

procedure TdmCommData.ReadSystemParams(Dataset: TDataset);
var
  CodeField, NameField: TField;
  IdObjectList: TIdObjectList;
begin
  if Dataset <> nil then
  begin
    CodeField := Dataset.FieldByName('lcert_code');
    NameField := Dataset.FieldByName('sname');
    IdObjectList := TIdObjectList.Create(deSystemParams, CurrentDepartmentNo);
    Dataset.First;
    while not Dataset.Eof do
    begin
      IdObjectList.Add(TIdObject.Create(CodeField.AsString,
        NameField.AsString));
      WriteLog(Format('SystemParam:%s.%s', [CodeField.AsString,
        NameField.AsString]), lcKSClientStart);
      Dataset.Next;
    end;
  end;
end;

procedure TdmCommData.GetDataDictionary(IdObjects: TIdObjectList);
var
  tempStr: string;
  I: Integer;
begin
  Assert(FReady);
  try
    case IdObjects.DataEntry of
      deNotUsed: ;
      deDictionaryCategory: GetDictionaryCategory(IdObjects);
      // wsn 20040916 校园一卡通框架不需要
      {deBusinessFlag : GetBusinessFlags(IdObjects);
      deDepart:GetBranchDirectory(IdObjects);

      deOperator_CustNO :
      begin
        dmContext.DoBaseInitAferLogin(True);  //更新客户号
        IdObjects := GetIdObjectList(IdObjects.DataEntry,CurrentDepartmentNo);
      end;
      (deExchange_Seat - 100)..deExchange_Kind :
      begin
        tempStr := GetExistDataEntryName(
          FindStringListFormObjectList(UIShareObjList,SLName_Exchange_Kind),
          IdObjects.DataEntry);
        dmContext.DoBaseInitAferLogin(False); //更新交易所对应的品种，席位。
        try
          I := StrToInt(FindStringListFormObjectList(UIShareObjList,SLName_Exchange_Kind).Values[tempStr]);
        except
          IdObjects := nil;
          Exit;
        end;
        IdObjects := GetIdObjectList(I,CurrentDepartmentNo);
      end; }
    else
      begin
        // 请求数据字典
        WriteLog('请求数据字典', lcKSClientStart);

        WorkView.FieldByName('数据字典条目').Data.SetInteger(IdObjects.DataEntry);
        //Assert(IdObjects.Department<>'');
        //WorkView.FieldByName('查询营业部').Data.SetString(IdObjects.Department);
        rqGetDataDictionary.SendCommand;
        // 读取数据字典
        WriteLog('读取数据字典', lcKSClientStart);
        ReadOneDataDictionary(Dataset, IdObjects);
      end;
    end;
  except
    on E: Exception do
    begin
      Context.GetExceptionHandler.HandleException(E);
      IdObjects.UpdateTime := GetTickCount;
      IdObjects.Valid := False;
    end;
  end;
end;

procedure TdmCommData.GetBranchDirectory(IdObjects: TIdObjectList);
begin
  Assert(FReady);
  try
    // 请求数据字典
    WriteLog('请求数据字典', lcKSClientStart);
    WorkView.FieldByName('条目代码').Data.SetInteger(IdObjects.DataEntry);

    DatasetForInit.Close;
    rqInitDataDictionary.SendCommand;
    Assert(DatasetForInit.Active);

    // 读取数据字典
    WriteLog('读取数据字典', lcKSClientStart);
    ReadOneDataDictionary2(DatasetForInit, IdObjects);
  except
    on E: Exception do
    begin
      Context.GetExceptionHandler.HandleException(E);
      IdObjects.UpdateTime := GetTickCount;
      IdObjects.Valid := False;
    end;
  end;
end;

procedure TdmCommData.ReadOneDataDictionary(Dataset: TDataset;
  IdObjects: TIdObjectList);
var
  CategoryField, CodeField, NameField: TField;
  ItemsList : TStrings;
  ItemsArray : array of TIdObject;
  i : Integer;
  SortFile : TextFile;
  str : string;
  
  function CompareToNode(s,d: TIdObject):integer;
  var s_val,d_val : string;
    i : Integer;
  begin
    s_val := s.Name;
    d_val := d.Name;
    Result := StrIComp(PChar(s_val),PChar(d_val));
  end;
  procedure QuickSortNodeData(lo,hi:Integer);
  var
    lo_tmp,hi_tmp,anchorIndex : Integer;
    tmp,anchor : TIdObject;
  begin
    //showmessage(inttostr((lo + hi) div 2 + 1));
    anchorIndex := (lo + hi) div 2 + 1;
    if ((anchorIndex < lo) or (anchorIndex >= hi)) then
      Exit;
    anchor := ItemsArray[anchorIndex];

    lo_tmp := lo;
    hi_tmp := hi;
    while (lo_tmp <= hi_tmp) do
    begin
      while ((CompareToNode(ItemsArray[lo_tmp],anchor) < 0)
        and (lo_tmp < hi))do
        Inc(lo_tmp);
      while ((CompareToNode(ItemsArray[hi_tmp],anchor) > 0 )
        and (hi_tmp > lo)) do
        Dec(hi_tmp);
      if ( lo_tmp <= hi_tmp ) then
      begin
        //ShowMessage(Format('%s - %s',
        //  [ItemsList[lo_tmp].Name,ItemsList[hi_tmp].Name]));
        tmp := ItemsArray[lo_tmp];
        ItemsArray[lo_tmp] := ItemsArray[hi_tmp];
        ItemsArray[hi_tmp] := tmp;
        Inc(lo_tmp);
        Dec(hi_tmp);
      end;
    end;
    if ( lo_tmp < hi ) then
      QuickSortNodeData(lo_tmp,hi);
    if ( hi_tmp > lo ) then
      QuickSortNodeData(lo,hi_tmp);
  end;
begin
  if Dataset <> nil then
  begin
    ItemsList := TStringList.Create;
    try
      CategoryField := Dataset.FieldByName('lcert_code');
      CodeField := Dataset.FieldByName('sname');
      NameField := Dataset.FieldByName('sall_name');
      Dataset.First;
      while not Dataset.Eof do
      begin
        if CategoryField.AsInteger <> IdObjects.DataEntry then
          Break;
        ItemsList.AddObject(CodeField.AsString,
          TIdObject.Create(CodeField.AsString, Trim(NameField.AsString)));
        Dataset.Next;
      end;
    except
      WriteLog(Format('%d-%s', [IdObjects.DataEntry, SDataDictionaryIsNull]),
        lcKsClientPreQuery);
    end;
    //
    // 如果没有找到返回
    if( ItemsList.Count = 0 ) then
    begin
      ItemsList.Free;
      Exit;
    end;
    SetLength(ItemsArray,ItemsList.Count);
    for i := 0 to ItemsList.Count - 1 do
    begin
      ItemsArray[i] := TIdObject(ItemsList.Objects[i]);
    end;
    if(IdObjects.DataEntry = -22) or(IdObjects.DataEntry = -23) then
    begin
      //AssignFile(SortFile,'sort' + IntToStr(IdObjects.DataEntry)+'.txt');
      //Rewrite(SortFile);
      QuickSortNodeData(0,Length(ItemsArray) - 1);
    end;
    for i := 0 to Length(ItemsArray) - 1  do
    begin
      IdObjects.Add(ItemsArray[i]);
      //if(IdObjects.DataEntry = -22) or(IdObjects.DataEntry = -23) then
      //  Writeln(SortFile,ItemsArray[i].Name);
    end;
    {
    if(IdObjects.DataEntry = -22) or(IdObjects.DataEntry = -23) then
    begin
      CloseFile(SortFile);
    end;
    }
    ItemsList.Free;
    SetLength(ItemsArray,0);
  end;
end;

procedure TdmCommData.ReadOneDataDictionary2(Dataset: TDataset;
  IdObjects: TIdObjectList);
var
  CategoryField, CodeField, NameField: TField;
begin
  if Dataset <> nil then
  begin
    CategoryField := Dataset.FieldByName('lcert_code');
    CodeField := Dataset.FieldByName('sname');
    //wlj 20040219 将原来用的cpack字段从sdate0改为sname
    NameField := Dataset.FieldByName('sall_name');

    Dataset.First;
    while not Dataset.Eof do
    begin
      if CategoryField.AsInteger <> IdObjects.DataEntry then
      begin
        continue;
        Dataset.Next;
      end;
      IdObjects.Add(TIdObject.Create(CodeField.AsString, NameField.AsString));
      Break;
    end;
  end;
end;

procedure TdmCommData.GetDictionaryCategory(IdObjects: TIdObjectList);
var
  CategoryField, NameField, CanEditField, LengthField, DataTypeField: TField;
  AMaintainMethod: TMaintainMethod;
  MaintainValue: string;
begin
  // 请求数据字典条目
  WriteLog('请求数据字典条目', lcKSClientStart);
  WorkView.FieldByName('数据字典条目').Data.SetInteger(deNotUsed);
  rqGetDataDictionaryCategory.SendCommand;
  // 读取数据字典条目
  WriteLog('读取数据字典条目', lcKSClientStart);
  CategoryField := Dataset.FieldByName('lcert_code');
  NameField := Dataset.FieldByName('sname');
  CanEditField := Dataset.FieldByName('sstatus0');
  LengthField := Dataset.FieldByName('lvol1');
  DataTypeField := Dataset.FieldByName('sstatus1');
  Dataset.First;
  while not Dataset.Eof do
  begin
    MaintainValue := CanEditField.AsString;
    if (MaintainValue = '0') then
      AMaintainMethod := mmReadOnly
    else if MaintainValue = '1' then
      AMaintainMethod := mmCenter
    else if (MaintainValue = 'H') then
      AMaintainMethod := mmHide
    else
      AMaintainMethod := mmDepartment;
    //if MaintainValue<>'H' then
    IdObjects.Add(
      TDataDictionaryCategory.Create(
        CategoryField.AsString,
        NameField.AsString,
        AMaintainMethod,
        LengthField.AsInteger,
        DataTypeField.AsString = '1'
        ));
    Dataset.Next;
  end;
end;

procedure TdmCommData.AccountInputMethodsReinput(Sender: TKSAccountEdit;
  var Passed: Boolean);
var
  ReinputText: string;
begin
  ReinputText := '';
  Passed := KSInputText('请操作员重新输入账号', '账号', False, False,
    ReinputText);
  Assert(Sender.CurrentInputMethod <> nil);
  Sender.CurrentInputMethod.FormatAndValidAccount(ReinputText);
  if Passed and (ReinputText <> Sender.Text) then
  begin
    Passed := False;
    TKSContext(Context).GetDialogSystem.ShowError('重新输入的账号与原来输入的账号不符！');
  end;
end;

type
  TKSAccountEditAccess = class(TKSAccountEdit);

procedure TdmCommData.AccountInputMethodsInputPassword(
  Sender: TKSAccountEdit; var Passed: Boolean);
var
  InputPassword: string;
  PasswordCaption: string;
begin
  // wsn 20040916 校园一卡通框架不需要客户概念
  {  case Sender.PasswordType of
      ptTransactionPassword : PasswordCaption := STransactionPassword;
      ptFundPassword        : PasswordCaption := SFundPassword;
    else
      PasswordCaption := SAllPassword;
    end;
    repeat
      Passed := KSInputText('请客户输入密码',PasswordCaption,True,True,InputPassword);
      if Passed then
      begin
        WorkView.FieldByName('客户号').Data.SetString(Sender.Customer.CustomerNo);
        WorkView.FieldByName('客户密码').Data.SetString(InputPassword);
        WorkView.FieldByName('验证方式').Data.SetInteger(Sender.PasswordType);
        rqCheckCustomerPassword.SendCommand;
        TKSAccountEditAccess(Sender).SetCustomerPassword(InputPassword);
        //Passed := True;
        Break;
      end;
    until not Passed;  }
end;

procedure TdmCommData.AccountInputMethodsSelectCustomer(
  Sender: TKSAccountEdit; Customers: TObjectList;
  var SelectedCustomer: TKSAbstractCustomer; var Passed: Boolean);
begin
  // Passed := KSSelectCustomers(Customers,SelectedCustomer);
end;

procedure TdmCommData.AccountInputMethodsGetCustomers(
  Sender: TKSAccountEdit; Customers: TObjectList);
begin
  {  CheckObject(Sender.CurrentInputMethod,'Error : CurrentInputMethod is nil');
    Customers.Clear;
    WorkView.FieldByName('检验帐号类型').Data.SetString(Sender.CurrentInputMethod.MethodChar);
    WorkView.FieldByName('检验帐号').Data.SetString(Sender.Text);
    rqGetCustomers.SendCommand;
    GetCustomersFromDataset(TDataset(WorkView.FieldByName(SReturnDataset).Data.AsObject),Customers);
    WorkView.FieldByName(SReturnDataset).Data.Clear;
    }
end;

procedure TdmCommData.AccountInputMethodsGetMainAccounts(
  Sender: TKSAccountEdit; MainAccounts: TObjectList);
begin
  CheckObject(Sender.Customer, 'Error : Customer is nil.');
  MainAccounts.Clear;
  {
  WorkView.FieldByName('客户号').Data.SetString(Sender.Customer.CustomerNo);
  rqGetMainAccounts.SendCommand;
  GetSecAccountsFromDataset(Dataset,MainAccounts);
  }
  //ComCmdDefinition.GetSecAccounts(Sender.Customer.CustomerNo,'',True,MainAccounts);
end;

procedure TdmCommData.AccountInputMethodsGetMoneyAccounts(
  Sender: TKSAccountEdit; MoneyAccounts: TObjectList);
begin
  { TODO : 获取资金账号信息 }
  MoneyAccounts.Clear;
  //  ComCmdDefinition.GetMoneyAccounts(Sender.Customer,'',MoneyAccounts);
end;

procedure TdmCommData.CreateOtherDataDictionary;
var
  IdObjects: TIdObjectList;
begin
  //IdObjects := NeedIdObjectList(deBoolean);
  IdObjects := TIdObjectList.Create(deBoolean, CurrentDepartmentNo);
  IdObjects.Add(TIdObject.Create(IdForFalse, NameForFalse));
  IdObjects.Add(TIdObject.Create(IdForTrue, NameForTrue));
end;

procedure TdmCommData.AccountInputMethodsAdvancedSelect(
  Sender: TKSAccountEdit; var Selected: Boolean; var CustomerNo: string);
begin
  Selected := AdvancedSelectCustomer(CustomerNo);
end;

procedure TdmCommData.GetBusinessFlags(IdObjects: TIdObjectList);
var
  ADataset: TDataset;
  IDField, NameField, CategoryField: TField;
begin
  // wsn 20040916 校园一卡通框架不需要客户概念
  {  rqGetBusinessFlags.SendCommand;
    ADataset := TDataset(WorkView.FieldByName(SReturnDataset).Data.AsObject);
    if ADataset<>nil then
    begin
      IDField := ADataset.FieldByName('spost_code');
      NameField := ADataset.FieldByName('sname');
      CategoryField := ADataset.FieldByName('spost_code2');
      ADataset.First;
      while not ADataset.Eof do
      begin
        IdObjects.Add(TBusinessFlag.Create(IDField.AsString,NameField.AsString,CategoryField.AsString));
        ADataset.Next;
      end;
    end;
    WorkView.FieldByName(SReturnDataset).Data.Clear;
    }
end;

procedure TdmCommData.ShutDown;
begin
  FreeAndNil(InfoAdmin);
end;

procedure TdmCommData.HandleException;
var
  E: Exception;
begin
  E := Exception(ExceptObject);
  if E <> nil then
    Context.GetExceptionHandler.HandleException(E);
end;

procedure TdmCommData.SetupInputMethods;
var
  ConfigSystem: IConfigSystem;
  CustomerNoPattern: string;
  InputSequence: string;
  Start, I, Len: Integer;
  Length1, Length2: Integer;
  InputMethod: TAccountInputMethod;
  TheFirst: string;

  MarketCode: char;
  Market: TKSAbstractMarket;
begin
  ConfigSystem := Context.GetConfigSystem;
  // 客户号补齐格式
  CustomerNoPattern := ConfigSystem.ReadString(ccInput, ckCustomerNo,
    cdCustomerNo);
  // 在资金委托等界面缺省的第一个输入方式
  TheFirst := ConfigSystem.ReadString(ccInput, ckDefaultMethod,
    cdDefaultMethod);
  if TheFirst = '' then
    TheFirst := cdDefaultMethod;
  AccountInputMethods.FirstMethodChar := TheFirst[1];
  // 输入方式的顺序
  InputSequence := ConfigSystem.ReadString(ccInput, ckInputSequence,
    cdInputSequence);
  TAccountInputMethod(AccountInputMethods.Methods.Items[0]).Pattern :=
    CustomerNoPattern;
  // 客户号的长度
  Length1 := ConfigSystem.ReadInteger(ccInput, ckCustomerNoLength1,
    cdCustomerNoLength1);
  Length2 := ConfigSystem.ReadInteger(ccInput, ckCustomerNoLength2,
    cdCustomerNoLength2);
  TAccountInputMethod(AccountInputMethods.Methods.Items[0]).Length1 := Length1;
  TAccountInputMethod(AccountInputMethods.Methods.Items[0]).Length2 := Length2;

  //先把预先设置好的几个市场和客户号和磁卡号的切换顺序定好
  Start := 0;
  Len := Length(InputSequence);
  for I := 1 to Len do
  begin
    InputMethod := AccountInputMethods.FindInputMethod(InputSequence[I]);
    if InputMethod <> nil then
    begin
      InputMethod.Index := Start;
      Inc(Start);
    end;
  end;

  ComCmdDefinition.NeedMarkets;

  //对预先设定的市场，根据配置设定Pattern和length，如果没有用预先设定的值
  //对其他增加的市场的帐号，根据配置设定Pattern和length，并且根据配置的顺序设定切换顺序
  for I := 1 to Length(InputSequence) do
  begin
    MarketCode := InputSequence[I];
    InputMethod := AccountInputMethods.FindInputMethod(MarketCode);
    Market := ComCmdDefinition.GetMarket(MarketCode);
    if (Market <> nil) then
    begin
      if (InputMethod = nil) then
      begin
        InputMethod := TAccountInputMethod(AccountInputMethods.Methods.Add);
        InputMethod.Index := Start;
        Inc(Start);
      end;
      InputMethod.MethodChar := MarketCode;
      InputMethod.Market := MarketCode;
      InputMethod.Length1 := Market.AccountLength;
      InputMethod.Length2 := 0;
      InputMethod.Caption := Market.Name + '帐号';
      InputMethod.Pattern := Market.AccountPattern;
      InputMethod.CheckChars := False;
    end;
  end;
end;

procedure TdmCommData.AccountInputMethodsException(Sender: TObject);
begin
  HandleException;
end;

procedure TdmCommData.AccountInputMethodsWarningCustomerStatus(
  Sender: TObject);
var
  S: string;
begin
  with TKSAccountEdit(Sender).Customer do
  begin
    if Status <> '0' then
      S := Format('%s-%s状态不正常，客户号已经%s',
        [CustomerNo, CustomerName, GetIdObjectName(deAccountStatus, Status)])
    else
      S := Format('%s-%s状态正常，不需要执行该操作',
        [CustomerNo, CustomerName])
  end;
  Context.GetDialogSystem.ShowWarning(S);
end;

procedure TdmCommData.AccountInputMethodsShowEditHint(Sender: TObject);
var
  HintStr: string;
begin
  if Sender is TKSAccountEdit then
  begin
    if TKSAccountEdit(Sender).CurrentInputMethod <> nil then
    begin
      HintStr := Format('输入的%s格式错误，正确的格式是：'#13#10'%s',
        [TKSAccountEdit(Sender).CurrentInputMethod.Caption,
        TKSAccountEdit(Sender).CurrentInputMethod.Hint]);
      Context.GetDialogSystem.ShowHintFor(TKSAccountEdit(Sender), HintStr);
    end;
  end;
end;

{procedure TdmCommData.GetBranchInfos;
var
  ADataset : TDataset;
begin
  if InfoAdmin<>nil then
  begin
    InfoAdmin.Free ;
    InfoAdmin := TInfoAdmin.Create;
  end;
  WorkView.FieldByName(SReturnDataset).Data.Clear;
  rqQueryInitBranch.SendCommand;
  ADataset := TDataset(WorkView.FieldByName(SReturnDataset).Data.AsObject);
  if (ADataset<>nil)and(WorkView.FieldByName(SReturnDataset).Data.AsObject<>nil)
  and(not TDataSet(WorkView.FieldByName(SReturnDataset).Data.AsObject).Eof) and
  (not WorkView.FieldByName(SReturnDataset).Data.IsEmpty) then
  begin
    ReadBranchInfoFromDataSet(ADataset,InfoAdmin);
  end;
  WorkView.FieldByName(SReturnDataset).Data.Clear;
end;}

procedure TdmCommData.AccountInputMethodsMethods5FormatAndValidAccount(
  Sender: TAccountInputMethod; var Account: string; var Valid: Boolean);
begin
  Account := FormatBarCode(Account);
end;

procedure TdmCommData.cpQhLogOutBindOutput(Dataset: TKCDataset;
  Command: TWVCommand);
begin
  CheckCommandReturnValue(Command);
  Context.ParamData(svOperatorNoName).SetString('');
  Context.ParamData(svOperatorPasswordName).SetString('');
  Command.ParamData(svLoginStatusName).SetBoolean(False);
end;

function TdmCommData.GetExistDataEntryName(SourceSL: TStringList;
  NowDataEntry: Integer): string;
var
  I: Integer;
  StrNowDataEntry: string;
begin
  Result := '';
  StrNowDataEntry := IntToStr(NowDataEntry);
  for I := 0 to SourceSL.Count - 1 do
  begin
    if SourceSL.Values[SourceSL[I]] = StrNowDataEntry then
    begin
      Result := SourceSL[I];
      Exit;
    end;
  end;
end;

procedure TdmCommData.rqGetSystemDateAfterExec(Request: TWVRequest;
  Command: TWVCommand);
begin
  CheckCommandReturnValue(Command, False);

end;

initialization
  GetIdObjectsProc := GetIdObjects;
end.

