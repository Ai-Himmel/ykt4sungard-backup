unit UACardReRelease;

interface
              
uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls,
  UICtrls, WVCtrls, Mask, UtCardDll, SmartCardCommon,Db,
  RzPanel, RzStatus, RzButton, RzRadChk, Buttons, UIncrementComboBox,
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
    tradeNum:Integer;

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
end;

procedure TfaqhCardReRelease.btnReleaseCardClick(Sender: TObject);
var
  //rCardId:Integer;
  rBalance:Integer;
  rFeeType:Integer;
  rPwd:string;
  rEndDate:string;
  rTradeNum:Integer;
  cardManage: TCardManage;
  CardInfo: TPublishCardMes;
  perCoutMoney,perDayMoney:Integer;
begin
  phyId:='';
  cardId:='';
  balance:=0;
  tradeNum:=0;
  if Application.MessageBox('��ȷ��Ҫ����Ȼ�������·��иÿ���',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  if readCardInfo=False then
    Exit;
  WorkView.FieldByName('����').Data.SetInteger(StrToInt(cardId));
  WorkView.FieldByName('������').Data.SetString(phyId);
  WorkView.FieldByName('���״���').Data.SetInteger(tradeNum);
  WorkView.FieldByName('�����').Data.SetInteger(balance);
  MainRequest.SendCommand;
  if (WorkView.FieldByName('������').Data.AsInteger = 0) then
  begin
    //rCardId := WorkView.fieldbyname('����').Data.AsInteger;
    rBalance := WorkView.fieldbyname('�����').Data.AsInteger;
    rFeeType := WorkView.fieldbyname('�շ����').Data.AsInteger;
    rPwd := WorkView.fieldbyname('������').Data.AsString;
    rEndDate := WorkView.fieldbyname('��Ч��').Data.AsString;
    rTradeNum := WorkView.fieldbyname('���״���').Data.AsInteger;
    cardManage := nil;
    try
      cardManage := TCardManage.Create;
      strcopy(@CardInfo.DeadLineDate, PChar(rEndDate)); //��������*
      CardInfo.CardRightType := rFeeType;               //�շ����*
      strcopy(@CardInfo.ucPwd, PChar(rPwd));            //����*
      strcopy(@CardInfo.ucName, PChar(''));             //�ͻ�����
      strcopy(@CardInfo.ucDutyNo, PChar(''));           //ְλ����
      strcopy(@CardInfo.ucCertificateNo, PChar(''));    //���֤��
      strcopy(@CardInfo.ucDepartmentNo, PChar(''));     //���Ŵ���
      strcopy(@CardInfo.ucLibraryNo, PChar(''));        //ͼ��֤��
      strcopy(@CardInfo.ucSexNo, PChar(''));            //�Ա�
      strcopy(@CardInfo.ucIdentifyNo, PChar(''));       //�ͻ����
      strcopy(@CardInfo.ucCardNo, PChar(''));           //ѧ����
      //ShowMessage(CardInfo.ucPwd);
      //strcopy(@CardInfo.ShowCardNo, PChar(sshowCardNo));//��ʾ����
      if CardManage.UpdateCardBasicInfo(CardInfo)<>0 then
      begin
        Context.GetDialogSystem.ShowWarning('д����Ϣʧ�ܣ���źÿ�������ִ�иò�����');
        exit;
      end;
      if (CardManage.ChangeCardPsw(rPwd))<>0 then
      begin
        Context.GetDialogSystem.ShowWarning('���¿�����ʧ�ܣ���źÿ������²�����');
        exit;
      end;

      if CardManage.packetSetMoneyAndChk(inttostr(rBalance),rBalance)<>0 then
      begin
        Context.GetDialogSystem.ShowWarning('д�����ʧ�ܣ���źÿ�������ִ�иò�����');
        exit;
      end;

      if cardManage.changeTradeNum(rTradeNum)<>0 then
      begin
        Context.GetDialogSystem.ShowWarning('���¿����״���ʧ�ܣ���źÿ�������ִ�иò�����');
        exit;
      end;
      //���õ��������޶���������޶�
      if maxper=1 then
      begin
        perCoutMoney := WorkView.fieldbyname('�����޶�').Data.AsInteger;
        perDayMoney := WorkView.fieldbyname('���޶�').Data.AsInteger;
        if cardManage.SetConsumeLimit(perCoutMoney,perDayMoney)<>0 then
        begin
          Context.GetDialogSystem.ShowMessage('���¿������޶�͵����޶�ʧ��,�����²���!');
          Exit;
        end;
      end;

      edtPhyId.Text := phyId;
      edtCardId.Text := cardId;
      edtBalance.Text := FloatToStr(rBalance/100);
      edtEndDate.Text := rEndDate;
      edtFeeType.Text := GetIdObjectName(-43,IntToStr(rFeeType));
      edtPwd.Text := rPwd;

      CardManage.ControlBuzzer;
      Context.GetDialogSystem.ShowSuccess('����д����Ϣ�ɹ���');
    finally
      cardManage.Destroy;
    end;
  end
  else
  begin
    getReturn('',WorkView);
    RzStatusPane1.Caption:=WorkView.FieldByName('������Ϣ').Data.AsString;
  end;
end;

function TfaqhCardReRelease.readCardInfo:Boolean;
var
  cardManage: TCardManage;
  LPI: LOOPPURSEINFO;
begin
  Result := False;
  if PrepareReadCardInfo=False then
    Exit;
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    //ȡ������
    if CardManage.ReadCardPhyID(phyId) <> 0 then
    begin
      ShowMessage('�������к�ʧ�ܣ������°ѿ����õ���д���ϣ�');
      exit;
    end;
    //��ȡ���׿���
    if CardManage.ReadExCardID(cardId) <> 0 then
    begin
      ShowMessage('�����׿���ʧ�ܣ�����úÿ���');
      Exit;
    end;
    if CardManage.ReadCardConsumeInfo(LPI, 0)=False then
    begin
      ShowMessage('���û���������Ϣʧ�ܣ�');
      Exit;
    end
    else
    begin
      balance := StrToInt(format('%d', [LPI.RemainMoney]));
      tradeNum := StrToInt(format('%d', [LPI.DealTimes]));
    end;
    Result := True;
  finally
    cardManage.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('�������ٷ���', TfaqhCardReRelease);
end.
