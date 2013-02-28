unit UAAccCertificate;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db,GridsEh,
  RzDBGrid, Buttons, sncCurrency, RzPanel, ADODB, sncDBCurrency,ZDataset,
  ZAbstractRODataset, ZAbstractDataset, ZAbstractTable,DBGridEh,
  UIncrementComboBox;

type
  TfaqhAccCertificate = class(TfaqhSimpleQueryTemp)
    ztblPZ: TZTable;
    ztblPZcertificate: TStringField;
    ztblPZsubjno: TIntegerField;
    ztblPZsubjname: TStringField;
    ztblPZdebit: TFloatField;
    ztblPZcredit: TFloatField;
    WVRequest1: TWVRequest;
    WorkView1: TWorkView;
    dbgrdh1: TDBGridEh;
    edtMoney: TsncDBCurrencyEdit;
    btnAdd: TBitBtn;
    btnSave: TBitBtn;
    rzpnlTot: TRzPanel;
    lblUPCASE: TLabel;
    pnlTop: TPanel;
    pnl1: TPanel;
    lbl1: TLabel;
    cbbVoucherType: TWVComboBox;
    Label1: TLabel;
    edtNum: TEdit;
    Label2: TLabel;
    Label3: TLabel;
    edtDate: TWVEdit;
    procedure SetHighLightColor;
    procedure SetNormalColor;
    procedure edtMoneyExit(Sender: TObject);
    procedure edtMoneyMoveOut(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure edtMoneyEnter(Sender: TObject);
    procedure dbgrdh1ColEnter(Sender: TObject);
    procedure dbgrdh1ColExit(Sender: TObject);
    procedure dbgrdh1KeyPress(Sender: TObject; var Key: Char);
    procedure dbgrdh1DrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumnEh; State: TGridDrawState);
    procedure btnSaveClick(Sender: TObject);
    procedure edtMoneyKeyPress(Sender: TObject; var Key: Char);
    procedure btnQueryClick(Sender: TObject);
    procedure ztblPZBeforeInsert(DataSet: TDataSet);
  private

    { Private declarations }
    procedure delTbl();
    procedure addRecord();
    function editRecord():Integer;
    procedure newVoucher();
    function checkVoucher():Integer;
    function saveVoucher():Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

const
  CurrencyFieldSet: array[0..1] of string=('debit', 'credit');  //借方金额，贷方金额
var
  faqhAccCertificate: TfaqhAccCertificate;

implementation

uses KsFrameworks, UAccountMgrImp,SmartCardCommon,KSClientConsts;
     
{$R *.DFM}

procedure TfaqhAccCertificate.Init;
begin
  inherited;
  edtDate.Text := sysDate;
  rzpnlTot.Left := 0;
  rzpnlTot.Top := dbgrdh1.Height-20;
  rzpnlTot.Width := dbgrdh1.Width;
  lblUPCASE.Caption := '';
  try
    delTbl;
    addRecord;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('连接本地数据库失败-'+e.Message);
      Exit;
    end;
  end;
  edtMoney.Color := dbgrdh1.Color;
  edtMoney.Font.Assign(dbgrdh1.Font);
  edtMoney.Tag := 0;
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

procedure TfaqhAccCertificate.SetHighLightColor;
begin
  edtMoney.Color := clHighLight;
  edtMoney.Font.Color := clWhite;
end;

procedure TfaqhAccCertificate.SetNormalColor;
begin
  edtMoney.Color := dbgrdh1.Color;
  edtMoney.Font.Color := dbgrdh1.Font.Color;
end;

procedure TfaqhAccCertificate.edtMoneyExit(Sender: TObject);
begin
  SetHighLightColor;
end;

procedure TfaqhAccCertificate.edtMoneyMoveOut(Sender: TObject;
  var Key: Word; Shift: TShiftState);
begin
  case Key of
    VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT:
    begin
      dbgrdh1.SetFocus;
      SendMessage(dbgrdh1.Handle, WM_KEYDOWN, WORD(Key), 0);
    end;
  end;
end;

procedure TfaqhAccCertificate.edtMoneyEnter(Sender: TObject);
begin
  SetNormalColor;
