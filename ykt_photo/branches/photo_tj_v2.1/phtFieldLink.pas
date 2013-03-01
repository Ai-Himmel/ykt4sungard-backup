unit phtFieldLink;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, CheckLst, Db, phtImportForm;

type
  TfrmFieldLink = class(TfrmImportForm)
    Label1: TLabel;
    Shape1: TShape;
    Shape2: TShape;
    gbDataLink: TGroupBox;
    Label2: TLabel;
    Label3: TLabel;
    sbDataLink: TScrollBox;
    lbFields: TListBox;
    clbFields: TCheckListBox;
    edtField: TEdit;
    cbField: TComboBox;
    btnMatch: TButton;
    btnClear: TButton;
    procedure clbFieldsClick(Sender: TObject);
    procedure clbFieldsClickCheck(Sender: TObject);
    procedure btnMatchClick(Sender: TObject);
    procedure btnClearClick(Sender: TObject);
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

{ TfrmFieldLink }

procedure TfrmFieldLink.clbFieldsClick(Sender: TObject);
var
  Index: Integer;
begin
  Index := clbFields.ItemIndex;
  edtField.Text := G_phtImport.MatchGroup[Index].impFldName;

  G_phtImport.InitComboBox(cbField, Index);
end;

procedure TfrmFieldLink.clbFieldsClickCheck(Sender: TObject);
var
  Index: Integer;
begin
  Index := clbFields.ItemIndex;
  G_phtImport.MatchGroup[Index].isImport := clbFields.Checked[Index];
end;

procedure TfrmFieldLink.btnMatchClick(Sender: TObject);
var
  impI: Integer;
  phtI: Integer;
begin
  phtI := G_phtImport.IndexOfFields(cbField.Text);
  if phtI <> -1 then
  begin
    impI := clbFields.ItemIndex;
    clbFields.Checked[impI] := True;
    lbFields.Items[impI] := cbField.Text;
    G_phtImport.Match(impI, phtI);
  end
  else
  begin
     MessageDlg('请选择匹配的字段!', mtInformation, [mbOk], 0);
  end;
end;

procedure TfrmFieldLink.btnClearClick(Sender: TObject);
var
  impI: Integer;
begin
  impI := clbFields.ItemIndex;
  clbFields.Checked[impI] := False;
  if G_phtImport.DeMatch(impI) then
    lbFields.Items[impI] := '';
end;
 
procedure TfrmFieldLink.Enter;   
{
  获得导入数据源的字段名, 加入 CheckListBox (clbFields)中。
  根据同名原则，将导入字段名自动匹配到 表 photo.T_CIF_Photo 中的对应字段。
}
var
  I,
  H: Integer;
  impFields: TFields;
begin
  clbFields.Items.Clear;
  lbFields.Items.Clear;

  G_phtImport.BeforeMatch;
  impFields := G_phtImport.ImportTable.Fields;
  for I := 0 to impFields.Count - 1 do
  begin
    clbFields.Items.Add(impFields[I].FieldName);
    G_phtImport.MatchGroup[I].impFldName := clbFields.Items[I];
    // 寻找匹配字段
    if G_phtImport.PreMatch(I) then
    begin
      clbFields.Checked[I] := True;
      // 匹配的 CIF_Fields 字段
      lbFields.Items.Add(G_phtImport.MatchGroup[I].phtField.ChName);
    end
    else
      lbFields.Items.Add('');

  end;

  H := clbFields.ItemHeight * clbFields.Items.Count + 4;
  if (H > sbDataLink.Height - 22) then
  begin
    clbFields.Height := H;
    clbFields.Height := H;
    sbDataLink.VertScrollBar.Range := clbFields.Height + 22;
  end;
  // 将导入表的第一个字段设置为当前处理字段
  clbFields.ItemIndex := 0;
  clbFieldsClick(clbFields);
  Self.Show;
end;

function TfrmFieldLink.Leave: Boolean;
begin
  Result := True;
end;

end.
