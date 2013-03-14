unit KSComCmdDefs;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSComCmdDefs
   <What>���������������������������ݱ�﷽ʽ�����õĹ��������ȵȡ�
   ��Щ��������һ����������Դ���ʡ���Щ����Դ�ķ�����ʽ���������������塣
   ��Ӧ����������һ��λ���������UCommData��Ԫ��
   <Written By> Huang YanLai (������)���Ź���
   <History>
      01  ���������е������򣬲�ֳ�ҵ���޹���ҵ����������֣����Ժ�
          ά���õ�Ԫ��ͬ־Ҳ����ע�����֣�����ߴ���Ŀ�������
                                                �Ź���   20010922
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
    //�ַ���������
    GetDataDictionaryItems: TWVStringsMan;

    //���ݱ�����ʽ����
    fpIDObjects: TWVFieldPresent;
    fpMultiIDObjects: TWVFieldPresent;
    fpCurrency: TWVFieldPresent;
    fpChinaCurrency: TWVFieldPresent;
    fpFeeRate: TWVFieldPresent;

    //������������
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

    //ҵ���޹ز��ֵ���
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

    //ҵ����ز��ֵ���
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

    //��Ԫ���Ĺ���
    procedure DataModuleCreate(Sender: TObject);
    procedure DataModuleDestroy(Sender: TObject);

    //��������ֵ���Ŀ�е��ַ����Ĵ������
    procedure GetDataDictionaryItemsGetStrings(const StringsName: string;
      Items: TStrings; var Handled: Boolean);

    //����ת����ʽ�Ĵ������
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

    //ҵ���޹ص���Ĵ������
    procedure fdReinputCheckCheckValid(WorkField: TWVField);
    procedure fdCompDataCheckValid(WorkField: TWVField);
    procedure fdCompData2CheckValid(WorkField: TWVField);
    procedure fdDateCheckCheckValid(WorkField: TWVField);
    procedure fdDateCheck2CheckValid(WorkField: TWVField);
    procedure fdDateReCheckCheckValid(WorkField: TWVField);
    procedure fdYearMonthCheckCheckValid(WorkField: TWVField);
    procedure fdCheckTimeCheckValid(WorkField: TWVField);
    procedure fdTimeReCheckCheckValid(WorkField: TWVField);

    //ҵ����ص���Ĵ������
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
    //wlj 20031219 �۸��domain����ʾ��ʽҪ��ȡ����,�۸�Ϊ������С�����4λ
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
    //  CompDataCheck �Ƚ�����ֵ�Ĵ�С
    procedure CompDataCheck(WorkField: TWVField; IsZeroEqueltoAll: Boolean;
      IsBig: Boolean = True; RetouchNum: Double = 0);
    // CheckDateValid�������ڵ���Ч��
    function CheckDateValid(const DateString: string; Needed: Boolean): Boolean;
    // CheckTimeValid����ʱ�����Ч��
    function CheckTimeValid(const TimeString: string): Boolean;

    // CheckExists ����˺�/�ͻ�/֤���Ƿ���ڡ�����true����,false������
    function CheckExists(AccountType: Char; CertType: Integer; const BankCode:
      string; const Account: string): Boolean;
    // GetCustomer ����Ӫҵ�����ͻ��Ż�ȡ�ͻ���Ϣ
    function GetCustomer(const BranchCode, CustomerNo: string):
      TKSAbstractCustomerInfo;
    // GetCustomerInfo ����Ӫҵ�����ͻ��Ż�ȡ�ͻ���Ϣ
    procedure GetCustomerInfo(const BranchCode, CustomerNo: string;
      CustomerInfos: TObjectList);
    // GetBroker ����Ӫҵ���������˺Ż�ȡ��������Ϣ
    function GetBroker(const BranchCode, BrokerNo: string):
      TKSAbstractBrokerInfo;
    // GetBrokerInfo ����Ӫҵ���������˺Ż�ȡ��������Ϣ
    procedure GetBrokerInfo(const BranchCode, BrokerNo: string; BrokerInfos:
      TObjectList);
    // GetSecAccount �����г����ɶ������ȡ�ɶ���Ϣ
    function GetSecAccount(const Market, Account: string):
      TKSAbstractSecAccount;
    // GetSecAccounts ���ݿͻ��Ż�ȡ�ɶ�����(SecAccounts�������TKSAbstractSecAccount)��Market=''��ʾ�����г�,AccountStatus=0��ʾȡ״̬�����Ĺɶ��ʺţ��ձ�ʾȫ��
    procedure GetSecAccounts(const CustomerNo: string; const Market: string;
      OnlyMainAccounts: Boolean; SecAccounts: TObjectList; AccountStatus: string
        =
      '');
    // GetMoneyAccounts ���ݿͻ��Ż�ȡ�ʽ��˺���Ϣ(MoneyAccounts�������TKSAbstractMoneyAccount)��CurrencyType=''��ʾ���б���
    procedure GetMoneyAccounts(Customer: TKSAbstractCustomer; const
      CurrencyType: string; MoneyAccounts: TObjectList);
    // GetBankAccounts ���ݿͻ��Ż�ȡ�����˺�(BankAccounts�������TKSAbstractBankAccount)
    procedure GetBankAccounts(const CustomerNo, Bank, CurrencyType: string;
      BankAccounts: TObjectList; QryType: Integer = 0);
    // GetGetSecInfo ����֤ȯ������г������ȡ֤ȯ��Ϣ(SecInfos�������TKSAbstractSecInfo)
    procedure GetSecInfo(const SecCode, Market: string; SecInfos: TObjectList);
    // GetSeatInfo �����г�����,��ѯӪҵ����ϯλ�����ȡϯλ��Ϣ(SeatInfos�������TKSAbstractSeatInfo)
    procedure GetSeatInfo(const Market, BranchCode, SeatNo: string; SeatInfos:
      TObjectList; UniqueFlag: Integer = 1);
    // GetSeat �����г�����,��ѯӪҵ����ϯλ�����ȡϯλ��Ϣ(SeatInfos�������TKSAbstractSeatInfo)
    function GetSeat(const Market: string; const BranchCode: string = '';
      UniqueFlag: Integer = 1): TKSAbstractSeatInfo;
    // GetEmpInfo ���ݲ�ѯӪҵ����ְ�������ȡְ����Ϣ(EmpInfos�������TKSAbstractEmpInfo)
    procedure GetEmpInfo(const BranchCode, EmpNo: string; EmpInfos:
      TObjectList);
    // GetEmp ���ݲ�ѯӪҵ����ְ�������ȡְ����Ϣ(EmpInfos�������TKSAbstractEmpInfo)
    function GetEmp(const EmpNo: string; const BranchCode: string = ''):
      TKSAbstractEmpInfo;
    // GetReportDay ��ÿ��Դ�ӡ��������һ��������
    function GetReportDay: string;
    // GetBranch2BankInfo ���ݲ�ѯӪҵ��,���Ҵ�������д����ȡӪҵ����Ӧ��������Ϣ(BankInfos�������TKSAbstractBankInfo)
    procedure GetBranch2BankInfo(const BranchCode, CurrencyType, BankCode:
      string; BankInfos: TObjectList);
    // GetStationAuth ���ݲ�ѯӪҵ���͸�λ�����ȡ��λȨ����Ϣ
    function GetStationAuth(const BranchCode: string = ''; const Station: string
      = ''): TKSAbstractStationAuthInfo;
    // GetStationAuthInfo ���ݲ�ѯӪҵ���͸�λ�����ȡ��λȨ����Ϣ(StationInfos�������TKSAbstractEmpInfo)
    procedure GetStationAuthInfo(const BranchCode, Station: string;
      StationInfos: TObjectList);
    // GetBranchInfos ��ȡӪҵ����Ϣ
    procedure GetBranchInfos;
    //NeedBranchs, ������е�Ӫҵ����Ϣ
    function NeedBranchs: TObjectList;
    //GetBranch return TKSAbstractBranch ��Ҫ�ֹ��ͷ�TKSAbstractBranch
    function GetBranch(const Branch: string): TKSAbstractBranch;
    //GetBranchInfoAdmin, ��ʼ��InfoAdmin
    procedure GetBranchInfoAdmin;
    //GetFeeLevel, �����շѷ�ʽ����շѵ���
    procedure GetFeeLevel(const Branch, FeeType: string; QueryType: Integer;
      FeeLevelSet: TObjectList);

    {***********��������************}
