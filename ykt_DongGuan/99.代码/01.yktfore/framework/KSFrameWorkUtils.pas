unit KSFrameWorkUtils;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSFrameWorkUtils
   <What>�����ܵĸ�������
   ��Щ����������������Դ���ʡ�
   <Written By> Huang YanLai (������)
   <History>
**********************************************}

interface

uses Windows, SysUtils, Classes, Controls, KSFrameWorks, WVCommands,
KSDataDictionary,
  WorkViews, DB, Comctrls, ExtCtrls, CheckLst, DataTypes, WVCtrls, DBGrids,
    Contnrs,
  UBranchManWindow, KsBranchTree, dialogs, forms, ShellAPI, Messages;

const
  KS_WarningInfo = WM_User + $2000;

type
  ECommandError = class(Exception)
  private
    FReturnCode: Integer;
  public
    property ReturnCode: Integer read FReturnCode;
  end;
  {
    TWorkViewExceptionHandler = class
    public
      class procedure HandleException(Sender : TObject; E : Exception);
    end;
  }
  {
    <Procedure>RegisterModule
    <What>ע��Module��������������������
    ����������������
      TWVCommandTypeInfo : ע��������������
      TWVCustomProcessor : ע���������
      TKCDataset, TKCWVQuery : �������ݿ�
      TWVRequest : ���������Ķ���
    <Params>
      -
    <Exception>
  }
procedure RegisterModule(Module: TComponent);

{
  <Procedure>CheckCommandReturnValue
  <What>���������󷵻ص������Ƿ���Ч�������Ч���׳�����
  <Params>
    -
  <Exception>
}
procedure CheckCommandReturnValue(Command: TWVCommand; ShowWarning: Boolean =
  True);

{
  <Procedure>FreeDataSetForCtommand
  <What>�ͷ����������������Ľ����������Ҫ�ͷſ����ͷŵ����͡�
  <Params>
    -
  <Exception>
}
procedure FreeDataSetForCommand(Command: TWVCommand);

{
  <Procedure>IsCenterDepartment
  <What>��ǰӪҵ���Ƿ����ܲ�
  <Params>
    -
  <Exception>
}
function IsCenterDepartment: Boolean;

{
  <Procedure>CurrentDepartment
  <What>���ص�ǰӪҵ������ΪTIdObject����
  <Params>
    -
  <Exception>
}
function CurrentDepartment: TIdObject;

function CurrentDepartmentNo: string;

{
  <Procedure>CompanyName
  <What>���ع�˾����
  <Params>
    -
  <Exception>
}
function CompanyName: string;

{
  <Procedure>InitIdObjectItems
  <What>�������ֵ����ӵ��ַ����б����档�ַ����б��Objects������Ӧ�Ķ���
  <Params>
    IdObjectItems - �ַ����б�
    DataEntry - �����ֵ���Ŀ
    AddEmptyIdObject - �Ƿ�����һ���ն���
  <Exception>
}
procedure InitIdObjectItems(IdObjectItems: TStrings; const DataEntry:
  TDataEntry;
  AddEmptyIdObject: Boolean = False; Filtered: Boolean = True; const
    DepartmentNo: string = '');

{
  <Procedure>InitDepartmentItems
  <What>��Ӫҵ�����ӵ��ַ����б�����
  <Params>
    -
  <Exception>
}
procedure InitDepartmentItems(DepartmentList: TStrings; AddAllDepart: Boolean =
  False);

{
  <Procedure>InitOnlyDepartmentItems
  <What>��Ӫҵ�����ӵ��ַ����б�����,������ܲ�,ͬʱ֧���ֶε�Ĭ��ֵ
  <Params>
    -
  <Exception>
}
procedure InitOnlyDepartmentItems(DepartmentList: TStrings; WorkField: TWVField
  = nil; AddAllDepart: Boolean = False);

{
  <Procedure>InitTreeDepartmentItems
  <What>��Ӫҵ���������������Ӫҵ����ӣ������������
  <Params>  SpecialFlag���ͨ��ͨ�Һ�ͨ��ͨ����ѯ
    -
  <Exception>
}
procedure InitTreeDepartmentItems(DepartmentList: TStrings; WorkField: TWVField
  = nil; AddAllDepart: Boolean = False; SpecialFlag: Boolean = False);

{
  <Procedure>InitOnlyTreeDepartmentItems
  <What>��Ӫҵ���������������Ӫҵ�����,�������������
  <Params>
    -
  <Exception>
}
procedure InitOnlyTreeDepartmentItems(DepartmentList: TStrings; WorkField:
  TWVField = nil; AddAllDepart: Boolean = False);

{
  <Procedure>IslinealChildBranch
  <What>�ж��Ƿ���ָ��Ӫҵ����ֱ���¼�Ӫҵ��
  <Params>  CurrentBranchs��ָ��Ӫҵ����ChildBranch����Ҫ�жϵ�Ӫҵ��
    -
  <Exception>
}
function IslinealChildBranch(CurrentBranch, ChildrenBranch: string): Boolean;

{
  <Procedure>InitDepartCustomerTypes
  <What>��Ӫҵ���ͻ������䵽�ַ����б�����
  <Params>
    -
  <Exception>
}
procedure InitDepartCustomerTypes(const DepartmentNo: string; CustomerTypes:
  TStrings; AddAll: Boolean = False);

{
  <Procedure>InitCustomerGroups
  <What>��Ӫҵ���ͻ������䵽�ַ����б�����
  <Params>
    -
  <Exception>
}
procedure InitCustomerGroups(const DepartmentNo: string; CustomerGroups:
  TStrings; AddAll: Boolean = False);

{
  <Procedure>AddOnlyEmptyItem
  <What>���������л��߿���Ŀ��IDObject���뵽�ַ����б����棬ʹ���б��������һ����Ŀ��
  <Params>
    -
  <Exception>
}
procedure AddOnlyEmptyItem(IdObjectItems: TStrings);

{
  <Procedure>ResetOtherInputBox
  <What>�����������ؼ���λ����գ���Ŀǰ��Ҫ����ͻ�������ؼ�
  <Params>
    -
  <Exception>
}
procedure ResetOtherInputBox(Owner: TComponent);

{
  <Procedure>InitBusinessFlagItems
  <What>����ҵ������ʼ���ַ����б�
  <Params>
    -
  <Exception>
}
procedure InitBusinessFlagItems(BusinessFlagItems: TStrings; const AFrom, ATo:
  string); overload;

procedure InitBusinessFlagItems(BusinessFlagItems: TStrings; const ACategories:
  string = ''); overload;

{
  <Funtion>FindAssociatedWorkView
  <What>������ָ���ؼ���صĹ�����ͼ
  <Params>
    Control - �ؼ�
  <Return>
    ��صĹ�����ͼ
  <Exception>
}
function FindAssociatedWorkView(Control: TControl): TWorkView;

{
  <Function>GetFileName
  <What>����Ŀ¼���ͺ��ļ�������ļ���ȫ·��
  <Params>
    -
  <Return>
  �ļ���ȫ·��
  <Exception>
}
function GetFileName(DirKey: Integer; const BasedFileName: string): string;

