unit UACardMonyIn;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox,RzStatus, EditExts, CardDll, RzEdit,
  Buttons,RM_Class;

type
  TfaqhCardMonyIn = class(TfaqhSimpleQueryTemp)
    btnReadCardInfo: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    grp1: TGroupBox;
    WVLabel5: TWVLabel;
    edtName: TRzEdit;
    edtCardNo: TRzEdit;
    edtStuempNo: TRzEdit;
    edtCardMoney: TRzEdit;
    grp2: TGroupBox;
    cbbType: TWVComboBox;
    WVLabel3: TWVLabel;
    edtAfterMoney: TRzEdit;
    WVLabel10: TWVLabel;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    RzStatusPane7: TRzStatusPane;
    RzStatusPane8: TRzStatusPane;
    RzStatusPane9: TRzStatusPane;
    btnMoneyIn: TBitBtn;
    lblTip: TLabel;
    WVLabel1: TWVLabel;
    edtmoneymoneymoney: TRzNumericEdit;
    edtmoney: TWVDigitalEdit;
    chkSaveMoney: TCheckBox;
    chkPrint: TCheckBox;
    btnRePrint: TBitBtn;
    WVRequest1: TWVRequest;
    WorkView1: TWorkView;
    WVRTradeCancel: TWVRequest;
    WVTradeCancel: TWorkView;
    procedure btnMoneyInClick(Sender: TObject);
    procedure cbbTypeChange(Sender: TObject);
    procedure WVEdit6KeyPress(Sender: TObject; var Key: Char);
    procedure btnReadCardInfoClick(Sender: TObject);
    procedure cbbTypeKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure edtmoneyKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure btnRePrintClick(Sender: TObject);
  private
    { Private declarations }
    oldPhyId:string;
    function readCardInfo(cm:TCM): Boolean;

    //procedure writeSuccess(wv: TWorkView;money:Integer;cm:TCM);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardMonyIn: TfaqhCardMonyIn;
  OldMoney: string;

implementation

uses KsFrameworks, KSClientConsts,SmartCardCommon,KSDataDictionary;

{$R *.DFM}

procedure TfaqhCardMonyIn.Init;
begin
  inherited;
  lblTip.Caption := '';
  cbbType.ItemIndex:=0;
  //edtTicketNo.Enabled := False;
  btnMoneyIn.Enabled:=False;
  btnReadCardInfo.SetFocus;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaqhCardMonyIn.btnMoneyInClick(Sender: TObject);
var
  payCnt,dptCnt,subsidyNo:Integer;
  balance:Integer;
  st:Integer;
  //OutMoney: Integer;
  //rCardNo:string;

  //rTradeDate:string;
  //rTradeTime:string;
  //rStationNo:string;
  nowTime:Cardinal;
  cm: TCM;
  tp:TTRANSPACK;
  phyId:string;
  loDate,loTime:string;
  
  rptReport:TRMReport;
  custName:string;
  phoneNo:string;
  serialNo:string;
  cardType:string;
  fMoney:string;
  cardNo1:string;
  reErrMsg:array[0..255] of Char;
  rest:PChar;
  appSerialNo:string;
  tmpDataset:TDataSet;
