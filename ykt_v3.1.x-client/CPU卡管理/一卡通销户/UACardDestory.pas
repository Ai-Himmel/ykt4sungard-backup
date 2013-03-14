unit UACardDestory;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db,LogFile,
  RzDBGrid, RzButton,RzRadChk, RzStatus, RzPanel, RzEdit, Buttons,
  dxCntner, dxInspct, RzSplit, Menus, UIncrementComboBox, CardDll,WaterDll,
  RM_Common, RM_Class;

type
  TfaqhCardDestory = class(TfaqhSimpleQueryTemp)
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    btnRenewCard: TBitBtn;
    WVRCardDestory: TWVRequest;
    WVCardDestory: TWorkView;
    btnReadCardNo: TBitBtn;
    wvrSmlPacket: TWVRequest;
    wvsmlpacket: TWorkView;
    btnReturnSmlBag: TBitBtn;
    chkPrint: TCheckBox;
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVLabel5: TWVLabel;
    WVLabel6: TWVLabel;
    WVLabel2: TWVLabel;
    Label7: TLabel;
    WVLabel9: TWVLabel;
    WVLabel1: TWVLabel;
    WVLabel8: TWVLabel;
    Label5: TLabel;
    Label4: TLabel;
    WVLabel4: TWVLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    WVComboBox6: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox3: TWVComboBox;
    WVEdit8: TWVEdit;
    WVComboBox2: TWVComboBox;
    WVComboBox5: TWVComboBox;
    WVEdit5: TWVEdit;
    edtCardNo: TWVEdit;
    WVEdit4: TWVEdit;
    WVComboBox4: TWVComboBox;
    rpt1: TRMReport;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnRenewCardClick(Sender: TObject);
    procedure btnReadCardNoClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
    procedure btnReturnSmlBagClick(Sender: TObject);
  private
    { Private declarations }
    smlCustId:integer;      //СǮ���ͻ���
    smlCardNo:integer;      //СǮ������
    smlBal:Real;          //����СǮ�����

    function readSmlPacket():integer;
    procedure printDestVoucher(rtn,custName,custId,cardNo,stempNO,lastDate,regDate:String);
    {
    function appendSmlSerial(wv:TWorkView;wvRequest:TWVRequest;
      custId:integer;packettype:integer;
      outCardId:integer;inCardId:integer;
      smlMoney:real):integer;
      }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardDestory: TfaqhCardDestory;

implementation

uses KsFrameworks,KSDataDictionary,KSClientConsts;

{$R *.DFM}

procedure TfaqhCardDestory.Init;
begin
  inherited;
  smlCustId:=0;
  smlCardNo:=0;
  smlBal:=0;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaqhCardDestory.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhCardDestory.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit1.Text) = '' then
  begin
    WorkView.FieldByName('�ͻ���').Data.SetInteger(0);
  end;
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  WorkView.FieldByName('Ǯ����').Data.SetInteger(1);
  inherited;
end;

