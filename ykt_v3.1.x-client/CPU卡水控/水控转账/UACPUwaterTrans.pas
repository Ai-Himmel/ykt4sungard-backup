unit UACPUwaterTrans;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons, RzStatus, CardDll,WaterDll, RzPanel, RzRadGrp,
  UIncrementComboBox;

type
  TfaqhwaterTrans_cqcsgl = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    GroupBox1: TGroupBox;
    edtsmlMoney: TWVEdit;
    edtMoney: TWVEdit;
    edtStuempNo: TWVEdit;
    edtName: TWVEdit;
    edtCardNo: TWVEdit;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    grp1: TGroupBox;
    edtAddMoney: TWVEdit;
    RzStatusPane6: TRzStatusPane;
    btnTran: TBitBtn;
    btnReadCard: TButton;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    WVRcashOperCancel: TWVRequest;
    WVcashOperCancel: TWorkView;
    rzstspn1: TRzStatusPane;
    edtPhyId: TWVEdit;
    rzstspnStat: TRzStatusPane;
    rzstspn2: TRzStatusPane;
    edtAfterMoney: TWVEdit;
    rzstspn3: TRzStatusPane;
    edtAfterSmlMoney: TWVEdit;
    rzstspn4: TRzStatusPane;
    RzStatusPane7: TRzStatusPane;
    edtExpireDate: TWVEdit;
    cbbSmlNo: TWVComboBox;
    WVRWaterPrice: TWVRequest;
    WVWaterPrice: TWorkView;
    procedure edtAddMoneyKeyPress(Sender: TObject; var Key: Char);
    procedure btnReadCardClick(Sender: TObject);
    procedure btnTranClick(Sender: TObject);
    procedure edtAddMoneyKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
  private

    { Private declarations }
    cardno : Integer;                   //交易卡号
    custno : Integer;                   //客户号
    custtype : Integer;                 //客户类别
    expireddate : string;  //有效期
    lockflag : Integer;                 //锁定标志，00 锁定，FF可用
    //钱包信息
    money : Integer;                    //卡余额
    totalmoney : Integer;               //充值总金额
    addtime : string;                   //充值时间
    addcount : Integer;                 //充值次数
    {
    nprice1 : Integer;                   //水价1
    nprice2 : Integer;                   //水价2
    nprice3 : Integer;                   //水价3
    }
    smallCnt:Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhwaterTrans_cqcsgl: TfaqhwaterTrans_cqcsgl;

implementation

uses KsFrameworks,SmartCardCommon,KSClientConsts;
     
{$R *.DFM}

procedure TfaqhwaterTrans_cqcsgl.Init;
begin
  inherited;
  cbbSmlNo.ItemIndex := 0;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
  btnTran.Enabled := False;
  btnReadCard.SetFocus;
end;

procedure TfaqhwaterTrans_cqcsgl.edtAddMoneyKeyPress(Sender: TObject;var Key: Char);
begin
  inherited;
  if Checkedt(Key,edtAddMoney.Text)=False then
    Key := #0;
end;

procedure TfaqhwaterTrans_cqcsgl.btnReadCardClick(Sender: TObject);
var
  cm: TCM;
  phyId:string;
  st:SmallInt;
  waterPack:TWATERCOMMPACK;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
  smlbgNo:Integer;
