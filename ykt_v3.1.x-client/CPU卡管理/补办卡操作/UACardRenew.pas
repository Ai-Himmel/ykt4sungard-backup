unit UACardRenew;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzButton,RzRadChk, RzStatus, RzPanel, RzEdit, Buttons,
  RzSplit, Menus, UIncrementComboBox, CardDll,WaterDll;

type
  TfaqhCardRenew = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    WVLabel5: TWVLabel;
    WVComboBox6: TWVComboBox;
    WVLabel6: TWVLabel;
    WVComboBox1: TWVComboBox;
    WVLabel2: TWVLabel;
    WVComboBox3: TWVComboBox;
    btnRenewCard: TBitBtn;
    grpReleaseCard: TGroupBox;
    WVLabel11: TWVLabel;
    cbbType: TWVComboBox;
    Label7: TLabel;
    WVEdit8: TWVEdit;
    Label4: TLabel;
    edtMoney: TWVEdit;
    Label8: TLabel;
    WVRRenewCard: TWVRequest;
    WVRenewCard: TWorkView;
    WVRelCardOk: TWorkView;
    WVRRelCardOk: TWVRequest;
    WVLabel9: TWVLabel;
    WVLabel1: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel8: TWVLabel;
    WVComboBox5: TWVComboBox;
    WVEdit6: TWVEdit;
    Label6: TLabel;
    WVEdit5: TWVEdit;
    Label5: TLabel;
    WVFeeQuery: TWorkView;
    WVRFeeQuery: TWVRequest;
    WVEdit4: TWVEdit;
    chkSaveMoney: TCheckBox;
    Label10: TLabel;
    edtTicketNo: TWVEdit;
    wvrSmlPacket: TWVRequest;
    wvsmlpacket: TWorkView;
    WVLabel4: TWVLabel;
    WVComboBox4: TWVComboBox;
    WVWaterPrice: TWorkView;
    WVRWaterPrice: TWVRequest;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnRenewCardClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
    procedure cbbTypeChange(Sender: TObject);
  private
    { Private declarations }
    selectSign : Boolean;
    fMoney:Real;
    procedure getFeeResult;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardRenew: TfaqhCardRenew;

implementation

uses KsFrameworks,KSDataDictionary,KSClientConsts;

{$R *.DFM}

procedure TfaqhCardRenew.Init;
begin
  inherited;
  cbbType.ItemIndex := 0;
  //cbbPhyType.ItemIndex := 0;
  edtTicketNo.Enabled := False;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaqhCardRenew.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhCardRenew.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit1.Text) = '' then
  begin
    WorkView.FieldByName('�ͻ���').Data.SetInteger(0);
  end;
  WorkView.FieldByName('Ǯ����').Data.SetInteger(1);
  WorkView.FieldByName('�����־').Data.SetString('1');
  inherited;
  selectSign := False;
end;

