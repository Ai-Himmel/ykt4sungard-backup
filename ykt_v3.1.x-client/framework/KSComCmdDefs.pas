unit KSComCmdDefs;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSComCmdDefs
   <What>包含基本的命令定义对象、数据域、数据表达方式、常用的公共函数等等。
   这些公共函数一般会产生数据源访问。这些数据源的访问形式被命令定义对象所定义。
   对应的命令处理对象一般位于主程序的UCommData单元。
   <Written By> Huang YanLai (黄燕来)、张国彦
   <History>
      01  整理了所有的数据域，拆分成业务无关与业务相关两部分，请以后
          维护该单元的同志也尽量注意区分，以提高代码的可重用性
                                                张国彦   20010922
**********************************************}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, KSCmdModules,
  WorkViews, DB, WVCmdTypeInfo, Contnrs, KSCustomers, WVCmdProc, KCWVProcBinds,
  KSEdits, WVCtrls, Dialogs, KSBranchInfo, KsBranchTree, BDAImpEx,
  KCDataAccess;

type
  TDoSingleStationCheckEvent = procedure(
    const AOperation: string;
    var CheckerNo, CheckerPassword: string;
    var Passed: Boolean) of object;

  TComCmdDefinition = class(TCommandModule)
    //字符串处理器
    GetDataDictionaryItems: TWVStringsMan;

    //数据表现形式对象
    fpIDObjects: TWVFieldPresent;
    fpMultiIDObjects: TWVFieldPresent;
    fpCurrency: TWVFieldPresent;
    fpChinaCurrency: TWVFieldPresent;
    fpFeeRate: TWVFieldPresent;

    //命令描述对象
    ctGetCustomerInfo: TWVCommandTypeInfo;
    ctGetMarketInfo: TWVCommandTypeInfo;
    ctCheckCustomerPassword: TWVCommandTypeInfo;
    ctCheckExist: TWVCommandTypeInfo;
    ctGetAccounts: TWVCommandTypeInfo;
    ctGetMoneyInfo: TWVCommandTypeInfo;
    ctGetBankAccounts: TWVCommandTypeInfo;
    ctGetSecInfo: TWVCommandTypeInfo;
    ctGetSeatInfo: TWVCommandTypeInfo;
    ctGetEmpInfo: TWVCommandTypeInfo;
    ctGetBrokerInfo: TWVCommandTypeInfo;
    ctGetBranch2Bank: TWVCommandTypeInfo;

    //业务无关部分的域
    fdName: TWVFieldDomain;
    fdInteger: TWVFieldDomain;
    fdInteger2: TWVFieldDomain;
    fdDouble: TWVFieldDomain;
    fdDouble2: TWVFieldDomain;
    fdRate: TWVFieldDomain;
    fdRate2: TWVFieldDomain;
    fdChoice: TWVFieldDomain;
    fdDateCheck: TWVFieldDomain;
    fdDateCheck2: TWVFieldDomain;
    fdDateReCheck: TWVFieldDomain;
    fdCheckTime: TWVFieldDomain;
    fdYearMonthCheck: TWVFieldDomain;
    fdTimeReCheck: TWVFieldDomain;
    fdReinputCheck: TWVFieldDomain;
    fdCompData: TWVFieldDomain;
    fdCompData2: TWVFieldDomain;

    //业务相关部分的域
    fdStockNo: TWVFieldDomain;
    fdStockNo2: TWVFieldDomain;
    fdCustomerNo: TWVFieldDomain;
    fdCustomerNo2: TWVFieldDomain;
    fdBroketNo: TWVFieldDomain;
    fdBroketNo2: TWVFieldDomain;
    fdSHA: TWVFieldDomain;
    fdSHA2: TWVFieldDomain;
    fdSZA: TWVFieldDomain;
    fdSZA2: TWVFieldDomain;
    fdSHB: TWVFieldDomain;
    fdSHB2: TWVFieldDomain;
    fdSZB: TWVFieldDomain;
    fdSZB2: TWVFieldDomain;
    fdBankAccount: TWVFieldDomain;
    fdBankAccount2: TWVFieldDomain;
    fdCard: TWVFieldDomain;
    fdCard2: TWVFieldDomain;
    fdOperator: TWVFieldDomain;
    fdOperatorPassword: TWVFieldDomain;
    fdPassword: TWVFieldDomain;
    fdBoolean: TWVFieldDomain;
    fpAgentDate: TWVFieldPresent;
    fdOperator2: TWVFieldDomain;
    fdEntrustVol: TWVFieldDomain;
    fdCashDomain: TWVFieldDomain;
    fdBankBookCheckDomain: TWVFieldDomain;
    fdStockNoEx: TWVFieldDomain;
    fdBroketNoEx: TWVFieldDomain;
    fdCompData3: TWVFieldDomain;
    ctQueryStationAuth: TWVCommandTypeInfo;
    fpNumber: TWVFieldPresent;
    fdOperatorEx: TWVFieldDomain;
    fdNotEmpty: TWVFieldDomain;
    fdYearCheck: TWVFieldDomain;
    fdST: TWVFieldDomain;
    fdST2: TWVFieldDomain;
    ctGetSecType: TWVCommandTypeInfo;
    ctQueyBranch: TWVCommandTypeInfo;
    ctInitQueyBranch: TWVCommandTypeInfo;
    ctStartLiquidate: TWVCommandTypeInfo;
    ctGetSerialNo: TWVCommandTypeInfo;
    ctGetWorkDate: TWVCommandTypeInfo;
    ctGetLiquidateStatus: TWVCommandTypeInfo;
    ctGetDate: TWVCommandTypeInfo;
    ctGetFeeLevel: TWVCommandTypeInfo;
    ctSimpleQuery: TWVCommandTypeInfo;
    pcSimpleQuery: TKCWVQuery;
    fdCashDomainAll: TWVFieldDomain;
    fdDeliverDate: TWVFieldDomain;
    fdDateReCheck2: TWVFieldDomain;
    fdDeliverDate2: TWVFieldDomain;
    fpPrice: TWVFieldPresent;
    fdPrice: TWVFieldDomain;
    fdFeeMoney: TWVFieldDomain;
    fdFeeMoney2: TWVFieldDomain;
    fdPrice2: TWVFieldDomain;
    fdSysNo: TWVFieldDomain;
    fdRateAll: TWVFieldDomain;
    fdRateAll2: TWVFieldDomain;
    cqQueryWorkerCommon: TWVCommandTypeInfo; //rding,20040526

    //单元级的过程
    procedure DataModuleCreate(Sender: TObject);
    procedure DataModuleDestroy(Sender: TObject);

    //获得数据字典项目中的字符串的处理过程
    procedure GetDataDictionaryItemsGetStrings(const StringsName: string;
      Items: TStrings; var Handled: Boolean);

    //数据转换形式的处理过程
    procedure fpIDObjectsFieldToCtrl(Field: TWVField; Ctrl: TObject;
      const DataPresentType: TDataPresentType; const Param: string; var Handled:
      Boolean);
    procedure fpIDObjectsSetFieldHandler(Field: TField;
      const DataPresentType: TDataPresentType; const Param: string;
      var Handled: Boolean);
    procedure fpIDObjectsCtrlToField(Ctrl: TObject; Field: TWVField;
      const DataPresentType: TDataPresentType; const Param: string; var Handled:
      Boolean);
    procedure fpMultiIDObjectsFieldToCtrl(Field: TWVField; Ctrl: TObject;
      const DataPresentType: TDataPresentType; const Param: string;
      var Handled: Boolean);
    procedure fpMultiIDObjectsSetFieldHandler(Field: TField;
      const DataPresentType: TDataPresentType; const Param: string;
      var Handled: Boolean);
    procedure fpCurrencyCtrlToField(Ctrl: TObject; Field: TWVField;
      const DataPresentType: TDataPresentType; const Param: string;
      var Handled: Boolean);
    procedure fpCurrencySetFieldHandler(Field: TField;
      const DataPresentType: TDataPresentType; const Param: string;
      var Handled: Boolean);
    procedure fpCurrencyFieldToCtrl(Field: TWVField; Ctrl: TObject;
      const DataPresentType: TDataPresentType; const Param: string;
      var Handled: Boolean);
    procedure fpChinaCurrencyFieldToCtrl(Field: TWVField;
      Ctrl: TObject; const DataPresentType: TDataPresentType;
      const Param: string; var Handled: Boolean);
    procedure fpFeeRateFieldToCtrl(Field: TWVField; Ctrl: TObject;
      const DataPresentType: TDataPresentType; const Param: string;
      var Handled: Boolean);
    procedure fpFeeRateSetFieldHandler(Field: TField;
      const DataPresentType: TDataPresentType; const Param: string;
      var Handled: Boolean);
    procedure fpFeeRateCtrlToField(Ctrl: TObject; Field: TWVField;
      const DataPresentType: TDataPresentType; const Param: string;
      var Handled: Boolean);

    procedure fpPriceCtrlToField(Ctrl: TObject; Field: TWVField;
      const DataPresentType: TDataPresentType; const Param: string;
      var Handled: Boolean);
    procedure fpPriceFieldToCtrl(Field: TWVField; Ctrl: TObject;
      const DataPresentType: TDataPresentType; const Param: string;
      var Handled: Boolean);
    procedure fpPriceSetFieldHandler(Field: TField;
      const DataPresentType: TDataPresentType; const Param: string;
      var Handled: Boolean);

    //业务无关的域的处理过程
    procedure fdReinputCheckCheckValid(WorkField: TWVField);
    procedure fdCompDataCheckValid(WorkField: TWVField);
    procedure fdCompData2CheckValid(WorkField: TWVField);
    procedure fdDateCheckCheckValid(WorkField: TWVField);
    procedure fdDateCheck2CheckValid(WorkField: TWVField);
    procedure fdDateReCheckCheckValid(WorkField: TWVField);
    procedure fdYearMonthCheckCheckValid(WorkField: TWVField);
    procedure fdCheckTimeCheckValid(WorkField: TWVField);
    procedure fdTimeReCheckCheckValid(WorkField: TWVField);

    //业务相关的域的处理过程
    procedure fdStockNoCheckValid(WorkField: TWVField);
    procedure fdStockNo2CheckValid(WorkField: TWVField);
    procedure fdCustomerNoCheckValid(WorkField: TWVField);
    procedure fdCustomerNo2CheckValid(WorkField: TWVField);
    procedure fdSHACheckValid(WorkField: TWVField);
    procedure fdSHA2CheckValid(WorkField: TWVField);
    procedure fdSZACheckValid(WorkField: TWVField);
    procedure fdSZA2CheckValid(WorkField: TWVField);
    procedure fdSHBCheckValid(WorkField: TWVField);
    procedure fdSHB2CheckValid(WorkField: TWVField);
    procedure fdSZBCheckValid(WorkField: TWVField);
    procedure fdSZB2CheckValid(WorkField: TWVField);
    procedure fdBankAccountCheckValid(WorkField: TWVField);
    procedure fdBankAccount2CheckValid(WorkField: TWVField);
    procedure fdCardCheckValid(WorkField: TWVField);
    procedure fdCard2CheckValid(WorkField: TWVField);
    procedure fdBroketNoCheckValid(WorkField: TWVField);
    procedure fdBroketNo2CheckValid(WorkField: TWVField);
    procedure fdOperatorCheckValid(WorkField: TWVField);
    procedure fdBooleanCheckValid(WorkField: TWVField);
    procedure fpAgentDateFieldToCtrl(Field: TWVField; Ctrl: TObject;
      const DataPresentType: TDataPresentType; const Param: string;
      var Handled: Boolean);
    procedure fdOperator2CheckValid(WorkField: TWVField);
    procedure fdStockNoExCheckValid(WorkField: TWVField);
    procedure fdBroketNoExCheckValid(WorkField: TWVField);
    procedure fdCompData3CheckValid(WorkField: TWVField);
    procedure fpNumberFieldToCtrl(Field: TWVField; Ctrl: TObject;
      const DataPresentType: TDataPresentType; const Param: string;
      var Handled: Boolean);
    procedure fpNumberSetFieldHandler(Field: TField;
      const DataPresentType: TDataPresentType; const Param: string;
      var Handled: Boolean);
    procedure fdOperatorExCheckValid(WorkField: TWVField);
    procedure fdSTCheckValid(WorkField: TWVField);
    procedure fdST2CheckValid(WorkField: TWVField);
    procedure fdDeliverDateCheckValid(WorkField: TWVField);
    procedure fdDateReCheck2CheckValid(WorkField: TWVField);
    procedure fdDeliverDate2CheckValid(WorkField: TWVField);
    procedure fdPriceCheckValid(WorkField: TWVField);
    procedure fdPrice2CheckValid(WorkField: TWVField);
    procedure fdSysNoCheckValid(WorkField: TWVField);
    procedure fdNameCheckValid(WorkField: TWVField); //rding,20040526

  private
    { Private declarations }
    FMarkets: TObjectList;
    FBranchInfos: TObjectList;
    FSHAStocks: TObjectList;
    FSZAStocks: TObjectList;
    FSHBStocks: TObjectList;
    FSZBStocks: TObjectList;
    FOtherStocks: TObjectList;

    FOperatorNoPattern: string;
    FBrokerNoPattern: string;
    //wlj 20031219 价格的domain和显示格式要读取配置,价格为整数或小数点后4位
    FPriceFormat: string;
    FPricePrecision: integer;

    procedure InitAccountDomains;
    procedure InitAccountDomain(Domain: TWVFieldDomain; MethodChar: Char);
    procedure GetMarkets;
    procedure CreateStockMarkets;
    procedure ReadConfig;
    procedure FormatAndValidSecField(WorkField: TWVField; Required: Boolean);
    function GetMonitorField(WorkField: TWVField): TWVField;

  protected
    procedure Init; override;
  public
    { Public declarations }
    //  CompDataCheck 比较数据值的大小
    procedure CompDataCheck(WorkField: TWVField; IsZeroEqueltoAll: Boolean;
      IsBig: Boolean = True; RetouchNum: Double = 0);
    // CheckDateValid检验日期的有效性
    function CheckDateValid(const DateString: string; Needed: Boolean): Boolean;
    // CheckTimeValid检验时间的有效性
    function CheckTimeValid(const TimeString: string): Boolean;

    // CheckExists 检查账号/客户/证件是否存在。返回true存在,false不存在
    function CheckExists(AccountType: Char; CertType: Integer; const BankCode:
      string; const Account: string): Boolean;
    // GetCustomer 根据营业部、客户号获取客户信息
    function GetCustomer(const BranchCode, CustomerNo: string):
      TKSAbstractCustomerInfo;
    // GetCustomerInfo 根据营业部、客户号获取客户信息
    procedure GetCustomerInfo(const BranchCode, CustomerNo: string;
      CustomerInfos: TObjectList);
    // GetBroker 根据营业部、经纪人号获取经纪人信息
    function GetBroker(const BranchCode, BrokerNo: string):
      TKSAbstractBrokerInfo;
    // GetBrokerInfo 根据营业部、经纪人号获取经纪人信息
    procedure GetBrokerInfo(const BranchCode, BrokerNo: string; BrokerInfos:
      TObjectList);
    // GetSecAccount 根据市场、股东代码获取股东信息
    function GetSecAccount(const Market, Account: string):
      TKSAbstractSecAccount;
    // GetSecAccounts 根据客户号获取股东代码(SecAccounts里面包含TKSAbstractSecAccount)，Market=''表示所有市场,AccountStatus=0表示取状态正常的股东帐号，空表示全部
    procedure GetSecAccounts(const CustomerNo: string; const Market: string;
      OnlyMainAccounts: Boolean; SecAccounts: TObjectList; AccountStatus: string
        =
      '');
    // GetMoneyAccounts 根据客户号获取资金账号信息(MoneyAccounts里面包含TKSAbstractMoneyAccount)，CurrencyType=''表示所有币种
    procedure GetMoneyAccounts(Customer: TKSAbstractCustomer; const
      CurrencyType: string; MoneyAccounts: TObjectList);
    // GetBankAccounts 根据客户号获取银行账号(BankAccounts里面包含TKSAbstractBankAccount)
    procedure GetBankAccounts(const CustomerNo, Bank, CurrencyType: string;
      BankAccounts: TObjectList; QryType: Integer = 0);
    // GetGetSecInfo 根据证券代码和市场代码获取证券信息(SecInfos里面包含TKSAbstractSecInfo)
    procedure GetSecInfo(const SecCode, Market: string; SecInfos: TObjectList);
    // GetSeatInfo 根据市场代码,查询营业部和席位代码获取席位信息(SeatInfos里面包含TKSAbstractSeatInfo)
    procedure GetSeatInfo(const Market, BranchCode, SeatNo: string; SeatInfos:
      TObjectList; UniqueFlag: Integer = 1);
    // GetSeat 根据市场代码,查询营业部和席位代码获取席位信息(SeatInfos里面包含TKSAbstractSeatInfo)
    function GetSeat(const Market: string; const BranchCode: string = '';
      UniqueFlag: Integer = 1): TKSAbstractSeatInfo;
    // GetEmpInfo 根据查询营业部和职工代码获取职工信息(EmpInfos里面包含TKSAbstractEmpInfo)
    procedure GetEmpInfo(const BranchCode, EmpNo: string; EmpInfos:
      TObjectList);
    // GetEmp 根据查询营业部和职工代码获取职工信息(EmpInfos里面包含TKSAbstractEmpInfo)
    function GetEmp(const EmpNo: string; const BranchCode: string = ''):
      TKSAbstractEmpInfo;
    // GetReportDay 获得可以打印报表的最后一个工作日
    function GetReportDay: string;
    // GetBranch2BankInfo 根据查询营业部,货币代码和银行代码获取营业部对应的银行信息(BankInfos里面包含TKSAbstractBankInfo)
    procedure GetBranch2BankInfo(const BranchCode, CurrencyType, BankCode:
      string; BankInfos: TObjectList);
    // GetStationAuth 根据查询营业部和岗位代码获取岗位权限信息
    function GetStationAuth(const BranchCode: string = ''; const Station: string
      = ''): TKSAbstractStationAuthInfo;
    // GetStationAuthInfo 根据查询营业部和岗位代码获取岗位权限信息(StationInfos里面包含TKSAbstractEmpInfo)
    procedure GetStationAuthInfo(const BranchCode, Station: string;
      StationInfos: TObjectList);
    // GetBranchInfos 获取营业部信息
    procedure GetBranchInfos;
    //NeedBranchs, 获得所有的营业部信息
    function NeedBranchs: TObjectList;
    //GetBranch return TKSAbstractBranch 不要手工释放TKSAbstractBranch
    function GetBranch(const Branch: string): TKSAbstractBranch;
    //GetBranchInfoAdmin, 初始化InfoAdmin
    procedure GetBranchInfoAdmin;
    //GetFeeLevel, 根据收费方式获得收费档次
    procedure GetFeeLevel(const Branch, FeeType: string; QueryType: Integer;
      FeeLevelSet: TObjectList);

    {***********合作配售************}
