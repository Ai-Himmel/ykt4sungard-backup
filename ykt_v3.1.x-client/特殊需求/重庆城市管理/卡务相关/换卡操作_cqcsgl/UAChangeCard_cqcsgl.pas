unit UAChangeCard_cqcsgl;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db,WaterDll,
  RzDBGrid, RzStatus, RzPanel, Buttons, CardDll, UIncrementComboBox;

type
  TfaqhnewStuChangeCard = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    btnReadCardQuery: TBitBtn;
    btnPatchCard: TBitBtn;
    grp1: TGroupBox;
    lbl1: TLabel;
    edtEndDate: TWVEdit;
    Label1: TLabel;
    edtCustNo: TWVEdit;
    WVComboBox1: TWVComboBox;
    WVLabel6: TWVLabel;
    WVLabel2: TWVLabel;
    WVComboBox3: TWVComboBox;
    WVEdit4: TWVEdit;
    WVLabel9: TWVLabel;
    Label5: TLabel;
    WVEdit5: TWVEdit;
    WVComboBox2: TWVComboBox;
    WVLabel1: TWVLabel;
    Label3: TLabel;
    WVEdit3: TWVEdit;
    WVEdit2: TWVEdit;
    Label2: TLabel;
    Label7: TLabel;
    WVLabel5: TWVLabel;
    WVLabel8: TWVLabel;
    Label6: TLabel;
    edtCardNo: TWVEdit;
    WVComboBox5: TWVComboBox;
    WVComboBox6: TWVComboBox;
    WVEdit8: TWVEdit;
    WorkViewOK: TWorkView;
    WVRequestOK: TWVRequest;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnPrintClick(Sender: TObject);
    procedure btnReadCardQueryClick(Sender: TObject);
    procedure btnPatchCardClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure edtShowCardKeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
    procedure replaceNewCard(phyCardId:string;cardNo:Integer;operType:string);//更换新生卡信息
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhnewStuChangeCard: TfaqhnewStuChangeCard;

implementation

uses KsFrameworks, KSClientConsts,SmartCardCommon;

{$R *.DFM}

procedure TfaqhnewStuChangeCard.Init;
begin
  inherited;
  edtEndDate.Text:=FormatDateTime('yyyymmdd',Date()+1461);
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
end;

