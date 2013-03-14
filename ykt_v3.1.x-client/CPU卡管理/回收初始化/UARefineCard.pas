unit UARefineCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  Mask, WVCtrls, RzStatus, RzPanel, Buttons, RzEdit;

type
  TfaRefineCard = class(TfaInputTemp)
    UIPnlQueryCount: TUIPanel;
    LabRecordCount: TLabel;
    RzStatusPane2: TRzStatusPane;
    btnRecycle: TButton;
    grp1: TGroupBox;
    RzStatusPane1: TRzStatusPane;
    edtShowCardNo: TRzEdit;
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
  faRefineCard: TfaRefineCard;

implementation
uses ksframeworks, KSClientConsts,CardDll, UKey;

{$R *.DFM}

procedure TfaRefineCard.Init;
begin
  inherited;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaRefineCard.btnRecycleClick(Sender: TObject);
var
  st : Integer;
  //flag:Integer;
  showCardNo:string;
  rephyId:array[0..16] of Char;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
  phyid:string;
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
  if cardZero<>0 then
  begin  
  end;
  {
  showCardNo := readCardOneInfo(SHOW_CARDNO);
  if (showCardNo='') and (Trim(edtShowCardNo.Text)='') then
  begin
    Context.GetDialogSystem.ShowMessage('���ڵ���ʾ����Ϊ�գ���������ʾ���ţ�');
    edtShowCardNo.SetFocus;
    Exit;
  end;
  if showCardNo='' then
    showCardNo := Trim(edtShowCardNo.Text);
  if Trim(edtShowCardNo.Text)<>'' then
    showCardNo := Trim(edtShowCardNo.Text);
  }
  if Trim(edtShowCardNo.Text)='' then
    showCardNo := ''
  else
    showCardNo := Trim(edtShowCardNo.Text);
  if chkTip.Checked then
    if Application.MessageBox('��ȷ��Ҫ���³�ʼ���ÿ���',PChar(Application.Title),MB_YESNO+mb_iconquestion)=IDNO  then
      Exit;
  FillChar(rephyId,17,0);
  //��Ѱ����ȡ��������
  if ks_card(PChar(@rephyId))<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('�����Ҫ��ʼ���Ŀ���');
    Exit;
  end;
  st := ks_recycleusercard();
  if st=0 then
  begin
    //Sleep(100);
    phyid := rephyId;
    //showCardNo := Trim(edtShowCardNo.Text);
    //��ʼ��ʼ��
    st := ks_publishusercard(PChar(phyId),PChar(showCardNo));
    if st<>0 then
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      Context.GetDialogSystem.ShowMessage('��ʼ����ʧ��--'+rest);
      Exit;
    end
    else
    begin
      kng_beep();
      if chkTip.Checked then
        Context.GetDialogSystem.ShowMessage('���³�ʼ�����ɹ���');
      RzStatusPane2.Caption := edtShowCardNo.Text+'--���³�ʼ�����ɹ���';
    end;

  end
  else
  begin
    reSt := ks_geterrmsg(PChar(@reErrMsg));
    Context.GetDialogSystem.ShowMessage('���տ�ʧ��--'+reSt);
  end;
end;

function TfaRefineCard.cardZero: Integer;
var
  cm:TCM;
  tradeDate,tradeTime:string;
  payCnt,dptCnt,subsidyNo,balance,cardNo:Integer;
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
    tp.CardNo := cardNo;
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
  TUIStdClassFactory.Create('���ճ�ʼ��', TfaRefineCard);

end.