// GetTreatyGroupInfos 根据查询营业部,协议组号,协议状态,查询方式，是否包含下属，是否向下属发布取得分组信息(GroupInfos里面包含TKSAbstractGroupInfo)
    procedure GetTreatyGroupInfos(const BranchCode, TreatyStatus, IsDownToChild:
      string; const IsContainChild, QueryMode, GroupNo: Integer; GroupInfos:
      TObjectList);

    procedure CheckAccountFieldValid(WorkField: TWVField; MethodChar: Char;
      CanEmpty: Boolean = False);
    //NeedMarkets, 获得所有的市场信息
    function NeedMarkets: TObjectList;
    //GetMarket return TKSAbstractMarket 不要手工释放TKSAbstractMarket
    function GetMarket(const Market: string): TKSAbstractMarket;
    //SearchStock return TKSAbstractSecInfo in TObjectList.
    function SearchStock(const SecCode, Market: string; StockList: TObjectList):
      TKSAbstractSecInfo;
    //GetStock return TKSAbstractSecInfo 不要手工释放TKSAbstractSecInfo
    function GetStock(const SecCode, Market: string): TKSAbstractSecInfo;
    function FindStock(const SecCode, Market: string): TKSAbstractSecInfo;
    //RequestStockInfo  从TObjectList中获得指定的证券信息，不要手工释放TKSAbstractSecInfo
    function RequestStockInfo(const SecCode, Market: string; StockList:
      TObjectList): TKSAbstractSecInfo;

    // FormatAndValidSecurityCode根据市场代码,检验证券代码的有效性并补齐
    function FormatAndValidSecurityCode(const Market: string; var SecurityCode:
      string): Boolean;
    // FormatAndValidBrokerNo根据营业部代码,检验经纪人号的有效性并补齐
    function FormatAndValidBrokerNo(var BrokerNo: string): Boolean;
    // 进行单机双柜员复核,通过参数返回复核操作员的工号和密码，通过返回值返回操作员的工号和密码是否合法。
    function DoSingleStationCheck(
      const AOperation: string;
      var CheckerNo, CheckerPassword: string;
      FuncNo: Integer = 0;
      const CustomerNo: string = '';
      const CurrentType: string = '';
      const ACaption: string = ''
      ): Boolean;
    //在特定查询方式下，相关项目的显示控制（用于查询界面）
    procedure QueryControl(const QueryMethod: string; CustField, DeptField:
      TWVField;
      CustNo: TKSAccountEdit; BranchCode: TWVComboBox);
    (*
    //获取营业部参数的值
    function GetBranchParam(ParamCode: string;const BranchCode:string=''): string;
    *)

    // GetSecTypeSets 根据市场获取证券类别集合，Market可以为空
    procedure GetSecTypeSets(const Market: string; SecTypeSet: TStringList);
    procedure GetWorkDay(var LastDay, CurrentDay, NextDay: string; const Market:
      string = '');
    //GetLiquidate获取清算日期
    function GetLiquidate(DateType: Integer): string;

    //ADD BY CGM
    //根据一个表的某个字段的名称和值查询另一个字段的值
    function GetResultValue(const TableName: string; const FieldName: string;
      const FieldValue: string; const ResultFieldName: string): string;

  end;

var
  ComCmdDefinition: TComCmdDefinition;

implementation

uses
  KSFrameWorks, KSClientConsts, KSFrameWorkUtils, StdCtrls, SafeCode, DataTypes,
  LogFile, KSDataDictionary, WVCommands, {KSEdits,} ConvertUtils, {WVCtrls,}
  KSStrUtils, DBAIntf;

{$R *.DFM}

procedure TComCmdDefinition.fdReinputCheckCheckValid(WorkField: TWVField);
{var
  CheckedFieldName : string;
  CheckedField : TWVField;}
begin
  ReinputCheck(WorkField);
  {
  inherited;
  CheckedFieldName := WorkField.MonitorValueChangedFields;
  CheckedFieldName := StringReplace(CheckedFieldName,'|','',[rfReplaceAll]);
  CheckedField := WorkField.WorkView.FindField(CheckedFieldName);
  if CheckedField<>nil then
  begin
    WorkField.Valid := CheckedField.Valid and (WorkField.Data.AsString = CheckedField.Data.AsString);
    WorkField.SetInvalidMessage(SInvalidReinput);
  end;
  }
end;

procedure TComCmdDefinition.fpIDObjectsCtrlToField(Ctrl: TObject;
  Field: TWVField; const DataPresentType: TDataPresentType;
  const Param: string; var Handled: Boolean);
var
  Obj: TObject;
