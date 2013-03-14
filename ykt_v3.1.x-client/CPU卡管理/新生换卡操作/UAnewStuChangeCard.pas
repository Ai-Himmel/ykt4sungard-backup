unit UAnewStuChangeCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db,WaterDll, 
  RzDBGrid, RzStatus, RzPanel, Buttons, CardDll, UIncrementComboBox;
{
type
  TSMLBAGINFO = packed record
    cardno : Integer;                     //���׿���
    custno : Integer;                     //�ͻ���
    custtype : Integer;                   //�ͻ����
    expireddate : string;                 //��Ч��
    lockflag : Integer;                   //������־��00 ������FF����
    // Ǯ����Ϣ
    money : Integer;                    //�����
    totalmoney : Integer;               //��ֵ�ܽ��
    addtime : string;                   //��ֵʱ��
    addcount : Integer;                 //��ֵ����
    price1 : Integer;                   //ˮ��1
    price2 : Integer;                   //ˮ��2
    price3 : Integer;                   //ˮ��3
  end;
}  
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
    WVLabel4: TWVLabel;
    WVComboBox4: TWVComboBox;
    wvSmlBg: TWorkView;
    wvrSmlBg: TWVRequest;
    WVWaterPrice: TWorkView;
    WVRWaterPrice: TWVRequest;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnPrintClick(Sender: TObject);
    procedure btnReadCardQueryClick(Sender: TObject);
    procedure btnPatchCardClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure edtShowCardKeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
    //smlbgInfo : array of TSMLBAGINFO;
    procedure replaceNewCard(phyCardId:string;cardNo:Integer;operType:string);//������������Ϣ

    function recycleSmlbg(oldphyId:string;wv:TWorkView;wvr:TWVRequest):Integer;
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
  //SetLength(smlbgInfo,waterStrings.Count);
  
  edtEndDate.Text:=FormatDateTime('yyyymmdd',Date()+1461);
  //cbbPhyType.ItemIndex := 0;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
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
  rmoney:Integer;
  rTrade:Integer;
  rPatchNo:Integer;
  PCardId:string;
  cardNo:string;
  st:Integer;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowWarning('û�����ݣ��޷����д˲�����');
    Exit;
  end;  
  //������������Ϣ
  cm := nil;
  try
    cm:=TCM.Create();
    //�����СǮ��������СǮ�����ӵ���Ǯ����
    st := recycleSmlbg(PCardId,wvSmlBg,wvrSmlBg);
    if st<>0 then
      Exit;
      
    st := cm.card(PCardId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
      exit;
    end;
    //��������еĶ�ȡȨ��
    cm.clearallfieldreadmode;
    //����Ҫ��ȡ���ݵ�Ȩ��
    //setOperReadMode(cm);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(PATCH_NO);
    cm.setfieldreadmode(CARD_NO);
    if cm.readCard(PCardId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ������ԣ�');
      exit;
    end;
    try
      rmoney:=StrToInt(cm.getCardBalance);
      rTrade:=StrToInt(cm.getPayCardCnt);
      rPatchNo := StrToInt(cm.getPatchNo);
      cardNo:=cm.getCardNo;
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowWarning('���û���������Ϣʧ��--'+e.Message);
        Exit;
      end;
    end;
    
    //���ǰ�ȸ���̨�����������Ϣ��Ϣ�����ͳɹ������������Ϣ 847122
    WorkViewOK.FieldByName('��������').Data.SetString('S');
    WorkViewOK.FieldByName('ԭ����').Data.SetInteger(StrToInt((cardNo)));
    WorkViewOK.FieldByName('ԭ������').Data.SetString(PCardID);
    WorkViewOK.FieldByName('ԭ�����').Data.SetInteger(rmoney);
    WorkViewOK.FieldByName('ԭ�����״���').Data.SetInteger(rTrade);
    WorkViewOK.FieldByName('�������κ�').Data.SetInteger(rPatchNo);
    WorkViewOK.FieldByName('�¿�������').Data.SetString('');
    WorkViewOK.FieldByName('��ʾ����').Data.SetString('');
    WorkViewOK.FieldByName('��������').Data.SetString('');
    WorkViewOK.FieldByName('ҵ������').Data.SetString('');
    WorkViewOK.FieldByName('��ˮ��').Data.SetInteger(0);
    WorkViewOK.FieldByName('�ն˱��').Data.SetInteger(0);
    WVRequestOK.SendCommand;
    if WorkViewOK.FieldByName('������').Data.AsInteger<>0 then
    begin
      getReturn('��տ�ʧ��--',WorkViewOK);
      RzStatusPane1.Caption:=WorkViewOK.FieldByName('������Ϣ').Data.AsString;
      Exit;
    end;
    //���������ʱ����Ϣ������ɹ������Ϣ�͵���̨����̨����ոÿ���־д��
    st := cm.clearCard(WorkViewOK);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('�ɿ��������ʧ�ܣ�����ÿ��Ƿ����--'+inttostr(st));
      Exit;
    end
    else
    begin
      {
      //��ȡˮ�ؿ���Ϣ
      if waterStrings.Count>0 then
      begin
        //��СǮ����Ϣ
        st := mfcard(phyId);
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowMessage('СǮ��Ѱ��ʧ�ܣ����ܰ�СǮ�������¿�--'+inttostr(st));
          Exit;
        end;
        for i:=0 to waterStrings.Count-1 do
        begin
          try
            smlbgNo := StrToInt(waterStrings[i]);
          except
            smlbgNo := 0;
          end;
          preCommWaterPack(waterPack);
          st := ks_water_readmoney(smlbgNo,@waterpack);
          if st<>0 then
          begin
            Continue;
          end;
          smlbgInfo[smlbgNo].cardno := waterPack.cardno;                     //���׿���
          smlbgInfo[smlbgNo].custno := waterPack.custno;                     //�ͻ���
          smlbgInfo[smlbgNo].custtype := waterPack.custtype;                 //�ͻ����
          smlbgInfo[smlbgNo].expireddate := waterPack.expireddate;           //��Ч��
          smlbgInfo[smlbgNo].lockflag := waterPack.lockflag;                 //������־��00 ������FF����
          smlbgInfo[smlbgNo].money := waterPack.money;                       //�����
          smlbgInfo[smlbgNo].totalmoney := waterPack.totalmoney;             //��ֵ�ܽ��
          smlbgInfo[smlbgNo].addtime := waterPack.addtime;                   //��ֵʱ��
          smlbgInfo[smlbgNo].addcount := waterPack.addcount;                 //��ֵ����
          smlbgInfo[smlbgNo].price1 := waterPack.price1;                     //ˮ��1
          smlbgInfo[smlbgNo].price2 :=waterPack.price2;                      //ˮ��2
          smlbgInfo[smlbgNo].price3 :=waterPack.price3;                      //ˮ��3

          st := ks_water_recyclecard(smlbgNo);
          if st<>0 then
            Context.GetDialogSystem.ShowMessage('���СǮ��ʧ�ܣ��ÿ�����ճ�ʼ����ʹ�ã�');
        end;
      end;
      }
      cm.beep;
      Context.GetDialogSystem.ShowMessage('�ɿ�����������ɹ������Ȱ�Ҫ�����Ŀ����úã�');
      //��ʼ�ѿ���Ϣд���¿���ȥ
      replaceNewCard(PCardID,StrToInt(cardNo),'C');
    end;
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhnewStuChangeCard.btnReadCardQueryClick(Sender: TObject);
begin
  edtCardNo.Text:= readCardOneInfo(CARD_NO);
  btnQueryClick(Sender);
end;

{-------------------------------------------------------------------------------
  ������:    TfaqhnewStuChangeCard.replaceNewCard������������Ϣ
  ����:      Administrator
  ����:      2005.07.29
  ����:      ��
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
procedure TfaqhnewStuChangeCard.replaceNewCard(phyCardId:string;cardNo:Integer;operType:string);
var
  cm:TCM;
  newphyCardNo:string;
  inShowCardNo:string;
  tradeCardNo:Integer;      //���׿���
  showCardNo:string;        //��ʾ����
  //tradeNum:Integer;         //���״���
  cardEndDate:string;       //��ʹ�ý�������
  limitType:Integer;        //��ʹ��Ȩ��
  custType:Integer;         //�ͻ����
  custName:string;          //�ͻ�����
  cardID:string;            //���֤��
  deptNo:string;            //���Ŵ���
  sex:string;               //�Ա�
  stuempNo:string;          //ѧ����
  cardBalance:Integer;      //�����
  cardPWD:string;           //������
  sOperDate:string;         //��������
  stationId:Integer;        //�ն˱��
  backTradeID:Integer;      //��̨������ˮ��
  maxPerCount:Integer;      //�����޶�
  maxPerDay:Integer;        //���޶�
  cardType:string;         //������
  cardPhyType:integer;
  cardSelfType:integer;
  custId:string;
  relCardSign:string;
  certType:string;
  re:Integer;
  ResInt:Integer;
  patchNo:Integer;
  tradeTime:string;
  tmpPhyId:string;
  TOF: Integer;
  tp:TTRANSPACK;
  st:Integer;
  cardVer:string;
begin
  if preReadCard=False then
    Exit;
  re := -1;
  ResInt := -1;
  tof := -1;
  stationId := 0;
  backTradeID := 0;
  tradeCardNo := 0;
  limitType := 0;
  //����Ƿ��п����޿����˳�
  if (StrToInt(strToZero(readCardOneInfo(CARD_NO)))>0) and (StrToInt(strToZero(readCardOneInfo(BLACK_CARD_SIGN)))=0) then
  begin
      Context.GetDialogSystem.ShowMessage('�ÿ��Ѿ���ʹ�ã��ȳ����ÿ��Ļ���������һ���¿������²�����');
      Exit;
  end;
  cm := nil;
  try
    cm := TCM.Create();
    st := cm.card(newphyCardNo);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
      exit;
    end;
    //��������еĶ�ȡȨ��
    cm.clearallfieldreadmode;
    //����Ҫ��ȡ���ݵ�Ȩ��
    //setOperReadMode(cm);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(SHOW_CARDNO);
    if cm.readCard(newphyCardNo)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ������ԣ�');
      Exit;
    end;
    if (cm.getCardBalance='') or (cm.getCardBalance<>'0') then
    begin
      context.GetDialogSystem.ShowMessage('�ÿ���Ϊ�㣬�Ȼ��ոÿ���');
      exit;
    end;
    
    //ȡ���ڲ�����
    try
      cardSelfType := ks_cardtype();
    except
      cardSelfType := 0;
    end;
    try
      //����������
      cardPhyType := 0;//StrToInt(Copy(cbbPhyType.Text,1,Pos('-',cbbPhyType.Text)-1));
    except
      cardPhyType := 0;
    end;
    inShowCardNo := cm.getShowCardNo;
    //���¿��������ż������Ϣ�����̨
    WorkViewOK.FieldByName('��������').Data.SetString(operType);
    WorkViewOK.FieldByName('ԭ����').Data.SetInteger(cardNo);
    WorkViewOK.FieldByName('ԭ������').Data.SetString(phyCardId);
    WorkViewOK.FieldByName('ԭ�����').Data.SetInteger(0);
    WorkViewOK.FieldByName('ԭ�����״���').Data.SetInteger(0);
    WorkViewOK.FieldByName('�������κ�').Data.SetInteger(0);
    WorkViewOK.FieldByName('�¿�������').Data.SetString(newphyCardNo);
    WorkViewOK.FieldByName('��ʾ����').Data.SetString(inShowCardNo);
    WorkViewOK.FieldByName('��������').Data.SetString(Trim(edtEndDate.Text));
    WorkViewOK.FieldByName('����������').Data.SetInteger(cardPhyType);
    WorkViewOK.FieldByName('���ڲ�����').Data.SetInteger(cardSelfType);
    WorkViewOK.FieldByName('ҵ������').Data.SetString('');
    WorkViewOK.FieldByName('��ˮ��').Data.SetInteger(0);
    WorkViewOK.FieldByName('�ն˱��').Data.SetInteger(0);
    try
      WVRequestOK.SendCommand;
    except
      on ex:Exception do
      begin
        Context.GetDialogSystem.ShowMessage(ex.Message);
        exit;
      end;
    end;
    if WorkViewOK.FieldByName('������').Data.AsInteger=0 then
    begin
      //��ʼ�����¿���ʧ�����ͳ�������
      try
        tradeCardNo:=WorkViewOK.fieldbyname('����').Data.AsInteger;
        showCardNo:=WorkViewOK.fieldbyname('��ʾ����').Data.AsString;
        cardEndDate:=WorkViewOK.fieldbyname('��������').Data.AsString;
        limitType:=WorkViewOK.fieldbyname('�շ����').Data.AsInteger;
        custType:=WorkViewOK.fieldbyname('�ͻ����').Data.AsInteger;
        custName:=WorkViewOK.fieldbyname('�ͻ�����').Data.AsString;
        cardID:=WorkViewOK.fieldbyname('֤������').Data.AsString;
        deptNo:=WorkViewOK.fieldbyname('���Ŵ���').Data.AsString;
        sex:=WorkViewOK.fieldbyname('�Ա�').Data.AsString;
        stuempNo:=WorkViewOK.fieldbyname('ѧ����').Data.AsString;
        cardBalance:=WorkViewOK.fieldbyname('����ֵ').Data.AsInteger;
        cardPWD:=WorkViewOK.fieldbyname('������').Data.AsString;
        backTradeID:=WorkViewOK.fieldbyname('��ˮ��').Data.AsInteger;
        sOperDate := WorkViewOK.fieldbyname('ҵ������').Data.AsString;
        tradeTime := WorkViewOK.fieldbyname('ҵ��ʱ��').Data.AsString;
        stationId := WorkViewOK.fieldbyname('�ն˱��').Data.AsInteger;
        //tradeNum := WorkViewOK.fieldbyname('���״���').Data.AsInteger;
        patchNo := WorkViewOK.fieldbyname('�������κ�').Data.AsInteger;
        certType := WorkViewOK.fieldbyname('֤������').Data.AsString;
        relCardSign := WorkViewOK.fieldbyname('���з���ʶ').Data.AsString;
        cardType := WorkViewOK.fieldbyname('������').Data.AsString;
        custId := WorkViewOK.fieldbyname('�ͻ���').Data.AsString;
        cardVer := WorkViewOK.fieldbyname('�汾��').Data.AsString;
      except
        on ex:Exception do
        begin
          Context.GetDialogSystem.ShowMessage('��̨������������--'+ex.Message);
          Exit;
        end;
      end;
      //��������еĶ�ȡȨ��
      cm.clearallfieldreadmode;
      //����Ҫ��ȡ���ݵ�Ȩ��
      //setOperReadMode(cm);
      cm.setCardNo(IntToStr(tradeCardNo));
      cm.setShowCardNo(showCardNo);
      cm.setDeadLineDate(cardEndDate);
      cm.setCardLimitType(IntToStr(limitType));
      cm.setCustType(IntToStr(custType));
      cm.setDeptNo(deptNo);
      cm.setCustName(custName);
      //֤������--û��
      cm.setCertType(certType);
      cm.setCertNo(cardID);
      cm.setCustSex(sex);
      cm.setStuempNo(stuempNo);
      //��������ʶ---û��
      cm.setReaCardSign(relCardSign);
      cm.setCardType(cardType);
      cm.setCustNo(custId);
      cm.setCardPwd(cardPWD);
      cm.setPatchNo(IntToStr(patchNo));
      cm.setBlackCardSign(IntToStr(NORMAL_CARD));
      cm.setBlackVer(cardVer);
      //���õ��������޶���������޶�
      if maxper=1 then
      begin
        maxPerCount := WorkViewOK.fieldbyname('�����޶�').Data.AsInteger;
        maxPerDay := WorkViewOK.fieldbyname('���޶�').Data.AsInteger;
        cm.setMaxPerCount(IntToStr(maxPerCount));
        cm.setMaxPerDay(IntToStr(maxPerDay));
      end;
      re := cm.writeData(newphyCardNo);
      //д���ɹ����жϿ����Ƿ�д��
      if re=0 then
      begin
        try
          ResInt := StrToInt(readCardOneInfo(CARD_NO));
        except
          ResInt := 0;
        end;
      end;
      if ResInt=0 then
      begin
        if Application.MessageBox(PChar('д��ʧ�ܣ���ʹ��ͬһ�ſ�����ȷ���õ���д���ϣ���Ҫ����һ����'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
          Exit;
        tmpPhyId := readCardOneInfo(CARD_SERI_NO);
        if tmpPhyId='' then
        begin
          Context.GetDialogSystem.ShowMessage('����������ʧ�ܣ���Ѹÿ��ȳ���������Ȼ���������������ף�');
          Exit;
        end;
        if tmpPhyId<>newphyCardNo then
        begin
          Context.GetDialogSystem.ShowMessage('�͸ղŷ��õĲ���ͬһ�ſ�����Ѹÿ��ȳ���������Ȼ���������������ף�');
          Exit;
        end;
        //����дһ�ο�
        re := cm.writeData(newphyCardNo);
      end;
      //д���ɹ�����ʼ���ÿ����
      if re = 0 then
      begin
        //preSetMoney(tp);
        ZeroMemory(@tp,SizeOf(tp));
        //�ն˽������к�
        tp.TermSeqno := 1;
        //�ն˱��
        StrCopy(@tp.Termno,PChar(scSiteNo));
        //���׿���
        tp.CardNo := tradeCardNo;
        //������
        StrCopy(@tp.CardPhyID,PChar(newphyCardNo));
        //��������
        StrCopy(@tp.TransDate,PChar(sOperDate));
        //����ʱ��
        StrCopy(@tp.TransTime,PChar(tradeTime));
        //���׺���
        tp.AftBalance :=  cardBalance;
        //����ǰ���
        tp.BefBalance := 0;
        //����ǰ��ֵ����
        tp.DptCardCnt := 0;
        //����ǰ���Ѵ���
        tp.PayCardCnt := 0;
        //����ǰ��������
        tp.SubsidyNo := 0;
        tof := setCardBal(tp,cm,newphyCardNo);//ks_setcardbal(@tp);
      end;
    end;
  finally
    if ((re = 0) and (tof=0)) then
    begin
      if waterStrings.Count>0 then
      begin
        setWaterPrice(WVWaterPrice,WVRWaterPrice,limitType);

        pubSmlBag(tradeCardNo,StrToInt(custId),limitType,cardEndDate,newphyCardNo);
      end;
      
      cm.beep;
      if operType='D' then
        Context.GetDialogSystem.ShowMessage('�ÿ��Ѿ����������ɹ�  '+WorkViewOK.FieldByName('������Ϣ').Data.AsString)
      else
        Context.GetDialogSystem.ShowMessage('�ÿ��Ѿ������ɹ�  '+WorkViewOK.FieldByName('������Ϣ').Data.AsString);
      RzStatusPane1.Caption:='��ʾ����Ϊ��'+showCardNo+'�Ŀ������ɹ�'

    end
    else
    begin
      WorkViewOK.FieldByName('��������').Data.SetString('V');
      WorkViewOK.FieldByName('ԭ����').Data.SetInteger(0);
      WorkViewOK.FieldByName('ԭ������').Data.SetString('');
      WorkViewOK.FieldByName('ԭ�����').Data.SetInteger(0);
      WorkViewOK.FieldByName('ԭ�����״���').Data.SetInteger(0);
      WorkViewOK.FieldByName('�¿�������').Data.SetString('');
      WorkViewOK.FieldByName('��ʾ����').Data.SetString('');
      WorkViewOK.FieldByName('��������').Data.SetString('');
      WorkViewOK.FieldByName('ҵ������').Data.SetString(sOperDate);
      WorkViewOK.FieldByName('��ˮ��').Data.SetInteger(backTradeID);
      WorkViewOK.FieldByName('�ն˱��').Data.SetInteger(stationId);
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
    tmpdata:=WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet;
    phyCardId := tmpdata.fieldbyname('sstation1').AsString;
    cardNo := tmpdata.fieldbyname('lvol0').AsInteger;
  except
    on ex:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣ��'+ex.Message+' ����û�в�ѯ���');
      Exit;
    end;
  end;
  if preReadCard=False then
  Exit;
  //ȡ������
  tmpPhyId := readCardOneInfo(CARD_SERI_NO);
  if tmpPhyId='' then
  begin
    Context.GetDialogSystem.ShowMessage('�������к�ʧ�ܣ������°ѿ����õ���д���ϣ�');
    exit;
  end;

  if tmpPhyId<>phyCardId then
  begin
    Context.GetDialogSystem.ShowMessage('Ҫ�����Ŀ��Ͳ�ѯ���Ŀ�����ͬһ�ſ���');
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

function TfaqhnewStuChangeCard.recycleSmlbg(oldphyId: string; wv: TWorkView;wvr: TWVRequest): Integer;
var
  cm:TCM;
  st:Integer;
  phyId,mfPhyid:string;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
  //CardState:string;
  waterPack:TWATERCOMMPACK;
  cardNo:Integer;
  payCnt,dptCnt,balance:Integer;
  rCardNo:Integer;
  OutMoney: Integer;
  rTradeDate:string;
  rTradeTime:string;
  tp:TTRANSPACK;
  i:Integer;
  smlBagNo:Integer;
begin
  dptCnt:=0;
  payCnt := 0;
  cardNo := 0;
  balance := 0;
  if preReadCard=False then
    Exit;
  cm := nil;
  try
    cm := TCM.Create;
    if waterStrings.Count>0 then 
    begin
      for i:=0 to waterStrings.Count-1 do
      begin
        try
          smlBagNo := StrToInt(waterStrings[i])
        except
          smlBagNo := 0;
        end;
        
        st := cm.card(phyId);
        if st<>0 then
        begin
          context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���Ȼ���ٲ�����');
          result := -1;
          exit;
        end;
        //��������еĶ�ȡȨ��
        cm.clearallfieldreadmode;
        //����Ҫ��ȡ���ݵ�Ȩ��
        //setOperReadMode(cm);
        cm.setfieldreadmode(CARD_BALANCE);
        cm.setfieldreadmode(DPT_CARD_CNT);
        cm.setfieldreadmode(CARD_NO);
        cm.setfieldreadmode(PAY_CARD_CNT);
        if cm.readCard(phyId)<>0 then
        begin
          Context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ������ԣ�');
          Result := -2;
          Exit;
        end;
        try
          dptCnt:=StrToInt(cm.getDptCardCnt);
          payCnt := StrToInt(cm.getPayCardCnt);
          cardNo := StrToInt(cm.getCardNo);
          balance := StrToInt(cm.getCardBalance);
        except
        end;
        wv.FieldByName('�ն˺�').Data.SetInteger(0);
        wv.FieldByName('���޿���־').Data.SetInteger(1);
        wv.FieldByName('������').Data.SetString(phyId);
        wv.FieldByName('����').Data.SetInteger(cardNo);
        wv.FieldByName('��Ǯ����ֵ����').Data.SetInteger(payCnt);
        wv.FieldByName('��Ǯ�����Ѵ���').Data.SetInteger(dptCnt);
        wv.FieldByName('��Ǯ�����').Data.SetInteger(balance);
        wv.FieldByName('Ǯ����').Data.SetInteger(smlBagNo);
        //��СǮ����Ϣ
        st := mfcard(mfPhyid);
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowMessage('ˮ��Ǯ��Ѱ��ʧ��--'+inttostr(st));
          Result := -3;
          Exit;
        end;
        if mfPhyid<>phyId then
        begin
          Context.GetDialogSystem.ShowMessage('��ʹ��ͬһ�ſ����в���--'+inttostr(st));
          Result := -6;
          Exit;
        end;
        preCommWaterPack(waterPack);
        st := ks_water_readmoney(smlBagNo,@waterpack);
        if st<>0 then
        begin
          reSt := ks_geterrmsg(PChar(@reErrMsg));
          Context.GetDialogSystem.ShowMessage('��ȡˮ��Ǯ�����ʧ��-'+reSt);
          Result := -4;
          Exit;
        end;
        if waterPack.money=0 then
          Continue;
        wv.FieldByName('СǮ�����Ѵ���').Data.SetInteger(0);
        wv.FieldByName('СǮ�����').Data.SetInteger(waterPack.money);
        wvr.SendCommand;
        
        if wv.FieldByName('������').Data.AsInteger = 0 then
        begin
          //�����ɹ������ô�Ǯ�����
          OutMoney := wv.FieldByName('r��Ǯ�����').Data.AsInteger;
          rCardNo := wv.FieldByName('r����').Data.AsInteger;
          rTradeDate := wv.FieldByName('r��������').Data.AsString;
          rtradetime := wv.FieldByName('r����ʱ��').Data.AsString;
          ZeroMemory(@tp,SizeOf(tp));
          //�ն˽������к�
          tp.TermSeqno := 1;
          //�ն˱��
          StrCopy(@tp.Termno,PChar(scSiteNo));
          //���׿���
          tp.CardNo := rCardNo;
          //������
          StrCopy(@tp.CardPhyID,PChar(phyId));
          //��������
          StrCopy(@tp.TransDate,PChar(rTradeDate));
          //����ʱ��
          StrCopy(@tp.TransTime,PChar(rtradeTime));
          //����ǰ���
          tp.BefBalance := balance;
          //���׺���
          tp.AftBalance := OutMoney;
          //����ǰ��ֵ����
          tp.DptCardCnt := dptCnt;
          //����ǰ���Ѵ���
          tp.PayCardCnt := payCnt;
          //����ǰ��������
          //tp.SubsidyNo := subsidyNo;
          st := ks_water_recyclecard(smlBagNo);
          if st<>0 then
            WriteLog('СǮ��['+inttostr(smlBagNo)+']����ʧ��-'+inttostr(st))
          else
          begin
            st := cm.card(phyId);
            if st<>0 then
            begin
              context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ����ȵ�������Ȼ����������');
              result := -7;
              exit;
            end;
            //�޸����ý�ʽ
            st := setCardBal(tp,cm,phyId);
            if st<>0 then
            begin

            end;
            //cm.beep;
          end;
        end
        else
        begin
          Context.GetDialogSystem.ShowMessage(wv.FieldByName('������Ϣ').Data.AsString);
          Result := -5;
        end;
      end;
    end;
    Result := 0;
  finally
    cm.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('������������',TfaqhnewStuChangeCard);

end.