begin
  if ((trim(edtmoney.Text) = '') or (edtMoney.text = '0') or (edtMoney.text = '0.0') or (edtMoney.text = '0.00')) then
  begin
    Context.GetDialogSystem.ShowMessage('����Ľ��С��λ������Ϊ�ջ�0��');
    edtMoney.SetFocus;
    Exit;
  end;
  cm := nil;
  rptReport := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ����ȷ��úÿ���');
      exit;
    end;
    cm.clearallfieldreadmode;
    //setOperReadMode(cm);
    cm.setfieldreadmode(CF_APPSERIALNO);
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(PATCH_NO);

    if cm.readCard(phyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣʧ��-'+geterrmsg);
      Exit;
    end;
    
    if oldPhyId <> phyId then
    begin
      Context.GetDialogSystem.ShowMessage('��ʹ��ͬһ�ſ����г�ֵ��');
      btnReadCardInfo.SetFocus;
      btnMoneyIn.Enabled := False;
      Exit;
    end;
    if psamTermId='' then
    begin
      Context.GetDialogSystem.ShowMessage('��������PSAM������Ȼ���ٳ�ֵ��');
      Exit;
    end;

    //��ȡ��ֵ�Ľ��״���
    try
      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      subsidyNo := StrToInt(cm.getPatchNo);
      balance := StrToInt(cm.getCardBalance);
      appSerialNo := cm.getAppSerialNo;
    except
      Context.GetDialogSystem.ShowMessage('��ȡ�����Ѵ���ʧ�ܣ�����ȡ����');
      Exit;
    end;
    loDate := FormatDateTime('yyyymmdd',Date);
    loTime := FormatDateTime('hhmmss',Now);
    fMoney := edtMoney.Text;
    {
    //���͹��ܺ�
    WorkView.FieldByName('������').Data.SetString(phyId);
    WorkView.FieldByName('����').Data.SetString(edtCardNo.Text);
    WorkView.FieldByName('�뿨���').Data.SetInteger(balance);
    WorkView.FieldByName('���״���').Data.SetInteger(dptCnt);
    WorkView.FieldByName('���Ѵ���').Data.SetInteger(payCnt);
    WorkView.FieldByName('��ֵ����').Data.SetInteger(StrToInt(Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1)));
    WorkView.FieldByName('��ֵ���').Data.SetFloat(StrToFloat(fMoney));
    WorkView.FieldByName('psam����').Data.SetString(psamTermId);
    WorkView.FieldByName('������ˮ��').Data.SetString(loTime);
    WorkView.FieldByName('��������').Data.SetString(loDate);
    WorkView.FieldByName('����ʱ��').Data.SetString(loTime);
    try
      MainRequest.SendCommand;
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage(e.Message);
        exit;
      end;
    end;
    if WorkView.fieldbyname('������').data.asinteger<>0 then
    begin
      getReturn('',WorkView);
      RzStatusPane2.Caption:=WorkView.FieldByName('������Ϣ').Data.AsString;
      Exit;
    end;
    OutMoney := WorkView.FieldByName('�������').Data.AsInteger;
    serialNo := WorkView.FieldByName('��ˮ��').Data.AsString;
    rCardNo := WorkView.FieldByName('����').Data.AsString;
    cardNo1 := WorkView.FieldByName('����1').Data.AsString;
    rTradeDate := WorkView.FieldByName('ҵ������').Data.AsString;
    rtradetime := WorkView.FieldByName('ҵ��ʱ��').Data.AsString;
    rStationNo := WorkView.FieldByName('�ն˱��').Data.AsString;
    }

    //preSetMoney(tp);
    ZeroMemory(@tp,SizeOf(tp));
    //�ն˽������к�
    tp.TermSeqno := StrToInt(FormatDateTime('hhmmss',Now));
    //�ն˱��
    StrCopy(@tp.Termno,PChar(scSiteNo));
    //���׿���
    tp.CardNo := 0;//rCardNo;
    //������
    StrCopy(@tp.CardPhyID,PChar(phyId));
    //��������
    StrCopy(@tp.TransDate,PChar(loDate));
    //����ʱ��
    StrCopy(@tp.TransTime,PChar(loTime));
    //�ն˺�
    StrCopy(@tp.Termno,PChar(psamTermId));
    //ShowMessage(tp.Termno);
    //��ֵ����Ա
    StrCopy(@tp.OperCode,PChar(Context.ParamData(svOperatorNoName).AsString));
    //��ֵ����
    tp.FundType := StrToInt(Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1));
    //����ǰ���
    tp.BefBalance := balance;
    //���׽��
    tp.TransAmt := Round(StrToFloat(fMoney)*100);
    //����ǰ��ֵ����
    tp.DptCardCnt := dptCnt;
    //����ǰ���Ѵ���
    tp.PayCardCnt := payCnt;
    //����ǰ��������
    tp.SubsidyNo := subsidyNo;

    //�޸����ý�ʽ
    {
    if setCardBal(tp,cm,phyId)<>0 then
      Exit;
    writeSuccess(WorkView,OutMoney,cm);
    }
    //��ʼ���ÿ����
    st := ks_load4card(@tp);
    if st<>0 then
    begin
      if tp.cGetProveFlag=Char(1) then
      begin
        //ѭ��Ѱ��
        nowTime := GetTickCount;
        while (1>0) do
        begin
          if (GetTickCount-nowTime)>30000 then
          begin
            Context.GetDialogSystem.ShowMessage('��ֵ��ʱ����ʹ�ÿ�����������Ƿ��ֵ�ɹ���');
            ks_dotransunprove(@tp);
            Exit;
          end;
          st := cm.card(PhyId);
          if st<>0 then
          begin
            Context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
          end
          else
          begin
            //Ѱ�������ж��Ƿ�Ϊͬһ�ſ���������ǣ���ʾ���·ſ�
            if PhyId<>oldPhyId then
              Context.GetDialogSystem.ShowMessage('���õĿ��͸ղŷ��õĲ���ͬһ�ſ��������·��ã�')
            else
              Break;
          end;
          Continue;
        end;
        Sleep(50);
        st:=ks_load4card_retry(@tp);
        if st=0 then
        begin
          cm.beep;
        end
        else
        begin
          //����д��ʧ�ܣ���ʾ�Ƿ�����ý���,�����˳�
          WVTradeCancel.FieldByName('��������').Data.SetString(tp.TransDate);
          WVTradeCancel.FieldByName('����ʱ��').Data.SetString(tp.TransTime);
          WVTradeCancel.FieldByName('sam�ն˺�').Data.SetString(psamTermId);
          WVTradeCancel.FieldByName('��������').Data.SetString(tp.TransDate);
          WVTradeCancel.FieldByName('���ײο���').Data.SetString(tp.RefNo);
          //WVTradeCancel.FieldByName('��������Ա').Data.SetInteger(tOperId);
          WVTradeCancel.FieldByName('�������').Data.SetFloat(StrToFloat(fMoney));
          try
            WVRTradeCancel.SendCommand;
            RzStatusPane2.Caption := WVTradeCancel.fieldbyname('������Ϣ').Data.AsString;
          except

          end;
          Exit;
        end;
      end
      else
      begin
        reSt := ks_geterrmsg(PChar(@reErrMsg));
        Context.GetDialogSystem.ShowMessage(reErrMsg);
      end;
    end
    else
    begin
      edtAfterMoney.Text := format('%f', [tp.AftBalance / 100]);
      cm.beep;
      if chkPrint.Checked then
      begin
        try
          WorkView1.FieldByName('�ͻ���').Data.SetInteger(0);
          WorkView1.FieldByName('�����к�').Data.SetString(appSerialNo);
          WorkView1.FieldByName('������').Data.SetInteger(0);
          WorkView1.FieldByName('��״̬').Data.SetInteger(0);
          try
            WVRequest1.SendCommand;
            if WorkView1.FieldByName('������').Data.AsInteger=0 then
            begin
              tmpDataset := TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject);
              cardType := GetIdObjectName(-1,tmpDataset.fieldbyname('lvol1').AsString);
              phoneNo := tmpDataset.fieldbyname('sphone2').AsString;
              custName := tmpDataset.fieldbyname('snote').AsString;
              cardNo1 := tmpDataset.fieldbyname('scard0').AsString;
            end;
          except

          end;
          serialNo := tp.RefNo;
          rptReport := TRMReport.Create(Self);
          rptReport.LoadFromFile(sPreAppPath+'report\RtnTicket\printTemp.rmf');
          rptReport.Dictionary.Variables.AsString['phoneNo'] := phoneNo;
          rptReport.Dictionary.Variables.AsString['custName'] := custName;
          rptReport.Dictionary.Variables.AsString['titleType'] := '��  ֵ';
          rptReport.Dictionary.Variables.AsString['serialNo'] := serialNo;
          rptReport.Dictionary.Variables.AsString['netId'] := scNetNo;
          rptReport.Dictionary.Variables.AsString['netName'] := scNetName;
          rptReport.Dictionary.Variables.AsString['termId'] := psamTermId;
          rptReport.Dictionary.Variables.AsString['operId'] := scOperNo+'-'+Context.ParamData(svOperatorNameName).AsString;
          rptReport.Dictionary.Variables.AsString['cardNo'] := cardNo1;
          rptReport.Dictionary.Variables.AsString['cardType'] := cardType;
          rptReport.Dictionary.Variables.AsString['param1'] := '������';
          rptReport.Dictionary.Variables.AsString['pValue1'] := format('%f', [tp.AftBalance / 100.0])+'Ԫ';
          rptReport.Dictionary.Variables.AsString['param2'] := '��ֵ��';
          rptReport.Dictionary.Variables.AsString['pValue2'] := format('%f', [strtofloat(fMoney)])+' Ԫ';
          rptReport.Dictionary.Variables.AsString['param3'] := '��ֵʱ�䣺';
          rptReport.Dictionary.Variables.AsString['pValue3'] := FormatDateTime('yyyy-MM-dd hh:MM:ss',Now);
          rptReport.ShowPrintDialog := False;
          rptReport.SaveToFile(sPreAppPath+'report\RtnTicket\cardmoneyin.rmp');
          if showrpt=1 then
            rptReport.ShowReport
          else
            rptReport.PrintReport;
        except
          on e:Exception do
          Context.GetDialogSystem.ShowMessage('��û�а�װ��ӡ�������ܴ�ӡ--'+e.Message);
        end;
      end;
    end;
  finally
    rptReport.Free;
    cm.Free;
  end;
