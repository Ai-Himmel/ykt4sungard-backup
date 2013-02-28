unit KSDataDictionary;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSDataDictionary
   <What>数据字典
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}

interface

uses Classes, ObjDir, DB, Dialogs;

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
    constructor Create(const AID, AName : string);
    property    ID : string read FID;
    property    Name : string read FName;
  end;

  TIdClass = class of TIdObject;

  TDataEntry = type Integer;

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
    FDataEntry: TDataEntry;
    FDepartment: string;
    FValid: Boolean;
    FUpdateTime: LongWord;
    function    GetItems(Index: Integer): TIdObject;
  public
    constructor Create(const ADataEntry : TDataEntry; const ADepartment : string);
    function    Find(const ID:string) : TIdObject;
    procedure   GetText(Sender: TField; var Text: string; DisplayText: Boolean);
    procedure   GetText2(Sender: TField; var Text: string; DisplayText: Boolean);
    function    GetDisplayText(const ID : string) : string;
    function    GetDisplayText2(const IDs : string) : string;
    property    DataEntry : TDataEntry read FDataEntry;
    property    Department : string read FDepartment;
    property    Items[Index : Integer] : TIdObject read GetItems; default;
    property    UpdateTime : LongWord read FUpdateTime write FUpdateTime;
    property    Valid : Boolean read FValid write FValid;
  end;
  {数据字典 Entry }
  TDictDataEntry = class
  private
    FObjList : TIdObjectList;
    FReferCount : Integer;
    function GetDataEntry: TDataEntry;
    procedure SetObjectList(const Value: TIdObjectList);
    function GetTickCount: LongInt;
  public
    {增加引用计数}
    function IncRefer(step : Integer = 1):Integer;
    {减少引用计数}
    function DecRefer(step : Integer = 1):Integer;
    property Entry : TDataEntry read GetDataEntry;
    property ObjectList : TIdObjectList read FObjList write SetObjectList;
    property TickCount : LongInt read GetTickCount;
    property ReferCount : Integer read FReferCount;
    constructor Create(objList:TIdObjectList);
    destructor Destroy; override;
  end;
  {数据字典管理}
  TDictionaryManage = class
  private
    FDictList : TStrings;
    function GetObjectList(Index: TDataEntry): TIdObjectList;
  protected
    constructor Create;
    {清空所有数据字典}
    procedure Clear;
  public
    {查找指定的数据字典}
    function FindEntry(entry:TDataEntry; tickCount:LongInt):TDictDataEntry;overload;
    {查找最新的数据字典}
    function FindEntry(entry:TDataEntry):TDictDataEntry;overload;
    {生成新的数据字典}
    function GetNewEntry(list: TIdObjectList):TIdObjectList;
    {删除一个数据字典}
    procedure DeleteEntry(entry:TDataEntry;tickCount:LongWord = 0);
    {取得唯一实例}
    class function GetInstance: TDictionaryManage;
    property ObjectsList[Index:TDataEntry] : TIdObjectList read GetObjectList;
    {析构函数}
    destructor Destroy; override;
  end;

function  FindIdObject(const DataEntry : TDataEntry; const ID : string; const Department : string='') : TIdObject;

function  GetIdObjectName(const DataEntry : TDataEntry; const ID : string; const Department : string='') : string;

function  GetIdObjectList(const DataEntry : TDataEntry; const Department : string='') : TIdObjectList;

function  NeedIdObjectList(const DataEntry : TDataEntry; const Department : string='') : TIdObjectList;

function  DataEntryToCategory(const DataEntry : TDataEntry; const Department : string) : string;

function  GetFirstItemID(const DataEntry : TDataEntry; const Department : string=''; Filtered : Boolean = True) : string;

//用于收费比率设置
function  GetSecondItemID(const DataEntry : TDataEntry; const Department : string=''; Filtered : Boolean = True) : string;

procedure FreeIdObjects(const DataEntry : TDataEntry; const Department : string='');


