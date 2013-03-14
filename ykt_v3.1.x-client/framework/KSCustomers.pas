unit KSCustomers;
{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSCustomers
   <What>定义客户、账号等与证券系统相关的实体对象
   <Written By> Huang YanLai (黄燕来)、张国彦
   <History>
**********************************************}


{ TODO : 尚未实现少数对象的Clone操作。 }
interface

uses SysUtils, Classes, DB, Contnrs;

type
  TKSAbstractObject = class(TObject)
  public
    function    GetID : string; virtual; abstract;
    function    GetName : string; virtual; abstract;
    function    GetDisplayLabel : string; virtual; abstract;
    procedure   Assign(Source : TKSAbstractObject); virtual;
    function    GetParamValue(const ParamName : string): string; virtual; abstract;
  end;

  TKSAbstractCustomer = class(TKSAbstractObject)
  protected
    function    GetCustomerName : string; virtual; abstract;
    function    GetCustomerNo : string; virtual; abstract;
    function    GetDepartment : string; virtual; abstract;
    function    GetStatus : string; virtual; abstract;
  public
    function    GetID : string; override;
    function    GetName : string; override;
    function    GetDisplayLabel : string; override;
    function    Clone : TKSAbstractCustomer; virtual; abstract;
    property    CustomerNo : string read GetCustomerNo;
    property    CustomerName : string read GetCustomerName;
    property    Department : string read GetDepartment;
    property    Status : string read GetStatus;
  end;

  TKSAbstractCustomerInfo = class(TKSAbstractObject)
  protected
    function    GetCustomerName : string; virtual; abstract;
    function    GetCustomerNo : string; virtual; abstract;
    function    GetDepartment : string; virtual; abstract;
    function    GetStatus : string; virtual; abstract;
  public
    function    GetID : string; override;
    function    GetName : string; override;
    function    GetDisplayLabel : string; override;
    property    CustomerNo : string read GetCustomerNo;
    property    CustomerName : string read GetCustomerName;
    property    Department : string read GetDepartment;
    property    Status : string read GetStatus;
  end;

  TKSAbstractBrokerInfo = class(TKSAbstractObject)
  protected
    function    GetBrokerName : string; virtual; abstract;
    function    GetBrokerNo : string; virtual; abstract;
    function    GetDepartment : string; virtual; abstract;
    function    GetStatus : string; virtual; abstract;
  public
    function    GetID : string; override;
    function    GetName : string; override;
    function    GetDisplayLabel : string; override;
    property    BrokerNo : string read GetBrokerNo;
    property    BrokerName : string read GetBrokerName;
    property    Department : string read GetDepartment;
    property    Status : string read GetStatus;
  end;

  TKSAbstractSecAccount = class(TKSAbstractObject)
  protected
    function    GetAccount: string; virtual; abstract;
    function    GetAccountName: string; virtual; abstract;
    function    GetMarket: string; virtual; abstract;
    function    GetStatus : string; virtual; abstract;
  public
    function    GetID : string; override;
    function    GetName : string; override;
    function    GetDisplayLabel : string; override;

    property    Market : string read GetMarket;
    property    Account : string read GetAccount;
    property    AccountName : string read GetAccountName;
    property    Status : string read GetStatus;
  end;

  TKSAbstractMoneyAccount = class(TKSAbstractObject)
  protected
    function    GetCurrencyType : string; virtual; abstract;
    function    GetCustomerNo : string; virtual; abstract;
    function    GetCanDisplay : Boolean; virtual; abstract;
  public
    function    GetID : string; override;
    function    GetName : string; override;
    function    GetDisplayLabel : string; override;

    property    CurrencyType : string read GetCurrencyType;
    property    CustomerNo : string read GetCustomerNo;
    property    CanDisplay : Boolean read GetCanDisplay;
  end;

  TKSAbstractBankAccount = class(TKSAbstractObject)
  protected
    function    GetAccount: string; virtual; abstract;
    function    GetAccountName: string; virtual; abstract;
    function    GetBank: string; virtual; abstract;
  public
    function    GetID : string; override;
    function    GetName : string; override;
    function    GetDisplayLabel : string; override;

    property    Bank : string read GetBank;
    property    Account : string read GetAccount;
    property    AccountName : string read GetAccountName;
  end;

  TKSAbstractSecInfo = class(TKSAbstractObject)
  protected
    function    GetSecCode: string; virtual; abstract;
    function    GetSecName: string; virtual; abstract;
    function    GetMarket: string; virtual; abstract;
    function    GetStatus: string; virtual; abstract;
    function    GetSecType: string; virtual; abstract;
  public
    function    GetID : string; override;
    function    GetName : string; override;
    function    GetDisplayLabel : string; override;
    property    Market : string read GetMarket;
    property    SecCode : string read GetSecCode;
    property    SecName : string read GetSecName;
    property    SecType : string read GetSecType;
    property    Status : string read GetStatus;
  end;

  TKSAbstractSeatInfo = class(TKSAbstractObject)
  protected
    function    GetSeatNo: string; virtual; abstract;
    function    GetBranchCode: string; virtual; abstract;
    function    GetMarket: string; virtual; abstract;
  public
    function    GetID : string; override;
    function    GetName : string; override;
    function    GetDisplayLabel : string; override;
    function    GetReportDisplay : string; virtual;
    property    Market : string read GetMarket;
    property    SeatNo : string read GetSeatNo;
    property    BranchCode : string read GetBranchCode;
    property    ReportDisplay : string read GetReportDisplay;
  end;

  TKSAbstractEmpInfo = class(TKSAbstractObject)
  protected
    function    GetEmpName: string; virtual; abstract;
    function    GetBranchCode: string; virtual; abstract;
    function    GetEmpNo: string; virtual; abstract;
  public
    function    GetID : string; override;
    function    GetName : string; override;
    function    GetDisplayLabel : string; override;
    property    EmpNO : string read GetEmpNo;
    property    EmpName : string read GetEmpName;
    property    BranchCode : string read GetBranchCode;
  end;

  TKSAbstractMarket = class(TKSAbstractObject)
  protected
    function    GetCurrencyType : string; virtual; abstract;
    function    GetSecurityLength: Integer; virtual; abstract;
    function    GetSecurityPattern: string; virtual; abstract;
    function    GetAccountLength: Integer; virtual; abstract;
    function    GetAccountPattern: string; virtual; abstract;
    function    GetCurrencySet: string; virtual; abstract;
    function    GetSecTypeSet: string; virtual; abstract;
    function    GetAllSecTypeSet: string; virtual; abstract;
  public
    function    GetDisplayLabel : string; override;
    property    Market : string read GetID;
    property    Name : string read GetName;
    property    CurrencyType : string read GetCurrencyType;
    property    SecurityLength : Integer read GetSecurityLength;
    property    SecurityPattern: string read GetSecurityPattern;
    property    AccountLength : Integer read GetAccountLength;
    property    AccountPattern: string read GetAccountPattern;
    property    CurrencySet: string read GetCurrencySet;
    property    SecTypeSet: string read GetSecTypeSet;
    property    AllSecTypeSet: string read GetAllSecTypeSet;
  end;

  TKSAbstractBranch = class(TKSAbstractObject)
  protected
  public
    function    GetDisplayLabel : string; override;
    property    Branch : string read GetID;
    property    Name : string read GetName;
  end;

  TKSAbstractBankInfo = class(TKSAbstractObject)
  protected
    function    GetBankName: string; virtual; abstract;
    function    GetBranchCode: string; virtual; abstract;
    function    GetBankNo: string; virtual; abstract;
    function    GetCurrency: string ; virtual; abstract;
  public
    function    GetReportDisplay: string; virtual;
    function    GetID : string; override;
    function    GetName : string; override;
    function    GetDisplayLabel : string; override;
    property    BankNO : string read GetBankNo;
    property    BankName : string read GetBankName;
    property    BranchCode : string read GetBranchCode;
    property    Currency : string read GetCurrency;
    property    ReportDisplay : string read GetReportDisplay;
  end;

  TKSAbstractStationAuthInfo = class(TKSAbstractObject)
  protected
    function    GetStationName: string; virtual; abstract;
    function    GetBranchCode: string; virtual; abstract;
    function    GetStationNo: string; virtual; abstract;
  public
    function    GetID : string; override;
    function    GetName : string; override;
    function    GetDisplayLabel : string; override;
    property    StationNO : string read GetStationNo;
    property    StationName : string read GetStationName;
    property    BranchCode : string read GetBranchCode;
  end;

  TKSAbstractGroupInfo = class(TKSAbstractObject)
  protected
    function    GetGroupName: string; virtual; abstract;
    function    GetBranchCode: string; virtual; abstract;
    function    GetGroupNo: string; virtual; abstract;
  public
    function    GetID : string; override;
    function    GetName : string; override;
    function    GetDisplayLabel : string; override;
    property    GroupNO : string read GetGroupNo;
    property    GroupName : string read GetGroupName;
    property    BranchCode : string read GetBranchCode;
  end;

  TKSAbstractFeeLevelInfo = class(TKSAbstractObject)
  protected
    function    GetFeeLevelName: string; virtual; abstract;
    function    GetBranchCode: string; virtual; abstract;
    function    GetFeeLevelNo: string; virtual; abstract;
  public
    function    GetID : string; override;
    function    GetName : string; override;
    function    GetDisplayLabel : string; override;
    property    FeeLevel : string read GetFeeLevelNo;
    property    FeeLevelName : string read GetFeeLevelName;
    property    BranchCode : string read GetBranchCode;
  end;

  TKSCustomer = class(TKSAbstractCustomer)
  private
    FParams: TStrings;
  protected
    function    GetCustomerName: string; override;
    function    GetCustomerNo: string; override;
    function    GetDepartment: string; override;
    function    GetStatus : string; override;
    //property    Params : TStrings read FParams;
  public
    constructor Create(Dataset : TDataset); overload;
    constructor Create(Customer: TKSCustomer); overload;
    destructor  Destroy;override;
    function    GetParamValue(const ParamName : string): string; override;
    procedure   Assign(Source : TKSAbstractObject); override;
    function    Clone : TKSAbstractCustomer; override;
  end;

  TKSCustomerInfo = class(TKSAbstractCustomerInfo)
  private
    FParams: TStrings;
  protected
    function    GetCustomerName: string; override;
    function    GetCustomerNo: string; override;
    function    GetDepartment: string; override;
    function    GetStatus : string; override;
  public
    constructor Create(Dataset : TDataset);
    destructor  Destroy;override;
    function    GetParamValue(const ParamName : string): string; override;
    procedure   Assign(Source : TKSAbstractObject); override;
  end;

  TKSBrokerInfo = class(TKSAbstractBrokerInfo)
  private
    FParams: TStrings;
  protected
    function    GetBrokerName: string; override;
    function    GetBrokerNo: string; override;
    function    GetDepartment: string; override;
    function    GetStatus : string; override;
  public
    constructor Create(Dataset : TDataset);
    destructor  Destroy;override;
    function    GetParamValue(const ParamName : string): string; override;
    procedure   Assign(Source : TKSAbstractObject); override;
  end;

  TKSSecAccount = class(TKSAbstractSecAccount)
  private
    FParams : TStrings;
  protected
    function    GetAccount: string; override;
    function    GetAccountName: string; override;
    function    GetMarket: string; override;
    function    GetStatus : string; override;
  public
    constructor Create(Dataset : TDataset);
    destructor  Destroy;override;
    function    GetParamValue(const ParamName : string): string; override;
    procedure   Assign(Source : TKSAbstractObject); override;
  end;

  TKSSecAccount2 = class(TKSAbstractSecAccount)
  private
    FMarket : string;
    FAccount : string;
    FAccountName: string;
    FAccountStatus : string;
  protected
    function    GetAccount: string; override;
    function    GetAccountName: string; override;
    function    GetMarket: string; override;
    function    GetStatus : string; override;
  public
    constructor Create(Customer: TKSAbstractCustomer; const AMarket: string);
    function    GetParamValue(const ParamName : string): string; override;
    procedure   Assign(Source : TKSAbstractObject); override;
  end;

  TKSMoneyAccount = class(TKSAbstractMoneyAccount)
  private
    FParams : TStrings;
  protected
    function    GetCurrencyType: string; override;
    function    GetCustomerNo: string; override;
    function    GetCanDisplay : Boolean; override;
  public
    constructor Create(Dataset : TDataset);
    destructor  Destroy;override;
    function    GetParamValue(const ParamName : string): string; override;
    procedure   Assign(Source : TKSAbstractObject); override;
  end;

  TKSBankAccount = class(TKSAbstractBankAccount)
  private
    FParams : TStrings;
  protected
    function    GetAccount: string; override;
    function    GetAccountName: string; override;
    function    GetBank: string; override;
  public
    constructor Create(Dataset : TDataset);
    destructor  Destroy;override;
    function    GetParamValue(const ParamName : string): string; override;
    procedure   Assign(Source : TKSAbstractObject); override;
  end;

  TKSSecInfo = class(TKSAbstractSecInfo)
  private
    FParams : TStrings;
  protected
    function    GetSecCode: string; override;
    function    GetSecName: string; override;
    function    GetMarket: string; override;
    function    GetStatus: string; override;
    function    GetSecType: string; override;
  public
    constructor Create(Dataset : TDataset);
    destructor  Destroy;override;
    function    GetParamValue(const ParamName : string): string; override;
    procedure   Assign(Source : TKSAbstractObject); override;
  end;

  TKSSeatInfo = class(TKSAbstractSeatInfo)
  private
    FParams : TStrings;
  protected
    function    GetSeatNo: string; override;
    function    GetBranchCode: string; override;
    function    GetMarket: string; override;
  public
    constructor Create(Dataset : TDataset);
    destructor  Destroy;override;
    function    GetParamValue(const ParamName : string): string; override;
    procedure   Assign(Source : TKSAbstractObject); override;
  end;

  TKSEmpInfo = class(TKSAbstractEmpInfo)
  private
    FParams : TStrings;
  protected
    function    GetEmpName: string; override;
    function    GetBranchCode: string; override;
    function    GetEmpNo: string; override;
  public
    constructor Create(Dataset : TDataset);
    destructor  Destroy;override;
    function    GetParamValue(const ParamName : string): string; override;
    procedure   Assign(Source : TKSAbstractObject); override;
  end;

  TKSMarket = class(TKSAbstractMarket)
  private
    FParams : TStrings;
    FSecurityLength: Integer;
    FSecurityPattern: string;
    FAccountLength: Integer;
    FAccountPattern: string;
    FSecTypeSet: string;
    FAllSecTypeSet:string;
    procedure   ReadConfig;
    procedure   ReadSecType;
  protected
    function    GetCurrencyType : string; override;
    function    GetSecurityLength: Integer; override;
    function    GetSecurityPattern: string; override;
    function    GetAccountLength: Integer; override;
    function    GetAccountPattern: string; override;
    function    GetCurrencySet: string; override;
    function    GetSecTypeSet: string; override;
    function    GetAllSecTypeSet: string; override;
  public
    constructor Create(Dataset : TDataset);
    destructor  Destroy; override;
    function    GetID : string; override;
    function    GetName : string; override;
    function    GetParamValue(const ParamName : string): string; override;
    procedure   Assign(Source : TKSAbstractObject); override;
  end;

  TKSBranch = class(TKSAbstractBranch)
  private
    FParams : TStrings;
  protected

  public
    constructor Create(Dataset : TDataset);
    destructor  Destroy; override;
    function    GetID : string; override;
    function    GetName : string; override;
    function    GetParamValue(const ParamName : string): string; override;
    procedure   Assign(Source : TKSAbstractObject); override;
  end;

  TKSBankInfo = class(TKSAbstractBankInfo)
  private
    FParams : TStrings;
  protected
    function    GetBankName: string; override;
    function    GetBranchCode: string; override;
    function    GetBankNo: string; override;
    function    GetCurrency: string ; override;
  public
    constructor Create(Dataset : TDataset);
    destructor  Destroy;override;
    function    GetParamValue(const ParamName : string): string; override;
    procedure   Assign(Source : TKSAbstractObject); override;
  end;

  TKSStationAuthInfo = class(TKSAbstractStationAuthInfo)
  private
    FParams : TStrings;
  protected
    function    GetStationName: string; override;
    function    GetBranchCode: string; override;
    function    GetStationNo: string; override;
  public
    constructor Create(Dataset : TDataset);
    destructor  Destroy;override;
    function    GetParamValue(const ParamName : string): string; override;
    procedure   Assign(Source : TKSAbstractObject); override;
  end;

  TKSGroupInfo = class(TKSAbstractGroupInfo)
  private
    FParams : TStrings;
  protected
    function    GetGroupName: string; override;
    function    GetBranchCode: string; override;
    function    GetGroupNo: string; override;
  public
    constructor Create(Dataset : TDataset);
    destructor  Destroy;override;
    function    GetParamValue(const ParamName : string): string; override;
    procedure   Assign(Source : TKSAbstractObject); override;
  end;

  TKSFeeLevelInfo = class(TKSAbstractFeeLevelInfo)
  private
    FParams : TStrings;
  protected
    function    GetFeeLevelName: string; override;
    function    GetBranchCode: string; override;
    function    GetFeeLevelNo: string; override;
  public
    constructor Create(Dataset : TDataset);
    destructor  Destroy;override;
    function    GetParamValue(const ParamName : string): string; override;
    procedure   Assign(Source : TKSAbstractObject); override;
  end;

