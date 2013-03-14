unit DBGrid2Excel;

interface

uses
  Windows, Variants, Classes, SysUtils, Forms, DB, DBGrids, ComObj,Math,Controls,
  Graphics, Dialogs, DBGridEh, ExtCtrls, ComCtrls;

type
  TWorkBeginEvent = procedure (Sender: TObject;
                     const AWorkCountMax: Integer) of object;
  TWorkEvent = procedure (Sender: TObject;
							const AWorkCount: Integer) of object;

  TDBGridToExcel = class(TComponent)
  private
    FMAX_VAR_ONCE: Integer;         //每次导入数
    FFileName: TFileName;              //要保存的文件名
    FRecordCount: Integer;          //记录数
    FWorkCount:Integer;             //导出数
    FAllCountHead: Boolean;         //是否要ColumnHead
    FName: Variant;
    FTitle:string;                  //导出标题
    FTitleFont:TFont;               //标题字体
    FTitleRow:Word;                 //标题行
    FTitleCol:Word;                 //标题列
    FDataBeginRow:Word;             //数据开始行
    FDataBeginCol:Word;             //数据开始列
    FxltName:TFileName;             //模板名称
    FxltNameV:Variant;
    FGrid:Boolean;                  //是否有网格
    FOnWorkBegin: TWorkBeginEvent;  //导出前事件
    FOnWork: TWorkEvent;            //导出时事件
    FOnWorkEnd: TNotifyEvent;       //导出后后事件
    FMergeTitle:Boolean;            //是否合并标题
    FHeadFont:TFont;                //数据头字体
    FDataFont:TFont;                //数据字体
    FDBGridEh:TDBGridEh;
    procedure SetMax_Var_Once(const Value: Integer);
    procedure SetFileName(const Value: TFileName);
    procedure SetxltName(const Value: TFileName);
    procedure SetGrid(const Value: Boolean);
    procedure SetTitleCol(const Value: Word);
    procedure SetTitleRow(const Value: Word);
    procedure SetDataBeginRow(const Value: Word);
    procedure SetTitle(const Value: string);
    procedure SetDataBeginCol(const Value: Word);
    procedure SetTitleFont(const Value: TFont);
    procedure SetMergeTitle(const Value: Boolean);
    procedure SetDataFont(const Value: TFont);
    procedure SetHeadFont(const Value: TFont);
  protected
    procedure DoWorkBegin;
    procedure DoWork;
    procedure DoWorkEnd;
  public
    pnlProg: TPanel;
    ProgBar: TProgressBar;
    frmParent: TForm;
    property RecordCount:Integer read FRecordCount;
    property AllCountHead:Boolean read FAllCountHead {write FAllCountHead default True};
    function DataSetToExcel(Ds:TDataSet):Integer;overload;
    function DataSetToExcel(Ds:TDataSet;FieldNameList:TStrings;FieldCaptionList:TStrings;FieldWidths:TStrings=nil):Integer;overload;
    function ExportToExcel(dgrSource:TDBGrid):Integer; overload;
    function ExportToExcel(dgrSource:TDBGridEh):Integer; overload;
    constructor Create(AOwner: TComponent);override;
    destructor Destroy;override;
  published
    property DataBeginCol:Word read FDataBeginCol write SetDataBeginCol;
    property MergeTitle:Boolean read FMergeTitle write SetMergeTitle;
    property DataBeginRow:Word read FDataBeginRow write SetDataBeginRow;
    property MAX_VAR_ONCE:Integer read FMAX_VAR_ONCE write SetMax_Var_Once default 1000;
    property FileName:TFileName read FFileName write SetFileName;
    property Grid:Boolean read FGrid write SetGrid;
    property Title:string read FTitle write SetTitle;
    property TitleFont:TFont read FTitleFont write SetTitleFont;
    property xltName:TFileName read FxltName write SetxltName;
    property TitleRow:Word read FTitleRow write SetTitleRow default 0;
    property TitleCol:Word read FTitleCol write SetTitleCol default 0;
    property DataFont:TFont read FDataFont write SetDataFont;
    property HeadFont:TFont read FHeadFont write SetHeadFont;
    property OnWorkBegin:TWorkBeginEvent read FOnWorkBegin write FOnWorkBegin;
    property OnWork:TWorkEvent read FOnWork write FOnWork;
    property OnWorkEnd:TNotifyEvent read FOnWorkEnd write FOnWorkEnd;
  end;

