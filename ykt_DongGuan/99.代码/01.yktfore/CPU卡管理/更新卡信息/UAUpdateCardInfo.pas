unit UAUpdateCardInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, WVCommands, RzStatus, RzPanel, RzEdit, RzButton, RzRadChk,
  Buttons, UIncrementComboBox,CardDll;

type
  TfaqhUpdateCardInfo = class(TfaqhSimpleQueryTemp)
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    btnReadCardQuery: TBitBtn;
    btnOK: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    grpCardInfo: TGroupBox;
    rzstspn1: TRzStatusPane;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    RzStatusPane7: TRzStatusPane;
    RzStatusPane8: TRzStatusPane;
    RzStatusPane9: TRzStatusPane;
    RzStatusPane20: TRzStatusPane;
    RzStatusPane21: TRzStatusPane;
    RzStatusPane22: TRzStatusPane;
    RzStatusPane23: TRzStatusPane;
    RzStatusPane28: TRzStatusPane;
    edtcCardNo: TRzEdit;
    edtcPhyId: TRzEdit;
    edtcStuempNo: TRzEdit;
    edtcShowNo: TRzEdit;
    edtcBalance: TRzEdit;
    edtcIdCard: TRzEdit;
    edtcName: TRzEdit;
    edtcEndDate: TRzEdit;
    edtCCustType: TRzEdit;
    edtCFeeType: TRzEdit;
    edtCDept: TRzEdit;
    edtCSex: TRzEdit;
    edtCardDptNum: TRzEdit;
    grpLibInfo: TGroupBox;
    RzStatusPane11: TRzStatusPane;
    RzStatusPane12: TRzStatusPane;
    RzStatusPane13: TRzStatusPane;
    RzStatusPane14: TRzStatusPane;
    RzStatusPane15: TRzStatusPane;
    RzStatusPane16: TRzStatusPane;
    RzStatusPane17: TRzStatusPane;
    RzStatusPane18: TRzStatusPane;
    RzStatusPane24: TRzStatusPane;
    RzStatusPane25: TRzStatusPane;
    RzStatusPane26: TRzStatusPane;
    RzStatusPane27: TRzStatusPane;
    RzStatusPane19: TRzStatusPane;
    RzStatusPane29: TRzStatusPane;
    edtCardNo: TRzEdit;
    edtPhyID: TRzEdit;
    edtNo: TRzEdit;
    edtIDCard: TRzEdit;
    edtBalance: TRzEdit;
    edtShowCardNo: TRzEdit;
    edtName: TRzEdit;
    edtEndDate: TRzEdit;
    edtCustType: TRzEdit;
    edtFeeType: TRzEdit;
    edtDept: TRzEdit;
    edtSex: TRzEdit;
    cbbRType: TWVComboBox;
    edtDptCnt: TRzEdit;
    RzStatusPane10: TRzStatusPane;
    edtCPatchNo: TRzEdit;
    RzStatusPane30: TRzStatusPane;
    edtPatchNo: TRzEdit;
    RzStatusPane31: TRzStatusPane;
    edtMaxcPerCount: TRzEdit;
    RzStatusPane32: TRzStatusPane;
    edtcMaxPerDay: TRzEdit;
    edtMaxPercount: TRzEdit;
    RzStatusPane33: TRzStatusPane;
    RzStatusPane34: TRzStatusPane;
    edtMaxPerDay: TRzEdit;
    rzstspn2: TRzStatusPane;
    edtCCertType: TRzEdit;
    rzstspn3: TRzStatusPane;
    edtCertType: TRzEdit;
    rzstspn4: TRzStatusPane;
    edtCPayCnt: TRzEdit;
    rzstspn5: TRzStatusPane;
    edtPayCnt: TRzEdit;
    imgPhoto: TImage;
    procedure btnOKClick(Sender: TObject);
    procedure btnReadCardQueryClick(Sender: TObject);
    procedure edtShowCardNoKeyPress(Sender: TObject; var Key: Char);
    procedure cbbRTypeChange(Sender: TObject);
  private
    tempPCardID:string;
    { Private declarations }
    custNo:string;
    endGetPhotoSign:Boolean;
    Function readCardInfo:Boolean;
    procedure edtEnabledT;                    //ʹ�༭��Ϊ����
    procedure resultQuery;                    //��ѯ���
    procedure clearEdt;                       //��ձ༭������
    procedure getPhoto;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhUpdateCardInfo: TfaqhUpdateCardInfo;
  CardID: string;

