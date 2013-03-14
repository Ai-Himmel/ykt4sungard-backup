unit DataUsageUtils;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>DataUsageUtils
   <What>表现数据、处理数据的公共函数
   这些方法：不产生数据源访问。
   <Written By> Huang YanLai (黄燕来)、赵东波、曾创能
   <History>
**********************************************}


interface

uses Windows, SysUtils, Classes, Graphics, Controls, Forms, Db, Grids, DBGrids, WorkViews, StdCtrls
     ,comctrls,Dialogs,RzListVw;

{
  修改自zdb的程序
}

type
  TDataSearchOptions = record
    //FieldIndex: Integer;
    FieldName : string;
    SearchValue: string;
    IsFromFirst: Boolean;
    IsUpperLowercase: Boolean;
    IsForward: Boolean;
    IsFirst : Boolean;
  end;

function  SetupGrid(Grid: TDBGrid; ColColor: TColor):Boolean;

procedure ReadGridInfo(Grid: TDBGrid; ColColor: TColor; const FileName : string);

procedure SaveGridInfo(Grid: TDBGrid; const FileName : string);

function  IsSearchDataset(DataSet: TDataSet; var SearchOptions : TDataSearchOptions):Boolean; overload;

function  IsSearchDataset(Grid : TDBGrid; var SearchOptions : TDataSearchOptions):Boolean; overload;

{//wsn 20041013 加入独立的自定义查询
function IsSearchSmartDataset(Grid : TDBGrid;  var SearchOptions : TDataSearchOptions):Boolean; overload;
//wsn 20041013 加入独立的自定义查询
function IsSearchSmartDataset(DataSet : TDataSet;  var SearchOptions : TDataSearchOptions):Boolean; overload;
 }
function  SearchDataset(DataSet: TDataSet; var SearchOptions : TDataSearchOptions):Boolean;

{
  修改自zcn的程序
}

//  输出函数（过程）列表：
//     PrintDBGrid(dbGrid:TDBGrid;Title:String); 打印DbGrid中的数据
//        参数 dbGrid:dbGrid  Title:报表的标题
//
//     PrintToText(DbGrid:TDbGrid;RptTitle,FileName:String);打印DbGrid的数据到文本
//        参数 dbGrid:dbGrid  RptTitle:报表的标题  FileName:保存到的文件名


procedure DbGridPrint(DBGrid : TDBGrid; const RptTitle : string;
    const LRptTitle : string; const RRptTitle:string;
    const RtpDateSpotTitle:string); //打印DbGrid   输出函数

procedure DbListViewPrint(ListView:TListView;DataSet:TDataSet; const RptTitle : string;
    const LRptTitle : string; const RRptTitle:string;const RtpDateSpotTitle:string);  //打印ListView 输出函数

procedure StringGridPrint(StringGrid : TStringGrid; const RptTitle : string;
    const LRptTitle : string; const RRptTitle:string;const RtpDateSpotTitle:string); //打印DbGrid   输出函数


// 打印回单
procedure PrintReceipt(const BasedFileName : string; WorkView : TWorkView; AddDefaultSystemParams : Boolean=True);

// 打印回单。根据配置确定是否打印回单，如果要打印，出现对话框，询问操作员，是否打印。返回是否打印
function  DoPrintReceipt(const AOperation : string; const BasedFileName : string; WorkView : TWorkView; AddDefaultSystemParams : Boolean=True):Boolean;

// 根据配置确定是否出现确认对话框。如果出现确认对话框，并且用户选择取消，返回False，否则返回True
function  DoPrompt(const AOperation, APrompt : string) : Boolean;



// 获得自动汇总的数据
// function  GetAggregateFields(WorkView : TWorkView; GroupIndex : Integer; Dataset : TDataset):Boolean;

procedure DrawCellForSysParams(
  Grid : TDBGrid;
  const Rect: TRect;
  DataCol: Integer;
  Column: TColumn;
  State: TGridDrawState;
  const DepartFieldName : string);

{
  <Function>GetPrinterInfoToLabel
  <What>将当前打印机信息填充到标签里面
  如果没有安装打印机，在标签里面显示错误信息
  <Params>
    -
  <Return>
  是否安装了打印机
  <Exception>
}

