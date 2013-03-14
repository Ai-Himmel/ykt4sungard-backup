unit UAnonymityCard;

interface
              
uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhInputTemp, WVCmdReq, WorkViews, StdCtrls, ExtCtrls,
  UICtrls, WVCtrls, Mask, CardDll,WaterDll, 
  RzPanel, RzStatus, Buttons, UIncrementComboBox,
  EditExts;

type
  TfaqhAnonyCard = class(TfaqhInputTemp)
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
    edtDate: TWVEdit;
    edtTicketNo: TWVEdit;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    lbl1: TLabel;
    WVFeeQuery: TWorkView;
    WVRFeeQuery: TWVRequest;
    WVRReleaseCard: TWVRequest;
    WVReleaseCard: TWorkView;
    WVRelCardOk: TWorkView;
    WVRRelCardOk: TWVRequest;
    RzStatusPane7: TRzStatusPane;
    cbbType: TWVComboBox;
    Label1: TLabel;
    btnReleaseCard: TBitBtn;
    edtmoney: TWVDigitalEdit;
    chkSaveMoney: TCheckBox;
    RzStatusPane2: TRzStatusPane;
    cbbPhyType: TWVComboBox;
    WVWaterPrice: TWorkView;
    WVRWaterPrice: TWVRequest;
    procedure edtDateExit(Sender: TObject);
    procedure edtmoneyKeyPress(Sender: TObject; var Key: Char);
    procedure edtTicketNoKeyPress(Sender: TObject; var Key: Char);
    procedure cbbCardTypeChange(Sender: TObject);
    procedure cbbFeeTypeChange(Sender: TObject);
    procedure btnReleaseCardClick(Sender: TObject);
  private
    { Private declarations }
   //procedure lineWriteCard;

    procedure getFeeResult;
  public
    { Public declarations }
    procedure Init;override;
  end;

var
  faqhAnonyCard: TfaqhAnonyCard;

implementation
uses KSFrameWorks, KSClientConsts,SmartCardCommon;

{$R *.DFM}

procedure TfaqhAnonyCard.Init;
begin
  inherited;
  //cbbPhyType.ItemIndex := 0;
  //getFeeResult;
  edtDate.Text:=formatdatetime('yyyymmdd',(Date()+365));
  edtmoney.Text := '0';
  cbbPhyType.ItemIndex := 0;
  cbbType.ItemIndex := 0;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
end;

procedure TfaqhAnonyCard.edtDateExit(Sender: TObject);
begin
  inherited;
  if CheckInputDateFormat(edtDate.Text)=false then
  begin
    Context.GetDialogSystem.ShowMessage('日期输入有误，请重新输入');
    edtDate.Text:=formatdatetime('yyyymmdd',(Date()+365));
    edtDate.SetFocus;
  end;
end;

procedure TfaqhAnonyCard.edtmoneyKeyPress(Sender: TObject; var Key: Char);
begin
  //inherited;
  if Checkedt(Key,edtmoney.Text)=False then
    Key := #0;
end;

procedure TfaqhAnonyCard.edtTicketNoKeyPress(Sender: TObject;
  var Key: Char);
begin
  //inherited;
  if inputNum(Key)=False then
    Key := #0;

end;

procedure TfaqhAnonyCard.getFeeResult;
var
  feeType: Integer;
  sReturnInfo:string;
  fMoney:real;
  cardType:Integer;
