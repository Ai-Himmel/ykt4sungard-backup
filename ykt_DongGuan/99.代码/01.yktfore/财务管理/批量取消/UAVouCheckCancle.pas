unit UAVouCheckCancle;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  ComCtrls, RzListVw;

type
  TfaqhCheckCancle = class(TfaqhSimpleQueryTemp)
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
    procedure btnQueryClick(Sender: TObject);
    procedure btnCheckClick(Sender: TObject);
    procedure btnCancelCheckClick(Sender: TObject);
    procedure btnEnterClick(Sender: TObject);
    procedure chkSelectClick(Sender: TObject);
  private

    { Private declarations }
    function enterAccount(operSign:string;btn:TBitBtn):Integer;
    function selectSign:Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCheckCancle: TfaqhCheckCancle;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhCheckCancle.Init;
begin
  inherited;
  edtDate.Text := accountDate;
  edtYear.Text := Copy(accountDate,1,4);
  edtMonth.Text := Copy(accountDate,5,2);
  cbbManual.ItemIndex := 0;
end;

procedure TfaqhCheckCancle.btnQueryClick(Sender: TObject);
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
  WorkView.FieldByName('��ѯ����').Data.SetInteger(2);
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

function TfaqhCheckCancle.enterAccount(operSign: string;btn:TBitBtn): Integer;
var
  i:Integer;
  Id:Integer;
begin
  if selectSign<0 then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ�����ļ�¼��');
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

procedure TfaqhCheckCancle.btnCheckClick(Sender: TObject);
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

procedure TfaqhCheckCancle.btnCancelCheckClick(Sender: TObject);
begin
  if enterAccount('C',btnCancelCheck)<>0 then
    Exit;
  Context.GetDialogSystem.ShowMessage('����ȡ����˳ɹ���');

end;

procedure TfaqhCheckCancle.btnEnterClick(Sender: TObject);
begin
  if enterAccount('B',btnEnter)<>0 then
    Exit;
  Context.GetDialogSystem.ShowMessage('����ƾ֤���˳ɹ���');

end;

procedure TfaqhCheckCancle.chkSelectClick(Sender: TObject);
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

function TfaqhCheckCancle.selectSign: Integer;
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

initialization
  TUIStdClassFactory.Create('ƾ֤���ȡ��',TfaqhCheckCancle);

end.