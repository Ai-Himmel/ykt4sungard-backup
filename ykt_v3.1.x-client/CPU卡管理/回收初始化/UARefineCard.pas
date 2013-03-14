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
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
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
    Context.GetDialogSystem.ShowMessage('请先读取密钥卡！');
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
    Context.GetDialogSystem.ShowMessage('卡内的显示卡号为空，请输入显示卡号！');
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
    if Application.MessageBox('你确定要重新初始化该卡吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=IDNO  then
      Exit;
  FillChar(rephyId,17,0);
  //先寻卡，取得物理卡号
  if ks_card(PChar(@rephyId))<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('请放置要初始化的卡！');
    Exit;
  end;
  st := ks_recycleusercard();
  if st=0 then
  begin
    //Sleep(100);
    phyid := rephyId;
    //showCardNo := Trim(edtShowCardNo.Text);
    //开始初始化
    st := ks_publishusercard(PChar(phyId),PChar(showCardNo));
    if st<>0 then
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      Context.GetDialogSystem.ShowMessage('初始化卡失败--'+rest);
      Exit;
    end
    else
    begin
      kng_beep();
      if chkTip.Checked then
        Context.GetDialogSystem.ShowMessage('重新初始化卡成功！');
      RzStatusPane2.Caption := edtShowCardNo.Text+'--重新初始化卡成功！';
    end;

  end
  else
  begin
    reSt := ks_geterrmsg(PChar(@reErrMsg));
    Context.GetDialogSystem.ShowMessage('回收卡失败--'+reSt);
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
      context.GetDialogSystem.ShowMessage('寻卡失败，请把卡放置好！');
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
    //读取卡信息
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
    //终端交易序列号
    tp.TermSeqno := 1;
    //终端编号
    StrCopy(@tp.Termno,PChar(scSiteNo));
    //交易卡号
    tp.CardNo := cardNo;
    //物理编号
    StrCopy(@tp.CardPhyID,PChar(cm.getCardSeriNo));
    //交易日期
    StrCopy(@tp.TransDate,PChar(tradeDate));
    //交易时间
    StrCopy(@tp.TransTime,PChar(tradeTime));
    //交易前金额
    tp.BefBalance := balance;
    //交易后金额
    tp.AftBalance := 0;
    //交易前充值次数
    tp.DptCardCnt := dptCnt;
    //交易前消费次数
    tp.PayCardCnt := payCnt;
    //交易前补助次数
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
  TUIStdClassFactory.Create('回收初始化', TfaRefineCard);

end.