Type
  ExcelColumnCount = 1..256;
  ExcelRowCount = 1..65536;
  rExcelRangeCR = record
    Row1:ExcelColumnCount;
    Col1:ExcelRowCount;
    Row2:ExcelColumnCount;
    Col2:ExcelRowCount;
  end;

const
  ExcelColumnArray : array [ExcelColumnCount] of string=(
'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
'AA','AB','AC','AD','AE','AF','AG','AH','AI','AJ','AK','AL','AM','AN','AO','AP','AQ','AR','AS','AT','AU','AV','AW','AX','AY','AZ',
'BA','BB','BC','BD','BE','BF','BG','BH','BI','BJ','BK','BL','BM','BN','BO','BP','BQ','BR','BS','BT','BU','BV','BW','BX','BY','BZ',
'CA','CB','CC','CD','CE','CF','CG','CH','CI','CJ','CK','CL','CM','CN','CO','CP','CQ','CR','CS','CT','CU','CV','CW','CX','CY','CZ',
'DA','DB','DC','DD','DE','DF','DG','DH','DI','DJ','DK','DL','DM','DN','DO','DP','DQ','DR','DS','DT','DU','DV','DW','DX','DY','DZ',
'EA','EB','EC','ED','EE','EF','EG','EH','EI','EJ','EK','EL','EM','EN','EO','EP','EQ','ER','ES','ET','EU','EV','EW','EX','EY','EZ',
'FA','FB','FC','FD','FE','FF','FG','FH','FI','FJ','FK','FL','FM','FN','FO','FP','FQ','FR','FS','FT','FU','FV','FW','FX','FY','FZ',
'GA','GB','GC','GD','GE','GF','GG','GH','GI','GJ','GK','GL','GM','GN','GO','GP','GQ','GR','GS','GT','GU','GV','GW','GX','GY','GZ',
'HA','HB','HC','HD','HE','HF','HG','HH','HI','HJ','HK','HL','HM','HN','HO','HP','HQ','HR','HS','HT','HU','HV','HW','HX','HY','HZ',
'IA','IB','IC','ID','IE','IF','IG','IH','II','IJ','IK','IL','IM','IN','IO','IP','IQ','IR','IS','IT','IU','IV');


function ExcelCells(Row:ExcelRowCount;Col:ExcelColumnCount):string;
function ExcelRange(Row1:ExcelRowCount;Col1:ExcelColumnCount;
  Row2:ExcelRowCount;Col2:ExcelColumnCount):string;
function GetExcelRangeCR(Range:Variant):rExcelRangeCR;

function DBGridToExcel(dgrSource: TDBGrid;FileName:string='';
               UpAniInfo: TWorkEvent = nil): Integer;

function StrCount(SubStr,SourceStr: String):Integer;

procedure Register;

implementation

const
  MAX_SHEET_ROWS = 65535;  //Excel每Sheet最大行数

function StrCount(SubStr,SourceStr: String):Integer;
begin
  Result := 0;
  while Pos(SubStr,SourceStr)>0 do
  begin
    Inc(Result);
    SourceStr := Copy(SourceStr,Pos(SubStr,SourceStr)+1,Length(SourceStr));
  end;
end;

function ExcelCells(Row:ExcelRowCount;Col:ExcelColumnCount):string;
begin
  Result:=ExcelColumnArray[Col]+IntToStr(Row);
end;

function ExcelRange(Row1:ExcelRowCount;Col1:ExcelColumnCount;
  Row2:ExcelRowCount;Col2:ExcelColumnCount):string;
begin
  Result:=ExcelCells(Row1,Col1)+':'+ExcelCells(Row2,Col2);
end;

function GetExcelRangeCR(Range:Variant):rExcelRangeCR;
var
  ExcelRangCR:rExcelRangeCR;
begin
  ExcelRangCR.Row1:=Range.Row;
  ExcelRangCR.Col1:=Range.Column;
  ExcelRangCR.Row2:=Range.Rows.Count+ExcelRangCR.Row1-1;
  ExcelRangCR.Col2:=Range.Columns.Count+ExcelRangCR.Col1-1;
  Result:=ExcelRangCR;
end;


function DBGridToExcel(dgrSource: TDBGrid; FileName:string='';UpAniInfo: TWorkEvent=nil): Integer;
//返回导出记录条数
const               //从DBGrid导出到Excel(2005.8.23改进至可以导入几乎无限的数据)
  MAX_SHEET_ROWS = 65536-1;  //Excel每Sheet最大行数
  MAX_VAR_ONCE   = 1000;     //一次导出的条数
