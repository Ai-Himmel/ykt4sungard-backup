unit DBGrid2Excel;

interface

uses
  Windows, Variants, Classes, SysUtils, Forms, DB, DBGrids, ComObj;

type
  TUpAniInfoProc = procedure (const sInfo: string) of object;

  function DBGridToExcel(dgrSource: TDBGrid;
               UpAniInfo: TUpAniInfoProc = nil): Integer;

implementation

function DBGridToExcel(dgrSource: TDBGrid; UpAniInfo: TUpAniInfoProc): Integer;
const               //从DBGrid导出到Excel(2005.8.23改进至可以导入几乎无限的数据)
  MAX_SHEET_ROWS = 65536-1;  //Excel每Sheet最大行数
  MAX_VAR_ONCE   = 1000;     //一次导出的条数
var                          //返回导出记录条数
  MyExcel, varCells: Variant;
  MySheet, MyCells, Cell1, Cell2, Range: OleVariant;
  iRow, iCol, iSheetIdx, iVarCount, iCurRow: integer;
  CurPos: TBookmark;
begin
  dgrSource.DataSource.DataSet.DisableControls;
  CurPos  := dgrSource.DataSource.DataSet.GetBookmark;
  dgrSource.DataSource.DataSet.First;

  MyExcel := CreateOleObject('Excel.Application');
  MyExcel.WorkBooks.Add;
  MyExcel.Visible := False;

  if dgrSource.DataSource.DataSet.RecordCount <= MAX_VAR_ONCE then
    iVarCount := dgrSource.DataSource.DataSet.RecordCount
  else
    iVarCount := MAX_VAR_ONCE;
  varCells  := VarArrayCreate([1,
                               iVarCount,
                               1,
                               dgrSource.FieldCount], varVariant);
  iSheetIdx := 1;
  iRow      := 0;
  Result    := 0;
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
        if Assigned(UpAniInfo) then
          UpAniInfo(Format('(已导出%d条)', [Result])); //显示已导出条数
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
  MyExcel.WorkBooks[1].Saved := True;
  MyExcel  := Unassigned;
  if CurPos <> nil then
  begin
    dgrSource.DataSource.DataSet.GotoBookmark(CurPos);
    dgrSource.DataSource.DataSet.FreeBookmark(CurPos);
  end;
  dgrSource.DataSource.DataSet.EnableControls;
end;

end.
 