begin
  edtTicketNo.Text:='';
  if (cbbType.ItemIndex = 0) then
    edtTicketNo.Enabled := False
  else
    edtTicketNo.Enabled := True;

  try
    cardType := StrToInt(Copy(cbbPhyType.Text,1,Pos('-',cbbPhyType.Text)-1));
    feeType := 0;//StrToInt(Copy(cbbFeeType.Text,1,Pos('-',cbbFeeType.Text)-1));
  except
    Exit;
  end;
  WVFeeQuery.FieldByName('收费类别').Data.SetInteger(feeType);
  WVFeeQuery.FieldByName('卡类型').Data.SetInteger(cardType);
  WVFeeQuery.FieldByName('客户号').Data.SetInteger(0);
  WVFeeQuery.FieldByName('功能号').Data.SetInteger(846301);
  WVFeeQuery.FieldByName('是否不记名卡').Data.setstring('1');
  WVRFeeQuery.SendCommand;
  if WVFeeQuery.FieldByName('返回码').Data.AsInteger=0 then
  begin
    sReturnInfo := WVFeeQuery.fieldbyname('收费信息').Data.AsString;
    edtDate.Text := WVFeeQuery.Fieldbyname('卡有效期').Data.AsString;
    fMoney := WVFeeQuery.fieldbyname('总费用').Data.AsFloat;
    if chkSaveMoney.Checked=False then
      edtMoney.Text := floattostr(fMoney);
    RzStatusPane1.Caption := sReturnInfo;
  end;
end;

procedure TfaqhAnonyCard.cbbCardTypeChange(Sender: TObject);
begin
  inherited;
  getFeeResult;
end;

procedure TfaqhAnonyCard.cbbFeeTypeChange(Sender: TObject);
begin
  inherited;
  getFeeResult;
end;

procedure TfaqhAnonyCard.btnReleaseCardClick(Sender: TObject);
var
  showCardNo:string;
  pCardID:string;
  feeType:string;
  cm: TCM;
  operCode:string;
  saveType:string;
  cardPhyType:integer;
  cardSelfType:integer;
  reCode:integer;
  cardType:Integer;
  custId:Integer;
  //waterCard:TWATERCOMMPACK;
  cardNo:Integer;
  cardEndDate:string;
  custType:Integer;
  st:Integer;
  rst:integer;
  payCnt,dptCnt:Integer;
  //showCard
