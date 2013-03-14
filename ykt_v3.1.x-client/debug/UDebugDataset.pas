unit UDebugDataset;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Db, Grids, DBGrids, ExtCtrls, DBCtrls, StdCtrls, ComCtrls, ToolWin;

type
  TdlgDebugDataset = class(TForm)
    DataSource1: TDataSource;
    pcPages: TPageControl;
    TabSheet1: TTabSheet;
    TabSheet2: TTabSheet;
    Panel1: TPanel;
    DBNavigator1: TDBNavigator;
    btnViewPlainText: TButton;
    Grid: TDBGrid;
    StatusBar: TStatusBar;
    lvParams: TListView;
    ToolBar1: TToolBar;
    btnRefresh: TToolButton;
    procedure btnViewPlainTextClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure btnRefreshClick(Sender: TObject);
    procedure GridDblClick(Sender: TObject);
  private
    procedure RefreshParams;
    { Private declarations }
  public
    { Public declarations }
    procedure DoDebugDataset(Dataset : TDataset; const ACaption:string='');
    procedure DoDebugDataSource(DataSource : TDataSource; const ACaption:string='');
  end;

var
  dlgDebugDataset: TdlgDebugDataset;

procedure DoDebugDataset(Dataset : TDataset; const ACaption:string='');

procedure DoDebugDataSource(DataSource : TDataSource; const ACaption:string='');

implementation

{$R *.DFM}

uses BDAImpEx, KCDataAccess, ConvertUtils, TypInfo, DBAIntf, ULongText;

procedure DoDebugDataset(Dataset : TDataset; const ACaption:string='');
var
  Dialog : TdlgDebugDataset;
begin
  Dialog := TdlgDebugDataset.Create(Application);
  Dialog.DoDebugDataset(Dataset,ACaption);
end;

procedure DoDebugDataSource(DataSource : TDataSource; const ACaption:string='');
var
  Dialog : TdlgDebugDataset;
begin
  Dialog := TdlgDebugDataset.Create(Application);
  Dialog.DoDebugDataSource(DataSource,ACaption);
end;

{ TdlgDebugDataset }

procedure TdlgDebugDataset.btnViewPlainTextClick(Sender: TObject);
var
  Dataset : TDataset;
  I : Integer;
begin
  if Grid.DataSource<>nil then
  begin
    Dataset := Grid.DataSource.DataSet;
    if Dataset<>nil then
    begin
      for I:=0 to Dataset.FieldCount-1 do
      begin
        Dataset.Fields[I].OnGetText := nil;
      end;
      Grid.Invalidate;
    end;
  end;
end;

procedure TdlgDebugDataset.DoDebugDataset(Dataset: TDataset;
  const ACaption: string);
begin
  pcPages.ActivePageIndex := 0;
  DataSource1.DataSet := Dataset;
  Grid.DataSource := DataSource1;
  Caption := Hint + ACaption;
  RefreshParams;
  Show;
end;

procedure TdlgDebugDataset.DoDebugDataSource(DataSource: TDataSource;
  const ACaption: string);
begin
  pcPages.ActivePageIndex := 0;
  Grid.DataSource := DataSource;
  DBNavigator1.DataSource := DataSource;
  Caption := Hint + ACaption;
  RefreshParams;
  Show;
end;

procedure TdlgDebugDataset.FormClose(Sender: TObject;
  var Action: TCloseAction);
begin
  Action := caFree;
end;

procedure TdlgDebugDataset.RefreshParams;
var
  KCDataset : TKCDataset;
  I : Integer;
  Param : THRPCParam;
  ListItem : TListItem;
  StrValue : string;
begin
  StatusBar.SimpleText := '';
  try
    lvParams.Items.BeginUpdate;
    lvParams.Items.Clear;
    if (Grid.DataSource<>nil) and (Grid.DataSource.Dataset is TKCDataset) then
    begin
      KCDataset := TKCDataset(Grid.DataSource.Dataset);
      for I:=0 to KCDataset.Params.Count-1 do
      begin
        Param := KCDataset.Params.Items[I];
        ListItem := lvParams.Items.Add;
        ListItem.Caption := Param.Name;
        ListItem.SubItems.Add(GetEnumName(TypeInfo(TDBFieldType),Integer(Param.DataType)));
        StrValue := Param.AsString;
        ListItem.SubItems.Add(StrValue);
      end;
      StatusBar.SimpleText := Format('Request=%d, ParamCount=%d, Return=%d, Done=%s, CurrentRecordCount=%d',
        [KCDataset.RequestType, KCDataset.Params.Count, KCDataset.ReturnCode, BoolToStr(KCDataset.Done), KCDataset.CurrentRecordCount]);
    end;
  finally
    lvParams.Items.EndUpdate;
  end;
end;

procedure TdlgDebugDataset.btnRefreshClick(Sender: TObject);
begin
  RefreshParams;
end;

procedure TdlgDebugDataset.GridDblClick(Sender: TObject);
begin
  if Grid.SelectedField<>nil then
  begin
    ShowLongText(Grid.SelectedField.FieldName, Grid.SelectedField.AsString);
  end;
end;

end.