{
  <Procedure>GetCustTypeText
  <What>将营业部客户类别字段转换为文字
  <Params>
    DepartFieldName - 数据集里面营业部代码的字段名
  <Exception>
}
procedure GetCustTypeText(Sender: TField; const DepartFieldName : string; var Text: string);

{
  <Procedure>GetCustGroupText
  <What>将营业部客户类别字段转换为文字
  <Params>
    DepartFieldName - 数据集里面营业部代码的字段名
  <Exception>
}
procedure GetCustGroupText(Sender: TField; const DepartFieldName : string; var Text: string);

type
  TGetIdObjectsProc = procedure (IdObjects : TIdObjectList);

var
  GetIdObjectsProc : TGetIdObjectsProc;
//  GetIdObjectsProc2 : TGetIdObjectsProc;
  AllDepartemntIdObject : TIdObject;
  EmptyIdObject : TIdObject;
  DictionaryManageInstance : TDictionaryManage;

type
  TMaintainMethod = (mmReadOnly, mmCenter, mmDepartment, mmHide);

  TDataDictionaryCategory = class(TIdObject)
  private
    FMaintainMethod: TMaintainMethod;
    FLength: Integer;
    FOnlyNumber: Boolean;

  public
    constructor Create(const AID, AName : string; AMaintainMethod: TMaintainMethod;
      ALength : Integer=0; AOnlyNumber : Boolean=False);
    property    MaintainMethod : TMaintainMethod read FMaintainMethod;
    property    Length : Integer read FLength;
    property    OnlyNumber : Boolean read FOnlyNumber;
  end;

  TBusinessFlag = class(TIdObject)
  private
    FChangeCategory: string;
  public
    constructor Create(const AID, AName, AChangeCategory : string);
    property    ChangeCategory : string read FChangeCategory;
  end;

implementation

uses SysUtils, KSClientConsts, KSFrameWorks, KSFrameWorkUtils, Windows;

function  DataEntryToCategory(const DataEntry : TDataEntry; const Department : string) : string;
begin
  Result := Format('KSDataDictionary[%d.%s]',[DataEntry,Department]);
end;

function  GetDepartment(const Department : string='') : string;
begin
  if Department='' then
    Result := CurrentDepartmentNo else
    Result := Department;
end;

procedure CompareIdObject(Obj : TObject; const Name:string; ID : integer; var Finded : Boolean);
begin
  Finded := TidObject(Obj).ID = Name;
end;

function  FindIdObject(const DataEntry : TDataEntry; const ID : string; const Department : string='') : TIdObject;
var
  List : TIdObjectList;
begin
  List := NeedIdObjectList(DataEntry, GetDepartment(Department));
  Result := List.Find(ID);
end;

function  GetIdObjectName(const DataEntry : TDataEntry; const ID : string; const Department : string='') : string;
var
  IdObject : TIdObject;
begin
  IdObject := FindIdObject(DataEntry,ID, GetDepartment(Department));
  if IdObject<>nil then
    Result := IdObject.Name else
    Result := '';
end;

function  GetIdObjectList(const DataEntry : TDataEntry; const Department : string='') : TIdObjectList;
begin
  Result := TIdObjectList(GetCategory(DataEntryToCategory(DataEntry, GetDepartment(Department))));
  //Result := TDictionaryManage.GetInstance.ObjectsList[DataEntry];
  Assert((Result=nil) or (Result is TIdObjectList));
end;

function  NeedIdObjectList(const DataEntry : TDataEntry; const Department : string='') : TIdObjectList;
begin
  Result := GetIdObjectList(DataEntry, GetDepartment(Department));
  if Result=nil then
  begin
    Result := TIdObjectList.Create(DataEntry, GetDepartment(Department));
    if Assigned(GetIdObjectsProc) then
    begin
      GetIdObjectsProc(Result);
      TDictionaryManage.GetInstance.GetNewEntry(Result);
    end;
  end else
  begin
    if Assigned(GetIdObjectsProc)
      and not Result.Valid then
      //and (GetTickCount-Result.UpdateTime>1000*10) then
    begin
      Result.Clear;
      GetIdObjectsProc(Result);
    end;
  end;
  Assert(Result<>nil);
end;

