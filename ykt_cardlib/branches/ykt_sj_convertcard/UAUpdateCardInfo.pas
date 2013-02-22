unit UAUpdateCardInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, WVCommands, RzStatus, RzPanel;

type
  TfaqhUpdateCardInfo = class(TfaqhSimpleQueryTemp)
    btnOK: TImageButton;
    btnReadCardQuery: TImageButton;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    grp3: TGroupBox;
    Label2: TLabel;
    edtcCardNo: TWVEdit;
    edtcPhyId: TWVEdit;
    WVLabel6: TWVLabel;
    edtcStuempNo: TWVEdit;
    WVLabel8: TWVLabel;
    WVLabel11: TWVLabel;
    edtcShowNo: TWVEdit;
    edtcBalance: TWVEdit;
    WVLabel14: TWVLabel;
    WVLabel15: TWVLabel;
    edtcIdCard: TWVEdit;
    WVLabel17: TWVLabel;
    WVLabel18: TWVLabel;
    WVLabel20: TWVLabel;
    edtcBookId: TWVEdit;
    edtcName: TWVEdit;
    edtcEndDate: TWVEdit;
    grp1: TGroupBox;
    Label1: TLabel;
    WVLabel2: TWVLabel;
    WVLabel9: TWVLabel;
    WVLabel7: TWVLabel;
    WVLabel16: TWVLabel;
    WVLabel19: TWVLabel;
    WVLabel10: TWVLabel;
    WVLabel1: TWVLabel;
    WVLabel5: TWVLabel;
    edtCardNo: TWVEdit;
    edtCardID: TWVEdit;
    edtNo: TWVEdit;
    edtIDCard: TWVEdit;
    edtBalance: TWVEdit;
    edtShowCardNo: TWVEdit;
    edtBookID: TWVEdit;
    edtName: TWVEdit;
    edtEndDate: TWVEdit;
    chkmoney: TCheckBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnReadCardQueryClick(Sender: TObject);
    procedure chkmoneyClick(Sender: TObject);
    procedure edtShowCardNoKeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }

    CardKind:Integer;
    DepartNo,sex:string;
    feetype:Integer;                          //�շ����
    tempPCardID:string;                       //��������
    cardPwd:string;                           //������
    cardTreadNum:Integer;                         //���Ľ��״���
    patchNum:Integer;                         //�������κ�

    //���ݴ�ѧ����������
    area_code : string;                       //ԺУ����
    cut_id : Integer;                         //�ͻ�ID��
    certificate_type : string;                //֤������
    people:string;                            //����
    nationality:string;                       //����
    open_card_flag : string;                  //�Ƿ��Ѿ�����,0δ����,1�ѿ���
    card_version : string;                    //�ƿ��汾��
    pub_card_flag:string;                     //����ע���ʶ��
    ser_flag:string;                          //����ע���ʶ��
    pwd_open_flag : string;                   //�������뿪��0����,1δ����

    Function readCardInfo:Boolean;
    procedure edtEnabledF;                    //ʹ�༭��Ϊ������
    procedure edtEnabledT;                    //ʹ�༭��Ϊ����
    procedure resultQuery;                    //��ѯ���
    procedure clearEdt;                       //��ձ༭������
  public
    sOperID,sOperPWD,sSign:string;
    imoney:Integer;
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhUpdateCardInfo: TfaqhUpdateCardInfo;
  CardID: string;

implementation

uses KsFrameworks, 
  KSClientConsts, UtCardDll;

{$R *.DFM}

procedure TfaqhUpdateCardInfo.Init;
begin
  inherited;
  WorkView.FieldByName('����ʶ').DefaultValue := 0;
  btnReadCardQuery.caption:='&I������ѯ';
  btnQuery.caption:='&Q������ѯ';
  edtEnabledF;
  WorkView.Reset;
  btnok.Enabled := false;
  imoney:=2;
end;

procedure TfaqhUpdateCardInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhUpdateCardInfo.btnQueryClick(Sender: TObject);
begin
  clearEdt;
  inherited;
  try
    resultQuery;
    edtEnabledT;
  except
  end;
end;

procedure TfaqhUpdateCardInfo.btnOKClick(Sender: TObject);
var
  OperatorNoName:string;
  CusName: string;
  DutyID: string;
  ReadBookCardID: string;
  CertifiNo: string;
  SOWNo: string;
  sShowCardNo: string;
  FDeadLineDate: string;
  PCardID: string;
  CardInfo: TPublishCardMes;
  CardManage: TCardManage;
  cardmoney:LongInt;
  st:LongInt;