// GetTreatyGroupInfos ���ݲ�ѯӪҵ��,Э�����,Э��״̬,��ѯ��ʽ���Ƿ�����������Ƿ�����������ȡ�÷�����Ϣ(GroupInfos�������TKSAbstractGroupInfo)
    procedure GetTreatyGroupInfos(const BranchCode, TreatyStatus, IsDownToChild:
      string; const IsContainChild, QueryMode, GroupNo: Integer; GroupInfos:
      TObjectList);

    procedure CheckAccountFieldValid(WorkField: TWVField; MethodChar: Char;
      CanEmpty: Boolean = False);
    //NeedMarkets, ������е��г���Ϣ
    function NeedMarkets: TObjectList;
    //GetMarket return TKSAbstractMarket ��Ҫ�ֹ��ͷ�TKSAbstractMarket
    function GetMarket(const Market: string): TKSAbstractMarket;
    //SearchStock return TKSAbstractSecInfo in TObjectList.
    function SearchStock(const SecCode, Market: string; StockList: TObjectList):
      TKSAbstractSecInfo;
    //GetStock return TKSAbstractSecInfo ��Ҫ�ֹ��ͷ�TKSAbstractSecInfo
    function GetStock(const SecCode, Market: string): TKSAbstractSecInfo;
    function FindStock(const SecCode, Market: string): TKSAbstractSecInfo;
    //RequestStockInfo  ��TObjectList�л��ָ����֤ȯ��Ϣ����Ҫ�ֹ��ͷ�TKSAbstractSecInfo
    function RequestStockInfo(const SecCode, Market: string; StockList:
      TObjectList): TKSAbstractSecInfo;

    // FormatAndValidSecurityCode�����г�����,����֤ȯ�������Ч�Բ�����
    function FormatAndValidSecurityCode(const Market: string; var SecurityCode:
      string): Boolean;
    // FormatAndValidBrokerNo����Ӫҵ������,���龭���˺ŵ���Ч�Բ�����
    function FormatAndValidBrokerNo(var BrokerNo: string): Boolean;
    // ���е���˫��Ա����,ͨ���������ظ��˲���Ա�Ĺ��ź����룬ͨ������ֵ���ز���Ա�Ĺ��ź������Ƿ�Ϸ���
    function DoSingleStationCheck(
      const AOperation: string;
      var CheckerNo, CheckerPassword: string;
      FuncNo: Integer = 0;
      const CustomerNo: string = '';
      const CurrentType: string = '';
      const ACaption: string = ''
      ): Boolean;
    //���ض���ѯ��ʽ�£������Ŀ����ʾ���ƣ����ڲ�ѯ���棩
    procedure QueryControl(const QueryMethod: string; CustField, DeptField:
      TWVField;
      CustNo: TKSAccountEdit; BranchCode: TWVComboBox);
    (*
    //��ȡӪҵ��������ֵ
    function GetBranchParam(ParamCode: string;const BranchCode:string=''): string;
    *)

    // GetSecTypeSets �����г���ȡ֤ȯ��𼯺ϣ�Market����Ϊ��
    procedure GetSecTypeSets(const Market: string; SecTypeSet: TStringList);
    procedure GetWorkDay(var LastDay, CurrentDay, NextDay: string; const Market:
      string = '');
    //GetLiquidate��ȡ��������
    function GetLiquidate(DateType: Integer): string;

    //ADD BY CGM
    //����һ�����ĳ���ֶε����ƺ�ֵ��ѯ��һ���ֶε�ֵ
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
    Command.ParamData('�ʺ�����').SetString(AccountType);
    Command.ParamData('֤������').SetInteger(CertType);
    Command.ParamData('�ʺ�').SetString(Account);
    Command.ParamData('���д���').SetString(BankCode);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command);
    Result := not (Command.ParamData('����').AsInteger = 0);
  finally
    Command.Free;
  end;
