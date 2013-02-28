unit UAMachineConsume;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox,RzStatus, EditExts, CardDll, RzEdit,
  Buttons,RM_Class;

type
  TfaqhMachineConsume = class(TfaqhSimpleQueryTemp)
    btnReadCardInfo: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    grp1: TGroupBox;
    WVLabel5: TWVLabel;
    edtName: TRzEdit;
    edtCardNo: TRzEdit;
    edtStuempNo: TRzEdit;
    edtCardMoney: TRzEdit;
    grp2: TGroupBox;
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
    btnMoneyIn: TBitBtn;
    lblTip: TLabel;
    edtmoney: TWVDigitalEdit;
    chkSaveMoney: TCheckBox;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    chkPrint: TCheckBox;
    btnRePrint: TBitBtn;
    WorkView2: TWorkView;
    WVRequest2: TWVRequest;
    procedure btnMoneyInClick(Sender: TObject);
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

    procedure writeSuccess(wv: TWorkView;money:Integer;cm:TCM);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhMachineConsume: TfaqhMachineConsume;
  OldMoney: string;

implementation

uses KsFrameworks, KSClientConsts,SmartCardCommon;

{$R *.DFM}

procedure TfaqhMachineConsume.Init;
begin
  inherited;
  lblTip.Caption := '';
  btnMoneyIn.Enabled:=False;
  btnReadCardInfo.SetFocus;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaqhMachineConsume.btnMoneyInClick(Sender: TObject);
var
  payCnt,dptCnt,subsidyNo:Integer;
  balance:Integer;
  OutMoney: Integer;
  rCardNo:string;
  appSerialNo:string;

  rTradeDate:string;
  rTradeTime:string;
  //rStationNo:string;
  cm: TCM;
  tp:TTRANSPACK;
  st:integer;
  phyId:string;
  loDate,loTime:string;
  
  rptReport:TRMReport;
  custName:string;
  phoneNo:string;
  serialNo:string;
  cardType:string;
  fMoney:string;
  //cardNo1:string;
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
      Context.GetDialogSystem.ShowMessage('��ʹ��ͬһ�ſ��������ѣ�');
      btnReadCardInfo.SetFocus;
      btnMoneyIn.Enabled := False;
      Exit;
    end;
    //��ȡ���Ľ��״���
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
    //���͹��ܺ�
    WorkView.FieldByName('���ױ�־').Data.SetString('1');
    WorkView.FieldByName('��������').Data.SetString(loDate);
    WorkView.FieldByName('����ʱ��').Data.SetString(loTime);
    WorkView.FieldByName('sam�ն˺�').Data.SetString(psamTermId);
    WorkView.FieldByName('sam��ˮ��').Data.SetInteger(StrToInt(loTime));
    WorkView.FieldByName('Ӧ�����к�').Data.SetString(appSerialNo);
    WorkView.FieldByName('������').Data.SetString(phyId);
    WorkView.FieldByName('��ֵ����').Data.SetInteger(dptCnt);
    WorkView.FieldByName('���Ѵ���').Data.SetInteger(payCnt);
    WorkView.FieldByName('���ѽ��').Data.SetFloat(StrToFloat(fMoney));
    WorkView.FieldByName('�����').Data.SetInteger(balance);
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
    OutMoney := WorkView.FieldByName('����ֵ').Data.AsInteger;
    serialNo := WorkView.FieldByName('���ײο���').Data.AsString;
    rTradeDate := WorkView.FieldByName('��������').Data.AsString;
    rtradetime := WorkView.FieldByName('����ʱ��').Data.AsString;
    //rStationNo := WorkView.FieldByName('�ն˱��').Data.AsString;
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
    //�޸����ý�ʽ
    if setCardBal(tp,cm,phyId)=0 then
    begin
      WorkView2.FieldByName('���ױ�־').Data.SetString('2');
      WorkView2.FieldByName('��������').Data.SetString(loDate);
      WorkView2.FieldByName('����ʱ��').Data.SetString(loTime);
      WorkView2.FieldByName('sam�ն˺�').Data.SetString(psamTermId);
      WorkView2.FieldByName('sam��ˮ��').Data.SetInteger(StrToInt(loTime));
      WorkView2.FieldByName('Ӧ�����к�').Data.SetString(appSerialNo);
      WorkView2.FieldByName('��������').Data.SetString(rTradeDate);
      WorkView2.FieldByName('���ײο���').Data.SetString(serialNo);
      WorkView2.FieldByName('TAC��').Data.SetString(tp.Mac);
      WVRequest2.SendCommand;
      //Context.GetDialogSystem.ShowMessage('����ʧ�ܣ������²�����');
      //Exit;
    end
    else
    begin
      Context.GetDialogSystem.ShowMessage('����ʧ�ܣ������²�����');
      Exit;
    end;
    writeSuccess(WorkView,OutMoney,cm);
    
    if chkPrint.Checked then
    begin
      try
        //serialNo := WorkView.fieldbyname('������ˮ').Data.AsString;
        rCardNo := WorkView2.FieldByName('����').Data.AsString;
        cardType := WorkView2.fieldbyname('������').Data.AsString;
        phoneNo := WorkView2.fieldbyname('�ֻ�').Data.AsString;
        custName := WorkView2.fieldbyname('����').Data.AsString;
        rptReport := TRMReport.Create(Self);
        rptReport.LoadFromFile(sPreAppPath+'report\RtnTicket\printTemp.rmf');
        rptReport.Dictionary.Variables.AsString['phoneNo'] := phoneNo;
        rptReport.Dictionary.Variables.AsString['custName'] := custName;
        rptReport.Dictionary.Variables.AsString['titleType'] := '��  ��';
        rptReport.Dictionary.Variables.AsString['serialNo'] := serialNo;
        rptReport.Dictionary.Variables.AsString['netId'] := scNetNo;
        rptReport.Dictionary.Variables.AsString['netName'] := scNetName;
        rptReport.Dictionary.Variables.AsString['termId'] := psamTermId;
        rptReport.Dictionary.Variables.AsString['operId'] := scOperNo;
        rptReport.Dictionary.Variables.AsString['cardNo'] := rCardNo;
        rptReport.Dictionary.Variables.AsString['cardType'] := cardType;
        rptReport.Dictionary.Variables.AsString['param1'] := '������';
        rptReport.Dictionary.Variables.AsString['pValue1'] := format('%f', [OutMoney / 100.0])+'Ԫ';
        rptReport.Dictionary.Variables.AsString['param2'] := '���ѽ�';
        rptReport.Dictionary.Variables.AsString['pValue2'] := format('%f', [strtofloat(fMoney)])+' Ԫ';
        rptReport.Dictionary.Variables.AsString['param3'] := '����ʱ�䣺';
        rptReport.Dictionary.Variables.AsString['pValue3'] := FormatDateTime('yyyy-MM-dd hh:MM:ss',Now);
        rptReport.ShowPrintDialog := False;
        rptReport.SaveToFile(sPreAppPath+'report\RtnTicket\cardmoneyout.rmp');
        if showrpt=1 then
          rptReport.ShowReport
        else
          rptReport.PrintReport;
      except
        on e:Exception do
        Context.GetDialogSystem.ShowMessage('��û�а�װ��ӡ�������ܴ�ӡ--'+e.Message);
      end;
    end;
  finally
    rptReport.Free;
    cm.Free;
  end;
