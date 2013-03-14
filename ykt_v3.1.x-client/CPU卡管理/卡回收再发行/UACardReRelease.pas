unit UACardReRelease;

interface
              
uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhInputTemp, WVCmdReq, WorkViews, StdCtrls, ExtCtrls,
  UICtrls, WVCtrls, Mask, CardDll,WaterDll, 
  RzPanel, RzStatus, Buttons, 
  RzEdit;

type
  TfaqhCardReRelease = class(TfaqhInputTemp)
    UIPanel3: TUIPanel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    UIPnlQueryCount: TUIPanel;
    LabRecordCount: TLabel;
    WVLabel3: TWVLabel;
    WVLabel4: TWVLabel;
    WVLabel5: TWVLabel;
    WVLabel6: TWVLabel;
    WVLabel11: TWVLabel;
    WVLabel12: TWVLabel;
    WVLabel10: TWVLabel;
    WVLabel9: TWVLabel;
    WVLabel8: TWVLabel;
    WVLabel7: TWVLabel;
    grp1: TGroupBox;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    WVRelCardOk: TWorkView;
    WVRRelCardOk: TWVRequest;
    RzStatusPane7: TRzStatusPane;
    btnReleaseCard: TBitBtn;
    RzStatusPane4: TRzStatusPane;
    edtPhyId: TRzEdit;
    edtCardId: TRzEdit;
    edtEndDate: TRzEdit;
    edtBalance: TRzEdit;
    edtPwd: TRzEdit;
    edtFeeType: TRzEdit;
    RzStatusPane5: TRzStatusPane;
    procedure btnReleaseCardClick(Sender: TObject);
  private
    { Private declarations }
    phyId:string;
    cardId:string;
    balance:Integer;
    payCnt,dptCnt:Integer;
    //subsidyNo:Integer;

    function readCardInfo: Boolean;
  public
    { Public declarations }
    procedure Init;override;
  end;

var
  faqhCardReRelease: TfaqhCardReRelease;

implementation
uses KSFrameWorks, KSClientConsts,KSDataDictionary;

{$R *.DFM}

procedure TfaqhCardReRelease.Init;
begin
  inherited;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
end;

procedure TfaqhCardReRelease.btnReleaseCardClick(Sender: TObject);
var
  //stationId:Integer;
  cm : TCM;
  rBalance:Integer;
  rFeeType:Integer;
  rPwd:string;
  rEndDate:string;
  maxPerCount,maxPerDay:Integer;
  tradeDate,tradeTime:string;
  st:Integer;
  tof : Integer;
  tp:TTRANSPACK;
  waterSt:Integer;
  ssphyId:string;
  cardVer:string;

  cardno : Integer;                   //交易卡号
  custno : Integer;                   //客户号
  custtype : Integer;                 //客户类别
  expireddate : string;  //有效期
  waterPack:TWATERCOMMPACK; 
