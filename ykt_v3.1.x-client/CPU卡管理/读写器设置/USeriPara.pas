unit USeriPara;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  WVCtrls,Db, Mask, RzEdit, RzCmboBx, RzStatus, RzPanel, Buttons, CardDll;

type
  TfaMachinePara = class(TfaInputTemp)
    UIPnlQueryCount: TUIPanel;
    LabRecordCount: TLabel;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    WVLabel1: TWVLabel;
    rgcom: TRadioGroup;
    grpCardInfo: TGroupBox;
    edtPhyID: TRzEdit;
    edtCardNo: TRzEdit;
    edtShowNo: TRzEdit;
    lblOper: TLabel;
    edtVerNo: TRzEdit;
    edtBalack: TRzEdit;
    edtMoney: TRzEdit;
    edtTreadeNum: TRzEdit;
    edtPayCnt: TRzEdit;
    cbbBit: TRzComboBox;
    stat1: TRzStatusBar;
    rzstspn1: TRzStatusPane;
    rzstspn2: TRzStatusPane;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane16: TRzStatusPane;
    RzStatusPane17: TRzStatusPane;
    RzStatusPane18: TRzStatusPane;
    RzStatusPane20: TRzStatusPane;
    RzStatusPane23: TRzStatusPane;
    grpOper: TGroupBox;
    btnOpen: TBitBtn;
    btnClose: TBitBtn;
    btnReadCard: TBitBtn;
    grpCustInfo: TGroupBox;
    RzStatusPane14: TRzStatusPane;
    RzStatusPane13: TRzStatusPane;
    RzStatusPane12: TRzStatusPane;
    RzStatusPane10: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    edtStuempNo: TRzEdit;
    edtName: TRzEdit;
    edtSex: TRzEdit;
    edtIDCard: TRzEdit;
    edtFeeType: TRzEdit;
    edtDept: TRzEdit;
    edtCustType: TRzEdit;
    RzStatusPane15: TRzStatusPane;
    edtEndDate: TRzEdit;
    edtPatchNo: TRzEdit;
    RzStatusPane7: TRzStatusPane;
    edtMaxPerCount: TRzEdit;
    RzStatusPane8: TRzStatusPane;
    edtmaxPerDay: TRzEdit;
    WVLabel2: TWVLabel;
    lblVer: TWVLabel;
    rzstspn3: TRzStatusPane;
    edtCertType: TRzEdit;
    rzstspn5: TRzStatusPane;
    rzstspn6: TRzStatusPane;
    edtCardType: TRzEdit;
    edtCustId: TRzEdit;
    rzstspn7: TRzStatusPane;
    edtStartDate: TRzEdit;
    RzStatusPane21: TRzStatusPane;
    edtTradeDate: TRzEdit;
    cbbpasmSeat: TComboBox;
    WVLabel3: TWVLabel;
    btnKey: TBitBtn;
    btnSetPasm: TBitBtn;
    grp1: TGroupBox;
    RzStatusPane9: TRzStatusPane;
    edtLibStat: TRzEdit;
    RzStatusPane11: TRzStatusPane;
    edtAccMoney: TRzEdit;
    WorkView2: TWorkView;
    WVRequest2: TWVRequest;
    procedure btnOKClick(Sender: TObject);
    procedure btnOpenClick(Sender: TObject);
    procedure btnCloseClick(Sender: TObject);
    procedure SaveToINI;
    procedure OPenFormINI;
    procedure CloseFormINI;
    procedure btnReadCardClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure btnKeyClick(Sender: TObject);
    procedure btnSetPasmClick(Sender: TObject);
  private
   { Private declarations }
   procedure initCardInfoPosi;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faMachinePara: TfaMachinePara;

implementation
uses KSFrameWorks, INIFiles,KSClientConsts,KSDataDictionary,
  UCMqhCardImp, UKey,SmartCardCommon;

{$R *.DFM}

procedure TfaMachinePara.btnOKClick(Sender: TObject);
begin
  SaveToINI;
end;

procedure TfaMachinePara.Init;
var
  my: tinifile;
  tempBit: integer;
  tempCom: integer;
  sPath:string;
  cm:TCM;
  reVer,reBuildDate,desc:string;
  st:Integer;
