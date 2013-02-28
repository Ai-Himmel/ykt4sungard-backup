unit ViewDataDetail;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ComCtrls, ExtCtrls, DBCtrls, Db, DBGrids, DBActns, ActnList,DataUsageUtils,
  Menus, RzDBNav;

type
  TdlgViewDataDetail = class(TForm)
    DataSource: TDataSource;
    alDatasetActions: TActionList;
    DataSetLast: TDataSetLast;
    DataSetNext: TDataSetNext;
    DataSetPrior: TDataSetPrior;
    DataSetFirst: TDataSetFirst;
    dlgPrint: TAction;
    PopupMenu1: TPopupMenu;
    N1: TMenuItem;
    DBNavigator1: TRzDBNavigator;
    lvDetail: TListView;
    procedure DataSourceDataChange(Sender: TObject; Field: TField);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormKeyUp(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure alDatasetActionsExecute(Action: TBasicAction;
      var Handled: Boolean);
    procedure alDatasetActionsUpdate(Action: TBasicAction;
      var Handled: Boolean);
    procedure dlgPrintExecute(Sender: TObject);
    procedure N1Click(Sender: TObject);
  private
    { Private declarations }
    FTitles : TStringList;
    procedure UpdateDetailData;
    procedure InternalExecute(Dataset : TDataset; const Title:string);
    procedure SetupListView;
  public
    { Public declarations }
    procedure Execute(Grid : TDBGrid; const Title:string=''); overload;
    procedure Execute(Dataset : TDataset; const Title:string=''); overload;
  end;

var
  dlgViewDataDetail: TdlgViewDataDetail;

procedure ShowDataDetail(Grid : TDBGrid; const Title:string=''); overload;

procedure ShowDataDetail(Dataset : TDataset; const Title:string=''); overload;

implementation

{$R *.DFM}

procedure ShowDataDetail(Grid : TDBGrid; const Title:string=''); overload;
var
  Dialog : TdlgViewDataDetail;
begin
  Dialog := TdlgViewDataDetail.Create(Application);
  try
    Dialog.Execute(Grid,Title);
  finally
    Dialog.Free;
  end;
end;

procedure ShowDataDetail(Dataset : TDataset; const Title:string=''); overload;
var
  Dialog : TdlgViewDataDetail;
begin
  Dialog := TdlgViewDataDetail.Create(Application);
  try
    Dialog.Execute(Dataset,Title);
  finally
    Dialog.Free;
  end;
end;

{ TdlgViewDataDetail }

procedure TdlgViewDataDetail.FormCreate(Sender: TObject);
begin
  FTitles := TStringList.Create;
end;

procedure TdlgViewDataDetail.FormDestroy(Sender: TObject);
begin
  FreeAndNil(FTitles);
end;

procedure TdlgViewDataDetail.DataSourceDataChange(Sender: TObject;
  Field: TField);
begin
  if Field=nil then
  begin
    UpdateDetailData;
  end;
end;

procedure TdlgViewDataDetail.Execute(Grid: TDBGrid; const Title:string='');
var
  I : Integer;
begin
  Assert(Grid<>nil);
  // 增加 DataSet 不为空的判断 add by 汤成
  if (Grid.DataSource<>nil) and (Grid.DataSource.Dataset<>nil)
    and ( not Grid.DataSource.DataSet.IsEmpty )then
  begin
    FTitles.Clear;
    for I:=0 to Grid.Columns.Count-1 do
    begin
      if Grid.Columns[I].Visible then
      begin
        with Grid.Columns[I] do
          FTitles.AddObject(Title.Caption,Field);
      end;
    end;
    InternalExecute(Grid.DataSource.Dataset, Title);
  end;
end;

procedure TdlgViewDataDetail.Execute(Dataset: TDataset; const Title:string='');
var
  I : Integer;
begin
  Assert(Dataset<>nil);
  // 增加 DataSet 不为空的判断 add by 汤成
  if ( Dataset.IsEmpty ) then
    Exit;
  FTitles.Clear;
  for I:=0 to Dataset.FieldCount-1 do
  begin
    FTitles.AddObject(Dataset.Fields[I].DisplayName,Dataset.Fields[I]);
  end;
  InternalExecute(Dataset,Title);
end;

procedure TdlgViewDataDetail.InternalExecute(Dataset: TDataset; const Title:string);
begin
  if Title<>'' then
    Caption := Title;
  if Dataset.Active then
  begin
    SetupListView;
    DataSource.DataSet := Dataset;
    try
      UpdateDetailData;
      ShowModal;
    finally
      DataSource.DataSet := nil;
    end;
  end;
end;

procedure TdlgViewDataDetail.UpdateDetailData;
var
  I : Integer;
  Item : TListItem;
  Field : TField;
begin
  Assert(FTitles.Count=lvDetail.Items.Count);
  lvDetail.Items.BeginUpdate;
  try
    for I:=0 to FTitles.Count-1 do
    begin
      Item := lvDetail.Items[I];
      Field := TField(FTitles.Objects[I]);
      if Field<>nil then
        Item.SubItems[0]:=Field.DisplayText else
        Item.SubItems[0]:='';
    end;
  finally
    lvDetail.Items.EndUpdate;
  end;
end;

procedure TdlgViewDataDetail.SetupListView;
var
  I : Integer;
  Item : TListItem;
begin
  lvDetail.Items.BeginUpdate;
  try
    lvDetail.Items.Clear;
    for I:=0 to FTitles.Count-1 do
    begin
      Item := lvDetail.Items.Add;
      Item.Caption := FTitles[I];
      Item.SubItems.Add('');
    end;
  finally
    lvDetail.Items.EndUpdate;
  end;
end;

procedure TdlgViewDataDetail.FormKeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=VK_ESCAPE then
  begin
    Key := 0;
    Close;
  end;
end;

procedure TdlgViewDataDetail.alDatasetActionsExecute(Action: TBasicAction;
  var Handled: Boolean);
begin
  Handled := True;
  if Action.HandlesTarget(DataSource) then
    Action.ExecuteTarget(DataSource);
end;

procedure TdlgViewDataDetail.alDatasetActionsUpdate(Action: TBasicAction;
  var Handled: Boolean);
begin
  Handled := True;
  Action.UpdateTarget(DataSource);
end;

procedure TdlgViewDataDetail.dlgPrintExecute(Sender: TObject);
begin
  if  DataSource.DataSet=nil then ShowMessage('数据集为空！');
  DbListViewPrint(lvDetail,DataSource.DataSet,dlgViewDataDetail.Caption,'','','');
end;

procedure TdlgViewDataDetail.N1Click(Sender: TObject);
begin
  if  DataSource.DataSet=nil then ShowMessage('数据集为空！');
  DbListViewPrint(lvDetail,DataSource.DataSet,dlgViewDataDetail.Caption,'','','');
end;

end.