implementation

uses KsFrameworks, KSClientConsts,KSDataDictionary,SmartCardCommon,filetrans;

{$R *.DFM}

procedure TfaqhUpdateCardInfo.Init;
begin
  inherited;
  btnok.Enabled := false;
  cbbRType.ItemIndex :=0;
  edtEndDate.Enabled := False;
  edtMaxPerDay.Enabled := True;
  edtMaxPercount.Enabled := True;
  try
    KSG_uninit;
    KSG_init(PChar(scIp),scPort,scFuncNo);
    endGetPhotoSign := True;
    //filePath := sAppPath+'nophoto.jpg';
    imgPhoto.Picture.LoadFromFile(sAppPath+'nophoto.jpg');
  except

  end;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaqhUpdateCardInfo.btnOKClick(Sender: TObject);
var
  PCardID: string;
  CardNo:Integer;           //���׿���
  showCardNo:string;        //��ʾ����
  cardEndDate:string;       //��ʹ�ý�������
  feeType:Integer;          //�շ����
  custType:Integer;         //�ͻ����
  custName:string;          //�ͻ�����
  IDCard:string;            //���֤��
  deptNo:string;             //���Ŵ���
  sex:string;               //�Ա�
  stuempNo:string;          //ѧ����
  cardBalance:Integer;      //�����
  cardpwd:string;           //������
  cardTradeNum:Integer;     //�����״���
  patchNO:Integer;          //�������κ�
  certType:string;          //֤������
  maxPerCount:Integer;
  maxPerDay:Integer;
  tradeDate,tradeTime:string;

  cm: TCM;
  cardmoney:LongInt;
  payCnt,dptCnt,subsidyNo:Integer;
  st,stPNo:LongInt;
  rType:string;
  Tof:Integer;
  reError:array[0..128] of char;
  function setCardBalance: Integer;
  var
    tp:TTRANSPACK;
  begin
    //preSetMoney(tp);
    ZeroMemory(@tp,SizeOf(tp));
    //���ÿ����
    //�ն˽������к�
    tp.TermSeqno := 1;
    //�ն˱��
    StrCopy(@tp.Termno,PChar(scSiteNo));
    //���׿���
    tp.CardNo := CardNo;
    //������
    StrCopy(@tp.CardPhyID,PChar(PCardID));
    //��������
    StrCopy(@tp.TransDate,PChar(tradeDate));
    //����ʱ��
    StrCopy(@tp.TransTime,PChar(tradeTime));
    //���׺���
    tp.AftBalance := cardBalance;
    //����ǰ���
    tp.BefBalance := cardmoney;
    //����ǰ��ֵ����
    tp.DptCardCnt := dptCnt;
    //����ǰ���Ѵ���
    tp.PayCardCnt := payCnt;
    //����ǰ��������
    tp.SubsidyNo := subsidyNo;

    Result := ks_setcardbal(@tp);
  end;