end;

procedure TfaqhCardMonyIn.cbbTypeChange(Sender: TObject);
begin
  inherited;
  //edtTicketNo.Text:='';
  if (cbbType.ItemIndex = 0) then
  begin
    edtmoneymoneymoney.Enabled := True;
    //edtTicketNo.Enabled := False;
  end
  else
  begin
    edtmoneymoneymoney.Enabled := True;
    //edtTicketNo.Enabled := True;
  end;
end;

procedure TfaqhCardMonyIn.WVEdit6KeyPress(Sender: TObject; var Key: Char);
begin
  //inherited;
  if Checkedt(Key,edtMoney.Text)=False then
    Key := #0;
end;

function TfaqhCardMonyIn.readCardInfo(cm: TCM): Boolean;
var
  //CardExID: string;
  cardPhyId:string;
  //CardState:string;
  st:Integer;

begin
  Result := False;
  if preReadCard=False then
    Exit;
  st := cm.card(cardPhyId);
  if st<>0 then
  begin
    context.GetDialogSystem.ShowMessage('Ѱ��ʧ��-'+geterrmsg);
    exit;
  end;

  oldPhyId := CardPhyID;
  //��������еĶ�ȡȨ��
  cm.clearallfieldreadmode;
  //����Ҫ��ȡ���ݵ�Ȩ��
  cm.setfieldreadmode(CF_APPSERIALNO);
  cm.setfieldreadmode(CARD_BALANCE);
  cm.setfieldreadmode(PAY_CARD_CNT);
  cm.setfieldreadmode(DPT_CARD_CNT);
  cm.setfieldreadmode(CERTIFICATE_NO);

  //setOperReadMode(cm);
  st := cm.readCard(cardPhyId);
  if st<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('������Ϣʧ��-'+geterrmsg);
    Exit;
  end;
  //CardExID := readCardOneInfo(CARD_NO);
  edtCardNo.Text := cm.getAppSerialNo;
  edtName.Text := cm.getCustName;
  edtStuempNo.Text := cm.getCertNo;

  OldMoney := cm.getCardBalance;
  if OldMoney='' then
  begin
    Context.GetDialogSystem.ShowWarning('��ȡ�����ʧ�ܣ�');
    btnReadCardInfo.SetFocus;
    Exit;
  end;
  edtCardMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
  edtAfterMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
  //���Ͳ�ѯ���ף��鿴�ÿ��Ƿ�Ϊ������������������������������˳�
  {
  WorkView1.FieldByName('����').Data.SetInteger(0);
  WorkView1.FieldByName('�ͻ���').Data.SetInteger(0);
  WorkView1.FieldByName('�ͻ����').Data.SetInteger(0);
  WorkView1.FieldByName('�շ����').Data.SetInteger(0);
  WorkView1.FieldByName('Ǯ����').Data.SetInteger(0);
  WorkView1.FieldByName('������').Data.SetString(CardPhyID);
  try
    WVRequest1.SendCommand;
  except
    on e:exception do
    begin
      Context.GetDialogSystem.ShowWarning(e.message);
      btnReadCardInfo.SetFocus;
      Exit;
    end;
  end;
  CardState := (WorkView1.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('sserial0').AsString;
  if Copy(CardState,1,4) <> '1000' then
  begin
    cm.beep;
    cm.beep;
    Context.GetDialogSystem.ShowMessage('�ÿ���������״̬�Ŀ������ܳ�ֵ��');
    btnReadCardInfo.SetFocus;
    Exit;
  end;
  }
  Result := True;
end;

procedure TfaqhCardMonyIn.btnReadCardInfoClick(Sender: TObject);
var
  cm:TCM;
begin
  cm := nil;
  try
    cm := TCM.Create;
    if readCardInfo(cm)=False then
      Exit;
      {
    if bjopen=1 then
    begin
      bj(bjcomport,'W');
      bj(bjcomport,'&C11��  ����'+trim(edtName.Text)+'$');
      bj(bjcomport,'&C21����'+trim(edtCardMoney.Text)+'Ԫ$');
    end;
    }
    btnMoneyIn.Enabled := True;
    cbbType.SetFocus;
    lblTip.Caption := '';
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhCardMonyIn.cbbTypeKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
  begin
    {
    if edtTicketNo.Enabled then
      edtTicketNo.SetFocus
    else
    }
      edtmoney.SetFocus;
  end;
end;

procedure TfaqhCardMonyIn.edtmoneyKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
  begin
    if Application.MessageBox(PChar('��ȷ��ҪΪ�ÿ���ֵ['+edtmoney.Text+'Ԫ]��'), PChar(Application.Title),MB_OKCANCEL + MB_ICONQUESTION) = IDCANCEL then
    begin
      edtmoney.SetFocus;
      Exit;
    end;
    btnMoneyIn.Click;
  end;
end;

{
procedure TfaqhCardMonyIn.writeSuccess(wv: TWorkView;money: Integer;cm: TCM);
begin
  edtAfterMoney.Text := format('%f', [money / 100]);
  cm.beep;
  if chkSaveMoney.Checked=False then
    edtmoney.Text := '0';
  btnMoneyIn.Enabled := False;
  btnReadCardInfo.SetFocus;
  RzStatusPane2.Caption:=wv.FieldByName('������Ϣ').Data.AsString;

end;
}
procedure TfaqhCardMonyIn.btnRePrintClick(Sender: TObject);
begin
  rePrintOrder(sPreAppPath+'report\RtnTicket\cardmoneyin.rmp');
end;

initialization
  TUIStdClassFactory.Create('���ֽ��ֵ', TfaqhCardMonyIn);

end.

