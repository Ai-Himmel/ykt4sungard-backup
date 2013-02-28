unit UASetCardMony;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox,RzStatus, EditExts, CardDll, RzEdit,
  Buttons, RzPanel, RzRadGrp;

type
  TfaqhSetCardMony = class(TfaqhSimpleQueryTemp)
    btnReadCardInfo: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    grp1: TGroupBox;
    edtName: TRzEdit;
    edtAppCardNo: TRzEdit;
    edtPhyId: TRzEdit;
    grp2: TGroupBox;
    WVLabel3: TWVLabel;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane7: TRzStatusPane;
    btnMoneyIn: TBitBtn;
    WVRcashOperCancel: TWVRequest;
    WVcashOperCancel: TWorkView;
    edtmoneymoneymoney: TRzNumericEdit;
    rzstspn1: TRzStatusPane;
    rgDirection: TRzRadioGroup;
    edtMoney: TRzEdit;
    rzstspn2: TRzStatusPane;
    edtTradeNum: TRzEdit;
    rzstspn3: TRzStatusPane;
    rzstspn4: TRzStatusPane;
    cbbErrOperNo: TWVComboBox;
    edtPwd: TWVEdit;
    rzstspn5: TRzStatusPane;
    edtLibMoney: TRzEdit;
    rzstspn6: TRzStatusPane;
    edtCardBal: TRzEdit;
    RzStatusPane8: TRzStatusPane;
    edtPayNum: TRzEdit;
    RzStatusPane5: TRzStatusPane;
    edtBeforeMoney: TRzEdit;
    edtAfterMoney: TRzEdit;
    RzStatusPane6: TRzStatusPane;
    WVLabel10: TWVLabel;
    WVLabel5: TWVLabel;
    WVLabel1: TWVLabel;
    WVLabel2: TWVLabel;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    procedure btnMoneyInClick(Sender: TObject);
    procedure btnReadCardInfoClick(Sender: TObject);
    procedure edtmoneyKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure edtMoneyChange(Sender: TObject);
    procedure rgDirectionClick(Sender: TObject);
  private
    { Private declarations }
    oldPhyId:string;
    function readCardInfo(cm:TCM): Boolean;
    procedure writeSuccess(wv:TWorkView;money:Integer;cm:TCM);
    procedure calcMoney;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetCardMony: TfaqhSetCardMony;
  OldMoney: string;

implementation

uses KsFrameworks, KSClientConsts;

{$R *.DFM}

procedure TfaqhSetCardMony.Init;
begin
  inherited;
  btnMoneyIn.Enabled:=False;
  btnReadCardInfo.SetFocus;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaqhSetCardMony.btnMoneyInClick(Sender: TObject);
var
  cm:TCM;
  st:Integer;
  payCnt,dptCnt:Integer;
  CardPhyID: string;
  balance:Integer;
  OutMoney: Integer;
  tp:TTRANSPACK;
  //tof:Integer;
  rTradeDate:string;
  rtradetime:string;
  //SeilID: integer;
  ragion:Integer;
  operCode:string;
  operPwd:string;
  subsidyNo:Integer;
