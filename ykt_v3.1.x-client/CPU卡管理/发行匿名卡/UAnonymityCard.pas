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
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaqhAnonyCard.edtDateExit(Sender: TObject);
begin
  inherited;
  if CheckInputDateFormat(edtDate.Text)=false then
  begin
    Context.GetDialogSystem.ShowMessage('����������������������');
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
  WVFeeQuery.FieldByName('�շ����').Data.SetInteger(feeType);
  WVFeeQuery.FieldByName('������').Data.SetInteger(cardType);
  WVFeeQuery.FieldByName('�ͻ���').Data.SetInteger(0);
  WVFeeQuery.FieldByName('���ܺ�').Data.SetInteger(846301);
  WVFeeQuery.FieldByName('�Ƿ񲻼�����').Data.setstring('1');
  WVRFeeQuery.SendCommand;
  if WVFeeQuery.FieldByName('������').Data.AsInteger=0 then
  begin
    sReturnInfo := WVFeeQuery.fieldbyname('�շ���Ϣ').Data.AsString;
    edtDate.Text := WVFeeQuery.Fieldbyname('����Ч��').Data.AsString;
    fMoney := WVFeeQuery.fieldbyname('�ܷ���').Data.AsFloat;
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
    Context.GetDialogSystem.ShowMessage('��ѡ���ֵ����,Ȼ���ٽ��з�����');
    cbbType.SetFocus;
    Exit;
  end;
  if Trim(edtDate.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('�����뿨��Ч�ڣ�');
    Exit;
  end;
  if CheckInputDateFormat(edtDate.Text)=False then
  begin
    Context.GetDialogSystem.ShowMessage('����Ч�����벻��ȷ����ʽ��yyyymmdd');
    edtDate.SetFocus;
    Exit;
  end;
  if relCardJudge=False then
    Exit;
  {
  if readCardOneInfo(APP_TYPE)='0' then
  begin
    context.GetDialogSystem.ShowMessage('�ÿ�û�г�ʼ�������ȳ�ʼ����');
    exit;
  end;
  if readCardOneInfo(CARD_BALANCE)<>'0' then
  begin
    context.GetDialogSystem.ShowMessage('�ÿ���Ϊ�㣬�Ȼ��ոÿ���');
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
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
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
      context.GetDialogSystem.ShowMessage('�ÿ�û�г�ʼ�������ȳ�ʼ����');
      exit;
    end
    else
    begin
      {
      if (cm.getAppType='') or (cm.getAppType='0') then
      begin
        context.GetDialogSystem.ShowMessage('�ÿ���ʼ�������ȷ�������³�ʼ��-'+cm.getAppType);
        exit;
      end;
      }
      if (cm.getCardBalance='') or (cm.getCardBalance<>'0') then
      begin
        context.GetDialogSystem.ShowMessage('�ÿ���Ϊ�㣬�Ȼ��ոÿ���');
        exit;
      end;
      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      //ȡ����ʾ����
      showCardNo:=cm.getShowCardNo;
    end;
    //ȡ���ڲ�����
    try
      cardSelfType := ks_cardtype();
    except
      cardSelfType := 0;
    end;
    //ȡ����ʾ����
    //showCardNo:=readCardOneInfo(SHOW_CARDNO);
    //��������
    cardType := StrToInt(Copy(cbbPhyType.Text,1,Pos('-',cbbPhyType.Text)-1));
    try
      //�շѷ�ʽ
      feeType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
      //����������
      cardPhyType := 0;//StrToInt(Copy(cbbPhyType.Text,1,Pos('-',cbbPhyType.Text)-1));
    except
      feeType :='0';
      cardPhyType := 0;
    end;
    //����Ա
    operCode := Context.ParamData(svOperatorNoName).AsString;
    WVReleaseCard.FieldByName('����Ա').Data.SetString(operCode);
    WVReleaseCard.FieldByName('��ʾ����').Data.SetString(showCardNo);        //
    WVReleaseCard.FieldByName('������').Data.SetString(pCardID);           //
    WVReleaseCard.FieldByName('�շѷ�ʽ').Data.SetInteger(StrToInt(feeType));
    WVReleaseCard.FieldByName('Ʊ�ݺ���').Data.SetString(edtTicketNo.Text);
    WVReleaseCard.FieldByName('��������').Data.SetString(edtDate.Text);
    WVReleaseCard.FieldByName('������').Data.SetInteger(cardType);
    WVReleaseCard.FieldByName('����������').Data.SetInteger(cardPhyType);
    WVReleaseCard.FieldByName('���ڲ�����').Data.SetInteger(cardSelfType);
    WVReleaseCard.FieldByName('�ͻ���').Data.SetInteger(0);
    WVReleaseCard.FieldByName('�շѽ��').Data.SetFloat(StrToFloat(edtMoney.Text));
    WVReleaseCard.FieldByName('�Ƿ񲻼�����').Data.SetString('1');
    WVReleaseCard.FieldByName('��ֵ����').Data.SetInteger(dptCnt);
    WVReleaseCard.FieldByName('���Ѵ���').Data.SetInteger(payCnt);
    WVRReleaseCard.SendCommand;
    if (WVReleaseCard.FieldByName('������').Data.AsInteger = 0) then
    begin
      if waterStrings.Count = 0 then
      begin
        RzStatusPane1.Caption:=pubCardNew(WVReleaseCard,WVRelCardOk,WVRRelCardOk,pCardID,1,reCode);
        if reCode = 0 then
          kng_beep;
      end
      else
      begin
        //��ʼ��ˮ�ؿ�
        RzStatusPane1.Caption:=pubCardNew(WVReleaseCard,WVRelCardOk,WVRRelCardOk,pCardID,0,reCode);
        cardNo:=WVReleaseCard.fieldbyname('����').Data.AsInteger;

        if reCode >= 0 then
        begin
          cardEndDate:=WVReleaseCard.fieldbyname('��������').Data.AsString;
          custType := WVReleaseCard.fieldbyname('�շ����').Data.AsInteger;
          custId := WVReleaseCard.fieldbyname('�ͻ���').Data.AsInteger;
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
            Context.GetDialogSystem.ShowMessage('ˮ��Ǯ����ʼ��ʧ�ܣ������³�ʼ��ˮ��Ǯ����');
        end;
      end;
    end
    else
    begin
      getReturn('',WVReleaseCard);
      RzStatusPane1.Caption:='��ʾ����['+showCardNo+'],����['+inttostr(cardNo)+']�Ŀ����гɹ���'+WVReleaseCard.FieldByName('������Ϣ').Data.AsString;
    end;
    //getFeeResult;
  finally
    cm.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('����������', TfaqhAnonyCard);
end.
