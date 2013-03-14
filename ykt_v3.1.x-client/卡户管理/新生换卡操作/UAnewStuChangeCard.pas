unit UAnewStuChangeCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzStatus, RzPanel, Buttons, UtCardDll, UIncrementComboBox;

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
    PCM: TPublishCardMes;
    { Private declarations }
    //operType,oPhyId,nPhyId,nShowCardNo,nEndDate,operDate:string;
    //oCardNo,oCardBalance,oTradeNum,seriNo,stationId:integer

    //procedure setWVvalues(operType,oPhyId,nPhyId,nShowCardNo,nEndDate,operDate:string;
    //  oCardNo,oCardBalance,oTradeNum,seriNo,stationId:integer);
    procedure replaceNewCard(phyCardId:string;cardNo:Integer;operType:string);//������������Ϣ
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhnewStuChangeCard: TfaqhnewStuChangeCard;

implementation

uses KsFrameworks, KSClientConsts;

{$R *.DFM}

procedure TfaqhnewStuChangeCard.Init;
begin
  inherited;
  edtEndDate.Text:=FormatDateTime('yyyymmdd',Date()+1461);
  {
  btnQuery.Caption:='������ѯ';
  btnPrint.Caption:='�� ��';
  btnReadCardQuery.Caption:='������ѯ';
  btnPatchCard.Caption:='��������д';
  }
end;

procedure TfaqhnewStuChangeCard.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhnewStuChangeCard.btnPrintClick(Sender: TObject);
var
  nPacketNo: smallint;
  LPI: LOOPPURSEINFO;
  cardManage:TCardManage;
  Tof:Boolean;

  //������Ϣ
  rmoney:Integer;
  rTrade:Integer;
  rPatchNo:Integer;
  PCardId:string;

  cardNo:string;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowWarning('û�����ݣ��޷����д˲�����');
    Exit;
  end;

  //������������Ϣ
  cardManage := nil;
  try
    cardManage:=TCardManage.Create();
    //ȡ������
    if CardManage.ReadCardPhyID(PCardID) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('�������к�ʧ�ܣ������°ѿ����õ���д���ϣ�');
      exit;
    end;

    TOF := CardManage.ReadCardConsumeInfo(LPI, nPacketNo); //������������Ϣ
    if TOF = false then
    begin
      Context.GetDialogSystem.ShowWarning('���û���������Ϣʧ�ܣ�');
      Exit;
    end
    else
    begin
      rmoney:=LPI.RemainMoney;
      rTrade:=LPI.DealTimes;
      rPatchNo := LPI.DealTimes_CurDay;
    end;
    //�Ͽ��Ŀ���
    cardNo:=readCardNo;

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
    //operType,oPhyId,nPhyId,nShowCardNo,nEndDate,operDate:string;
    //oCardNo,oCardBalance,oTradeNum,seriNo,stationId:integer
    WVRequestOK.SendCommand;
    if WorkViewOK.FieldByName('������').Data.AsInteger<>0 then
    begin
      getReturn('��տ�ʧ��--',WorkViewOK);
      RzStatusPane1.Caption:=WorkViewOK.FieldByName('������Ϣ').Data.AsString;
      Exit;
    end;
    //���������ʱ����Ϣ������ɹ������Ϣ�͵���̨����̨����ոÿ���־д��
    if cardManage.ClearCard<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('�ɿ����������ʧ�ܣ�����ÿ��Ƿ���ã�');
      Exit;
    end
    else
    begin
      cardManage.ControlBuzzer;
      Context.GetDialogSystem.ShowMessage('�ɿ�����������ɹ������Ȱ�Ҫ�����Ŀ����úã�');

      //��ʼ�ѿ���Ϣд���¿���ȥ
      replaceNewCard(PCardID,StrToInt(cardNo),'C');
    end;
  finally
    cardManage.Destroy;
  end;
end;

procedure TfaqhnewStuChangeCard.btnReadCardQueryClick(Sender: TObject);
begin
  //FCurrentCardNo := readCardNo;
  edtCardNo.Text:= readCardNo;
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
  cardManage:TCardManage;
  newphyCardNo:string;
  inShowCardNo:string;

  tradeCardNo:Integer;      //���׿���
  showCardNo:string;        //��ʾ����
  tradeNum:Integer;         //���״���
  cardEndDate:string;       //��ʹ�ý�������
  limitType:Integer;        //��ʹ��Ȩ��
  custType:Integer;         //�ͻ����
  custName:string;          //�ͻ�����
  dutyNo:string;            //ְ�����
  cardID:string;            //���֤��
  depNo:string;             //���Ŵ���
  bookID:string;            //ͼ��֤��
  sex:string;               //�Ա�
  ID:string;                //ѧ����
  cardBalance:Integer;      //�����
  cardPWD:string;           //������
  isFormation:Char;         //�Ƿ��ʽ����һ����
  sOperDate:string;         //��������
  stationId:Integer;        //�ն˱��
  backTradeID:Integer;      //��̨������ˮ��
  maxPerCount:Integer;      //�����޶�
  maxPerDay:Integer;        //���޶�
  re,ret:Integer;
  ResInt:Integer;
  patchNo:Integer;
  sNewCardNo:string;

  i:Integer;
  tryNum:Integer;
  tmpPhyId:string;