begin
  if not SmartCardPortStatus then
  begin
    Context.GetDialogSystem.ShowWarning('���ȴ򿪴��ڣ�');
    Exit;
  end;
  if not SmartCardAuthStatus then
  begin
    Context.GetDialogSystem.ShowWarning('����Ϊ��д����Ȩ��');
    Exit;
  end;

  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('û�����ݣ��޷����иò�����');
    Exit;
  end;
  {
  if (Trim(edtShowCardNo.Text)<>'') and (Length(Trim(edtShowCardNo.Text))<>10) then
  begin
    Context.GetDialogSystem.ShowMessage('��������Ч����ʾ���ţ�');
    Exit;
  end;
  }
  //���¶�ȡ�����ţ��ж��Ƿ��Ҫ���µ�������һ��
  CardManage := TCardManage.Create;
  if CardManage.ReadCardPhyID(PCardID)=0 then
  begin
    if PCardID<>trim(tempPCardID) then
    begin
      Context.GetDialogSystem.ShowMessage('����ʱ��ʹ��ͬһ�ſ���');
      CardManage.Destroy;
      Exit;
    end;
  end;

  //ȡ����Ա�ţ�����еķ���
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;

  WorkView1.FieldByName('����').Data.SetInteger(strtoint(edtcCardNo.text));
  WorkView1.FieldByName('������').Data.Setstring(edtCardID.Text);
  WorkView1.FieldByName('��ʾ����').Data.Setstring(edtShowCardNo.text);
  WorkView1.FieldByName('����Ա��').Data.Setstring(OperatorNoName);
  WorkView1.FieldByName('����վ��').Data.SetInteger(SmartCardSubSystemNo);
  WorkView1.FieldByName('��������').Data.Setstring(edtEndDate.Text);
  WorkView1.FieldByName('����Ա��').Data.Setstring('0');
  WorkView1.FieldByName('����Ա����').Data.Setstring('0');
  WorkView1.FieldByName('�Ƿ�д�����').Data.setinteger(imoney);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('������').Data.AsInteger=0 then
  begin
    //��ʹ�ý�ֹ����
    FDeadLineDate := edtEndDate.text;
    CusName := edtName.Text;
    //ְ����� DutyID
    DutyID:='0';
    //ͼ��֤��
    ReadBookCardID := edtBookID.Text;
    //���֤��
    CertifiNo := edtIDCard.text;
    //ѧ����
    SOWNo := edtNo.text;
    //��ʾ����
    sshowCardNo := edtShowCardNo.text;
    //���н��
    if trim(edtbalance.Text) = '' then
      cardmoney:=0
    else
      cardmoney := round(strtofloat(edtbalance.text)*100);
    ShowWaiting(SWaitingOperation);

    //����Ϣд�뿨�У�����dll����
    strcopy(@CardInfo.DeadLineDate, PChar(FDeadLineDate));
    CardInfo.CardRightType := feetype;                              //�շ����
    strcopy(@CardInfo.CardNo, PChar(edtCardNo.Text));
    //showmessage(CardInfo.CardNo);
    strcopy(@CardInfo.ucName, PChar(CusName));
    strcopy(@CardInfo.ucDutyNo, PChar(DutyID));
    strcopy(@CardInfo.ucCertificateNo, PChar(CertifiNo));           //���֤��
    strcopy(@CardInfo.ucDepartmentNo, PChar(DepartNo));
    strcopy(@CardInfo.ucLibraryNo, PChar(ReadBookCardID));
    strcopy(@CardInfo.ucSexNo, PChar(sex));                         //ͼ��֤��
    strcopy(@CardInfo.ucIdentifyNo, PChar(IntToStr(CardKind)));     //�ͻ����  cardPwd
    strcopy(@CardInfo.ucCardNo, PChar(SOWNo));
    strcopy(@CardInfo.ucPwd, PChar(cardPwd));
    //ShowMessage(CardInfo.ucPwd);

    strcopy(@CardInfo.ShowCardNo, PChar(sshowCardNo));
    ///showmessage(CardInfo.ShowCardNo);
    CardInfo.cut_id := cut_id;                                       //�ͻ�ID��
    strcopy(@CardInfo.area_code, PChar(area_code));                  //ԺУ����
    strcopy(@CardInfo.certificate_type, PChar(certificate_type));    //֤������
    strcopy(@CardInfo.people, PChar(people));                        //����
    strcopy(@CardInfo.nationality, PChar(nationality));              //����
    strcopy(@CardInfo.card_version, PChar(card_version));            //�ƿ��汾��
    strcopy(@CardInfo.pub_card_flag, PChar(pub_card_flag));          //����ע���ʶ��
    strcopy(@CardInfo.ser_flag, PChar(ser_flag));                    //����ע���ʶ��
    try
      if chkmoney.checked then
      begin
        st := CardManage.UpdateCardBasicInfo(CardInfo);
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('���¿���Ϣʧ��--'+inttostr(st));
          CardManage.Destroy;
          exit;
        end;
        //ShowMessage(IntToStr(patchNum));
        if CardManage.UpdateMoneyAndTxCnt(Cardmoney,cardTreadNum,patchNum)<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('���¿����ʧ�ܣ�');
          CardManage.Destroy;
          exit;
        end;
      end
      else
      begin
        st := CardManage.UpdateCardBasicInfo(CardInfo);
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('���¿���Ϣʧ��--'+inttostr(st));
          CardManage.Destroy;
          exit;
        end;
      end;
      CardManage.ControlBuzzer;
      edtEnabledF;
      clearEdt;
      Context.GetDialogSystem.ShowSuccess('���¿���Ϣ�ɹ���');
    finally
      CloseWaiting;
      btnok.Enabled := false;
    end;
  end
  else
  begin
    getreturn('',workview1);
  end;
  CardManage.Destroy;