var
  MyExcel, varCells,FName: Variant;
  MySheet, MyCells, Cell1, Cell2, Range: OleVariant;
  iRow, iCol, iSheetIdx, iVarCount, iCurRow: integer;
  CurPos: TBookmarkStr;
begin
  dgrSource.DataSource.DataSet.DisableControls;   //导出时不显示滚动情况
  CurPos  := dgrSource.DataSource.DataSet.Bookmark; //设置书签
  dgrSource.DataSource.DataSet.First;

  try
    MyExcel := CreateOleObject('Excel.Application'); //启动Excel
  except
    Application.MessageBox('没有安装Excel！','错误',MB_OK+MB_ICONERROR);
    Result:=0;
    Exit;
  end;

  MyExcel.WorkBooks.Add;
  MyExcel.Visible := False;

  if dgrSource.DataSource.DataSet.RecordCount <= MAX_VAR_ONCE then
    iVarCount := dgrSource.DataSource.DataSet.RecordCount
  else
    iVarCount := MAX_VAR_ONCE;                     //设置每次导入数据行数

  //创建一个二维数组varCells
  varCells  := VarArrayCreate([1,iVarCount,1,dgrSource.FieldCount], varVariant);
  iSheetIdx := 1; //Sheet序列
  iRow      := 0; //行数
  Result    := 0; //导出数
  while not dgrSource.DataSource.DataSet.Eof do
  begin
    if (iRow = 0) or (iRow > MAX_SHEET_ROWS + 1) then
    begin                  //新增一个Sheet
      if iSheetIdx <= MyExcel.WorkBooks[1].WorkSheets.Count then
        MySheet := MyExcel.WorkBooks[1].WorkSheets[iSheetIdx]
      else
        MySheet := MyExcel.WorkBooks[1].WorkSheets.Add(NULL, MySheet);//加在后面
      MyCells := MySheet.Cells;
      Inc(iSheetIdx);
      iRow := 1;

      for iCol := 1 to dgrSource.FieldCount do
      begin
        MySheet.Cells[1, iCol] := dgrSource.Fields[iCol-1].DisplayName;
        MySheet.Cells[1, iCol].Font.Bold := True;
        {MySheet.Select;
        MySheet.Cells[iRow,iCol].Select;
        MyExcel.Selection.Font.Bold := true;}//这种方法也可(Sheet.Select不可少)
        if dgrSource.Fields[iCol-1].DisplayWidth>255 then
          MySheet.Columns[iCol].ColumnWidth := 255
        else
          MySheet.Columns[iCol].ColumnWidth := dgrSource.Fields[iCol-1].DisplayWidth;
        if (dgrSource.Fields[iCol - 1].DataType = ftString)
           or (dgrSource.Fields[iCol - 1].DataType = ftWideString) then
        begin           //对于“字符串”型数据则设Excel单元格为“文本”型
          MySheet.Columns[iCol].NumberFormatLocal := '@';
        end;
      end;
      Inc(iRow);
    end;
    iCurRow := 1;
    while not dgrSource.DataSource.DataSet.Eof do
    begin
      for iCol := 1 to dgrSource.FieldCount do
      begin
        varCells[iCurRow, iCol] := dgrSource.Fields[iCol-1].AsString;
      end;
      Inc(iRow);
      Inc(iCurRow);
      Inc(Result);
      dgrSource.DataSource.DataSet.Next;
      if (iCurRow > iVarCount) or (iRow > MAX_SHEET_ROWS + 1) then
      begin
//        if Assigned(UpAniInfo) then
//          UpAniInfo(Format('(已导出%d条)', [Result])); //显示已导出条数
        Application.ProcessMessages;
        Break;
      end;
    end;
    Cell1 := MyCells.Item[iRow - iCurRow + 1, 1];
    Cell2 := MyCells.Item[iRow - 1,
                          dgrSource.FieldCount];
    Range := MySheet.Range[Cell1 ,Cell2];
    Range.Value := varCells;
    if (iRow > MAX_SHEET_ROWS + 1) then     //一个Sheet导出结束
    begin
      MySheet.Select;
      MySheet.Cells[1, 1].Select;    //使得每一Sheet均定位在第一格
    end;
    Cell1    := Unassigned;
    Cell2    := Unassigned;
    Range    := Unassigned;

  end;

  MyCells  := Unassigned;
  varCells := Unassigned;
  MyExcel.WorkBooks[1].WorkSheets[1].Select;   //必须先选Sheet  2005.8.23
  MyExcel.WorkBooks[1].WorkSheets[1].Cells[1,1].Select;
  MyExcel.Visible := True;
  if FileName<>'' then
  begin
    FName:=FileName;
    try
      MyExcel.WorkBooks[1].SaveAs(FName);
      MyExcel.WorkBooks[1].Saved := True;
      MyExcel  := Unassigned;
    except
      Application.MessageBox('路径不存在或者文件不可写(其它程序已经打开了此文件！)','错误',MB_OK+MB_ICONERROR);
    end;
  end;
  if CurPos <> '' then
  begin
    dgrSource.DataSource.DataSet.Bookmark:=CurPos;