begin
  if PrepareReadCardInfo=False then
    Exit;
  re := 0;
  ResInt := 0;
  stationId := 0;
  backTradeID := 0;
  sNewCardNo := '0';
  cardManage := nil;
  tryNum := 2;
  //����Ƿ��п����޿����˳�
  for i := 1 to tryNum do
  begin
    if StrToInt(readCardNo)=0 then
      Break
    else
      Context.GetDialogSystem.ShowMessage('�ÿ��Ŀ����Ѿ����ڣ������һ���¿���');
  end;

  try
    cardManage := TCardManage.Create();
    if CardManage.ReadCardPhyID(newphyCardNo) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('�������к�ʧ�ܣ����ȳ���������Ȼ��׼�����¿����²�����');
      Exit;
    end;
    inShowCardNo := readShowCarNo;
    if inShowCardNo='-1' then
      Exit;
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
        dutyNo:='';
        cardID:=WorkViewOK.fieldbyname('֤������').Data.AsString;
        depNo:=WorkViewOK.fieldbyname('���Ŵ���').Data.AsString;
        bookID:='';
        sex:=WorkViewOK.fieldbyname('�Ա�').Data.AsString;
        ID:=WorkViewOK.fieldbyname('ѧ����').Data.AsString;
        cardBalance:=WorkViewOK.fieldbyname('����ֵ').Data.AsInteger;
        cardPWD:=WorkViewOK.fieldbyname('������').Data.AsString;
        isFormation := Char('N');

        backTradeID:=WorkViewOK.fieldbyname('��ˮ��').Data.AsInteger;
        sOperDate := WorkViewOK.fieldbyname('ҵ������').Data.AsString;
        stationId := WorkViewOK.fieldbyname('�ն˱��').Data.AsInteger;
        tradeNum := WorkViewOK.fieldbyname('���״���').Data.AsInteger;
        patchNo := WorkViewOK.fieldbyname('�������κ�').Data.AsInteger;
      except
        on ex:Exception do
        begin
          Context.GetDialogSystem.ShowMessage('��̨������������--'+ex.Message);
          Exit;
        end;
      end;
      strcopy(@PCM.CardNo, PChar(IntToStr(tradeCardNo)));         //���׿���
      strcopy(@PCM.ShowCardNo, PChar(showCardNo));                //��ʾ����
      strcopy(@PCM.DeadLineDate, PChar(cardEndDate));             //��ֹ����
      PCM.CardRightType := limitType;                             //�շ�����
      strcopy(@PCM.ucIdentifyNo, PChar(IntToStr(custType)));      //�ͻ�����
      strcopy(@PCM.ucName, PChar(custName));                      //����
      strcopy(@PCM.ucDutyNo, PChar(dutyNo));                      //ְ��
      strcopy(@PCM.ucCertificateNo, PChar(cardID));               //���֤��
      strcopy(@PCM.ucDepartmentNo, PChar(depNo));                 //����
      strcopy(@PCM.ucLibraryNo, PChar(bookID));                   //ͼ��֤��
      strcopy(@PCM.ucSexNo, PChar(sex));                          //�Ա�
      strcopy(@PCM.ucCardNo, PChar(ID));                          //ѧ����
      //PCM.Money := cardBalance;                                   //�����
      strcopy(@PCM.ucPwd, PChar(cardPWD));                        //������
      PCM.isFormat := isFormation;                                //�Ƿ��ʽ����һ����

      re := CardManage.PublishACard(PCM);
      //���õ��������޶���������޶�
      if maxper=1 then
      begin
        maxPerCount := WorkViewOK.fieldbyname('�����޶�').Data.AsInteger;
        maxPerDay := WorkViewOK.fieldbyname('���޶�').Data.AsInteger;
        ret := cardManage.SetConsumeLimit(maxPerCount,maxPerDay);
      end;
      //д�������κ�
      if cardManage.changePatchNo(patchNo)<>0 then
        Context.GetDialogSystem.ShowMessage('���������κ�д��ʧ�ܣ��뵽���¿���Ϣ�и��²������κţ�');
      //���ÿ����״����������
      if CardManage.PacketSetMoney2(cardBalance,TradeNum)<>0 then
        Context.GetDialogSystem.ShowMessage('�����״���д��ʧ�ܣ��뵽���¿���Ϣ�и��¿����״�����');

      //�����ɹ��������ųɹ�����ȡ���Ŵ������ȷ���ÿ��Ѿ����гɹ����������·���
      ResInt := CardManage.ReadExCardID(sNewCardNo);
      if ((re <> 0) or (ResInt<>0) or (StrToInt(sNewCardNo)=0))or(ret<>0) then
      begin
        if Application.MessageBox(PChar('д��ʧ�ܣ���ʹ��ͬһ�ſ�����ȷ���õ���д���ϣ���Ҫ����һ����'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
          Exit;
        //���������ţ�����ǰ�������űȽϣ���һ������
        if CardManage.ReadCardPhyID(tmpPhyId) <> 0 then
        begin
          Context.GetDialogSystem.ShowMessage('����������ʧ�ܣ���Ѹÿ��ȳ���������Ȼ���������������ף�');
          Exit;
        end;
        if tmpPhyId<>newphyCardNo then
        begin
          Context.GetDialogSystem.ShowMessage('�͸ղŷ��õĲ���ͬһ�ſ�����Ѹÿ��ȳ���������Ȼ���������������ף�');
          Exit;
        end;
        //д�����״���
        if CardManage.changeTradeNum(tradeNum)<>0 then
        begin

        end;
        //����дһ�ο�
        re := CardManage.PublishACard(PCM);
        //���õ��������޶���������޶�
        if maxper=1 then
        begin
          maxPerCount := WorkViewOK.fieldbyname('�����޶�').Data.AsInteger;
          maxPerDay := WorkViewOK.fieldbyname('���޶�').Data.AsInteger;
          ret := cardManage.SetConsumeLimit(maxPerCount,maxPerDay);
        end;
        //�����ɹ��������ųɹ�����ȡ���Ŵ������ȷ���ÿ��Ѿ����гɹ����������·���
        ResInt := CardManage.ReadExCardID(sNewCardNo);
        //д�������κ�
        if cardManage.changePatchNo(patchNo)<>0 then
          Context.GetDialogSystem.ShowMessage('���������κ�д��ʧ�ܣ��뵽���¿���Ϣ�и��²������κţ�');
        //���ÿ����״����������
        if CardManage.PacketSetMoney2(cardBalance,TradeNum)<>0 then
          Context.GetDialogSystem.ShowMessage('�����״���д��ʧ�ܣ��뵽���¿���Ϣ�и��¿����״�����');

      end;
    end
    else
    begin
      getReturn('',WorkViewOK);
      RzStatusPane1.Caption:=WorkViewOK.FieldByName('������Ϣ').Data.AsString;
    end;
  finally
    cardManage.Destroy;
    if ((re = 0) and (ResInt=0) and (StrToInt(sNewCardNo)>0))and (ret=0) then
    begin
      if operType='D' then
        Context.GetDialogSystem.ShowMessage('�ÿ��Ѿ����������ɹ�  '+WorkViewOK.FieldByName('������Ϣ').Data.AsString)
      else
        Context.GetDialogSystem.ShowMessage('�ÿ��Ѿ������ɹ�  '+WorkViewOK.FieldByName('������Ϣ').Data.AsString);
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
      //if WorkViewOK.FieldByName('������').Data.AsInteger<>0 then
        //Context.GetDialogSystem.ShowMessage('��������ʧ��--'+WorkViewOK.FieldByName('������Ϣ').Data.AsString);
    end;

  end;
end;

procedure TfaqhnewStuChangeCard.btnPatchCardClick(Sender: TObject);
var
  tmpdata:TDataSet;
  phyCardId,tmpPhyId:string;
  cardNo:Integer;
  cardManage:TCardManage;
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
  if PrepareReadCardInfo=False then
    Exit;
  //������������Ϣ
  cardManage := nil;
  try
    cardManage:=TCardManage.Create();
    //ȡ������
    if CardManage.ReadCardPhyID(tmpPhyId) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('�������к�ʧ�ܣ������°ѿ����õ���д���ϣ�');
      exit;
    end;
    if tmpPhyId<>phyCardId then
    begin
      Context.GetDialogSystem.ShowMessage('Ҫ�����Ŀ��Ͳ�ѯ���Ŀ�����ͬһ�ſ���');
      Exit;
    end;
  finally
    cardManage.Destroy;
  end;
  //ShowMessage(IntToStr(cardNo));
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