begin
  phyId:='';
  cardId:='';
  balance:=0;
  payCnt:=0;
  if Application.MessageBox('你确定要回收然后再重新发行该卡吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  if readCardInfo=False then
    Exit;
  WorkView.FieldByName('卡号').Data.SetInteger(StrToInt(cardId));
  WorkView.FieldByName('物理编号').Data.SetString(phyId);
  WorkView.FieldByName('交易次数').Data.SetInteger(payCnt);
  WorkView.FieldByName('充值次数').Data.SetInteger(dptCnt);
  WorkView.FieldByName('卡余额').Data.SetInteger(balance);
  MainRequest.SendCommand;
  if (WorkView.FieldByName('返回码').Data.AsInteger = 0) then
  begin
    //stationId := WorkView.fieldbyname('终端编号').Data.AsInteger;
    rBalance := WorkView.fieldbyname('卡余额').Data.AsInteger;
    rFeeType := WorkView.fieldbyname('收费类别').Data.AsInteger;
    rPwd := WorkView.fieldbyname('卡密码').Data.AsString;
    rEndDate := WorkView.fieldbyname('有效期').Data.AsString;
    tradeDate  := WorkView.fieldbyname('业务日期').Data.AsString;
    tradeTime := WorkView.fieldbyname('业务时间').Data.AsString;
    cardVer := WorkView.fieldbyname('版本号').Data.AsString;
    //rTradeNum := WorkView.fieldbyname('交易次数').Data.AsInteger;
    cm:= nil;
    try
      cm := TCM.Create;
      st := cm.card(ssphyId);
      if st<>0 then
      begin
        context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡!');
        exit;
      end;
      cm.clearallfieldwritemode;
      //setOperWriteMode(cm);
      cm.setBlackVer(cardVer);
      cm.setCardLimitType(IntToStr(rFeeType));
      cm.setDeadLineDate(rEndDate);

      if maxper=1 then
      begin
        maxPerCount := WorkView.fieldbyname('单次限额').Data.AsInteger;
        maxPerDay := WorkView.fieldbyname('日限额').Data.AsInteger;
        cm.setMaxPerCount(IntToStr(maxPerCount));
        cm.setMaxPerDay(IntToStr(maxPerDay));
        //rst := cardManage.SetConsumeLimit(maxPerCount,maxPerDay);
      end;
      st := cm.writeData(ssphyId);
      //preSetMoney(tp);
      ZeroMemory(@tp,SizeOf(tp));
      //设置卡余额
      //终端交易序列号
      tp.TermSeqno := 1;
      //终端编号
      StrCopy(@tp.Termno,PChar(scSiteNo));
      //交易卡号
      tp.CardNo := StrToInt(cardId);
      //物理编号
      StrCopy(@tp.CardPhyID,PChar(phyId));
      //交易日期
      StrCopy(@tp.TransDate,PChar(tradeDate));
      //交易时间
      StrCopy(@tp.TransTime,PChar(tradeTime));
      //交易后金额
      tp.AftBalance :=  rBalance;
      //交易前金额
      tp.BefBalance := balance;
      //交易前充值次数
      tp.DptCardCnt := dptCnt;
      //交易前消费次数
      tp.PayCardCnt := payCnt;
      //交易前补助次数
      tp.SubsidyNo := 0;

      tof := setCardBal(tp,cm,ssphyId);;
      //如果有水控钱包，先清空水控钱包金额，如果失败则不再进行主钱包操作
      if waterStrings.Count > 0 then
      begin
        //读小钱包信息
        st := mfcard(phyId);
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowMessage('小钱包寻卡失败，请重试！');
          Exit;
        end;
        preCommWaterPack(waterPack);
        st := ks_water_readmoney(StrToInt(waterStrings[0]),@waterpack);
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowMessage('小钱包读卡失败，请重试！');
          Exit;
        end
        else
        begin
          cardno := waterPack.cardno;                     //交易卡号
          custno := waterPack.custno;                     //客户号
          custtype := waterPack.custtype;                 //客户类别
          expireddate := waterPack.expireddate;           //有效期
        end;
        waterSt := pubSmlBag(cardno,custno,custType,expireddate,ssphyId);
        if waterSt <> 0 then
        begin
          Context.GetDialogSystem.ShowMessage('重置水控钱包失败，请重试！');
          Exit;
        end;
      end;
      if (st=0) and (tof = 0) then
      begin
        cm.beep;
        Context.GetDialogSystem.ShowSuccess('重新写卡信息成功！');
      end
      else
      begin
        Context.GetDialogSystem.ShowSuccess('重新写卡信息失败！');
      end;
    finally
      cm.Destroy;
    end;
    edtPhyId.Text := phyId;
    edtCardId.Text := cardId;
    edtBalance.Text := FloatToStr(rBalance/100);
    edtEndDate.Text := rEndDate;
    edtFeeType.Text := GetIdObjectName(-43,IntToStr(rFeeType));
    edtPwd.Text := rPwd;
  end
  else
  begin
    getReturn('',WorkView);
    RzStatusPane1.Caption:=WorkView.FieldByName('返回信息').Data.AsString;
  end;
end;

function TfaqhCardReRelease.readCardInfo:Boolean;
var
  cm:TCM;
  st:Integer;
begin
  Result := False;
  if preReadCard=False then
    Exit;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('寻卡失败，请冲正该交易！');
      exit;
    end;
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(CARD_BALANCE);
    if cm.readCard(phyId)<>0 then
    begin
      context.GetDialogSystem.ShowMessage('读卡失败，请放置好卡重新操作！');
      exit;
    end;
    cardId := cm.getCardNo;
    balance := StrToInt(cm.getCardBalance);
    payCnt :=  StrToInt(cm.getPayCardCnt);
    dptCnt := StrToInt(cm.getDptCardCnt);
    Result := True;
  finally
    cm.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('卡回收再发行', TfaqhCardReRelease);
end.