//    dgrSource.DataSource.DataSet.FreeBookmark(CurPos);
  end;
  dgrSource.DataSource.DataSet.EnableControls;
end;

{ TDBGridToExcel }

constructor TDBGridToExcel.Create(AOwner: TComponent);
begin
  inherited;
  FMAX_VAR_ONCE:=1000;
  FAllCountHead:=True;
  FDataBeginRow:=1;
  FDataBeginCol:=1;
  FTitleFont:=TFont.Create;
  FHeadFont:=TFont.Create;
  FDataFont:=TFont.Create;
  if (AOwner<>nil) and (AOwner is TWinControl) then
  begin
    pnlProg := TPanel.Create(self);
    ProgBar := TProgressBar.Create(self);
    pnlProg.Visible := False;
    pnlProg.Width := 200;
    pnlProg.Height := 30;
    ProgBar.Width := 180;
    ProgBar.Height := 10;
    ProgBar.Top := 10;
    ProgBar.Left := 10;
    pnlProg.Top := Round((TWinControl(AOwner).Height-pnlProg.Height)/2);
    pnlProg.Left := Round((TWinControl(AOwner).Width-pnlProg.Width)/2);
    ProgBar.Parent := pnlProg;
    pnlProg.Parent := TWinControl(AOwner);
  end;
end;

function TDBGridToExcel.DataSetToExcel(Ds: TDataSet): Integer;
var
  i:Integer;
  S1,S2:TStringList;
begin
  S1:=TStringList.Create;
  S2:=TStringList.Create;
  try
    for I:=0 to Ds.FieldCount-1 do
    begin
      S1.Add(ds.Fields[I].FieldName);
      S2.Add(ds.Fields[I].DisplayLabel);
    end;
    Result:=DataSetToExcel(Ds,S1,S2);
  finally
    S1.Free;
    S2.Free;
  end;
end;

function TDBGridToExcel.DataSetToExcel(Ds: TDataSet; FieldNameList,
  FieldCaptionList: TStrings;FieldWidths:TStrings=nil): Integer;
