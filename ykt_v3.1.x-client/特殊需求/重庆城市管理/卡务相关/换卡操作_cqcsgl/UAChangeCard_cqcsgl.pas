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
    procedure replaceNewCard(phyCardId:string;cardNo:Integer;operType:string);//������������Ϣ
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
  //������Ϣ
  rmoney:Integer;
  rTrade:Integer;
  rPatchNo:Integer;
  PCardId:string;
  smlPhyId:string;

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
    //��������еĶ�ȡȨ��
    cm.clearallfieldreadmode;
    //����Ҫ��ȡ���ݵ�Ȩ��
    setOperReadMode(cm);
    if cm.readCard<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ������ԣ�');
      exit;
    end;
    //ȡ������
    PCardId := cm.getCardSeriNo;
    if PCardId='' then
    begin
      Context.GetDialogSystem.ShowMessage('�������к�ʧ�ܣ�');
      exit;
    end;
    try
      rmoney:=StrToInt(cm.getCardBalance);
      rTrade:=StrToInt(cm.getCardCnt);
      rPatchNo := StrToInt(cm.getPatchNo);
    except
      Context.GetDialogSystem.ShowWarning('���û���������Ϣʧ�ܣ�');
      Exit;
    end;
    //�Ͽ��Ŀ���
    cardNo:=cm.getCardNo;

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
      mfcard(smlPhyId);
      st := ks_sr_setmoeny(0,1);
      cm.beep;
      Context.GetDialogSystem.ShowMessage('�ɿ�����������ɹ������Ȱ�Ҫ�����Ŀ����úã�');

      //��ʼ�ѿ���Ϣд���¿���ȥ
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
  tradeNum:Integer;         //���״���
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
  //����Ƿ��п����޿����˳�
  if (StrToInt(strToZero(readCardOneInfo(CARD_NO)))>0) and (StrToInt(strToZero(readCardOneInfo(BLACK_CARD_SIGN)))=0) then
  begin
      Context.GetDialogSystem.ShowMessage('�ÿ��Ѿ���ʹ�ã��ȳ����ÿ��Ļ���������һ���¿������²�����');
      Exit;
  end;
  cm := nil;
  try
    cm := TCM.Create();
    //��������еĶ�ȡȨ��
    cm.clearallfieldreadmode;
    //����Ҫ��ȡ���ݵ�Ȩ��
    setOperReadMode(cm);
    if cm.readCard<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ������ԣ�');
      Exit;
    end;
    newphyCardNo := cm.getCardSeriNo;
    if newphyCardNo='' then
    begin
      Context.GetDialogSystem.ShowMessage('�������к�ʧ�ܣ����ȳ���������Ȼ��׼�����¿����²�����');
      Exit;
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
        //dutyNo:='';
        cardID:=WorkViewOK.fieldbyname('֤������').Data.AsString;
        deptNo:=WorkViewOK.fieldbyname('���Ŵ���').Data.AsString;
        //bookID:='';
        sex:=WorkViewOK.fieldbyname('�Ա�').Data.AsString;
        stuempNo:=WorkViewOK.fieldbyname('ѧ����').Data.AsString;
        cardBalance:=WorkViewOK.fieldbyname('����ֵ').Data.AsInteger;
        cardPWD:=WorkViewOK.fieldbyname('������').Data.AsString;
        //isFormation := Char('N');

        backTradeID:=WorkViewOK.fieldbyname('��ˮ��').Data.AsInteger;
        sOperDate := WorkViewOK.fieldbyname('ҵ������').Data.AsString;
        tradeTime := WorkViewOK.fieldbyname('ҵ��ʱ��').Data.AsString;
        stationId := WorkViewOK.fieldbyname('�ն˱��').Data.AsInteger;
        tradeNum := WorkViewOK.fieldbyname('���״���').Data.AsInteger;
        patchNo := WorkViewOK.fieldbyname('�������κ�').Data.AsInteger;

        certType := WorkViewOK.fieldbyname('֤������').Data.AsString;
        relCardSign := WorkViewOK.fieldbyname('���з���ʶ').Data.AsString;
        cardType := WorkViewOK.fieldbyname('������').Data.AsString;
        custId := WorkViewOK.fieldbyname('�ͻ���').Data.AsString;
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
      setOperReadMode(cm);

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
      //������
      //�ͻ���
      cm.setReaCardSign(relCardSign);
      cm.setCardType(cardType);
      cm.setCustNo(custId);
      cm.setCardPwd(cardPWD);
      cm.setPatchNo(IntToStr(patchNo));
      cm.setBlackCardSign(IntToStr(NORMAL_CARD));
      cm.setBlackVer('00000000000000');
      //cm.setCardCnt(IntToStr(tradeNum));
      //���õ��������޶���������޶�
      if maxper=1 then
      begin
        maxPerCount := WorkViewOK.fieldbyname('�����޶�').Data.AsInteger;
        maxPerDay := WorkViewOK.fieldbyname('���޶�').Data.AsInteger;
        cm.setMaxPerCount(IntToStr(maxPerCount));
        cm.setMaxPerDay(IntToStr(maxPerDay));
      end;
      re := cm.writeData;
      {TODO:���ý��״����Ϳ����}
      if re = 0 then
      begin
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
        if Application.MessageBox(PChar('д��ʧ�ܣ���ʹ��ͬһ�ſ�����ȷ���õ���д���ϣ���Ҫ����һ����'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
          Exit;
        //���������ţ�����ǰ�������űȽϣ���һ������
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
        re := cm.writeData;
        tof := ks_setcardbal(@tp);
        //�����ɹ��������ųɹ�����ȡ���Ŵ������ȷ���ÿ��Ѿ����гɹ����������·���
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
      //��ɺ���ˮ��Ǯ��
      st := mfcard(pCardID);
      waterCard.cardno := tradeCardNo;
      waterCard.custno := StrToInt(custId);
      waterCard.cardtype := 1;
      st := ks_sr_publishcard(@waterCard);
      cm.beep;
      if operType='D' then
        Context.GetDialogSystem.ShowMessage('�ÿ��Ѿ����������ɹ�  '+WorkViewOK.FieldByName('������Ϣ').Data.AsString)
      else
        Context.GetDialogSystem.ShowMessage('�ÿ��Ѿ������ɹ�  '+WorkViewOK.FieldByName('������Ϣ').Data.AsString);
     //Context.GetDialogSystem.ShowMessage('��ʾ����Ϊ��'+showCardNo+'�Ŀ������ɹ�');
     if st=0 then
      RzStatusPane1.Caption:='��ʾ����Ϊ��'+showCardNo+'�Ŀ������ɹ�'
     else
      RzStatusPane1.Caption:='��ʾ����Ϊ��'+showCardNo+'�Ŀ������ɹ�,��ˮ��Ǯ��д��ʧ�ܣ�';

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

initialization
  TUIStdClassFactory.Create('������������',TfaqhnewStuChangeCard);

end.