end;

procedure TfaqhAccCertificate.dbgrdh1ColEnter(Sender: TObject);
begin
  if CheckCurrencyField(dbgrdh1.SelectedField.FieldName) then
  begin
    edtMoney.DataField := dbgrdh1.SelectedField.FieldName;
    edtMoney.Tag := 1;
  end;
end;

procedure TfaqhAccCertificate.dbgrdh1ColExit(Sender: TObject);
var
  subjno:string;
begin
  if CheckCurrencyField(dbgrdh1.SelectedField.FieldName) then
  begin
    edtMoney.Visible := false;
    edtMoney.Tag := 0;
  end
  else
  if (dbgrdh1.SelectedField.FieldName = 'subjno') then
  begin
    subjno := dbgrdh1.DataSource.DataSet.fieldbyname('subjno').AsString;
    //调用后台功能号取科目名称，没有则退出
    if Trim(subjno)='' then
    begin
      Context.GetDialogSystem.ShowMessage('科目号不能为空，请输入！');
      Exit;
    end;
    WorkView1.FieldByName('账号').Data.SetString(subjno);
    WVRequest1.SendCommand;
    if WorkView1.FieldByName('返回码').Data.AsInteger=0 then
    begin
      ztblPZ.Edit;
      ztblPZ.FieldByName('subjname').AsString:=WorkView1.fieldbyname('名称').Data.AsString;
    end
    else
    begin
      Context.GetDialogSystem.ShowMessage(WorkView1.fieldbyname('返回信息').Data.AsString);
      Exit;
    end;
  end
end;

procedure TfaqhAccCertificate.dbgrdh1KeyPress(Sender: TObject;var Key: Char);
begin
  if (key<>chr(9)) and CheckCurrencyField(dbgrdh1.SelectedField.FieldName) then
  begin
    edtMoney.SetFocus;
    SendMessage(edtMoney.Handle, WM_Char, WORD(Key), 0);
  end;
end;

procedure TfaqhAccCertificate.dbgrdh1DrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumnEh;State: TGridDrawState);
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

procedure TfaqhAccCertificate.delTbl;
var
  qry:TZQuery;
begin
  qry := nil;
  try
    qry := TZQuery.Create(nil);
    qry.Connection := cmAccountMgrImp.conFB;
    qry.Close;
    qry.SQL.Clear;
    qry.SQL.Add('delete from certificate');
    qry.ExecSQL;
  finally
    qry.Close;
    qry.Destroy;
  end;
end;

procedure TfaqhAccCertificate.btnSaveClick(Sender: TObject);
begin
  //凭证合法性检测
  if checkVoucher<>0 then
    Exit;
  if Application.MessageBox('你确定要保存该凭证吗？',PChar(Application.Title),mb_yesno+mb_iconquestion)=idno then
    Exit;
  if saveVoucher<>0 then
    Exit;
  Context.GetDialogSystem.ShowMessage('凭证保存成功，将建一张新的凭证！');
  newVoucher;
end;

procedure TfaqhAccCertificate.edtMoneyKeyPress(Sender: TObject;var Key: Char);
begin
  if Key=Chr(VK_RETURN) then
  begin
    dbgrdh1.SetFocus;
    ztblPZ.Post;
    editRecord;
    lblUPCASE.Caption := '金额大写：'+NtoC(dbgrdh1.Columns[3].Footer.SumValue);
  end;
end;

procedure TfaqhAccCertificate.addRecord;
var
  qry:TZQuery;
  i:Integer;
begin
  qry := nil;
  try
    qry := TZQuery.Create(nil);
    qry.Connection := cmAccountMgrImp.conFB;
    try
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add('BEGIN TRANSACTION');
      qry.ExecSQL;

      for i:= 0 to 3 do
      begin
        qry.Close;
        qry.SQL.Clear;
        qry.SQL.Add('Insert into certificate(id) Values(:VoucherID)');
        qry.Params.ParamByName('VoucherID').Value := i;
        qry.ExecSQL;
      end;

      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add('COMMIT');
      qry.ExecSQL;
    except
      on e:Exception do
        Context.GetDialogSystem.ShowMessage(e.Message);
    end;
    editRecord;
  finally
    qry.Close;
    qry.Destroy;
  end;
