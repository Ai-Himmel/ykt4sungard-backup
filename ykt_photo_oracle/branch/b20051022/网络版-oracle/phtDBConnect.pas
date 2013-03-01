unit phtDBConnect;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, Grids, DBGrids, Db, phtImportForm;

type
  TfrmDBConnect = class(TfrmImportForm)
    Label1: TLabel;
    Label3: TLabel;
    edtDataSource: TEdit;
    Label4: TLabel;
    cbTable: TComboBox;
    Shape1: TShape;
    Shape2: TShape;
    grdSource: TDBGrid;
    DataSource: TDataSource;
    lblTotal: TLabel;
    procedure cbTableChange(Sender: TObject);
  private
    { Private declarations }
  public
    { public declarations }
    procedure Enter; override;
    function Leave: Boolean; override;
  end;

implementation

uses
  phtImport;

{$R *.DFM}

{ TfrmDBConnect }

procedure TfrmDBConnect.cbTableChange(Sender: TObject);
begin
  G_phtImport.ImportTable.Close;
  G_phtImport.ImportTable.TableName := cbTable.Text;
  G_phtImport.ImportTable.Open;
  lblTotal.Caption := '共有 '+ IntToStr(G_phtImport.ImportTable.RecordCount)
      + ' 条记录';
end;

procedure TfrmDBConnect.Enter;
begin 
  edtDataSource.Text := G_phtImport.DataSource;
  case G_phtImport.SourceType of
    stFoxpro:
    begin
      cbTable.Text := G_phtImport.ImportTable.TableName;
      cbTable.Enabled := False;
      cbTable.Style := csSimple;
      DataSource.DataSet := G_phtImport.ImportTable;
    end;
    stAccess:
    begin
      G_phtImport.ImportConn.GetTableNames(cbTable.Items);
      cbTable.Enabled := True;
      cbTable.Style := csOwnerDrawFixed;
      DataSource.DataSet := G_phtImport.ImportTable;

      cbTable.ItemIndex := 0;
      cbTableChange(cbTable);
    end;
  end;
  Self.Show;
end;

function TfrmDBConnect.Leave: Boolean;
begin
  if cbTable.Text = '' then
  begin
    MessageDlg('请选择要导入的表!', mtInformation, [mbOk], 0);
    Result := False;
  end
  else
    Result := True;
end;

end.
