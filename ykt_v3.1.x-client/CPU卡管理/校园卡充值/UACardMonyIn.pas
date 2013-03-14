unit UACardMonyIn;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox,RzStatus, EditExts, CardDll, RzEdit,
  Buttons;

type
  TfaqhCardMonyIn = class(TfaqhSimpleQueryTemp)
    btnReadCardInfo: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    grp1: TGroupBox;
    WVLabel5: TWVLabel;
    edtName: TRzEdit;
    edtCardNo: TRzEdit;
    edtStuempNo: TRzEdit;
    edtCardMoney: TRzEdit;
    grp2: TGroupBox;
    cbbType: TWVComboBox;
    edtTicketNo: TWVEdit;
    WVLabel3: TWVLabel;
    edtAfterMoney: TRzEdit;
    WVLabel10: TWVLabel;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    RzStatusPane7: TRzStatusPane;
    RzStatusPane8: TRzStatusPane;
    RzStatusPane9: TRzStatusPane;
    btnMoneyIn: TBitBtn;
    lblTip: TLabel;
    WVRcashOperCancel: TWVRequest;
    WVcashOperCancel: TWorkView;
    WVLabel1: TWVLabel;
    edtmoneymoneymoney: TRzNumericEdit;
    edtmoney: TWVDigitalEdit;
    chkSaveMoney: TCheckBox;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    procedure btnMoneyInClick(Sender: TObject);
    procedure cbbTypeChange(Sender: TObject);
    procedure WVEdit6KeyPress(Sender: TObject; var Key: Char);
    procedure btnReadCardInfoClick(Sender: TObject);
    procedure cbbTypeKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure edtmoneyKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
  private
    { Private declarations }
    oldPhyId:string;
    function readCardInfo(cm:TCM): Boolean;

    procedure writeSuccess(wv: TWorkView;money:Integer;cm:TCM);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardMonyIn: TfaqhCardMonyIn;
  OldMoney: string;

implementation

uses KsFrameworks, KSClientConsts,SmartCardCommon;

{$R *.DFM}

procedure TfaqhCardMonyIn.Init;
begin
  inherited;
  lblTip.Caption := '';
  cbbType.ItemIndex:=0;
  edtTicketNo.Enabled := False;
  btnMoneyIn.Enabled:=False;
  btnReadCardInfo.SetFocus;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaqhCardMonyIn.btnMoneyInClick(Sender: TObject);
var
  //CardPhyID: string;
  payCnt,dptCnt,subsidyNo:Integer;
  balance:Integer;
  OutMoney: Integer;
  rCardNo:Integer;

  rTradeDate:string;
  rTradeTime:string;
  rStationNo:string;
  //SeilID: integer;
  cm: TCM;
  //TOF: Integer;
  //NewMoney: Integer;
  tp:TTRANSPACK;
  //reErrMsg:array[0..255] of Char;
  //reSt : PChar;
  st:integer;
  phyId:string;
