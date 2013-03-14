unit UACardReRel_cqcsgl;

interface
              
uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhInputTemp, WVCmdReq, WorkViews, StdCtrls, ExtCtrls,
  UICtrls, WVCtrls, Mask, CardDll,WaterDll,
  RzPanel, RzStatus, Buttons, 
  RzEdit;

type
  TfaqhCardReRelease = class(TfaqhInputTemp)
    UIPanel3: TUIPanel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    UIPnlQueryCount: TUIPanel;
    LabRecordCount: TLabel;
    WVLabel3: TWVLabel;
    WVLabel4: TWVLabel;
    WVLabel5: TWVLabel;
    WVLabel6: TWVLabel;
    WVLabel11: TWVLabel;
    WVLabel12: TWVLabel;
    WVLabel10: TWVLabel;
    WVLabel9: TWVLabel;
    WVLabel8: TWVLabel;
    WVLabel7: TWVLabel;
    grp1: TGroupBox;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    WVRelCardOk: TWorkView;
    WVRRelCardOk: TWVRequest;
    RzStatusPane7: TRzStatusPane;
    btnReleaseCard: TBitBtn;
    RzStatusPane4: TRzStatusPane;
    edtPhyId: TRzEdit;
    edtCardId: TRzEdit;
    edtEndDate: TRzEdit;
    edtBalance: TRzEdit;
    edtPwd: TRzEdit;
    edtFeeType: TRzEdit;
    RzStatusPane5: TRzStatusPane;
    procedure btnReleaseCardClick(Sender: TObject);
  private
    { Private declarations }
    phyId:string;
    cardId:string;
    balance:Integer;
    payCnt,dptCnt,subsidyNo:Integer;


    function readCardInfo: Boolean;
  public
    { Public declarations }
    procedure Init;override;
  end;

var
  faqhCardReRelease: TfaqhCardReRelease;

implementation
uses KSFrameWorks, KSClientConsts,KSDataDictionary;

{$R *.DFM}

procedure TfaqhCardReRelease.Init;
begin
  inherited;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaqhCardReRelease.btnReleaseCardClick(Sender: TObject);
var
  stationId:Integer;
  cm : TCM;
  rBalance:Integer;
  rFeeType:Integer;
  rPwd:string;
  rEndDate:string;
  //rTradeNum:Integer;
  maxPerCount,maxPerDay:Integer;
  tradeDate,tradeTime:string;
  st:Integer;
  tof : Integer;
  tp:TTRANSPACK;
  wst:Integer;
