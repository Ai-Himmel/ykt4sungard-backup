unit UFeeCardUnLock;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  Mask, WVCtrls, WVDBBinders, Db, 
  RzStatus, EditExts, RzEdit, Buttons, CardDll;

type
  TfaFeeCardUnlock = class(TfaInputTemp)
    DataSource1: TDataSource;
    WVDBBinder1: TWVDBBinder;
    btnReadCardInfo: TBitBtn;
    btnMoneyOut: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    UIPnlQueryCount: TUIPanel;
    grp1: TGroupBox;
    WVLabel5: TWVLabel;
    WVLabel10: TWVLabel;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    edtName: TRzEdit;
    edtCardNo: TRzEdit;
    edtStuempNo: TRzEdit;
    edtCardMoney: TRzEdit;
    edtAfterMoney: TRzEdit;
    WVcashOperCancel: TWorkView;
    WVRcashOperCancel: TWVRequest;
    RzStatusPane7: TRzStatusPane;
    edtMoney: TRzEdit;
    lbl1: TWVLabel;
    procedure btnReadCardInfoClick(Sender: TObject);
    procedure btnMoneyOutClick(Sender: TObject);
  private
    { Private declarations }
    oldPhyId:string;

    procedure writeSuccess(wv:TWorkView;money:Integer;cm:TCM);
  protected
     procedure Init; override;
  public
    { Public declarations }
  end;

var
  faFeeCardUnlock: TfaFeeCardUnlock;
  OldMoney: string;

implementation
uses KsFrameworks, KSClientConsts;

{$R *.DFM}

procedure TfaFeeCardUnlock.Init;
begin
  inherited;
  btnMoneyOut.Enabled:=false;
  btnreadcardinfo.setfocus;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaFeeCardUnlock.btnReadCardInfoClick(Sender: TObject);
var
  CardExID: string;
  cm: TCM;
  CardPhyID:string;
  st:integer;
  cardSign:Integer;
