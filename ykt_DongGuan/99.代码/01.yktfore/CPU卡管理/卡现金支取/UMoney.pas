unit UMoney;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  Mask, WVCtrls, WVDBBinders, Db, 
  RzStatus, EditExts, RzEdit, Buttons, CardDll, RM_Common, RM_Class;

type
  TfaMoney = class(TfaInputTemp)
    DataSource1: TDataSource;
    WVDBBinder1: TWVDBBinder;
    btnReadCardInfo: TBitBtn;
    btnMoneyOut: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    UIPnlQueryCount: TUIPanel;
    grp2: TGroupBox;
    edtmoney: TWVDigitalEdit;
    WVLabel1: TWVLabel;
    grp1: TGroupBox;
    WVLabel5: TWVLabel;
    WVLabel10: TWVLabel;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    edtName: TRzEdit;
    edtCardNo: TRzEdit;
    edtStuempNo: TRzEdit;
    edtCardMoney: TRzEdit;
    edtAfterMoney: TRzEdit;
    RzStatusPane7: TRzStatusPane;
    WVcashOperCancel: TWorkView;
    WVRcashOperCancel: TWVRequest;
    chkPrint: TCheckBox;
    rpt1: TRMReport;
    procedure btnReadCardInfoClick(Sender: TObject);
    procedure btnMoneyOutClick(Sender: TObject);
  private
    { Private declarations }
    oldPhyId:string;

    procedure writeSuccess(wv:TWorkView;money:Integer;cm:TCM);

    procedure printDestVoucher(rtn,custName,custId,cardNo,stempNO,lastDate,regDate:String);
  protected
     procedure Init; override;
  public
    { Public declarations }
  end;

var
  faMoney: TfaMoney;
  OldMoney: string;

implementation
uses KsFrameworks, KSClientConsts,KSDataDictionary;

{$R *.DFM}

procedure TfaMoney.Init;
begin
  inherited;
  btnMoneyOut.Enabled:=false;
  btnreadcardinfo.setfocus;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaMoney.btnReadCardInfoClick(Sender: TObject);
var
  CardExID: string;
  cm: TCM;
  CardPhyID:string;
  st:integer;
  //ResInt: SmallInt;