procedure TfaqhCardDestory.btnRenewCardClick(Sender: TObject);
var
  cardBalance: Integer; //Ԫ���֡��������ַ���
  CardID: integer;
  CardState: string;
  CardNo: string;
  cm:TCM;
  //ResInt2,ResInt3: longint;
  patchNo:Integer;//�������κ�
  payCnt,dptCnt:Integer;
  phyid:string;

  tmpData:TDataSet;
  custName:string;
  custType,regDate,stuempNo,custId,rtnInfo:string;
  money:Real;
  totMoney:Real;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
  //rtnMoney:string;
  //subsidyNo:Integer;
  st:integer;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowWarning('û�����ݣ��޷����д˲�����');
    Exit;
  end;
  if preReadCard=False then
    Exit;
  tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  //�ж��Ƿ���������
  CardState := tmpData.FieldByName('sserial0').AsString;
  CardID := tmpData.FieldByName('lvol0').AsInteger;
  custName := tmpData.fieldbyname('sall_name').AsString;
  custType := GetIdObjectName(-34,tmpData.fieldbyname('lsafe_level2').AsString);
  regDate := tmpData.fieldbyname('sdate1').AsString;
  stuempNo := tmpData.fieldbyname('spager').AsString;
  custId := tmpData.fieldbyname('lvol1').AsString;
  money := tmpData.fieldbyname('damt5').AsFloat;
  //�������������ȥ���������򲻶���
  cm := nil;
  try
    cm := TCM.Create;
    if Copy(CardState,1,4) = '1000' then
    begin
      smlBal:=0;
      //�ж�СǮ������Ƿ�Ϊ�㣬��Ϊ��Ҫ��ʾ����СǮ����Ȼ���ٲ���
      if waterStrings.Count>0 then
      begin
        if (readSmlPacket)=0 then
        begin
          if (smlBal>0) then
          begin
            Context.GetDialogSystem.ShowMessage('СǮ����Ϊ�㣬������СǮ����Ȼ����������');
            Exit;
          end;
        end;
      end;
      st := cm.card(phyId);
      if st<>0 then
      begin
        context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���Ȼ���ٲ�����');
        exit;
      end;
      //��������еĶ�ȡȨ��
      cm.clearallfieldreadmode;
      //����Ҫ��ȡ���ݵ�Ȩ��
      setOperReadMode(cm);
      if cm.readCard(phyId)<>0 then
      begin
        Context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ������ԣ�');
        Exit;
      end;

      CardNo := cm.getCardNo;
      if CardNo = '' then
      begin
        Context.GetDialogSystem.ShowMessage('��ȡ���Ŵ���,����úøÿ�!');
        Exit;
      end;

      //�ȽϿ����Ƿ����
      if CardID <> StrToInt(CardNo) then
      begin
        Context.GetDialogSystem.ShowMessage('�ÿ��Ŀ��ź���ѡ���¼�Ŀ��Ų���������ܽ����˿�������');
        Exit;
      end;

      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      cardBalance := StrToInt(cm.getCardBalance);
      //AccUseNum:=StrToInt(cm.getCardCnt);
      try
        patchNo := StrToInt(cm.getPatchNo);
      except
        patchNo := 0;
      end;

      WVCardDestory.FieldByName('��������').Data.SetString(phyId);
      WVCardDestory.FieldByName('�����').Data.SetInteger(cardBalance);
      WVCardDestory.FieldByName('����').Data.SetInteger(CardID);
      WVCardDestory.FieldByName('���״���').Data.SetInteger(dptCnt);
      WVCardDestory.FieldByName('��ֵ����').Data.SetInteger(payCnt);
      WVCardDestory.FieldByName('�������κ�').Data.SetInteger(patchNo);
      WVCardDestory.FieldByName('�Ƿ��п�').Data.SetInteger(1);
    end
    else
    begin
      //CardID := tmpData.FieldByName('lvol0').AsInteger;
      WVCardDestory.FieldByName('����').Data.SetInteger(CardID);
      WVCardDestory.FieldByName('�����').Data.SetInteger(0);
      WVCardDestory.FieldByName('��������').Data.SetString('');
      WVCardDestory.FieldByName('���״���').Data.SetInteger(0);
      WVCardDestory.FieldByName('�������κ�').Data.SetInteger(0);
      WVCardDestory.FieldByName('�Ƿ��п�').Data.SetInteger(0);
    end;
    WVCardDestory.FieldByName('����').Data.SetInteger(0);
    WVRCardDestory.SendCommand;
    if WVCardDestory.FieldByName('������').Data.AsInteger = 0 then
    begin
      if (Copy(CardState,1,4) = '1000') then
      begin
        try
          st := cm.clearCard(WVCardDestory);
          if st=0 then
            cm.beep
          else
          begin
            reSt := ks_geterrmsg(PChar(@reErrMsg));
            Context.GetDialogSystem.ShowMessage('���˿�ʱû����տ���Ϣ-'+reSt);
          end;
        except
          on e:Exception do
          begin
            Context.GetDialogSystem.ShowMessage('���˿�ʱû����տ���Ϣ'+e.Message);
          end;
        end;
      end
      else
        ConText.GetDialogSystem.ShowWarning('���˿�ʱû����տ���Ϣ��');

      if bjopen=1 then
      try
        //tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
        bj(bjcomport,'&Sc$');
        bj(bjcomport,'&C11��  ����'+trim(custName)+'$');
        bj(bjcomport,'&C21�����:'+floattostr(money)+'Ԫ$');
        try
          totMoney := WVCardDestory.fieldbyname('�˿���').Data.AsFloat;
        except
          totMoney := money;
        end;
        bj(bjcomport,'&C31���˿�:'+floattostr(totMoney)+'Ԫ$');
      except
      end;
      rtnInfo := WVCardDestory.FieldByName('������Ϣ').Data.AsString;
      //rtnMoney := WVCardDestory.fieldbyname('�˿���').Data.AsString;
      Context.GetDialogSystem.ShowMessage(rtnInfo);
      RzStatusPane1.caption:=rtnInfo;
      try
        if chkPrint.Checked then
          printDestVoucher(rtnInfo,custName,custId,IntToStr(CardID),stuempNo,custType,regDate);
      except

      end;
    end
    else
    begin
      getReturn('�ջؿ�ʧ��--',WVCardDestory);
      RzStatusPane1.caption:=WVCardDestory.FieldByName('������Ϣ').Data.AsString;
    end;
    btnQueryClick(Sender);
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhCardDestory.btnReadCardNoClick(Sender: TObject);
var
  cardNo:string;