{
  <Function>GetReportFileName
  <What>��ñ����ļ�ȫ·����
  <Params>
    BasedFileName - �����ļ���(������·��)
  <Return>
  �����ļ�ȫ·����
  <Exception>
}
function GetReportFileName(const BasedFileName: string): string;

{
  <Procedure>AddSystemParams
  <What>��ϵͳ������Ӫҵ�����롢���ƣ�ְ�����롢���ƣ����ӵ��ַ����б�����
  <Params>
    -
  <Exception>
}
procedure AddSystemParams(Params: TStrings);

{
  <Function>GetToday
  <What>��õ�ǰ��������(yyyymmdd)��
  <Params>
    -
  <Return>
  <Exception>
}
function GetToday: string;

{
  <Function>GetTodayStr
  <What>��õ�ǰ�������ڵ��ַ�������ʽ��FullDateFormatȷ��
  <Params>
    -
  <Return>
  <Exception>
}
function GetTodayStr: string;

{
  <Function>GetSystemDate
  <What>��õ�ǰϵͳ����(yyyymmdd)��
  <Params>
    -
  <Return>
  <Exception>
}
function GetSystemDate: string;

{
  <Function>GetSystemDateStr
  <What>��õ�ǰϵͳ���ڵ��ַ�������ʽ��FullDateFormatȷ��
  <Params>
    -
  <Return>
  <Exception>
}
function GetSystemDateStr: string;

{
  <Function>DBStrDateToDateTime
  <What>�����ݿ���ַ������ڸ�ʽ(yyyymmdd)ת��Ϊ��������
  <Params>
    DateStr - ���ݿ���ַ������ڸ�ʽ
  <Return>
    ��������
  <Exception>
    �����ʽ����ȷ��������
}
function DBStrDateToDateTime(const DateStr: string): TDateTime;

{
  <Function>FormatDBStrDate
  <What>�����ݿ���ַ������ڸ�ʽ(yyyymmdd)��ʽ��Ϊָ�����ַ�����ʽ��
  <Params>
    DateFormat-�����ַ�����ʽ���μ�FormatDateTime
    DateStr - ���ݿ���ַ������ڸ�ʽ
  <Return>
    ��ʽ���Ժ�������ַ���
  <Exception>
    ������ڲ��Ϸ������ؿմ���
}
function FormatDBStrDate(const DateFormat, DateStr: string): string;

{
  <Procedure>TryRefreshDates
  <What>���Ը����������ݡ�
  ���Silence=True���������⡣
  ������ִ���Ի���ѯ���Ƿ������������������׳�EAbort��
  <Params>
    -
  <Exception>
}

//wsn 20050107 �������
procedure TryRefreshDates(var FSysDate: string; Silence: Boolean = True);

{
  <Procedure>����ϵͳ���ã��޸Ŀؼ�����ۣ����塢��ɫ�ȵȣ�
  <What>
  <Params>
    -
  <Exception>
}
procedure UpdateControlStyle(Control: TControl);

{
  <Procedure>HookControl
  <What>���ÿؼ����¼�������
  <Params>
    -
  <Exception>
}
procedure HookControl(Control: TControl);

{
  <Procedure>MakeChildrenReadOnly
  <What>���ӿؼ�����Ϊֻ��
  <Params>
    -
  <Exception>
}
procedure MakeChildrenReadOnly(AParent: TWinControl; AReadOnly: Boolean);

procedure MakeControlReadOnly(Control: TControl; AReadOnly: Boolean);

type
  TDoSomeThing = procedure of object;
  TDoSomeThingForDataset = procedure(Dataset: TDataset) of object;

  {
    <Procedure>DoLongOperation
    <What>����һ����ʱ��Ĳ�����������ʾһ���ȴ�����ĶԻ��򡣴�������Ժ�رոöԻ���
    <Params>
      WaitMsg - ��ʾ���ȴ��Ի����˵������
      DoSomeThing - ����Ĵ�����
    <Exception>
  }
procedure DoLongOperation(const WaitMsg: string; DoSomeThing: TDoSomeThing);

{
  <Procedure>DoLongDatasetOperation
  <What>����һ����ʱ��ı������ݼ��Ĳ�����������ʾһ���ȴ�����ĶԻ��򡣴�������Ժ�رոöԻ���
  <Params>
    WaitMsg - ��ʾ���ȴ��Ի����˵������
    Dataset - ���ݼ�
    DoSomeThing - ����Ĵ��������ù��̽�Ϊ����������ÿһ�е���DoSomeThing
  <Exception>
}
procedure DoLongDatasetOperation(const WaitMsg: string; Dataset: TDataset;
  DoSomeThing: TDoSomeThingForDataset);

{
  <Procedure>ReinputCheck
  <What>��WorkField��������У�飬ע��WorkField.MonitorValueChangedFields���������һ��������ֶε�����
  <Params>
    -
  <Exception>
}
procedure ReinputCheck(WorkField: TWVField);

{
  <Procedure>NotReinputCheck
  <What>��WorkField���в�һ��У�飬ע��WorkField.MonitorValueChangedFields���������һ��������ֶε�����
  <Params>
    -
  <Exception>
}
procedure NotEqualCheck(WorkField: TWVField);

{
  <Procedure>AddRecToListview
  <What> ����ŵ�ǰ�����¼��listview
  <Params>
    ListView��-����ż�¼��listview�ؼ���
    Rec       -  ��¼����
  <Exception>
}
procedure AddRecToListview(listview: Tlistview; const Rec: Tstrings; const
  MaxRecCount: integer = 3);

{
  <Procedure>GetReceipt
  <What>   ��ȡǰ׺.���ȡ'01-�����'��ǰ׺Ϊ'01'��
  <Params>
    -
  <Exception>
}
function GetPrefix(const Ftext: string; const SeperateChar: char = '-'): string;

{
  <Procedure>DelPrefix
  <What>   ��ȥǰ׺���罫'01-�����'��ȥǰ׺��Ϊ'�����'��
  <Params>
    -
  <Exception>
}
function DelPrefix(const Ftext: string; const SeperateChar: char = '-'): string;

{
    <Procedure>  SelectAll
    <What>       ����TCheckListBox�����ȫ��ѡ�л�ȫ����ѡ�У�����ö�����
                 TWVCheckListBox����,����InputDataChanged������ͬ��
    <Params>
    <Exception>
}
procedure SelectAll(CheckListBox: TCheckListBox; SelectAll: Boolean);

{
    <Procedure>  MakeSelectAllToNoSelected
    <What>       ��ȫѡת��Ϊȫ��ѡ�������Ż�����
    <Params>
    <Exception>
}

procedure MakeSelectAllToNoSelected(FieldData, ParamData: TKSDataObject;
  CheckListBox: TWVCheckListBox);

{
    <Procedure>  ShowBranchMan
    <What>       ��ʾ��֧�����������ο�
    <Params>
    <Exception>
}