begin
  //CardExID:=readCardOneInfo(CARD_NO);
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(cardPhyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
      exit;
    end;
    cm.clearallfieldreadmode;
    setOperReadMode(cm);
    if cm.readCard(cardPhyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ������ԣ�');
      Exit;
    end;
    oldPhyId := CardPhyID;
    CardExID := cm.getCardNo;
    if CardExID='' then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ����ʧ��,�����¶�ȡ��');
      Exit;
    end;
    edtCardNo.Text := CardExID;
    edtName.Text := cm.getCustName;
    edtStuempNo.Text := cm.getStuempNo;
    try
      OldMoney := cm.getCardBalance;
      edtCardMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
      edtAfterMoney.Text :=format('%f', [StrToInt(OldMoney) / 100.0]);
    except
      Context.GetDialogSystem.ShowWarning('��ȡ�����ʧ�ܣ�');
      Exit;
    end;

    if bjopen=1 then
    begin
      bj(bjcomport,'W');
      bj(bjcomport,'&C11��  ����'+trim(edtName.Text)+'$');
      bj(bjcomport,'&C21����'+trim(edtCardMoney.Text)+'Ԫ$');
    end;

    btnMoneyOut.Enabled:=True;
  finally
    cm.Destroy;
  end;
end;

procedure TfaMoney.btnMoneyOutClick(Sender: TObject);
var
  CardPhyID: string;
  balance:Integer;
  OutMoney: Integer;
  cm:TCM;
  //rStationNo:Integer;
  //SeilID: integer;
  //TOF: Integer;
  //NewMoney: Integer;
  payCnt,dptCnt,subsidyNo:Integer;
  tp:TTRANSPACK;
  tradeDate,tradeTime:string;
  st:Integer;
  custType:string;
  //reErrMsg:array[0..255] of Char;
  //reSt : PChar;
begin
  if preReadCard=False then
    Exit;

  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(cardPhyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
      exit;
    end;
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CARD_SERI_NO);
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(CUST_TYPE);
    cm.setfieldreadmode(PATCH_NO);
    if cm.readCard(cardPhyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ������ԣ�');
      Exit;
    end;

    if oldPhyId <> CardPhyID then
    begin
      ShowMessage('��ʹ��ͬһ�ſ�����֧ȡ��');
      btnReadCardInfo.SetFocus;
      btnMoneyOut.Enabled := False;
      Exit;
    end;
    //���״���
    try
      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      subsidyNo := StrToInt(cm.getPatchNo);
      balance := StrToInt(cm.getCardBalance);
      custType := GetIdObjectName(-34,Trim(cm.getCustType));
    except
      Context.GetDialogSystem.ShowMessage('��ȡ�����Ѵ���ʧ�ܣ�����ȡ����');
      Exit;
    end;

    if (StrToFloat(edtCardMoney.Text))<(StrToFloat(Trim(edtMoney.Text))) then
    begin
      Context.GetDialogSystem.ShowMessage('��֧ȡ������������');
      Exit;
    end;
    //���͹��ܺ�
    WorkView.SynchronizeCtrlsToFields;
    WorkView.FieldByName('����').Data.SetInteger(StrToInt(edtCardNo.Text));
    WorkView.FieldByName('������').Data.SetString(CardPhyID);
    WorkView.FieldByName('��ֵ����').Data.SetInteger(dptCnt);
    WorkView.FieldByName('���״���').Data.SetInteger(payCnt);
    WorkView.FieldByName('�뿨���').Data.SetInteger(balance);
    MainRequest.SendCommand;
    if WorkView.FieldByName('������').Data.asinteger<>0 then
    begin
      getReturn('��֧ȡʧ�ܣ���',WorkView);
      RzStatusPane2.Caption:=WorkView.FieldByName('������Ϣ').Data.AsString;
      Exit;
    end;

    OutMoney := WorkView.FieldByName('�������').Data.AsInteger;
    //SeilID := WorkView.FieldByName('��ˮ��').Data.AsInteger;
    //rCardNo := WorkView.FieldByName('����').Data.AsInteger;
    tradeDate := WorkView.FieldByName('ҵ������').Data.AsString;
    tradeTime := WorkView.fieldbyname('ҵ��ʱ��').Data.AsString;
    //rStationNo := WorkView.FieldByName('�ն˱��').Data.AsInteger;
    //preSetMoney(tp);
    ZeroMemory(@tp,SizeOf(tp));
    //�ն˽������к�
    tp.TermSeqno := 1;
    //�ն˱��
    StrCopy(@tp.Termno,PChar(scSiteNo));
    //���׿���
    tp.CardNo := StrToInt(edtCardNo.Text);
    //������
    StrCopy(@tp.CardPhyID,PChar(CardPhyID));
    //��������
    StrCopy(@tp.TransDate,PChar(TradeDate));
    //����ʱ��
    StrCopy(@tp.TransTime,PChar(tradeTime));
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
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      //Context.GetDialogSystem.ShowMessage(reSt);
      RzStatusPane2.Caption:=cashOperCancel(WVcashOperCancel,WVRcashOperCancel,TradeDate,SeilID,StrToInt(scsiteno));
    end;
    }
    //cm.halt;
    try
      if chkPrint.Checked then
        printDestVoucher(edtmoney.Text,edtName.Text,'',edtCardNo.Text,edtStuempNo.Text,custType,'');
    except

    end;
  finally
    cm.Destroy;
  end;

end;

procedure TfaMoney.writeSuccess(wv: TWorkView; money: Integer;
  cm: TCM);
begin
  edtAfterMoney.Text := format('%f', [money / 100]);
  cm.beep;
  if bjopen=1 then
  begin
    bj(bjcomport,'&Sc$');
    bj(bjcomport,'&C11��  ����'+trim(edtName.Text)+'$');
    bj(bjcomport,'&C21��  ֵ��'+trim(edtmoney.Text)+'Ԫ$');
    bj(bjcomport,'&C31����'+trim(edtAfterMoney.Text)+'Ԫ$');
  end;

  btnMoneyOut.Enabled := False;
  btnReadCardInfo.SetFocus;
  RzStatusPane2.Caption:=wv.FieldByName('������Ϣ').Data.AsString;

end;

procedure TfaMoney.printDestVoucher(rtn, custName, custId, cardNo, stempNO,
  lastDate, regDate: String);
begin
  try
    rpt1.LoadFromFile(sPreAppPath+'report\֧ȡƾ֤.rmf');
    rpt1.Dictionary.Variables.AsString['rtnInfo'] := rtn+' Ԫ';
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
  TUIStdClassFactory.Create('���ֽ�֧ȡ',TfaMoney);

end.