function  GetPrinterInfoToLabel(ALabel : TLabel) : Boolean;

//add by cgm
//根据输入字段的值决定DBGRID的输入颜色
procedure DrawGridColumnCell(Grid : TDBGrid;const Rect: TRect;Column: TColumn;DataCol: Integer;State: TGridDrawState;IndexFieldName : string);


implementation

uses AdjustGridDlg,  Inifiles, UPrintMode, KSFrameWorks, KSClientConsts, RPDesignInfo,
  KSFrameWorkUtils, BDAImp, BDAImpEx, LogFile, PrintUtils, Printers,DataSearchDlg{SmartDataSearchDlg};

function SetupGrid(Grid: TDBGrid; ColColor: TColor):Boolean;
var
  Dialog : TdlgAdjustGrid;
begin
  Dialog := TdlgAdjustGrid.Create(Application);
  try
    Result := Dialog.Execute(Grid,ColColor);
  finally
    Dialog.Free;
  end;
end;

procedure ReadGridInfo(Grid: TDBGrid; ColColor: TColor; const FileName : string);
var
  GridInfo: TIniFile;
  Count, I, Sequence : Integer;
  Section: string;
  Visible: Boolean;
  FieldName : string;
  Column : TColumn;

  function  FindColumn(const FieldName : string) : TColumn;
  var
    J: Integer;
  begin
    Result := nil;
    for J:=0 to Grid.Columns.Count-1 do
      if SameText(Grid.Columns[J].FieldName, FieldName) then
      begin
        Result := Grid.Columns[J];
        Break;
      end;
  end;

begin
  GridInfo := TIniFile.Create(FileName);
  try
    with GridInfo do
    begin
      Count := ReadInteger('Root','Count',0);
      if Count = 0 then Exit;
      {
      // 该版本根据配置文件生成整个DBGrid的Columns
      Grid.Columns.Clear;
      For I := 0 to Count - 1 do
      begin
        Section := IntToStr(I+1);
        Grid.Columns.Add;
        Grid.Columns[I].Width :=  ReadInteger(Section,'Width',64);
        Grid.Columns[I].FieldName := ReadString(Section,'FieldName','');
        Grid.Columns[I].Title.Caption := ReadString(Section,'Title',Grid.Columns[I].FieldName);
        Visible := ReadBool(Section,'Visible',True);
        if Visible then
          Grid.Columns[I].Color := Grid.Color
        else
          Grid.Columns[I].Color := ColColor;
      end;
      }
      
      // 该版本根据配置文件仅仅调整Column的顺序、宽度、颜色，不修改标题和字段名，
      // 避免因为配置文件的错误影响整个DBGrid
      Sequence := 0;
      for I:=0 to Count - 1 do
      begin
        Section := IntToStr(I+1);
        FieldName := ReadString(Section,'FieldName','');
        Column := FindColumn(FieldName);
        if Column<>nil then
        begin
          Column.Index := Sequence;
          Inc(Sequence);
          Column.Width :=  ReadInteger(Section,'Width',Column.Width);
          Visible := ReadBool(Section,'Visible',True);
          if Visible then
          begin
          
            Column.Color := Grid.Color ;
          end
          else
          begin
            Column.Visible := False;
            Column.Width := -1;
            Column.Color := ColColor;
          end;
        end;
      end;
    end;
  finally
    GridInfo.Free;
  end;
end;

procedure SaveGridInfo(Grid: TDBGrid; const FileName : string);
var
  GridInfo: TIniFile;
  I: Integer;
  Section: String;
  Visible: Boolean;
begin
  GridInfo := TInifile.Create(FileName);
  try
    with GridInfo do
    begin
      WriteInteger('Root','Count',Grid.Columns.Count);
      For I := 0 to Grid.Columns.Count - 1 do
      begin
        Visible := Grid.Columns[I].Color = Grid.Color;
        Section := IntToStr(I+1);
        WriteString(Section,'FieldName',Grid.Columns[I].FieldName);
        WriteString(Section,'Title',Grid.Columns[I].Title.Caption);
        WriteInteger(Section,'Width',Grid.Columns[I].Width);
        WriteBool(Section,'Visible',Visible);
      end;
    end;
  finally
    GridInfo.Free;
  end;
end;