var
  FMyExcel: Variant;
  FWorkBooks: Variant;
  varCells: Variant;
  MySheet, MyCells, Cell1, Cell2, Range: OleVariant;
  iRow, iCol, iSheetIdx, iVarCount, iCurRow: integer;
  CurPos: TBookmarkStr;
  Rs:string;

  procedure SetGridHead;
  var
    iCol:Integer;
    i,iTitleRows: Integer;
    strS,strS1,strS2:string;
  begin
    if (FTitle<>'')and(FTitleRow>0)and(FTitleCol>0) then
    begin
      MySheet.Cells[FTitleRow,FTitleCol] := FTitle;
      if FMergeTitle then
      begin
        Rs:=ExcelRange(1,FDataBeginCol,FTitleRow,FDataBeginCol+FieldNameList.Count-1);
        MySheet.Range[Rs].Font.Bold:=(fsBold in FTitleFont.Style);
        MySheet.Range[Rs].Font.Color:=FTitleFont.Color;
        MySheet.Range[Rs].Font.Italic:=(fsItalic in FTitleFont.Style);
        MySheet.Range[Rs].Font.Name:=FTitleFont.Name;
        MySheet.Range[Rs].Font.Size:=FTitleFont.Size;
        MySheet.Range[Rs].Font.Strikethrough:=(fsStrikeOut in FTitleFont.Style);
        MySheet.Range[Rs].Font.Underline:=(fsUnderline in FTitleFont.Style);
        MySheet.Range[Rs].Merge;
        MySheet.Range[Rs].HorizontalAlignment:=4294963188;
        MySheet.Range[Rs].VerticalAlignment:=4294963188;
      end;
    end;
    //DBGridTitle
    //计算多列头的行数
    iTitleRows := 1;
    for iCol := 0 to FieldNameList.Count-1 do
    begin
      if (StrCount('|',FieldCaptionList[iCol])+1)>iTitleRows then
      begin
        iTitleRows := StrCount('|',FieldCaptionList[iCol])+1;
      end;
    end;
    iRow := iRow + iTitleRows - 1;
    for iCol := 0 to FieldNameList.Count-1 do
    begin
      if AllCountHead then
      begin
        //处理多列头
        strS := FieldCaptionList[iCol];
        for i := 0 to iTitleRows - 1 do
        begin
          if Pos('|',strS) <= 0 then
            MySheet.Cells[FDataBeginRow+i, iCol+FDataBeginCol] := strS
          else
          begin
            MySheet.Cells[FDataBeginRow+i, iCol+FDataBeginCol] := Copy(strS,1,Pos('|',strS)-1);
            strS := Copy(strS,Pos('|',strS)+1,Length(strS));
          end;
          if iCol>0 then
          begin
            strS1 := MySheet.Cells[FDataBeginRow+i, iCol+FDataBeginCol-1];
            strS2 := MySheet.Cells[FDataBeginRow+i, iCol+FDataBeginCol];
            if strS1=strS2 then
            begin
              MySheet.Cells[FDataBeginRow+i, iCol+FDataBeginCol] := '';
              Rs:=ExcelRange(FDataBeginRow+i, iCol+FDataBeginCol-1,FDataBeginRow+i, iCol+FDataBeginCol);
              MySheet.Range[Rs].Merge;
              MySheet.Range[Rs].HorizontalAlignment:=4294963188;
              MySheet.Range[Rs].VerticalAlignment:=4294963188;
            end
            else
            begin
              strS1 := MySheet.Cells[FDataBeginRow, iCol+FDataBeginCol];
              strS2 := MySheet.Cells[FDataBeginRow+i, iCol+FDataBeginCol];
              if (i>0) and (strS1=strS2) then
              begin
                MySheet.Cells[FDataBeginRow+i, iCol+FDataBeginCol] := '';
                Rs:=ExcelRange(FDataBeginRow,iCol+FDataBeginCol,FDataBeginRow+i,iCol+FDataBeginCol);
                MySheet.Range[Rs].Merge;
                MySheet.Range[Rs].HorizontalAlignment:=4294963188;
                MySheet.Range[Rs].VerticalAlignment:=4294963188;
              end;
            end;
          end
          else
          begin
            strS1 := MySheet.Cells[FDataBeginRow, iCol+FDataBeginCol];
            strS2 := MySheet.Cells[FDataBeginRow+i, iCol+FDataBeginCol];
            if (i>0) and (strS1=strS2) then
            begin
              MySheet.Cells[FDataBeginRow+i, iCol+FDataBeginCol] := '';
              Rs:=ExcelRange(FDataBeginRow,iCol+FDataBeginCol,FDataBeginRow+i,iCol+FDataBeginCol);
              MySheet.Range[Rs].Merge;
              MySheet.Range[Rs].HorizontalAlignment:=4294963188;
              MySheet.Range[Rs].VerticalAlignment:=4294963188;
            end;
          end;
        end;
      end;
      if FieldWidths=nil then
      begin
        MySheet.Columns[iCol+FDataBeginCol].ColumnWidth :=Min(Ds.FieldByName(FieldNameList[iCol]).DisplayWidth,255);
      end
      else begin
        try
          MySheet.Columns[iCol+FDataBeginCol].ColumnWidth :=Min(StrToInt(FieldWidths[iCol]),255);
        except
          MySheet.Columns[iCol+FDataBeginCol].ColumnWidth :=Min(Ds.FieldByName(FieldNameList[iCol]).DisplayWidth,255);
        end;
      end;
      if (Ds.FieldByName(FieldNameList[iCol]).DataType = ftString)
         or (Ds.FieldByName(FieldNameList[iCol]).DataType = ftWideString) then
      begin           //对于“字符串”型数据则设Excel单元格为“文本”型
        MySheet.Columns[iCol+FDataBeginCol].NumberFormatLocal := '@';
      end;
    end;

    Rs:=ExcelRange(FDataBeginRow,FDataBeginCol,FDataBeginRow+(iTitleRows-1),FDataBeginCol+FieldNameList.Count-1);

    MySheet.Range[Rs].Font.Bold:=(fsBold in FHeadFont.Style);
    MySheet.Range[Rs].Font.Color:=FHeadFont.Color;
    MySheet.Range[Rs].Font.Italic:=(fsItalic in FHeadFont.Style);
    MySheet.Range[Rs].Font.Name:=FHeadFont.Name;
    MySheet.Range[Rs].Font.Size:=FHeadFont.Size;
    MySheet.Range[Rs].Font.Strikethrough:=(fsStrikeOut in FHeadFont.Style);
    MySheet.Range[Rs].Font.Underline:=(fsUnderline in FHeadFont.Style);

    if FGrid then
    begin
      MySheet.Range[Rs].Borders[7].LineStyle:=1;
      MySheet.Range[Rs].Borders[8].LineStyle:=1;
      MySheet.Range[Rs].Borders[9].LineStyle:=1;
      MySheet.Range[Rs].Borders[10].LineStyle:=1;
      if FieldNameList.Count>1 then
        MySheet.Range[Rs].Borders[11].LineStyle:=1;
      if iTitleRows>1 then
        MySheet.Range[Rs].Borders[12].LineStyle:=1;
    end;

  end;