procedure  GetParamsFromDataset(Items : TStrings; Dataset : TDataset);

procedure  GetCustomersFromDataset(Dataset : TDataset; Customers : TObjectList);

procedure  GetBrokerInfosFromDataset(Dataset : TDataset; BrokerInfos : TObjectList);

procedure  GetCustomerInfosFromDataset(Dataset : TDataset; CustomerInfos : TObjectList);

procedure  GetSecAccountsFromDataset(Dataset : TDataset; SecAccounts: TObjectList);

procedure  GetMoneyAccountsFromDataset(Dataset : TDataset; MoneyAccounts: TObjectList);

procedure  GetBankAccountsFromDataset(Dataset : TDataset; BankAccounts: TObjectList);

procedure  GetSecInfosFromDataset(Dataset : TDataset; SecInfos: TObjectList);

function   GetStockFromDataset(Dataset : TDataset; StockList: TObjectList):TKSAbstractSecInfo ;

procedure  GetSeatInfosFromDataset(Dataset : TDataset; SeatInfos: TObjectList);

procedure  GetEmpInfosFromDataset(Dataset : TDataset; EmpInfos: TObjectList);

procedure  GetMarketInfosFromDataset(Dataset : TDataset; MarketInfos: TObjectList);

procedure  GetBranchInfosFromDataset(Dataset : TDataset; BranchInfos: TObjectList);

