unit UAVoucherMgr;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ExtCtrls, UICtrls, RzDBNav, RzButton, RzRadChk, RzDBGrid, RzTabs, Buttons,
  UIncrementComboBox, GridsEh, DBGridEh, ZAbstractRODataset,
  ZAbstractDataset, ZAbstractTable, ZDataset, sncCurrency, sncDBCurrency,
  RzPanel, RM_Common, RM_Class, RM_Dataset;

type
  TfaqhVoucherMgr = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    edtYear: TWVEdit;
    edtMonth: TWVEdit;
    edtQBDate: TWVEdit;
    edtVoucherNo: TWVEdit;
    WVEdit7: TWVEdit;
    cbbVoucherType: TWVComboBox;
    cbbStatus: TWVComboBox;
    cbbManual: TWVComboBox;
    pnlTop: TPanel;
    lbl1: TLabel;
    Label2: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    pnl1: TPanel;
    cbbVType: TWVComboBox;
    edtDate: TWVEdit;
    dbgrdh1: TDBGridEh;
    WVRequest1: TWVRequest;
    WorkView1: TWorkView;
    DataSource1: TDataSource;
    ztblPZ: TZTable;
    ztblPZcertificate: TStringField;
    ztblPZsubjname: TStringField;
    ztblPZdebit: TFloatField;
    ztblPZcredit: TFloatField;
    rzpnlTot: TRzPanel;
    lblUPCASE: TLabel;
    edtMoney: TsncDBCurrencyEdit;
    wvVoucherQ: TWorkView;
    wvrVoucherQ: TWVRequest;
    subjno: TStringField;
    pnl2: TPanel;
    lbl2: TLabel;
    lblOperName: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    cbbAccType: TWVComboBox;
    edtAccNo: TWVEdit;
    Label14: TLabel;
    cbbAccTypeQ: TWVComboBox;
    wvVQuery: TWorkView;
    edtNum: TWVEdit;
    lbl3: TLabel;
    lblAccount: TLabel;
    Label15: TLabel;
    lblCheck: TLabel;
    btnPrintVoucher: TBitBtn;
    rmDS1: TRMDBDataSet;
    rptQRpt: TRMReport;
    lbl4: TLabel;
    Label16: TLabel;
    edtQEDate: TWVEdit;
    procedure SetHighLightColor;
    procedure SetNormalColor;
    procedure btnAddClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure edtMoneyExit(Sender: TObject);
    procedure edtMoneyEnter(Sender: TObject);
    procedure edtMoneyKeyPress(Sender: TObject; var Key: Char);
    procedure edtMoneyMoveOut(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure dbgrdh1ColEnter(Sender: TObject);
    procedure dbgrdh1ColExit(Sender: TObject);
    procedure dbgrdh1DrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumnEh; State: TGridDrawState);
    procedure dbgrdh1KeyPress(Sender: TObject; var Key: Char);
    procedure btnChangeClick(Sender: TObject);
    procedure GridDblClick(Sender: TObject);
    procedure btnPrintVoucherClick(Sender: TObject);
  private

    { Private declarations }
    pvoucherNo,pvoucherType:string;
    procedure delTbl();
    procedure addRecord();
    function insertRecord(tempData:TDataSet):Integer;
    function editRecord():Integer;
    procedure newVoucher();
    function checkVoucher():Integer;
    function saveVoucher():Integer;
    procedure clearWV();
  public
    procedure Init; override;
    { Public declarations }
  end;

const
  CurrencyFieldSet: array[0..1] of string=('debit', 'credit');  //借方金额，贷方金额
var
  faqhVoucherMgr: TfaqhVoucherMgr;

implementation

uses KsFrameworks, UAccountMgrImp,KSClientConsts,SmartCardCommon, DataTypes,KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhVoucherMgr.Init;
begin
  inherited;
  edtYear.Text := Copy(accountDate,1,4);
  edtMonth.Text := Copy(accountDate,5,2);
  rzpnlTot.Left := 0;
  rzpnlTot.Top := dbgrdh1.Height-20;
  rzpnlTot.Width := dbgrdh1.Width;
  lblUPCASE.Caption := '';
  lblOperName.Caption := '';
  cbbManual.ItemIndex := 0;
  cbbStatus.ItemIndex := 0;
  cbbAccTypeQ.ItemIndex := 0;
  

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