begin
  if (not Ds.Active)or (Ds.RecordCount=0) then
  begin
    Result:=0;
    Exit;
  end;

  if FieldNameList.Count+FDataBeginCol-1>255 then
  begin
    Application.MessageBox('字段太多或者字段开始行太大','错误',MB_OK+MB_ICONERROR);
    FWorkCount:=0;
    Result:=0;
    Exit;
  end;

  FRecordCount:=Ds.RecordCount;
  if ProgBar<>nil then
  begin
    pnlProg.Visible := True;
    ProgBar.Max := FRecordCount;
  end;
  if Assigned(FOnWorkBegin) then
    DoWorkBegin;

  try
    FMyExcel := CreateOleObject('Excel.Application'); //启动Excel
  except
    Application.MessageBox('没有安装Excel！','错误',MB_OK+MB_ICONERROR);
    FMyExcel:=Null;
    Result:=0;
    Exit;
  end;

  FMyExcel.Visible := False;

  Ds.DisableControls;   //导出时不显示滚动情况
  try
	  CurPos := Ds.Bookmark; //设置书签
    Ds.First;

    if (FxltName<>'')and(FileExists(FxltName)) then
    begin
      try
        FWorkBooks:=FMyExcel.WorkBooks.Add(FxltNameV); //添加一个WorkBook
      except
        FWorkBooks:=FMyExcel.WorkBooks.Add; //添加一个WorkBook
      end;
    end
    else
      FWorkBooks:=FMyExcel.WorkBooks.Add; //添加一个WorkBook


    //设置每次导入数据行数
    if Ds.RecordCount <= MAX_VAR_ONCE then
      iVarCount := Ds.RecordCount
    else
      iVarCount := MAX_VAR_ONCE;

    //创建一个二维数组varCells
    varCells  := VarArrayCreate([1,iVarCount,1,FieldNameList.Count], varVariant);

    //初始化
    iSheetIdx := 1; //Sheet序列
    iRow      := 0; //行数
//    iRow      := FDataBeginRow-1; //行数
    FWorkCount:= 0;  //导出数

    //开始导数
    while not Ds.Eof do
    begin