procedure  GetSecTypeSetFromDataset(Dataset : TDataset; SecTypeSet: TStringList);

procedure  GetBankInfosFromDataset(Dataset : TDataset; BankInfos: TObjectList);

procedure GetStationInfosFromDataset(Dataset : TDataset; StationInfos: TObjectList);

procedure GetGroupInfosFromDataset(Dataset : TDataset; GroupInfos: TObjectList);

procedure GetFeeLevelInfosFromDataset(Dataset : TDataset; FeeLevelInfos: TObjectList);



{
  <Procedure>GetObjectItems
  <What>根据对象列表生成字符串列表。
  对象列表包含的对象是TKSAbstractObject对象。
  生成的字符串列表的Objects包含对应的TKSAbstractObject对象。
  <Params>
    -
  <Exception>
}
procedure  GetObjectsItems(Items : TStrings; Objects : TObjectList);

implementation

uses KSDataDictionary, KSClientConsts, KSFrameWorks,KSComCmdDefs;

procedure  GetObjectsItems(Items : TStrings; Objects : TObjectList);
var
  I : Integer;
  Obj : TKSAbstractObject;
begin
  Items.Clear;
  if Objects<>nil then
    for I:=0 to Objects.Count-1 do
    begin
      Obj := TKSAbstractObject(Objects[I]);
      Items.AddObject(Obj.GetDisplayLabel,Obj);
    end;