function IsSearchDataset(DataSet: TDataSet; var SearchOptions : TDataSearchOptions):Boolean;
var
  Dialog: TdlgSearchDataset;
begin
  Dialog := TdlgSearchDataset.Create(Application);
  try
    SearchOptions.IsFirst := True;
    Result := Dialog.Execute(DataSet,SearchOptions);
  finally
    Dialog.Free;
  end;
end;

{function IsSearchSmartDataset(Grid : TDBGrid;  var SearchOptions : TDataSearchOptions):Boolean;
var
  Dialog: TdlgSmartSearchDataset;
begin
  Dialog := TdlgSmartSearchDataset.Create(Application);
  try 
    SearchOptions.IsFirst := True;
    Result := Dialog.Execute(Grid,SearchOptions);
  finally
    Dialog.Free;
  end;
end;   }


{function IsSearchSmartDataset(DataSet: TDataSet; var SearchOptions : TDataSearchOptions):Boolean;
var
  Dialog: TdlgSmartSearchDataset;
begin
  Dialog := TdlgSmartSearchDataset.Create(Application);
  try
    SearchOptions.IsFirst := True;
    Result := Dialog.Execute(DataSet,SearchOptions);
  finally
    Dialog.Free;
  end;
end;      }


function  IsSearchDataset(Grid : TDBGrid; var SearchOptions : TDataSearchOptions):Boolean;
var
  Dialog: TdlgSearchDataset;
begin
  Dialog := TdlgSearchDataset.Create(Application);
  try
    SearchOptions.IsFirst := True;
    Result := Dialog.Execute(Grid, SearchOptions);
  finally
    Dialog.Free;
  end;
end;

function  SearchDataset(DataSet: TDataSet; var SearchOptions : TDataSearchOptions):Boolean;
var
  Field : TField;
  I: Integer;
