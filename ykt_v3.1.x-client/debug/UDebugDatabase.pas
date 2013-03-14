unit UDebugDatabase;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ComCtrls, ToolWin, KCDataAccess;

type
  TfmDebugDatabase = class(TForm)
    ToolBar1: TToolBar;
    btnRefresh: TToolButton;
    lvDatasets: TListView;
    StatusBar: TStatusBar;
    btnDebugDataset: TToolButton;
    procedure btnRefreshClick(Sender: TObject);
    procedure btnDebugDatasetClick(Sender: TObject);
  private
    FDatabase: TKCDatabase;
    { Private declarations }
  protected
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
  public
    { Public declarations }
    procedure Execute(ADatabase : TKCDatabase);
    procedure ClearData;
    procedure RefreshData;
    property  Database : TKCDatabase read FDatabase;
  end;

var
  fmDebugDatabase: TfmDebugDatabase;

procedure DoDebugDatabase(ADatabase : TKCDatabase);

implementation

{$R *.DFM}

uses ConvertUtils, KSFrameWorks, DB;

procedure DoDebugDatabase(ADatabase : TKCDatabase);
begin
  if fmDebugDatabase=nil then
    fmDebugDatabase := TfmDebugDatabase.Create(Application);
  fmDebugDatabase.Execute(ADatabase);
end;

{ TfmDebugDatabase }

procedure TfmDebugDatabase.Execute(ADatabase: TKCDatabase);
begin
  FDatabase := ADatabase;
  RefreshData;
  Show;
end;

procedure TfmDebugDatabase.RefreshData;
var
  I,Count : Integer;
  Dataset : TKCDataset;
  Item : TListItem;
begin
  try
    lvDatasets.Items.BeginUpdate;
    lvDatasets.Items.Clear;
    if Database<>nil then
    begin
      Count := Database.DatasetCount;
      for I:=0 to Count-1 do
      begin
        Dataset := TKCDataset(Database.Datasets[I]);
        Item := lvDatasets.Items.Add;
        if Dataset.Owner<>nil then
          Item.Caption := Dataset.Owner.ClassName else
          Item.Caption := '<нч>';
        Item.SubItems.Add(BoolToStr(Dataset.Active));
        Item.SubItems.Add(BoolToStr(Dataset.Done));
        Item.SubItems.Add(IntToStr(Dataset.RequestType));
        Item.SubItems.Add(IntToStr(Dataset.ReturnCode));
        Item.Data := Dataset;
        Dataset.FreeNotification(Self);
      end;
      with Database do
        StatusBar.SimpleText := Format('IP=%s,Port=%d,DestNo=%d,FuncNo=%d,Datasets=%d,Pooled=%d',
          [GatewayIP,GatewayPort,DestNo,FuncNo,Count,PooledConnectionCount]);
    end else
      StatusBar.SimpleText := 'None';
  finally
    lvDatasets.Items.EndUpdate;
  end;
end;

procedure TfmDebugDatabase.btnRefreshClick(Sender: TObject);
begin
  RefreshData;
end;

procedure TfmDebugDatabase.btnDebugDatasetClick(Sender: TObject);
begin
  if (lvDatasets.Selected<>nil) and (Context.GetDebugSystem<>nil) then
  begin
    Context.GetDebugSystem.DebugDataset(TDataset(lvDatasets.Selected.Data));
  end;
end;

procedure TfmDebugDatabase.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited;
  if (Operation=opRemove) and (AComponent is TDataset) then
  begin
    ClearData;
  end;
end;

procedure TfmDebugDatabase.ClearData;
begin
  lvDatasets.Items.BeginUpdate;
  lvDatasets.Items.Clear;
  lvDatasets.Items.EndUpdate;
  StatusBar.SimpleText := '';
end;

end.