begin
  //if SameText(DataPresentType,dptIdObjects) then
  begin
    if Ctrl is TWVComboBox then
    begin
      with TWVComboBox(Ctrl) do
      begin
        Handled := True;
        //        CheckTrue(Style=csDropDownList,'Style<>csDropDownList');
        if ItemIndex < 0 then
          if Field.DataType = kdtInteger then
            Field.Data.SetInteger(0)
          else
            Field.Data.AsString := ''
        else // ItemIndex>=0
        begin
          Obj := Items.Objects[ItemIndex];
          {if not (Items.Objects[I] is TIdObject) then
            Break;}
          CheckTrue(Obj is TIdObject, 'Obj not is TIdObject');
          if TIdObject(Obj).ID = '' then
            if Field.DataType = kdtInteger then
              Field.Data.SetInteger(0)
            else
              Field.Data.AsString := ''
          else
            Field.Data.AsString := TIdObject(Obj).ID;
        end;
      end;
    end;
  end;
end;

procedure TComCmdDefinition.fpIDObjectsFieldToCtrl(Field: TWVField;
  Ctrl: TObject; const DataPresentType: TDataPresentType;
  const Param: string; var Handled: Boolean);
var
  Find: Boolean;
  I: Integer;
  SValue: string;
  DataEntry: Integer;
  IdObjects: TIdObjectList;
begin
  //if SameText(DataPresentType,dptIdObjects) then
  begin
    if Ctrl is TWVComboBox then
    begin
      with TWVComboBox(Ctrl) do
      begin
        Handled := True;
        //        CheckTrue(Style=csDropDownList,'Style<>csDropDownList');
        Find := False;
        if not Field.Data.IsEmpty then
        begin
          SValue := Field.Data.AsString;
          for I := 0 to Items.Count - 1 do
          begin
            if not (Items.Objects[I] is TIdObject) then
              Break;
            if TIdObject(Items.Objects[I]).ID = SValue then
            begin
              Find := True;
              ItemIndex := I;
              Break;
            end;
          end;
        end;
        if not Find then
          ItemIndex := -1;
      end;
    end
    else if Ctrl is TWVLabel then
    begin
      DataEntry := StrToIntDef(Param, deNotUsed);
      if DataEntry <> deNotUsed then
      begin
        IdObjects := NeedIdObjectList(DataEntry);
        TWVLabel(Ctrl).Caption := IdObjects.GetDisplayText(Field.Data.AsString);
      end
      else
        TWVLabel(Ctrl).Caption := Field.Data.AsString;
    end;
  end;
end;

procedure TComCmdDefinition.fpIDObjectsSetFieldHandler(Field: TField;
  const DataPresentType: TDataPresentType; const Param: string;
  var Handled: Boolean);
var
  DataEntry: Integer;
  IdObjects: TIdObjectList;
begin
  DataEntry := StrToIntDef(Param, deNotUsed);
  if DataEntry <> deNotUsed then
  begin
    IdObjects := NeedIdObjectList(DataEntry);
    Field.OnGetText := IdObjects.GetText;
    Field.Alignment := taLeftJustify;
    Handled := True;
  end;
end;

procedure TComCmdDefinition.GetDataDictionaryItemsGetStrings(
  const StringsName: string; Items: TStrings; var Handled: Boolean);
var
  DataEntry: Integer;
  IncludeEmpty: Boolean;
  TheEntry: string;
  Filtered: Boolean;
begin
  TheEntry := StringsName;
  if (TheEntry <> '') and (TheEntry[1] = '*') then
  begin
    IncludeEmpty := True;
    TheEntry := Copy(TheEntry, 2, Length(TheEntry));
  end
  else
  begin
    IncludeEmpty := False;
  end;
  if (TheEntry <> '') and (TheEntry[1] = '#') then
  begin
    Filtered := False;
    TheEntry := Copy(TheEntry, 2, Length(TheEntry));
  end
  else
  begin
    Filtered := True;
  end;
  DataEntry := StrToIntDef(TheEntry, deNotUsed);
  if DataEntry <> deNotUsed then
  begin
    if DataEntry = deDepart then
      InitDepartmentItems(Items, IncludeEmpty)
    else
      InitIdObjectItems(Items, DataEntry, IncludeEmpty, Filtered);
    Handled := True;
  end;
end;

function TComCmdDefinition.CheckExists(AccountType: Char;
  CertType: Integer; const BankCode, Account: string): Boolean;
var
  Command: TWVCommand;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctCheckExist.ID,
    ctCheckExist.Version);
  try
    Command.ParamData('帐号类型').SetString(AccountType);
    Command.ParamData('证件类型').SetInteger(CertType);
    Command.ParamData('帐号').SetString(Account);
    Command.ParamData('银行代码').SetString(BankCode);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command);
    Result := not (Command.ParamData('个数').AsInteger = 0);
  finally
    Command.Free;
  end;
end;

//获得股东代码

procedure TComCmdDefinition.GetSecAccounts(const CustomerNo,
  Market: string; OnlyMainAccounts: Boolean; SecAccounts: TObjectList;
  AccountStatus: string = '');
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetAccounts.ID,
    ctGetAccounts.Version);
  try
    Command.ParamData('客户号').SetString(CustomerNo);
    Command.ParamData('市场代码').SetString(Market);
    if OnlyMainAccounts then
      Command.ParamData('主代码标志').SetInteger(2)
    else
      Command.ParamData('主代码标志').SetInteger(1);
    Command.ParamData('股东代码').SetString('');
    if AccountStatus <> '' then
      Command.ParamData('股东状态').SetString(AccountStatus)
    else
      Command.ParamData('股东状态').SetString('');
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    GetSecAccountsFromDataset(Dataset, SecAccounts);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

//获得各个市场的资金信息

procedure TComCmdDefinition.GetMoneyAccounts(Customer: TKSAbstractCustomer;
  const CurrencyType: string; MoneyAccounts: TObjectList);
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetMoneyInfo.ID,
    ctGetMoneyInfo.Version);
  try
    Command.ParamData('客户号').SetString(Customer.CustomerNo);
    Command.ParamData('开户营业部').SetString(Customer.Department);
    Command.ParamData('货币类型').SetString(CurrencyType);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    GetMoneyAccountsFromDataset(Dataset, MoneyAccounts);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

//获得证券信息

procedure TComCmdDefinition.GetSecInfo(const SecCode, Market: string; SecInfos:
  TObjectList);
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetSecInfo.ID,
    ctGetSecInfo.Version);
  try
    Command.ParamData('证券代码').SetString(SecCode);
    Command.ParamData('市场代码').SetString(Market);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    GetSecInfosFromDataset(Dataset, SecInfos);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

//获得银行帐号

procedure TComCmdDefinition.GetBankAccounts(const CustomerNo,
  Bank, CurrencyType: string; BankAccounts: TObjectList; QryType: Integer = 0);
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetBankAccounts.ID,
    ctGetBankAccounts.Version);
  try
    Command.ParamData('客户号').SetString(CustomerNo);
    Command.ParamData('银行代码').SetString(Bank);
    Command.ParamData('货币类型').SetString(CurrencyType);
    Command.ParamData('查询方式').setinteger(QryType);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    GetBankAccountsFromDataset(Dataset, BankAccounts);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

// 获得席位信息

procedure TComCmdDefinition.GetSeatInfo(const Market, BranchCode,
  SeatNo: string; SeatInfos: TObjectList; UniqueFlag: Integer = 1);
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetSeatInfo.ID,
    ctGetSeatInfo.Version);
  try
    Command.ParamData('市场代码').SetString(Market);
    Command.ParamData('查询营业部').SetString(BranchCode);
    Command.ParamData('席位代码').SetString(SeatNo);
    Command.ParamData('席位唯一标志').SetInteger(UniqueFlag);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    GetSeatInfosFromDataset(Dataset, SeatInfos);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

//简单查询

function TComCmdDefinition.GetResultValue(const TableName: string; const
  FieldName: string; const FieldValue: string; const ResultFieldName: string):
  string;
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctSimpleQuery.ID,
    ctSimpleQuery.Version);
  try
    Command.ParamData('表名').SetString(TableName);
    Command.ParamData('字段名').SetString(FieldName);
    Command.ParamData('字段值').SetString(FieldValue);
    Command.ParamData('结果字段名').SetString(ResultFieldName);

    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);

    if (DataSet = nil) or (DataSet.RecordCount = 0) or
      (DataSet.Fields[0].AsString = '无返回值') then
      result := ''
    else
      result := DataSet.Fields[0].AsString;

    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

// 获得席位信息

function TComCmdDefinition.GetSeat(const Market: string;
  const BranchCode: string = ''; UniqueFlag: Integer = 1): TKSAbstractSeatInfo;
var
  Command: TWVCommand;
  Dataset: TDataset;
  Branch: string;
begin
  CheckObject(Context, 'Invalid Context');
  if BranchCode = '' then
    Branch := CurrentDepartmentNo
  else
    Branch := BranchCode;
  Command := Context.CommandFactory.NewCommand(ctGetCustomerInfo.ID,
    ctGetCustomerInfo.Version);
  try
    Command.ParamData('市场代码').SetString(Market);
    Command.ParamData('查询营业部').SetString(Branch);
    Command.ParamData('席位唯一标志').SetInteger(UniqueFlag);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    if (Dataset = nil) or Dataset.IsEmpty then
      Result := nil
    else
      Result := TKSSeatInfo.Create(Dataset);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

// 获得职工信息

procedure TComCmdDefinition.GetEmpInfo(const BranchCode, EmpNo: string;
  EmpInfos: TObjectList);
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetEmpInfo.ID,
    ctGetEmpInfo.Version);
  try
    Command.ParamData('查询营业部').SetString(BranchCode);
    Command.ParamData('职工代码').SetString(EmpNo);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    GetEmpInfosFromDataset(Dataset, EmpInfos);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

// 获得职工信息

function TComCmdDefinition.GetEmp(const EmpNo,
  BranchCode: string): TKSAbstractEmpInfo;
var
  Command: TWVCommand;
  Dataset: TDataset;
  Branch: string;
begin
  CheckObject(Context, 'Invalid Context');
  if BranchCode = '' then
    Branch := CurrentDepartmentNo
  else
    Branch := BranchCode;
  Command := Context.CommandFactory.NewCommand(ctGetEmpInfo.ID,
    ctGetEmpInfo.Version);
  try
    Command.ParamData('查询营业部').SetString(Branch);
    Command.ParamData('职工代码').SetString(EmpNo);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    if (Dataset = nil) or Dataset.IsEmpty then
      Result := nil
    else
      Result := TKSEmpInfo.Create(Dataset);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

procedure TComCmdDefinition.fdCustomerNoCheckValid(WorkField: TWVField);
begin
  inherited;
  CheckAccountFieldValid(WorkField, CustomerNoInputMethodChar);
end;

procedure TComCmdDefinition.fdSHACheckValid(WorkField: TWVField);
begin
  inherited;
  CheckAccountFieldValid(WorkField, SHAInputMethodChar);
end;

procedure TComCmdDefinition.fdSZACheckValid(WorkField: TWVField);
begin
  inherited;
  CheckAccountFieldValid(WorkField, SZAInputMethodChar);
end;

procedure TComCmdDefinition.fdSHBCheckValid(WorkField: TWVField);
begin
  inherited;
  CheckAccountFieldValid(WorkField, SHBInputMethodChar);
end;

procedure TComCmdDefinition.fdSZBCheckValid(WorkField: TWVField);
begin
  inherited;
  CheckAccountFieldValid(WorkField, SZBInputMethodChar);
end;

procedure TComCmdDefinition.fdSTCheckValid(WorkField: TWVField);
begin
  inherited;
  CheckAccountFieldValid(WorkField, SSTInputMethodChar);
end;

procedure TComCmdDefinition.fdBankAccountCheckValid(WorkField: TWVField);
begin
  inherited;
  CheckAccountFieldValid(WorkField, BankAccountInputMethodChar);