function  GetFirstItemID(const DataEntry : TDataEntry; const Department : string=''; Filtered : Boolean = True) : string;
var
  List : TIdObjectList;
  // I : Integer;
  // ProhibitStr : string;
begin
  List := NeedIdObjectList(DataEntry, GetDepartment(Department));
  Result := '';
  if List.Count>0 then
  begin
    { // 需要根据权限过滤市场和币种的版本
    if Filtered and ((DataEntry=deCurrency) or (DataEntry=deMarket)) then
    begin
      // 如果是币种和市场，根据禁止集合过滤
      if DataEntry=deCurrency then
        ProhibitStr := Context.GetParamValue(svProhibitMoneyName)
      else if DataEntry=deMarket then
        ProhibitStr := Context.GetParamValue(svProhibitMarketsName)
      else
        ProhibitStr := '';
      for I:=0 to List.Count-1 do
      begin
        if (ProhibitStr='') or (Pos(List[I].ID,ProhibitStr)<=0) then
        begin
          Result := List[I].ID;
          Break;
        end;
      end;
    end else
      // 不需要过滤
      Result := TIdObject(List[0]).ID;
    }
    // 不需要根据权限过滤市场和币种的版本
    Result := TIdObject(List[0]).ID;
  end;
end;

function  GetSecondItemID(const DataEntry : TDataEntry; const Department : string=''; Filtered : Boolean = True) : string;
var
  List : TIdObjectList;
  // I : Integer;
  // ProhibitStr : string;
begin
  List := NeedIdObjectList(DataEntry, GetDepartment(Department));
  Result := '';
  if List.Count>0 then
  begin
    { // 需要根据权限过滤市场和币种的版本
    if Filtered and ((DataEntry=deCurrency) or (DataEntry=deMarket)) then
    begin
      // 如果是币种和市场，根据禁止集合过滤
      if DataEntry=deCurrency then
        ProhibitStr := Context.GetParamValue(svProhibitMoneyName)
      else if DataEntry=deMarket then
        ProhibitStr := Context.GetParamValue(svProhibitMarketsName)
      else
        ProhibitStr := '';
      for I:=0 to List.Count-1 do
      begin
        if (ProhibitStr='') or (Pos(List[I].ID,ProhibitStr)<=0) then
        begin
          Result := List[I].ID;
          Break;
        end;
      end;
    end else
      // 不需要过滤
      Result := TIdObject(List[0]).ID;
    }
    // 不需要根据权限过滤市场和币种的版本
    Result := TIdObject(List[1]).ID;
  end;
end;

procedure FreeIdObjects(const DataEntry : TDataEntry; const Department : string='');
var
  List : TIdObjectList;
begin
  //TDictionaryManage.GetInstance.DeleteEntry(DataEntry);

  List := GetIdObjectList(DataEntry, GetDepartment(Department));
  if List<>nil then
    List.Free;
  
end;

procedure GetCustTypeText(Sender: TField; const DepartFieldName : string;
  var Text: string);
var
  IDObjects : TIdObjectList;
  DepartField : TField;
begin
  DepartField := Sender.Dataset.FindField(DepartFieldName);
  if (DepartField<>nil) and (DepartField.AsString<>'') then
  begin
    IDObjects := NeedIdObjectList(deDepartCustomerType,DepartField.AsString);
    IDObjects.GetText(Sender, Text, True);
  end;
end;

procedure GetCustGroupText(Sender: TField; const DepartFieldName : string; var Text: string);
var
  IDObjects : TIdObjectList;
  DepartField : TField;
begin
  DepartField := Sender.Dataset.FindField(DepartFieldName);
  if (DepartField<>nil) and (DepartField.AsString<>'') then
  begin
    IDObjects := NeedIdObjectList(deCustomerGroup,DepartField.AsString);
    IDObjects.GetText(Sender, Text, True);
  end;
end;

{ TIdObjectList }

constructor TIdObjectList.Create(const ADataEntry : TDataEntry; const ADepartment : string);
begin
  //Assert(GetIdObjectList(ADataEntry, ADepartment)=nil);
  inherited Create(DataEntryToCategory(ADataEntry, ADepartment),True);
  FDataEntry := ADataEntry;
  FDepartment := ADepartment;
  FValid := True;
  FUpdateTime := GetTickCount;
