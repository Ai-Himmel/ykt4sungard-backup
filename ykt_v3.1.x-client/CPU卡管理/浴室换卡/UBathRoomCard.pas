unit UBathRoomCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  Mask, WVCtrls, WVDBBinders, Db,IniFiles, 
  RzStatus, EditExts, RzEdit, Buttons, CardDll;

  const overTime=10000;

type
  TfaBathRoomCard = class(TfaInputTemp)
    DataSource1: TDataSource;
    WVDBBinder1: TWVDBBinder;
    btnLock: TBitBtn;
    btnUnlock: TBitBtn;
    TipInfo: TRzStatusPane;
    UIPnlQueryCount: TUIPanel;
    grpCardInfo: TGroupBox;
    WVLabel5: TWVLabel;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    edtName: TRzEdit;
    edtCardNo: TRzEdit;
    edtStuempNo: TRzEdit;
    edtBeforeMoney: TRzEdit;
    RzStatusPane7: TRzStatusPane;
    edtmoney: TWVDigitalEdit;
    WVLabel1: TWVLabel;
    grp2: TGroupBox;
    RzStatusPane8: TRzStatusPane;
    edtBathCardPhyId: TRzEdit;
    RzStatusPane9: TRzStatusPane;
    edtBathCardMoney: TRzEdit;
    RzStatusPane10: TRzStatusPane;
    edtSetMoney: TRzEdit;
    btnSetMoney: TBitBtn;
    RzStatusPane11: TRzStatusPane;
    edtBathCardNO: TRzEdit;
    RzStatusPane2: TRzStatusPane;
    edtAfterMoney: TRzEdit;
    WVLabel2: TWVLabel;
    procedure btnLockClick(Sender: TObject);
    procedure btnUnlockClick(Sender: TObject);
    procedure btnSetMoneyClick(Sender: TObject);
  private
    { Private declarations }
    broomcardmoney:Real;
    procedure clearEdtInfo(grp:TGroupBox);

  protected
     procedure Init; override;
  public
    { Public declarations }
  end;

var
  faBathRoomCard: TfaBathRoomCard;

implementation
uses KsFrameworks, KSClientConsts;

{$R *.DFM}

procedure TfaBathRoomCard.Init;
var
  myfile:TIniFile;
begin
  inherited;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
    
  myfile := nil;
  try
    try
      myfile := TIniFile.Create(appPath+'../configs/SetPara.ini');
      broomcardmoney := myfile.ReadFloat('bathroomcard','cardmoney',0);
      edtSetMoney.Text := FloatToStr(broomcardmoney);
    except
      on e:Exception do
      begin
        ShowMessage('setPara配置文件读取错误--'+e.Message);
      end;
    end;
  finally
    myfile.Destroy;
  end;
end;


procedure TfaBathRoomCard.btnLockClick(Sender: TObject);
var
  cm: TCM;
  CardPhyID:string;
  st:integer;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
