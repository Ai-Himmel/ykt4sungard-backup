unit KSEdits;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSEdits
   <What>���������ؼ�
   �˺�����ؼ�
   ������TPasswordInputMethod��ȫ�ֶ���PasswordInputMethod�ṩ�˴�������С���̵Ľӿڡ�
   <Written By> Huang YanLai (������)
   <History>
**********************************************}


interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Mask, KSCustomers, Contnrs, WorkViews, LibMessages;

const
  WM_CheckData = LM_END+1;
  DefaultInputValidFieldName = '�ͻ�.������Ч��';
  InputValidValue = 1;
  InputInValidValue = 0;

type
  TKSAccountEdit = class;
  TAccountInputMethod = class;

  TAccountEditEvent = procedure (Sender : TKSAccountEdit; var Passed : Boolean) of object;
  TSelectCustomerEvent = procedure (Sender : TKSAccountEdit; Customers : TObjectList;
                  var SelectedCustomer : TKSAbstractCustomer; var Passed : Boolean) of object;
  TGetCustomersEvent = procedure (Sender : TKSAccountEdit; Customers : TObjectList) of object;
  TGetMainAccountsEvent = procedure (Sender : TKSAccountEdit; MainAccounts : TObjectList) of object;
  TGetMoneyAccountsEvent = procedure (Sender : TKSAccountEdit; MoneyAccounts : TObjectList) of object;
  TAdvancedSelectEvent = procedure (Sender : TKSAccountEdit; var Selected : Boolean; var CustomerNo : string) of object;
  TFormatAndValidAccountEvent = procedure (Sender : TAccountInputMethod; var Account : string; var Valid : Boolean) of object;

  TAccountInputMethod = class(TCollectionItem)
  private
    FNeedReinput: Boolean;
    FMethodChar: Char;
    FMarket: string;
    FCaption: string;
    FPattern: string;
    FLength1: Integer;
    FFirstChars: string;
    FLength2: Integer;
    FOnFormatAndValidAccount: TFormatAndValidAccountEvent;
    FCheckLength: Boolean;
    FCheckChars: Boolean;
    FHint: string;
  protected
    function    GetDisplayName: string; override;
  public
    constructor Create(Collection: TCollection); override;
    procedure   Assign(Source: TPersistent); override;
    function    NextInputMethod : TAccountInputMethod;
    function    FormatAndValidAccount(var Account : string; CanEmpty : Boolean=False): Boolean;
  published
    property    MethodChar : Char read FMethodChar write FMethodChar;
    property    Caption : string read FCaption write FCaption;
    property    NeedReinput : Boolean read FNeedReinput write FNeedReinput;
    property    Market : string read FMarket write FMarket;
    property    Pattern : string read FPattern write FPattern;
    property    FirstChars : string read FFirstChars write FFirstChars;
    property    Length1 : Integer read FLength1 write FLength1;
    property    Length2 : Integer read FLength2 write FLength2;
    property    CheckLength : Boolean read FCheckLength write FCheckLength default True;
    property    CheckChars : Boolean read FCheckChars write FCheckChars default True;
    property    Hint : string read FHint write FHint;
    property    OnFormatAndValidAccount : TFormatAndValidAccountEvent
                  read FOnFormatAndValidAccount write FOnFormatAndValidAccount;
  end;

  TAccountInputMethods = class(TComponent)
  private
    FMethods: TCollection;
    FOnInputPassword: TAccountEditEvent;
    FOnReinput: TAccountEditEvent;
    FOnGetCustomers: TGetCustomersEvent;
    FOnGetMainAccounts: TGetMainAccountsEvent;
    FOnSelectCustomer: TSelectCustomerEvent;
    FOnGetMoneyAccounts: TGetMoneyAccountsEvent;
    FOnAdvancedSelect: TAdvancedSelectEvent;
    FOnException: TNotifyEvent;
    FOnWarningCustomerStatus: TNotifyEvent;
    FOnShowEditHint: TNotifyEvent;
    FFirstMethodChar: Char;
    procedure   SetMethods(const Value: TCollection);
  protected
    procedure   GetCustomers(Sender : TKSAccountEdit; Customers : TObjectList);
    procedure   GetMainAccounts(Sender : TKSAccountEdit; MainAccounts : TObjectList);
    procedure   GetMoneyAccounts(Sender : TKSAccountEdit; MoneyAccounts : TObjectList);
    procedure   InputPassword(Sender : TKSAccountEdit; var Passed : Boolean);
    procedure   ReInput(Sender : TKSAccountEdit; var Passed : Boolean);
    procedure   SelectCustomer(Sender : TKSAccountEdit; Customers : TObjectList;
                  var SelectedCustomer : TKSAbstractCustomer; var Passed : Boolean);
    procedure   DoAdvancedSelect(Sender : TKSAccountEdit; var Selected : Boolean; var CustomerNo : string);
    procedure   ShowTheHint(Sender : TKSAccountEdit);
  public
    constructor Create(AOwner : TComponent); override;
    destructor  Destroy;override;
    function    FindInputMethod(MethodChar : Char): TAccountInputMethod;
  published
    property    Methods : TCollection read FMethods write SetMethods;
    property    FirstMethodChar : Char read FFirstMethodChar write FFirstMethodChar default '0';
    property    OnReinput : TAccountEditEvent read FOnReinput write FOnReinput;
    property    OnInputPassword : TAccountEditEvent read FOnInputPassword write FOnInputPassword;
    property    OnSelectCustomer : TSelectCustomerEvent read FOnSelectCustomer write FOnSelectCustomer;
    property    OnGetCustomers : TGetCustomersEvent read FOnGetCustomers write FOnGetCustomers;
    property    OnGetMainAccounts : TGetMainAccountsEvent read FOnGetMainAccounts write FOnGetMainAccounts;
    property    OnGetMoneyAccounts : TGetMoneyAccountsEvent read FOnGetMoneyAccounts write FOnGetMoneyAccounts;
    property    OnAdvancedSelect : TAdvancedSelectEvent read FOnAdvancedSelect write FOnAdvancedSelect;
    property    OnException : TNotifyEvent read FOnException write FOnException;
    property    OnWarningCustomerStatus : TNotifyEvent read FOnWarningCustomerStatus write FOnWarningCustomerStatus;
    property    OnShowEditHint : TNotifyEvent read FOnShowEditHint write FOnShowEditHint;
  end;

  TNeedPasswordEvent = procedure (Sender : TKSAccountEdit; var NeedPassWord : Boolean) of object;

  TCheckCustomerValidEvent = procedure (Sender : TKSAccountEdit; var CustomerValid : Boolean) of object;

  TKSAccountEdit = class(TMaskEdit)
  private
    { Private declarations }
    FAllowMethods: string;
    FLabelCtrl: TControl;
    FSavedInputMethod : TAccountInputMethod;
    FSavedValue : string;
    FCurrentInputMethod: TAccountInputMethod;
    FSwitchKey: Word;
    FValid: Boolean;
    FDataChanged: Boolean;
    FCustomer: TKSAbstractCustomer;
    FMainAccounts: TObjectList;
    FFirstMethodChar: Char;
    FNeedMainAccounts: Boolean;
    FNeedReinput: Boolean;
    FNeedPassword: Boolean;
    FOnValidChanged: TNotifyEvent;
    FPasswordType: Integer;
    FWorkView: TWorkView;
    FCustInfoGroupIndex: Integer;
    FAccountInfoGroupIndex: Integer;
    FMarket: string;
    FTempAccount : TKSSecAccount2;
    FMoneyAccounts: TObjectList;
    FNeedMoneyAccounts: Boolean;
    FMoneyInfoGroupIndex: Integer;
    FCurrencyType: string;
    FGoNextWhenPressEnter: Boolean;
    FGoPrevChar: Char;
    FNeedPasswordOnCrossDepart: Boolean;
    FDepartment: string;
    FOnNeedPassword: TNeedPasswordEvent;
    FAdvancedSelect: Boolean;
    FAcceptAlphabet : Boolean;
    FAcceptOther : Boolean;
    FRequired: Boolean;
    FOnException: TNotifyEvent;
    FOnInputValidChanged: TNotifyEvent;
    FInputValid : Boolean;
    FAllowCustomerStatus: string;
    FNormalStatus: Char;
    FOnWarningCustomerStatus: TNotifyEvent;
    FProhibitCrossDepart: Boolean;
    FIsWarningCustomerStatus: Boolean;
    FCustomerPassword: string;
    FProhibitSelectDepart: Boolean;
    FGlobalFirstMethodChar: Boolean;
    FAllowCenter: Boolean;
    FInputValidFieldName: string;
    FCustomerValid : Boolean;
    FOnCheckCustomerValid: TCheckCustomerValidEvent;
    FOnCustomerChanged: TNotifyEvent;
    FAutoGoNext: Boolean;
    procedure   SetLabelCtrl(const Value: TControl);
    procedure   UpdateLabelDisplay;
    procedure   SaveLastData;
    procedure   SetAllowMethods(const Value: string);
    procedure   SetValid(const Value: Boolean);
    procedure   SetCurrentInputMethod(const Value: TAccountInputMethod);
    // DoReinput �� �����Ƿ����ִ�С�����True��˵�����������������ͬ������False����ʾ����Աȡ���������������
    function    DoReinput : Boolean;
    // DoInputPassword : �����Ƿ����ִ�С�����True��˵��������ȷ������False����ʾ����Աȡ���������������Զ�Ҫ�������������롣
    function    DoInputPassword : Boolean;
    // GetCustomers �����������˺ŷ�ʽ���������ݣ�ȡ��Customers�б�
    procedure   GetCustomers(Customers : TObjectList);
    // SelectCustomers : ѡ��ͬӪҵ���Ŀͻ��������Ƿ������
    // ���Customers.Count=1��ֱ�ӷ���True
    // ���Customers.Count=0��ֱ�ӷ���False
    // ���Customers.Count>1�����ֶԻ����ò���Աѡ�����ѡ�񣬷���True�����ȡ��������False
    // �������True����SelectedCustomer���淵��ѡ�еĿͻ�
    // �����Ķ����ɸÿؼ������ͷš�
    function    SelectCustomers(Customers : TObjectList; var SelectedCustomer : TKSAbstractCustomer): Boolean;
    // ����Customer��ȡ�����г������ɶ�����(������MainAccounts)
    // �����Ķ����ɸÿؼ������ͷš�
    procedure   DoGetMainAccounts;
    // ����Customer��ȡ�������ֵ��ʽ��˺ŵ����(������MoneyAccounts)
    // �����Ķ����ɸÿؼ������ͷš�
    procedure   DoGetMoneyAccounts;
    function    GetMethod(InputMethod : TAccountInputMethod): TAccountInputMethod;
    procedure   SetWorkView(const Value: TWorkView);
    procedure   UpdateCustInfoWorkFields;
    procedure   UpdateAccountInfoWorkFields;
    procedure   UpdateMoneyInfoWorkFields;
    procedure   UpdateColor;
    procedure   SetMarket(const Value: string);
    procedure   SetCurrencyType(const Value: string);
    procedure   SetRequired(const Value: Boolean);
    function    GetInputValid: Boolean;
    procedure   HandleException;
    procedure   CheckInputValid;
    procedure   WMCheckData(var Message:TMessage); message WM_CheckData;
    function    IsStoreInputValidFieldName: Boolean;
    procedure   CMEnabledChanged(var Message: TMessage); message CM_ENABLEDCHANGED;
    procedure   GetCustomerInfoFromDB;
    procedure   RefreshCustomerInfoDisplay;
  protected
    { Protected declarations }
    procedure   Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure   Loaded; override;
    procedure   DoEnter; override;
    procedure   DoExit; override;
    procedure   KeyUp(var Key: Word; Shift: TShiftState); override;
    procedure   KeyPress(var Key: Char); override;
    procedure   Change; override;
    procedure   SelectAll;
    procedure   WarningCustomerStatus;
    procedure   SetCustomerPassword(const Password : string);
    procedure   ShowTheHint;
  public
    { Public declarations }
    constructor Create(AOwner : TComponent); override;
    destructor  Destroy;override;
    procedure   Reset; reintroduce;
    procedure   FirstInputMethod;
    procedure   NextInputMethod;
    function    AcceptInputMethod(InputMethod : TAccountInputMethod): Boolean;
    // IsDataChanged : �����Ƿ����ı�
    function    IsDataChanged : Boolean;
    // IsNeedReinput : �Ƿ���Ҫ�����˺�
    function    IsNeedReinput : Boolean;
    // IsNeedPassword : �Ƿ���Ҫ�ͻ���������
    function    IsNeedPassword : Boolean;
    // IsNeedMainAccounts : �Ƿ���Ҫ��ø����г������ɶ�����
    function    IsNeedMainAccounts : Boolean;
    // IsNeedMoneyAccounts : �Ƿ���Ҫ��ø������ֵ��ʽ����
    function    IsNeedMoneyAccounts : Boolean;
    // IsAllowCenter : �Ƿ������ܲ���ѯ����Ӫҵ���Ŀͻ�
    function    IsAllowCenter : Boolean;
    // CheckData return whether go to next input automatically
    function    CheckData(
                  CheckNeedReinput:Boolean=True;
                  CheckNeedPassword:Boolean=True;
                  IgnoreNoChange : Boolean=False;
                  AShowHint : Boolean=False) : Boolean;
    function    GetSecAccount(const AMarket : string) : TKSAbstractSecAccount;
    function    GetMoneyAccount(const ACurrencyType : string): TKSAbstractMoneyAccount;
    procedure   SetCustomer(const CustomerNo : string);
    procedure   Assign(Source: TPersistent); override;
    procedure   DoAdvancedSelect;
    procedure   CheckCustomerStatus;
    property    CurrentInputMethod : TAccountInputMethod read FCurrentInputMethod write SetCurrentInputMethod;
    property    Valid : Boolean read FValid write SetValid;
    property    InputValid : Boolean read GetInputValid;
    property    DataChanged : Boolean read FDataChanged;
    property    Customer : TKSAbstractCustomer read FCustomer;
    property    MainAccounts : TObjectList read FMainAccounts;
    property    MoneyAccounts : TObjectList read FMoneyAccounts;
    property    CustomerPassword : string read FCustomerPassword;
    property    AutoGoNext : Boolean read FAutoGoNext write FAutoGoNext;
  published
    { Published declarations }
    property    CharCase default ecUpperCase;
    property    AllowMethods : string read FAllowMethods write SetAllowMethods;
    property    LabelCtrl : TControl read FLabelCtrl write SetLabelCtrl;
    property    SwitchKey : Word read FSwitchKey write FSwitchKey default VK_F2;
    property    FirstMethodChar : Char read FFirstMethodChar write FFirstMethodChar default '0';
    property    GlobalFirstMethodChar : Boolean read FGlobalFirstMethodChar write FGlobalFirstMethodChar default False;
    property    NeedPassword : Boolean read FNeedPassword write FNeedPassword default False;
    property    NeedPasswordOnCrossDepart : Boolean read FNeedPasswordOnCrossDepart write FNeedPasswordOnCrossDepart default False;
    property    NeedReinput : Boolean read FNeedReinput write FNeedReinput default False;
    property    NeedMainAccounts : Boolean read FNeedMainAccounts write FNeedMainAccounts default True;
    property    NeedMoneyAccounts : Boolean read FNeedMoneyAccounts write FNeedMoneyAccounts default False;
    property    PasswordType : Integer read FPasswordType write FPasswordType default 1;
    property    WorkView : TWorkView read FWorkView write SetWorkView;
    property    CustInfoGroupIndex : Integer read FCustInfoGroupIndex write FCustInfoGroupIndex default 1;
    property    AccountInfoGroupIndex : Integer read FAccountInfoGroupIndex write FAccountInfoGroupIndex default 2;
    property    MoneyInfoGroupIndex : Integer read FMoneyInfoGroupIndex write FMoneyInfoGroupIndex default 3;
    property    Market : string read FMarket write SetMarket;
    property    CurrencyType : string read FCurrencyType write SetCurrencyType;
    property    Department : string read FDepartment write FDepartment;
    property    AdvancedSelect : Boolean read FAdvancedSelect write FAdvancedSelect;
    property    GoNextWhenPressEnter : Boolean read FGoNextWhenPressEnter write FGoNextWhenPressEnter default True;
    property    GoPrevChar : Char read FGoPrevChar write FGoPrevChar default '*';
    property    Required : Boolean read FRequired write SetRequired default True;
    property    AllowCustomerStatus : string read FAllowCustomerStatus write FAllowCustomerStatus;
    property    NormalStatus : Char read FNormalStatus write FNormalStatus default '0';
    property    ProhibitCrossDepart : Boolean read FProhibitCrossDepart write FProhibitCrossDepart default False;
    property    IsWarningCustomerStatus : Boolean read FIsWarningCustomerStatus write FIsWarningCustomerStatus default True;
    property    ProhibitSelectDepart : Boolean read FProhibitSelectDepart write FProhibitSelectDepart default False;
    property    AllowCenter : Boolean read FAllowCenter write FAllowCenter default True;
    property    InputValidFieldName : string read FInputValidFieldName write FInputValidFieldName stored IsStoreInputValidFieldName;
    property    OnValidChanged : TNotifyEvent read FOnValidChanged write FOnValidChanged;
    property    OnNeedPassword : TNeedPasswordEvent read FOnNeedPassword write FOnNeedPassword;
    property    OnException : TNotifyEvent read FOnException write FOnException;
    property    OnInputValidChanged : TNotifyEvent read FOnInputValidChanged write FOnInputValidChanged;
    property    OnWarningCustomerStatus : TNotifyEvent read FOnWarningCustomerStatus write FOnWarningCustomerStatus;
    property    OnCheckCustomerValid : TCheckCustomerValidEvent read FOnCheckCustomerValid write FOnCheckCustomerValid;
    property    OnCustomerChanged : TNotifyEvent read FOnCustomerChanged write FOnCustomerChanged;
  end;

