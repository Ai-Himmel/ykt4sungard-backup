unit SmartDataSearchDlg;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>SmartDataSearchDlg
   <What>在结果集里面查找记录
   <Written By> 王苏娜
   <History>
**********************************************}


interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Buttons, Db, DBGrids, ExtCtrls, DataUsageUtils, UICtrls,
  ImageCtrls ,BDAImpEx;

type
  TdlgSmartSearchDataset = class(TForm)
    UIPanel1: TUIPanel;
    Panel1: TPanel;
    cbIsUpperLowerCase: TCheckBox;
    rgDirection: TRadioGroup;
    rgOrigin: TRadioGroup;
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    edFieldValue: TEdit;
    cbbFieldName: TComboBox;
    ImageButton1: TBitBtn;
    ImageButton2: TBitBtn;
    ImageButton3: TBitBtn;
    ImageButton4: TBitBtn;
    Label3: TLabel;
    ComboBox1: TComboBox;
    Label4: TLabel;
    ComboBox2: TComboBox;
    procedure FormKeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
    procedure GetFieldName(DataSet: TDataSet; const SelectFieldName : string); overload;
    procedure GetFieldName(DBGrid : TDBGrid; const SelectFieldName : string); overload;
    {将当前的数据整合为一个所需的数据集}
 //   procedure GetConditionDataSet(DBGrid:TDBGrid);
  public
    { Public declarations }
    function  Execute(DataSet : TDataSet; var SearchOptions : TDataSearchOptions):Boolean; overload;
    function  Execute(Grid : TDBGrid; var SearchOptions : TDataSearchOptions):Boolean; overload;
    function  Execute(Grid : TDBGrid;  var SearchOptions : TDataSearchOptions ; SearchKind:Integer):Boolean;overload;
  end;

var
  dlgSmartSearchDataset: TdlgSmartSearchDataset;

implementation

{$R *.DFM}

function TdlgSmartSearchDataset.Execute(Grid: TDBGrid;
  var SearchOptions: TDataSearchOptions ; SearchKind:Integer): Boolean;
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


function TdlgSmartSearchDataset.Execute(DataSet: TDataSet; var SearchOptions : TDataSearchOptions): Boolean;
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

function TdlgSmartSearchDataset.Execute(Grid: TDBGrid;
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

procedure TdlgSmartSearchDataset.GetFieldName(DataSet: TDataSet; const SelectFieldName : string);
var
  I: Integer;
  Index : Integer;
begin
  Index := -1;
  cbbFieldName.Items.Clear;
//  AdvStringGrid.ClearComboString;
  for I := 0 to DataSet.FieldCount - 1 do
  begin
    cbbFieldName.Items.AddObject(DataSet.Fields[I].DisplayName,DataSet.Fields[I]);
//    AdvStringGrid.AddComboString(DataSet.Fields[I].DisplayName);
    if SameText(DataSet.Fields[I].FieldName,SelectFieldName) then
      Index := I;
  end;
  cbbFieldName.ItemIndex := Index;
//  AdvStringGrid.Combobox.Sorted := True;
end;

procedure TdlgSmartSearchDataset.GetFieldName(DBGrid: TDBGrid; const SelectFieldName : string);
var
  I: Integer;
  Index : Integer;
begin
  Index := -1;
  cbbFieldName.Items.Clear;
//  AdvStringGrid.ClearComboString;
  for I := 0 to DBGrid.Columns.Count - 1 do
  begin
    cbbFieldName.Items.AddObject(DBGrid.Columns[I].Title.Caption,DBGrid.Columns[I]);
//    AdvStringGrid.AddComboStringObject(DBGrid.Columns[I].Title.Caption,DBGrid.Columns[I]);
    ShowMessage('Get Fieldname -'+DBGrid.Columns[I].Title.Caption);
 //   AdvStringGrid.AddComboString(DBGrid.Columns[I].Title.Caption);
    if SameText(DBGrid.Columns[I].FieldName,SelectFieldName) then
      Index := I;
  end;
  cbbFieldName.ItemIndex := Index;
//  AdvStringGrid.Combobox.Sorted := True;
//  AdvStringGrid.SortByColumn(1);
end;

procedure TdlgSmartSearchDataset.FormKeyPress(Sender: TObject; var Key: Char);
begin
  if (Key=#13) and not (ActiveControl is TImageButton) then
  begin
    Key := #0;
    SelectNext(ActiveControl, True, True);
  end;
end;

end.
