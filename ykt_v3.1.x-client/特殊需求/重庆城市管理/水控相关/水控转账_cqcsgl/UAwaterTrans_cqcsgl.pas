unit UAwaterTrans_cqcsgl;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons, RzStatus, CardDll,WaterDll;

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
    procedure edtAddMoneyKeyPress(Sender: TObject; var Key: Char);
    procedure btnReadCardClick(Sender: TObject);
    procedure btnTranClick(Sender: TObject);
  private

    { Private declarations }
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
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
  btnTran.Enabled := False;
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
  waterPack:TWATERPACK;
begin
  if preReadCard=False then
    Exit;
  cm := nil;
  try
    cm := TCM.Create;
    //先清除所有的读取权限
    cm.clearallfieldreadmode;
    //设置要读取内容的权限
    setOperReadMode(cm);
    //cm.card(phyId);
    st := cm.readCard;
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
      Context.GetDialogSystem.ShowMessage('小钱包寻卡失败--'+inttostr(st));
      Exit;
    end;
    preReadWaterPack(waterPack);
    st := ks_sr_readmoney(@waterpack);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读取小钱包金额失败--'+inttostr(st));
      Exit;
    end;
    edtsmlMoney.Text := Format('%f',[waterPack.money/100.0]);
    smallCnt := waterPack.add_count;
    //edtsmlMoney.Text := 
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
  //kouMoney:Integer;
  //patchMoney:Integer;
  smlMoney:Integer;
  tp:TTRANSPACK;
  payCnt,dptCnt,subsidyNo:Integer;
  smlPhyId:string;
begin
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
    cm.clearallfieldreadmode;

    cm.setfieldreadmode(CARD_SERI_NO);
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PATCH_NO);
    cm.setfieldreadmode(DPT_CARD_CNT);
    if cm.readCard<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡信息失败，请重试！');
      Exit;
    end;
    phyId := cm.getCardSeriNo;
    if phyId='' then
    begin
      Context.GetDialogSystem.ShowMessage('读取物理卡号失败！');
      Exit;
    end
    else
    begin
      WorkView1.FieldByName('卡物理编号').Data.SetString(phyId);
    end;
    if phyId <> edtPhyId.Text then
    begin
      Context.GetDialogSystem.ShowMessage('请使用同一张卡进行充值！');
      btnReadCard.SetFocus;
      btnTran.Enabled := False;
      Exit;
    end;
    //cardBal := StrToInt(cm.getCardBalance);
    dptCnt:=StrToInt(cm.getDptCardCnt);
    payCnt := StrToInt(cm.getPayCardCnt);
    subsidyNo := StrToInt(cm.getPatchNo);
    balance := StrToInt(cm.getCardBalance);

    WorkView1.FieldByName('交易参考号').Data.SetString(tradeCode);
    WorkView1.FieldByName('随机数').Data.SetString(mac);
    WorkView1.FieldByName('卡号').Data.SetInteger(StrToInt(cm.getCardNo));
    WorkView1.FieldByName('卡余额').Data.SetInteger(balance);
    WorkView1.FieldByName('交易次数').Data.SetInteger(StrToInt(cm.getPayCardCnt));
    WorkView1.FieldByName('小钱包余额').Data.SetInteger(StrToInt(FloatToStr(StrToFloat(edtsmlMoney.Text)*100)));
    WorkView1.FieldByName('转账金额').Data.SetInteger(StrToInt(FloatToStr(StrToFloat(edtAddMoney.Text)*100)));
    WorkView1.FieldByName('支付代码').Data.SetInteger(1000);
    WVRequest1.SendCommand;
    if workview1.FieldByName('返回码').Data.AsInteger<>0 then
    begin
      getReturn('',WorkView1);
      Exit;
    end;
    accdate := WorkView1.fieldbyname('记账日期').Data.AsString;
    accTime := WorkView1.fieldbyname('记账时间').Data.AsString;
    outMoney := WorkView1.fieldbyname('出卡值').Data.AsInteger;
    //kouMoney := WorkView1.fieldbyname('扣款金额').Data.AsInteger;
    //patchMoney := WorkView1.fieldbyname('补写金额').Data.AsInteger;
    smlMoney := WorkView1.fieldbyname('小钱包余额').Data.AsInteger;
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
    st := ks_setcardbal(@tp);
    if st = 0 then
    begin
      //扣款成功开始写水控余额 ,写之前要先寻卡
      //读小钱包信息
      st := mfcard(smlPhyId);
      if st<>0 then
      begin
        Context.GetDialogSystem.ShowMessage('小钱包寻卡失败--'+inttostr(st));
        Exit;
      end;
      st := ks_sr_setmoeny(smlMoney,smallCnt+1);
      if st = 0 then
        cm.beep
      else
        Context.GetDialogSystem.ShowMessage('写水控钱包失败，请到冲正界面冲正该交易--'+inttostr(st));
      
    end
    else
    begin
      rzstspnStat.Caption:=CancelOper(WVcashOperCancel,WVRcashOperCancel,tradeCode,mac);
      btnReadCard.SetFocus;
      btnTran.Enabled := False;
      Exit;
    end;
    cm.halt;
    edtAfterMoney.Text := Format('%f',[outMoney/100.0]);
    edtAfterSmlMoney.Text := Format('%f',[smlMoney/100.0]);
    btnReadCard.SetFocus;
    btnTran.Enabled := False;
  finally
    cm.Destroy;
  end;

end;

initialization
  TUIStdClassFactory.Create('水控钱包转账',TfaqhwaterTrans_cqcsgl);

end.