end;

function TIdObjectList.Find(const ID: string): TIdObject;
begin
  Result := TIdObject(FindObject(Id,0,CompareIdObject));
end;

function TIdObjectList.GetDisplayText(const ID: string): string;
var
  IdObject : TIdObject;
begin
  Result := ID;
  IdObject := Find(ID);
  if IdObject<>nil then
    Result := Format(IdObjectDisplayFormat,[IdObject.Id,IdObject.Name]);
end;

function TIdObjectList.GetDisplayText2(const IDs: string): string;
var
  I : Integer;
  TranslatedText : string;
  IdObject : TIdObject;
begin
  TranslatedText := '';
  for I:=0 to Count-1 do
  begin
    IdObject := Items[I];
    if Pos(IdObject.Id, IDs)>0 then
      TranslatedText := TranslatedText + IdObject.Name + IdObjectSeparateChar;
  end;
  if TranslatedText<>'' then
  begin
    System.Delete(TranslatedText,Length(TranslatedText),1); // 删除最后的IdObjectSeparateChar
    Result := TranslatedText;
  end else
    Result := IDs;
end;

function TIdObjectList.GetItems(Index: Integer): TIdObject;
begin
  Result := TIdObject(inherited Items[Index]);
end;

procedure TIdObjectList.GetText(Sender: TField; var Text: string;
  DisplayText: Boolean);
begin
  Text := Sender.AsString;
  if DisplayText then
    Text := GetDisplayText(Text);
end;

procedure TIdObjectList.GetText2(Sender: TField; var Text: string;
  DisplayText: Boolean);
begin
  Text := Sender.AsString;
  if DisplayText then
    Text := GetDisplayText2(Text);
end;

{ TIdObject }

constructor TIdObject.Create(const AID, AName: string);
begin
  FID := AID;
  FName := AName;
end;

{ TDataDictionaryCategory }

constructor TDataDictionaryCategory.Create(const AID, AName: string;
  AMaintainMethod: TMaintainMethod; ALength : Integer; AOnlyNumber : Boolean);
begin
  inherited Create(AID,AName);
  FMaintainMethod := AMaintainMethod;
  FLength := ALength;
  FOnlyNumber := AOnlyNumber;
end;

{ TBusinessFlag }

constructor TBusinessFlag.Create(const AID, AName,
  AChangeCategory: string);
begin
  inherited Create(AID,AName);
  FChangeCategory := AChangeCategory;
end;

{ TDictionaryManage }

procedure TDictionaryManage.Clear;
var
  i : Integer;
  dict : TDictDataEntry;
  list : TIdObjectList;
begin
  //
  for i := 0 to FDictList.Count - 1 do
  begin
    dict := TDictDataEntry(FDictList.Objects[i]);
    list := TIdObjectList(dict.ObjectList);
    try
      list.Free;
    except
    end;
    try
      dict.Free;
    except
    end;
  end;
  FDictList.Clear();
end;

constructor TDictionaryManage.Create;
begin
  //
  FDictList := TStringList.Create;
  FDictList.Clear;
end;

procedure TDictionaryManage.DeleteEntry(entry: TDataEntry;
  tickCount: LongWord);
var
  i ,refer,delIndex: Integer;
  dict,delDict : TDictDataEntry;
  list : TIdObjectList;
  tmpList : TStringList;
  canDel : boolean;