procedure TfaqhVoucherMgr.btnAddClick(Sender: TObject);
begin
  clearWV;
  inherited;
  lblOperName.Caption := Context.ParamData(svOperatorNameName).AsString;
  lblAccount.Caption := '';
  lblCheck.Caption := '';
  pvoucherNo:='';
  pvoucherType:='';
  ztblPZ.Close;
  newVoucher;
  WorkView.FieldByName('标志').Data.SetString('A');
  WorkView.FieldByName('凭证日期').Data.SetString(accountDate);
  edtNum.ReadOnly := False;
  edtDate.ReadOnly := False;
  dbgrdh1.ReadOnly := False;
  //btnOK.Visible := True;
end;

procedure TfaqhVoucherMgr.btnDeleteClick(Sender: TObject);
var
  voucherType,voucherNo:Integer;
  syear,smonth:Integer;
  sdate:string;
  ticketNum:Integer;
  tempData:TDataSet;
  operName,checkName,accountName:string;
begin
  if wvVQuery.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('请先选择要修改的记录！');
    Exit;
  end;
  try
    tempData := TDataSet(wvVQuery.FieldByName('查询结果集').Data.AsObject);
    syear := tempData.fieldbyname('lvol10').AsInteger;
    smonth  := tempData.fieldbyname('lvol11').AsInteger;
    sdate := tempData.fieldbyname('sorder0').AsString;
    voucherType := tempData.fieldbyname('lsafe_level').AsInteger;
    voucherNo := tempData.fieldbyname('lserial0').AsInteger;
    ticketNum := tempData.fieldbyname('lbank_acc_type').AsInteger;
    operName := tempData.fieldbyname('semp_no').AsString;
    checkName :=  tempData.fieldbyname('scheck_emp').AsString;
    accountName := tempData.fieldbyname('schange_emp').AsString;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Exit;
    end;
  end;
  //delTbl;
  wvVoucherQ.FieldByName('标志').Data.SetString('R');
  wvVoucherQ.FieldByName('查询.会计期间(年)').Data.SetInteger(syear);
  wvVoucherQ.FieldByName('查询.会计期间(月)').Data.SetInteger(smonth);
  wvVoucherQ.FieldByName('查询.凭证日期').Data.SetString(sdate);
  wvVoucherQ.FieldByName('查询.凭证类型').Data.SetInteger(voucherType);
  wvVoucherQ.FieldByName('查询.凭证号').Data.SetInteger(voucherNo);
  try
    wvrVoucherQ.SendCommand;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Exit;
    end;
  end;
  if wvVoucherQ.FieldByName('查询结果集').Data.IsEmpty then
  begin
    //addRecord;
  end
  else
  begin
    tempData := TDataSet(wvVoucherQ.FieldByName('查询结果集').Data.AsObject);
    insertRecord(tempData);
  end;
  pvoucherNo:='';
  pvoucherType:='';
  clearWV;
  ztblPZ.Close;
  editRecord;
  inherited;
  WorkView.FieldByName('标志').Data.SetString('D');
  WorkView.FieldByName('凭证日期').Data.SetString(sdate);
  WorkView.FieldByName('年').Data.SetInteger(syear);
  WorkView.FieldByName('月').Data.SetInteger(smonth);
  WorkView.FieldByName('凭证号').Data.SetInteger(voucherNo);
  WorkView.FieldByName('凭证类型').Data.SetInteger(voucherType);
  lblOperName.Caption := GetIdObjectName(-30,operName);
  lblCheck.Caption := GetIdObjectName(-30,checkName);
  lblAccount.Caption := GetIdObjectName(-30,accountName);
  lblUPCASE.Caption := NtoC(dbgrdh1.Columns[3].Footer.SumValue);
  edtNum.Text := IntToStr(ticketNum);
  pvoucherNo := IntToStr(voucherNo);
  pvoucherType:= GetIdObjectName(-61,IntToStr(voucherType));
  edtNum.ReadOnly := True;
  edtDate.ReadOnly := True;
  dbgrdh1.ReadOnly := True;
  btnOK.SetFocus;
end;

