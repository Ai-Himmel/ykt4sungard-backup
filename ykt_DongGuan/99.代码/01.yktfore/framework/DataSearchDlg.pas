unit DataSearchDlg;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>DataSearchDlg
   <What>在结果集里面查找记录
   <Written By> Huang YanLai (黄燕来)、赵东波
   <History>
**********************************************}


interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Buttons, Db, DBGrids, ExtCtrls, DataUsageUtils, UICtrls,
  ImageCtrls, Mask, RzEdit, RzCmboBx, RzPanel, RzButton, RzRadChk;

type
  TdlgSearchDataset = class(TForm)
    UIPanel1: TUIPanel;
    Panel1: TPanel;
    rgDirection: TRadioGroup;
    rgOrigin: TRadioGroup;
    ImageButton1: TBitBtn;
    ImageButton2: TBitBtn;
    RzGroupBox1: TRzGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    cbbFieldName: TRzComboBox;
    edFieldValue: TRzEdit;
    cbIsUpperLowerCase: TRzCheckBox;
    procedure FormKeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
    procedure GetFieldName(DataSet: TDataSet; const SelectFieldName : string); overload;
    procedure GetFieldName(DBGrid : TDBGrid; const SelectFieldName : string); overload;
  public
    { Public declarations }
    function  Execute(DataSet : TDataSet; var SearchOptions : TDataSearchOptions):Boolean; overload;
    function  Execute(Grid : TDBGrid; var SearchOptions : TDataSearchOptions):Boolean; overload;
  end;

var
  dlgSearchDataset: TdlgSearchDataset;

implementation

{$R *.DFM}

function TdlgSearchDataset.Execute(DataSet: TDataSet; var SearchOptions : TDataSearchOptions): Boolean;
begin
  GetFieldName(DataSet,SearchOptions.FieldName);
  edFieldValue.Text := SearchOptions.SearchValue;
  cbIsUpperLowerCase.Checked  := SearchOptions.IsUpperLowercase;
  rgOrigin.ItemIndex := Integer(SearchOptions.IsFromFirst);
  rgDirection.ItemIndex := Integer(SearchOptions.IsForward);
  Result := ShowModal=mrYes;
  if Result then
  begin
    if cbbFieldName.ItemIndex>=0 then
      SearchOptions.FieldName := TField(cbbFieldName.Items.Objects[cbbFieldName.ItemIndex]).FieldName else
      SearchOptions.FieldName := '';
    SearchOptions.SearchValue := edFieldValue.Text;
    SearchOptions.IsUpperLowercase := cbIsUpperLowerCase.Checked;
    SearchOptions.IsFromFirst := rgOrigin.ItemIndex = 1;
    SearchOptions.IsForward := rgDirection.ItemIndex = 1;
  end;
end;

function TdlgSearchDataset.Execute(Grid: TDBGrid;
  var SearchOptions: TDataSearchOptions): Boolean;
begin
  GetFieldName(Grid,SearchOptions.FieldName);
  edFieldValue.Text := SearchOptions.SearchValue;
  cbIsUpperLowerCase.Checked  := SearchOptions.IsUpperLowercase;
  rgOrigin.ItemIndex := Integer(SearchOptions.IsFromFirst);
  rgDirection.ItemIndex := Integer(SearchOptions.IsForward);
  Result := ShowModal=mrYes;
  if Result then
  begin
    if cbbFieldName.ItemIndex>=0 then
      SearchOptions.FieldName := TColumn(cbbFieldName.Items.Objects[cbbFieldName.ItemIndex]).FieldName else
      SearchOptions.FieldName := '';
    SearchOptions.SearchValue := edFieldValue.Text;
    SearchOptions.IsUpperLowercase := cbIsUpperLowerCase.Checked;
    SearchOptions.IsFromFirst := rgOrigin.ItemIndex = 1;
    SearchOptions.IsForward := rgDirection.ItemIndex = 1;
  end;
end;

procedure TdlgSearchDataset.GetFieldName(DataSet: TDataSet; const SelectFieldName : string);
var
  I: Integer;
  Index : Integer;
begin
  Index := -1;
  cbbFieldName.Items.Clear;
  for I := 0 to DataSet.FieldCount - 1 do
  begin
    cbbFieldName.Items.AddObject(DataSet.Fields[I].DisplayName,DataSet.Fields[I]);
    if SameText(DataSet.Fields[I].FieldName,SelectFieldName) then
      Index := I;
  end;
  cbbFieldName.ItemIndex := Index;
end;

procedure TdlgSearchDataset.GetFieldName(DBGrid: TDBGrid; const SelectFieldName : string);
var
  I: Integer;
  Index : Integer;
begin
  Index := -1;
  cbbFieldName.Items.Clear;
  for I := 0 to DBGrid.Columns.Count - 1 do
  begin
    cbbFieldName.Items.AddObject(DBGrid.Columns[I].Title.Caption,DBGrid.Columns[I]);
    if SameText(DBGrid.Columns[I].FieldName,SelectFieldName) then
      Index := I;
  end;
  cbbFieldName.ItemIndex := Index;
end;

procedure TdlgSearchDataset.FormKeyPress(Sender: TObject; var Key: Char);
begin
  if (Key=#13) and not (ActiveControl is TImageButton) then
  begin
    Key := #0;
    SelectNext(ActiveControl, True, True);
  end;
end;

end.