begin
  edtCardNo.Text:='';
  try
    cardNo := readCardOneInfo(CARD_NO);
  except
    Exit;
  end;
  if (cardNo='') or (cardNo='0') then
  begin
    Context.GetDialogSystem.ShowMessage('������ѯʧ�ܣ�����Ϊ��򲻴���!');
    Exit;
  end;
  edtCardNo.Text:=cardNo;
  btnQuery.Click();
end;

procedure TfaqhCardDestory.GridCellClick(Column: TColumn);
var
  tmpData:TDataSet;
  custName:string;
  money:Real;
begin
  //inherited;
  if bjopen=1 then
    try
      tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
      custName := tmpData.fieldbyname('sall_name').AsString;
      money := tmpData.fieldbyname('damt5').AsFloat;
      bj(bjcomport,'W');
      bj(bjcomport,'&Sc$');
      bj(bjcomport,'&C11��  ����'+trim(custName)+'$');
      bj(bjcomport,'&C21�����:'+floattostr(money)+'Ԫs$');
    except
    end;
end;

function TfaqhCardDestory.readSmlPacket:integer;
var
  phyId:string;
  st:SmallInt;
  waterPack:TWATERCOMMPACK;
  i:Integer;
  smlbgNo:Integer;
begin
  //��СǮ����Ϣ
  st := mfcard(phyId);
  if st<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('СǮ��Ѱ��ʧ�ܣ�');
    Result := -1;
    Exit;
  end;
  preCommWaterPack(waterPack);
  //��ȡСǮ�����
  if waterStrings.Count>0 then
  begin
    for i:= 0 to waterStrings.Count-1 do
    begin
      try
        smlbgNo := StrToInt(waterStrings[i]);
      except
        smlbgNo := 0;
      end;
      st := ks_water_readmoney(smlbgNo,@waterpack);
      if st<>0 then
        smlBal := 0
      else
        smlBal := waterPack.money;                 //СǮ�����
      if smlBal>0 then
        Break;
    end;
  end;
  result := 0;
end;