var
  AccountInputMethods : TAccountInputMethods;

function   FormatAndValidAccount(MethodChar : Char; var Account : string; CanEmpty : Boolean=False): Boolean;

type
  TInputPasswordEvent = procedure (MaxLen : Integer; var AText : string; var OK : Boolean) of object;

  TPasswordInputMethod = class(TComponent)
  private
    FOnInputPassword: TInputPasswordEvent;
  protected

  public
    constructor Create(AOwner : TComponent); override;
    destructor  Destroy; override;
    function    InputPassword(MaxLen : Integer; var AText : string) : Boolean;
  published
    property    OnInputPassword : TInputPasswordEvent read FOnInputPassword write FOnInputPassword;
  end;

var
  PasswordInputMethod : TPasswordInputMethod;

implementation

uses KSStrUtils, SafeCode, LogFile, WVCtrls, KSClientConsts, KSFrameWorkUtils, DataTypes;

type
  TControlAccess = class(TControl);
  TWinControlAccess = class(TWinControl);

function   FormatAndValidAccount(MethodChar : Char; var Account : string; CanEmpty : Boolean=False): Boolean;
var
  AccountInputMethod : TAccountInputMethod;
begin
  Result := True; // ����������ʶ����˺�����
  if AccountInputMethods<>nil then
  begin
    AccountInputMethod := AccountInputMethods.FindInputMethod(MethodChar);
    if AccountInputMethod<>nil then
      Result := AccountInputMethod.FormatAndValidAccount(Account,CanEmpty);
  end;