begin
  if not preReadCard then
    Exit;
  cm := nil;
  try
    //���¶�ȡ�����ţ��ж��Ƿ��Ҫ���µ�������һ��
    cm := TCM.Create;
    st := cm.card(PCardID);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
      exit;
    end;
    cm.clearallfieldreadmode;
    setOperReadMode(cm);
    cm.readCard(PCardID);
    //PCardID := cm.getCardSeriNo;
    if PCardID<>trim(tempPCardID) then
    begin
      Context.GetDialogSystem.ShowMessage('����ʱ��ʹ��ͬһ�ſ���');
      Exit;
    end;

    rType := Copy(cbbRType.Text,1,Pos('-',cbbRType.Text)-1);
    if (rType='') or (rType='-') then
    begin
      Context.GetDialogSystem.ShowMessage('��ѡ��������ͣ�');
      cbbRType.SetFocus;
      Exit;
    end;

    try
      cardmoney := StrToInt(cm.getCardBalance);
      payCnt := StrToInt(cm.getPayCardCnt);
      dptCnt := StrToInt(cm.getDptCardCnt);
      subsidyNo := StrToInt(cm.getPatchNo);

    except
      cardmoney := 0;
      payCnt := 0;
      dptCnt := 0;
      subsidyNo := 0;
      RzStatusPane1.Caption :='��ȡ����Ϣʧ�ܣ�';
    end;

    WorkView.FieldByName('����').Data.SetInteger(StrToInt(edtCardNo.Text));
    WorkView.FieldByName('������').Data.Setstring(PCardID);
    WorkView.FieldByName('����������').Data.Setstring(edtEndDate.text);
    WorkView.FieldByName('�����').Data.SetInteger(cardmoney);
    WorkView.FieldByName('���״���').Data.SetInteger(payCnt);
    WorkView.FieldByName('��ֵ����').Data.SetInteger(dptCnt);
    WorkView.FieldByName('��������').Data.Setstring(rType);
    if maxPer=1 then
    begin
      try
        WorkView.FieldByName('�뵥���޶�').Data.SetFloat(StrToFloat(edtMaxPercount.text));
        WorkView.FieldByName('�����޶�').Data.SetFloat(StrToFloat(edtMaxPerDay.Text));
      except
        Context.GetDialogSystem.ShowMessage('��������Ч�ĵ����޶�����޶');
        Exit;
      end;
    end
    else
    begin
      WorkView.FieldByName('�����޶�').Data.SetInteger(0);
      WorkView.FieldByName('���޶�').Data.SetInteger(0);
    end;
    MainRequest.SendCommand;
    if WorkView.FieldByName('������').Data.AsInteger=0 then
    begin
      CardNo:=WorkView.fieldbyname('����').Data.AsInteger;
      showCardNo:=WorkView.fieldbyname('��ʾ����').Data.AsString;
      cardEndDate:=WorkView.fieldbyname('����������').Data.AsString;
      feeType:=WorkView.fieldbyname('�շ����').Data.AsInteger;
      custType:=WorkView.fieldbyname('�ͻ����').Data.AsInteger;
      custName:=WorkView.fieldbyname('����').Data.AsString;
      certType:=WorkView.fieldbyname('֤������').Data.AsString;
      IDCard:=WorkView.fieldbyname('֤������').Data.AsString;
      deptNo:=WorkView.fieldbyname('���Ŵ���').Data.AsString;
      sex:=WorkView.fieldbyname('�Ա�').Data.AsString;
      stuempNo:=WorkView.fieldbyname('ѧ����').Data.AsString;
      cardBalance:=WorkView.fieldbyname('�����').Data.AsInteger;
      //isFormation := Char('N');
      cardTradeNum := WorkView.fieldbyname('���״���').Data.AsInteger;
      patchNO  := WorkView.fieldbyname('�������κ�').Data.AsInteger;
      cardpwd := WorkView.fieldbyname('������').Data.AsString;
      tradeDate:=WorkView.fieldbyname('��������').Data.AsString;
      tradeTime:=WorkView.fieldbyname('����ʱ��').Data.AsString;
      if rType='1' then
      begin
        cm.clearallfieldwritemode;
        //setOperWriteMode(cm);
        cm.setCardNo(IntToStr(CardNo));
        cm.setShowCardNo(showCardNo);
        cm.setDeadLineDate(cardEndDate);
        cm.setCardLimitType(IntToStr(feeType));
        cm.setCustType(IntToStr(custType));
        cm.setCertType(certType);
        cm.setCertNo(IDCard);
        cm.setDeptNo(deptNo);
        cm.setCustSex(sex);
        cm.setStuempNo(stuempNo);
        cm.setCustName(custName);
        //cm.setBlackCardSign(IntToStr(NORMAL_CARD));

        //st := CardManage.UpdateCardBasicInfo(PCM);
        //���õ��������޶���������޶�
        if maxper=1 then
        begin
          maxPerCount := WorkView.fieldbyname('�����޶�').Data.AsInteger;
          maxPerDay := WorkView.fieldbyname('���޶�').Data.AsInteger;
          cm.setMaxPerCount(IntToStr(maxPerCount));
          cm.setMaxPerDay(IntToStr(maxPerDay));
          //rst := cardManage.SetConsumeLimit(maxPerCount,maxPerDay);
        end;
        st := cm.writeData(PCardID);
        //tof := setcardbalance;
        if (st<>0) then
        begin
          Context.GetDialogSystem.ShowWarning('���¿���Ϣʧ��--'+ks_geterrmsg(PChar(@reError)));
          exit;
        end;
      end
      else if rType='2' then  //������Ч��
      begin
        cm.clearallfieldwritemode;
        cm.setfieldwritemode(DEADLINE_DATE);
        cm.setDeadLineDate(cardEndDate);
        st := cm.writeData(PCardID);
        if (st<>0) then
        begin
          Context.GetDialogSystem.ShowWarning('���¿���Ч��ʧ��--'+inttostr(st));
          exit;
        end;
      end
      else if rType='3' then  //���¿����������κ�
      begin
        cm.clearallfieldwritemode;
        cm.setfieldwritemode(CARD_CNT);
        cm.setCardCnt(IntToStr(cardTradeNum));
        cm.setPatchNo(IntToStr(patchNO));
        st := cm.writeData(PCardID);
        tof := setcardbalance;
        if (st<>0)or(Tof<>0) then
        begin
          Context.GetDialogSystem.ShowWarning('���¿����ʧ��--'+inttostr(st));
          exit;
        end;
        if stPNo<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('���¿��������κ�ʧ��--'+inttostr(st));
          exit;
        end;
      end
      else if rType='4' then  //��д����Ϣ
      begin
        cm.clearallfieldwritemode;
        setOperWriteMode(cm);

        cm.setCardNo(IntToStr(CardNo));
        cm.setShowCardNo(showCardNo);
        cm.setDeadLineDate(cardEndDate);
        cm.setCardLimitType(IntToStr(feeType));
        cm.setCustType(IntToStr(custType));
        cm.setCertType(certType);
        cm.setCertNo(IDCard);
        cm.setDeptNo(deptNo);
        cm.setCustSex(sex);
        cm.setStuempNo(stuempNo);
        cm.setPatchNo(IntToStr(patchNO));
        cm.setCustName(custName);
        st := cm.writeData(PCardID);
        tof := setcardbalance;
        if (st<>0)or(Tof<>0) then
        begin
          Context.GetDialogSystem.ShowWarning('��д�����ʧ�ܣ���ִ�и�������Ϊ4�Ĳ���--'+inttostr(st));
          exit;
        end;
        if stPNo<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('��д��������Ϣʧ��,����д--'+inttostr(st));
          exit;
        end;

      end
      else if rType='5' then  //��տ���Ϣ
      begin
        {st := cm.clearCard;
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowMessage('��տ���Ϣʧ��--'+inttostr(st));
          Exit;
        end;}
        Context.GetDialogSystem.ShowMessage('û����տ���Ϣ���ܣ�');
        Exit;
      end;
      cm.beep;
      clearEdt;
      imgPhoto.Picture.Assign(nil);
      Context.GetDialogSystem.ShowSuccess('���¿���Ϣ�ɹ���');
    end
    else
    begin
      getreturn('',workview1);
    end;
  finally
    btnok.Enabled := false;
    cm.Destroy;
  end;