end;

procedure  GetParamsFromDataset(Items : TStrings; Dataset : TDataset);
var
  I : Integer;
begin
  Items.Clear;
  for I:=0 to Dataset.FieldCount-1 do
    with Dataset.Fields[I] do
      Items.Add(Format('%s=%s',[FieldName,AsString]));
end;

procedure  GetCustomersFromDataset(Dataset : TDataset; Customers : TObjectList);
begin
  Customers.Clear;
  if Dataset<>nil then
  begin
    Dataset.First;
    while not Dataset.Eof do
    begin
      Customers.add(TKSCustomer.Create(Dataset));
      Dataset.Next;
    end;
  end;
end;

procedure  GetBrokerInfosFromDataset(Dataset : TDataset; BrokerInfos : TObjectList);
begin
  BrokerInfos.Clear;
  if Dataset<>nil then
  begin
    Dataset.First;
    while not Dataset.Eof do
    begin
      BrokerInfos.add(TKSBrokerInfo.Create(Dataset));
      Dataset.Next;
    end;
  end;
end;

procedure  GetCustomerInfosFromDataset(Dataset : TDataset; CustomerInfos : TObjectList);
begin
  CustomerInfos.Clear;
  if Dataset<>nil then
  begin
    Dataset.First;
    while not Dataset.Eof do
    begin
      CustomerInfos.add(TKSCustomerInfo.Create(Dataset));
      Dataset.Next;
    end;
  end;
end;

procedure  GetSecAccountsFromDataset(Dataset : TDataset; SecAccounts: TObjectList);
begin
  SecAccounts.Clear;
  if Dataset<>nil then
  begin
    Dataset.First;
    while not Dataset.Eof do
    begin
      SecAccounts.add(TKSSecAccount.Create(Dataset));
      Dataset.Next;
    end;
  end;
end;

procedure  GetMoneyAccountsFromDataset(Dataset : TDataset; MoneyAccounts: TObjectList);
begin
  MoneyAccounts.Clear;
  if Dataset<>nil then
  begin
    Dataset.First;
    while not Dataset.Eof do
    begin
      MoneyAccounts.add(TKSMoneyAccount.Create(Dataset));
      Dataset.Next;
    end;
  end;
end;

procedure  GetBankAccountsFromDataset(Dataset : TDataset; BankAccounts: TObjectList);
begin
  BankAccounts.Clear;
  if Dataset<>nil then
  begin
    Dataset.First;
    while not Dataset.Eof do
    begin
      BankAccounts.add(TKSBankAccount.Create(Dataset));
      Dataset.Next;
    end;
  end;
end;

procedure  GetSecInfosFromDataset(Dataset : TDataset; SecInfos: TObjectList);
begin
  SecInfos.Clear;
  if Dataset<>nil then
  begin
    Dataset.First;
    while not Dataset.Eof do
    begin
      SecInfos.add(TKSSecInfo.Create(Dataset));
      Dataset.Next;
    end;
  end;
end;

function  GetStockFromDataset(Dataset : TDataset; StockList: TObjectList): TKSAbstractSecInfo;
begin
  Result:= nil;
  if Dataset<>nil then
  begin
    Dataset.First;
    while not Dataset.Eof do
    begin
      Result:= TKSSecInfo.Create(Dataset);
      StockList.add(Result);
      Dataset.Next;
    end;
  end;
end;

procedure  GetSeatInfosFromDataset(Dataset : TDataset; SeatInfos: TObjectList);
begin
  SeatInfos.Clear;
  if Dataset<>nil then
  begin
    Dataset.First;
    while not Dataset.Eof do
    begin
      SeatInfos.add(TKSSeatInfo.Create(Dataset));
      Dataset.Next;
    end;
  end;
end;

procedure  GetEmpInfosFromDataset(Dataset : TDataset; EmpInfos: TObjectList);
begin
  EmpInfos.Clear;
  if Dataset<>nil then
  begin
    Dataset.First;
    while not Dataset.Eof do
    begin
      EmpInfos.add(TKSEmpInfo.Create(Dataset));
      Dataset.Next;
    end;
  end;
end;

procedure  GetMarketInfosFromDataset(Dataset : TDataset; MarketInfos: TObjectList);
begin
  MarketInfos.Clear;
  if Dataset<>nil then
  begin
    Dataset.First;
    while not Dataset.Eof do
    begin
      MarketInfos.add(TKSMarket.Create(Dataset));
      Dataset.Next;
    end;
  end;
end;

procedure  GetBranchInfosFromDataset(Dataset : TDataset; BranchInfos: TObjectList);
begin
  BranchInfos.Clear;
  if Dataset<>nil then
  begin
    Dataset.First;
    while not Dataset.Eof do
    begin
      BranchInfos.add(TKSBranch.Create(Dataset));
      Dataset.Next;
    end;
  end;
end;

procedure  GetSecTypeSetFromDataset(Dataset : TDataset; SecTypeSet: TStringList);
begin
  SecTypeSet.Clear;
  if Dataset<>nil then
  begin
    Dataset.First;
    while not Dataset.Eof do
    begin
      SecTypeSet.add(Dataset.FieldByName('scust_type').AsString+',');
      Dataset.Next;
    end;
  end;
end;

procedure  GetBankInfosFromDataset(Dataset : TDataset; BankInfos: TObjectList);
begin
  BankInfos.Clear;
  if Dataset<>nil then
  begin
    Dataset.First;
    while not Dataset.Eof do
    begin
      BankInfos.add(TKSBankInfo.Create(Dataset));
      Dataset.Next;
    end;
  end;
end;

procedure  GetStationInfosFromDataset(Dataset : TDataset; StationInfos: TObjectList);
begin
  StationInfos.Clear;
  if Dataset<>nil then
  begin
    Dataset.First;
    while not Dataset.Eof do
    begin
      StationInfos.add(TKSStationAuthInfo.Create(Dataset));
      Dataset.Next;
    end;
  end;
end;

procedure GetGroupInfosFromDataset(Dataset : TDataset; GroupInfos: TObjectList);
begin
  GroupInfos.Clear;
  if Dataset<>nil then
  begin
    Dataset.First;
    while not Dataset.Eof do
    begin
      GroupInfos.add(TKSGroupInfo.Create(Dataset));
      Dataset.Next;
    end;
  end;
end;

procedure GetFeeLevelInfosFromDataset(Dataset : TDataset; FeeLevelInfos: TObjectList);
begin
  FeeLevelInfos.Clear;
  if Dataset<>nil then
  begin
    Dataset.First;
    while not Dataset.Eof do
    begin
      FeeLevelInfos.add(TKSFeeLevelInfo.Create(Dataset));
      Dataset.Next;
    end;
  end;