procedure TfaqhCardRenew.btnRenewCardClick(Sender: TObject);
var
  showCardNo:string;
  pCardID:string;
  custId:Integer;
  cardIf:Integer;
  cardId:Integer;
  feeType:string;
  cardPhyType:integer;
  cardSelfType:integer;
  tipInfo:string;
  custName:string;
  fillMoney:Real;
  reCode:Integer;

  waterCard:TWATERCOMMPACK;
  cardNo:Integer;
  cardEndDate:string;
  custType:Integer;
  st,sti:Integer;
  rSmlMoney:integer;
  rst:integer;
  payCnt,dptCnt:Integer;
  cm:TCM;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
     Context.GetDialogSystem.ShowMessage('û�����ݣ����Ȳ�ѯ��Ȼ���ٽ��в�����');
    Exit;
  end;
  if selectSign=False then
  begin
    Context.GetDialogSystem.ShowMessage('����ѡ��һ����¼��Ȼ���ٽ��в�����');
    Exit;
  end;
  try
    custName := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('sall_name').AsString;
    //ȡ�ͻ���
    custId := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol1').AsInteger;
    //ȡ����
    cardId := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol0').AsInteger;
    tipInfo := '���Ƿ�ȷ��Ҫ��������Ϊ��'+custname+'���Ŀ���';
  except
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ���쿨����Ա��');
    Exit;
  end;
  if Application.MessageBox(PChar(tipInfo),PChar(Application.title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  if preReadCard=False then
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
  {
    //ȡ������
    pCardID := readCardOneInfo(CARD_SERI_NO);
    if pCardID='' then
    begin
      Context.GetDialogSystem.ShowMessage('�������к�ʧ�ܣ������°ѿ����õ���д���ϣ�');
      exit;
    end;
   }
  cm := nil;
  try
    cm := tcm.Create;
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

  finally
    cm.Destroy;
  end;
  //ȡ���ڲ�����
  try
    cardSelfType := ks_cardtype();
  except
    cardSelfType := 0;
  end;
  //ȡ����ʾ����
  //showCardNo:=readCardOneInfo(SHOW_CARDNO);
  try
    //�շѷ�ʽ
    feeType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
    //����������
    cardPhyType := 0;//StrToInt(Copy(cbbPhyType.Text,1,Pos('-',cbbPhyType.Text)-1));
  except
    feeType := '0';
    cardPhyType := 0;
  end;
  cardIf := 0;
  WVRenewCard.FieldByName('����Ա').Data.SetString(Context.ParamData(svOperatorNoName).AsString);
  WVRenewCard.FieldByName('��ʾ����').Data.SetString(showCardNo);        //
  WVRenewCard.FieldByName('������').Data.SetString(pCardID);           //
  WVRenewCard.FieldByName('�շѷ�ʽ').Data.SetString(feeType);
  WVRenewCard.FieldByName('Ʊ�ݺ���').Data.SetString(Trim(edtTicketNo.Text));
  WVRenewCard.FieldByName('�ͻ���').Data.SetInteger(custId);
  WVRenewCard.FieldByName('����').Data.SetInteger(cardId);
  WVRenewCard.FieldByName('����������').Data.SetInteger(cardPhyType);
  WVRenewCard.FieldByName('���ڲ�����').Data.SetInteger(cardSelfType);
  WVRenewCard.FieldByName('��ֵ����').Data.SetInteger(dptCnt);
  WVRenewCard.FieldByName('���Ѵ���').Data.SetInteger(payCnt);
  try
    WVRenewCard.FieldByName('�շѽ��').Data.SetFloat(StrToFloat(edtMoney.Text));
  except
    Context.GetDialogSystem.ShowMessage('Ӧ�ս���Ϊ��,�����룡');
    edtMoney.SetFocus;
    Exit;
  end;
  WVRenewCard.FieldByName('�տ��ɱ���').Data.SetInteger(cardIf);
  WVRRenewCard.SendCommand;
  if (WVRenewCard.FieldByName('������').Data.AsInteger = 0) then
  begin
    fillMoney := WVRenewCard.FieldByName('����ֵ').data.asfloat;
    if waterStrings.Count = 0 then
    begin
      RzStatusPane1.Caption:=pubCardNew(WVRenewCard,WVRelCardOk,WVRRelCardOk,pCardID,1,reCode);
      if reCode = 0 then
        KNG_beep;
    end
    else
    begin
      //��ʼ��ˮ�ؿ�
      RzStatusPane1.Caption:=pubCardNew(WVRenewCard,WVRelCardOk,WVRRelCardOk,pCardID,0,reCode);

      if reCode >= 0 then
      begin
        cardNo:=WVRenewCard.fieldbyname('����').Data.AsInteger;
        cardEndDate:=WVRenewCard.fieldbyname('��������').Data.AsString;
        custType := WVRenewCard.fieldbyname('�շ����').Data.AsInteger;
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
        //��СǮ���Ľ��Ӻ�̨ȡ��д�����ڵ�СǮ������------------
        }
        //д����СǮ��
        {
        wvsmlpacket.FieldByName('������־').data.SetString('Q');
        wvsmlpacket.FieldByName('�ͻ���').data.setinteger(custId);
        wvsmlpacket.FieldByName('СǮ����').data.setinteger(PACKETTYPE_XT);
        wvsmlpacket.FieldByName('ת������').data.setinteger(0);
        wvsmlpacket.FieldByName('ת�뿨��').data.setinteger(cardNo);
        wvsmlpacket.FieldByName('СǮ�����').data.setfloat(0);
        try
          wvrSmlPacket.SendCommand;
          rSmlMoney := round(wvsmlpacket.fieldbyname('СǮ�����').data.asfloat*100);
        except
          rSmlMoney := 0;
        end;
        waterCard.money := rSmlMoney;
        waterCard.totalmoney := rSmlMoney;
        st :=ks_water_publishcard(xtWater,@waterCard);

        if st=0 then
          wvsmlpacket.FieldByName('������־').data.SetString('S')
        else
          wvsmlpacket.FieldByName('������־').data.SetString('F');

        wvsmlpacket.FieldByName('�ͻ���').data.setinteger(custId);
        wvsmlpacket.FieldByName('СǮ����').data.setinteger(PACKETTYPE_XT);
        wvsmlpacket.FieldByName('ת������').data.setinteger(0);
        wvsmlpacket.FieldByName('ת�뿨��').data.setinteger(cardNo);
        wvsmlpacket.FieldByName('СǮ�����').data.setfloat(0);
        try
          wvrSmlPacket.SendCommand;
        except
        end;

        //д���СǮ��
        wvsmlpacket.FieldByName('������־').data.SetString('Q');
        wvsmlpacket.FieldByName('�ͻ���').data.setinteger(custId);
        wvsmlpacket.FieldByName('СǮ����').data.setinteger(PACKETTYPE_HD);
        wvsmlpacket.FieldByName('ת������').data.setinteger(0);
        wvsmlpacket.FieldByName('ת�뿨��').data.setinteger(cardNo);
        wvsmlpacket.FieldByName('СǮ�����').data.setfloat(0);
        try
          wvrSmlPacket.SendCommand;
          rSmlMoney := round(wvsmlpacket.fieldbyname('СǮ�����').data.asfloat*100);
        except
          rSmlMoney := 0;
        end;
        waterCard.money := rSmlMoney;
        waterCard.totalmoney := rSmlMoney;
        sti :=ks_water_publishcard(hdWater,@waterCard);

        if sti=0 then
          wvsmlpacket.FieldByName('������־').data.SetString('S')
        else
          wvsmlpacket.FieldByName('������־').data.SetString('F');

        wvsmlpacket.FieldByName('�ͻ���').data.setinteger(custId);
        wvsmlpacket.FieldByName('СǮ����').data.setinteger(PACKETTYPE_HD);
        wvsmlpacket.FieldByName('ת������').data.setinteger(0);
        wvsmlpacket.FieldByName('ת�뿨��').data.setinteger(cardNo);
        wvsmlpacket.FieldByName('СǮ�����').data.setfloat(0);
        try
          wvrSmlPacket.SendCommand;
        except
        end;
        }
        //--------------------------------------------------------------------
        //st := ks_water_publishcard(xtWater,@waterCard);
        //sti := ks_water_publishcard(hdWater,@waterCard);
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
    getReturn('',WVRenewCard);
    RzStatusPane1.Caption:=WVRenewCard.FieldByName('������Ϣ').Data.AsString;
  end;
  if bjopen=1 then
  begin
    {
    bj(bjcomport,'&Sc$');
    //bj(bjcomport,'W');
    bj(bjcomport,'&C11������'+trim(custName)+'$');
    bj(bjcomport,'&C21Ӧ��:'+floattostr(fMoney)+'$');
    //bj(bjcomport,'&C31ʵ��:'+edtmoney.Text+'$');
    bj(bjcomport,'&C41�����:'+floattostr(fillMoney)+'$');
    }
    bj(bjcomport,'&Sc$');
    bj(bjcomport,'&C11��  ��:'+trim(custName)+'$');
    bj(bjcomport,'&C21Ӧ  ��:'+floattostr(fMoney)+'?$');
    bj(bjcomport, 'B');    //������Ԥ��
    bj(bjcomport, floattostr(fMoney)+'P');//����������Ǯ
    bj(bjcomport,'&C31�����:'+floattostr(fillMoney)+'?$');
    bj(bjcomport, 't'); //�������˻����
    bj(bjcomport, floattostr(fillMoney)+'P');   //����������Ǯ
    bj(bjcomport,'&C41лл'+'X');

    
  end;
end;

procedure TfaqhCardRenew.getFeeResult();
var
  feeType, cardType,custNo,cardNo: Integer;
  sReturnInfo:string;
  custName:string;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
    Exit;
  feeType := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol5').AsInteger;
  cardType := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lsafe_level').AsInteger;
  custNo :=(WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol1').AsInteger;
  custName := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('sall_name').AsString;
  cardNo := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol0').AsInteger;
  WVFeeQuery.FieldByName('�շ����').Data.SetInteger(feeType);
  WVFeeQuery.FieldByName('������').Data.SetInteger(cardType); 
  WVFeeQuery.FieldByName('���ܺ�').Data.SetInteger(846305);
  WVFeeQuery.FieldByName('�ͻ���').Data.SetInteger(custNo);
  WVFeeQuery.FieldByName('����').Data.SetInteger(cardNo);
  WVFeeQuery.FieldByName('�Ƿ񲻼�����').Data.setstring('0');
  WVRFeeQuery.SendCommand;
  if WVFeeQuery.FieldByName('������').Data.AsInteger=0 then
  begin
    sReturnInfo := WVFeeQuery.fieldbyname('�շ���Ϣ').Data.AsString;
    fMoney := WVFeeQuery.fieldbyname('�ܷ���').Data.AsFloat;
    if bjopen=1 then
    begin
      bj(bjcomport,'&Sc$');
      bj(bjcomport,'W');
      bj(bjcomport,'&C11������'+trim(custName)+'$');
      bj(bjcomport,floattostr(fMoney)+'J');
    end;
    if chkSaveMoney.Checked=False then
      edtMoney.Text := floattostr(fMoney);
    //edtEndDate.Text := sEndDate;
    RzStatusPane1.Caption := sReturnInfo;
    selectSign := True;
  end;
end;

procedure TfaqhCardRenew.GridCellClick(Column: TColumn);
begin
  inherited;
  getFeeResult;
end;

procedure TfaqhCardRenew.cbbTypeChange(Sender: TObject);
var
  accMoney:Real;
  feeType : string;
begin
  feeType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
  if feeType='1' then
  begin
    edtTicketNo.Text := '';
    edtTicketNo.Enabled := False;
    edtMoney.Enabled := True;
  end
  else if (feeType='2') or (feeType='3') then
  begin
    edtTicketNo.Enabled := True;
    edtMoney.Enabled := True;
  end
  else if feeType='9' then
  begin
    try
      accMoney := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('damt0').asfloat;
    except
      Context.GetDialogSystem.ShowMessage('���Ȳ�ѯ����¼��Ȼ��ѡ��Ҫ����Ŀ���ѡ���շѷ�ʽ��');
      cbbType.ItemIndex := 0;
      Exit;
    end;
    if accMoney<fMoney then
    begin
       Context.GetDialogSystem.ShowMessage('�ʻ����㣬��ʹ���ֽ𲹰쿨��');
       cbbType.ItemIndex := 0;
    end
    else
    begin
      edtMoney.Enabled := False;
      edtMoney.Text := FloatToStr(fMoney);
      edtTicketNo.Text := '';
      edtTicketNo.Enabled := False;
    end;
  end;
end;

initialization
  TUIStdClassFactory.Create('���쿨����', TfaqhCardRenew);

end.