begin
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(cardPhyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
      exit;
    end;
    cm.clearallfieldreadmode;
    setOperReadMode(cm);
    if cm.readCard(cardPhyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ������ԣ�');
      Exit;
    end;
    oldPhyId := CardPhyID;
    CardExID := cm.getCardNo;
    if CardExID='' then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ����ʧ��,�����¶�ȡ��');
      Exit;
    end;

    try
      cardSign := StrToInt(cm.getBlackCardSign);
    except
      Context.GetDialogSystem.ShowMessage('��ȡ����־ʧ��-'+geterrmsg);
      Exit;
    end;

    if cardSign<>FEE_LOCK_CARD then
    begin
      Context.GetDialogSystem.ShowMessage('�ÿ�״̬���Ǻ󸶷�����״̬�������ڴ˽��������');
      Exit;
    end;
    
    edtCardNo.Text := CardExID;
    edtName.Text := cm.getCustName;
    edtStuempNo.Text := cm.getStuempNo;
    try
      OldMoney := cm.getCardBalance;
      edtCardMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
      edtAfterMoney.Text :=format('%f', [StrToInt(OldMoney) / 100.0]);
    except
      Context.GetDialogSystem.ShowWarning('��ȡ�����ʧ�ܣ�');
      Exit;
    end;

    if bjopen=1 then
    begin
      bj(bjcomport,'W');
      bj(bjcomport,'&C11��  ����'+trim(edtName.Text)+'$');
      bj(bjcomport,'&C21����'+trim(edtCardMoney.Text)+'Ԫ$');
    end;

    btnMoneyOut.Enabled:=True;
  finally
    cm.Destroy;
  end;
end;

procedure TfaFeeCardUnlock.btnMoneyOutClick(Sender: TObject);
var
  CardPhyID: string;
  balance:Integer;
  OutMoney: Integer;
  cm:TCM;
  payCnt,dptCnt,lockCnt:Integer;
  lockDev,lockDate,lockTime:string;
  tp:TTRANSPACK;
  tradeDate,tradeTime:string;
  rtnCardNo,rtnTradeMoney:Integer;
  st:Integer;

begin
  if preReadCard=False then
    Exit;

  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(cardPhyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ��-'+geterrmsg);
      exit;
    end;
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CARD_SERI_NO);
    cm.setfieldreadmode(LOCK_TERMID);
    cm.setfieldreadmode(LOCK_TRANSDATE);
    cm.setfieldreadmode(LOCK_TRANSTIME);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(LOCK_CARDCNT);
    //cm.setfieldreadmode();
    if cm.readCard(cardPhyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣʧ��-'+geterrmsg);
      Exit;
    end;

    if oldPhyId <> CardPhyID then
    begin
      ShowMessage('��ʹ��ͬһ�ſ����в�����');
      btnReadCardInfo.SetFocus;
      btnMoneyOut.Enabled := False;
      Exit;
    end;
    //���״���
    try
      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      balance := StrToInt(cm.getCardBalance);
      lockDev:=cm.getLockTermId;
      lockDate:=cm.getLockTransDate;
      lockTime:=cm.getLockTransTime;
      lockCnt := StrToInt(cm.getLockCardCnt);
    except
      Context.GetDialogSystem.ShowMessage('��ȡ�����Ѵ���ʧ�ܣ�����ȡ����');
      Exit;
    end;

    //���͹��ܺ�
    //WorkView.SynchronizeCtrlsToFields;

    WorkView.FieldByName('����').Data.SetInteger(StrToInt(cm.getCardNo));
    WorkView.FieldByName('������').Data.SetString(CardPhyID);
    WorkView.FieldByName('���Ѵ���').Data.SetInteger(payCnt);
    WorkView.FieldByName('�뿨���').Data.SetInteger(balance);
    WorkView.FieldByName('�����豸').Data.SetString(lockDev);
    WorkView.FieldByName('��������').Data.SetString(lockDate);
    WorkView.FieldByName('����ʱ��').Data.SetString(lockTime);
    WorkView.FieldByName('��������').Data.SetInteger(lockCnt);
    
    MainRequest.SendCommand;
    if WorkView.FieldByName('������').Data.AsString<>'0' then
    begin
      getReturn('',WorkView);
      RzStatusPane2.Caption:=WorkView.FieldByName('������Ϣ').Data.AsString;
      Exit;
    end;
    rtnCardNo := WorkView.FieldByName('����').Data.AsInteger;
    OutMoney := WorkView.FieldByName('�������').Data.AsInteger;
    rtnTradeMoney := WorkView.FieldByName('�ۿ���').Data.AsInteger;
    tradeDate := WorkView.FieldByName('ҵ������').Data.AsString;
    tradeTime := WorkView.fieldbyname('ҵ��ʱ��').Data.AsString;
    if rtnTradeMoney<>0 then
    begin
      ZeroMemory(@tp,SizeOf(tp));
      //�ն˽������к�
      tp.TermSeqno := 1;
      //�ն˱��
      StrCopy(@tp.Termno,PChar(scSiteNo));
      //���׿���
      tp.CardNo := rtnCardNo;
      //������
      StrCopy(@tp.CardPhyID,PChar(CardPhyID));
      //��������
      StrCopy(@tp.TransDate,PChar(TradeDate));
      //����ʱ��
      StrCopy(@tp.TransTime,PChar(tradeTime));
      //����ǰ���
      tp.BefBalance := balance;
      //���׺���
      tp.AftBalance := OutMoney;
      //����ǰ��ֵ����
      tp.DptCardCnt := dptCnt;
      //����ǰ���Ѵ���
      tp.PayCardCnt := payCnt;
      //����ǰ��������
      //tp.SubsidyNo := subsidyNo;

      if setCardBal(tp,cm,cardPhyId)<>0 then
        Exit;
    end;
    //��ʼ����
    cm.clearallfieldwritemode;
    //cm.setfieldwritemode(BLACK_CARD_SIGN);
    //cm.setfieldwritemode(BLACK_VER);
    //cm.setBlackVer(WVCardLose.FieldByName('���汾��').Data.AsString);
    cm.setBlackCardSign(IntToStr(NORMAL_CARD));
    st := cm.writeData(cardPhyId);
    if st <> 0 then
    begin
      Context.GetDialogSystem.ShowWarning('����ʧ��-'+geterrmsg);
    end
    else
    begin
      edtMoney.Text := format('%f', [rtnTradeMoney / 100]);
      writeSuccess(WorkView,OutMoney,cm);
      //cm.halt;
    end;
  finally
    cm.Destroy;
  end;

end;

procedure TfaFeeCardUnlock.writeSuccess(wv: TWorkView; money: Integer;
  cm: TCM);
begin
  edtAfterMoney.Text := format('%f', [money / 100]);
  cm.beep;
  if bjopen=1 then
  begin
    bj(bjcomport,'&Sc$');
    bj(bjcomport,'&C11��  ����'+trim(edtName.Text)+'$');
    bj(bjcomport,'&C21��  ֵ��'+trim(edtmoney.Text)+'Ԫ$');
    bj(bjcomport,'&C31����'+trim(edtAfterMoney.Text)+'Ԫ$');
  end;

  btnMoneyOut.Enabled := False;
  btnReadCardInfo.SetFocus;
  Context.GetDialogSystem.ShowMessage('�󸶷ѿۿ�ɹ���');
  RzStatusPane2.Caption:=wv.FieldByName('������Ϣ').Data.AsString;

end;

initialization
  TUIStdClassFactory.Create('�󸶷ѿۿ�',TfaFeeCardUnlock);

end.