end;

procedure TComCmdDefinition.fdCardCheckValid(WorkField: TWVField);
begin
  inherited;
  WorkField.Data.SetString(FormatBarCode(WorkField.Data.AsString));
  CheckAccountFieldValid(WorkField, CardInputMethodChar);
end;

procedure TComCmdDefinition.CheckAccountFieldValid(WorkField: TWVField;
  MethodChar: Char; CanEmpty: Boolean = False);
var
  AText, OldText: string;
begin
  AText := WorkField.Data.AsString;
  OldText := AText;
  WorkField.Valid := FormatAndValidAccount(MethodChar, AText, CanEmpty);
  if AText <> OldText then
    WorkField.Data.AsString := AText;
  WorkField.SetInvalidMessage(SInvalidAccount);
end;

procedure TComCmdDefinition.Init;
begin
  inherited;
  RegisterModule(Self);
  ReadConfig;
  InitAccountDomains;
end;

procedure TComCmdDefinition.InitAccountDomains;
begin
  CheckTrue(AccountInputMethods <> nil,
    'Error : AccountInputMethods not init!');
  InitAccountDomain(fdCustomerNo, CustomerNoInputMethodChar);
  InitAccountDomain(fdSHA, SHAInputMethodChar);
  InitAccountDomain(fdSZA, SZAInputMethodChar);
  InitAccountDomain(fdSHB, SHBInputMethodChar);
  InitAccountDomain(fdSZB, SZBInputMethodChar);
  InitAccountDomain(fdBankAccount, BankAccountInputMethodChar);
  InitAccountDomain(fdCard, CardInputMethodChar);
  InitAccountDomain(fdCustomerNo2, CustomerNoInputMethodChar);
  InitAccountDomain(fdSHA2, SHAInputMethodChar);
  InitAccountDomain(fdSZA2, SZAInputMethodChar);
  InitAccountDomain(fdSHB2, SHBInputMethodChar);
  InitAccountDomain(fdSZB2, SZBInputMethodChar);
  InitAccountDomain(fdBankAccount2, BankAccountInputMethodChar);
  InitAccountDomain(fdCard2, CardInputMethodChar);
end;

procedure TComCmdDefinition.InitAccountDomain(Domain: TWVFieldDomain;
  MethodChar: Char);
var
  InputMethod: TAccountInputMethod;
begin
  InputMethod := AccountInputMethods.FindInputMethod(MethodChar);
  if InputMethod <> nil then
  begin
    Domain.Checker.AcceptAlphabet := not InputMethod.CheckChars or
      (InputMethod.FirstChars <> '');
    Domain.Checker.AcceptOther := not InputMethod.CheckChars;
    if InputMethod.CheckLength then
    begin
      Domain.Checker.MaxLength := InputMethod.Length1;
      if InputMethod.Length2 > InputMethod.Length1 then
        Domain.Checker.MaxLength := InputMethod.Length2;
    end
    else
    begin
      Domain.Checker.MaxLength := 0;
    end;
    Domain.Checker.Required := True;
    Domain.Hint := InputMethod.Hint + Domain.Hint;
  end;
end;

procedure TComCmdDefinition.fdCustomerNo2CheckValid(WorkField: TWVField);
begin
  inherited;
  CheckAccountFieldValid(WorkField, CustomerNoInputMethodChar, True);
end;

procedure TComCmdDefinition.fdSHA2CheckValid(WorkField: TWVField);
begin
  inherited;
  CheckAccountFieldValid(WorkField, SHAInputMethodChar, True);
end;

procedure TComCmdDefinition.fdSZA2CheckValid(WorkField: TWVField);
begin
  inherited;
  CheckAccountFieldValid(WorkField, SZAInputMethodChar, True);
end;

procedure TComCmdDefinition.fdSHB2CheckValid(WorkField: TWVField);
begin
  inherited;
  CheckAccountFieldValid(WorkField, SHBInputMethodChar, True);
end;

procedure TComCmdDefinition.fdSZB2CheckValid(WorkField: TWVField);
begin
  inherited;
  CheckAccountFieldValid(WorkField, SZBInputMethodChar, True);
end;

procedure TComCmdDefinition.fdST2CheckValid(WorkField: TWVField);
begin
  inherited;
  CheckAccountFieldValid(WorkField, SSTInputMethodChar, True);
end;

procedure TComCmdDefinition.fdBankAccount2CheckValid(WorkField: TWVField);
begin
  inherited;
  CheckAccountFieldValid(WorkField, BankAccountInputMethodChar, True);
end;

procedure TComCmdDefinition.fdCard2CheckValid(WorkField: TWVField);
begin
  inherited;
  WorkField.Data.SetString(FormatBarCode(WorkField.Data.AsString));
  CheckAccountFieldValid(WorkField, CardInputMethodChar, True);
end;

procedure TComCmdDefinition.fdDateCheckCheckValid(WorkField: TWVField);
begin
  inherited;
  WorkField.Valid := CheckDateValid(WorkField.Data.AsString, True);
end;

procedure TComCmdDefinition.fdDateReCheckCheckValid(WorkField: TWVField);
var
  CheckedField: TWVField;
begin
  inherited;
  WorkField.Valid := False;
  CheckedField := GetMonitorField(WorkField);
  if CheckedField = nil then
    Exit;
  if not (CheckDateValid(CheckedField.Data.AsString, True)) then
    Exit;
  if not CheckDateValid(WorkField.Data.AsString, True) then
    Exit;
  if DBStrDateToDateTime(CheckedField.Data.AsString) >
    DBStrDateToDateTime(WorkField.Data.AsString) then
  begin
    WorkField.Valid := False;
    WorkField.SetInvalidMessage(Format(SInvalidSmallData,
      [CheckedField.Caption]));
    WorkField.Hint := ' ';
  end
  else
    WorkField.Valid := true;
end;

procedure TComCmdDefinition.fpCurrencySetFieldHandler(Field: TField;
  const DataPresentType: TDataPresentType; const Param: string;
  var Handled: Boolean);
begin
  inherited;
  if Field is TNumericField then
  begin
    if Param = '' then
      TNumericField(Field).DisplayFormat := CurrencyFormat
    else
      TNumericField(Field).DisplayFormat := Param;
    Handled := True;
  end;
end;

procedure TComCmdDefinition.fpCurrencyFieldToCtrl(Field: TWVField;
  Ctrl: TObject; const DataPresentType: TDataPresentType;
  const Param: string; var Handled: Boolean);
begin
  inherited;
  if Ctrl is TWVLabel then
  begin
    Handled := True;
    if Field.Data.AsString <> '' then
      if Param = '' then
        TWVLabel(Ctrl).Caption := FormatFloat(CurrencyFormat, Field.Data.AsFloat)
      else
        TWVLabel(Ctrl).Caption := FormatFloat(Param, Field.Data.AsFloat)
    else
      TWVLabel(Ctrl).Caption := '';
  end
  else if Ctrl is TWVEdit then
  begin
    Handled := True;
    if Field.Data.AsString <> '' then
      TWVEdit(Ctrl).Text := FloatToStrF(Field.Data.AsFloat, ffFixed, 15, 2)
    else
      TWVEdit(Ctrl).Text := '';
  end
end;

procedure TComCmdDefinition.fpChinaCurrencyFieldToCtrl(
  Field: TWVField; Ctrl: TObject; const DataPresentType: TDataPresentType;
  const Param: string; var Handled: Boolean);
begin
  inherited;
  if Ctrl is TWVLabel then
  begin
    if Field.Data.AsString <> '' then
      TWVLabel(Ctrl).Caption := MoneyToStr(Field.Data.AsFloat)
    else
      TWVLabel(Ctrl).Caption := '';
  end
end;

function TComCmdDefinition.GetMarket(
  const Market: string): TKSAbstractMarket;
var
  I: Integer;
begin
  NeedMarkets;
  if Market <> '' then
    for I := 0 to FMarkets.Count - 1 do
    begin
      Result := TKSAbstractMarket(FMarkets[I]);
      if Result.Market = Market then
        Exit;
    end;
  Result := nil;
end;

function TComCmdDefinition.NeedMarkets: TObjectList;
begin
  if FMarkets = nil then
    GetMarkets;
  Result := FMarkets;
end;

procedure TComCmdDefinition.DataModuleDestroy(Sender: TObject);
begin
  WriteLog('ComCmdDefinition Destroying...', lcConstruct_Destroy);
  inherited;
  FreeAndNil(FMarkets);
  ComCmdDefinition := nil;
  WriteLog('ComCmdDefinition Destroyed', lcConstruct_Destroy);
end;

procedure TComCmdDefinition.DataModuleCreate(Sender: TObject);
begin
  FMarkets := nil;
  FBranchInfos := nil;
  inherited;
end;

procedure TComCmdDefinition.GetMarkets;
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  FMarkets := TObjectList.Create;
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetMarketInfo.ID,
    ctGetMarketInfo.Version);
  try
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command);
    Command.ParamData('市场代码').SetString('');
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    GetMarketInfosFromDataset(Dataset, FMarkets);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

{
// hardcode版本
function TComCmdDefinition.FormatAndValidSecurityCode(const Market: string;
  var SecurityCode: string): Boolean;
var
  I: Integer;
begin
  I:=length(SecurityCode);
  if (I<7) and (I>0) then
  begin
    if Market='1' then
      SecurityCode:= ExpandLeft(SecurityCode,'600600')
    else if Market='2' then
      SecurityCode:= ExpandLeft(SecurityCode,'000000')
    else if Market='3' then
      SecurityCode:= ExpandLeft(SecurityCode,'900900')
    else if Market='4' then
      SecurityCode:= ExpandLeft(SecurityCode,'200000')
    else
      SecurityCode:= ExpandLeft(SecurityCode,'000000');
    result:= True;
  end else
    result:= False;
end;
}

// 根据新的市场对象

function TComCmdDefinition.FormatAndValidSecurityCode(const Market: string;
  var SecurityCode: string): Boolean;
var
  MarketObj: TKSAbstractMarket;
begin
  Result := False;
  MarketObj := GetMarket(Market);
  if (MarketObj <> nil) and (SecurityCode <> '') then
  begin
    SecurityCode := ExpandLeft(SecurityCode, MarketObj.SecurityPattern);
    Result := Length(SecurityCode) = MarketObj.SecurityLength;
  end;
end;

function TComCmdDefinition.CheckDateValid(
  const DateString: string; Needed: Boolean): Boolean;
begin
  Result := False;
  if not Needed and (DateString = '') then
  begin
    Result := True;
    Exit;
  end;
  if Length(DateString) <> 8 then
    Exit;
  try
    DBStrDateToDateTime(DateString);
    Result := True;
  except
    Result := False;
  end;
end;

procedure TComCmdDefinition.fdStockNoCheckValid(WorkField: TWVField);
begin
  inherited;
  FormatAndValidSecField(WorkField, True);
end;

procedure TComCmdDefinition.fpFeeRateFieldToCtrl(Field: TWVField;
  Ctrl: TObject; const DataPresentType: TDataPresentType;
  const Param: string; var Handled: Boolean);
begin
  inherited;
  if Ctrl is TWVLabel then
  begin
    if Field.Data.AsString <> '' then
      if Param = '' then
        TWVLabel(Ctrl).Caption := FormatFloat(FeeRateFormat, Field.Data.AsFloat)
      else
        TWVLabel(Ctrl).Caption := FormatFloat(Param, Field.Data.AsFloat)
    else
      TWVLabel(Ctrl).Caption := '';
  end
  else if Ctrl is TWVEdit then
  begin
    Handled := True;
    if Field.Data.AsString <> '' then
      TWVEdit(Ctrl).Text := FloatToStrF(Field.Data.AsFloat, ffFixed, 15, 8)
    else
      TWVEdit(Ctrl).Text := '';
  end
end;

