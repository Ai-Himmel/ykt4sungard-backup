unit AdjustGridDlg;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>AdjustGridDlg
   <What>调整DBGrid显示列顺序
   <Written By> Huang YanLai (黄燕来)、赵东波
   <History>
**********************************************}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Buttons, CheckLst, Db, DBGrids, ExtCtrls, UICtrls, ImageCtrls;

type
  TMoveDirection = (mdUp, mdDown);

  TdlgAdjustGrid = class(TForm)
    UIPanel1: TUIPanel;
    sbMoveUp: TSpeedButton;
    sbMoveDown: TSpeedButton;
    lsColumns: TCheckListBox;
    ImageButton1: TBitBtn;
    ImageButton2: TBitBtn;
    procedure sbMoveUpClick(Sender: TObject);
    procedure sbMoveDownClick(Sender: TObject);
  private
    { Private declarations }
    procedure GridControl(Grid: TDBGrid; ColColor: TColor);
    procedure GetFieldName(Grid: TDBGrid);
    procedure CLBControl(MoveDirection: TMoveDirection);
  public
    { Public declarations }
    function  Execute(Grid: TDBGrid; ColColor: TColor):Boolean;
  end;

var
  dlgAdjustGrid: TdlgAdjustGrid;

implementation

{$R *.DFM}

procedure TdlgAdjustGrid.sbMoveUpClick(Sender: TObject);
begin
  CLBControl(mdUp);
end;

procedure TdlgAdjustGrid.sbMoveDownClick(Sender: TObject);
begin
  CLBControl(mdDown);
end;

procedure TdlgAdjustGrid.GetFieldName(Grid: TDBGrid);
var
  I: Integer;
begin
  lsColumns.Clear;
  for I := 0 to Grid.Columns.Count-1  do
  begin
    //if Grid.Columns[I].Visible = False then
     // Continue;
    lsColumns.Items.AddObject(Grid.Columns[I].Title.Caption,Grid.Columns[I]);
    //lsColumns.Checked[lsColumns.Items.Count-1] := Grid.Columns[I].Color=Grid.Color;
    lsColumns.Checked[lsColumns.Items.Count-1] := Grid.Columns[I].Visible;
  end;
end;

procedure TdlgAdjustGrid.GridControl(Grid: TDBGrid; ColColor: TColor);
var
  I,J: Integer;
  Column: TColumn;
begin
  J := -1;
  with lsColumns do
  begin
    for I := 0 to Items.Count-1 do
      if Checked[I] then
      begin
        J := J+1;
        Column := TColumn(Items.Objects[I]);
        Column.Index := J;
        Column.Color := Grid.Color;
      end;
    for I := 0 to Items.Count-1 do
      if not Checked[I] then
      begin
        J := J+1;
        Column := TColumn(Items.Objects[I]);
        Column.Index := J;
        Column.Color := ColColor;
      end;
  end;
end;

procedure TdlgAdjustGrid.CLBControl(MoveDirection: TMoveDirection);
var
  OldIndex : Integer;
begin
  with lsColumns do
    begin
      OldIndex := ItemIndex;
      if OldIndex<0 then
        Exit;
      if (MoveDirection = mdUp) and (ItemIndex > 0 ) then
      begin
        Items.Move(ItemIndex,ItemIndex-1);
        ItemIndex := OldIndex-1;
      end;
      if (MoveDirection = mdDown) and (ItemIndex <Items.Count - 1 ) then
      begin
        Items.Move(ItemIndex,ItemIndex+1);
        ItemIndex := OldIndex+1;
      end;
    end;
end;

function TdlgAdjustGrid.Execute(Grid: TDBGrid; ColColor: TColor): Boolean;
begin
  if Grid.DataSource=nil then
  begin
    showmessage('该功能不支持此操作！');
    exit;
  end;
  GetFieldName(Grid);
  Result := ShowModal=mrYes;
  if Result then
    GridControl(Grid,ColColor);
end;

end.