procedure ShowBranchMan(Sender: TComponent; WorkView: TWorkView; SingleSelect:
  Boolean; BranchName: string; ACaption: string = ''; IncludeStr: string =
  '������Ӫҵ��');

{
    <function>   UnZipString
    <What>       ����ַ���0-11,1-01,2-10
    <Params>
    <Exception>
}
function UnZipString(const SourceStr: string): string;

{
    <function>   ZipString
    <What>       ����ַ���11-0,01-1,10-2
    <Params>
    <Exception>
}
function ZipString(const SourceStr: string): string;

{
    <function>   RefreshInfoAdmin
    <What>       ˢ��Ӫҵ����֧�������
    <Params>
    <Exception>
}
procedure RefreshInfoAdmin;

{
    <function>   FormatBarCode
    <What>       �Դſ��Ž��и�ʽ���������λ��;����ĩβ�ǣ���Ҫȥ��(��������)
    <Params>
    <Exception>
}
function FormatBarCode(Source: string): string;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation
   <Unit>
   <What> �Դ����ObjectList������Ϊ������Ķ�����TStringList����
          ÿ��TStringList�����String[0]����Ϊ�Ǹö����Name��
          ���մ����Name���������ظ�ObjectList����ģ������϶����Name��
              StringList����
   <Written By> Zhu pengfei (�����)
   <History>
**********************************************}
function FindStringListFormObjectList(ObjectList: TObjectList; Name: string):
  TStringList;

{
    <function> DoReturnCode(IN REPORT)
    <What> �Է�����ͷ�����Ϣ���д���
    <Params> ReturnCode ReMess
    <Exception>
}

function DoReturnCode(ReturnCode: Integer; ReMess: string): Boolean;

function CreateOneStringList(ObjectList: TObjectList; StringListName: string):
  TStringList;

procedure UpdateBranchDirectory;

procedure GetlinealChildBranch(Items: TStrings; Objects: TObjectList);

procedure ShowDetailForGrid(Grid: TDBGrid);

function InputText(const ACaption, APrompt: string; HideText, CustomerPassword:
  Boolean; var Value: string; MaxLength: Integer = 0): Boolean;

function InputCustomerPasswordForField(Field: TWVField; MaxLength: Integer = 0):
  Boolean;

function InputQueryCH(const ACaption, APrompt: string; var Value: string):
  Boolean;
{
  ��ʾ�ַ�������򣬰�ťΪ���ģ���Ӧ��borland��InputQuery
}

{
  ���Command�Ĳ����Լ����ò����ĵ�ǰֵ��
  ��Ҫ���ڵ���
}
procedure CheckCommandParamOneByOne(Command : TWVCommand);

implementation

uses
  KCDataAccess, KCWVProcBinds, WVCmdTypeInfo, WVCmdProc, WVCmdReq,
    KSClientConsts,
  LogFile, KsEdits, KSStrUtils, UIStyles, stdctrls, UAuth, {UMenu,} Graphics,
  ViewDataDetail, KSFrames, KSKeyboard, KSComCmdDefs, KSCustomers, SafeCode;

type
  TGlobalEventHandler = class
  public
    class procedure DBGridDoubleClick(Sender: TObject);
    class procedure DBGridKeyDown(Sender: TObject; var Key: Word; Shift:
      TShiftState);
    class procedure CheckListBoxClick(Sender: TObject);
    class procedure CheckListBoxKeyPress(Sender: TObject; var Key: Char);
  end;

  { TGlobalEventHandler }

class procedure TGlobalEventHandler.CheckListBoxClick(Sender: TObject);
begin
  if (Sender is TCheckListBox) and TKSKeyboard.IsDown(VK_CONTROL) then
  begin
    if TCheckListBox(Sender).ItemIndex >= 0 then
      SelectAll(TCheckListBox(Sender),
        TCheckListBox(Sender).Checked[TCheckListBox(Sender).ItemIndex]);
  end;
end;

class procedure TGlobalEventHandler.CheckListBoxKeyPress(Sender: TObject;
  var Key: Char);
begin
  if (Sender is TCheckListBox) then
  begin
    if (Key = '+') or (Key = '=') then
    begin
      SelectAll(TCheckListBox(Sender), True);
      Key := #0;
    end
    else if (Key = '-') or (Key = '_') then
    begin
      SelectAll(TCheckListBox(Sender), False);
      Key := #0;
    end
  end;
end;

class procedure TGlobalEventHandler.DBGridDoubleClick(Sender: TObject);
begin
  if (Sender is TDBGrid) then
  begin
    ShowDetailForGrid(TDBGrid(Sender));
  end;
end;

class procedure TGlobalEventHandler.DBGridKeyDown(Sender: TObject;
  var Key: Word; Shift: TShiftState);
begin
  if (Sender is TDBGrid) and (Key = VK_RETURN) and ([ssCtrl] = Shift) then
  begin
    Key := 0;
    ShowDetailForGrid(TDBGrid(Sender));
  end;
end;

procedure ShowDetailForGrid(Grid: TDBGrid);
var
  Title: string;
begin
  if Grid.Owner is TKSFrame then
    Title := TKSFrame(Grid.Owner).Caption
  else
    Title := '';
  ShowDataDetail(Grid, Title);
end;

procedure RegisterModule(Module: TComponent);
var
  Database: TKCDatabase;
  I: Integer;
  Comp: TComponent;
  RobotSystem: IRobotSystem;
begin
  Assert(Context <> nil);
  Database := TKCDatabase(Context.GetSystemObject(SODatabase));
  RobotSystem := Context.GetRobotSystem;
  Assert(Database is TKCDatabase);
  try
    // ע��������������
    RegisterCommandDescriptors(Module, Context);
    // ע���������
    RegisterCommandProcessors(Module, Context);
    for I := 0 to Module.ComponentCount - 1 do
    begin
      Comp := Module.Components[I];
      if Comp is TKCDataset then
      begin
        // �������ݿ�
        if TKCDataset(Comp).Database = nil then
          TKCDataset(Comp).Database := Database;
      end
      else if Comp is TKCWVQuery then
      begin
        // �������ݿ�
        if TKCWVQuery(Comp).KCDatabase = nil then
          TKCWVQuery(Comp).KCDatabase := Database;
      end
      else if Comp is TWVRequest then
        // ���������Ķ���
        TWVRequest(Comp).Context := Context
          {
        else if Comp is TWorkView then
          // ���ù�����ͼ�����⴦��
          TWorkView(Comp).OnException := TWorkViewExceptionHandler.HandleException
        }
      else if Comp is TKSAccountEdit then
        // ����Ӫҵ��
        TKSAccountEdit(Comp).Department :=
          Context.ParamData(svDepartNoName).AsString;
      //else if Comp is TDBGrid then
      if Comp is TControl then
      begin
        // ����DBGrid�����
        UpdateControlStyle(TControl(Comp));
        HookControl(TControl(Comp));
      end;
      if RobotSystem <> nil then
      begin
        RobotSystem.MonitorComponent(Comp);
      end;
    end;
  except
    WriteException;
  end;
end;