end;

{ TKSAbstractObject }

procedure TKSAbstractObject.Assign(Source: TKSAbstractObject);
begin

end;

{ TKSAbstractCustomer }

function TKSAbstractCustomer.GetDisplayLabel: string;
begin
  Result := CustomerNo+'-'+CustomerName;
end;

function TKSAbstractCustomer.GetID: string;
begin
  Result := CustomerNo;
end;

function TKSAbstractCustomer.GetName: string;
begin
  Result := CustomerName;
end;

{ TKSCustomer }

constructor TKSCustomer.Create(Dataset: TDataset);
begin
  Assert((Dataset<>nil) and not Dataset.IsEmpty);
  FParams := TStringList.Create;
  GetParamsFromDataset(FParams,Dataset);
  if Trim(FParams.Values['sname2'])='' then
    FParams.Values['lsafe_level']:='';
end;

constructor TKSCustomer.Create(Customer: TKSCustomer);
begin
  FParams := TStringList.Create;
  Assign(Customer);
end;

destructor TKSCustomer.Destroy;
begin
  FParams.Free;
  inherited;
end;

procedure TKSCustomer.Assign(Source: TKSAbstractObject);
begin
  inherited;
  if Source is TKSCustomer then
    FParams.Assign(TKSCustomer(Source).FParams);
end;

function TKSCustomer.GetCustomerName: string;
begin
  Result := GetParamValue('sname');
end;

function TKSCustomer.GetCustomerNo: string;
begin
  Result := GetParamValue('scust_no');
end;

function TKSCustomer.GetDepartment: string;
begin
  Result := GetParamValue('sbranch_code0');
end;

function TKSCustomer.GetParamValue(const ParamName: string): string;
begin
  Result := FParams.Values[ParamName];
end;

function TKSCustomer.Clone: TKSAbstractCustomer;
begin
  Result := TKSCustomer.Create(Self);
end;

function TKSCustomer.GetStatus: string;
begin
  Result := GetParamValue('sstatus0');
end;

{ TKSAbstractSecAccount }

function TKSAbstractSecAccount.GetDisplayLabel: string;
begin
  if GetParamValue('smain_flag')='1' then
    Result := Account+'-'+AccountName+'*'
  else
    Result := Account+'-'+AccountName;
end;

function TKSAbstractSecAccount.GetID: string;
begin
  Result := Account;
end;

function TKSAbstractSecAccount.GetName: string;
begin
  Result := AccountName;
end;

{ TKSSecAccount }

constructor TKSSecAccount.Create(Dataset: TDataset);
begin
  Assert((Dataset<>nil) and not Dataset.IsEmpty);
  FParams := TStringList.Create;
  GetParamsFromDataset(FParams,Dataset);
end;

destructor TKSSecAccount.Destroy;
begin
  FParams.Free;
  inherited;
end;

function TKSSecAccount.GetAccount: string;
begin
  Result := GetParamValue('sholder_ac_no');
end;

function TKSSecAccount.GetAccountName: string;
begin
  Result := GetParamValue('sname');
end;

function TKSSecAccount.GetMarket: string;
begin
  Result := GetParamValue('smarket_code');
end;

function TKSSecAccount.GetParamValue(const ParamName: string): string;
begin
  Result := FParams.Values[ParamName];
end;

procedure TKSSecAccount.Assign(Source: TKSAbstractObject);
begin
  inherited;
  if Source is TKSSecAccount then
    FParams.Assign(TKSSecAccount(Source).FParams);
end;

function TKSSecAccount.GetStatus: string;
begin
  Result := GetParamValue('sstatus1');
end;

{ TKSSecAccount2 }

procedure TKSSecAccount2.Assign(Source: TKSAbstractObject);
begin
  inherited;
  if Source is TKSAbstractSecAccount then
  begin
    FMarket := TKSAbstractSecAccount(Source).Market;
    FAccount := TKSAbstractSecAccount(Source).Account;
    FAccountName := TKSAbstractSecAccount(Source).AccountName;
  end;
end;

constructor TKSSecAccount2.Create(Customer: TKSAbstractCustomer;
  const AMarket: string);
begin
  Assert(Customer<>nil);
  FMarket := AMarket;
  FAccount := Customer.GetParamValue('sholder_ac_no');
  FAccountName := Customer.GetCustomerName;
  FAccountStatus := Customer.GetParamValue('sstatus2');
end;

function TKSSecAccount2.GetAccount: string;
begin
  Result := FAccount;
end;

function TKSSecAccount2.GetAccountName: string;
begin
  Result := FAccountName;
end;

function TKSSecAccount2.GetMarket: string;
begin
  Result := FMarket;
end;

function TKSSecAccount2.GetParamValue(const ParamName: string): string;
begin
  if SameText(ParamName,'sholder_ac_no') then
    Result := FAccount
  else if SameText(ParamName,'sname') then
    Result := FAccountName
  else if SameText(ParamName,'smarket_code') then
    Result := FMarket
  else if SameText(ParamName,'sstatus1') then
    Result := FAccountStatus;
end;

function TKSSecAccount2.GetStatus: string;
begin
  Result := FAccountStatus;
end;

{ TKSAbstractMoneyAccount }

function TKSAbstractMoneyAccount.GetDisplayLabel: string;
begin
  Result := CustomerNo+'-'+CurrencyType;
end;

function TKSAbstractMoneyAccount.GetID: string;
begin
  Result := CustomerNo;
end;

function TKSAbstractMoneyAccount.GetName: string;
begin
  Result := CurrencyType;
end;

{ TKSMoneyAccount }

procedure TKSMoneyAccount.Assign(Source: TKSAbstractObject);
begin
  inherited;
  if Source is TKSMoneyAccount then
    FParams.Assign(TKSMoneyAccount(Source).FParams);
end;

constructor TKSMoneyAccount.Create(Dataset: TDataset);
begin
  Assert((Dataset<>nil) and not Dataset.IsEmpty);
  FParams := TStringList.Create;
  GetParamsFromDataset(FParams,Dataset);
end;

destructor TKSMoneyAccount.Destroy;
begin
  FParams.Free;
  inherited;
end;

function TKSMoneyAccount.GetCanDisplay: Boolean;
begin
  Result := GetParamValue('Lsafe_level')='1';
end;

function TKSMoneyAccount.GetCurrencyType: string;
begin
  Result := GetParamValue('Scurrency_type');
end;

function TKSMoneyAccount.GetCustomerNo: string;
begin
  Result := GetParamValue('Scust_no');
end;

function TKSMoneyAccount.GetParamValue(const ParamName: string): string;
begin
  Result := FParams.Values[ParamName];
end;

{ TKSAbstractBankAccount }

function TKSAbstractBankAccount.GetDisplayLabel: string;
begin
  Result := Account+'-'+ GetIdObjectName(deBankCode,Bank) +'-'+AccountName;
