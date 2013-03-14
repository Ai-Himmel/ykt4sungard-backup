unit UVoucherDetail;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  RzPanel, GridsEh, DBGridEh, StdCtrls, Mask, WVCtrls, UIncrementComboBox,
  ExtCtrls, sncCurrency, sncDBCurrency, Db, ZAbstractRODataset,
  ZAbstractDataset, ZAbstractTable, ZDataset;

type
  TfrmVoucherDetail = class(TForm)
    pnlTop: TPanel;
    lbl1: TLabel;
    Label2: TLabel;
    Label11: TLabel;
    pnl1: TPanel;
    cbbVType: TWVComboBox;
    edtDate: TWVEdit;
    edtNum: TWVEdit;
    dbgrdh1: TDBGridEh;
    rzpnlTot: TRzPanel;
    lblUPCASE: TLabel;
    lbl4: TLabel;
    pnl2: TPanel;
    lbl2: TLabel;
    lblOperName: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    lbl3: TLabel;
    lblAccount: TLabel;
    Label15: TLabel;
    lblCheck: TLabel;
    cbbAccType: TWVComboBox;
    edtAccNo: TWVEdit;
    pnlBottom: TPanel;
    edtMoney: TsncDBCurrencyEdit;
    ztblPZ: TZTable;
    ztblPZcertificate: TStringField;
    subjno: TStringField;
    ztblPZsubjname: TStringField;
    ztblPZdebit: TFloatField;
    ztblPZcredit: TFloatField;
    procedure SetHighLightColor;
    procedure SetNormalColor;
    procedure FormShow(Sender: TObject);
    procedure edtMoneyEnter(Sender: TObject);
    procedure dbgrdh1ColEnter(Sender: TObject);
    procedure dbgrdh1DrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumnEh; State: TGridDrawState);
    procedure dbgrdh1KeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
    function editRecord: Integer;
  public
    { Public declarations }
    sAccount,sOper,sCheck:string;
    calcType,calcNo,caseUp:string;
    voucherType,ticketNum:string;
  end;

const
  CurrencyFieldSet: array[0..1] of string=('debit', 'credit');  //借方金额，贷方金额
var
  frmVoucherDetail: TfrmVoucherDetail;

implementation

uses UAccountMgrImp;

{$R *.DFM}

procedure TfrmVoucherDetail.FormShow(Sender: TObject);
begin
  lblUPCASE.Caption := '';
  lblOperName.Caption := '';
  edtMoney.Color := dbgrdh1.Color;
  edtMoney.Font.Assign(dbgrdh1.Font);
  edtMoney.Tag := 0;
  editRecord;
  //
end;

function CheckCurrencyField(FieldName: String): Boolean;
var
  I: Integer;
begin
  Result := False;
  for I:=0 to Length(CurrencyFieldSet)-1 do
  begin
    if (FieldName=CurrencyFieldSet[I]) then
    begin
      Result := True;
      Break;
    end;
  end;
end;

procedure TfrmVoucherDetail.edtMoneyEnter(Sender: TObject);
begin
  SetNormalColor;
end;

procedure TfrmVoucherDetail.dbgrdh1ColEnter(Sender: TObject);
begin
  if CheckCurrencyField(dbgrdh1.SelectedField.FieldName) then
  begin
    edtMoney.DataField := dbgrdh1.SelectedField.FieldName;
    edtMoney.Tag := 1;
  end;
end;

procedure TfrmVoucherDetail.dbgrdh1DrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumnEh;
  State: TGridDrawState);
var
  OldColor, OldFontColor: TColor;
begin
  if CheckCurrencyField(Column.FieldName) then
  begin
    if (gdFocused in State) then
    begin
      edtMoney.Left := Rect.Left + dbgrdh1.Left+2;
      edtMoney.Top := Rect.Top + dbgrdh1.top+2;
      edtMoney.Width := Rect.Right-Rect.Left;
      edtMoney.Height := Rect.Bottom- Rect.Top;
      SetHighLightColor;
      if (edtMoney.Tag=1) and not edtMoney.Visible then
        edtMoney.Visible := True;
    end
    else
    begin
      OldColor := edtMoney.Color;
      OldFontColor := edtMoney.Font.Color;
      SetNormalColor;
      DrawCurrencyFrame(dbgrdh1.Canvas, Rect, edtMoney, Column.Field.AsFloat);
      edtMoney.Color := OldColor;
      edtMoney.Font.Color := OldFontColor;
    end;
  end;
end;

procedure TfrmVoucherDetail.dbgrdh1KeyPress(Sender: TObject;
  var Key: Char);
begin
  if (key<>chr(9)) and CheckCurrencyField(dbgrdh1.SelectedField.FieldName) then
  begin
    edtMoney.SetFocus;
    SendMessage(edtMoney.Handle, WM_Char, WORD(Key), 0);
  end;
end;

procedure TfrmVoucherDetail.SetHighLightColor;
begin
  edtMoney.Color := clHighLight;
  edtMoney.Font.Color := clWhite;

end;

procedure TfrmVoucherDetail.SetNormalColor;
begin
  edtMoney.Color := dbgrdh1.Color;
  edtMoney.Font.Color := dbgrdh1.Font.Color;

end;

function TfrmVoucherDetail.editRecord: Integer;
begin
  try
    if not ztblPZ.Active then
      ztblPZ.Open;
    ztblPZ.Edit;
  except
    on e:Exception do
    begin
      ShowMessage('本地数据库打开失败，请检查-'+e.Message);
      Result := -1;
      Exit;
    end;
  end;
  Result := 0;

end;

end.