procedure TfaqhnewStuChangeCard.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhnewStuChangeCard.btnPrintClick(Sender: TObject);
var
  cm:TCM;
  //读卡信息
  rmoney:Integer;
  rTrade:Integer;
  rPatchNo:Integer;
  PCardId:string;
  smlPhyId:string;

  cardNo:string;
  st:Integer;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowWarning('没有数据，无法进行此操作！');
    Exit;
  end;

  //读卡获得相关信息
  cm := nil;
  try
    cm:=TCM.Create();
    //先清除所有的读取权限
    cm.clearallfieldreadmode;
    //设置要读取内容的权限
    setOperReadMode(cm);
    if cm.readCard<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡信息失败，请重试！');
      exit;
    end;
    //取物理卡号
    PCardId := cm.getCardSeriNo;
    if PCardId='' then
    begin
      Context.GetDialogSystem.ShowMessage('读卡序列号失败！');
      exit;
    end;
    try
      rmoney:=StrToInt(cm.getCardBalance);
      rTrade:=StrToInt(cm.getCardCnt);
      rPatchNo := StrToInt(cm.getPatchNo);
    except
      Context.GetDialogSystem.ShowWarning('读用户卡消费信息失败！');
      Exit;
    end;
    //老卡的卡号
    cardNo:=cm.getCardNo;

    //清空前先给后台发送清除卡信息消息，发送成功后再情况卡信息 847122
    WorkViewOK.FieldByName('操作类型').Data.SetString('S');

    WorkViewOK.FieldByName('原卡号').Data.SetInteger(StrToInt((cardNo)));
    WorkViewOK.FieldByName('原物理编号').Data.SetString(PCardID);
    WorkViewOK.FieldByName('原卡余额').Data.SetInteger(rmoney);
    WorkViewOK.FieldByName('原卡交易次数').Data.SetInteger(rTrade);
    WorkViewOK.FieldByName('补助批次号').Data.SetInteger(rPatchNo);

    WorkViewOK.FieldByName('新卡物理编号').Data.SetString('');
    WorkViewOK.FieldByName('显示卡号').Data.SetString('');
    WorkViewOK.FieldByName('到期日期').Data.SetString('');
    
    WorkViewOK.FieldByName('业务日期').Data.SetString('');
    WorkViewOK.FieldByName('流水号').Data.SetInteger(0);
    WorkViewOK.FieldByName('终端编号').Data.SetInteger(0);
    WVRequestOK.SendCommand;
    if WorkViewOK.FieldByName('返回码').Data.AsInteger<>0 then
    begin
      getReturn('清空卡失败--',WorkViewOK);
      RzStatusPane1.Caption:=WorkViewOK.FieldByName('返回信息').Data.AsString;
      Exit;
    end;
    //清空新生临时卡信息，清除成功后把信息送到后台，后台把清空该卡标志写上

    st := cm.clearCard(WorkViewOK);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('旧卡内容清除失败，请检查该卡是否可用--'+inttostr(st));
      Exit;
    end
    else
    begin
      mfcard(smlPhyId);
      st := ks_sr_setmoeny(0,1);
      cm.beep;
      Context.GetDialogSystem.ShowMessage('旧卡内容已清除成功，请先把要更换的卡放置好！');

      //开始把卡信息写到新卡上去
      //ShowMessage(cardNo);
      replaceNewCard(PCardID,StrToInt(cardNo),'C');
    end;
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhnewStuChangeCard.btnReadCardQueryClick(Sender: TObject);
begin
  //FCurrentCardNo := readCardNo;
  edtCardNo.Text:= readCardOneInfo(CARD_NO);
  btnQueryClick(Sender);
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhnewStuChangeCard.replaceNewCard更换新生卡信息
  作者:      Administrator
  日期:      2005.07.29
  参数:      无
  返回值:    Boolean
-------------------------------------------------------------------------------}
procedure TfaqhnewStuChangeCard.replaceNewCard(phyCardId:string;cardNo:Integer;operType:string);
var
  cm:TCM;
  newphyCardNo:string;
  inShowCardNo:string;

  tradeCardNo:Integer;      //交易卡号
  showCardNo:string;        //显示卡号
  tradeNum:Integer;         //交易次数
  cardEndDate:string;       //卡使用截至日期
  limitType:Integer;        //卡使用权限
  custType:Integer;         //客户类别
  custName:string;          //客户姓名
  cardID:string;            //身份证号
  deptNo:string;            //部门代码
  sex:string;               //性别
  stuempNo:string;          //学工号
  cardBalance:Integer;      //卡余额
  cardPWD:string;           //卡密码
  sOperDate:string;         //操作日期
  stationId:Integer;        //终端编号
  backTradeID:Integer;      //后台交易流水号
  maxPerCount:Integer;      //单次限额
  maxPerDay:Integer;        //日限额
  cardType:string;         //卡类型
  custId:string;
  relCardSign:string;
  certType:string;
  re:Integer;
  ResInt:Integer;
  patchNo:Integer;
  //sNewCardNo:string;
  tradeTime:string;

  i:Integer;
  tryNum:Integer;
  tmpPhyId:string;
  TOF: Integer;
  tp:TTRANSPACK;

  waterCard:TWATERINFO;
  st:Integer;
  pCardID:string;
