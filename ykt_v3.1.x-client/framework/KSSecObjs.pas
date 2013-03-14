unit KSSecObjs;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSSecObjs
   <What>证券系统的实体对象
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}

interface

uses Classes, ObjDir;

type
  {
    <Class>TIdObject
    <What>代表有唯一主键的实体对象
    <Properties>
      -
    <Methods>
      -
    <Event>
      -
  }
  TIdObject = class(TObject)
  private
    FID: string;
    FName: string;
  protected

  public
    property  ID : string read FID write FID;
    property  Name : string read FName write FName;
  end;

  TIdClass = class of TIdObject;

  {
    <Class>TIdObjectList
    <What>包含有唯一主键的实体对象的列表
    <Properties>
      -
    <Methods>
      -
    <Event>
      -
  }
  TIdObjectList = class(TObjectCategory)
  private
    FIdClass: TIdClass;
  public
    constructor Create(AIdClass : TIdClass);
    property    IdClass : TIdClass read FIdClass;
    function    Find(const ID:string) : TIdObject;
  end;

  //货币代码
  TKSCurrencyKind = class(TIdObject);

  //市场
  TKSMarket = class(TIdObject)
  private
    FCurrencyKindID: string;
    FCurrencyKind: TKSCurrencyKind;
  public
    property  CurrencyKind : TKSCurrencyKind read FCurrencyKind write FCurrencyKind;
    property  CurrencyKindID : string read FCurrencyKindID write FCurrencyKindID;
  end;

  // 证券类别
  TKSSecuritiesKind = class(TIdObject);

  // 证券
  TKSSecurities = class(TIdObject)
  private
    FStockKindID: string;
    FMarketID: string;
    FMarket: TKSMarket;
    FStockKind: TKSSecuritiesKind;
    FSpell: string;
  public
    property  MarketID : string read FMarketID write FMarketID;
    property  Market : TKSMarket read FMarket write FMarket;
    property  StockKindID : string read FStockKindID write FStockKindID;
    property  StockKind : TKSSecuritiesKind read FStockKind write FStockKind;
    property  Spell : string read FSpell write FSpell;
  end;

  // 客户类别
  TKSCustomerKind = class(TIdObject);
  TKSCenterCustomerKind = class(TKSCustomerKind);
  TKSDepartCustomerKind = class(TKSCustomerKind);
  TKSCustomerGroup = class(TKSCustomerKind);

  // 错误信息
  TKSErrorInfo = class(TIdObject);

  // 代理方式
  TKSAgentKind = class(TIdObject);

  // 国籍
  TKSNation = class(TIdObject);

  // 证件类别
  TKSCertKind = class(TIdObject);

  // 委托方式
  TKSEntrustMethod = class(TIdObject);

  // 银行
  TKSBank = class(TIdObject);

  // 性别
  TKSSex = class(TIdObject);

  // 账号类别 (1 客户号，2 沪A股东代码,...)
  TKSAccountType = class(TIdObject);

  // 账户类别（法人、基金）
  TKSAccountKind = class(TIdObject);

  // 客户标志
  TKSCustomerProp = class(TIdObject);

  // 营业部
  TKSDepartment = class(TIdObject);



function  FindIdObject(IdClass : TIdClass; const ID : string) : TIdObject;

function  RegisterIdClass(IdClass : TIdClass) : TIdObjectList;

function  GetIdObjectList(IdClass : TIdClass) : TIdObjectList;

var
  CurrencyKinds,
  Markets,
  StockKinds,
  Stocks,
  CustomerKinds,
  ErrorInfos
   : TIdObjectList;

implementation

function  RegisterIdClass(IdClass : TIdClass) : TIdObjectList;
begin
  Result := TIdObjectList.Create(IdClass);
end;

function  GetIdObjectList(IdClass : TIdClass) : TIdObjectList;
begin
  Result := TIdObjectList(GetCategory(IdClass.ClassName));
  Assert((Result=nil) or (Result is TIdObjectList));
end;

procedure CompareIdObject(Obj : TObject; const Name:string; ID : integer; var Finded : Boolean);
begin
  Finded := TidObject(Obj).ID = Name;
end;

function  FindIdObject(IdClass : TIdClass; const ID : string) : TIdObject;
var
  List : TIdObjectList;
begin
  List := GetIdObjectList(IdClass);
  Result := List.Find(ID);
end;

{ TIdObjectList }

constructor TIdObjectList.Create(AIdClass: TIdClass);
begin
  inherited Create(AIdClass.ClassName,True);
  FIDClass := AIdClass;
end;

function TIdObjectList.Find(const ID: string): TIdObject;
begin
  Result := TIdObject(FindObject(Id,0,CompareIdObject));
  Assert((Result=nil) or (Result is IdClass));
end;

initialization
  CurrencyKinds := RegisterIdClass(TKSCurrencyKind);
  Markets := RegisterIdClass(TKSMarket);
  StockKinds := RegisterIdClass(TKSSecuritiesKind);
  Stocks := RegisterIdClass(TKSSecurities);
  CustomerKinds := RegisterIdClass(TKSCenterCustomerKind);
  ErrorInfos := RegisterIdClass(TKSErrorInfo);

end.