end;

{ TAccountInputMethod }

procedure TAccountInputMethod.Assign(Source: TPersistent);
begin
  if Source is TAccountInputMethod then
    with TAccountInputMethod(Source) do
    begin
      FNeedReinput := Self.NeedReinput;
      FMethodChar := Self.MethodChar;
      FMarket := Self.Market;
      FCaption := Self.Caption;
      FPattern := Self.Pattern;
    end
  else
    inherited;
end;

constructor TAccountInputMethod.Create(Collection: TCollection);
begin
  inherited;
  FCheckLength := True;
  FCheckChars := True;
end;

function TAccountInputMethod.FormatAndValidAccount(
  var Account: string; CanEmpty : Boolean=False): Boolean;
const
  Digitals = ['0'..'9'];
var
  I : Integer;
  Len : Integer;
  ErrorChar : Boolean;
begin
  Result := False;
  // �ǿյ�ʱ����
  if Account<>'' then
    Account := ExpandLeft(Account,Pattern);
  Len := Length(Account);
  if Len=0 then
    Result := CanEmpty
  else if not CheckLength or (Len=Length1) or (Len=Length2) then
  begin
    if CheckChars then
    begin
      // ������ַ��Ƿ������ֻ�����FirstChars����
      if (Account[1] in Digitals) or (Pos(Account[1],FirstChars)>0) then
      begin
        // ����һ������������ַ�������������֣�����ȷ��
        ErrorChar := False;
        for I:=2 to Len do
          if not (Account[I] in Digitals) then
          begin
            ErrorChar := True;
            Break;
          end;
        Result := not ErrorChar;
      end;
    end else
      // ������ַ��Ƿ���Ч
      Result := True;
  end; // else �մ����߳��Ȳ�����Ч
  // ������������¼����д���
  if Assigned(OnFormatAndValidAccount) then
    OnFormatAndValidAccount(Self,Account,Result);
