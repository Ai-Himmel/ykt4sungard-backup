unit UAVouPatchCheck;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  ComCtrls, RzListVw, ZAbstractRODataset,ZAbstractDataset, ZAbstractTable, ZDataset;

type
  TfaqhPatchCheck = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label9: TLabel;
    edtYear: TWVEdit;
    edtMonth: TWVEdit;
    edtDate: TWVEdit;
    edtVoucherNo: TWVEdit;
    cbbVoucherType: TWVComboBox;
    cbbManual: TWVComboBox;
    btnCheck: TBitBtn;
    btnCancelCheck: TBitBtn;
    btnEnter: TBitBtn;
    wvVOper: TWorkView;
    wvrVOper: TWVRequest;
    lvVoucher: TRzListView;
    chkSelect: TWVCheckBox;
    wvVoucherQ: TWorkView;
    wvrVoucherQ: TWVRequest;
    procedure btnQueryClick(Sender: TObject);
    procedure btnCheckClick(Sender: TObject);
    procedure btnCancelCheckClick(Sender: TObject);
    procedure btnEnterClick(Sender: TObject);
    procedure chkSelectClick(Sender: TObject);
    procedure lvVoucherClick(Sender: TObject);
  private

    { Private declarations }
    function enterAccount(operSign:string;btn:TBitBtn):Integer;
    function selectSign:Integer;

    function insertRecord(tempData:TDataSet):Integer;
    //function editRecord: Integer;
    procedure  delTbl;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhPatchCheck: TfaqhPatchCheck;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon,
  UAccountMgrImp, UVoucherDetail;
     
{$R *.DFM}

procedure TfaqhPatchCheck.Init;
begin
  inherited;
  edtDate.Text := accountDate;
  edtYear.Text := Copy(accountDate,1,4);
  edtMonth.Text := Copy(accountDate,5,2);
  cbbManual.ItemIndex := 0;
end;

procedure TfaqhPatchCheck.btnQueryClick(Sender: TObject);
var
  tempData:TDataSet;
  tmpItem: TListItem;