procedure TfaqhVoucherMgr.btnOKClick(Sender: TObject);
begin
  //凭证合法性检测
  if checkVoucher<>0 then
    Exit;
  if Application.MessageBox('你确定要保存该凭证吗？',PChar(Application.Title),mb_yesno+mb_iconquestion)=idno then
    Exit;
  if saveVoucher<>0 then
    Exit;
  inherited;
  btnQuery.Click;
end;

procedure TfaqhVoucherMgr.btnQueryClick(Sender: TObject);
begin
  //clearWV;
  if Trim(edtYear.Text)='' then
    edtYear.Text := '0';

  if Trim(edtMonth.Text)='' then
    edtMonth.Text := '0';

  if Trim(edtVoucherNo.Text)='' then
    edtVoucherNo.Text := '0';
  if (Trim(edtYear.Text)<>'') and (Trim(edtYear.Text)<>'0') then
  begin
    try
      if (StrToInt(edtYear.Text)<=1900) or (StrToInt(edtYear.Text)>=2100) then
      begin
        Context.GetDialogSystem.ShowMessage('请输入有效的年份！');
        edtYear.SetFocus;
        Exit;
      end;
    except
      Context.GetDialogSystem.ShowMessage('请输入有效的年份！');
      edtYear.SetFocus;
      Exit;
    end;
  end;
  if (Trim(edtMonth.Text)<>'') and (Trim(edtMonth.Text)<>'0') then
  begin
    try
      if (StrToInt(edtMonth.Text)<=0) or (StrToInt(edtMonth.Text)>12) then
      begin
        Context.GetDialogSystem.ShowMessage('请输入有效的月份！');
        edtMonth.SetFocus;
        Exit;
      end;
    except
      Context.GetDialogSystem.ShowMessage('请输入有效的月份！');
      edtMonth.SetFocus;
      Exit;
    end;
  end;
  if Trim(edtQbDate.Text)<>'' then
  begin
    if CheckInputDateFormat(edtQbDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('请输入正确的日期，格式:yyyymmdd');
      edtQbDate.SetFocus;
      Exit;
    end;
  end;
  if Trim(edtQEDate.Text)<>'' then
  begin
    if CheckInputDateFormat(edtQEDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('请输入正确的日期，格式:yyyymmdd');
      edtQEDate.SetFocus;
      Exit;
    end;
  end;
  if (Trim(edtQEDate.Text)<>'') and (Trim(edtQbDate.Text)<>'') then
    if Trim(edtQbDate.Text)>Trim(edtQEDate.Text) then
      Context.GetDialogSystem.ShowMessage('开始日期不能大于结束日期!');
  wvVQuery.FieldByName('标志').Data.SetString('R');
  inherited;

end;

procedure TfaqhVoucherMgr.addRecord;
var
  qry:TZQuery;
  i:Integer;
begin
  qry := nil;
  try
    qry := TZQuery.Create(nil);
    qry.Connection := cmAccountMgrImp.conFB;
    try
      {
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add('BEGIN TRANSACTION');
      qry.ExecSQL;
      }
      for i:= 0 to 3 do
      begin
        qry.Close;
        qry.SQL.Clear;
        qry.SQL.Add('Insert into certificate(id) Values(:VoucherID)');
        qry.Params.ParamByName('VoucherID').Value := i;
        qry.ExecSQL;
      end;
      {
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add('COMMIT');
      qry.ExecSQL;
      }
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

function TfaqhVoucherMgr.checkVoucher: Integer;
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

  if cbbVType.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('请选择凭证类型！');
    cbbVType.SetFocus;
    Result := -3;
    Exit;
  end;
  
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

          if debit=credit then
          begin
            Context.GetDialogSystem.ShowMessage('借、贷方金额必须有一项为零！');
            Result := -2;
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

procedure TfaqhVoucherMgr.delTbl;
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

function TfaqhVoucherMgr.editRecord: Integer;
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

procedure TfaqhVoucherMgr.newVoucher;
begin
  delTbl;
  ztblPZ.Close;
  addRecord;
  dbgrdh1.SetFocus;
  dbgrdh1.SelectedIndex := 0;
end;

function TfaqhVoucherMgr.saveVoucher: Integer;
var
  i:Integer;
begin
  i:=0;
  if ztblPZ.RecordCount=0 then
  begin
    Result := -1;
    Exit;
  end;
  //WorkView.FieldByName('标志').Data.SetString('A');
  WorkView.FieldByName('单据数').Data.SetInteger(StrToInt(edtNum.Text));
  ztblPZ.First;
  if ztblPZ.FieldByName('subjno').AsString<>'' then
  begin
    Inc(i);
    WorkView.FieldByName('行号1').Data.SetInteger(i);
    WorkView.FieldByName('摘要1').Data.SetString(ztblPZ.fieldbyname('certificate').AsString);
    WorkView.FieldByName('科目代码1').Data.SetString(ztblPZ.fieldbyname('subjno').AsString);
    WorkView.FieldByName('借方金额1').Data.SetFloat(ztblPZ.fieldbyname('debit').AsFloat);
    WorkView.FieldByName('贷方金额1').Data.SetFloat(ztblPZ.fieldbyname('credit').AsFloat);
  end;
  ztblPZ.Next;
  if ztblPZ.FieldByName('subjno').AsString<>'' then
  begin
    Inc(i);
    WorkView.FieldByName('行号2').Data.SetInteger(i);
    WorkView.FieldByName('摘要2').Data.SetString(ztblPZ.fieldbyname('certificate').AsString);
    WorkView.FieldByName('科目代码2').Data.SetString(ztblPZ.fieldbyname('subjno').AsString);
    WorkView.FieldByName('借方金额2').Data.SetFloat(ztblPZ.fieldbyname('debit').AsFloat);
    WorkView.FieldByName('贷方金额2').Data.SetFloat(ztblPZ.fieldbyname('credit').AsFloat);
  end;
  ztblPZ.Next;
  if ztblPZ.FieldByName('subjno').AsString<>'' then
  begin
    Inc(i);
    WorkView.FieldByName('行号3').Data.SetInteger(i);
    WorkView.FieldByName('摘要3').Data.SetString(ztblPZ.fieldbyname('certificate').AsString);
    WorkView.FieldByName('科目代码3').Data.SetString(ztblPZ.fieldbyname('subjno').AsString);
    WorkView.FieldByName('借方金额3').Data.SetFloat(ztblPZ.fieldbyname('debit').AsFloat);
    WorkView.FieldByName('贷方金额3').Data.SetFloat(ztblPZ.fieldbyname('credit').AsFloat);
  end;
  ztblPZ.Next;
  if ztblPZ.FieldByName('subjno').AsString<>'' then
  begin
    Inc(i);
    WorkView.FieldByName('行号4').Data.SetInteger(i);
    WorkView.FieldByName('摘要4').Data.SetString(ztblPZ.fieldbyname('certificate').AsString);
    WorkView.FieldByName('科目代码4').Data.SetString(ztblPZ.fieldbyname('subjno').AsString);
    WorkView.FieldByName('借方金额4').Data.SetFloat(ztblPZ.fieldbyname('debit').AsFloat);
    WorkView.FieldByName('贷方金额4').Data.SetFloat(ztblPZ.fieldbyname('credit').AsFloat);
  end;
  WorkView.FieldByName('分录总条数').Data.SetInteger(i);
  Result :=0;
end;

procedure TfaqhVoucherMgr.SetHighLightColor;
begin
  edtMoney.Color := clHighLight;
  edtMoney.Font.Color := clWhite;
end;

procedure TfaqhVoucherMgr.SetNormalColor;
begin
  edtMoney.Color := dbgrdh1.Color;
  edtMoney.Font.Color := dbgrdh1.Font.Color;
end;

procedure TfaqhVoucherMgr.edtMoneyExit(Sender: TObject);
begin
  SetHighLightColor;
  ztblPZ.Post;
  editRecord;
  lblUPCASE.Caption := NtoC(dbgrdh1.Columns[3].Footer.SumValue);
end;

procedure TfaqhVoucherMgr.edtMoneyEnter(Sender: TObject);
begin
  SetNormalColor;
end;

procedure TfaqhVoucherMgr.edtMoneyKeyPress(Sender: TObject; var Key: Char);
begin
  if Key=Chr(VK_RETURN) then
  begin
    dbgrdh1.SetFocus;
    ztblPZ.Post;
    editRecord;
    lblUPCASE.Caption := NtoC(dbgrdh1.Columns[3].Footer.SumValue);
  end;
end;

procedure TfaqhVoucherMgr.edtMoneyMoveOut(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  case Key of
    VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT:
    begin
      dbgrdh1.SetFocus;
      SendMessage(dbgrdh1.Handle, WM_KEYDOWN, WORD(Key), 0);
    end;
  end;
end;

procedure TfaqhVoucherMgr.dbgrdh1ColEnter(Sender: TObject);
begin
  if CheckCurrencyField(dbgrdh1.SelectedField.FieldName) then
  begin
    edtMoney.DataField := dbgrdh1.SelectedField.FieldName;
    edtMoney.Tag := 1;
  end;
end;

procedure TfaqhVoucherMgr.dbgrdh1ColExit(Sender: TObject);
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
    WorkView1.FieldByName('标志').Data.SetInteger(1);
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

procedure TfaqhVoucherMgr.dbgrdh1DrawColumnCell(Sender: TObject;
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

procedure TfaqhVoucherMgr.dbgrdh1KeyPress(Sender: TObject; var Key: Char);
begin
  if (key<>chr(9)) and CheckCurrencyField(dbgrdh1.SelectedField.FieldName) then
  begin
    edtMoney.SetFocus;
    SendMessage(edtMoney.Handle, WM_Char, WORD(Key), 0);
  end;
end;

procedure TfaqhVoucherMgr.clearWV;

var
  iwv:Integer;
  //icomp:Integer;
  //wv:TWorkView;
begin
  {
  for icomp := 0 to Self.ComponentCount-1 do
  begin
    if Self.Components[icomp] is TWorkView then
    begin
      wv := TWorkView(Self.Components[icomp]);
      for iwv := 0 to wv.FieldCount-1 do
      begin
        if (wv.Fields[iwv].DataType = kdtInteger) or (wv.Fields[iwv].DataType = kdtFloat) then
          wv.FieldByName(wv.Fields[iwv].Name).DefaultValue := 0
        else if wv.Fields[iwv].DataType = kdtstring then
          wv.FieldByName(wv.Fields[iwv].Name).DefaultValue := '';
      end;
      wv.Reset;
    end;
  end;
  }
  for iwv := 12 to WorkView.FieldCount-1 do
  begin
    if (WorkView.Fields[iwv].DataType = kdtInteger) or (WorkView.Fields[iwv].DataType = kdtFloat) then
      WorkView.FieldByName(WorkView.Fields[iwv].Name).DefaultValue := 0
    else if WorkView.Fields[iwv].DataType = kdtstring then
      WorkView.FieldByName(WorkView.Fields[iwv].Name).DefaultValue := '';
  end;
  WorkView.Reset;
end;

procedure TfaqhVoucherMgr.btnChangeClick(Sender: TObject);
var
  voucherType,voucherNo:Integer;
  syear,smonth:Integer;
  sdate:string;
  ticketNum:Integer;
  tempData:TDataSet;
  operName,checkName,accountName:string;
begin
  if wvVQuery.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('请先选择要修改的记录！');
    Exit;
  end;
  try
    tempData := TDataSet(wvVQuery.FieldByName('查询结果集').Data.AsObject);
    sdate := tempData.fieldbyname('sorder0').AsString;
    voucherType := tempData.fieldbyname('lsafe_level').AsInteger;
    voucherNo := tempData.fieldbyname('lserial0').AsInteger;
    ticketNum := tempData.fieldbyname('lbank_acc_type').AsInteger;
    syear := tempData.fieldbyname('lvol10').AsInteger;
    smonth  := tempData.fieldbyname('lvol11').AsInteger;
    
    operName := tempData.fieldbyname('semp_no').AsString;
    checkName :=  tempData.fieldbyname('scheck_emp').AsString;
    accountName := tempData.fieldbyname('schange_emp').AsString;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Exit;
    end;
  end;
  clearWV;
  pvoucherNo:='';
  pvoucherType:='';
  wvVoucherQ.FieldByName('标志').Data.SetString('R');
  wvVoucherQ.FieldByName('查询.会计期间(年)').Data.SetInteger(syear);
  wvVoucherQ.FieldByName('查询.会计期间(月)').Data.SetInteger(smonth);
  wvVoucherQ.FieldByName('查询.凭证日期').Data.SetString(sdate);
  wvVoucherQ.FieldByName('查询.凭证类型').Data.SetInteger(voucherType);
  wvVoucherQ.FieldByName('查询.凭证号').Data.SetInteger(voucherNo);
  try
    wvrVoucherQ.SendCommand;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Exit;
    end;
  end;
  if wvVoucherQ.FieldByName('查询结果集').Data.IsEmpty then
  begin
    //addRecord;
  end
  else
  begin
    tempData := TDataSet(wvVoucherQ.FieldByName('查询结果集').Data.AsObject);
    insertRecord(tempData);
  end;
  ztblPZ.Close;
  editRecord;
  inherited;
  WorkView.FieldByName('标志').Data.SetString('U');
  WorkView.FieldByName('凭证日期').Data.SetString(sdate);
  WorkView.FieldByName('年').Data.SetInteger(syear);
  WorkView.FieldByName('月').Data.SetInteger(smonth);
  WorkView.FieldByName('凭证号').Data.SetInteger(voucherNo);
  WorkView.FieldByName('凭证类型').Data.SetInteger(voucherType);
  pvoucherNo := IntToStr(voucherNo);
  pvoucherType := GetIdObjectName(-61,IntToStr(voucherType));
  lblOperName.Caption := GetIdObjectName(-30,operName);
  lblCheck.Caption := GetIdObjectName(-30,checkName);
  lblAccount.Caption := GetIdObjectName(-30,accountName);
  lblUPCASE.Caption := NtoC(dbgrdh1.Columns[3].Footer.SumValue);
  edtNum.Text := IntToStr(ticketNum);
  edtNum.ReadOnly := False;
  edtDate.ReadOnly := False;
  dbgrdh1.ReadOnly := False;
  btnOK.SetFocus;
end;

function TfaqhVoucherMgr.insertRecord(tempData:TDataSet): Integer;
var
  qry:TZQuery;
  i,ai:Integer;
begin
  delTbl;
  qry := nil;
  i := 0;
  try
    qry := TZQuery.Create(nil);
    qry.Connection := cmAccountMgrImp.conFB;
    try
      {
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add('BEGIN TRANSACTION');
      qry.ExecSQL;
      }
      tempData.First;
      while not tempData.Eof do
      begin
        Inc(i);
        qry.Close;
        qry.SQL.Clear;
        qry.SQL.Add('Insert into certificate(id,certificate,subjno,subjname,debit,credit) Values(:VoucherID,:certificate,:subjno,:subjname,:debit,:credit)');
        qry.Params.ParamByName('VoucherID').Value := i;
        qry.Params.ParamByName('certificate').Value := tempData.fieldbyname('snote').AsString;
        qry.Params.ParamByName('subjno').Value := tempData.fieldbyname('scust_auth').AsString;
        qry.Params.ParamByName('subjname').Value := tempData.fieldbyname('scusttypes').AsString;
        qry.Params.ParamByName('debit').Value := tempData.fieldbyname('damt1').AsFloat;
        qry.Params.ParamByName('credit').Value := tempData.fieldbyname('damt2').AsFloat;
        qry.ExecSQL;
        tempData.Next;
      end;
      if i<4 then
      begin
        inc(i);
        for ai:=i to 4 do
        begin
          qry.Close;
          qry.SQL.Clear;
          qry.SQL.Add('Insert into certificate(id) Values(:VoucherID)');
          qry.Params.ParamByName('VoucherID').Value := ai;
          qry.ExecSQL;
        end;
      end;
      {
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add('COMMIT');
      qry.ExecSQL;
      }
    except
      on e:Exception do
        Context.GetDialogSystem.ShowMessage(e.Message);
    end;
    editRecord;
  finally
    qry.Close;
    qry.Destroy;
  end;
  Result := 0;
end;

procedure TfaqhVoucherMgr.GridDblClick(Sender: TObject);
{
var
  voucherType,voucherNo:Integer;
  syear,smonth:Integer;
  sdate:string;
  ticketNum:Integer;
  tempData:TDataSet;
  operName,checkName,accountName:string;
  }
begin
  {
  if wvVQuery.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('请先选择要修改的记录！');
    Exit;
  end;
  try
    tempData := TDataSet(wvVQuery.FieldByName('查询结果集').Data.AsObject);
    syear := tempData.fieldbyname('lvol10').AsInteger;
    smonth  := tempData.fieldbyname('lvol11').AsInteger;
    sdate := tempData.fieldbyname('sorder0').AsString;
    voucherType := tempData.fieldbyname('lsafe_level').AsInteger;
    voucherNo := tempData.fieldbyname('lserial0').AsInteger;
    ticketNum := tempData.fieldbyname('lbank_acc_type').AsInteger;
    operName := tempData.fieldbyname('semp_no').AsString;
    checkName :=  tempData.fieldbyname('scheck_emp').AsString;
    accountName := tempData.fieldbyname('schange_emp').AsString;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Exit;
    end;
  end;
  //delTbl;
  wvVoucherQ.FieldByName('标志').Data.SetString('R');
  wvVoucherQ.FieldByName('查询.会计期间(年)').Data.SetInteger(syear);
  wvVoucherQ.FieldByName('查询.会计期间(月)').Data.SetInteger(smonth);
  wvVoucherQ.FieldByName('查询.凭证日期').Data.SetString(sdate);
  wvVoucherQ.FieldByName('查询.凭证类型').Data.SetInteger(voucherType);
  wvVoucherQ.FieldByName('查询.凭证号').Data.SetInteger(voucherNo);
  try
    wvrVoucherQ.SendCommand;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Exit;
    end;
  end;
  if wvVoucherQ.FieldByName('查询结果集').Data.IsEmpty then
  begin
    //addRecord;
  end
  else
  begin
    tempData := TDataSet(wvVoucherQ.FieldByName('查询结果集').Data.AsObject);
    insertRecord(tempData);
  end;

  clearWV;
  ztblPZ.Close;
  editRecord;
  inherited;
  WorkView.FieldByName('标志').Data.SetString('D');
  WorkView.FieldByName('凭证日期').Data.SetString(sysDate);
  WorkView.FieldByName('年').Data.SetInteger(syear);
  WorkView.FieldByName('月').Data.SetInteger(smonth);
  WorkView.FieldByName('凭证号').Data.SetInteger(voucherNo);
  WorkView.FieldByName('凭证类型').Data.SetInteger(voucherType);
  pvoucherNo := IntToStr(voucherNo);
  pvoucherType := GetIdObjectName(-61,IntToStr(voucherType));
  lblOperName.Caption := GetIdObjectName(-30,operName);
  lblCheck.Caption := GetIdObjectName(-30,checkName);
  lblAccount.Caption := GetIdObjectName(-30,accountName);
  edtNum.Text := IntToStr(ticketNum);
  edtNum.ReadOnly := True;
  edtDate.ReadOnly := True;
  dbgrdh1.ReadOnly := True;
  }
  btnChange.Click;
end;

procedure TfaqhVoucherMgr.btnPrintVoucherClick(Sender: TObject);
var
  i:Integer;
begin
  if (pvoucherNo='') or (pvoucherNo='0') then
  begin
    Context.GetDialogSystem.ShowMessage('该凭证还没有生成凭证号，不能打印！');
    Exit;
  end;
  for i:=Length(pvoucherNo) to 3 do
  begin
    pvoucherNo := '0'+pvoucherNo;
  end;
  rptQRpt.LoadFromFile(sPreAppPath+'report\Account\凭证打印.rmf');
  //rptQRpt.Dictionary.Variables.AsString['totMoneyCN'] := lblUPCASE.Caption;
  rptQRpt.Dictionary.Variables.AsString['totMoney'] := FloatToStr(dbgrdh1.Columns[3].Footer.SumValue);
  rptQRpt.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
  rptQRpt.Dictionary.Variables.AsString['voucherNo'] := pvouchertype+'-'+pvoucherNo;
  rptQRpt.Dictionary.Variables.AsString['ticketNum'] := edtNum.Text;
  rptQRpt.Dictionary.Variables.AsString['oper'] := lblOperName.Caption;
  rptQRpt.Dictionary.Variables.AsString['check'] := lblCheck.Caption;
  rptQRpt.Dictionary.Variables.AsString['account'] := lblAccount.Caption;
  //rptQRpt.Dictionary.Variables.AsString['voucherNo'] := lblAccount.Caption;
  //rptQRpt.Dictionary.Variables.AsString['account'] := lblAccount.Caption;
  rptQRpt.DoublePass := True;
  rptQRpt.ShowReport;
end;

initialization
  TUIStdClassFactory.Create('凭证管理',TfaqhVoucherMgr);

end.