begin
  if StrToInt(Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1))<>1 then
    if Trim(edtTicketNo.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('������Ʊ�ݺ��룡');
      edtTicketNo.SetFocus;
      Exit;
    end;
  if ((trim(edtmoney.Text) = '') or (edtMoney.text = '0') or (edtMoney.text = '0.0') or (edtMoney.text = '0.00')) then
  begin
    Context.GetDialogSystem.ShowMessage('����Ľ��С��λ������Ϊ�ջ�0��');
    edtMoney.SetFocus;
    Exit;
  end;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ����ȷ��úÿ���');
      exit;
    end;
    cm.clearallfieldreadmode;
    //setOperReadMode(cm);

    //cm.setfieldreadmode(CARD_SERI_NO);
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(PATCH_NO);
    cm.setfieldreadmode(BLACK_CARD_SIGN);
    cm.setfieldreadmode(DEADLINE_DATE);
    if cm.readCard(phyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣʧ��-'+geterrmsg);
      Exit;
    end;
    if (cm.getDeadLineDate<FormatDateTime('yyyymmdd',Date()))then
    begin
      Context.GetDialogSystem.ShowMessage('���ѹ��ڣ����ܳ�ֵ��');
      Exit;
    end;
    if cm.getBlackCardSign<>'0' then
    begin
      Context.GetDialogSystem.ShowMessage('�ÿ���������״̬�Ŀ�������ת�ˣ��뵽������Ϣ�ж�ȡ��״̬��');
      Exit;
    end;
    {
    CardPhyID := cm.getCardSeriNo;
    if CardPhyID='' then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ������ʧ�ܣ�');
      Exit;
    end
    else
    begin
      WorkView.FieldByName('������').Data.SetString(CardPhyID);
    end;
    }
    if oldPhyId <> phyId then
    begin
      Context.GetDialogSystem.ShowMessage('��ʹ��ͬһ�ſ����г�ֵ��');
      btnReadCardInfo.SetFocus;
      btnMoneyIn.Enabled := False;
      Exit;
    end;
    //��ȡ��ֵ�Ľ��״���
    try
      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      subsidyNo := StrToInt(cm.getPatchNo);
      balance := StrToInt(cm.getCardBalance);
    except
      Context.GetDialogSystem.ShowMessage('��ȡ�����Ѵ���ʧ�ܣ�����ȡ����');
      Exit;
    end;
    //���͹��ܺ�
    WorkView.FieldByName('������').Data.SetString(phyId);
    WorkView.FieldByName('����').Data.SetInteger(StrToInt(edtCardNo.Text));
    WorkView.FieldByName('�뿨���').Data.SetInteger(balance);
    WorkView.FieldByName('���״���').Data.SetInteger(dptCnt);
    WorkView.FieldByName('���Ѵ���').Data.SetInteger(payCnt);
    WorkView.FieldByName('��ֵ����').Data.SetInteger(StrToInt(Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1)));
    WorkView.FieldByName('��ֵ���').Data.SetFloat(StrToFloat(edtMoney.Text));
    MainRequest.SendCommand;
    if WorkView.fieldbyname('������').data.asinteger<>0 then
    begin
      getReturn('',WorkView);
      RzStatusPane2.Caption:=WorkView.FieldByName('������Ϣ').Data.AsString;
      Exit;
    end;
    OutMoney := WorkView.FieldByName('�������').Data.AsInteger;
    //SeilID := WorkView.FieldByName('��ˮ��').Data.AsInteger;
    rCardNo := WorkView.FieldByName('����').Data.AsInteger;
    rTradeDate := WorkView.FieldByName('ҵ������').Data.AsString;
    rtradetime := WorkView.FieldByName('ҵ��ʱ��').Data.AsString;
    rStationNo := WorkView.FieldByName('�ն˱��').Data.AsString;
    //preSetMoney(tp);
    ZeroMemory(@tp,SizeOf(tp));
    //�ն˽������к�
    tp.TermSeqno := 1;
    //�ն˱��
    StrCopy(@tp.Termno,PChar(scSiteNo));
    //���׿���
    tp.CardNo := rCardNo;
    //������
    StrCopy(@tp.CardPhyID,PChar(phyId));
    //��������
    StrCopy(@tp.TransDate,PChar(rTradeDate));
    //����ʱ��
    StrCopy(@tp.TransTime,PChar(rtradeTime));
    //����ǰ���
    tp.BefBalance := balance;
    //���׺���
    tp.AftBalance := OutMoney;
    //����ǰ��ֵ����
    tp.DptCardCnt := dptCnt;
    //����ǰ���Ѵ���
    tp.PayCardCnt := payCnt;
    //����ǰ��������
    tp.SubsidyNo := subsidyNo;
    //�޸����ý�ʽ
    if setCardBal(tp,cm,phyId)<>0 then
      Exit;
    writeSuccess(WorkView,OutMoney,cm);
    {
    tof := ks_setcardbal(@tp);
    if tof = 0 then
    begin
      writeSuccess(WorkView,OutMoney,cm);
    end
    else
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      Context.GetDialogSystem.ShowMessage(reSt);
      RzStatusPane2.Caption:=cashOperCancel(WVcashOperCancel,WVRcashOperCancel,rTradeDate,SeilID,StrToInt(scsiteno));
    end;
    }
    //cm.halt;
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhCardMonyIn.cbbTypeChange(Sender: TObject);
begin
  inherited;
  edtTicketNo.Text:='';
  if (cbbType.ItemIndex = 0) then
  begin
    edtmoneymoneymoney.Enabled := True;
    edtTicketNo.Enabled := False;
  end
  else
  begin
    edtmoneymoneymoney.Enabled := True;
    edtTicketNo.Enabled := True;
  end;
end;

procedure TfaqhCardMonyIn.WVEdit6KeyPress(Sender: TObject; var Key: Char);
begin
  //inherited;
  if Checkedt(Key,edtMoney.Text)=False then
    Key := #0;
end;

function TfaqhCardMonyIn.readCardInfo(cm: TCM): Boolean;
var
  //CardExID: string;
  cardPhyId:string;
  CardState:string;
  st:Integer;

begin
  Result := False;
  if preReadCard=False then
    Exit;
  st := cm.card(cardPhyId);
  if st<>0 then
  begin
    context.GetDialogSystem.ShowMessage('Ѱ��ʧ��-'+geterrmsg);
    exit;
  end;

  oldPhyId := CardPhyID;
  //��������еĶ�ȡȨ��
  cm.clearallfieldreadmode;
  //����Ҫ��ȡ���ݵ�Ȩ��
  cm.setfieldreadmode(CARD_NO);
  cm.setfieldreadmode(CUST_NAME);
  cm.setfieldreadmode(STUEMP_NO);
  cm.setfieldreadmode(CARD_BALANCE);

  //setOperReadMode(cm);
  st := cm.readCard(cardPhyId);
  if st<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('������Ϣʧ��-'+geterrmsg);
    Exit;
  end;
  //CardExID := readCardOneInfo(CARD_NO);
  edtCardNo.Text := cm.getCardNo;
  edtName.Text := cm.getCustName;
  edtStuempNo.Text := cm.getStuempNo;

  OldMoney := cm.getCardBalance;
  if OldMoney='' then
  begin
    Context.GetDialogSystem.ShowWarning('��ȡ�����ʧ�ܣ�');
    btnReadCardInfo.SetFocus;
    Exit;
  end;
  edtCardMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
  edtAfterMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
  //���Ͳ�ѯ���ף��鿴�ÿ��Ƿ�Ϊ������������������������������˳�
  WorkView1.FieldByName('����').Data.SetInteger(StrToInt(edtCardNo.Text));
  WorkView1.FieldByName('�ͻ���').Data.SetInteger(0);
  WorkView1.FieldByName('�ͻ����').Data.SetInteger(0);
  WorkView1.FieldByName('�շ����').Data.SetInteger(0);
  WorkView1.FieldByName('Ǯ����').Data.SetInteger(0);
  WorkView1.FieldByName('������').Data.SetString(CardPhyID);
  //WorkView1.FieldByName('������').Data.SetString(CardPhyID);
  try
    WVRequest1.SendCommand;
  except
    on e:exception do
    begin
      Context.GetDialogSystem.ShowWarning(e.message);
      btnReadCardInfo.SetFocus;
      Exit;
    end;
  end;
  CardState := (WorkView1.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('sserial0').AsString;
  if Copy(CardState,1,4) <> '1000' then
  begin
    cm.beep;
    cm.beep;
    Context.GetDialogSystem.ShowMessage('�ÿ��Ѿ���ʧ��ע�������ܳ�ֵ��');
    btnReadCardInfo.SetFocus;
    Exit;
  end;
  Result := True;
end;

procedure TfaqhCardMonyIn.btnReadCardInfoClick(Sender: TObject);
var
  cm:TCM;
begin
  cm := nil;
  try
    cm := TCM.Create;
    if readCardInfo(cm)=False then
      Exit;
    if bjopen=1 then
    begin
      {
      bj(bjcomport,'W');
      bj(bjcomport,'&C11��  ����'+trim(edtName.Text)+'$');
      bj(bjcomport,'&C21����'+trim(edtCardMoney.Text)+'Ԫ$');
      }
      bj(bjcomport,'W');
      bj(bjcomport,'&C11��  ��:'+trim(edtName.Text)+'$');
      bj(bjcomport,'&C21�����:'+trim(edtCardMoney.Text)+'?$');
      bj(bjcomport, 't');
      bj(bjcomport, trim(edtCardMoney.Text)+'P'); //
    end;
    btnMoneyIn.Enabled := True;
    cbbType.SetFocus;
    lblTip.Caption := '';
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhCardMonyIn.cbbTypeKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
  begin
    if edtTicketNo.Enabled then
      edtTicketNo.SetFocus
    else
      edtmoney.SetFocus;
  end;
end;

procedure TfaqhCardMonyIn.edtmoneyKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
  begin
    if Application.MessageBox(PChar('��ȷ��ҪΪ�ÿ���ֵ['+edtmoney.Text+'Ԫ]��'), PChar(Application.Title),MB_OKCANCEL + MB_ICONQUESTION) = IDCANCEL then
    begin
      edtmoney.SetFocus;
      Exit;
    end;
    btnMoneyIn.Click;
  end;
end;

procedure TfaqhCardMonyIn.writeSuccess(wv: TWorkView;money: Integer;cm: TCM);
begin
  edtAfterMoney.Text := format('%f', [money / 100]);
  cm.beep;
  if bjopen=1 then
  begin
    {
    bj(bjcomport,'&Sc$');
    bj(bjcomport,'&C11��  ����'+trim(edtName.Text)+'$');
    bj(bjcomport,'&C21��  ֵ��'+trim(edtmoney.Text)+'Ԫ$');
    bj(bjcomport,'&C31����'+trim(edtAfterMoney.Text)+'Ԫ$');
    }
        bj(bjcomport,'&Sc$');
        bj(bjcomport,'&C11��  ��:'+trim(edtName.Text)+'$');
        bj(bjcomport,'&C21��  ֵ:'+trim(edtmoney.Text)+'?$');
        bj(bjcomport, 'B');    //������Ԥ��
        bj(bjcomport, trim(edtmoney.Text)+'P');//����������Ǯ

        bj(bjcomport,'&C31�����:'+trim(edtAfterMoney.Text)+'?$');

        bj(bjcomport, 't'); //�������˻����
        bj(bjcomport, trim(edtAfterMoney.Text)+'P');   //����������Ǯ
        bj(bjcomport,'&C41лл'+'X');

  end;

  if chkSaveMoney.Checked=False then
    edtmoney.Text := '0';
  btnMoneyIn.Enabled := False;
  btnReadCardInfo.SetFocus;
  RzStatusPane2.Caption:=wv.FieldByName('������Ϣ').Data.AsString;

end;

initialization
  TUIStdClassFactory.Create('���ֽ��ֵ', TfaqhCardMonyIn);

end.