begin
  phyId:='';
  cardId:='';
  balance:=0;
  payCnt:=0;
  if Application.MessageBox('��ȷ��Ҫ����Ȼ�������·��иÿ���',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  if readCardInfo=False then
    Exit;
  WorkView.FieldByName('����').Data.SetInteger(StrToInt(cardId));
  WorkView.FieldByName('������').Data.SetString(phyId);
  WorkView.FieldByName('���״���').Data.SetInteger(payCnt);
  WorkView.FieldByName('��ֵ����').Data.SetInteger(dptCnt);
  WorkView.FieldByName('�����').Data.SetInteger(balance);
  MainRequest.SendCommand;
  if (WorkView.FieldByName('������').Data.AsInteger = 0) then
  begin
    stationId := WorkView.fieldbyname('�ն˱��').Data.AsInteger;
    rBalance := WorkView.fieldbyname('�����').Data.AsInteger;
    rFeeType := WorkView.fieldbyname('�շ����').Data.AsInteger;
    rPwd := WorkView.fieldbyname('������').Data.AsString;
    rEndDate := WorkView.fieldbyname('��Ч��').Data.AsString;
    tradeDate  := WorkView.fieldbyname('ҵ������').Data.AsString;
    tradeTime := WorkView.fieldbyname('ҵ��ʱ��').Data.AsString;
    //rTradeNum := WorkView.fieldbyname('���״���').Data.AsInteger;
    cm:= nil;
    try
      cm := TCM.Create;
      cm.clearallfieldwritemode;
      setOperWriteMode(cm);
      cm.setCardLimitType(IntToStr(rFeeType));
      cm.setDeadLineDate(rEndDate);
      {TODO:���½��״����Ϳ����}
      if maxper=1 then
      begin
        maxPerCount := WorkView.fieldbyname('�����޶�').Data.AsInteger;
        maxPerDay := WorkView.fieldbyname('���޶�').Data.AsInteger;
        cm.setMaxPerCount(IntToStr(maxPerCount));
        cm.setMaxPerDay(IntToStr(maxPerDay));
        //rst := cardManage.SetConsumeLimit(maxPerCount,maxPerDay);
      end;
      st := cm.writeData;
      //���ÿ����
      //�ն˽������к�
      tp.TermSeqno := 1;
      //�ն˱��
      StrCopy(@tp.Termno,PChar(scSiteNo));
      //���׿���
      tp.CardNo := StrToInt(cardId);
      //������
      StrCopy(@tp.CardPhyID,PChar(phyId));
      //��������
      StrCopy(@tp.TransDate,PChar(tradeDate));
      //����ʱ��
      StrCopy(@tp.TransTime,PChar(tradeTime));
      //���׺���
      tp.AftBalance :=  rBalance;
      //����ǰ���
      tp.BefBalance := balance;
      //����ǰ��ֵ����
      tp.DptCardCnt := dptCnt;
      //����ǰ���Ѵ���
      tp.PayCardCnt := payCnt;
      //����ǰ��������
      tp.SubsidyNo := subsidyNo;

      tof := ks_setcardbal(@tp);
      wst := ks_sr_setmoeny(0,1);
      if (st=0) and (tof = 0) and (wst = 0) then
      begin
        cm.beep;
        Context.GetDialogSystem.ShowSuccess('����д����Ϣ�ɹ���');
      end
      else
      begin
        Context.GetDialogSystem.ShowSuccess('����д����Ϣʧ�ܣ�');
      end;
    finally
      cm.Destroy;
    end;
    edtPhyId.Text := phyId;
    edtCardId.Text := cardId;
    edtBalance.Text := FloatToStr(rBalance/100);
    edtEndDate.Text := rEndDate;
    edtFeeType.Text := GetIdObjectName(-43,IntToStr(rFeeType));
    edtPwd.Text := rPwd;
  end
  else
  begin
    getReturn('',WorkView);
    RzStatusPane1.Caption:=WorkView.FieldByName('������Ϣ').Data.AsString;
  end;
end;

function TfaqhCardReRelease.readCardInfo:Boolean;
begin
  Result := False;
  if preReadCard=False then
    Exit;
  //ȡ������
  phyId := readCardOneInfo(CARD_SERI_NO);
  if phyId = '' then
  begin
    Context.GetDialogSystem.ShowMessage('�������к�ʧ�ܣ������°ѿ����õ���д���ϣ�');
    exit;
  end;
  //��ȡ���׿���
  cardId := readCardOneInfo(CARD_NO);
  if cardId = '' then
  begin
    Context.GetDialogSystem.ShowMessage('�����׿���ʧ�ܣ�����úÿ���');
    Exit;
  end;
  try
    balance := StrToInt(readCardOneInfo(CARD_BALANCE));
    payCnt :=  StrToInt(readCardOneInfo(PAY_CARD_CNT));
    dptCnt := StrToInt(readCardOneInfo(DPT_CARD_CNT));
    subsidyNo := StrToInt(readCardOneInfo(PATCH_NO));
  except
    Context.GetDialogSystem.ShowMessage('��������Ϣʧ�ܣ�����úÿ���');
    Exit;
  end;
  Result := True;
end;

initialization
  TUIStdClassFactory.Create('�������ٷ���', TfaqhCardReRelease);
end.
