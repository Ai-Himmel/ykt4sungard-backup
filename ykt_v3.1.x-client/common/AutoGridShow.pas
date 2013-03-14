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
  //���ܺ�
  //funcId : string;
  //�ֶ�����
  fieldName:string;
  //��ʾ����
  showName :string;
  //�Ƿ���ʾ
  ifshow:string;
  //��ʾ˳���
  //showId:Integer;
  //�����
  gridWidth:Integer;
  //��ͷ���뷽ʽ
  titAlign:Integer;
  //��ͷ����
  titFont:string;
  //��ͷ�����С
  titFontSize:Integer;
  //��ͷ������ɫ
  titFontColor:string;
  //�����뷽ʽ
  gridAlign:Integer;
  //�������
  gridFont:string;
  //��������С
  gridFontSize:Integer;
  //���������ɫ
  gridFontColor:string;

  i:Integer;
begin
  i:=0;
  tempDataSet := TDataSet(wv.FieldByName('��ѯ�����').Data.AsObject);
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