procedure TComCmdDefinition.fpFeeRateSetFieldHandler(Field: TField;
  const DataPresentType: TDataPresentType; const Param: string;
  var Handled: Boolean);
begin
  inherited;
  if Field is TNumericField then
  begin
    if Param = '' then
      TNumericField(Field).DisplayFormat := FeeRateFormat
    else
      TNumericField(Field).DisplayFormat := Param;
    Handled := True;
  end;
end;

//取得股东信息

function TComCmdDefinition.GetSecAccount(const Market,
  Account: string): TKSAbstractSecAccount;
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetAccounts.ID,
    ctGetAccounts.Version);
  try
    Command.ParamData('客户号').SetString('');
    Command.ParamData('市场代码').SetString(Market);
    Command.ParamData('主代码标志').SetInteger(1);
    Command.ParamData('股东代码').SetString(Account);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    if (Dataset = nil) or Dataset.IsEmpty then
      Result := nil
    else
      Result := TKSSecAccount.Create(Dataset);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

procedure TComCmdDefinition.fpCurrencyCtrlToField(Ctrl: TObject;
  Field: TWVField; const DataPresentType: TDataPresentType;
  const Param: string; var Handled: Boolean);
begin
  inherited;
  if Ctrl is TWVEdit then
  begin
    Handled := True;
    Field.Data.AsString := TWVEdit(Ctrl).Text;
  end
end;

procedure TComCmdDefinition.fpFeeRateCtrlToField(Ctrl: TObject;
  Field: TWVField; const DataPresentType: TDataPresentType;
  const Param: string; var Handled: Boolean);
begin
  inherited;
  if Ctrl is TWVEdit then
  begin
    Handled := True;
    Handled := True;
    Field.Data.AsString := TWVEdit(Ctrl).Text;
  end
end;

function TComCmdDefinition.DoSingleStationCheck(
  const AOperation: string;
  var CheckerNo, CheckerPassword: string;
  FuncNo: Integer = 0;
  const CustomerNo: string = '';
  const CurrentType: string = '';
  const ACaption: string = ''
  ): Boolean;
begin
  CheckerNo := '';
  CheckerPassword := '';
  Result := True;
  if Context.GetConfigSystem.ReadBoolean(ccDoubleCheck, AOperation,
    cdDoubleCheck) then
  begin
    WriteLog('Need Double Check:' + AOperation, lcKSClient);
    Result := Context.GetDialogSystem.DoSingleStationCheck(
      AOperation,
      CheckerNo,
      CheckerPassword,
      FuncNo,
      CustomerNo,
      CurrentType,
      ACaption);
  end
  else
    WriteLog('Not Need Double Check:' + AOperation, lcKSClient);
end;

procedure TComCmdDefinition.fpMultiIDObjectsFieldToCtrl(Field: TWVField;
  Ctrl: TObject; const DataPresentType: TDataPresentType;
  const Param: string; var Handled: Boolean);
var
  SValue: string;
  DataEntry: Integer;
  IdObjects: TIdObjectList;
begin
  inherited;
  if Ctrl is TWVLabel then
  begin
    Handled := True;
    SValue := Field.Data.AsString;
    DataEntry := StrToIntDef(Param, deNotUsed);
    if DataEntry <> deNotUsed then
    begin
      IdObjects := NeedIdObjectList(DataEntry);
      TWVLabel(Ctrl).Caption := IdObjects.GetDisplayText2(SValue);
    end
    else
      TWVLabel(Ctrl).Caption := SValue;
  end;
end;

procedure TComCmdDefinition.fpMultiIDObjectsSetFieldHandler(Field: TField;
  const DataPresentType: TDataPresentType; const Param: string;
  var Handled: Boolean);
var
  DataEntry: Integer;
  IdObjects: TIdObjectList;
begin
  DataEntry := StrToIntDef(Param, deNotUsed);
  if DataEntry <> deNotUsed then
  begin
    IdObjects := NeedIdObjectList(DataEntry);
    Field.OnGetText := IdObjects.GetText2;
    Field.Alignment := taLeftJustify;
    Handled := True;
  end;
end;

procedure TComCmdDefinition.fdStockNo2CheckValid(WorkField: TWVField);
begin
  inherited;
  FormatAndValidSecField(WorkField, False);
end;

procedure TComCmdDefinition.fdOperatorCheckValid(WorkField: TWVField);
var
  S, S1: string;
begin
  inherited;
  S := WorkField.Data.AsString;
  if (S <> '') then
  begin
    S1 := ExpandLeft(S, FOperatorNoPattern);
    if S1 <> S then
    begin
      // 先补齐
      WorkField.Data.AsString := S1;
      // 再校验一次
      fdOperator.Checker.CheckValid(WorkField);
    end;
  end;
end;

procedure TComCmdDefinition.ReadConfig;
var
  ConfigSystem: IConfigSystem;
  MaxEntrustVol: integer;
  MaxCashSum: Real;
  MaxBankBookCheckSum: Real;
begin
  ConfigSystem := Context.GetConfigSystem;
  FOperatorNoPattern := ConfigSystem.ReadString(ccInput, ckOperatorNo,
    cdOperatorNo);
  FBrokerNoPattern := ConfigSystem.ReadString(ccInput, ckBrokerNo, cdBrokerNo);

  //通过读配置,设置最大委托数量
  MaxEntrustVol := ConfigSystem.ReadInteger(ccInput, ckMaxEntrustVol,
    cdMaxEntrustVol);
  if MaxEntrustVol > 0 then
    fdEntrustVol.Checker.Max := MaxEntrustVol
  else
    fdEntrustVol.Checker.Max := cdMaxEntrustVol;
  fdEntrustVol.Hint := '委托数量:大于0,且小于等于' +
    inttostr(Trunc(fdEntrustVol.Checker.Max)) + '的整数';

  //通过读配置,设置最大现金存取金额
  MaxCashSum := ConfigSystem.ReadFloat(ccInput, ckMaxCashSum, cdMaxCashSum);
  if MaxCashSum > 0 then
    fdCashDomain.Checker.Max := MaxCashSum
  else
    fdCashDomain.Checker.Max := cdMaxCashSum;
  fdCashDomain.Hint := '现金金额:大于0,且小于等于' +
    FloatToStr(fdCashDomain.Checker.Max) + '的数';

  //通过读配置,设置最大存折(支票)存取金额
  MaxBankBookCheckSum := ConfigSystem.ReadFloat(ccInput, ckMaxBankBookCheckSum,
    cdMaxBankBookCheckSum);
  if MaxBankBookCheckSum > 0 then
    fdBankBookCheckDomain.Checker.Max := MaxBankBookCheckSum
  else
    fdBankBookCheckDomain.Checker.Max := cdMaxBankBookCheckSum;
  fdBankBookCheckDomain.Hint := '存折(支票)金额：大于0,小于等于' +
    FloatToStr(fdBankBookCheckDomain.Checker.Max) + '的数';

  //wlj 20031219 读取价格的格式
  FPriceFormat := ConfigSystem.ReadString(ccInput, ckPriceFormat,
    cdPriceFormat);
  FPricePrecision := ConfigSystem.ReadInteger(ccInput, ckPircePrecision,
    cdPricePrecision);

  if FPricePrecision > 0 then //修改domain的hint,加上小数点位数表示.
  begin
    fdPrice.Hint := fdPrice.Hint + ',' + IntToStr(FPricePrecision) + '位小数';
    fdPrice2.Hint := fdPrice2.Hint + ',' + IntToStr(FPricePrecision) + '位小数';
  end
  else
  begin
    fdPrice.Hint := fdPrice.Hint + ',整数';
    fdPrice2.Hint := fdPrice2.Hint + ',整数';
  end;
end;

function TComCmdDefinition.GetCustomer(const BranchCode,
  CustomerNo: string): TKSAbstractCustomerInfo;
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetCustomerInfo.ID,
    ctGetCustomerInfo.Version);
  try
    Command.ParamData('查询营业部').SetString(BranchCode);
    Command.ParamData('客户号').SetString(CustomerNo);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    if (Dataset = nil) or Dataset.IsEmpty then
      Result := nil
    else
      Result := TKSCustomerInfo.Create(Dataset);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

function TComCmdDefinition.GetBroker(const BranchCode,
  BrokerNo: string): TKSAbstractBrokerInfo;
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetBrokerInfo.ID,
    ctGetBrokerInfo.Version);
  try
    Command.ParamData('查询营业部').SetString(BranchCode);
    Command.ParamData('经纪人号').SetString(BrokerNo);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    if (Dataset = nil) or Dataset.IsEmpty then
      Result := nil
    else
      Result := TKSBrokerInfo.Create(Dataset);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

procedure TComCmdDefinition.fdCheckTimeCheckValid(WorkField: TWVField);
var
  TimeStr: string;
  OutPutTimeStr: string;
begin
  inherited;
  TimeStr := WorkField.Data.AsString;
  OutPutTimeStr := TimeStr;
  if TimeStr = '' then
    exit;
  if (Length(TimeStr) <> 8) and (Length(TimeStr) <> 6) then
  begin
    WorkField.Valid := false;
    exit;
  end;
  if Length(TimeStr) = 6 then
    TimeStr := copy(TimeStr, 1, 2) + ':' + copy(TimeStr, 3, 2) + ':' +
      copy(TimeStr, 5, 2);
  WorkField.Valid := CheckTimeValid(TimeStr);
  if WorkField.Valid then
    WorkField.Data.SetString(OutPutTimeStr);
end;

procedure TComCmdDefinition.fdTimeReCheckCheckValid(WorkField: TWVField);
var
  CheckedFieldName: string;
  CheckedField: TWVField;
  FormatStartTime, FormatEndTime, TimeStr: string;
begin
  inherited;
  WorkField.Valid := false;
  TimeStr := WorkField.Data.AsString;
  if TimeStr = '' then
    exit;
  if (Length(TimeStr) <> 8) and (Length(TimeStr) <> 6) then
  begin
    WorkField.Valid := false;
    exit;
  end;
  if Length(TimeStr) = 6 then
    Timestr := copy(TimeStr, 1, 2) + ':' + copy(TimeStr, 3, 2) + ':' +
      copy(TimeStr, 5, 2);
  if not CheckTimeValid(TimeStr) then
    exit;
  CheckedFieldName := WorkField.MonitorValueChangedFields;
  CheckedFieldName := StringReplace(CheckedFieldName, '|', '', [rfReplaceAll]);
  CheckedField := WorkField.WorkView.FindField(CheckedFieldName);
  if CheckedField = nil then
    exit;

  if not (CheckTimeValid(CheckedField.Data.AsString)) then
    exit;
  FormatStartTime := CheckedField.Data.AsString;
  FormatEndTime := TimeStr;
  if (StrtoTime(FormatStartTime) > strtoTime(FormatEndTime)) then
  begin
    WorkField.Valid := false;
    WorkField.SetInvalidMessage(Format(SInvalidSmallData,
      [CheckedField.Caption]));
  end
  else
    WorkField.Valid := true;

  if WorkField.Valid then
    WorkField.Data.SetString(TimeStr)
end;

function TComCmdDefinition.CheckTimeValid(const TimeString: string): Boolean;
begin
  Result := False;
  if (TimeString = '') or (Length(TimeString) <> 8) then
    Exit;
  try
    StrToTime(TimeString);
    Result := True;
  except
    Result := False;
  end;
end;

procedure TComCmdDefinition.fdCompDataCheckValid(WorkField: TWVField);
begin
  CompDataCheck(WorkField, False);
end;

procedure TComCmdDefinition.CreateStockMarkets;
begin
  if FSHAStocks = nil then
    FSHAStocks := TObjectList.Create;
  if FSZAStocks = nil then
    FSZAStocks := TObjectList.Create;
  if FSHBStocks = nil then
    FSHBStocks := TObjectList.Create;
  if FSZBStocks = nil then
    FSZBStocks := TObjectList.Create;
  if FOtherStocks = nil then
    FOtherStocks := TObjectList.Create;