end;

function TAccountInputMethod.GetDisplayName: string;
begin
  Result := Caption;
end;

function TAccountInputMethod.NextInputMethod: TAccountInputMethod;
begin
  if Index<Collection.Count-1 then
    Result := TAccountInputMethod(Collection.Items[Index+1]) else
    Result := TAccountInputMethod(Collection.Items[0]);
end;

{ TAccountInputMethods }

procedure TAccountInputMethods.DoAdvancedSelect(Sender: TKSAccountEdit;
  var Selected: Boolean; var CustomerNo: string);
begin
  if Assigned(OnAdvancedSelect) then
    OnAdvancedSelect(Sender,Selected,CustomerNo) else
    Selected := False;
end;

constructor TAccountInputMethods.Create(AOwner: TComponent);
begin
  inherited;
  FMethods := TOwnedCollection.Create(Self,TAccountInputMethod);
  FFirstMethodChar := '0';
  if AccountInputMethods=nil then
    AccountInputMethods := Self;
end;

destructor TAccountInputMethods.Destroy;
begin
  if AccountInputMethods=Self then
    AccountInputMethods := nil;
  FMethods.Free;
  inherited;
end;

function TAccountInputMethods.FindInputMethod(
  MethodChar: Char): TAccountInputMethod;
var
  I : Integer;
begin
  for I:=0 to Methods.Count-1 do
  begin
    Result := TAccountInputMethod(Methods.Items[I]);
    if Result.MethodChar=MethodChar then
      Exit;
  end;
  Result := nil;
end;

procedure TAccountInputMethods.GetCustomers(Sender: TKSAccountEdit;
  Customers: TObjectList);
begin
  CheckTrue(Assigned(OnGetCustomers));
  OnGetCustomers(Sender,Customers);
end;

procedure TAccountInputMethods.GetMainAccounts(Sender: TKSAccountEdit;
  MainAccounts: TObjectList);
begin
  CheckTrue(Assigned(OnGetMainAccounts));
  OnGetMainAccounts(Sender,MainAccounts);
end;

procedure TAccountInputMethods.GetMoneyAccounts(Sender: TKSAccountEdit;
  MoneyAccounts: TObjectList);
begin
  CheckTrue(Assigned(OnGetMoneyAccounts));
  OnGetMoneyAccounts(Sender,MoneyAccounts);
end;

procedure TAccountInputMethods.InputPassword(Sender: TKSAccountEdit;
  var Passed: Boolean);
begin
  if Assigned(OnInputPassword) then
    OnInputPassword(Sender,Passed);
end;

procedure TAccountInputMethods.ReInput(Sender: TKSAccountEdit;
  var Passed: Boolean);
begin
  if Assigned(OnReInput) then
    OnReInput(Sender,Passed);
end;

procedure TAccountInputMethods.SelectCustomer(Sender: TKSAccountEdit;
  Customers: TObjectList; var SelectedCustomer: TKSAbstractCustomer;
  var Passed: Boolean);
begin
  CheckTrue(Assigned(OnSelectCustomer));
  OnSelectCustomer(Sender,Customers,SelectedCustomer,Passed);
end;

procedure TAccountInputMethods.SetMethods(const Value: TCollection);
begin
  FMethods.Assign(Value);
end;

procedure TAccountInputMethods.ShowTheHint(Sender: TKSAccountEdit);
begin
  if Assigned(OnShowEditHint) then
    OnShowEditHint(Sender);
end;

{ TKSAccountEdit }

constructor TKSAccountEdit.Create(AOwner: TComponent);
begin
  inherited;
  CharCase := ecUpperCase;
  FSwitchKey := VK_F2;
  FMainAccounts := TObjectList.Create;
  FMoneyAccounts := TObjectList.Create;
  FNeedMainAccounts := True;
  FNeedReinput := False;
  FNeedPassword := False;
  FNeedPasswordOnCrossDepart := False;
  FFirstMethodChar := '0';
  FPasswordType := 1;
  FCustInfoGroupIndex := 1;
  FAccountInfoGroupIndex := 2;
  FMoneyInfoGroupIndex := 3;
  FGoNextWhenPressEnter := True;
  FGoPrevChar := '*';
  FRequired := True;
  FInputValid := False;
  FAllowCustomerStatus := '';
  FNormalStatus := '0';
  FProhibitCrossDepart := False;
  FIsWarningCustomerStatus := True;
  FProhibitSelectDepart := False;
  FGlobalFirstMethodChar := False;
  FAllowCenter := True;
  FInputValidFieldName := DefaultInputValidFieldName;
  FAutoGoNext := True;
end;

destructor TKSAccountEdit.Destroy;
begin
  FreeAndNil(FMainAccounts);
  FreeAndNil(FMoneyAccounts);
  inherited;