end;

//��ùɶ�����

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
    Command.ParamData('�ͻ���').SetString(CustomerNo);
    Command.ParamData('�г�����').SetString(Market);
    if OnlyMainAccounts then
      Command.ParamData('�������־').SetInteger(2)
    else
      Command.ParamData('�������־').SetInteger(1);
    Command.ParamData('�ɶ�����').SetString('');
    if AccountStatus <> '' then
      Command.ParamData('�ɶ�״̬').SetString(AccountStatus)
    else
      Command.ParamData('�ɶ�״̬').SetString('');
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
    GetSecAccountsFromDataset(Dataset, SecAccounts);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

//��ø����г����ʽ���Ϣ

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
    Command.ParamData('�ͻ���').SetString(Customer.CustomerNo);
    Command.ParamData('����Ӫҵ��').SetString(Customer.Department);
    Command.ParamData('��������').SetString(CurrencyType);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
    GetMoneyAccountsFromDataset(Dataset, MoneyAccounts);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

//���֤ȯ��Ϣ

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
    Command.ParamData('֤ȯ����').SetString(SecCode);
    Command.ParamData('�г�����').SetString(Market);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
    GetSecInfosFromDataset(Dataset, SecInfos);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

//��������ʺ�

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
    Command.ParamData('�ͻ���').SetString(CustomerNo);
    Command.ParamData('���д���').SetString(Bank);
    Command.ParamData('��������').SetString(CurrencyType);
    Command.ParamData('��ѯ��ʽ').setinteger(QryType);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
    GetBankAccountsFromDataset(Dataset, BankAccounts);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

