unit AutoGridShow;

interface
uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Dialogs,
    KSFrameWorks,WorkViews,KSClientConsts,Db, WVCmdReq,RzDBGrid;

  procedure autoShowGrid(wv:TWorkView;grid:TRzDBGrid);
  
implementation
procedure autoShowGrid(wv:TWorkView;grid:TRzDBGrid);
var
  tempDataSet:TDataSet;
  //功能号
  //funcId : string;
  //字段名称
  fieldName:string;
  //显示名称
  showName :string;
  //是否显示
  ifshow:string;
  //显示顺序号
  //showId:Integer;
  //表格宽度
  gridWidth:Integer;
  //表头对齐方式
  titAlign:Integer;
  //表头字体
  titFont:string;
  //表头字体大小
  titFontSize:Integer;
  //表头字体颜色
  titFontColor:string;
  //表格对齐方式
  gridAlign:Integer;
  //表格字体
  gridFont:string;
  //表格字体大小
  gridFontSize:Integer;
  //表格字体颜色
  gridFontColor:string;

  i:Integer;
begin
  i:=0;
  tempDataSet := TDataSet(wv.FieldByName('查询结果集').Data.AsObject);
  grid.Columns.Clear;
  tempDataSet.First;
  while not tempDataSet.Eof do
  begin
    //funcId := tempDataSet.fieldbyname('').AsString;
    fieldName := tempDataSet.fieldbyname('').AsString;
    showName  := tempDataSet.fieldbyname('').AsString;
    ifshow := tempDataSet.fieldbyname('').AsString;
    //showId := tempDataSet.fieldbyname('').AsInteger;
    gridWidth := tempDataSet.fieldbyname('').AsInteger;
    titAlign := tempDataSet.fieldbyname('').AsInteger;
    titFont := tempDataSet.fieldbyname('').AsString;
    titFontSize := tempDataSet.fieldbyname('').AsInteger;
    titFontColor := tempDataSet.fieldbyname('').AsString;
    gridAlign := tempDataSet.fieldbyname('').AsInteger;
    gridFont := tempDataSet.fieldbyname('').AsString;
    gridFontSize := tempDataSet.fieldbyname('').AsInteger;
    gridFontColor := tempDataSet.fieldbyname('').AsString;
    grid.Columns.Add;
    
    grid.Columns[i].FieldName:=fieldName;
    grid.Columns[i].Title.Caption:=showName;
    if ifshow='1' then
      grid.Columns[i].Visible:=True
    else
      grid.Columns[i].Visible:=False;
    grid.Columns[i].Width:=gridWidth;
    grid.Columns[i].Title.Alignment:=talignment(titAlign);
    grid.Columns[i].Title.Font.Name:=titFont;
    grid.Columns[i].Title.Font.Size:=titFontSize;
    grid.Columns[i].Title.Font.Color:=StringToColor(titFontColor);
    grid.Columns[i].Alignment:=talignment(gridAlign);
    grid.Columns[i].Font.Name:=gridFont;
    grid.Columns[i].Font.Size:=gridFontSize;
    grid.Columns[i].Font.Color:=StringToColor(gridFontColor);

    i:=i+1;
    tempDataSet.Next;
  end;
end;
end.