begin
  TipInfo.Caption := '';
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(cardPhyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
      exit;
    end;
    cm.clearallfieldreadmode;
    setOperReadMode(cm);
    if cm.readCard(cardPhyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡信息失败，请重试！');
      Exit;
    end;
    edtCardNo.Text := cm.getCardNo;
    edtName.Text := cm.getCustName;
    edtStuempNo.Text := cm.getStuempNo;
    try
      edtBeforeMoney.Text := format('%f', [StrToInt(cm.getCardBalance) / 100.0]);
    except
      Context.GetDialogSystem.ShowWarning('读取卡余额失败！');
      edtBeforeMoney.Text :='0';
    end;
    //手机锁定
    cm.clearallfieldwritemode;
    cm.setBlackCardSign(IntToStr(LOCK_CARD));
    st := cm.writeData(cardPhyId);
    if st<>0 then
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      TipInfo.Caption := '卡锁定失败，请重新锁定-'+reSt;
      Exit;
    end;
    cm.beep;
    TipInfo.Caption := '卡锁定成功！';
  finally
    cm.Destroy;
  end;
end;

procedure TfaBathRoomCard.btnUnlockClick(Sender: TObject);
var
  CardPhyID,newPhyId: string;
  balance:Integer;
  cm:TCM;
  cardNo,payCnt:Integer;
  tp:TTRANSPACK;
  st:Integer;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;

  nowTime:Cardinal;
begin
  TipInfo.Caption := '';
  if preReadCard=False then
    Exit;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(cardPhyId);
    if st<>0 then
    begin
      TipInfo.Caption := '寻卡失败，请放置好卡！';
      exit;
    end;
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CUST_NAME);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(STUEMP_NO);
    if cm.readCard(cardPhyId)<>0 then
    begin
      TipInfo.Caption := '读卡信息失败，请重试！';
      Exit;
    end;

    //交易次数
    try
      //dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      //subsidyNo := StrToInt(cm.getPatchNo);
      balance := StrToInt(cm.getCardBalance);
      cardNo := StrToInt(cm.getCardNo);
      
      edtName.Text := cm.getCustName;
      edtCardNo.Text := cm.getCardNo;
      edtStuempNo.Text := cm.getStuempNo;
      edtBeforeMoney.Text := format('%f', [StrToInt(cm.getCardBalance) / 100.0]);
    except
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      TipInfo.Caption := '读取卡信息失败-'+reSt;
      Exit;
    end;

    if (StrToFloat(edtmoney.Text))=0 then
    begin
      if Application.MessageBox('要扣款的金额为零，你确定吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
        Exit;
    end;

    //扣款---------------------------------------------------------------------b
    //preSetMoney(tp);
    ZeroMemory(@tp,SizeOf(tp));
    //终端编号
    StrCopy(@tp.Termno,PChar(scSiteNo));
    //交易码
    tp.PayCode := 3000;
    //交易卡号
    tp.CardNo := cardNo;
    //物理编号
    StrCopy(@tp.CardPhyID,PChar(CardPhyID));
    //支付交易次数
    tp.PayCardCnt := payCnt;
    //交易前金额
    tp.BefBalance := balance;
    //交易金额
    tp.TransAmt := Round(StrToFloat(edtmoney.Text))*100;
    //操作员代码
    StrCopy(@tp.OperCode,PChar(scOperNo));
    tp.ErrCode := SizeOf(tp);
    //后台试入账
    st := ks_payinit(@tp);
    if st<>0 then
    begin
      if tp.cRetryFlag<>Char(0) then
      begin
        st := ks_payinit(@tp);
        if st<>0 then
        begin
          reSt := ks_geterrmsg(PChar(@reErrMsg));
          Context.GetDialogSystem.ShowMessage('扣款试入账失败-'+reSt);
          Exit;
        end;
      end
      else
      begin
        reSt := ks_geterrmsg(PChar(@reErrMsg));
        Context.GetDialogSystem.ShowMessage('扣款试入账失败-'+reSt);
        Exit;
      end;
    end;    
    //后台试入账结束
    //开始扣款
    st := ks_setcardbal(@tp);
    if st<>0 then
    begin
      //扣款失败，重试
      if tp.cRetryFlag<>Char(0) then
      begin
        //循环寻卡
        nowTime := GetTickCount;
        while (1>0) do
        begin
          if (GetTickCount-nowTime)>overTime then
          begin
            //时间大于10秒，提示超时，退出
            ks_dotransunprove(@tp);
            Context.GetDialogSystem.ShowMessage('寻卡超时，请重新操作该业务！');
            Exit;
          end;

          st := cm.card(newPhyId);
          if st<>0 then
          begin
            Context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
          end
          else
          begin
            //寻到卡后，判断是否为同一张卡，如果不是，提示重新放卡
            if newPhyId<>CardPhyID then
              Context.GetDialogSystem.ShowMessage('放置的卡和刚才放置的不是同一张卡，请重新放置！')
            else
              Break;
          end;
          Sleep(50);
          Continue;
        end;
        //重试一次
        st := ks_setcardbal(@tp);
        if st<>0 then
        begin
          while (1>0) do
          begin
            //判断是否中途拔卡
            if tp.cGetProveFlag>Char(0) then
            begin
              //循环寻卡
              nowTime := GetTickCount;
              while (1>0) do
              begin
                if (GetTickCount-nowTime)>overTime then
                begin
                  //时间大于10秒，提示超时，退出
                  ks_dotransunprove(@tp);
                  Context.GetDialogSystem.ShowMessage('寻卡超时，请重新操作该业务！');
                  Exit;
                end;

                st := cm.card(newPhyId);
                if st<>0 then
                begin
                  Context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
                end
                else
                begin
                  //寻到卡后，判断是否为同一张卡，如果不是，提示重新放卡
                  if newPhyId<>CardPhyID then
                    Context.GetDialogSystem.ShowMessage('放置的卡和刚才放置的不是同一张卡，请重新放置！')
                  else
                    Break;
                end;
                Sleep(50);
              end;
              st:=ks_gettransprove(2,tp.PayCardCnt+1);
              if st=0 then
                Break;
              st:=ks_setcardbal(@tp);
              if st=0 then
                Break;
              Continue;
            end
            else
            begin
              reSt := ks_geterrmsg(PChar(@reErrMsg));
              Context.GetDialogSystem.ShowMessage('扣款失败-'+reSt);
              Exit;
            end;
          end;
        end;
      end;
    end;
    //开始正式入账
    st := ks_pay(@tp);
    if st<>0 then
    begin
      if(tp.cRetryFlag)<>Char(0) then
      begin
        st := ks_pay(@tp);
        if st<>0 then
        begin
          reSt := ks_geterrmsg(PChar(@reErrMsg));
          Context.GetDialogSystem.ShowMessage('入账失败-'+reSt);
          Exit;
        end;
      end;
    end;

    //入账成功，开始解锁
    cm.clearallfieldwritemode;
    cm.setfieldwritemode(BLACK_CARD_SIGN);
    cm.setBlackCardSign(IntToStr(NORMAL_CARD));
    st := cm.writeData(cardPhyId);
    if st<>0 then
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      Context.GetDialogSystem.ShowMessage('解锁失败，请更新卡信息-'+reSt);
      Exit;
    end;

    //读取扣款后余额
    cm.clearallfieldwritemode;
    cm.setfieldreadmode(CARD_BALANCE);
    st := cm.readCard(cardPhyId);
    if st<>0 then
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      TipInfo.Caption := '重读卡信息失败-'+reSt;
    end;
    try
      edtAfterMoney.Text := format('%f', [StrToInt(cm.getCardBalance) / 100.0]);
    except

    end;
    edtmoney.Text := '0';
    cm.beep;
    TipInfo.Caption := '扣款成功！';
    //cm.halt;
    //-------------------------------------------------------------------------e
  finally
    cm.Destroy;
  end;

end;

procedure TfaBathRoomCard.btnSetMoneyClick(Sender: TObject);
var
  cm: TCM;
  CardPhyID:string;
  st:integer;
  reErrMsg:array[0..255] of Char;
  tp:TTRANSPACK;
  rest:PChar;
  cardNo:string;
  payCnt,dptCnt,subsidyNo:Integer;

begin
  TipInfo.Caption := '';
  clearEdtInfo(grpCardInfo);
  if preReadCard=False then
    Exit;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(cardPhyId);
    if st<>0 then
    begin
      TipInfo.Caption := '寻卡失败，请放置好卡！';
      exit;
    end;
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(PATCH_NO);
    if cm.readCard(cardPhyId)<>0 then
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      TipInfo.Caption := '读卡信息失败--'+reSt;
      Exit;
    end;
    edtBathCardPhyId.Text := cardPhyId;
    cardNo := cm.getCardNo;
    edtBathCardNO.Text := cardNo;
    try
      edtBathCardMoney.Text := format('%f', [StrToInt(cm.getCardBalance) / 100.0]);
      edtmoney.Text := FloatToStr(broomcardmoney-StrToFloat(edtBathCardMoney.Text));
      
      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      subsidyNo := StrToInt(cm.getPatchNo);
    except
      edtBathCardMoney.Text := '0';
      edtmoney.Text := '0';
      TipInfo.Caption := '读取卡余额失败！';
      Exit;
    end;

    //设置mf卡金额为默认金额
    //preSetMoney(tp);
    ZeroMemory(@tp,SizeOf(tp));
    //终端交易序列号
    tp.TermSeqno := 1;
    //终端编号
    StrCopy(@tp.Termno,PChar(scSiteNo));
    //交易卡号
    tp.CardNo := StrToInt(cardNo);
    //物理编号
    StrCopy(@tp.CardPhyID,PChar(CardPhyID));
    //交易日期
    StrCopy(@tp.TransDate,PChar(FormatDateTime('yyyymmdd',Date)));
    //交易时间
    StrCopy(@tp.TransTime,PChar(FormatDateTime('hhmmss',Now)));
    //交易前金额
    tp.BefBalance := Round(StrToFloat(edtBathCardMoney.Text)*100);
    //交易后金额
    tp.AftBalance := Round(broomcardmoney*100);
    //交易前充值次数
    tp.DptCardCnt := dptCnt;
    //交易前消费次数
    tp.PayCardCnt := payCnt;
    //交易前补助次数
    tp.SubsidyNo := subsidyNo;
    st := ks_setcardbal(@tp);
    if st<>0 then
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      TipInfo.Caption := '重置卡金额失败--'+reSt;
    end
    else
    begin
      cm.beep;
      TipInfo.Caption := '重置卡金额成功，请给手机卡扣款！';
      //Context.GetDialogSystem.ShowMessage('重置卡金额成功，请给手机卡扣款！');
      btnUnlock.SetFocus;
    end;
  finally
    cm.Destroy;
  end;
end;

procedure TfaBathRoomCard.clearEdtInfo(grp: TGroupBox);
var
  i:Integer;
begin
  for i:=0 to grp.ControlCount-1 do
  begin
    if grp.Controls[i] is TRzEdit then
      TRzEdit(grp.Controls[i]).Text := '';
  end;
end;

initialization
  TUIStdClassFactory.Create('浴室换卡',TfaBathRoomCard);

end.
