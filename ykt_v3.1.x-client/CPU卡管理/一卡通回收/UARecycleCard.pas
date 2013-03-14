unit UARecycleCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  Mask, WVCtrls, RzStatus, RzPanel, Buttons, RzEdit;

type
  TfaRecycleCard = class(TfaInputTemp)
    UIPnlQueryCount: TUIPanel;
    LabRecordCount: TLabel;
    RzStatusPane2: TRzStatusPane;
    btnRecycle: TButton;
    lbl1: TLabel;
    chkTip: TCheckBox;
    procedure btnRecycleClick(Sender: TObject);
  private
    { Private declarations }
    function cardZero(): Integer;
  public
    { Public declarations }
    procedure Init; override;
  end;

var
  faRecycleCard: TfaRecycleCard;

implementation
uses ksframeworks, KSClientConsts,CardDll, UKey;

{$R *.DFM}

procedure TfaRecycleCard.Init;
begin
  inherited;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaRecycleCard.btnRecycleClick(Sender: TObject);
var
  st : Integer;
  rephyId:array[0..16] of Char;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
begin
  if preReadCard=False then
    Exit;
  {
  st := ks_checkloadkeys;
  if st=0 then
  begin
    Context.GetDialogSystem.ShowMessage('���ȶ�ȡ��Կ����');
    Exit;
  end;
  }
  //�ѽ����0
  if cardZero<>0 then
  begin
  end;
    
  if chkTip.Checked then
    if Application.MessageBox('��ȷ��Ҫ�Ѹÿ����ճɳ���״̬��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
      Exit;
  FillChar(rephyId,17,0);
  //��Ѱ����ȡ��������
  if ks_card(PChar(@rephyId))<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
    Exit;
  end;
  st := ks_recycleusercard();
  if st=0 then
  begin
    KNG_beep;
    RzStatusPane2.Caption := '�����ճɹ���';
  end
  else
  begin
    reSt := ks_geterrmsg(PChar(@reErrMsg));
    Context.GetDialogSystem.ShowMessage('���տ�ʧ��--'+reSt);
  end;
end;

function TfaRecycleCard.cardZero: Integer;
var
  cm:TCM;
  tradeDate,tradeTime:string;
  payCnt,dptCnt,subsidyNo,balance,cardNO:Integer;
  st:Integer;
  tp:TTRANSPACK;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
  phyId:string;
begin
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ���ѿ����úã�');
      result := -1;
      exit;
    end;
    cm.clearallfieldwritemode;
    cm.setfieldwritemode(BLACK_CARD_SIGN);
    cm.setBlackCardSign(IntToStr(DESTORY));
    st := cm.writeData(phyid);
    if st<>0 then
    begin
      Result := st;
      Exit;
    end;
    //��ȡ����Ϣ
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(PATCH_NO);
    cm.setfieldreadmode(CARD_BALANCE);
    try
      st := cm.readCard(phyid);
    except
      Result := -1;
      Exit;
    end;
    if st<>0 then
    begin
      Result := st;
      Exit;
    end;
    try
      payCnt := StrToInt(cm.getPayCardCnt);
    except
      payCnt := 0;
    end;
    try
      dptCnt := StrToInt(cm.getDptCardCnt);
    except
      dptCnt := 0;
    end;
    try
      subsidyNo := StrToInt(cm.getPatchNo);
    except
      subsidyNo := 0;
    end;
    try
      balance := StrToInt(cm.getCardBalance);
    except
      balance := 0;
    end;
    
    if balance=0 then
    begin
      Result := 0;
      Exit;
    end;
    
    try
      cardNO := StrToInt(cm.getCardNo);
    except
      cardNO := 0;
    end;
    tradeDate := FormatDateTime('yyyymmdd',date);
    tradeTime := FormatDateTime('hhmmss',now);
    //preSetMoney(tp);
    ZeroMemory(@tp,SizeOf(tp));
    //�ն˽������к�
    tp.TermSeqno := 1;
    //�ն˱��
    StrCopy(@tp.Termno,PChar(scSiteNo));
    //���׿���
    tp.CardNo := cardNO;
    //������
    StrCopy(@tp.CardPhyID,PChar(cm.getCardSeriNo));
    //��������
    StrCopy(@tp.TransDate,PChar(tradeDate));
    //����ʱ��
    StrCopy(@tp.TransTime,PChar(tradeTime));
    //����ǰ���
    tp.BefBalance := balance;
    //���׺���
    tp.AftBalance := 0;
    //����ǰ��ֵ����
    tp.DptCardCnt := dptCnt;
    //����ǰ���Ѵ���
    tp.PayCardCnt := payCnt;
    //����ǰ��������
    tp.SubsidyNo := subsidyNo;
    try
      st := ks_setcardbal(@tp);
      if st<>0 then
      begin
        reSt := ks_geterrmsg(PChar(@reErrMsg));
        Context.GetDialogSystem.ShowMessage(reSt+'+'+inttostr(st));
        Result := st;
        Exit;
      end;
    except
      Result := -3;
      Exit;
    end;
    Result := 0;
  finally
    cm.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('һ��ͨ����', TfaRecycleCard);

end.