end;

function TfaqhAccCertificate.editRecord:Integer;
begin
  try
    if not ztblPZ.Active then
      ztblPZ.Open;
    ztblPZ.Edit;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('本地数据库打开失败，请检查-'+e.Message);
      Result := -1;
      Exit;
    end;
  end;
  Result := 0;
end;

procedure TfaqhAccCertificate.btnQueryClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要新建凭证吗？',PChar(Application.Title),mb_yesno+mb_iconquestion)=idno then
    Exit;
  newVoucher;
end;

procedure TfaqhAccCertificate.newVoucher;
begin
  delTbl;
  ztblPZ.Close;
  addRecord;
  dbgrdh1.SetFocus;
  dbgrdh1.SelectedIndex := 0;
end;

function TfaqhAccCertificate.checkVoucher: Integer;
var
  qry:TZQuery;
  subjno,subjname:string;
  debit,credit:Real;
begin

  if edtDate.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('请输入凭证日期！');
    edtDate.SetFocus;
    Result := -3;
    Exit;
  end;
  if CheckInputDateFormat(edtDate.Text)=False then
  begin
    Context.GetDialogSystem.ShowMessage('请输入正确的日期，格式:yyyymmdd');
    edtDate.SetFocus;
    Result := -6;
    Exit;
  end;
  {
  if cbbVoucherType.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('请选择凭证类型！');
    cbbVoucherType.SetFocus;
    Result := -3;
    Exit;
  end;
  }
  try
    if edtNum.Text = '' then
      edtNum.Text := '0';
    if StrToInt(edtNum.Text)<0 then
    begin
      Context.GetDialogSystem.ShowMessage('请输入正确的附件张数！');
      Result := -4;
      Exit;
    end;
  except
    Context.GetDialogSystem.ShowMessage('请输入正确的附件张数！');
    Result := -5;
    Exit;
  end;

  if (dbgrdh1.Columns[3].Footer.SumValue=0) and (dbgrdh1.Columns[4].Footer.SumValue=0) then
  begin
    Context.GetDialogSystem.ShowMessage('借贷金额都为零，请修改后再保存！');
    Result := -7;
    Exit;
  end;

  if dbgrdh1.Columns[3].Footer.SumValue<>dbgrdh1.Columns[4].Footer.SumValue then
  begin
    Context.GetDialogSystem.ShowMessage('借贷关系不平衡，请修改后再保存！');
    Result := -7;
    Exit;
  end;

  qry := nil;
  try
    qry := TZQuery.Create(nil);
    qry.Connection := cmAccountMgrImp.conFB;
    qry.Close;
    qry.SQL.Clear;
    qry.SQL.Add('select * from certificate ');
    try
      qry.Open;
      qry.First;
      while not qry.Eof do
      begin
        subjno := Trim(qry.fieldbyname('subjno').AsString);
        subjname := Trim(qry.fieldbyname('subjname').AsString);

        debit := qry.fieldbyname('debit').AsFloat;
        credit := qry.fieldbyname('credit').AsFloat;
        if subjno<>'' then
        begin
          if subjname='' then
          begin
            Context.GetDialogSystem.ShowMessage('科目['+subjno+']科目名称为空！');
            Result := -1;
            Exit;
          end;
          if debit+credit=0 then
          begin
            Context.GetDialogSystem.ShowMessage('科目['+subjno+']借,贷方金额都为零！');
            Result := -2;
            Exit;
          end;
        end;

        if debit+credit>0 then
        begin
          if subjno='' then
          begin
            Context.GetDialogSystem.ShowMessage('借,贷金额已经存在，科目不能为空');
            Result := -3;
            Exit;
          end;
        end;

        if subjno='' then
        begin
          qry.Next;
          Continue;
        end;
        
        qry.Next;
      end;
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage('凭证检查失败-'+e.Message);
      end;
    end;
  Result := 0;
  finally
    qry.Close;
    qry.Destroy;
  end;