begin
  if preReadCard=False then
    Exit;
  re := 0;
  ResInt := 0;
  stationId := 0;
  backTradeID := 0;
  //检测是否有卡，无卡则退出
  if (StrToInt(strToZero(readCardOneInfo(CARD_NO)))>0) and (StrToInt(strToZero(readCardOneInfo(BLACK_CARD_SIGN)))=0) then
  begin
      Context.GetDialogSystem.ShowMessage('该卡已经在使用，先撤销该卡的换卡，放置一张新卡后重新操作！');
      Exit;
  end;
  cm := nil;
  try
    cm := TCM.Create();
    //先清除所有的读取权限
    cm.clearallfieldreadmode;
    //设置要读取内容的权限
    setOperReadMode(cm);
    if cm.readCard<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡信息失败，请重试！');
      Exit;
    end;
    newphyCardNo := cm.getCardSeriNo;
    if newphyCardNo='' then
    begin
      Context.GetDialogSystem.ShowMessage('读卡序列号失败，请先撤销换卡，然后准备好新卡重新操作！');
      Exit;
    end;
    inShowCardNo := cm.getShowCardNo;
    //把新卡的物理编号及相关信息传入后台
    WorkViewOK.FieldByName('操作类型').Data.SetString(operType);
    WorkViewOK.FieldByName('原卡号').Data.SetInteger(cardNo);
    WorkViewOK.FieldByName('原物理编号').Data.SetString(phyCardId);
    WorkViewOK.FieldByName('原卡余额').Data.SetInteger(0);
    WorkViewOK.FieldByName('原卡交易次数').Data.SetInteger(0);
    WorkViewOK.FieldByName('补助批次号').Data.SetInteger(0);

    WorkViewOK.FieldByName('新卡物理编号').Data.SetString(newphyCardNo);
    WorkViewOK.FieldByName('显示卡号').Data.SetString(inShowCardNo);
    WorkViewOK.FieldByName('到期日期').Data.SetString(Trim(edtEndDate.Text));
    
    WorkViewOK.FieldByName('业务日期').Data.SetString('');
    WorkViewOK.FieldByName('流水号').Data.SetInteger(0);
    WorkViewOK.FieldByName('终端编号').Data.SetInteger(0);
    try
      WVRequestOK.SendCommand;
    except
      on ex:Exception do
      begin
        Context.GetDialogSystem.ShowMessage(ex.Message);
        exit;
      end;
    end;
    if WorkViewOK.FieldByName('返回码').Data.AsInteger=0 then
    begin
      //开始发行新卡，失败则发送冲正交易
      try
        tradeCardNo:=WorkViewOK.fieldbyname('卡号').Data.AsInteger;

        showCardNo:=WorkViewOK.fieldbyname('显示卡号').Data.AsString;
        cardEndDate:=WorkViewOK.fieldbyname('到期日期').Data.AsString;
        limitType:=WorkViewOK.fieldbyname('收费类别').Data.AsInteger;
        custType:=WorkViewOK.fieldbyname('客户类别').Data.AsInteger;
        custName:=WorkViewOK.fieldbyname('客户姓名').Data.AsString;
        //dutyNo:='';
        cardID:=WorkViewOK.fieldbyname('证件号码').Data.AsString;
        deptNo:=WorkViewOK.fieldbyname('部门代码').Data.AsString;
        //bookID:='';
        sex:=WorkViewOK.fieldbyname('性别').Data.AsString;
        stuempNo:=WorkViewOK.fieldbyname('学工号').Data.AsString;
        cardBalance:=WorkViewOK.fieldbyname('出卡值').Data.AsInteger;
        cardPWD:=WorkViewOK.fieldbyname('卡密码').Data.AsString;
        //isFormation := Char('N');

        backTradeID:=WorkViewOK.fieldbyname('流水号').Data.AsInteger;
        sOperDate := WorkViewOK.fieldbyname('业务日期').Data.AsString;
        tradeTime := WorkViewOK.fieldbyname('业务时间').Data.AsString;
        stationId := WorkViewOK.fieldbyname('终端编号').Data.AsInteger;
        tradeNum := WorkViewOK.fieldbyname('交易次数').Data.AsInteger;
        patchNo := WorkViewOK.fieldbyname('补助批次号').Data.AsInteger;

        certType := WorkViewOK.fieldbyname('证件类型').Data.AsString;
        relCardSign := WorkViewOK.fieldbyname('发行方标识').Data.AsString;
        cardType := WorkViewOK.fieldbyname('卡类型').Data.AsString;
        custId := WorkViewOK.fieldbyname('客户号').Data.AsString;
      except
        on ex:Exception do
        begin
          Context.GetDialogSystem.ShowMessage('后台返回数据有误--'+ex.Message);
          Exit;
        end;
      end;
      //先清除所有的读取权限
      cm.clearallfieldreadmode;
      //设置要读取内容的权限
      setOperReadMode(cm);

      cm.setCardNo(IntToStr(tradeCardNo));
      cm.setShowCardNo(showCardNo);
      cm.setDeadLineDate(cardEndDate);
      cm.setCardLimitType(IntToStr(limitType));
      cm.setCustType(IntToStr(custType));
      cm.setDeptNo(deptNo);
      cm.setCustName(custName);
      //证件类型--没有
      cm.setCertType(certType);
      cm.setCertNo(cardID);
      cm.setCustSex(sex);
      cm.setStuempNo(stuempNo);
      //发卡方标识---没有
      //卡类型
      //客户号
      cm.setReaCardSign(relCardSign);
      cm.setCardType(cardType);
      cm.setCustNo(custId);
      cm.setCardPwd(cardPWD);
      cm.setPatchNo(IntToStr(patchNo));
      cm.setBlackCardSign(IntToStr(NORMAL_CARD));
      cm.setBlackVer('00000000000000');
      //cm.setCardCnt(IntToStr(tradeNum));
      //设置单次消费限额和日消费限额
      if maxper=1 then
      begin
        maxPerCount := WorkViewOK.fieldbyname('单次限额').Data.AsInteger;
        maxPerDay := WorkViewOK.fieldbyname('日限额').Data.AsInteger;
        cm.setMaxPerCount(IntToStr(maxPerCount));
        cm.setMaxPerDay(IntToStr(maxPerDay));
      end;
      re := cm.writeData;
      {TODO:设置交易次数和卡余额}
      if re = 0 then
      begin
        //终端交易序列号
        tp.TermSeqno := 1;
        //终端编号
        StrCopy(@tp.Termno,PChar(scSiteNo));
        //交易卡号
        tp.CardNo := tradeCardNo;
        //物理编号
        StrCopy(@tp.CardPhyID,PChar(newphyCardNo));
        //交易日期
        StrCopy(@tp.TransDate,PChar(sOperDate));
        //交易时间
        StrCopy(@tp.TransTime,PChar(tradeTime));
        //交易后金额
        tp.AftBalance :=  cardBalance;
        //交易前金额
        tp.BefBalance := 0;
        //交易前充值次数
        tp.DptCardCnt := 0;
        //交易前消费次数
        tp.PayCardCnt := 0;
        //交易前补助次数
        tp.SubsidyNo := 0;
        tof := ks_setcardbal(@tp);
      end;
      try
        ResInt := StrToInt(readCardOneInfo(CARD_NO));
      except
        ResInt := 0;
      end;
      //ShowMessage(IntToStr(re)+'ResInt'+inttostr(ResInt)+'tof'+inttostr(tof));
      if ((re <> 0) or (ResInt=0) or (TOF<>0)) then
      begin
        if Application.MessageBox(PChar('写卡失败，请使用同一张卡并正确放置到读写器上，你要重试一次吗？'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
          Exit;
        //读卡物理编号，和以前的物理编号比较，不一样则不行
        tmpPhyId := readCardOneInfo(CARD_SERI_NO);
        if tmpPhyId='' then
        begin
          Context.GetDialogSystem.ShowMessage('读卡物理编号失败，请把该卡先撤销换卡，然后重新做换卡交易！');
          Exit;
        end;
        if tmpPhyId<>newphyCardNo then
        begin
          Context.GetDialogSystem.ShowMessage('和刚才放置的不是同一张卡，请把该卡先撤销换卡，然后重新做换卡交易！');
          Exit;
        end;
        //重新写一次卡
        re := cm.writeData;
        tof := ks_setcardbal(@tp);
        //发卡成功，读卡号成功，读取卡号大于零才确定该卡已经发行成功，否则重新发行
        try
          ResInt := StrToInt(readCardOneInfo(CARD_NO));
        except
          ResInt := 0;
        end;
      end;
    end
    else
    begin
      //getReturn('',WorkViewOK);
    end;
  finally
    if ((re = 0) and (ResInt>0)) then
    begin
      //完成后发行水控钱包
      st := mfcard(pCardID);
      waterCard.cardno := tradeCardNo;
      waterCard.custno := StrToInt(custId);
      waterCard.cardtype := 1;
      st := ks_sr_publishcard(@waterCard);
      cm.beep;
      if operType='D' then
        Context.GetDialogSystem.ShowMessage('该卡已经撤销换卡成功  '+WorkViewOK.FieldByName('返回信息').Data.AsString)
      else
        Context.GetDialogSystem.ShowMessage('该卡已经换卡成功  '+WorkViewOK.FieldByName('返回信息').Data.AsString);
     //Context.GetDialogSystem.ShowMessage('显示卡号为：'+showCardNo+'的卡换卡成功');
     if st=0 then
      RzStatusPane1.Caption:='显示卡号为：'+showCardNo+'的卡换卡成功'
     else
      RzStatusPane1.Caption:='显示卡号为：'+showCardNo+'的卡换卡成功,但水控钱包写卡失败！';

    end

    else
    begin
      WorkViewOK.FieldByName('操作类型').Data.SetString('V');

      WorkViewOK.FieldByName('原卡号').Data.SetInteger(0);
      WorkViewOK.FieldByName('原物理编号').Data.SetString('');
      WorkViewOK.FieldByName('原卡余额').Data.SetInteger(0);
      WorkViewOK.FieldByName('原卡交易次数').Data.SetInteger(0);

      WorkViewOK.FieldByName('新卡物理编号').Data.SetString('');
      WorkViewOK.FieldByName('显示卡号').Data.SetString('');
      WorkViewOK.FieldByName('到期日期').Data.SetString('');

      WorkViewOK.FieldByName('业务日期').Data.SetString(sOperDate);
      WorkViewOK.FieldByName('流水号').Data.SetInteger(backTradeID);
      WorkViewOK.FieldByName('终端编号').Data.SetInteger(stationId);
      WVRequestOK.SendCommand;
    end;
    cm.Destroy;
  end;
end;

procedure TfaqhnewStuChangeCard.btnPatchCardClick(Sender: TObject);
var
  tmpdata:TDataSet;
  phyCardId,tmpPhyId:string;
  cardNo:Integer;
begin
  //inherited;
  try
    tmpdata:=WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet;
    phyCardId := tmpdata.fieldbyname('sstation1').AsString;
    cardNo := tmpdata.fieldbyname('lvol0').AsInteger;
  except
    on ex:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('错误信息：'+ex.Message+' 可能没有查询结果');
      Exit;
    end;
  end;
  if preReadCard=False then
  Exit;
  //取物理卡号
  tmpPhyId := readCardOneInfo(CARD_SERI_NO);
  if tmpPhyId='' then
  begin
    Context.GetDialogSystem.ShowMessage('读卡序列号失败，请重新把卡放置到读写器上！');
    exit;
  end;

  if tmpPhyId<>phyCardId then
  begin
    Context.GetDialogSystem.ShowMessage('要撤销的卡和查询出的卡不是同一张卡！');
    Exit;
  end;
  replaceNewCard(phyCardId,cardNo,'D');
end;

procedure TfaqhnewStuChangeCard.btnQueryClick(Sender: TObject);
begin
  if (edtCardNo.Text)='' then
    edtCardNo.Text:='0';
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text:='0';
  inherited;
end;

procedure TfaqhnewStuChangeCard.edtShowCardKeyPress(Sender: TObject;
  var Key: Char);
begin
  //inherited;
  if inputNum(Key)=False then
    Key := #0;

end;

initialization
  TUIStdClassFactory.Create('新生换卡操作',TfaqhnewStuChangeCard);

end.