// ���ϯλ��Ϣ

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
    Command.ParamData('�г�����').SetString(Market);
    Command.ParamData('��ѯӪҵ��').SetString(BranchCode);
    Command.ParamData('ϯλ����').SetString(SeatNo);
    Command.ParamData('ϯλΨһ��־').SetInteger(UniqueFlag);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
    GetSeatInfosFromDataset(Dataset, SeatInfos);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

//�򵥲�ѯ

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
    Command.ParamData('����').SetString(TableName);
    Command.ParamData('�ֶ���').SetString(FieldName);
    Command.ParamData('�ֶ�ֵ').SetString(FieldValue);
    Command.ParamData('����ֶ���').SetString(ResultFieldName);

    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);

    if (DataSet = nil) or (DataSet.RecordCount = 0) or
      (DataSet.Fields[0].AsString = '�޷���ֵ') then
      result := ''
    else
      result := DataSet.Fields[0].AsString;

    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

// ���ϯλ��Ϣ

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
    Command.ParamData('�г�����').SetString(Market);
    Command.ParamData('��ѯӪҵ��').SetString(Branch);
    Command.ParamData('ϯλΨһ��־').SetInteger(UniqueFlag);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
    if (Dataset = nil) or Dataset.IsEmpty then
      Result := nil
    else
      Result := TKSSeatInfo.Create(Dataset);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

// ���ְ����Ϣ

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
    Command.ParamData('��ѯӪҵ��').SetString(BranchCode);
    Command.ParamData('ְ������').SetString(EmpNo);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
    GetEmpInfosFromDataset(Dataset, EmpInfos);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

// ���ְ����Ϣ

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
    Command.ParamData('��ѯӪҵ��').SetString(Branch);
    Command.ParamData('ְ������').SetString(EmpNo);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
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
    Command.ParamData('�г�����').SetString('');
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
    GetMarketInfosFromDataset(Dataset, FMarkets);
    FreeAndNil(Dataset);
  finally
    Command.Free;
  end;
end;