//      if (iRow = 0) or (iRow > MAX_SHEET_ROWS + 1) then
      if (iRow = 0) or (iRow > MAX_SHEET_ROWS + 1) then
      begin                  //新增一个Sheet
        if iSheetIdx <= FWorkBooks.WorkSheets.Count then
          MySheet := FWorkBooks.WorkSheets[iSheetIdx]
        else
          MySheet := FWorkBooks.WorkSheets.Add(NULL, MySheet);//加在后面
        MyCells := MySheet.Cells;
        Inc(iSheetIdx);
        iRow := FDataBeginRow;
        //设置数据头
  		  SetGridHead;
        Inc(iRow);
      end;
      iCurRow := 1;
      while not Ds.Eof do
      begin
        for iCol := 0 to FieldNameList.Count-1 do
        begin
          if not DS.FieldByName(FieldNameList[iCol]).IsNull then
          begin
            if DS.FieldByName(FieldNameList[iCol]).DataType=ftDateTime then
              varCells[iCurRow, iCol+1] := FormatDateTime(TDateTimeField(DS.FieldByName(FieldNameList[iCol])).DisplayFormat, DS.FieldByName(FieldNameList[iCol]).AsDateTime)
            else
              varCells[iCurRow, iCol+1] := DS.FieldByName(FieldNameList[iCol]).AsString;
          end;
        end;
        Inc(iRow);
        Inc(iCurRow);
        Inc(FWorkCount);
        Ds.Next;
        if ProgBar<>nil then
          ProgBar.Position := FWorkCount;
        if Assigned(FOnWork) then
          DoWork;
        Application.ProcessMessages;
        if (iCurRow > iVarCount) or (iRow > MAX_SHEET_ROWS + 1) then
        begin
          Break;
        end;
      end;
      Cell1 := MyCells.Item[iRow - iCurRow + 1, FDataBeginCol];
      Cell2 := MyCells.Item[iRow - 1,FieldNameList.Count+FDataBeginCol-1];
      Range := MySheet.Range[Cell1 ,Cell2];
      Range.Value := varCells;

      Range.Font.Bold:=(fsBold in FDataFont.Style);
      Range.Font.Color:=FDataFont.Color;
      Range.Font.Italic:=(fsItalic in FDataFont.Style);
      Range.Font.Name:=FDataFont.Name;
      Range.Font.Size:=FDataFont.Size;
      Range.Font.Strikethrough:=(fsStrikeOut in FDataFont.Style);
      Range.Font.Underline:=(fsUnderline in FDataFont.Style);

      if FGrid then
      begin
        Range.Borders[7].LineStyle:=1;
        Range.Borders[8].LineStyle:=1;
        Range.Borders[9].LineStyle:=1;
        Range.Borders[10].LineStyle:=1;
        try
          if FieldNameList.Count>1 then
            Range.Borders[11].LineStyle:=1;
        except
        end;
        try
          if iCurRow>2 then
            Range.Borders[12].LineStyle:=1;
        except
        end;
      end;
      if (iRow > MAX_SHEET_ROWS + 1) then     //一个Sheet导出结束
      begin
        MySheet.Select;
        MySheet.Cells[1, 1].Select;    //使得每一Sheet均定位在第一格
      end;
      Cell1    := Unassigned;
      Cell2    := Unassigned;
      Range    := Unassigned;
    end;//结束

    MyCells  := Unassigned;
    varCells := Unassigned;
    FWorkBooks.WorkSheets[1].Select;   //必须先选Sheet  2005.8.23
    FWorkBooks.WorkSheets[1].Cells[1,1].Select;
    //设置打印时自动缩放为一张纸
    FMyExcel.ActiveSheet.PageSetup.Zoom := False;
    FMyExcel.ActiveSheet.PageSetup.FitToPagesWide := 1;
//  FMyExcel.ActiveSheet.PageSetup.FitToPagesTall = 1;
    FMyExcel.Visible := True;
    if FFileName<>'' then
    begin
      try
        FWorkBooks.SaveAs(FName);
        FWorkBooks.Saved := True;
      except
        Application.MessageBox('路径不存在或者文件不可写(其它程序已经打开了此文件！)','错误',MB_OK+MB_ICONERROR);
      end;
    end;
  finally
    FMyExcel  := Unassigned;
    Result    := FWorkCount;
    Ds.EnableControls;
	 if CurPos <> '' then
      Ds.Bookmark:=CurPos;
  end;
  if ProgBar<>nil then
  begin
    pnlProg.Visible := False;
  end;
  if Assigned(FOnWorkEnd) then
    DoWorkEnd;
end;

destructor TDBGridToExcel.Destroy;
begin
  inherited;
  FTitleFont.Free;
  FHeadFont.Free;
  FDataFont.Free;
end;

procedure TDBGridToExcel.DoWork;
begin
  if Assigned(OnWork) then
    FOnWork(Self,FWorkCount);
end;

procedure TDBGridToExcel.DoWorkBegin;
begin
  if Assigned(OnWorkBegin) then
    FOnWorkBegin(Self,FRecordCount);
end;

procedure TDBGridToExcel.DoWorkEnd;
begin
  if Assigned(OnWorkEnd) then
    FOnWorkEnd(Self);
end;

function TDBGridToExcel.ExportToExcel(dgrSource: TDBGrid): Integer;
var
  i:Integer;
  S1,S2,S3:TStringList;