begin
  inherited;
  ksLicence;
  tempBit:=0;
  tempCom:=0;
  lblVer.Caption := '';
  cm := nil;
  try
    try
      cm := TCM.Create;
      cm.getVersion(reVer,reBuildDate,desc);
      lblVer.Caption := reVer+'-'+rebuildDate;//+'('+desc+')';
    except
      lblVer.Caption := '����̬��汾ʧ��';
    end;
  finally
    cm.Destroy;
  end;
  stat1.Font.Color := clBlue;
  initCardInfoPosi;
  btnOpen.Caption := '&O �򿪴���';
  btnOpen.Width := 120;
  btnClose.Caption := '&C �رմ���';
  btnClose.Width := 120;
  btnReadCard.Caption := '&R ��ȡ����Ϣ';
  btnReadCard.Width := 120;
  sPath := ExtractFilePath(Application.ExeName);
  if fileexists(spath+'..\configs\setPara.ini') = false then
  begin
    context.GetDialogSystem.ShowWarning('��ȡ�����ļ�����');
  end
  else
  begin
    try
      my := tinifile.Create(spath+'..\configs\setPara.ini');
      tempBit := my.ReadInteger('CardPara', 'bit', -1);
      tempCom := my.ReadInteger('CardPara', 'com', -1);
      my.Free;
    except
      context.GetDialogSystem.ShowWarning('����������������Ϣ��������');
    end;
  end;
  cbbBit.Text := IntToStr(tempBit);
  try
    if tempCom=USB_PORT then
      rgcom.ItemIndex := 4
    else
      rgcom.ItemIndex := tempCom-1;
  except
  end;
  sleep(50);
  cbbpasmSeat.ItemIndex := pasmseat-1;
  //����mfone����Կ
  //ShowMessage(smartCardPwd);
  st := setMainWorkKey(smartCardPwd);
  if st<>0 then
    WriteLog('дmfone����Կʧ��-'+inttostr(st));
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
  {
  if not SmartCardPortStatus then
    Exit;
  ks_setcpupara4sam(cbbpasmSeat.ItemIndex+1);
  ks_samcpureset;
  }
end;

procedure TfaMachinePara.btnOpenClick(Sender: TObject);
begin
  rzstspn1.Caption := '';
  if SmartCardPortStatus then
  begin
    rzstspn1.Caption :='�����Ѿ��򿪣�';
    Exit;
  end;
  SaveToINI;
  OPenFormINI;
end;

procedure TfaMachinePara.btnCloseClick(Sender: TObject);
begin
  rzstspn1.Caption := '';
  if not SmartCardPortStatus then
  begin
    rzstspn1.Caption :='û����Ҫ�رյĴ��ڣ�';
    Exit;
  end;
  CloseFormINI;
end;

procedure TfaMachinePara.SaveToINI;
var
  my: tinifile;
  tempBit: integer;
  tempCom: integer;
  spath : string;
begin
  tempBit:=0;
  tempCom:=0;
  try
    tempBit := StrToInt(cbbBit.Text);
    if rgcom.ItemIndex=4 then
      tempCom := USB_PORT
    else
      tempCom := rgcom.ItemIndex+1;
  except
  end;
  sPath := ExtractFilePath(Application.ExeName);
  if fileexists(spath+'..\configs\setPara.ini') = false then
  begin
    context.GetDialogSystem.ShowWarning('��ȡ�����ļ�����');
  end
  else
  begin
    try
      my := tinifile.Create(spath+'..\configs\setPara.ini');
      my.WriteInteger('CardPara', 'bit', tempBit);
      my.WriteInteger('CardPara', 'com', tempCom);
      my.Free;
    except
      context.GetDialogSystem.ShowWarning('д�����ļ�����,�뽫�����ļ�����Ϊ��д״̬��');
    end;
  end;

end;

procedure TfaMachinePara.OPenFormINI;
var
  my: tinifile;
  BaudRate: longint;
  tempCom: integer;
  tempRe: smallint;
  cm: TCM;
  spath:string;
  //pasmCard:TPUBPSAMCARD;
  st:Integer;
begin
  sPath := ExtractFilePath(Application.ExeName);
  BaudRate:=0;
  tempCom:=0;
  //tempRe:=0;
  cm := nil;
  try
    cm := TCM.Create;
    if fileexists(spath+'..\configs\setPara.ini') = false then
    begin
      context.GetDialogSystem.ShowError('��ȡ�����ļ�����');
    end
    else
    begin
      try
        my := tinifile.Create(spath+'..\configs\setPara.ini');
        BaudRate := my.ReadInteger('CardPara', 'bit', -1);
        tempCom := my.ReadInteger('CardPara', 'com', -1);
        my.Free;
      except
        context.GetDialogSystem.ShowWarning('���������ó�ʼ����Ϣ��������');
      end;
    end;

    //�ȹرմ��ڣ�Ȼ���ٴ�
    try
      tempRe := cm.openDevice(tempCom, BaudRate);
    except
      Context.GetDialogSystem.ShowMessage('�򿪴���ʧ��-'+geterrmsg);
      Exit;
    end;
    if tempRe = 0 then
    begin
      rzstspn1.Caption := '�򿪴��ڳɹ�!';
      SmartCardPortStatus := True;
      cm.beep;
      //�򿪴��ڳɹ�������psam����
      {
      ks_setcpupara4sam(cbbpasmSeat.ItemIndex+1);
      st := ks_samcpureset;
      if st<>0 then
      begin
        context.GetDialogSystem.ShowWarning('PSAM����ʧ��-'+geterrmsg);
      end;
      }
    end
    else
    begin
      rzstspn1.Caption :='�򿪴���ʧ�ܣ������д���Ƿ���Լ�ѡ����ȷ�Ĵ��ںͲ�����-'+inttostr(tempRe);
    end;
  finally
    cm.Destroy;
  end;