end;

procedure TfaqhAccCertificate.ztblPZBeforeInsert(DataSet: TDataSet);
begin
  if ztblPZ.RecordCount>=4 then
  begin
    Context.GetDialogSystem.ShowMessage('目前只能支持4笔分录！');
    Exit;
  end;

end;

function TfaqhAccCertificate.saveVoucher: Integer;
var
  i:Integer;
begin
  i:=0;
  if ztblPZ.RecordCount=0 then
  begin
    Result := -1;
    Exit;
  end;
  WorkView.FieldByName('标志').Data.SetString('A');
  WorkView.FieldByName('单据数').Data.SetInteger(StrToInt(edtNum.Text));
  ztblPZ.First;
  if ztblPZ.FieldByName('subjno').AsString<>'' then
  begin
    Inc(i);
    WorkView.FieldByName('行号1').Data.SetInteger(i);
    WorkView.FieldByName('摘要1').Data.SetString(ztblPZ.fieldbyname('subjname').AsString);
    WorkView.FieldByName('科目代码1').Data.SetString(ztblPZ.fieldbyname('subjno').AsString);
    WorkView.FieldByName('借方金额1').Data.SetFloat(ztblPZ.fieldbyname('debit').AsFloat);
    WorkView.FieldByName('贷方金额1').Data.SetFloat(ztblPZ.fieldbyname('credit').AsFloat);
  end;
  ztblPZ.Next;
  if ztblPZ.FieldByName('subjno').AsString<>'' then
  begin
    Inc(i);
    WorkView.FieldByName('行号2').Data.SetInteger(i);
    WorkView.FieldByName('摘要2').Data.SetString(ztblPZ.fieldbyname('subjname').AsString);
    WorkView.FieldByName('科目代码2').Data.SetString(ztblPZ.fieldbyname('subjno').AsString);
    WorkView.FieldByName('借方金额2').Data.SetFloat(ztblPZ.fieldbyname('debit').AsFloat);
    WorkView.FieldByName('贷方金额2').Data.SetFloat(ztblPZ.fieldbyname('credit').AsFloat);
  end;
  ztblPZ.Next;
  if ztblPZ.FieldByName('subjno').AsString<>'' then
  begin
    Inc(i);
    WorkView.FieldByName('行号3').Data.SetInteger(i);
    WorkView.FieldByName('摘要3').Data.SetString(ztblPZ.fieldbyname('subjname').AsString);
    WorkView.FieldByName('科目代码3').Data.SetString(ztblPZ.fieldbyname('subjno').AsString);
    WorkView.FieldByName('借方金额3').Data.SetFloat(ztblPZ.fieldbyname('debit').AsFloat);
    WorkView.FieldByName('贷方金额3').Data.SetFloat(ztblPZ.fieldbyname('credit').AsFloat);
  end;
  ztblPZ.Next;
  if ztblPZ.FieldByName('subjno').AsString<>'' then
  begin
    Inc(i);
    WorkView.FieldByName('行号4').Data.SetInteger(i);
    WorkView.FieldByName('摘要4').Data.SetString(ztblPZ.fieldbyname('subjname').AsString);
    WorkView.FieldByName('科目代码4').Data.SetString(ztblPZ.fieldbyname('subjno').AsString);
    WorkView.FieldByName('借方金额4').Data.SetFloat(ztblPZ.fieldbyname('debit').AsFloat);
    WorkView.FieldByName('贷方金额4').Data.SetFloat(ztblPZ.fieldbyname('credit').AsFloat);
  end;
  WorkView.FieldByName('分录总条数').Data.SetInteger(i);
  try
    MainRequest.SendCommand;
    if WorkView.FieldByName('返回码').Data.AsString<>'0' then
    begin
      Context.GetDialogSystem.ShowMessage(WorkView.FieldByName('返回信息').Data.AsString);
      Result := -3;
      Exit;
    end;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowError(e.Message);
      Result := -2;
      Exit;
    end;
  end;
  Result :=0;
end;

initialization
  TUIStdClassFactory.Create('凭证录入',TfaqhAccCertificate);

end.