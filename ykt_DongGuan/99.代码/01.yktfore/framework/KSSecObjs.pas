unit KSSecObjs;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSSecObjs
   <What>֤ȯϵͳ��ʵ�����
   <Written By> Huang YanLai (������)
   <History>
**********************************************}

interface

uses Classes, ObjDir;

type
  {
    <Class>TIdObject
    <What>������Ψһ������ʵ�����
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
    <What>������Ψһ������ʵ�������б�
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

  //���Ҵ���
  TKSCurrencyKind = class(TIdObject);

  //�г�
  TKSMarket = class(TIdObject)
  private
    FCurrencyKindID: string;
    FCurrencyKind: TKSCurrencyKind;
  public
    property  CurrencyKind : TKSCurrencyKind read FCurrencyKind write FCurrencyKind;
    property  CurrencyKindID : string read FCurrencyKindID write FCurrencyKindID;
  end;

  // ֤ȯ���
  TKSSecuritiesKind = class(TIdObject);

  // ֤ȯ
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

  // �ͻ����
  TKSCustomerKind = class(TIdObject);
  TKSCenterCustomerKind = class(TKSCustomerKind);
  TKSDepartCustomerKind = class(TKSCustomerKind);
  TKSCustomerGroup = class(TKSCustomerKind);

  // ������Ϣ
  TKSErrorInfo = class(TIdObject);

  // ����ʽ
  TKSAgentKind = class(TIdObject);

  // ����
  TKSNation = class(TIdObject);

  // ֤�����
  TKSCertKind = class(TIdObject);

  // ί�з�ʽ
  TKSEntrustMethod = class(TIdObject);

  // ����
  TKSBank = class(TIdObject);

  // �Ա�
  TKSSex = class(TIdObject);

  // �˺���� (1 �ͻ��ţ�2 ��A�ɶ�����,...)
  TKSAccountType = class(TIdObject);

  // �˻���𣨷��ˡ�����
  TKSAccountKind = class(TIdObject);

  // �ͻ���־
  TKSCustomerProp = class(TIdObject);

  // Ӫҵ��
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