end;

function TComCmdDefinition.GetStock(const SecCode, Market: string):
  TKSAbstractSecInfo;
begin
  Result := FindStock(SecCode, Market);
  if Result = nil then
    Context.GetDialogSystem.ShowError(Format('在%s市场不存在代码为%s的证券',
      [GetIdObjectName(deMarket, Market), SecCode]));
end;

function TComCmdDefinition.SearchStock(const SecCode, Market: string; StockList:
  TObjectList): TKSAbstractSecInfo;
var
  I: Integer;
begin
  for I := 0 to StockList.Count - 1 do
  begin
    Result := TKSAbstractSecInfo(StockList[I]);
    if Result.SecCode = SecCode then
      Exit;
  end;
  Result := RequestStockInfo(SecCode, Market, StockList);
end;

function TComCmdDefinition.RequestStockInfo(const SecCode, Market: string;
  StockList: TObjectList): TKSAbstractSecInfo;
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetSecInfo.ID,
    ctGetSecInfo.Version);
  try
    Command.ParamData('市场代码').SetString(Market);
    Command.ParamData('证券代码').SetString(SecCode);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    Result := GetStockFromDataset(Dataset, StockList);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

procedure TComCmdDefinition.fdDateCheck2CheckValid(WorkField: TWVField);
begin
  inherited;
  WorkField.Valid := CheckDateValid(WorkField.Data.AsString, False);
end;

procedure TComCmdDefinition.fdBroketNoCheckValid(WorkField: TWVField);
var
  s: string;
begin
  inherited;
  WorkField.Valid := False;
  s := WorkField.Data.AsString;
  if s = '' then
    Exit;
  s := ExpandLeft(s, FBrokerNoPattern);
  WorkField.Data.SetString(s);
  WorkField.Valid := True;
end;

procedure TComCmdDefinition.fdBroketNo2CheckValid(WorkField: TWVField);
var
  s: string;
begin
  inherited;
  WorkField.Valid := True;
  s := WorkField.Data.AsString;
  if s = '' then
    Exit;
  s := ExpandLeft(s, FBrokerNoPattern);
  WorkField.Data.SetString(s);
  WorkField.Valid := True;
end;

procedure TComCmdDefinition.GetBrokerInfo(const BranchCode,
  BrokerNo: string; BrokerInfos: TObjectList);
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetBrokerInfo.ID,
    ctGetBrokerInfo.Version);
  try
    Command.ParamData('查询营业部').SetString(BranchCode);
    Command.ParamData('经纪人号').SetString(BrokerNo);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    GetBrokerInfosFromDataset(Dataset, BrokerInfos);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

procedure TComCmdDefinition.GetCustomerInfo(const BranchCode,
  CustomerNo: string; CustomerInfos: TObjectList);
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetCustomerInfo.ID,
    ctGetCustomerInfo.Version);
  try
    Command.ParamData('查询营业部').SetString(BranchCode);
    Command.ParamData('客户号').SetString(CustomerNo);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    GetCustomerInfosFromDataset(Dataset, CustomerInfos);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

procedure TComCmdDefinition.fdCompData2CheckValid(WorkField: TWVField);
begin
  CompDataCheck(WorkField, True);
end;

procedure TComCmdDefinition.fdBooleanCheckValid(WorkField: TWVField);
begin
  inherited;
  if WorkField.DataType = kdtBoolean then
    if WorkField.Data.IsEmpty then
      WorkField.Valid := False
    else
      WorkField.Valid := WorkField.Data.AsBoolean;
end;

procedure TComCmdDefinition.GetBranch2BankInfo(const BranchCode,
  CurrencyType, BankCode: string; BankInfos: TObjectList);
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetBranch2Bank.ID,
    ctGetBranch2Bank.Version);
  try
    Command.ParamData('查询.营业部').SetString(BranchCode);
    Command.ParamData('查询.货币代码').SetString(CurrencyType);
    Command.ParamData('查询.银行代码').SetString(BankCode);
    Command.ParamData('包含子营业部').SetInteger(1);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    GetBankInfosFromDataset(Dataset, BankInfos);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

procedure TComCmdDefinition.fpAgentDateFieldToCtrl(Field: TWVField;
  Ctrl: TObject; const DataPresentType: TDataPresentType;
  const Param: string; var Handled: Boolean);
var
  ExpireDate: string;
begin
  inherited;
  if Ctrl is TWVLabel then
  begin
    Handled := True;
    ExpireDate := Field.Data.AsString;
    if (ExpireDate <> '') and (ExpireDate < GetToday) then
    begin
      // 过期
      TWVLabel(Ctrl).Caption := Format(SOutOfDate, [ExpireDate]);
      TWVLabel(Ctrl).Font.Color := clRed;
    end
    else
    begin
      // 正常
      TWVLabel(Ctrl).Caption := ExpireDate;
      TWVLabel(Ctrl).ParentFont := True;
    end;
  end;
end;

procedure TComCmdDefinition.fdOperator2CheckValid(WorkField: TWVField);
begin
  inherited;
  fdOperatorCheckValid(WorkField);
  if WorkField.Data.AsString = '' then
    WorkField.Valid := True;
end;

function TComCmdDefinition.FindStock(const SecCode,
  Market: string): TKSAbstractSecInfo;
begin
  Result := nil;
  CreateStockMarkets;
  if Market = '1' then
    Result := SearchStock(SecCode, Market, FSHAStocks);
  if Market = '2' then
    Result := SearchStock(SecCode, Market, FSZAStocks);
  if Market = '3' then
    Result := SearchStock(SecCode, Market, FSHBStocks);
  if Market = '4' then
    Result := SearchStock(SecCode, Market, FSZBStocks)
  else
    Result := SearchStock(SecCode, Market, FOtherStocks);
end;

procedure TComCmdDefinition.FormatAndValidSecField(WorkField: TWVField;
  Required: Boolean);
var
  StockNo, Market: string;
  Valid: Boolean;
  CheckedFieldName: string;
  CheckedField: TWVField;
begin
  inherited;
  if WorkField.Valid then
  begin
    // 格式基本正确
    StockNo := WorkField.data.Asstring;
    if StockNo <> '' then
    begin
      CheckedFieldName := WorkField.MonitorValueChangedFields;
      CheckedFieldName := StringReplace(CheckedFieldName, '|', '',
        [rfReplaceAll]);
      CheckedField := WorkField.WorkView.FindField(CheckedFieldName);
      if (CheckedField <> nil) and (CheckedField.Data.AsString <> '') then
        Market := CheckedField.Data.AsString
      else
        Market := '2';
      Valid := FormatAndValidSecurityCode(Market, StockNo);
      if StockNo <> WorkField.Data.AsString then
        WorkField.Data.SetString(StockNo);
    end
    else
      Valid := not Required;
    WorkField.Valid := Valid;
  end;
  // else //格式不正确，例如包含非法字符
end;

procedure TComCmdDefinition.fdStockNoExCheckValid(WorkField: TWVField);
var
  WorkView: TWorkView;
  MarketField, SecurityNameField, SecurityObjField: TWVField;
  // 定义几个字段对象方便使用
  SecInfo: TKSAbstractSecInfo;
  Required: Boolean;
  AllowTypes: string;
  Market, SecCode: string;
begin
  // 注意，该字段的MonitorValueChangedFields='|市场|'，
  // 当市场发生改变的时候，自动触发证券代码字段的CheckValid事件，
  // 所以不需要再加一个专门的Monitor

  WorkView := WorkField.WorkView;

  // 先获得相关的字段，
  // 一方面可以优化代码减少对根据名称查找对象的操作，FieldByName()
  // 另一方面增强可读性和维护性，例如字段名称发生改变，只需要在一个集中的地方处理。

  // 先根据MonitorValueChangedFields获取市场字段和市场代码
  MarketField := GetMonitorField(WorkField);
  if MarketField <> nil then
    Market := MarketField.Data.AsString
  else
    Market := '';
  // 根据市场代码格式化（补齐）字段
  if WorkField.Valid and (Market <> '') then
  begin
    SecCode := WorkField.Data.AsString;
    WorkField.Valid := FormatAndValidSecurityCode(Market, SecCode);
    if SecCode <> WorkField.Data.AsString then
      WorkField.Data.SetString(SecCode);
  end
  else
    WorkField.Valid := False;

  SecurityNameField :=
    WorkView.FindField(WorkField.Features.Values[SecNameParam]);
  SecurityObjField :=
    WorkView.FindField(WorkField.Features.Values[SecObjParam]);

  if WorkField.Valid then
  begin
    // 一个格式有效的证券代码
    SecInfo := ComCmdDefinition.FindStock(WorkField.Data.AsString, Market);
    if SecInfo <> nil then
    begin
      // 有该证券
      if SecurityNameField <> nil then
        SecurityNameField.Data.SetString(SecInfo.SecName);
      if SecurityObjField <> nil then
        SecurityObjField.Data.SetObject(SecInfo);
      AllowTypes := WorkField.Features.Values[AllowSecTypeParam];
      WorkField.Valid := (AllowTypes = '') or (Pos(SecInfo.SecType, AllowTypes)
        > 0);
      if not WorkField.Valid then
      begin
        WorkField.ErrorMessage :=
          WorkField.Features.Values[NotAllowSecErrorParam];
        WorkField.Hint := ' '; // 屏蔽掉显示正确格式的说明
      end;
    end
    else
    begin
      // 无该证券
      if SecurityNameField <> nil then
        SecurityNameField.Data.Clear;
      if SecurityObjField <> nil then
        SecurityObjField.Data.Clear;
      WorkField.Valid := False;
      WorkField.ErrorMessage := SNotExist;
      WorkField.Hint := ' '; // 屏蔽掉显示正确格式的说明
    end;
  end
  else
  begin
    // 一个格式无效的证券代码
    if SecurityNameField <> nil then
      SecurityNameField.Data.Clear;
    if SecurityObjField <> nil then
      SecurityObjField.Data.Clear;
    Required := WorkField.Features.Values[RequiredSecParam] = '1';
    {
    if (WorkField.Data.AsString='') and not Required then
    begin
      // 为空同时允许不输
      WorkField.Valid := True;
    end else
    begin
      WorkField.Valid := False;
      //WorkField.ErrorMessage := SFormatError; // 千万不要设置ErrorMessage，因为下层会写一些消息，例如包含非法字符
      WorkField.Hint := ''; // 显示出正确格式的说明
    end;
    }
    if WorkField.Data.AsString = '' then
    begin
      WorkField.Valid := not Required;
      WorkField.ErrorMessage := SNotEmpty;
      WorkField.Hint := ' '; // 屏蔽掉显示正确格式的说明
    end
    else
    begin
      WorkField.Valid := False;
      //WorkField.ErrorMessage := SFormatError; // 千万不要设置ErrorMessage，因为下层会写一些消息，例如包含非法字符
      WorkField.Hint := ''; // 显示出正确格式的说明
    end;
  end;
end;

procedure TComCmdDefinition.fdBroketNoExCheckValid(WorkField: TWVField);
var
  WorkView: TWorkView;
  BranchNoField, BroketNameField, BroketObjField: TWVField;
  // 定义几个字段对象方便使用
  BroketInfo: TKSAbstractBrokerInfo;
  Required: Boolean;
  BranchCode, BroketNo: string;