begin
  try
    smlbgNo := StrToInt(Copy(cbbSmlNo.Text,1,Pos('-',cbbSmlNo.Text)-1));
    if (smlbgNo<=0) then
    begin
      Context.GetDialogSystem.ShowMessage('水控类型错误,请重新选择！');
      Exit;
    end;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('请选择要读取的水控类型');
      Exit;
    end;
  end;
  if preReadCard=False then
    Exit;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
      exit;
    end;
    //先清除所有的读取权限
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(CUST_NAME);
    cm.setfieldreadmode(STUEMP_NO);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(CARD_SERI_NO);
    //设置要读取内容的权限
    //setOperReadMode(cm);
    //cm.card(phyId);
    st := cm.readCard(phyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读取卡信息失败，请放好卡后重新读取-'+inttostr(st));
      Exit;
    end;
    edtPhyID.Text := cm.getCardSeriNo;
    edtCardNo.Text := cm.getCardNo;
    edtName.Text := cm.getCustName;
    edtStuempNo.Text := cm.getStuempNo;
    edtMoney.Text := format('%f', [strtofloat(cm.getCardBalance) / 100.0]);
    edtAfterMoney.Text := '';
    edtAfterSmlMoney.Text := '';

    //读小钱包信息
    st := mfcard(phyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('水控钱包寻卡失败--'+inttostr(st));
      Exit;
    end;
    preCommWaterPack(waterPack);
    st := ks_water_readmoney(smlbgNo,@waterpack);
    reSt := ks_geterrmsg(PChar(@reErrMsg));
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读取小钱包失败,该钱包已经回收-'+reSt+inttostr(st));
      Exit;
    end;
    edtsmlMoney.Text := Format('%f',[waterPack.money/100.0]);
    smallCnt := waterPack.addcount;
    cardno := waterPack.cardno;                     //交易卡号
    custno := waterPack.custno;                     //客户号
    custtype := waterPack.custtype;                 //客户类别
    expireddate := waterPack.expireddate;           //有效期
    edtExpireDate.Text := expireddate;
    lockflag := waterPack.lockflag;                 //锁定标志，00 锁定，FF可用
    // 钱包信息
    money := waterPack.money;                       //卡余额
    totalmoney := waterPack.totalmoney;             //充值总金额
    addtime := waterPack.addtime;                   //充值时间
    addcount := waterPack.addcount;                 //充值次数
    {
    nprice1 := waterPack.price1;                     //水价1
    nprice2 := waterPack.price2;                     //水价2
    nprice3 := waterPack.price3;                     //水价3
    }
    edtAddMoney.SetFocus;
    btnTran.Enabled := true;
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhwaterTrans_cqcsgl.btnTranClick(Sender: TObject);
var
  cm: TCM;
  phyId:string;
  st:Integer;
  tradeCode:string;
  mac:string;
  balance:Integer;
  accDate,accTime:string;
  outMoney:Integer;
  addMoney:Integer;
  smlMoney:Integer;
  tp:TTRANSPACK;
  payCnt,dptCnt,subsidyNo:Integer;
  smlPhyId:string;
  waterPack:TWATERCOMMPACK;
  smlbgNo:Integer;
  feeType:Integer;
begin
  try
    addMoney := StrToInt(FloatToStr(StrToFloat(edtAddMoney.Text)*100));
  except
    Context.GetDialogSystem.ShowMessage('请输入有效的转账金额！');
    Exit;
  end;
  try
    smlbgNo := StrToInt(Copy(cbbSmlNo.Text,1,Pos('-',cbbSmlNo.Text)-1));
    if (smlbgNo<=0) then
    begin
      Context.GetDialogSystem.ShowMessage('钱包号错误,请重新选择！');
      Exit;
    end;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Exit;
    end;
  end;
  //先取交易参考号
  WorkView.FieldByName('终端号').Data.SetInteger(StrToInt(scSiteNo));
  WorkView.FieldByName('时间戳').Data.SetString(FormatDateTime('yyyymmddhhmmss',Now));
  MainRequest.SendCommand;
  if WorkView.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    getReturn('',WorkView);
    Exit;
  end;
  tradeCode := WorkView.fieldbyname('交易参考号').Data.AsString;
  mac := WorkView.fieldbyname('随机数').Data.AsString;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
      exit;
    end;
    cm.clearallfieldreadmode;

    cm.setfieldreadmode(CARD_SERI_NO);
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(PATCH_NO);
    cm.setfieldreadmode(CARD_LIMIT_TYPE);
    cm.setfieldreadmode(BLACK_CARD_SIGN);

    if cm.readCard(phyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡信息失败，请重试！');
      Exit;
    end;
    if cm.getBlackCardSign<>'0' then
    begin
      Context.GetDialogSystem.ShowMessage('该卡不是正常状态的卡，不能转账，请到读卡信息中读取卡状态！');
      Exit;
    end;
    if phyId <> edtPhyId.Text then
    begin
      Context.GetDialogSystem.ShowMessage('请使用同一张卡进行充值！');
      btnReadCard.SetFocus;
      btnTran.Enabled := False;
      Exit;
    end;
    dptCnt:=StrToInt(cm.getDptCardCnt);
    payCnt := StrToInt(cm.getPayCardCnt);
    subsidyNo := StrToInt(cm.getPatchNo);
    balance := StrToInt(cm.getCardBalance);
    feeType := StrToInt(cm.getCardLimitType);
    WorkView1.FieldByName('卡物理编号').Data.SetString(phyId);
    WorkView1.FieldByName('交易参考号').Data.SetString(tradeCode);
    WorkView1.FieldByName('随机数').Data.SetString(mac);
    WorkView1.FieldByName('卡号').Data.SetInteger(StrToInt(cm.getCardNo));
    WorkView1.FieldByName('卡余额').Data.SetInteger(balance);
    WorkView1.FieldByName('交易次数').Data.SetInteger(payCnt);
    WorkView1.FieldByName('小钱包余额').Data.SetInteger(StrToInt(FloatToStr(StrToFloat(edtsmlMoney.Text)*100)));
    WorkView1.FieldByName('转账金额').Data.SetInteger(addMoney);
    WorkView1.FieldByName('钱包号').Data.SetInteger(smlbgNo);
    WorkView1.FieldByName('支付代码').Data.SetInteger(1191);
    WVRequest1.SendCommand;
    if workview1.FieldByName('返回码').Data.AsInteger<>0 then
    begin
      getReturn('',WorkView1);
      Exit;
    end;
    setWaterPrice(WVWaterPrice,WVRWaterPrice,feeType);
    
    accdate := WorkView1.fieldbyname('记账日期').Data.AsString;
    accTime := WorkView1.fieldbyname('记账时间').Data.AsString;
    outMoney := WorkView1.fieldbyname('出卡值').Data.AsInteger;
    smlMoney := WorkView1.fieldbyname('小钱包余额').Data.AsInteger;
    ZeroMemory(@tp,SizeOf(tp));
    //从大钱包扣款
    //终端交易序列号
    tp.TermSeqno := 1;
    //终端编号
    StrCopy(@tp.Termno,PChar(scSiteNo));
    //交易卡号
    tp.CardNo := StrToInt(edtCardNo.Text);
    //物理编号
    StrCopy(@tp.CardPhyID,PChar(phyId));
    //交易日期
    StrCopy(@tp.TransDate,PChar(accdate));
    //交易时间
    StrCopy(@tp.TransTime,PChar(accTime));
    //交易前金额
    tp.BefBalance := balance;
    //交易后金额
    tp.AftBalance := outMoney;
    //交易前充值次数
    tp.DptCardCnt := dptCnt;
    //交易前消费次数
    tp.PayCardCnt := payCnt;
    //交易前补助次数
    tp.SubsidyNo := subsidyNo;

    st := setCardBal(tp,cm,phyId);//ks_setcardbal(@tp);
    if st = 0 then
    begin
      //扣款成功开始写水控余额 ,写之前要先寻卡
      //读小钱包信息
      st := mfcard(smlPhyId);
      if st<>0 then
      begin
        Context.GetDialogSystem.ShowMessage('水控钱包寻卡失败--'+inttostr(st));
        Exit;
      end;
      //设置小钱包结构体
      waterPack.cardno := cardno;
      waterPack.custno := custno;
      waterPack.custtype := custtype;
      StrCopy(@waterPack.expireddate,PChar(FormatDateTime('yyyymmdd',Date+waterExpiredate)));
      //ShowMessage(waterPack.expireddate);
      waterPack.lockflag := lockflag;
      waterPack.money := smlMoney;
      waterPack.totalmoney := totalmoney+addMoney;
      StrCopy(@waterPack.addtime,PChar(addtime));
      waterPack.addcount := addcount+1;
      waterPack.price1 := cpuWaterPrice1;
      waterPack.price2 := cpuWaterPrice2;
      waterPack.price3 := cpuWaterPrice3;
      //ShowMessage(IntToStr(waterPack.money));
      st := ks_water_writemoney(smlbgNo,@waterPack);

      if st = 0 then
      begin
        cm.beep;
        Context.GetDialogSystem.ShowMessage(workview1.FieldByName('返回信息').Data.AsString);
        rzstspnStat.Caption:= workview1.FieldByName('返回信息').Data.AsString;
      end
      else
        Context.GetDialogSystem.ShowMessage('写水控钱包失败，请到冲正界面冲正该交易--'+inttostr(st));      
    end
    else
    begin
      //rzstspnStat.Caption:=CancelOper(WVcashOperCancel,WVRcashOperCancel,tradeCode,mac)+inttostr(st);
      btnReadCard.SetFocus;
      btnTran.Enabled := False;
      Exit;
    end;
    //cm.halt;
    edtAfterMoney.Text := Format('%f',[outMoney/100.0]);
    edtAfterSmlMoney.Text := Format('%f',[smlMoney/100.0]);
    edtExpireDate.Text := FormatDateTime('yyyymmdd',Date+waterExpiredate);
    btnReadCard.SetFocus;
    btnTran.Enabled := False;
  finally
    cm.Destroy;
  end;

end;

procedure TfaqhwaterTrans_cqcsgl.edtAddMoneyKeyDown(Sender: TObject;var Key: Word; Shift: TShiftState);
begin
  inherited;
  if key = vk_return then
    btnTran.SetFocus;

end;

initialization
  TUIStdClassFactory.Create('水控钱包转账',TfaqhwaterTrans_cqcsgl);

end.