end;

procedure TfaqhUpdateCardInfo.btnReadCardQueryClick(Sender: TObject);
begin
  clearEdt;  
  if preReadCard=False then
    Exit;
  if readCardInfo=False then
    Exit;
  custNo := '';
  //getInMoney;
  WorkView1.FieldByName('����').Data.SetInteger(0);
  WorkView1.FieldByName('�ͻ���').Data.SetInteger(0);
  WorkView1.FieldByName('�ͻ����').Data.SetInteger(0);
  WorkView1.FieldByName('�շ����').Data.SetInteger(0);
  WorkView1.FieldByName('Ǯ����').Data.SetInteger(0);
  WorkView1.FieldByName('������').Data.SetString(edtcPhyId.Text);
  WVRequest1.SendCommand;
  if WorkView1.fieldbyname('������').data.AsInteger<>0 then
  begin
    getreturn('',WorkView1);
    exit;
  end;
  resultQuery;
  getPhoto;
  edtEnabledT;
  btnok.enabled := true;
end;

Function TfaqhUpdateCardInfo.readCardInfo():Boolean;
var
  cm: TCM;
  phycardid,cardNo:string;
  st:integer;
  //maxPerCount,maxPerDay:Integer;
begin
  Result := True;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(phycardid);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
      Result := False;
      exit;
    end;
    cm.clearallfieldreadmode;
    setOperReadMode(cm);
    if cm.readCard(phycardid)<>0 then
    begin
      context.GetDialogSystem.ShowMessage('��ȡ����Ϣʧ�ܣ������ԣ�');
      Result := False;
      Exit;
    end;
    {
    phycardid := cm.getCardSeriNo;
    if phycardid='' then
    begin
      context.GetDialogSystem.ShowMessage('��������ʧ�ܣ��ÿ��Ѿ��𻵣�');
      Result:=False;
      Exit;
    end;
    }
    //��ȡ���׿���
    cardNo := cm.getCardNo;
    if cardNo = '' then
      RzStatusPane1.Caption := '��ȡ���׿���ʧ�ܣ�'
    else
      edtcCardNo.Text := cardNo;
    tempPCardID := phycardid;
    //����
    edtcName.Text := cm.getCustName;
    //������
    edtcPhyId.Text := phycardid;
    //֤������
    edtcCertType.Text := cm.getCertType;
    //֤������
    edtcIdCard.Text := cm.getCertNo;
    //ѧ����
    edtcStuempNo.Text := cm.getStuempNo;
    //��������
    edtcEndDate.Text := cm.getDeadLineDate;
    //��ʾ����
    edtcShowNo.Text := cm.getShowCardNo;
    //�շ����
    edtcFeeType.Text := GetIdObjectName(-43,Trim(cm.getCardLimitType));
    //�ͻ����
    edtCCustType.Text := GetIdObjectName(-34,Trim(cm.getCustType));
    //����
    edtCDept.Text := GetIdObjectName(-22,Trim(cm.getDeptNo));
    //�Ա�
    edtCSex.Text := GetIdObjectName(39,Trim(cm.getCustSex));

    edtcBalance.Text := format('%f', [strtoint(cm.getCardBalance) / 100.0]);
    edtCardDptNum.Text := cm.getDptCardCnt;
    edtCPayCnt.Text := cm.getPayCardCnt;
    edtCPatchNo.Text := cm.getPatchNo;
    if maxPer=1 then
    begin
      edtMaxcPerCount.Text := FloatToStr(StrToFloat(cm.getMaxPerCount)/100);
      edtcMaxPerDay.Text := FloatToStr(StrToFloat(cm.getMaxPerDay)/100);
    end
    else
    begin
      edtMaxcPerCount.Text := '��';
      edtcMaxPerDay.Text := '��';
    end;
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhUpdateCardInfo.edtEnabledT;
begin
  //edtEndDate.Enabled:=True;
  edtEndDate.Color:=clwhite;
