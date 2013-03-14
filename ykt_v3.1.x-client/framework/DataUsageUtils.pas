unit DataUsageUtils;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>DataUsageUtils
   <What>�������ݡ��������ݵĹ�������
   ��Щ����������������Դ���ʡ�
   <Written By> Huang YanLai (������)���Զ�����������
   <History>
**********************************************}


interface

uses Windows, SysUtils, Classes, Graphics, Controls, Forms, Db, Grids, DBGrids, WorkViews, StdCtrls
     ,comctrls,Dialogs,RzListVw;

{
  �޸���zdb�ĳ���
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

{//wsn 20041013 ����������Զ����ѯ
function IsSearchSmartDataset(Grid : TDBGrid;  var SearchOptions : TDataSearchOptions):Boolean; overload;
//wsn 20041013 ����������Զ����ѯ
function IsSearchSmartDataset(DataSet : TDataSet;  var SearchOptions : TDataSearchOptions):Boolean; overload;
 }
function  SearchDataset(DataSet: TDataSet; var SearchOptions : TDataSearchOptions):Boolean;

{
  �޸���zcn�ĳ���
}

//  ������������̣��б�
//     PrintDBGrid(dbGrid:TDBGrid;Title:String); ��ӡDbGrid�е�����
//        ���� dbGrid:dbGrid  Title:����ı���
//
//     PrintToText(DbGrid:TDbGrid;RptTitle,FileName:String);��ӡDbGrid�����ݵ��ı�
//        ���� dbGrid:dbGrid  RptTitle:����ı���  FileName:���浽���ļ���


procedure DbGridPrint(DBGrid : TDBGrid; const RptTitle : string;
    const LRptTitle : string; const RRptTitle:string;
    const RtpDateSpotTitle:string); //��ӡDbGrid   �������

procedure DbListViewPrint(ListView:TListView;DataSet:TDataSet; const RptTitle : string;
    const LRptTitle : string; const RRptTitle:string;const RtpDateSpotTitle:string);  //��ӡListView �������

procedure StringGridPrint(StringGrid : TStringGrid; const RptTitle : string;
    const LRptTitle : string; const RRptTitle:string;const RtpDateSpotTitle:string); //��ӡDbGrid   �������


// ��ӡ�ص�
procedure PrintReceipt(const BasedFileName : string; WorkView : TWorkView; AddDefaultSystemParams : Boolean=True);

// ��ӡ�ص�����������ȷ���Ƿ��ӡ�ص������Ҫ��ӡ�����ֶԻ���ѯ�ʲ���Ա���Ƿ��ӡ�������Ƿ��ӡ
function  DoPrintReceipt(const AOperation : string; const BasedFileName : string; WorkView : TWorkView; AddDefaultSystemParams : Boolean=True):Boolean;

// ��������ȷ���Ƿ����ȷ�϶Ի����������ȷ�϶Ի��򣬲����û�ѡ��ȡ��������False�����򷵻�True
function  DoPrompt(const AOperation, APrompt : string) : Boolean;



// ����Զ����ܵ�����
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
  <What>����ǰ��ӡ����Ϣ��䵽��ǩ����
  ���û�а�װ��ӡ�����ڱ�ǩ������ʾ������Ϣ
  <Params>
    -
  <Return>
  �Ƿ�װ�˴�ӡ��
  <Exception>
}

function  GetPrinterInfoToLabel(ALabel : TLabel) : Boolean;

//add by cgm
//���������ֶε�ֵ����DBGRID��������ɫ
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
      // �ð汾���������ļ���������DBGrid��Columns
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
      
      // �ð汾���������ļ���������Column��˳�򡢿�ȡ���ɫ�����޸ı�����ֶ�����
      // ������Ϊ�����ļ��Ĵ���Ӱ������DBGrid
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
    if SearchOptions.IsForward then  //��ǰ��Ѱ
    begin
      if not SearchOptions.IsFirst then
        DataSet.Next;
      while not DataSet.Eof do
      begin
        if SearchOptions.IsUpperLowercase then //���ִ�Сд
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
    else                             //�����Ѱ
    begin
      if not SearchOptions.IsFirst then
        DataSet.Prior;
      while not DataSet.Bof do
      begin
        if SearchOptions.IsUpperLowercase then //���ִ�Сд
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
    const LRptTitle : string; const RRptTitle:string;const RtpDateSpotTitle:string); //��ӡDbGrid   �������
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
  //wsn 20050107 �޸�ȡ���ں�����
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
// ��ӡ�ص�����������ȷ���Ƿ��ӡ�ص������Ҫ��ӡ�����ֶԻ���ѯ�ʲ���Ա���Ƿ��ӡ�������Ƿ��ӡ
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

// ��������ȷ���Ƿ����ȷ�϶Ի����������ȷ�϶Ի��򣬲����û�ѡ��ȡ��������False�����򷵻�True
function  DoPrompt(const AOperation, APrompt : string) : Boolean;
var
  ConfirmType : Integer;
begin
  ConfirmType := Context.GetConfigSystem.ReadInteger(ccConfirm,AOperation,cdConfirm);
  //WriteLog('Need Prompt:'+AOperation,lcKSClient);
  case ConfirmType of
    1 : Result := Context.GetDialogSystem.Confirm2(APrompt); // ����ȷ��
    2 : Result := Context.GetDialogSystem.Confirm(APrompt)=uaYes; // ��ͨȷ��
  else
    // 0
    Result := True; // ����Ҫȷ��
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
      Orientation := '����' else
      Orientation := '����';
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