begin
  // 注意，该字段的MonitorValueChangedFields='|营业部|'，
  // 当营业部发生改变的时候，自动触发经纪人号字段的CheckValid事件，
  // 所以不需要再加一个专门的Monitor
  inherited;
  WorkView := WorkField.WorkView;

  // 先获得相关的字段，
  // 一方面可以优化代码减少对根据名称查找对象的操作，FieldByName()
  // 另一方面增强可读性和维护性，例如字段名称发生改变，只需要在一个集中的地方处理。

  // 先根据MonitorValueChangedFields获取营业部字段和营业部代码
  BranchNoField := GetMonitorField(WorkField);
  if BranchNoField <> nil then
    BranchCode := BranchNoField.Data.AsString
  else
    BranchCode := '';
  // 根据营业部格式化（补齐）字段
  if WorkField.Valid and (BranchCode <> '') then
  begin
    BroketNo := WorkField.Data.AsString;
    WorkField.Valid := FormatAndValidBrokerNo(BroketNo);
    if BroketNo <> WorkField.Data.AsString then
      WorkField.Data.SetString(BroketNo);
  end
  else
    WorkField.Valid := False;
  BroketNameField :=
    WorkView.FindField(WorkField.Features.Values[BroketNameParam]);
  BroketObjField :=
    WorkView.FindField(WorkField.Features.Values[BroketObjParam]);
  if WorkField.Valid then
  begin
    // 一个格式有效的经纪人号
    BroketInfo := ComCmdDefinition.GetBroker(BranchCode,
      WorkField.Data.AsString);
    if BroketInfo <> nil then
    begin
      // 有该经纪人号
      if BroketNameField <> nil then
        BroketNameField.Data.SetString(BroketInfo.BrokerName);
      if BroketObjField <> nil then
        BroketObjField.Data.SetObject(BroketInfo);
    end
    else
    begin
      // 无该证券
      if BroketNameField <> nil then
        BroketNameField.Data.Clear;
      if BroketObjField <> nil then
        BroketObjField.Data.Clear;
      WorkField.Valid := False;
      WorkField.ErrorMessage := SNotExist;
      WorkField.Hint := ' '; // 屏蔽掉显示正确格式的说明
    end;
  end
  else
  begin
    // 一个格式无效的经纪人号
    if BroketNameField <> nil then
      BroketNameField.Data.Clear;
    if BroketObjField <> nil then
      BroketObjField.Data.Clear;
    Required := WorkField.Features.Values[RequiredSecParam] = '1';
    {
    if (WorkField.Data.AsString='') and not Required then
    begin
      // 为空同时允许不输
      WorkField.Valid := True;
    end else
    begin
      WorkField.Valid := False;
      //WorkField.ErrorMessage := SFormatError; // 千万不要设置ErrorMessage，因为下层会写一些消息，例如包含非法字符
      WorkField.Hint := ''; // 显示出正确格式的说明
    end;
    }
    if WorkField.Data.AsString = '' then
    begin
      WorkField.Valid := not Required;
      WorkField.ErrorMessage := SNotEmpty;
      WorkField.Hint := ' '; // 屏蔽掉显示正确格式的说明
    end
    else
    begin
      WorkField.Valid := False;
      //WorkField.ErrorMessage := SFormatError; // 千万不要设置ErrorMessage，因为下层会写一些消息，例如包含非法字符
      WorkField.Hint := ''; // 显示出正确格式的说明
    end;
  end;
end;

function TComCmdDefinition.FormatAndValidBrokerNo(var BrokerNo: string):
  Boolean;
var
  I: Integer;
begin
  I := length(BrokerNo);
  if (I < 10) and (I > 0) then
  begin
    BrokerNo := ExpandLeft(BrokerNo, FBrokerNoPattern);
    result := True;
  end
  else
    result := False;
end;

procedure TComCmdDefinition.QueryControl(const QueryMethod: string;
  CustField, DeptField: TWVField; CustNo: TKSAccountEdit;
  BranchCode: TWVComboBox);
begin
  CustNo.Reset;
  if QueryMethod = '1' then //按营业部查询
  begin
    CustField.Constrained := False;
    DeptField.Reset;
    CustNo.Enabled := False;
    CustNo.Required := False;
    //    BranchCode.Enabled := IsCenterDepartment;
    BranchCode.Enabled := True;
  end
  else //按客户号查询
  begin
    CustField.Constrained := True;
    DeptField.Data.Clear;
    CustNo.Enabled := True;
    CustNo.Required := True;
    BranchCode.Enabled := False;
  end;
end;

procedure TComCmdDefinition.CompDataCheck(WorkField: TWVField;
  IsZeroEqueltoAll: Boolean; IsBig: Boolean = True; RetouchNum: Double = 0);
var
  CheckedField: TWVField;
  BigData, SmallData: string;
begin
  inherited;
  WorkField.Valid := False;
  if WorkField.Data.AsString = '' then
    Exit;
  if IsZeroEqueltoAll and (WorkField.Data.AsString = '0') then
  begin
    WorkField.Valid := True;
    Exit;
  end;
  CheckedField := GetMonitorField(WorkField);
  if CheckedField = nil then
    Exit;
  if CheckedField.Data.AsString = '' then
    Exit;
  if IsBig then
  begin
    SmallData := CheckedField.Data.AsString;
    BigData := WorkField.Data.AsString;
    if (StrToFloat(BigData) + RetouchNum) < StrToFloat(SmallData) then
    begin
      WorkField.Valid := False;
      WorkField.Hint := ' ';
      if RetouchNum = 0 then
        WorkField.SetInvalidMessage(Format(SInvalidSmallData,
          [CheckedField.Caption]));
      if RetouchNum > 0 then
        WorkField.SetInvalidMessage(Format('应该至少比%s大%f',
          [CheckedField.Caption, RetouchNum]));
      if RetouchNum < 0 then
        WorkField.SetInvalidMessage(Format('应该至多比%s少%f',
          [CheckedField.Caption, Abs(RetouchNum)]));
    end
    else
      WorkField.Valid := True;
  end
  else
  begin
    BigData := CheckedField.Data.AsString;
    SmallData := WorkField.Data.AsString;
    if (StrToFloat(BigData) + RetouchNum) < StrToFloat(SmallData) then
    begin
      WorkField.Valid := False;
      WorkField.Hint := ' ';
      if RetouchNum = 0 then
        WorkField.SetInvalidMessage(Format(SInvalidBigData,
          [CheckedField.Caption]));
      if RetouchNum > 0 then
        WorkField.SetInvalidMessage(Format('应该至多比%s多%f',
          [CheckedField.Caption, RetouchNum]));
      if RetouchNum < 0 then
        WorkField.SetInvalidMessage(Format('应该至少比%s少%f',
          [CheckedField.Caption, Abs(RetouchNum)]));
    end
    else
      WorkField.Valid := True;
  end;
end;

{
 Function:获取营业部某参数的值
 Writer  :  Zeng Chuang Neng
 Date    : 2001.10.23
}
(*
function TComCmdDefinition.GetBranchParam(ParamCode: string;const BranchCode:string=''): string;
var
  Command : TWVCommand;
  Dataset : TDataset;
  i:integer;
begin
  CheckObject(Context,'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetBranchParam.ID,ctGetBranchParam.Version);
  try
    Command.ParamData('参数代码').SetString(ParamCode);
    if BranchCode='' then
      Command.ParamData('查询营业部代码').SetString(Context.ParamData(svDepartNoName).AsString)
    else
      Command.ParamData('查询营业部代码').SetString(BranchCode);
    Command.ParamData('是否需要并列输出').SetInteger(1);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command);
    //Result := Command.ParamData('参数值').AsString;
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    if DataSet=nil then exit;

    //如果查出来只有一条记录，则直接赋值
    if DataSet.RecordCount=1  then
      Result:=DataSet.FieldByName('scert_no').Asstring
    else
    //如果查出来不止一条记录，则取本营业部的参数值
    if DataSet.RecordCount>1 then
    begin
      for i:=0 to DataSet.RecordCount -1 do
      begin
        if (DataSet.FieldByName('sbranch_code0').Asstring=BranchCode) then
        Result :=DataSet.FieldByName('scert_no').Asstring;
      end;
    end;
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;
*)

procedure TComCmdDefinition.fdCompData3CheckValid(WorkField: TWVField);
begin
  inherited;
  CompDataCheck(WorkField, False, False);
end;

function TComCmdDefinition.GetReportDay: string;
{
// old version
var
  Command : TWVCommand;
begin
  CheckObject(Context,'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetSystemDate.ID,ctGetSystemDate.Version);
  try
    Command.ParamData('发生营业部').SetString(CurrentDepartmentNo);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command,False);
    Result := Command.ParamData('轧帐日期').AsString;
  finally
    Command.Free;
  end;
end;
}
// new
begin
  //  TryRefreshDates(True);
  //  Result := Context.GetParamValue(svReportDateName);
end;

function TComCmdDefinition.GetStationAuth(const BranchCode,
  Station: string): TKSAbstractStationAuthInfo;
var
  Command: TWVCommand;
  Dataset: TDataset;
  Branch: string;
begin
  CheckObject(Context, 'Invalid Context');
  if BranchCode = '' then
    Branch := CurrentDepartmentNo
  else
    Branch := BranchCode;
  Command := Context.CommandFactory.NewCommand(ctQueryStationAuth.ID,
    ctQueryStationAuth.Version);
  try
    Command.ParamData('营业部').SetString(Branch);
    Command.ParamData('岗位代码').SetString(Station);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    if (Dataset = nil) or Dataset.IsEmpty then
      Result := nil
    else
      Result := TKSStationAuthInfo.Create(Dataset);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

procedure TComCmdDefinition.GetStationAuthInfo(const BranchCode,
  Station: string; StationInfos: TObjectList);
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctQueryStationAuth.ID,
    ctQueryStationAuth.Version);
  try
    Command.ParamData('营业部').SetString(BranchCode);
    Command.ParamData('岗位代码').SetString(Station);
    Command.ParamData('包含子营业部').SetInteger(1);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    GetStationInfosFromDataset(Dataset, StationInfos);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

procedure TComCmdDefinition.GetTreatyGroupInfos(const BranchCode, TreatyStatus,
  IsDownToChild: string;
  const IsContainChild, QueryMode, GroupNo: Integer; GroupInfos: TObjectList);
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand('查询合作配售协议分组信息', 1);
  try
    Command.ParamData('被查询营业部').SetString(BranchCode);
    Command.ParamData('协议状态').SetString(TreatyStatus);
    Command.ParamData('是否向下级发布').SetString(IsDownToChild);
    Command.ParamData('查询方式').SetInteger(QueryMode);
    Command.ParamData('协议组号').SetInteger(GroupNo);
    Command.ParamData('查询是否包含下属').SetInteger(IsContainChild);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    GetGroupInfosFromDataset(Dataset, GroupInfos);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

procedure TComCmdDefinition.fpNumberFieldToCtrl(Field: TWVField;
  Ctrl: TObject; const DataPresentType: TDataPresentType;
  const Param: string; var Handled: Boolean);
begin
  inherited;
  if Ctrl is TWVLabel then
  begin
    Handled := True;
    if Field.Data.AsString <> '' then
      if Param = '' then
        TWVLabel(Ctrl).Caption := FormatFloat(NumberFormat, Field.Data.AsFloat)
      else
        TWVLabel(Ctrl).Caption := FormatFloat(Param, Field.Data.AsFloat)
    else
      TWVLabel(Ctrl).Caption := '';
  end
end;

procedure TComCmdDefinition.fpNumberSetFieldHandler(Field: TField;
  const DataPresentType: TDataPresentType; const Param: string;
  var Handled: Boolean);
begin
  inherited;
  if Field is TNumericField then
  begin
    if Param = '' then
      TNumericField(Field).DisplayFormat := NumberFormat
    else
      TNumericField(Field).DisplayFormat := Param;
    Handled := True;
  end;
end;

function TComCmdDefinition.GetMonitorField(WorkField: TWVField): TWVField;
var
  CheckedFieldName: string;
begin
  CheckedFieldName := WorkField.MonitorValueChangedFields;
  CheckedFieldName := StringReplace(CheckedFieldName, '|', '', [rfReplaceAll]);
  Result := WorkField.WorkView.FindField(CheckedFieldName);
end;