procedure TfaqhCardDestory.btnReturnSmlBagClick(Sender: TObject);
var
  cm:TCM;
  st:Integer;
  phyId,mfPhyid:string;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
  CardState:string;
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
  //ifMoney:Integer;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowWarning('û�����ݣ��޷����д˲�����');
    Exit;
  end;
  dptCnt:=0;
  payCnt := 0;
  cardNo := 0;
  balance := 0;
  if preReadCard=False then
    Exit;
  st := -1;
  //�ж��Ƿ���������
  CardState := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('sserial0').AsString;
  cm := nil;
  try
    if waterStrings.Count>0 then
    begin
      for i:=0 to waterStrings.Count-1 do
      begin
        try
          smlBagNo := StrToInt(waterStrings[i])
        except
          smlBagNo := 0;
        end;
        cm := TCM.Create;
        if Copy(CardState,1,4) = '1000' then
        begin
          st := cm.card(phyId);
          if st<>0 then
          begin
            context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���Ȼ���ٲ�����');
            exit;
          end;
          //��������еĶ�ȡȨ��
          cm.clearallfieldreadmode;
          //����Ҫ��ȡ���ݵ�Ȩ��
          cm.setfieldreadmode(DPT_CARD_CNT);
          cm.setfieldreadmode(PAY_CARD_CNT);
          cm.setfieldreadmode(CARD_NO);
          cm.setfieldreadmode(CARD_BALANCE);
          //setOperReadMode(cm);
          if cm.readCard(phyId)<>0 then
          begin
            Context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ������ԣ�');
            Exit;
          end;
          try
            dptCnt:=StrToInt(cm.getDptCardCnt);
            payCnt := StrToInt(cm.getPayCardCnt);
            cardNo := StrToInt(cm.getCardNo);
            balance := StrToInt(cm.getCardBalance);
          except
          end;
          wvsmlpacket.FieldByName('�ն˺�').Data.SetInteger(0);
          wvsmlpacket.FieldByName('���޿���־').Data.SetInteger(1);
          wvsmlpacket.FieldByName('������').Data.SetString(phyId);
          wvsmlpacket.FieldByName('����').Data.SetInteger(cardNo);
          wvsmlpacket.FieldByName('��Ǯ����ֵ����').Data.SetInteger(payCnt);
          wvsmlpacket.FieldByName('��Ǯ�����Ѵ���').Data.SetInteger(dptCnt);
          wvsmlpacket.FieldByName('��Ǯ�����').Data.SetInteger(balance);
          wvsmlpacket.FieldByName('Ǯ����').Data.SetInteger(smlBagNo);
          //��СǮ����Ϣ
          st := mfcard(mfPhyid);
          if st<>0 then
          begin
            Context.GetDialogSystem.ShowMessage('ˮ��Ǯ��Ѱ��ʧ��--'+inttostr(st));
            Exit;
          end;
          if mfPhyid<>phyId then
          begin
            Context.GetDialogSystem.ShowMessage('��ʹ��ͬһ�ſ����в���--'+inttostr(st));
            Exit;
          end;
          preCommWaterPack(waterPack);
          st := ks_water_readmoney(smlBagNo,@waterpack);
          if st<>0 then
          begin
            reSt := ks_geterrmsg(PChar(@reErrMsg));
            Context.GetDialogSystem.ShowMessage('��ȡСǮ��ʧ��,��Ǯ���Ѿ�����-'+reSt);
            Exit;
          end;
          if waterPack.money=0 then
            Continue;
          wvsmlpacket.FieldByName('СǮ�����Ѵ���').Data.SetInteger(0);
          wvsmlpacket.FieldByName('СǮ�����').Data.SetInteger(waterPack.money);
        end
        else
        begin
          cardNo := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol0').AsInteger;
          wvsmlpacket.FieldByName('�ն˺�').Data.SetInteger(0);
          wvsmlpacket.FieldByName('���޿���־').Data.SetInteger(0);
          wvsmlpacket.FieldByName('������').Data.SetString('');
          wvsmlpacket.FieldByName('����').Data.SetInteger(cardNo);
          wvsmlpacket.FieldByName('��Ǯ����ֵ����').Data.SetInteger(0);
          wvsmlpacket.FieldByName('��Ǯ�����Ѵ���').Data.SetInteger(0);
          wvsmlpacket.FieldByName('��Ǯ�����').Data.SetInteger(0);
          wvsmlpacket.FieldByName('СǮ�����Ѵ���').Data.SetInteger(0);
          wvsmlpacket.FieldByName('СǮ�����').Data.SetInteger(0);
          wvsmlpacket.FieldByName('Ǯ����').Data.SetInteger(smlBagNo);
        end;
        wvrSmlPacket.SendCommand;
        if wvsmlpacket.FieldByName('������').Data.AsInteger = 0 then
        begin
          if (Copy(CardState,1,4) = '1000') then
          begin
            //�����ɹ������ô�Ǯ�����
            OutMoney := wvsmlpacket.FieldByName('r��Ǯ�����').Data.AsInteger;
            rCardNo := wvsmlpacket.FieldByName('r����').Data.AsInteger;
            rTradeDate := wvsmlpacket.FieldByName('r��������').Data.AsString;
            rtradetime := wvsmlpacket.FieldByName('r����ʱ��').Data.AsString;
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
              //Context.GetDialogSystem.ShowMessage('СǮ������ʧ��-'+inttostr(st))
              WriteLog('СǮ��['+inttostr(smlBagNo)+']����ʧ��-'+inttostr(st),0)
            else
            begin
              st := cm.card(phyId);
              if st<>0 then
              begin
                context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ����ȵ�������Ȼ����������');
                exit;
              end;
              //�޸����ý�ʽ
              st := setCardBal(tp,cm,phyId);
              if st<>0 then
              begin

              end;
              cm.beep;
            end;
          end
          else
            WriteLog('СǮ��['+inttostr(smlBagNo)+']����ʧ��-'+inttostr(st),0);
        end
        else
        begin
          Context.GetDialogSystem.ShowMessage(wvsmlpacket.FieldByName('������Ϣ').Data.AsString);
          Exit;
        end;
      end;
    end;
    Context.GetDialogSystem.ShowMessage('��СǮ����ɣ�����������');
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhCardDestory.printDestVoucher(rtn,custName,custId,cardNo,stempNO,lastDate,regDate:String);
begin
  try
    //qckrp1.qr
    {
    frmDestCard := TfrmDestCard.Create(nil);
    frmDestCard.qrlblRptTitle.Caption := rptTitle;
    frmDestCard.qrlblPrintDate.Caption := '��ӡ����:'+formatdatetime('yyyy-mm-dd',Date);
    frmDestCard.qrlblCustNo.Caption := custId;
    frmDestCard.qrlblCardNo.Caption := cardNo;
    frmDestCard.qrlblStuempNo.Caption := stempNO;
    frmDestCard.qrlblCustName.Caption := custName;
    frmDestCard.qrlblRegDate.Caption := regDate;
    frmDestCard.qrlblRMoney.Caption := lastDate;
    //qrmRstInfo.Caption := rtn;
    frmDestCard.qrlblRtn.Caption := rtn;
    frmDestCard.qrlblOperName.Caption := Context.ParamData(svOperatorNameName).AsString;
    //qckrp1.Page.Orientation:= poLandscape;
    frmDestCard.qckrp1.Preview;
    frmDestCard.Destroy;
    }

    rpt1.LoadFromFile(sPreAppPath+'report\����ƾ֤.rmf');
    rpt1.Dictionary.Variables.AsString['rtnInfo'] := rtn;
    rpt1.Dictionary.Variables.AsString['custName'] := custName;
    rpt1.Dictionary.Variables.AsString['custId'] := custId;
    rpt1.Dictionary.Variables.AsString['cardNo'] := cardNo;
    rpt1.Dictionary.Variables.AsString['stuempNo'] := stempNO;
    rpt1.Dictionary.Variables.AsString['custType'] := lastDate;
    rpt1.Dictionary.Variables.AsString['regDate'] := regDate;
    rpt1.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
    rpt1.Dictionary.Variables.AsString['operName'] := Context.ParamData(svOperatorNameName).AsString;
    rpt1.DoublePass := True;
    //rpt1.Preview := rmprvwP;
    rpt1.ShowReport;
    
  except
    Context.GetDialogSystem.ShowMessage('��û�а�װ��ӡ�������Ȱ�װ(�����������ӡ��)��');
  end;

end;

initialization
  TUIStdClassFactory.Create('һ��ͨ����', TfaqhCardDestory);

end.