end;

procedure TfaMachinePara.CloseFormINI;
var
  tempRe: smallint;
  cm: TCM;
begin
  cm:=nil;
  try
    cm := TCM.Create;
    tempRe := cm.closeDevice;
    if tempRe = 0 then
    begin
      //cm.beep;
      rzstspn1.Caption := '�����Ѿ��ر�!';
      SmartCardPortStatus := False;
    end
    else
    begin
      rzstspn1.Caption := '�رմ���ʧ��!';
    end;
  finally
    cm.Destroy;
  end;
end;

procedure TfaMachinePara.btnReadCardClick(Sender: TObject);
var
  cm: TCM;
  st:Integer;
  blackSign:Integer;
  sex:string;
  phyId:string;
  sSt:string;
  tmpdataset:TDataSet;
  //rePhyid : array[0..16] of Char;
begin
  initCardInfoPosi;
  rzstspn1.Caption := '';
  if preReadCard=False then
    Exit;
  
  sSt := readCardOneInfo(APP_TYPE);
  //ShowMessage('@'+sSt+'@');
  if sSt='0' then
  begin
    context.GetDialogSystem.ShowMessage('�ÿ�û�г�ʼ�������ȳ�ʼ����');
    exit;
  end;
  blackSign := 0;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ��-'+geterrmsg);
      exit;
    end;
    //��������еĶ�ȡȨ��
    cm.clearallfieldreadmode;
    //����Ҫ��ȡ���ݵ�Ȩ��
    setOperReadMode(cm);
    //cm.card(phyId);
    st := cm.readCard(phyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ����Ϣʧ��-'+geterrmsg);
      Exit;
    end;
    edtPhyID.Text := cm.getCardSeriNo;
    sex := cm.getCustSex;
    if Trim(sex)='1' then
      sex := '��'
    else if Trim(sex)='2' then
      sex := 'Ů'
    else
      sex := '';
    //���׿���
    edtCardNo.Text := cm.getCardNo;
    //��ʾ����
    edtShowNo.Text :=  cm.getShowCardNo;//Trim(Copy(PCM.ShowCardNo,1,10));
    //��������
    edtEndDate.Text := cm.getDeadLineDate;
    //�շ����
    edtFeeType.Text := GetIdObjectName(-43,cm.getCardLimitType);
    //�����
    edtCardType.Text := GetIdObjectName(-5,cm.getCardType);
    //�ͻ����
    edtCustType.Text := GetIdObjectName(-34,Trim(cm.getCustType));
    //�ͻ���
    edtCustId.Text := cm.getCustNo;
    //����
    edtName.Text := cm.getCustName;
    //֤������
    edtCertType.Text := GetIdObjectName(87,Trim(cm.getCertType));
    //֤������
    edtIDCard.Text := cm.getCertNo;
    //����
    edtDept.Text := GetIdObjectName(-22,Trim(cm.getDeptNo));
    //�ձ�
    edtSex.Text := sex;
    //ѧ����
    edtStuempNo.Text := cm.getStuempNo;
    //�汾��
    edtVerNo.Text := cm.getBlackVer;
    //��������
    edtStartDate.Text := cm.getStartUseDate;
    //ShowMessage(cm.getCardPwd);
    //������,û�����ö�ģʽ�����ܶ�ȡ��
    //edtPwd.Text := '123456';//cm.getCardPwd;
    //�Ƿ�ڿ�
    try
      blackSign := StrToInt(cm.getBlackCardSign);
    except
    end;
    if blackSign=NORMAL_CARD then
    begin
      edtBalack.Text := '����';
      edtBalack.Font.Color := clBlack;
      edtVerNo.Font.Color := clBlack;
    end
    else
    begin
      edtBalack.Font.Color := clRed;
      edtVerNo.Font.Color := clRed;
      if blackSign=LOCK_CARD then
        edtBalack.Text := '����'
      else if blackSign=LOSE_CARD then
        edtBalack.Text := '��ʧ'
      else  if blackSign=FREEZE_CARD then
        edtBalack.Text := '����'
      else  if blackSign=DESTORY then
        edtBalack.Text := '����'
      else if blackSign=DEAL_CARD then
        edtBalack.Text := '����'
      else if blackSign=FEE_LOCK_CARD then
        edtBalack.Text := '�󸶷�����'
      else
        edtBalack.Text := IntToStr(blackSign);
    end;
    //���κ�-----------����
    edtPatchNo.Text := cm.getPatchNo;
    try
      edtMoney.Text := format('%f', [strtofloat(cm.getCardBalance) / 100.0]);
    except

    end;
    edtTreadeNum.Text := cm.getDptCardCnt;
    edtPayCnt.Text := cm.getPayCardCnt;
    //edtPatchCnt.Text := cm.getSsdCardCnt;
    edtTradeDate.Text := cm.getTransDate;
    //��ȡ���������޶���������޶�
    if maxPer=1 then
    begin
      try
        edtMaxPerCount.Text := FloatToStr(StrToFloat(cm.getMaxPerCount)/100);
        edtmaxPerDay.Text := FloatToStr(StrToFloat(cm.getMaxPerDay)/100);
      except

      end;
    end
    else
    begin
      edtMaxPerCount.Text := '��';
      edtmaxPerDay.Text := '��';
    end;
    try
      WorkView2.FieldByName('����').Data.SetInteger(StrToInt(edtCardNo.Text));
      WorkView2.FieldByName('�ͻ���').Data.SetInteger(0);
      WorkView2.FieldByName('�ͻ����').Data.SetInteger(0);
      WorkView2.FieldByName('�շ����').Data.SetInteger(0);
      WorkView2.FieldByName('Ǯ����').Data.SetInteger(0);
      WorkView2.FieldByName('������').Data.SetString(edtPhyId.Text);
      WVRequest2.SendCommand;
      if WorkView2.fieldbyname('������').data.AsInteger=0 then
      begin
        tmpdataset := TDataSet(WorkView2.FieldByName('��ѯ�����').Data.AsObject);
        //�����
        edtAccMoney.Text := tmpdataset.FieldByName('damt5').AsString;
        //��״̬
        edtLibStat.Text := GetIdObjectName(17,tmpdataset.FieldByName('sserial0').AsString);
        //exit; sserial0
      end;

    except
    end;
  finally
    cm.Destroy;
  end;
end;

procedure TfaMachinePara.btnCancelClick(Sender: TObject);
begin
  Close;
end;

procedure TfaMachinePara.initCardInfoPosi;
var
  i:Integer;
begin
  for i := 0 to grpCardInfo.ControlCount-1 do
  begin
    if grpCardInfo.Controls[i] is TRzEdit then
      TRzEdit(grpCardInfo.Controls[i]).Text := '';
  end;
  for i := 0 to grpCustInfo.ControlCount-1 do
  begin
    if grpCustInfo.Controls[i] is TRzEdit then
      TRzEdit(grpCustInfo.Controls[i]).Text := '';
  end;
  for i := 0 to grp1.ControlCount-1 do
  begin
    if grp1.Controls[i] is TRzEdit then
      TRzEdit(grp1.Controls[i]).Text := '';
  end;

end;

procedure TfaMachinePara.btnKeyClick(Sender: TObject);
var
  st:Integer;
  vkey :string;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
begin
  if not preReadCard then
    Exit;
  st := ks_checkloadkeys;
  if st=1 then
  begin
    Context.GetDialogSystem.ShowMessage('��Կ���Ѿ���ȡ��');
    Exit;
  end
  else
  begin
    try
      frmKey := TfrmKey.Create(nil);
      frmKey.ShowModal;
      vKey := frmKey.getPwd;
    finally
      frmKey.Free;
    end;
    st := ks_loadcardkeys(PChar(vKey));
    if st <>0 then
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      Context.GetDialogSystem.ShowMessage(reSt);
      //Context.GetDialogSystem.ShowMessage('װ����Կʧ�ܣ����ȷ�����Կ��--'+inttostr(st));
      Exit;
    end;
    rzstspn1.Caption := '��Կ����ȡ�ɹ�';
    KNG_beep;
  end;
end;

procedure TfaMachinePara.btnSetPasmClick(Sender: TObject);
var
  st:Integer;
  my:TIniFile;
begin
  if not SmartCardPortStatus then
    Exit;
  ks_setcpupara4sam(cbbpasmSeat.ItemIndex+1);
  st := ks_samcpureset;
  if st<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('PSAM������ʧ��-'+inttostr(st));
    Exit;
  end;
  KNG_beep;
  try
    my := tinifile.Create(sAppPath+'..\configs\setPara.ini');
    my.WriteInteger('psamseat', 'psamseat', cbbpasmSeat.ItemIndex+1);
    my.Free;
  except
    context.GetDialogSystem.ShowWarning('д�����ļ�����,�뽫�����ļ�����Ϊ��д״̬��');
  end;
  rzstspn1.Caption := 'PSAM�������óɹ�';
end;

initialization
  TUIStdClassFactory.Create('��д����Ȩ', TfaMachinePara);

end.