begin
  if ((trim(edtmoney.Text) = '') or (edtMoney.text = '0') or (edtMoney.text = '0.0')
    or (edtMoney.text = '0.00')) then
  begin
    Context.GetDialogSystem.ShowMessage('����Ľ��С��λ������Ϊ�ջ�0��');
    edtMoney.SetFocus;
    Exit;
  end;
  try
    if StrToFloat(edtMoney.Text)>0 then

  except
    Context.GetDialogSystem.ShowMessage('��������Ч�ĵ�����');
    edtMoney.SetFocus;
    Exit;
  end;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(cardPhyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
      exit;
    end;
    {
    cardPhyId := readCardOneInfo(CARD_SERI_NO);
    if cardPhyId = '' then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ������ʧ��,�ÿ��Ѿ��𻵣�');
      btnReadCardInfo.SetFocus;
      Exit;
    end
    else
    begin
      WorkView.FieldByName('������').Data.SetString(CardPhyID);
    end;
    }
    if oldPhyId <> CardPhyID then
    begin
      Context.GetDialogSystem.ShowMessage('��ʹ��ͬһ�ſ��������ÿ���');
      btnReadCardInfo.SetFocus;
      btnMoneyIn.Enabled := False;
      Exit;
    end;

    //��������еĶ�ȡȨ��
    cm.clearallfieldreadmode;
    //����Ҫ��ȡ���ݵ�Ȩ��
    setOperReadMode(cm);
    st := cm.readCard(cardPhyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣʧ��--'+inttostr(st));
      Exit;
    end;

    //��ȡ��ֵ�Ľ��״���
    try
      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      subsidyNo := StrToInt(cm.getPatchNo);
      balance := StrToInt(cm.getCardBalance);
    except
      Context.GetDialogSystem.ShowMessage('��ȡ�����Ѵ���ʧ�ܣ�����ȡ����');
      Exit;
    end;

    if rgDirection.ItemIndex=0 then
      ragion := 1
    else
      ragion := -1;
    operCode := Copy(cbbErrOperNo.Text,1,Pos('-',cbbErrOperNo.Text)-1);
    operPwd := encOperPwd(operCode,Trim(edtPwd.Text));
    WorkView.FieldByName('�ն˱��').Data.SetString(psamTermId);
    WorkView.FieldByName('����').Data.SetString(edtAppCardNo.Text);
    WorkView.FieldByName('������').Data.SetString(CardPhyID);
    WorkView.FieldByName('�뿨���').Data.SetInteger(balance);
    WorkView.FieldByName('���״���').Data.SetInteger(payCnt);
    WorkView.FieldByName('��ֵ����').Data.SetInteger(dptCnt);
    WorkView.FieldByName('��֤����').Data.SetString(operPwd);
    WorkView.FieldByName('����').Data.SetInteger(ragion);
    WorkView.FieldByName('�������').Data.SetFloat(StrToFloat(edtMoney.Text));
    MainRequest.SendCommand;
    if WorkView.fieldbyname('������').data.asinteger<>0 then
    begin
      getReturn('',WorkView);
      RzStatusPane2.Caption:=WorkView.FieldByName('������Ϣ').Data.AsString;
      Exit;
    end;
    OutMoney := WorkView.FieldByName('�������').Data.AsInteger;
    //SeilID := WorkView.FieldByName('��ˮ��').Data.AsInteger;
    //rCardNo := WorkView.FieldByName('����').Data.AsInteger;
    rTradeDate := WorkView.FieldByName('ҵ������').Data.AsString;
    rtradetime := WorkView.FieldByName('ҵ��ʱ��').Data.AsString;
    //rStationNo := WorkView.FieldByName('�ն˱��').Data.AsInteger;
    //preSetMoney(tp);
    ZeroMemory(@tp,SizeOf(tp));
    //�ն˽������к�
    tp.TermSeqno := 1;
    //�ն˱��
    StrCopy(@tp.Termno,PChar(scSiteNo));
    //���׿���
    tp.CardNo := 0;//StrToInt(edtCardNo.Text);
    //������
    StrCopy(@tp.CardPhyID,PChar(CardPhyID));
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
    tp.SubsidyNo := subsidyNo;

    if setCardBal(tp,cm,cardPhyId)<>0 then
      Exit;
    writeSuccess(WorkView,OutMoney,cm);
    {
    tof := ks_setcardbal(@tp);
    if tof = 0 then
    begin
      writeSuccess(WorkView,OutMoney,cm);
    end
    else
      RzStatusPane2.Caption:=cashOperCancel(WVcashOperCancel,WVRcashOperCancel,rTradeDate,SeilID,StrToInt(scsiteno));
    }
    edtPwd.Text := '';
    //cm.halt;
  finally
    cm.Destroy;
  end;
end;

function TfaqhSetCardMony.readCardInfo(cm: TCM): Boolean;
var
  cardPhyId:string;
  st:Integer;
  //CardExID: string;
  tradeNum:Integer;
begin
  Result := False;
  if preReadCard=False then
    Exit;
  {
  cardPhyId := readCardOneInfo(CARD_SERI_NO);
  if cardPhyId = '' then
  begin
    Context.GetDialogSystem.ShowMessage('��ȡ������ʧ��,�ÿ��Ѿ��𻵣�');
    btnReadCardInfo.SetFocus;
    Exit;
  end;
  }
  st := cm.card(cardPhyId);
  if st<>0 then
  begin
    context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
    exit;
  end;

  oldPhyId := CardPhyID;
  //��������еĶ�ȡȨ��
  cm.clearallfieldreadmode;
  //����Ҫ��ȡ���ݵ�Ȩ��
  //setOperReadMode(cm);
  cm.setfieldreadmode(CF_APPSERIALNO);
  cm.setfieldreadmode(CARD_BALANCE);
  cm.setfieldreadmode(PAY_CARD_CNT);
  cm.setfieldreadmode(DPT_CARD_CNT);
  cm.setfieldreadmode(CERTIFICATE_NO);
  cm.setfieldreadmode(CUST_NAME);
  st := cm.readCard(cardPhyId);
  if st<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('������Ϣʧ��--'+inttostr(st));
    Exit;
  end;


  edtAppCardNo.Text := cm.getAppSerialNo;
  
  edtName.Text := cm.getCustName;
  edtPhyId.Text := cardPhyId;

  OldMoney := cm.getCardBalance;
  edtBeforeMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
  edtCardBal.Text := edtBeforeMoney.Text;
  //edtAfterMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
  tradeNum := StrToInt(cm.getDptCardCnt);
  edtTradeNum.Text := IntToStr(tradeNum);
  edtpayNum.text := cm.getPayCardCnt;

  //���Ͳ�ѯ���ף��鿴�ÿ��Ƿ�Ϊ������������������������������˳�
  WorkView1.FieldByName('�����к�').Data.SetString(cm.getAppSerialNo);
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
  
  edtLibMoney.Text := (WorkView1.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('damt1').AsString;
  //
  try
    edtAfterMoney.Text := edtLibMoney.Text;
    edtMoney.Text := FloatToStr(Abs(StrToFloat(edtCardBal.Text)-strtofloat(edtLibMoney.Text)));
  except

  end;
  {
  if Copy(CardState,1,4) <> '1000' then
  begin
    CardManage.ControlBuzzer;
    CardManage.ControlBuzzer;
    Context.GetDialogSystem.ShowMessage('�ÿ���������״̬�Ŀ������ܵ�������');
    btnReadCardInfo.SetFocus;
    Exit;
  end;
  }
  Result := True;
end;

procedure TfaqhSetCardMony.btnReadCardInfoClick(Sender: TObject);
var
  cm:TCM;
begin
  cm := nil;
  try
    cm := TCM.Create;
    if readCardInfo(cm)=False then
      Exit;
    btnMoneyIn.Enabled := True;
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhSetCardMony.edtmoneyKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
  begin
    if Application.MessageBox(PChar('��ȷ��ҪΪ�ÿ����ý��['+edtmoney.Text+'Ԫ]��'), PChar(Application.Title),MB_OKCANCEL + MB_ICONQUESTION) = IDCANCEL then
    begin
      edtmoney.SetFocus;
      Exit;
    end;
    btnMoneyIn.Click;
  end;
end;

procedure TfaqhSetCardMony.writeSuccess(wv: TWorkView; money: Integer;cm: TCM);
begin
  edtAfterMoney.Text := format('%f', [money / 100]);
  cm.beep;
  btnMoneyIn.Enabled := False;
  btnReadCardInfo.SetFocus;
  RzStatusPane2.Caption:=wv.FieldByName('������Ϣ').Data.AsString;

end;

procedure TfaqhSetCardMony.edtMoneyChange(Sender: TObject);
begin
  calcMoney;
end;

procedure TfaqhSetCardMony.rgDirectionClick(Sender: TObject);
begin
  calcMoney;
end;

procedure TfaqhSetCardMony.calcMoney;
begin
  if edtMoney.Text='' then
  begin
    edtMoney.Text := '0';
  end;
  try
    if rgDirection.ItemIndex=0 then
    begin
      edtAfterMoney.Text := FloatToStr(StrToFloat(edtBeforeMoney.Text)+strtofloat(edtMoney.Text));
    end
    else
    begin
      edtAfterMoney.Text := FloatToStr(StrToFloat(edtBeforeMoney.Text)-strtofloat(edtMoney.Text));
    end;
  except
    Context.GetDialogSystem.ShowMessage('��������Ч�����֣�');
    Exit;
  end;
end;

initialization
  TUIStdClassFactory.Create('��������', TfaqhSetCardMony);

end.