procedure FreeDataSetForCommand(Command: TWVCommand);
var
  I: Integer;
  Descriptor: TWVCommandDescriptor;
  DataObj: TKSDataObject;
  Obj: TObject;
begin
  Descriptor := Command.GetDescriptor;
  for I := 0 to Descriptor.GetParamCount - 1 do
  begin
    DataObj := Command.ParamData(I);
    if DataObj.DataType = kdtObject then
    begin
      Obj := DataObj.AsObject;
      if (Obj is TKCDataset) and (TKCDataset(Obj).Owner = nil) and not
        (DataObj.OwnObject) then
      begin
        DataObj.SetObject(nil);
        Obj.Free;
      end;
    end;
  end;
end;

procedure CheckCommandReturnValue(Command: TWVCommand; ShowWarning: Boolean =
  True);
var
  Error: ECommandError;
  ReturnCode: Integer;
  DataObj: TKSDataObject;
  ErrorMsg: string;
  TmpStr: string;
begin
  if Command.Error <> nil then
  begin
    FreeDataSetForCommand(Command);
  end;
  Command.CheckError;
  DataObj := Command.FindParamData(cpReturnCodeParamName);
  if DataObj <> nil then
  begin
    ReturnCode := DataObj.AsInteger;
    if ReturnCode <> 0 then
    begin
      FreeDataSetForCommand(Command);
      DataObj := Command.FindParamData(cpReturnMessageParamName);
      if DataObj <> nil then
        ErrorMsg := DataObj.AsString
      else
        ErrorMsg := ''; //wsn ����һ��ͨ������Ϣ�����޸�
      if {(ReturnCode<=0) and}(ReturnCode <= WarningReturnCode) then
      begin
         {if ShowWarning and (ReturnCode<>1) then
           Context.GetDialogSystem.ShowWarning(Format('���� : %d, %s',[ReturnCode,ErrorMsg]));

          //TmpStr:=Format('���� : %d, %s',[ReturnCode,ErrorMsg]);
          //Message.Msg:=TmpStr;
          //PostMessageW( Application.MainForm.Handle,KS_WarningInfo,1,0);
          //Exit;}
      end
      else if (ReturnCode = InforReturnCode) then
        //wlj 20040105 ������ʾ��Ϣ�Ĵ���,����ͨmsgbox��ʾ.
      begin
        Context.GetDialogSystem.ShowMessage(ErrorMsg);
      end
      else
      begin
        ErrorMsg := Format('���� : %d, %s', [ReturnCode, ErrorMsg]);
        Error := ECommandError.Create(ErrorMsg);
        Error.FReturnCode := ReturnCode;
        raise Error;
        Context.GetDialogSystem.ShowWarning(Format('���� : %s',[ErrorMsg]));
      end;
    end;
  end;
end;

function IsCenterDepartment: Boolean;
begin
  Assert(Context <> nil);
  Result := Context.ParamData(svDepartNoName).AsString = CenterDepartNo;
  //wsn ǿ������Ϊ�ܲ��˵�
  Result := True;
end;

procedure InitIdObjectItems(IdObjectItems: TStrings; const DataEntry:
  TDataEntry;
  AddEmptyIdObject: Boolean = False; Filtered: Boolean = True; const
    DepartmentNo: string = '');
var
  IdObjects: TIdObjectList;
  I: Integer;
  // ProhibitStr : string;
begin
  IdObjectItems.Clear;
  IdObjects := NeedIdObjectList(DataEntry, DepartmentNo);

  if AddEmptyIdObject then
    IdObjectItems.AddObject(Format(IdObjectTextFormat, [EmptyIdObject.ID,
      EmptyIdObject.Name]), EmptyIdObject);

  // ����Ҫ����Ȩ�޹����г��ͱ��ֵİ汾
  if (DataEntry <> deCurrency) or not Filtered then
  begin
    for I := 0 to IdObjects.Count - 1 do
      IdObjectItems.AddObject(Format(IdObjectTextFormat, [IdObjects[I].ID,
        IdObjects[I].Name]), IdObjects[I]);
  end
  else
  begin
    // ������ң���01-�����ת��Ϊ1-�����
    for I := 0 to IdObjects.Count - 1 do
      IdObjectItems.AddObject(Format(IdObjectTextFormat, [Copy(IdObjects[I].ID,
        2, Length(IdObjects[I].ID)), IdObjects[I].Name]), IdObjects[I]);
  end;
  {
  // ��Ҫ����Ȩ�޹����г��ͱ��ֵİ汾
  if ((DataEntry<>deCurrency) and (DataEntry<>deMarket)) or not Filtered then
  begin
    // ��ͨ�������ֵ���߲�����
    for I:=0 to IdObjects.Count-1 do
      IdObjectItems.AddObject(Format(IdObjectTextFormat,[IdObjects[I].ID,IdObjects[I].Name]),IdObjects[I]);
  end
  else if DataEntry=deCurrency then
  begin
    // ������ң���01-�����ת��Ϊ1-����ң�ͬʱ����Ȩ�޹���
    ProhibitStr := Context.GetParamValue(svProhibitMoneyName);
    for I:=0 to IdObjects.Count-1 do
      if (ProhibitStr='') or (Pos(IdObjects[I].ID,ProhibitStr)<=0) then
        IdObjectItems.AddObject(Format(IdObjectTextFormat,[Copy(IdObjects[I].ID,2,Length(IdObjects[I].ID)),IdObjects[I].Name]),IdObjects[I]);
  end
  else if DataEntry=deMarket then
  begin
    // �����г�����Ȩ�޹���
    ProhibitStr := Context.GetParamValue(svProhibitMarketsName);
    for I:=0 to IdObjects.Count-1 do
      if (ProhibitStr='') or (Pos(IdObjects[I].ID,ProhibitStr)<=0) then
        IdObjectItems.AddObject(Format(IdObjectTextFormat,[IdObjects[I].ID,IdObjects[I].Name]),IdObjects[I]);
  end;
  }
end;

procedure InitDepartmentItems(DepartmentList: TStrings; AddAllDepart: Boolean =
  False);
var
  Depart: TIdObject;
  IsCenter: Boolean;
begin
  DepartmentList.Clear;
  IsCenter := IsCenterDepartment;
  NeedIdObjectList(deDepart);
  if IsCenter then
  begin
    InitIdObjectItems(DepartmentList, deDepart);
    if AddAllDepart and IsCenter then
      DepartmentList.InsertObject(0, SAllDepartments, AllDepartemntIdObject);
  end
  else
  begin
    Depart := CurrentDepartment;
    DepartmentList.AddObject(Format(IdObjectTextFormat, [Depart.ID,
      Depart.Name]), Depart);
  end;
end;

procedure InitOnlyDepartmentItems(DepartmentList: TStrings; WorkField: TWVField
  = nil; AddAllDepart: Boolean = False);
var
  I: Integer;
begin
  DepartmentList.Clear;
  NeedIdObjectList(deDepart);
  InitIdObjectItems(DepartmentList, deDepart);
  if AddAllDepart then
    DepartmentList.InsertObject(0, Format(IdObjectTextFormat, [EmptyIdObject.ID,
      EmptyIdObject.Name]), EmptyIdObject);
  for I := 0 to DepartmentList.Count - 1 do
    if TIdObject(DepartmentList.Objects[I]).ID = CenterDepartNo then
    begin
      DepartmentList.Delete(I);
      Break;
    end;
  if (WorkField = nil) or not (DepartmentList.Count > 0) then
    Exit;
  if IsCenterDepartment then
    WorkField.DefaultValue := GetPrefix(DepartmentList.Strings[0])
  else
    WorkField.DefaultValue := CurrentDepartmentNo;
end;

procedure InitTreeDepartmentItems(DepartmentList: TStrings; WorkField: TWVField
  = nil; AddAllDepart: Boolean = False; SpecialFlag: Boolean = False);
var
  BranchObjects: TObjectList;
begin
  DepartmentList.Clear;
  BranchObjects := ComCmdDefinition.NeedBranchs;
  GetObjectsItems(DepartmentList, BranchObjects);
  if (AddAllDepart and IsCenterDepartment) or (AddAllDepart and SpecialFlag)
    then
    DepartmentList.InsertObject(0, Format(IdObjectTextFormat, [EmptyIdObject.ID,
      EmptyIdObject.Name]), EmptyIdObject);
  if (WorkField = nil) or not (DepartmentList.Count > 0) then
    Exit;
  if (AddAllDepart and IsCenterDepartment) or (AddAllDepart and SpecialFlag)
    then
    WorkField.DefaultValue := ''
  else
    WorkField.DefaultValue := GetPrefix(DepartmentList.Strings[0]);
end;

procedure InitOnlyTreeDepartmentItems(DepartmentList: TStrings; WorkField:
  TWVField = nil; AddAllDepart: Boolean = False);
var
  BranchObjects: TObjectList;
begin
  DepartmentList.Clear;
  BranchObjects := ComCmdDefinition.NeedBranchs;
  GetlinealChildBranch(DepartmentList, BranchObjects);
  if AddAllDepart and IsCenterDepartment then
    DepartmentList.InsertObject(0, Format(IdObjectTextFormat, [EmptyIdObject.ID,
      EmptyIdObject.Name]), EmptyIdObject);

  if (WorkField = nil) or not (DepartmentList.Count > 0) then
    Exit;
  if AddAllDepart and IsCenterDepartment then
    WorkField.DefaultValue := ''
  else
    WorkField.DefaultValue := GetPrefix(DepartmentList.Strings[0]);
end;

function IslinealChildBranch(CurrentBranch, ChildrenBranch: string): Boolean;
var
  ChildrenInfos: TList;
  ChildBranch: string;
  I: Integer;
begin
  Result := False;
  CheckObject(InfoAdmin, 'Error : InfoAdmin not init');
  ChildrenInfos := TList.Create;
  InfoAdmin.StructureList.Find(ChildrenInfos, CurrentBranch);
  for I := 0 to ChildrenInfos.Count - 1 do
  begin
    ChildBranch := ChildBranch + TKSTreeStructure(ChildrenInfos[I]).ChildId +
      ',';
  end;
  if Pos(ChildrenBranch, ChildBranch) <> 0 then
    Result := True;
end;

procedure InitDepartCustomerTypes(const DepartmentNo: string; CustomerTypes:
  TStrings; AddAll: Boolean = False);
begin
  InitIdObjectItems(CustomerTypes, deDepartCustomerType, AddAll, True,
    DepartmentNo);
end;

procedure InitCustomerGroups(const DepartmentNo: string; CustomerGroups:
  TStrings; AddAll: Boolean = False);
begin
  InitIdObjectItems(CustomerGroups, deCustomerGroup, AddAll, True,
    DepartmentNo);
end;

procedure AddOnlyEmptyItem(IdObjectItems: TStrings);
begin
  IdObjectItems.Clear;
  IdObjectItems.AddObject(Format(IdObjectTextFormat, [EmptyIdObject.ID,
    EmptyIdObject.Name]), EmptyIdObject);
end;

function CurrentDepartmentNo: string;
begin
  Result := Context.ParamData(svDepartNoName).AsString;
end;

function CompanyName: string;
begin
  Result := Context.ParamData(svCompanyNameName).AsString;
end;

function CurrentDepartment: TIdObject;
var
  Departs: TIdObjectList;
begin
  Assert(Context <> nil);
  Departs := NeedIdObjectList(deDepart);
  Result := Departs.Find(CurrentDepartmentNo);
  // only for test
  { TODO : ȥ�������Ӷ��� }
  if Result = nil then
  begin
    Result := TIdObject.Create(Context.ParamData(svDepartNoName).AsString,
      Context.ParamData(svDepartNameName).AsString);
    Departs.Add(Result);
  end;
  Assert(Result <> nil);
end;

procedure ResetOtherInputBox(Owner: TComponent);
var
  I: Integer;
begin
  for I := 0 to Owner.ComponentCount - 1 do
  begin
    if Owner.Components[I] is TKSAccountEdit then
      TKSAccountEdit(Owner.Components[I]).Reset;
  end;
end;

procedure InitBusinessFlagItems(BusinessFlagItems: TStrings; const AFrom, ATo:
  string); overload;
var
  Flags: TIdObjectList;
  I: Integer;
  Flag: TBusinessFlag;
begin
  BusinessFlagItems.Clear;
  Flags := NeedIdObjectList(deBusinessFlag);
  for I := 0 to Flags.Count - 1 do
  begin
    Flag := TBusinessFlag(Flags[I]);
    if (AFrom <= Flag.ID) and (Flag.ID <= ATo) then
      BusinessFlagItems.AddObject(Format(IdObjectTextFormat, [Flag.ID,
        Flag.Name]), Flag);
  end;
end;

procedure InitBusinessFlagItems(BusinessFlagItems: TStrings; const ACategories:
  string = ''); overload;
var
  Flags: TIdObjectList;
  I: Integer;
  Flag: TBusinessFlag;
begin
  BusinessFlagItems.Clear;
  Flags := NeedIdObjectList(deBusinessFlag);
  for I := 0 to Flags.Count - 1 do
  begin
    Flag := TBusinessFlag(Flags[I]);
    if (ACategories = '') or (Pos(Flag.ChangeCategory, ACategories) > 0) then
      BusinessFlagItems.AddObject(Format(IdObjectTextFormat, [Flag.ID,
        Flag.Name]), Flag);
  end;
end;

function FindAssociatedWorkView(Control: TControl): TWorkView;
var
  Comp, TempComp: TComponent;

  function FindWorkView(AComp: TComponent): TWorkView;
  var
    I: Integer;
  begin
    Result := nil;
    for I := 0 to AComp.ComponentCount - 1 do
    begin
      if AComp.Components[I] is TWorkView then
      begin
        Result := TWorkView(AComp.Components[I]);
        Break;
      end;
    end;
  end;

begin
  Comp := Control;
  Result := nil;
  while (Result = nil) and (Comp <> nil) do
  begin
    Result := FindWorkView(Comp);
    if Result = nil then
    begin
      TempComp := Comp.Owner;
      if (TempComp = nil) and (Comp is TControl) then
        Comp := TControl(Comp).Parent
      else
        Comp := TempComp;
    end;
  end;
end;

function GetFileName(DirKey: Integer; const BasedFileName: string): string;
begin
  if (BasedFileName <> '') and (ExtractFileDrive(BasedFileName) = '') and
    (Context <> nil) then
    Result := AddPathAndName(Context.GetDir(DirKey), BasedFileName)
  else
    Result := BasedFileName;
end;

function GetReportFileName(const BasedFileName: string): string;
begin
  Result := GetFileName(dkReport, BasedFileName);
end;

procedure AddSystemParams(Params: TStrings);
begin
  Params.Values[svDepartNoName] := Context.GetParamValue(svDepartNoName);
  Params.Values[svDepartNameName] := Context.GetParamValue(svDepartNameName);
  Params.Values[svOperatorNoName] := Context.GetParamValue(svOperatorNoName);
  Params.Values[svOperatorNameName] :=
    Context.GetParamValue(svOperatorNameName);
  Params.Values[svOperatorNameName] :=
    Context.GetParamValue(svOperatorNameName);
  Params.Values[svSystemDateName] := GetSystemDate;
  Params.Values[PrintFullDateField] := GetSystemDateStr;
  //Params.Values[PrintFullDepartmentNameField] := CompanyName+CurrentDepartment.Name;
end;

function GetToday: string;
begin
  Result := Context.GetParamValue(svWorkDateName);
end;

function GetTodayStr: string;
begin
  Result := FormatDBStrDate(FullDateFormat, GetToday);
end;

function GetSystemDate: string;
var
  TmpCurrentDataSet: TDataSet;
  LocalDate: string;
  FLastDay: string;
  FNextDay: string;
  FCurrentDay: string;
begin
  Context.RefreshSysParams(SmartCardSystemDate);
  Result := SmartCardSystemDate;
end;

function GetSystemDateStr: string;
begin
  Result := FormatDBStrDate(FullDateFormat, GetSystemDate);
end;

procedure UpdateControlStyle(Control: TControl);
begin
  if Control is TDBGrid then
    with TDBGrid(Control) do
    begin
      if Color = clWindow then
      begin
        Color := FindColorOfStyle2(GridStyleItemName, Color);
        FindFontOfStyle(GridStyleItemName, Font);
        FixedColor := FindColorOfStyle2(GridTitleStyleItemName, FixedColor);
        FindFontOfStyle(GridTitleStyleItemName, TitleFont);
      end;
      TabStop := False;
    end;
end;

procedure HookControl(Control: TControl);
var
  NotifyEvent: TNotifyEvent;
  KeyPressEvent: TKeyPressEvent;
  KeyEvent: TKeyEvent;
begin
  if Control is TDBGrid then
  begin
    NotifyEvent := TDBGrid(Control).OnDblClick;
    if not Assigned(NotifyEvent) then
      TDBGrid(Control).OnDblClick := TGlobalEventHandler.DBGridDoubleClick;
    KeyEvent := TDBGrid(Control).OnKeyDown;
    if not Assigned(KeyEvent) then
      TDBGrid(Control).OnKeyDown := TGlobalEventHandler.DBGridKeyDown;
  end
  else if Control is TCheckListBox then
  begin
    NotifyEvent := TCheckListBox(Control).OnClickCheck;
    if not Assigned(NotifyEvent) then
      TCheckListBox(Control).OnClickCheck :=
        TGlobalEventHandler.CheckListBoxClick;
    KeyPressEvent := TCheckListBox(Control).OnKeyPress;
    if not Assigned(KeyPressEvent) then
      TCheckListBox(Control).OnKeyPress :=
        TGlobalEventHandler.CheckListBoxKeyPress;
  end;
end;

procedure MakeChildrenReadOnly(AParent: TWinControl; AReadOnly: Boolean);
var
  I: Integer;
  Ctrl: TControl;
begin
  for I := 0 to AParent.ControlCount - 1 do
  begin
    Ctrl := AParent.Controls[I];
    if Ctrl is TWinControl then
    begin
      if {(Ctrl is TfaMenu) or }(Ctrl is TfaAuth) then
        MakeControlReadOnly(Ctrl, AReadOnly)
      else if (csAcceptsControls in Ctrl.ControlStyle) or (Ctrl is TPageControl)
        then
        MakeChildrenReadOnly(TWinControl(Ctrl), AReadOnly)
      else
        MakeControlReadOnly(Ctrl, AReadOnly);
    end
    else
      MakeControlReadOnly(Ctrl, AReadOnly);
  end;
end;

procedure MakeControlReadOnly(Control: TControl; AReadOnly: Boolean);
var
  I: Integer;
begin
  if Control is TWVEdit then
    TWVEdit(Control).ReadOnly := AReadOnly
  else if Control is TCustomEdit then
    TEdit(Control).ReadOnly := AReadOnly
  else if Control is TCheckListBox then
  begin
    with TCheckListBox(Control) do
    begin
      for I := 0 to Items.Count - 1 do
        ItemEnabled[I] := not AReadOnly;
      Invalidate;
    end;
  end
    {else if Control is TfaMenu then
      TfaMenu(Control).CanEdit := not AReadOnly}
  else if Control is TfaAuth then
    TfaAuth(Control).CanEdit := not AReadOnly
  else if not (Control is TCustomLabel) then
    Control.Enabled := not AReadOnly;
end;

procedure DoLongOperation(const WaitMsg: string; DoSomeThing: TDoSomeThing);
begin
  Context.GetDialogSystem.ShowWaiting(WaitMsg);
  try
    DoSomeThing();
  finally
    Context.GetDialogSystem.CloseWaiting;
  end;
end;

procedure DoLongDatasetOperation(const WaitMsg: string; Dataset: TDataset;
  DoSomeThing: TDoSomeThingForDataset);
begin
  Context.GetDialogSystem.ShowWaiting(WaitMsg);
  try
    Dataset.DisableControls;
    try
      Dataset.First;
      while not Dataset.Eof do
      begin
        DoSomeThing(Dataset);
        Dataset.Next;
      end;
    finally
      Dataset.EnableControls;
    end;
  finally
    Context.GetDialogSystem.CloseWaiting;
  end;
end;

procedure ReinputCheck(WorkField: TWVField);
var
  CheckedFieldName: string;
  CheckedField: TWVField;
begin
  CheckedFieldName := WorkField.MonitorValueChangedFields;
  CheckedFieldName := StringReplace(CheckedFieldName, '|', '', [rfReplaceAll]);
  CheckedField := WorkField.WorkView.FindField(CheckedFieldName);
  if CheckedField <> nil then
  begin
    WorkField.Valid := CheckedField.Valid and (WorkField.Data.AsString =
      CheckedField.Data.AsString);
    WorkField.SetInvalidMessage(SInvalidReinput);
    WorkField.Hint := ' ';
  end;
end;

procedure NotEqualCheck(WorkField: TWVField);
var
  CheckedFieldName: string;
  CheckedField: TWVField;
begin
  CheckedFieldName := WorkField.MonitorValueChangedFields;
  CheckedFieldName := StringReplace(CheckedFieldName, '|', '', [rfReplaceAll]);
  CheckedField := WorkField.WorkView.FindField(CheckedFieldName);
  if CheckedField <> nil then
  begin
    WorkField.Valid := CheckedField.Valid and (WorkField.Data.AsString <>
      CheckedField.Data.AsString);
    WorkField.SetInvalidMessage('��' + CheckedField.Name + '�������ݵ���ͬ');
    WorkField.Hint := ' ';
  end;
end;

function DBStrDateToDateTime(const DateStr: string): TDateTime;
var
  Year, Month, Day: Word;
begin
  Year := StrToInt(Copy(DateStr, 1, 4));
  Month := StrToInt(Copy(DateStr, 5, 2));
  Day := StrToInt(Copy(DateStr, 7, 2));
  Result := EncodeDate(Year, Month, Day);
end;

function FormatDBStrDate(const DateFormat, DateStr: string): string;
var
  ADateTime: TDateTime;
begin
  try
    ADateTime := DBStrDateToDateTime(DateStr);
    Result := FormatDateTime(DateFormat, ADateTime);
  except
    Result := '';
  end;
end;

procedure AddRecToListview(listview: Tlistview; const Rec: Tstrings; const
  MaxRecCount: integer = 3);
var
  i, j: integer;
begin
  with ListView do
  begin
    //Move to Upper Line with all.
    if Items.count >= MaxRecCount then
      for i := 0 to Items.Count - 2 do
      begin
        items[i].caption := items[i + 1].caption;
        Items[i].SubItems.Clear;
        for j := 1 to Rec.Count - 1 do
        begin
          Items[i].SubItems.Add(Items[i + 1].SubItems[j - 1]);
        end;
      end;

    if Items.count < MaxRecCount then
      Items.Add;

    //Set Current Record to the Last Line.
    items[Items.Count - 1].caption := Rec.strings[0];
    Items[Items.Count - 1].SubItems.clear;
    for i := 1 to Rec.count - 1 do
    begin
      Items[Items.Count - 1].SubItems.Add(Rec.strings[i]);
    end;
  end;
end;

//��ȡǰ׺

function GetPrefix(const Ftext: string; const SeperateChar: char = '-'): string;
var
  FPos: integer;
begin
  FPos := Pos(SeperateChar, Ftext);
  if FPos < 1 then
  begin
    Result := Ftext;
    exit;
  end;
  Result := copy(Ftext, 1, FPos - 1);
end;

//��ȥǰ׺

function DelPrefix(const Ftext: string; const SeperateChar: char = '-'): string;
var
  FPos: integer;
begin
  FPos := Pos(SeperateChar, Ftext);
  if FPos < 1 then
  begin
    Result := Ftext;
    exit;
  end;
  Result := copy(Ftext, FPos + 1, Length(Ftext) - FPos + 1);
end;

//����TCheckListBox�����ȫ��ѡ�л�ȫ����ѡ��

procedure SelectAll(CheckListBox: TCheckListBox; SelectAll: Boolean);
var
  I: Integer;
begin
  for I := 0 to CheckListBox.Items.Count - 1 do
    if CheckListBox.ItemEnabled[I] then
      CheckListBox.Checked[I] := SelectAll;
  if CheckListBox is TWVCheckListBox then
    TWVCheckListBox(CheckListBox).InputDataChanged;
end;

//��ȫѡת��Ϊȫ��ѡ�������Ż�����

procedure MakeSelectAllToNoSelected(FieldData, ParamData: TKSDataObject;
  CheckListBox: TWVCheckListBox);
var
  CompareChar: Char;
  CompareStr: string;
  function CountCharInStr(const CompareChar: char; const CompareStr: string):
    Integer;
  var
    I: Integer;
  begin
    Result := 0;
    for I := 1 to Length(CompareStr) do
      if CompareStr[I] = CompareChar then
        Result := Result + 1;
  end;
begin
  CompareChar := CheckListBox.SeperateChar;
  CompareStr := trim(FieldData.AsString);
  if CompareChar <> #0 then
    if CountCharInStr(CompareChar, CompareStr) = CheckListBox.Items.Count then
      ParamData.AsString := ''
    else
      ParamData.AsString := CompareStr
  else if Length(CompareStr) = CheckListBox.Items.Count then
    ParamData.AsString := ''
  else
    ParamData.AsString := CompareStr;
end;

function InputText(const ACaption, APrompt: string; HideText, CustomerPassword:
  Boolean; var Value: string; MaxLength: Integer = 0): Boolean;
begin
  Result := Context.GetDialogSystem.InputText(ACaption, APrompt, HideText,
    CustomerPassword, Value, MaxLength);
end;

function InputCustomerPasswordForField(Field: TWVField; MaxLength: Integer = 0):
  Boolean;
var
  AText: string;
begin
  AText := '';
  Result := InputText(SInputPassword, Field.Caption, True, True, AText,
    MaxLength);
  if Result then
    Field.Data.AsString := AText;
end;

procedure TryRefreshDates(var FSysDate: string; Silence: Boolean = True);
begin
  try
    Context.RefreshSysParams(FSysDate);
  except
    WriteException;
    if not Silence and
      (Context.GetDialogSystem.ShowError2(SCannotRefreshDates) <> uaYes) then
      Abort;
  end;
end;

procedure ShowBranchMan(Sender: TComponent; WorkView: TWorkView; SingleSelect:
  Boolean; BranchName: string; ACaption: string = ''; IncludeStr: string =
  '������Ӫҵ��');
var
  Dialog: TfmBranchMan;
begin
  Dialog := TfmBranchMan.Create(Sender);
  Dialog.faBranchMan.HandleNeeded;
  Dialog.faBranchMan.TreeView.HandleNeeded;
  Dialog.faBranchMan.BuildTree;
  if ACaption = '' then
    Dialog.Init(WorkView, SingleSelect, BranchName, IncludeStr)
  else
  begin
    if Context.GetConfigSystem.ReadInteger(ccSelectTree, ACaption, cdSelectTree)
      = 0 then
      Dialog.Init(WorkView, True, BranchName, IncludeStr)
    else
      Dialog.Init(WorkView, False, BranchName, IncludeStr);
  end;
  Dialog.faBranchMan.TreeView.Items.BeginUpdate;
  try
    Dialog.faBranchMan.InitTreeNode(Dialog.faBranchMan.TreeView.Items.GetFirstNode);
  finally
    Dialog.faBranchMan.TreeView.Items.EndUpdate;
  end;
  Dialog.ShowModal;
end;

function UnZipString(const SourceStr: string): string;
var
  I: Integer;
begin
  Result := '';
  if Length(SourceStr) = 0 then
    Exit;
  for I := 1 to Length(SourceStr) do
  begin
    case SourceStr[I] of
      '0': Result := Result + '11';
      '1': Result := Result + '01';
      '2': Result := Result + '10';
    end;
  end;
end;

function ZipString(const SourceStr: string): string;
var
  I: Integer;
  temp: string;
begin
  Result := '';
  if Length(SourceStr) = 0 then
    Exit;
  I := 1;
  while I < Length(SourceStr) do
  begin
    temp := SourceStr[I] + SourceStr[I + 1];
    if temp = '11' then
      Result := Result + '0'
    else if temp = '01' then
      Result := Result + '1'
    else if temp = '10' then
      Result := Result + '2';
    I := I + 2;
  end;
end;

procedure RefreshInfoAdmin;
begin
  ComCmdDefinition.GetBranchInfoAdmin;
end;

function FormatBarCode(Source: string): string;
var
  FFilter: Boolean;
  tempstr: string;
begin
  FFilter := False;
  if Context.GetConfigSystem.ReadBoolean(ccInput, ckBarInput, False) then
    FFilter := True;
  tempstr := Source;
  if FFilter then
  begin
    if Copy(tempstr, 1, 1) = ';' then
      tempstr := Copy(tempstr, 2, Length(tempstr));
    if Copy(tempstr, Length(tempstr), 1) = '?' then
      tempstr := Copy(tempstr, 1, Length(tempstr) - 1);
    Result := tempstr;
  end
  else
  begin
    Result := tempstr;
  end;
end;

procedure UpdateBranchDirectory;
begin
  //����Ӫҵ�������ֵ�
  FreeIdObjects(deDepart);
end;

procedure GetlinealChildBranch(Items: TStrings; Objects: TObjectList);
var
  I: Integer;
  Obj: TKSAbstractObject;
  ChildrenInfos: TList;
  ChildBranch: string;
begin
  CheckObject(InfoAdmin, 'Error : InfoAdmin not init');
  ChildrenInfos := TList.Create;
  InfoAdmin.StructureList.Find(ChildrenInfos,
    Context.ParamData(svDepartNoName).AsString);
  for I := 0 to ChildrenInfos.Count - 1 do
  begin
    ChildBranch := ChildBranch + TKSTreeStructure(ChildrenInfos[I]).ChildId +
      ',';
  end;

  try
    Items.Clear;
    if Objects <> nil then
      for I := 0 to Objects.Count - 1 do
      begin
        Obj := TKSAbstractObject(Objects[I]);
        if Pos(Obj.GetID, ChildBranch) <> 0 then
        begin
          Items.AddObject(Obj.GetDisplayLabel, Obj);
        end;
      end;
  finally
    ChildrenInfos.Free;
  end;
end;

function FindStringListFormObjectList(ObjectList: TObjectList; Name: string):
  TStringList;
var
  I: Integer;
begin
  Result := nil;
  Assert(ObjectList <> nil);
  for I := 0 to ObjectList.Count - 1 do
  begin
    if Trim(TStringList(ObjectList.Items[I]).Strings[0]) = Trim(Name) then
    begin
      Result := TStringList(ObjectList.Items[I]);
      Exit;
    end;
  end;
end;

function CreateOneStringList(ObjectList: TObjectList; StringListName: string):
  TStringList;
begin
  Result := nil;
  Assert(ObjectList <> nil);
  Result := FindStringListFormObjectList(ObjectList, StringListName);
  if Result = nil then
  begin
    Result := TStringList.Create;
    Result.Add(StringListName);
    ObjectList.Add(Result);
  end;
end;

//(IN REPORT)

function DoReturnCode(ReturnCode: Integer; ReMess: string): Boolean;
begin
  Result := True;
  if ReturnCode <> 0 then
  begin
    Context.GetDialogSystem.ShowWarning(ReMess);
    Result := False;
  end;
end;

//rding,20040526

function InputQueryCH(const ACaption, APrompt: string; var Value: string):
  Boolean;
var
  Form: TForm;
  Prompt: TLabel;
  Edit: TEdit;
  DialogUnits: TPoint;
  ButtonTop, ButtonWidth, ButtonHeight: Integer;

  function GetAveCharSize(Canvas: TCanvas): TPoint;
  var
    I: Integer;
    Buffer: array[0..51] of Char;
  begin
    for I := 0 to 25 do
      Buffer[I] := Chr(I + Ord('A'));
    for I := 0 to 25 do
      Buffer[I + 26] := Chr(I + Ord('a'));
    GetTextExtentPoint(Canvas.Handle, Buffer, 52, TSize(Result));
    Result.X := Result.X div 52;
  end;
begin
  Result := False;
  Form := TForm.Create(Application);
  with Form do
  try
    Canvas.Font := Font;
    DialogUnits := GetAveCharSize(Canvas);
    BorderStyle := bsDialog;
    Caption := ACaption;
    ClientWidth := MulDiv(180, DialogUnits.X, 4);
    ClientHeight := MulDiv(63, DialogUnits.Y, 8);
    Position := poScreenCenter;
    Prompt := TLabel.Create(Form);
    with Prompt do
    begin
      Parent := Form;
      AutoSize := True;
      Left := MulDiv(8, DialogUnits.X, 4);
      Top := MulDiv(8, DialogUnits.Y, 8);
      Caption := APrompt;
    end;
    Edit := TEdit.Create(Form);
    with Edit do
    begin
      Parent := Form;
      Left := Prompt.Left;
      Top := MulDiv(19, DialogUnits.Y, 8);
      Width := MulDiv(164, DialogUnits.X, 4);
      MaxLength := 255;
      Text := Value;
      SelectAll;
    end;
    ButtonTop := MulDiv(41, DialogUnits.Y, 8);
    ButtonWidth := MulDiv(50, DialogUnits.X, 4);
    ButtonHeight := MulDiv(14, DialogUnits.Y, 8);
    with TButton.Create(Form) do
    begin
      Parent := Form;
      Caption := 'ȷ��&O';
      ModalResult := mrOk;
      Default := True;
      SetBounds(MulDiv(38, DialogUnits.X, 4), ButtonTop, ButtonWidth,
        ButtonHeight);
    end;
    with TButton.Create(Form) do
    begin
      Parent := Form;
      Caption := 'ȡ��&C';
      ModalResult := mrCancel;
      Cancel := True;
      SetBounds(MulDiv(92, DialogUnits.X, 4), ButtonTop, ButtonWidth,
        ButtonHeight);
    end;
    if ShowModal = mrOk then
    begin
      Value := Edit.Text;
      Result := True;
    end;
  finally
    Form.Free;
  end;
end;

procedure CheckCommandParamOneByOne(Command : TWVCommand);
var
  DataObj: TKSDataObject;
  Descriptor : TWVCommandDescriptor;
  I : Integer;
begin
  Assert( Command <> nil );
  Descriptor := Command.GetDescriptor;
  for I := 0 to Descriptor.GetParamCount - 1 do
  begin
    DataObj := Command.ParamData(I);
    ShowMessage(Format('%s - %s ',
      [Descriptor.GetParamName(I),DataObj.AsString]));
  end;
end;
end.