end;

procedure TKSAccountEdit.Loaded;
begin
  inherited;
  if (AccountInputMethods<>nil) and GlobalFirstMethodChar then
  begin
    if (AllowMethods='') or (Pos(AccountInputMethods.FirstMethodChar, AllowMethods)>0) then
      FirstMethodChar := AccountInputMethods.FirstMethodChar;
  end;
  Reset;
end;

procedure TKSAccountEdit.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited;
  if Operation=opRemove then
  begin
    if AComponent=LabelCtrl  then
      FLabelCtrl := nil
    else if AComponent=WorkView then
      FWorkView := nil;
  end;
end;


procedure TKSAccountEdit.FirstInputMethod;
var
  TheMethod : TAccountInputMethod;
begin
  if (AccountInputMethods=nil) or (AccountInputMethods.Methods.Count=0) then
    CurrentInputMethod := nil
  else
  begin
    TheMethod := AccountInputMethods.FindInputMethod(FirstMethodChar);
    if TheMethod=nil then
      TheMethod := TAccountInputMethod(AccountInputMethods.Methods.Items[0]);
    CurrentInputMethod := GetMethod(TheMethod);
  end;
end;

procedure TKSAccountEdit.NextInputMethod;
begin
  if CurrentInputMethod=nil then
    FirstInputMethod else
    CurrentInputMethod := GetMethod(CurrentInputMethod.NextInputMethod);
end;

procedure TKSAccountEdit.Reset;
begin
  Text := '';
  Valid := False;
  FDataChanged := False;
  FirstInputMethod;
  UpdateLabelDisplay;
  SaveLastData;
  CheckInputValid;
  UpdateColor;
end;

procedure TKSAccountEdit.SetAllowMethods(const Value: string);
begin
  if FAllowMethods <> Value then
  begin
    FAllowMethods := Value;
    Reset;
  end;
end;

procedure TKSAccountEdit.SetLabelCtrl(const Value: TControl);
begin
  if FLabelCtrl <> Value then
  begin
    FLabelCtrl := Value;
    if FLabelCtrl<>nil then
    begin
      FLabelCtrl.FreeNotification(Self);
      UpdateLabelDisplay;
    end;
  end;
end;

procedure TKSAccountEdit.UpdateLabelDisplay;
begin
  if FLabelCtrl<>nil then
    if FCurrentInputMethod<>nil then
      TControlAccess(FLabelCtrl).Caption := FCurrentInputMethod.Caption
    else if csDesigning in ComponentState then
      TControlAccess(FLabelCtrl).Caption := '<�����˺�>'
    else
      TControlAccess(FLabelCtrl).Caption := '';
end;

procedure TKSAccountEdit.SetCurrentInputMethod(
  const Value: TAccountInputMethod);
begin
  if FCurrentInputMethod <> Value then
  begin
    FCurrentInputMethod := Value;
    if FCurrentInputMethod<>nil then
    begin
      FAcceptAlphabet := not FCurrentInputMethod.CheckChars or (FCurrentInputMethod.FirstChars<>'');
      FAcceptOther := not FCurrentInputMethod.CheckChars;
      if FCurrentInputMethod.Length2>FCurrentInputMethod.Length1 then
        MaxLength := FCurrentInputMethod.Length2 else
        MaxLength := FCurrentInputMethod.Length1;
      ReadOnly := False;  
    end else
    begin
      FAcceptAlphabet := False;
      FAcceptOther := False;
      MaxLength := 0;
      ReadOnly := True;
    end;
    UpdateLabelDisplay;
  end;
end;

procedure TKSAccountEdit.DoEnter;
begin
  inherited;
  //SaveLastData;
end;

procedure TKSAccountEdit.DoExit;
begin
  inherited;
  PostMessage(Handle,WM_CheckData,0,0);
  //CheckData;
end;

procedure TKSAccountEdit.KeyUp(var Key: Word; Shift: TShiftState);
begin
  if Key=FSwitchKey then
  begin
    // �û���F2�л������˺����
    if ssAlt in Shift  then
    begin
      if AdvancedSelect then
        DoAdvancedSelect;
    end
    else if ssCtrl in Shift then
    begin
      if Valid then
      begin
        GetCustomerInfoFromDB;
        RefreshCustomerInfoDisplay;
      end;
    end else
      NextInputMethod;
    Key := 0;
  end;
  inherited;
end;

procedure TKSAccountEdit.KeyPress(var Key: Char);

  procedure GoCtrl(GoForward : Boolean);
  var
    WinControl : TWinControl;
  begin
    if Owner is TWinControl then
      WinControl := TWinControl(Owner) else
      WinControl := GetParentForm(Self);
    if WinControl=nil then
      WinControl:=Parent;
    if WinControl<>nil then
      TWinControlAccess(WinControl).SelectNext(Self,GoForward,True);
  end;