end;

procedure TfaqhMachineConsume.WVEdit6KeyPress(Sender: TObject; var Key: Char);
begin
  //inherited;
  if Checkedt(Key,edtMoney.Text)=False then
    Key := #0;
end;

function TfaqhMachineConsume.readCardInfo(cm: TCM): Boolean;
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
  Result := True;
end;

procedure TfaqhMachineConsume.btnReadCardInfoClick(Sender: TObject);
var
  cm:TCM;
begin
  cm := nil;
  try
    cm := TCM.Create;
    if readCardInfo(cm)=False then
      Exit;
    btnMoneyIn.Enabled := True;
    lblTip.Caption := '';
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhMachineConsume.cbbTypeKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
  begin
    edtmoney.SetFocus;
  end;
end;

procedure TfaqhMachineConsume.edtmoneyKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
  begin
    if Application.MessageBox(PChar('��ȷ��Ҫʹ�øÿ�����['+edtmoney.Text+'Ԫ]��'), PChar(Application.Title),MB_OKCANCEL + MB_ICONQUESTION) = IDCANCEL then
    begin
      edtmoney.SetFocus;
      Exit;
    end;
    btnMoneyIn.Click;
  end;
end;

procedure TfaqhMachineConsume.writeSuccess(wv: TWorkView;money: Integer;cm: TCM);
begin
  edtAfterMoney.Text := format('%f', [money / 100]);
  cm.beep;
  if chkSaveMoney.Checked=False then
    edtmoney.Text := '0';
  btnMoneyIn.Enabled := False;
  btnReadCardInfo.SetFocus;
  RzStatusPane2.Caption:=wv.FieldByName('������Ϣ').Data.AsString;

end;

procedure TfaqhMachineConsume.btnRePrintClick(Sender: TObject);
begin
  rePrintOrder(sPreAppPath+'report\RtnTicket\cardmoneyout.rmp');
end;

initialization
  TUIStdClassFactory.Create('����������', TfaqhMachineConsume);

end.