begin
  Result := False;
  Field := DataSet.FindField(SearchOptions.FieldName);
  if (Field = nil) or (SearchOptions.SearchValue = '')then
  begin
    //MessageDlg('The Search String cannot be blank.', mtError, [mbOK], 0);
    SearchOptions.IsFirst := False;
    Exit;
  end;
  Dataset.DisableControls;
  try
    if SearchOptions.IsFromFirst and SearchOptions.IsFirst then
      Dataset.First;
    if SearchOptions.IsForward then  //向前搜寻
    begin
      if not SearchOptions.IsFirst then
        DataSet.Next;
      while not DataSet.Eof do
      begin
        if SearchOptions.IsUpperLowercase then //区分大小写
          I := CompareStr(Field.AsString, SearchOptions.SearchValue)
        else
          I := CompareText(Field.AsString, SearchOptions.SearchValue);
        if I = 0 then
        begin
          Result := True;
          Break;
        end;
        DataSet.Next;
      end
    end
    else                             //向后搜寻
    begin
      if not SearchOptions.IsFirst then
        DataSet.Prior;
      while not DataSet.Bof do
      begin
        if SearchOptions.IsUpperLowercase then //区分大小写
          I := CompareStr(Field.AsString, SearchOptions.SearchValue)
        else
          I := CompareText(Field.AsString, SearchOptions.SearchValue);
        if I = 0 then
        begin
          Result := True;
          Break;
        end;
        DataSet.Prior;
      end;
    end;
    {
    if not Result then
      MessageDlg('Search String '+''''+SearchOptions.SearchValue+''''+' not found', mtInformation, [mbOK], 0);
    }
  finally
    DataSet.EnableControls;
    SearchOptions.IsFirst := False;
  end;
end;

procedure DbGridPrint(DBGrid : TDBGrid; const RptTitle : string;
    const LRptTitle : string; const RRptTitle:string;const RtpDateSpotTitle:string);
var
  Dialog : TfmPrintMode;
begin
  if (DBGrid.DataSource<>nil) and (DBGrid.DataSource.DataSet<>nil)
    and (DBGrid.DataSource.DataSet.Active) then
  begin
    Dialog := TfmPrintMode.Create(Application);
    DBGrid.DataSource.Dataset.DisableControls;
    try
      Dialog.Execute(dbGrid,RptTitle,LRptTitle,RRptTitle,RtpDateSpotTitle);
    finally
      DBGrid.DataSource.Dataset.EnableControls;
      Dialog.Free;
    end;
  end;
end;


procedure StringGridPrint(StringGrid : TStringGrid; const RptTitle : string;
    const LRptTitle : string; const RRptTitle:string;const RtpDateSpotTitle:string); //打印DbGrid   输出函数
var
  Dialog : TfmPrintMode;
begin
  if (StringGrid<>nil)  then
  begin
    Dialog := TfmPrintMode.Create(Application);
    //DBGrid.DataSource.Dataset.DisableControls;
    try
      Dialog.Execute(StringGrid,RptTitle,LRptTitle,RRptTitle,RtpDateSpotTitle);
    finally
      Dialog.Free;
    end;
  end;
end;



procedure DbListViewPrint(ListView:TListView;DataSet:TDataSet; const RptTitle : string;
    const LRptTitle : string; const RRptTitle:string;const RtpDateSpotTitle:string);
var
  Dialog : TfmPrintMode;
begin
  if (ListView<>nil) {and (DataSet<>nil) and (DataSet.Active)}then
  begin
    Dialog := TfmPrintMode.Create(Application);
    try
      Dialog.Execute(ListView,DataSet,RptTitle,LRptTitle,RRptTitle,RtpDateSpotTitle);
    finally
      Dialog.Free;
    end;
  end;
end;


procedure PrintReceipt(const BasedFileName : string; WorkView : TWorkView; AddDefaultSystemParams : Boolean=True);
var
  FileName : string;
  ReportInfo : TReportInfo;
  I : Integer;
  s:String;
begin
  //wsn 20050107 修改取日期函数后
  TryRefreshDates(s,False);

  //FileName := Context.GetDir(dkReport)+BasedFileName;
  FileName := GetReportFileName(BasedFileName);
  ReportInfo := TReportInfo.Create(Application);
  try
    ReportInfo.LoadFromFile(FileName);
    ReportInfo.CheckCreate;
    for I:=0 to WorkView.FieldCount-1 do
    with WorkView.Fields[I] do
    begin
      ReportInfo.SetVariantValue(Name,Data.AsString);
      //ReportInfo.VariantValues.Values[Name] := Data.AsString;
    end;

    if AddDefaultSystemParams then
    begin
      AddSystemParams(ReportInfo.VariantValues);
      with ReportInfo.VariantValues do
      begin
        Values['Date'] := GetToday; //FormatDateTime('yyyy/mm/dd',Now);
        Values['Date2'] := GetTodayStr; //FormatDateTime('yyyy/mm/dd',Now);
        Values['Time'] := FormatDateTime('hh:nn:ss',Now);
      end;
    end;

    if Context.GetConfigSystem.ReadBoolean(ccPrintReceipt,ckPreview,cdPreview) then
      ReportInfo.Preview else
      ReportInfo.Print;
  finally
    ReportInfo.Free;
  end;

end;

{
function  GetAggregateFields(WorkView : TWorkView; GroupIndex : Integer; Dataset : TDataset):Boolean;
var
  I : Integer;
  Field : TWVField;
  DataFieldName : string;
  AggregateField : THDBAggregateField;
  AggregateName : string;
begin
  Result := False;
  if (Dataset is THCustomDataset) and THCustomDataset(Dataset).Done then
  begin
    Result := True;
    WorkView.Reset(GroupIndex);
    for I:=0 to WorkView.FieldCount-1 do
    begin
      Field := WorkView.Fields[I];
      if (Field.GroupIndex=GroupIndex) or (GroupIndex=0) then
      begin
        AggregateName := Field.Feature;
        if SameText(AggregateName,'Count') then
        begin
          Field.Data.AsString := IntToStr(THCustomDataset(Dataset).CurrentRecordCount);
        end else
        begin
          DataFieldName := Field.DataField;
          if SameText(AggregateName,'SUM') then
            AggregateField := THCustomDataset(Dataset).AggregateField(DataFieldName,atSum)
          else if SameText(AggregateName,'MIN') then
            AggregateField := THCustomDataset(Dataset).AggregateField(DataFieldName,atMin)
          else if SameText(AggregateName,'MAX') then
            AggregateField := THCustomDataset(Dataset).AggregateField(DataFieldName,atMax)
          else
            AggregateField := nil;
          if AggregateField<>nil then
            Field.Data.AsString := AggregateField.AsString;
            //Field.Data.Value := AggregateField.Value;
        end;
      end;
    end;
  end;
end;
}
// 打印回单。根据配置确定是否打印回单，如果要打印，出现对话框，询问操作员，是否打印。返回是否打印
function  DoPrintReceipt(const AOperation : string; const BasedFileName : string; WorkView : TWorkView; AddDefaultSystemParams : Boolean=True):Boolean;
var
  AType : Integer;
begin
  AType := Context.GetConfigSystem.ReadInteger(ccPrintReceipt,AOperation,cdPrintReceipt);
  case AType of
    0 : Result := False;
    2 : Result := True;
  else
    // 1 : 
    Result := Context.GetDialogSystem.Confirm(SPrintReceiptPrompt)=uaYes;
  end;
  if Result then
    PrintReceipt(BasedFileName, WorkView, AddDefaultSystemParams);
end;

// 根据配置确定是否出现确认对话框。如果出现确认对话框，并且用户选择取消，返回False，否则返回True
function  DoPrompt(const AOperation, APrompt : string) : Boolean;
var
  ConfirmType : Integer;
begin
  ConfirmType := Context.GetConfigSystem.ReadInteger(ccConfirm,AOperation,cdConfirm);
  //WriteLog('Need Prompt:'+AOperation,lcKSClient);
  case ConfirmType of
    1 : Result := Context.GetDialogSystem.Confirm2(APrompt); // 特殊确认
    2 : Result := Context.GetDialogSystem.Confirm(APrompt)=uaYes; // 普通确认
  else
    // 0
    Result := True; // 不需要确认
  end;
end;

procedure DrawCellForSysParams(
  Grid : TDBGrid;
  const Rect: TRect;
  DataCol: Integer;
  Column: TColumn;
  State: TGridDrawState;
  const DepartFieldName : string);
var
  Dataset : TDataset;
begin
  if (State=[]) then
  begin
    if Grid.DataSource<>nil then
      Dataset := Grid.DataSource.Dataset else
      Dataset := nil;
    if (Dataset<>nil) and
      (DepartFieldName<>'') and
      (Dataset.FieldByName(DepartFieldName).AsString=CenterDepartNo) then
    begin
      Grid.Canvas.Brush.Color := clBtnFace;
    end;
  end;
  Grid.DefaultDrawColumnCell(Rect,DataCol,Column,State);
end;

function  GetPrinterInfoToLabel(ALabel : TLabel) : Boolean;
var
  PrinterInfo : TKSPrinterInfo;
  Orientation : string;
begin
  try
    GetPrinterInfo(PrinterInfo);
    if PrinterInfo.Orientation=poPortrait then
      Orientation := '纵向' else
      Orientation := '横向';
    ALabel.Caption := Format('%s %s %s',[PrinterInfo.Device, PrinterInfo.FormName, Orientation]);
    ALabel.ParentFont := True;
    Result := True;
  except
    ALabel.Caption := SNoPrinter;
    ALabel.Font.Color := clRed;
    Result := False;
  end;
end;


procedure DrawGridColumnCell(Grid : TDBGrid;const Rect: TRect;Column: TColumn;DataCol: Integer;State: TGridDrawState;IndexFieldName : string);
begin
    if (Grid.DataSource.DataSet.FieldByName(IndexFieldName).AsInteger mod 2) =1 then
      Grid.Canvas.Brush.Color := clInfoBk
      else Grid.Canvas.Brush.Color := $00F6F3EF;

    if (Column.Field is TIntegerField) or
       (Column.Field is TSmallIntField) or
       (Column.Field is TLargeIntField) or
       (Column.Field is TFloatField) or
       (Column.Field is TCurrencyField) or
       (Column.Field is TWordField) or
       (Column.Field is TBytesField) then
    begin
      if Column.Field.AsInteger<0 then
        Grid.Canvas.Font.Color := clRed
        else Grid.Canvas.Font.Color := clBlack;
    end
      else Grid.Canvas.Font.Color := clBlack;

   Grid.DefaultDrawColumnCell(Rect, DataCol, Column, State);
end;
end.
