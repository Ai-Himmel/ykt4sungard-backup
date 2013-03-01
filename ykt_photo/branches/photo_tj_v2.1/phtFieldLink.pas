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
     MessageDlg('��ѡ��ƥ����ֶ�!', mtInformation, [mbOk], 0);
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
  ��õ�������Դ���ֶ���, ���� CheckListBox (clbFields)�С�
  ����ͬ��ԭ�򣬽������ֶ����Զ�ƥ�䵽 �� photo.T_CIF_Photo �еĶ�Ӧ�ֶΡ�
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
    // Ѱ��ƥ���ֶ�
    if G_phtImport.PreMatch(I) then
    begin
      clbFields.Checked[I] := True;
      // ƥ��� CIF_Fields �ֶ�
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
  // �������ĵ�һ���ֶ�����Ϊ��ǰ�����ֶ�
  clbFields.ItemIndex := 0;
  clbFieldsClick(clbFields);
  Self.Show;
end;

function TfrmFieldLink.Leave: Boolean;
begin
  Result := True;
end;

end.