begin
  lvVoucher.Items.Clear;
  chkSelect.Checked := False;
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
        Context.GetDialogSystem.ShowMessage('��������Ч����ݣ�');
        edtYear.SetFocus;
        Exit;
      end;
    except
      Context.GetDialogSystem.ShowMessage('��������Ч����ݣ�');
      edtYear.SetFocus;
      Exit;
    end;
  end;
  if (Trim(edtMonth.Text)<>'') and (Trim(edtMonth.Text)<>'0') then
  begin
    try
      if (StrToInt(edtMonth.Text)<=0) or (StrToInt(edtMonth.Text)>12) then
      begin
        Context.GetDialogSystem.ShowMessage('��������Ч���·ݣ�');
        edtMonth.SetFocus;
        Exit;
      end;
    except
      Context.GetDialogSystem.ShowMessage('��������Ч���·ݣ�');
      edtMonth.SetFocus;
      Exit;
    end;
  end;
  if Trim(edtDate.Text)<>'' then
  begin
    if CheckInputDateFormat(edtDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('��������ȷ�����ڣ���ʽ:yyyymmdd');
      edtDate.SetFocus;
      Exit;
    end;
  end;

  WorkView.FieldByName('��־').Data.SetString('Q');
  WorkView.FieldByName('��ѯ����').Data.SetInteger(1);
  inherited;
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
    exit;
  tempData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  tempData.First;
  while not tempData.Eof do
  begin
    try
      tmpItem := lvVoucher.Items.Add;
      //ƾ֤����
      tmpItem.Caption := tempData.fieldbyname('sorder0').AsString;
      //ID
      tmpItem.SubItems.Add(tempData.fieldbyname('lserial1').AsString);
      //ƾ֤��
      tmpItem.SubItems.Add(tempData.fieldbyname('sphone').AsString);
      //ժҪ
      tmpItem.SubItems.Add(tempData.fieldbyname('snote').AsString);
      //�跽���
      tmpItem.SubItems.Add(tempData.fieldbyname('damt1').AsString);
      //�������
      tmpItem.SubItems.Add(tempData.fieldbyname('damt2').AsString);
      //���״̬
      tmpItem.SubItems.Add(GetIdObjectName(160,tempData.fieldbyname('lsafe_level2').AsString));
      //����״̬
      tmpItem.SubItems.Add(GetIdObjectName(161,tempData.fieldbyname('lvol5').AsString));
      //�ֹ��˱�־
      tmpItem.SubItems.Add(GetIdObjectName(162,tempData.fieldbyname('lbank_acc_type2').AsString));
      //�Ƶ�
      tmpItem.SubItems.Add(GetIdObjectName(-30,tempData.fieldbyname('semp_no').AsString));
      //����
      tmpItem.SubItems.Add(GetIdObjectName(-30,tempData.fieldbyname('sclose_emp').AsString));
      //���
      tmpItem.SubItems.Add(GetIdObjectName(-30,tempData.fieldbyname('scheck_emp').AsString));
      //����
      tmpItem.SubItems.Add(GetIdObjectName(-30,tempData.fieldbyname('schange_emp').AsString));
    except
    end;
    tempData.Next;
  end;
end;

function TfaqhPatchCheck.enterAccount(operSign: string;btn:TBitBtn): Integer;
var
  i:Integer;
  Id:Integer;
begin
  if selectSign<0 then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ�����ļ�¼��');
    Result := -1;
    Exit;
  end;
  if Application.MessageBox(PChar('��ȷ��Ҫִ��'+btn.Caption+'������'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
  begin
    Result := -4;
    Exit;
  end;
  for i:=0 to lvVoucher.Items.Count-1 do
  begin
    if lvVoucher.Items[i].Checked then
    begin
      id:=StrToInt(lvVoucher.Items[i].SubItems[0]);
      wvVOper.FieldByName('��־').Data.SetString(operSign);
      wvVOper.FieldByName('����ڼ�(��)').Data.SetInteger(0);
      wvVOper.FieldByName('����ڼ�(��)').Data.SetInteger(0);
      wvVOper.FieldByName('ƾ֤����').Data.SetInteger(0);
      wvVOper.FieldByName('ƾ֤��').Data.SetInteger(0);
      wvVOper.FieldByName('ƾ֤ID').Data.SetInteger(Id);
      try
        wvrVOper.SendCommand;
        if wvVOper.FieldByName('������').Data.AsString<>'0' then
        begin
          Context.GetDialogSystem.ShowMessage(wvVOper.FieldByName('������Ϣ').Data.AsString);
          Result := -2;
          Exit;
        end;
      except
        on e:Exception do
        begin
          Context.GetDialogSystem.ShowMessage(e.Message);
          Result := -3;
          Exit;
        end;
      end;
    end;
  end;
  Result := 0;
end;

procedure TfaqhPatchCheck.btnCheckClick(Sender: TObject);
begin
  if selectSign<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ��������ļ�¼!');
    Exit;
  end;
  if enterAccount('K',btnCheck)<>0 then
    Exit;
  Context.GetDialogSystem.ShowMessage('�������ƾ֤�ɹ���');
end;

procedure TfaqhPatchCheck.btnCancelCheckClick(Sender: TObject);
begin
  if enterAccount('C',btnCancelCheck)<>0 then
    Exit;
  Context.GetDialogSystem.ShowMessage('����ȡ����˳ɹ���');

end;

procedure TfaqhPatchCheck.btnEnterClick(Sender: TObject);
begin
  if enterAccount('B',btnEnter)<>0 then
    Exit;
  Context.GetDialogSystem.ShowMessage('����ƾ֤���˳ɹ���');

end;

procedure TfaqhPatchCheck.chkSelectClick(Sender: TObject);
var
  i: integer;
begin
  if lvVoucher.Items.Count = 0 then
  begin
    Exit;
  end;
  if chkSelect.Checked = True then
  begin
    for i := 0 to lvVoucher.Items.Count - 1 do
    begin
      lvVoucher.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to lvVoucher.Items.Count - 1 do
    begin
      lvVoucher.Items[i].Checked := False;
    end;
  end;
end;

function TfaqhPatchCheck.selectSign: Integer;
var
  i:Integer;
begin
  Result := -1;
  for i := 0 to lvVoucher.Items.Count-1 do
  begin
    if lvVoucher.Items[i].Checked then
    begin
      Result := 0;
      Exit;
    end;
  end;
end;

procedure TfaqhPatchCheck.lvVoucherClick(Sender: TObject);
var
  voucherID:Integer;
  tempData:TDataSet;
begin
  Exit;
  try
    voucherID := StrToInt(lvVoucher.Items[lvVoucher.Selected.Index].SubItems[0])
  except
    Exit;
  end;
  wvVoucherQ.FieldByName('��־').Data.SetString('R');
  wvVoucherQ.FieldByName('��ѯ.����ڼ�(��)').Data.SetInteger(0);
  wvVoucherQ.FieldByName('��ѯ.����ڼ�(��)').Data.SetInteger(0);
  wvVoucherQ.FieldByName('��ѯ.ƾ֤����').Data.SetString('');
  wvVoucherQ.FieldByName('��ѯ.ƾ֤����').Data.SetInteger(0);
  wvVoucherQ.FieldByName('��ѯ.ƾ֤��').Data.SetInteger(0);
  wvVoucherQ.FieldByName('��ѯ.ID').Data.SetInteger(voucherID);
  try
    wvrVoucherQ.SendCommand;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Exit;
    end;
  end;
  if wvVoucherQ.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    //addRecord;
  end
  else
  begin
    tempData := TDataSet(wvVoucherQ.FieldByName('��ѯ�����').Data.AsObject);
    insertRecord(tempData);
    tempData.First;
    try
      frmVoucherDetail := TfrmVoucherDetail.Create(nil);
      //ȡ��һ����¼�õ�����Ա�����˲���Ա��ƾ֤���ͣ���������
      frmVoucherDetail.sAccount := tempData.fieldbyname('schange_emp').AsString;
      frmVoucherDetail.sOper := tempData.fieldbyname('semp_no').AsString;
      frmVoucherDetail.sCheck := tempData.fieldbyname('scheck_emp').AsString;
      frmVoucherDetail.calcType := tempData.fieldbyname('lvol9').AsString;
      frmVoucherDetail.calcNo := tempData.fieldbyname('sname2').AsString;
      //frmVoucherDetail.caseUp := tempData.fieldbyname('').AsString;
      frmVoucherDetail.voucherType := tempData.fieldbyname('lsafe_level').AsString;
      frmVoucherDetail.ticketNum := tempData.fieldbyname('lbank_acc_type').AsString;
      frmVoucherDetail.ShowModal;
      frmVoucherDetail.Close;
    finally
      frmVoucherDetail.Destroy;
    end;
  end;
  //ƾ֤��ϸ����ʱ����
  //ztblPZ.Close;
  //editRecord;
end;

function TfaqhPatchCheck.insertRecord(tempData: TDataSet): Integer;
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
    except
      on e:Exception do
        Context.GetDialogSystem.ShowMessage(e.Message);
    end;
    //editRecord;
  finally
    qry.Close;
    qry.Destroy;
  end;
  Result := 0;
end;

procedure TfaqhPatchCheck.delTbl;
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

initialization
  TUIStdClassFactory.Create('ƾ֤�������',TfaqhPatchCheck);

end.