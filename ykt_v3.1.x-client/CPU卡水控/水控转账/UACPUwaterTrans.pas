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
    cardno : Integer;                   //���׿���
    custno : Integer;                   //�ͻ���
    custtype : Integer;                 //�ͻ����
    expireddate : string;  //��Ч��
    lockflag : Integer;                 //������־��00 ������FF����
    //Ǯ����Ϣ
    money : Integer;                    //�����
    totalmoney : Integer;               //��ֵ�ܽ��
    addtime : string;                   //��ֵʱ��
    addcount : Integer;                 //��ֵ����
    {
    nprice1 : Integer;                   //ˮ��1
    nprice2 : Integer;                   //ˮ��2
    nprice3 : Integer;                   //ˮ��3
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
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
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
      Context.GetDialogSystem.ShowMessage('ˮ�����ʹ���,������ѡ��');
      Exit;
    end;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ��ȡ��ˮ������');
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
      Context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
      exit;
    end;
    //��������еĶ�ȡȨ��
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(CUST_NAME);
    cm.setfieldreadmode(STUEMP_NO);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(CARD_SERI_NO);
    //����Ҫ��ȡ���ݵ�Ȩ��
    //setOperReadMode(cm);
    //cm.card(phyId);
    st := cm.readCard(phyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ����Ϣʧ�ܣ���źÿ������¶�ȡ-'+inttostr(st));
      Exit;
    end;
    edtPhyID.Text := cm.getCardSeriNo;
    edtCardNo.Text := cm.getCardNo;
    edtName.Text := cm.getCustName;
    edtStuempNo.Text := cm.getStuempNo;
    edtMoney.Text := format('%f', [strtofloat(cm.getCardBalance) / 100.0]);
    edtAfterMoney.Text := '';
    edtAfterSmlMoney.Text := '';

    //��СǮ����Ϣ
    st := mfcard(phyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('ˮ��Ǯ��Ѱ��ʧ��--'+inttostr(st));
      Exit;
    end;
    preCommWaterPack(waterPack);
    st := ks_water_readmoney(smlbgNo,@waterpack);
    reSt := ks_geterrmsg(PChar(@reErrMsg));
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡСǮ��ʧ��,��Ǯ���Ѿ�����-'+reSt+inttostr(st));
      Exit;
    end;
    edtsmlMoney.Text := Format('%f',[waterPack.money/100.0]);
    smallCnt := waterPack.addcount;
    cardno := waterPack.cardno;                     //���׿���
    custno := waterPack.custno;                     //�ͻ���
    custtype := waterPack.custtype;                 //�ͻ����
    expireddate := waterPack.expireddate;           //��Ч��
    edtExpireDate.Text := expireddate;
    lockflag := waterPack.lockflag;                 //������־��00 ������FF����
    // Ǯ����Ϣ
    money := waterPack.money;                       //�����
    totalmoney := waterPack.totalmoney;             //��ֵ�ܽ��
    addtime := waterPack.addtime;                   //��ֵʱ��
    addcount := waterPack.addcount;                 //��ֵ����
    {
    nprice1 := waterPack.price1;                     //ˮ��1
    nprice2 := waterPack.price2;                     //ˮ��2
    nprice3 := waterPack.price3;                     //ˮ��3
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
    Context.GetDialogSystem.ShowMessage('��������Ч��ת�˽�');
    Exit;
  end;
  try
    smlbgNo := StrToInt(Copy(cbbSmlNo.Text,1,Pos('-',cbbSmlNo.Text)-1));
    if (smlbgNo<=0) then
    begin
      Context.GetDialogSystem.ShowMessage('Ǯ���Ŵ���,������ѡ��');
      Exit;
    end;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Exit;
    end;
  end;
  //��ȡ���ײο���
  WorkView.FieldByName('�ն˺�').Data.SetInteger(StrToInt(scSiteNo));
  WorkView.FieldByName('ʱ���').Data.SetString(FormatDateTime('yyyymmddhhmmss',Now));
  MainRequest.SendCommand;
  if WorkView.FieldByName('������').Data.AsInteger<>0 then
  begin
    getReturn('',WorkView);
    Exit;
  end;
  tradeCode := WorkView.fieldbyname('���ײο���').Data.AsString;
  mac := WorkView.fieldbyname('�����').Data.AsString;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
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
      Context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ������ԣ�');
      Exit;
    end;
    if cm.getBlackCardSign<>'0' then
    begin
      Context.GetDialogSystem.ShowMessage('�ÿ���������״̬�Ŀ�������ת�ˣ��뵽������Ϣ�ж�ȡ��״̬��');
      Exit;
    end;
    if phyId <> edtPhyId.Text then
    begin
      Context.GetDialogSystem.ShowMessage('��ʹ��ͬһ�ſ����г�ֵ��');
      btnReadCard.SetFocus;
      btnTran.Enabled := False;
      Exit;
    end;
    dptCnt:=StrToInt(cm.getDptCardCnt);
    payCnt := StrToInt(cm.getPayCardCnt);
    subsidyNo := StrToInt(cm.getPatchNo);
    balance := StrToInt(cm.getCardBalance);
    feeType := StrToInt(cm.getCardLimitType);
    WorkView1.FieldByName('��������').Data.SetString(phyId);
    WorkView1.FieldByName('���ײο���').Data.SetString(tradeCode);
    WorkView1.FieldByName('�����').Data.SetString(mac);
    WorkView1.FieldByName('����').Data.SetInteger(StrToInt(cm.getCardNo));
    WorkView1.FieldByName('�����').Data.SetInteger(balance);
    WorkView1.FieldByName('���״���').Data.SetInteger(payCnt);
    WorkView1.FieldByName('СǮ�����').Data.SetInteger(StrToInt(FloatToStr(StrToFloat(edtsmlMoney.Text)*100)));
    WorkView1.FieldByName('ת�˽��').Data.SetInteger(addMoney);
    WorkView1.FieldByName('Ǯ����').Data.SetInteger(smlbgNo);
    WorkView1.FieldByName('֧������').Data.SetInteger(1191);
    WVRequest1.SendCommand;
    if workview1.FieldByName('������').Data.AsInteger<>0 then
    begin
      getReturn('',WorkView1);
      Exit;
    end;
    setWaterPrice(WVWaterPrice,WVRWaterPrice,feeType);
    
    accdate := WorkView1.fieldbyname('��������').Data.AsString;
    accTime := WorkView1.fieldbyname('����ʱ��').Data.AsString;
    outMoney := WorkView1.fieldbyname('����ֵ').Data.AsInteger;
    smlMoney := WorkView1.fieldbyname('СǮ�����').Data.AsInteger;
    ZeroMemory(@tp,SizeOf(tp));
    //�Ӵ�Ǯ���ۿ�
    //�ն˽������к�
    tp.TermSeqno := 1;
    //�ն˱��
    StrCopy(@tp.Termno,PChar(scSiteNo));
    //���׿���
    tp.CardNo := StrToInt(edtCardNo.Text);
    //������
    StrCopy(@tp.CardPhyID,PChar(phyId));
    //��������
    StrCopy(@tp.TransDate,PChar(accdate));
    //����ʱ��
    StrCopy(@tp.TransTime,PChar(accTime));
    //����ǰ���
    tp.BefBalance := balance;
    //���׺���
    tp.AftBalance := outMoney;
    //����ǰ��ֵ����
    tp.DptCardCnt := dptCnt;
    //����ǰ���Ѵ���
    tp.PayCardCnt := payCnt;
    //����ǰ��������
    tp.SubsidyNo := subsidyNo;

    st := setCardBal(tp,cm,phyId);//ks_setcardbal(@tp);
    if st = 0 then
    begin
      //�ۿ�ɹ���ʼдˮ����� ,д֮ǰҪ��Ѱ��
      //��СǮ����Ϣ
      st := mfcard(smlPhyId);
      if st<>0 then
      begin
        Context.GetDialogSystem.ShowMessage('ˮ��Ǯ��Ѱ��ʧ��--'+inttostr(st));
        Exit;
      end;
      //����СǮ���ṹ��
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
        Context.GetDialogSystem.ShowMessage(workview1.FieldByName('������Ϣ').Data.AsString);
        rzstspnStat.Caption:= workview1.FieldByName('������Ϣ').Data.AsString;
      end
      else
        Context.GetDialogSystem.ShowMessage('дˮ��Ǯ��ʧ�ܣ��뵽������������ý���--'+inttostr(st));      
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
  TUIStdClassFactory.Create('ˮ��Ǯ��ת��',TfaqhwaterTrans_cqcsgl);

end.