begin
  if Key=FGoPrevChar then
  begin
    // ����ǰ����'*'
    Key := #0;
    { // old version
    WinControl := GetParentForm(Self);
    if WinControl=nil then
      WinControl:=Parent;
    if WinControl<>nil then
      TWinControlAccess(WinControl).SelectNext(Self,False,True);
    }
    if WorkView<>nil then
      WorkView.SelectPrev(Self) else
      GoCtrl(False);
  end
  else if Key=#13 then
  begin
    // ����س�
    Key := #0;
    FAutoGoNext := True;
    if CheckData(True,True,False,True) then
    begin
      if GoNextWhenPressEnter and FAutoGoNext then
      begin
        { // old version
        if Owner is TWinControl then
          WinControl := TWinControl(Owner) else
          WinControl := GetParentForm(Self);
        if WinControl=nil then
          WinControl:=Parent;
        if WinControl<>nil then
          TWinControlAccess(WinControl).SelectNext(Self,True,True);
        }
        if WorkView<>nil then
          WorkView.SelectNext(Self) else
          GoCtrl(True);
      end else
        SelectAll;
    end else
      SelectAll;
  end
  else if Key in ['a'..'z','A'..'Z'] then
  begin
    // ������ĸ
    if not FAcceptAlphabet then
      Key := #0;
  end
  else if (Key>=#32) and not (Key in ['0'..'9']) then
  begin
    // �������������ַ������磺+,-,(,)
    if not FAcceptOther then
      Key := #0;
  end;
  inherited;
end;


function  TKSAccountEdit.CheckData(
  CheckNeedReinput:Boolean=True;
  CheckNeedPassword:Boolean=True;
  IgnoreNoChange : Boolean=False;
  AShowHint : Boolean=False) : Boolean;
var
  NewText : string;
  Customers : TObjectList;
  AccountFormatValid : Boolean;
  AIsDataChanged : Boolean;
  OldValid, OldInputValid : Boolean;
begin
  OldValid := Valid;
  OldInputValid := InputValid;
  AIsDataChanged := False;
  try
    Result := False;
    if CurrentInputMethod=nil then
      Valid:=False else
    try
      // a����ʽ�����Ҽ����˺Ÿ�ʽ�Ƿ����
      //NewText := ExpandLeft(Text,CurrentInputMethod.Pattern);
      NewText := Text;
      AccountFormatValid := CurrentInputMethod.FormatAndValidAccount(NewText);
      if NewText<>Text  then
        Text := NewText;
      // b������˺��������������뱣�����ǰ���˺��������������в�ͬ����Ϊ��һ����������˺�ֵ���˺���δ��֤�ġ�
      AIsDataChanged := IsDataChanged;
      if AIsDataChanged then
      begin
        Valid := False;
        FCustomerPassword := '';
      end;
      // ���浱ǰ��״̬
      SaveLastData;
      // c������˺�ֵ��������ģ�����˺Ų��ǿմ�����Ϊ��һ��������Ч���˺�ֵ��������Ϊ��һ��������Ч���˺�ֵ��
      if (Text='') or not AccountFormatValid then
      begin
        Valid := False;
        if (Text<>'') and not AccountFormatValid and AShowHint then
          ShowTheHint;
      end
      else if not Valid and (Text<>'') and (not IgnoreNoChange or AIsDataChanged) then
      begin
        FCustomerPassword := '';
        // d������˺�ֵ��δ��֤�ģ����һ�����Ч���ǿգ������Ҳ�����û�иı��ֵ��ִ������Ĳ���
        // i�����Ҫ�����䣬���ֶԻ����������ֵ����ͬ�����߲���Աȡ�����˳���������δ��֤״̬�����������һ����
        if IsNeedReinput and CheckNeedReinput then
          if not DoReinput then
            Exit;
        // ii�������˺������˺�ֵ�������������ͻ���Ϣ��
        Customers := TObjectList.Create;
        try
          GetCustomers(Customers);
          // iii��������ض��Ӫҵ��������һ�У���Ҫ�����Աѡ��Ӫҵ�����������Աȡ�����˳���������δ��֤״̬�����������һ����
          // iv������ѡ�е�Ӫҵ��������ͻ��źͿͻ���Ϣ�� FCustomer
          if not SelectCustomers(Customers, FCustomer) then
            Exit;
          Customers.Extract(FCustomer);
        finally
          Customers.Free;
        end;
        FCustomerValid := True;
        // ����Ƿ��ֹ��Ӫҵ��
        if ProhibitCrossDepart and (FCustomer.Department<>Department) and not IsAllowCenter then
          raise Exception.Create('�����������Ӫҵ���Ŀͻ����в���');
        // v�����Ҫ��ͻ��������룬���ֶԻ���Ҫ��ͻ��������롣
        if IsNeedPassword and CheckNeedPassword then
          if not DoInputPassword then
          begin
            FreeAndNil(FCustomer);
            Exit;
          end;

        // vii�������Ҫȡ�����г������ɶ����룬��ô���ݿͻ��ţ�ȡ�����г������ɶ����룬���档
        // viii)�����Ҫ��ȡ�������ֵĻ����������ô���ݿͻ��ţ�ȡ�������ֵĻ�����������档
        GetCustomerInfoFromDB;

        // ix����ʾ�ͻ���Ϣ�����Ե�ii������������Ϊ����֤״̬��
        Valid := True;
        // x)���ͻ�״̬
        CheckCustomerStatus;
      end;
      //Result := True;
      // ������Ч��ʱ�������л�����һ�����뽹��
      Result := InputValid; //(Text<>'')
    except
      // ���ݷ��ʴ���
      Valid := False;
      FreeAndNil(FCustomer);
      Result := False; // ���Զ��л����뽹��
      HandleException;
      //WriteException;
    end;
  finally
    // ���е�Exit�������
    if ( (OldValid <> Valid) or (OldInputValid<>InputValid) or AIsDataChanged ) and
      Assigned(FOnCustomerChanged) then
      FOnCustomerChanged(Self);
  end;
end;

procedure TKSAccountEdit.GetCustomers(Customers: TObjectList);
begin
  Assert(AccountInputMethods<>nil);
  AccountInputMethods.GetCustomers(Self,Customers);
end;

function TKSAccountEdit.SelectCustomers(Customers: TObjectList; var SelectedCustomer : TKSAbstractCustomer): Boolean;
begin
  SelectedCustomer := nil;
  // SelectCustomers : ѡ��ͬӪҵ���Ŀͻ��������Ƿ������
  // ���Customers.Count=1��ֱ�ӷ���True
  if Customers.Count=1 then
  begin
    Result := True;
    SelectedCustomer := TKSAbstractCustomer(Customers[0]);
  end
  // ���Customers.Count=0�����߽�ֹѡ��Ӫҵ����ֱ�ӷ���False
  else if (Customers.Count=0) or ProhibitSelectDepart then
    Result := False
  else
  begin
  // ���Customers.Count>1�����ֶԻ����ò���Աѡ�����ѡ�񣬷���True�����ȡ��������False
    Result := True;
    Assert(AccountInputMethods<>nil);
    AccountInputMethods.SelectCustomer(Self,Customers,SelectedCustomer,Result);
    Assert(not Result or (SelectedCustomer<>nil));
  end;
end;

procedure TKSAccountEdit.SetValid(const Value: Boolean);
begin
  if FValid <> Value then
  begin
    if Value then
      CheckObject(FCustomer);
    FValid := Value;
    if FValid then
    begin
      SaveLastData;
      FreeAndNil(FTempAccount);
      if CurrentInputMethod.Market<>'' then
        FTempAccount := TKSSecAccount2.Create(Customer,CurrentInputMethod.Market);
    end else
    begin
      FMainAccounts.Clear;
      FMoneyAccounts.Clear;
      FreeAndNil(FCustomer);
      FreeAndNil(FTempAccount);
      FCustomerPassword := '';
    end;
    CheckInputValid;
    try
      RefreshCustomerInfoDisplay;
      if Assigned(OnValidChanged) then
        OnValidChanged(Self);
    except
      //WriteException;
      HandleException;
    end;
  end;
end;

function TKSAccountEdit.DoInputPassword: Boolean;
begin
  Assert(AccountInputMethods<>nil);
  Result := True;
  AccountInputMethods.InputPassword(Self,Result);
end;

function TKSAccountEdit.DoReinput: Boolean;
begin
  Assert(AccountInputMethods<>nil);
  Result := True;
  AccountInputMethods.ReInput(Self,Result);
end;

procedure TKSAccountEdit.DoGetMainAccounts;
begin
  MainAccounts.Clear;
  Assert(AccountInputMethods<>nil);
  AccountInputMethods.GetMainAccounts(Self,MainAccounts);
end;

procedure TKSAccountEdit.DoGetMoneyAccounts;
begin
  MoneyAccounts.Clear;
  Assert(AccountInputMethods<>nil);
  AccountInputMethods.GetMoneyAccounts(Self,MoneyAccounts);
end;

function TKSAccountEdit.IsDataChanged: Boolean;
begin
  Result := (FSavedInputMethod<>CurrentInputMethod) or (FSavedValue<>Text);
end;

function TKSAccountEdit.IsNeedPassword: Boolean;
begin
  Assert(Customer<>nil);
  if NeedPasswordOnCrossDepart and not IsAllowCenter then
  begin
    Result := (Customer.Department<>Department) or FNeedPassword;
  end else
    Result := FNeedPassword;
  if Assigned(OnNeedPassword) then
    OnNeedPassword(Self,Result);
end;

function TKSAccountEdit.IsNeedReinput: Boolean;
begin
  Assert(FCurrentInputMethod<>nil);
  Result := NeedReinput and (FCurrentInputMethod.NeedReinput);
end;

function TKSAccountEdit.IsNeedMainAccounts: Boolean;
begin
  Result := NeedMainAccounts;
end;

function TKSAccountEdit.IsNeedMoneyAccounts: Boolean;
begin
  Result := NeedMoneyAccounts;
end;

procedure TKSAccountEdit.SaveLastData;
begin
  FSavedInputMethod := CurrentInputMethod;
  FSavedValue := Text;
end;

function TKSAccountEdit.AcceptInputMethod(
  InputMethod: TAccountInputMethod): Boolean;
begin
  Result := (AllowMethods='') or (Pos(InputMethod.MethodChar,AllowMethods)>0);
end;

function TKSAccountEdit.GetMethod(
  InputMethod: TAccountInputMethod): TAccountInputMethod;
var
  AMethod : TAccountInputMethod;
  {$ifdef debug }
  I : Integer;
  {$endif}
begin
  {$ifdef debug }
  I := 0;
  {$endif}
  AMethod := InputMethod;
  Result := nil;
  repeat
    if AcceptInputMethod(AMethod) then
    begin
      Result := AMethod;
      Break;
    end else
      AMethod := AMethod.NextInputMethod;
    {$ifdef debug }
    Inc(I);
    Assert(I<=AMethod.Collection.Count+2);
    {$endif}
  until AMethod=InputMethod;
end;

(*
function TKSAccountEdit.GetAccount(
  const Market: string): TKSAbstractSecAccount;
begin
  CheckData;
  if not Valid then
    Result := nil
  else
  begin
    if CurrentInputMethod.Market=Market then
  end;
end;
*)
procedure TKSAccountEdit.SetWorkView(const Value: TWorkView);
begin
  if FWorkView <> Value then
  begin
    FWorkView := Value;
    if FWorkView<>nil then
    begin
      FWorkView.FreeNotification(Self);
    end;
  end;
end;

procedure TKSAccountEdit.UpdateCustInfoWorkFields;
var
  I : Integer;
  Field : TWVField;
begin
  if WorkView<>nil then
  begin
    //if not Valid then
    WorkView.Reset(CustInfoGroupIndex);
    if Customer<>nil then
      for I:=0 to WorkView.FieldCount-1 do
      begin
        Field := WorkView.Fields[I];
        if (Field.GroupIndex=CustInfoGroupIndex) or (CustInfoGroupIndex=0) then
          Field.Data.AsString := Customer.GetParamValue(Field.DataField);
        if Customer=nil then
          Break;
      end;
  end;
end;

procedure TKSAccountEdit.SetMarket(const Value: string);
begin
  if FMarket <> Value then
  begin
    FMarket := Value;
    UpdateAccountInfoWorkFields;
  end;
end;

procedure TKSAccountEdit.SetCurrencyType(const Value: string);
begin
  if FCurrencyType <> Value then
  begin
    FCurrencyType := Value;
    UpdateMoneyInfoWorkFields;
  end;
end;

procedure TKSAccountEdit.UpdateAccountInfoWorkFields;
var
  Account : TKSAbstractSecAccount;
  I : Integer;
  Field : TWVField;
begin
  if (WorkView<>nil) and IsNeedMainAccounts then
  begin
    //if not Valid then
    WorkView.Reset(AccountInfoGroupIndex);
    Account := GetSecAccount(Market);
    if Account<>nil then
    begin
      for I:=0 to WorkView.FieldCount-1 do
      begin
        Field := WorkView.Fields[I];
        if (Field.GroupIndex=FAccountInfoGroupIndex) or (FAccountInfoGroupIndex=0) then
          Field.Data.AsString := Account.GetParamValue(Field.DataField);
        if Customer=nil then
          Break;  
      end;
    end;
  end;
end;

function TKSAccountEdit.GetSecAccount(
  const AMarket: string): TKSAbstractSecAccount;
var
  I : Integer;
begin
  Result := nil;
  if Valid then
  begin
    if (FTempAccount<>nil) and (FTempAccount.Market=Market) then
    begin
      Result := FTempAccount;
    end else
    begin
      for I:=0 to MainAccounts.Count-1 do
      begin
        if TKSAbstractSecAccount(MainAccounts[I]).Market=AMarket then
        begin
          Result := TKSAbstractSecAccount(MainAccounts[I]);
          Break;
        end;
      end;
    end;
  end;
end;

procedure TKSAccountEdit.UpdateMoneyInfoWorkFields;
var
  Account : TKSAbstractMoneyAccount;
  I : Integer;
  Field : TWVField;
begin
  if (WorkView<>nil) and IsNeedMoneyAccounts then
  begin
    //if not Valid then
    WorkView.Reset(MoneyInfoGroupIndex);
    Account := GetMoneyAccount(CurrencyType);
    if Account<>nil then
    begin
      for I:=0 to WorkView.FieldCount-1 do
      begin
        Field := WorkView.Fields[I];
        if (Field.GroupIndex=MoneyInfoGroupIndex) or (MoneyInfoGroupIndex=0) then
          Field.Data.AsString := Account.GetParamValue(Field.DataField);
        if Customer=nil then
          Break;  
      end;
    end;
  end;
end;

function TKSAccountEdit.GetMoneyAccount(
  const ACurrencyType: string): TKSAbstractMoneyAccount;
var
  I : Integer;
begin
  Result := nil;
  if Valid then
    for I:=0 to MoneyAccounts.Count-1 do
    begin
      if TKSAbstractMoneyAccount(MoneyAccounts[I]).CurrencyType=ACurrencyType then
      begin
        Result := TKSAbstractMoneyAccount(MoneyAccounts[I]);
        Break;
      end;
    end;
end;

procedure TKSAccountEdit.SetCustomer(const CustomerNo: string);
begin
  //CustomerNo := ;
  Text := CustomerNo;
  if AccountInputMethods<>nil then
  begin
    CurrentInputMethod := AccountInputMethods.FindInputMethod(CustomerNoInputMethodChar);
    CheckData(False,True,False,False);
  end;
end;

procedure TKSAccountEdit.Assign(Source: TPersistent);
begin
  if Source is TKSAccountEdit then
  begin
    // �������ƿͻ���Ϣ
    CurrentInputMethod := TKSAccountEdit(Source).CurrentInputMethod;
    Text := TKSAccountEdit(Source).Text;
    //Customer
    { TODO : ��δAssign�� }
  end;
  inherited;
end;

procedure TKSAccountEdit.DoAdvancedSelect;
var
  Selected : Boolean;
  CustomerNo : string;
begin
  Selected := False;
  if AccountInputMethods<>nil then
  begin
    AccountInputMethods.DoAdvancedSelect(Self,Selected,CustomerNo);
    if Selected then
      SetCustomer(CustomerNo);
  end;
end;

procedure TKSAccountEdit.SetRequired(const Value: Boolean);
begin
  if FRequired <> Value then
  begin
    FRequired := Value;
    CheckInputValid;
  end;
end;

function TKSAccountEdit.GetInputValid: Boolean;
begin
  if Valid then
    Result := FCustomerValid else
    Result := not Required and (Text='');
end;

procedure TKSAccountEdit.UpdateColor;
begin
  if WorkView<>nil then
    SetControlColor(Self,WorkView,InputValid,ReadOnly or not Enabled);
end;

procedure TKSAccountEdit.HandleException;
begin
  if Assigned(OnException) then
    OnException(Self)
  else if AccountInputMethods<>nil then
  begin
    if Assigned(AccountInputMethods.OnException) then
      AccountInputMethods.OnException(Self);
  end;
end;

procedure TKSAccountEdit.CheckInputValid;
var
  Value : Boolean;
  Field : TWVField;
begin
  FCustomerValid := True;
  if Assigned(FOnCheckCustomerValid) then
    FOnCheckCustomerValid(Self, FCustomerValid);

  Value := InputValid;
  if Value<>FInputValid then
  begin
    FInputValid := Value;
    if WorkView<>nil then
    begin
      Field := WorkView.FindField(InputValidFieldName);
      if (Field<>nil) and (Field.DataType=kdtBoolean) then
        Field.Data.SetBoolean(FInputValid);
    end;

    if Assigned(OnInputValidChanged) then
      OnInputValidChanged(Self);
    UpdateColor;
  end;
end;

procedure TKSAccountEdit.Change;
begin
  inherited;
  CheckInputValid;
  if WorkView<>nil then
    WorkView.DataChanged;
end;

procedure TKSAccountEdit.SelectAll;
begin
  SelStart := 0;
  SelLength := Length(Text);
end;

procedure TKSAccountEdit.WMCheckData(var Message: TMessage);
begin
  CheckData(True,True,True,False);
end;

procedure TKSAccountEdit.CheckCustomerStatus;
var
  NeedWarning : Boolean;
begin
  if IsWarningCustomerStatus then
  begin
    NeedWarning := False;
    if (Customer<>nil) then
    begin
      if AllowCustomerStatus='' then
      begin
        // û��ָ������Ŀͻ�״̬����ô���ͻ�״̬��������ʱ����ʾ
        if (Customer.Status<>NormalStatus) then
          NeedWarning := True;
      end
      else if Pos(Customer.Status,AllowCustomerStatus)<=0 then
        // ָ������ͻ�״̬����ô���ͻ�״̬���������״̬����ʾ
        NeedWarning := True;
    end;
    if NeedWarning then
      WarningCustomerStatus;
  end;
end;

procedure TKSAccountEdit.WarningCustomerStatus;
begin
  if Assigned(OnWarningCustomerStatus) then
    OnWarningCustomerStatus(Self)
  else if (AccountInputMethods<>nil)
    and Assigned(AccountInputMethods.OnWarningCustomerStatus) then
    AccountInputMethods.OnWarningCustomerStatus(Self);
end;

procedure TKSAccountEdit.SetCustomerPassword(const Password: string);
begin
  FCustomerPassword := Password;
end;

procedure TKSAccountEdit.ShowTheHint;
begin
  if AccountInputMethods<>nil then
    AccountInputMethods.ShowTheHint(Self);
end;

function TKSAccountEdit.IsAllowCenter: Boolean;
begin
  Result := FAllowCenter and IsCenterDepartment;
end;

function TKSAccountEdit.IsStoreInputValidFieldName: Boolean;
begin
  Result := not SameText(InputValidFieldName,DefaultInputValidFieldName);
end;

procedure TKSAccountEdit.CMEnabledChanged(var Message: TMessage);
begin
  inherited;
  UpdateColor;
end;

procedure TKSAccountEdit.GetCustomerInfoFromDB;
begin
  Assert(Customer<>nil);
  if IsNeedMainAccounts then
    DoGetMainAccounts;
  if IsNeedMoneyAccounts then
    DoGetMoneyAccounts;
end;

procedure TKSAccountEdit.RefreshCustomerInfoDisplay;
begin
  UpdateCustInfoWorkFields;
  UpdateAccountInfoWorkFields;
  UpdateMoneyInfoWorkFields;
end;

{ TPasswordInputMethod }

constructor TPasswordInputMethod.Create(AOwner: TComponent);
begin
  inherited;
  if PasswordInputMethod=nil then
    PasswordInputMethod:=Self;
end;

destructor TPasswordInputMethod.Destroy;
begin
  if PasswordInputMethod=Self then
    PasswordInputMethod:=nil;
  inherited;
end;

function TPasswordInputMethod.InputPassword(MaxLen: Integer;
  var AText: string): Boolean;
begin
  Result := False;
  if Assigned(FOnInputPassword) then
  begin
    FOnInputPassword(MaxLen,AText,Result);
  end;
end;

end.