{
// hardcode�汾
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

// �����µ��г�����

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

//ȡ�ùɶ���Ϣ

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
    Command.ParamData('�ͻ���').SetString('');
    Command.ParamData('�г�����').SetString(Market);
    Command.ParamData('�������־').SetInteger(1);
    Command.ParamData('�ɶ�����').SetString(Account);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
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
      // �Ȳ���
      WorkField.Data.AsString := S1;
      // ��У��һ��
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

  //ͨ��������,�������ί������
  MaxEntrustVol := ConfigSystem.ReadInteger(ccInput, ckMaxEntrustVol,
    cdMaxEntrustVol);
  if MaxEntrustVol > 0 then
    fdEntrustVol.Checker.Max := MaxEntrustVol
  else
    fdEntrustVol.Checker.Max := cdMaxEntrustVol;
  fdEntrustVol.Hint := 'ί������:����0,��С�ڵ���' +
    inttostr(Trunc(fdEntrustVol.Checker.Max)) + '������';

  //ͨ��������,��������ֽ��ȡ���
  MaxCashSum := ConfigSystem.ReadFloat(ccInput, ckMaxCashSum, cdMaxCashSum);
  if MaxCashSum > 0 then
    fdCashDomain.Checker.Max := MaxCashSum
  else
    fdCashDomain.Checker.Max := cdMaxCashSum;
  fdCashDomain.Hint := '�ֽ���:����0,��С�ڵ���' +
    FloatToStr(fdCashDomain.Checker.Max) + '����';

  //ͨ��������,����������(֧Ʊ)��ȡ���
  MaxBankBookCheckSum := ConfigSystem.ReadFloat(ccInput, ckMaxBankBookCheckSum,
    cdMaxBankBookCheckSum);
  if MaxBankBookCheckSum > 0 then
    fdBankBookCheckDomain.Checker.Max := MaxBankBookCheckSum
  else
    fdBankBookCheckDomain.Checker.Max := cdMaxBankBookCheckSum;
  fdBankBookCheckDomain.Hint := '����(֧Ʊ)������0,С�ڵ���' +
    FloatToStr(fdBankBookCheckDomain.Checker.Max) + '����';

  //wlj 20031219 ��ȡ�۸�ĸ�ʽ
  FPriceFormat := ConfigSystem.ReadString(ccInput, ckPriceFormat,
    cdPriceFormat);
  FPricePrecision := ConfigSystem.ReadInteger(ccInput, ckPircePrecision,
    cdPricePrecision);

  if FPricePrecision > 0 then //�޸�domain��hint,����С����λ����ʾ.
  begin
    fdPrice.Hint := fdPrice.Hint + ',' + IntToStr(FPricePrecision) + 'λС��';
    fdPrice2.Hint := fdPrice2.Hint + ',' + IntToStr(FPricePrecision) + 'λС��';
  end
  else
  begin
    fdPrice.Hint := fdPrice.Hint + ',����';
    fdPrice2.Hint := fdPrice2.Hint + ',����';
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
    Command.ParamData('��ѯӪҵ��').SetString(BranchCode);
    Command.ParamData('�ͻ���').SetString(CustomerNo);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
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
    Command.ParamData('��ѯӪҵ��').SetString(BranchCode);
    Command.ParamData('�����˺�').SetString(BrokerNo);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
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
    Context.GetDialogSystem.ShowError(Format('��%s�г������ڴ���Ϊ%s��֤ȯ',
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
    Command.ParamData('�г�����').SetString(Market);
    Command.ParamData('֤ȯ����').SetString(SecCode);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
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
    Command.ParamData('��ѯӪҵ��').SetString(BranchCode);
    Command.ParamData('�����˺�').SetString(BrokerNo);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
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
    Command.ParamData('��ѯӪҵ��').SetString(BranchCode);
    Command.ParamData('�ͻ���').SetString(CustomerNo);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
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
    Command.ParamData('��ѯ.Ӫҵ��').SetString(BranchCode);
    Command.ParamData('��ѯ.���Ҵ���').SetString(CurrencyType);
    Command.ParamData('��ѯ.���д���').SetString(BankCode);
    Command.ParamData('������Ӫҵ��').SetInteger(1);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
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
      // ����
      TWVLabel(Ctrl).Caption := Format(SOutOfDate, [ExpireDate]);
      TWVLabel(Ctrl).Font.Color := clRed;
    end
    else
    begin
      // ����
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
    // ��ʽ������ȷ
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
  // else //��ʽ����ȷ����������Ƿ��ַ�
end;

procedure TComCmdDefinition.fdStockNoExCheckValid(WorkField: TWVField);
var
  WorkView: TWorkView;
  MarketField, SecurityNameField, SecurityObjField: TWVField;
  // ���弸���ֶζ��󷽱�ʹ��
  SecInfo: TKSAbstractSecInfo;
  Required: Boolean;
  AllowTypes: string;
  Market, SecCode: string;
begin
  // ע�⣬���ֶε�MonitorValueChangedFields='|�г�|'��
  // ���г������ı��ʱ���Զ�����֤ȯ�����ֶε�CheckValid�¼���
  // ���Բ���Ҫ�ټ�һ��ר�ŵ�Monitor

  WorkView := WorkField.WorkView;

  // �Ȼ����ص��ֶΣ�
  // һ��������Ż�������ٶԸ������Ʋ��Ҷ���Ĳ�����FieldByName()
  // ��һ������ǿ�ɶ��Ժ�ά���ԣ������ֶ����Ʒ����ı䣬ֻ��Ҫ��һ�����еĵط�����

  // �ȸ���MonitorValueChangedFields��ȡ�г��ֶκ��г�����
  MarketField := GetMonitorField(WorkField);
  if MarketField <> nil then
    Market := MarketField.Data.AsString
  else
    Market := '';
  // �����г������ʽ�������룩�ֶ�
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
    // һ����ʽ��Ч��֤ȯ����
    SecInfo := ComCmdDefinition.FindStock(WorkField.Data.AsString, Market);
    if SecInfo <> nil then
    begin
      // �и�֤ȯ
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
        WorkField.Hint := ' '; // ���ε���ʾ��ȷ��ʽ��˵��
      end;
    end
    else
    begin
      // �޸�֤ȯ
      if SecurityNameField <> nil then
        SecurityNameField.Data.Clear;
      if SecurityObjField <> nil then
        SecurityObjField.Data.Clear;
      WorkField.Valid := False;
      WorkField.ErrorMessage := SNotExist;
      WorkField.Hint := ' '; // ���ε���ʾ��ȷ��ʽ��˵��
    end;
  end
  else
  begin
    // һ����ʽ��Ч��֤ȯ����
    if SecurityNameField <> nil then
      SecurityNameField.Data.Clear;
    if SecurityObjField <> nil then
      SecurityObjField.Data.Clear;
    Required := WorkField.Features.Values[RequiredSecParam] = '1';
    {
    if (WorkField.Data.AsString='') and not Required then
    begin
      // Ϊ��ͬʱ������
      WorkField.Valid := True;
    end else
    begin
      WorkField.Valid := False;
      //WorkField.ErrorMessage := SFormatError; // ǧ��Ҫ����ErrorMessage����Ϊ�²��дһЩ��Ϣ����������Ƿ��ַ�
      WorkField.Hint := ''; // ��ʾ����ȷ��ʽ��˵��
    end;
    }
    if WorkField.Data.AsString = '' then
    begin
      WorkField.Valid := not Required;
      WorkField.ErrorMessage := SNotEmpty;
      WorkField.Hint := ' '; // ���ε���ʾ��ȷ��ʽ��˵��
    end
    else
    begin
      WorkField.Valid := False;
      //WorkField.ErrorMessage := SFormatError; // ǧ��Ҫ����ErrorMessage����Ϊ�²��дһЩ��Ϣ����������Ƿ��ַ�
      WorkField.Hint := ''; // ��ʾ����ȷ��ʽ��˵��
    end;
  end;
end;

procedure TComCmdDefinition.fdBroketNoExCheckValid(WorkField: TWVField);
var
  WorkView: TWorkView;
  BranchNoField, BroketNameField, BroketObjField: TWVField;
  // ���弸���ֶζ��󷽱�ʹ��
  BroketInfo: TKSAbstractBrokerInfo;
  Required: Boolean;
  BranchCode, BroketNo: string;
begin
  // ע�⣬���ֶε�MonitorValueChangedFields='|Ӫҵ��|'��
  // ��Ӫҵ�������ı��ʱ���Զ����������˺��ֶε�CheckValid�¼���
  // ���Բ���Ҫ�ټ�һ��ר�ŵ�Monitor
  inherited;
  WorkView := WorkField.WorkView;

  // �Ȼ����ص��ֶΣ�
  // һ��������Ż�������ٶԸ������Ʋ��Ҷ���Ĳ�����FieldByName()
  // ��һ������ǿ�ɶ��Ժ�ά���ԣ������ֶ����Ʒ����ı䣬ֻ��Ҫ��һ�����еĵط�����

  // �ȸ���MonitorValueChangedFields��ȡӪҵ���ֶκ�Ӫҵ������
  BranchNoField := GetMonitorField(WorkField);
  if BranchNoField <> nil then
    BranchCode := BranchNoField.Data.AsString
  else
    BranchCode := '';
  // ����Ӫҵ����ʽ�������룩�ֶ�
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
    // һ����ʽ��Ч�ľ����˺�
    BroketInfo := ComCmdDefinition.GetBroker(BranchCode,
      WorkField.Data.AsString);
    if BroketInfo <> nil then
    begin
      // �иþ����˺�
      if BroketNameField <> nil then
        BroketNameField.Data.SetString(BroketInfo.BrokerName);
      if BroketObjField <> nil then
        BroketObjField.Data.SetObject(BroketInfo);
    end
    else
    begin
      // �޸�֤ȯ
      if BroketNameField <> nil then
        BroketNameField.Data.Clear;
      if BroketObjField <> nil then
        BroketObjField.Data.Clear;
      WorkField.Valid := False;
      WorkField.ErrorMessage := SNotExist;
      WorkField.Hint := ' '; // ���ε���ʾ��ȷ��ʽ��˵��
    end;
  end
  else
  begin
    // һ����ʽ��Ч�ľ����˺�
    if BroketNameField <> nil then
      BroketNameField.Data.Clear;
    if BroketObjField <> nil then
      BroketObjField.Data.Clear;
    Required := WorkField.Features.Values[RequiredSecParam] = '1';
    {
    if (WorkField.Data.AsString='') and not Required then
    begin
      // Ϊ��ͬʱ������
      WorkField.Valid := True;
    end else
    begin
      WorkField.Valid := False;
      //WorkField.ErrorMessage := SFormatError; // ǧ��Ҫ����ErrorMessage����Ϊ�²��дһЩ��Ϣ����������Ƿ��ַ�
      WorkField.Hint := ''; // ��ʾ����ȷ��ʽ��˵��
    end;
    }
    if WorkField.Data.AsString = '' then
    begin
      WorkField.Valid := not Required;
      WorkField.ErrorMessage := SNotEmpty;
      WorkField.Hint := ' '; // ���ε���ʾ��ȷ��ʽ��˵��
    end
    else
    begin
      WorkField.Valid := False;
      //WorkField.ErrorMessage := SFormatError; // ǧ��Ҫ����ErrorMessage����Ϊ�²��дһЩ��Ϣ����������Ƿ��ַ�
      WorkField.Hint := ''; // ��ʾ����ȷ��ʽ��˵��
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
  if QueryMethod = '1' then //��Ӫҵ����ѯ
  begin
    CustField.Constrained := False;
    DeptField.Reset;
    CustNo.Enabled := False;
    CustNo.Required := False;
    //    BranchCode.Enabled := IsCenterDepartment;
    BranchCode.Enabled := True;
  end
  else //���ͻ��Ų�ѯ
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
        WorkField.SetInvalidMessage(Format('Ӧ�����ٱ�%s��%f',
          [CheckedField.Caption, RetouchNum]));
      if RetouchNum < 0 then
        WorkField.SetInvalidMessage(Format('Ӧ�������%s��%f',
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
        WorkField.SetInvalidMessage(Format('Ӧ�������%s��%f',
          [CheckedField.Caption, RetouchNum]));
      if RetouchNum < 0 then
        WorkField.SetInvalidMessage(Format('Ӧ�����ٱ�%s��%f',
          [CheckedField.Caption, Abs(RetouchNum)]));
    end
    else
      WorkField.Valid := True;
  end;
end;

{
 Function:��ȡӪҵ��ĳ������ֵ
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
    Command.ParamData('��������').SetString(ParamCode);
    if BranchCode='' then
      Command.ParamData('��ѯӪҵ������').SetString(Context.ParamData(svDepartNoName).AsString)
    else
      Command.ParamData('��ѯӪҵ������').SetString(BranchCode);
    Command.ParamData('�Ƿ���Ҫ�������').SetInteger(1);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command);
    //Result := Command.ParamData('����ֵ').AsString;
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
    if DataSet=nil then exit;

    //��������ֻ��һ����¼����ֱ�Ӹ�ֵ
    if DataSet.RecordCount=1  then
      Result:=DataSet.FieldByName('scert_no').Asstring
    else
    //����������ֹһ����¼����ȡ��Ӫҵ���Ĳ���ֵ
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
    Command.ParamData('����Ӫҵ��').SetString(CurrentDepartmentNo);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command,False);
    Result := Command.ParamData('��������').AsString;
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
    Command.ParamData('Ӫҵ��').SetString(Branch);
    Command.ParamData('��λ����').SetString(Station);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
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
    Command.ParamData('Ӫҵ��').SetString(BranchCode);
    Command.ParamData('��λ����').SetString(Station);
    Command.ParamData('������Ӫҵ��').SetInteger(1);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
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
  Command := Context.CommandFactory.NewCommand('��ѯ��������Э�������Ϣ', 1);
  try
    Command.ParamData('����ѯӪҵ��').SetString(BranchCode);
    Command.ParamData('Э��״̬').SetString(TreatyStatus);
    Command.ParamData('�Ƿ����¼�����').SetString(IsDownToChild);
    Command.ParamData('��ѯ��ʽ').SetInteger(QueryMode);
    Command.ParamData('Э�����').SetInteger(GroupNo);
    Command.ParamData('��ѯ�Ƿ��������').SetInteger(IsContainChild);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
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
      WorkField.ErrorMessage := '������';
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
    Command.ParamData('�г�����').SetString(Market);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
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
    Command.ParamData('��ѯ.Ӫҵ��').SetString('');
    Command.ParamData('������Ӫҵ��').SetInteger(1);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
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
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
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
    Command.ParamData('����Ӫҵ��').SetString(Branch);
    Command.ParamData('�շѷ�ʽ').SetString(FeeType);
    Command.ParamData('��ѯ��ʽ').SetInteger(QueryType);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Dataset := TDataset(Command.ParamData('��ѯ�����').AsObject);
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
    Command.ParamData('�г�').SetString(Market);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    LastDay := Command.ParamData('��һ��������').AsString;
    CurrentDay := Command.ParamData('��ǰ��������').AsString;
    NextDay := Command.ParamData('��һ��������').AsString;
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
    Command.ParamData('��������').SetInteger(DateType);
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    Result := Command.ParamData('����').AsString;
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
  if DateStr = '0' then //wlj 20040318 ������Ϊ��
  begin
    WorkField.Valid := False;
    exit;
  end;

  iPos := pos('.', DateStr);
  iLen := Length(DateStr);
  //���û��С����,������Ч��.
  //�����С����, С��λ������С�������С����
  if iPos > 0 then //��С����
  begin //����С����,����С��
    if iLen - iPos > FPricePrecision then
      WorkField.Valid := False
    else
      WorkField.Valid := True;
  end
  else
    WorkField.Valid := True;

  //wlj 20040311 ����������ֵ�򱨴�
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