end;

procedure TfaqhUpdateCardInfo.btnReadCardQueryClick(Sender: TObject);
//var
  //CardManage: TCardManage;
  //ResInt: SmallInt;
  //cardNo:string;
begin
  if PrepareReadCardInfo=False then
    Exit;
  if readCardInfo=False then
    Exit;
  {
  CardManage := TCardManage.Create;
  //��ȡ���׿���
  ResInt := CardManage.ReadExCardID(CardID);
  if ResInt <> 0 then
    edtCardNo.Text := '0'
  else
    edtCardNo.Text := CardID;
  else
  begin
    if CardID='0' then
    begin
      Context.GetDialogSystem.ShowMessage('�ÿ�û�з��У����ȷ�����');
      CardManage.Destroy;
      Exit;
    end
    else
    begin
      WVEdit1.Text := CardID;
      CardManage.Destroy;
    end;
  end;
  }
  //inherited;
  WorkView.FieldByName('����ʶ').Data.SetInteger(StrToInt(edtcCardNo.Text));
  WorkView.FieldByName('������').Data.SetString(edtcPhyId.Text);
  MainRequest.SendCommand;
  if WorkView.fieldbyname('������').data.asinteger<>0 then
  begin
    getreturn('',WorkView);
    exit;
  end;
  try
    resultQuery;
    edtEnabledT;
    btnok.enabled := true;
  except
  end;
end;

Function TfaqhUpdateCardInfo.readCardInfo():Boolean;
var
  CardManage: TCardManage;
  PCM: TPublishCardMes;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  phycardid,cardNo:string;
  st : longint;
begin
  Result := True;
  CardManage := TCardManage.Create;
  if CardManage.ReadCardPhyID(phycardid) <> 0 then
  begin
    context.GetDialogSystem.ShowMessage('��������ʧ�ܣ��ÿ��Ѿ��𻵣�');
    CardManage.Destroy;
    Result:=False;
    Exit;
  end;
  //��ȡ���׿���

  if CardManage.ReadExCardID(cardNo) <> 0 then
  begin
    edtcCardNo.Text := '0';
    //��ȡ�������ţ���ʼ��ʼ���ÿ�
    st :=cardmanage.InitCard('');
    if st<>0 then
    begin
      showmessage('��ʼ����ʧ�ܣ������½��ж�����ѯ����������ܳ�ʼ���ÿ�����ÿ��Ѿ��𻵣�');
      exit;
    end;
  end
  else
    edtcCardNo.Text := cardNo;
    
  //��ȡ������Ϣ
  if CardManage.ReadCardInfo(PCM) = 0 then
  begin
    edtcName.Text := PCM.ucName;                                  //����
    edtcPhyId.Text := phycardid;                                  //������
    edtcIdCard.Text := PCM.ucCertificateNo;                       //���֤��
    edtcStuempNo.Text := PCM.ucCardNo;                            //ѧ����
    edtcBookId.Text := PCM.ucLibraryNo;                           //ͼ��֤��
    edtcEndDate.Text := PCM.DeadLineDate;                         //��������
    edtcShowNo.Text := Copy(PCM.ShowCardNo,1,10);                 //��ʾ����

    open_card_flag := Copy(PCM.open_card_flag,1,1);               //�Ƿ��Ѿ�����,0δ����,1�ѿ���
    card_version := Copy(PCM.card_version,1,1);                   //�ƿ��汾��
    pub_card_flag:=Copy(PCM.pub_card_flag,1,10);                  //����ע���ʶ��
    ser_flag:=Copy(PCM.ser_flag,1,10);                            //����ע���ʶ��
    pwd_open_flag := Copy(PCM.pwd_open_flag,1,1);                 //�������뿪��0����,1δ����

    if CardManage.ReadCardConsumeInfo(LPI, nPacketNo)=True then
    begin
      edtcBalance.Text := format('%f', [LPI.RemainMoney / 100.0]);
    end
    else
    begin
      Context.GetDialogSystem.ShowWarning('��ȡǮ����Ϣʧ�ܣ�');
      Result := False;
      Exit;
    end;
    CardManage.Destroy;
  end
  else
  begin
    Context.GetDialogSystem.ShowWarning('��ȡ����Ϣ����ʧ�ܣ�');
    CardManage.Destroy;
    Result:=False;
  end;