begin
  canDel := False;
  delDict := nil;
  dict := nil;
  //tmpList := TStringList.Create;
  try
    for i := 0 to FDictList.Count - 1 do
    begin
      if not ( FDictList.Objects[i] is TDictDataEntry ) then
        Exit;
      dict := TDictDataEntry(FDictList.Objects[i]);
      if (dict = nil) then
        Continue;
      // 如果是可以删除的 ID
      if( dict.Entry = entry) then
      begin
        if( dict.tickCount = tickCount )then
        begin
          delDict := dict;
          refer := dict.DecRefer;
          delIndex := i;
          Continue;
        end
        else
        begin
          if (dict.tickCount > delDict.tickCount) then
          begin
            canDel := True;
          end;
        end;
      end;
      //tmpList.AddObject(dict.ObjectList.Name,dict);
    end;
    //FDictList.Clear;
    //FDictList.Assign(tmpList);
    if( refer <= 0) and (canDel = True) then
    begin
      FDictList.Delete(delIndex);
      try
        list := TIdObjectList(delDict.ObjectList);
        list.Free;
      except
      end;
      try
        delDict.Free;
      except
      end;
    end;
  finally
  end;
  //tmpList.Free;
end;

destructor TDictionaryManage.Destroy;
begin
  // release dict
  Clear;
  FreeAndNil(FDictList);
  inherited;
end;

function TDictionaryManage.FindEntry(entry: TDataEntry;
  tickCount: Integer): TDictDataEntry;
var
  i : Integer;
begin
  for i := 0 to FDictList.Count - 1 do
  begin
    Result := TDictDataEntry(FDictList.Objects[i]);
    if( Result.Entry = entry)
      and ((Result.TickCount = tickCount) or (tickCount = -1)) then
    begin
      Result.IncRefer;
      Exit;
    end;
  end;
  Result := nil;
end;

function TDictionaryManage.FindEntry(entry: TDataEntry): TDictDataEntry;
var
  i: Integer;
  dict : TDictDataEntry;
begin
  Result := nil;
  for i := 0 to FDictList.Count - 1 do
  begin
    dict := TDictDataEntry(FDictList.Objects[i]);
    if (dict.Entry = entry) then
    begin
      if ((Result <> nil) and (Result.TickCount < dict.TickCount))
        or (Result = nil) then
      begin
        Result := dict;
      end;
    end;
  end;
  if( Result <> nil) then
    Result.IncRefer;
end;

class function TDictionaryManage.GetInstance: TDictionaryManage;
begin
  if (DictionaryManageInstance = nil) then
  begin
    DictionaryManageInstance := TDictionaryManage.Create;
  end;
  Result := DictionaryManageInstance;
end;

function TDictionaryManage.GetNewEntry(list: TIdObjectList): TIdObjectList;
var
  dict : TDictDataEntry;
begin
  //
  dict := TDictDataEntry.Create(list);
  FDictList.AddObject(list.Name,dict);
  Result := list;
end;

function TDictionaryManage.GetObjectList(Index: TDataEntry): TIdObjectList;
var
  dict : TDictDataEntry;
begin
  //
  Result := nil;
  dict := FindEntry(Index);
  if( dict <> nil ) then
  begin
    Result := dict.ObjectList;
  end;
end;

{ TDictDataEntry }

constructor TDictDataEntry.Create(objList: TIdObjectList);
begin
  assert(objList <> nil);
  FObjList := objList;
  FReferCount := 0;
end;

function TDictDataEntry.DecRefer(step: Integer): Integer;
begin
  Dec(FReferCount,step);
  if FReferCount < 0 then
    FReferCount := 0;
  Result := FReferCount;
end;

destructor TDictDataEntry.Destroy;
begin
  //
  inherited;
end;

function TDictDataEntry.GetDataEntry: TDataEntry;
begin
  Result := FObjList.DataEntry;
end;

function TDictDataEntry.GetTickCount: LongInt;
begin
  Result := FObjList.UpdateTime;
end;

function TDictDataEntry.IncRefer(step: Integer): Integer;
begin
  Inc(FReferCount,step);
  Result := FReferCount;
end;

procedure TDictDataEntry.SetObjectList(const Value: TIdObjectList);
begin
  FObjList := Value;
end;

initialization
  AllDepartemntIdObject := TIdObject.Create(AllDepartsNo,SAllDepartments);
  EmptyIdObject := TIdObject.Create(EmptyIdObjectCode,EmptyIdObjectName);
  DictionaryManageInstance := nil;

finalization
  FreeAndNil(AllDepartemntIdObject);
  FreeAndNil(DictionaryManageInstance);

end.