end;

function TKSAbstractBankAccount.GetID: string;
begin
  Result := Account;
end;

function TKSAbstractBankAccount.GetName: string;
begin
  Result := AccountName;
end;

{ TKSBankAccount }

function TKSBankAccount.GetAccount: string;
begin
  Result := GetParamValue('sbank_acc');
end;

function TKSBankAccount.GetAccountName: string;
begin
  Result := GetParamValue('sname');
end;

function TKSBankAccount.GetBank: string;
begin
  Result := GetParamValue('sbank_code');
end;

constructor TKSBankAccount.Create(Dataset: TDataset);
begin
  Assert((Dataset<>nil) and not Dataset.IsEmpty);
  FParams := TStringList.Create;
  GetParamsFromDataset(FParams,Dataset);
end;

destructor TKSBankAccount.Destroy;
begin
  FParams.Free;
  inherited;
end;

function TKSBankAccount.GetParamValue(const ParamName: string): string;
begin
  Result := FParams.Values[ParamName];
end;

procedure TKSBankAccount.Assign(Source: TKSAbstractObject);
begin
  inherited;
  if Source is TKSBankAccount then
    FParams.Assign(TKSBankAccount(Source).FParams);
end;

{ TKSAbstractSecInfo }

function TKSAbstractSecInfo.GetDisplayLabel: string;
begin
  Result := SecCode+'-'+SecName;
end;

function TKSAbstractSecInfo.GetID: string;
begin
  Result := SecCode;
end;

function TKSAbstractSecInfo.GetName: string;
begin
  Result := SecName;
end;

{ TKSSecInfo }

function TKSSecInfo.GetSecCode: string;
begin
  Result := GetParamValue('sstock_code');
end;

function TKSSecInfo.GetSecName: string;
begin
  Result := GetParamValue('sname');
end;

function TKSSecInfo.GetMarket: string;
begin
  Result := GetParamValue('smarket_code');
end;

function TKSSecInfo.GetStatus: string;
begin
  Result := GetParamValue('sstatus1');
end;

function TKSSecInfo.GetSecType: string;
begin
  Result := GetParamValue('scust_type');
end;

constructor TKSSecInfo.Create(Dataset: TDataset);
begin
  Assert((Dataset<>nil) and not Dataset.IsEmpty);
  FParams := TStringList.Create;
  GetParamsFromDataset(FParams,Dataset);
end;

destructor TKSSecInfo.Destroy;
begin
  FParams.Free;
  inherited;
end;

function TKSSecInfo.GetParamValue(const ParamName: string): string;
begin
  Result := FParams.Values[ParamName];
end;

{ TKSAbstractSeatInfo }

function TKSAbstractSeatInfo.GetDisplayLabel: string;
begin
  Result := SeatNo;
end;

function TKSAbstractSeatInfo.GetID: string;
begin
  Result := SeatNo;
end;

function TKSAbstractSeatInfo.GetName: string;
begin
  Result := '';
end;

function TKSAbstractSeatInfo.GetReportDisplay: string;
begin
  Result :=GetIdObjectName(deMarket,Market) + '-' + SeatNo;
end;

{ TKSSeatInfo }

procedure TKSSecInfo.Assign(Source: TKSAbstractObject);
begin
  inherited;
  if Source is TKSSecInfo then
    FParams.Assign(TKSSecInfo(Source).FParams);
end;

function TKSSeatInfo.GetSeatNo: string;
begin
  Result := GetParamValue('sstock_code');
end;

function TKSSeatInfo.GetBranchCode: string;
begin
  Result := GetParamValue('sbranch_code0');
end;

function TKSSeatInfo.GetMarket: string;
begin
  Result := GetParamValue('smarket_code');
end;

constructor TKSSeatInfo.Create(Dataset: TDataset);
begin
  Assert((Dataset<>nil) and not Dataset.IsEmpty);
  FParams := TStringList.Create;
  GetParamsFromDataset(FParams,Dataset);
end;

destructor TKSSeatInfo.Destroy;
begin
  FParams.Free;
  inherited;
end;

function TKSSeatInfo.GetParamValue(const ParamName: string): string;
begin
  Result := FParams.Values[ParamName];
end;

procedure TKSSeatInfo.Assign(Source: TKSAbstractObject);
begin
  inherited;
  if Source is TKSSeatInfo then
    FParams.Assign(TKSSeatInfo(Source).FParams);
end;

{ TKSAbstractEmpInfo }

function TKSAbstractEmpInfo.GetDisplayLabel: string;
begin
  Result := EmpNO+'-'+EmpName;
end;

function TKSAbstractEmpInfo.GetID: string;
begin
  Result := EmpNO;
end;

function TKSAbstractEmpInfo.GetName: string;
begin
  Result := EmpName;
end;

procedure TKSEmpInfo.Assign(Source: TKSAbstractObject);
begin
  inherited;
  if Source is TKSEmpInfo then
    FParams.Assign(TKSEmpInfo(Source).FParams);
end;

{ TKSEmpInfo }

function TKSEmpInfo.GetEmpNo: string;
begin
  Result := GetParamValue('Sopen_emp');
end;

function TKSEmpInfo.GetBranchCode: string;
begin
  Result := GetParamValue('sbranch_code0');
end;

function TKSEmpInfo.GetEmpName: string;
begin
  Result := GetParamValue('sname');
end;

constructor TKSEmpInfo.Create(Dataset: TDataset);
begin
  Assert((Dataset<>nil) and not Dataset.IsEmpty);
  FParams := TStringList.Create;
  GetParamsFromDataset(FParams,Dataset);
end;

destructor TKSEmpInfo.Destroy;
begin
  FParams.Free;
  inherited;
end;

function TKSEmpInfo.GetParamValue(const ParamName: string): string;
begin
  Result := FParams.Values[ParamName];
end;

{ TKSAbstractMarket }

function TKSAbstractMarket.GetDisplayLabel: string;
begin
  Result := Market+'-'+Name;
end;

{ TKSMarket }

procedure TKSMarket.Assign(Source: TKSAbstractObject);
begin
  inherited;

end;

constructor TKSMarket.Create(Dataset: TDataset);
begin
  Assert((Dataset<>nil) and not Dataset.IsEmpty);
  FParams := TStringList.Create;
  GetParamsFromDataset(FParams,Dataset);
  ReadSecType;
  ReadConfig;
end;

destructor TKSMarket.Destroy;
begin
  FParams.Free;
  inherited;
end;

function TKSMarket.GetAccountLength: Integer;
begin
  Result := FAccountLength;
end;

function TKSMarket.GetAccountPattern: string;
begin
  Result := FAccountPattern;
end;

function TKSMarket.GetAllSecTypeSet: string;
begin
  Result := FAllSecTypeSet;