end;

procedure TfaqhUpdateCardInfo.resultQuery;
var
  tempDataSet: TDataSet;
begin
  try
    tempDataSet := WorkView1.FieldByName('��ѯ�����').Data.AsObject as TDataSet;
    //�ͻ���
    custNo := tempDataSet.FieldByName('lvol1').AsString;
    //���׿���
    edtCardNo.Text := tempDataSet.FieldByName('lvol0').AsString;
    //��ʹ�ý�ֹ����
    edtEndDate.Text := tempDataSet.FieldByName('sdate2').AsString;
    //����
    edtName.Text := tempDataSet.FieldByName('sall_name').AsString;
    //֤������
    edtCertType.Text := tempDataSet.FieldByName('smarket_code').AsString;
    //֤������
    edtIDCard.Text := tempDataSet.FieldByName('semail2').AsString;
    //ѧ����
    edtNo.Text := tempDataSet.FieldByName('spager').AsString;
    //��ʾ����
    edtShowCardNo.Text := tempDataSet.FieldByName('sorder0').AsString;
    //�����
    edtBalance.Text := tempDataSet.FieldByName('damt5').AsString;
    //������
    edtPhyID.Text := tempDataSet.FieldByName('sstation1').AsString;
    //�ͻ����
    edtCustType.Text:= GetIdObjectName(-34,tempDataSet.FieldByName('lsafe_level2').AsString);
    //�շ����
    edtFeeType.Text:=GetIdObjectName(-43,tempDataSet.FieldByName('lvol5').AsString);
    //���ű��
    edtDept.Text := GetIdObjectName(-22,tempDataSet.FieldByName('scert_no').AsString);
    //�Ա�
    edtSex.Text := GetIdObjectName(39,tempDataSet.FieldByName('smarket_code2').AsString);
    //������
    edtPhyID.Text := tempDataSet.fieldbyname('sstation1').AsString;
    //��ֵ����
    edtDptCnt.Text := tempDataSet.fieldbyname('lvol7').AsString;
    //���Ѵ���
    edtPayCnt.Text := tempDataSet.fieldbyname('lvol8').AsString;
    //�������κ�
    edtPatchNo.Text :=  tempDataSet.fieldbyname('lvol10').AsString;
    if maxPer=1 then
    begin
      //���޶�
      edtMaxPerDay.Text :=  tempDataSet.fieldbyname('damt12').AsString;
      //�����޶�
      edtMaxPercount.Text :=  tempDataSet.fieldbyname('damt11').AsString;
    end
    else
    begin
      edtMaxPerCount.Text := '��';
      edtMaxPerDay.Text := '��';
    end;
  except
    on ex:Exception do
      context.GetDialogSystem.ShowMessage(ex.Message);
  end;
