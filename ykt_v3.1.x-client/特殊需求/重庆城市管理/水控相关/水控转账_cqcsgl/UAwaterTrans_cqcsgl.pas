unit UAwaterTrans_cqcsgl;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons, RzStatus, CardDll,WaterDll;

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
    procedure edtAddMoneyKeyPress(Sender: TObject; var Key: Char);
    procedure btnReadCardClick(Sender: TObject);
    procedure btnTranClick(Sender: TObject);
  private

    { Private declarations }
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
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
  btnTran.Enabled := False;
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
  waterPack:TWATERPACK;
begin
  if preReadCard=False then
    Exit;
  cm := nil;
  try
    cm := TCM.Create;
    //��������еĶ�ȡȨ��
    cm.clearallfieldreadmode;
    //����Ҫ��ȡ���ݵ�Ȩ��
    setOperReadMode(cm);
    //cm.card(phyId);
    st := cm.readCard;
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
      Context.GetDialogSystem.ShowMessage('СǮ��Ѱ��ʧ��--'+inttostr(st));
      Exit;
    end;
    preReadWaterPack(waterPack);
    st := ks_sr_readmoney(@waterpack);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡСǮ�����ʧ��--'+inttostr(st));
      Exit;
    end;
    edtsmlMoney.Text := Format('%f',[waterPack.money/100.0]);
    smallCnt := waterPack.add_count;
    //edtsmlMoney.Text := 
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
  //kouMoney:Integer;
  //patchMoney:Integer;
  smlMoney:Integer;
  tp:TTRANSPACK;
  payCnt,dptCnt,subsidyNo:Integer;
  smlPhyId:string;
begin
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
    cm.clearallfieldreadmode;

    cm.setfieldreadmode(CARD_SERI_NO);
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PATCH_NO);
    cm.setfieldreadmode(DPT_CARD_CNT);
    if cm.readCard<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ������ԣ�');
      Exit;
    end;
    phyId := cm.getCardSeriNo;
    if phyId='' then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ������ʧ�ܣ�');
      Exit;
    end
    else
    begin
      WorkView1.FieldByName('��������').Data.SetString(phyId);
    end;
    if phyId <> edtPhyId.Text then
    begin
      Context.GetDialogSystem.ShowMessage('��ʹ��ͬһ�ſ����г�ֵ��');
      btnReadCard.SetFocus;
      btnTran.Enabled := False;
      Exit;
    end;
    //cardBal := StrToInt(cm.getCardBalance);
    dptCnt:=StrToInt(cm.getDptCardCnt);
    payCnt := StrToInt(cm.getPayCardCnt);
    subsidyNo := StrToInt(cm.getPatchNo);
    balance := StrToInt(cm.getCardBalance);

    WorkView1.FieldByName('���ײο���').Data.SetString(tradeCode);
    WorkView1.FieldByName('�����').Data.SetString(mac);
    WorkView1.FieldByName('����').Data.SetInteger(StrToInt(cm.getCardNo));
    WorkView1.FieldByName('�����').Data.SetInteger(balance);
    WorkView1.FieldByName('���״���').Data.SetInteger(StrToInt(cm.getPayCardCnt));
    WorkView1.FieldByName('СǮ�����').Data.SetInteger(StrToInt(FloatToStr(StrToFloat(edtsmlMoney.Text)*100)));
    WorkView1.FieldByName('ת�˽��').Data.SetInteger(StrToInt(FloatToStr(StrToFloat(edtAddMoney.Text)*100)));
    WorkView1.FieldByName('֧������').Data.SetInteger(1000);
    WVRequest1.SendCommand;
    if workview1.FieldByName('������').Data.AsInteger<>0 then
    begin
      getReturn('',WorkView1);
      Exit;
    end;
    accdate := WorkView1.fieldbyname('��������').Data.AsString;
    accTime := WorkView1.fieldbyname('����ʱ��').Data.AsString;
    outMoney := WorkView1.fieldbyname('����ֵ').Data.AsInteger;
    //kouMoney := WorkView1.fieldbyname('�ۿ���').Data.AsInteger;
    //patchMoney := WorkView1.fieldbyname('��д���').Data.AsInteger;
    smlMoney := WorkView1.fieldbyname('СǮ�����').Data.AsInteger;
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
    st := ks_setcardbal(@tp);
    if st = 0 then
    begin
      //�ۿ�ɹ���ʼдˮ����� ,д֮ǰҪ��Ѱ��
      //��СǮ����Ϣ
      st := mfcard(smlPhyId);
      if st<>0 then
      begin
        Context.GetDialogSystem.ShowMessage('СǮ��Ѱ��ʧ��--'+inttostr(st));
        Exit;
      end;
      st := ks_sr_setmoeny(smlMoney,smallCnt+1);
      if st = 0 then
        cm.beep
      else
        Context.GetDialogSystem.ShowMessage('дˮ��Ǯ��ʧ�ܣ��뵽������������ý���--'+inttostr(st));
      
    end
    else
    begin
      rzstspnStat.Caption:=CancelOper(WVcashOperCancel,WVRcashOperCancel,tradeCode,mac);
      btnReadCard.SetFocus;
      btnTran.Enabled := False;
      Exit;
    end;
    cm.halt;
    edtAfterMoney.Text := Format('%f',[outMoney/100.0]);
    edtAfterSmlMoney.Text := Format('%f',[smlMoney/100.0]);
    btnReadCard.SetFocus;
    btnTran.Enabled := False;
  finally
    cm.Destroy;
  end;

end;

initialization
  TUIStdClassFactory.Create('ˮ��Ǯ��ת��',TfaqhwaterTrans_cqcsgl);

end.