end;

function TKSMarket.GetCurrencySet: string;
begin
  Result := GetParamValue('scust_limit');
end;

function TKSMarket.GetCurrencyType : string;
begin
  Result := GetParamValue('scurrency_type');
end;

function TKSMarket.GetID: string;
begin
  Result := GetParamValue('smarket_code');
end;

function TKSMarket.GetName: string;
begin
  Result := GetParamValue('sname');
end;

function TKSMarket.GetParamValue(const ParamName: string): string;
begin
  Result := FParams.Values[ParamName];
end;

function TKSMarket.GetSecTypeSet: string;
begin
  Result := FSecTypeSet;
end;

function TKSMarket.GetSecurityLength: Integer;
begin
  Result := FSecurityLength;
end;

function TKSMarket.GetSecurityPattern: string;
begin
  Result := FSecurityPattern;
end;

procedure TKSMarket.ReadConfig;
var
  Config : IConfigSystem;
  AID : string;
  MarketID : Integer;
begin
  Config := Context.GetConfigSystem;
  AID := GetID;
  MarketID := StrToIntDef(AID,0);
  if (KnownMarketMin<=MarketID) and (MarketID<=KnownMarketMax) then
  begin
    FSecurityLength := KnownSecurityLengths[MarketID];
    FSecurityPattern:= KnownSecurityPatterns[MarketID];
    FAccountLength  := KnownAccountLengths[MarketID];
    FAccountPattern := KnownAccountPatterns[MarketID];
  end else
  begin
    FSecurityLength := cdSecurityLength;
    FSecurityPattern:= cdSecurityPattern;
    FAccountLength  := cdAccountLength;
    FAccountPattern := cdAccountPattern;
  end;
  FSecurityLength:= Config.ReadInteger(
    ccInput,
    Format(ckSecurityLength,[AID]),
    FSecurityLength);
  FSecurityPattern:= Config.ReadString(
    ccInput,
    Format(ckSecurityPattern,[AID]),
    FSecurityPattern);
  FAccountLength := Config.ReadInteger(
    ccInput,
    Format(ckAccountLength,[AID]),
    FAccountLength);
  FAccountPattern:= Config.ReadString(
    ccInput,
    Format(ckAccountPattern,[AID]),
    FAccountPattern);
end;

procedure TKSMarket.ReadSecType;
var
  SecTypeList:TStringList;
  AID,Temp:string;
  I:Integer;
begin
  SecTypeList:=TStringList.Create;
  AID := GetID;
  ComCmdDefinition.GetSecTypeSets(AID,SecTypeList);
  Temp:='';
  for I:=0 to SecTypeList.Count-1 do
  begin
    Temp:= Temp+trim(SecTypeList.Strings[I]) ;
  end;
  FSecTypeSet:=Temp;
  if AID='1' then             //这是选取所有市场的证券类别(从证券类别表中取)
  begin                     //暂时保存在第一个市场的FAllSecTypeSet中
    SecTypeList.Clear;
    ComCmdDefinition.GetSecTypeSets('',SecTypeList);
    Temp:='';
    for I:=0 to SecTypeList.Count-1 do
    begin
      Temp:= Temp+trim(SecTypeList.Strings[I]) ;
    end;
    FAllSecTypeSet:=Temp;
  end;
  SecTypeList.Free;
end;


{ TKSAbstractBrokerInfo }

function TKSAbstractBrokerInfo.GetDisplayLabel: string;
begin
  Result := BrokerNo+'-'+BrokerName;
end;

function TKSAbstractBrokerInfo.GetID: string;
begin
  Result := BrokerNo;
end;

function TKSAbstractBrokerInfo.GetName: string;
begin
  Result := BrokerName;
end;

{ TKSBrokerInfo }

procedure TKSBrokerInfo.Assign(Source: TKSAbstractObject);
begin
  inherited;
  if Source is TKSBrokerInfo then
    FParams.Assign(TKSBrokerInfo(Source).FParams);
end;

constructor TKSBrokerInfo.Create(Dataset: TDataset);
begin
  Assert((Dataset<>nil) and not Dataset.IsEmpty);
  FParams := TStringList.Create;
  GetParamsFromDataset(FParams,Dataset);
end;

destructor TKSBrokerInfo.Destroy;
begin
  FParams.Free;
  inherited;
end;

function TKSBrokerInfo.GetBrokerName: string;
begin
  Result := GetParamValue('sname');
end;

function TKSBrokerInfo.GetBrokerNo: string;
begin
  Result := GetParamValue('scust_no2');
end;

function TKSBrokerInfo.GetDepartment: string;
begin
  Result := GetParamValue('sbranch_code0');
end;

function TKSBrokerInfo.GetParamValue(const ParamName: string): string;
begin
  Result := FParams.Values[ParamName];
end;

function TKSBrokerInfo.GetStatus: string;
begin
  Result := GetParamValue('sstatus4');
end;

{ TKSAbstractCustomerInfo }

function TKSAbstractCustomerInfo.GetDisplayLabel: string;
begin
  Result := CustomerNo+'-'+CustomerName;
end;

function TKSAbstractCustomerInfo.GetID: string;
begin
  Result := CustomerNo;
end;

function TKSAbstractCustomerInfo.GetName: string;
begin
  Result := CustomerName;
end;

{ TKSCustomerInfo }

procedure TKSCustomerInfo.Assign(Source: TKSAbstractObject);
begin
  inherited;
  if Source is TKSCustomerInfo then
    FParams.Assign(TKSCustomerInfo(Source).FParams);
end;

constructor TKSCustomerInfo.Create(Dataset: TDataset);
begin
  Assert((Dataset<>nil) and not Dataset.IsEmpty);
  FParams := TStringList.Create;
  GetParamsFromDataset(FParams,Dataset);
end;

destructor TKSCustomerInfo.Destroy;
begin
  FParams.Free;
  inherited;
end;

function TKSCustomerInfo.GetCustomerName: string;
begin
  Result := GetParamValue('sname');
end;

function TKSCustomerInfo.GetCustomerNo: string;
begin
  Result := GetParamValue('scust_no');
end;

function TKSCustomerInfo.GetDepartment: string;
begin
  Result := GetParamValue('sbranch_code1');
end;

function TKSCustomerInfo.GetParamValue(const ParamName: string): string;
begin
  Result := FParams.Values[ParamName];
end;

function TKSCustomerInfo.GetStatus: string;
begin
  Result := GetParamValue('sstatus0');
end;

{ TKSAbstractBankInfo }

function TKSAbstractBankInfo.GetDisplayLabel: string;
begin
  Result:= BankNo + '-' + BankName;
end;

function TKSAbstractBankInfo.GetID: string;
begin
  Result:= BankNo;
end;

function TKSAbstractBankInfo.GetName: string;
begin
  Result:= BankName;