begin
  saveType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
  if saveType='' then
  begin
    Context.GetDialogSystem.ShowMessage('请选择充值类型,然后再进行发卡！');
    cbbType.SetFocus;
    Exit;
  end;
  if Trim(edtDate.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('请输入卡有效期！');
    Exit;
  end;
  if CheckInputDateFormat(edtDate.Text)=False then
  begin
    Context.GetDialogSystem.ShowMessage('卡有效期输入不正确，格式：yyyymmdd');
    edtDate.SetFocus;
    Exit;
  end;
  if relCardJudge=False then
    Exit;
  {
  if readCardOneInfo(APP_TYPE)='0' then
  begin
    context.GetDialogSystem.ShowMessage('该卡没有初始化，请先初始化！');
    exit;
  end;
  if readCardOneInfo(CARD_BALANCE)<>'0' then
  begin
    context.GetDialogSystem.ShowMessage('该卡金额不为零，先回收该卡！');
    exit;
  end;
  }
  cardNo := 0;
  cm := nil;
  try
    cm := TCM.Create;
    rst := cm.card(pCardID);
    if rst<>0 then
    begin
      context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
      exit;
    end;

    cm.clearallfieldreadmode;
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(APP_TYPE);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(SHOW_CARDNO);
    if cm.readCard(pCardID)<>0 then
    begin
      context.GetDialogSystem.ShowMessage('该卡没有初始化，请先初始化！');
      exit;
    end
    else
    begin
      {
      if (cm.getAppType='') or (cm.getAppType='0') then
      begin
        context.GetDialogSystem.ShowMessage('该卡初始化类别不正确，请重新初始化-'+cm.getAppType);
        exit;
      end;
      }
      if (cm.getCardBalance='') or (cm.getCardBalance<>'0') then
      begin
        context.GetDialogSystem.ShowMessage('该卡金额不为零，先回收该卡！');
        exit;
      end;
      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      //取得显示卡号
      showCardNo:=cm.getShowCardNo;
    end;
    //取卡内部编码
    try
      cardSelfType := ks_cardtype();
    except
      cardSelfType := 0;
    end;
    //取得显示卡号
    //showCardNo:=readCardOneInfo(SHOW_CARDNO);
    //发卡类型
    cardType := StrToInt(Copy(cbbPhyType.Text,1,Pos('-',cbbPhyType.Text)-1));
    try
      //收费方式
      feeType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
      //卡物理类型
      cardPhyType := 0;//StrToInt(Copy(cbbPhyType.Text,1,Pos('-',cbbPhyType.Text)-1));
    except
      feeType :='0';
      cardPhyType := 0;
    end;
    //操作员
    operCode := Context.ParamData(svOperatorNoName).AsString;
    WVReleaseCard.FieldByName('操作员').Data.SetString(operCode);
    WVReleaseCard.FieldByName('显示卡号').Data.SetString(showCardNo);        //
    WVReleaseCard.FieldByName('物理卡号').Data.SetString(pCardID);           //
    WVReleaseCard.FieldByName('收费方式').Data.SetInteger(StrToInt(feeType));
    WVReleaseCard.FieldByName('票据号码').Data.SetString(edtTicketNo.Text);
    WVReleaseCard.FieldByName('到期日期').Data.SetString(edtDate.Text);
    WVReleaseCard.FieldByName('卡类型').Data.SetInteger(cardType);
    WVReleaseCard.FieldByName('卡物理类型').Data.SetInteger(cardPhyType);
    WVReleaseCard.FieldByName('卡内部编码').Data.SetInteger(cardSelfType);
    WVReleaseCard.FieldByName('客户号').Data.SetInteger(0);
    WVReleaseCard.FieldByName('收费金额').Data.SetFloat(StrToFloat(edtMoney.Text));
    WVReleaseCard.FieldByName('是否不记名卡').Data.SetString('1');
    WVReleaseCard.FieldByName('充值次数').Data.SetInteger(dptCnt);
    WVReleaseCard.FieldByName('消费次数').Data.SetInteger(payCnt);
    WVRReleaseCard.SendCommand;
    if (WVReleaseCard.FieldByName('返回码').Data.AsInteger = 0) then
    begin
      if waterStrings.Count = 0 then
      begin
        RzStatusPane1.Caption:=pubCardNew(WVReleaseCard,WVRelCardOk,WVRRelCardOk,pCardID,1,reCode);
        if reCode = 0 then
          kng_beep;
      end
      else
      begin
        //初始化水控卡
        RzStatusPane1.Caption:=pubCardNew(WVReleaseCard,WVRelCardOk,WVRRelCardOk,pCardID,0,reCode);
        cardNo:=WVReleaseCard.fieldbyname('卡号').Data.AsInteger;

        if reCode >= 0 then
        begin
          cardEndDate:=WVReleaseCard.fieldbyname('到期日期').Data.AsString;
          custType := WVReleaseCard.fieldbyname('收费类别').Data.AsInteger;
          custId := WVReleaseCard.fieldbyname('客户号').Data.AsInteger;
          {
          st := mfcard(pCardID);
          //ShowMessage(IntToStr(st));
          waterCard.cardno := cardNo;
          waterCard.custno := custId;
          watercard.custtype := custType;
          StrCopy(@waterCard.expireddate,PChar(cardEndDate));
          waterCard.lockflag := 255;
          waterCard.money := 0;
          waterCard.totalmoney := 0;
          StrCopy(@waterCard.addtime,PChar('00000000000000'));
          waterCard.addcount := 0;
          waterCard.price1 := cpuWaterPrice1;
          waterCard.price2 := cpuWaterPrice2;
          waterCard.price3 := cpuWaterPrice3;
          st := ks_water_publishcard(4,@waterCard);
          //sti := ks_water_publishcard(hdWater,@waterCard);
          }
          setWaterPrice(WVWaterPrice,WVRWaterPrice,custType);
          st := pubSmlBag(cardno,custId,custType,cardEndDate,pCardID);
          KNG_beep;
          if (st<>0) then
            Context.GetDialogSystem.ShowMessage('水控钱包初始化失败，请重新初始化水控钱包！');
        end;
      end;
    end
    else
    begin
      getReturn('',WVReleaseCard);
      RzStatusPane1.Caption:='显示卡号['+showCardNo+'],卡号['+inttostr(cardNo)+']的卡发行成功，'+WVReleaseCard.FieldByName('返回信息').Data.AsString;
    end;
    //getFeeResult;
  finally
    cm.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('匿名卡发行', TfaqhAnonyCard);
end.