end;

procedure TfaqhUpdateCardInfo.clearEdt;
var
  i:Integer;
begin
  for i := 0 to grpCardInfo.ControlCount-1 do
  begin
    if grpCardInfo.Controls[i] is TRzEdit then
      TRzEdit(grpCardInfo.Controls[i]).Text := '';
  end;
  for i := 0 to grpLibInfo.ControlCount-1 do
  begin
    if grpLibInfo.Controls[i] is TRzEdit then
      TRzEdit(grpLibInfo.Controls[i]).Text := '';
  end;
end;

procedure TfaqhUpdateCardInfo.edtShowCardNoKeyPress(Sender: TObject;
  var Key: Char);
begin
  //inherited;
  if inputNum(Key)=False then
    Key := #0;
end;

procedure TfaqhUpdateCardInfo.cbbRTypeChange(Sender: TObject);
var
  rType:string;
begin
  rType := Copy(cbbRType.Text,1,Pos('-',cbbRType.Text)-1);
  if rType='1' then
  begin
    if maxPer=1 then
    begin
      edtMaxPerCount.Enabled := True;
      edtMaxPerDay.Enabled := True;
    end;
  end
  else
  begin
      edtMaxPerCount.Enabled := False;
      edtMaxPerDay.Enabled := False;
  end;
  if rType='2' then
    edtEndDate.Enabled := True
  else
    edtEndDate.Enabled := False;
end;

procedure TfaqhUpdateCardInfo.getPhoto;
var
  dFile:string;
  ret:Integer;
begin
  if showphoto=0 then
    Exit;
  //��ѯ��Ƭǰ�������ǰ����Ƭ��Ϣ
  imgPhoto.Picture := nil;

  if endGetPhotoSign=false then
    Exit;
  {
  try
    //�Ӻ�̨ȡ����Ƭ�����ƣ���Ƭ��Ϊ�ͻ���
    custNo := Grid.DataSource.DataSet.fieldbyname('lvol1').asstring;
  except
    Context.GetDialogSystem.ShowMessage('����ѡ��һ����¼��Ȼ����ȡ��Ƭ��');
    Exit;
  end;
  }
  dFile := 'photo999999.jpg';
  try
    try
      endGetPhotoSign:=false;
      ret := KSG_Downloadphoto_File(custNo,dFile);
      if ret = KSG_SUCCESS then
      begin
        imgPhoto.Picture.LoadFromFile(sAppPath+dFile);
      end
      else
      begin
        imgPhoto.Picture.LoadFromFile(sAppPath+'nophoto.jpg');
        //Context.GetDialogSystem.ShowMessage('�ÿͻ�û����Ƭ��Ϣ-'+inttostr(ret));
        Exit;
      end;
    except
      on e:Exception do
      begin        
        Context.GetDialogSystem.ShowMessage('������Ƭ��Ϣʧ�ܣ��ÿͻ�����û������-'+e.Message);
        Exit;
      end;
    end;
  finally
    endGetPhotoSign:=True;
  end;
  //������Ƭ��ɺ�ɾ��
  //�ڱ��ز����Ƿ����dFile����Ƭ��������ɾ��
  try
    if FileExists(sAppPath+dFile) then
      DeleteFile(sAppPath+dFile);
  except
    //WriteLog('ɾ�� photo999999.jpg ʧ�ܣ����ļ������ڣ�');
  end;
end;

initialization
  TUIStdClassFactory.Create('����Ϣ����', TfaqhUpdateCardInfo);

end.