end;
procedure TfaqhUpdateCardInfo.edtEnabledF;
begin
  edtCardID.Enabled:=False;
  edtCardID.Color:=clScrollBar;
end;

procedure TfaqhUpdateCardInfo.edtEnabledT;
begin
  edtShowCardNo.Enabled:=True;
  edtEndDate.Enabled:=True;
  edtshowCardNo.Color:=clwhite;
  edtEndDate.Color:=clwhite;
end;

procedure TfaqhUpdateCardInfo.resultQuery;
var
  tempDataSet: TDataSet;
begin
  tempDataSet := WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet;
  //���׿���
  edtCardNo.Text := tempDataSet.FieldByName('lvol0').AsString;
  //��ʹ�ý�ֹ����
  edtEndDate.Text := tempDataSet.FieldByName('sdate0').AsString;
  //����
  edtName.Text := tempDataSet.FieldByName('sname').AsString;
  //ͼ��֤��
  edtBookID.text := tempDataSet.FieldByName('sname2').AsString;
  //���֤��
  edtIDCard.Text := tempDataSet.FieldByName('scust_auth2').AsString;
  //ѧ����
  edtNo.Text := tempDataSet.FieldByName('scust_limit').AsString;
  //��ʾ����
  edtShowCardNo.Text := tempDataSet.FieldByName('scust_no').AsString;
  //�����
  edtBalance.Text := tempDataSet.FieldByName('damt0').AsString;
  //������
  edtCardID.Text := tempDataSet.FieldByName('sbank_acc').AsString;
  //�ͻ����
  cardkind:= tempDataSet.FieldByName('lvol1').asinteger;
  //�շ����
  feetype:=tempDataSet.FieldByName('lvol5').asinteger;
  //���ű��
  DepartNo := tempDataSet.FieldByName('sserial0').AsString;
  //�Ա�
  Sex := tempDataSet.FieldByName('scust_type').AsString;
  //������
  tempPCardID := tempDataSet.fieldbyname('sbank_acc').AsString;
  
  //ԺУ����
  area_code := tempDataSet.fieldbyname('sbranch_code0').AsString;
  //�ͻ�ID��
  cut_id := tempDataSet.fieldbyname('sholder_ac_no').AsInteger;
  //֤������
  certificate_type := tempDataSet.fieldbyname('sstat_type').AsString;
  //����
  people:=tempDataSet.fieldbyname('sstat_type2').AsString;
  //����
  nationality:=tempDataSet.fieldbyname('snation_code').AsString;
  //������
  cardPwd :=  tempDataSet.fieldbyname('sbank_acc2').AsString;
  //�����״���
  cardTreadNum := tempDataSet.fieldbyname('lvol10').AsInteger;
  //�������κ�
  patchNum := tempDataSet.fieldbyname('lvol11').AsInteger;
end;

procedure TfaqhUpdateCardInfo.clearEdt;
var
  i:Integer;
begin
  chkmoney.Checked:=False;
  for i := 0 to UIPanel1.ControlCount-1 do
    if (UIPanel1.Controls[i] is TWVEdit)and (TWVEdit(UIPanel1.Controls[i]).tag<>15) then
      TWVEdit(UIPanel1.Controls[i]).Text:='';
end;

procedure TfaqhUpdateCardInfo.chkmoneyClick(Sender: TObject);
begin
  if chkmoney.Checked then
    imoney := 1
  else
    imoney := 2;
end;

procedure TfaqhUpdateCardInfo.edtShowCardNoKeyPress(Sender: TObject;
  var Key: Char);
begin
  //inherited;
  if inputNum(Key)=False then
    Key := #0;
end;

initialization
  TUIStdClassFactory.Create('����Ϣ����', TfaqhUpdateCardInfo);

end.