end;

function TKSAbstractBankInfo.GetReportDisplay: string;
begin
  Result:= GetIdObjectName(deCurrency,Currency) + '-' + BankName;
end;

{ TKSBankInfo }

procedure TKSBankInfo.Assign(Source: TKSAbstractObject);
begin
  inherited;
  if Source is TKSCustomerInfo then
    FParams.Assign(TKSCustomerInfo(Source).FParams);
end;

constructor TKSBankInfo.Create(Dataset: TDataset);
begin
  Assert((Dataset<>nil) and not Dataset.IsEmpty);
  FParams := TStringList.Create;
  GetParamsFromDataset(FParams,Dataset);
end;

destructor TKSBankInfo.Destroy;
begin
  FParams.Free;
  inherited;
end;

function TKSBankInfo.GetBankName: string;
begin
  Result := GetParamValue('sall_name');
end;

function TKSBankInfo.GetBankNo: string;
begin
  Result := GetParamValue('sbank_code');
end;

function TKSBankInfo.GetBranchCode: string;
begin
  Result := GetParamValue('sbranch_code0');
end;

function TKSBankInfo.GetCurrency: string;
begin
  Result := GetParamValue('scurrency_type');
end;

function TKSBankInfo.GetParamValue(const ParamName: string): string;
begin
  Result := FParams.Values[ParamName];
end;


{ TKSStationAuthInfo }

procedure TKSStationAuthInfo.Assign(Source: TKSAbstractObject);
begin
  inherited;
  if Source is TKSStationAuthInfo then
    FParams.Assign(TKSStationAuthInfo(Source).FParams);
end;

constructor TKSStationAuthInfo.Create(Dataset: TDataset);
begin
  Assert((Dataset<>nil) and not Dataset.IsEmpty);
  FParams := TStringList.Create;
  GetParamsFromDataset(FParams,Dataset);
end;

destructor TKSStationAuthInfo.Destroy;
begin
  FParams.Free;
  inherited;
end;

function TKSStationAuthInfo.GetBranchCode: string;
begin
  Result := GetParamValue('sbranch_code0');
end;

function TKSStationAuthInfo.GetParamValue(const ParamName: string): string;
begin
  Result := FParams.Values[ParamName];
end;

function TKSStationAuthInfo.GetStationName: string;
begin
  Result := GetParamValue('sname');
end;

function TKSStationAuthInfo.GetStationNo: string;
begin
  Result := GetParamValue('scurrency_type');
end;

{ TKSAbstractStationAuthInfo }

function TKSAbstractStationAuthInfo.GetDisplayLabel: string;
begin
  Result := StationNO+'-'+StationName;
end;

function TKSAbstractStationAuthInfo.GetID: string;
begin
  Result := StationNO;
end;

function TKSAbstractStationAuthInfo.GetName: string;
begin
  Result := StationName;
end;

{ TKSBranch }

procedure TKSBranch.Assign(Source: TKSAbstractObject);
begin
  inherited;

end;

constructor TKSBranch.Create(Dataset: TDataset);
begin
  Assert((Dataset<>nil) and not Dataset.IsEmpty);
  FParams := TStringList.Create;
  GetParamsFromDataset(FParams,Dataset);
end;

destructor TKSBranch.Destroy;
begin
  FParams.Free;
  inherited;
end;

function TKSBranch.GetID: string;
begin
  Result := GetParamValue('sbranch_code1');
end;

function TKSBranch.GetName: string;
begin
  Result := GetParamValue('sbank_acc');
end;

function TKSBranch.GetParamValue(const ParamName: string): string;
begin
  Result := FParams.Values[ParamName];
end;

{ TKSAbstractBranch }

function TKSAbstractBranch.GetDisplayLabel: string;
begin
  Result := Branch+'-'+Name;
end;

{ TKSAbstractGroupInfo }

function TKSAbstractGroupInfo.GetDisplayLabel: string;
begin
  Result := GroupNO+'-'+GroupName;
end;

function TKSAbstractGroupInfo.GetID: string;
begin
  Result := GroupNO;
end;

function TKSAbstractGroupInfo.GetName: string;
begin
  Result := GroupName;
end;

{ TKSGroupInfo }

procedure TKSGroupInfo.Assign(Source: TKSAbstractObject);
begin
  if Source is TKSGroupInfo then
    FParams.Assign(TKSGroupInfo(Source).FParams);
end;

constructor TKSGroupInfo.Create(Dataset: TDataset);
begin
  Assert((Dataset<>nil) and not Dataset.IsEmpty);
  FParams := TStringList.Create;
  GetParamsFromDataset(FParams,Dataset);
end;

destructor TKSGroupInfo.Destroy;
begin
  FParams.Free;
  inherited;
end;

function TKSGroupInfo.GetBranchCode: string;
begin
  Result := GetParamValue('sbranch_code0');
end;

function TKSGroupInfo.GetGroupName: string;
begin
  Result := GetParamValue('sname');
end;

function TKSGroupInfo.GetGroupNo: string;
begin
  Result := GetParamValue('Lvol0');
end;

function TKSGroupInfo.GetParamValue(const ParamName: string): string;
begin
  Result := FParams.Values[ParamName];
end;

{ TKSFeeLevelInfo }

procedure TKSFeeLevelInfo.Assign(Source: TKSAbstractObject);
begin
  inherited;
  if Source is TKSFeeLevelInfo then
    FParams.Assign(TKSFeeLevelInfo(Source).FParams);
end;

constructor TKSFeeLevelInfo.Create(Dataset: TDataset);
begin
  Assert((Dataset<>nil) and not Dataset.IsEmpty);
  FParams := TStringList.Create;
  GetParamsFromDataset(FParams,Dataset);
end;

destructor TKSFeeLevelInfo.Destroy;
begin
  FParams.Free;
  inherited;
end;

function TKSFeeLevelInfo.GetBranchCode: string;
begin
  Result := GetParamValue('sbranch_code0');
end;

function TKSFeeLevelInfo.GetFeeLevelName: string;
begin
  Result := GetIdObjectName(de1820,GetParamValue('sroom_no'));
end;

function TKSFeeLevelInfo.GetFeeLevelNo: string;
begin
  Result := GetParamValue('sroom_no');
end;

function TKSFeeLevelInfo.GetParamValue(const ParamName: string): string;
begin
  Result := FParams.Values[ParamName];
end;

{ TKSAbstractFeeLevelInfo }

function TKSAbstractFeeLevelInfo.GetDisplayLabel: string;
begin
  Result := FeeLevel+'-'+FeeLevelName;
end;

function TKSAbstractFeeLevelInfo.GetID: string;
begin
  Result := FeeLevel;
end;

function TKSAbstractFeeLevelInfo.GetName: string;
begin
  Result := FeeLevelName;
end;

end.