begin
  FDBGridEh := nil;
  S1:=TStringList.Create;
  S2:=TStringList.Create;
  S3:=TStringList.Create;
  try
    for I:=0 to dgrSource.FieldCount-1 do
    begin
      if dgrSource.Columns[I].Visible and (dgrSource.Columns[I].FieldName<>'') then
      begin
        S1.Add(dgrSource.Columns[I].FieldName);
        S2.Add(dgrSource.Columns[I].Title.Caption);
        S3.Add(IntToStr(dgrSource.Columns[I].Width div 7));
      end;
    end;
    Result:=DataSetToExcel(dgrSource.DataSource.DataSet,S1,S2,S3);
  finally
    S1.Free;
    S2.Free;
    S3.Free;
  end;
end;

function TDBGridToExcel.ExportToExcel(dgrSource: TDBGridEh): Integer;
var
  i:Integer;
  S1,S2,S3:TStringList;
begin
  FDBGridEh := dgrSource;
  S1:=TStringList.Create;
  S2:=TStringList.Create;
  S3:=TStringList.Create;
  try
    for I:=0 to dgrSource.FieldCount-1 do
    begin
      if dgrSource.Columns[I].Visible and (dgrSource.Columns[I].FieldName<>'') then
      begin
        S1.Add(dgrSource.Columns[I].FieldName);
        S2.Add(dgrSource.Columns[I].Title.Caption);
        S3.Add(IntToStr(dgrSource.Columns[I].Width div 7));
      end;
    end;
    Result:=DataSetToExcel(dgrSource.DataSource.DataSet,S1,S2,S3);
  finally
    S1.Free;
    S2.Free;
    S3.Free;
  end;
end;

procedure TDBGridToExcel.SetDataBeginCol(const Value: Word);
begin
  if Value<=0 then
    FDataBeginCol:=1
  else if Value>255 then
    FDataBeginCol:=255
  else
    FDataBeginCol := Value;
end;

procedure TDBGridToExcel.SetDataBeginRow(const Value: Word);
begin
  if FTitleRow=0 then
  begin
    if Value<1 then
      FDataBeginRow:=1
    else FDataBeginRow:=Value;
  end
  else begin
    if Value<=FTitleRow then
      FDataBeginRow:=FTitleRow+2
    else FDataBeginRow:=Value;
  end;
end;

procedure TDBGridToExcel.SetxltName(const Value: TFileName);
begin
  FxltName:=Value;
  FxltNameV:=Value;
end;

procedure TDBGridToExcel.SetFileName(const Value: TFileName);
begin
  FFileName := Value;
  FName:= Value;
end;

procedure TDBGridToExcel.SetGrid(const Value: Boolean);
begin
  FGrid := Value;
end;

procedure TDBGridToExcel.SetMax_Var_Once(const Value: Integer);
begin
  if (Value>5000)or(Value<100) then
    FMAX_VAR_ONCE:=1000
  else FMAX_VAR_ONCE := Value;
end;

procedure Register;
begin
  RegisterComponents('Ehlib',[TDBGridToExcel]);
end;

procedure TDBGridToExcel.SetTitle(const Value: string);
begin
  FTitle := Value;
  if Value='' then
  begin
    FTitleRow:=0;
    FTitleCol:=0;
    FDataBeginRow:=1;
  end
  else begin
    if FTitleRow=0 then
      TitleRow:=1;
    if FTitleCol=0 then
      FTitleCol:=1;
  end;
end;

procedure TDBGridToExcel.SetTitleCol(const Value: Word);
begin
  if FTitle<>'' then
  begin
    if Value>255 then
      FTitleCol:=1
    else if Value<1 then
      FTitleCol:=1
    else
      FTitleCol := Value;
  end
  else begin
    FTitleCol:=0;
  end;
end;

procedure TDBGridToExcel.SetTitleFont(const Value: TFont);
begin
  FTitleFont.Assign(Value);
end;

procedure TDBGridToExcel.SetTitleRow(const Value: Word);
begin
  if FTitle<>'' then
  begin
    FTitleRow:=Min(65533,Value);
    if FTitleRow=0 then
      FTitleRow:=1;
    if FDataBeginRow<=FTitleRow then
      FDataBeginRow:=FTitleRow+2;
  end
  else begin
    FTitleRow:=0;
    if FDataBeginRow=0 then
      FDataBeginRow:=1;
  end;
end;

procedure TDBGridToExcel.SetMergeTitle(const Value: Boolean);
begin
  FMergeTitle := Value;
end;

procedure TDBGridToExcel.SetDataFont(const Value: TFont);
begin
  FDataFont.Assign(Value);
end;

procedure TDBGridToExcel.SetHeadFont(const Value: TFont);
begin
  FHeadFont.Assign(Value);
end;

end.