procedure TComCmdDefinition.fdYearMonthCheckCheckValid(
  WorkField: TWVField);
begin
  inherited;
  WorkField.Valid := CheckDateValid(WorkField.Data.AsString + '01', False);
end;

procedure TComCmdDefinition.fdOperatorExCheckValid(WorkField: TWVField);
var
  WorkView: TWorkView;
  OperatorNameField: TWVField;
  OperatorNoName, OperatorNo: string;
  Required, CheckExits: Boolean;
  EmpInfo: TKSAbstractEmpInfo;
begin
  inherited;
  OperatorNo := WorkField.Data.AsString;
  WorkView := WorkField.WorkView;
  OperatorNoName := WorkField.Features.Values[OperatorName];
  OperatorNameField := WorkView.FindField(OperatorNoName);
  if OperatorNameField <> nil then
    OperatorNameField.Data.Clear;
  Required := WorkField.Features.Values[RequiredOperatorNo] = '1';
  CheckExits := WorkField.Features.Values[CheckOperatorExits] = '1';
  if OperatorNo = '' then
  begin
    WorkField.Valid := not Required;
    WorkField.ErrorMessage := SNotEmpty;
    WorkField.Hint := ' ';
  end
  else
  begin
    OperatorNo := ExpandLeft(OperatorNo, FOperatorNoPattern);
    WorkField.Data.SetString(OperatorNo);
    if not CheckExits then
    begin
      WorkField.Valid := True;
      Exit;
    end;
    EmpInfo := ComCmdDefinition.GetEmp(OperatorNo, CurrentDepartment.ID);
    if EmpInfo = nil then
    begin
      WorkField.Valid := False;
      WorkField.ErrorMessage := '不存在';
      WorkField.Hint := ' ';
    end
    else
    begin
      WorkField.Valid := True;
      if OperatorNameField <> nil then
        OperatorNameField.Data.SetString(EmpInfo.EmpName);
    end;
  end;
end;

procedure TComCmdDefinition.GetSecTypeSets(const Market: string;
  SecTypeSet: TStringList);
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetSecType.ID,
    ctGetSecType.Version);
  try
    Command.ParamData('市场代码').SetString(Market);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    GetSecTypeSetFromDataset(Dataset, SecTypeSet);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

procedure TComCmdDefinition.GetBranchInfos;
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  FBranchInfos := TObjectList.Create;
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctQueyBranch.ID,
    ctQueyBranch.Version);
  try
    Command.ParamData('查询.营业部').SetString('');
    Command.ParamData('包含子营业部').SetInteger(1);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    GetBranchInfosFromDataset(Dataset, FBranchInfos);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

function TComCmdDefinition.NeedBranchs: TObjectList;
begin
  if FBranchInfos = nil then
    GetBranchInfos;
  Result := FBranchInfos;
end;

function TComCmdDefinition.GetBranch(const Branch: string): TKSAbstractBranch;
var
  I: Integer;
begin
  NeedBranchs;
  if Branch <> '' then
    for I := 0 to FBranchInfos.Count - 1 do
    begin
      Result := TKSAbstractBranch(FBranchInfos[I]);
      if Result.Branch = Branch then
        Exit;
    end;
  Result := nil;
end;

procedure TComCmdDefinition.GetBranchInfoAdmin;
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  if InfoAdmin <> nil then
  begin
    InfoAdmin.Free;
    InfoAdmin := TInfoAdmin.Create;
  end;
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctInitQueyBranch.ID,
    ctInitQueyBranch.Version);
  try
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    if (Dataset <> nil) and (not Dataset.Eof) then
    begin
      ReadBranchInfoFromDataSet(Dataset, InfoAdmin);
    end;
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

procedure TComCmdDefinition.GetFeeLevel(const Branch, FeeType: string;
  QueryType: Integer; FeeLevelSet: TObjectList);
var
  Command: TWVCommand;
  Dataset: TDataset;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetFeeLevel.ID,
    ctGetFeeLevel.Version);
  try
    Command.ParamData('设置营业部').SetString(Branch);
    Command.ParamData('收费方式').SetString(FeeType);
    Command.ParamData('查询方式').SetInteger(QueryType);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('查询结果集').AsObject);
    GetFeeLevelInfosFromDataset(Dataset, FeeLevelSet);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

procedure TComCmdDefinition.GetWorkDay(var LastDay, CurrentDay,
  NextDay: string; const Market: string = '');
var
  Command: TWVCommand;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetWorkDate.ID,
    ctGetWorkDate.Version);
  try
    Command.ParamData('市场').SetString(Market);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    LastDay := Command.ParamData('上一个工作日').AsString;
    CurrentDay := Command.ParamData('当前工作日期').AsString;
    NextDay := Command.ParamData('下一个工作日').AsString;
  finally
    Command.Free;
  end;
end;

function TComCmdDefinition.GetLiquidate(DateType: Integer): string;
var
  Command: TWVCommand;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand(ctGetDate.ID, ctGetDate.Version);
  try
    Command.ParamData('日期类型').SetInteger(DateType);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Result := Command.ParamData('日期').AsString;
  finally
    Command.Free;
  end;
end;

procedure TComCmdDefinition.fdDeliverDateCheckValid(WorkField: TWVField);
var
  DateStr: string;
begin
  inherited;
  DateStr := WorkField.Data.AsString;
  if Trim(DateStr) = '' then
  begin
    WorkField.Valid := False;
    Exit;
  end;
  if Length(DateStr) = 6 then
    DateStr := '20' + DateStr
  else if Length(DateStr) = 4 then
    DateStr := '20' + DateStr + '01'
  else
  begin
    WorkField.Valid := False;
    Exit;
  end;
  WorkField.Valid := CheckDateValid(DateStr, False);
end;

procedure TComCmdDefinition.fdDateReCheck2CheckValid(WorkField: TWVField);
var
  CheckedField: TWVField;
begin
  inherited;
  WorkField.Valid := False;
  CheckedField := GetMonitorField(WorkField);
  if CheckedField = nil then
    Exit;
  if not (CheckDateValid(CheckedField.Data.AsString, False)) then
    Exit;
  if not CheckDateValid(WorkField.Data.AsString, False) then
    Exit;
  //(StrComp(PChar(CheckedField.Data.AsString),PChar(WorkField.Data.AsString))>0)

  if ((CheckedField.Data.AsString = '') and
    CheckDateValid(WorkField.Data.AsString, False))
    or ((WorkField.Data.AsString = '') and
    CheckDateValid(CheckedField.Data.AsString, False)) then
  begin
    WorkField.Valid := true;
    Exit;
  end;

  if DBStrDateToDateTime(CheckedField.Data.AsString) >
    DBStrDateToDateTime(WorkField.Data.AsString) then
  begin
    WorkField.Valid := False;
    WorkField.SetInvalidMessage(Format(SInvalidSmallData,
      [CheckedField.Caption]));
    WorkField.Hint := ' ';
  end
  else
    WorkField.Valid := true;
end;

procedure TComCmdDefinition.fdDeliverDate2CheckValid(WorkField: TWVField);
begin
  inherited;
  if WorkField.Data.AsString = '' then
  begin
    WorkField.Valid := True;
    Exit;
  end;
  fdDeliverDateCheckValid(WorkField);
end;

procedure TComCmdDefinition.fpPriceCtrlToField(Ctrl: TObject;
  Field: TWVField; const DataPresentType: TDataPresentType;
  const Param: string; var Handled: Boolean);
begin
  inherited;
  if Ctrl is TWVEdit then
  begin
    Handled := True;
    Handled := True;
    Field.Data.AsString := TWVEdit(Ctrl).Text;
  end
end;

procedure TComCmdDefinition.fpPriceFieldToCtrl(Field: TWVField;
  Ctrl: TObject; const DataPresentType: TDataPresentType;
  const Param: string; var Handled: Boolean);
begin
  inherited;
  if Ctrl is TWVLabel then
  begin
    if Field.Data.AsString <> '' then
      if Param = '' then
        TWVLabel(Ctrl).Caption := FormatFloat(FPriceFormat, Field.Data.AsFloat)
      else
        TWVLabel(Ctrl).Caption := FormatFloat(Param, Field.Data.AsFloat)
    else
      TWVLabel(Ctrl).Caption := '';
  end
  else if Ctrl is TWVEdit then
  begin
    Handled := True;
    if Field.Data.AsString <> '' then
      TWVEdit(Ctrl).Text := FloatToStrF(Field.Data.AsFloat, ffFixed, 9,
        FPricePrecision)
    else
      TWVEdit(Ctrl).Text := '';
  end

end;

procedure TComCmdDefinition.fpPriceSetFieldHandler(Field: TField;
  const DataPresentType: TDataPresentType; const Param: string;
  var Handled: Boolean);
begin
  inherited;
  if Field is TNumericField then
  begin
    if Param = '' then
      TNumericField(Field).DisplayFormat := FPriceFormat
    else
      TNumericField(Field).DisplayFormat := Param;
    Handled := True;
  end;
end;

procedure TComCmdDefinition.fdPriceCheckValid(WorkField: TWVField);
var
  DateStr: string;
  iPos: integer;
  iLen: integer;
begin
  inherited;
  DateStr := WorkField.Data.AsString;
  if DateStr = '' then
  begin
    WorkField.Valid := False;
    exit;
  end;
  if DateStr = '0' then //wlj 20040318 不允许为零
  begin
    WorkField.Valid := False;
    exit;
  end;

  iPos := pos('.', DateStr);
  iLen := Length(DateStr);
  //如果没有小数点,总是有效的.
  //如果有小数点, 小数位数必须小于允许的小数点
  if iPos > 0 then //有小数点
  begin //允许小数点,并且小数
    if iLen - iPos > FPricePrecision then
      WorkField.Valid := False
    else
      WorkField.Valid := True;
  end
  else
    WorkField.Valid := True;

  //wlj 20040311 如果超过最大值则报错
  if (Abs(StrToFloat(DateStr)) >= 100000) then
    WorkField.Valid := False;
end;

procedure TComCmdDefinition.fdPrice2CheckValid(WorkField: TWVField);
begin
  inherited;
  if WorkField.Data.AsString = '0' then
  begin
    WorkField.Valid := True;
    Exit;
  end;
  fdPriceCheckValid(WorkField);

end;

//rding,20040526

procedure TComCmdDefinition.fdSysNoCheckValid(WorkField: TWVField);
var
  SysNo: string;
  iCount: Integer;
begin
  inherited;
  if WorkField.Valid then
  begin
    SysNo := WorkField.Data.AsString;
    if SysNo = '' then
      WorkField.Valid := not WorkField.Checker.Required
    else
    begin
      if Length(SysNo) > 10 then
      begin
        WorkField.Valid := False;
        exit;
      end;
      if not (SysNo[1] in ['m', 'M', '0'..'9']) then
      begin
        WorkField.Valid := False;
        exit;
      end;
      for iCount := 2 to Length(SysNo) do
      begin
        if not (SysNo[iCount] in ['0'..'9']) then
        begin
          WorkField.Valid := False;
          exit;
        end;
      end;
    end;
  end;
end;

procedure TComCmdDefinition.fdNameCheckValid(WorkField: TWVField);
var
  S, S1: string;
  Len: Integer;
  TotalLen: Integer;
  i: Integer;
begin
  inherited;
  S := WorkField.Data.AsString;
  Len := Length(S);
  if (S <> '') then
  begin
    TotalLen := 0;
    i := 0;
    while (i <= len) do
    begin
      if (i < len) and boolean(byte(S[i]) and $80) and boolean(byte(S[i + 1])
        and
        $80) then
      begin
        TotalLen := TotalLen + 3;
        i := i + 1;
      end
      else
      begin
        TotalLen := TotalLen + 1;
        i := i + 1;
      end;
    end;
    if TotalLen > 60 then
      WorkField.Valid := False;
  end;
end;

end.

